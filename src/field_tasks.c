#include "global.h"
#include "bike.h"
#include "clock.h"
#include "event_data.h"
#include "field_camera.h"
#include "field_effect_helpers.h"
#include "field_player_avatar.h"
#include "field_special_scene.h"
#include "field_tasks.h"
#include "fieldmap.h"
#include "item.h"
#include "main.h"
#include "metatile_behavior.h"
#include "overworld.h"
#include "script.h"
#include "secret_base.h"
#include "sound.h"
#include "task.h"
#include "constants/field_tasks.h"
#include "palette.h"
#include "constants/items.h"
#include "constants/songs.h"
#include "constants/metatile_labels.h"
#include "constants/field_tasks.h"

#include "menu.h"
#include "string_util.h"

/*  This file handles some persistent tasks that run in the overworld.
 *  - Task_RunTimeBasedEvents: Periodically updates local time and RTC events. Also triggers ambient cries.
 *  - Task_MuddySlope: Handles the metatile animation when the player steps on muddy slopes.
 *  - Task_RunPerStepCallback: Calls one of the functions in sPerStepCallbacks, listed below...
 *      . DummyPerStepCallback: Default, does nothing
 *      . AshGrassPerStepCallback: Removes the ash from ash-covered grass that the player steps on.
 *      . FortreeBridgePerStepCallback: Depresses Fortree log bridges that the player steps on.
 *      . PacifidlogBridgePerStepCallback: Submerges Pacifidlog log bridges that the player steps on.
 *      . SootopolisGymIcePerStepCallback: Cracks/breaks ice in Sootopolis Gym that the player steps on.
 *      . EndTruckSequence: Sets the moving truck boxes to their final position when the truck sequence ends.
 *      . SecretBasePerStepCallback: Records the decorations in a friend's secret base that the player steps on.
 *      . CrackedFloorPerStepCallback: Breaks cracked floors that the player steps on.
 *
 *  NOTE: "PerStep" is perhaps misleading. One function in sPerStepCallbacks is called
 *        every frame while in the overworld by Task_RunPerStepCallback regardless of
 *        whether or not steps are being taken. However, nearly all of the functions in
 *        the table check if the player has moved from their previous position before
 *        doing anything else.
 */

struct PacifidlogMetatileOffsets
{
    s8 x;
    s8 y;
    u16 metatileId;
};

static void DummyPerStepCallback(u8);
static void AshGrassPerStepCallback(u8);
static void FortreeBridgePerStepCallback(u8);
static void PacifidlogBridgePerStepCallback(u8);
static void WaterTemplePerStepCallback(u8 taskId);
static void SootopolisGymIcePerStepCallback(u8);
static void CrackedFloorPerStepCallback(u8);
static void MonitorObjectEventTriggersStepCallback(u8 taskId);
static void MonitorMultiObjectEventTriggersStepCallback(u8 taskId);
extern void HiddenMaze_PulseWallTiles(u8 taskId);
extern void TrickHouse_CycleTextPalette(u8 taskId);
static void Task_MuddySlope(u8);

static const TaskFunc sPerStepCallbacks[] =
{
    [STEP_CB_DUMMY]              = DummyPerStepCallback,
    [STEP_CB_ASH]                = AshGrassPerStepCallback,
    [STEP_CB_FORTREE_BRIDGE]     = FortreeBridgePerStepCallback,
    [STEP_CB_PACIFIDLOG_BRIDGE]  = PacifidlogBridgePerStepCallback, //3
    [STEP_CB_SOOTOPOLIS_ICE]     = SootopolisGymIcePerStepCallback,
    [STEP_CB_TRUCK]              = EndTruckSequence,
    [STEP_CB_SECRET_BASE]        = SecretBasePerStepCallback,
    [STEP_CB_CRACKED_FLOOR]      = CrackedFloorPerStepCallback,
    [STEP_CB_WATER_TEMPLE]       = WaterTemplePerStepCallback, //8
    [STEP_CB_NPC_TRIGGER]        = MonitorObjectEventTriggersStepCallback,
    [STEP_CB_HIDDEN_WALLS]       = HiddenMaze_PulseWallTiles,
    [STEP_CB_CYCLE_TEXT_PAL]     = TrickHouse_CycleTextPalette,
    [STEP_CB_NPC_MULTI_TRIGGER]  = MonitorMultiObjectEventTriggersStepCallback, //12
};

// Each element corresponds to a y coordinate row in the sootopolis gym 1F map.
static const u16 sSootopolisGymIceRowVars[] =
{
    0,
    0,
    0,
    0,
    0,
    0,
    VAR_TEMP_1,
    VAR_TEMP_2,
    VAR_TEMP_3,
    VAR_TEMP_4,
    0,
    0,
    VAR_TEMP_5,
    VAR_TEMP_6,
    VAR_TEMP_7,
    0,
    0,
    VAR_TEMP_8,
    VAR_TEMP_9,
    VAR_TEMP_A,
    0,
    0,
    0,
    0,
    0,
    0
};

static const u16 sMuddySlopeMetatiles[] = {
    METATILE_ID(General, MuddySlope_Frame0),
    METATILE_ID(General, MuddySlope_Frame3),
    METATILE_ID(General, MuddySlope_Frame2),
    METATILE_ID(General, MuddySlope_Frame1)
};
#define tCallbackId data[0]

static void Task_RunPerStepCallback(u8 taskId)
{
    int idx = gTasks[taskId].tCallbackId;
    sPerStepCallbacks[idx](taskId);
}

#define tState           data[0]
#define tAmbientCryState data[1]
#define tAmbientCryDelay data[2]

#define TIME_UPDATE_INTERVAL (1 << 12)

static void RunTimeBasedEvents(s16 *data)
{
    switch (tState)
    {
    case 0:
        if (gMain.vblankCounter1 & TIME_UPDATE_INTERVAL)
        {
            DoTimeBasedEvents();
            tState++;
        }
        break;
    case 1:
        if (!(gMain.vblankCounter1 & TIME_UPDATE_INTERVAL))
            tState--;
        break;
    }
}

static void Task_RunTimeBasedEvents(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    if (!ArePlayerFieldControlsLocked())
    {
        RunTimeBasedEvents(data);
        UpdateAmbientCry(&tAmbientCryState, &tAmbientCryDelay);
    }
}

#undef tState

void SetUpFieldTasks(void)
{
    if (!FuncIsActiveTask(Task_RunPerStepCallback))
    {
        u8 taskId = CreateTask(Task_RunPerStepCallback, 80);
        gTasks[taskId].tCallbackId = STEP_CB_DUMMY;
    }

    if (!FuncIsActiveTask(Task_MuddySlope))
        CreateTask(Task_MuddySlope, 80);

    if (!FuncIsActiveTask(Task_RunTimeBasedEvents))
        CreateTask(Task_RunTimeBasedEvents, 80);
}

