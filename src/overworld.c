#include "global.h"
#include "overworld.h"
#include "battle_pyramid.h"
#include "battle_setup.h"
#include "berry.h"
#include "bg.h"
#include "cable_club.h"
#include "clock.h"
#include "event_data.h"
#include "field_camera.h"
#include "field_control_avatar.h"
#include "field_effect.h"
#include "event_object_movement.h"
#include "field_message_box.h"
#include "field_player_avatar.h"
#include "field_screen_effect.h"
#include "field_special_scene.h"
#include "field_specials.h"
#include "field_tasks.h"
#include "field_weather.h"
#include "fieldmap.h"
#include "fldeff.h"
#include "gpu_regs.h"
#include "heal_location.h"
#include "link.h"
#include "link_rfu.h"
#include "load_save.h"
#include "main.h"
#include "alloc.h"
#include "m4a.h"
#include "map_name_popup.h"
#include "match_call.h"
#include "menu.h"
#include "metatile_behavior.h"
#include "mirage_tower.h"
#include "money.h"
#include "new_game.h"
#include "palette.h"
#include "play_time.h"
#include "random.h"
#include "roamer.h"
#include "rotating_gate.h"
#include "safari_zone.h"
#include "save.h"
#include "save_location.h"
#include "script.h"
#include "script_pokemon_util_80F87D8.h"
#include "secret_base.h"
#include "sound.h"
#include "start_menu.h"
#include "task.h"
#include "tileset_anims.h"
#include "time_events.h"
#include "trainer_hill.h"
#include "trainer_pokemon_sprites.h"
#include "tv.h"
#include "scanline_effect.h"
#include "wild_encounter.h"
#include "frontier_util.h"
#include "constants/abilities.h"
#include "constants/layouts.h"
#include "constants/map_types.h"
#include "constants/maps.h"
#include "constants/region_map_sections.h"
#include "constants/songs.h"
#include "constants/species.h"
#include "constants/weather.h"

#define PLAYER_TRADING_STATE_IDLE 0x80
#define PLAYER_TRADING_STATE_BUSY 0x81
#define PLAYER_TRADING_STATE_UNK_2 0x82
#define PLAYER_TRADING_STATE_EXITING_ROOM 0x83

#define FACING_NONE 0
#define FACING_UP 1
#define FACING_DOWN 2
#define FACING_LEFT 3
#define FACING_RIGHT 4
#define FACING_FORCED_UP 7
#define FACING_FORCED_DOWN 8
#define FACING_FORCED_LEFT 9
#define FACING_FORCED_RIGHT 10

// event scripts
extern const u8 EventScript_WhiteOut[];
extern const u8 EventScript_ResetMrBriney[];
extern const u8 EventScript_DoLinkRoomExit[];
extern const u8 gEventScript_TradeRoom_TooBusyToNotice[];
extern const u8 gEventScript_TradeRoom_ReadTrainerCard_NoColor[];
extern const u8 gEventScript_TradeRoom_ReadTrainerCard_Normal[];
// extern const u8 EventScript_DoubleBattleColosseum_PlayerSpot0[];
// extern const u8 EventScript_DoubleBattleColosseum_PlayerSpot1[];
// extern const u8 EventScript_DoubleBattleColosseum_PlayerSpot2[];
// extern const u8 EventScript_DoubleBattleColosseum_PlayerSpot3[];
// extern const u8 EventScript_RecordCenter_Spot0[];
// extern const u8 EventScript_RecordCenter_Spot1[];
// extern const u8 EventScript_RecordCenter_Spot2[];
// extern const u8 EventScript_RecordCenter_Spot3[];
// extern const u8 EventScript_SingleBattleColosseum_PlayerSpot0[];
// extern const u8 EventScript_SingleBattleColosseum_PlayerSpot1[];
// extern const u8 EventScript_TradeCenter_Chair1[];
// extern const u8 EventScript_TradeCenter_Chair0[];
extern const u8 EventScript_ConfirmLeaveTradeRoom[];
extern const u8 EventScript_TerminateLink[];

extern const struct MapLayout *const gMapLayouts[];
extern const struct MapHeader *const *const gMapGroups[];
extern const struct MapHeader *const *const gMapGroups_End[];
extern const int gMaxFlashLevel;
extern const u16 gOverworldBackgroundLayerFlags[];

static void Overworld_ResetStateAfterWhiteOut(void);
static void c2_80567AC(void);
static void CB2_LoadMap2(void);
static void VBlankCB_Field(void);
static void SpriteCB_LinkPlayer(struct Sprite *sprite);
static void ChooseAmbientCrySpecies(void);
static void do_load_map_stuff_loop(u8 *state);
static bool32 map_loading_iteration_3(u8 *state);
static bool32 sub_8086638(u8 *state);
static bool32 load_map_stuff(u8 *state, u32);
static bool32 map_loading_iteration_2_link(u8 *state);
static void mli4_mapscripts_and_other(void);
static void InitOverworldGraphicsRegisters(void);
static u8 GetSpriteForLinkedPlayer(u8);
static u16 KeyInterCB_SendNothing(u32 a1);
static void sub_80867C8(void);
static void sub_80867D8(void);
static void sub_8086AE4(void);
static void sub_80869DC(void);
static void sub_8086B14(void);
static void SetCameraToTrackGuestPlayer(void);
static void sub_8086988(bool32 arg0);
static void sub_8086A80(void);
static void sub_8086A68(void);
static void sub_8086860(void);
static void SetCameraToTrackGuestPlayer_2(void);
static void CreateLinkPlayerSprites(void);
static void ClearAllPlayerKeys(void);
static void ResetAllTradingStates(void);
static void UpdateHeldKeyCode(u16);
static void UpdateAllLinkPlayers(u16*, s32);
static u8 FlipVerticalAndClearForced(u8 a1, u8 a2);
static u8 LinkPlayerDetectCollision(u8 selfEventObjId, u8 a2, s16 x, s16 y);
static void CreateLinkPlayerSprite(u8 linkPlayerId, u8 gameVersion);
static void GetLinkPlayerCoords(u8 linkPlayerId, u16 *x, u16 *y);
static u8 GetLinkPlayerFacingDirection(u8 linkPlayerId);
static u8 GetLinkPlayerElevation(u8 linkPlayerId);
static s32 sub_80878E4(u8 linkPlayerId);
static u8 GetLinkPlayerIdAt(s16 x, s16 y);
static void SetPlayerFacingDirection(u8 linkPlayerId, u8 a2);
static void ZeroEventObject(struct EventObject *eventObj);
static void SpawnLinkPlayerEventObject(u8 linkPlayerId, s16 x, s16 y, u8 a4);
static void InitLinkPlayerEventObjectPos(struct EventObject *eventObj, s16 x, s16 y);
static void sub_80877DC(u8 linkPlayerId, u8 a2);
static void sub_808780C(u8 linkPlayerId);
static u8 GetSpriteForLinkedPlayer(u8 linkPlayerId);
static void sub_8087584(void);
static u32 GetLinkSendQueueLength(void);
static void ZeroLinkPlayerEventObject(struct LinkPlayerEventObject *linkPlayerEventObj);
static const u8 *TryInteractWithPlayer(struct TradeRoomPlayer *a1);
static u16 GetDirectionForEventScript(const u8 *script);
static void sub_8087510(void);
static void InitLinkRoomStartMenuScript(void);
static void sub_8087530(const u8 *script);
static void CreateConfirmLeaveTradeRoomPrompt(void);
static void InitMenuBasedScript(const u8 *script);
static void LoadTradeRoomPlayer(s32 linkPlayerId, s32 a2, struct TradeRoomPlayer *a3);
static bool32 sub_8087340(struct TradeRoomPlayer *a1);
static bool32 sub_8087340_2(struct TradeRoomPlayer *a1);
static u8 *TryGetTileEventScript(struct TradeRoomPlayer *a1);
static bool32 PlayerIsAtSouthExit(struct TradeRoomPlayer *a1);
static const u8 *TryInteractWithPlayer(struct TradeRoomPlayer *a1);
static u16 KeyInterCB_DeferToRecvQueue(u32);
static u16 KeyInterCB_DeferToSendQueue(u32);
static void ResetPlayerHeldKeys(u16 *a1);
static u16 KeyInterCB_SelfIdle(u32 a1);
static u16 KeyInterCB_DeferToEventScript(u32 a1);
static u16 GetDirectionForDpadKey(u16 a1);
static void CB1_UpdateLinkState(void);
static void SetKeyInterceptCallback(u16 (*func)(u32));
static void SetFieldVBlankCallback(void);
static void FieldClearVBlankHBlankCallbacks(void);
static void sub_8085810(void);
static u8 GetAdjustedInitialTransitionFlags(struct InitialPlayerAvatarState *playerStruct, u16 a2, u8 a3);
static u8 GetAdjustedInitialDirection(struct InitialPlayerAvatarState *playerStruct, u8 a2, u16 a3, u8 a4);
static u16 GetCenterScreenMetatileBehavior(void);

// IWRAM bss vars
static void *sUnusedOverworldCallback;
static u8 sPlayerTradingStates[4];
// This callback is called with a player's key code. It then returns an
// adjusted key code, effectively intercepting the input before anything
// can process it.
static u16 (*sPlayerKeyInterceptCallback)(u32);
static bool8 sUnknown_03000E18;
static u8 sRfuKeepAliveTimer;
static u32 sUnusedVar;

// IWRAM common
u16 *gBGTilemapBuffers1;
u16 *gBGTilemapBuffers2;
u16 *gBGTilemapBuffers3;
u16 gHeldKeyCodeToSend;
void (*gFieldCallback)(void);
bool8 (*gFieldCallback2)(void);
u8 gLocalLinkPlayerId; // This is our player id in a multiplayer mode.
u8 gFieldLinkPlayerCount;

// EWRAM vars
EWRAM_DATA static u8 sUnknown_020322D8 = 0;
EWRAM_DATA struct WarpData gLastUsedWarp = {0};
EWRAM_DATA static struct WarpData sWarpDestination = {0};  // new warp position
EWRAM_DATA static struct WarpData gFixedDiveWarp = {0};
EWRAM_DATA static struct WarpData gFixedHoleWarp = {0};
EWRAM_DATA static u16 sLastMapSectionId = 0;
EWRAM_DATA static struct InitialPlayerAvatarState gInitialPlayerAvatarState = {0};
EWRAM_DATA static u16 sAmbientCrySpecies = 0;
EWRAM_DATA static bool8 sIsAmbientCryWaterMon = FALSE;
EWRAM_DATA struct LinkPlayerEventObject gLinkPlayerEventObjects[4] = {0};

// const rom data
static const struct WarpData sDummyWarpData =
{
    .mapGroup = -1,
    .mapNum = -1,
    .warpId = -1,
    .x = -1,
    .y = -1,
};

static const u8 sUnusedData[] =
{
    0xB0, 0x04, 0x00, 0x00,
    0x10, 0x0E, 0x00, 0x00,
    0xB0, 0x04, 0x00, 0x00,
    0x60, 0x09, 0x00, 0x00,
    0x32, 0x00, 0x00, 0x00,
    0x50, 0x00, 0x00, 0x00,
    0xD4, 0xFF, 0xFF, 0xFF,
    0x2C, 0x00, 0x00, 0x00,
};

const struct UCoords32 gDirectionToVectors[] =
{
    [DIR_NONE] =
    {
        .x =  0,
        .y =  0,
    },
    [DIR_SOUTH] =
    {
        .x =  0,
        .y =  1,
    },
    [DIR_NORTH] =
    {
        .x =  0,
        .y = -1,
    },
    [DIR_WEST] =
    {
        .x = -1,
        .y =  0,
    },
    [DIR_EAST] =
    {
        .x =  1,
        .y =  0,
    },
    [DIR_SOUTHWEST] =
    {
        .x = -1,
        .y =  1,
    },
    [DIR_SOUTHEAST] =
    {
        .x =  1,
        .y =  1,
    },
    [DIR_NORTHWEST] =
    {
        .x = -1,
        .y = -1,
    },
    [DIR_NORTHEAST] =
    {
        .x =  1,
        .y = -1,
    },
};

static const struct BgTemplate sOverworldBgTemplates[] =
{
    {
        .bg = 0,
        .charBaseIndex = 2,
        .mapBaseIndex = 31,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0
    },
    {
        .bg = 1,
        .charBaseIndex = 0,
        .mapBaseIndex = 29,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 1,
        .baseTile = 0
    },
    {
        .bg = 2,
        .charBaseIndex = 0,
        .mapBaseIndex = 28,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 2,
        .baseTile = 0
    },
    {
        .bg = 3,
        .charBaseIndex = 0,
        .mapBaseIndex = 30,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 3,
        .baseTile = 0
    }
};

static const struct ScanlineEffectParams sFlashEffectParams =
{
    (void *)REG_ADDR_WIN0H,
    ((DMA_ENABLE | DMA_START_HBLANK | DMA_REPEAT | DMA_DEST_RELOAD) << 16) | 1,
    1,
    0,
};

static u8 MovementEventModeCB_Normal(struct LinkPlayerEventObject *, struct EventObject *, u8);
static u8 MovementEventModeCB_Ignored(struct LinkPlayerEventObject *, struct EventObject *, u8);
static u8 MovementEventModeCB_Normal_2(struct LinkPlayerEventObject *, struct EventObject *, u8);

static u8 (*const gLinkPlayerMovementModes[])(struct LinkPlayerEventObject *, struct EventObject *, u8) =
{
    MovementEventModeCB_Normal, // MOVEMENT_MODE_FREE
    MovementEventModeCB_Ignored, // MOVEMENT_MODE_FROZEN
    MovementEventModeCB_Normal_2, // MOVEMENT_MODE_SCRIPTED
};

static u8 FacingHandler_DoNothing(struct LinkPlayerEventObject *, struct EventObject *, u8);
static u8 FacingHandler_DpadMovement(struct LinkPlayerEventObject *, struct EventObject *, u8);
static u8 FacingHandler_ForcedFacingChange(struct LinkPlayerEventObject *, struct EventObject *, u8);

