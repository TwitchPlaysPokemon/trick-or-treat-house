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
#include "battle_factory.h"
#include "battle_factory_screen.h"
#include "random.h"
#include "item.h"
#include "strings.h"
#include "battle_tower.h"
#include "international_string_util.h"
#include "constants/map_scripts.h"
#include "constants/maps.h"
#include "constants/map_groups.h"
#include "constants/songs.h"
#include "constants/vars.h"
#include "constants/flags.h"
#include "constants/opponents.h"
#include "constants/event_objects.h"
#include "constants/species.h"
#include "constants/items.h"

static void Task_PuzzleSelect(u8 taskId);
static void GenerateRentalMons(void);

extern const u16 gPuzzleList[];

const u8 sPuzzleSecretCodes[][0x100] = {
	_("This is Halloween!"),
	_("Pumpkaboo scream in the dead of night…"),
	_("Ride with the moon in the dead of night…"),
	_("I am the shadow on the moon at night…"),
	_("The clown with the tearaway face…"),
	_("Watch out for Ekans!"),
	_("It's just a bunch of Hocus Pocus!"),
	_("Double double, toil and trouble…"),
	_("Nevermore!"),
	_("Something wicked this way comes…"),
	_("Don't look behind you…"),
};


///////////////////////////////////////////////////////////////////////////////

extern void LoadMapNamePopUpWindowBg(void);
const u8 sPuzzleText[] = _("{NO}: {STR_VAR_1}");
extern const u8 PuzzleCommon_Text_UntitledPuzzleName[];
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
		str = PuzzleCommon_Text_UntitledPuzzleName;
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

void ClearPuzzleEventData(struct ScriptContext *ctx)
{
	memset(gSaveBlock1Ptr->flags + 0x04, 0, 0x0A);
	memset(gSaveBlock1Ptr->vars  + 0x20, 0, 0x40);
	memset(gSaveBlock1Ptr->flags + (FLAG_TRAINER_FLAG_START >> 3), 0, TRAINERS_PERMAP_END >> 3);
}

void SetupPuzzleWarp(struct ScriptContext *ctx)
{
	u16 currPuzzle = gPuzzleList[VarGet(VAR_CURRENT_PUZZLE)];
	SetDynamicWarp(0, currPuzzle >> 8, currPuzzle & 0xFF, 0);
}

extern const u8 PuzzleCommon_Text_FirstPuzzleIntro[];
void LoadPuzzleIntro(struct ScriptContext *ctx)
{
	u16 currPuzzle = gPuzzleList[VarGet(VAR_CURRENT_PUZZLE)];
	const u8 *str = GetMapHeaderString(currPuzzle, MAP_SCRIPT_PUZZLE_CUSTOM_INTRO);
	// Check for custom intro
	if (str != NULL) {
		gSpecialVar_Result = 2;
		ctx->data[0] = (u32)str;
		return;
	}
	// Check if this is the first puzzle, load as a custom intro
	if (VarGet(VAR_CURRENT_PUZZLE) == 0) { //first puzzle
		gSpecialVar_Result = 2;
		ctx->data[0] = (u32)PuzzleCommon_Text_FirstPuzzleIntro;
		return;
	}
	ctx->data[0] = 0;
	// Check if this puzzle has items
	{
		const u16 *array = (u16*)GetMapHeaderString(currPuzzle, MAP_SCRIPT_PUZZLE_HEADER_PREREQ_LIST);
		if (array != NULL && array[0] != ITEM_NONE) {
			// Use generic item intro
			gSpecialVar_Result = 1;
		}
	}
	// Otherwise use generic no-item intro
	gSpecialVar_Result = 0;
}

// extern const u8 PuzzleCommon_Text_DefaultAuthor[];
// void LoadPuzzleAuthor(struct ScriptContext *ctx)
// {
// 	u16 currPuzzle = gPuzzleList[VarGet(VAR_CURRENT_PUZZLE)];
// 	const u8 *str = GetMapHeaderString(currPuzzle, MAP_SCRIPT_PUZZLE_HEADER_AUTHOR);
// 	if (str == NULL)
// 	{
// 		str = PuzzleCommon_Text_DefaultAuthor;
// 	}
// 	StringCopy(gStringVar1, str);
// }

// extern const u8 PuzzleCommon_Text_DefaultAdjective[];
// void LoadPuzzleAdjective(struct ScriptContext *ctx)
// {
// 	u16 currPuzzle = gPuzzleList[VarGet(VAR_CURRENT_PUZZLE)];
// 	const u8 *str = GetMapHeaderString(currPuzzle, MAP_SCRIPT_PUZZLE_HEADER_ADJECTIVE);
// 	if (str == NULL)
// 	{
// 		str = PuzzleCommon_Text_DefaultAdjective;
// 	}
// 	StringCopy(gStringVar2, str);
// }

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
	
	// Reset introducer to trick master by default
	VarSet(VAR_OBJ_GFX_ID_0, EVENT_OBJ_GFX_TRICK_MASTER);
	// Randomize quip person by default
	VarSet(VAR_OBJ_GFX_ID_1, (Random() % (EVENT_OBJ_GFX_FISHERMAN - EVENT_OBJ_GFX_BOY_1)) + EVENT_OBJ_GFX_BOY_1);
	
	if (array != NULL)
	{
		while (array[0] != 0)
		{
			VarSet(array[0], array[1]);
			array += 2;
		}
	}
}


