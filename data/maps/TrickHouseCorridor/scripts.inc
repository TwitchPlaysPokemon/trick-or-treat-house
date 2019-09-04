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
	call_if_lt TrickHouseCorridor_CloseBackDoor
	compare VAR_PUZZLE_STATE, 1
	call_if_eq TrickHouseCorridor_OpenPuzzleDoor
	end

TrickHouseCorridor_OpenPuzzleDoor:
	setmetatile 22, 2, 0x01F, FALSE
	return

TrickHouseCorridor_CloseBackDoor:
	setmetatile 4, 6, 0x21B, TRUE
	return

@ -----------------------------------------------------

TrickHouseCorridor_FrameTable:
	map_script_2 VAR_PUZZLE_STATE, 2, TrickHouseCorridor_IncrementPuzzle
	.2byte 0

TrickHouseCorridor_IncrementPuzzle:
	call PuzzleCommon_EventScript_IncrementPuzzle
	clearflag FLAG_HIDE_TRICK_HOUSE_INTRO_CHAR
	callnative SetupPuzzleWarp
	call AssignPuzzleMetaVariables
	call TrickHouseCorridor_CloseBackDoor
	end

@ -----------------------------------------------------

TrickHouseCorridor_EventScript_PokemonTable::
	lockall
	msgbox TrickHouseCorridor_Text_PokemonTable1
	fadescreen 1
	callnative SelectTrickHouseParty
	waitstate
	msgbox TrickHouseCorridor_Text_PokemonTable2
	releaseall
	end
TrickHouseCorridor_Text_PokemonTable1:
	.string "Hi!$"
TrickHouseCorridor_Text_PokemonTable2:
	.string "Bye!$"

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
	callnative LoadPuzzleAuthor
	callnative LoadPuzzleAdjective
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
	.string "someone named {STR_VAR_1}.\p"
	.string "I'd call it a {STR_VAR_2} puzzle.$"
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