// These handlers return TRUE if the movement was scripted and successful, and FALSE otherwise.
static bool8 (*const gLinkPlayerFacingHandlers[])(struct LinkPlayerEventObject *, struct EventObject *, u8) =
{
    FacingHandler_DoNothing,
    FacingHandler_DpadMovement,
    FacingHandler_DpadMovement,
    FacingHandler_DpadMovement,
    FacingHandler_DpadMovement,
    FacingHandler_DoNothing,
    FacingHandler_DoNothing,
    FacingHandler_ForcedFacingChange,
    FacingHandler_ForcedFacingChange,
    FacingHandler_ForcedFacingChange,
    FacingHandler_ForcedFacingChange,
};

static void MovementStatusHandler_EnterFreeMode(struct LinkPlayerEventObject *, struct EventObject *);
static void MovementStatusHandler_TryAdvanceScript(struct LinkPlayerEventObject *, struct EventObject *);

// These handlers are run after an attempted movement.
static void (*const gMovementStatusHandler[])(struct LinkPlayerEventObject *, struct EventObject *) =
{
    // FALSE:
    MovementStatusHandler_EnterFreeMode,
    // TRUE:
    MovementStatusHandler_TryAdvanceScript,
};

// code
void DoWhiteOut(void)
{
    ScriptContext2_RunNewScript(EventScript_WhiteOut);
    SetMoney(&gSaveBlock1Ptr->money, GetMoney(&gSaveBlock1Ptr->money) / 2);
    HealPlayerParty();
    Overworld_ResetStateAfterWhiteOut();
    SetWarpDestinationToLastHealLocation();
    WarpIntoMap();
}

void Overworld_ResetStateAfterFly(void)
{
    ResetInitialPlayerAvatarState();
    FlagClear(FLAG_SYS_CYCLING_ROAD);
    FlagClear(FLAG_SYS_CRUISE_MODE);
    FlagClear(FLAG_SYS_SAFARI_MODE);
    FlagClear(FLAG_SYS_USE_STRENGTH);
    FlagClear(FLAG_SYS_USE_FLASH);
}

void Overworld_ResetStateAfterTeleport(void)
{
    ResetInitialPlayerAvatarState();
    FlagClear(FLAG_SYS_CYCLING_ROAD);
    FlagClear(FLAG_SYS_CRUISE_MODE);
    FlagClear(FLAG_SYS_SAFARI_MODE);
    FlagClear(FLAG_SYS_USE_STRENGTH);
    FlagClear(FLAG_SYS_USE_FLASH);
    ScriptContext2_RunNewScript(EventScript_ResetMrBriney);
}

void Overworld_ResetStateAfterDigEscRope(void)
{
    ResetInitialPlayerAvatarState();
    FlagClear(FLAG_SYS_CYCLING_ROAD);
    FlagClear(FLAG_SYS_CRUISE_MODE);
    FlagClear(FLAG_SYS_SAFARI_MODE);
    FlagClear(FLAG_SYS_USE_STRENGTH);
    FlagClear(FLAG_SYS_USE_FLASH);
}

static void Overworld_ResetStateAfterWhiteOut(void)
{
    ResetInitialPlayerAvatarState();
    FlagClear(FLAG_SYS_CYCLING_ROAD);
    FlagClear(FLAG_SYS_CRUISE_MODE);
    FlagClear(FLAG_SYS_SAFARI_MODE);
    FlagClear(FLAG_SYS_USE_STRENGTH);
    FlagClear(FLAG_SYS_USE_FLASH);
    // If you were defeated by Kyogre/Groudon and the step counter has
    // maxed out, end the unusual weather.
    if (VarGet(VAR_SHOULD_END_UNUSUAL_WEATHER) == 1)
    {
        VarSet(VAR_SHOULD_END_UNUSUAL_WEATHER, 0);
        VarSet(VAR_UNUSUAL_WEATHER_LOCATION, UNUSUAL_WEATHER_NONE);
    }
}

static void sub_8084788(void)
{
    FlagClear(FLAG_SYS_SAFARI_MODE);
    ChooseAmbientCrySpecies();
    ResetCyclingRoadChallengeData();
    UpdateLocationHistoryForRoamer();
    RoamerMoveToOtherLocationSet();
}

void ResetGameStats(void)
{
    s32 i;

    for (i = 0; i < NUM_GAME_STATS; i++)
        SetGameStat(i, 0);
}

void IncrementGameStat(u8 index)
{
    if (index < NUM_USED_GAME_STATS)
    {
        u32 statVal = GetGameStat(index);
        if (statVal < 0xFFFFFF)
            statVal++;
        else
            statVal = 0xFFFFFF;

        SetGameStat(index, statVal);
    }
}

u32 GetGameStat(u8 index)
{
    if (index >= NUM_USED_GAME_STATS)
        return 0;

    return gSaveBlock1Ptr->gameStats[index] ^ gSaveBlock2Ptr->encryptionKey;
}

void SetGameStat(u8 index, u32 value)
{
    if (index < NUM_USED_GAME_STATS)
        gSaveBlock1Ptr->gameStats[index] = value ^ gSaveBlock2Ptr->encryptionKey;
}

void ApplyNewEncryptionKeyToGameStats(u32 newKey)
{
    u8 i;

    for (i = 0; i < NUM_GAME_STATS; i++)
        ApplyNewEncryptionKeyToWord(&gSaveBlock1Ptr->gameStats[i], newKey);
}

void LoadEventObjTemplatesFromHeader(void)
{
    // Clear map object templates
    CpuFill32(0, gSaveBlock1Ptr->eventObjectTemplates, sizeof(gSaveBlock1Ptr->eventObjectTemplates));

    // Copy map header events to save block
    CpuCopy32(gMapHeader.events->eventObjects,
              gSaveBlock1Ptr->eventObjectTemplates,
              gMapHeader.events->eventObjectCount * sizeof(struct EventObjectTemplate));
}

void LoadSaveblockEventObjScripts(void)
{
    struct EventObjectTemplate *mapHeaderObjTemplates = gMapHeader.events->eventObjects;
    struct EventObjectTemplate *savObjTemplates = gSaveBlock1Ptr->eventObjectTemplates;
    s32 i;

    for (i = 0; i < EVENT_OBJECT_TEMPLATES_COUNT; i++)
        savObjTemplates[i].script = mapHeaderObjTemplates[i].script;
}

void Overworld_SetEventObjTemplateCoords(u8 localId, s16 x, s16 y)
{
    s32 i;
    struct EventObjectTemplate *savObjTemplates = gSaveBlock1Ptr->eventObjectTemplates;

    for (i = 0; i < EVENT_OBJECT_TEMPLATES_COUNT; i++)
    {
        struct EventObjectTemplate *eventObjectTemplate = &savObjTemplates[i];
        if (eventObjectTemplate->localId == localId)
        {
            eventObjectTemplate->x = x;
            eventObjectTemplate->y = y;
            return;
        }
    }
}

void Overworld_SetEventObjTemplateMovementType(u8 localId, u8 movementType)
{
    s32 i;

    struct EventObjectTemplate *savObjTemplates = gSaveBlock1Ptr->eventObjectTemplates;
    for (i = 0; i < EVENT_OBJECT_TEMPLATES_COUNT; i++)
    {
        struct EventObjectTemplate *eventObjectTemplate = &savObjTemplates[i];
        if (eventObjectTemplate->localId == localId)
        {
            eventObjectTemplate->movementType = movementType;
            return;
        }
    }
}

static void mapdata_load_assets_to_gpu_and_full_redraw(void)
{
    move_tilemap_camera_to_upper_left_corner();
    copy_map_tileset1_tileset2_to_vram(gMapHeader.mapLayout);
    apply_map_tileset1_tileset2_palette(gMapHeader.mapLayout);
    DrawWholeMapView();
    InitTilesetAnimations();
}

const struct MapLayout *GetMapLayout(void)
{
    u16 mapLayoutId = gSaveBlock1Ptr->mapLayoutId;
    if (mapLayoutId)
        return gMapLayouts[mapLayoutId - 1];
    return NULL;
}

void ApplyCurrentWarp(void)
{
    gLastUsedWarp = gSaveBlock1Ptr->location;
    gSaveBlock1Ptr->location = sWarpDestination;
    gFixedDiveWarp = sDummyWarpData;
    gFixedHoleWarp = sDummyWarpData;
}

static void ClearDiveAndHoleWarps(void)
{
    gFixedDiveWarp = sDummyWarpData;
    gFixedHoleWarp = sDummyWarpData;
}

static void SetWarpData(struct WarpData *warp, s8 mapGroup, s8 mapNum, s8 warpId, s8 x, s8 y)
{
    warp->mapGroup = mapGroup;
    warp->mapNum = mapNum;
    warp->warpId = warpId;
    warp->x = x;
    warp->y = y;
}

static bool32 IsDummyWarp(struct WarpData *warp)
{
    if (warp->mapGroup != -1)
        return FALSE;
    else if (warp->mapNum != -1)
        return FALSE;
    else if (warp->warpId != -1)
        return FALSE;
    else if (warp->x != -1)
        return FALSE;
    else if (warp->y != -1)
        return FALSE;
    else
        return TRUE;
}

struct MapHeader const *const Overworld_GetMapHeaderByGroupAndId(u16 mapGroup, u16 mapNum)
{
    // Sanity checking
    if ((u32)&gMapGroups[mapGroup] > (u32)&gMapGroups_End) goto error;
    if ((u32)&gMapGroups[mapGroup][mapNum] > (u32)&gMapGroups) goto error;
    
    return gMapGroups[mapGroup][mapNum];
error:
    return gMapGroups[0][0];
}

struct MapHeader const *const GetDestinationWarpMapHeader(void)
{
    return Overworld_GetMapHeaderByGroupAndId(sWarpDestination.mapGroup, sWarpDestination.mapNum);
}

extern const struct Trainer *gCurrTrainerTable;

static void LoadCurrentMapData(void)
{
    sLastMapSectionId = gMapHeader.regionMapSectionId;
    gMapHeader = *Overworld_GetMapHeaderByGroupAndId(gSaveBlock1Ptr->location.mapGroup, gSaveBlock1Ptr->location.mapNum);
    gSaveBlock1Ptr->mapLayoutId = gMapHeader.mapLayoutId;
    gMapHeader.mapLayout = GetMapLayout();
    gCurrTrainerTable = gMapHeader.trainerTable;
}

static void LoadSaveblockMapHeader(void)
{
    gMapHeader = *Overworld_GetMapHeaderByGroupAndId(gSaveBlock1Ptr->location.mapGroup, gSaveBlock1Ptr->location.mapNum);
    gMapHeader.mapLayout = GetMapLayout();
    gCurrTrainerTable = gMapHeader.trainerTable;
}

static void SetPlayerCoordsFromWarp(void)
{
    if (gSaveBlock1Ptr->location.warpId >= 0 && gSaveBlock1Ptr->location.warpId < gMapHeader.events->warpCount)
    {
        gSaveBlock1Ptr->pos.x = gMapHeader.events->warps[gSaveBlock1Ptr->location.warpId].x;
        gSaveBlock1Ptr->pos.y = gMapHeader.events->warps[gSaveBlock1Ptr->location.warpId].y;
    }
    else if (gSaveBlock1Ptr->location.x >= 0 && gSaveBlock1Ptr->location.y >= 0)
    {
        gSaveBlock1Ptr->pos.x = gSaveBlock1Ptr->location.x;
        gSaveBlock1Ptr->pos.y = gSaveBlock1Ptr->location.y;
    }
    else
    {
        gSaveBlock1Ptr->pos.x = gMapHeader.mapLayout->width / 2;
        gSaveBlock1Ptr->pos.y = gMapHeader.mapLayout->height / 2;
    }
}

void WarpIntoMap(void)
{
    ApplyCurrentWarp();
    LoadCurrentMapData();
    SetPlayerCoordsFromWarp();
}

void SetWarpDestination(s8 mapGroup, s8 mapNum, s8 warpId, s8 x, s8 y)
{
    SetWarpData(&sWarpDestination, mapGroup, mapNum, warpId, x, y);
}

void SetWarpDestinationToMapWarp(s8 mapGroup, s8 mapNum, s8 warpId)
{
    SetWarpDestination(mapGroup, mapNum, warpId, -1, -1);
}

void SetDynamicWarp(s32 unused, s8 mapGroup, s8 mapNum, s8 warpId)
{
    SetWarpData(&gSaveBlock1Ptr->dynamicWarp, mapGroup, mapNum, warpId, gSaveBlock1Ptr->pos.x, gSaveBlock1Ptr->pos.y);
}

void SetDynamicWarpWithCoords(s32 unused, s8 mapGroup, s8 mapNum, s8 warpId, s8 x, s8 y)
{
    SetWarpData(&gSaveBlock1Ptr->dynamicWarp, mapGroup, mapNum, warpId, x, y);
}

void SetWarpDestinationToDynamicWarp(u8 unusedWarpId)
{
    sWarpDestination = gSaveBlock1Ptr->dynamicWarp;
}

void SetWarpDestinationToHealLocation(u8 healLocationId)
{
    const struct HealLocation *warp = GetHealLocation(healLocationId);
    if (warp)
        SetWarpDestination(warp->group, warp->map, -1, warp->x, warp->y);
}

void SetWarpDestinationToLastHealLocation(void)
{
    sWarpDestination = gSaveBlock1Ptr->lastHealLocation;
}

void SetLastHealLocationWarp(u8 healLocationId)
{
    const struct HealLocation *healLocation = GetHealLocation(healLocationId);
    if (healLocation)
        SetWarpData(&gSaveBlock1Ptr->lastHealLocation, healLocation->group, healLocation->map, -1, healLocation->x, healLocation->y);
}

