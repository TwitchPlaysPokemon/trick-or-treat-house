#include "global.h"
#include "battle_setup.h"
#include "berry.h"
#include "clock.h"
#include "coins.h"
#include "contest.h"
#include "contest_util.h"
#include "contest_painting.h"
#include "data.h"
#include "decoration.h"
#include "decoration_inventory.h"
#include "dynamic_placeholder_text_util.h"
#include "event_data.h"
#include "field_door.h"
#include "field_effect.h"
#include "event_object_lock.h"
#include "event_object_movement.h"
#include "field_message_box.h"
#include "field_player_avatar.h"
#include "field_screen_effect.h"
#include "field_specials.h"
#include "field_camera.h"
#include "field_tasks.h"
#include "field_weather.h"
#include "fieldmap.h"
#include "item.h"
#include "lilycove_lady.h"
#include "main.h"
#include "menu.h"
#include "money.h"
#include "mgba.h"
#include "mystery_event_script.h"
#include "palette.h"
#include "party_menu.h"
#include "pokemon_storage_system.h"
#include "random.h"
#include "overworld.h"
#include "rotating_tile_puzzle.h"
#include "rtc.h"
#include "script.h"
#include "script_menu.h"
#include "script_movement.h"
#include "script_pokemon_util.h"
#include "strings.h"
#include "shop.h"
#include "slot_machine.h"
#include "sound.h"
#include "string_util.h"
#include "text.h"
#include "text_window.h"
#include "trainer_see.h"
#include "tv.h"
#include "window.h"
#include "constants/event_objects.h"
#include "constants/script_cmds.h"

typedef u16 (*SpecialFunc)(void);
typedef void (*NativeFunc)(struct ScriptContext *ctx);
typedef bool8 (*SrcCmd)(struct ScriptContext *ctx);

EWRAM_DATA const u8 *gRamScriptPtr = NULL;
static EWRAM_DATA u32 sAddressOffset = 0; // For relative addressing in vgoto etc., used by saved scripts (e.g. Mystery Event)
static EWRAM_DATA u16 sPauseCounter = 0;
static EWRAM_DATA u16 sMovingNpcId = 0;
static EWRAM_DATA u16 sMovingNpcMapGroup = 0;
static EWRAM_DATA u16 sMovingNpcMapNum = 0;
static EWRAM_DATA u16 sFieldEffectScriptId = 0;

static u8 sBrailleWindowId;
static bool8 gIsScriptedWildDouble;

// Reference to an assembly defined constant, the start of the ROM
// We don't actually use the value, just the address it's at.
extern const int Start;

extern const SpecialFunc gSpecials[];
extern const u8 *gStdScripts[];
extern const u8 *gStdScripts_End[];

static void CloseBrailleWindow(void);

// This is defined in here so the optimizer can't see its value when compiling
// script.c.
void * const gNullScriptPtr = NULL;

static const u8 sScriptConditionTable[6][3] =
{
//  <  =  >
    1, 0, 0, // <
    0, 1, 0, // =
    0, 0, 1, // >
    1, 1, 0, // <=
    0, 1, 1, // >=
    1, 0, 1, // !=
};

static u8 *const sScriptStringVars[] =
{
    gStringVar1,
    gStringVar2,
    gStringVar3,
};

static const u8 ErrStr_ScriptError[] = _("Script Error: {NO}{STR_VAR_2}\n{STR_VAR_1}");
static bool8 ShowScriptError(struct ScriptContext *ctx, int errno, const u8 *str)
{
    u8 n = CountDigits(errno);
    ConvertIntToDecimalStringN(gStringVar2, errno, 0, n);
    StringCopy(gStringVar1, str);
    SetupNativeScript(ctx, IsFieldMessageBoxHidden);
    ShowFieldMessage(ErrStr_ScriptError);
    return TRUE;
}

bool8 ScrCmd_nop(struct ScriptContext *ctx)
{
    return FALSE;
}

bool8 ScrCmd_nop1(struct ScriptContext *ctx)
{
    return FALSE;
}

bool8 ScrCmd_end(struct ScriptContext *ctx)
{
    mgba_printf(MGBA_LOG_INFO, "====");
    StopScript(ctx);
    return FALSE;
}

bool8 ScrCmd_special(struct ScriptContext *ctx)
{
    u16 index = ScriptReadHalfword(ctx);

    gSpecials[index]();
    return FALSE;
}

bool8 ScrCmd_specialvar(struct ScriptContext *ctx)
{
    u16 *var = GetVarPointer(ScriptReadHalfword(ctx));

    *var = gSpecials[ScriptReadHalfword(ctx)]();
    return FALSE;
}

bool8 ScrCmd_waitnative(struct ScriptContext *ctx)
{
    bool8 (*addr)(void) = (bool8 (*)(void))ScriptReadWord(ctx);

    SetupNativeScript(ctx, addr);
    return TRUE;
}

bool8 ScrCmd_callnative(struct ScriptContext *ctx)
{
    NativeFunc func = (NativeFunc)ScriptReadWord(ctx);

    func(ctx);
    return FALSE;
}

bool8 ScrCmd_waitstate(struct ScriptContext *ctx)
{
    ScriptContext_Stop();
    return TRUE;
}

bool8 ScrCmd_goto(struct ScriptContext *ctx)
{
    const u8 *ptr = (const u8 *)ScriptReadWord(ctx);

    if ((u32)ptr < ARRAY_COUNT(ctx->data))
        ptr = (const void *)ctx->data[(u32)ptr];

    ScriptJump(ctx, ptr);
    return FALSE;
}

bool8 ScrCmd_return(struct ScriptContext *ctx)
{
    ScriptReturn(ctx);
    return FALSE;
}

bool8 ScrCmd_call(struct ScriptContext *ctx)
{
    const u8 *ptr = (const u8 *)ScriptReadWord(ctx);

    if ((u32)ptr < ARRAY_COUNT(ctx->data))
        ptr = (const void *)ctx->data[(u32)ptr];

    ScriptCall(ctx, ptr);
    return FALSE;
}

bool8 ScrCmd_goto_if(struct ScriptContext *ctx)
{
    u8 condition = ScriptReadByte(ctx);
    const u8 *ptr = (const u8 *)ScriptReadWord(ctx);

    if (sScriptConditionTable[condition][ctx->comparisonResult] == 1)
        ScriptJump(ctx, ptr);
    return FALSE;
}

bool8 ScrCmd_call_if(struct ScriptContext *ctx)
{
    u8 condition = ScriptReadByte(ctx);
    const u8 *ptr = (const u8 *)ScriptReadWord(ctx);

    if (sScriptConditionTable[condition][ctx->comparisonResult] == 1)
        ScriptCall(ctx, ptr);
    return FALSE;
}

bool8 ScrCmd_setvaddress(struct ScriptContext *ctx)
{
    u32 addr1 = (u32)ctx->scriptPtr - 1;
    u32 addr2 = ScriptReadWord(ctx);

    sAddressOffset = addr2 - addr1;
    return FALSE;
}

bool8 ScrCmd_vgoto(struct ScriptContext *ctx)
{
    u32 addr = ScriptReadWord(ctx);

    ScriptJump(ctx, (u8 *)(addr - sAddressOffset));
    return FALSE;
}

bool8 ScrCmd_vcall(struct ScriptContext *ctx)
{
    u32 addr = ScriptReadWord(ctx);

    ScriptCall(ctx, (u8 *)(addr - sAddressOffset));
    return FALSE;
}

bool8 ScrCmd_vgoto_if(struct ScriptContext *ctx)
{
    u8 condition = ScriptReadByte(ctx);
    const u8 *ptr = (const u8 *)(ScriptReadWord(ctx) - sAddressOffset);

    if (sScriptConditionTable[condition][ctx->comparisonResult] == 1)
        ScriptJump(ctx, ptr);
    return FALSE;
}

bool8 ScrCmd_vcall_if(struct ScriptContext *ctx)
{
    u8 condition = ScriptReadByte(ctx);
    const u8 *ptr = (const u8 *)(ScriptReadWord(ctx) - sAddressOffset);

    if (sScriptConditionTable[condition][ctx->comparisonResult] == 1)
        ScriptCall(ctx, ptr);
    return FALSE;
}

bool8 ScrCmd_gotostd(struct ScriptContext *ctx)
{
    u8 index = ScriptReadByte(ctx);
    const u8 **ptr = &gStdScripts[index];

    if (ptr < gStdScripts_End)
        ScriptJump(ctx, *ptr);
    return FALSE;
}

bool8 ScrCmd_callstd(struct ScriptContext *ctx)
{
    u8 index = ScriptReadByte(ctx);
    const u8 **ptr = &gStdScripts[index];

    if (ptr < gStdScripts_End)
        ScriptCall(ctx, *ptr);
    return FALSE;
}

bool8 ScrCmd_gotostd_if(struct ScriptContext *ctx)
{
    u8 condition = ScriptReadByte(ctx);
    u8 index = ScriptReadByte(ctx);

    if (sScriptConditionTable[condition][ctx->comparisonResult] == 1)
    {
        const u8 **ptr = &gStdScripts[index];
        if (ptr < gStdScripts_End)
            ScriptJump(ctx, *ptr);
    }
    return FALSE;
}

bool8 ScrCmd_callstd_if(struct ScriptContext *ctx)
{
    u8 condition = ScriptReadByte(ctx);
    u8 index = ScriptReadByte(ctx);

    if (sScriptConditionTable[condition][ctx->comparisonResult] == 1)
    {
        const u8 **ptr = &gStdScripts[index];
        if (ptr < gStdScripts_End)
            ScriptCall(ctx, *ptr);
    }
    return FALSE;
}
/*
// bool8 ScrCmd_returnram(struct ScriptContext *ctx)
bool8 ScrCmd_gotoram(struct ScriptContext *ctx)
{
    ScriptJump(ctx, gRamScriptPtr);
    return FALSE;
}

bool8 ScrCmd_endram(struct ScriptContext *ctx)
{
    ClearRamScript();
    StopScript(ctx);
    return TRUE;
}

bool8 ScrCmd_setmysteryeventstatus(struct ScriptContext *ctx)
{
    u8 status = ScriptReadByte(ctx);

    SetMysteryEventScriptStatus(status);
    return FALSE;
} */

bool8 ScrCmd_loadword(struct ScriptContext *ctx)
{
    u8 index = ScriptReadByte(ctx);

    ctx->data[index] = ScriptReadWord(ctx);
    return FALSE;
}

bool8 ScrCmd_loadhalf(struct ScriptContext *ctx)
{
    u8 index = ScriptReadByte(ctx);

    ctx->data[index] = VarGet(ScriptReadHalfword(ctx));
    return FALSE;
}

bool8 ScrCmd_loadbyte(struct ScriptContext *ctx)
{
    u8 index = ScriptReadByte(ctx);

    ctx->data[index] = ScriptReadByte(ctx);
    return FALSE;
}

bool8 ScrCmd_loadarg(struct ScriptContext *ctx)
{
    u8 index = ScriptReadByte(ctx);

    ctx->locals[index] = VarGet(ScriptReadHalfword(ctx));
    return FALSE;
}

bool8 ScrCmd_copylocal(struct ScriptContext *ctx)
{
    u8 destIndex = ScriptReadByte(ctx);
    u8 srcIndex = ScriptReadByte(ctx);

    ctx->data[destIndex] = ctx->data[srcIndex];
    return FALSE;
}

bool8 ScrCmd_setvar(struct ScriptContext *ctx)
{
    u16 *ptr = GetVarPointer(ScriptReadHalfword(ctx));
    *ptr = ScriptReadHalfword(ctx);
    return FALSE;
}

bool8 ScrCmd_copyvar(struct ScriptContext *ctx)
{
    u16 *ptr = GetVarPointer(ScriptReadHalfword(ctx));
    *ptr = *GetVarPointer(ScriptReadHalfword(ctx));
    return FALSE;
}

bool8 ScrCmd_setorcopyvar(struct ScriptContext *ctx)
{
    u16 *ptr = GetVarPointer(ScriptReadHalfword(ctx));
    *ptr = VarGet(ScriptReadHalfword(ctx));
    return FALSE;
}

u8 Compare(u16 a, u16 b)
{
    if (a < b)
        return 0;
    if (a == b)
        return 1;
    return 2;
}

bool8 ScrCmd_compare_local_to_local(struct ScriptContext *ctx)
{
    const u8 value1 = ctx->data[ScriptReadByte(ctx)];
    const u8 value2 = ctx->data[ScriptReadByte(ctx)];

    ctx->comparisonResult = Compare(value1, value2);
    return FALSE;
}

bool8 ScrCmd_compare_local_to_value(struct ScriptContext *ctx)
{
    const u8 value1 = ctx->data[ScriptReadByte(ctx)];
    const u8 value2 = ScriptReadByte(ctx);

    ctx->comparisonResult = Compare(value1, value2);
    return FALSE;
}

bool8 ScrCmd_compare_local_to_ptr(struct ScriptContext *ctx)
{
    const u8 value1 = ctx->data[ScriptReadByte(ctx)];
    const u8 value2 = *(const u8 *)ScriptReadWord(ctx);

    ctx->comparisonResult = Compare(value1, value2);
    return FALSE;
}

bool8 ScrCmd_compare_ptr_to_local(struct ScriptContext *ctx)
{
    const u8 value1 = *(const u8 *)ScriptReadWord(ctx);
    const u8 value2 = ctx->data[ScriptReadByte(ctx)];

    ctx->comparisonResult = Compare(value1, value2);
    return FALSE;
}

bool8 ScrCmd_compare_ptr_to_value(struct ScriptContext *ctx)
{
    const u8 value1 = *(const u8 *)ScriptReadWord(ctx);
    const u8 value2 = ScriptReadByte(ctx);

    ctx->comparisonResult = Compare(value1, value2);
    return FALSE;
}

