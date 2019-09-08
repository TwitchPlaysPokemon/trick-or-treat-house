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
#include "field_camera.h"
#include "fieldmap.h"
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
	memset(gSaveBlock1Ptr->flags + (FLAG_HIDDEN_ITEMS_START >> 3), 0, 0x20 >> 8);
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


///////////////////////////////////////////////////////////////////////////////
// Water Temple Natives

#define X (x+7)
#define Y (y+7)

// VAR_0x8001 => 0 = make random currents, 1 = lower water level, 2 = almost drained
void WaterTempleDrainTo1(struct ScriptContext *ctx)
{
	int x, y, mtid;
	for (y = 14; y < 26; y++) {
		for (x = 32; x < 48; x++) {
			mtid = MapGridGetMetatileIdAt(X, Y);
			if (gSpecialVar_0x8001 == 1) {
				// Lower water level around rocks
				switch (mtid) {
					case 0x23A: mtid = 0x222; break;
					case 0x242: mtid = 0x22A; break;
					case 0x24A: mtid = 0x232; break;
					case 0x249: mtid = 0x231; break;
					case 0x248: mtid = 0x230; break;
					case 0x240: mtid = 0x228; break;
					case 0x238: mtid = 0x220; break;
					case 0x239: mtid = 0x221; break;
				}
			} 
			else if (gSpecialVar_0x8001 == 2) {
				// Lower water level around rocks
				switch (mtid) {
					case 0x222: mtid = 0x252; break;
					case 0x22A: mtid = 0x25A; break;
					case 0x232: mtid = 0x262; break;
					case 0x231: mtid = 0x261; break;
					case 0x230: mtid = 0x260; break;
					case 0x228: mtid = 0x258; break;
					case 0x220: mtid = 0x250; break;
					case 0x221: mtid = 0x251; break;
					case 0x21E: case 0x207: case 0x206: case 0x21F:
					case 0x170: mtid = 0x19E; break;
				}
			}
			else {
				if (mtid == 0x170 && (Random() % 3) == 0) {
					if (y >= 15 && y <= 21) mtid = 0x207;
					else mtid = 0x21E;
				}
			}
			MapGridSetMetatileIdAt(X, Y, mtid);
		}
	}
	DrawWholeMapView();
}

// VAR_0x8001 => 0 = make random currents, 1 = lower water level, 2 = almost drained
void WaterTempleDrainTo2(struct ScriptContext *ctx)
{
	int x, y, mtid;
	for (y = 8; y < 20; y++) {
		for (x = 23; x < 40; x++) {
			mtid = MapGridGetMetatileIdAt(X, Y);
			if (gSpecialVar_0x8001 == 1) {
				// Lower water level around rocks
				switch (mtid) {
					case 0x23D: mtid = 0x225; break;
					case 0x245: mtid = 0x22D; break;
					case 0x24D: mtid = 0x235; break;
					case 0x24C: mtid = 0x234; break;
					case 0x24B: mtid = 0x233; break;
					case 0x243: mtid = 0x22B; break;
					case 0x23B: mtid = 0x223; break;
					case 0x23C: mtid = 0x224; break;
				}
			} 
			else if (gSpecialVar_0x8001 == 2) {
				// Lower water level around rocks
				switch (mtid) {
					case 0x225: mtid = 0x257; break;
					case 0x22D: mtid = 0x25F; break;
					case 0x235: mtid = 0x267; break;
					case 0x234: mtid = 0x24F; break;
					case 0x233: mtid = 0x266; break;
					case 0x22B: mtid = 0x25E; break;
					case 0x223: mtid = 0x256; break;
					case 0x224: mtid = 0x24E; break;
				}
				switch (mtid) {
					case 0x21E: case 0x207: case 0x206: case 0x21F:
					case 0x170: {
						if (y == 8) 
							mtid = (x >= 33 && x <= 36)? 0x207 : 0x19E; 
						else if (y <= 11)
							mtid = (x <= 36)? 0x21E : 0x19E; 
						else
							mtid = (x <= 25)? 0x207 : 0x19E; 
					} break;
				}
			}
			else {
				if (mtid == 0x170 && (Random() % 3) == 0) {
					if (x <= 29) mtid = 0x207;
					else mtid = 0x21E;
				}
			}
			MapGridSetMetatileIdAt(X, Y, mtid);
		}
	}
	DrawWholeMapView();
}

