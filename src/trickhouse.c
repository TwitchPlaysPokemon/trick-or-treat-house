#include "global.h"
#include "trickhouse.h"
#include "main.h"
#include "menu.h"
#include "menu_helpers.h"
#include "event_data.h"
#include "script.h"
#include "task.h"
#include "bg.h"
#include "alloc.h"
#include "window.h"
#include "text.h"
#include "text_window.h"
#include "string_util.h"
#include "sound.h"
#include "map_name_popup.h"
#include "overworld.h"
#include "field_message_box.h"
#include "international_string_util.h"
#include "constants/map_scripts.h"
#include "constants/maps.h"
#include "constants/map_groups.h"
#include "constants/songs.h"
#include "constants/vars.h"
#include "constants/event_objects.h"

static void Task_PuzzleSelect(u8 taskId);

extern const u16 gPuzzleList[];

const u8 sPuzzleSecretCodes[][0x100] = {
	_("Watch out for Snakes"),
};

///////////////////////////////////////////////////////////////////////////////

extern void LoadMapNamePopUpWindowBg(void);
const u8 sPuzzleText[] = _("{NO}: {STR_VAR_1}");
const u8 sUntitledPuzzle[] = _("<Untitled Puzzle>");
static const struct WindowTemplate sPuzzleSelectWinTemplate =
{
	.bg = 0,
	.tilemapLeft = 20,
	.tilemapTop = 11,
	.width = 8,
	.height = 2,
	.paletteNum = 15,
	.baseBlock = 0x0176,
};

static void ShowMapNamePopUpWindow(u16 num)
{
    u8 mapDisplayHeader[0x100];
    u8 *withoutPrefixPtr;
    u8 x;
    const u8* mapDisplayHeaderSource;

	u16 currPuzzle = gPuzzleList[num-1];
	const u8 *str = GetMapHeaderString(currPuzzle, MAP_SCRIPT_PUZZLE_HEADER_NAME);
	if (str == NULL)
		str = sUntitledPuzzle;
	withoutPrefixPtr = &(mapDisplayHeader[3]);
	StringCopy(withoutPrefixPtr, str);

    AddMapNamePopUpWindow();
    LoadMapNamePopUpWindowBg();
    x = GetStringCenterAlignXOffset(7, withoutPrefixPtr, 80);
    mapDisplayHeader[0] = EXT_CTRL_CODE_BEGIN;
    mapDisplayHeader[1] = EXT_CTRL_CODE_HIGHLIGHT;
    mapDisplayHeader[2] = TEXT_COLOR_TRANSPARENT;
    AddTextPrinterParameterized(GetMapNamePopUpWindowId(), 7, mapDisplayHeader, x, 3, 0xFF, NULL);
    CopyWindowToVram(GetMapNamePopUpWindowId(), 3);
}


static void RedrawPuzzleSelectWindow(u8 windowId, u16 num)
{
	const u8* txt = sPuzzleText;
	
	ConvertIntToDecimalStringN(gStringVar1, num, 2, 3);
    StringExpandPlaceholders(gStringVar4, txt);
    AddTextPrinterParameterized(windowId, 1, gStringVar4, 0, 1, 0, NULL);
	
	ShowMapNamePopUpWindow(num);
}

#define tWindow data[0]
#define tSelected data[1]
#define tMax data[2]

static void Task_InitPuzzleSelect(u8 taskId)
{
	u16 i;
    s16 *data = gTasks[taskId].data;
	
	for (i = 0; i < 65535; i++) 
	{
		if (gPuzzleList[i] == 0xFFFF) break;
	}
	
	tSelected = VarGet(VAR_CURRENT_PUZZLE) + 1;
	tMax = i;
	tWindow = AddWindow(&sPuzzleSelectWinTemplate);
 
	AddMapNamePopUpWindow();
	LoadMapNamePopUpWindowBg();
	
    DrawStdWindowFrame(tWindow, FALSE);
	FillWindowPixelBuffer(tWindow, PIXEL_FILL(1));
	RedrawPuzzleSelectWindow(tWindow, tSelected);
    schedule_bg_copy_tilemap_to_vram(0);

    gTasks[taskId].func = Task_PuzzleSelect;
}

static void Task_PuzzleSelect(u8 taskId)
{
    s16* data = gTasks[taskId].data;

    if (AdjustQuantityAccordingToDPadInput(&tSelected, tMax) == TRUE)
    {
        RedrawPuzzleSelectWindow(tWindow, tSelected);
    }
    else if (gMain.newKeys & A_BUTTON)
    {
        VarSet(VAR_CURRENT_PUZZLE, tSelected-1);
		goto exit;
    }
    else if (gMain.newKeys & B_BUTTON)
	{
		goto exit;
	}
	return;
	
exit:
	PlaySE(SE_SELECT);
	ClearStdWindowAndFrameToTransparent(tWindow, 0);
	ClearWindowTilemap(tWindow);
	RemoveWindow(tWindow);
	ClearStdWindowAndFrame(GetMapNamePopUpWindowId(), TRUE);
	RemoveMapNamePopUpWindow();
	EnableBothScriptContexts();
	DestroyTask(taskId);
}