bool8 ScrCmd_compare_ptr_to_ptr(struct ScriptContext *ctx)
{
    const u8 value1 = *(const u8 *)ScriptReadWord(ctx);
    const u8 value2 = *(const u8 *)ScriptReadWord(ctx);

    ctx->comparisonResult = Compare(value1, value2);
    return FALSE;
}

bool8 ScrCmd_compare_var_to_value(struct ScriptContext *ctx)
{
    const u16 value1 = *GetVarPointer(ScriptReadHalfword(ctx));
    const u16 value2 = ScriptReadHalfword(ctx);

    ctx->comparisonResult = Compare(value1, value2);
    return FALSE;
}

bool8 ScrCmd_compare_var_to_var(struct ScriptContext *ctx)
{
    const u16 *ptr1 = GetVarPointer(ScriptReadHalfword(ctx));
    const u16 *ptr2 = GetVarPointer(ScriptReadHalfword(ctx));

    ctx->comparisonResult = Compare(*ptr1, *ptr2);
    return FALSE;
}

// Note: addvar doesn't support adding from a variable in vanilla. If you were to
// add a VarGet() to the above, make sure you change the `addvar VAR_*, -1`
// in the contest scripts to `subvar VAR_*, 1`, else contests will break.
bool8 ScrCmd_addvar(struct ScriptContext *ctx)
{
    u16 *ptr = GetVarPointer(ScriptReadHalfword(ctx));
    *ptr += ScriptReadHalfword(ctx);
    return FALSE;
}

bool8 ScrCmd_subvar(struct ScriptContext *ctx)
{
    u16 *ptr = GetVarPointer(ScriptReadHalfword(ctx));
    *ptr -= VarGet(ScriptReadHalfword(ctx));
    return FALSE;
}

bool8 ScrCmd_mulvar(struct ScriptContext *ctx)
{
    u16 *ptr = GetVarPointer(ScriptReadHalfword(ctx));
    *ptr *= VarGet(ScriptReadHalfword(ctx));
    return FALSE;
}

bool8 ScrCmd_random(struct ScriptContext *ctx)
{
    u16 max = VarGet(ScriptReadHalfword(ctx));

    gSpecialVar_Result = Random() % max;
    return FALSE;
}

bool8 ScrCmd_additem(struct ScriptContext *ctx)
{
    u16 itemId = VarGet(ScriptReadHalfword(ctx));
    u32 quantity = VarGet(ScriptReadHalfword(ctx));

    gSpecialVar_Result = AddBagItem(itemId, (u8)quantity);
    return FALSE;
}

bool8 ScrCmd_resolveitem(struct ScriptContext *ctx)
{
    u16 *itemId = GetVarPointer(ScriptReadHalfword(ctx));
    u16 *quantity = GetVarPointer(ScriptReadHalfword(ctx));
    
    ResolveSpecialItemIds(itemId, quantity);
    return FALSE;
}

bool8 ScrCmd_removeitem(struct ScriptContext *ctx)
{
    u16 itemId = VarGet(ScriptReadHalfword(ctx));
    u32 quantity = VarGet(ScriptReadHalfword(ctx));

    gSpecialVar_Result = RemoveBagItem(itemId, (u8)quantity);
    return FALSE;
}

bool8 ScrCmd_checkitemspace(struct ScriptContext *ctx)
{
    u16 itemId = VarGet(ScriptReadHalfword(ctx));
    u32 quantity = VarGet(ScriptReadHalfword(ctx));

    gSpecialVar_Result = CheckBagHasSpace(itemId, (u8)quantity);
    return FALSE;
}

bool8 ScrCmd_checkitem(struct ScriptContext *ctx)
{
    u16 itemId = VarGet(ScriptReadHalfword(ctx));
    u32 quantity = VarGet(ScriptReadHalfword(ctx));

    gSpecialVar_Result = CheckBagHasItem(itemId, (u8)quantity);
    return FALSE;
}

bool8 ScrCmd_checkitemtype(struct ScriptContext *ctx)
{
    u16 itemId = VarGet(ScriptReadHalfword(ctx));

    gSpecialVar_Result = GetPocketByItemId(itemId);
    return FALSE;
}

bool8 ScrCmd_addpcitem(struct ScriptContext *ctx)
{
    u16 itemId = VarGet(ScriptReadHalfword(ctx));
    u16 quantity = VarGet(ScriptReadHalfword(ctx));

    gSpecialVar_Result = AddPCItem(itemId, quantity);
    return FALSE;
}

bool8 ScrCmd_checknumitem(struct ScriptContext *ctx)
{
    u16 itemId = VarGet(ScriptReadHalfword(ctx));

    gSpecialVar_Result = CountTotalItemQuantityInBag(itemId);
    return FALSE;
}
// bool8 ScrCmd_checkpcitem(struct ScriptContext *ctx)
// {
//     u16 itemId = VarGet(ScriptReadHalfword(ctx));
//     u16 quantity = VarGet(ScriptReadHalfword(ctx));

//     gSpecialVar_Result = CheckPCHasItem(itemId, quantity);
//     return FALSE;
// }

bool8 ScrCmd_adddecoration(struct ScriptContext *ctx)
{
    u32 decorId = VarGet(ScriptReadHalfword(ctx));

    gSpecialVar_Result = DecorationAdd(decorId);
    return FALSE;
}

bool8 ScrCmd_removedecoration(struct ScriptContext *ctx)
{
    u32 decorId = VarGet(ScriptReadHalfword(ctx));

    gSpecialVar_Result = DecorationRemove(decorId);
    return FALSE;
}

bool8 ScrCmd_checkdecorspace(struct ScriptContext *ctx)
{
    u32 decorId = VarGet(ScriptReadHalfword(ctx));

    gSpecialVar_Result = DecorationCheckSpace(decorId);
    return FALSE;
}

bool8 ScrCmd_checkdecor(struct ScriptContext *ctx)
{
    u32 decorId = VarGet(ScriptReadHalfword(ctx));

    gSpecialVar_Result = CheckHasDecoration(decorId);
    return FALSE;
}

bool8 ScrCmd_setflag(struct ScriptContext *ctx)
{
    FlagSet(ScriptReadHalfword(ctx));
    return FALSE;
}

bool8 ScrCmd_clearflag(struct ScriptContext *ctx)
{
    FlagClear(ScriptReadHalfword(ctx));
    return FALSE;
}

bool8 ScrCmd_checkflag(struct ScriptContext *ctx)
{
    ctx->comparisonResult = FlagGet(ScriptReadHalfword(ctx));
    return FALSE;
}

bool8 ScrCmd_incrementgamestat(struct ScriptContext *ctx)
{
    IncrementGameStat(ScriptReadByte(ctx));
    return FALSE;
}

bool8 ScrCmd_animateflash(struct ScriptContext *ctx)
{
    AnimateFlash(ScriptReadByte(ctx));
    ScriptContext_Stop();
    return TRUE;
}

bool8 ScrCmd_setflashlevel(struct ScriptContext *ctx)
{
    SetFlashLevel(VarGet(ScriptReadHalfword(ctx)));
    return FALSE;
}

static bool8 IsPaletteNotActive(void)
{
    if (!gPaletteFade.active)
        return TRUE;
    else
        return FALSE;
}

bool8 ScrCmd_fadescreen(struct ScriptContext *ctx)
{
    FadeScreen(ScriptReadByte(ctx), 0);
    SetupNativeScript(ctx, IsPaletteNotActive);
    return TRUE;
}

bool8 ScrCmd_fadescreenspeed(struct ScriptContext *ctx)
{
    u8 mode = ScriptReadByte(ctx);
    u8 speed = ScriptReadByte(ctx);

    FadeScreen(mode, speed);
    SetupNativeScript(ctx, IsPaletteNotActive);
    return TRUE;
}

bool8 ScrCmd_fadescreenswapbuffers(struct ScriptContext *ctx)
{
    u8 mode = ScriptReadByte(ctx);

    switch (mode)
    {
    case FADE_TO_BLACK:
    case FADE_TO_WHITE:
    default:
        CpuCopy32(gPlttBufferUnfaded, gPaletteDecompressionBuffer, PLTT_DECOMP_BUFFER_SIZE);
        FadeScreen(mode, 0);
        break;
    case FADE_FROM_BLACK:
    case FADE_FROM_WHITE:
        CpuCopy32(gPaletteDecompressionBuffer, gPlttBufferUnfaded, PLTT_DECOMP_BUFFER_SIZE);
        FadeScreen(mode, 0);
        break;
    }

    SetupNativeScript(ctx, IsPaletteNotActive);
    return TRUE;
}

static bool8 RunPauseTimer(void)
{
    if (--sPauseCounter == 0)
        return TRUE;
    else
        return FALSE;
}

bool8 ScrCmd_delay(struct ScriptContext *ctx)
{
    sPauseCounter = ScriptReadHalfword(ctx);
    SetupNativeScript(ctx, RunPauseTimer);
    return TRUE;
}

bool8 ScrCmd_gettime(struct ScriptContext *ctx)
{
    RtcCalcLocalTime();
    gSpecialVar_0x8000 = gLocalTime.hours;
    gSpecialVar_0x8001 = gLocalTime.minutes;
    gSpecialVar_0x8002 = gLocalTime.seconds;
    return FALSE;
}

bool8 ScrCmd_setweather(struct ScriptContext *ctx)
{
    u16 weather = VarGet(ScriptReadHalfword(ctx));

    SetSavedWeather(weather);
    return FALSE;
}

bool8 ScrCmd_resetweather(struct ScriptContext *ctx)
{
    SetSavedWeatherFromCurrMapHeader();
    return FALSE;
}

bool8 ScrCmd_doweather(struct ScriptContext *ctx)
{
    DoCurrentWeather();
    return FALSE;
}

bool8 ScrCmd_setstepcallback(struct ScriptContext *ctx)
{
    ActivatePerStepCallback(ScriptReadByte(ctx));
    return FALSE;
}

bool8 ScrCmd_setnpctriggercallback(struct ScriptContext *ctx)
{
    ActivateNpcTriggerCallback(ScriptReadByte(ctx));
    return FALSE;
}

bool8 ScrCmd_setmaplayout(struct ScriptContext *ctx)
{
    u16 value = VarGet(ScriptReadHalfword(ctx));

    SetCurrentMapLayout(value);
    return FALSE;
}

extern const struct MapLayout *const gMapLayouts[];
static const u8 ErrStr_switchmaplayout[] = _("switchmaplayout checks failed!{PAUSE 50}");
bool8 ScrCmd_switchmaplayout(struct ScriptContext *ctx)
{
    u16 toId = VarGet(ScriptReadHalfword(ctx)) - 1;
    u16 fromId = gSaveBlock1Ptr->mapLayoutId - 1;
    
    if (fromId == toId) return FALSE; //Do nothing
    { // Sanity checks
        if (gMapLayouts[fromId] == NULL)
            return ShowScriptError(ctx, 1, ErrStr_switchmaplayout);
        if (gMapLayouts[toId] == NULL)
            return ShowScriptError(ctx, 2, ErrStr_switchmaplayout);
        if (gMapLayouts[fromId]->width != gMapLayouts[toId]->width) 
            return ShowScriptError(ctx, 3, ErrStr_switchmaplayout);
        if (gMapLayouts[fromId]->height != gMapLayouts[toId]->height)
            return ShowScriptError(ctx, 4, ErrStr_switchmaplayout);
        if (gMapLayouts[fromId]->primaryTileset != gMapLayouts[toId]->primaryTileset)
            return ShowScriptError(ctx, 5, ErrStr_switchmaplayout);
        if (gMapLayouts[fromId]->secondaryTileset != gMapLayouts[toId]->secondaryTileset)
            return ShowScriptError(ctx, 6, ErrStr_switchmaplayout);
    }
    
    SetCurrentMapLayout(toId + 1);
    InitMap();
    MoveCameraAndRedrawMap(0, 0);
    UpdateAllObjectEventsZCoordAndPriority();
    return FALSE;
}

bool8 ScrCmd_setwarp(struct ScriptContext *ctx)
{
    u8 destType = ScriptReadByte(ctx);
    u8 mapGroup = ScriptReadByte(ctx);
    u8 mapNum = ScriptReadByte(ctx);
    u8 warpId = ScriptReadByte(ctx);
    s16 x = VarGet(ScriptReadHalfword(ctx));
    s16 y = VarGet(ScriptReadHalfword(ctx));
    // mgba_printf(MGBA_LOG_INFO, "ScrCmd_setwarp(%d, %d, %d, %d, %d, %d)", destType, mapGroup, mapNum, warpId, x, y);
    
    switch (destType) {
        case WARPTYPE_DYNAMIC:
            SetDynamicWarpWithCoords(0, mapGroup, mapNum, warpId, x, y);
            SetWarpDestinationToDynamicWarp(0);
            break;
        case WARPTYPE_DIVE:
            SetFixedDiveWarp(mapGroup, mapNum, warpId, x, y);
            break;
        case WARPTYPE_HOLE:
            SetFixedHoleWarp(mapGroup, mapNum, warpId, x, y);
            break;
        case WARPTYPE_ESCAPE:
            SetEscapeWarp(mapGroup, mapNum, warpId, x, y);
            break;
        case WARPTYPE_AUXILIARY:
            if (x == -1 || y == -1) {
                // mgba_printf(MGBA_LOG_INFO, "SetAuxilaryWarp(%d, %d, %d)", mapGroup, mapNum, warpId);
                SetAuxilaryWarp(mapGroup, mapNum, warpId);
            }
            else {
                // mgba_printf(MGBA_LOG_INFO, "SetAuxilaryWarpWithCoords(%d, %d, %d, %d, %d)", mapGroup, mapNum, warpId, x, y);
                SetAuxilaryWarpWithCoords(mapGroup, mapNum, warpId, x, y);
            } 
            break;
        default:
            SetWarpDestination(mapGroup, mapNum, warpId, x, y);
            break;
    }
    return FALSE;
}

