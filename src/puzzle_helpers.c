#include "global.h"
#include "event_data.h"
#include "script.h"
#include "puzzle_helpers.h"
#include "sound.h"
#include "field_camera.h"
#include "field_player_avatar.h"
#include "fieldmap.h"
#include "palette.h"
#include "random.h"
#include "strings.h"
#include "string_util.h"
#include "text.h"
#include "task.h"
#include "trickhouse.h"
#include "script.h"
#include "pokemon_storage_system.h"
#include "event_object_movement.h"
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

// Some common debugging helpers

void PrintData0(struct ScriptContext *ctx)
{
	ConvertIntToHexStringN(gStringVar1, ctx->data[0], STR_CONV_MODE_LEADING_ZEROS, 8);
}

void PrintData1(struct ScriptContext *ctx)
{
	ConvertIntToHexStringN(gStringVar1, ctx->data[1], STR_CONV_MODE_LEADING_ZEROS, 8);
}

///////////////////////////////////////////////////////////////////////////////
// Puzzle: Pokemon Says 
// MAP_PUZZLE_MUSIC_NOTE_TILES

#define FLAG_MUSIC_NOTE_PUZZLE_HIDE_SCROLL          FLAG_TEMP_1
#define FLAG_MUSIC_NOTE_PUZZLE_TILES_ACTIVE         FLAG_PUZZLE_20
#define VAR_MUSIC_NOTE_PUZZLE_CUR_SONG              VAR_PUZZLE_00
#define VAR_MUSIC_NOTE_PUZZLE_NUM_CORRECT_STEPS     VAR_PUZZLE_01
#define VAR_MUSIC_NOTE_PUZZLE_TARGET_TILE           VAR_PUZZLE_02
#define VAR_MUSIC_NOTE_PUZZLE_SONG_COMPLETION_STATE VAR_PUZZLE_03

static const u16 sSongNotes0[] = {
    METATILE_ID(TrickHousePuzzle, MusicNoteGreen),
    METATILE_ID(TrickHousePuzzle, MusicNoteRed),
    METATILE_ID(TrickHousePuzzle, MusicNoteBlue),
    0xFFFF,
};

static const u16 sSongNotes1[] = {
    METATILE_ID(TrickHousePuzzle, MusicNoteGreen),
    METATILE_ID(TrickHousePuzzle, MusicNoteBlue),
    METATILE_ID(TrickHousePuzzle, MusicNoteRed),
    METATILE_ID(TrickHousePuzzle, MusicNoteYellow),
    0xFFFF,
};

static const u16 sSongNotes2[] = {
    METATILE_ID(TrickHousePuzzle, MusicNoteRed),
    METATILE_ID(TrickHousePuzzle, MusicNoteYellow),
    METATILE_ID(TrickHousePuzzle, MusicNotePink),
    METATILE_ID(TrickHousePuzzle, MusicNoteGreen),
    METATILE_ID(TrickHousePuzzle, MusicNoteBlue),
    0xFFFF,
};

static const u16 sSongNotes3[] = {
    METATILE_ID(TrickHousePuzzle, MusicNoteRed),
    METATILE_ID(TrickHousePuzzle, MusicNoteRed),
    METATILE_ID(TrickHousePuzzle, MusicNotePink),
    METATILE_ID(TrickHousePuzzle, MusicNoteGreen),
    METATILE_ID(TrickHousePuzzle, MusicNoteBlue),
    METATILE_ID(TrickHousePuzzle, MusicNoteGreen),
    0xFFFF,
};

static const u16 *const sSongNotes[] = {
    sSongNotes0,
    sSongNotes1,
    sSongNotes2,
    sSongNotes3,
};

static void PlayPuzzleMusicTileNote(u32 metatileId)
{
    switch (metatileId)
    {
    case METATILE_ID(TrickHousePuzzle, MusicNoteYellow):
        PlaySE(SE_TOY_C);
        break;
    case METATILE_ID(TrickHousePuzzle, MusicNoteBlue):
        PlaySE(SE_TOY_D);
        break;
    case METATILE_ID(TrickHousePuzzle, MusicNoteGreen):
        PlaySE(SE_TOY_E);
        break;
    case METATILE_ID(TrickHousePuzzle, MusicNotePink):
        PlaySE(SE_TOY_F);
        break;
    case METATILE_ID(TrickHousePuzzle, MusicNoteRed):
        PlaySE(SE_TOY_G);
        break;
    }
}

void HandlePuzzleMusicTileStep(u32 metatileId)
{
    u16 curSong, curStep, correctNote;

    if (!FlagGet(FLAG_MUSIC_NOTE_PUZZLE_TILES_ACTIVE))
    {
        PlayPuzzleMusicTileNote(metatileId);
        return;
    }

    curSong = VarGet(VAR_MUSIC_NOTE_PUZZLE_CUR_SONG);
    curStep = VarGet(VAR_MUSIC_NOTE_PUZZLE_NUM_CORRECT_STEPS);
    correctNote = sSongNotes[curSong][curStep];
    if (metatileId == correctNote)
    {
        PlayPuzzleMusicTileNote(metatileId);
        if (sSongNotes[curSong][curStep + 1] != 0xFFFF)
        {
            VarSet(VAR_MUSIC_NOTE_PUZZLE_NUM_CORRECT_STEPS, curStep + 1);
        }
        else
        {
            if (curSong < ARRAY_COUNT(sSongNotes) - 1)
                VarSet(VAR_MUSIC_NOTE_PUZZLE_SONG_COMPLETION_STATE, 1);
            else
                VarSet(VAR_MUSIC_NOTE_PUZZLE_SONG_COMPLETION_STATE, 2);

            FlagClear(FLAG_MUSIC_NOTE_PUZZLE_TILES_ACTIVE);
        }
    }
    else
    {
        PlaySE(SE_HAZURE);
        // FlagClear(FLAG_MUSIC_NOTE_PUZZLE_TILES_ACTIVE);
        VarSet(VAR_MUSIC_NOTE_PUZZLE_NUM_CORRECT_STEPS, 0);
    }
}


#undef FLAG_MUSIC_NOTE_PUZZLE_HIDE_SCROLL
#undef FLAG_MUSIC_NOTE_PUZZLE_TILES_ACTIVE
#undef VAR_MUSIC_NOTE_PUZZLE_CUR_SONG
#undef VAR_MUSIC_NOTE_PUZZLE_NUM_CORRECT_STEPS
#undef VAR_MUSIC_NOTE_PUZZLE_TARGET_TILE
#undef VAR_MUSIC_NOTE_PUZZLE_SONG_COMPLETION_STATE

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