void ActivatePerStepCallback(u8 callbackId)
{
    u8 taskId = FindTaskIdByFunc(Task_RunPerStepCallback);
    if (taskId != TASK_NONE)
    {
        s32 i;
        s16 *data = gTasks[taskId].data;

        for (i = 0; i < NUM_TASK_DATA; i++)
            data[i] = 0;

        if (callbackId >= ARRAY_COUNT(sPerStepCallbacks))
            tCallbackId = STEP_CB_DUMMY;
        else
            tCallbackId = callbackId;
    }
}

void ResetFieldTasksArgs(void)
{
    u8 taskId;
    s16 *data;

    taskId = FindTaskIdByFunc(Task_RunPerStepCallback);
    if (taskId != TASK_NONE)
        data = gTasks[taskId].data;

    taskId = FindTaskIdByFunc(Task_RunTimeBasedEvents);
    if (taskId != TASK_NONE)
    {
        data = gTasks[taskId].data;
        tAmbientCryState = 0;
        tAmbientCryDelay = 0;
    }
}

#undef tAmbientCryState
#undef tAmbientCryDelay

static void DummyPerStepCallback(u8 taskId)
{

}

//-----------------------------------------------------------------------------
// Each array has 4 pairs of data, each pair representing two metatiles of a log and their relative position.
// The 4 pairs are for:
// 0: If the player is standing on the top of a vertical log
// 1: If the player is standing on the bottom of a vertical log
// 2: If the player is standing on the left of a horizontal log
// 3: If the player is standing on the right of a horizontal log
// i.e. the element with an offset of 0,0 is the one the player is standing on.
static const struct PacifidlogMetatileOffsets sHalfSubmergedBridgeMetatileOffsets[] =
{
    { 0,  0, METATILE_ID(Pacifidlog, HalfSubmergedLogs_VerticalTop)}, {0, 1, METATILE_ID(Pacifidlog, HalfSubmergedLogs_VerticalBottom)},
    { 0, -1, METATILE_ID(Pacifidlog, HalfSubmergedLogs_VerticalTop)}, {0, 0, METATILE_ID(Pacifidlog, HalfSubmergedLogs_VerticalBottom)},
    { 0,  0, METATILE_ID(Pacifidlog, HalfSubmergedLogs_HorizontalLeft)}, {1, 0, METATILE_ID(Pacifidlog, HalfSubmergedLogs_HorizontalRight)},
    {-1,  0, METATILE_ID(Pacifidlog, HalfSubmergedLogs_HorizontalLeft)}, {0, 0, METATILE_ID(Pacifidlog, HalfSubmergedLogs_HorizontalRight)}
};
static const struct PacifidlogMetatileOffsets sFullySubmergedBridgeMetatileOffsets[] =
{
    { 0,  0, METATILE_ID(Pacifidlog, SubmergedLogs_VerticalTop)}, {0, 1, METATILE_ID(Pacifidlog, SubmergedLogs_VerticalBottom)},
    { 0, -1, METATILE_ID(Pacifidlog, SubmergedLogs_VerticalTop)}, {0, 0, METATILE_ID(Pacifidlog, SubmergedLogs_VerticalBottom)},
    { 0,  0, METATILE_ID(Pacifidlog, SubmergedLogs_HorizontalLeft)}, {1, 0, METATILE_ID(Pacifidlog, SubmergedLogs_HorizontalRight)},
    {-1,  0, METATILE_ID(Pacifidlog, SubmergedLogs_HorizontalLeft)}, {0, 0, METATILE_ID(Pacifidlog, SubmergedLogs_HorizontalRight)}
};
static const struct PacifidlogMetatileOffsets sFloatingBridgeMetatileOffsets[] =
{
    { 0,  0, METATILE_ID(Pacifidlog, FloatingLogs_VerticalTop)}, {0, 1, METATILE_ID(Pacifidlog, FloatingLogs_VerticalBottom)},
    { 0, -1, METATILE_ID(Pacifidlog, FloatingLogs_VerticalTop)}, {0, 0, METATILE_ID(Pacifidlog, FloatingLogs_VerticalBottom)},
    { 0,  0, METATILE_ID(Pacifidlog, FloatingLogs_HorizontalLeft)}, {1, 0, METATILE_ID(Pacifidlog, FloatingLogs_HorizontalRight)},
    {-1,  0, METATILE_ID(Pacifidlog, FloatingLogs_HorizontalLeft)}, {0, 0, METATILE_ID(Pacifidlog, FloatingLogs_HorizontalRight)}
};

static const struct PacifidlogMetatileOffsets *GetPacifidlogBridgeMetatileOffsets(const struct PacifidlogMetatileOffsets *offsets, u16 metatileBehavior)
{
    if (MetatileBehavior_IsPacifidlogVerticalLogTop(metatileBehavior))
        return &offsets[0 * 2];
    else if (MetatileBehavior_IsPacifidlogVerticalLogBottom(metatileBehavior))
        return &offsets[1 * 2];
    else if (MetatileBehavior_IsPacifidlogHorizontalLogLeft(metatileBehavior))
        return &offsets[2 * 2];
    else if (MetatileBehavior_IsPacifidlogHorizontalLogRight(metatileBehavior))
        return &offsets[3 * 2];
    else
        return NULL;
}

static void TrySetPacifidlogBridgeMetatiles(const struct PacifidlogMetatileOffsets *offsets, s16 x, s16 y, bool32 redrawMap)
{
    offsets = GetPacifidlogBridgeMetatileOffsets(offsets, MapGridGetMetatileBehaviorAt(x, y));
    
    // If offsets is NULL, position is not a log (don't set it)
    if (offsets)
    {
        // Set both metatiles of the log
        MapGridSetMetatileIdAt(x + offsets[0].x, y + offsets[0].y, offsets[0].metatileId);
        if (redrawMap)
            CurrentMapDrawMetatileAt(x + offsets[0].x, y + offsets[0].y);

        MapGridSetMetatileIdAt(x + offsets[1].x, y + offsets[1].y, offsets[1].metatileId);
        if (redrawMap)
            CurrentMapDrawMetatileAt(x + offsets[1].x, y + offsets[1].y);
    }
}

static void TrySetLogBridgeHalfSubmerged(s16 x, s16 y, bool32 redrawMap)
{
    TrySetPacifidlogBridgeMetatiles(sHalfSubmergedBridgeMetatileOffsets, x, y, redrawMap);
}

static void TrySetLogBridgeFullySubmerged(s16 x, s16 y, bool32 redrawMap)
{
    TrySetPacifidlogBridgeMetatiles(sFullySubmergedBridgeMetatileOffsets, x, y, redrawMap);
}