void UpdateEscapeWarp(s16 x, s16 y)
{
    u8 currMapType = GetCurrentMapType();
    u8 destMapType = GetMapTypeByGroupAndId(sWarpDestination.mapGroup, sWarpDestination.mapNum);
    if (IsMapTypeOutdoors(currMapType) && IsMapTypeOutdoors(destMapType) != TRUE)
        SetEscapeWarp(gSaveBlock1Ptr->location.mapGroup, gSaveBlock1Ptr->location.mapNum, -1, x - 7, y - 6);
}

void SetEscapeWarp(s8 mapGroup, s8 mapNum, s8 warpId, s8 x, s8 y)
{
    SetWarpData(&gSaveBlock1Ptr->escapeWarp, mapGroup, mapNum, warpId, x, y);
}

void SetWarpDestinationToEscapeWarp(void)
{
    sWarpDestination = gSaveBlock1Ptr->escapeWarp;
}

void SetFixedDiveWarp(s8 mapGroup, s8 mapNum, s8 warpId, s8 x, s8 y)
{
    SetWarpData(&gFixedDiveWarp, mapGroup, mapNum, warpId, x, y);
}

static void SetWarpDestinationToDiveWarp(void)
{
    sWarpDestination = gFixedDiveWarp;
}

void SetFixedHoleWarp(s8 mapGroup, s8 mapNum, s8 warpId, s8 x, s8 y)
{
    SetWarpData(&gFixedHoleWarp, mapGroup, mapNum, warpId, x, y);
}

void SetWarpDestinationToFixedHoleWarp(s16 x, s16 y)
{
    if (IsDummyWarp(&gFixedHoleWarp) == TRUE)
        sWarpDestination = gLastUsedWarp;
    else
        SetWarpDestination(gFixedHoleWarp.mapGroup, gFixedHoleWarp.mapNum, -1, x, y);
}

static void SetWarpDestinationToContinueGameWarp(void)
{
    sWarpDestination = gSaveBlock1Ptr->continueGameWarp;
}

void SetContinueGameWarp(s8 mapGroup, s8 mapNum, s8 warpId, s8 x, s8 y)
{
    SetWarpData(&gSaveBlock1Ptr->continueGameWarp, mapGroup, mapNum, warpId, x, y);
}

void SetContinueGameWarpToHealLocation(u8 healLocationId)
{
    const struct HealLocation *warp = GetHealLocation(healLocationId);
    if (warp)
        SetWarpData(&gSaveBlock1Ptr->continueGameWarp, warp->group, warp->map, -1, warp->x, warp->y);
}

void SetContinueGameWarpToDynamicWarp(int unused)
{
    gSaveBlock1Ptr->continueGameWarp = gSaveBlock1Ptr->dynamicWarp;
}

const struct MapConnection *GetMapConnection(u8 dir)
{
    s32 i;
    s32 count = gMapHeader.connections->count;
    const struct MapConnection *connection = gMapHeader.connections->connections;

    if (connection == NULL)
        return NULL;

    for(i = 0; i < count; i++, connection++)
        if (connection->direction == dir)
            return connection;

    return NULL;
}

static bool8 SetDiveWarp(u8 dir, u16 x, u16 y)
{
    const struct MapConnection *connection = GetMapConnection(dir);

    if (connection != NULL)
    {
        SetWarpDestination(connection->mapGroup, connection->mapNum, -1, x, y);
    }
    else
    {
        RunOnDiveWarpMapScript();
        if (IsDummyWarp(&gFixedDiveWarp))
            return FALSE;
        SetWarpDestinationToDiveWarp();
    }
    return TRUE;
}

bool8 SetDiveWarpEmerge(u16 x, u16 y)
{
    return SetDiveWarp(CONNECTION_EMERGE, x, y);
}

bool8 SetDiveWarpDive(u16 x, u16 y)
{
    return SetDiveWarp(CONNECTION_DIVE, x, y);
}

void LoadMapFromCameraTransition(u8 mapGroup, u8 mapNum)
{
    s32 paletteIndex;

    SetWarpDestination(mapGroup, mapNum, -1, -1, -1);
    if (gMapHeader.regionMapSectionId != 0x3A)
        sub_8085810();

    ApplyCurrentWarp();
    LoadCurrentMapData();
    LoadEventObjTemplatesFromHeader();
    TrySetMapSaveWarpStatus();
    ClearTempFieldEventData();
    ResetCyclingRoadChallengeData();
    RestartWildEncounterImmunitySteps();
    TryUpdateRandomTrainerRematches(mapGroup, mapNum);
    DoTimeBasedEvents();
    SetSav1WeatherFromCurrMapHeader();
    ChooseAmbientCrySpecies();
    SetDefaultFlashLevel();
    Overworld_ClearSavedMusic();
    RunOnTransitionMapScript();
    InitMap();
    copy_map_tileset2_to_vram_2(gMapHeader.mapLayout);
    apply_map_tileset2_palette(gMapHeader.mapLayout);

    for (paletteIndex = 6; paletteIndex < 13; paletteIndex++)
        ApplyWeatherGammaShiftToPal(paletteIndex);

    InitSecondaryTilesetAnimation();
    UpdateLocationHistoryForRoamer();
    RoamerMove();
    DoCurrentWeather();
    ResetFieldTasksArgs();
    RunOnResumeMapScript();

    if (gMapHeader.regionMapSectionId != MAPSEC_BATTLE_FRONTIER || gMapHeader.regionMapSectionId != sLastMapSectionId)
        ShowMapNamePopup();
}

static void mli0_load_map(u32 a1)
{
    bool8 isOutdoors;
    bool8 isIndoors;

    LoadCurrentMapData();
    if (!(sUnknown_020322D8 & 1))
    {
        // if (gMapHeader.mapLayoutId == LAYOUT_BATTLE_FRONTIER_BATTLE_PYRAMID_EMPTY_SQUARE)
        //     LoadBattlePyramidEventObjectTemplates();
        // else if (InTrainerHill())
        //     sub_81D5DF8();
        // else
            LoadEventObjTemplatesFromHeader();
    }

    isOutdoors = IsMapTypeOutdoors(gMapHeader.mapType);
    isIndoors = IsMapTypeIndoors(gMapHeader.mapType);

    sub_80EB218();
    TrySetMapSaveWarpStatus();
    ClearTempFieldEventData();
    ResetCyclingRoadChallengeData();
    RestartWildEncounterImmunitySteps();
    TryUpdateRandomTrainerRematches(gSaveBlock1Ptr->location.mapGroup, gSaveBlock1Ptr->location.mapNum);
    if (a1 != 1)
        DoTimeBasedEvents();
    SetSav1WeatherFromCurrMapHeader();
    ChooseAmbientCrySpecies();
    if (isOutdoors)
        FlagClear(FLAG_SYS_USE_FLASH);
    SetDefaultFlashLevel();
    Overworld_ClearSavedMusic();
    RunOnTransitionMapScript();
    UpdateLocationHistoryForRoamer();
    RoamerMoveToOtherLocationSet();
    // if (gMapHeader.mapLayoutId == LAYOUT_BATTLE_FRONTIER_BATTLE_PYRAMID_EMPTY_SQUARE)
    //     InitBattlePyramidMap(FALSE);
    // else if (InTrainerHill())
    //     InitTrainerHillMap();
    // else
        InitMap();

    if (a1 != 1 && isIndoors)
    {
        UpdateTVScreensOnMap(gBackupMapLayout.width, gBackupMapLayout.height);
        InitSecretBaseAppearance(TRUE);
    }
}

void ResetInitialPlayerAvatarState(void)
{
    gInitialPlayerAvatarState.direction = DIR_SOUTH;
    gInitialPlayerAvatarState.transitionFlags = PLAYER_AVATAR_FLAG_ON_FOOT;
}

void StoreInitialPlayerAvatarState(void)
{
    gInitialPlayerAvatarState.direction = GetPlayerFacingDirection();

    if (TestPlayerAvatarFlags(PLAYER_AVATAR_FLAG_MACH_BIKE))
        gInitialPlayerAvatarState.transitionFlags = PLAYER_AVATAR_FLAG_MACH_BIKE;
    else if (TestPlayerAvatarFlags(PLAYER_AVATAR_FLAG_ACRO_BIKE))
        gInitialPlayerAvatarState.transitionFlags = PLAYER_AVATAR_FLAG_ACRO_BIKE;
    else if (TestPlayerAvatarFlags(PLAYER_AVATAR_FLAG_SURFING))
        gInitialPlayerAvatarState.transitionFlags = PLAYER_AVATAR_FLAG_SURFING;
    else if (TestPlayerAvatarFlags(PLAYER_AVATAR_FLAG_UNDERWATER))
        gInitialPlayerAvatarState.transitionFlags = PLAYER_AVATAR_FLAG_UNDERWATER;
    else
        gInitialPlayerAvatarState.transitionFlags = PLAYER_AVATAR_FLAG_ON_FOOT;
}

static struct InitialPlayerAvatarState *GetInitialPlayerAvatarState(void)
{
    struct InitialPlayerAvatarState playerStruct;
    u8 mapType = GetCurrentMapType();
    u16 metatileBehavior = GetCenterScreenMetatileBehavior();
    u8 transitionFlags = GetAdjustedInitialTransitionFlags(&gInitialPlayerAvatarState, metatileBehavior, mapType);
    playerStruct.transitionFlags = transitionFlags;
    playerStruct.direction = GetAdjustedInitialDirection(&gInitialPlayerAvatarState, transitionFlags, metatileBehavior, mapType);
    gInitialPlayerAvatarState = playerStruct;
    return &gInitialPlayerAvatarState;
}

static u8 GetAdjustedInitialTransitionFlags(struct InitialPlayerAvatarState *playerStruct, u16 metatileBehavior, u8 mapType)
{
    if (mapType != MAP_TYPE_INDOOR && FlagGet(FLAG_SYS_CRUISE_MODE))
        return PLAYER_AVATAR_FLAG_ON_FOOT;
    else if (mapType == MAP_TYPE_UNDERWATER)
        return PLAYER_AVATAR_FLAG_UNDERWATER;
    else if (MetatileBehavior_IsSurfableWaterOrUnderwater(metatileBehavior) == TRUE)
        return PLAYER_AVATAR_FLAG_SURFING;
    else if (Overworld_IsBikingAllowed() != TRUE)
        return PLAYER_AVATAR_FLAG_ON_FOOT;
    else if (playerStruct->transitionFlags == PLAYER_AVATAR_FLAG_MACH_BIKE)
        return PLAYER_AVATAR_FLAG_MACH_BIKE;
    else if (playerStruct->transitionFlags != PLAYER_AVATAR_FLAG_ACRO_BIKE)
        return PLAYER_AVATAR_FLAG_ON_FOOT;
    else
        return PLAYER_AVATAR_FLAG_ACRO_BIKE;
}

static u8 GetAdjustedInitialDirection(struct InitialPlayerAvatarState *playerStruct, u8 transitionFlags, u16 metatileBehavior, u8 mapType)
{
    if (FlagGet(FLAG_SYS_CRUISE_MODE) && mapType == MAP_TYPE_OCEAN_ROUTE)
        return DIR_EAST;
    else if (MetatileBehavior_IsDeepSouthWarp(metatileBehavior) == TRUE)
        return DIR_NORTH;
    else if (MetatileBehavior_IsNonAnimDoor(metatileBehavior) == TRUE || MetatileBehavior_IsDoor(metatileBehavior) == TRUE)
        return DIR_SOUTH;
    else if (MetatileBehavior_IsSouthArrowWarp(metatileBehavior) == TRUE)
        return DIR_NORTH;
    else if (MetatileBehavior_IsNorthArrowWarp(metatileBehavior) == TRUE)
        return DIR_SOUTH;
    else if (MetatileBehavior_IsWestArrowWarp(metatileBehavior) == TRUE)
        return DIR_EAST;
    else if (MetatileBehavior_IsEastArrowWarp(metatileBehavior) == TRUE)
        return DIR_WEST;
    else if ((playerStruct->transitionFlags == PLAYER_AVATAR_FLAG_UNDERWATER  && transitionFlags == PLAYER_AVATAR_FLAG_SURFING)
     || (playerStruct->transitionFlags == PLAYER_AVATAR_FLAG_SURFING && transitionFlags == PLAYER_AVATAR_FLAG_UNDERWATER ))
        return playerStruct->direction;
    else if (MetatileBehavior_IsLadder(metatileBehavior) == TRUE)
        return playerStruct->direction;
    else
        return DIR_SOUTH;
}

static u16 GetCenterScreenMetatileBehavior(void)
{
    return MapGridGetMetatileBehaviorAt(gSaveBlock1Ptr->pos.x + 7, gSaveBlock1Ptr->pos.y + 7);
}

bool32 Overworld_IsBikingAllowed(void)
{
    if (!(gMapHeader.flags & 1))
        return FALSE;
    else
        return TRUE;
}

void SetDefaultFlashLevel(void)
{
    if (!gMapHeader.cave)
        gSaveBlock1Ptr->flashLevel = 0;
    else if (FlagGet(FLAG_SYS_USE_FLASH))
        gSaveBlock1Ptr->flashLevel = 1;
    else
        gSaveBlock1Ptr->flashLevel = gMaxFlashLevel - 1;
}

void Overworld_SetFlashLevel(s32 flashLevel)
{
    if (flashLevel < 0 || flashLevel > gMaxFlashLevel)
        flashLevel = 0;
    gSaveBlock1Ptr->flashLevel = flashLevel;
}

u8 Overworld_GetFlashLevel(void)
{
    return gSaveBlock1Ptr->flashLevel;
}

void SetCurrentMapLayout(u16 mapLayoutId)
{
    gSaveBlock1Ptr->mapLayoutId = mapLayoutId;
    gMapHeader.mapLayout = GetMapLayout();
}

void sub_8085540(u8 var)
{
    sUnknown_020322D8 = var;
}

u8 sub_808554C(void)
{
    return sUnknown_020322D8;
}

