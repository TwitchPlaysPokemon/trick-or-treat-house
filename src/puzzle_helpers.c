#include "global.h"
#include "event_data.h"
#include "script.h"
#include "puzzle_helpers.h"
#include "sound.h"
#include "field_camera.h"
#include "fieldmap.h"
#include "random.h"
#include "constants/flags.h"
#include "constants/metatile_labels.h"
#include "constants/songs.h"
#include "constants/vars.h"

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
        FlagClear(FLAG_MUSIC_NOTE_PUZZLE_TILES_ACTIVE);
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

