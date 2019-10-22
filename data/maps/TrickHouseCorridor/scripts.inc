TrickHouseCorridor_MapScripts:: @ 826B903
	map_script MAP_SCRIPT_ON_LOAD, TrickHouseCorridor_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, TrickHouseCorridor_FrameTable
	map_script MAP_SCRIPT_ON_TRANSITION, TrickHouseCorridor_Transition
	.byte 0

@ -----------------------------------------------------

TrickHouseCorridor_Transition:
	callnative SetupPuzzleWarp
	callnative AssignPuzzleMetaVariables
	end

@ -----------------------------------------------------

TrickHouseCorridor_OnLoad:
	compare VAR_PUZZLE_STATE, 2
	call_if_eq TrickHouseCorridor_OpenBackDoor
	compare VAR_PUZZLE_STATE, 1
	call_if_eq TrickHouseCorridor_OpenPuzzleDoor
	end

TrickHouseCorridor_OpenPuzzleDoor:
	setmetatile 22, 2, 0x01F, FALSE
	return

TrickHouseCorridor_OpenBackDoor:
	setmetatile 4, 6, 0x01E, TRUE
	return
TrickHouseCorridor_CloseBackDoor:
	setmetatile 4, 6, 0x21B, TRUE
	return

@ -----------------------------------------------------

TrickHouseCorridor_FrameTable:
	map_script_2 VAR_PUZZLE_STATE, 2, TrickHouseCorridor_IncrementPuzzle
	map_script_2 VAR_TEMP_E, 0, TrickHouseCorridor_SetupPokemonTableStop
	.2byte 0

TrickHouseCorridor_IncrementPuzzle:
	call PuzzleCommon_EventScript_IncrementPuzzle
	clearflag FLAG_HIDE_TRICK_HOUSE_INTRO_CHAR
	callnative SetupPuzzleWarp
	callnative AssignPuzzleMetaVariables
	call TrickHouseCorridor_CloseBackDoor
	end

TrickHouseCorridor_SetupPokemonTableStop:
	goto_if_set FLAG_SYS_POKEMON_GET, TrickHouseCorridor_SetupPokemonTableStop2
	setvar VAR_TEMP_E, 1
	end
TrickHouseCorridor_SetupPokemonTableStop2:
	setvar VAR_TEMP_E, 2
	end

@ -----------------------------------------------------

TrickHouseCorridor_EventScript_PokemonTable::
	lockall
	goto_if_set FLAG_TEMP_E, TrickHouseCorridor_EventScript_PokemonTable_GoodLuck
	goto_if_unset FLAG_SYS_POKEMON_GET, TrickHouseCorridor_EventScript_PokemonTable_FirstRental
	goto TrickHouseCorridor_EventScript_PokemonTable_Swap
	end

TrickHouseCorridor_EventScript_PokemonTable_GoodLuck:
	msgbox TrickHouseCorridor_Text_PokemonTable_GoodLuck
	releaseall
	end
TrickHouseCorridor_Text_PokemonTable_GoodLuck:
	.string "Good luck on the PUZZLE CHALLENGE!$"

TrickHouseCorridor_EventScript_PokemonTable_FirstRental:
	msgbox TrickHouseCorridor_Text_PokemonTable_FirstRental1
	fadescreen 1
	callnative SelectInitialRentalParty
	waitstate
	setflag FLAG_TEMP_E
	setvar VAR_TEMP_E, 2
	msgbox TrickHouseCorridor_Text_PokemonTable_FirstRental2
	releaseall
	end
TrickHouseCorridor_Text_PokemonTable_FirstRental1:
	.string "Good evening! It looks like you'll be\n"
	.string "needing some POKéMON to battle with!\p"
	.string "Fortunately, the TRICK MASTER hired us\n"
	.string "to give out RENTAL POKéMON to his\l"
	.string "adoring participants tonight!\p"
	.string "Take a look at what we have!$"
TrickHouseCorridor_Text_PokemonTable_FirstRental2:
	.string "Excellent selection!\p"
	.string "If you'd ever like to swap out, feel\n"
	.string "free to come back to this table!\p"
	.string "Good luck on the PUZZLE CHALLENGE!$"

TrickHouseCorridor_EventScript_PokemonTable_Swap:
	msgbox TrickHouseCorridor_Text_PokemonTable_Swap1, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq TrickHouseCorridor_EventScript_PokemonTable_GoodLuck
	fadescreen 1
	special HealPlayerParty
	callnative SwapRentalParty
	waitstate
	setflag FLAG_TEMP_E
	msgbox TrickHouseCorridor_Text_PokemonTable_FirstRental2
	releaseall
	end
TrickHouseCorridor_Text_PokemonTable_Swap1:
	.string "Good evening! How are you doing on\n"
	.string "your PUZZLE CHALLENGE?\p"
	.string "Would you like to swap some of your\n"
	.string "RENTAL POKéMON?$"