u16 GetLocationMusic(struct WarpData *warp)
{
    return Overworld_GetMapHeaderByGroupAndId(warp->mapGroup, warp->mapNum)->music;
}

u16 GetCurrLocationDefaultMusic(void)
{
    return GetLocationMusic(&gSaveBlock1Ptr->location);
}

u16 GetWarpDestinationMusic(void)
{
    return GetLocationMusic(&sWarpDestination);
}

void Overworld_ResetMapMusic(void)
{
    ResetMapMusic();
}

void Overworld_PlaySpecialMapMusic(void)
{
    u16 music = GetCurrLocationDefaultMusic();

    if (music != MUS_OOAME && music != 0xFFFF)
    {
        if (gSaveBlock1Ptr->savedMusic)
            music = gSaveBlock1Ptr->savedMusic;
        else if (GetCurrentMapType() == MAP_TYPE_UNDERWATER)
            music = MUS_DEEPDEEP;
        else if (TestPlayerAvatarFlags(PLAYER_AVATAR_FLAG_SURFING))
            music = MUS_NAMINORI;
    }

    if (music != GetCurrentMapMusic())
        PlayNewMapMusic(music);
}

void Overworld_SetSavedMusic(u16 songNum)
{
    gSaveBlock1Ptr->savedMusic = songNum;
}

void Overworld_ClearSavedMusic(void)
{
    gSaveBlock1Ptr->savedMusic = 0;
}

static void sub_8085810(void)
{
    if (FlagGet(FLAG_SPECIAL_FLAG_0x4001) != TRUE)
    {
        u16 newMusic = GetWarpDestinationMusic();
        u16 currentMusic = GetCurrentMapMusic();
        if (newMusic != MUS_OOAME && newMusic != 0xFFFF)
        {
            if (currentMusic == MUS_DEEPDEEP || currentMusic == MUS_NAMINORI)
                return;
            if (TestPlayerAvatarFlags(PLAYER_AVATAR_FLAG_SURFING))
                newMusic = MUS_NAMINORI;
        }
        if (newMusic != currentMusic)
        {
            if (TestPlayerAvatarFlags(PLAYER_AVATAR_FLAG_MACH_BIKE | PLAYER_AVATAR_FLAG_ACRO_BIKE))
                FadeOutAndFadeInNewMapMusic(newMusic, 4, 4);
            else
                FadeOutAndPlayNewMapMusic(newMusic, 8);
        }
    }
}

void Overworld_ChangeMusicToDefault(void)
{
    u16 currentMusic = GetCurrentMapMusic();
    if (currentMusic != GetCurrLocationDefaultMusic())
        FadeOutAndPlayNewMapMusic(GetCurrLocationDefaultMusic(), 8);
}

void Overworld_ChangeMusicTo(u16 newMusic)
{
    u16 currentMusic = GetCurrentMapMusic();
    if (currentMusic != newMusic && currentMusic != MUS_OOAME)
        FadeOutAndPlayNewMapMusic(newMusic, 8);
}

u8 GetMapMusicFadeoutSpeed(void)
{
    const struct MapHeader *mapHeader = GetDestinationWarpMapHeader();
    if (IsMapTypeIndoors(mapHeader->mapType) == TRUE)
        return 2;
    else
        return 4;
}

void TryFadeOutOldMapMusic(void)
{
    u16 currentMusic = GetCurrentMapMusic();
    u16 warpMusic = GetWarpDestinationMusic();
    if (FlagGet(FLAG_SPECIAL_FLAG_0x4001) != TRUE && warpMusic != GetCurrentMapMusic())
    {
        if (currentMusic == MUS_NAMINORI
            && VarGet(VAR_SKY_PILLAR_STATE) == 2
            && gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(SOOTOPOLIS_CITY)
            && gSaveBlock1Ptr->location.mapNum == MAP_NUM(SOOTOPOLIS_CITY)
            && sWarpDestination.mapGroup == MAP_GROUP(SOOTOPOLIS_CITY)
            && sWarpDestination.mapNum == MAP_NUM(SOOTOPOLIS_CITY)
            && sWarpDestination.x == 29
            && sWarpDestination.y == 53)
            return;
        FadeOutMapMusic(GetMapMusicFadeoutSpeed());
    }
}

bool8 BGMusicStopped(void)
{
    return IsNotWaitingForBGMStop();
}

void Overworld_FadeOutMapMusic(void)
{
    FadeOutMapMusic(4);
}

static void PlayAmbientCry(void)
{
    s16 x, y;
    s8 pan;
    s8 volume;

    PlayerGetDestCoords(&x, &y);
    if (sIsAmbientCryWaterMon == TRUE
     && !MetatileBehavior_IsSurfableWaterOrUnderwater(MapGridGetMetatileBehaviorAt(x, y)))
        return;
    pan = (Random() % 88) + 212;
    volume = (Random() % 30) + 50;
    PlayCry2(sAmbientCrySpecies, pan, volume, 1);
}

void UpdateAmbientCry(s16 *state, u16 *delayCounter)
{
    u8 i, monsCount, divBy;

    switch (*state)
    {
    case 0:
        if (sAmbientCrySpecies == SPECIES_NONE)
            *state = 4;
        else
            *state = 1;
        break;
    case 1:
        *delayCounter = (Random() % 2400) + 1200;
        *state = 3;
        break;
    case 2:
        divBy = 1;
        monsCount = CalculatePlayerPartyCount();
        for (i = 0; i < monsCount; i++)
        {
            if (!GetMonData(&gPlayerParty[i], MON_DATA_SANITY_IS_EGG)
                && GetMonAbility(&gPlayerParty[0]) == ABILITY_SWARM)
            {
                divBy = 2;
                break;
            }
        }
        *delayCounter = ((Random() % 1200) + 1200) / divBy;
        *state = 3;
        break;
    case 3:
        (*delayCounter)--;
        if (*delayCounter == 0)
        {
            PlayAmbientCry();
            *state = 2;
        }
        break;
    case 4:
        break;
    }
}

static void ChooseAmbientCrySpecies(void)
{
    if ((gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(ROUTE130)
     && gSaveBlock1Ptr->location.mapNum == MAP_NUM(ROUTE130))
     && !IsMirageIslandPresent())
    {
        // Only play water pokemon cries on this route
        // when Mirage Island is not present
        sIsAmbientCryWaterMon = TRUE;
        sAmbientCrySpecies = GetLocalWaterMon();
    }
    else
    {
        sAmbientCrySpecies = GetLocalWildMon(&sIsAmbientCryWaterMon);
    }
}

u8 GetMapTypeByGroupAndId(s8 mapGroup, s8 mapNum)
{
    return Overworld_GetMapHeaderByGroupAndId(mapGroup, mapNum)->mapType;
}

u8 GetMapTypeByWarpData(struct WarpData *warp)
{
    return GetMapTypeByGroupAndId(warp->mapGroup, warp->mapNum);
}

u8 GetCurrentMapType(void)
{
    return GetMapTypeByWarpData(&gSaveBlock1Ptr->location);
}

u8 GetLastUsedWarpMapType(void)
{
    return GetMapTypeByWarpData(&gLastUsedWarp);
}

bool8 IsMapTypeOutdoors(u8 mapType)
{
    if (mapType == MAP_TYPE_ROUTE
     || mapType == MAP_TYPE_TOWN
     || mapType == MAP_TYPE_UNDERWATER
     || mapType == MAP_TYPE_CITY
     || mapType == MAP_TYPE_OCEAN_ROUTE)
        return TRUE;
    else
        return FALSE;
}

bool8 Overworld_MapTypeAllowsTeleportAndFly(u8 mapType)
{
    if (mapType == MAP_TYPE_ROUTE
     || mapType == MAP_TYPE_TOWN
     || mapType == MAP_TYPE_OCEAN_ROUTE
     || mapType == MAP_TYPE_CITY)
        return TRUE;
    else
        return FALSE;
}

bool8 IsMapTypeIndoors(u8 mapType)
{
    if (mapType == MAP_TYPE_INDOOR
     || mapType == MAP_TYPE_SECRET_BASE)
        return TRUE;
    else
        return FALSE;
}

u8 GetSavedWarpRegionMapSectionId(void)
{
    return Overworld_GetMapHeaderByGroupAndId(gSaveBlock1Ptr->dynamicWarp.mapGroup, gSaveBlock1Ptr->dynamicWarp.mapNum)->regionMapSectionId;
}

u8 GetCurrentRegionMapSectionId(void)
{
    return Overworld_GetMapHeaderByGroupAndId(gSaveBlock1Ptr->location.mapGroup, gSaveBlock1Ptr->location.mapNum)->regionMapSectionId;
}

u8 GetCurrentMapBattleScene(void)
{
    return Overworld_GetMapHeaderByGroupAndId(gSaveBlock1Ptr->location.mapGroup, gSaveBlock1Ptr->location.mapNum)->battleType;
}

static void InitOverworldBgs(void)
{
    InitBgsFromTemplates(0, sOverworldBgTemplates, ARRAY_COUNT(sOverworldBgTemplates));
    SetBgAttribute(1, BG_ATTR_MOSAIC, 1);
    SetBgAttribute(2, BG_ATTR_MOSAIC, 1);
    SetBgAttribute(3, BG_ATTR_MOSAIC, 1);
    gBGTilemapBuffers2 = AllocZeroed(BG_SCREEN_SIZE);
    gBGTilemapBuffers1 = AllocZeroed(BG_SCREEN_SIZE);
    gBGTilemapBuffers3 = AllocZeroed(BG_SCREEN_SIZE);
    SetBgTilemapBuffer(1, gBGTilemapBuffers2);
    SetBgTilemapBuffer(2, gBGTilemapBuffers1);
    SetBgTilemapBuffer(3, gBGTilemapBuffers3);
    InitStandardTextBoxWindows();
}

void CleanupOverworldWindowsAndTilemaps(void)
{
    ClearMirageTowerPulseBlendEffect();
    FreeAllOverworldWindowBuffers();
    if (gBGTilemapBuffers3)
        FREE_AND_SET_NULL(gBGTilemapBuffers3);
    if (gBGTilemapBuffers1)
        FREE_AND_SET_NULL(gBGTilemapBuffers1);
    if (gBGTilemapBuffers2)
        FREE_AND_SET_NULL(gBGTilemapBuffers2);
}

static void ResetSafariZoneFlag_(void)
{
    ResetSafariZoneFlag();
}

bool32 IsUpdateLinkStateCBActive(void)
{
    if (gMain.callback1 == CB1_UpdateLinkState)
        return TRUE;
    else
        return FALSE;
}

static void DoCB1_Overworld(u16 newKeys, u16 heldKeys)
{
    struct FieldInput inputStruct;

    sub_808B578();
    FieldClearPlayerInput(&inputStruct);
    FieldGetPlayerInput(&inputStruct, newKeys, heldKeys);
    if (!ScriptContext2_IsEnabled())
    {
        if (ProcessPlayerFieldInput(&inputStruct) == 1)
        {
            ScriptContext2_Enable();
            HideMapNamePopUpWindow();
        }
        else
        {
            player_step(inputStruct.dpadDirection, newKeys, heldKeys);
        }
    }
}

void CB1_Overworld(void)
{
    if (gMain.callback2 == CB2_Overworld)
        DoCB1_Overworld(gMain.newKeys, gMain.heldKeys);
}

static void OverworldBasic(void)
{
    ScriptContext2_RunScript();
    RunTasks();
    AnimateSprites();
    CameraUpdate();
    UpdateCameraPanning();
    BuildOamBuffer();
    UpdatePaletteFade();
    UpdateTilesetAnimations();
    do_scheduled_bg_tilemap_copies_to_vram();
}

// This CB2 is used when starting
void CB2_OverworldBasic(void)
{
    OverworldBasic();
}

void CB2_Overworld(void)
{
    bool32 fading = (gPaletteFade.active != 0);
    if (fading)
        SetVBlankCallback(NULL);
    OverworldBasic();
    if (fading)
        SetFieldVBlankCallback();
}

void SetMainCallback1(MainCallback cb)
{
    gMain.callback1 = cb;
}

// This function is never called.
void SetUnusedCallback(void *func)
{
    sUnusedOverworldCallback = func;
}

static bool8 map_post_load_hook_exec(void)
{
    if (gFieldCallback2)
    {
        if (!gFieldCallback2())
        {
            return FALSE;
        }
        else
        {
            gFieldCallback2 = NULL;
            gFieldCallback = NULL;
        }
    }
    else
    {
        if (gFieldCallback)
            gFieldCallback();
        else
            mapldr_default();

        gFieldCallback = NULL;
    }

    return TRUE;
}

void CB2_NewGame(void)
{
    FieldClearVBlankHBlankCallbacks();
    StopMapMusic();
    ResetSafariZoneFlag_();
    NewGameInitData();
    ResetInitialPlayerAvatarState();
    PlayTimeCounter_Start();
    ScriptContext1_Init();
    ScriptContext2_Disable();
    gFieldCallback = NULL; //ExecuteTruckSequence;
    gFieldCallback2 = NULL;
    do_load_map_stuff_loop(&gMain.state);
    SetFieldVBlankCallback();
    SetMainCallback1(CB1_Overworld);
    SetMainCallback2(CB2_Overworld);
}

void CB2_WhiteOut(void)
{
    u8 val;

    if (++gMain.state >= 120)
    {
        FieldClearVBlankHBlankCallbacks();
        StopMapMusic();
        ResetSafariZoneFlag_();
        DoWhiteOut();
        ResetInitialPlayerAvatarState();
        ScriptContext1_Init();
        ScriptContext2_Disable();
        gFieldCallback = sub_80AF3C8;
        val = 0;
        do_load_map_stuff_loop(&val);
        SetFieldVBlankCallback();
        SetMainCallback1(CB1_Overworld);
        SetMainCallback2(CB2_Overworld);
    }
}

