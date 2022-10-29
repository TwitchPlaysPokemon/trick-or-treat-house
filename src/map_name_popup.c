#include "global.h"
#include "bg.h"
#include "event_data.h"
#include "gpu_regs.h"
#include "international_string_util.h"
#include "menu.h"
#include "map_name_popup.h"
#include "mgba.h"
#include "palette.h"
#include "region_map.h"
#include "start_menu.h"
#include "string_util.h"
#include "task.h"
#include "text.h"
#include "script.h"
#include "trickhouse.h"
#include "overworld.h"
#include "constants/map_groups.h"
#include "constants/maps.h"
#include "constants/layouts.h"
#include "constants/region_map_sections.h"
#include "constants/weather.h"
#include "constants/map_scripts.h"

// enums
enum MapPopUp_Themes
{
    MAPPOPUP_THEME_WOOD,
    MAPPOPUP_THEME_MARBLE,
    MAPPOPUP_THEME_STONE,
    MAPPOPUP_THEME_BRICK,
    MAPPOPUP_THEME_UNDERWATER,
    MAPPOPUP_THEME_STONE2,
};

// static functions
static void Task_MapNamePopUpWindow(u8 taskId);
void ShowMapNamePopUpWindow(void);
void ShowRoomNamePopUpWindow(void);
void LoadMapNamePopUpWindowBg(void);
void LoadRoomNamePopUpWindowBg(void);

// EWRAM
static EWRAM_DATA u8 sPopupTaskId = 0;

// .rodata

static const u8 gMapPopUp_Gfx[] = INCBIN_U8("graphics/map_popup/scroll.4bpp");
static const u16 gMapPopUp_Pal[] = INCBIN_U16("graphics/map_popup/scroll.gbapal");

static const u8 gMetaRoomPopUp_Gfx[] = INCBIN_U8("graphics/map_popup/stone.4bpp");
static const u8 gMetaRoomPopUpOutline_Gfx[] = INCBIN_U8("graphics/map_popup/stone_outline.4bpp");
static const u16 gMetaRoomPopUp_Pal[] = INCBIN_U16("graphics/map_popup/stone_outline.gbapal");

// Unused
static bool8 StartMenu_ShowMapNamePopup(void)
{
    HideStartMenu();
    ShowMapNamePopup();
    return TRUE;
}

#define tState data[0]
#define tTimer1 data[1]
#define tBgOff data[2]
#define tDoReopen data[3]
#define tTimer4 data[4]

void ShowMapNamePopup(void)
{
    if (FlagGet(FLAG_HIDE_MAP_NAME_POPUP) != TRUE)
    {
        if (!FuncIsActiveTask(Task_MapNamePopUpWindow))
        {
            sPopupTaskId = CreateTask(Task_MapNamePopUpWindow, 90);
            SetGpuReg(REG_OFFSET_BG0VOFS, 40);
            gTasks[sPopupTaskId].tState = 6;
            gTasks[sPopupTaskId].tBgOff = 40;
        }
        else
        {
            if (gTasks[sPopupTaskId].tState != 2)
                gTasks[sPopupTaskId].tState = 2;
            gTasks[sPopupTaskId].tDoReopen = 1;
        }
    }
}