static void TrySetLogBridgeFloating(s16 x, s16 y, bool32 redrawMap)
{
    TrySetPacifidlogBridgeMetatiles(sFloatingBridgeMetatileOffsets, x, y, redrawMap);
}

// Returns FALSE if player has moved from one end of a log to the other (log should remain submerged).
// Otherwise it returns TRUE.
static bool32 ShouldRaisePacifidlogLogs(s16 newX, s16 newY, s16 oldX, s16 oldY)
{
    u16 oldBehavior = MapGridGetMetatileBehaviorAt(oldX, oldY);

    if (MetatileBehavior_IsPacifidlogVerticalLogTop(oldBehavior))
    {
        // Still on same one if moved from top to bottom
        if (newY > oldY)
            return FALSE;
    }
    else if (MetatileBehavior_IsPacifidlogVerticalLogBottom(oldBehavior))
    {
        // Still on same one if moved from bottom to top
        if (newY < oldY)
            return FALSE;
    }
    else if (MetatileBehavior_IsPacifidlogHorizontalLogLeft(oldBehavior))
    {
        // Still on same one if moved from left to right 
        if (newX > oldX)
            return FALSE;
    }
    else if (MetatileBehavior_IsPacifidlogHorizontalLogRight(oldBehavior))
    {
        // Still on same one if moved from right to left
        if (newX < oldX)
            return FALSE;
    }

    // Player is either on a different log or no log at all
    return TRUE;
}

// Returns FALSE if player has moved from one end of a log to the other (log should remain submerged).
// Otherwise it returns TRUE.
// This is the effectively the same as ShouldRaisePacifidlogLogs, as it swaps both the conditions and which position's behavior to check.
// In effect the previous function asks "was the player's previous position not the other end of a log they're standing on?"
// while this function asks "is the player's current position not the other end of a log they were previously standing on?"
// and with the same positions both questions always have the same answer.
static bool32 ShouldSinkPacifidlogLogs(s16 newX, s16 newY, s16 oldX, s16 oldY)
{
    u16 newBehavior = MapGridGetMetatileBehaviorAt(newX, newY);

    if (MetatileBehavior_IsPacifidlogVerticalLogTop(newBehavior))
    {
        // Still on same one if moved from bottom to top
        if (newY < oldY)
            return FALSE;
    }
    else if (MetatileBehavior_IsPacifidlogVerticalLogBottom(newBehavior))
    {
        // Still on same one if moved from top to bottom
        if (newY > oldY)
            return FALSE;
    }
    else if (MetatileBehavior_IsPacifidlogHorizontalLogLeft(newBehavior))
    {
        // Still on same one if moved from right to left 
        if (newX < oldX)
            return FALSE;
    }
    else if (MetatileBehavior_IsPacifidlogHorizontalLogRight(newBehavior))
    {
        // Still on same one if moved from left to right 
        if (newX > oldX)
            return FALSE;
    }
    return TRUE;
}

#define tState    data[1]
#define tPrevX    data[2]
#define tPrevY    data[3]
#define tToRaiseX data[4]
#define tToRaiseY data[5]
#define tDelay    data[6]

static void PacifidlogBridgePerStepCallback(u8 taskId)
{
    s16 *data;
    s16 x, y;
    data = gTasks[taskId].data;
    PlayerGetDestCoords(&x, &y);
    switch (tState)
    {
    case 0:
        tPrevX = x;
        tPrevY = y;
        
        // If player is already standing on a log when the callback
        // is set then immediately set it to submerged
        TrySetLogBridgeFullySubmerged(x, y, TRUE);
        tState = 1;
        break;
    case 1:
        // Skip if player hasn't moved
        if (x == tPrevX && y == tPrevY)
            return;

        if (ShouldRaisePacifidlogLogs(x, y, tPrevX, tPrevY))
        {
            // Player's previous position is not the other end of a log
            // they're standing on, try and set it half-submerged (rising to surface).
            // The floating metatile is queued up by setting it but not drawing it,
            // but this is pointless as state 2 will handle it in full anyway.
            TrySetLogBridgeHalfSubmerged(tPrevX, tPrevY, TRUE);
            TrySetLogBridgeFloating(tPrevX, tPrevY, FALSE);
            tToRaiseX = tPrevX;
            tToRaiseY = tPrevY;
            tState = 2;
            tDelay = 8;
        }
        else
        {
            // Player has moved but is still on the same log bridge section.
            // Keep it submerged.
            tToRaiseX = -1;
            tToRaiseY = -1;
        }

        if (ShouldSinkPacifidlogLogs(x, y, tPrevX, tPrevY))
        {
            // Player's current position is not the other end of a log
            // they were previously standing on, try and set it half-submerged (sinking)
            TrySetLogBridgeHalfSubmerged(x, y, TRUE);
            tState = 2;
            tDelay = 8;
        }

        tPrevX = x;
        tPrevY = y;

        // If player's new position is a log play the puddle SE
        if (MetatileBehavior_IsPacifidlogLog(MapGridGetMetatileBehaviorAt(x, y)))
            PlaySE(SE_PUDDLE);
        break;
    case 2:
        if (--tDelay == 0)
        {
            // If player's current position is a log submerge it fully.
            TrySetLogBridgeFullySubmerged(x, y, TRUE);
            
            // Player's previous position is not the other end of a log
            // they're standing on, try to raise their previous position.
            if (tToRaiseX != -1 && tToRaiseY != -1)
                TrySetLogBridgeFloating(tToRaiseX, tToRaiseY, TRUE);

            tState = 1;
        }
        break;
    }
}