void CB2_LoadMap(void)
{
    FieldClearVBlankHBlankCallbacks();
    ScriptContext1_Init();
    ScriptContext2_Disable();
    SetMainCallback1(NULL);
    SetMainCallback2(c2_change_map);
    gMain.savedCallback = CB2_LoadMap2;
}

static void CB2_LoadMap2(void)
{
    do_load_map_stuff_loop(&gMain.state);
    SetFieldVBlankCallback();
    SetMainCallback1(CB1_Overworld);
    SetMainCallback2(CB2_Overworld);
}

void sub_8086024(void)
{
    if (!gMain.state)
    {
        FieldClearVBlankHBlankCallbacks();
        ScriptContext1_Init();
        ScriptContext2_Disable();
        SetMainCallback1(NULL);
    }
    if (load_map_stuff(&gMain.state, 1))
    {
        SetFieldVBlankCallback();
        SetMainCallback1(CB1_Overworld);
        SetMainCallback2(CB2_Overworld);
    }
}

void sub_8086074(void)
{
    FieldClearVBlankHBlankCallbacks();
    gFieldCallback = sub_80AF314;
    SetMainCallback2(c2_80567AC);
}

static void c2_80567AC(void)
{
    if (map_loading_iteration_3(&gMain.state))
    {
        SetFieldVBlankCallback();
        SetMainCallback1(CB1_UpdateLinkState);
        ResetAllMultiplayerState();
        SetMainCallback2(CB2_Overworld);
    }
}

void CB2_ReturnToField(void)
{
    if (IsUpdateLinkStateCBActive() == TRUE)
    {
        SetMainCallback2(CB2_ReturnToFieldLink);
    }
    else
    {
        FieldClearVBlankHBlankCallbacks();
        SetMainCallback2(CB2_ReturnToFieldLocal);
    }
}

void CB2_ReturnToFieldLocal(void)
{
    if (sub_8086638(&gMain.state))
    {
        SetFieldVBlankCallback();
        SetMainCallback2(CB2_Overworld);
    }
}

void CB2_ReturnToFieldLink(void)
{
    if (!sub_8087598() && map_loading_iteration_2_link(&gMain.state))
        SetMainCallback2(CB2_Overworld);
}

void CB2_ReturnToFieldFromMultiplayer(void)
{
    FieldClearVBlankHBlankCallbacks();
    StopMapMusic();
    SetMainCallback1(CB1_UpdateLinkState);
    ResetAllMultiplayerState();

    if (gWirelessCommType != 0)
        gFieldCallback = sub_80AF314;
    else
        gFieldCallback = sub_80AF214;

    ScriptContext1_Init();
    ScriptContext2_Disable();
    CB2_ReturnToField();
}

void CB2_ReturnToFieldWithOpenMenu(void)
{
    FieldClearVBlankHBlankCallbacks();
    gFieldCallback2 = sub_80AF6A4;
    CB2_ReturnToField();
}

void CB2_ReturnToFieldContinueScript(void)
{
    FieldClearVBlankHBlankCallbacks();
    gFieldCallback = sub_80AF188;
    CB2_ReturnToField();
}

void CB2_ReturnToFieldContinueScriptPlayMapMusic(void)
{
    FieldClearVBlankHBlankCallbacks();
    gFieldCallback = FieldCallback_ReturnToEventScript2;
    CB2_ReturnToField();
}

void sub_80861E8(void)
{
    FieldClearVBlankHBlankCallbacks();
    gFieldCallback = sub_80AF3C8;
    CB2_ReturnToField();
}

static void sub_8086204(void)
{
    if ((gMapHeader.flags & 0xF8) == 8 && SecretBaseMapPopupEnabled() == TRUE)
        ShowMapNamePopup();
    sub_80AF3C8();
}

void CB2_ContinueSavedGame(void)
{
    u8 trainerHillMapId;

    FieldClearVBlankHBlankCallbacks();
    StopMapMusic();
    ResetSafariZoneFlag_();
    if (gSaveFileStatus == 0xFF)
        sub_81A3908();

    LoadSaveblockMapHeader();
    ClearDiveAndHoleWarps();
    // trainerHillMapId = GetCurrentTrainerHillMapId();
    // if (gMapHeader.mapLayoutId == LAYOUT_BATTLE_FRONTIER_BATTLE_PYRAMID_EMPTY_SQUARE)
    //     LoadBattlePyramidFloorEventObjectScripts();
    // else if (trainerHillMapId != 0 && trainerHillMapId != 6)
    //     sub_81D5F48();
    // else
        LoadSaveblockEventObjScripts();

    UnfreezeEventObjects();
    DoTimeBasedEvents();
    sub_8084788();
    // if (gMapHeader.mapLayoutId == LAYOUT_BATTLE_FRONTIER_BATTLE_PYRAMID_EMPTY_SQUARE)
    //     InitBattlePyramidMap(TRUE);
    // else if (trainerHillMapId != 0)
    //     InitTrainerHillMap();
    // else
        InitMapFromSavedGame();

    PlayTimeCounter_Start();
    ScriptContext1_Init();
    ScriptContext2_Disable();
    InitMatchCallCounters();
    if (UseContinueGameWarp() == TRUE)
    {
        ClearContinueGameWarpStatus();
        SetWarpDestinationToContinueGameWarp();
        WarpIntoMap();
        sub_80EDB44();
        SetMainCallback2(CB2_LoadMap);
    }
    else
    {
        sub_80EDB44();
        gFieldCallback = sub_8086204;
        SetMainCallback1(CB1_Overworld);
        CB2_ReturnToField();
    }
}

static void FieldClearVBlankHBlankCallbacks(void)
{
    if (warp0_in_pokecenter() == TRUE)
        CloseLink();

    if (gWirelessCommType != 0)
    {
        EnableInterrupts(INTR_FLAG_VBLANK | INTR_FLAG_VCOUNT | INTR_FLAG_TIMER3 | INTR_FLAG_SERIAL);
        DisableInterrupts(INTR_FLAG_HBLANK);
    }
    else
    {
        u16 savedIme = REG_IME;
        REG_IME = 0;
        REG_IE &= ~INTR_FLAG_HBLANK;
        REG_IE |= INTR_FLAG_VBLANK;
        REG_IME = savedIme;
    }

    SetVBlankCallback(NULL);
    SetHBlankCallback(NULL);
}

static void SetFieldVBlankCallback(void)
{
    SetVBlankCallback(VBlankCB_Field);
}

static void VBlankCB_Field(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    ScanlineEffect_InitHBlankDmaTransfer();
    FieldUpdateBgTilemapScroll();
    TransferPlttBuffer();
    TransferTilesetAnimsBuffer();
}

static void InitCurrentFlashLevelScanlineEffect(void)
{
    u8 flashLevel;

    // if (InBattlePyramid_())
    // {
    //     WriteBattlePyramidViewScanlineEffectBuffer();
    //     ScanlineEffect_SetParams(sFlashEffectParams);
    // }
    // else
    if ((flashLevel = Overworld_GetFlashLevel()))
    {
        WriteFlashScanlineEffectBuffer(flashLevel);
        ScanlineEffect_SetParams(sFlashEffectParams);
    }
}

static bool32 map_loading_iteration_3(u8 *state)
{
    switch (*state)
    {
    case 0:
        InitOverworldBgs();
        ScriptContext1_Init();
        ScriptContext2_Disable();
        sub_80867C8();
        sub_80867D8();
        (*state)++;
        break;
    case 1:
        mli0_load_map(1);
        (*state)++;
        break;
    case 2:
        sub_8086988(TRUE);
        (*state)++;
        break;
    case 3:
        sub_8086AE4();
        sub_80869DC();
        sub_8086B14();
        SetCameraToTrackGuestPlayer();
        (*state)++;
        break;
    case 4:
        InitCurrentFlashLevelScanlineEffect();
        InitOverworldGraphicsRegisters();
        sub_8197200();
        (*state)++;
        break;
    case 5:
        move_tilemap_camera_to_upper_left_corner();
        (*state)++;
        break;
    case 6:
        copy_map_tileset1_to_vram(gMapHeader.mapLayout);
        (*state)++;
        break;
    case 7:
        copy_map_tileset2_to_vram(gMapHeader.mapLayout);
        (*state)++;
        break;
    case 8:
        if (free_temp_tile_data_buffers_if_possible() != TRUE)
        {
            apply_map_tileset1_tileset2_palette(gMapHeader.mapLayout);
            (*state)++;
        }
        break;
    case 9:
        DrawWholeMapView();
        (*state)++;
        break;
    case 10:
        InitTilesetAnimations();
        (*state)++;
        break;
    case 11:
        if (gWirelessCommType != 0)
        {
            LoadWirelessStatusIndicatorSpriteGfx();
            CreateWirelessStatusIndicatorSprite(0, 0);
        }
        (*state)++;
        break;
    case 12:
        if (map_post_load_hook_exec())
            (*state)++;
        break;
    case 13:
        return TRUE;
    }

    return FALSE;
}

static bool32 load_map_stuff(u8 *state, u32 a2)
{
    switch (*state)
    {
    case 0:
        FieldClearVBlankHBlankCallbacks();
        mli0_load_map(a2);
        (*state)++;
        break;
    case 1:
        sub_80867C8();
        sub_80867D8();
        (*state)++;
        break;
    case 2:
        sub_8086988(a2);
        (*state)++;
        break;
    case 3:
        mli4_mapscripts_and_other();
        sub_8086A80();
        (*state)++;
        break;
    case 4:
        InitCurrentFlashLevelScanlineEffect();
        InitOverworldGraphicsRegisters();
        sub_8197200();
        (*state)++;
        break;
    case 5:
        move_tilemap_camera_to_upper_left_corner();
        (*state)++;
        break;
    case 6:
        copy_map_tileset1_to_vram(gMapHeader.mapLayout);
        (*state)++;
        break;
    case 7:
        copy_map_tileset2_to_vram(gMapHeader.mapLayout);
        (*state)++;
        break;
    case 8:
        if (free_temp_tile_data_buffers_if_possible() != TRUE)
        {
            apply_map_tileset1_tileset2_palette(gMapHeader.mapLayout);
            (*state)++;
        }
        break;
    case 9:
        DrawWholeMapView();
        (*state)++;
        break;
    case 10:
        InitTilesetAnimations();
        (*state)++;
        break;
    case 11:
        if ((gMapHeader.flags & 0xF8) == 8 && SecretBaseMapPopupEnabled() == TRUE)
            ShowMapNamePopup();
        (*state)++;
        break;
    case 12:
        if (map_post_load_hook_exec())
            (*state)++;
        break;
    case 13:
        return TRUE;
    }

    return FALSE;
}

static bool32 sub_8086638(u8 *state)
{
    switch (*state)
    {
    case 0:
        sub_80867C8();
        sub_80867D8();
        sub_8086988(0);
        sub_8086A68();
        sub_8086A80();
        (*state)++;
        break;
    case 1:
        sub_8086860();
        // sub_81D64C0();
        (*state)++;
        break;
    case 2:
        if (map_post_load_hook_exec())
            (*state)++;
        break;
    case 3:
        return TRUE;
    }

    return FALSE;
}

static bool32 map_loading_iteration_2_link(u8 *state)
{
    switch (*state)
    {
    case 0:
        FieldClearVBlankHBlankCallbacks();
        sub_80867C8();
        sub_80867D8();
        (*state)++;
        break;
    case 1:
        sub_8086988(1);
        (*state)++;
        break;
    case 2:
        CreateLinkPlayerSprites();
        sub_8086A68();
        SetCameraToTrackGuestPlayer_2();
        (*state)++;
        break;
    case 3:
        InitCurrentFlashLevelScanlineEffect();
        InitOverworldGraphicsRegisters();
        sub_8197200();
        (*state)++;
        break;
    case 4:
        move_tilemap_camera_to_upper_left_corner();
        (*state)++;
        break;
    case 5:
        copy_map_tileset1_to_vram(gMapHeader.mapLayout);
        (*state)++;
        break;
    case 6:
        copy_map_tileset2_to_vram(gMapHeader.mapLayout);
        (*state)++;
        break;
    case 7:
        if (free_temp_tile_data_buffers_if_possible() != TRUE)
        {
            apply_map_tileset1_tileset2_palette(gMapHeader.mapLayout);
            (*state)++;
        }
        break;
    case 8:
        DrawWholeMapView();
        (*state)++;
        break;
    case 9:
        InitTilesetAnimations();
        (*state)++;
        break;
    case 11:
        if (gWirelessCommType != 0)
        {
            LoadWirelessStatusIndicatorSpriteGfx();
            CreateWirelessStatusIndicatorSprite(0, 0);
        }
        (*state)++;
        break;
    case 12:
        if (map_post_load_hook_exec())
            (*state)++;
        break;
    case 10:
        (*state)++;
        break;
    case 13:
        SetFieldVBlankCallback();
        (*state)++;
        return TRUE;
    }

    return FALSE;
}

static void do_load_map_stuff_loop(u8 *state)
{
    while (!load_map_stuff(state, 0));
}

static void sub_80867C8(void)
{
    ClearMirageTowerPulseBlend();
    MoveSaveBlocks_ResetHeap();
}

static void sub_80867D8(void)
{
    SetGpuReg(REG_OFFSET_DISPCNT, 0);
    ScanlineEffect_Stop();

    DmaClear16(3, PLTT + 2, PLTT_SIZE - 2);
    DmaFillLarge16(3, 0, (void *)(VRAM + 0x0), 0x18000, 0x1000);
    ResetOamRange(0, 128);
    LoadOam();
}

static void sub_8086860(void)
{
    InitCurrentFlashLevelScanlineEffect();
    InitOverworldGraphicsRegisters();
    sub_8197200();
    mapdata_load_assets_to_gpu_and_full_redraw();
}