static void Task_MapNamePopUpWindow(u8 taskId)
{
    struct Task *task = &gTasks[taskId];

    switch (task->tState)
    {
    case 6:
        task->tTimer4++;
        if (task->tTimer4 > 30)
        {
            task->tState = 0;
            task->tTimer4 = 0;
            ShowMapNamePopUpWindow();
        }
        break;
    case 10:
        task->tTimer4++;
        if (task->tTimer4 > 30)
        {
            task->tState = 0;
            task->tTimer4 = 0;
            ShowRoomNamePopUpWindow();
        }
        break;
    case 0:
        task->tBgOff -= 2;
        if (task->tBgOff <= 0 )
        {
            task->tBgOff = 0;
            task->tState = 1;
            gTasks[sPopupTaskId].tTimer1 = 0;
        }
        break;
    case 1:
        task->tTimer1++;
        if (task->tTimer1 > 120)
        {
            task->tTimer1 = 0;
            task->tState = 2;
        }
        break;
    case 2:
        task->tBgOff += 2;
        if (task->tBgOff > 39)
        {
            task->tBgOff = 40;
            if (task->tDoReopen == 1)
            {
                task->tState = 6;
                task->tTimer4 = 0;
                task->tDoReopen = 0;
            }
            else if (task->tDoReopen == 2)
            {
                task->tState = 10;
                task->tTimer4 = 0;
                task->tDoReopen = 0;
            }
            else
            {
                task->tState = 4;
                return;
            }
        }
        break;
    case 4:
        ClearStdWindowAndFrame(GetMapNamePopUpWindowId(), TRUE);
        task->tState = 5;
        break;
    case 5:
        HideMapNamePopUpWindow();
        return;
    }
    SetGpuReg(REG_OFFSET_BG0VOFS, task->tBgOff);
}

void WindowFunc_ClearMapWindowAndFrameToTransparent(u8 bg, u8 tilemapLeft, u8 tilemapTop, u8 width, u8 height, u8 paletteNum)
{
    FillBgTilemapBufferRect(bg, 0, tilemapLeft - 2, tilemapTop - 1, width + 4, height + 2, 0);
}

void HideMapNamePopUpWindow(void)
{
    if (FuncIsActiveTask(Task_MapNamePopUpWindow))
    {
        u8 windowId = GetMapNamePopUpWindowId();
        CallWindowFunction(windowId, WindowFunc_ClearMapWindowAndFrameToTransparent);
        FillWindowPixelBuffer(windowId, PIXEL_FILL(0));
        ClearWindowTilemap(windowId);
        CopyWindowToVram(windowId, 3);
        
        RemoveMapNamePopUpWindow();
        SetGpuReg_ForcedBlank(REG_OFFSET_BG0VOFS, 0);
        DestroyTask(sPopupTaskId);
    }
}

extern const u8 PuzzleCommon_Text_UntitledPuzzleName[];
void ShowMapNamePopUpWindow(void)
{
    u8 mapDisplayHeader[0x100];
    u8 *withoutPrefixPtr;
    u8 x;
    u16 currPuzzle;
    const u8* mapDisplayHeaderSource;
    const u8* str;
    
    if (gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(TRICK_TREAT_SLATEPORT_CITY1)) {
        str = GetMapHeaderString(MAP_TRICK_TREAT_SLATEPORT_CITY1, MAP_SCRIPT_PUZZLE_HEADER_NAME);
    } else {
        currPuzzle = GetCurrentPuzzleMapId();
        str = GetMapHeaderString(currPuzzle, MAP_SCRIPT_PUZZLE_HEADER_NAME);
    }
    if (str == NULL) 
        str = PuzzleCommon_Text_UntitledPuzzleName;
    withoutPrefixPtr = &(mapDisplayHeader[3]);
    StringCopy(withoutPrefixPtr, str);
    
    AddMapNamePopUpWindow();
    LoadMapNamePopUpWindowBg();
    x = GetStringCenterAlignXOffset(FONT_NARROW, withoutPrefixPtr, 8*MAP_NAME_WINDOW_WIDTH);
    mapDisplayHeader[0] = EXT_CTRL_CODE_BEGIN;
    mapDisplayHeader[1] = EXT_CTRL_CODE_HIGHLIGHT;
    mapDisplayHeader[2] = TEXT_COLOR_TRANSPARENT;
    AddTextPrinterParameterized(GetMapNamePopUpWindowId(), FONT_NARROW, mapDisplayHeader, x, 5, TEXT_SKIP_DRAW, NULL);
    CopyWindowToVram(GetMapNamePopUpWindowId(), COPYWIN_FULL);
}

