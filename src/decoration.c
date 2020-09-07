#include "global.h"
#include "alloc.h"
#include "decompress.h"
#include "decoration.h"
#include "decoration_inventory.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "event_scripts.h"
#include "field_camera.h"
#include "field_player_avatar.h"
#include "field_screen_effect.h"
#include "field_weather.h"
#include "fieldmap.h"
#include "graphics.h"
#include "international_string_util.h"
#include "item_icon.h"
#include "list_menu.h"
#include "main.h"
#include "menu.h"
#include "menu_helpers.h"
#include "metatile_behavior.h"
#include "overworld.h"
#include "palette.h"
#include "player_pc.h"
#include "script.h"
#include "secret_base.h"
#include "sound.h"
#include "string_util.h"
#include "strings.h"
#include "task.h"
#include "text.h"
#include "tilesets.h"
#include "trader.h"
#include "tv.h"
#include "constants/decorations.h"
#include "constants/event_objects.h"
#include "constants/songs.h"
#include "constants/region_map_sections.h"
#include "constants/metatile_labels.h"

#define PLACE_DECORATION_SELECTOR_TAG 0xbe5
#define PLACE_DECORATION_PLAYER_TAG   0x008

struct DecorationItemsMenu
{
    struct ListMenuItem items[41];
    u8 names[41][24];
    u8 numMenuItems;
    u8 maxShownItems;
    u8 scrollIndicatorsTaskId;
};

struct PlaceDecorationGraphicsDataBuffer
{
    const struct Decoration *decoration;
    u16 tiles[0x40];
    u8 image[0x800];
    u16 palette[16];
};

struct DecorRearrangementDataBuffer
{
    u8 idx;
    u8 width;
    u8 height;
    u16 flagId;
};

EWRAM_DATA u8 *gCurDecorationItems = NULL;
EWRAM_DATA static u8 sDecorationActionsCursorPos = 0;
EWRAM_DATA static u8 sNumOwnedDecorationsInCurCategory = 0;
EWRAM_DATA static u8 sSecretBaseItemsIndicesBuffer[16] = {};
EWRAM_DATA static u8 sPlayerRoomItemsIndicesBuffer[12] = {};
EWRAM_DATA static u16 sDecorationsCursorPos = 0;
EWRAM_DATA static u16 sDecorationsScrollOffset = 0;
EWRAM_DATA u8 gCurDecorationIndex = 0;
EWRAM_DATA static u8 sCurDecorationCategory = DECORCAT_DESK;
EWRAM_DATA static u32 filler_0203a174[2] = {};
EWRAM_DATA struct DecorationPCContext gDecorationContext = {};
EWRAM_DATA static u8 sDecorMenuWindowIds[4] = {};
EWRAM_DATA static struct DecorationItemsMenu *sDecorationItemsMenu = NULL;
EWRAM_DATA struct PlaceDecorationGraphicsDataBuffer sPlaceDecorationGraphicsDataBuffer = {};
EWRAM_DATA static u16 sCurDecorMapX = 0;
EWRAM_DATA static u16 sCurDecorMapY = 0;
EWRAM_DATA static u8 sDecor_CameraSpriteObjectIdx1 = 0;
EWRAM_DATA static u8 sDecor_CameraSpriteObjectIdx2 = 0;
EWRAM_DATA static u8 sDecorationLastDirectionMoved = 0;
EWRAM_DATA static struct OamData sDecorSelectorOam = {};
EWRAM_DATA static struct DecorRearrangementDataBuffer sDecorRearrangementDataBuffer[16] = {};
EWRAM_DATA static u8 sCurDecorSelectedInRearrangement = 0;

static void HandleDecorationActionsMenuInput(u8 taskId);
static void PrintCurMainMenuDescription(void);
static void DecorationMenuAction_Decorate(u8 taskId);
static void DecorationMenuAction_PutAway(u8 taskId);
static void DecorationMenuAction_Toss(u8 taskId);
static void DecorationMenuAction_Cancel(u8 taskId);
static void ReturnToDecorationActionsAfterInvalidSelection(u8 taskId);
static void SecretBasePC_PrepMenuForSelectingStoredDecors(u8 taskId);
static void InitDecorationCategoriesWindow(u8 taskId);
static void PrintDecorationCategoryMenuItems(u8 taskId);
static void PrintDecorationCategoryMenuItem(u8 winid, u8 category, u8 x, u8 y, bool8 disabled, u8 speed);
static void ColorMenuItemString(u8 *str, bool8 disabled);
static void HandleDecorationCategoriesMenuInput(u8 taskId);
static void SelectDecorationCategory(u8 taskId);
static void ReturnToDecorationCategoriesAfterInvalidSelection(u8 taskId);
static void ExitDecorationCategoriesMenu(u8 taskId);
static void ReturnToActionsMenuFromCategories(u8 taskId);
static void ExitTraderDecorationMenu(u8 taskId);
static void CopyDecorationMenuItemName(u8 *dest, u16 decoration);
static void DecorationItemsMenu_OnCursorMove(s32 itemIndex, bool8 flag, struct ListMenu *menu);
void sub_81274A0(u8 a0, s32 a1, u8 a2);
static void ShowDecorationItemsWindow(u8 taskId);
static void HandleDecorationItemsMenuInput(u8 taskId);
static void PrintDecorationItemDescription(u32 itemIndex);
static void RemoveDecorationItemsOtherWindows(void);
bool8 sub_81277BC(u8 idx);
bool8 sub_81277E8(u8 idx);
static void IdentifyOwnedDecorationsCurrentlyInUse(u8 taskId);
static void InitDecorationItemsWindow(u8 taskId);
static void ShowDecorationCategorySummaryWindow(u8 category);
void sub_8127A30(u8 taskId);
void sub_8127A8C(u8 taskId);
void sub_8127F68(u8 taskId);
void sub_8128060(u8 taskId);
void ConfigureCameraObjectForPlacingDecoration(struct PlaceDecorationGraphicsDataBuffer *data, u8 decor);
void SetUpPlacingDecorationPlayerAvatar(u8 taskId, struct PlaceDecorationGraphicsDataBuffer *data);
void sub_812826C(u8 taskId);
void sub_81283BC(u8 taskId);
void sub_8128414(u8 taskId);
void sub_8128950(u8 taskId);
void sub_81289D0(u8 taskId);
void sub_81289F0(u8 taskId);
void sub_8128AAC(u8 taskId);
void sub_8128B80(u8 taskId);
void sub_8128BA0(u8 taskId);
void sub_8128BBC(u8 taskId);
void c1_overworld_prev_quest(u8 taskId);
void sub_8128CD4(void);
void sub_8128DE0(void);
void sub_8128FD8(u8 taskId);
void sub_8129020(u8 taskId);
void sub_81292D0(struct Sprite *sprite);
void sub_81292E8(struct Sprite *sprite);
u8 gpu_pal_decompress_alloc_tag_and_upload(struct PlaceDecorationGraphicsDataBuffer *data, u8 decor);
const u32 *GetDecorationIconPicOrPalette(u16 decor, u8 mode);
bool8 sub_81299AC(u8 taskId);
void sub_8129ABC(u8 taskId);
void sub_8129B34(u8 taskId);
void sub_8129BCC(u8 taskId);
void sub_8129BF8(u8 taskId);
void sub_8129C74(u8 taskId);
void sub_8129D64(u8 taskId);
void sub_812A0E8(u8 taskId);
void sub_812A1A0(u8 taskId);
void sub_812A1C0(u8 taskId);
void sub_812A1F0(u8 taskId);
void sub_812A210(u8 taskId);
void sub_812A22C(u8 taskId);
void sub_812A25C(u8 taskId);
void sub_812A334(void);
void sub_812A36C(struct Sprite *sprite);
void sub_812A39C(void);
void sub_812A3C8(void);
void sub_812A3D4(u8 taskId);
void sub_812A458(u8 taskId);
void sub_812A478(u8 taskId);

#include "data/decoration/tiles.h"
#include "data/decoration/description.h"
#include "data/decoration/header.h"

static const u8 *const sDecorationCategoryNames[] =
{
    gText_Desk,
    gText_Chair,
    gText_Plant,
    gText_Ornament,
    gText_Mat,
    gText_Poster,
    gText_Doll,
    gText_Cushion
};

static const struct MenuAction sDecorationMainMenuActions[] =
{
    {
        .text = gText_Decorate,
        .func = { .void_u8 = DecorationMenuAction_Decorate },
    },
    {
        .text = gText_PutAway,
        .func = { .void_u8 = DecorationMenuAction_PutAway },
    },
    {
        .text = gText_Toss2,
        .func = { .void_u8 = DecorationMenuAction_Toss },
    },
    {
        .text = gText_Cancel,
        .func = { .void_u8 = DecorationMenuAction_Cancel },
    },
};

static const u8 *const sSecretBasePCMenuItemDescriptions[] =
{
    gText_PutOutSelectedDecorItem,
    gText_StoreChosenDecorInPC,
    gText_ThrowAwayUnwantedDecors,
    gText_GoBackPrevMenu
};

static const TaskFunc sSecretBasePC_SelectedDecorationActions[][2] =
{
   { sub_8127F68, sub_8127A8C },
   { sub_812A3D4, sub_8127A8C },
   { sub_8133DA0, sub_8127A8C },
};

static const struct WindowTemplate sDecorationWindowTemplates[4] =
{
    {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 1,
        .width = 18,
        .height = 8,
        .paletteNum = 15,
        .baseBlock = 0x0001
    },
    {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 1,
        .width = 13,
        .height = 18,
        .paletteNum = 13,
        .baseBlock = 0x0091
    },
    {
        .bg = 0,
        .tilemapLeft = 17,
        .tilemapTop = 1,
        .width = 12,
        .height = 2,
        .paletteNum = 15,
        .baseBlock = 0x017b
    },
    {
        .bg = 0,
        .tilemapLeft = 16,
        .tilemapTop = 13,
        .width = 13,
        .height = 6,
        .paletteNum = 15,
        .baseBlock = 0x0193
    }
};

static const u16 sDecorationMenuPalette[] = INCBIN_U16("graphics/decorations/decoration_menu.gbapal");

static const struct ListMenuTemplate sDecorationItemsListMenuTemplate =
{
    .items = NULL,
    .moveCursorFunc = DecorationItemsMenu_OnCursorMove,
    .itemPrintFunc = sub_81274A0,
    .totalItems = 0,
    .maxShowed = 0,
    .windowId = 0,
    .header_X = 0,
    .item_X = 8,
    .cursor_X = 0,
    .upText_Y = 9,
    .cursorPal = 2,
    .fillValue = 1,
    .cursorShadowPal = 3,
    .lettersSpacing = FALSE,
    .itemVerticalPadding = 0,
    .scrollMultiple = FALSE,
    .fontId = 7
};

#include "data/decoration/icon.h"
#include "data/decoration/tilemaps.h"

static const struct {
    u8 shape;
    u8 size;
    u8 cameraX;
    u8 cameraY;
} sDecorationMovementInfo[] =
{
    [DECORSHAPE_1x1] = {SPRITE_SHAPE(16x16), SPRITE_SIZE(16x16), 120, 78},
    [DECORSHAPE_2x1] = {SPRITE_SHAPE(32x16), SPRITE_SIZE(32x16), 128, 78},
    [DECORSHAPE_3x1] = {SPRITE_SHAPE(64x32), SPRITE_SIZE(64x32), 144, 86},
    [DECORSHAPE_4x2] = {SPRITE_SHAPE(64x32), SPRITE_SIZE(64x32), 144, 70},
    [DECORSHAPE_2x2] = {SPRITE_SHAPE(32x32), SPRITE_SIZE(32x32), 128, 70},
    [DECORSHAPE_1x2] = {SPRITE_SHAPE(16x32), SPRITE_SIZE(16x32), 120, 70},
    [DECORSHAPE_1x3] = {SPRITE_SHAPE(32x64), SPRITE_SIZE(32x64), 128, 86},
    [DECORSHAPE_2x4] = {SPRITE_SHAPE(32x64), SPRITE_SIZE(32x64), 128, 54},
    [DECORSHAPE_3x3] = {SPRITE_SHAPE(64x64), SPRITE_SIZE(64x64), 144, 70},
    [DECORSHAPE_3x2] = {SPRITE_SHAPE(64x32), SPRITE_SIZE(64x32), 144, 70},
};

