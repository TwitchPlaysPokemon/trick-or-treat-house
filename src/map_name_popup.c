#include "global.h"
// #include "battle_pyramid.h"
#include "bg.h"
#include "event_data.h"
#include "gpu_regs.h"
#include "international_string_util.h"
#include "menu.h"
#include "map_name_popup.h"
#include "palette.h"
#include "region_map.h"
#include "start_menu.h"
#include "string_util.h"
#include "task.h"
#include "text.h"
#include "script.h"
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
void LoadMapNamePopUpWindowBg(void);

// EWRAM
static EWRAM_DATA u8 sPopupTaskId = 0;

// .rodata

static const u8 gMapPopUp_Gfx[] = INCBIN_U8("graphics/interface/map_popup/scroll.4bpp");
static const u16 gMapPopUp_Pal[] = INCBIN_U16("graphics/interface/map_popup/scroll.gbapal");

// text
bool8 sub_80D47D4(void)
{
    HideStartMenu();
    ShowMapNamePopup();
    return TRUE;
}

void ShowMapNamePopup(void)
{
    if (FlagGet(FLAG_HIDE_MAP_NAME_POPUP) != TRUE)
    {
        if (!FuncIsActiveTask(Task_MapNamePopUpWindow))
        {
            sPopupTaskId = CreateTask(Task_MapNamePopUpWindow, 90);
            SetGpuReg(REG_OFFSET_BG0VOFS, 40);
            gTasks[sPopupTaskId].data[0] = 6;
            gTasks[sPopupTaskId].data[2] = 40;
        }
        else
        {
            if (gTasks[sPopupTaskId].data[0] != 2)
                gTasks[sPopupTaskId].data[0] = 2;
            gTasks[sPopupTaskId].data[3] = 1;
        }
    }
}

static void Task_MapNamePopUpWindow(u8 taskId)
{
    struct Task *task = &gTasks[taskId];

    switch (task->data[0])
    {
    case 6:
        task->data[4]++;
        if (task->data[4] > 30)
        {
            task->data[0] = 0;
            task->data[4] = 0;
            ShowMapNamePopUpWindow();
        }
        break;
    case 0:
        task->data[2] -= 2;
        if (task->data[2] <= 0 )
        {
            task->data[2] = 0;
            task->data[0] = 1;
            gTasks[sPopupTaskId].data[1] = 0;
        }
        break;
    case 1:
        task->data[1]++;
        if (task->data[1] > 120 )
        {
            task->data[1] = 0;
            task->data[0] = 2;
        }
        break;
    case 2:
        task->data[2] += 2;
        if (task->data[2] > 39)
        {
            task->data[2] = 40;
            if (task->data[3])
            {
                task->data[0] = 6;
                task->data[4] = 0;
                task->data[3] = 0;
            }
            else
            {
                task->data[0] = 4;
                return;
            }
        }
        break;
    case 4:
        ClearStdWindowAndFrame(GetMapNamePopUpWindowId(), TRUE);
        task->data[0] = 5;
        break;
    case 5:
        HideMapNamePopUpWindow();
        return;
    }
    SetGpuReg(REG_OFFSET_BG0VOFS, task->data[2]);
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

extern const u16 gPuzzleList[];
extern const u8 PuzzleCommon_Text_UntitledPuzzleName[];
void ShowMapNamePopUpWindow(void)
{
    u8 mapDisplayHeader[0x100];
    u8 *withoutPrefixPtr;
    u8 x;
    const u8* mapDisplayHeaderSource;
    
    u16 currPuzzle = gPuzzleList[VarGet(VAR_CURRENT_PUZZLE)];
    const u8 *str = GetMapHeaderString(currPuzzle, MAP_SCRIPT_PUZZLE_HEADER_NAME);
    if (str == NULL) 
        str = PuzzleCommon_Text_UntitledPuzzleName;
    withoutPrefixPtr = &(mapDisplayHeader[3]);
    StringCopy(withoutPrefixPtr, str);
    
    AddMapNamePopUpWindow();
    LoadMapNamePopUpWindowBg();
    x = GetStringCenterAlignXOffset(7, withoutPrefixPtr, 8*14);
    mapDisplayHeader[0] = EXT_CTRL_CODE_BEGIN;
    mapDisplayHeader[1] = EXT_CTRL_CODE_HIGHLIGHT;
    mapDisplayHeader[2] = TEXT_COLOR_TRANSPARENT;
    AddTextPrinterParameterized(GetMapNamePopUpWindowId(), 7, mapDisplayHeader, x, 5, 0xFF, NULL);
    CopyWindowToVram(GetMapNamePopUpWindowId(), 3);
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
    u16 regionMapSectionId = gMapHeader.regionMapSectionId;

    if (regionMapSectionId > MAPSEC_DYNAMIC)
    {
        if (regionMapSectionId > MAPSEC_SPECIAL_AREA)
            regionMapSectionId -= (MAPSEC_SPECIAL_AREA - MAPSEC_DYNAMIC);
        else
            regionMapSectionId = 0; // Discard kanto region sections;
    }

    LoadBgTiles(GetWindowAttribute(popupWindowId, WINDOW_BG), gMapPopUp_Gfx, 0x400, 0x21D);
    CallWindowFunction(popupWindowId, WindowFunc_DrawMapNamePlate);
    PutWindowTilemap(popupWindowId);
    
    LoadPalette(gMapPopUp_Pal, 0xE0, 0x20);
    FillWindowPixelRect(popupWindowId, PIXEL_FILL(3), 0, 0, 8*14, 3);
    FillWindowPixelRect(popupWindowId, PIXEL_FILL(1), 0, 3, 8*14, 8*3-3);
}
