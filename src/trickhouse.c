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
#include "overworld.h"
#include "field_message_box.h"
#include "constants/map_scripts.h"
#include "constants/songs.h"
#include "constants/vars.h"
#include "constants/event_objects.h"

static void Task_PuzzleSelect(u8 taskId);

extern const u16 gPuzzleList[];

///////////////////////////////////////////////////////////////////////////////

const u8 sPuzzleText[] = _("{NO}: {STR_VAR_1}");
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

static void RedrawPuzzleSelectWindow(u8 windowId, u16 num)
{
	const u8* txt = sPuzzleText;
	
	ConvertIntToDecimalStringN(gStringVar1, num, 2, 3);
    StringExpandPlaceholders(gStringVar4, txt);
    AddTextPrinterParameterized(windowId, 1, gStringVar4, 0, 1, 0, NULL);
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
	EnableBothScriptContexts();
	DestroyTask(taskId);
}

void ShowPuzzleSelect()
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
	const u8 *script = GetMapHeaderString(currPuzzle, MAP_SCRIPT_PUZZLE_SETUP_SCRIPT);
	if (script != NULL)
	{
		ScriptContext2_RunNewScript(script);
	}
}

extern const u8 PuzzleCommon_DefaultTeardownScript[];
void RunPuzzleTeardownScript()
{
	u16 currPuzzle = gPuzzleList[VarGet(VAR_CURRENT_PUZZLE)];
	const u8 *script = GetMapHeaderString(currPuzzle, MAP_SCRIPT_PUZZLE_TEARDOWN_SCRIPT);
	if (script != NULL)
	{
		ScriptContext2_RunNewScript(script);
	}
}

///////////////////////////////////////////////////////////////////////////////

void SetupPuzzleWarp()
{
	u16 currPuzzle = gPuzzleList[VarGet(VAR_CURRENT_PUZZLE)];
	SetDynamicWarp(0, currPuzzle >> 8, currPuzzle & 0xFF, 0);
}

extern const u8 PuzzleCommon_Text_DefaultAdjective[];
void LoadPuzzleAdjective()
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
void ShowPuzzleQuip()
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
void AssignPuzzleMetaVariables()
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