static const union AnimCmd sDecorSelectorAnimCmd0[] =
{
    ANIMCMD_FRAME(0, 0, FALSE, FALSE),
    ANIMCMD_END
};

static const union AnimCmd *const sDecorSelectorAnimCmds[] = { sDecorSelectorAnimCmd0 };

static const struct SpriteFrameImage sDecorSelectorSpriteFrameImages =
{
    .data = (const u8 *)&sPlaceDecorationGraphicsDataBuffer.image,
    .size = 0x800,
};

static const struct SpriteTemplate sDecorationSelectorSpriteTemplate =
{
    0xFFFF,
    PLACE_DECORATION_SELECTOR_TAG,
    &sDecorSelectorOam,
    sDecorSelectorAnimCmds,
    &sDecorSelectorSpriteFrameImages,
    gDummySpriteAffineAnimTable,
    SpriteCallbackDummy
};

const struct SpriteTemplate sDecorWhilePlacingSpriteTemplate =
{
    0x0000,
    0x0000,
    &sDecorSelectorOam,
    sDecorSelectorAnimCmds,
    NULL,
    gDummySpriteAffineAnimTable,
    SpriteCallbackDummy
};

const struct SpritePalette gUnknown_085A72BC =
{
    .data = (const u16 *)&sPlaceDecorationGraphicsDataBuffer.palette,
    .tag = PLACE_DECORATION_SELECTOR_TAG,
};

const struct YesNoFuncTable gUnknown_085A72C4 =
{
    .yesFunc = sub_81289F0,
    .noFunc = sub_8128FD8,
};

const struct YesNoFuncTable gUnknown_085A72CC =
{
    .yesFunc = sub_8128BA0,
    .noFunc = sub_8128FD8,
};

const struct YesNoFuncTable gUnknown_085A72D4[] =
{
    {
        .yesFunc = sub_81283BC,
        .noFunc = sub_8128414,
    },
    {
        .yesFunc = sub_8129BCC,
        .noFunc = sub_8129BF8,
    }
};

static const u8 sDecorationStandElevations[] =
{
    4, 4, 4, 4,
    0, 3, 3, 0
};

static const u8 sDecorationSlideElevation[] =
{
    4, 4,
    4, 4,
    0, 4,
    3, 0,
};

const u16 gUnknown_085A72F4[] = {
    0x04, 0x08, 0x10, 0x20, 0x10, 0x08, 0x10, 0x20, 0x40, 0x20
};

const u16 gUnknown_085A7308[] = INCBIN_U16("graphics/decorations/unk_85a7308.gbapal");

const u16 gUnknown_085A7328[] = INCBIN_U16("graphics/decorations/unk_85a7328.gbapal");

const struct YesNoFuncTable gUnknown_085A7348 =
{
    .yesFunc = sub_812A1C0,
    .noFunc = sub_8129B34,
};

const struct YesNoFuncTable gUnknown_085A7350 =
{
    .yesFunc = sub_812A210,
    .noFunc = sub_8129B34,
};

const u8 gUnknown_085A7358[] = INCBIN_U8("graphics/misc/decoration_unk_85a7358.4bpp");

const struct SpritePalette gUnknown_085A73D8 =
{
    .data = gUnknown_085A7308,
    .tag = PLACE_DECORATION_PLAYER_TAG,
};

const struct SpritePalette gUnknown_085A73E0 =
{
    .data = gUnknown_085A7328,
    .tag = PLACE_DECORATION_PLAYER_TAG,
};

const struct OamData gUnknown_085A73E8 =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(16x16),
    .x = 0,
    .size = SPRITE_SIZE(16x16),
    .tileNum = 0,
    .priority = 1,
    .paletteNum = 0,
};

const union AnimCmd gUnknown_085A73F0[] =
{
    ANIMCMD_FRAME(0, 0, 0),
    ANIMCMD_END
};

const union AnimCmd *const gUnknown_085A73F8[] =
{
    gUnknown_085A73F0,
};

const struct SpriteFrameImage gUnknown_085A73FC =
{
    .data = gUnknown_085A7358,
    .size = 0x80,
};

const struct SpriteTemplate gUnknown_085A7404 =
{
    0xFFFF,
    PLACE_DECORATION_PLAYER_TAG,
    &gUnknown_085A73E8,
    gUnknown_085A73F8,
    &gUnknown_085A73FC,
    gDummySpriteAffineAnimTable,
    sub_812A36C
};

const struct YesNoFuncTable gUnknown_085A741C =
{
    .yesFunc = sub_812A478,
    .noFunc = sub_8127A30,
};


void InitDecorationContextItems(void)
{
    if (sCurDecorationCategory < DECORCAT_COUNT)
        gCurDecorationItems = gDecorationInventories[sCurDecorationCategory].items;

    if (gDecorationContext.isPlayerRoom == FALSE)
    {
        gDecorationContext.items = gSaveBlock1Ptr->secretBases[0].decorations;
        gDecorationContext.pos = gSaveBlock1Ptr->secretBases[0].decorationPositions;
    }

    if (gDecorationContext.isPlayerRoom == TRUE)
    {
        gDecorationContext.items = gSaveBlock1Ptr->playerRoomDecor;
        gDecorationContext.pos = gSaveBlock1Ptr->playerRoomDecorPos;
    }
}

static u8 AddDecorationWindow(u8 windowIndex)
{
    u8 *windowId;
    struct WindowTemplate template;

    windowId = &sDecorMenuWindowIds[windowIndex];
    if (windowIndex == 0)
    {
        template = sDecorationWindowTemplates[0];
        template.width = GetMaxWidthInMenuTable(sDecorationMainMenuActions, ARRAY_COUNT(sDecorationMainMenuActions));
        if (template.width > 18)
            template.width = 18;

        *windowId = AddWindow(&template);
    }
    else
    {
        *windowId = AddWindow(&sDecorationWindowTemplates[windowIndex]);
    }

    DrawStdFrameWithCustomTileAndPalette(*windowId, FALSE, 0x214, 14);
    schedule_bg_copy_tilemap_to_vram(0);
    return *windowId;
}

static void RemoveDecorationWindow(u8 windowIndex)
{
    ClearStdWindowAndFrameToTransparent(sDecorMenuWindowIds[windowIndex], FALSE);
    ClearWindowTilemap(sDecorMenuWindowIds[windowIndex]);
    RemoveWindow(sDecorMenuWindowIds[windowIndex]);
    schedule_bg_copy_tilemap_to_vram(0);
}

static void AddDecorationActionsWindow(void)
{
    u8 windowId = AddDecorationWindow(0);
    PrintMenuTable(windowId, 4, sDecorationMainMenuActions);
    InitMenuInUpperLeftCornerPlaySoundWhenAPressed(windowId, 4, sDecorationActionsCursorPos);
}

static void InitDecorationActionsWindow(void)
{
    sDecorationActionsCursorPos = 0;
    ScriptContext2_Enable();
    AddDecorationActionsWindow();
    PrintCurMainMenuDescription();
}

void DoSecretBaseDecorationMenu(u8 taskId)
{
    InitDecorationActionsWindow();
    gDecorationContext.items = gSaveBlock1Ptr->secretBases[0].decorations;
    gDecorationContext.pos = gSaveBlock1Ptr->secretBases[0].decorationPositions;
    gDecorationContext.size = sizeof(gSaveBlock1Ptr->secretBases[0].decorations);
    gDecorationContext.isPlayerRoom = FALSE;
    gTasks[taskId].func = HandleDecorationActionsMenuInput;
}

void DoPlayerRoomDecorationMenu(u8 taskId)
{
    InitDecorationActionsWindow();
    gDecorationContext.items = gSaveBlock1Ptr->playerRoomDecor;
    gDecorationContext.pos = gSaveBlock1Ptr->playerRoomDecorPos;
    gDecorationContext.size = sizeof(gSaveBlock1Ptr->playerRoomDecor);
    gDecorationContext.isPlayerRoom = TRUE;
    gTasks[taskId].func = HandleDecorationActionsMenuInput;
}

static void HandleDecorationActionsMenuInput(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        s8 menuPos = Menu_GetCursorPos();
        switch (Menu_ProcessInput())
        {
        default:
            PlaySE(SE_SELECT);
            sDecorationMainMenuActions[sDecorationActionsCursorPos].func.void_u8(taskId);
            break;
        case MENU_NOTHING_CHOSEN:
            sDecorationActionsCursorPos = Menu_GetCursorPos();
            if (menuPos != sDecorationActionsCursorPos)
                PrintCurMainMenuDescription();
            break;
        case MENU_B_PRESSED:
            PlaySE(SE_SELECT);
            DecorationMenuAction_Cancel(taskId);
            break;
        }
    }
}

static void PrintCurMainMenuDescription(void)
{
    FillWindowPixelBuffer(0, PIXEL_FILL(1));
    AddTextPrinterParameterized2(0, 1, sSecretBasePCMenuItemDescriptions[sDecorationActionsCursorPos], 0, 0, 2, 1, 3);
}

static void DecorationMenuAction_Decorate(u8 taskId)
{
    if (GetNumOwnedDecorations() == 0)
    {
        StringExpandPlaceholders(gStringVar4, gText_NoDecorations);
        DisplayItemMessageOnField(taskId, gStringVar4, ReturnToDecorationActionsAfterInvalidSelection);
    }
    else
    {
        gTasks[taskId].data[11] = 0;
        sCurDecorationCategory = DECORCAT_DESK;
        SecretBasePC_PrepMenuForSelectingStoredDecors(taskId);
    }
}

static void DecorationMenuAction_PutAway(u8 taskId)
{
    if (!sub_81299AC(taskId))
    {
        StringExpandPlaceholders(gStringVar4, gText_NoDecorationsInUse);
        DisplayItemMessageOnField(taskId, gStringVar4, ReturnToDecorationActionsAfterInvalidSelection);
    }
    else
    {
        RemoveDecorationWindow(0);
        ClearDialogWindowAndFrame(0, 0);
        FadeScreen(1, 0);
        gTasks[taskId].data[2] = 0;
        gTasks[taskId].func = sub_8129ABC;
    }
}

static void DecorationMenuAction_Toss(u8 taskId)
{
    if (GetNumOwnedDecorations() == 0)
    {
        StringExpandPlaceholders(gStringVar4, gText_NoDecorations);
        DisplayItemMessageOnField(taskId, gStringVar4, ReturnToDecorationActionsAfterInvalidSelection);
    }
    else
    {
        gTasks[taskId].data[11] = 1;
        sCurDecorationCategory = DECORCAT_DESK;
        SecretBasePC_PrepMenuForSelectingStoredDecors(taskId);
    }
}

static void DecorationMenuAction_Cancel(u8 taskId)
{
    RemoveDecorationWindow(0);
    if (!gDecorationContext.isPlayerRoom)
    {
        ScriptContext1_SetupScript(gUnknown_0823B4E8);
        DestroyTask(taskId);
    }
    else
    {
        ReshowPlayerPC(taskId);
    }
}

static void ReturnToDecorationActionsAfterInvalidSelection(u8 taskId)
{
    PrintCurMainMenuDescription();
    gTasks[taskId].func = HandleDecorationActionsMenuInput;
}

static void SecretBasePC_PrepMenuForSelectingStoredDecors(u8 taskId)
{
    LoadPalette(sDecorationMenuPalette, 0xd0, 0x20);
    ClearDialogWindowAndFrame(0, 0);
    RemoveDecorationWindow(0);
    InitDecorationCategoriesWindow(taskId);
}

static void InitDecorationCategoriesWindow(u8 taskId)
{
    u8 windowId = AddDecorationWindow(1);
    PrintDecorationCategoryMenuItems(taskId);
    InitMenuInUpperLeftCornerPlaySoundWhenAPressed(windowId, DECORCAT_COUNT + 1, sCurDecorationCategory);
    gTasks[taskId].func = HandleDecorationCategoriesMenuInput;
}

static void sub_8126E44(u8 taskId)
{
    FillWindowPixelBuffer(sDecorMenuWindowIds[1], PIXEL_FILL(1));
    PrintDecorationCategoryMenuItems(taskId);
    InitMenuInUpperLeftCornerPlaySoundWhenAPressed(sDecorMenuWindowIds[1], DECORCAT_COUNT + 1, sCurDecorationCategory);
    gTasks[taskId].func = HandleDecorationCategoriesMenuInput;
}