static void InitOverworldGraphicsRegisters(void)
{
    clear_scheduled_bg_copies_to_vram();
    reset_temp_tile_data_buffers();
    SetGpuReg(REG_OFFSET_MOSAIC, 0);
    SetGpuReg(REG_OFFSET_WININ, WININ_WIN0_BG_ALL | WININ_WIN0_OBJ | WININ_WIN1_BG_ALL | WININ_WIN1_OBJ);
    SetGpuReg(REG_OFFSET_WINOUT, WINOUT_WIN01_BG0 | WINOUT_WINOBJ_BG0);
    SetGpuReg(REG_OFFSET_WIN0H, 0xFF);
    SetGpuReg(REG_OFFSET_WIN0V, 0xFF);
    SetGpuReg(REG_OFFSET_WIN1H, 0xFFFF);
    SetGpuReg(REG_OFFSET_WIN1V, 0xFFFF);
    SetGpuReg(REG_OFFSET_BLDCNT, gOverworldBackgroundLayerFlags[1] | gOverworldBackgroundLayerFlags[2] | gOverworldBackgroundLayerFlags[3]
                               | BLDCNT_TGT2_OBJ | BLDCNT_EFFECT_BLEND);
    SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(13, 7));
    InitOverworldBgs();
    schedule_bg_copy_tilemap_to_vram(1);
    schedule_bg_copy_tilemap_to_vram(2);
    schedule_bg_copy_tilemap_to_vram(3);
    ChangeBgX(0, 0, 0);
    ChangeBgY(0, 0, 0);
    ChangeBgX(1, 0, 0);
    ChangeBgY(1, 0, 0);
    ChangeBgX(2, 0, 0);
    ChangeBgY(2, 0, 0);
    ChangeBgX(3, 0, 0);
    ChangeBgY(3, 0, 0);
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_ON | DISPCNT_WIN0_ON | DISPCNT_WIN1_ON
                                | DISPCNT_OBJ_1D_MAP | DISPCNT_HBLANK_INTERVAL);
    ShowBg(0);
    ShowBg(1);
    ShowBg(2);
    ShowBg(3);
    InitFieldMessageBox();
}

static void sub_8086988(u32 a1)
{
    ResetTasks();
    ResetSpriteData();
    ResetPaletteFade();
    ScanlineEffect_Clear();
    ResetAllPicSprites();
    ResetCameraUpdateInfo();
    InstallCameraPanAheadCallback();
    if (!a1)
        InitEventObjectPalettes(0);
    else
        InitEventObjectPalettes(1);

    FieldEffectActiveListClear();
    StartWeather();
    ResumePausedWeather();
    if (!a1)
        SetUpFieldTasks();
    RunOnResumeMapScript();
    TryStartMirageTowerPulseBlendEffect();
}

static void sub_80869DC(void)
{
    gTotalCameraPixelOffsetX = 0;
    gTotalCameraPixelOffsetY = 0;
    ResetEventObjects();
    TrySpawnEventObjects(0, 0);
    TryRunOnWarpIntoMapScript();
}

static void mli4_mapscripts_and_other(void)
{
    s16 x, y;
    struct InitialPlayerAvatarState *player;

    gTotalCameraPixelOffsetX = 0;
    gTotalCameraPixelOffsetY = 0;
    ResetEventObjects();
    GetCameraFocusCoords(&x, &y);
    player = GetInitialPlayerAvatarState();
    InitPlayerAvatar(x, y, player->direction, gSaveBlock2Ptr->playerGender);
    SetPlayerAvatarTransitionFlags(player->transitionFlags);
    ResetInitialPlayerAvatarState();
    TrySpawnEventObjects(0, 0);
    TryRunOnWarpIntoMapScript();
}

static void sub_8086A68(void)
{
    sub_808E16C(0, 0);
    RotatingGate_InitPuzzleAndGraphics();
    RunOnReturnToFieldMapScript();
}

static void sub_8086A80(void)
{
    gEventObjects[gPlayerAvatar.eventObjectId].trackedByCamera = 1;
    InitCameraUpdateCallback(gPlayerAvatar.spriteId);
}

static void SetCameraToTrackGuestPlayer(void)
{
    InitCameraUpdateCallback(GetSpriteForLinkedPlayer(gLocalLinkPlayerId));
}

// Duplicate function.
static void SetCameraToTrackGuestPlayer_2(void)
{
    InitCameraUpdateCallback(GetSpriteForLinkedPlayer(gLocalLinkPlayerId));
}

static void sub_8086AE4(void)
{
    u16 x, y;
    GetCameraFocusCoords(&x, &y);

    // This is a hack of some kind; it's undone in sub_8086B14, which is called
    // soon after this function.
    sub_8088B3C(x + gLocalLinkPlayerId, y);
}

static void sub_8086B14(void)
{
    u16 i;
    u16 x, y;

    GetCameraFocusCoords(&x, &y);
    x -= gLocalLinkPlayerId;

    for (i = 0; i < gFieldLinkPlayerCount; i++)
    {
        SpawnLinkPlayerEventObject(i, i + x, y, gLinkPlayers[i].gender);
        CreateLinkPlayerSprite(i, gLinkPlayers[i].version);
    }

    ClearAllPlayerKeys();
}

static void CreateLinkPlayerSprites(void)
{
    u16 i;
    for (i = 0; i < gFieldLinkPlayerCount; i++)
        CreateLinkPlayerSprite(i, gLinkPlayers[i].version);
}


static void CB1_UpdateLinkState(void)
{
    if (gWirelessCommType == 0 || !IsRfuRecvQueueEmpty() || !IsSendingKeysToLink())
    {
        u8 selfId = gLocalLinkPlayerId;
        UpdateAllLinkPlayers(gLinkPartnersHeldKeys, selfId);

        // Note: Because guestId is between 0 and 4, while the smallest key code is
        // LINK_KEY_CODE_EMPTY, this is functionally equivalent to `sPlayerKeyInterceptCallback(0)`.
        // It is expecting the callback to be KeyInterCB_SelfIdle, and that will 
        // completely ignore any input parameters.
        //
        // UpdateHeldKeyCode performs a sanity check on its input; if 
        // sPlayerKeyInterceptCallback echoes back the argument, which is selfId, then
        // it'll use LINK_KEY_CODE_EMPTY instead.
        //
        // Note 2: There are some key intercept callbacks that treat the key as a player
        // ID. It's so hacky.
        UpdateHeldKeyCode(sPlayerKeyInterceptCallback(selfId));
        ClearAllPlayerKeys();
    }
}

void ResetAllMultiplayerState(void)
{
    ResetAllTradingStates();
    SetKeyInterceptCallback(KeyInterCB_SelfIdle);
}

static void ClearAllPlayerKeys(void)
{
    ResetPlayerHeldKeys(gLinkPartnersHeldKeys);
}

static void SetKeyInterceptCallback(u16 (*func)(u32))
{
    sRfuKeepAliveTimer = 0;
    sPlayerKeyInterceptCallback = func;
}

// Once every ~60 frames, if the link state hasn't changed (timer reset by calls
// to SetKeyInterceptCallback), it does a bunch of sanity checks on the connection.
// I'm not sure if sRfuKeepAliveTimer is reset in the process, though; rfu stuff is
// still undocumented.
static void CheckRfuKeepAliveTimer(void)
{
    if (gWirelessCommType != 0 && ++sRfuKeepAliveTimer > 60)
        LinkRfu_FatalError();
}

static void ResetAllTradingStates(void)
{
    s32 i;
    for (i = 0; i < 4; i++)
        sPlayerTradingStates[i] = PLAYER_TRADING_STATE_IDLE;
}

// Returns true if all connected players are in tradingState.
static bool32 AreAllPlayersInTradingState(u16 tradingState)
{
    s32 i;
    s32 count = gFieldLinkPlayerCount;

    for (i = 0; i < count; i++)
        if (sPlayerTradingStates[i] != tradingState)
            return FALSE;
    return TRUE;
}

static bool32 IsAnyPlayerInTradingState(u16 tradingState)
{
    s32 i;
    s32 count = gFieldLinkPlayerCount;

    for (i = 0; i < count; i++)
        if (sPlayerTradingStates[i] == tradingState)
            return TRUE;
    return FALSE;
}

static void HandleLinkPlayerKeyInput(u32 playerId, u16 key, struct TradeRoomPlayer *trainer, u16 *forceFacing)
{
    const u8 *script;

    if (sPlayerTradingStates[playerId] == PLAYER_TRADING_STATE_IDLE)
    {
        script = TryGetTileEventScript(trainer);
        if (script)
        {
            *forceFacing = GetDirectionForEventScript(script);
            sPlayerTradingStates[playerId] = PLAYER_TRADING_STATE_BUSY;
            if (trainer->isLocalPlayer)
            {
                SetKeyInterceptCallback(KeyInterCB_DeferToEventScript);
                sub_8087530(script);
            }
            return;
        }
        if (IsAnyPlayerInTradingState(PLAYER_TRADING_STATE_EXITING_ROOM) == TRUE)
        {
            sPlayerTradingStates[playerId] = PLAYER_TRADING_STATE_BUSY;
            if (trainer->isLocalPlayer)
            {
                SetKeyInterceptCallback(KeyInterCB_DeferToEventScript);
                sub_8087584();
            }
            return;
        }

        switch (key)
        {
        case LINK_KEY_CODE_START_BUTTON:
            if (sub_8087340_2(trainer))
            {
                sPlayerTradingStates[playerId] = PLAYER_TRADING_STATE_BUSY;
                if (trainer->isLocalPlayer)
                {
                    SetKeyInterceptCallback(KeyInterCB_DeferToEventScript);
                    InitLinkRoomStartMenuScript();
                }
            }
            break;
        case LINK_KEY_CODE_DPAD_DOWN:
            if (PlayerIsAtSouthExit(trainer) == TRUE)
            {
                sPlayerTradingStates[playerId] = PLAYER_TRADING_STATE_BUSY;
                if (trainer->isLocalPlayer)
                {
                    SetKeyInterceptCallback(KeyInterCB_DeferToEventScript);
                    CreateConfirmLeaveTradeRoomPrompt();
                }
            }
            break;
        case LINK_KEY_CODE_A_BUTTON:
            script = TryInteractWithPlayer(trainer);
            if (script)
            {
                sPlayerTradingStates[playerId] = PLAYER_TRADING_STATE_BUSY;
                if (trainer->isLocalPlayer)
                {
                    SetKeyInterceptCallback(KeyInterCB_DeferToEventScript);
                    InitMenuBasedScript(script);
                }
            }
            break;
        case LINK_KEY_CODE_HANDLE_RECV_QUEUE:
            if (sub_8087340(trainer))
            {
                sPlayerTradingStates[playerId] = PLAYER_TRADING_STATE_BUSY;
                if (trainer->isLocalPlayer)
                {
                    SetKeyInterceptCallback(KeyInterCB_DeferToRecvQueue);
                    sub_8087510();
                }
            }
            break;
        case LINK_KEY_CODE_HANDLE_SEND_QUEUE:
            if (sub_8087340(trainer))
            {
                sPlayerTradingStates[playerId] = PLAYER_TRADING_STATE_BUSY;
                if (trainer->isLocalPlayer)
                {
                    SetKeyInterceptCallback(KeyInterCB_DeferToSendQueue);
                    sub_8087510();
                }
            }
            break;
        }
    }

    switch (key)
    {
    case LINK_KEY_CODE_EXIT_ROOM:
        sPlayerTradingStates[playerId] = PLAYER_TRADING_STATE_EXITING_ROOM;
        break;
    case LINK_KEY_CODE_UNK_2:
        sPlayerTradingStates[playerId] = PLAYER_TRADING_STATE_UNK_2;
        break;
    case LINK_KEY_CODE_UNK_4:
        sPlayerTradingStates[playerId] = PLAYER_TRADING_STATE_IDLE;
        if (trainer->isLocalPlayer)
            SetKeyInterceptCallback(KeyInterCB_SelfIdle);
        break;
    case LINK_KEY_CODE_UNK_7:
        if (sPlayerTradingStates[playerId] == PLAYER_TRADING_STATE_UNK_2)
            sPlayerTradingStates[playerId] = PLAYER_TRADING_STATE_BUSY;
        break;
    }
}

static void UpdateAllLinkPlayers(u16 *keys, s32 selfId)
{
    struct TradeRoomPlayer trainer;
    s32 i;

    for (i = 0; i < 4; i++)
    {
        u8 key = keys[i];
        u16 setFacing = FACING_NONE;
        LoadTradeRoomPlayer(i, selfId, &trainer);
        HandleLinkPlayerKeyInput(i, key, &trainer, &setFacing);
        if (sPlayerTradingStates[i] == PLAYER_TRADING_STATE_IDLE)
            setFacing = GetDirectionForDpadKey(key);
        SetPlayerFacingDirection(i, setFacing);
    }
}

static void UpdateHeldKeyCode(u16 key)
{
    if (key >= LINK_KEY_CODE_EMPTY && key < LINK_KEY_CODE_UNK_8)
        gHeldKeyCodeToSend = key;
    else
        gHeldKeyCodeToSend = LINK_KEY_CODE_EMPTY;

    if (gWirelessCommType != 0
        && GetLinkSendQueueLength() > 1
        && IsUpdateLinkStateCBActive() == TRUE
        && IsSendingKeysToLink() == TRUE)
    {
        switch (key)
        {
        case LINK_KEY_CODE_EMPTY:
        case LINK_KEY_CODE_DPAD_DOWN:
        case LINK_KEY_CODE_DPAD_UP:
        case LINK_KEY_CODE_DPAD_LEFT:
        case LINK_KEY_CODE_DPAD_RIGHT:
        case LINK_KEY_CODE_START_BUTTON:
        case LINK_KEY_CODE_A_BUTTON:
            gHeldKeyCodeToSend = LINK_KEY_CODE_NULL;
            break;
        }
    }
}