//-----------------------------------------------------------------------------
// they are in pairs but declared as 1D array
static const struct PacifidlogMetatileOffsets sHalfSubmergedTempleLogsMetatileOffsets[] =
{
    { 0,  0, METATILE_ID(WaterfallCave, HalfSubmergedLogs_Vertical0)}, {0, 1, METATILE_ID(WaterfallCave, HalfSubmergedLogs_Vertical1)},
    { 0, -1, METATILE_ID(WaterfallCave, HalfSubmergedLogs_Vertical0)}, {0, 0, METATILE_ID(WaterfallCave, HalfSubmergedLogs_Vertical1)},
    { 0,  0, METATILE_ID(WaterfallCave, HalfSubmergedLogs_Horizontal0)}, {1, 0, METATILE_ID(WaterfallCave, HalfSubmergedLogs_Horizontal1)},
    {-1,  0, METATILE_ID(WaterfallCave, HalfSubmergedLogs_Horizontal0)}, {0, 0, METATILE_ID(WaterfallCave, HalfSubmergedLogs_Horizontal1)}
};
static const struct PacifidlogMetatileOffsets sFullySubmergedTempleLogsMetatileOffsets[] =
{
    { 0,  0, METATILE_ID(WaterfallCave, SubmergedLogs_Vertical0)}, {0, 1, METATILE_ID(WaterfallCave, SubmergedLogs_Vertical1)},
    { 0, -1, METATILE_ID(WaterfallCave, SubmergedLogs_Vertical0)}, {0, 0, METATILE_ID(WaterfallCave, SubmergedLogs_Vertical1)},
    { 0,  0, METATILE_ID(WaterfallCave, SubmergedLogs_Horizontal0)}, {1, 0, METATILE_ID(WaterfallCave, SubmergedLogs_Horizontal1)},
    {-1,  0, METATILE_ID(WaterfallCave, SubmergedLogs_Horizontal0)}, {0, 0, METATILE_ID(WaterfallCave, SubmergedLogs_Horizontal1)}
};
static const struct PacifidlogMetatileOffsets sFloatingTempleLogsMetatileOffsets[] =
{
    { 0,  0, METATILE_ID(WaterfallCave, FloatingLogs_Vertical0)}, {0, 1, METATILE_ID(WaterfallCave, FloatingLogs_Vertical1)},
    { 0, -1, METATILE_ID(WaterfallCave, FloatingLogs_Vertical0)}, {0, 0, METATILE_ID(WaterfallCave, FloatingLogs_Vertical1)},
    { 0,  0, METATILE_ID(WaterfallCave, FloatingLogs_Horizontal0)}, {1, 0, METATILE_ID(WaterfallCave, FloatingLogs_Horizontal1)},
    {-1,  0, METATILE_ID(WaterfallCave, FloatingLogs_Horizontal0)}, {0, 0, METATILE_ID(WaterfallCave, FloatingLogs_Horizontal1)}
};

static const struct PacifidlogMetatileOffsets *GetPacifidlogTempleLogsMetatileOffsets(const struct PacifidlogMetatileOffsets *offsets, u16 metatileBehavior)
{
    if (MetatileBehavior_IsPacifidlogVerticalLogTop(metatileBehavior))
        return &offsets[0 * 2];
    else if (MetatileBehavior_IsPacifidlogVerticalLogBottom(metatileBehavior))
        return &offsets[1 * 2];
    else if (MetatileBehavior_IsPacifidlogHorizontalLogLeft(metatileBehavior))
        return &offsets[2 * 2];
    else if (MetatileBehavior_IsPacifidlogHorizontalLogRight(metatileBehavior))
        return &offsets[3 * 2];
    else
        return NULL;
}

static void SetPacifidlogTempleLogsMetatiles(const struct PacifidlogMetatileOffsets *offsets, s16 x, s16 y, bool32 redrawMap)
{
    offsets = GetPacifidlogTempleLogsMetatileOffsets(offsets, MapGridGetMetatileBehaviorAt(x, y));
    if (offsets)
    {
        MapGridSetMetatileIdAt(x + offsets[0].x, y + offsets[0].y, offsets[0].metatileId);
        if (redrawMap)
            CurrentMapDrawMetatileAt(x + offsets[0].x, y + offsets[0].y);

        MapGridSetMetatileIdAt(x + offsets[1].x, y + offsets[1].y, offsets[1].metatileId);
        if (redrawMap)
            CurrentMapDrawMetatileAt(x + offsets[1].x, y + offsets[1].y);
    }
}

static void UpdateHalfSubmergedTempleLogsMetatiles(s16 x, s16 y, bool32 redrawMap)
{
    SetPacifidlogTempleLogsMetatiles(sHalfSubmergedTempleLogsMetatileOffsets, x, y, redrawMap);
}

static void UpdateFullySubmergedTempleLogsMetatiles(s16 x, s16 y, bool32 redrawMap)
{
    SetPacifidlogTempleLogsMetatiles(sFullySubmergedTempleLogsMetatileOffsets, x, y, redrawMap);
}

static void UpdateFloatingTempleLogsMetatiles(s16 x, s16 y, bool32 redrawMap)
{
    SetPacifidlogTempleLogsMetatiles(sFloatingTempleLogsMetatileOffsets, x, y, redrawMap);
}

static bool32 StandingOnNewPacifidlogTempleLogs(s16 x1, s16 y1, s16 x2, s16 y2)
{
    u16 metatileBehavior = MapGridGetMetatileBehaviorAt(x2, y2);

    if (MetatileBehavior_IsPacifidlogVerticalLogTop(metatileBehavior))
    {
        if (y1 > y2)
            return FALSE;
    }
    else if (MetatileBehavior_IsPacifidlogVerticalLogBottom(metatileBehavior))
    {
        if (y1 < y2)
            return FALSE;
    }
    else if (MetatileBehavior_IsPacifidlogHorizontalLogLeft(metatileBehavior))
    {
        if (x1 > x2)
            return FALSE;
    }
    else if (MetatileBehavior_IsPacifidlogHorizontalLogRight(metatileBehavior))
    {
        if (x1 < x2)
            return FALSE;
    }
    return TRUE;
}

static bool32 StandingOnSamePacifidlogTempleLogs(s16 x1, s16 y1, s16 x2, s16 y2)
{
    u16 metatileBehavior = MapGridGetMetatileBehaviorAt(x1, y1);

    if (MetatileBehavior_IsPacifidlogVerticalLogTop(metatileBehavior))
    {
        if (y1 < y2)
            return FALSE;
    }
    else if (MetatileBehavior_IsPacifidlogVerticalLogBottom(metatileBehavior))
    {
        if (y1 > y2)
            return FALSE;
    }
    else if (MetatileBehavior_IsPacifidlogHorizontalLogLeft(metatileBehavior))
    {
        if (x1 < x2)
            return FALSE;
    }
    else if (MetatileBehavior_IsPacifidlogHorizontalLogRight(metatileBehavior))
    {
        if (x1 > x2)
            return FALSE;
    }
    return TRUE;
}

#define state data[1]
#define prevX data[2]
#define prevY data[3]
#define storedX data[4]
#define storedY data[5]
#define delay data[6]
#define prevJump data[7]