static void PrintDecorationCategoryMenuItems(u8 taskId)
{
    u8 i;
    s16 *data = gTasks[taskId].data;
    u8 windowId = sDecorMenuWindowIds[1];
    bool8 isPlayerRoom = gDecorationContext.isPlayerRoom;
    bool8 shouldDisable = FALSE;
    if (isPlayerRoom == TRUE && data[11] == 0)
        shouldDisable = TRUE;

    for (i = 0; i < DECORCAT_COUNT; i++)
    {
        // Only DOLL and CUSHION decorations are enabled when decorating the player's room.
        if (shouldDisable == TRUE && i != DECORCAT_DOLL && i != DECORCAT_CUSHION)
            PrintDecorationCategoryMenuItem(windowId, i, 8, i * 16, TRUE, TEXT_SPEED_FF);
        else
            PrintDecorationCategoryMenuItem(windowId, i, 8, i * 16, FALSE, TEXT_SPEED_FF);
    }

    AddTextPrinterParameterized(windowId, 1, gTasks[taskId].data[11] == 2 ? gText_Exit : gText_Cancel, 8, i * 16 + 1, 0, NULL);
    schedule_bg_copy_tilemap_to_vram(0);
}

static void PrintDecorationCategoryMenuItem(u8 winid, u8 category, u8 x, u8 y, bool8 disabled, u8 speed)
{
    u8 width;
    u8 *str;

    width = x == 8 ? 104 : 96;
    y++;
    ColorMenuItemString(gStringVar4, disabled);
    str = StringLength(gStringVar4) + gStringVar4;
    StringCopy(str, sDecorationCategoryNames[category]);
    AddTextPrinterParameterized(winid, 1, gStringVar4, x, y, speed, NULL);
    str = ConvertIntToDecimalStringN(str, GetNumOwnedDecorationsInCategory(category), STR_CONV_MODE_RIGHT_ALIGN, 2);
    *(str++) = CHAR_SLASH;
    ConvertIntToDecimalStringN(str, gDecorationInventories[category].size, STR_CONV_MODE_RIGHT_ALIGN, 2);
    x = GetStringRightAlignXOffset(1, gStringVar4, width);
    AddTextPrinterParameterized(winid, 1, gStringVar4, x, y, speed, NULL);
}

static void ColorMenuItemString(u8 *str, bool8 disabled)
{
    StringCopy(str, gText_Color161Shadow161);
    if (disabled == TRUE)
    {
        str[2] = 4;
        str[5] = 5;
    }
    else
    {
        str[2] = 2;
        str[5] = 3;
    }
}

static void HandleDecorationCategoriesMenuInput(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        s8 input = Menu_ProcessInput();
        switch (input)
        {
        case MENU_B_PRESSED:
        case DECORCAT_COUNT: // CANCEL
            PlaySE(SE_SELECT);
            ExitDecorationCategoriesMenu(taskId);
            break;
        case MENU_NOTHING_CHOSEN:
            break;
        default:
            PlaySE(SE_SELECT);
            sCurDecorationCategory = input;
            SelectDecorationCategory(taskId);
            break;
        }
    }
}

static void SelectDecorationCategory(u8 taskId)
{
    sNumOwnedDecorationsInCurCategory = GetNumOwnedDecorationsInCategory(sCurDecorationCategory);
    if (sNumOwnedDecorationsInCurCategory != 0)
    {
        CondenseDecorationsInCategory(sCurDecorationCategory);
        gCurDecorationItems = gDecorationInventories[sCurDecorationCategory].items;
        IdentifyOwnedDecorationsCurrentlyInUse(taskId);
        sDecorationsScrollOffset = 0;
        sDecorationsCursorPos = 0;
        gTasks[taskId].func = ShowDecorationItemsWindow;
    }
    else
    {
        RemoveDecorationWindow(1);
        StringExpandPlaceholders(gStringVar4, gText_NoDecorations);
        DisplayItemMessageOnField(taskId, gStringVar4, ReturnToDecorationCategoriesAfterInvalidSelection);
    }
}

static void ReturnToDecorationCategoriesAfterInvalidSelection(u8 taskId)
{
    ClearDialogWindowAndFrame(0, 0);
    InitDecorationCategoriesWindow(taskId);
}

static void ExitDecorationCategoriesMenu(u8 taskId)
{
    if (gTasks[taskId].data[11] != 2)
        ReturnToActionsMenuFromCategories(taskId);
    else
        ExitTraderDecorationMenu(taskId);
}

static void ReturnToActionsMenuFromCategories(u8 taskId)
{
    RemoveDecorationWindow(1);
    AddDecorationActionsWindow();
    DrawDialogueFrame(0, 0);
    PrintCurMainMenuDescription();
    gTasks[taskId].func = HandleDecorationActionsMenuInput;
}

void ShowDecorationCategoriesWindow(u8 taskId)
{
    LoadPalette(sDecorationMenuPalette, 0xd0, 0x20);
    ClearDialogWindowAndFrame(0, 0);
    gTasks[taskId].data[11] = 2;
    sCurDecorationCategory = DECORCAT_DESK;
    InitDecorationCategoriesWindow(taskId);
}

void CopyDecorationCategoryName(u8 *dest, u8 category)
{
    StringCopy(dest, sDecorationCategoryNames[category]);
}

static void ExitTraderDecorationMenu(u8 taskId)
{
    RemoveDecorationWindow(1);
    ExitTraderMenu(taskId);
}

static void InitDecorationItemsMenuLimits(void)
{
    sDecorationItemsMenu->numMenuItems = sNumOwnedDecorationsInCurCategory + 1;
    if (sDecorationItemsMenu->numMenuItems > 8)
        sDecorationItemsMenu->maxShownItems = 8;
    else
        sDecorationItemsMenu->maxShownItems = sDecorationItemsMenu->numMenuItems;
}

static void sub_81272C8(void)
{
    sub_812225C(&sDecorationsScrollOffset, &sDecorationsCursorPos, sDecorationItemsMenu->maxShownItems, sDecorationItemsMenu->numMenuItems);
}

static void sub_81272F8(void)
{
    sub_8122298(&sDecorationsScrollOffset, &sDecorationsCursorPos, sDecorationItemsMenu->maxShownItems, sDecorationItemsMenu->numMenuItems, 8);
}

static void PrintDecorationItemMenuItems(u8 taskId)
{
    s16 *data;
    u16 i;

    data = gTasks[taskId].data;
    if ((sCurDecorationCategory < DECORCAT_DOLL || sCurDecorationCategory > DECORCAT_CUSHION) && gDecorationContext.isPlayerRoom == TRUE && data[11] == 0)
        ColorMenuItemString(gStringVar1, TRUE);
    else
        ColorMenuItemString(gStringVar1, FALSE);

    for (i = 0; i < sDecorationItemsMenu->numMenuItems - 1; i++)
    {
        CopyDecorationMenuItemName(sDecorationItemsMenu->names[i], gCurDecorationItems[i]);
        sDecorationItemsMenu->items[i].name = sDecorationItemsMenu->names[i];
        sDecorationItemsMenu->items[i].id = i;
    }

    StringCopy(sDecorationItemsMenu->names[i], gText_Cancel);
    sDecorationItemsMenu->items[i].name = sDecorationItemsMenu->names[i];
    sDecorationItemsMenu->items[i].id = -2;
    gMultiuseListMenuTemplate = sDecorationItemsListMenuTemplate;
    gMultiuseListMenuTemplate.windowId = sDecorMenuWindowIds[1];
    gMultiuseListMenuTemplate.totalItems = sDecorationItemsMenu->numMenuItems;
    gMultiuseListMenuTemplate.items = sDecorationItemsMenu->items;
    gMultiuseListMenuTemplate.maxShowed = sDecorationItemsMenu->maxShownItems;
}

static void CopyDecorationMenuItemName(u8 *dest, u16 decoration)
{
    StringCopy(dest, gStringVar1);
    StringAppend(dest, gDecorations[decoration].name);
}

static void DecorationItemsMenu_OnCursorMove(s32 itemIndex, bool8 flag, struct ListMenu *menu)
{
    if (flag != TRUE)
        PlaySE(SE_SELECT);

    PrintDecorationItemDescription(itemIndex);
}

void sub_81274A0(u8 a0, s32 a1, u8 a2)
{
    if (a1 != -2)
    {
        if (sub_81277BC(a1 + 1) == TRUE)
        {
            blit_move_info_icon(a0, 0x18, 0x5c, a2 + 2);
        }
        else if (sub_81277E8(a1 + 1) == TRUE)
        {
            blit_move_info_icon(a0, 0x19, 0x5c, a2 + 2);
        }
    }
}

static void AddDecorationItemsScrollIndicators(void)
{
    if (sDecorationItemsMenu->scrollIndicatorsTaskId == 0xFF)
    {
        sDecorationItemsMenu->scrollIndicatorsTaskId = AddScrollIndicatorArrowPairParameterized(
            SCROLL_ARROW_UP,
            0x3c,
            0x0c,
            0x94,
            sDecorationItemsMenu->numMenuItems - sDecorationItemsMenu->maxShownItems,
            0x6e,
            0x6e,
            &sDecorationsScrollOffset);
    }
}

static void RemoveDecorationItemsScrollIndicators(void)
{
    if (sDecorationItemsMenu->scrollIndicatorsTaskId != 0xFF)
    {
        RemoveScrollIndicatorArrowPair(sDecorationItemsMenu->scrollIndicatorsTaskId);
        sDecorationItemsMenu->scrollIndicatorsTaskId = 0xFF;
    }
}

void sub_8127580(u8 taskId)
{
    AddDecorationWindow(1);
    InitDecorationItemsWindow(taskId);
}

static void InitDecorationItemsWindow(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    AddDecorationWindow(3);
    ShowDecorationCategorySummaryWindow(sCurDecorationCategory);
    sDecorationItemsMenu = AllocZeroed(sizeof(*sDecorationItemsMenu));
    sDecorationItemsMenu->scrollIndicatorsTaskId = 0xFF;
    InitDecorationItemsMenuLimits();
    sub_81272C8();
    sub_81272F8();
    PrintDecorationItemMenuItems(taskId);
    data[13] = ListMenuInit(&gMultiuseListMenuTemplate, sDecorationsScrollOffset, sDecorationsCursorPos);
    AddDecorationItemsScrollIndicators();
}

static void ShowDecorationItemsWindow(u8 taskId)
{
    InitDecorationItemsWindow(taskId);
    gTasks[taskId].func = HandleDecorationItemsMenuInput;
}

static void HandleDecorationItemsMenuInput(u8 taskId)
{
    s16 *data;
    s32 input;

    data = gTasks[taskId].data;
    if (!gPaletteFade.active)
    {
        input = ListMenu_ProcessInput(data[13]);
        ListMenuGetScrollAndRow(data[13], &sDecorationsScrollOffset, &sDecorationsCursorPos);
        switch (input)
        {
        case LIST_NOTHING_CHOSEN:
            break;
        case LIST_CANCEL:
            PlaySE(SE_SELECT);
            sSecretBasePC_SelectedDecorationActions[data[11]][1](taskId);
            break;
        default:
            PlaySE(SE_SELECT);
            gCurDecorationIndex = input;
            RemoveDecorationItemsScrollIndicators();
            DestroyListMenuTask(data[13], &sDecorationsScrollOffset, &sDecorationsCursorPos);
            RemoveDecorationWindow(1);
            RemoveDecorationItemsOtherWindows();
            free(sDecorationItemsMenu);
            sSecretBasePC_SelectedDecorationActions[data[11]][0](taskId);
            break;
        }
    }
}

static void ShowDecorationCategorySummaryWindow(u8 category)
{
    PrintDecorationCategoryMenuItem(AddDecorationWindow(2), category, 0, 0, 0, 0);
}

static void PrintDecorationItemDescription(u32 itemIndex)
{
    u8 windowId;
    const u8 *str;

    windowId = sDecorMenuWindowIds[3];
    FillWindowPixelBuffer(windowId, PIXEL_FILL(1));
    if (itemIndex >= sNumOwnedDecorationsInCurCategory)
        str = gText_GoBackPrevMenu;
    else
        str = gDecorations[gCurDecorationItems[itemIndex]].description;

    AddTextPrinterParameterized(windowId, 1, str, 0, 1, 0, 0);
}

