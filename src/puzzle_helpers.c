#include "global.h"
#include "event_data.h"
#include "puzzle_helpers.h"
#include "sound.h"
#include "constants/flags.h"
#include "constants/metatile_labels.h"
#include "constants/songs.h"
#include "constants/vars.h"


#define FLAG_HIDE_SCROLL          FLAG_TEMP_1
#define FLAG_TILES_ACTIVE         FLAG_PUZZLE_20
#define VAR_CUR_SONG              VAR_PUZZLE_00
#define VAR_NUM_CORRECT_STEPS     VAR_PUZZLE_01
#define VAR_TARGET_TILE           VAR_PUZZLE_02
#define VAR_SONG_COMPLETION_STATE VAR_PUZZLE_03

const u16 sSongNotes0[] = {
    METATILE_ID(TrickHousePuzzle, MusicNoteGreen),
    METATILE_ID(TrickHousePuzzle, MusicNoteRed),
    METATILE_ID(TrickHousePuzzle, MusicNoteBlue),
    0xFFFF,
};

const u16 sSongNotes1[] = {
    METATILE_ID(TrickHousePuzzle, MusicNoteGreen),
    METATILE_ID(TrickHousePuzzle, MusicNoteBlue),
    METATILE_ID(TrickHousePuzzle, MusicNoteRed),
    METATILE_ID(TrickHousePuzzle, MusicNoteYellow),
    0xFFFF,
};

const u16 sSongNotes2[] = {
    METATILE_ID(TrickHousePuzzle, MusicNoteRed),
    METATILE_ID(TrickHousePuzzle, MusicNoteYellow),
    METATILE_ID(TrickHousePuzzle, MusicNotePink),
    METATILE_ID(TrickHousePuzzle, MusicNoteGreen),
    METATILE_ID(TrickHousePuzzle, MusicNoteBlue),
    0xFFFF,
};

const u16 sSongNotes3[] = {
    METATILE_ID(TrickHousePuzzle, MusicNoteRed),
    METATILE_ID(TrickHousePuzzle, MusicNoteRed),
    METATILE_ID(TrickHousePuzzle, MusicNotePink),
    METATILE_ID(TrickHousePuzzle, MusicNoteGreen),
    METATILE_ID(TrickHousePuzzle, MusicNoteBlue),
    METATILE_ID(TrickHousePuzzle, MusicNoteGreen),
    0xFFFF,
};

const u16 *const sSongNotes[] = {
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

    if (!FlagGet(FLAG_TILES_ACTIVE))
    {
        PlayPuzzleMusicTileNote(metatileId);
        return;
    }

    curSong = VarGet(VAR_CUR_SONG);
    curStep = VarGet(VAR_NUM_CORRECT_STEPS);
    correctNote = sSongNotes[curSong][curStep];
    if (metatileId == correctNote)
    {
        PlayPuzzleMusicTileNote(metatileId);
        if (sSongNotes[curSong][curStep + 1] != 0xFFFF)
        {
            VarSet(VAR_NUM_CORRECT_STEPS, curStep + 1);
        }
        else
        {
            if (curSong < ARRAY_COUNT(sSongNotes) - 1)
                VarSet(VAR_SONG_COMPLETION_STATE, 1);
            else
                VarSet(VAR_SONG_COMPLETION_STATE, 2);

            FlagClear(FLAG_TILES_ACTIVE);
        }
    }
    else
    {
        PlaySE(SE_HAZURE);
        FlagClear(FLAG_TILES_ACTIVE);
        VarSet(VAR_NUM_CORRECT_STEPS, 0);
    }
}


#undef FLAG_HIDE_SCROLL
#undef FLAG_TILES_ACTIVE
#undef VAR_CUR_SONG
#undef VAR_NUM_CORRECT_STEPS
#undef VAR_TARGET_TILE