static void WaterTemplePerStepCallback(u8 taskId)
{
    s16 *data;
    s16 x, y;
    data = gTasks[taskId].data;
    PlayerGetDestCoords(&x, &y);
    switch (state)
    {
        case 0: //Init case
            prevX = x;
            prevY = y;
            prevJump = FALSE;
            UpdateFullySubmergedTempleLogsMetatiles(x, y, TRUE);
            state = 1;
            break;
        case 1: //Usual case
            if (IsPlayerJumping())
            {
                if (prevJump != IsPlayerJumping())
                {
                    // Set the previous logs half out of water (prevX/Y), redraw now
                    UpdateHalfSubmergedTempleLogsMetatiles(prevX, prevY, TRUE);
                    // Store out of the water location for later use
                    storedX = prevX;
                    storedY = prevY;
                    // Go to delay case
                    state = 2;
                    delay = 8;
                    
                    prevJump = IsPlayerJumping();
                    prevX = -1;
                    prevY = -1;
                }
                else
                {
                    // Clear last out of water location
                    storedX = -1;
                    storedY = -1;
                }
            }
            else if (x != prevX || y != prevY)
            {
                // If the player has switched logs (currX, currY, prevX, prevY)
                if (StandingOnNewPacifidlogTempleLogs(x, y, prevX, prevY))
                {
                    // Set the previous logs half out of water (prevX/Y), redraw now
                    UpdateHalfSubmergedTempleLogsMetatiles(prevX, prevY, TRUE);
                    // Set the previous logs out of water (prevX/Y), don't redraw
                    UpdateFloatingTempleLogsMetatiles(prevX, prevY, FALSE);
                    // Store out of the water location for later use
                    storedX = prevX;
                    storedY = prevY;
                    // Go to delay case
                    state = 2;
                    delay = 8;
                }
                else
                {
                    // Clear last out of water location
                    storedX = -1;
                    storedY = -1;
                }
                
                // If the player is standing on the same logs as before
                if (StandingOnSamePacifidlogTempleLogs(x, y, prevX, prevY))
                {
                    // Start submerging current location (currX/Y)
                    UpdateHalfSubmergedTempleLogsMetatiles(x, y, TRUE);
                    // Go to delay case
                    state = 2;
                    delay = 8;
                }
                
                // Store currX/Y to prevX/Y
                prevJump = IsPlayerJumping();
                prevX = x;
                prevY = y;
                // Make sound
                if (MetatileBehavior_IsPacifidlogLog(MapGridGetMetatileBehaviorAt(x, y)) && !IsPlayerJumping())
                    PlaySE(SE_PUDDLE);
            }
            break;
        case 2: //Delay case
            // Once the delay runs out
            if ((--delay) == 0)
            {
                // Draw current location fully submerged
                UpdateFullySubmergedTempleLogsMetatiles(x, y, TRUE);
                // If there was a stored previous location
                if (storedX != -1 && storedY != -1)
                    // Draw it fully out of water
                    UpdateFloatingTempleLogsMetatiles(storedX, storedY, TRUE);
                // Back to usual case
                state = 1;
            }
            break;
    }
}

#undef state
#undef prevX
#undef prevY
#undef storedX
#undef storedY
#undef delay
#undef prevJump

//-----------------------------------------------------------------------------

#undef tState
#undef tPrevX
#undef tPrevY
#undef tToRaiseX
#undef tToRaiseY
#undef tDelay

static void TryLowerFortreeBridge(s16 x, s16 y)
{
    u8 elevation = PlayerGetElevation();
    if (!(elevation & 1))
    {
        switch (MapGridGetMetatileIdAt(x, y))
        {
        case METATILE_Fortree_BridgeOverGrass_Raised:
            MapGridSetMetatileIdAt(x, y, METATILE_Fortree_BridgeOverGrass_Lowered);
            break;
        case METATILE_Fortree_BridgeOverTrees_Raised:
            MapGridSetMetatileIdAt(x, y, METATILE_Fortree_BridgeOverTrees_Lowered);
            break;
        }
    }
}

static void TryRaiseFortreeBridge(s16 x, s16 y)
{
    u8 elevation = PlayerGetElevation();
    if (!(elevation & 1))
    {
        switch (MapGridGetMetatileIdAt(x, y))
        {
        case METATILE_Fortree_BridgeOverGrass_Lowered:
            MapGridSetMetatileIdAt(x, y, METATILE_Fortree_BridgeOverGrass_Raised);
            break;
        case METATILE_Fortree_BridgeOverTrees_Lowered:
            MapGridSetMetatileIdAt(x, y, METATILE_Fortree_BridgeOverTrees_Raised);
            break;
        }
    }
}

#define tState      data[1]
#define tPrevX      data[2]
#define tPrevY      data[3]
#define tOldBridgeX data[4]
#define tOldBridgeY data[5]
#define tBounceTime data[6]

static void FortreeBridgePerStepCallback(u8 taskId)
{
    bool8 isFortreeBridgeCur;
    bool8 isFortreeBridgePrev;
    u8 elevation, onBridgeElevation;
    s16 x, y, prevX, prevY;
    s16 *data = gTasks[taskId].data;
    PlayerGetDestCoords(&x, &y);
    switch (tState)
    {
    default:
        break;
    case 0:
        tPrevX = x;
        tPrevY = y;
        
        // If player is already on bridge when callback is set then lower it immediately.
        if (MetatileBehavior_IsFortreeBridge(MapGridGetMetatileBehaviorAt(x, y)))
        {
            TryLowerFortreeBridge(x, y);
            CurrentMapDrawMetatileAt(x, y);
        }
        tState = 1;
        break;
    case 1:
        prevX = tPrevX;
        prevY = tPrevY;

        // Skip if player hasn't moved
        if (x == prevX && y == prevY)
            break;

        isFortreeBridgeCur = MetatileBehavior_IsFortreeBridge(MapGridGetMetatileBehaviorAt(x, y));
        isFortreeBridgePrev = MetatileBehavior_IsFortreeBridge(MapGridGetMetatileBehaviorAt(prevX, prevY));
        
        // Make sure player isn't below bridge
        elevation = PlayerGetElevation();
        onBridgeElevation = FALSE;
        if ((u8)(elevation & 1) == 0)
            onBridgeElevation = TRUE;

        if (onBridgeElevation && (isFortreeBridgeCur == TRUE || isFortreeBridgePrev == TRUE))
            PlaySE(SE_BRIDGE_WALK);

        // Because this doesn't check for isFortreeBridgeCur, bridge sections aren't
        // lowered when first stepping onto them from anything other than another bridge.
    #ifdef BUGFIX
        if (isFortreeBridgePrev || isFortreeBridgeCur)
    #else
        if (isFortreeBridgePrev)
    #endif
        {
            // Raise old bridge
            TryRaiseFortreeBridge(prevX, prevY);
            CurrentMapDrawMetatileAt(prevX, prevY);

            // Lower new bridge
            TryLowerFortreeBridge(x, y);
            CurrentMapDrawMetatileAt(x, y);
        }

        // These should really be set below the !isFortreeBridgePrev conditional,
        // but it doesn't matter because it's not read until case 2 anyway.
        tOldBridgeX = prevX;
        tOldBridgeY = prevY;

        tPrevX = x;
        tPrevY = y;
        if (!isFortreeBridgePrev)
            break;

        tBounceTime = 16;
        tState = 2;
        // fallthrough
    case 2:
        tBounceTime--;
        prevX = tOldBridgeX;
        prevY = tOldBridgeY;
        switch (tBounceTime % 7)
        {
        case 0:
            CurrentMapDrawMetatileAt(prevX, prevY);
        case 1:
        case 2:
        case 3:
            break;
        case 4:
            // Bounce bridge section that player has stepped off of
            TryLowerFortreeBridge(prevX, prevY);
            CurrentMapDrawMetatileAt(prevX, prevY);
            TryRaiseFortreeBridge(prevX, prevY);
        case 5:
        case 6:
        case 7: // Not possible with % 7
            break;
        }
        if (tBounceTime == 0)
            tState = 1;
        break;
    }
}