static void RemoveDecorationItemsOtherWindows(void)
{
    // Remove description and category summary windows
    RemoveDecorationWindow(3);
    RemoveDecorationWindow(2);
}

bool8 sub_81277BC(u8 idx)
{
    u8 i;
    for (i = 0; i < ARRAY_COUNT(sSecretBaseItemsIndicesBuffer); i++)
    {
        if (sSecretBaseItemsIndicesBuffer[i] == idx)
            return TRUE;
    }

    return FALSE;
}

bool8 sub_81277E8(u8 idx)
{
    u8 i;
    for (i = 0; i < ARRAY_COUNT(sPlayerRoomItemsIndicesBuffer); i++)
    {
        if (sPlayerRoomItemsIndicesBuffer[i] == idx)
            return TRUE;
    }

    return FALSE;
}

static void IdentifyOwnedDecorationsCurrentlyInUseInternal(u8 taskId)
{
    u16 i, j, k;
    u16 count;

    count = 0;
    memset(sSecretBaseItemsIndicesBuffer, 0, sizeof(sSecretBaseItemsIndicesBuffer));
    memset(sPlayerRoomItemsIndicesBuffer, 0, sizeof(sPlayerRoomItemsIndicesBuffer));

    for (i = 0; i < ARRAY_COUNT(sSecretBaseItemsIndicesBuffer); i++)
    {
        if (gSaveBlock1Ptr->secretBases[0].decorations[i] != DECOR_NONE)
        {
            for (j = 0; j < gDecorationInventories[sCurDecorationCategory].size; j++)
            {
                if (gCurDecorationItems[j] == gSaveBlock1Ptr->secretBases[0].decorations[i])
                {
                    for (k = 0; k < count && sSecretBaseItemsIndicesBuffer[k] != j + 1; k++)
                        ;

                    if (k == count)
                    {
                        sSecretBaseItemsIndicesBuffer[count] = j + 1;
                        count++;
                        break;
                    }
                }
            }
        }
    }

    count = 0;
    for (i = 0; i < ARRAY_COUNT(sPlayerRoomItemsIndicesBuffer); i++)
    {
        if (gSaveBlock1Ptr->playerRoomDecor[i] != DECOR_NONE)
        {
            for (j = 0; j < gDecorationInventories[sCurDecorationCategory].size; j++)
            {
                if (gCurDecorationItems[j] == gSaveBlock1Ptr->playerRoomDecor[i] && sub_81277BC(j + 1) != TRUE)
                {
                    for (k = 0; k < count && sPlayerRoomItemsIndicesBuffer[k] != j + 1; k++);
                    if (k == count)
                    {
                        sPlayerRoomItemsIndicesBuffer[count] = j + 1;
                        count++;
                        break;
                    }
                }
            }
        }
    }
}

static void IdentifyOwnedDecorationsCurrentlyInUse(u8 taskId)
{
    IdentifyOwnedDecorationsCurrentlyInUseInternal(taskId);
}

bool8 IsSelectedDecorInThePC(void)
{
    u16 i;
    for (i = 0; i < ARRAY_COUNT(sSecretBaseItemsIndicesBuffer); i++)
    {
        if (sSecretBaseItemsIndicesBuffer[i] == sDecorationsScrollOffset + sDecorationsCursorPos + 1)
            return FALSE;

        if (i < ARRAY_COUNT(sPlayerRoomItemsIndicesBuffer)
         && sPlayerRoomItemsIndicesBuffer[i] == sDecorationsScrollOffset + sDecorationsCursorPos + 1)
        {
            return FALSE;
        }
    }

    return TRUE;
}

static void sub_8127A14(u8 taskId)
{
    AddDecorationWindow(1);
    ShowDecorationItemsWindow(taskId);
}

void sub_8127A30(u8 taskId)
{
    ClearDialogWindowAndFrame(0, 0);
    gTasks[taskId].func = sub_8127A14;
}

void sub_8127A5C(u8 taskId)
{
    if (gMain.newKeys & (A_BUTTON | B_BUTTON))
    {
        ClearDialogWindowAndFrame(0, 0);
        AddDecorationWindow(1);
        ShowDecorationItemsWindow(taskId);
    }
}

void sub_8127A8C(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    RemoveDecorationItemsScrollIndicators();
    RemoveDecorationItemsOtherWindows();
    DestroyListMenuTask(data[13], NULL, NULL);
    free(sDecorationItemsMenu);
    sub_8126E44(taskId);
}

void sub_8127ACC(u8 taskId)
{
    gTasks[taskId].data[3] = gSaveBlock1Ptr->pos.x;
    gTasks[taskId].data[4] = gSaveBlock1Ptr->pos.y;
    PlayerGetDestCoords(&gTasks[taskId].data[0], &gTasks[taskId].data[1]);
}

void sub_8127B04(u8 taskId)
{
    DrawWholeMapView();
    SetWarpDestination(gSaveBlock1Ptr->location.mapGroup, gSaveBlock1Ptr->location.mapNum, -1, gTasks[taskId].data[3], gTasks[taskId].data[4]);
    WarpIntoMap();
}

static u16 GetDecorationElevation(u8 decoration, u8 tileIndex)
{
    u16 elevation = -1;
    switch (decoration)
    {
    case DECOR_STAND:
        elevation = sDecorationStandElevations[tileIndex] << 12;
        return elevation;
    case DECOR_SLIDE:
        elevation = sDecorationSlideElevation[tileIndex] << 12;
        return elevation;
    default:
        return elevation;
    }
}

static void ShowDecorationOnMap_(u16 mapX, u16 mapY, u8 decWidth, u8 decHeight, u16 decoration)
{
    u16 i, j;
    s16 x, y;
    u16 behavior;
    u16 impassableFlag;
    u16 posterSide;
    u16 elevation;

    for (j = 0; j < decHeight; j++)
    {
        y = mapY - decHeight + 1 + j;
        for (i = 0; i < decWidth; i++)
        {
            x = mapX + i;
            behavior = GetBehaviorByMetatileId(0x200 + gDecorations[decoration].tiles[j * decWidth + i]);
            if (MetatileBehavior_IsSecretBaseImpassable(behavior) == TRUE || (gDecorations[decoration].permission != DECORPERM_PASS_FLOOR && (behavior >> 12)))
                impassableFlag = METATILE_COLLISION_MASK;
            else
                impassableFlag = 0;

            if (gDecorations[decoration].permission != DECORPERM_NA_WALL && MetatileBehavior_IsSecretBaseNorthWall(MapGridGetMetatileBehaviorAt(x, y)) == TRUE)
                posterSide = 1;
            else
                posterSide = 0;

            elevation = GetDecorationElevation(gDecorations[decoration].id, j * decWidth + i);
            if (elevation != 0xFFFF)
                MapGridSetMetatileEntryAt(x, y, (gDecorations[decoration].tiles[j * decWidth + i] + (0x200 | posterSide)) | impassableFlag | elevation);
            else
                MapGridSetMetatileIdAt(x, y, (gDecorations[decoration].tiles[j * decWidth + i] + (0x200 | posterSide)) | impassableFlag);
        }
    }
}

void ShowDecorationOnMap(u16 mapX, u16 mapY, u16 decoration)
{
    switch (gDecorations[decoration].shape)
    {
    case DECORSHAPE_1x1:
        ShowDecorationOnMap_(mapX, mapY, 1, 1, decoration);
        break;
    case DECORSHAPE_2x1:
        ShowDecorationOnMap_(mapX, mapY, 2, 1, decoration);
        break;
    case DECORSHAPE_3x1: // unused
        ShowDecorationOnMap_(mapX, mapY, 3, 1, decoration);
        break;
    case DECORSHAPE_4x2:
        ShowDecorationOnMap_(mapX, mapY, 4, 2, decoration);
        break;
    case DECORSHAPE_2x2:
        ShowDecorationOnMap_(mapX, mapY, 2, 2, decoration);
        break;
    case DECORSHAPE_1x2:
        ShowDecorationOnMap_(mapX, mapY, 1, 2, decoration);
        break;
    case DECORSHAPE_1x3: // unused
        ShowDecorationOnMap_(mapX, mapY, 1, 3, decoration);
        break;
    case DECORSHAPE_2x4:
        ShowDecorationOnMap_(mapX, mapY, 2, 4, decoration);
        break;
    case DECORSHAPE_3x3:
        ShowDecorationOnMap_(mapX, mapY, 3, 3, decoration);
        break;
    case DECORSHAPE_3x2:
        ShowDecorationOnMap_(mapX, mapY, 3, 2, decoration);
        break;
    }
}

void sub_8127E18(void)
{
    u8 i;
    u8 j;

    for (i = 0; i < 14; i++)
    {
        if (FlagGet(FLAG_DECORATION_1 + i) == TRUE)
        {
            FlagClear(FLAG_DECORATION_1 + i);
            for (j = 0; j < gMapHeader.events->eventObjectCount; j++)
            {
                if (gMapHeader.events->eventObjects[j].flagId == FLAG_DECORATION_1 + i)
                    break;
            }

            VarSet(
                VAR_OBJ_GFX_ID_0 + (gMapHeader.events->eventObjects[j].graphicsId - EVENT_OBJ_GFX_VAR_0),
                sPlaceDecorationGraphicsDataBuffer.decoration->tiles[0]);

            gSpecialVar_0x8005 = gMapHeader.events->eventObjects[j].localId;
            gSpecialVar_0x8006 = sCurDecorMapX;
            gSpecialVar_0x8007 = sCurDecorMapY;
            TrySpawnEventObject(gSpecialVar_0x8005, gSaveBlock1Ptr->location.mapNum, gSaveBlock1Ptr->location.mapGroup);
            TryMoveEventObjectToMapCoords(gSpecialVar_0x8005, gSaveBlock1Ptr->location.mapNum, gSaveBlock1Ptr->location.mapGroup, gSpecialVar_0x8006, gSpecialVar_0x8007);
            TryOverrideEventObjectTemplateCoords(gSpecialVar_0x8005, gSaveBlock1Ptr->location.mapNum, gSaveBlock1Ptr->location.mapGroup);
            break;
        }
    }
}

bool8 sub_8127F38(void)
{
    u16 i;

    for (i = 0; i < gDecorationContext.size; i++)
    {
        if (gDecorationContext.items[i] == DECOR_NONE)
        {
            return TRUE;
        }
    }
    return FALSE;
}

void sub_8127F68(u8 taskId)
{
    if (gDecorationContext.isPlayerRoom == TRUE && sCurDecorationCategory != DECORCAT_DOLL && sCurDecorationCategory != DECORCAT_CUSHION)
    {
        StringExpandPlaceholders(gStringVar4, gText_CantPlaceInRoom);
        DisplayItemMessageOnField(taskId, gStringVar4, sub_8127A5C);
    }
    else if (IsSelectedDecorInThePC() == TRUE)
    {
        if (sub_8127F38() == TRUE)
        {
            FadeScreen(1, 0);
            gTasks[taskId].data[2] = 0;
            gTasks[taskId].func = sub_8128060;
        }
        else
        {
            ConvertIntToDecimalStringN(gStringVar1, gDecorationContext.size, STR_CONV_MODE_RIGHT_ALIGN, 2);
            if (gDecorationContext.isPlayerRoom == FALSE) {
                StringExpandPlaceholders(gStringVar4, gText_NoMoreDecorations);
            }
            else
            {
                StringExpandPlaceholders(gStringVar4, gText_NoMoreDecorations2);
            }
            DisplayItemMessageOnField(taskId, gStringVar4, sub_8127A5C);
        }
    }
    else
    {
        StringExpandPlaceholders(gStringVar4, gText_InUseAlready);
        DisplayItemMessageOnField(taskId, gStringVar4, sub_8127A5C);
    }
}