static void WindowFunc_DrawMapNamePlate(u8 bg, u8 x, u8 y, u8 width, u8 height, u8 paletteNum)
{
    s32 i;

    FillBgTilemapBufferRect(bg, 0x21D, x - 2,     y - 1,     1, 1, paletteNum);
    FillBgTilemapBufferRect(bg, 0x21E, x - 1,     y - 1, width+2, 1, paletteNum);
    FillBgTilemapBufferRect(bg, 0x21F, x + 9,     y - 1,     1, 1, paletteNum);
    FillBgTilemapBufferRect(bg, 0x220, x+width+1, y - 1,     1, 1, paletteNum);
    
    FillBgTilemapBufferRect(bg, 0x221, x - 1,     y,     1, 1, paletteNum);
    FillBgTilemapBufferRect(bg, 0x222, x,         y, width, 1, paletteNum);
    FillBgTilemapBufferRect(bg, 0x224, width + x, y,     1, 1, paletteNum);
    
    FillBgTilemapBufferRect(bg, 0x225, x - 1,     y+1, 1,     height-1, paletteNum);
    FillBgTilemapBufferRect(bg, 0x226, x,         y+1, width, height-1, paletteNum);
    FillBgTilemapBufferRect(bg, 0x228, width + x, y+1, 1,     height-1, paletteNum);

    FillBgTilemapBufferRect(bg, 0x229, x - 1,     y+height,     1, 1, paletteNum);
    FillBgTilemapBufferRect(bg, 0x22A, x,         y+height, width, 1, paletteNum);
    FillBgTilemapBufferRect(bg, 0x22C, width + x, y+height,     1, 1, paletteNum);
}

void LoadMapNamePopUpWindowBg(void)
{
    u8 popupWindowId = GetMapNamePopUpWindowId();
    
    LoadBgTiles(GetWindowAttribute(popupWindowId, WINDOW_BG), gMapPopUp_Gfx, 0x400, 0x21D);
    CallWindowFunction(popupWindowId, WindowFunc_DrawMapNamePlate);
    PutWindowTilemap(popupWindowId);
    
    LoadPalette(gMapPopUp_Pal, 0xE0, 0x20);
    FillWindowPixelRect(popupWindowId, PIXEL_FILL(3), 0, 0, 8*MAP_NAME_WINDOW_WIDTH, 3);
    FillWindowPixelRect(popupWindowId, PIXEL_FILL(1), 0, 3, 8*MAP_NAME_WINDOW_WIDTH, 8*3-3);
}

//-----------------------------------------------------------------------------

void ShowRoomNamePopup(void)
{
    u16 currMap = (u8)gSaveBlock1Ptr->location.mapGroup << 8 | (u8)gSaveBlock1Ptr->location.mapNum;
    const u8* str = GetMapHeaderString(currMap, MAP_SCRIPT_ROOM_NAME);
    if (str == NULL) return; // no show
    
    if (FlagGet(FLAG_HIDE_MAP_NAME_POPUP) != TRUE)
    {
        if (!FuncIsActiveTask(Task_MapNamePopUpWindow))
        {
            sPopupTaskId = CreateTask(Task_MapNamePopUpWindow, 90);
            SetGpuReg(REG_OFFSET_BG0VOFS, 40);
            gTasks[sPopupTaskId].tState = 10;
            gTasks[sPopupTaskId].tBgOff = 40;
        }
        else
        {
            if (gTasks[sPopupTaskId].tState != 2)
                gTasks[sPopupTaskId].tState = 2;
            gTasks[sPopupTaskId].tDoReopen = 2;
        }
    }
}

#define TILE_TOP_EDGE_START 0x21D
#define TILE_TOP_EDGE_END   0x228
#define TILE_LEFT_EDGE_TOP  0x229
#define TILE_RIGHT_EDGE_TOP 0x22A
#define TILE_LEFT_EDGE_MID  0x22B
#define TILE_RIGHT_EDGE_MID 0x22C
#define TILE_LEFT_EDGE_BOT  0x22D
#define TILE_RIGHT_EDGE_BOT 0x22E
#define TILE_BOT_EDGE_START 0x22F
#define TILE_BOT_EDGE_END   0x23A