#undef tState
#undef tPrevX
#undef tPrevY
#undef tOldBridgeX
#undef tOldBridgeY
#undef tBounceTime

//-----------------------------------------------------------------------------

#define state      data[1]
#define prevX      data[2]
#define prevY      data[3]
#define crackedX   data[4]
#define crackedY   data[5]
#define delayTimer data[6]

#define rectX      data[10]
#define rectY      data[11]
#define rectW      data[12]
#define rectH      data[13]

static bool32 CoordInIcePuzzleRegion(s16 *data, s16 x, s16 y);

void SetSootopolisGymCrackedIceConfig(struct ScriptContext *ctx)
{
    u8 taskId = FindTaskIdByFunc(Task_RunPerStepCallback);
    s16 *data = gTasks[taskId].data;
    
    if (taskId == 0xff || data[0] != STEP_CB_SOOTOPOLIS_ICE) return; //can't do anything if cracked ice is not set
    rectX = ctx->data[0];
    rectY = ctx->data[1];
    rectW = ctx->data[2];
    rectH = ctx->data[3];
}

void SetSootopolisGymCrackedIceMetatilesRegion(s16 *data, s16 dx, s16 dy) {
    s32 x, y;
    s32 width = gMapHeader.mapLayout->width;
    s32 height = gMapHeader.mapLayout->height;
    
    for (x = 0; x < width; x++)
    {
        for (y = 0; y < height; y++)
        {
            if (CoordInIcePuzzleRegion(data, x, y) == TRUE)
                MapGridSetMetatileIdAt(x + 7, y + 7, 0x202);//METATILE_ID(SootopolisGym, Ice_Cracked));
        }
    }
    MapGridSetMetatileIdAt(dx + 7, dy + 7, 0x201);
    DrawWholeMapView();
}

static bool32 CoordInIcePuzzleRegion(s16 *data, s16 x, s16 y)
{
    // if ((u16)(x - 3) < 11 && (u16)(y - 6) < 14 && sSootopolisGymIceRowVars[y])
    //     return TRUE;
    // else
    //     return FALSE;
    if (rectW == 0 || rectH == 0) return FALSE;
    if (x < rectX || x >= rectX + rectW) return FALSE;
    if (y < rectY || y >= rectY + rectH) return FALSE;
    return TRUE;
}

static void MarkIcePuzzleCoordVisited(s16 *data, s16 x, s16 y)
{
    if (!CoordInIcePuzzleRegion(data, x, y)) return;
        // *GetVarPointer(sSootopolisGymIceRowVars[y]) |= (1 << (x - 3));
    *GetVarPointer(VAR_TEMP_0 + (y - rectY)) |= (1 << ( x - rectX ));
}

static bool32 IsIcePuzzleCoordVisited(s16 *data, s16 x, s16 y)
{
    u32 var;
    if (!CoordInIcePuzzleRegion(data, x, y)) return FALSE;
    var = VarGet(VAR_TEMP_0 + (y - rectY));
    
    return (var & (1 << ( x - rectX ))) != 0;
}

void SetSootopolisGymCrackedIceMetatiles(void)
{
    s32 x, y;
    s32 width = gMapHeader.mapLayout->width;
    s32 height = gMapHeader.mapLayout->height;
    u8 taskId = FindTaskIdByFunc(Task_RunPerStepCallback);
    s16 *data = gTasks[taskId].data;
    
    if (taskId == 0xff || data[0] != STEP_CB_SOOTOPOLIS_ICE) return; //can't do anything if cracked ice is not set
    if (rectW == 0 || rectY == 0) return; //can't do anything without config info
    
    for (x = 0; x < width; x++)
    {
        for (y = 0; y < height; y++)
        {
            if (IsIcePuzzleCoordVisited(data, x, y) == TRUE)
                MapGridSetMetatileIdAt(x + MAP_OFFSET, y + MAP_OFFSET, METATILE_SootopolisGym_Ice_Cracked);
        }
    }
}

static void SootopolisGymIcePerStepCallback(u8 taskId)
{
    s16 x, y; // Note: this X/Y is already offset by view distance
    u16 tileBehavior;
    u16 *iceStepCount;
    s16 *data = gTasks[taskId].data;
    
    switch (state)
    {
        case 0:
            PlayerGetDestCoords(&x, &y);
            prevX = x;
            prevY = y;
            state = 1;
            break;
        case 1:
            PlayerGetDestCoords(&x, &y);
            // Return if player hasn't moved
            if (x == prevX && y == prevY) return;
            
            prevX = x;
            prevY = y;
            tileBehavior = MapGridGetMetatileBehaviorAt(x, y);
            iceStepCount = GetVarPointer(VAR_STEP_TRIGGER);
            if (MetatileBehavior_IsThinIce(tileBehavior) == TRUE)// && CoordInIcePuzzleRegion(data, x, y) == TRUE)
            {
                // Thin ice, set it to cracked ice
                if (CoordInIcePuzzleRegion(data, x - 7, y - 7) == TRUE)
                {
                    (*iceStepCount)++;
                    // ConvertIntToDecimalStringN(gStringBuffer, *iceStepCount, 0, 3);
                    // AddTextPrinterWithCustomSpeedForMessage(FALSE, 0xFF);
                }
                else
                {
                    MapGridSetMetatileIdAt(x, y, 0); // put down obviously bad tile to show the ice step doesn't count
                    CurrentMapDrawMetatileAt(x, y);
                }
                delayTimer = 4;
                state = 2;
                crackedX = x;
                crackedY = y;
            }
            else if (MetatileBehavior_IsCrackedIce(tileBehavior) == TRUE)
            {
                // Cracked ice, set it to broken ice
                *iceStepCount = 0;
                delayTimer = 4;
                state = 3;
                crackedX = x;
                crackedY = y;
            }
            break;
        case 2:
            if (delayTimer != 0)
            {
                delayTimer--;
            }
            else
            {
                // Crack ice
                x = crackedX;
                y = crackedY;
                PlaySE(SE_ICE_CRACK);
                MapGridSetMetatileIdAt(x, y, METATILE_ID(SootopolisGym, Ice_Cracked));
                CurrentMapDrawMetatileAt(x, y);
                MarkIcePuzzleCoordVisited(data, x - 7, y - 7);
                state = 1;
            }
            break;
        case 3:
            if (delayTimer != 0)
            {
                delayTimer--;
            }
            else
            {
                // Break ice
                x = crackedX;
                y = crackedY;
                PlaySE(SE_ICE_BREAK);
                MapGridSetMetatileIdAt(x, y, METATILE_ID(SootopolisGym, Ice_Broken));
                CurrentMapDrawMetatileAt(x, y);
                state = 1;
            }
            break;
    }
}