bool8 ScrCmd_dowarp(struct ScriptContext *ctx)
{
    u8 destType = ScriptReadByte(ctx);
    u8 warpType = ScriptReadByte(ctx);
    u16 x, y;
    
    switch (destType) {
        case WARPTYPE_DYNAMIC:
            SetWarpDestinationToDynamicWarp(0);
            break;
        case WARPTYPE_HOLE:
            PlayerGetDestCoords(&x, &y);
            SetWarpDestinationToFixedHoleWarp(x - MAP_OFFSET, y - MAP_OFFSET);
            break;
        case WARPTYPE_ESCAPE:
            SetWarpDestinationToEscapeWarp();
            break;
        case WARPTYPE_AUXILIARY:
            SetWarpDestinationToAuxilaryWarp();
            break;
        default:
            break;
    }
    switch (warpType) {
        case DOWARP_SILENT:
            DoDiveWarp();
            break;
        case DOWARP_DOOR:
            DoDoorWarp();
            break;
        case DOWARP_HOLE:
            DoFallWarp();
            break;
        case DOWARP_TELEPORT:
            DoTeleportTileWarp();
            break;
        case DOWARP_SPIN_ENTER:
            SetSpinStartFacingDir(GetPlayerFacingDirection());
            DoSpinEnterWarp();
            break;
        case DOWARP_MOSSDEEP:
            DoMossdeepGymWarp();
            break;
        case DOWARP_WHITEFADE:
            DoWhiteFadeWarp();
            break;
        case DOWARP_CUSTOM:
            DoCustomWarp();
            break;
        case DOWARP_STANDARD:
        default:
            DoWarp();
            break;
    }
    ResetInitialPlayerAvatarState();
    return TRUE;
}

/*
bool8 ScrCmd_warptodynamic(struct ScriptContext *ctx)
{
    SetWarpDestinationToDynamicWarp(0);
    DoWarp();
    ResetInitialPlayerAvatarState();
    return TRUE;
}

bool8 ScrCmd_warp(struct ScriptContext *ctx)
{
    u8 mapGroup = ScriptReadByte(ctx);
    u8 mapNum = ScriptReadByte(ctx);
    u8 warpId = ScriptReadByte(ctx);
    u16 x = VarGet(ScriptReadHalfword(ctx));
    u16 y = VarGet(ScriptReadHalfword(ctx));

    SetWarpDestination(mapGroup, mapNum, warpId, x, y);
    DoWarp();
    ResetInitialPlayerAvatarState();
    return TRUE;
}

bool8 ScrCmd_warpsilent(struct ScriptContext *ctx)
{
    u8 mapGroup = ScriptReadByte(ctx);
    u8 mapNum = ScriptReadByte(ctx);
    u8 warpId = ScriptReadByte(ctx);
    u16 x = VarGet(ScriptReadHalfword(ctx));
    u16 y = VarGet(ScriptReadHalfword(ctx));

    SetWarpDestination(mapGroup, mapNum, warpId, x, y);
    DoDiveWarp();
    ResetInitialPlayerAvatarState();
    return TRUE;
}

bool8 ScrCmd_warpcustom(struct ScriptContext *ctx)
{
    u8 mapGroup = ScriptReadByte(ctx);
    u8 mapNum = ScriptReadByte(ctx);
    u8 warpId = ScriptReadByte(ctx);
    u16 x = VarGet(ScriptReadHalfword(ctx));
    u16 y = VarGet(ScriptReadHalfword(ctx));

    SetWarpDestination(mapGroup, mapNum, warpId, x, y);
    DoCustomWarp();
    ResetInitialPlayerAvatarState();
    return TRUE;
}

bool8 ScrCmd_warpdoor(struct ScriptContext *ctx)
{
    u8 mapGroup = ScriptReadByte(ctx);
    u8 mapNum = ScriptReadByte(ctx);
    u8 warpId = ScriptReadByte(ctx);
    u16 x = VarGet(ScriptReadHalfword(ctx));
    u16 y = VarGet(ScriptReadHalfword(ctx));

    SetWarpDestination(mapGroup, mapNum, warpId, x, y);
    DoDoorWarp();
    ResetInitialPlayerAvatarState();
    return TRUE;
}

bool8 ScrCmd_warphole(struct ScriptContext *ctx)
{
    u8 mapGroup = ScriptReadByte(ctx);
    u8 mapNum = ScriptReadByte(ctx);
    u16 x;
    u16 y;

    PlayerGetDestCoords(&x, &y);
    if (mapGroup == MAP_GROUP(UNDEFINED) && mapNum == MAP_NUM(UNDEFINED))
        SetWarpDestinationToFixedHoleWarp(x - MAP_OFFSET, y - MAP_OFFSET);
    else
        SetWarpDestination(mapGroup, mapNum, WARP_ID_NONE, x - MAP_OFFSET, y - MAP_OFFSET);
    DoFallWarp();
    ResetInitialPlayerAvatarState();
    return TRUE;
}

// RS mossdeep gym warp, unused in Emerald
bool8 ScrCmd_warpteleport(struct ScriptContext *ctx)
{
    u8 mapGroup = ScriptReadByte(ctx);
    u8 mapNum = ScriptReadByte(ctx);
    u8 warpId = ScriptReadByte(ctx);
    u16 x = VarGet(ScriptReadHalfword(ctx));
    u16 y = VarGet(ScriptReadHalfword(ctx));

    SetWarpDestination(mapGroup, mapNum, warpId, x, y);
    DoTeleportTileWarp();
    ResetInitialPlayerAvatarState();
    return TRUE;
}

bool8 ScrCmd_warpmossdeepgym(struct ScriptContext *ctx)
{
    u8 mapGroup = ScriptReadByte(ctx);
    u8 mapNum = ScriptReadByte(ctx);
    u8 warpId = ScriptReadByte(ctx);
    u16 x = VarGet(ScriptReadHalfword(ctx));
    u16 y = VarGet(ScriptReadHalfword(ctx));

    SetWarpDestination(mapGroup, mapNum, warpId, x, y);
    DoMossdeepGymWarp();
    ResetInitialPlayerAvatarState();
    return TRUE;
}

bool8 ScrCmd_setdynamicwarp(struct ScriptContext *ctx)
{
    u8 mapGroup = ScriptReadByte(ctx);
    u8 mapNum = ScriptReadByte(ctx);
    u8 warpId = ScriptReadByte(ctx);
    u16 x = VarGet(ScriptReadHalfword(ctx));
    u16 y = VarGet(ScriptReadHalfword(ctx));

    SetDynamicWarpWithCoords(0, mapGroup, mapNum, warpId, x, y);
    return FALSE;
}

bool8 ScrCmd_setdivewarp(struct ScriptContext *ctx)
{
    u8 mapGroup = ScriptReadByte(ctx);
    u8 mapNum = ScriptReadByte(ctx);
    u8 warpId = ScriptReadByte(ctx);
    u16 x = VarGet(ScriptReadHalfword(ctx));
    u16 y = VarGet(ScriptReadHalfword(ctx));

    SetFixedDiveWarp(mapGroup, mapNum, warpId, x, y);
    return FALSE;
}

bool8 ScrCmd_setholewarp(struct ScriptContext *ctx)
{
    u8 mapGroup = ScriptReadByte(ctx);
    u8 mapNum = ScriptReadByte(ctx);
    u8 warpId = ScriptReadByte(ctx);
    u16 x = VarGet(ScriptReadHalfword(ctx));
    u16 y = VarGet(ScriptReadHalfword(ctx));

    SetFixedHoleWarp(mapGroup, mapNum, warpId, x, y);
    return FALSE;
}

bool8 ScrCmd_setescapewarp(struct ScriptContext *ctx)
{
    u8 mapGroup = ScriptReadByte(ctx);
    u8 mapNum = ScriptReadByte(ctx);
    u8 warpId = ScriptReadByte(ctx);
    u16 x = VarGet(ScriptReadHalfword(ctx));
    u16 y = VarGet(ScriptReadHalfword(ctx));

    SetEscapeWarp(mapGroup, mapNum, warpId, x, y);
    return FALSE;
}
//*/

bool8 ScrCmd_getplayerxy(struct ScriptContext *ctx)
{
    u16 *pX = GetVarPointer(ScriptReadHalfword(ctx));
    u16 *pY = GetVarPointer(ScriptReadHalfword(ctx));

    *pX = gSaveBlock1Ptr->pos.x;
    *pY = gSaveBlock1Ptr->pos.y;
    return FALSE;
}

bool8 ScrCmd_getpartysize(struct ScriptContext *ctx)
{
    gSpecialVar_Result = CalculatePlayerPartyCount();
    return FALSE;
}

bool8 ScrCmd_playse(struct ScriptContext *ctx)
{
    PlaySE(ScriptReadHalfword(ctx));
    return FALSE;
}

static bool8 WaitForSoundEffectFinish(void)
{
    if (!IsSEPlaying())
        return TRUE;
    else
        return FALSE;
}

bool8 ScrCmd_waitse(struct ScriptContext *ctx)
{
    SetupNativeScript(ctx, WaitForSoundEffectFinish);
    return TRUE;
}

bool8 ScrCmd_playfanfare(struct ScriptContext *ctx)
{
    PlayFanfare(ScriptReadHalfword(ctx));
    return FALSE;
}

static bool8 WaitForFanfareFinish(void)
{
    return IsFanfareTaskInactive();
}

bool8 ScrCmd_waitfanfare(struct ScriptContext *ctx)
{
    SetupNativeScript(ctx, WaitForFanfareFinish);
    return TRUE;
}

bool8 ScrCmd_playbgm(struct ScriptContext *ctx)
{
    u16 songId = ScriptReadHalfword(ctx);
    bool8 save = ScriptReadByte(ctx);

    if (save == TRUE)
        Overworld_SetSavedMusic(songId);
    PlayNewMapMusic(songId);
    return FALSE;
}

bool8 ScrCmd_savebgm(struct ScriptContext *ctx)
{
    Overworld_SetSavedMusic(ScriptReadHalfword(ctx));
    return FALSE;
}

bool8 ScrCmd_fadedefaultbgm(struct ScriptContext *ctx)
{
    Overworld_ChangeMusicToDefault();
    return FALSE;
}

bool8 ScrCmd_fadenewbgm(struct ScriptContext *ctx)
{
    Overworld_ChangeMusicTo(ScriptReadHalfword(ctx));
    return FALSE;
}

bool8 ScrCmd_fadeoutbgm(struct ScriptContext *ctx)
{
    u8 speed = ScriptReadByte(ctx);

    if (speed != 0)
        FadeOutBGMTemporarily(4 * speed);
    else
        FadeOutBGMTemporarily(4);
    
    if (ctx->data[3] == 1) {
        return FALSE;
    }
    SetupNativeScript(ctx, IsBGMPausedOrStopped);
    return TRUE;
}

bool8 ScrCmd_fadeinbgm(struct ScriptContext *ctx)
{
    u8 speed = ScriptReadByte(ctx);

    if (speed != 0)
        FadeInBGM(4 * speed);
    else
        FadeInBGM(4);
    return FALSE;
}

const static u8 ErrStr_movepointer[] = _("move pointer check failed!{PAUSE 50}");
bool8 ScrCmd_applymovement(struct ScriptContext *ctx)
{
    u16 localId = VarGet(ScriptReadHalfword(ctx));
    const void *movementScript = (const void *)ScriptReadWord(ctx);
    
    if ((u32)movementScript < 4)
        movementScript = (const void *)ctx->data[(u32)movementScript];
    
    // if (movementScript <= (const void*)&Start) {
    //     ShowScriptError(ctx, 5, ErrStr_movepointer);
    //     return FALSE;
    // }

    ScriptMovement_StartObjectMovementScript(localId, gSaveBlock1Ptr->location.mapNum, gSaveBlock1Ptr->location.mapGroup, movementScript);
    sMovingNpcId = localId;
    return FALSE;
}

bool8 ScrCmd_applymovementat(struct ScriptContext *ctx)
{
    u16 localId = VarGet(ScriptReadHalfword(ctx));
    const void *movementScript = (const void *)ScriptReadWord(ctx);
    u8 mapGroup = ScriptReadByte(ctx);
    u8 mapNum = ScriptReadByte(ctx);

    if ((u32)movementScript < ARRAY_COUNT(ctx->data))
        movementScript = (const void *)ctx->data[(u32)movementScript];
    
    if (movementScript <= (const void*)&Start) {
        ShowScriptError(ctx, 5, ErrStr_movepointer);
        return FALSE;
    }

    ScriptMovement_StartObjectMovementScript(localId, mapNum, mapGroup, movementScript);
    sMovingNpcId = localId;
    return FALSE;
}

static bool8 WaitForMovementFinish(void)
{
    return ScriptMovement_IsObjectMovementFinished(sMovingNpcId, sMovingNpcMapNum, sMovingNpcMapGroup);
}

bool8 ScrCmd_waitmovement(struct ScriptContext *ctx)
{
    u16 localId = VarGet(ScriptReadHalfword(ctx));

    if (localId != 0)
        sMovingNpcId = localId;
    sMovingNpcMapGroup = gSaveBlock1Ptr->location.mapGroup;
    sMovingNpcMapNum = gSaveBlock1Ptr->location.mapNum;
    SetupNativeScript(ctx, WaitForMovementFinish);
    return TRUE;
}