void sub_8128060(u8 taskId)
{
    switch (gTasks[taskId].data[2])
    {
        case 0:
            if (!gPaletteFade.active)
            {
                sub_8127ACC(taskId);
                gTasks[taskId].data[2] = 1;
            }
            break;
        case 1:
            gPaletteFade.bufferTransferDisabled = TRUE;
            ConfigureCameraObjectForPlacingDecoration(&sPlaceDecorationGraphicsDataBuffer, gCurDecorationItems[gCurDecorationIndex]);
            sub_812826C(taskId);
            SetUpPlacingDecorationPlayerAvatar(taskId, &sPlaceDecorationGraphicsDataBuffer);
            FadeInFromBlack();
            gPaletteFade.bufferTransferDisabled = FALSE;
            gTasks[taskId].data[2] = 2;
            break;
        case 2:
            if (IsWeatherNotFadingIn() == TRUE)
            {
                gTasks[taskId].data[12] = 0;
                sub_8128FD8(taskId);
            }
            break;
    }
}

void ConfigureCameraObjectForPlacingDecoration(struct PlaceDecorationGraphicsDataBuffer *data, u8 decor)
{
    sDecor_CameraSpriteObjectIdx1 = gSprites[gFieldCamera.spriteId].data[0];
    gFieldCamera.spriteId = gpu_pal_decompress_alloc_tag_and_upload(data, decor);
    gSprites[gFieldCamera.spriteId].oam.priority = 1;
    gSprites[gFieldCamera.spriteId].callback = sub_81292D0;
    gSprites[gFieldCamera.spriteId].pos1.x = sDecorationMovementInfo[data->decoration->shape].cameraX;
    gSprites[gFieldCamera.spriteId].pos1.y = sDecorationMovementInfo[data->decoration->shape].cameraY;
}

void SetUpPlacingDecorationPlayerAvatar(u8 taskId, struct PlaceDecorationGraphicsDataBuffer *data)
{
    u8 x;

    x = 16 * (u8)gTasks[taskId].data[5] + sDecorationMovementInfo[data->decoration->shape].cameraX - 8 * ((u8)gTasks[taskId].data[5] - 1);
    if (data->decoration->shape == DECORSHAPE_3x1 || data->decoration->shape == DECORSHAPE_3x3 || data->decoration->shape == DECORSHAPE_3x2)
        x -= 8;

    switch (gSaveBlock2Ptr->playerGender) {
        default:
        case GENDER_M: 
            sDecor_CameraSpriteObjectIdx2 = AddPseudoEventObject(EVENT_OBJ_GFX_BRENDAN_DECORATING, SpriteCallbackDummy, x, 72, 0);
            break;
        case GENDER_F:
            sDecor_CameraSpriteObjectIdx2 = AddPseudoEventObject(EVENT_OBJ_GFX_MAY_DECORATING, SpriteCallbackDummy, x, 72, 0);
            break;
        case GENDER_N: 
            sDecor_CameraSpriteObjectIdx2 = AddPseudoEventObject(EVENT_OBJ_GFX_TREEKID_DECORATING, SpriteCallbackDummy, x, 72, 0);
            break;
    }

    gSprites[sDecor_CameraSpriteObjectIdx2].oam.priority = 1;
    DestroySprite(&gSprites[sDecor_CameraSpriteObjectIdx1]);
    sDecor_CameraSpriteObjectIdx1 = gFieldCamera.spriteId;
}

void sub_812826C(u8 taskId)
{
    switch (gDecorations[gCurDecorationItems[gCurDecorationIndex]].shape)
    {
        case DECORSHAPE_1x1:
            gTasks[taskId].data[5] = 1;
            gTasks[taskId].data[6] = 1;
            break;
        case DECORSHAPE_2x1:
            gTasks[taskId].data[5] = 2;
            gTasks[taskId].data[6] = 1;
            break;
        case DECORSHAPE_3x1:
            gTasks[taskId].data[5] = 3;
            gTasks[taskId].data[6] = 1;
            break;
        case DECORSHAPE_4x2:
            gTasks[taskId].data[5] = 4;
            gTasks[taskId].data[6] = 2;
            break;
        case DECORSHAPE_2x2:
            gTasks[taskId].data[5] = 2;
            gTasks[taskId].data[6] = 2;
            break;
        case DECORSHAPE_1x2:
            gTasks[taskId].data[5] = 1;
            gTasks[taskId].data[6] = 2;
            break;
        case DECORSHAPE_1x3:
            gTasks[taskId].data[5] = 1;
            gTasks[taskId].data[6] = 3;
            gTasks[taskId].data[1]++;
            break;
        case DECORSHAPE_2x4:
            gTasks[taskId].data[5] = 2;
            gTasks[taskId].data[6] = 4;
            break;
        case DECORSHAPE_3x3:
            gTasks[taskId].data[5] = 3;
            gTasks[taskId].data[6] = 3;
            break;
        case DECORSHAPE_3x2:
            gTasks[taskId].data[5] = 3;
            gTasks[taskId].data[6] = 2;
            break;
    }
}

void sub_81283BC(u8 taskId)
{
    gTasks[taskId].data[10] = 0;
    gSprites[sDecor_CameraSpriteObjectIdx1].data[7] = 1;
    gSprites[sDecor_CameraSpriteObjectIdx2].data[7] = 1;
    sub_8128DE0();
    sub_8128950(taskId);
}

void sub_8128414(u8 taskId)
{
    gTasks[taskId].data[10] = 0;
    gSprites[sDecor_CameraSpriteObjectIdx1].data[7] = 1;
    gSprites[sDecor_CameraSpriteObjectIdx2].data[7] = 1;
    sub_8128DE0();
    StringExpandPlaceholders(gStringVar4, gText_CancelDecorating);
    DisplayItemMessageOnField(taskId, gStringVar4, sub_8128B80);
}

bool8 sub_8128484(u8 behaviorAt, u16 behaviorBy)
{
    if (MetatileBehavior_IsBlockDecoration(behaviorAt) != TRUE || behaviorBy != 0)
    {
        return FALSE;
    }
    return TRUE;
}

bool8 sub_81284AC(u8 taskId, s16 x, s16 y, u16 decor)
{
    if (x == gTasks[taskId].data[3] + 7 && y == gTasks[taskId].data[4] + 7 && decor != DECOR_NONE)
    {
        return FALSE;
    }
    return TRUE;
}

bool8 sub_81284F4(u16 behaviorAt, const struct Decoration *decoration)
{
    if (MetatileBehavior_IsBlockDecoration(behaviorAt) != TRUE)
    {
        if (decoration->id == DECOR_SOLID_BOARD && MetatileBehavior_IsSecretBaseHole(behaviorAt) == TRUE)
            return TRUE;

        if (MetatileBehavior_IsNormal(behaviorAt))
            return TRUE;
    }

    return FALSE;
}

bool8 sub_812853C(u8 taskId, const struct Decoration *decoration)
{
    u8 i;
    u8 j;
    u8 behaviorAt;
    u16 behaviorBy;
    u8 mapY;
    u8 mapX;
    s16 curY;
    s16 curX;
    mapY = gTasks[taskId].data[6];
    mapX = gTasks[taskId].data[5];

    switch (decoration->permission)
    {
    case DECORPERM_SOLID_FLOOR:
    case DECORPERM_PASS_FLOOR:
        for (i = 0; i < mapY; i++)
        {
            curY = gTasks[taskId].data[1] - i;
            for (j = 0; j < mapX; j++)
            {
                curX = gTasks[taskId].data[0] + j;
                behaviorAt = MapGridGetMetatileBehaviorAt(curX, curY);
                behaviorBy = GetBehaviorByMetatileId(0x200 + decoration->tiles[(mapY - 1 - i) * mapX + j]) & METATILE_ELEVATION_MASK;
                if (!sub_81284F4(behaviorAt, decoration))
                    return FALSE;

                if (!sub_81284AC(taskId, curX, curY, behaviorBy))
                    return FALSE;

                behaviorAt = GetEventObjectIdByXYZ(curX, curY, 0);
                if (behaviorAt != 0 && behaviorAt != 16)
                    return FALSE;
            }
        }
        break;
    case DECORPERM_BEHIND_FLOOR:
        for (i = 0; i < mapY - 1; i++)
        {
            curY = gTasks[taskId].data[1] - i;
            for (j = 0; j < mapX; j++)
            {
                curX = gTasks[taskId].data[0] + j;
                behaviorAt = MapGridGetMetatileBehaviorAt(curX, curY);
                behaviorBy = GetBehaviorByMetatileId(0x200 + decoration->tiles[(mapY - 1 - i) * mapX + j]) & METATILE_ELEVATION_MASK;
                if (!MetatileBehavior_IsNormal(behaviorAt) && !sub_8128484(behaviorAt, behaviorBy))
                    return FALSE;

                if (!sub_81284AC(taskId, curX, curY, behaviorBy))
                    return FALSE;

                if (GetEventObjectIdByXYZ(curX, curY, 0) != 16)
                    return FALSE;
            }
        }

        curY = gTasks[taskId].data[1] - mapY + 1;
        for (j = 0; j < mapX; j++)
        {
            curX = gTasks[taskId].data[0] + j;
            behaviorAt = MapGridGetMetatileBehaviorAt(curX, curY);
            behaviorBy = GetBehaviorByMetatileId(0x200 + decoration->tiles[j]) & METATILE_ELEVATION_MASK;
            if (!MetatileBehavior_IsNormal(behaviorAt) && !MetatileBehavior_IsSecretBaseNorthWall(behaviorAt))
                return FALSE;

            if (!sub_81284AC(taskId, curX, curY, behaviorBy))
                return FALSE;

            behaviorAt = GetEventObjectIdByXYZ(curX, curY, 0);
            if (behaviorAt != 0 && behaviorAt != 16)
                return FALSE;
        }
        break;
    case DECORPERM_NA_WALL:
        for (i = 0; i < mapY; i++)
        {
            curY = gTasks[taskId].data[1] - i;
            for (j = 0; j < mapX; j++)
            {
                curX = gTasks[taskId].data[0] + j;
                if (!MetatileBehavior_IsSecretBaseNorthWall(MapGridGetMetatileBehaviorAt(curX, curY)))
                    return FALSE;

                if (MapGridGetMetatileIdAt(curX, curY + 1) == 0x28c)
                    return FALSE;
            }
        }
        break;
    case DECORPERM_SPRITE:
        curY = gTasks[taskId].data[1];
        for (j = 0; j < mapX; j++)
        {
            curX = gTasks[taskId].data[0] + j;
            behaviorAt = MapGridGetMetatileBehaviorAt(curX, curY);
            if (decoration->shape == DECORSHAPE_1x2)
            {
                if (!MetatileBehavior_HoldsLargeDecoration(behaviorAt))
                    return FALSE;
            }
            else if (!MetatileBehavior_HoldsSmallDecoration(behaviorAt))
            {
                if (!MetatileBehavior_HoldsLargeDecoration(behaviorAt))
                    return FALSE;
            }

            if (GetEventObjectIdByXYZ(curX, curY, 0) != 16)
                return FALSE;
        }
        break;
    }
    return TRUE;
}

void sub_8128950(u8 taskId)
{
    if (sub_812853C(taskId, &gDecorations[gCurDecorationItems[gCurDecorationIndex]]) == TRUE)
    {
        StringExpandPlaceholders(gStringVar4, gText_PlaceItHere);
        DisplayItemMessageOnField(taskId, gStringVar4, sub_81289D0);
    }
    else
    {
        PlaySE(SE_HAZURE);
        StringExpandPlaceholders(gStringVar4, gText_CantBePlacedHere);
        DisplayItemMessageOnField(taskId, gStringVar4, sub_8129020);
    }
}

void sub_81289D0(u8 taskId)
{
    DisplayYesNoMenuDefaultYes();
    DoYesNoFuncWithChoice(taskId, &gUnknown_085A72C4);
}

void sub_81289F0(u8 taskId)
{
    ClearDialogWindowAndFrame(0, 0);
    sub_8128AAC(taskId);
    if (gDecorations[gCurDecorationItems[gCurDecorationIndex]].permission != DECORPERM_SPRITE)
    {
        ShowDecorationOnMap(gTasks[taskId].data[0], gTasks[taskId].data[1], gCurDecorationItems[gCurDecorationIndex]);
    }
    else
    {
        sCurDecorMapX = gTasks[taskId].data[0] - 7;
        sCurDecorMapY = gTasks[taskId].data[1] - 7;
        ScriptContext1_SetupScript(EventScript_275D1F);
    }

    gSprites[sDecor_CameraSpriteObjectIdx1].pos1.y += 2;
    if (gMapHeader.regionMapSectionId == MAPSEC_SECRET_BASE)
        TV_PutSecretBaseVisitOnTheAir();

    sub_8128BBC(taskId);
}