#undef state
#undef prevX
#undef prevY
#undef crackedX
#undef crackedY
#undef delayTimer
#undef rectX
#undef rectY
#undef rectW
#undef rectH

//-----------------------------------------------------------------------------

#define tPrevX data[1]
#define tPrevY data[2]

static void AshGrassPerStepCallback(u8 taskId)
{
    s16 x, y;
    u16 *ashGatherCount;
    s16 *data = gTasks[taskId].data;
    PlayerGetDestCoords(&x, &y);

    // End if player hasn't moved
    if (x == tPrevX && y == tPrevY)
        return;

    tPrevX = x;
    tPrevY = y;
    if (MetatileBehavior_IsAshGrass(MapGridGetMetatileBehaviorAt(x, y)))
    {
        // Remove ash from grass
        if (MapGridGetMetatileIdAt(x, y) == METATILE_Fallarbor_AshGrass)
            StartAshFieldEffect(x, y, METATILE_Fallarbor_NormalGrass, 4);
        else
            StartAshFieldEffect(x, y, METATILE_Lavaridge_NormalGrass, 4);

        // Try to gather ash
        if (CheckBagHasItem(ITEM_SOOT_SACK, 1))
        {
            ashGatherCount = GetVarPointer(VAR_ASH_GATHER_COUNT);
            if (*ashGatherCount < 9999)
                (*ashGatherCount)++;
        }
    }
}

#undef tPrevX
#undef tPrevY

// This function uses the constants for gTileset_Cave's metatile labels, but other tilesets with
// the CrackedFloorPerStepCallback callback use the same metatile numbers for the cracked floor
// and hole metatiles, such as gTileset_MirageTower.
static void SetCrackedFloorHoleMetatile(s16 x, s16 y)
{
    u16 metatileId = MapGridGetMetatileIdAt(x, y) == METATILE_Cave_CrackedFloor ? METATILE_Cave_CrackedFloor_Hole : METATILE_Pacifidlog_SkyPillar_CrackedFloor_Hole;
    MapGridSetMetatileIdAt(x, y, metatileId);
    CurrentMapDrawMetatileAt(x, y);
}

//-----------------------------------------------------------------------------

#define tPrevX       data[2]
#define tPrevY       data[3]
#define tFloor1Delay data[4]
#define tFloor1X     data[5]
#define tFloor1Y     data[6]
#define tFloor2Delay data[7]
#define tFloor2X     data[8]
#define tFloor2Y     data[9]

static void CrackedFloorPerStepCallback(u8 taskId)
{
    s16 x, y;
    u16 behavior;
    s16 *data = gTasks[taskId].data;
    PlayerGetDestCoords(&x, &y);
    behavior = MapGridGetMetatileBehaviorAt(x, y);

    // Update up to 2 previous cracked floor spaces
    if (tFloor1Delay != 0 && (--tFloor1Delay) == 0)
        SetCrackedFloorHoleMetatile(tFloor1X, tFloor1Y);
    if (tFloor2Delay != 0 && (--tFloor2Delay) == 0)
        SetCrackedFloorHoleMetatile(tFloor2X, tFloor2Y);

    if (MetatileBehavior_IsCrackedFloorHole(behavior))
        VarSet(VAR_STEP_TRIGGER, 0); // this var does double duty

    // End if player hasn't moved
    if (x == tPrevX && y == tPrevY)
        return;

    tPrevX = x;
    tPrevY = y;
    if (MetatileBehavior_IsCrackedFloor(behavior))
    {
        if (GetPlayerSpeed() != PLAYER_SPEED_FASTEST)
            VarSet(VAR_STEP_TRIGGER, 0); // this var does double duty

        if (tFloor1Delay == 0)
        {
            tFloor1Delay = 3;
            tFloor1X = x;
            tFloor1Y = y;
        }
        else if (tFloor2Delay == 0)
        {
            tFloor2Delay = 3;
            tFloor2X = x;
            tFloor2Y = y;
        }
    }
}

#undef tPrevX
#undef tPrevY
#undef tFloor1Delay
#undef tFloor1X
#undef tFloor1Y
#undef tFloor2Delay
#undef tFloor2X
#undef tFloor2Y

//-----------------------------------------------------------------------------

#define tMapId data[0]
#define tState data[1]
#define tPrevX data[2]
#define tPrevY data[3]
// data[4] - data[15] are data about up to 4 individual animating muddy slope metatiles
// They're divided into groups of 3, i.e data[4]-[6] track one metatile, data[7]-[9] another, and so on.
// For each data triplet, the 1st is the animation time, and the 2nd/3rd are the x/y coordinates.
#define SLOPE_DATA_START 4
#define SLOPE_DATA_END  (3 * SLOPE_DATA_SIZE + SLOPE_DATA_START) // 13, which is the last slope data start point
enum {
    SLOPE_TIME,
    SLOPE_X,
    SLOPE_Y,
    SLOPE_DATA_SIZE
};
#define tSlopeAnimTime(i) data[(i) * SLOPE_DATA_SIZE + SLOPE_DATA_START + SLOPE_TIME]

#define SLOPE_ANIM_TIME 32
#define SLOPE_ANIM_STEP_TIME (SLOPE_ANIM_TIME / (int)ARRAY_COUNT(sMuddySlopeMetatiles))

static void SetMuddySlopeMetatile(s16 *data, s16 x, s16 y)
{
    u16 metatileId;
    if ((--data[SLOPE_TIME]) == 0)
        metatileId = METATILE_General_MuddySlope_Frame0;
    else
        metatileId = sMuddySlopeMetatiles[data[SLOPE_TIME] / SLOPE_ANIM_STEP_TIME];

    MapGridSetMetatileIdAt(x, y, metatileId);
    CurrentMapDrawMetatileAt(x, y);
    MapGridSetMetatileIdAt(x, y, METATILE_General_MuddySlope_Frame0);
}

