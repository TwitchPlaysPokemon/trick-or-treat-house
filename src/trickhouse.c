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
extern const u16 gDebugPuzzles[];
#define DEBUG_PUZZLE_START 32768

///////////////////////////////////////////////////////////////////////////////

u16 GetCurrentPuzzleMapId()
{
#if DEBUG
	u16 i = VarGet(VAR_CURRENT_PUZZLE);
	if (i < DEBUG_PUZZLE_START)
		return gPuzzleList[i];
	else
		return gDebugPuzzles[i-DEBUG_PUZZLE_START];
#else
	return gPuzzleList[VarGet(VAR_CURRENT_PUZZLE)];
#endif
}

///////////////////////////////////////////////////////////////////////////////

extern const u8 PuzzleCommon_DefaultSetupScript[];
void RunPuzzleSetupScript()
{
	u16 currPuzzle = GetCurrentPuzzleMapId();
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
		u16 currPuzzle = GetCurrentPuzzleMapId();
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
	memset(gSaveBlock1Ptr->flags + (FLAG_HIDDEN_ITEMS_START >> 3), 0, 0x20 >> 8);
}

void SetupPuzzleWarp(struct ScriptContext *ctx)
{
	u16 currPuzzle = GetCurrentPuzzleMapId();
	if (currPuzzle == 0xFFFF) currPuzzle = MAP_TRICK_HOUSE_END; //sanity check
	SetDynamicWarp(0, currPuzzle >> 8, currPuzzle & 0xFF, 0);
}

extern const u8 PuzzleCommon_Text_FirstPuzzleIntro[];
void LoadPuzzleIntro(struct ScriptContext *ctx)
{
	u16 currPuzzle = GetCurrentPuzzleMapId();
	const u8 *str = GetMapHeaderString(currPuzzle, MAP_SCRIPT_PUZZLE_CUSTOM_INTRO);
	// Set up for generic no-item intro
	ctx->data[0] = 0;
	gSpecialVar_Result = 0;
	
	// Check if this puzzle has items
	{
		const u16 *array = (u16*)GetMapHeaderString(currPuzzle, MAP_SCRIPT_PUZZLE_HEADER_PREREQ_LIST);
		if (array != NULL && array[0] != ITEM_NONE) {
			// Use generic item intro
			gSpecialVar_Result += 1;
		}
	}
	// Check for custom intro
	if (str != NULL) {
		gSpecialVar_Result += 2;
		ctx->data[0] = (u32)str;
		return;
	}
	// Check if this is the first puzzle, load as a custom intro
	if (VarGet(VAR_CURRENT_PUZZLE) == 0) { //first puzzle
		gSpecialVar_Result += 2;
		ctx->data[0] = (u32)PuzzleCommon_Text_FirstPuzzleIntro;
		return;
	}
}