void ShowPuzzleSelect(struct ScriptContext *ctx)
{
	CreateTask(Task_InitPuzzleSelect, 0);
}


#undef tWindow
#undef tSelected
#undef tMax

///////////////////////////////////////////////////////////////////////////////

extern const u8 PuzzleCommon_DefaultSetupScript[];
void RunPuzzleSetupScript()
{
	u16 currPuzzle = gPuzzleList[VarGet(VAR_CURRENT_PUZZLE)];
	if (!FlagGet(FLAG_IS_PUZZLE_SETUP) &&
	    gSaveBlock1Ptr->location.mapGroup == (currPuzzle >> 8) &&
		gSaveBlock1Ptr->location.mapNum == (currPuzzle & 0xFF))
	{
		// Find and run a setup script
		const u8 *script = GetMapHeaderString(currPuzzle, MAP_SCRIPT_PUZZLE_SETUP_SCRIPT);
		if (script != NULL)
		{
			ScriptContext2_RunNewScript(script);
		}
		// Show map name
		ShowMapNamePopup();
		// 
		FlagSet(FLAG_IS_PUZZLE_SETUP);
	}
}

extern const u8 PuzzleCommon_DefaultTeardownScript[];
void RunPuzzleTeardownScript()
{
	if (FlagGet(FLAG_IS_PUZZLE_SETUP) &&
	    gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(TRICK_HOUSE_END))
	{
		u16 currPuzzle = gPuzzleList[VarGet(VAR_CURRENT_PUZZLE)];
		const u8 *script = GetMapHeaderString(currPuzzle, MAP_SCRIPT_PUZZLE_TEARDOWN_SCRIPT);
		if (script != NULL)
		{
			ScriptContext2_RunNewScript(script);
		}
		FlagClear(FLAG_IS_PUZZLE_SETUP);
	}
}

///////////////////////////////////////////////////////////////////////////////

void SetupPuzzleWarp(struct ScriptContext *ctx)
{
	u16 currPuzzle = gPuzzleList[VarGet(VAR_CURRENT_PUZZLE)];
	SetDynamicWarp(0, currPuzzle >> 8, currPuzzle & 0xFF, 0);
}

void LoadSecretCode(struct ScriptContext *ctx)
{
	VarGet(VAR_CURRENT_PUZZLE); //TODO stub
}

extern const u8 PuzzleCommon_Text_DefaultAdjective[];
void LoadPuzzleAdjective(struct ScriptContext *ctx)
{
	u16 currPuzzle = gPuzzleList[VarGet(VAR_CURRENT_PUZZLE)];
	const u8 *str = GetMapHeaderString(currPuzzle, MAP_SCRIPT_PUZZLE_HEADER_ADJECTIVE);
	if (str == NULL)
	{
		str = PuzzleCommon_Text_DefaultAdjective;
	}
	StringCopy(gStringVar1, str);
}

extern const u8 PuzzleCommon_Text_DefaultQuip[];
void ShowPuzzleQuip(struct ScriptContext *ctx)
{
	u16 currPuzzle = gPuzzleList[VarGet(VAR_CURRENT_PUZZLE)];
	const u8 *str = GetMapHeaderString(currPuzzle, MAP_SCRIPT_PUZZLE_HEADER_QUIP);
	if (str == NULL)
	{
		str = PuzzleCommon_Text_DefaultQuip;
	}
	ShowFieldMessage(str);
}

extern const u8 PuzzleCommon_DefaultVariableAssignments[];
void AssignPuzzleMetaVariables(struct ScriptContext *ctx)
{
	u16 currPuzzle = gPuzzleList[VarGet(VAR_CURRENT_PUZZLE)];
	const u16 *array = (u16*)GetMapHeaderString(currPuzzle, MAP_SCRIPT_PUZZLE_META_VARIABLES);
	
	// Reset variables to defaults
	VarSet(VAR_OBJ_GFX_ID_0, EVENT_OBJ_GFX_TRICK_MASTER);
	VarSet(VAR_OBJ_GFX_ID_1, EVENT_OBJ_GFX_TRICK_MASTER);
	
	if (array != NULL)
	{
		while (array[0] != 0)
		{
			VarSet(array[0], array[1]);
			array += 2;
		}
	}
}