bool8 ScrCmd_waitmovementat(struct ScriptContext *ctx)
{
    u16 localId = VarGet(ScriptReadHalfword(ctx));
    u8 mapGroup;
    u8 mapNum;

    if (localId != 0)
        sMovingNpcId = localId;
    mapGroup = ScriptReadByte(ctx);
    mapNum = ScriptReadByte(ctx);
    sMovingNpcMapGroup = mapGroup;
    sMovingNpcMapNum = mapNum;
    SetupNativeScript(ctx, WaitForMovementFinish);
    return TRUE;
}

bool8 ScrCmd_removeobject(struct ScriptContext *ctx)
{
    u16 localId = VarGet(ScriptReadHalfword(ctx));

    RemoveObjectEventByLocalIdAndMap(localId, gSaveBlock1Ptr->location.mapNum, gSaveBlock1Ptr->location.mapGroup);
    return FALSE;
}

bool8 ScrCmd_removeobjectat(struct ScriptContext *ctx)
{
    u16 objectId = VarGet(ScriptReadHalfword(ctx));
    u8 mapGroup = ScriptReadByte(ctx);
    u8 mapNum = ScriptReadByte(ctx);

    RemoveObjectEventByLocalIdAndMap(objectId, mapNum, mapGroup);
    return FALSE;
}

bool8 ScrCmd_addobject(struct ScriptContext *ctx)
{
    u16 objectId = VarGet(ScriptReadHalfword(ctx));

    TrySpawnObjectEvent(objectId, gSaveBlock1Ptr->location.mapNum, gSaveBlock1Ptr->location.mapGroup);
    return FALSE;
}

bool8 ScrCmd_addobjectat(struct ScriptContext *ctx)
{
    u16 objectId = VarGet(ScriptReadHalfword(ctx));
    u8 mapGroup = ScriptReadByte(ctx);
    u8 mapNum = ScriptReadByte(ctx);

    TrySpawnObjectEvent(objectId, mapNum, mapGroup);
    return FALSE;
}

bool8 ScrCmd_setobjectxy(struct ScriptContext *ctx)
{
    u16 localId = VarGet(ScriptReadHalfword(ctx));
    u16 x = VarGet(ScriptReadHalfword(ctx));
    u16 y = VarGet(ScriptReadHalfword(ctx));

    TryMoveObjectEventToMapCoords(localId, gSaveBlock1Ptr->location.mapNum, gSaveBlock1Ptr->location.mapGroup, x, y);
    return FALSE;
}

bool8 ScrCmd_setobjectxyperm(struct ScriptContext *ctx)
{
    u16 localId = VarGet(ScriptReadHalfword(ctx));
    u16 x = VarGet(ScriptReadHalfword(ctx));
    u16 y = VarGet(ScriptReadHalfword(ctx));

    SetObjEventTemplateCoords(localId, x, y);
    return FALSE;
}

bool8 ScrCmd_copyobjectxytoperm(struct ScriptContext *ctx)
{
    u16 localId = VarGet(ScriptReadHalfword(ctx));

    TryOverrideObjectEventTemplateCoords(localId, gSaveBlock1Ptr->location.mapNum, gSaveBlock1Ptr->location.mapGroup);
    return FALSE;
}

bool8 ScrCmd_showobjectat(struct ScriptContext *ctx)
{
    u16 localId = VarGet(ScriptReadHalfword(ctx));
    u8 mapGroup = ScriptReadByte(ctx);
    u8 mapNum = ScriptReadByte(ctx);

    SetObjectInvisibility(localId, mapNum, mapGroup, FALSE);
    return FALSE;
}

bool8 ScrCmd_hideobjectat(struct ScriptContext *ctx)
{
    u16 localId = VarGet(ScriptReadHalfword(ctx));
    u8 mapGroup = ScriptReadByte(ctx);
    u8 mapNum = ScriptReadByte(ctx);

    SetObjectInvisibility(localId, mapNum, mapGroup, TRUE);
    return FALSE;
}

bool8 ScrCmd_setobjectsubpriority(struct ScriptContext *ctx)
{
    u16 localId = VarGet(ScriptReadHalfword(ctx));
    u8 mapGroup = ScriptReadByte(ctx);
    u8 mapNum = ScriptReadByte(ctx);
    u8 priority = ScriptReadByte(ctx);

    SetObjectSubpriority(localId, mapNum, mapGroup, priority + 83);
    return FALSE;
}

bool8 ScrCmd_resetobjectsubpriority(struct ScriptContext *ctx)
{
    u16 localId = VarGet(ScriptReadHalfword(ctx));
    u8 mapGroup = ScriptReadByte(ctx);
    u8 mapNum = ScriptReadByte(ctx);

    ResetObjectSubpriority(localId, mapNum, mapGroup);
    return FALSE;
}

bool8 ScrCmd_faceplayer(struct ScriptContext *ctx)
{
    if (gObjectEvents[gSelectedObjectEvent].active)
    {
        ObjectEventFaceOppositeDirection(&gObjectEvents[gSelectedObjectEvent],
          GetPlayerFacingDirection());
    }
    return FALSE;
}

bool8 ScrCmd_turnobject(struct ScriptContext *ctx)
{
    u16 localId = VarGet(ScriptReadHalfword(ctx));
    u8 direction = ScriptReadByte(ctx);

    ObjectEventTurnByLocalIdAndMap(localId, gSaveBlock1Ptr->location.mapNum, gSaveBlock1Ptr->location.mapGroup, direction);
    return FALSE;
}

bool8 ScrCmd_setobjectmovementtype(struct ScriptContext *ctx)
{
    u16 localId = VarGet(ScriptReadHalfword(ctx));
    u8 movementType = ScriptReadByte(ctx);

    SetObjEventTemplateMovementType(localId, movementType);
    return FALSE;
}

bool8 ScrCmd_createvobject(struct ScriptContext *ctx)
{
    gfxId_t graphicsId = ScriptReadHalfword(ctx);
    u8 virtualObjId = ScriptReadByte(ctx);
    u16 x = VarGet(ScriptReadHalfword(ctx));
    u32 y = VarGet(ScriptReadHalfword(ctx));
    u8 elevation = ScriptReadByte(ctx);
    u8 direction = ScriptReadByte(ctx);

    CreateVirtualObject(graphicsId, virtualObjId, x, y, elevation, direction);
    return FALSE;
}

bool8 ScrCmd_turnvobject(struct ScriptContext *ctx)
{
    u8 virtualObjId = ScriptReadByte(ctx);
    u8 direction = ScriptReadByte(ctx);

    TurnVirtualObject(virtualObjId, direction);
    return FALSE;
}

// lockall freezes all object events except the player immediately.
// The player is frozen after waiting for their current movement to finish.
bool8 ScrCmd_lockall(struct ScriptContext *ctx)
{
    if (IsOverworldLinkActive())
    {
        return FALSE;
    }
    else
    {
        FreezeObjects_WaitForPlayer();
        SetupNativeScript(ctx, IsFreezePlayerFinished);
        return TRUE;
    }
}

// lock freezes all object events except the player and the selected object immediately.
// The player and selected object are frozen after waiting for their current movement to finish.
bool8 ScrCmd_lock(struct ScriptContext *ctx)
{
    if (IsOverworldLinkActive())
    {
        return FALSE;
    }
    else
    {
        if (gObjectEvents[gSelectedObjectEvent].active)
        {
            FreezeObjects_WaitForPlayerAndSelected();
            SetupNativeScript(ctx, IsFreezeSelectedObjectAndPlayerFinished);
        }
        else
        {
            FreezeObjects_WaitForPlayer();
            SetupNativeScript(ctx, IsFreezePlayerFinished);
        }
        return TRUE;
    }
}

bool8 ScrCmd_releaseall(struct ScriptContext *ctx)
{
    u8 playerObjectId;

    HideFieldMessageBox();
    playerObjectId = GetObjectEventIdByLocalIdAndMap(OBJ_EVENT_ID_PLAYER, 0, 0);
    ObjectEventClearHeldMovementIfFinished(&gObjectEvents[playerObjectId]);
    ScriptMovement_UnfreezeObjectEvents();
    UnfreezeObjectEvents();
    return FALSE;
}

bool8 ScrCmd_release(struct ScriptContext *ctx)
{
    u8 playerObjectId;

    HideFieldMessageBox();
    if (gObjectEvents[gSelectedObjectEvent].active)
        ObjectEventClearHeldMovementIfFinished(&gObjectEvents[gSelectedObjectEvent]);
    playerObjectId = GetObjectEventIdByLocalIdAndMap(OBJ_EVENT_ID_PLAYER, 0, 0);
    ObjectEventClearHeldMovementIfFinished(&gObjectEvents[playerObjectId]);
    ScriptMovement_UnfreezeObjectEvents();
    UnfreezeObjectEvents();
    return FALSE;
}

bool8 ScrCmd_setspeaker(struct ScriptContext *ctx)
{
    const u8 *name = (const u8 *)ScriptReadWord(ctx);
    SetSpeakerName(name);
    return FALSE;
}

bool8 ScrCmd_message(struct ScriptContext *ctx)
{
    const u8 *msg = (const u8 *)ScriptReadWord(ctx);

    if ((u32) msg < ARRAY_COUNT(ctx->data))
        msg = (const u8 *)ctx->data[(u32) msg];
    ShowFieldMessage(msg);
    return FALSE;
}

bool8 ScrCmd_pokenavcall(struct ScriptContext *ctx)
{
    const u8 *msg = (const u8 *)ScriptReadWord(ctx);

    if (msg == NULL)
        msg = (const u8 *)ctx->data[0];
    ShowPokenavFieldMessage(msg);
    return FALSE;
}

bool8 ScrCmd_messageautoscroll(struct ScriptContext *ctx)
{
    const u8 *msg = (const u8 *)ScriptReadWord(ctx);

    if (msg == NULL)
        msg = (const u8 *)ctx->data[0];
    gTextFlags.autoScroll = TRUE;
    gTextFlags.forceMidTextSpeed = TRUE;
    ShowFieldAutoScrollMessage(msg);
    return FALSE;
}

// Prints all at once. Skips waiting for player input. Only used by link contests
bool8 ScrCmd_messageinstant(struct ScriptContext *ctx)
{
    const u8 *msg = (const u8 *)ScriptReadWord(ctx);

    if (msg == NULL)
        msg = (const u8 *)ctx->data[0];
    LoadMessageBoxAndBorderGfx();
    DrawDialogueFrame(0, TRUE);
    AddTextPrinterParameterized(0, FONT_NORMAL, msg, 0, 1, 0, NULL);
    return FALSE;
}

// TODO:
bool8 ScrCmd_messagewordwrap(struct ScriptContext *ctx)
{
    const u8 *msg = (const u8 *)ScriptReadWord(ctx);

    if (msg == NULL)
        msg = (const u8 *)ctx->data[0];
    
    StringExpandPlaceholders(gStringBuffer, msg);
    mgba_printf(MGBA_LOG_INFO, "doing messagewordwrap: %S", gStringBuffer);
    DetermineWordWrapInStrVar4(1, 1, 210);
    ShowFieldMessageFromBuffer();
    return FALSE;
}

bool8 ScrCmd_waitmessage(struct ScriptContext *ctx)
{
    SetupNativeScript(ctx, IsFieldMessageBoxHidden);
    return TRUE;
}

bool8 ScrCmd_closemessage(struct ScriptContext *ctx)
{
    HideFieldMessageBox();
    return FALSE;
}

static bool8 WaitForAorBPress(void)
{
    if (JOY_NEW(A_BUTTON))
        return TRUE;
    if (JOY_NEW(B_BUTTON))
        return TRUE;
    return FALSE;
}

bool8 ScrCmd_waitbuttonpress(struct ScriptContext *ctx)
{
    SetupNativeScript(ctx, WaitForAorBPress);
    return TRUE;
}

