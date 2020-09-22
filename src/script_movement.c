#include "global.h"
#include "script_movement.h"
#include "event_object_movement.h"
#include "task.h"
#include "util.h"

// static functions
static void ScriptMovement_StartMoveObjects(u8);
static u8 GetMoveObjectsTaskId(void);
static bool8 ScriptMovement_TryAddNewMovement(u8, u8, const u8 *);
static u8 GetMovementScriptIdFromObjectEventId(u8, u8);
static bool8 IsMovementScriptFinished(u8, u8);
static void ScriptMovement_AddNewMovement(u8, u8, u8, const u8 *);
static void ScriptMovement_UnfreezeActiveObjects(u8);
static void ScriptMovement_MoveObjects(u8);
static void ScriptMovement_TakeStep(u8, u8, u8, const u8 *);

// EWRAM_DATA
static EWRAM_DATA const u8 *gMovementScripts[16] = {0};

// text
bool8 ScriptMovement_StartObjectMovementScript(u8 localId, u8 mapNum, u8 mapGroup, const u8 *movementScript)
{
    u8 eventObjId;

    if (TryGetEventObjectIdByLocalIdAndMap(localId, mapNum, mapGroup, &eventObjId))
        return TRUE;
    if (!FuncIsActiveTask(ScriptMovement_MoveObjects))
        ScriptMovement_StartMoveObjects(50);
    return ScriptMovement_TryAddNewMovement(GetMoveObjectsTaskId(), eventObjId, movementScript);
}

bool8 ScriptMovement_IsObjectMovementFinished(u8 localId, u8 mapNum, u8 mapBank)
{
    u8 eventObjId;
    u8 r4;
    u8 r1;

    if (TryGetEventObjectIdByLocalIdAndMap(localId, mapNum, mapBank, &eventObjId))
        return TRUE;
    r4 = GetMoveObjectsTaskId();
    r1 = GetMovementScriptIdFromObjectEventId(r4, eventObjId);
    if (r1 == 16)
        return TRUE;
    return IsMovementScriptFinished(r4, r1);
}

void ScriptMovement_UnfreezeObjectEvents(void)
{
    u8 taskId;

    taskId = GetMoveObjectsTaskId();
    if (taskId != 0xFF)
    {
        ScriptMovement_UnfreezeActiveObjects(taskId);
        DestroyTask(taskId);
    }
}


static void ScriptMovement_StartMoveObjects(u8 priority)
{
    u8 taskId;
    u8 i;

    taskId = CreateTask(ScriptMovement_MoveObjects, priority);
    for (i = 1; i < 16; i++)
        gTasks[taskId].data[i] = 0xFFFF;
}

static u8 GetMoveObjectsTaskId(void)
{
    return FindTaskIdByFunc(ScriptMovement_MoveObjects);
}

static bool8 ScriptMovement_TryAddNewMovement(u8 taskId, u8 eventObjId, const u8 *movementScript)
{
    u8 r4;

    r4 = GetMovementScriptIdFromObjectEventId(taskId, eventObjId);
    if (r4 != 16)
    {
        if (IsMovementScriptFinished(taskId, r4) == 0)
        {
            return TRUE;
        }
        else
        {
            ScriptMovement_AddNewMovement(taskId, r4, eventObjId, movementScript);
            return FALSE;
        }
    }
    r4 = GetMovementScriptIdFromObjectEventId(taskId, 0xFF);
    if (r4 == 16)
    {
        return TRUE;
    }
    else
    {
        ScriptMovement_AddNewMovement(taskId, r4, eventObjId, movementScript);
        return FALSE;
    }
}

static u8 GetMovementScriptIdFromObjectEventId(u8 taskId, u8 b)
{
    u8 *ptr;
    u8 i;

    ptr = (u8 *)&gTasks[taskId].data[1];
    for (i = 0; i < 16; i++, ptr++)
    {
        if (*ptr == b)
            return i;
    }
    return 16;
}

static void sub_80D34B0(u8 taskId, u8 b, u8 **c)
{
    u8 i;

    *c = (u8 *)&gTasks[taskId].data[1];
    for (i = 0; i < b; i++, (*c)++)
        ;
}

static void sub_80D34E4(u8 taskId, u8 b, u8 c)
{
    u8 *ptr;

    sub_80D34B0(taskId, b, &ptr);
    *ptr = c;  //what is this supposed to do?
}

static void sub_80D3508(u8 taskId, u8 b, u8 *c)
{
    u8 *ptr;

    sub_80D34B0(taskId, b, &ptr);
    *c = *ptr;
}

static void sub_80D352C(u8 a, u8 b)
{
    u16 var = ~gBitTable[b];

    gTasks[a].data[0] &= var;
}

static void sub_80D355C(u8 taskId, u8 b)
{
    gTasks[taskId].data[0] |= gBitTable[b];
}

static bool8 IsMovementScriptFinished(u8 taskId, u8 b)
{
    u16 var = (u16)gTasks[taskId].data[0] & gBitTable[b];

    if (var != 0)
        return TRUE;
    else
        return FALSE;
}

static void npc_obj_offscreen_culling_and_flag_update(u8 a, const u8 *movementScript)
{
    gMovementScripts[a] = movementScript;
}

static const u8 *sub_80D35CC(u8 a)
{
    return gMovementScripts[a];
}

static void ScriptMovement_AddNewMovement(u8 taskId, u8 b, u8 eventObjId, const u8 *movementScript)
{
    sub_80D352C(taskId, b);
    npc_obj_offscreen_culling_and_flag_update(b, movementScript);
    sub_80D34E4(taskId, b, eventObjId);
}

static void ScriptMovement_UnfreezeActiveObjects(u8 taskId)
{
    u8 *pEventObjId;
    u8 i;

    pEventObjId = (u8 *)&gTasks[taskId].data[1];
    for (i = 0; i < 16; i++, pEventObjId++)
    {
        if (*pEventObjId != 0xFF)
            UnfreezeEventObject(&gEventObjects[*pEventObjId]);
    }
}

static void ScriptMovement_MoveObjects(u8 taskId)
{
    u8 i;
    u8 var;

    for (i = 0; i < 16; i++)
    {
        sub_80D3508(taskId, i, &var);
        if (var != 0xFF)
            ScriptMovement_TakeStep(taskId, i, var, sub_80D35CC(i));
    }
}

static void ScriptMovement_TakeStep(u8 taskId, u8 b, u8 eventObjId, const u8 *d)
{
    u8 var;

    if (EventObjectIsHeldMovementActive(&gEventObjects[eventObjId])
     && !EventObjectClearHeldMovementIfFinished(&gEventObjects[eventObjId]))
        return;

    var = *d;
    if (var == 0xFE)
    {
        sub_80D355C(taskId, b);
        FreezeEventObject(&gEventObjects[eventObjId]);
    }
    else
    {
        if (!EventObjectSetHeldMovement(&gEventObjects[eventObjId], var))
        {
            d++;
            npc_obj_offscreen_culling_and_flag_update(b, d);
        }
    }
}