extern const u8 PuzzleCommon_Text_DefaultQuip[];
void ShowPuzzleQuip(struct ScriptContext *ctx)
{
	u16 currPuzzle = GetCurrentPuzzleMapId();
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
	u16 currPuzzle = GetCurrentPuzzleMapId();
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
	// Note: This function might also overwrite string vars 2 and 3 as well, depending on how many items we give.
	u8 itemCount = 0;
	u16 currPuzzle = GetCurrentPuzzleMapId();
	const u16 *array = (u16*)GetMapHeaderString(currPuzzle, MAP_SCRIPT_PUZZLE_HEADER_PREREQ_LIST);
	
	gSpecialVar_Result = 0;
	*ptr = EOS;
	
	if (array != NULL)
	{
		while (array[0] != ITEM_NONE)
		{
			if (AddBagItem(array[0], 1)) {
				gSpecialVar_Result++;
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
	u16 currPuzzle = GetCurrentPuzzleMapId();
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

///////////////////////////////////////////////////////////////////////////////
// Puzzle Select Dialog

extern void LoadMapNamePopUpWindowBg(void);
const u8 sPuzzleText[] = _(" Pz {NO}: {STR_VAR_1}  ");
const u8 sDebugPuzzleText[] = _(" Db {NO}: {STR_VAR_1}  ");
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

static void ShowMapNamePopUpWindow(u16 num, bool8 mode)
{
    u8 mapDisplayHeader[0x100];
    u8 *withoutPrefixPtr;
    u8 x;
    const u8* mapDisplayHeaderSource;
	u16 currPuzzle = (mode) ? gDebugPuzzles[num-1] : gPuzzleList[num-1];

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


static void RedrawPuzzleSelectWindow(u8 windowId, u16 num, bool8 mode)
{
	const u8* txt = (mode)? sDebugPuzzleText : sPuzzleText;
	
	ConvertIntToDecimalStringN(gStringVar1, num, 2, 3);
    StringExpandPlaceholders(gStringVar3, txt);
    AddTextPrinterParameterized(windowId, 1, gStringVar3, 0, 1, 0, NULL);
	
	ShowMapNamePopUpWindow(num, mode);
}

#define tWindow data[0]
#define tSelected data[1]
#define tMax data[2]
#define tMainMax data[3]
#define tDebugMax data[4]
#define tMode data[5]

static void Task_InitPuzzleSelect(u8 taskId)
{
	u16 i;
    s16 *data = gTasks[taskId].data;
	
	for (i = 0; i < DEBUG_PUZZLE_START; i++) 
	{
		if (gPuzzleList[i] == 0xFFFF) break;
	}
	tMainMax = i;
	
	for (i = 0; i < DEBUG_PUZZLE_START; i++) 
	{
		if (gDebugPuzzles[i] == 0xFFFF) break;
	}
	tDebugMax = i;
	
	if (VarGet(VAR_CURRENT_PUZZLE) < DEBUG_PUZZLE_START) {
		tSelected = VarGet(VAR_CURRENT_PUZZLE) + 1;
		tMode = 0;
	} else {
		tSelected = VarGet(VAR_CURRENT_PUZZLE) - DEBUG_PUZZLE_START + 1;
		tMode = 1;
	}
	tMax = tMainMax;
	tWindow = AddWindow(&sPuzzleSelectWinTemplate);
 
	AddMapNamePopUpWindow();
	LoadMapNamePopUpWindowBg();
	
    DrawStdWindowFrame(tWindow, FALSE);
	FillWindowPixelBuffer(tWindow, PIXEL_FILL(1));
	RedrawPuzzleSelectWindow(tWindow, tSelected, tMode);
    schedule_bg_copy_tilemap_to_vram(0);

    gTasks[taskId].func = Task_PuzzleSelect;
}

static void Task_PuzzleSelect(u8 taskId)
{
    s16* data = gTasks[taskId].data;

    if (AdjustQuantityAccordingToDPadInput(&tSelected, tMax) == TRUE)
    {
        RedrawPuzzleSelectWindow(tWindow, tSelected, tMode);
    }
    else if (gMain.newKeys & A_BUTTON)
    {
		if (tMode)
        	VarSet(VAR_CURRENT_PUZZLE, tSelected-1+DEBUG_PUZZLE_START);
		else
			VarSet(VAR_CURRENT_PUZZLE, tSelected-1);
		goto exit;
    }
    else if (gMain.newKeys & B_BUTTON)
	{
		goto exit;
	}
    else if (gMain.newKeys & START_BUTTON)
	{
		tMode = !tMode;
		if (tMode)
			tMax = tDebugMax;
		else
			tMax = tMainMax;
		tSelected = 1;
		AdjustQuantityAccordingToDPadInput(&tSelected, tMax);
		RedrawPuzzleSelectWindow(tWindow, tSelected, tMode);
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
#if DEBUG
	CreateTask(Task_InitPuzzleSelect, 0);
#endif
}


#undef tWindow
#undef tSelected
#undef tMax


///////////////////////////////////////////////////////////////////////////////
// Sound Test Dialog

const u8 DebugScript_Text_SoundTest_SFX[] = _("SFX: {STR_VAR_1}");
const u8 DebugScript_Text_SoundTest_BGM[] = _("BGM: {STR_VAR_1}");
const u8 DebugScript_Text_SoundTest_PH[] = _("PH?: {STR_VAR_1}");
static const struct WindowTemplate sSoundTestWinTemplate =
{
	.bg = 0,
	.tilemapLeft = 20,
	.tilemapTop = 11,
	.width = 8,
	.height = 2,
	.paletteNum = 15,
	.baseBlock = 0x0176,
};

static void Task_MusicSelect(u8 taskId);

static void RedrawSongSelectWindow(u8 windowId, u16 num)
{
	const u8* txt = DebugScript_Text_SoundTest_SFX;
	num--;
	if (num >= MUS_TETSUJI) txt = DebugScript_Text_SoundTest_BGM;
	if (num >= PH_TRAP_BLEND) txt = DebugScript_Text_SoundTest_PH;
	
	ConvertIntToDecimalStringN(gStringVar1, num, 2, 3);
    StringExpandPlaceholders(gStringVar3, txt);
    AddTextPrinterParameterized(windowId, 1, gStringVar3, 0, 1, 0, NULL);
}

#define tWindow data[0]
#define tSelected data[1]
#define tMax data[2]
#define tMapMusic data[3]


static void Task_InitMusicSelect(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
	
	tSelected = MUS_TETSUJI + 1;
	tMax = PH_NURSE_SOLO + 1;
	tWindow = AddWindow(&sSoundTestWinTemplate);
	tMapMusic = GetCurrentMapMusic();
	
	StopMapMusic();
    DrawStdWindowFrame(tWindow, FALSE);
	FillWindowPixelBuffer(tWindow, PIXEL_FILL(1));
	RedrawSongSelectWindow(tWindow, tSelected);
    schedule_bg_copy_tilemap_to_vram(0);

    gTasks[taskId].func = Task_MusicSelect;
}

static void Task_MusicSelect(u8 taskId)
{
    s16* data = gTasks[taskId].data;

    if (AdjustQuantityAccordingToDPadInput(&tSelected, tMax) == TRUE)
    {
        RedrawSongSelectWindow(tWindow, tSelected);
    }
    else if (gMain.newKeys & A_BUTTON)
    {
        // PlaySE(SE_SELECT);
		PlayBGM(tSelected-1);
    }
    else if (gMain.newKeys & B_BUTTON)
	{
		PlayBGM(MUS_NONE);
	}
    else if (gMain.newKeys & START_BUTTON)
    {
        PlaySE(SE_SELECT);
        ClearStdWindowAndFrameToTransparent(tWindow, 0);
		ClearWindowTilemap(tWindow);
		RemoveWindow(tWindow);
		EnableBothScriptContexts();
		ResetMapMusic();
		PlayNewMapMusic(tMapMusic);
		DestroyTask(taskId);
    }
}

void DoSoundTest(struct ScriptContext *ctx)
{
	CreateTask(Task_InitMusicSelect, 0);
}

#undef tWindow
#undef tSelected
#undef tMax