static u16 KeyInterCB_ReadButtons(u32 key)
{
    if (gMain.heldKeys & DPAD_UP)
        return LINK_KEY_CODE_DPAD_UP;
    else if (gMain.heldKeys & DPAD_DOWN)
        return LINK_KEY_CODE_DPAD_DOWN;
    else if (gMain.heldKeys & DPAD_LEFT)
        return LINK_KEY_CODE_DPAD_LEFT;
    else if (gMain.heldKeys & DPAD_RIGHT)
        return LINK_KEY_CODE_DPAD_RIGHT;
    else if (gMain.newKeys & START_BUTTON)
        return LINK_KEY_CODE_START_BUTTON;
    else if (gMain.newKeys & A_BUTTON)
        return LINK_KEY_CODE_A_BUTTON;
    else
        return LINK_KEY_CODE_EMPTY;
}

static u16 GetDirectionForDpadKey(u16 a1)
{
    switch (a1)
    {
    case LINK_KEY_CODE_DPAD_RIGHT:
        return FACING_RIGHT;
    case LINK_KEY_CODE_DPAD_LEFT:
        return FACING_LEFT;
    case LINK_KEY_CODE_DPAD_UP:
        return FACING_UP;
    case LINK_KEY_CODE_DPAD_DOWN:
        return FACING_DOWN;
    default:
        return FACING_NONE;
    }
}

// Overwrites the keys with 0x11
static void ResetPlayerHeldKeys(u16 *keys)
{
    s32 i;
    for (i = 0; i < 4; i++)
        keys[i] = LINK_KEY_CODE_EMPTY;
}


static u16 KeyInterCB_SelfIdle(u32 key)
{
    if (ScriptContext2_IsEnabled() == TRUE)
        return LINK_KEY_CODE_EMPTY;
    if (GetLinkRecvQueueLength() > 4)
        return LINK_KEY_CODE_HANDLE_RECV_QUEUE;
    if (GetLinkSendQueueLength() <= 4)
        return KeyInterCB_ReadButtons(key);
    return LINK_KEY_CODE_HANDLE_SEND_QUEUE;
}

static u16 sub_80870EC(u32 key)
{
    CheckRfuKeepAliveTimer();
    return LINK_KEY_CODE_EMPTY;
}

// Ignore the player's inputs as long as there is an event script
// in ScriptContext2.
static u16 KeyInterCB_DeferToEventScript(u32 key)
{
    u16 retVal;
    if (ScriptContext2_IsEnabled() == TRUE)
    {
        retVal = LINK_KEY_CODE_EMPTY;
    }
    else
    {
        retVal = LINK_KEY_CODE_UNK_4;
        SetKeyInterceptCallback(sub_80870EC);
    }
    return retVal;
}

// Ignore the player's inputs as long as there are events being recived.
static u16 KeyInterCB_DeferToRecvQueue(u32 key)
{
    u16 retVal;
    if (GetLinkRecvQueueLength() > 2)
    {
        retVal = LINK_KEY_CODE_EMPTY;
    }
    else
    {
        retVal = LINK_KEY_CODE_UNK_4;
        ScriptContext2_Disable();
        SetKeyInterceptCallback(sub_80870EC);
    }
    return retVal;
}

// Ignore the player's inputs as long as there are events being sent.
static u16 KeyInterCB_DeferToSendQueue(u32 key)
{
    u16 retVal;
    if (GetLinkSendQueueLength() > 2)
    {
        retVal = LINK_KEY_CODE_EMPTY;
    }
    else
    {
        retVal = LINK_KEY_CODE_UNK_4;
        ScriptContext2_Disable();
        SetKeyInterceptCallback(sub_80870EC);
    }
    return retVal;
}

static u16 KeyInterCB_DoNothingAndKeepAlive(u32 key)
{
    CheckRfuKeepAliveTimer();
    return LINK_KEY_CODE_EMPTY;
}

static u16 sub_8087170(u32 keyOrPlayerId)
{
    if (sPlayerTradingStates[keyOrPlayerId] == PLAYER_TRADING_STATE_UNK_2)
    {
        if (gMain.newKeys & B_BUTTON)
        {
            SetKeyInterceptCallback(KeyInterCB_DoNothingAndKeepAlive);
            return LINK_KEY_CODE_UNK_7;
        }
        else
        {
            return LINK_KEY_CODE_EMPTY;
        }
    }
    else
    {
        CheckRfuKeepAliveTimer();
        return LINK_KEY_CODE_EMPTY;
    }
}

static u16 sub_80871AC(u32 a1)
{
    SetKeyInterceptCallback(sub_8087170);
    return LINK_KEY_CODE_UNK_2;
}

static u16 KeyInterCB_SendNothing(u32 key)
{
    return LINK_KEY_CODE_EMPTY;
}

static u16 KeyInterCB_WaitForPlayersToExit(u32 keyOrPlayerId)
{
    // keyOrPlayerId could be any keycode. This callback does no sanity checking
    // on the size of the key. It's assuming that it is being called from
    // CB1_UpdateLinkState.
    if (sPlayerTradingStates[keyOrPlayerId] != PLAYER_TRADING_STATE_EXITING_ROOM)
        CheckRfuKeepAliveTimer();
    if (AreAllPlayersInTradingState(PLAYER_TRADING_STATE_EXITING_ROOM) == TRUE)
    {
        ScriptContext1_SetupScript(EventScript_DoLinkRoomExit);
        SetKeyInterceptCallback(KeyInterCB_SendNothing);
    }
    return LINK_KEY_CODE_EMPTY;
}

static u16 KeyInterCB_SendExitRoomKey(u32 key)
{
    SetKeyInterceptCallback(KeyInterCB_WaitForPlayersToExit);
    return LINK_KEY_CODE_EXIT_ROOM;
}

// Duplicate function.
static u16 KeyInterCB_SendNothing_2(u32 key)
{
    return LINK_KEY_CODE_EMPTY;
}

u32 sub_8087214(void)
{
    if (IsAnyPlayerInTradingState(PLAYER_TRADING_STATE_EXITING_ROOM) == TRUE)
        return 2;
    if (sPlayerKeyInterceptCallback == sub_8087170 && sPlayerTradingStates[gLocalLinkPlayerId] != PLAYER_TRADING_STATE_UNK_2)
        return 0;
    if (sPlayerKeyInterceptCallback == KeyInterCB_DoNothingAndKeepAlive && sPlayerTradingStates[gLocalLinkPlayerId] == PLAYER_TRADING_STATE_BUSY)
        return 2;
    if (AreAllPlayersInTradingState(PLAYER_TRADING_STATE_UNK_2) != FALSE)
        return 1;
    return 0;
}

bool32 sub_808727C(void)
{
    return IsAnyPlayerInTradingState(PLAYER_TRADING_STATE_EXITING_ROOM);
}

u16 sub_8087288(void)
{
    SetKeyInterceptCallback(sub_80871AC);
    return 0;
}

u16 sub_808729C(void)
{
    SetKeyInterceptCallback(KeyInterCB_DeferToEventScript);
    return 0;
}

// The exit room key will be sent at the next opportunity.
// The return value is meaningless.
u16 QueueExitLinkRoomKey(void)
{
    SetKeyInterceptCallback(KeyInterCB_SendExitRoomKey);
    return 0;
}

u16 sub_80872C4(void)
{
    SetKeyInterceptCallback(KeyInterCB_SendNothing_2);
    return 0;
}

static void LoadTradeRoomPlayer(s32 linkPlayerId, s32 myPlayerId, struct TradeRoomPlayer *trainer)
{
    s16 x, y;

    trainer->playerId = linkPlayerId;
    trainer->isLocalPlayer = (linkPlayerId == myPlayerId) ? 1 : 0;
    trainer->c = gLinkPlayerEventObjects[linkPlayerId].movementMode;
    trainer->facing = GetLinkPlayerFacingDirection(linkPlayerId);
    GetLinkPlayerCoords(linkPlayerId, &x, &y);
    trainer->pos.x = x;
    trainer->pos.y = y;
    trainer->pos.height = GetLinkPlayerElevation(linkPlayerId);
    trainer->field_C = MapGridGetMetatileBehaviorAt(x, y);
}

static bool32 sub_8087340(struct TradeRoomPlayer *player)
{
    u8 v1 = player->c;
    if (v1 == MOVEMENT_MODE_SCRIPTED || v1 == MOVEMENT_MODE_FREE)
        return TRUE;
    else
        return FALSE;
}

// Duplicate function.
static bool32 sub_8087340_2(struct TradeRoomPlayer *player)
{
    u8 v1 = player->c;
    if (v1 == MOVEMENT_MODE_SCRIPTED || v1 == MOVEMENT_MODE_FREE)
        return TRUE;
    else
        return FALSE;
}

static u8 *TryGetTileEventScript(struct TradeRoomPlayer *player)
{
    if (player->c != MOVEMENT_MODE_SCRIPTED)
        return FACING_NONE;
    return GetCoordEventScriptAtMapPosition(&player->pos);
}

static bool32 PlayerIsAtSouthExit(struct TradeRoomPlayer *player)
{
    if (player->c != MOVEMENT_MODE_SCRIPTED && player->c != MOVEMENT_MODE_FREE)
        return FALSE;
    else if (!MetatileBehavior_IsSouthArrowWarp(player->field_C))
        return FALSE;
    else if (player->facing != 1)
        return FALSE;
    else
        return TRUE;
}

static const u8 *TryInteractWithPlayer(struct TradeRoomPlayer *player)
{
    struct MapPosition otherPlayerPos;
    u8 linkPlayerId;

    if (player->c != MOVEMENT_MODE_FREE && player->c != MOVEMENT_MODE_SCRIPTED)
        return FACING_NONE;

    otherPlayerPos = player->pos;
    otherPlayerPos.x += gDirectionToVectors[player->facing].x;
    otherPlayerPos.y += gDirectionToVectors[player->facing].y;
    otherPlayerPos.height = 0;
    linkPlayerId = GetLinkPlayerIdAt(otherPlayerPos.x, otherPlayerPos.y);

    if (linkPlayerId != 4)
    {
        if (!player->isLocalPlayer)
            return gEventScript_TradeRoom_TooBusyToNotice;
        else if (sPlayerTradingStates[linkPlayerId] != PLAYER_TRADING_STATE_IDLE)
            return gEventScript_TradeRoom_TooBusyToNotice;
        else if (!GetLinkTrainerCardColor(linkPlayerId))
            return gEventScript_TradeRoom_ReadTrainerCard_NoColor;
        else
            return gEventScript_TradeRoom_ReadTrainerCard_Normal;
    }

    return GetInteractedLinkPlayerScript(&otherPlayerPos, player->field_C, player->facing);
}

// This returns which direction to force the player to look when one of
// these event scripts runs.
static u16 GetDirectionForEventScript(const u8 *script)
{
    // if (script == EventScript_DoubleBattleColosseum_PlayerSpot0)
    //     return FACING_FORCED_RIGHT;
    // else if (script == EventScript_DoubleBattleColosseum_PlayerSpot1)
    //     return FACING_FORCED_LEFT;
    // else if (script == EventScript_DoubleBattleColosseum_PlayerSpot2)
    //     return FACING_FORCED_RIGHT;
    // else if (script == EventScript_DoubleBattleColosseum_PlayerSpot3)
    //     return FACING_FORCED_LEFT;
    // else if (script == EventScript_RecordCenter_Spot0)
    //     return FACING_FORCED_RIGHT;
    // else if (script == EventScript_RecordCenter_Spot1)
    //     return FACING_FORCED_LEFT;
    // else if (script == EventScript_RecordCenter_Spot2)
    //     return FACING_FORCED_RIGHT;
    // else if (script == EventScript_RecordCenter_Spot3)
    //     return FACING_FORCED_LEFT;
    // else if (script == EventScript_SingleBattleColosseum_PlayerSpot0)
    //     return FACING_FORCED_RIGHT;
    // else if (script == EventScript_SingleBattleColosseum_PlayerSpot1)
    //     return FACING_FORCED_LEFT;
    // else if (script == EventScript_TradeCenter_Chair0)
    //     return FACING_FORCED_RIGHT;
    // else if (script == EventScript_TradeCenter_Chair1)
    //     return FACING_FORCED_LEFT;
    // else
        return FACING_NONE;
}

static void sub_8087510(void)
{
    ScriptContext2_Enable();
}

static void InitLinkRoomStartMenuScript(void)
{
    PlaySE(SE_WIN_OPEN);
    ShowStartMenu();
    ScriptContext2_Enable();
}

static void sub_8087530(const u8 *script)
{
    PlaySE(SE_SELECT);
    ScriptContext1_SetupScript(script);
    ScriptContext2_Enable();
}

static void CreateConfirmLeaveTradeRoomPrompt(void)
{
    PlaySE(SE_WIN_OPEN);
    ScriptContext1_SetupScript(EventScript_ConfirmLeaveTradeRoom);
    ScriptContext2_Enable();
}

static void InitMenuBasedScript(const u8 *script)
{
    PlaySE(SE_SELECT);
    ScriptContext1_SetupScript(script);
    ScriptContext2_Enable();
}

static void sub_8087584(void)
{
    ScriptContext1_SetupScript(EventScript_TerminateLink);
    ScriptContext2_Enable();
}

bool32 sub_8087598(void)
{
    if (!IsUpdateLinkStateCBActive())
        return FALSE;
    if (GetLinkRecvQueueLength() >= 3)
        sUnknown_03000E18 = TRUE;
    else
        sUnknown_03000E18 = FALSE;
    return sUnknown_03000E18;
}

bool32 sub_80875C8(void)
{
    u8 temp;

    if (GetLinkRecvQueueLength() < 2)
        return FALSE;
    else if (IsUpdateLinkStateCBActive() != TRUE)
        return FALSE;
    else if (IsSendingKeysToLink() != TRUE)
        return FALSE;
    else if (sPlayerKeyInterceptCallback == KeyInterCB_DeferToRecvQueue)
        return TRUE;
    else if (sPlayerKeyInterceptCallback != KeyInterCB_DeferToEventScript)
        return FALSE;

    temp = sUnknown_03000E18;
    sUnknown_03000E18 = FALSE;

    if (temp == TRUE)
        return TRUE;
    else if (gPaletteFade.active && gPaletteFade.softwareFadeFinishing)
        return TRUE;
    else
        return FALSE;
}