bool8 ScrCmd_yesnobox(struct ScriptContext *ctx)
{
    u8 left = ScriptReadByte(ctx);
    u8 top = ScriptReadByte(ctx);

    if (ScriptMenu_YesNo(left, top) == TRUE)
    {
        ScriptContext_Stop();
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

bool8 ScrCmd_multichoice(struct ScriptContext *ctx)
{
    u8 left = ScriptReadByte(ctx);
    u8 top = ScriptReadByte(ctx);
    u8 multichoiceId = ScriptReadByte(ctx);
    bool8 ignoreBPress = ScriptReadByte(ctx);

    // mgba_printf(MGBA_LOG_INFO, "multichoice");
    mgba_printf(MGBA_LOG_INFO, "multichoice: %d, %d, %d, %d", left, top, multichoiceId, ignoreBPress);
    if (ScriptMenu_Multichoice(left, top, multichoiceId, ignoreBPress) == TRUE)
    {
        mgba_printf(MGBA_LOG_INFO, "multichoice success!");
        ScriptContext_Stop();
        return TRUE;
    }
    else
    {
        mgba_printf(MGBA_LOG_INFO, "multichoice failed!");
        return FALSE;
    }
}

bool8 ScrCmd_multichoicedefault(struct ScriptContext *ctx)
{
    u8 left = ScriptReadByte(ctx);
    u8 top = ScriptReadByte(ctx);
    u8 multichoiceId = ScriptReadByte(ctx);
    u8 defaultChoice = ScriptReadByte(ctx);
    bool8 ignoreBPress = ScriptReadByte(ctx);

    if (ScriptMenu_MultichoiceWithDefault(left, top, multichoiceId, ignoreBPress, defaultChoice) == TRUE)
    {
        ScriptContext_Stop();
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

bool8 ScrCmd_loaddynamicstring(struct ScriptContext *ctx)
{
    u8 id = ScriptReadByte(ctx);
    const u8 *ptr = (u8 *)ScriptReadWord(ctx);
    
    if ((u32)ptr < ARRAY_COUNT(ctx->data))
        ptr = (const u8*)ctx->data[(u32)ptr];
    
    DynamicPlaceholder_Set(id, ptr);
    return FALSE;
}

bool8 ScrCmd_multichoicegrid(struct ScriptContext *ctx)
{
    u8 left = ScriptReadByte(ctx);
    u8 top = ScriptReadByte(ctx);
    u8 multichoiceId = ScriptReadByte(ctx);
    u8 numColumns = ScriptReadByte(ctx);
    bool8 ignoreBPress = ScriptReadByte(ctx);

    if (ScriptMenu_MultichoiceGrid(left, top, multichoiceId, ignoreBPress, numColumns) == TRUE)
    {
        ScriptContext_Stop();
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

bool8 ScrCmd_showmonpic(struct ScriptContext *ctx)
{
    u16 species = VarGet(ScriptReadHalfword(ctx));
    u8 x = ScriptReadByte(ctx);
    u8 y = ScriptReadByte(ctx);

    ScriptMenu_ShowPokemonPic(species, x, y);
    return FALSE;
}

bool8 ScrCmd_hidemonpic(struct ScriptContext *ctx)
{
    // The hide function returns a pointer to a function
    // that returns true once the pic is hidden
    bool8 (*func)(void) = ScriptMenu_HidePokemonPic();

    if (func == NULL)
        return FALSE;
    SetupNativeScript(ctx, func);
    return TRUE;
}

bool8 ScrCmd_showcontestpainting(struct ScriptContext *ctx)
{
    u8 contestWinnerId = ScriptReadByte(ctx);

    // Artist's painting is temporary and already has its data loaded
    if (contestWinnerId != CONTEST_WINNER_ARTIST)
        SetContestWinnerForPainting(contestWinnerId);

    ShowContestPainting();
    ScriptContext_Stop();
    return TRUE;
}

bool8 ScrCmd_braillemessage(struct ScriptContext *ctx)
{
    u8 *ptr = (u8 *)ScriptReadWord(ctx);
    struct WindowTemplate winTemplate;
    s32 i;
    u8 width, height;
    u8 xWindow, yWindow, xText, yText;
    u8 temp;

    // + 6 for the 6 bytes at the start of a braille message (brailleformat macro)
    // In RS these bytes are used to position the text and window, but
    // in Emerald they are unused and position is calculated below instead
    StringExpandPlaceholders(gStringBuffer, ptr + 6);

    width = GetStringWidth(FONT_BRAILLE, gStringBuffer, -1) / 8u;

    if (width > 28)
        width = 28;

    for (i = 0, height = 4; gStringBuffer[i] != EOS;)
    {
        if (gStringBuffer[i++] == CHAR_NEWLINE)
            height += 3;
    }

    if (height > 18)
        height = 18;

    temp = width + 2;
    xWindow = (30 - temp) / 2;

    temp = height + 2;
    yText = (20 - temp) / 2;

    xText = xWindow;
    xWindow += 1;

    yWindow = yText;
    yText += 2;

    xText = (xWindow - xText - 1) * 8 + 3;
    yText = (yText - yWindow - 1) * 8;

    winTemplate = CreateWindowTemplate(0, xWindow, yWindow + 1, width, height, 0xF, 0x1);
    sBrailleWindowId = AddWindow(&winTemplate);
    LoadUserWindowBorderGfx(sBrailleWindowId, 0x214, 0xE0);
    DrawStdWindowFrame(sBrailleWindowId, FALSE);
    PutWindowTilemap(sBrailleWindowId);
    FillWindowPixelBuffer(sBrailleWindowId, PIXEL_FILL(1));
    AddTextPrinterParameterized(sBrailleWindowId, FONT_BRAILLE, gStringBuffer, xText, yText, TEXT_SKIP_DRAW, NULL);
    CopyWindowToVram(sBrailleWindowId, COPYWIN_FULL);
    return FALSE;
}

bool8 ScrCmd_closebraillemessage(struct ScriptContext *ctx)
{
    CloseBrailleWindow();
    return FALSE;
}

bool8 ScrCmd_vmessage(struct ScriptContext *ctx)
{
    u32 msg = ScriptReadWord(ctx);

    ShowFieldMessage((u8 *)(msg - sAddressOffset));
    return FALSE;
}

bool8 ScrCmd_bufferspeciesname(struct ScriptContext *ctx)
{
    u8 stringVarIndex = ScriptReadByte(ctx);
    u16 species = VarGet(ScriptReadHalfword(ctx));

    StringCopy(sScriptStringVars[stringVarIndex], gSpeciesNames[species]);
    return FALSE;
}

bool8 ScrCmd_bufferleadmonspeciesname(struct ScriptContext *ctx)
{
    u8 stringVarIndex = ScriptReadByte(ctx);

    u8 *dest = sScriptStringVars[stringVarIndex];
    u8 partyIndex = GetLeadMonIndex();
    u32 species = GetMonData(&gPlayerParty[partyIndex], MON_DATA_SPECIES, NULL);
    StringCopy(dest, gSpeciesNames[species]);
    return FALSE;
}

bool8 ScrCmd_bufferpartymonnick(struct ScriptContext *ctx)
{
    u8 stringVarIndex = ScriptReadByte(ctx);
    u16 partyIndex = VarGet(ScriptReadHalfword(ctx));

    GetMonData(&gPlayerParty[partyIndex], MON_DATA_NICKNAME, sScriptStringVars[stringVarIndex]);
    StringGet_Nickname(sScriptStringVars[stringVarIndex]);
    return FALSE;
}

bool8 ScrCmd_bufferitemname(struct ScriptContext *ctx)
{
    u8 stringVarIndex = ScriptReadByte(ctx);
    u16 itemId = VarGet(ScriptReadHalfword(ctx));

    CopyItemName(itemId, sScriptStringVars[stringVarIndex]);
    return FALSE;
}

bool8 ScrCmd_bufferitemnameplural(struct ScriptContext *ctx)
{
    u8 stringVarIndex = ScriptReadByte(ctx);
    u16 itemId = VarGet(ScriptReadHalfword(ctx));
    u16 quantity = VarGet(ScriptReadHalfword(ctx));

    CopyItemNameHandlePlural(itemId, sScriptStringVars[stringVarIndex], quantity);
    return FALSE;
}

bool8 ScrCmd_bufferdecorationname(struct ScriptContext *ctx)
{
    u8 stringVarIndex = ScriptReadByte(ctx);
    u16 decorId = VarGet(ScriptReadHalfword(ctx));

    StringCopy(sScriptStringVars[stringVarIndex], gDecorations[decorId].name);
    return FALSE;
}

bool8 ScrCmd_buffermovename(struct ScriptContext *ctx)
{
    u8 stringVarIndex = ScriptReadByte(ctx);
    u16 moveId = VarGet(ScriptReadHalfword(ctx));

    StringCopy(sScriptStringVars[stringVarIndex], gMoveNames[moveId]);
    return FALSE;
}

bool8 ScrCmd_buffernumberstring(struct ScriptContext *ctx)
{
    u8 stringVarIndex = ScriptReadByte(ctx);
    u16 num = VarGet(ScriptReadHalfword(ctx));
    u8 numDigits = CountDigits(num);

    ConvertIntToDecimalStringN(sScriptStringVars[stringVarIndex], num, STR_CONV_MODE_LEFT_ALIGN, numDigits);
    return FALSE;
}

bool8 ScrCmd_bufferstdstring(struct ScriptContext *ctx)
{
    u8 stringVarIndex = ScriptReadByte(ctx);
    u16 index = VarGet(ScriptReadHalfword(ctx));

    StringCopy(sScriptStringVars[stringVarIndex], gStdStrings[index]);
    return FALSE;
}

bool8 ScrCmd_bufferselectedstring(struct ScriptContext *ctx)
{
    u8 stringVarIndex = ScriptReadByte(ctx);

    StringCopy(sScriptStringVars[stringVarIndex], (const u8*)ctx->data[0]);
    return FALSE;
}

bool8 ScrCmd_buffercontestname(struct ScriptContext *ctx)
{
    u8 stringVarIndex = ScriptReadByte(ctx);
    u16 category = VarGet(ScriptReadHalfword(ctx));

    BufferContestName(sScriptStringVars[stringVarIndex], category);
    return FALSE;
}

bool8 ScrCmd_bufferstring(struct ScriptContext *ctx)
{
    u8 stringVarIndex = ScriptReadByte(ctx);
    const u8 *text = (u8 *)ScriptReadWord(ctx);
    
    if (text == NULL)
        text = (const u8 *)ctx->data[0];

    StringCopy(sScriptStringVars[stringVarIndex], text);
    return FALSE;
}

bool8 ScrCmd_vbuffermessage(struct ScriptContext *ctx)
{
    const u8 *ptr = (u8 *)(ScriptReadWord(ctx) - sAddressOffset);

    StringExpandPlaceholders(gStringBuffer, ptr);
    return FALSE;
}

bool8 ScrCmd_vbufferstring(struct ScriptContext *ctx)
{
    u8 stringVarIndex = ScriptReadByte(ctx);
    u32 addr = ScriptReadWord(ctx);

    const u8 *src = (u8 *)(addr - sAddressOffset);
    u8 *dest = sScriptStringVars[stringVarIndex];
    StringCopy(dest, src);
    return FALSE;
}

bool8 ScrCmd_bufferboxname(struct ScriptContext *ctx)
{
    u8 stringVarIndex = ScriptReadByte(ctx);
    u16 boxId = VarGet(ScriptReadHalfword(ctx));

    StringCopy(sScriptStringVars[stringVarIndex], GetBoxNamePtr(boxId));
    return FALSE;
}

bool8 ScrCmd_givemon(struct ScriptContext *ctx)
{
    u16 species = VarGet(ScriptReadHalfword(ctx));
    u8 level = ScriptReadByte(ctx);
    u16 item = VarGet(ScriptReadHalfword(ctx));
    u32 unkParam1 = ScriptReadWord(ctx);
    u32 unkParam2 = ScriptReadWord(ctx);
    u8 unkParam3 = ScriptReadByte(ctx);

    gSpecialVar_Result = ScriptGiveMon(species, level, item, unkParam1, unkParam2, unkParam3);
    return FALSE;
}

bool8 ScrCmd_giveegg(struct ScriptContext *ctx)
{
    u16 species = VarGet(ScriptReadHalfword(ctx));

    gSpecialVar_Result = ScriptGiveEgg(species);
    return FALSE;
}

bool8 ScrCmd_setmonmove(struct ScriptContext *ctx)
{
    u8 partyIndex = ScriptReadByte(ctx);
    u8 slot = ScriptReadByte(ctx);
    u16 move = ScriptReadHalfword(ctx);

    ScriptSetMonMoveSlot(partyIndex, move, slot);
    return FALSE;
}

bool8 ScrCmd_checkpartymove(struct ScriptContext *ctx)
{
    u8 i;
    u16 moveId = ScriptReadHalfword(ctx);

    gSpecialVar_Result = PARTY_SIZE;
    for (i = 0; i < PARTY_SIZE; i++)
    {
        u16 species = GetMonData(&gPlayerParty[i], MON_DATA_SPECIES, NULL);
        if (!species)
            break;
        if (!GetMonData(&gPlayerParty[i], MON_DATA_IS_EGG) && MonKnowsMove(&gPlayerParty[i], moveId) == TRUE)
        {
            gSpecialVar_Result = i;
            gSpecialVar_0x8004 = species;
            break;
        }
    }
    return FALSE;
}

bool8 ScrCmd_addmoney(struct ScriptContext *ctx)
{
    u32 amount = VarGet(ScriptReadWord(ctx));
    u8 ignore = ScriptReadByte(ctx);

    if (!ignore)
        AddMoney(&gSaveBlock1Ptr->money, amount);
    return FALSE;
}

bool8 ScrCmd_removemoney(struct ScriptContext *ctx)
{
    u32 amount = VarGet(ScriptReadWord(ctx));
    u8 ignore = ScriptReadByte(ctx);

    if (!ignore)
        RemoveMoney(&gSaveBlock1Ptr->money, amount);
    return FALSE;
}

bool8 ScrCmd_checkmoney(struct ScriptContext *ctx)
{
    u32 amount = VarGet(ScriptReadWord(ctx));
    u8 ignore = ScriptReadByte(ctx);

    if (!ignore)
        gSpecialVar_Result = IsEnoughMoney(&gSaveBlock1Ptr->money, amount);
    return FALSE;
}

bool8 ScrCmd_showmoneybox(struct ScriptContext *ctx)
{
    u8 x = ScriptReadByte(ctx);
    u8 y = ScriptReadByte(ctx);
    u8 ignore = ScriptReadByte(ctx);

    if (!ignore)
        DrawMoneyBox(GetMoney(&gSaveBlock1Ptr->money), x, y);
    return FALSE;
}

bool8 ScrCmd_hidemoneybox(struct ScriptContext *ctx)
{
    /*u8 x = ScriptReadByte(ctx);
    u8 y = ScriptReadByte(ctx);*/

    HideMoneyBox();
    return FALSE;
}

bool8 ScrCmd_updatemoneybox(struct ScriptContext *ctx)
{
    u8 x = ScriptReadByte(ctx);
    u8 y = ScriptReadByte(ctx);
    u8 ignore = ScriptReadByte(ctx);

    if (!ignore)
        ChangeAmountInMoneyBox(GetMoney(&gSaveBlock1Ptr->money));
    return FALSE;
}

bool8 ScrCmd_showcoinsbox(struct ScriptContext *ctx)
{
    u8 x = ScriptReadByte(ctx);
    u8 y = ScriptReadByte(ctx);

    ShowCoinsWindow(GetCoins(), x, y);
    return FALSE;
}

bool8 ScrCmd_hidecoinsbox(struct ScriptContext *ctx)
{
    u8 x = ScriptReadByte(ctx);
    u8 y = ScriptReadByte(ctx);

    HideCoinsWindow();
    return FALSE;
}

bool8 ScrCmd_updatecoinsbox(struct ScriptContext *ctx)
{
    u8 x = ScriptReadByte(ctx);
    u8 y = ScriptReadByte(ctx);

    PrintCoinsString(GetCoins());
    return FALSE;
}

bool8 ScrCmd_trainerbattle(struct ScriptContext *ctx)
{
    ctx->scriptPtr = BattleSetup_ConfigureTrainerBattle(ctx->scriptPtr);
    return FALSE;
}

bool8 ScrCmd_dotrainerbattle(struct ScriptContext *ctx)
{
    BattleSetup_StartTrainerBattle();
    return TRUE;
}

bool8 ScrCmd_gotopostbattlescript(struct ScriptContext *ctx)
{
    ctx->scriptPtr = BattleSetup_GetScriptAddrAfterBattle();
    return FALSE;
}

bool8 ScrCmd_gotobeatenscript(struct ScriptContext *ctx)
{
    ctx->scriptPtr = BattleSetup_GetTrainerPostBattleScript();
    return FALSE;
}

bool8 ScrCmd_checktrainerflag(struct ScriptContext *ctx)
{
    u16 index = VarGet(ScriptReadHalfword(ctx));

    ctx->comparisonResult = HasTrainerBeenFought(index);
    return FALSE;
}

bool8 ScrCmd_settrainerflag(struct ScriptContext *ctx)
{
    u16 index = VarGet(ScriptReadHalfword(ctx));

    SetTrainerFlag(index);
    return FALSE;
}

bool8 ScrCmd_cleartrainerflag(struct ScriptContext *ctx)
{
    u16 index = VarGet(ScriptReadHalfword(ctx));

    ClearTrainerFlag(index);
    return FALSE;
}

bool8 ScrCmd_setwildbattle(struct ScriptContext *ctx)
{
    u16 species = ScriptReadHalfword(ctx);
    u8 level = ScriptReadByte(ctx);
    u16 item = ScriptReadHalfword(ctx);
    u16 species2 = ScriptReadHalfword(ctx);
    u8 level2 = ScriptReadByte(ctx);
    u16 item2 = ScriptReadHalfword(ctx);

    if(species2 == SPECIES_NONE)
    {
        CreateScriptedWildMon(species, level, item);
        gIsScriptedWildDouble = FALSE;
    }
    else
    { 
        CreateScriptedDoubleWildMon(species, level, item, species2, level2, item2);
        gIsScriptedWildDouble = TRUE;
    }

    return FALSE;
}

bool8 ScrCmd_dowildbattle(struct ScriptContext *ctx)
{
    if (gIsScriptedWildDouble == FALSE)
        BattleSetup_StartScriptedWildBattle();
    else
        BattleSetup_StartScriptedDoubleWildBattle();

    ScriptContext_Stop();

    return TRUE;
}

bool8 ScrCmd_pokemart(struct ScriptContext *ctx)
{
    const void *ptr = (void *)ScriptReadWord(ctx);
    
    if (ptr == NULL)
        ptr = (const u8 *)ctx->data[0];

    CreatePokemartMenu(ptr);
    ScriptContext_Stop();
    return TRUE;
}

bool8 ScrCmd_pokemartdecoration(struct ScriptContext *ctx)
{
    const void *ptr = (void *)ScriptReadWord(ctx);
    
    if (ptr == NULL)
        ptr = (const u8 *)ctx->data[0];

    CreateDecorationShop1Menu(ptr);
    ScriptContext_Stop();
    return TRUE;
}

// Changes clerk dialogue slightly from above. See MART_TYPE_DECOR2
bool8 ScrCmd_pokemartdecoration2(struct ScriptContext *ctx)
{
    const void *ptr = (void *)ScriptReadWord(ctx);
    
    if (ptr == NULL)
        ptr = (const u8 *)ctx->data[0];

    CreateDecorationShop2Menu(ptr);
    ScriptContext_Stop();
    return TRUE;
}

bool8 ScrCmd_playslotmachine(struct ScriptContext *ctx)
{
    u8 machineId = VarGet(ScriptReadHalfword(ctx));

    PlaySlotMachine(machineId, CB2_ReturnToFieldContinueScriptPlayMapMusic);
    ScriptContext_Stop();
    return TRUE;
}

bool8 ScrCmd_setberrytree(struct ScriptContext *ctx)
{
    u8 treeId = ScriptReadByte(ctx);
    u8 berry = ScriptReadByte(ctx);
    u8 growthStage = ScriptReadByte(ctx);

    if (berry == 0)
        PlantBerryTree(treeId, berry, growthStage, FALSE);
    else
        PlantBerryTree(treeId, berry, growthStage, FALSE);
    return FALSE;
}

bool8 ScrCmd_getpokenewsactive(struct ScriptContext *ctx)
{
    u16 newsKind = VarGet(ScriptReadHalfword(ctx));

    gSpecialVar_Result = IsPokeNewsActive(newsKind);
    return FALSE;
}

bool8 ScrCmd_choosecontestmon(struct ScriptContext *ctx)
{
    ChooseContestMon();
    ScriptContext_Stop();
    return TRUE;
}


bool8 ScrCmd_startcontest(struct ScriptContext *ctx)
{
    StartContest();
    ScriptContext_Stop();
    return TRUE;
}

bool8 ScrCmd_showcontestresults(struct ScriptContext *ctx)
{
    ShowContestResults();
    ScriptContext_Stop();
    return TRUE;
}

bool8 ScrCmd_contestlinktransfer(struct ScriptContext *ctx)
{
    ContestLinkTransfer(gSpecialVar_ContestCategory);
    ScriptContext_Stop();
    return TRUE;
}

bool8 ScrCmd_dofieldeffect(struct ScriptContext *ctx)
{
    u16 effectId = VarGet(ScriptReadHalfword(ctx));

    sFieldEffectScriptId = effectId;
    FieldEffectStart(sFieldEffectScriptId);
    return FALSE;
}

bool8 ScrCmd_setfieldeffectargument(struct ScriptContext *ctx)
{
    u8 argNum = ScriptReadByte(ctx);

    gFieldEffectArguments[argNum] = (s16)VarGet(ScriptReadHalfword(ctx));
    return FALSE;
}

bool8 ScrCmd_setfieldeffectargstoobjectloc(struct ScriptContext *ctx)
{
    u16 localId = VarGet(ScriptReadHalfword(ctx));
    u8 argNum = ScriptReadByte(ctx);
    u8 evtid = GetObjectEventIdByLocalIdAndMap(localId, gSaveBlock1Ptr->location.mapNum, gSaveBlock1Ptr->location.mapGroup);
    struct ObjectEvent *eventObj = &gObjectEvents[evtid];

    gFieldEffectArguments[argNum+0] = eventObj->currentCoords.x;
    gFieldEffectArguments[argNum+1] = eventObj->currentCoords.y;
    gFieldEffectArguments[argNum+2] = eventObj->previousElevation;
    return FALSE;
}

static bool8 WaitForFieldEffectFinish(void)
{
    if (!FieldEffectActiveListContains(sFieldEffectScriptId))
        return TRUE;
    else
        return FALSE;
}

bool8 ScrCmd_waitfieldeffect(struct ScriptContext *ctx)
{
    sFieldEffectScriptId = VarGet(ScriptReadHalfword(ctx));
    SetupNativeScript(ctx, WaitForFieldEffectFinish);
    return TRUE;
}

bool8 ScrCmd_setrespawn(struct ScriptContext *ctx)
{
    u16 healLocationId = VarGet(ScriptReadHalfword(ctx));

    SetLastHealLocationWarp(healLocationId);
    return FALSE;
}

bool8 ScrCmd_checkplayergender(struct ScriptContext *ctx)
{
    gSpecialVar_Result = gSaveBlock2Ptr->playerGender;
    return FALSE;
}

bool8 ScrCmd_playmoncry(struct ScriptContext *ctx)
{
    u16 species = VarGet(ScriptReadHalfword(ctx));
    u16 mode = VarGet(ScriptReadHalfword(ctx));

    PlayCry_Script(species, mode);
    return FALSE;
}

bool8 ScrCmd_waitmoncry(struct ScriptContext *ctx)
{
    SetupNativeScript(ctx, IsCryFinished);
    return TRUE;
}

bool8 ScrCmd_setmetatile(struct ScriptContext *ctx)
{
    u16 x = VarGet(ScriptReadHalfword(ctx));
    u16 y = VarGet(ScriptReadHalfword(ctx));
    u16 tileId = VarGet(ScriptReadHalfword(ctx));
    u16 isImpassable = VarGet(ScriptReadHalfword(ctx));

    x += MAP_OFFSET;
    y += MAP_OFFSET;
    if (!isImpassable)
        MapGridSetMetatileIdAt(x, y, tileId);
    else
        MapGridSetMetatileIdAt(x, y, tileId | MAPGRID_COLLISION_MASK);
    return FALSE;
}

bool8 ScrCmd_setmetatileex(struct ScriptContext *ctx)
{
    u16 x = VarGet(ScriptReadHalfword(ctx));
    u16 y = VarGet(ScriptReadHalfword(ctx));
    u16 metatile = ScriptReadHalfword(ctx);
    
    mgba_printf(MGBA_LOG_INFO, "Setting metatileEX => x=%d, y=%d, m=%x", x, y, metatile);

    x += MAP_OFFSET;
    y += MAP_OFFSET;
    MapGridSetMetatileEntryAt(x, y, metatile);
    return FALSE;
}

bool8 ScrCmd_opendoor(struct ScriptContext *ctx)
{
    u16 x = VarGet(ScriptReadHalfword(ctx));
    u16 y = VarGet(ScriptReadHalfword(ctx));

    x += MAP_OFFSET;
    y += MAP_OFFSET;
    PlaySE(GetDoorSoundEffect(x, y));
    FieldAnimateDoorOpen(x, y);
    return FALSE;
}

bool8 ScrCmd_closedoor(struct ScriptContext *ctx)
{
    u16 x = VarGet(ScriptReadHalfword(ctx));
    u16 y = VarGet(ScriptReadHalfword(ctx));

    x += MAP_OFFSET;
    y += MAP_OFFSET;
    FieldAnimateDoorClose(x, y);
    return FALSE;
}

static bool8 IsDoorAnimationStopped(void)
{
    if (!FieldIsDoorAnimationRunning())
        return TRUE;
    else
        return FALSE;
}

bool8 ScrCmd_waitdooranim(struct ScriptContext *ctx)
{
    SetupNativeScript(ctx, IsDoorAnimationStopped);
    return TRUE;
}

bool8 ScrCmd_setdooropen(struct ScriptContext *ctx)
{
    u16 x = VarGet(ScriptReadHalfword(ctx));
    u16 y = VarGet(ScriptReadHalfword(ctx));

    x += MAP_OFFSET;
    y += MAP_OFFSET;
    FieldSetDoorOpened(x, y);
    return FALSE;
}

bool8 ScrCmd_setdoorclosed(struct ScriptContext *ctx)
{
    u16 x = VarGet(ScriptReadHalfword(ctx));
    u16 y = VarGet(ScriptReadHalfword(ctx));

    x += MAP_OFFSET;
    y += MAP_OFFSET;
    FieldSetDoorClosed(x, y);
    return FALSE;
}

bool8 ScrCmd_dogroundeffect(struct ScriptContext *ctx)
{
    u8 localId = ScriptReadByte(ctx);
    u8 animId = ScriptReadByte(ctx);
    
    DoGroundEffect(localId, gSaveBlock1Ptr->location.mapNum, gSaveBlock1Ptr->location.mapGroup, animId);
    return FALSE;
}

bool8 ScrCmd_checkcoins(struct ScriptContext *ctx)
{
    u16 *ptr = GetVarPointer(ScriptReadHalfword(ctx));
    *ptr = GetCoins();
    return FALSE;
}

bool8 ScrCmd_addcoins(struct ScriptContext *ctx)
{
    u16 coins = VarGet(ScriptReadHalfword(ctx));

    if (AddCoins(coins) == TRUE)
        gSpecialVar_Result = FALSE;
    else
        gSpecialVar_Result = TRUE;
    return FALSE;
}

bool8 ScrCmd_removecoins(struct ScriptContext *ctx)
{
    u16 coins = VarGet(ScriptReadHalfword(ctx));

    if (RemoveCoins(coins) == TRUE)
        gSpecialVar_Result = FALSE;
    else
        gSpecialVar_Result = TRUE;
    return FALSE;
}

bool8 ScrCmd_moverotatingtileobjects(struct ScriptContext *ctx)
{
    u16 puzzleNumber = VarGet(ScriptReadHalfword(ctx));

    sMovingNpcId = MoveRotatingTileObjects(puzzleNumber);
    return FALSE;
}

bool8 ScrCmd_turnrotatingtileobjects(struct ScriptContext *ctx)
{
    TurnRotatingTileObjects();
    return FALSE;
}

bool8 ScrCmd_initrotatingtilepuzzle(struct ScriptContext *ctx)
{
    u16 isTrickHouse = VarGet(ScriptReadHalfword(ctx));

    InitRotatingTilePuzzle(isTrickHouse);
    return FALSE;
}

bool8 ScrCmd_freerotatingtilepuzzle(struct ScriptContext *ctx)
{
    FreeRotatingTilePuzzle();
    return FALSE;
}

bool8 ScrCmd_selectapproachingtrainer(struct ScriptContext *ctx)
{
    gSelectedObjectEvent = GetCurrentApproachingTrainerObjectEventId();
    return FALSE;
}

bool8 ScrCmd_selectobject(struct ScriptContext *ctx)
{
    u8 localId = ScriptReadByte(ctx);
    
    gSelectedObjectEvent = GetObjectEventIdByLocalIdAndMap(localId, gSaveBlock1Ptr->location.mapGroup, gSaveBlock1Ptr->location.mapNum);
    return FALSE;
}

bool8 ScrCmd_lockfortrainer(struct ScriptContext *ctx)
{
    if (IsOverworldLinkActive())
    {
        return FALSE;
    }
    else
    {
        if (gObjectEvents[gSelectedObjectEvent].active)
        {
            FreezeForApproachingTrainers();
            SetupNativeScript(ctx, IsFreezeObjectAndPlayerFinished);
        }
        return TRUE;
    }
}

// This command will set a Pokémon's eventLegal bit; there is no similar command to clear it.
bool8 ScrCmd_setmoneventlegal(struct ScriptContext *ctx)
{
    bool8 isEventLegal = TRUE;
    u16 partyIndex = VarGet(ScriptReadHalfword(ctx));

    SetMonData(&gPlayerParty[partyIndex], MON_DATA_EVENT_LEGAL, &isEventLegal);
    return FALSE;
}

bool8 ScrCmd_checkmoneventlegal(struct ScriptContext *ctx)
{
    u16 partyIndex = VarGet(ScriptReadHalfword(ctx));

    gSpecialVar_Result = GetMonData(&gPlayerParty[partyIndex], MON_DATA_EVENT_LEGAL, NULL);
    return FALSE;
}

// bool8 ScrCmd_trywondercardscript(struct ScriptContext *ctx)
// {
//     const u8 *script = GetSavedRamScriptIfValid();

//     if (script)
//     {
//         gRamScriptPtr = ctx->scriptPtr;
//         ScriptJump(ctx, script);
//     }
//     return FALSE;
// }

bool8 ScrCmd_callram(struct ScriptContext *ctx)
{
    if (gRamScriptPtr != NULL)
    {
        ScriptCall(ctx, gRamScriptPtr);
    }
    return FALSE;
}
/*
// This warp is only used by the Union Room.
// For the warp used by the Aqua Hideout, see DoTeleportTileWarp
bool8 ScrCmd_warpspinenter(struct ScriptContext *ctx)
{
    u8 mapGroup = ScriptReadByte(ctx);
    u8 mapNum = ScriptReadByte(ctx);
    u8 warpId = ScriptReadByte(ctx);
    u16 x = VarGet(ScriptReadHalfword(ctx));
    u16 y = VarGet(ScriptReadHalfword(ctx));

    SetWarpDestination(mapGroup, mapNum, warpId, x, y);
    SetSpinStartFacingDir(GetPlayerFacingDirection());
    DoSpinEnterWarp();
    ResetInitialPlayerAvatarState();
    return TRUE;
} */

bool8 ScrCmd_setmonmetlocation(struct ScriptContext *ctx)
{
    u16 partyIndex = VarGet(ScriptReadHalfword(ctx));
    u8 location = ScriptReadByte(ctx);

    if (partyIndex < PARTY_SIZE)
        SetMonData(&gPlayerParty[partyIndex], MON_DATA_MET_LOCATION, &location);
    return FALSE;
}

static void CloseBrailleWindow(void)
{
    ClearStdWindowAndFrame(sBrailleWindowId, TRUE);
    RemoveWindow(sBrailleWindowId);
}

bool8 ScrCmd_buffertrainerclassname(struct ScriptContext *ctx)
{
    u8 stringVarIndex = ScriptReadByte(ctx);
    u16 trainerClassId = VarGet(ScriptReadHalfword(ctx));

    StringCopy(sScriptStringVars[stringVarIndex], GetTrainerClassNameFromId(trainerClassId));
    return FALSE;
}

bool8 ScrCmd_buffertrainername(struct ScriptContext *ctx)
{
    u8 stringVarIndex = ScriptReadByte(ctx);
    u16 trainerClassId = VarGet(ScriptReadHalfword(ctx));

    StringCopy(sScriptStringVars[stringVarIndex], GetTrainerNameFromId(trainerClassId));
    return FALSE;
}

void SetMovingNpcId(u16 npcId)
{
    sMovingNpcId = npcId;
}
/*
bool8 ScrCmd_warpwhitefade(struct ScriptContext *ctx)
{
    u8 mapGroup = ScriptReadByte(ctx);
    u8 mapNum = ScriptReadByte(ctx);
    u8 warpId = ScriptReadByte(ctx);
    u16 x = VarGet(ScriptReadHalfword(ctx));
    u16 y = VarGet(ScriptReadHalfword(ctx));

    SetWarpDestination(mapGroup, mapNum, warpId, x, y);
    DoWhiteFadeWarp();
    ResetInitialPlayerAvatarState();
    return TRUE;
}*/

const static u8 ErrStr_selectpointer[] = _("selectpointer checks failed!{PAUSE 50}");
bool8 ScrCmd_selectpointer(struct ScriptContext *ctx)
{
    const u8 **ptr = (const u8 **)ScriptReadWord(ctx);
    u16 index = VarGet(ScriptReadHalfword(ctx));
    u8 overmethod = ScriptReadByte(ctx);
    u16 max;
    
    if (ptr == NULL)
    {
        ptr = (const u8 **)&ctx->data[0];
        max = 4;
    }
    else
    {
        for (max = 0; max < 64; max++)
        {
            if (ptr[max] == NULL) break;
        }
    }
    switch (overmethod)
    {
        default:
        case 0: //Error if past max
            break;
        case 1: //wrap if past max
            index = index % max;
            break;
        case 2: //clamp if past max
            index = min(index, max-1);
            break;
    }
    // Only load this pointer if it's within the array and pointing to someplace in ROM
    if (index >= max) return ShowScriptError(ctx, 1, ErrStr_selectpointer);
    if (ptr[index] <= (const u8*)&Start) return ShowScriptError(ctx, 2, ErrStr_selectpointer);
    
    if (index < max && ptr[index] > (const u8*)&Start) 
    {
        ctx->data[0] = (u32)ptr[index];
        ctx->data[1] = 0;
        ctx->data[2] = 0;
        ctx->data[3] = 0;
    }
    else
    {
        ctx->data[0] = (u32)&gText_ScriptError;
        // Debugging variables:
        ctx->data[1] = index;
        ctx->data[2] = max;
        ctx->data[3] = (u32)ptr;
        return ShowScriptError(ctx, 10, ErrStr_selectpointer);
    }
    return FALSE;
}

bool8 ScrCmd_selectwarpdestination(struct ScriptContext *ctx)
{
    const u16 *ptr = (const u16 *)ScriptReadWord(ctx);
    u16 index = VarGet(ScriptReadHalfword(ctx));
    u16 max;
    
    if (ptr == NULL) goto errorHandle;
    // Only load this pointer if it's within the array and pointing to someplace in ROM
    if (ptr <= (const u16*)&Start) goto errorHandle;
    
    for (max = 0; max < 256; max++)
    {
        if (ptr[max] == 0xFFFF) break;
    }
    if (index >= max) goto errorHandle;
    
    {
        u8 mapGroup = ptr[index] >> 8;
        u8 mapNum = ptr[index] & 0xFF;
        SetDynamicWarpWithCoords(0, mapGroup, mapNum, 0, -1, -1);
    }
    
    ctx->data[0] = 0;
    ctx->data[1] = 0;
    ctx->data[2] = 0;
    ctx->data[3] = 0;
    return FALSE;
    
errorHandle:
    SetDynamicWarpWithCoords(0, 0, 0, 0, -1, -1);
    ctx->data[0] = 0;
    // Debugging variables:
    ctx->data[1] = index;
    ctx->data[2] = max;
    ctx->data[3] = (u32)ptr;
    return FALSE;
}

bool8 ScrCmd_buffernumberstring2(struct ScriptContext *ctx)
{
    u8 stringVarIndex = ScriptReadByte(ctx);
    u16 v1 = VarGet(ScriptReadHalfword(ctx));
    u8 v2 = CountDigits(v1);
    u8 article = ScriptReadByte(ctx);
    
    if (v1 == 1) {
        if (article == 1) {
            StringCopy(sScriptStringVars[stringVarIndex], gText_The);
            return FALSE;
        } else if (article == 2) {
            //TODO "a/an"?
        }
    }

    ConvertIntToNameStringN(sScriptStringVars[stringVarIndex], v1, 0, v2);
    return FALSE;
}

//-----------------------------------------------------------------------------

#include "constants/script_cmds.h"

__attribute__((section("script_data")))
const SrcCmd gScriptCmdTable[NUM_SCRCMDS] = {
	[SCRCMD_NOP]                      = ScrCmd_nop,
	[SCRCMD_END]                      = ScrCmd_end,
	[SCRCMD_RETURN]                   = ScrCmd_return,
	[SCRCMD_GOTO]                     = ScrCmd_goto,
	[SCRCMD_CALL]                     = ScrCmd_call,
	[SCRCMD_GOTO_IF]                  = ScrCmd_goto_if,
	[SCRCMD_CALL_IF]                  = ScrCmd_call_if,
	[SCRCMD_CALLNATIVE]               = ScrCmd_callnative,
	[SCRCMD_WAITNATIVE]               = ScrCmd_waitnative,
	[SCRCMD_WAITSTATE]                = ScrCmd_waitstate,
	[SCRCMD_DELAY]                    = ScrCmd_delay,
	[SCRCMD_LOADWORD]                 = ScrCmd_loadword,
	[SCRCMD_LOADHALF]                 = ScrCmd_loadhalf,
	[SCRCMD_LOADBYTE]                 = ScrCmd_loadbyte,
	[SCRCMD_LOADARG]                  = ScrCmd_loadarg,
	[SCRCMD_COPYLOCAL]                = ScrCmd_copylocal,
	[SCRCMD_CMP_LOC2LOC]              = ScrCmd_compare_local_to_local,
	[SCRCMD_CMP_LOC2VAL]              = ScrCmd_compare_local_to_value,
	[SCRCMD_CMP_LOC2PTR]              = ScrCmd_compare_local_to_ptr,
	[SCRCMD_CMP_PTR2LOC]              = ScrCmd_compare_ptr_to_local,
	[SCRCMD_CMP_PTR2VAL]              = ScrCmd_compare_ptr_to_value,
	[SCRCMD_CMP_PTR2PTR]              = ScrCmd_compare_ptr_to_ptr,
	[SCRCMD_CMP_VAR2VAL]              = ScrCmd_compare_var_to_value,
	[SCRCMD_CMP_VAR2VAR]              = ScrCmd_compare_var_to_var,
	[SCRCMD_SETVAR]                   = ScrCmd_setvar,
	[SCRCMD_ADDVAR]                   = ScrCmd_addvar,
	[SCRCMD_SUBVAR]                   = ScrCmd_subvar,
	[SCRCMD_COPYVAR]                  = ScrCmd_copyvar,
	[SCRCMD_SET_COPYVAR]              = ScrCmd_setorcopyvar,
	[SCRCMD_MULVAR]                   = ScrCmd_mulvar,
	[SCRCMD_SETFLAG]                  = ScrCmd_setflag,
	[SCRCMD_CLEARFLAG]                = ScrCmd_clearflag,
	[SCRCMD_CHECKFLAG]                = ScrCmd_checkflag,
	[SCRCMD_LOCK]                     = ScrCmd_lock,
	[SCRCMD_RELEASE]                  = ScrCmd_release,
	[SCRCMD_LOCKALL]                  = ScrCmd_lockall,
	[SCRCMD_RELEASEALL]               = ScrCmd_releaseall,
	[SCRCMD_LOCKFORTRAINER]           = ScrCmd_lockfortrainer,
	[SCRCMD_SETWARP]                  = ScrCmd_setwarp,
	[SCRCMD_DOWARP]                   = ScrCmd_dowarp,
	[SCRCMD_RANDOM]                   = ScrCmd_random,
	[SCRCMD_FACEPLAYER]               = ScrCmd_faceplayer,
	[SCRCMD_TURNOBJECT]               = ScrCmd_turnobject,
	[SCRCMD_CREATEVOBJECT]            = ScrCmd_createvobject,
	[SCRCMD_TURNVOBJECT]              = ScrCmd_turnvobject,
	[SCRCMD_SETMAPLAYOUT]             = ScrCmd_setmaplayout,
	[SCRCMD_SWITCHMAPLAYOUT]          = ScrCmd_switchmaplayout, // Should be separate table?
	[SCRCMD_CALLRAM]                  = ScrCmd_callram,
	
	[SCRCMD_ADDOBJECT]                = ScrCmd_addobject,
	[SCRCMD_ADDOBJECT_AT]             = ScrCmd_addobjectat,
	[SCRCMD_REMOVEOBJECT]             = ScrCmd_removeobject,
	[SCRCMD_REMOVEOBJECT_AT]          = ScrCmd_removeobjectat,
	[SCRCMD_APPLYMOVEMENT]            = ScrCmd_applymovement,
	[SCRCMD_APPLYMOVEMENT_AT]         = ScrCmd_applymovementat,
	[SCRCMD_WAITMOVEMENT]             = ScrCmd_waitmovement,
	[SCRCMD_WAITMOVEMENT_AT]          = ScrCmd_waitmovementat,
	[SCRCMD_SHOWOBJECT_AT]            = ScrCmd_showobjectat,
	[SCRCMD_HIDEOBJECT_AT]            = ScrCmd_hideobjectat,
	[SCRCMD_SETOBJECTXY]              = ScrCmd_setobjectxy,
	[SCRCMD_SETOBJECTXYPERM]          = ScrCmd_setobjectxyperm,
	[SCRCMD_COPYOBJECTXYTOPERM]       = ScrCmd_copyobjectxytoperm,
	[SCRCMD_SETOBJECTMOVEMENTTYPE]    = ScrCmd_setobjectmovementtype,
	[SCRCMD_SETOBJECTSUBPRIORITY]     = ScrCmd_setobjectsubpriority,
	[SCRCMD_RESETOBJECTSUBPRIORITY]   = ScrCmd_resetobjectsubpriority,
	[SCRCMD_PLAYSE]                   = ScrCmd_playse,
	[SCRCMD_WAITSE]                   = ScrCmd_waitse,
	[SCRCMD_PLAYFANFARE]              = ScrCmd_playfanfare,
	[SCRCMD_WAITFANFARE]              = ScrCmd_waitfanfare,
	[SCRCMD_PLAYBGM]                  = ScrCmd_playbgm,
	[SCRCMD_SAVEBGM]                  = ScrCmd_savebgm,
	[SCRCMD_FADEDEFAULTBGM]           = ScrCmd_fadedefaultbgm,
	[SCRCMD_FADENEWBGM]               = ScrCmd_fadenewbgm,
	[SCRCMD_FADEOUTBGM]               = ScrCmd_fadeoutbgm,
	[SCRCMD_FADEINBGM]                = ScrCmd_fadeinbgm,
	[SCRCMD_OPENDOOR]                 = ScrCmd_opendoor,
	[SCRCMD_CLOSEDOOR]                = ScrCmd_closedoor,
	[SCRCMD_WAITDOORANIM]             = ScrCmd_waitdooranim,
	[SCRCMD_SETDOOROPEN]              = ScrCmd_setdooropen,
	[SCRCMD_SETDOORCLOSED]            = ScrCmd_setdoorclosed,
	[SCRCMD_SETSTEPCALLBACK]          = ScrCmd_setstepcallback,
	[SCRCMD_SETNPCTRIGGERCALLBACK]    = ScrCmd_setnpctriggercallback,
	[SCRCMD_MESSAGE]                  = ScrCmd_message,
	[SCRCMD_WAITMESSAGE]              = ScrCmd_waitmessage,
	[SCRCMD_CLOSEMESSAGE]             = ScrCmd_closemessage,
	[SCRCMD_MESSAGE_AUTOSCROLL]       = ScrCmd_messageautoscroll,
	[SCRCMD_MESSAGE_INSTANT]          = ScrCmd_messageinstant,
	[SCRCMD_MESSAGE_WORDWRAP]         = ScrCmd_messagewordwrap,
	[SCRCMD_WAITBUTTONPRESS]          = ScrCmd_waitbuttonpress,
	[SCRCMD_YESNOBOX]                 = ScrCmd_yesnobox,
	[SCRCMD_LOADDYNAMICSTRING]        = ScrCmd_loaddynamicstring,
	[SCRCMD_MULTICHOICE]              = ScrCmd_multichoice,
	[SCRCMD_MULTICHOICE_DEFAULT]      = ScrCmd_multichoicedefault,
	[SCRCMD_MULTICHOICE_GRID]         = ScrCmd_multichoicegrid,
	[SCRCMD_BRAILLE_MESSAGE]          = ScrCmd_braillemessage,
	[SCRCMD_BRAILLE_CLOSEMESSAGE]     = ScrCmd_closebraillemessage,
	[SCRCMD_POKENAVCALL]              = ScrCmd_pokenavcall,
	[SCRCMD_GETTIME]                  = ScrCmd_gettime,
	[SCRCMD_ADDITEM]                  = ScrCmd_additem,
	[SCRCMD_REMOVEITEM]               = ScrCmd_removeitem,
	[SCRCMD_RESOLVEITEM]              = ScrCmd_resolveitem,
	[SCRCMD_CHECKITEM]                = ScrCmd_checkitem,
	[SCRCMD_CHECKITEMSPACE]           = ScrCmd_checkitemspace,
	[SCRCMD_CHECKITEMTYPE]            = ScrCmd_checkitemtype,
	[SCRCMD_CHECKNUMITEM]             = ScrCmd_checknumitem,
	[SCRCMD_ADDDECOR]                 = ScrCmd_adddecoration,
	[SCRCMD_REMOVEDECOR]              = ScrCmd_removedecoration,
	[SCRCMD_CHECKDECOR]               = ScrCmd_checkdecor,
	[SCRCMD_CHECKDECORSPACE]          = ScrCmd_checkdecorspace,
	[SCRCMD_ADDPCITEM]                = ScrCmd_addpcitem,
	[SCRCMD_GETPLAYERXY]              = ScrCmd_getplayerxy,
	[SCRCMD_CHECKPLAYERGENDER]        = ScrCmd_checkplayergender,
	[SCRCMD_GETPARTYSIZE]             = ScrCmd_getpartysize,
	[SCRCMD_CHECKPARTYMOVE]           = ScrCmd_checkpartymove,
	[SCRCMD_GIVEMON]                  = ScrCmd_givemon,
	[SCRCMD_GIVEEGG]                  = ScrCmd_giveegg,
	[SCRCMD_PLAYMONCRY]               = ScrCmd_playmoncry,
	[SCRCMD_WAITMONCRY]               = ScrCmd_waitmoncry,
	[SCRCMD_SETMONMOVE]               = ScrCmd_setmonmove,
	[SCRCMD_SETMONEVENTLEGAL]         = ScrCmd_setmoneventlegal,
	[SCRCMD_CHECKMONEVENTLEGAL]       = ScrCmd_checkmoneventlegal,
	[SCRCMD_SETMONMETLOCATION]        = ScrCmd_setmonmetlocation,
	[SCRCMD_SHOWMONPIC]               = ScrCmd_showmonpic,
	[SCRCMD_HIDEMONPIC]               = ScrCmd_hidemonpic,
	[SCRCMD_ADDMONEY]                 = ScrCmd_addmoney,
	[SCRCMD_REMOVEMONEY]              = ScrCmd_removemoney,
	[SCRCMD_CHECKMONEY]               = ScrCmd_checkmoney,
	[SCRCMD_SHOWMONEYBOX]             = ScrCmd_showmoneybox,
	[SCRCMD_HIDEMONEYBOX]             = ScrCmd_hidemoneybox,
	[SCRCMD_UPDATEMONEYBOX]           = ScrCmd_updatemoneybox,
	
	[SCRCMD_BUFFERSTRING]             = ScrCmd_bufferstring,
	[SCRCMD_BUFFERNUMBERSTRING]       = ScrCmd_buffernumberstring,
	[SCRCMD_BUFFERNUMBERSTRING2]      = ScrCmd_buffernumberstring2,
	[SCRCMD_BUFFERSTDSTRING]          = ScrCmd_bufferstdstring,
	[SCRCMD_BUFFERLEADMONSPECIESNAME] = ScrCmd_bufferleadmonspeciesname,
	[SCRCMD_BUFFERPARTYMONNICK]       = ScrCmd_bufferpartymonnick,
	[SCRCMD_BUFFERMOVENAME]           = ScrCmd_buffermovename,
	[SCRCMD_BUFFERITEMNAME]           = ScrCmd_bufferitemname,
	[SCRCMD_BUFFERITEMNAMEPLURAL]     = ScrCmd_bufferitemnameplural,
	[SCRCMD_BUFFERDECORATIONNAME]     = ScrCmd_bufferdecorationname,
	[SCRCMD_BUFFERBOXNAME]            = ScrCmd_bufferboxname,
	[SCRCMD_BUFFERSELECTEDSTRING]     = ScrCmd_bufferselectedstring,
	[SCRCMD_BUFFERTRAINERCLASSNAME]   = ScrCmd_buffertrainerclassname,
	[SCRCMD_BUFFERTRAINERNAME]        = ScrCmd_buffertrainername,
	[SCRCMD_BUFFERCONTESTNAME]        = ScrCmd_buffercontestname,
	[SCRCMD_BUFFERSPECIESNAME]        = ScrCmd_bufferspeciesname,
	
	[SCRCMD_TRAINERBATTLE]            = ScrCmd_trainerbattle,
	[SCRCMD_DOTRAINERBATTLE]          = ScrCmd_dotrainerbattle,
	[SCRCMD_GOTOPOSTBATTLESCRIPT]     = ScrCmd_gotopostbattlescript,
	[SCRCMD_GOTOBEATENSCRIPT]         = ScrCmd_gotobeatenscript,
	[SCRCMD_CHECKTRAINERFLAG]         = ScrCmd_checktrainerflag,
	[SCRCMD_SETTRAINERFLAG]           = ScrCmd_settrainerflag,
	[SCRCMD_CLEARTRAINERFLAG]         = ScrCmd_cleartrainerflag,
	[SCRCMD_CHECKCOINS]               = ScrCmd_checkcoins,
	[SCRCMD_ADDCOINS]                 = ScrCmd_addcoins,
	[SCRCMD_REMOVECOINS]              = ScrCmd_removecoins,
	[SCRCMD_SHOWCOINSBOX]             = ScrCmd_showcoinsbox,
	[SCRCMD_HIDECOINSBOX]             = ScrCmd_hidecoinsbox,
	[SCRCMD_UPDATECOINSBOX]           = ScrCmd_updatecoinsbox,
	[SCRCMD_INCREMENTGAMESTAT]        = ScrCmd_incrementgamestat,
	[SCRCMD_SELECTPOINTER]            = ScrCmd_selectpointer,
	[SCRCMD_SELECTWARPDESTINATION]    = ScrCmd_selectwarpdestination,
	
	[SCRCMD_FADESCREEN]               = ScrCmd_fadescreen,
	[SCRCMD_FADESCREENSPEED]          = ScrCmd_fadescreenspeed,
	[SCRCMD_FADESCREENSWAPBUFFERS]    = ScrCmd_fadescreenswapbuffers,
	[SCRCMD_SETFLASHLEVEL]            = ScrCmd_setflashlevel,
	[SCRCMD_ANIMATEFLASH]             = ScrCmd_animateflash,
	[SCRCMD_POKEMART]                 = ScrCmd_pokemart,
	[SCRCMD_POKEMARTDECORATION]       = ScrCmd_pokemartdecoration,
	[SCRCMD_POKEMARTDECORATION2]      = ScrCmd_pokemartdecoration2,
	[SCRCMD_SETBERRYTREE]             = ScrCmd_setberrytree,
	
	[SCRCMD_DOFIELDEFFECT]            = ScrCmd_dofieldeffect,
	[SCRCMD_SETFIELDEFFECTARGUMENT]   = ScrCmd_setfieldeffectargument,
	[SCRCMD_SETFIELDEFFECTARGSTOOBJECTLOC] = ScrCmd_setfieldeffectargstoobjectloc,
	[SCRCMD_WAITFIELDEFFECT]          = ScrCmd_waitfieldeffect,
	[SCRCMD_DOGROUNDEFFECT]           = ScrCmd_dogroundeffect,
	[SCRCMD_SETRESPAWN]               = ScrCmd_setrespawn,
	[SCRCMD_SETMETATILE]              = ScrCmd_setmetatile,
	[SCRCMD_RESETWEATHER]             = ScrCmd_resetweather,
	[SCRCMD_SETWEATHER]               = ScrCmd_setweather,
	[SCRCMD_DOWEATHER]                = ScrCmd_doweather,
	[SCRCMD_SETWILDBATTLE]            = ScrCmd_setwildbattle,
	[SCRCMD_DOWILDBATTLE]             = ScrCmd_dowildbattle,
	[SCRCMD_SETMETATILEEX]            = ScrCmd_setmetatileex,
	
    [SCRCMD_SETSPEAKERNAM]            = ScrCmd_setspeaker,
	
	// TO BE REMOVED
	[SCRCMD_MOVEROTATINGTILEOBJECTS]   = ScrCmd_moverotatingtileobjects,
	[SCRCMD_TURNROTATINGTILEOBJECTS]   = ScrCmd_turnrotatingtileobjects,
	[SCRCMD_INITROTATINGTILEPUZZLE]    = ScrCmd_initrotatingtilepuzzle,
	[SCRCMD_FREEROTATINGTILEPUZZLE]    = ScrCmd_freerotatingtilepuzzle,
	[SCRCMD_SPECIAL]                   = ScrCmd_special,
	[SCRCMD_SPECIALVAR]                = ScrCmd_specialvar,
	[SCRCMD_CALLSTD]                   = ScrCmd_callstd,
	[SCRCMD_CALLSTD_IF]                = ScrCmd_callstd_if,
	[SCRCMD_SHOWCONTESTPAINTING]       = ScrCmd_showcontestpainting,
	[SCRCMD_PLAYSLOTMACHINE]           = ScrCmd_playslotmachine,
	[SCRCMD_CHOOSECONTESTMON]          = ScrCmd_choosecontestmon,
	[SCRCMD_STARTCONTEST]              = ScrCmd_startcontest,
	[SCRCMD_SHOWCONTESTRESULTS]        = ScrCmd_showcontestresults,
	[SCRCMD_CONTESTLINKTRANSFER]       = ScrCmd_contestlinktransfer,
	[SCRCMD_GETPOKENEWSACTIVE]         = ScrCmd_getpokenewsactive,
	[SCRCMD_SELECTAPPROACHINGTRAINER]  = ScrCmd_selectapproachingtrainer,
	[SCRCMD_SELECTOBJECT]              = ScrCmd_selectobject,
	
	
	// TODO 
	// [0xB8] = ScrCmd_setvaddress,
	// [0xB9] = ScrCmd_vgoto,
	// [0xBA] = ScrCmd_vcall,
	// [0xBB] = ScrCmd_vgoto_if,
	// [0xBC] = ScrCmd_vcall_if,
	// [0xBD] = ScrCmd_vmessage,
	// [0xBE] = ScrCmd_vbuffermessage,
	// [0xBF] = ScrCmd_vbufferstring,
	
};
__attribute__((section("script_data")))
const SrcCmd gScriptCmdTableEnd[1] = {};