static void Task_MuddySlope(u8 taskId)
{
    s16 x, y, cameraOffsetX, cameraOffsetY;
    int i;
    u16 mapId;
    s16 *data = gTasks[taskId].data;
    PlayerGetDestCoords(&x, &y);
    mapId = (gSaveBlock1Ptr->location.mapGroup << 8) | gSaveBlock1Ptr->location.mapNum;
    switch (tState)
    {
    case 0:
        tMapId = mapId;
        tPrevX = x;
        tPrevY = y;
        tState = 1;
        tSlopeAnimTime(0) = 0;
        tSlopeAnimTime(1) = 0;
        tSlopeAnimTime(2) = 0;
        tSlopeAnimTime(3) = 0;
        break;
    case 1:
        // Skip if player hasn't moved
        if (tPrevX == x && tPrevY == y)
            break;

        tPrevX = x;
        tPrevY = y;
        if (MetatileBehavior_IsMuddySlope(MapGridGetMetatileBehaviorAt(x, y)))
        {
            for (i = SLOPE_DATA_START; i <= SLOPE_DATA_END; i += SLOPE_DATA_SIZE)
            {
                if (data[i] == 0)
                {
                    data[i + SLOPE_TIME] = SLOPE_ANIM_TIME;
                    data[i + SLOPE_X] = x;
                    data[i + SLOPE_Y] = y;
                    break;
                }
            }
        }
        break;
    }

    if (gCamera.active && mapId != tMapId)
    {
        tMapId = mapId;
        cameraOffsetX = gCamera.x;
        cameraOffsetY = gCamera.y;
    }
    else
    {
        cameraOffsetX = 0;
        cameraOffsetY = 0;
    }

    for (i = SLOPE_DATA_START; i <= SLOPE_DATA_END; i += SLOPE_DATA_SIZE)
    {
        if (data[i + SLOPE_TIME])
        {
            data[i + SLOPE_X] -= cameraOffsetX;
            data[i + SLOPE_Y] -= cameraOffsetY;
            SetMuddySlopeMetatile(&data[i + SLOPE_TIME], data[i + SLOPE_X], data[i + SLOPE_Y]);
        }
    }
}

//-----------------------------------------------------------------------------

#define tPosX data[1]
#define tPosY data[2]
#define tRunningVar data[3]
#define tRunningIndex data[4]

static void MonitorObjectEventTriggersStepCallback(u8 taskId)
{
    s16 x, y, o, t;
    bool8 standing;
    struct ObjectEvent *objectEvent = NULL;
    struct CoordEvent *coordEvent = NULL;
    s16 *data = gTasks[taskId].data;
    PlayerGetDestCoords(&x, &y);
    
    
    // If the var is still set like we set it, the expected frame table script hasn't completed yet
    // so don't continue checking.
    if (tRunningVar != 0) {
        if (VarGet(tRunningVar) == tRunningIndex) return;
        // If the var isn't the same, the frame table script has cleared it, we can continue
        tRunningVar = 0;
        tRunningIndex = 0;
    }
    // Don't recheck if the the player hasn't moved
    if (gPlayerAvatar.preventStep) tPosX = -1;
    if (tPosX == x && tPosY == y) return;
    
    // For every event object
    for (o = 0; o < OBJECT_EVENTS_COUNT; o++) {
        objectEvent = &gObjectEvents[o];
        if (objectEvent->isPlayer) continue;
        if (!objectEvent->active) continue;
        if (objectEvent->heldMovementActive) return; //continue;
        
        // Clear the standing flag, but store its current value in case it needs to be put back
        standing = objectEvent->isStandingOnTrigger;
        objectEvent->isStandingOnTrigger = FALSE;
        
        // For every trigger on the map
        for (t = 0; t < gMapHeader.events->coordEventCount; t++) {
            coordEvent = &gMapHeader.events->coordEvents[t];
            if (!coordEvent->npcTrigger) continue;
            if (objectEvent->currentCoords.x != coordEvent->x + 7) continue;
            if (objectEvent->currentCoords.y != coordEvent->y + 7) continue;
            
            if (!standing) {
                // If this event wasn't standing on a trigger before, trigger it now
                tRunningVar = coordEvent->trigger;
                tRunningIndex = coordEvent->index;
                VarSet(tRunningVar, tRunningIndex);
                // If we got down here, we need to set the flag again
                objectEvent->isStandingOnTrigger = TRUE;
                return;
            }
            objectEvent->isStandingOnTrigger = standing;
        }
    }
    tPosX = x;
    tPosY = y;
}

#undef tPosX
#undef tPosY
#undef tRunningVar
#undef tRunningIndex

void TrickHouse_CycleTextPalette(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    u16 c1, c2, c3;
    
    data[1]++;
    if (data[1] < 20) return;
    data[1] = 0;
    
    c1 = gPlttBufferFaded[244];
    c2 = gPlttBufferFaded[246];
    c3 = gPlttBufferFaded[248];
    
    gPlttBufferFaded[244] = c3;
    gPlttBufferFaded[246] = c1;
    gPlttBufferFaded[248] = c2;
}

//-----------------------------------------------------------------------------

#define tPosX data[1]
#define tPosY data[2]

// The difference between this callback and the previous one
// is that this one can handle multiple objects stepping on triggers
// at the same time.
static void MonitorMultiObjectEventTriggersStepCallback(u8 taskId)
{
    s16 x, y, o, t;
    bool8 standing;
    struct ObjectEvent *objectEvent = NULL;
    struct CoordEvent *coordEvent = NULL;
    s16 *data = gTasks[taskId].data;
    PlayerGetDestCoords(&x, &y);
    
    // If the var is still set like we set it, the expected frame table script hasn't completed yet
    // so don't continue checking.
    if (VarGet(VAR_STEP_TRIGGER) != 0) return;
    
    // For every event object
    for (o = 0; o < OBJECT_EVENTS_COUNT; o++) {
        objectEvent = &gObjectEvents[o];
        if (objectEvent->isPlayer) continue;
        if (!objectEvent->active) continue;
        if (objectEvent->heldMovementActive || objectEvent->singleMovementActive) continue;
        
        // Clear the standing flag, but store its current value in case it needs to be put back
        standing = objectEvent->isStandingOnTrigger;
        objectEvent->isStandingOnTrigger = FALSE;
        
        // For every trigger on the map
        for (t = 0; t < gMapHeader.events->coordEventCount; t++) {
            coordEvent = &gMapHeader.events->coordEvents[t];
            if (!coordEvent->npcTrigger) continue;
            if (objectEvent->currentCoords.x != coordEvent->x + 7) continue;
            if (objectEvent->currentCoords.y != coordEvent->y + 7) continue;
            
            if (!standing) {
                // If this event wasn't standing on a trigger before, trigger it now
                VarSet(VAR_STEP_TRIGGER, 1);
            }
            objectEvent->isStandingOnTrigger = TRUE;
            break;
        }
    }
    tPosX = x;
    tPosY = y;
}

#undef tPosX
#undef tPosY
#undef tRunningVar
#undef tRunningIndex