void sub_8128AAC(u8 taskId)
{
    u16 i;

    for (i = 0; i < gDecorationContext.size; i++)
    {
        if (gDecorationContext.items[i] == DECOR_NONE)
        {
            gDecorationContext.items[i] = gCurDecorationItems[gCurDecorationIndex];
            gDecorationContext.pos[i] = ((gTasks[taskId].data[0] - 7) << 4) + (gTasks[taskId].data[1] - 7);
            break;
        }
    }

    if (!gDecorationContext.isPlayerRoom)
    {
        for (i = 0; i < 16; i++)
        {
            if (sSecretBaseItemsIndicesBuffer[i] == 0)
            {
                sSecretBaseItemsIndicesBuffer[i] = gCurDecorationIndex + 1;
                break;
            }
        }
    }
    else
    {
        for (i = 0; i < 12; i++)
        {
            if (sPlayerRoomItemsIndicesBuffer[i] == 0)
            {
                sPlayerRoomItemsIndicesBuffer[i] = gCurDecorationIndex + 1;
                break;
            }
        }
    }
}

void sub_8128B80(u8 taskId)
{
    DisplayYesNoMenuDefaultYes();
    DoYesNoFuncWithChoice(taskId, &gUnknown_085A72CC);
}

void sub_8128BA0(u8 taskId)
{
    ClearDialogWindowAndFrame(0, 0);
    sub_8128BBC(taskId);
}

void sub_8128BBC(u8 taskId)
{
    FadeScreen(1, 0);
    gTasks[taskId].data[2] = 0;
    gTasks[taskId].func = c1_overworld_prev_quest;
}

void c1_overworld_prev_quest(u8 taskId)
{
    switch (gTasks[taskId].data[2])
    {
    case 0:
        ScriptContext2_Enable();
        if (!gPaletteFade.active)
        {
            sub_8127B04(taskId);
            gTasks[taskId].data[2] = 1;
        }
        break;
    case 1:
        sub_812A3C8();
        FreeSpritePaletteByTag(PLACE_DECORATION_SELECTOR_TAG);
        gFieldCallback = sub_8128CD4;
        SetMainCallback2(CB2_ReturnToField);
        DestroyTask(taskId);
        break;
    }
}

void sub_8128C64(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    switch (data[2])
    {
    case 0:
        HideSecretBaseDecorationSprites();
        data[2]++;
        break;
    case 1:
        ScriptContext1_SetupScript(EventScript_275D0C);
        data[2]++;
        break;
    case 2:
        ScriptContext2_Enable();
        data[2]++;
        break;
    case 3:
        if (IsWeatherNotFadingIn() == TRUE)
            gTasks[taskId].func = HandleDecorationItemsMenuInput;
        break;
    }
}

void sub_8128CD4(void)
{
    u8 taskId;

    ScriptContext2_Enable();
    FadeInFromBlack();
    taskId = CreateTask(sub_8128C64, 8);
    sub_8127580(taskId);
    gTasks[taskId].data[2] = 0;
}

bool8 sub_8128D10(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    if (sDecorationLastDirectionMoved == DIR_SOUTH && data[1] - data[6] - 6 < 0)
    {
        data[1]++;
        return FALSE;
    }

    if (sDecorationLastDirectionMoved == DIR_NORTH && data[1] - 7 >= gMapHeader.mapLayout->height)
    {
        data[1]--;
        return FALSE;
    }

    if (sDecorationLastDirectionMoved == DIR_WEST && data[0] - 7 < 0)
    {
        data[0]++;
        return FALSE;
    }

    if (sDecorationLastDirectionMoved == DIR_EAST && data[0] + data[5] - 8 >= gMapHeader.mapLayout->width)
    {
        data[0]--;
        return FALSE;
    }

    return TRUE;
}

bool8 sub_8128DB4(void)
{
    u16 heldKeys = gMain.heldKeys & DPAD_ANY;
    if (heldKeys != DPAD_UP && heldKeys != DPAD_DOWN && heldKeys != DPAD_LEFT && heldKeys != DPAD_RIGHT)
        return FALSE;

    return TRUE;
}

void sub_8128DE0(void)
{
    sDecorationLastDirectionMoved = 0;
    gSprites[sDecor_CameraSpriteObjectIdx1].data[2] = 0;
    gSprites[sDecor_CameraSpriteObjectIdx1].data[3] = 0;
}

void sub_8128E18(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    if (!gSprites[sDecor_CameraSpriteObjectIdx1].data[4])
    {
        if (data[10] == 1)
        {
            gUnknown_085A72D4[data[12]].yesFunc(taskId);
            return;
        }
        else if (data[10] == 2)
        {
            gUnknown_085A72D4[data[12]].noFunc(taskId);
            return;
        }

        if ((gMain.heldKeys & DPAD_ANY) == DPAD_UP)
        {
            sDecorationLastDirectionMoved = DIR_SOUTH;
            gSprites[sDecor_CameraSpriteObjectIdx1].data[2] =  0;
            gSprites[sDecor_CameraSpriteObjectIdx1].data[3] = -2;
            data[1]--;
        }

        if ((gMain.heldKeys & DPAD_ANY) == DPAD_DOWN)
        {
            sDecorationLastDirectionMoved = DIR_NORTH;
            gSprites[sDecor_CameraSpriteObjectIdx1].data[2] =  0;
            gSprites[sDecor_CameraSpriteObjectIdx1].data[3] =  2;
            data[1]++;
        }

        if ((gMain.heldKeys & DPAD_ANY) == DPAD_LEFT)
        {
            sDecorationLastDirectionMoved = DIR_WEST;
            gSprites[sDecor_CameraSpriteObjectIdx1].data[2] = -2;
            gSprites[sDecor_CameraSpriteObjectIdx1].data[3] =  0;
            data[0]--;
        }

        if ((gMain.heldKeys & DPAD_ANY) == DPAD_RIGHT)
        {
            sDecorationLastDirectionMoved = DIR_EAST;
            gSprites[sDecor_CameraSpriteObjectIdx1].data[2] =  2;
            gSprites[sDecor_CameraSpriteObjectIdx1].data[3] =  0;
            data[0]++;
        }

        if (!sub_8128DB4() || !sub_8128D10(taskId))
            sub_8128DE0();
    }

    if (sDecorationLastDirectionMoved)
    {
        gSprites[sDecor_CameraSpriteObjectIdx1].data[4]++;
        gSprites[sDecor_CameraSpriteObjectIdx1].data[4] &= 7;
    }

    if (!data[10])
    {
        if (gMain.newKeys & A_BUTTON)
            data[10] = A_BUTTON;

        if (gMain.newKeys & B_BUTTON)
            data[10] = B_BUTTON;
    }
}

void sub_8128FD8(u8 taskId)
{
    ClearDialogWindowAndFrame(0, 1);
    gSprites[sDecor_CameraSpriteObjectIdx1].data[7] = 0;
    gTasks[taskId].data[10] = 0;
    gTasks[taskId].func = sub_8128E18;
}

void sub_8129020(u8 taskId)
{
    if (gMain.newKeys & A_BUTTON || gMain.newKeys & B_BUTTON)
        sub_8128FD8(taskId);
}

void sub_8129048(struct PlaceDecorationGraphicsDataBuffer *data)
{
    CpuFill16(0, data, sizeof(*data));
}

void sub_8129068(u16 *dest, u16 pal)
{
    CpuFastCopy(&((u16 *)gTilesetPointer_SecretBase->palettes)[pal << 4], dest, 32);
}

void sub_8129088(u8 *dest, u16 tile)
{
    u8 buffer[32];
    u16 mode;
    u16 i;

    mode = tile >> 10;
    if (tile != 0)
        tile &= 0x03FF;

    CpuFastCopy(&((u8 *)gTilesetPointer_SecretBase->tiles)[tile << 5], buffer, 32);
    switch (mode)
    {
    case 0:
        CpuFastCopy(buffer, dest, 32);
        break;
    case 1:
        for (i = 0; i < 8; i++)
        {
            dest[4 * i] = (buffer[4 * (i + 1) - 1] >> 4) + ((buffer[4 * (i + 1) - 1] & 0x0F) << 4);
            dest[4 * i + 1] = (buffer[4 * (i + 1) - 2] >> 4) + ((buffer[4 * (i + 1) - 2] & 0x0F) << 4);
            dest[4 * i + 2] = (buffer[4 * (i + 1) - 3] >> 4) + ((buffer[4 * (i + 1) - 3] & 0x0F) << 4);
            dest[4 * i + 3] = (buffer[4 * (i + 1) - 4] >> 4) + ((buffer[4 * (i + 1) - 4] & 0x0F) << 4);
        }
        break;
    case 2:
        for (i = 0; i < 8; i++)
        {
            dest[4 * i] = buffer[4 * (7 - i)];
            dest[4 * i + 1] = buffer[4 * (7 - i) + 1];
            dest[4 * i + 2] = buffer[4 * (7 - i) + 2];
            dest[4 * i + 3] = buffer[4 * (7 - i) + 3];
        }
        break;
    case 3:
        for (i = 0; i < 32; i++)
        {
            dest[i] = (buffer[31 - i] >> 4) + ((buffer[31 - i] & 0x0F) << 4);
        }
        break;
    }
}

void sub_81291A4(struct PlaceDecorationGraphicsDataBuffer *data)
{
    u16 i;
    for (i = 0; i < 64; i++)
        sub_8129088(&data->image[i * 32], data->tiles[i]);
}

u16 sub_81291CC(u16 tile)
{
    return ((u16 *)gTilesetPointer_SecretBaseRedCave->metatiles)[tile] & 0xFFF;
}

void sub_81291E8(struct PlaceDecorationGraphicsDataBuffer *data)
{
    u8 i;
    u8 shape;

    shape = data->decoration->shape;
    for (i = 0; i < gUnknown_085A71B0[shape].size; i++)
    {
        data->tiles[gUnknown_085A71B0[shape].tiles[i]] = sub_81291CC(data->decoration->tiles[gUnknown_085A71B0[shape].y[i]] * 8 + gUnknown_085A71B0[shape].x[i]);
    }
}

void SetDecorSelectionBoxOamAttributes(u8 decorShape)
{
    sDecorSelectorOam.y = 0;
    sDecorSelectorOam.affineMode = ST_OAM_AFFINE_OFF;
    sDecorSelectorOam.objMode = ST_OAM_OBJ_NORMAL;
    sDecorSelectorOam.mosaic = 0;
    sDecorSelectorOam.bpp = ST_OAM_4BPP;
    sDecorSelectorOam.shape = sDecorationMovementInfo[decorShape].shape;
    sDecorSelectorOam.x = 0;
    sDecorSelectorOam.matrixNum = 0;
    sDecorSelectorOam.size = sDecorationMovementInfo[decorShape].size;
    sDecorSelectorOam.tileNum = 0;
    sDecorSelectorOam.priority = 0;
    sDecorSelectorOam.paletteNum = 0;
}

void sub_81292D0(struct Sprite *sprite)
{
    sprite->data[2] = 0;
    sprite->data[3] = 0;
    sprite->data[4] = 0;
    sprite->data[5] = 0;
    sprite->data[6] = 0;
    sprite->data[7] = 0;
    sprite->callback = sub_81292E8;
}

void sub_81292E8(struct Sprite *sprite)
{
    if (sprite->data[7] == 0)
    {
        if (sprite->data[6] < 15)
            sprite->invisible = 0;
        else
            sprite->invisible = 1;

        sprite->data[6]++;
        sprite->data[6] &= 0x1F;
    }
    else
    {
        sprite->invisible = FALSE;
    }
}

u8 gpu_pal_decompress_alloc_tag_and_upload(struct PlaceDecorationGraphicsDataBuffer *data, u8 decor)
{
    sub_8129048(data);
    data->decoration = &gDecorations[decor];
    if (data->decoration->permission == DECORPERM_SPRITE)
        return AddPseudoEventObject(data->decoration->tiles[0], SpriteCallbackDummy, 0, 0, 1);

    FreeSpritePaletteByTag(PLACE_DECORATION_SELECTOR_TAG);
    sub_81291E8(data);
    SetDecorSelectionBoxOamAttributes(data->decoration->shape);
    sub_81291A4(data);
    sub_8129068(data->palette, ((u16 *)gTilesetPointer_SecretBaseRedCave->metatiles)[(data->decoration->tiles[0] * 8) + 7] >> 12);
    LoadSpritePalette(&gUnknown_085A72BC);
    return CreateSprite(&sDecorationSelectorSpriteTemplate, 0, 0, 0);
}

