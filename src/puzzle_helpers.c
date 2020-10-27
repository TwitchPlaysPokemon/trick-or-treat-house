#include "global.h"
#include "global.fieldmap.h"
#include "event_data.h"
#include "alloc.h"
#include "script.h"
#include "puzzle_helpers.h"
#include "sound.h"
#include "field_camera.h"
#include "field_message_box.h"
#include "field_player_avatar.h"
#include "fieldmap.h"
#include "palette.h"
#include "random.h"
#include "strings.h"
#include "string_util.h"
#include "text.h"
#include "task.h"
#include "mgba.h"
#include "trickhouse.h"
#include "script.h"
#include "pokeblock.h"
#include "pokemon_storage_system.h"
#include "event_object_movement.h"
#include "overworld.h"
#include "script_movement.h"
#include "constants/maps.h"
#include "constants/flags.h"
#include "constants/metatile_labels.h"
#include "constants/songs.h"
#include "constants/event_objects.h"
#include "constants/map_groups.h"
#include "constants/vars.h"
#include "constants/species.h"

// Reference to an assembly defined constant, the start of the ROM
// We don't actually use the value, just the address it's at.
extern const int Start;

extern const u8* gRamScriptPtr;

// Some common debugging helpers

void PrintData0(struct ScriptContext *ctx)
{
	ConvertIntToHexStringN(gStringVar1, ctx->data[0], STR_CONV_MODE_LEADING_ZEROS, 8);
}

void PrintData1(struct ScriptContext *ctx)
{
	ConvertIntToHexStringN(gStringVar1, ctx->data[1], STR_CONV_MODE_LEADING_ZEROS, 8);
}

extern u8* gSelect_RulesTable[];
extern u8* gSelect_RulesTable_End[];
void SetSelectVariables(struct ScriptContext *ctx)
{
	// Get the last rule discovered
	int last = GetGameStat(GAME_STAT_RULES_DISCOVERED);
	// Get the max rules discovered
	int max = 4 + (2 * GetGameStat(GAME_STAT_NUM_PUZZLES_COMPLETED));
	max = min(max, (gSelect_RulesTable_End - gSelect_RulesTable)/4);
	
	// If we haven't discovered some new rules, display the next undiscovered one
	if (last < max) {
		gSpecialVar_0x800B = last;
		IncrementGameStat(GAME_STAT_RULES_DISCOVERED);
	} 
	// If we've discovered them all, select one at random to display
	else {
		gSpecialVar_0x800B = (Random() % max);
	}
	gSpecialVar_0x800A = GetGameStat(GAME_STAT_SELECT_PRESSES);
}