// VAR_0x8001 => 0 = make random currents, 1 = remove random currents, 2 = convert sand, 3 = convert to water, 4 = fill
void WaterTempleFillTo1(struct ScriptContext *ctx)
{
	int x, y, mtid;
	for (y = 19; y < 31; y++) {
		for (x = 27; x < 43; x++) {
			mtid = MapGridGetMetatileIdAt(X, Y);
			if (gSpecialVar_0x8001 == 4) {
				// Raise water level around rocks
				switch (mtid) {
					case 0x21C: mtid = 0x234; break;
					case 0x21B: mtid = 0x233; break;
					case 0x213: mtid = 0x22B; break;
				}
			} 
			else if (gSpecialVar_0x8001 == 3) {
				// convert shallows to water
				switch (mtid) {
					case 0x19E:
					case 0x1AF:
					case 0x1B7:
					case 0x1BF:
					case 0x1BE:
					case 0x1BD:
					case 0x1B5:
					case 0x1AD:
					case 0x1AE: mtid = 0x170; break;
					case 0x24F: mtid = 0x21C; break;
					case 0x266: mtid = 0x21B; break;
					case 0x25E: mtid = 0x213; break;
				}
			}
			else if (gSpecialVar_0x8001 == 2) {
				// convert sand to shallows
				switch (mtid) {
					case 0x121: mtid = 0x19E; break;
					case 0x11D: mtid = 0x1AF; break;
					case 0x125: mtid = 0x1B7; break;
					case 0x12D: mtid = 0x1BF; break;
					case 0x12C: mtid = 0x1BE; break;
					case 0x12B: mtid = 0x1BD; break;
					case 0x123: mtid = 0x1B5; break;
					case 0x11B: mtid = 0x1AD; break;
					case 0x11C: mtid = 0x1AE; break;
					case 0x264: mtid = 0x24F; break;
					case 0x263: mtid = 0x266; break;
					case 0x25B: mtid = 0x25E; break;
				}
			}
			else if (gSpecialVar_0x8001 == 1) {
				if ((mtid == 0x206 || mtid == 0x21F) && (Random() % 3) == 0) {
					mtid = 0x170;
				}
			}
			else {
				if (mtid == 0x170 && (Random() % 3) == 0) {
					if (x <= y - 6) mtid = 0x207;
					else mtid = 0x21F;
				}
			}
			MapGridSetMetatileIdAt(X, Y, mtid);
		}
	}
	DrawWholeMapView();
}

// VAR_0x8001 => 0 = make random currents, 1 = remove random currents, 2 = convert sand, 3 = convert to water, 4 = fill
void WaterTempleFillTo0(struct ScriptContext *ctx)
{
	int x, y, mtid;
	for (y = 22; y < 35; y++) {
		for (x = 2; x < 18; x++) {
			mtid = MapGridGetMetatileIdAt(X, Y);
			if (gSpecialVar_0x8001 == 4) {
				// Raise water level around rocks
				switch (mtid) {
					case 0x261: mtid = 0x231; break;
					case 0x262: mtid = 0x232; break;
					case 0x25A: mtid = 0x22A; break;
				}
			} 
			else if (gSpecialVar_0x8001 == 3) {
				// convert shallows to water
				switch (mtid) {
					case 0x29E:
					case 0x19E:
					case 0x1AF:
					case 0x1B7:
					case 0x1BF:
					case 0x1BE:
					case 0x1BD:
					case 0x1B5:
					case 0x1AD:
					case 0x1AE: mtid = 0x170; break;
				}
			}
			else if (gSpecialVar_0x8001 == 2) {
				// convert sand to shallows
				switch (mtid) {
					case 0x23D: mtid = 0x1AF; break;
					case 0x245: mtid = 0x1B7; break;
					case 0x24D: mtid = 0x1BF; break;
					case 0x244:
					case 0x28E:
					case 0x24C: mtid = 0x1BE; break;
					case 0x24B: mtid = 0x1BD; break;
					case 0x243: mtid = 0x1B5; break;
					case 0x23B: mtid = 0x1AD; break;
					case 0x23C: mtid = 0x1AE; break;
					case 0x29B:
					case 0x214: mtid = 0x19E; break;
					case 0x29C: mtid = 0x29E; break;
				}
			}
			else if (gSpecialVar_0x8001 == 1) {
				if ((mtid == 0x206 || mtid == 0x21F) && (Random() % 3) == 0) {
					mtid = 0x170;
				}
			}
			else {
				if (mtid == 0x170 && (Random() % 3) == 0) {
					mtid = 0x21F;
				}
			}
			MapGridSetMetatileIdAt(X, Y, mtid);
		}
	}
	DrawWholeMapView();
}


///////////////////////////////////////////////////////////////////////////////
// Puzzle Select Dialog

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
    StringExpandPlaceholders(gStringVar3, txt);
    AddTextPrinterParameterized(windowId, 1, gStringVar3, 0, 1, 0, NULL);
	
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