u8 AddDecorationIconObjectFromIconTable(u16 tilesTag, u16 paletteTag, u8 decor)
{
    struct SpriteSheet sheet;
    struct CompressedSpritePalette palette;
    struct SpriteTemplate *template;
    u8 spriteId;

    if (!AllocItemIconTemporaryBuffers())
        return MAX_SPRITES;

    LZDecompressWram(GetDecorationIconPicOrPalette(decor, 0), gItemIconDecompressionBuffer);
    CopyItemIconPicTo4x4Buffer(gItemIconDecompressionBuffer, gItemIcon4x4Buffer);
    sheet.data = gItemIcon4x4Buffer;
    sheet.size = 0x200;
    sheet.tag = tilesTag;
    LoadSpriteSheet(&sheet);
    palette.data = GetDecorationIconPicOrPalette(decor, 1);
    palette.tag = paletteTag;
    LoadCompressedSpritePalette(&palette);
    template = malloc(sizeof(struct SpriteTemplate));
    *template = gItemIconSpriteTemplate;
    template->tileTag = tilesTag;
    template->paletteTag = paletteTag;
    spriteId = CreateSprite(template, 0, 0, 0);
    FreeItemIconTemporaryBuffers();
    free(template);
    return spriteId;
}

const u32 *GetDecorationIconPicOrPalette(u16 decor, u8 mode)
{
    if (decor > NUM_DECORATIONS)
        decor = DECOR_NONE;

    return gUnknown_085A6BE8[decor][mode];
}

u8 AddDecorationIconObjectFromEventObject(u16 tilesTag, u16 paletteTag, u8 decor)
{
    u8 spriteId;
    struct SpriteSheet sheet;
    struct SpritePalette palette;
    struct SpriteTemplate *template;

    sub_8129048(&sPlaceDecorationGraphicsDataBuffer);
    sPlaceDecorationGraphicsDataBuffer.decoration = &gDecorations[decor];
    if (sPlaceDecorationGraphicsDataBuffer.decoration->permission != DECORPERM_SPRITE)
    {
        sub_81291E8(&sPlaceDecorationGraphicsDataBuffer);
        SetDecorSelectionBoxOamAttributes(sPlaceDecorationGraphicsDataBuffer.decoration->shape);
        sub_81291A4(&sPlaceDecorationGraphicsDataBuffer);
        sub_8129068(sPlaceDecorationGraphicsDataBuffer.palette, ((u16 *)gTilesetPointer_SecretBaseRedCave->metatiles)[(sPlaceDecorationGraphicsDataBuffer.decoration->tiles[0] * 8) + 7] >> 12);
        sheet.data = sPlaceDecorationGraphicsDataBuffer.image;
        sheet.size = gUnknown_085A72F4[sPlaceDecorationGraphicsDataBuffer.decoration->shape] << 5;
        sheet.tag = tilesTag;
        LoadSpriteSheet(&sheet);
        palette.data = sPlaceDecorationGraphicsDataBuffer.palette;
        palette.tag = paletteTag;
        LoadSpritePalette(&palette);
        template = Alloc(sizeof(struct SpriteTemplate));
        *template = sDecorWhilePlacingSpriteTemplate;
        template->tileTag = tilesTag;
        template->paletteTag = paletteTag;
        spriteId = CreateSprite(template, 0, 0, 0);
        free(template);
    }
    else
    {
        spriteId = AddPseudoEventObject(sPlaceDecorationGraphicsDataBuffer.decoration->tiles[0], SpriteCallbackDummy, 0, 0, 1);
    }
    return spriteId;
}

u8 AddDecorationIconObject(u8 decor, s16 x, s16 y, u8 priority, u16 tilesTag, u16 paletteTag)
{
    u8 spriteId;

    if (decor > NUM_DECORATIONS)
    {
        spriteId = AddDecorationIconObjectFromIconTable(tilesTag, paletteTag, DECOR_NONE);
        if (spriteId == MAX_SPRITES)
            return MAX_SPRITES;

        gSprites[spriteId].pos2.x = x + 4;
        gSprites[spriteId].pos2.y = y + 4;
    }
    else if (gUnknown_085A6BE8[decor][0] == NULL)
    {
        spriteId = AddDecorationIconObjectFromEventObject(tilesTag, paletteTag, decor);
        if (spriteId == MAX_SPRITES)
            return MAX_SPRITES;

        gSprites[spriteId].pos2.x = x;
        if (decor == DECOR_SILVER_SHIELD || decor == DECOR_GOLD_SHIELD)
            gSprites[spriteId].pos2.y = y - 4;
        else
            gSprites[spriteId].pos2.y = y;
    }
    else
    {
        spriteId = AddDecorationIconObjectFromIconTable(tilesTag, paletteTag, decor);
        if (spriteId == MAX_SPRITES)
            return MAX_SPRITES;

        gSprites[spriteId].pos2.x = x + 4;
        gSprites[spriteId].pos2.y = y + 4;
    }

    gSprites[spriteId].oam.priority = priority;
    return spriteId;
}

void sub_81296EC(u8 idx)
{
    gDecorationContext.items[idx] = 0;
    gDecorationContext.pos[idx] = 0;
}

void sub_8129708(void)
{
    u16 i;

    gSpecialVar_0x8005 = 0;
    gSpecialVar_Result = 0;
    if (gSpecialVar_0x8004 == sCurDecorSelectedInRearrangement)
    {
        gSpecialVar_Result = 1;
    }
    else if (gDecorations[gDecorationContext.items[sDecorRearrangementDataBuffer[gSpecialVar_0x8004].idx]].permission == DECORPERM_SPRITE)
    {
        gSpecialVar_0x8005 = sDecorRearrangementDataBuffer[gSpecialVar_0x8004].flagId;
        sub_81296EC(sDecorRearrangementDataBuffer[gSpecialVar_0x8004].idx);
        for (i = 0; i < gMapHeader.events->eventObjectCount; i++)
        {
            if (gMapHeader.events->eventObjects[i].flagId == gSpecialVar_0x8005)
            {
                gSpecialVar_0x8006 = gMapHeader.events->eventObjects[i].localId;
                break;
            }
        }
    }
}

void sub_81297AC(void)
{
    u8 i;

    for (i = 0; i < gMapHeader.events->eventObjectCount; i++)
    {
        if (gMapHeader.events->eventObjects[i].flagId == gSpecialVar_0x8004)
        {
            gSpecialVar_0x8005 = gMapHeader.events->eventObjects[i].localId;
            break;
        }
    }
}

void sub_81297F8(void)
{
    u8 i;
    u8 y;
    u8 x;
    int posX;
    int posY;
    u8 perm;

    for (i = 0; i < sCurDecorSelectedInRearrangement; i++)
    {
        perm = gDecorations[gDecorationContext.items[sDecorRearrangementDataBuffer[i].idx]].permission;
        posX = gDecorationContext.pos[sDecorRearrangementDataBuffer[i].idx] >> 4;
        posY = gDecorationContext.pos[sDecorRearrangementDataBuffer[i].idx] & 0x0F;
        if (perm != DECORPERM_SPRITE)
        {
            for (y = 0; y < sDecorRearrangementDataBuffer[i].height; y++)
            {
                for (x = 0; x < sDecorRearrangementDataBuffer[i].width; x++)
                {
                    MapGridSetMetatileEntryAt(posX + 7 + x, posY + 7 - y, gMapHeader.mapLayout->map[posX + x + gMapHeader.mapLayout->width * (posY - y)] | 0x3000);
                }
            }

            sub_81296EC(sDecorRearrangementDataBuffer[i].idx);
        }
    }
}

void sub_81298EC(u8 taskId)
{
    switch (gTasks[taskId].data[2])
    {
    case 0:
        sub_81297F8();
        gTasks[taskId].data[2] = 1;
        break;
    case 1:
        if (!gPaletteFade.active) {
            DrawWholeMapView();
            ScriptContext1_SetupScript(EventScript_275D2E);
            ClearDialogWindowAndFrame(0, 1);
            gTasks[taskId].data[2] = 2;
        }
        break;
    case 2:
        ScriptContext2_Enable();
        IdentifyOwnedDecorationsCurrentlyInUseInternal(taskId);
        FadeInFromBlack();
        gTasks[taskId].data[2] = 3;
        break;
    case 3:
        if (IsWeatherNotFadingIn() == TRUE)
        {
            StringExpandPlaceholders(gStringVar4, gText_DecorationReturnedToPC);
            DisplayItemMessageOnField(taskId, gStringVar4, sub_8129D64);
            if (gMapHeader.regionMapSectionId == MAPSEC_SECRET_BASE)
                TV_PutSecretBaseVisitOnTheAir();
        }
        break;
    }
}


bool8 sub_81299AC(u8 taskId)
{
    u16 i;
    for (i = 0; i < gDecorationContext.size; i++)
    {
        if (gDecorationContext.items[i] != DECOR_NONE)
            return TRUE;
    }

    return FALSE;
}

void SetUpPuttingAwayDecorationPlayerAvatar(void)
{
    GetPlayerFacingDirection();
    sDecor_CameraSpriteObjectIdx1 = gSprites[gFieldCamera.spriteId].data[0];
    sub_812A39C();
    gFieldCamera.spriteId = CreateSprite(&gUnknown_085A7404, 120, 80, 0);
        
    switch (gSaveBlock2Ptr->playerGender) {
        default:
        case GENDER_M: 
            sDecor_CameraSpriteObjectIdx2 = AddPseudoEventObject(EVENT_OBJ_GFX_BRENDAN_DECORATING, SpriteCallbackDummy, 136, 72, 0);
            break;
        case GENDER_F:
            sDecor_CameraSpriteObjectIdx2 = AddPseudoEventObject(EVENT_OBJ_GFX_MAY_DECORATING, SpriteCallbackDummy,126, 72, 0);
            break;
        case GENDER_N: 
            sDecor_CameraSpriteObjectIdx2 = AddPseudoEventObject(EVENT_OBJ_GFX_TREEKID_DECORATING, SpriteCallbackDummy, 126, 72, 0);
            break;
    }

    gSprites[sDecor_CameraSpriteObjectIdx2].oam.priority = 1;
    DestroySprite(&gSprites[sDecor_CameraSpriteObjectIdx1]);
    sDecor_CameraSpriteObjectIdx1 = gFieldCamera.spriteId;
    gSprites[sDecor_CameraSpriteObjectIdx1].oam.priority = 1;
}

void sub_8129ABC(u8 taskId)
{
    s16 *data;

    data = gTasks[taskId].data;
    switch (data[2])
    {
    case 0:
        if (!gPaletteFade.active)
        {
            sub_8127ACC(taskId);
            data[2] = 1;
            data[6] = 1;
            data[5] = 1;
        }
        break;
    case 1:
        SetUpPuttingAwayDecorationPlayerAvatar();
        FadeInFromBlack();
        data[2] = 2;
        break;
    case 2:
        if (IsWeatherNotFadingIn() == TRUE)
        {
            data[12] = 1;
            sub_8129B34(taskId);
        }
        break;
    }
}

void sub_8129B34(u8 taskId)
{
    ClearDialogWindowAndFrame(0, 1);
    gSprites[sDecor_CameraSpriteObjectIdx1].data[7] = 0;
    gSprites[sDecor_CameraSpriteObjectIdx1].invisible = FALSE;
    gSprites[sDecor_CameraSpriteObjectIdx1].callback = sub_812A36C;
    gSprites[sDecor_CameraSpriteObjectIdx2].pos1.x = 136;
    gSprites[sDecor_CameraSpriteObjectIdx2].pos1.y = 72;
    gTasks[taskId].data[10] = 0;
    gTasks[taskId].func = sub_8128E18;
}

void sub_8129BCC(u8 taskId)
{
    gTasks[taskId].data[10] = 0;
    sub_8128DE0();
    sub_8129C74(taskId);
}