TrickHouseCorridor_TriggerScript_PokemonTable::
	getplayerxy VAR_0x8000, VAR_0x8001
	subvar VAR_0x8001, 7
	@
	applymovement 1, Common_Movement_ExclamationMarkAndWait
	waitmovement 0
	msgbox TrickHouseCorridor_Text_PokemonTable_Stop1
	closemessage
	@ Walk up
	selectpointer TrickHouseCorridor_MovementTable_PokemonTableStop, VAR_0x8001
	applymovement EVENT_OBJ_ID_PLAYER, 0
	waitmovement 0
	@
	msgbox TrickHouseCorridor_Text_PokemonTable_Stop2
	fadescreen 1
	callnative SelectInitialRentalParty
	waitstate
	setflag FLAG_TEMP_E
	setvar VAR_TEMP_E, 2
	msgbox TrickHouseCorridor_Text_PokemonTable_FirstRental2
	releaseall
	end
TrickHouseCorridor_Text_PokemonTable_Stop1:
	.string "Hey!\n"
	.string "You don't have any POKéMON, do you?\p"
	.string "You're gonna need some to take on the\n"
	.string "PUZZLE CHALLENGE! Com'on over here!$"
TrickHouseCorridor_Text_PokemonTable_Stop2:
	.string "The TRICK MASTER hired us to give\n"
	.string "out RENTAL POKéMON to his\l"
	.string "adoring participants tonight!\p"
	.string "Take a look at what we have!$"

.align 2
TrickHouseCorridor_MovementTable_PokemonTableStop:
	.4byte TrickHouseCorridor_Movement_PokemonTableStop1
	.4byte TrickHouseCorridor_Movement_PokemonTableStop2
	.4byte 0
TrickHouseCorridor_Movement_PokemonTableStop1:
	walk_left
	walk_in_place_fastest_up
	step_end
TrickHouseCorridor_Movement_PokemonTableStop2:
	walk_left
	walk_up
	step_end

@ -----------------------------------------------------

TrickHouseCorridor_EventScript_IntroCharacter::
	compare VAR_OBJ_GFX_ID_0, EVENT_OBJ_GFX_TRICK_MASTER
	goto_if_eq TrickHouseCorridor_TrickMaster
	
	end

TrickHouseCorridor_TrickMaster:
	
	end

@ -----------------------------------------------------
#define LID_MASTER 2

TrickHouseCorridor_TriggerScript_RunIntro::
	lockall
	getplayerxy VAR_0x8000, VAR_0x8001
	subvar VAR_0x8001, 7
	@ Walk up
	selectpointer TrickHouseCorridor_MovementTable_RunIntro, VAR_0x8001
	applymovement EVENT_OBJ_ID_PLAYER, 0
	applymovement LID_MASTER, Common_Movement_WalkLeft1
	waitmovement EVENT_OBJ_ID_PLAYER
	@ Introduce puzzle
	msgbox TrickHouseCorridor_Text_RunIntro1
	@ Give items, and talk about it if we do
	callnative GiveItemPrerequisites
	compare VAR_RESULT, TRUE
	call_if_eq TrickHouseCorridor_TriggerScript_RunIntro_ItemRecieve
	@ Leave
	msgbox TrickHouseCorridor_Text_RunIntro4
	closemessage
	compare VAR_OBJ_GFX_ID_0, EVENT_OBJ_GFX_TRICK_MASTER
	call_if_eq TrickHouseCorridor_TriggerScript_RunIntro_TrickMasterOut
	call_if_ne TrickHouseCorridor_TriggerScript_RunIntro_CompanionLeaves
	@
	setvar VAR_PUZZLE_STATE, 1
	call TrickHouseCorridor_OpenPuzzleDoor
	releaseall
	end
TrickHouseCorridor_Text_RunIntro1:
	.string "The next challenge I collected off\n"
	.string "someone named {PUZZLE_AUTHOR}.\p"
	.string "I'd call it a {PUZZLE_ADJECTIVE} puzzle.$"
TrickHouseCorridor_Text_RunIntro2:
	.string "Oh, yes, and you'll be needing this!$"
TrickHouseCorridor_Text_RunIntro3:
	.string "You're handed {STR_VAR_1}!$"
TrickHouseCorridor_Text_RunIntro4:
	.string "See you on the other side!$"

TrickHouseCorridor_TriggerScript_RunIntro_ItemRecieve:
	msgbox TrickHouseCorridor_Text_RunIntro2
	message TrickHouseCorridor_Text_RunIntro3
	waitmessage
	playfanfare MUS_FANFA4
	waitfanfare
	waitbuttonpress
	return

TrickHouseCorridor_TriggerScript_RunIntro_TrickMasterOut:
	@ Trick Master warps away
	setvar VAR_0x8000, LID_MASTER
	call PuzzleCommon_EventScript_WarpTrickMasterOut
	@ Player approaches door
	applymovement EVENT_OBJ_ID_PLAYER, Common_Movement_WalkUp2
	waitmovement 0
	@ Open the door to the puzzle
	opendoor 22, 2
	waitdooranim
	return

TrickHouseCorridor_TriggerScript_RunIntro_CompanionLeaves:
	@ Player approaches door
	applymovement EVENT_OBJ_ID_PLAYER, Common_Movement_WalkUp2
	waitmovement 0
	@ Open the door to the puzzle
	opendoor 22, 2
	waitdooranim
	return


.align 2
TrickHouseCorridor_MovementTable_RunIntro:
	.4byte Common_Movement_WalkRight2
	.4byte TrickHouseCorridor_Movement_RunIntro2
	.4byte 0

TrickHouseCorridor_Movement_RunIntro2:
	walk_right
	walk_up
	walk_right
	step_end
	

#undef LID_MASTER