void GiveItemPrerequisites(struct ScriptContext *ctx)
{
	u8 *ptr = gStringVar1;
	u8 itemCount = 0;
	u16 currPuzzle = gPuzzleList[VarGet(VAR_CURRENT_PUZZLE)];
	const u16 *array = (u16*)GetMapHeaderString(currPuzzle, MAP_SCRIPT_PUZZLE_HEADER_PREREQ_LIST);
	
	gSpecialVar_Result = FALSE;
	*ptr = EOS;
	
	if (array != NULL)
	{
		while (array[0] != ITEM_NONE)
		{
			gSpecialVar_Result |= AddBagItem(array[0], 1);
			
			if (array[1] == ITEM_NONE && itemCount > 0) {
				ptr = StringCopy(ptr, gText_And);
				(*ptr++) = CHAR_SPACE;
			}
			itemCount++;
			ptr = StringCopy(ptr, gText_One);
			(*ptr++) = CHAR_SPACE;
			ptr = StringCopy(ptr, ItemId_GetName(array[0]));
			if (array[1] != ITEM_NONE) {
				(*ptr++) = CHAR_COMMA;
				(*ptr++) = CHAR_NEWLINE;
			}
			array += 1;
		}
	}
	*ptr = EOS;
}


void RemovePuzzleItems(struct ScriptContext *ctx)
{
	u8 *ptr = gStringVar1;
	u8 itemCount = 0;
	u16 currPuzzle = gPuzzleList[VarGet(VAR_CURRENT_PUZZLE)];
	const u16 *array = (u16*)GetMapHeaderString(currPuzzle, MAP_SCRIPT_PUZZLE_HEADER_POST_LIST);
	gSpecialVar_Result = FALSE;
	
	if (array != NULL)
	{
		while (array[0] != ITEM_NONE)
		{
			gSpecialVar_Result |= RemoveBagItem(array[0], 1);
			
			if (array[1] == ITEM_NONE && itemCount > 0) {
				ptr = StringCopy(ptr, gText_And);
				(*ptr++) = CHAR_SPACE;
			}
			itemCount++;
			ptr = StringCopy(ptr, gText_One);
			(*ptr++) = CHAR_SPACE;
			ptr = StringCopy(ptr, ItemId_GetName(array[0]));
			if (array[1] != ITEM_NONE) {
				(*ptr++) = CHAR_COMMA;
				(*ptr++) = CHAR_NEWLINE;
			}
			array += 1;
		}
	}
	*ptr = EOS;
}

void SelectInitialRentalParty(struct ScriptContext *ctx)
{
	GenerateRentalMons();
	ZeroPlayerPartyMons();
	DoBattleFactorySelectScreen();
	FlagSet(FLAG_SYS_POKEMON_GET);
}

void SwapRentalParty(struct ScriptContext *ctx)
{
	DoBattleFactorySwapScreen();
}

void RandomizeRentalMons(struct ScriptContext *ctx)
{
	GenerateRentalMons();
}

///////////////////////////////////////////////////////////////////////////////

// extern const struct BattleFrontierTrainer *gFacilityTrainers;
extern const struct FacilityMon *gFacilityTrainerMons;
static void GenerateRentalMons(void)
{
    s32 i, j;
    u8 firstMonId;
    u16 monSetId;
    u16 currSpecies;
    u16 species[PARTY_SIZE];
    u16 monIds[PARTY_SIZE];
    u16 heldItems[PARTY_SIZE];

    firstMonId = 0;
    // gFacilityTrainers = gSlateportBattleTentTrainers;
    for (i = 0; i < PARTY_SIZE; i++)
    {
        species[i] = 0;
        monIds[i] = 0;
        heldItems[i] = 0;
    }
    gFacilityTrainerMons = gBattleFrontierMons;
    currSpecies = SPECIES_NONE;
    i = 0;
    while (i != PARTY_SIZE)
    {
		monSetId = min(880, (70 + (10 * VarGet(VAR_CURRENT_PUZZLE))));
        monSetId = Random() % monSetId;
		
        // Cannot have two pokemon of the same species.
        for (j = firstMonId; j < firstMonId + i; j++)
        {
            u16 monId = monIds[j];
            if (monIds[j] == monSetId)
                break;
            if (species[j] == gFacilityTrainerMons[monSetId].species)
            {
                if (currSpecies == SPECIES_NONE)
                    currSpecies = gFacilityTrainerMons[monSetId].species;
                else
                    break;
            }
        }
        if (j != i + firstMonId)
            continue;

        // Cannot have two same held items.
        for (j = firstMonId; j < i + firstMonId; j++)
        {
            if (heldItems[j] != 0 && heldItems[j] == gBattleFrontierHeldItems[gFacilityTrainerMons[monSetId].itemTableId])
            {
                if (gFacilityTrainerMons[monSetId].species == currSpecies)
                    currSpecies = SPECIES_NONE;
                break;
            }
        }
        if (j != i + firstMonId)
            continue;

        gSaveBlock2Ptr->frontier.rentalMons[i].monId = monSetId;
        species[i] = gFacilityTrainerMons[monSetId].species;
        heldItems[i] = gBattleFrontierHeldItems[gFacilityTrainerMons[monSetId].itemTableId];
        monIds[i] = monSetId;
        i++;
    }
}


