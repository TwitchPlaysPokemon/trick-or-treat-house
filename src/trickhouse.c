#include "global.h"
#include "trickhouse.h"
#include "main.h"
#include "menu.h"
#include "menu_helpers.h"
#include "event_data.h"
#include "script.h"
#include "task.h"
#include "credits.h"
#include "bg.h"
#include "alloc.h"
#include "window.h"
#include "text.h"
#include "text_window.h"
#include "string_util.h"
#include "sound.h"
#include "map_name_popup.h"
#include "item.h"
#include "money.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "overworld.h"
#include "field_message_box.h"
#include "battle_factory.h"
#include "battle_factory_screen.h"
#include "random.h"
#include "item.h"
#include "strings.h"
#include "battle_tower.h"
#include "start_menu.h"
#include "load_save.h"
#include "international_string_util.h"
#include "pokemon_summary_screen.h"
#include "field_screen_effect.h"
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
extern u32 gPuzzleTimer;
#define DEBUG_PUZZLE_START 32768

// Reference to an assembly defined constant, the start of the ROM
// We don't actually use the value, just the address it's at.
extern const int Start;

///////////////////////////////////////////////////////////////////////////////

u16 GetCurrentPuzzleMapId()
{
	u16 i = VarGet(VAR_CURRENT_PUZZLE);
	if (i < DEBUG_PUZZLE_START)
		return gPuzzleList[i];
	else
		return gDebugPuzzles[i-DEBUG_PUZZLE_START];
}

///////////////////////////////////////////////////////////////////////////////

extern const u8 PuzzleCommon_DefaultSetupScript[];
void RunPuzzleSetupScript()
{
	u16 currPuzzle = GetCurrentPuzzleMapId();
	if (!FlagGet(FLAG_PUZZLE_HAS_STARTED) &&
	    gSaveBlock1Ptr->location.mapGroup == (currPuzzle >> 8) &&
		gSaveBlock1Ptr->location.mapNum == (currPuzzle & 0xFF))
	{
		// Find and run a setup script
		const u8 *script = GetMapHeaderString(currPuzzle, MAP_SCRIPT_PUZZLE_SETUP_SCRIPT);
		if (script != NULL)
		{
			ScriptContext2_RunNewScript(script);
		}
		// 
		FlagSet(FLAG_PUZZLE_HAS_STARTED);
		gPuzzleTimer = gMain.vblankCounter1;
	}
}

extern const u8 PuzzleCommon_DefaultSetupScript[];
void RunPuzzleIntro()
{
	u16 currPuzzle = GetCurrentPuzzleMapId();
	if (!FlagGet(FLAG_IS_PUZZLE_INTRODUCED) &&
	    gSaveBlock1Ptr->location.mapGroup == (currPuzzle >> 8) &&
		gSaveBlock1Ptr->location.mapNum == (currPuzzle & 0xFF))
	{
		// Show map name
		ShowMapNamePopup();
		// 
		FlagSet(FLAG_IS_PUZZLE_INTRODUCED);
	}
}

extern const u8 PuzzleCommon_DefaultTeardownScript[];
void RunPuzzleTeardownScript()
{
	u16 currPuzzle = GetCurrentPuzzleMapId();
	if (FlagGet(FLAG_PUZZLE_HAS_STARTED) && 
		gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(TRICK_HOUSE_END) &&
		gSaveBlock1Ptr->location.mapNum == MAP_NUM(TRICK_HOUSE_END))
	{
		const u8 *script = GetMapHeaderString(currPuzzle, MAP_SCRIPT_PUZZLE_TEARDOWN_SCRIPT);
		if (script != NULL)
		{
			ScriptContext2_RunNewScript(script);
		}
		
		FlagClear(FLAG_PUZZLE_HAS_STARTED);
		FlagSet(FLAG_PUZZLE_HAS_COMPLETED);
		// set timer to the number of seconds it took to do the puzzle
		gPuzzleTimer = (gMain.vblankCounter1 - gPuzzleTimer) / 60;
	}
	
	if (gLastUsedWarp.mapGroup != MAP_GROUP(TRICK_HOUSE_END) &&
		gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(TRICK_HOUSE_END))
	{
		const u8 *script = GetMapHeaderString(currPuzzle, MAP_SCRIPT_PUZZLE_EXIT_SCRIPT);
		if (script != NULL)
		{
			ScriptContext2_RunNewScript(script);
		}
	}
}