u16 GetPlayerState(void)
{
    if (TestPlayerAvatarFlags(PLAYER_AVATAR_FLAG_ACRO_BIKE)) return 1;
    if (TestPlayerAvatarFlags(PLAYER_AVATAR_FLAG_MACH_BIKE)) return 2;
    if (TestPlayerAvatarFlags(PLAYER_AVATAR_FLAG_SURFING)) return 3;
    if (TestPlayerAvatarFlags(PLAYER_AVATAR_FLAG_UNDERWATER)) return 4;
    return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Puzzle: Scale the Belfry
// 

extern u8 gStringWorking[0x100];
void BORTizeBufferedStrings(struct ScriptContext *ctx)
{
	StringCopy(gStringWorking, gStringVar1);
	StringUppercase(gStringVar1, gStringWorking);
	
	StringCopy(gStringWorking, gStringVar2);
	StringUppercase(gStringVar2, gStringWorking);
	
	StringCopy(gStringWorking, gStringVar3);
	StringUppercase(gStringVar3, gStringWorking);
}


///////////////////////////////////////////////////////////////////////////////
// Puzzle: Pokemon Says 
// MAP_PUZZLE_MUSIC_NOTE_TILES

#define FLAG_HIDE_SCROLL            FLAG_PUZZLE_20
#define FLAG_TILES_ACTIVE           FLAG_PUZZLE_21
#define FLAG_HIDE_SINGERS           FLAG_PUZZLE_22
#define FLAG_SHOW_EXTRA_SINGER      FLAG_PUZZLE_23
#define FLAG_EXTRA_ENABLED     FLAG_PUZZLE_24
#define VAR_CURR_SONG               VAR_PUZZLE_00
#define VAR_NUM_CORRECT_STEPS       VAR_PUZZLE_01
#define VAR_TARGET_TILE             VAR_PUZZLE_02
#define VAR_SONG_COMPLETION_STATE   VAR_PUZZLE_03
#define VAR_SONG_A                  VAR_PUZZLE_0A
#define VAR_SONG_B                  VAR_PUZZLE_0B
#define VAR_SONG_C                  VAR_PUZZLE_0C
#define VAR_SONG_D                  VAR_PUZZLE_0D

struct PokemonSaysNote {
	u8 localId;
	u16 metaTileId;
	u16 soundEffect;
	const u8* movement;
};

enum {
	PS_NOTE_END,
	PS_NOTE_C,
	PS_NOTE_D,
	PS_NOTE_E,
	PS_NOTE_F,
	PS_NOTE_G,
	PS_NOTE_A,  // Unavailable
	PS_NOTE_B,  // Unavailable
	PS_NOTE_C1, // Unavailable
};

extern const u8 Common_Movement_EmoteNoteC[];
extern const u8 Common_Movement_EmoteNoteD[];
extern const u8 Common_Movement_EmoteNoteE[];
extern const u8 Common_Movement_EmoteNoteF[];
extern const u8 Common_Movement_EmoteNoteG[];
extern const u8 Puzzle_MusicNoteTiles_ExtraCurious[];

const struct PokemonSaysNote sSongNotes[] = {
	[PS_NOTE_END] = { 0, 0, MUS_DUMMY, NULL },
	[PS_NOTE_C] = { 2, 0x2C0, SE_TOY_C, Common_Movement_EmoteNoteC },
	[PS_NOTE_D] = { 3, 0x2C1, SE_TOY_D, Common_Movement_EmoteNoteD },
	[PS_NOTE_E] = { 4, 0x2C2, SE_TOY_E, Common_Movement_EmoteNoteE },
	[PS_NOTE_F] = { 5, 0x2C3, SE_TOY_F, Common_Movement_EmoteNoteF },
	[PS_NOTE_G] = { 6, 0x2C4, SE_TOY_G, Common_Movement_EmoteNoteG },
	[PS_NOTE_A] = { 7, 0x000, SE_TOY_A, Common_Movement_EmoteNoteC },
	[PS_NOTE_B] = { 7, 0x000, SE_TOY_B, Common_Movement_EmoteNoteD },
	[PS_NOTE_C1]= { 7, 0x000, SE_TOY_C1,Common_Movement_EmoteNoteE },
};

#define NOTE(l, length)   ((PS_NOTE_##l << 8) | length)

static const u16 Puzzle_MusicNoteTiles_MusicTableA[][4] = {
	{ NOTE(E, 60), NOTE(G, 30), NOTE(D, 30), PS_NOTE_END }, // Zelda's Lullaby
	{ NOTE(G, 20), NOTE(E, 20), NOTE(D, 30), PS_NOTE_END }, // Epona's Song
	{ NOTE(C, 20), NOTE(E, 20), NOTE(G, 30), PS_NOTE_END }, // Siara's Song
	{ NOTE(E, 20), NOTE(D, 20), NOTE(G, 30), PS_NOTE_END }, // Sun's Song
	{ NOTE(C, 30), NOTE(G, 30), NOTE(D, 30), PS_NOTE_END }, // Undertale's Motif (first 3 notes)
};
static const u16 Puzzle_MusicNoteTiles_MusicTableB[][5] = {
	{ NOTE(E, 30), NOTE(D, 60), NOTE(G, 30), NOTE(C, 30), PS_NOTE_END }, 
	{ NOTE(D, 30), NOTE(F, 30), NOTE(E, 30), NOTE(F, 30), PS_NOTE_END }, 
	{ NOTE(C, 15), NOTE(C, 15), NOTE(C, 15), NOTE(E, 30), PS_NOTE_END }, // Pokemon Item Pickup
	{ NOTE(D, 25), NOTE(F, 25), NOTE(E, 25), NOTE(C, 30), PS_NOTE_END }, // Bad Katinss's Motif
};
static const u16 Puzzle_MusicNoteTiles_MusicTableC[][6] = {
	{ NOTE(C, 20), NOTE(E, 20), NOTE(D, 20), NOTE(G, 20), NOTE(E, 30), PS_NOTE_END }, // Mystery Dungeon Theme
	{ NOTE(C, 20), NOTE(D, 20), NOTE(E, 20), NOTE(F, 20), NOTE(G, 30), PS_NOTE_END }, // Mystery Dungeon Dream / Scale
	{ NOTE(G, 30), NOTE(C, 60), NOTE(F, 15), NOTE(E, 15), NOTE(D, 30), PS_NOTE_END }, 
	{ NOTE(F, 15), NOTE(E, 15), NOTE(D, 60), NOTE(E, 60), NOTE(C, 30), PS_NOTE_END }, 
	{ NOTE(F, 15), NOTE(G, 15), NOTE(D, 20), NOTE(C, 25), NOTE(E, 30), PS_NOTE_END }, // Bad Close Encounters Theme
};
static const u16 Puzzle_MusicNoteTiles_MusicTableD[][7] = {
	{ NOTE(G, 30), NOTE(G, 30), NOTE(F, 30), NOTE(E, 30), NOTE(D, 30), NOTE(E, 30), PS_NOTE_END }, // Wind's Aria
	{ NOTE(C, 15), NOTE(G, 15), NOTE(E, 60), NOTE(D, 15), NOTE(E, 15), NOTE(D, 30), PS_NOTE_END }, // Minuet of Forest
	{ NOTE(E, 20), NOTE(E, 20), NOTE(D, 10), NOTE(E, 20), NOTE(G, 20), NOTE(E, 30), PS_NOTE_END }, // Power Ranger's Theme
	// { NOTE(C, 45), NOTE(G, 45), NOTE(D, 60), NOTE(E, 45), NOTE(G, 45), NOTE(C, 30), PS_NOTE_END }, // Bad Undertale's Motif
	{ NOTE(G, 15), NOTE(E, 15), NOTE(C, 30), NOTE(E, 30), NOTE(G, 30), NOTE(C1, 30), PS_NOTE_END }, // US National Anthem Start
};


void PokemonSaysInitPuzzle(struct ScriptContext *ctx)
{
	if (FlagGet(FLAG_SYS_RANDOM_DISABLED)) {
		// VarSet(VAR_CURR_SONG, 3);
		VarSet(VAR_SONG_A, 2);
		VarSet(VAR_SONG_B, 0);
		VarSet(VAR_SONG_C, 1);
		VarSet(VAR_SONG_D, 3);
	} else {
		VarSet(VAR_SONG_A, Random() % ARRAY_COUNT(Puzzle_MusicNoteTiles_MusicTableA));
		VarSet(VAR_SONG_B, Random() % ARRAY_COUNT(Puzzle_MusicNoteTiles_MusicTableB));
		VarSet(VAR_SONG_C, Random() % ARRAY_COUNT(Puzzle_MusicNoteTiles_MusicTableC));
		VarSet(VAR_SONG_D, Random() % ARRAY_COUNT(Puzzle_MusicNoteTiles_MusicTableD));
	}
	mgba_printf(MGBA_LOG_INFO, "Selected songs: %d, %d, %d, %d", VarGet(VAR_SONG_A), VarGet(VAR_SONG_B), VarGet(VAR_SONG_C), VarGet(VAR_SONG_D));
}

const u16* PokemonSays_GetCurrentSong()
{
	switch (VarGet(VAR_CURR_SONG)) {
		default: 
		case 0: return Puzzle_MusicNoteTiles_MusicTableA[VarGet(VAR_SONG_A)];
		case 1: return Puzzle_MusicNoteTiles_MusicTableB[VarGet(VAR_SONG_B)];
		case 2: return Puzzle_MusicNoteTiles_MusicTableC[VarGet(VAR_SONG_C)];
		case 3: return Puzzle_MusicNoteTiles_MusicTableD[VarGet(VAR_SONG_D)];
	}
}


extern u8 gStringWorking[];
void PokemonSaysSetupSongScript(struct ScriptContext *ctx)
{
	u8 i = 0, lastSingId = 0;
	u8* script = AllocZeroed(100); // (13 * numNotes) + 2 (max 6 notes = 80 bytes max)
	const u16* music = PokemonSays_GetCurrentSong();
	
	mgba_printf(MGBA_LOG_INFO, "Creating RAM script for song at %08X...", music);
	// Create a RAM script to play the music
	script[i++] = 0x00;
	for (i = 0; (*music) != PS_NOTE_END; music++)
	{
		u8 noteIndex = ((*music) >> 8) & 0xFF;
		u16 noteLen = (*music) & 0xFF;
		const struct PokemonSaysNote* note = &sSongNotes[noteIndex];
		
		// applymovement(localId, movementScript)
		mgba_printf(MGBA_LOG_INFO, "applymovement(%d, %08X)", note->localId, note->movement);
		script[i++] = 0x4F;
		script[i++] = ((note->localId) >> 0) & 0xFF;
		script[i++] = ((note->localId) >> 8) & 0xFF;
		script[i++] = (((u32)note->movement) >>  0) & 0xFF;
		script[i++] = (((u32)note->movement) >>  8) & 0xFF;
		script[i++] = (((u32)note->movement) >> 16) & 0xFF;
		script[i++] = (((u32)note->movement) >> 24) & 0xFF;
		// playse(sound)
		mgba_printf(MGBA_LOG_INFO, "playse(%d)", note->soundEffect);
		script[i++] = 0x2F;
		script[i++] = ((note->soundEffect) >> 0) & 0xFF;
		script[i++] = ((note->soundEffect) >> 8) & 0xFF;
		// delay(noteLength)
		mgba_printf(MGBA_LOG_INFO, "delay(%d)", noteLen);
		script[i++] = 0x28;
		script[i++] = ((noteLen) >> 0) & 0xFF;
		script[i++] = ((noteLen) >> 8) & 0xFF;
		
		if (noteIndex > PS_NOTE_G) {
			FlagSet(FLAG_EXTRA_ENABLED);
		}
		
		// ConvertIntToHexStringN(gStringVar1, (u32)note, STR_CONV_MODE_LEADING_ZEROS, 8);
		// script[i++] = 0x67; // message
		// script[i++] = (((u32) Puzzle_MusicNoteTiles_TEST) >>  0) & 0xFF;
		// script[i++] = (((u32) Puzzle_MusicNoteTiles_TEST) >>  8) & 0xFF;
		// script[i++] = (((u32) Puzzle_MusicNoteTiles_TEST) >> 16) & 0xFF;
		// script[i++] = (((u32) Puzzle_MusicNoteTiles_TEST) >> 24) & 0xFF;
		// script[i++] = 0x66; // waitmessage
		// script[i++] = 0x6d; // waitbuttonpress
	}
	
	if (FlagGet(FLAG_EXTRA_ENABLED) && !FlagGet(FLAG_SHOW_EXTRA_SINGER))
	{
		mgba_printf(MGBA_LOG_INFO, "call(Puzzle_MusicNoteTiles_ExtraCurious)");
		script[i++] = 0x04;
		script[i++] = (((u32)Puzzle_MusicNoteTiles_ExtraCurious) >>  0) & 0xFF;
		script[i++] = (((u32)Puzzle_MusicNoteTiles_ExtraCurious) >>  8) & 0xFF;
		script[i++] = (((u32)Puzzle_MusicNoteTiles_ExtraCurious) >> 16) & 0xFF;
		script[i++] = (((u32)Puzzle_MusicNoteTiles_ExtraCurious) >> 24) & 0xFF;
	} else {
		script[i++] = 0x28; // delay(60)
		script[i++] = ((60) >> 0) & 0xFF;
		script[i++] = ((60) >> 8) & 0xFF;
	}
	
	mgba_printf(MGBA_LOG_INFO, "return");
	script[i++] = 0x03; // return
	mgba_printf(MGBA_LOG_INFO, "end");
	script[i++] = 0x02; // end
	
	gRamScriptPtr = (const u8*) script;
	
	// gSpecialVar_Result = InitRamScript_NoEventObject(script, i);
}

void PokemonSaysTeardownSongScript(struct ScriptContext *ctx)
{
	Free((void*) gRamScriptPtr);
	gRamScriptPtr = NULL;
}

void PokemonSaysPlayExtraNote(struct ScriptContext *ctx)
{
	u16 curStep = VarGet(VAR_NUM_CORRECT_STEPS);
	const u16* music = PokemonSays_GetCurrentSong();
	const struct PokemonSaysNote* correctNote;
	
	if (!FlagGet(FLAG_TILES_ACTIVE))
    {
        PlaySE(SE_HAZURE);
		gSpecialVar_Result = FALSE;
        return;
    }
	correctNote = &sSongNotes[music[curStep] >> 8];
    if (VarGet(VAR_LAST_TALKED) == correctNote->localId)
	{
		ScriptMovement_StartObjectMovementScript(correctNote->localId, gSaveBlock1Ptr->location.mapNum, gSaveBlock1Ptr->location.mapGroup, correctNote->movement);
		PlaySE(correctNote->soundEffect);
		if (music[curStep+1] >> 8 != PS_NOTE_END)
        {
            VarSet(VAR_NUM_CORRECT_STEPS, curStep + 1);
        }
        else
        {
            if (VarGet(VAR_CURR_SONG) < 3)
                VarSet(VAR_SONG_COMPLETION_STATE, 1);
            else
                VarSet(VAR_SONG_COMPLETION_STATE, 2);

            FlagClear(FLAG_TILES_ACTIVE);
        }
		gSpecialVar_Result = TRUE;
	}
    else
    {
        PlaySE(SE_HAZURE);
        // FlagClear(FLAG_TILES_ACTIVE);
        VarSet(VAR_NUM_CORRECT_STEPS, 0);
		gSpecialVar_Result = FALSE;
    }
}

static void PlayPuzzleMusicTileNote(u32 metatileId)
{
	u8 i;
	for (i = 0; i < ARRAY_COUNT(sSongNotes); i++)
	{
		if (sSongNotes[i].metaTileId == metatileId)
		{
			PlaySE(sSongNotes[i].soundEffect);
        	break;
		}
	}
}

void HandlePuzzleMusicTileStep(u32 metatileId)
{
    u16 curStep = VarGet(VAR_NUM_CORRECT_STEPS);
	const u16* music = PokemonSays_GetCurrentSong();
	const struct PokemonSaysNote* correctNote;

    if (!FlagGet(FLAG_TILES_ACTIVE))
    {
        PlayPuzzleMusicTileNote(metatileId);
        return;
    }

	correctNote = &sSongNotes[music[curStep] >> 8];
    if (metatileId == correctNote->metaTileId)
    {
        PlayPuzzleMusicTileNote(metatileId);
        if (music[curStep+1] >> 8 != PS_NOTE_END)
        {
            VarSet(VAR_NUM_CORRECT_STEPS, curStep + 1);
        }
        else
        {
            if (VarGet(VAR_CURR_SONG) < 3)
                VarSet(VAR_SONG_COMPLETION_STATE, 1);
            else
                VarSet(VAR_SONG_COMPLETION_STATE, 2);

            FlagClear(FLAG_TILES_ACTIVE);
        }
    }
    else
    {
        PlaySE(SE_HAZURE);
        // FlagClear(FLAG_TILES_ACTIVE);
        VarSet(VAR_NUM_CORRECT_STEPS, 0);
    }
}


#undef FLAG_HIDE_SCROLL
#undef FLAG_TILES_ACTIVE
#undef FLAG_HIDE_SINGERS
#undef FLAG_SHOW_EXTRA_SINGER
#undef FLAG_EXTRA_ENABLED
#undef VAR_CURR_SONG
#undef VAR_NUM_CORRECT_STEPS
#undef VAR_TARGET_TILE
#undef VAR_SONG_COMPLETION_STATE
#undef VAR_SONG_A
#undef VAR_SONG_B
#undef VAR_SONG_C
#undef VAR_SONG_D

///////////////////////////////////////////////////////////////////////////////
// Puzzle: Waterflow Caverns 
// MAP_PUZZLE_WATER_TEMPLE

#define X (x+7)
#define Y (y+7)

// VAR_0x8001 => 0 = make random currents, 1 = lower water level, 2 = almost drained
void WaterTempleDrainTo1(struct ScriptContext *ctx)
{
	int x, y, mtid;
	for (y = 14; y < 26; y++) {
		for (x = 32; x < 48; x++) {
			mtid = MapGridGetMetatileIdAt(X, Y);
			if (gSpecialVar_0x8001 == 1) {
				// Lower water level around rocks
				switch (mtid) {
					case 0x23A: mtid = 0x222; break;
					case 0x242: mtid = 0x22A; break;
					case 0x24A: mtid = 0x232; break;
					case 0x249: mtid = 0x231; break;
					case 0x248: mtid = 0x230; break;
					case 0x240: mtid = 0x228; break;
					case 0x238: mtid = 0x220; break;
					case 0x239: mtid = 0x221; break;
				}
			} 
			else if (gSpecialVar_0x8001 == 2) {
				// Lower water level around rocks
				switch (mtid) {
					case 0x222: mtid = 0x252; break;
					case 0x22A: mtid = 0x25A; break;
					case 0x232: mtid = 0x262; break;
					case 0x231: mtid = 0x261; break;
					case 0x230: mtid = 0x260; break;
					case 0x228: mtid = 0x258; break;
					case 0x220: mtid = 0x250; break;
					case 0x221: mtid = 0x251; break;
					case 0x21E: case 0x207: case 0x206: case 0x21F:
					case 0x170: mtid = 0x19E; break;
				}
			}
			else {
				if (mtid == 0x170 && (Random() % 3) == 0) {
					if (y >= 15 && y <= 21) mtid = 0x207;
					else mtid = 0x21E;
				}
			}
			MapGridSetMetatileIdAt(X, Y, mtid);
		}
	}
	DrawWholeMapView();
}

// VAR_0x8001 => 0 = make random currents, 1 = lower water level, 2 = almost drained
void WaterTempleDrainTo2(struct ScriptContext *ctx)
{
	int x, y, mtid;
	for (y = 8; y < 20; y++) {
		for (x = 23; x < 40; x++) {
			mtid = MapGridGetMetatileIdAt(X, Y);
			if (gSpecialVar_0x8001 == 1) {
				// Lower water level around rocks
				switch (mtid) {
					case 0x23D: mtid = 0x225; break;
					case 0x245: mtid = 0x22D; break;
					case 0x24D: mtid = 0x235; break;
					case 0x24C: mtid = 0x234; break;
					case 0x24B: mtid = 0x233; break;
					case 0x243: mtid = 0x22B; break;
					case 0x23B: mtid = 0x223; break;
					case 0x23C: mtid = 0x224; break;
				}
			} 
			else if (gSpecialVar_0x8001 == 2) {
				// Lower water level around rocks
				switch (mtid) {
					case 0x225: mtid = 0x257; break;
					case 0x22D: mtid = 0x25F; break;
					case 0x235: mtid = 0x267; break;
					case 0x234: mtid = 0x24F; break;
					case 0x233: mtid = 0x266; break;
					case 0x22B: mtid = 0x25E; break;
					case 0x223: mtid = 0x256; break;
					case 0x224: mtid = 0x24E; break;
				}
				switch (mtid) {
					case 0x21E: case 0x207: case 0x206: case 0x21F:
					case 0x170: {
						if (y == 8) 
							mtid = (x >= 33 && x <= 36)? 0x207 : 0x19E; 
						else if (y <= 11)
							mtid = (x <= 36)? 0x21E : 0x19E; 
						else
							mtid = (x <= 25)? 0x207 : 0x19E; 
					} break;
				}
			}
			else {
				if (mtid == 0x170 && (Random() % 3) == 0) {
					if (x <= 29) mtid = 0x207;
					else mtid = 0x21E;
				}
			}
			MapGridSetMetatileIdAt(X, Y, mtid);
		}
	}
	DrawWholeMapView();
}

// VAR_0x8001 => 0 = make random currents, 1 = remove random currents, 2 = convert sand, 3 = convert to water, 4 = fill
void WaterTempleFillTo1(struct ScriptContext *ctx)
{
	int x, y, mtid;
	for (y = 19; y < 31; y++) {
		for (x = 27; x < 44; x++) {
			mtid = MapGridGetMetatileIdAt(X, Y);
			if (gSpecialVar_0x8001 == 4) {
				// Raise water level around rocks
				switch (mtid) {
					case 0x204: mtid = 0x22C; break;
					case 0x21C: mtid = 0x234; break;
					case 0x21B: mtid = 0x233; break;
					case 0x213: mtid = 0x22B; break;
				}
			} 
			else if (gSpecialVar_0x8001 == 3) {
				// convert shallows to water
				switch (mtid) {
					case 0x19E:
					case 0x1AF:
					case 0x1B7:
					case 0x1BF:
					case 0x1BE:
					case 0x1BD:
					case 0x1B5:
					case 0x1AD:
					case 0x1AE: mtid = 0x170; break;
					case 0x24F: mtid = 0x21C; break;
					case 0x266: mtid = 0x21B; break;
					case 0x25E: mtid = 0x213; break;
				}
			}
			else if (gSpecialVar_0x8001 == 2) {
				// convert sand to shallows
				switch (mtid) {
					case 0x121: mtid = 0x19E; break;
					case 0x11D: mtid = 0x1AF; break;
					case 0x125: mtid = 0x1B7; break;
					case 0x12D: mtid = 0x1BF; break;
					case 0x12C: mtid = 0x1BE; break;
					case 0x12B: mtid = 0x1BD; break;
					case 0x295:
					case 0x123: mtid = 0x1B5; break;
					case 0x11B: mtid = 0x1AD; break;
					case 0x11C: mtid = 0x1AE; break;
					case 0x264: mtid = 0x24F; break;
					case 0x263: mtid = 0x266; break;
					case 0x25B: mtid = 0x25E; break;
				}
			}
			else if (gSpecialVar_0x8001 == 1) {
				if ((mtid == 0x206 || mtid == 0x21F) && (Random() % 3) == 0) {
					mtid = 0x170;
				}
			}
			else {
				if (mtid == 0x170 && (Random() % 3) == 0) {
					if (x <= y - 6) mtid = 0x207;
					else mtid = 0x21F;
				}
			}
			MapGridSetMetatileIdAt(X, Y, mtid);
		}
	}
	DrawWholeMapView();
}

// VAR_0x8001 => 0 = make random currents, 1 = remove random currents, 2 = convert sand, 3 = convert to water, 4 = fill
void WaterTempleFillTo0(struct ScriptContext *ctx)
{
	int x, y, mtid;
	for (y = 22; y < 35; y++) {
		for (x = 2; x < 18; x++) {
			mtid = MapGridGetMetatileIdAt(X, Y);
			if (gSpecialVar_0x8001 == 4) {
				// Raise water level around rocks
				switch (mtid) {
					case 0x261: mtid = 0x231; break;
					case 0x262: mtid = 0x232; break;
					case 0x25A: mtid = 0x22A; break;
				}
			} 
			else if (gSpecialVar_0x8001 == 3) {
				// convert shallows to water
				switch (mtid) {
					case 0x29E:
					case 0x19E:
					case 0x1AF:
					case 0x1B7:
					case 0x1BF:
					case 0x1BE:
					case 0x1BD:
					case 0x1B5:
					case 0x1AD:
					case 0x1AE: mtid = 0x170; break;
				}
			}
			else if (gSpecialVar_0x8001 == 2) {
				// convert sand to shallows
				switch (mtid) {
					case 0x23D: mtid = 0x1AF; break;
					case 0x245: mtid = 0x1B7; break;
					case 0x24D: mtid = 0x1BF; break;
					case 0x244:
					case 0x28E:
					case 0x24C: mtid = 0x1BE; break;
					case 0x24B: mtid = 0x1BD; break;
					case 0x243: mtid = 0x1B5; break;
					case 0x23B: mtid = 0x1AD; break;
					case 0x23C: mtid = 0x1AE; break;
					case 0x29B:
					case 0x214: mtid = 0x19E; break;
					case 0x29C: mtid = 0x29E; break;
				}
			}
			else if (gSpecialVar_0x8001 == 1) {
				if ((mtid == 0x206 || mtid == 0x21F) && (Random() % 3) == 0) {
					mtid = 0x170;
				}
			}
			else {
				if (mtid == 0x170 && (Random() % 3) == 0) {
					mtid = 0x21F;
				}
			}
			MapGridSetMetatileIdAt(X, Y, mtid);
		}
	}
	DrawWholeMapView();
}

#undef X
#undef Y

///////////////////////////////////////////////////////////////////////////////
// Puzzle: Route 110 Road 
// MAP_PUZZLE_ROUTE110

extern bool8 gBikeCyclingChallenge;
extern u8 gBikeCollisions;
extern u32 gBikeCyclingTimer;
#define VAR_CYCLING_CHALLENGE_STATE VAR_PUZZLE_00

void ResetCyclingRoadChallengeData(struct ScriptContext *ctx)
{
    gBikeCyclingChallenge = FALSE;
    gBikeCollisions = 0;
    gBikeCyclingTimer = 0;
}

void Special_BeginCyclingRoadChallenge(void)
{
    gBikeCyclingChallenge = TRUE;
    gBikeCollisions = 0;
    gBikeCyclingTimer = gMain.vblankCounter1;
}

void ForcePlayerOntoMachBike(struct ScriptContext *ctx)
{
	SetPlayerAvatarTransitionFlags(PLAYER_AVATAR_FLAG_MACH_BIKE);
}

void ForcePlayerOntoAcroBike(struct ScriptContext *ctx)
{
	SetPlayerAvatarTransitionFlags(PLAYER_AVATAR_FLAG_ACRO_BIKE);
}

u16 GetPlayerAvatarBike(void)
{
    if (TestPlayerAvatarFlags(PLAYER_AVATAR_FLAG_ACRO_BIKE))
        return 1;
    if (TestPlayerAvatarFlags(PLAYER_AVATAR_FLAG_MACH_BIKE))
        return 2;
    return 0;
}

static void DetermineCyclingRoadResults(u32 numFrames, u8 numBikeCollisions)
{
    u8 result;

    if (numBikeCollisions < 100)
    {
        ConvertIntToDecimalStringN(gStringVar1, numBikeCollisions, STR_CONV_MODE_LEFT_ALIGN, 2);
        StringAppend(gStringVar1, gText_SpaceTimes);
    }
    else
    {
        StringCopy(gStringVar1, gText_99TimesPlus);
    }

    if (numFrames < 3600 * 3)
    {
        ConvertIntToDecimalStringN(gStringVar2, numFrames / 60, STR_CONV_MODE_RIGHT_ALIGN, 3);
        gStringVar2[3] = CHAR_PERIOD;
        ConvertIntToDecimalStringN(&gStringVar2[4], ((numFrames % 60) * 100) / 60, STR_CONV_MODE_LEADING_ZEROS, 2);
        StringAppend(gStringVar2, gText_SpaceSeconds);
    }
    else
    {
        StringCopy(gStringVar2, gText_3MinutePlus);
    }

    result = 0;
    if (numBikeCollisions == 0)
    {
        result = 5;
    }
    else if (numBikeCollisions < 6)//4)
    {
        result = 4;
    }
    else if (numBikeCollisions < 15)//10)
    {
        result = 3;
    }
    else if (numBikeCollisions < 25)//20)
    {
        result = 2;
    }
    else if (numBikeCollisions < 100)
    {
        result = 1;
    }

    if (numFrames / 60 <= 60)//10)
    {
        result += 5;
    }
    else if (numFrames / 60 <= 80)//15)
    {
        result += 4;
    }
    else if (numFrames / 60 <= 110)//20)
    {
        result += 3;
    }
    else if (numFrames / 60 <= 140)//40)
    {
        result += 2;
    }
    else if (numFrames / 60 < 180)//60)
    {
        result += 1;
    }


    gSpecialVar_Result = result;
}

static void RecordCyclingRoadResults(u32 numFrames, u8 numBikeCollisions) {
    u16 low = VarGet(VAR_CYCLING_ROAD_RECORD_TIME_L);
    u16 high = VarGet(VAR_CYCLING_ROAD_RECORD_TIME_H);
    u32 framesRecord = low + (high << 16);

    if (framesRecord > numFrames || framesRecord == 0)
    {
        VarSet(VAR_CYCLING_ROAD_RECORD_TIME_L, numFrames);
        VarSet(VAR_CYCLING_ROAD_RECORD_TIME_H, numFrames >> 16);
        VarSet(VAR_CYCLING_ROAD_RECORD_COLLISIONS, numBikeCollisions);
    }
}

u16 GetRecordedCyclingRoadResults(void) {
    u16 low = VarGet(VAR_CYCLING_ROAD_RECORD_TIME_L);
    u16 high = VarGet(VAR_CYCLING_ROAD_RECORD_TIME_H);
    u32 framesRecord = low + (high << 16);

    if (framesRecord == 0)
    {
        return FALSE;
    }

    DetermineCyclingRoadResults(framesRecord, VarGet(VAR_CYCLING_ROAD_RECORD_COLLISIONS));
    return TRUE;
}

void FinishCyclingRoadChallenge(void) {
    const u32 numFrames = gMain.vblankCounter1 - gBikeCyclingTimer;

    DetermineCyclingRoadResults(numFrames, gBikeCollisions);
    RecordCyclingRoadResults(numFrames, gBikeCollisions);
}

void GetCurrentCyclingRoadTime(struct ScriptContext *ctx)
{
	const u32 numSecs = (gMain.vblankCounter1 - gBikeCyclingTimer) / 60;
	if (numSecs < 999) {
		ConvertIntToDecimalStringN(gStringVar1, numSecs+0, STR_CONV_MODE_LEFT_ALIGN, 3);
		ConvertIntToDecimalStringN(gStringVar2, numSecs+1, STR_CONV_MODE_LEFT_ALIGN, 3);
		ConvertIntToDecimalStringN(gStringVar3, numSecs+2, STR_CONV_MODE_LEFT_ALIGN, 3);
	} else {
		StringCopy(gStringVar1, gText_WayTooLong1);
        StringCopy(gStringVar2, gText_WayTooLong2);
        StringCopy(gStringVar3, gText_WayTooLong3);
	}
}

void UpdateCyclingRoadState(void) {
    // if (gLastUsedWarp.mapNum == MAP_NUM(ROUTE110_SEASIDE_CYCLING_ROAD_SOUTH_ENTRANCE) && gLastUsedWarp.mapGroup == MAP_GROUP(ROUTE110_SEASIDE_CYCLING_ROAD_SOUTH_ENTRANCE))
    // {
    //     return;
    // }

    // if (VarGet(VAR_CYCLING_CHALLENGE_STATE) == 2 || VarGet(VAR_CYCLING_CHALLENGE_STATE) == 3)
    // {
    //     VarSet(VAR_CYCLING_CHALLENGE_STATE, 0);
    //     Overworld_SetSavedMusic(MUS_DUMMY);
    // }
}

#undef VAR_CYCLING_CHALLENGE_STATE

///////////////////////////////////////////////////////////////////////////////
// Puzzle: Twin Memories 
// MAP_PUZZLE_TWIN_MEMORIES

extern const u8 Puzzle_TwinMemories_Configs[][6];
extern const u8 Puzzle_TwinMemories_ConfigCount;

void CountTwinMemoriesBoulders(struct ScriptContext *ctx) {
	s16 o, i;
	s16 xbase = 0, ybase = 0, x, y;
	struct EventObject *eventObject = NULL;
    struct CoordEvent *coordEvent = NULL;
	const u8 *currConfig;
	
	gSpecialVar_Result = 0;
	// Only load this pointer if it's within the array and pointing to someplace in ROM
	if (VarGet(ctx->data[0]) > Puzzle_TwinMemories_ConfigCount) return;
	currConfig = Puzzle_TwinMemories_Configs[VarGet(ctx->data[0])];
	if (currConfig < (const u8*)&Start) return;
	
	xbase = COORD_X(ctx->data[1]);
	ybase = COORD_Y(ctx->data[1]);
	
	for (o = 0; o < EVENT_OBJECTS_COUNT; o++) {
		eventObject = &gEventObjects[o];
        if (eventObject->isPlayer) continue;
        if (!eventObject->active) continue;
		if (eventObject->graphicsId != EVENT_OBJ_GFX_PUSHABLE_BOULDER) continue;
		if (!eventObject->isStandingOnTrigger) continue;
		
		x = (eventObject->currentCoords.x - 7 - xbase) / 2;
		y = (eventObject->currentCoords.y - 7 - ybase) / 2;
		x = (x * 5) + y; //the index of the tile being stood on
		
		for (i = 0; i < 6; i++) {
			// Check to see if the tile this object is sitting on is part of the valid config
			if (currConfig[i] == x) {
				gSpecialVar_Result++;
				continue;
			}
		}
	}
}

void SetupTwinMemoriesBoulders(struct ScriptContext *ctx) {
	s16 o, i;
	s16 xbase, ybase, x, y;
	struct EventObject *eventObject = NULL;
	const u8 *currConfig;
	
	// Only load this pointer if it's within the array and pointing to someplace in ROM
	if (VarGet(ctx->data[0]) > Puzzle_TwinMemories_ConfigCount) { gSpecialVar_LastErrorNo = 1; return; }
	currConfig = Puzzle_TwinMemories_Configs[VarGet(ctx->data[0])];
	if (currConfig < (const u8*)&Start) { gSpecialVar_LastErrorNo = 2; return; }
	
	xbase = COORD_X(ctx->data[1]);
	ybase = COORD_Y(ctx->data[1]);
	
	// boulders are 2, 3, 4, 5, 6, 7
	for (o = 0; o < EVENT_OBJECTS_COUNT; o++) {
		eventObject = &gEventObjects[o];
		if (eventObject->localId >= 2 && eventObject->localId <= 7) {
			i = currConfig[eventObject->localId-2];
			x = ((i / 5) * 2) + xbase + 7;
			y = ((i % 5) * 2) + ybase + 7;
			MoveEventObjectToMapCoords(eventObject, x, y);
		}
	}
	gSpecialVar_LastErrorNo = 0;
}

///////////////////////////////////////////////////////////////////////////////
// Puzzle: Koga's Labyrinth 
// MAP_PUZZLE_HIDDEN_MAZE

#define PALETTE_SLOT_SRC (10*16+11)
#define PALETTE_SLOT_DST (10*16+15)

void HiddenMaze_PulseWallTiles(u8 taskId)
{
	u16 color = 0;
	u8 val = 0;
	s16 *data = gTasks[taskId].data;
	struct PlttData *palColor = (struct PlttData *)&color;
	
	if (data[2] == 0) { //init
		data[1] = -512;
		data[2] = 1;
	}
	
	data[1]++;
	if (data[1] > 512) data[1] = -512;
	val = max(31 - (abs(data[1])>>3), 0);
	
	color = gPlttBufferUnfaded[PALETTE_SLOT_SRC];
	palColor->r = max(palColor->r, val);
	palColor->g = max(palColor->g, val);
	palColor->b = min(palColor->b, 31-val);
	gPlttBufferFaded[PALETTE_SLOT_DST] = color;
}

#undef PALETTE_SLOT_SRC
#undef PALETTE_SLOT_DST

///////////////////////////////////////////////////////////////////////////////
// Trick or Treating in Mossdeep
// MAP_TRICK_TREAT_MOSSDEEP_CITY

#define VAR_TRICK_STOLEN_MON VAR_PUZZLE_00
#define TEMP_STORAGE_BOX 10
#define TEMP_STORAGE_POS 0

void MossdeepStealPokemon(struct ScriptContext *ctx)
{
	int i;
	CalculatePlayerPartyCount();
	if (VarGet(VAR_TRICK_STOLEN_MON) == 0) { //steal the mon
		for (i = 0; i < gPlayerPartyCount; i++) {
			if (SendMonToPCSlot(&gPlayerParty[i], TEMP_STORAGE_BOX, TEMP_STORAGE_POS+i)) {
				ZeroMonData(&gPlayerParty[i]);
			}
		}
	} else { //return the mon
		for (i = 0; i < PARTY_SIZE; i++) {
			GetMonFromPCSlot(&gPlayerParty[i], TEMP_STORAGE_BOX, TEMP_STORAGE_POS+i);
		}
	}
	CompactPartySlots();
	CalculatePlayerPartyCount();
}

#undef VAR_TRICK_STOLEN_MON 


///////////////////////////////////////////////////////////////////////////////
// Route 110 Cycling Maze
// MAP_PUZZLE_ROUTE110

void IsCurrentPuzzleCyclingRoad(struct ScriptContext *ctx)
{
	u16 currPuzzle = GetCurrentPuzzleMapId();
	VarSet(VAR_RESULT, currPuzzle == MAP_PUZZLE_ROUTE110);
}

///////////////////////////////////////////////////////////////////////////////
// Puzzle: A Bird in the Bush
// MAP_PUZZLE_ILEX_FOREST

#define VAR_BIRD_LOCATION   VAR_PUZZLE_00
#define LID_BIRD            3 

struct BirdSpot {
	const u16 x;
	const u16 y;
	const u8 *script;
};

extern const struct BirdSpot Puzzle_IlexForest_BirdSpots[];
extern const u8 *Puzzle_IlexForest_ConfigCount;

void LoadBirdLocation(struct ScriptContext *ctx)
{
	s32 i;
	struct EventObjectTemplate *savObjTemplates;
	
	u16 idx = VarGet(VAR_BIRD_LOCATION);
	const struct BirdSpot *spot = &Puzzle_IlexForest_BirdSpots[idx];
	if (((u32)spot) >= (u32)Puzzle_IlexForest_ConfigCount) return;
	
	// Loop through the event templates and find the bird
	savObjTemplates = gSaveBlock1Ptr->eventObjectTemplates;
	for (i = 0; i < EVENT_OBJECT_TEMPLATES_COUNT; i++)
    {
        struct EventObjectTemplate *eventObjectTemplate = &savObjTemplates[i];
        if (eventObjectTemplate->localId == LID_BIRD)
        {
			// Set the bird's location and script to the current location
            eventObjectTemplate->x = spot->x;
            eventObjectTemplate->y = spot->y;
			eventObjectTemplate->script = spot->script;
            break;
        }
    }
}

#undef LID_BIRD
#undef VAR_BIRD_LOCATION

///////////////////////////////////////////////////////////////////////////////
// Puzzle: Tic Rac Toe
// MAP_PUZZLE_TIC_RAC_TOE

void CountNPCTriggers(struct ScriptContext *ctx) {
	s16 o, i, x, y;
	int mid;
	struct EventObject *eventObject = NULL;
    struct CoordEvent *coordEvent = NULL;
	const u8 *currConfig;
	
	gSpecialVar_Result = 0;
	
	for (o = 0; o < EVENT_OBJECTS_COUNT; o++) {
		eventObject = &gEventObjects[o];
        if (eventObject->isPlayer) continue;
        if (!eventObject->active) continue;
		if (!eventObject->isStandingOnTrigger) continue;
		
		gSpecialVar_Result++;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Puzzle: The Frozen Excursion
// MAP_PUZZLE_ICE_PATH

#define VAR_CONFIG                VAR_PUZZLE_00
#define VAR_STORED_RANDOM         VAR_PUZZLE_01

extern const u32 Puzzle_IcePath_ConfigTable[][12];
extern const u8 Puzzle_IcePath_ConfigCount;

void InitIcePathPuzzleConfig(struct ScriptContext *ctx) {
	if (FlagGet(FLAG_SYS_RANDOM_DISABLED)) {
		VarSet(VAR_CONFIG, 1);
	} else {
		VarSet(VAR_CONFIG, Random() % Puzzle_IcePath_ConfigCount);
	}
	VarSet(VAR_STORED_RANDOM, Random());
}

void SetupIcePathLayout(struct ScriptContext *ctx) {
	u32 savedRng = gRng2Value;
	u8 c, i, b;
	SeedRng2(VarGet(VAR_STORED_RANDOM));
	
	c = VarGet(VAR_CONFIG);
	for (i = 0; i < 12; i++) {
		for (b = 0; b < 14; b++) {
			bool8 hasRock = (Puzzle_IcePath_ConfigTable[c][i] >> (13 - b)) & 0x1;
			if (hasRock) {
				switch (Random2() % 4) {
					case 0: MapGridSetMetatileIdAt(9 + b, 8 + i, 0x037D | METATILE_COLLISION_MASK); break;
					case 1: MapGridSetMetatileIdAt(9 + b, 8 + i, 0x037E | METATILE_COLLISION_MASK); break;
					case 2: MapGridSetMetatileIdAt(9 + b, 8 + i, 0x039A | METATILE_COLLISION_MASK); break;
					case 3: MapGridSetMetatileIdAt(9 + b, 8 + i, 0x039E | METATILE_COLLISION_MASK); break;
				}
			}
		}
	}
	
	gRng2Value = savedRng;
}

#undef VAR_CONFIG
#undef VAR_STORED_RANDOM

///////////////////////////////////////////////////////////////////////////////
// Puzzle: A Safari Among Friends
// MAP_PUZZLE_SAFARI_IMPOSTERS
#define VAR_CONFIG_IMPOSTER  VAR_PUZZLE_01
#define VAR_IMPOSTER_SELECT  VAR_PUZZLE_02
#define LID_JOEY             8
#define LID_JAMES            9
#define LID_IRENE            10
#define LID_WALLY            11
#define LID_BRENDAN          12
#define LID_MAY              13
#define LID_ALEX             14
#define LID_FRIEND_A         VAR_PUZZLE_1A
#define LID_FRIEND_B         VAR_PUZZLE_1B
#define LID_CUTSCENE_PLAYER  VAR_PUZZLE_1C
// For the reveal scene
#define LID_SELECTED         VAR_PUZZLE_10
#define LID_FRIEND_1         VAR_PUZZLE_11
#define LID_FRIEND_2         VAR_PUZZLE_12
#define LID_FRIEND_3         VAR_PUZZLE_13
#define LID_FRIEND_4         VAR_PUZZLE_14
#define LID_FRIEND_5         VAR_PUZZLE_15
//
#define VAR_JOEY_STATE         VAR_PUZZLE_10
#define VAR_JAMES_STATE        VAR_PUZZLE_11
#define VAR_IRENE_STATE        VAR_PUZZLE_12
#define VAR_WALLY_STATE        VAR_PUZZLE_13
#define VAR_BRENDAN_STATE      VAR_PUZZLE_14
#define VAR_MAY_STATE          VAR_PUZZLE_15
#define VAR_ALEX_STATE         VAR_PUZZLE_16
// compare against VAR_CONFIG_IMPOSTER:
#define IMP_JOEY    0
#define IMP_JAMES   1
#define IMP_IRENE   2
#define IMP_WALLY   3
#define IMP_BRENDAN 4
#define IMP_MAY     5
#define IMP_ALEX    6

extern const u8 gExpandedPlaceholder_Youngster[];
extern const u8 gExpandedPlaceholder_Link[];
extern const u8 gExpandedPlaceholder_FairyGirl[];
extern const u8 gExpandedPlaceholder_Wally[];
extern const u8 gExpandedPlaceholder_Brendan[];
extern const u8 gExpandedPlaceholder_May[];
extern const u8 gExpandedPlaceholder_Alex[];

extern const u8 Puzzle_SafariImposters_ImposterReveal_Text_he[];
extern const u8 Puzzle_SafariImposters_ImposterReveal_Text_she[];
extern const u8 Puzzle_SafariImposters_ImposterReveal_Text_they[];

// Because this is just easier to do in native than in script

void Imposter_RandomizeFriendLayout(struct ScriptContext *ctx) {
	u8 friendLayout[] = { IMP_JOEY, IMP_JAMES, IMP_IRENE, IMP_WALLY, IMP_BRENDAN, IMP_MAY };
	u8 i, a, b, x;
	u16 var;
	
	if (gSaveBlock2Ptr->playerGender == GENDER_M) {
		friendLayout[IMP_BRENDAN] = IMP_ALEX;
	} else if (gSaveBlock2Ptr->playerGender == GENDER_F) {
		friendLayout[IMP_MAY] = IMP_ALEX;
	}
	
	// Randomize the layout
	for (i = 0; i < 16; i++) {
		a = Random() % 6;
		b = Random() % 6;
		x = friendLayout[a];
		friendLayout[a] = friendLayout[b];
		friendLayout[b] = x;
	}
	// The selected goes in slot 6
	a = 5;
	for (b = 0; b < 6; b++) {
		if (friendLayout[b] == VarGet(VAR_IMPOSTER_SELECT)) break;
	}
	x = friendLayout[a];
	friendLayout[a] = friendLayout[b];
	friendLayout[b] = x;
	
	// The imposter goes in slot 2
	a = 1;
	for (b = 0; b < 6; b++) {
		if (friendLayout[b] == VarGet(VAR_CONFIG_IMPOSTER)) break;
	}
	x = friendLayout[a];
	friendLayout[a] = friendLayout[b];
	friendLayout[b] = x;
	
	// Now load in the LIDs into the variables
	x = 0;
	for (i = 0; i < 6; i++) {
		if (friendLayout[i] == VarGet(VAR_IMPOSTER_SELECT)) {
			var = LID_SELECTED;
		} else {
			var = LID_FRIEND_1 + x;
			x++;
		}
		switch(friendLayout[i]) {
			case IMP_JOEY:    VarSet(var, LID_JOEY); break;
			case IMP_JAMES:   VarSet(var, LID_JAMES); break;
			case IMP_IRENE:   VarSet(var, LID_IRENE); break;
			case IMP_WALLY:   VarSet(var, LID_WALLY); break;
			case IMP_BRENDAN: VarSet(var, LID_BRENDAN); break;
			case IMP_MAY:     VarSet(var, LID_MAY); break;
			case IMP_ALEX:    VarSet(var, LID_ALEX); break;
		}
	}
	
}

void Imposter_LoadRevealStrings(struct ScriptContext *ctx) {
	switch(VarGet(VAR_IMPOSTER_SELECT)) {
		case IMP_JOEY:    StringCopy(gStringVar1, gExpandedPlaceholder_Youngster); break;
		case IMP_JAMES:   StringCopy(gStringVar1, gExpandedPlaceholder_Link); break;
		case IMP_IRENE:   StringCopy(gStringVar1, gExpandedPlaceholder_FairyGirl); break;
		case IMP_WALLY:   StringCopy(gStringVar1, gExpandedPlaceholder_Wally); break;
		case IMP_BRENDAN: StringCopy(gStringVar1, gExpandedPlaceholder_Brendan); break;
		case IMP_MAY:     StringCopy(gStringVar1, gExpandedPlaceholder_May); break;
		case IMP_ALEX:    StringCopy(gStringVar1, gExpandedPlaceholder_Alex); break;
	}
	switch(VarGet(VAR_CONFIG_IMPOSTER)) {
		case IMP_JOEY:
			StringCopy(gStringVar3, gExpandedPlaceholder_Youngster);
			VarSet(VAR_OBJ_GFX_ID_0, TTH_FRIEND_JOEY);
			break;
		case IMP_JAMES:
			StringCopy(gStringVar3, gExpandedPlaceholder_Link);
			VarSet(VAR_OBJ_GFX_ID_0, TTH_FRIEND_JAMES);
			break;
		case IMP_IRENE:
			StringCopy(gStringVar3, gExpandedPlaceholder_FairyGirl);
			VarSet(VAR_OBJ_GFX_ID_0, TTH_FRIEND_IRENE);
			break;
		case IMP_WALLY:
			StringCopy(gStringVar3, gExpandedPlaceholder_Wally);
			VarSet(VAR_OBJ_GFX_ID_0, TTH_FRIEND_WALLY);
			break;
		case IMP_BRENDAN:
			StringCopy(gStringVar3, gExpandedPlaceholder_Brendan);
			VarSet(VAR_OBJ_GFX_ID_0, TTH_FRIEND_BRENDAN);
			break;
		case IMP_MAY:
			StringCopy(gStringVar3, gExpandedPlaceholder_May);
			VarSet(VAR_OBJ_GFX_ID_0, TTH_FRIEND_MAY);
			break;
		case IMP_ALEX:
			StringCopy(gStringVar3, gExpandedPlaceholder_Alex);
			VarSet(VAR_OBJ_GFX_ID_0, TTH_FRIEND_ALEX);
			break;
	}
	switch(VarGet(VAR_IMPOSTER_SELECT)) {
		case IMP_IRENE:
		case IMP_MAY:
			StringCopy(gStringVar2, Puzzle_SafariImposters_ImposterReveal_Text_she);
			break;
		case IMP_ALEX:
			StringCopy(gStringVar2, Puzzle_SafariImposters_ImposterReveal_Text_they);
			break;
		default:
			StringCopy(gStringVar2, Puzzle_SafariImposters_ImposterReveal_Text_he);
			break;
	}
}

static const u16 Imposter_ShowTalkingPoints_RNGVars[] = {
	VAR_JOEY_STATE,
	VAR_JAMES_STATE,
	VAR_IRENE_STATE,
	VAR_WALLY_STATE,
	VAR_BRENDAN_STATE,
	VAR_MAY_STATE,
	VAR_ALEX_STATE,
};
#define ACCUSE_IDX(rng)  (0x7 & ((rng) >> 12))

void Imposter_SetupTalkingPoints(struct ScriptContext *ctx) {
	u8 i, x;
	u16* var;
	for (i = 0; i < ARRAY_COUNT(Imposter_ShowTalkingPoints_RNGVars); i++) {
		var = GetVarPointer(Imposter_ShowTalkingPoints_RNGVars[i]);
		*var = Random2();
	}
	// eliminate impossible accusations, change to player accusations
	var = GetVarPointer(Imposter_ShowTalkingPoints_RNGVars[IMP_JOEY]);
	if (VarGet(VAR_CONFIG_IMPOSTER) != IMP_JAMES && ACCUSE_IDX(*var) == IMP_JAMES) {
		// Joey doesn't accuse James if James isn't the imposter
		*var = (*var & 0x0FFF) | IMP_JOEY;
	}
	
	var = GetVarPointer(Imposter_ShowTalkingPoints_RNGVars[IMP_JAMES]);
	if (VarGet(VAR_CONFIG_IMPOSTER) != IMP_JOEY && ACCUSE_IDX(*var) == IMP_JOEY) {
		// James doesn't accuse Joey if Joey isn't the imposter
		*var = (*var & 0x0FFF) | IMP_JAMES;
	}
	
	var = GetVarPointer(Imposter_ShowTalkingPoints_RNGVars[IMP_BRENDAN]);
	if (VarGet(VAR_CONFIG_IMPOSTER) == ACCUSE_IDX(*var)) {
		// Brendan never accuses the correct person
		*var = (*var & 0x0FFF) | IMP_BRENDAN;
	}
}

extern const u8** const Puzzle_SafariImposters_TalkTables[7][3];
extern const u8 Puzzle_SafariImposters_Text_JoeyAlibi1a[];

void Imposter_ShowTalkingPoints(struct ScriptContext *ctx) {
	u8 currSpeaker = ctx->data[0];
	bool8 isImposter = (currSpeaker == VarGet(VAR_CONFIG_IMPOSTER));
	const u8** alibiTable = Puzzle_SafariImposters_TalkTables[currSpeaker][0];
	const u8** imposterTable = Puzzle_SafariImposters_TalkTables[currSpeaker][1];
	const u8** accuseTable = Puzzle_SafariImposters_TalkTables[currSpeaker][2];
	u16 rng = VarGet(Imposter_ShowTalkingPoints_RNGVars[currSpeaker]);
	u8 i, x;
	u8 *str = gStringVar4;
	
	// So, for future reference, when using the gStringVar4 directly like this,
	// NEVER call ShowFieldMessage(), as that calls StringExpandPlaceholders(),
	// and now you're expanding placeholders in-place, guaranteeing that the
	// destination string is longer, and thus racing ahead of the src string
	// and that can cause all sorts of untold horrors and "jumps to invalid addresses".
	
	if (isImposter) {
		for(i = 0; imposterTable[i*4] != NULL && i < 6; i++) {
			x = 0x3 & (rng >> (i*2));
			// str = ConvertIntToDecimalStringN(str, (i*4)+x, 2, 3);
			str = StringExpandPlaceholders(str, imposterTable[(i*4)+x]);
		}
	} else {
		for(i = 0; alibiTable[i*4] != NULL && i < 6; i++) {
			x = 0x3 & (rng >> (i*2));
			// str = ConvertIntToDecimalStringN(str, (i*4)+x, 2, 3);
			str = StringExpandPlaceholders(str, alibiTable[(i*4)+x]);
		}
	}
	x = ACCUSE_IDX(rng);
	// if the random accusation is of the player character, change it to such
	if ((gSaveBlock2Ptr->playerGender == GENDER_M && x == IMP_BRENDAN)
	||  (gSaveBlock2Ptr->playerGender == GENDER_F && x == IMP_MAY)
	||  (gSaveBlock2Ptr->playerGender == GENDER_N && x == IMP_ALEX))
	{
		x = currSpeaker;
	}
	str = StringExpandPlaceholders(str, accuseTable[x]);
	*str = EOS;
	// If the gStringVar4 buffer is overflown, it rolls into 256 bytes of the 
	// gStringWorking, which is fine. Beyond that is some link variables we'll never use.
	// So this should be fiiiiiiine.
	ShowFieldMessageFromBuffer();
}

#define SET_POKEBLOCK(num, spicyA, dryA, sweetA, bitterA, sourA, colorA) \
	gSaveBlock1Ptr->pokeblocks[num].spicy = spicyA; \
	gSaveBlock1Ptr->pokeblocks[num].dry = dryA; \
	gSaveBlock1Ptr->pokeblocks[num].sweet = sweetA; \
	gSaveBlock1Ptr->pokeblocks[num].bitter = bitterA; \
	gSaveBlock1Ptr->pokeblocks[num].sour = sourA; \
	gSaveBlock1Ptr->pokeblocks[num].feel = spicyA + dryA + sweetA + bitterA + sourA; \
	gSaveBlock1Ptr->pokeblocks[num].color = colorA;


void Imposter_PopulatePokeblockCase(struct ScriptContext *ctx) {
	struct Pokeblock block;
	
	ClearPokeblocks();
	SET_POKEBLOCK( 0,20, 0, 0, 0, 0, PBLOCK_CLR_RED);
	SET_POKEBLOCK( 1, 0,20, 0, 0, 0, PBLOCK_CLR_BLUE);
	SET_POKEBLOCK( 2, 0, 0,20, 0, 0, PBLOCK_CLR_PINK);
	SET_POKEBLOCK( 3, 0, 0, 0,20, 0, PBLOCK_CLR_GREEN);
	SET_POKEBLOCK( 4, 0, 0, 0, 0,20, PBLOCK_CLR_YELLOW);
	SET_POKEBLOCK( 5,20, 0, 0, 0, 0, PBLOCK_CLR_RED);
	SET_POKEBLOCK( 6, 0,20, 0, 0, 0, PBLOCK_CLR_BLUE);
	SET_POKEBLOCK( 7, 0, 0,20, 0, 0, PBLOCK_CLR_PINK);
	SET_POKEBLOCK( 8, 0, 0, 0,20, 0, PBLOCK_CLR_GREEN);
	SET_POKEBLOCK( 9, 0, 0, 0, 0,20, PBLOCK_CLR_YELLOW);
	SET_POKEBLOCK(10,20, 0, 0, 0, 0, PBLOCK_CLR_RED);
	SET_POKEBLOCK(11, 0,20, 0, 0, 0, PBLOCK_CLR_BLUE);
	SET_POKEBLOCK(12, 0, 0,20, 0, 0, PBLOCK_CLR_PINK);
	SET_POKEBLOCK(13, 0, 0, 0,20, 0, PBLOCK_CLR_GREEN);
	SET_POKEBLOCK(14, 0, 0, 0, 0,20, PBLOCK_CLR_YELLOW);
	SET_POKEBLOCK(15,20, 0, 0, 0,15, PBLOCK_CLR_PURPLE);
}

#undef SET_POKEBLOCK

#undef VAR_CONFIG_IMPOSTER
#undef VAR_IMPOSTER_SELECT
#undef LID_JOEY
#undef LID_JAMES
#undef LID_IRENE
#undef LID_WALLY
#undef LID_BRENDAN
#undef LID_MAY
#undef LID_ALEX
#undef LID_FRIEND_A
#undef LID_FRIEND_B
#undef LID_CUTSCENE_PLAYER

#undef LID_SELECTED
#undef LID_FRIEND_1
#undef LID_FRIEND_2
#undef LID_FRIEND_3
#undef LID_FRIEND_4
#undef LID_FRIEND_5

#undef VAR_JOEY_STATE
#undef VAR_JAMES_STATE
#undef VAR_IRENE_STATE
#undef VAR_WALLY_STATE
#undef VAR_BRENDAN_STATE
#undef VAR_MAY_STATE
#undef VAR_ALEX_STATE

#undef IMP_JOEY
#undef IMP_JAMES
#undef IMP_IRENE
#undef IMP_WALLY
#undef IMP_BRENDAN
#undef IMP_MAY
#undef IMP_ALEX