void ShowRoomNamePopUpWindow(void)
{
    u8 mapDisplayHeader[0x100];
    u8 *withoutPrefixPtr;
    u8 x;
    u16 currMap;
    const u8* mapDisplayHeaderSource;
    const u8* str;
    
    currMap = (u8)gSaveBlock1Ptr->location.mapGroup << 8 | (u8)gSaveBlock1Ptr->location.mapNum;
    str = GetMapHeaderString(currMap, MAP_SCRIPT_ROOM_NAME);
    
    if (str == NULL) 
        str = PuzzleCommon_Text_UntitledPuzzleName;
    withoutPrefixPtr = &(mapDisplayHeader[3]);
    StringCopy(withoutPrefixPtr, str);
    
    AddRoomNamePopUpWindow();
    LoadRoomNamePopUpWindowBg();
    x = GetStringCenterAlignXOffset(FONT_NARROW, withoutPrefixPtr, 8*(ROOM_NAME_WINDOW_WIDTH));
    mapDisplayHeader[0] = EXT_CTRL_CODE_BEGIN;
    mapDisplayHeader[1] = EXT_CTRL_CODE_HIGHLIGHT;
    mapDisplayHeader[2] = TEXT_COLOR_TRANSPARENT;
    AddTextPrinterParameterized(GetMapNamePopUpWindowId(), FONT_NARROW, mapDisplayHeader, x, 2, TEXT_SKIP_DRAW, NULL);
    CopyWindowToVram(GetMapNamePopUpWindowId(), COPYWIN_FULL);
}


static void WindowFunc_DrawRoomNamePlate(u8 bg, u8 x, u8 y, u8 width, u8 height, u8 unused)
{
    s32 i;

    // Draw top edge
    for (i = 0; i < 1 + TILE_TOP_EDGE_END - TILE_TOP_EDGE_START; i++)
        FillBgTilemapBufferRect(bg, TILE_TOP_EDGE_START + i, i - 1 + x, y - 1, 1, 1, 14);

    // Draw sides
    FillBgTilemapBufferRect(bg, TILE_LEFT_EDGE_TOP,      x - 1,     y, 1, 1, 14);
    FillBgTilemapBufferRect(bg, TILE_RIGHT_EDGE_TOP, width + x,     y, 1, 1, 14);
    FillBgTilemapBufferRect(bg, TILE_LEFT_EDGE_MID,      x - 1, y + 1, 1, 1, 14);
    FillBgTilemapBufferRect(bg, TILE_RIGHT_EDGE_MID, width + x, y + 1, 1, 1, 14);
    FillBgTilemapBufferRect(bg, TILE_LEFT_EDGE_BOT,      x - 1, y + 2, 1, 1, 14);
    FillBgTilemapBufferRect(bg, TILE_RIGHT_EDGE_BOT, width + x, y + 2, 1, 1, 14);

    // Draw bottom edge
    for (i = 0; i < 1 + TILE_BOT_EDGE_END - TILE_BOT_EDGE_START; i++)
        FillBgTilemapBufferRect(bg, TILE_BOT_EDGE_START + i, i - 1 + x, y + height, 1, 1, 14);
}

void LoadRoomNamePopUpWindowBg(void)
{
    u8 popupWindowId = GetMapNamePopUpWindowId();

    LoadBgTiles(GetWindowAttribute(popupWindowId, WINDOW_BG), gMetaRoomPopUpOutline_Gfx, 0x400, 0x21D);
    CallWindowFunction(popupWindowId, WindowFunc_DrawRoomNamePlate);
    PutWindowTilemap(popupWindowId);
    LoadPalette(gMetaRoomPopUp_Pal, 0xE0, sizeof(gMetaRoomPopUp_Pal));
    BlitBitmapToWindow(popupWindowId, gMetaRoomPopUp_Gfx, 0, 0, 80, 24);
}