bool32 sub_8087634(void)
{
    if (GetLinkSendQueueLength() < 2)
        return FALSE;
    else if (IsUpdateLinkStateCBActive() != TRUE)
        return FALSE;
    else if (IsSendingKeysToLink() != TRUE)
        return FALSE;
    else if (sPlayerKeyInterceptCallback == KeyInterCB_DeferToSendQueue)
        return TRUE;
    else
        return FALSE;
}

bool32 sub_808766C(void)
{
    if (gWirelessCommType != 0)
        return FALSE;
    else if (!IsSendingKeysToLink())
        return FALSE;
    else
        return TRUE;
}

static u32 GetLinkSendQueueLength(void)
{
    if (gWirelessCommType != 0)
        return gUnknown_03005000.unk_9e8.unk_232;
    else
        return gLink.sendQueue.count;
}

static void ZeroLinkPlayerEventObject(struct LinkPlayerEventObject *linkPlayerEventObj)
{
    memset(linkPlayerEventObj, 0, sizeof(struct LinkPlayerEventObject));
}

void ClearLinkPlayerEventObjects(void)
{
    memset(gLinkPlayerEventObjects, 0, sizeof(gLinkPlayerEventObjects));
}

static void ZeroEventObject(struct EventObject *eventObj)
{
    memset(eventObj, 0, sizeof(struct EventObject));
}

static void SpawnLinkPlayerEventObject(u8 linkPlayerId, s16 x, s16 y, u8 a4)
{
    u8 eventObjId = GetFirstInactiveEventObjectId();
    struct LinkPlayerEventObject *linkPlayerEventObj = &gLinkPlayerEventObjects[linkPlayerId];
    struct EventObject *eventObj = &gEventObjects[eventObjId];

    ZeroLinkPlayerEventObject(linkPlayerEventObj);
    ZeroEventObject(eventObj);

    linkPlayerEventObj->active = 1;
    linkPlayerEventObj->linkPlayerId = linkPlayerId;
    linkPlayerEventObj->eventObjId = eventObjId;
    linkPlayerEventObj->movementMode = MOVEMENT_MODE_FREE;

    eventObj->active = 1;
    eventObj->singleMovementActive = a4;
    eventObj->range.as_byte = 2;
    eventObj->spriteId = 64;

    InitLinkPlayerEventObjectPos(eventObj, x, y);
}

static void InitLinkPlayerEventObjectPos(struct EventObject *eventObj, s16 x, s16 y)
{
    eventObj->currentCoords.x = x;
    eventObj->currentCoords.y = y;
    eventObj->previousCoords.x = x;
    eventObj->previousCoords.y = y;
    SetSpritePosToMapCoords(x, y, &eventObj->initialCoords.x, &eventObj->initialCoords.y);
    eventObj->initialCoords.x += 8;
    EventObjectUpdateZCoord(eventObj);
}

static void sub_80877DC(u8 linkPlayerId, u8 a2)
{
    if (gLinkPlayerEventObjects[linkPlayerId].active)
    {
        u8 eventObjId = gLinkPlayerEventObjects[linkPlayerId].eventObjId;
        struct EventObject *eventObj = &gEventObjects[eventObjId];
        eventObj->range.as_byte = a2;
    }
}

static void sub_808780C(u8 linkPlayerId)
{
    struct LinkPlayerEventObject *linkPlayerEventObj = &gLinkPlayerEventObjects[linkPlayerId];
    u8 eventObjId = linkPlayerEventObj->eventObjId;
    struct EventObject *eventObj = &gEventObjects[eventObjId];
    if (eventObj->spriteId != MAX_SPRITES)
        DestroySprite(&gSprites[eventObj->spriteId]);
    linkPlayerEventObj->active = 0;
    eventObj->active = 0;
}

// Returns the spriteId corresponding to this player.
static u8 GetSpriteForLinkedPlayer(u8 linkPlayerId)
{
    u8 eventObjId = gLinkPlayerEventObjects[linkPlayerId].eventObjId;
    struct EventObject *eventObj = &gEventObjects[eventObjId];
    return eventObj->spriteId;
}

static void GetLinkPlayerCoords(u8 linkPlayerId, u16 *x, u16 *y)
{
    u8 eventObjId = gLinkPlayerEventObjects[linkPlayerId].eventObjId;
    struct EventObject *eventObj = &gEventObjects[eventObjId];
    *x = eventObj->currentCoords.x;
    *y = eventObj->currentCoords.y;
}

static u8 GetLinkPlayerFacingDirection(u8 linkPlayerId)
{
    u8 eventObjId = gLinkPlayerEventObjects[linkPlayerId].eventObjId;
    struct EventObject *eventObj = &gEventObjects[eventObjId];
    return eventObj->range.as_byte;
}

static u8 GetLinkPlayerElevation(u8 linkPlayerId)
{
    u8 eventObjId = gLinkPlayerEventObjects[linkPlayerId].eventObjId;
    struct EventObject *eventObj = &gEventObjects[eventObjId];
    return eventObj->currentElevation;
}

static s32 sub_80878E4(u8 linkPlayerId)
{
    u8 eventObjId = gLinkPlayerEventObjects[linkPlayerId].eventObjId;
    struct EventObject *eventObj = &gEventObjects[eventObjId];
    return 16 - (s8)eventObj->directionSequenceIndex;
}

static u8 GetLinkPlayerIdAt(s16 x, s16 y)
{
    u8 i;
    for (i = 0; i < 4; i++)
    {
        if (gLinkPlayerEventObjects[i].active
         && (gLinkPlayerEventObjects[i].movementMode == 0 || gLinkPlayerEventObjects[i].movementMode == 2))
        {
            struct EventObject *eventObj = &gEventObjects[gLinkPlayerEventObjects[i].eventObjId];
            if (eventObj->currentCoords.x == x && eventObj->currentCoords.y == y)
                return i;
        }
    }
    return 4;
}

static void SetPlayerFacingDirection(u8 linkPlayerId, u8 facing)
{
    struct LinkPlayerEventObject *linkPlayerEventObj = &gLinkPlayerEventObjects[linkPlayerId];
    u8 eventObjId = linkPlayerEventObj->eventObjId;
    struct EventObject *eventObj = &gEventObjects[eventObjId];

    if (linkPlayerEventObj->active)
    {
        if (facing > FACING_FORCED_RIGHT)
        {
            eventObj->triggerGroundEffectsOnMove = 1;
        }
        else
        {
            // This is a hack to split this code onto two separate lines, without declaring a local variable.
            // C++ style inline variables would be nice here.
            #define TEMP gLinkPlayerMovementModes[linkPlayerEventObj->movementMode](linkPlayerEventObj, eventObj, facing)

            gMovementStatusHandler[TEMP](linkPlayerEventObj, eventObj);
            
            // Clean up the hack.
            #undef TEMP
        }
    }
}


static u8 MovementEventModeCB_Normal(struct LinkPlayerEventObject *linkPlayerEventObj, struct EventObject *eventObj, u8 a3)
{
    return gLinkPlayerFacingHandlers[a3](linkPlayerEventObj, eventObj, a3);
}

static u8 MovementEventModeCB_Ignored(struct LinkPlayerEventObject *linkPlayerEventObj, struct EventObject *eventObj, u8 a3)
{
    return FACING_UP;
}

// Duplicate Function
static u8 MovementEventModeCB_Normal_2(struct LinkPlayerEventObject *linkPlayerEventObj, struct EventObject *eventObj, u8 a3)
{
    return gLinkPlayerFacingHandlers[a3](linkPlayerEventObj, eventObj, a3);
}

static bool8 FacingHandler_DoNothing(struct LinkPlayerEventObject *linkPlayerEventObj, struct EventObject *eventObj, u8 a3)
{
    return FALSE;
}

static bool8 FacingHandler_DpadMovement(struct LinkPlayerEventObject *linkPlayerEventObj, struct EventObject *eventObj, u8 a3)
{
    s16 x, y;

    eventObj->range.as_byte = FlipVerticalAndClearForced(a3, eventObj->range.as_byte);
    EventObjectMoveDestCoords(eventObj, eventObj->range.as_byte, &x, &y);

    if (LinkPlayerDetectCollision(linkPlayerEventObj->eventObjId, eventObj->range.as_byte, x, y))
    {
        return FALSE;
    }
    else
    {
        eventObj->directionSequenceIndex = 16;
        ShiftEventObjectCoords(eventObj, x, y);
        EventObjectUpdateZCoord(eventObj);
        return TRUE;
    }
}

static bool8 FacingHandler_ForcedFacingChange(struct LinkPlayerEventObject *linkPlayerEventObj, struct EventObject *eventObj, u8 a3)
{
    eventObj->range.as_byte = FlipVerticalAndClearForced(a3, eventObj->range.as_byte);
    return FALSE;
}

// This is called every time a free movement happens. Most of the time it's a No-Op.
static void MovementStatusHandler_EnterFreeMode(struct LinkPlayerEventObject *linkPlayerEventObj, struct EventObject *eventObj)
{
    linkPlayerEventObj->movementMode = MOVEMENT_MODE_FREE;
}

static void MovementStatusHandler_TryAdvanceScript(struct LinkPlayerEventObject *linkPlayerEventObj, struct EventObject *eventObj)
{
    eventObj->directionSequenceIndex--;
    linkPlayerEventObj->movementMode = MOVEMENT_MODE_FROZEN;
    MoveCoords(eventObj->range.as_byte, &eventObj->initialCoords.x, &eventObj->initialCoords.y);
    if (!eventObj->directionSequenceIndex)
    {
        ShiftStillEventObjectCoords(eventObj);
        linkPlayerEventObj->movementMode = MOVEMENT_MODE_SCRIPTED;
    }
}

// Flip Up/Down facing codes. If newFacing doesn't specify a direction, default
// to oldFacing. Note that this clears also the "FORCED" part of the facing code,
// even for Left/Right codes.
static u8 FlipVerticalAndClearForced(u8 newFacing, u8 oldFacing)
{
    switch (newFacing)
    {
    case FACING_UP:
    case FACING_FORCED_UP:
        return DIR_NORTH;
    case FACING_DOWN:
    case FACING_FORCED_DOWN:
        return DIR_SOUTH;
    case FACING_LEFT:
    case FACING_FORCED_LEFT:
        return DIR_WEST;
    case FACING_RIGHT:
    case FACING_FORCED_RIGHT:
        return DIR_EAST;
    }
    return oldFacing;
}

static u8 LinkPlayerDetectCollision(u8 selfEventObjId, u8 a2, s16 x, s16 y)
{
    u8 i;
    for (i = 0; i < 16; i++)
    {
        if (i != selfEventObjId)
        {
            if ((gEventObjects[i].currentCoords.x == x && gEventObjects[i].currentCoords.y == y)
             || (gEventObjects[i].previousCoords.x == x && gEventObjects[i].previousCoords.y == y))
            {
                return 1;
            }
        }
    }
    return MapGridIsImpassableAt(x, y);
}

static void CreateLinkPlayerSprite(u8 linkPlayerId, u8 gameVersion)
{
    struct LinkPlayerEventObject *linkPlayerEventObj = &gLinkPlayerEventObjects[linkPlayerId];
    u8 eventObjId = linkPlayerEventObj->eventObjId;
    struct EventObject *eventObj = &gEventObjects[eventObjId];
    struct Sprite *sprite;

    if (linkPlayerEventObj->active)
    {
        switch (gameVersion)
        {
        case VERSION_FIRE_RED:
        case VERSION_LEAF_GREEN:
            eventObj->spriteId = AddPseudoEventObject(GetFRLGAvatarGraphicsIdByGender(eventObj->singleMovementActive), SpriteCB_LinkPlayer, 0, 0, 0);
            break;
        case VERSION_RUBY:
        case VERSION_SAPPHIRE:
            eventObj->spriteId = AddPseudoEventObject(GetRSAvatarGraphicsIdByGender(eventObj->singleMovementActive), SpriteCB_LinkPlayer, 0, 0, 0);
            break;
        case VERSION_EMERALD:
            eventObj->spriteId = AddPseudoEventObject(GetRivalAvatarGraphicsIdByStateIdAndGender(PLAYER_AVATAR_STATE_NORMAL, eventObj->singleMovementActive), SpriteCB_LinkPlayer, 0, 0, 0);
            break;
        }

        sprite = &gSprites[eventObj->spriteId];
        sprite->coordOffsetEnabled = TRUE;
        sprite->data[0] = linkPlayerId;
        eventObj->triggerGroundEffectsOnMove = 0;
    }
}

static void SpriteCB_LinkPlayer(struct Sprite *sprite)
{
    struct LinkPlayerEventObject *linkPlayerEventObj = &gLinkPlayerEventObjects[sprite->data[0]];
    struct EventObject *eventObj = &gEventObjects[linkPlayerEventObj->eventObjId];
    sprite->pos1.x = eventObj->initialCoords.x;
    sprite->pos1.y = eventObj->initialCoords.y;
    SetObjectSubpriorityByZCoord(eventObj->previousElevation, sprite, 1);
    sprite->oam.priority = ZCoordToPriority(eventObj->previousElevation);

    if (!linkPlayerEventObj->movementMode != MOVEMENT_MODE_FREE)
        StartSpriteAnim(sprite, GetFaceDirectionAnimNum(eventObj->range.as_byte));
    else
        StartSpriteAnimIfDifferent(sprite, GetMoveDirectionAnimNum(eventObj->range.as_byte));

    UpdateEventObjectSpriteVisibility(sprite, 0);
    if (eventObj->triggerGroundEffectsOnMove)
    {
        sprite->invisible = ((sprite->data[7] & 4) >> 2);
        sprite->data[7]++;
    }
}