void sub_8129BF8(u8 taskId)
{
    gTasks[taskId].data[10] = 0;
    sub_8128DE0();
    gSprites[sDecor_CameraSpriteObjectIdx1].invisible = FALSE;
    gSprites[sDecor_CameraSpriteObjectIdx1].callback = SpriteCallbackDummy;
    StringExpandPlaceholders(gStringVar4, gText_StopPuttingAwayDecorations);
    DisplayItemMessageOnField(taskId, gStringVar4, sub_812A1F0);
}

void sub_8129C74(u8 taskId)
{
    s16 *data;
    u8 behavior;

    sub_812A0E8(taskId);
    if (sCurDecorSelectedInRearrangement != 0)
    {
        StringExpandPlaceholders(gStringVar4, gText_ReturnDecorationToPC);
        DisplayItemMessageOnField(taskId, gStringVar4, sub_812A1A0);
    }
    else
    {
        data = gTasks[taskId].data;
        behavior = MapGridGetMetatileBehaviorAt(data[0], data[1]);
        if (MetatileBehavior_IsSecretBasePC(behavior) == TRUE || MetatileBehavior_IsPlayerRoomPCOn(behavior) == TRUE)
        {
            gSprites[sDecor_CameraSpriteObjectIdx1].invisible = FALSE;
            gSprites[sDecor_CameraSpriteObjectIdx1].callback = SpriteCallbackDummy;
            StringExpandPlaceholders(gStringVar4, gText_StopPuttingAwayDecorations);
            DisplayItemMessageOnField(taskId, gStringVar4, sub_812A1F0);
        }
        else
        {
            StringExpandPlaceholders(gStringVar4, gText_NoDecorationHere);
            DisplayItemMessageOnField(taskId, gStringVar4, sub_8129D64);
        }
    }
}

void sub_8129D64(u8 taskId)
{
    if (gMain.newKeys & A_BUTTON || gMain.newKeys & B_BUTTON)
        sub_8129B34(taskId);
}

void sub_8129D8C(u8 decor, struct DecorRearrangementDataBuffer *data)
{
    if (gDecorations[decor].shape == DECORSHAPE_1x1)
    {
        data->width = 1;
        data->height = 1;
    }
    else if (gDecorations[decor].shape == DECORSHAPE_2x1)
    {
        data->width = 2;
        data->height = 1;
    }
    else if (gDecorations[decor].shape == DECORSHAPE_3x1)
    {
        data->width = 3;
        data->height = 1;
    }
    else if (gDecorations[decor].shape == DECORSHAPE_4x2)
    {
        data->width = 4;
        data->height = 2;
    }
    else if (gDecorations[decor].shape == DECORSHAPE_2x2)
    {
        data->width = 2;
        data->height = 2;
    }
    else if (gDecorations[decor].shape == DECORSHAPE_1x2)
    {
        data->width = 1;
        data->height = 2;
    }
    else if (gDecorations[decor].shape == DECORSHAPE_1x3)
    {
        data->width = 1;
        data->height = 3;
    }
    else if (gDecorations[decor].shape == DECORSHAPE_2x4)
    {
        data->width = 2;
        data->height = 4;
    }
    else if (gDecorations[decor].shape == DECORSHAPE_3x3)
    {
        data->width = 3;
        data->height = 3;
    }
    else if (gDecorations[decor].shape == DECORSHAPE_3x2)
    {
        data->width = 3;
        data->height = 2;
    }
}

void sub_8129E0C(u8 x, u8 y)
{
    gSprites[sDecor_CameraSpriteObjectIdx1].invisible = TRUE;
    gSprites[sDecor_CameraSpriteObjectIdx1].callback = SpriteCallbackDummy;
    gSprites[sDecor_CameraSpriteObjectIdx2].pos1.x = (x << 4) + 136;
    gSprites[sDecor_CameraSpriteObjectIdx2].pos1.y = (y << 4) + 72;
}

bool8 sub_8129E74(u8 taskId, u8 idx, struct DecorRearrangementDataBuffer *data)
{
    u8 x;
    u8 y;
    u8 xOff;
    u8 yOff;
    u8 ht;

    x = gTasks[taskId].data[0] - 7;
    y = gTasks[taskId].data[1] - 7;
    xOff = gDecorationContext.pos[idx] >> 4;
    yOff = gDecorationContext.pos[idx] & 0x0F;
    ht = data->height;
    if (gDecorationContext.items[idx] == DECOR_SAND_ORNAMENT && MapGridGetMetatileIdAt(xOff + 7, yOff + 7) == 0x28C)
        ht--;

    if (x >= xOff && x < xOff + data->width && y > yOff - ht && y <= yOff)
    {
        sub_8129E0C(data->width - (x - xOff + 1), yOff - y);
        return TRUE;
    }

    return FALSE;
}

void sub_8129F20(void)
{
    u8 xOff;
    u8 yOff;
    u16 i;

    xOff = gDecorationContext.pos[sDecorRearrangementDataBuffer[sCurDecorSelectedInRearrangement].idx] >> 4;
    yOff = gDecorationContext.pos[sDecorRearrangementDataBuffer[sCurDecorSelectedInRearrangement].idx] & 0x0F;
    for (i = 0; i < 0x40; i++)
    {
        if (gSaveBlock1Ptr->eventObjectTemplates[i].x == xOff && gSaveBlock1Ptr->eventObjectTemplates[i].y == yOff && !FlagGet(gSaveBlock1Ptr->eventObjectTemplates[i].flagId))
        {
            sDecorRearrangementDataBuffer[sCurDecorSelectedInRearrangement].flagId = gSaveBlock1Ptr->eventObjectTemplates[i].flagId;
            break;
        }
    }
}

bool8 sub_8129FC8(u8 taskId)
{
    u16 i;

    for (i = 0; i < gDecorationContext.size; i++)
    {
        if (gDecorationContext.items[i] != 0)
        {
            if (gDecorations[gDecorationContext.items[i]].permission == DECORPERM_SPRITE)
            {
                sub_8129D8C(gDecorationContext.items[i], sDecorRearrangementDataBuffer);
                if (sub_8129E74(taskId, i, sDecorRearrangementDataBuffer) == TRUE)
                {
                    sDecorRearrangementDataBuffer->idx = i;
                    sub_8129F20();
                    sCurDecorSelectedInRearrangement = 1;
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}

void sub_812A040(u8 left, u8 top, u8 right, u8 bottom)
{
    u8 i;
    u8 xOff;
    u8 yOff;
    u8 decorIdx;

    for (i = 0; i < gDecorationContext.size; i++)
    {
        decorIdx = gDecorationContext.items[i];
        xOff = gDecorationContext.pos[i] >> 4;
        yOff = gDecorationContext.pos[i] & 0x0F;
        if (decorIdx != 0 && gDecorations[decorIdx].permission == DECORPERM_SPRITE && left <= xOff && top <= yOff && right >= xOff && bottom >= yOff)
        {
            sDecorRearrangementDataBuffer[sCurDecorSelectedInRearrangement].idx = i;
            sub_8129F20();
            sCurDecorSelectedInRearrangement++;
        }
    }
}

void sub_812A0E8(u8 taskId)
{
    u8 i;
    u8 xOff;
    u8 yOff;
    u8 var1;
    u32 var2;

    sCurDecorSelectedInRearrangement = 0;
    if (sub_8129FC8(taskId) != TRUE)
    {
        for (i = 0; i < gDecorationContext.size; i++)
        {
            var1 = gDecorationContext.items[i];
            if (var1 != DECOR_NONE)
            {
                sub_8129D8C(var1, &sDecorRearrangementDataBuffer[0]);
                if (sub_8129E74(taskId, i, &sDecorRearrangementDataBuffer[0]) == TRUE)
                {
                    sDecorRearrangementDataBuffer[0].idx = i;
                    sCurDecorSelectedInRearrangement++;
                    break;
                }
            }
        }
        if (sCurDecorSelectedInRearrangement != 0)
        {
            xOff = gDecorationContext.pos[sDecorRearrangementDataBuffer[0].idx] >> 4;
            yOff = gDecorationContext.pos[sDecorRearrangementDataBuffer[0].idx] & 0x0F;
            var1 = yOff - sDecorRearrangementDataBuffer[0].height + 1;
            var2 = sDecorRearrangementDataBuffer[0].width + xOff - 1;

            sub_812A040(xOff, var1, var2, yOff);
        }
    }
}

void sub_812A1A0(u8 taskId)
{
    DisplayYesNoMenuDefaultYes();
    DoYesNoFuncWithChoice(taskId, &gUnknown_085A7348);
}

void sub_812A1C0(u8 taskId)
{
    FadeScreen(1, 0);
    gTasks[taskId].data[2] = 0;
    gTasks[taskId].func = sub_81298EC;
}

void sub_812A1F0(u8 taskId)
{
    DisplayYesNoMenuDefaultYes();
    DoYesNoFuncWithChoice(taskId, &gUnknown_085A7350);
}

void sub_812A210(u8 taskId)
{
    ClearDialogWindowAndFrame(0, 0);
    sub_812A22C(taskId);
}

void sub_812A22C(u8 taskId)
{
    FadeScreen(1, 0);
    gTasks[taskId].data[2] = 0;
    gTasks[taskId].func = sub_812A25C;
}

void sub_812A25C(u8 taskId)
{
    switch (gTasks[taskId].data[2])
    {
    case 0:
        if (!gPaletteFade.active)
        {
            sub_8127B04(taskId);
            gTasks[taskId].data[2] = 1;
        }
        break;
    case 1:
        sub_812A3C8();
        gFieldCallback = sub_812A334;
        SetMainCallback2(CB2_ReturnToField);
        DestroyTask(taskId);
        break;
    }
}

void sub_812A2C4(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    switch (data[2])
    {
    case 0:
        HideSecretBaseDecorationSprites();
        data[2]++;
        break;
    case 1:
        ScriptContext1_SetupScript(EventScript_275D0C);
        data[2]++;
        break;
    case 2:
        ScriptContext2_Enable();
        data[2]++;
        break;
    case 3:
        if (IsWeatherNotFadingIn() == TRUE)
            gTasks[taskId].func = HandleDecorationActionsMenuInput;
        break;
    }
}

void sub_812A334(void)
{
    u8 taskId;

    FadeInFromBlack();
    DrawDialogueFrame(0, 1);
    InitDecorationActionsWindow();
    taskId = CreateTask(sub_812A2C4, 8);
    gTasks[taskId].data[2] = 0;
}

void sub_812A36C(struct Sprite *sprite)
{
    sprite->data[0]++;
    sprite->data[0] &= 0x1F;
    if (sprite->data[0] > 15)
        sprite->invisible = TRUE;
    else
        sprite->invisible = FALSE;
}

void sub_812A39C(void)
{
    if (gSaveBlock2Ptr->playerGender == MALE)
        LoadSpritePalette(&gUnknown_085A73D8);
    else
        LoadSpritePalette(&gUnknown_085A73E0);
}

void sub_812A3C8(void)
{
    FreeSpritePaletteByTag(PLACE_DECORATION_PLAYER_TAG);
}

void sub_812A3D4(u8 taskId)
{
    if (IsSelectedDecorInThePC() == TRUE)
    {
        StringCopy(gStringVar1, gDecorations[gCurDecorationItems[gCurDecorationIndex]].name);
        StringExpandPlaceholders(gStringVar4, gText_DecorationWillBeDiscarded);
        DisplayItemMessageOnField(taskId, gStringVar4, sub_812A458);
    }
    else
    {
        StringExpandPlaceholders(gStringVar4, gText_CantThrowAwayInUse);
        DisplayItemMessageOnField(taskId, gStringVar4, sub_8127A5C);
    }
}

void sub_812A458(u8 taskId)
{
    DisplayYesNoMenuDefaultYes();
    DoYesNoFuncWithChoice(taskId, &gUnknown_085A741C);
}

void sub_812A478(u8 taskId)
{
    gCurDecorationItems[gCurDecorationIndex] = DECOR_NONE;
    sNumOwnedDecorationsInCurCategory = GetNumOwnedDecorationsInCategory(sCurDecorationCategory);
    CondenseDecorationsInCategory(sCurDecorationCategory);
    IdentifyOwnedDecorationsCurrentlyInUseInternal(taskId);
    StringExpandPlaceholders(gStringVar4, gText_DecorationThrownAway);
    DisplayItemMessageOnField(taskId, gStringVar4, sub_8127A5C);
}