void RunPuzzleBlackoutScript()
{
	u16 currPuzzle = GetCurrentPuzzleMapId();
	if (gSaveBlock1Ptr->location.mapGroup != MAP_GROUP(TRICK_HOUSE_END))
	{
		const u8 *script = GetMapHeaderString(currPuzzle, MAP_SCRIPT_PUZZLE_BLACKOUT_SCRIPT);
		if (script != NULL)
		{
			ScriptContext2_RunNewScript(script);
		}
	}
}

void RunPuzzleEscapeRopeScript()
{
	u16 currPuzzle = GetCurrentPuzzleMapId();
	if (gSaveBlock1Ptr->location.mapGroup != MAP_GROUP(TRICK_HOUSE_END))
	{
		const u8 *script = GetMapHeaderString(currPuzzle, MAP_SCRIPT_PUZZLE_ESCAPE_SCRIPT);
		if (script != NULL)
		{
			ScriptContext2_RunNewScript(script);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////

bool8 IsAfterFirstLoop()
{
	return (GetGameStat(GAME_STAT_NUM_PUZZLES_COMPLETED) > VarGet(VAR_CURRENT_PUZZLE));
}

void ClearPuzzleEventData(struct ScriptContext *ctx)
{
	memset(gSaveBlock1Ptr->flags + 0x04, 0, 0x0A);
	memset(gSaveBlock1Ptr->vars  + 0x20, 0, 0x40);
	memset(gSaveBlock1Ptr->flags + (FLAG_TRAINER_FLAG_START >> 3), 0, TRAINERS_PERMAP_END >> 3);
	memset(gSaveBlock1Ptr->flags + (FLAG_HIDDEN_ITEMS_START >> 3), 0, 0x20 >> 3);
	FlagClear(FLAG_PUZZLE_HAS_STARTED);
	FlagClear(FLAG_PUZZLE_HAS_COMPLETED);
	FlagClear(FLAG_HIDE_MAP_NAME_POPUP);
	gPuzzleTimer = 0;
}

void ClearTrainerFlags(struct ScriptContext *ctx)
{
	memset(gSaveBlock1Ptr->flags + (FLAG_TRAINER_FLAG_START >> 3), 0, TRAINERS_PERMAP_END >> 3);
}

// Input VAR_0x8000 = Puzzle to compare to
void CheckIfNextPuzzleIs(struct ScriptContext *ctx)
{
	u16 currPuzzle;
	u16 i = VarGet(VAR_CURRENT_PUZZLE);
	i++;
	if (i < DEBUG_PUZZLE_START)
		currPuzzle = gPuzzleList[i];
	else
		currPuzzle = gDebugPuzzles[i-DEBUG_PUZZLE_START];
	
	gSpecialVar_Result = (currPuzzle == gSpecialVar_0x8000);
}

void CheckIfNoMorePuzzles(struct ScriptContext *ctx)
{
	u16 currPuzzle = GetCurrentPuzzleMapId();
	gSpecialVar_Result = FALSE;
	if (currPuzzle == 0xFFFF) {
		gSpecialVar_Result = TRUE;
		// Temporarily, loop the puzzles.
		VarSet(VAR_CURRENT_PUZZLE, 0); //reset to 0
	}
}

void GetTrainerIDMod(struct ScriptContext *ctx)
{
    u16 trainerId = (gSaveBlock2Ptr->playerTrainerId[1] << 8) | gSaveBlock2Ptr->playerTrainerId[0];
	if (gSpecialVar_0x8000 == 0) gSpecialVar_0x8000 = 5;
    gSpecialVar_Result = trainerId % gSpecialVar_0x8000;
}

void GetNumPuzzlesCompleted(struct ScriptContext *ctx)
{
	gSpecialVar_Result = GetGameStat(GAME_STAT_NUM_PUZZLES_COMPLETED);
}

void SetupPuzzleWarp(struct ScriptContext *ctx)
{
	u16 currPuzzle = GetCurrentPuzzleMapId();
	if (currPuzzle == 0xFFFF) currPuzzle = MAP_TRICK_HOUSE_END; //sanity check
	SetDynamicWarp(0, currPuzzle >> 8, currPuzzle & 0xFF, 0);
}

extern const u8 PuzzleCommon_Text_FirstPuzzleIntro[];
extern const u8 PuzzleCommon_Text_FirstPuzzleIntroRound2[];
void LoadPuzzleIntro(struct ScriptContext *ctx)
{
	u16 currPuzzle = GetCurrentPuzzleMapId();
	const u8 *str;// = GetMapHeaderString(currPuzzle, MAP_SCRIPT_PUZZLE_CUSTOM_INTRO);
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
	// Check for custom intro script
	str = GetMapHeaderString(currPuzzle, MAP_SCRIPT_PUZZLE_CUSTOM_INTRO_SCRIPT);
	if (str != NULL) {
		ScriptJump(ctx, str);
		return;
	}
	// Check for custom intro
	str = GetMapHeaderString(currPuzzle, MAP_SCRIPT_PUZZLE_CUSTOM_INTRO);
	if (str != NULL) {
		gSpecialVar_Result += 2;
		ctx->data[0] = (u32)str;
		return;
	}
	// Check if this is the first puzzle, load as a custom intro
	if (VarGet(VAR_CURRENT_PUZZLE) == 0) { //first puzzle
		if (IsAfterFirstLoop()) {
			gSpecialVar_Result += 2;
			ctx->data[0] = (u32)PuzzleCommon_Text_FirstPuzzleIntroRound2;
			return;
		} else {
			gSpecialVar_Result += 2;
			ctx->data[0] = (u32)PuzzleCommon_Text_FirstPuzzleIntro;
			return;
		}
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

extern const u8 PuzzleCommon_Text_DefaultDevCommentary[];
void ShowPuzzleDevCommentary(struct ScriptContext *ctx)
{
	u16 currPuzzle = GetCurrentPuzzleMapId();
	const u8 *str = GetMapHeaderString(currPuzzle, MAP_SCRIPT_PUZZLE_DEV_COMMENTARY);
	if (str == NULL)
	{
		str = PuzzleCommon_Text_DefaultDevCommentary;
	}
	ShowFieldMessage(str);
}

extern const u8 PuzzleCommon_Text_DefaultFriendCommentary[];
void ShowPuzzleFriendCommentary(struct ScriptContext *ctx)
{
	u16 currPuzzle = GetCurrentPuzzleMapId();
	const u8 *str = GetMapHeaderString(currPuzzle, MAP_SCRIPT_PUZZLE_FRIEND_COMMENTARY);
	if (str == NULL)
	{
		str = PuzzleCommon_Text_DefaultFriendCommentary;
	}
	ShowFieldMessage(str);
}

extern const u8 PuzzleCommon_DefaultVariableAssignments[];
void AssignPuzzleMetaVariables(struct ScriptContext *ctx)
{
	u16 currPuzzle = GetCurrentPuzzleMapId();
	const u16 *array = (u16*)GetMapHeaderString(currPuzzle, MAP_SCRIPT_PUZZLE_META_VARIABLES);
	
	// Reset introducer to trick master by default
	VarSet(VAR_INTRO_PERSON, EVENT_OBJ_GFX_TRICK_MASTER);
	// Randomize quip person by default
	VarSet(VAR_QUIP_PERSON, (Random() % (EVENT_OBJ_GFX_FISHERMAN - EVENT_OBJ_GFX_BOY_1)) + EVENT_OBJ_GFX_BOY_1);
	// Set developer commentator to Tustin by default
	VarSet(VAR_DEV_COMMENTATOR, EVENT_OBJ_GFX_DEV_TUSTIN2121);
	// Set endroom friend to no one by default
	VarSet(VAR_ENDROOM_FRIEND, EVENT_OBJ_GFX_GHOST);
	
	if ((IsAfterFirstLoop() || gMain.debugMode) 
		&& GetMapHeaderString(currPuzzle, MAP_SCRIPT_PUZZLE_DEV_COMMENTARY) != NULL) 
	{
		FlagClear(FLAG_HIDE_DEVELOPER_COMMENTATOR);
	} else {
		FlagSet(FLAG_HIDE_DEVELOPER_COMMENTATOR);
	}
	
	if (array != NULL) {
		while (array[0] != 0) {
			VarSet(array[0], array[1]);
			array += 2;
		}
	}
	
	if (GetMapHeaderString(currPuzzle, MAP_SCRIPT_PUZZLE_FRIEND_COMMENTARY) != NULL) {
		// Gotta check to make sure the friend is not the person the player is controlling
		bool8 shouldShow = TRUE;
		switch (gSaveBlock2Ptr->playerGender) {
			case GENDER_M:
				shouldShow = VarGet(VAR_ENDROOM_FRIEND) != TTH_FRIEND_BRENDAN;
				break;
			case GENDER_F:
				shouldShow = VarGet(VAR_ENDROOM_FRIEND) != TTH_FRIEND_MAY;
				break;
			case GENDER_N:
				shouldShow = VarGet(VAR_ENDROOM_FRIEND) != TTH_FRIEND_ALEX;
				break;
		}
		if (shouldShow) {
			FlagClear(FLAG_HIDE_ENDROOM_FRIEND);
		} else {
			FlagSet(FLAG_HIDE_ENDROOM_FRIEND);
		}
	} else {
		FlagSet(FLAG_HIDE_ENDROOM_FRIEND);
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

void GatherLastPuzzleStats(struct ScriptContext *ctx)
{
	u16 currPuzzle = GetCurrentPuzzleMapId();
	const u16 *candyArray = (u16*)GetMapHeaderString(currPuzzle, MAP_SCRIPT_PUZZLE_CANDY_LIST);
	
	gSpecialVar_Result = FALSE;
	if (!FlagGet(FLAG_PUZZLE_HAS_COMPLETED) || gPuzzleTimer == 0 || candyArray == NULL) {
		return;
	}
	gSpecialVar_0x8000 = 0; //items count
	gSpecialVar_0x8001 = 0; //items found
	while (candyArray[0] != 0)
	{
		gSpecialVar_0x8000++;
		gSpecialVar_0x8001 += FlagGet(candyArray[0]);
		candyArray += 1;
	}
	gSpecialVar_0x8004 = (gPuzzleTimer) % 60; //seconds
	gSpecialVar_0x8003 = (gPuzzleTimer / 60) % 60; //minutes
	gSpecialVar_0x8002 = (gPuzzleTimer / (60*60)); //hours
	
	gSpecialVar_Result = TRUE;
}

void CheckAllCandyGotten(struct ScriptContext *ctx)
{
	u8 itemCount = 0, itemGotten = 0;
	u16 currPuzzle = GetCurrentPuzzleMapId();
	const u16 *array = (u16*)GetMapHeaderString(currPuzzle, MAP_SCRIPT_PUZZLE_CANDY_LIST);
	if (array != NULL) {
		while (array[0] != 0)
		{
			itemCount++;
			itemGotten += FlagGet(array[0]);
			array += 1;
		}
		gSpecialVar_Result = (itemCount == itemGotten);
	} else {
		gSpecialVar_Result = 0xFF;
	}
}

void CountCandyItems(struct ScriptContext *ctx)
{
	u8 itemCount = 0, itemGotten = 0;
	u16 currPuzzle = GetCurrentPuzzleMapId();
	const u16 *array = (u16*)GetMapHeaderString(currPuzzle, MAP_SCRIPT_PUZZLE_CANDY_LIST);
	if (array != NULL) {
		while (array[0] != 0)
		{
			itemCount++;
			itemGotten += FlagGet(array[0]);
			array += 1;
		}
		gSpecialVar_Result = (itemCount - itemGotten);
	} else {
		gSpecialVar_Result = 0xFF;
	}
}

void RemovePuzzleItems(struct ScriptContext *ctx)
{
	u8 pocket, a, b;
	struct ItemSlot takenItems[5];
	struct ItemSlot *tempBag = NULL;
	gSpecialVar_0x800A = 0; //monetary compensation
	gSpecialVar_Result = 0;
	
	for (pocket = 0; pocket < POCKETS_COUNT; pocket++)
	{
		tempBag = AllocZeroed(sizeof(struct ItemSlot) * gBagPockets[pocket].capacity);
		for (a = 0, b = 0; a < gBagPockets[pocket].capacity; a++) 
		{
			u16 itemId = gBagPockets[pocket].itemSlots[a].itemId;
			if (itemId == ITEM_NONE) continue;
			if (ItemId_GetPuzzleItemExclusionFlag(itemId))
			{
				tempBag[b++] = gBagPockets[pocket].itemSlots[a];
				// tempBag[b].itemId = gBagPockets[pocket].itemSlots[a].itemId;
				// tempBag[b].quantity = gBagPockets[pocket].itemSlots[a].quantity;
				// b++;
			}
			else
			{
				u16 price = ItemId_GetPrice(gBagPockets[pocket].itemSlots[a].itemId) >> 1;
				price *= GetBagItemQuantity(&gBagPockets[pocket].itemSlots[a].quantity);
				if (gSpecialVar_Result < ARRAY_COUNT(takenItems))
				{
					takenItems[gSpecialVar_Result] = gBagPockets[pocket].itemSlots[a];
				}
				gSpecialVar_Result++;
				gSpecialVar_0x800A += price;
			}
		}
		for (a = 0; a < gBagPockets[pocket].capacity; a++)
		{
			gBagPockets[pocket].itemSlots[a] = tempBag[a];
		}
		Free(tempBag);
	}
	tempBag = NULL; //cheat to eliminate special case in next loop
	if (gSpecialVar_0x800A) {
		AddMoney(&gSaveBlock1Ptr->money, gSpecialVar_0x800A);
	}
	
	// If items were taken, build a new string
	if (gSpecialVar_Result)
	{
		u8 nlcount = 0;
		u8 *ptr = gStringVar1;
		for (a = 0; a < ARRAY_COUNT(takenItems) && a < gSpecialVar_Result; a++)
		{
			if (a + 1 == gSpecialVar_Result && a > 0) {
				ptr = StringCopy(ptr, gText_And);
				(*ptr++) = CHAR_SPACE;
			}
			ptr = ConvertIntToTheNameStringN(ptr, GetBagItemQuantity(&takenItems[a].quantity), 0, 3);
			(*ptr++) = CHAR_SPACE;
			ptr = StringCopy(ptr, ItemId_GetName(takenItems[a].itemId));
			if (a + 1 < gSpecialVar_Result) {
				(*ptr++) = CHAR_COMMA;
				if (a % 2 == 0)
					(*ptr++) = (nlcount++)? CHAR_PROMPT_SCROLL : CHAR_NEWLINE;
				else
					(*ptr++) = CHAR_SPACE;
			}
		}
		if (gSpecialVar_Result > a) {
			ptr = StringCopy(ptr, gText_And);
			(*ptr++) = CHAR_SPACE;
			ptr = ConvertUIntToDecimalStringN(ptr, gSpecialVar_Result-a, 0, 3);
			(*ptr++) = CHAR_SPACE;
			ptr = StringCopy(ptr, gText_MoreItems);
		}
		*ptr = EOS;
	}
}

void RemoveExtraPokemon(struct ScriptContext *ctx)
{
	u8 i;
	
	gSpecialVar_Result = FALSE;
	CalculatePlayerPartyCount();
	if (gPlayerPartyCount <= 3) return;
	
	gSpecialVar_Result = TRUE;
	for (i = 3; i < PARTY_SIZE; i++) {
		if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES, NULL) == SPECIES_NONE) break;
		SendMonToPC(&gPlayerParty[i]);
		ZeroMonData(&gPlayerParty[i]);
	}
	CompactPartySlots();
    CalculatePlayerPartyCount();
}

///////////////////////////////////////////////////////////////////////////////
// Starter Pokemon

static const u16 starterPokemon[][3] = {
	{ SPECIES_GROVYLE, SPECIES_BAYLEEF, SPECIES_IVYSAUR },
	{ SPECIES_COMBUSKEN, SPECIES_QUILAVA, SPECIES_CHARMELEON },
	{ SPECIES_MARSHTOMP, SPECIES_CROCONAW, SPECIES_WARTORTLE },
	
	{ SPECIES_ELECTRIKE, SPECIES_JOLTEON, SPECIES_FLAAFFY },
	{ SPECIES_RATICATE, SPECIES_ZIGZAGOON, SPECIES_SENTRET },
	{ SPECIES_KIRLIA, SPECIES_ESPEON, SPECIES_SLOWPOKE },
	
	{ SPECIES_ABSOL, SPECIES_POOCHYENA, SPECIES_UMBREON },
	{ SPECIES_SPINARAK, SPECIES_NINJASK, SPECIES_PARAS },
	{ SPECIES_TEDDIURSA, SPECIES_ZANGOOSE, SPECIES_SPINDA },
	
	{ SPECIES_SCYTHER, SPECIES_HERACROSS, SPECIES_VOLBEAT },
	{ SPECIES_SWABLU, SPECIES_HOOTHOOT, SPECIES_SPEAROW },
	{ SPECIES_SNORUNT, SPECIES_SWINUB, SPECIES_SEEL },
};

static const u8 *const starterNames[][3] = {
	{ gText_StarterNameLeafy,  gText_DefaultNameZane,   gText_DefaultNameNickey  }, 
	{ gText_StarterNameBlitz,  gText_DefaultNameLex,    gText_StarterNameEthan  }, 
	{ gText_StarterNameSquirt, gText_DefaultNameRiver,  gText_DefaultNameEaston  }, 
	
	{ gText_StarterNameZipper, gText_StarterNameSparky, gText_DefaultNameZane  }, 
	{ gText_StarterNameAce,    gText_DefaultNameAvery,  gText_DefaultNameParker }, 
	{ gText_StarterNameKamon,  gText_DefaultNameTiara,  gText_DefaultNameCasey }, 
	
	{ gText_StarterNameLycan,  gText_StarterNameOrphen, gText_DefaultNameKenny }, 
	{ gText_StarterNameBugsy,  gText_StarterNameKetut,  gText_DefaultNameKris }, 
	{ gText_StarterNameTeddy,  gText_DefaultNameTeru,   gText_DefaultNameAlex }, 
	
	{ gText_DefaultNameParker, gText_StarterNameHardy,  gText_DefaultNameCharlie }, 
	{ gText_DefaultNameGale,   gText_StarterNameKenya,  gText_DefaultNameSkylar }, 
	{ gText_StarterNameBilli,  gText_DefaultNameSawyer, gText_StarterNameRin }, 
};

static const u8 *const previousOtNames[] = {
	gText_DefaultNameJoel,
	gText_DefaultNameAdele,
	gText_DefaultNameLennie,
	gText_DefaultNameNatalie,
	gText_DefaultNameConley,
	gText_DefaultNameCrystal,
	gText_DefaultNameJustin,
	gText_DefaultNameMadelyn,
	gText_DefaultNameHugo,
	gText_DefaultNameAmelia,
	gText_DefaultNameDiego,
	gText_DefaultNameHanna,
	gText_DefaultNameDuncan,
	gText_DefaultNameOctavia,
	gText_DefaultNameJoey,
	gText_DefaultNameCileste,
	gText_DefaultNameLogan,
	gText_DefaultNameEdna,
	gText_DefaultNameEvan,
	gText_DefaultNameSierra,
};

// Last box holds starters
#define STARTER_BOX 13

void GenerateStarterMon(u16 slot, struct BoxPokemon* mon)
{
	const u8* nick;
	u16 speciesId = SPECIES_UNOWN;
	
	if (FlagGet(FLAG_SYS_RANDOM_DISABLED)) {
		speciesId = starterPokemon[slot][0];
		nick = starterNames[slot][0];
	} else {
		speciesId = starterPokemon[slot][Random() % 3];
		switch (Random() % 4) {
			case 0: nick = NULL; break;
			case 1: nick = starterNames[slot][0]; break;
			case 2: nick = starterNames[slot][1]; break;
			case 3: nick = starterNames[slot][2]; break;
		}
	}
	
	CreateBoxMon(mon, speciesId, 30, 32, 0, 0, OT_ID_PRESET, Random32());
	SetBoxMonData(mon, MON_DATA_OT_NAME, previousOtNames[Random() % ARRAY_COUNT(previousOtNames)]);
	if (nick != NULL) SetBoxMonData(mon, MON_DATA_NICKNAME, nick);
}

// In: gSpecialVar_MonBoxPos = Slot to get
// Out: gSpecialVar_0x8001 = Species of Pokemon in this slot
void GetOrGenerateStarterPokemon(struct ScriptContext *ctx)
{
	struct BoxPokemon* mon;
	u16 slot = gSpecialVar_MonBoxPos;
	
	if (gSpecialVar_MonBoxPos >= 12) return;
	
	mon = GetBoxedMonPtr(STARTER_BOX, slot);
	if (GetBoxMonData(mon, MON_DATA_SPECIES, NULL) == SPECIES_NONE)
	{
		GenerateStarterMon(slot, mon);
	}
	gSpecialVar_0x8001 = GetBoxMonData(mon, MON_DATA_SPECIES, NULL);
	
	GetBoxMonData(mon, MON_DATA_NICKNAME, gStringVar1);
    StringGetEnd10(gStringVar1);
}

void ShowStarterMonSummaryScreen(struct ScriptContext *ctx)
{
	u16 slot = gSpecialVar_MonBoxPos;
	struct BoxPokemon* mon = GetBoxedMonPtr(STARTER_BOX, slot);
	if (gSpecialVar_MonBoxPos >= 12) return;
	
	ShowPokemonSummaryScreen(PSS_MODE_BOX, mon, 0, 0, CB2_ReturnToField);
	gFieldCallback = FieldCB_ContinueScriptHandleMusic;
}

void GivePlayerStarterMon(struct ScriptContext *ctx)
{
	u16 slot = gSpecialVar_MonBoxPos;
	if (gSpecialVar_MonBoxPos >= 12) return;
	
	CalculatePlayerPartyCount();
	GetMonFromPCSlot(&gPlayerParty[gPlayerPartyCount], STARTER_BOX, slot);
	CompactPartySlots();
	CalculatePlayerPartyCount();
}

void CleanUpStarterMon(struct ScriptContext *ctx)
{
	static const u8 addressSlots[] = { 1, 4, 7, 10, 0, 3, 6, 9, 2, 5, 8, 11 };
	u8 start = 0, i = 0, destSlot = IN_BOX_COUNT - 9;
	
	// Generate any mons that haven't been already and weren't chosen
	for (i = 0; i < 12; i++) {
		struct BoxPokemon* mon = GetBoxedMonPtr(STARTER_BOX, i);
		if (GetBoxMonData(mon, MON_DATA_SPECIES, NULL) != SPECIES_NONE) continue;
		if (FlagGet(FLAG_TEMP_1+i)) continue;
		GenerateStarterMon(i, mon);
	}
	
	// Move the remaining pokemon to the end of the box, 
	// we'll try to use them for rival fights later.
	if (!FlagGet(FLAG_SYS_RANDOM_DISABLED)) {
		start = Random() % 12;
	}
	for (i = 0; i < 12; i++) {
		u8 srcSlot = addressSlots[(start + i) % 12];
		struct BoxPokemon* mon = GetBoxedMonPtr(STARTER_BOX, srcSlot);
		if (GetBoxMonData(mon, MON_DATA_SPECIES, NULL) == SPECIES_NONE) continue;
		SetBoxMonAt(STARTER_BOX, destSlot, mon);
		ZeroBoxMonData(mon);
		destSlot++;
	}
}

///////////////////////////////////////////////////////////////////////////////

void BufferItemPrice(struct ScriptContext *ctx)
{
	gSpecialVar_0x8006 = ItemId_GetPrice(gSpecialVar_0x8004);
	ConvertIntToDecimalStringN(gStringVar1, gSpecialVar_0x8006, 0, 3);
}

///////////////////////////////////////////////////////////////////////////////

void SetContinueGameWarp(s8 mapGroup, s8 mapNum, s8 warpId, s8 x, s8 y);
void SaveForCredits(struct ScriptContext *ctx)
{
	SetContinueGameWarpStatus();
	SetContinueGameWarp(MAP_GROUP(TRICK_HOUSE_ENTRANCE), MAP_NUM(TRICK_HOUSE_ENTRANCE), -1, 7, 4);
	ForceSaveGame();
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
		tMax = tMainMax;
	} else {
		tSelected = VarGet(VAR_CURRENT_PUZZLE) - DEBUG_PUZZLE_START + 1;
		tMode = 1;
		tMax = tDebugMax;
	}
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

///////////////////////////////////////////////////////////////////////////////
// Number Select Dialog

static const struct WindowTemplate sNumberSelectWinTemplate =
{
	.bg = 0,
	.tilemapLeft = 22,
	.tilemapTop = 11,
	.width = 6,
	.height = 2,
	.paletteNum = 15,
	.baseBlock = 0x0176,
};

static void Task_NumberSelect(u8 taskId);

static void RedrawNumberSelectWindow(u8 windowId, u16 num)
{
	ConvertIntToDecimalStringN(gStringVar1, num, 2, 6);
    AddTextPrinterParameterized(windowId, 1, gStringVar1, 0, 1, 0, NULL);
}

#define tWindow data[0]
#define tSelected data[1]
#define tMax data[2]

static void Task_InitNumberSelect(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
	tWindow = AddWindow(&sNumberSelectWinTemplate);
	
    DrawStdWindowFrame(tWindow, FALSE);
	FillWindowPixelBuffer(tWindow, PIXEL_FILL(1));
	RedrawNumberSelectWindow(tWindow, tSelected);
    schedule_bg_copy_tilemap_to_vram(0);

    gTasks[taskId].func = Task_NumberSelect;
}

static void Task_NumberSelect(u8 taskId)
{
    s16* data = gTasks[taskId].data;

    if (AdjustQuantityAccordingToDPadInput(&tSelected, tMax) == TRUE)
    {
        RedrawNumberSelectWindow(tWindow, tSelected);
    }
    else if (gMain.newKeys & A_BUTTON)
    {
		gSpecialVar_Result = tSelected;
        PlaySE(SE_SELECT);
        ClearStdWindowAndFrameToTransparent(tWindow, 0);
		ClearWindowTilemap(tWindow);
		RemoveWindow(tWindow);
		EnableBothScriptContexts();
		DestroyTask(taskId);
    }
    else if (gMain.newKeys & B_BUTTON)
    {
		gSpecialVar_Result = -1;
        PlaySE(SE_SELECT);
        ClearStdWindowAndFrameToTransparent(tWindow, 0);
		ClearWindowTilemap(tWindow);
		RemoveWindow(tWindow);
		EnableBothScriptContexts();
		DestroyTask(taskId);
    }
}

void ChooseNumber(struct ScriptContext *ctx)
{
	u8 taskId = CreateTask(Task_InitNumberSelect, 0);
	s16 *data = gTasks[taskId].data;
	
	tSelected = ctx->data[0];
	tMax = ctx->data[1];
}

void ChooseNumberOfTradeItems(struct ScriptContext *ctx)
{
	u8 taskId = CreateTask(Task_InitNumberSelect, 0);
	s16 *data = gTasks[taskId].data;
	
	tSelected = 1;
	tMax = CountTotalItemQuantityInBag(VarGet(VAR_0x8002));
}

#undef tWindow
#undef tSelected
#undef tMax

///////////////////////////////////////////////////////////////////////////////

void PlayCredits(struct ScriptContext *ctx)
{
	SetMainCallback2(CB2_StartCreditsSequence);
}

void DebugGetGameStat(struct ScriptContext *ctx)
{
	gSpecialVar_Result = ctx->data[0] = GetGameStat(ctx->data[1]);
}

void DebugSetGameStat(struct ScriptContext *ctx)
{
	
	SetGameStat(ctx->data[1], ctx->data[0]);
}

