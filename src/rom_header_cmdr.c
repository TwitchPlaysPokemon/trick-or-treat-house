#include "global.h"
#include "window.h"
#include "battle.h"
#include "battle_controllers.h"
#include "reshow_battle_screen.h"
#include "naming_screen.h"
#include "pokemon_summary_screen.h"
#include "string_util.h"
#include "item_menu.h"
#include "main.h"
#include "menu.h"
#include "party_menu.h"
#include "contest.h"

extern struct NamingScreenData *sNamingScreen;
extern struct PokemonSummaryScreenData *sMonSummaryScreen;
extern u8 sYesNoWindowId;
extern u16 sCurrentMapMusic;
extern struct Menu sMenu;
extern struct EvoInfo *sEvoStructPtr;
extern void CB2_ReturnToPartyMenuWhileLearningMove(void);
extern struct PartyMenuInternal *sPartyMenuInternal;
extern void HandleInputChooseTarget(void);
extern void HandleMoveSwitching(void);
extern void CB2_ReturnToPartyMenuFromSummaryScreen(void);

// Similar to the GF ROM header, this struct makes it easier to use the Commander.lua script
struct CommanderRomHeader
{
    /*0x00*/ char cmdr_magic[4]; // 'CMDR'. Useful to locate the header if it shifts.
    /*0x04*/ u32 Windows;
    /*0x08*/ u32 TargetingCursor;
    /*0x0C*/ u32 TargetingControllerFunction;
    /*0x10*/ u32 MoveSwitchingControllerFunction;
    /*0x14*/ u32 FirstMonBattleController;
    /*0x18*/ u32 SecondMonBattleController;
    /*0x1C*/ u32 NicknameScreen;
    /*0x20*/ u32 PokemonSummaryScreen;
    /*0x24*/ u32 PokemonSummaryScreenCallbackOffset;
    /*0x28*/ u32 SummaryReturnToBattle;
    /*0x2C*/ u32 SummaryReturnToParty;
    /*0x30*/ u32 SummaryReturnToTMLearn;
    /*0x34*/ u32 CursorMoveLearnOffset;
    /*0x38*/ u32 DialogText;
    /*0x3C*/ u32 BattleText;
    /*0x40*/ u32 BattleFlags;
    /*0x44*/ u32 BattleResources;
    /*0x48*/ u32 MenuIdOffset;
    /*0x4C*/ u32 DoubleBattleMenuIdOffset;
    /*0x50*/ u32 YesNoWindowId;
    /*0x54*/ u32 BattleMoveLearnState;
    /*0x58*/ u32 BattleCommunicationState;
    /*0x5C*/ u32 CursorYesNo;
    /*0x60*/ u32 CursorBattle;
    /*0x64*/ u32 CursorDoubleBattle;
    /*0x68*/ u32 CursorFight;
    /*0x6C*/ u32 CursorDoubleFight;
    /*0x70*/ u32 BagId;
    /*0x74*/ u32 CursorBagStart;
    /*0x78*/ u32 ScrollBagStart;
    /*0x7C*/ u32 SaveBlock1Pointer;
    /*0x80*/ u32 SaveBlock2Pointer;
    /*0x84*/ u32 CurrentMusic;
    /*0x88*/ u32 InBattle;
    /*0x8C*/ u32 CursorSubmenu;
    /*0x90*/ u32 PartyMenu;
    /*0x94*/ u32 BagMenu;
    /*0x98*/ u32 Evolution;
    /*0x9C*/ u32 SecurityKeyOffset;
    /*0xA0*/ u32 ContestResources;
    /*0xA4*/ u32 PartyMenuInternal;
    /*0xA8*/ u32 ItemsOffset;
    /*0xAC*/ u8 pcItemsCount;
    /*0xAD*/ u8 bagCountItems;
    /*0xAE*/ u8 bagCountKeyItems;
    /*0xAF*/ u8 bagCountCandy;
    /*0xB0*/ u8 bagCountTMHMs;
    /*0xB1*/ u8 bagCountBerries;
};

__attribute__((section(".text.header_cmdr")))
static const struct CommanderRomHeader sCommanderRomHeader =
{
    .cmdr_magic = { 'C', 'M', 'D', 'R' },
    .Windows = (u32) &gWindows,
    .TargetingCursor = (u32) &gMultiUsePlayerCursor,
    .TargetingControllerFunction = (u32) &HandleInputChooseTarget,
    .MoveSwitchingControllerFunction = (u32) &HandleMoveSwitching,
    .FirstMonBattleController = (u32) &gBattlerControllerFuncs[0],
    .SecondMonBattleController = (u32) &gBattlerControllerFuncs[2],
    .NicknameScreen = (u32) &sNamingScreen,
    .PokemonSummaryScreen = (u32) &sMonSummaryScreen,
    .PokemonSummaryScreenCallbackOffset = offsetof(struct PokemonSummaryScreenData, callback),
    .SummaryReturnToBattle = (u32) &ReshowBattleScreenAfterMenu,
    .SummaryReturnToParty = (u32) &CB2_ReturnToPartyMenuFromSummaryScreen,
    .SummaryReturnToTMLearn = (u32) &CB2_ReturnToPartyMenuWhileLearningMove,
    .CursorMoveLearnOffset = offsetof(struct PokemonSummaryScreenData, firstMoveIndex),
    .DialogText = (u32) &gStringVar4,
    .BattleText = (u32) &gDisplayedStringBattle,
    .BattleFlags = (u32) &gBattleTypeFlags,
    .BattleResources = (u32) &gBattleResources,
    .MenuIdOffset = offsetof(struct BattleResources, bufferA[0][0]),
    .DoubleBattleMenuIdOffset = offsetof(struct BattleResources, bufferA[2][0]),
    .YesNoWindowId = (u32) &sYesNoWindowId,
    .BattleMoveLearnState = (u32) &gBattleScripting.learnMoveState,
    .BattleCommunicationState = (u32) &gBattleCommunication[MULTIUSE_STATE],
    .CursorYesNo = (u32) &gBattleCommunication[CURSOR_POSITION],
    .CursorBattle = (u32) &gActionSelectionCursor[0],
    .CursorDoubleBattle = (u32) &gActionSelectionCursor[2],
    .CursorFight = (u32) &gMoveSelectionCursor[0],
    .CursorDoubleFight = (u32) &gMoveSelectionCursor[2],
    .BagId = (u32) &gBagPosition.pocket,
    .CursorBagStart = (u32) &gBagPosition.cursorPosition,
    .ScrollBagStart = (u32) &gBagPosition.scrollPosition,
    .SaveBlock1Pointer = (u32) &gSaveBlock1Ptr,
    .SaveBlock2Pointer = (u32) &gSaveBlock2Ptr,
    .CurrentMusic = (u32) &sCurrentMapMusic,
    .InBattle = ((u32) &gMain) + offsetof(struct Main, state) + 1,
    .CursorSubmenu = (u32) &sMenu.cursorPos,
    .PartyMenu = (u32) &gPartyMenu,
    .BagMenu = (u32) &gBagMenu,
    .Evolution = (u32) &sEvoStructPtr,
    .SecurityKeyOffset = offsetof(struct SaveBlock2, encryptionKey),
    .ContestResources = (u32) &gContestResources,
    .PartyMenuInternal = (u32) &sPartyMenuInternal,
    .bagCountItems = BAG_ITEMS_COUNT,
    .bagCountKeyItems = BAG_KEYITEMS_COUNT,
    .bagCountCandy = BAG_CANDY_COUNT,
    .bagCountTMHMs = BAG_TMHM_COUNT,
    .bagCountBerries = BAG_BERRIES_COUNT,
    .pcItemsCount = PC_ITEMS_COUNT,
    .ItemsOffset = offsetof(struct SaveBlock1, bagPocket_Candy),
};
