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
	compare VAR_PUZZLE_STATE, 3
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
	addvar VAR_CURRENT_PUZZLE, 1
	setvar VAR_PUZZLE_STATE, 0
	clearflag FLAG_HIDE_TRICK_HOUSE_INTRO_CHAR
	call AssignPuzzleMetaVariables
	call TrickHouseCorridor_CloseBackDoor
	end

@ -----------------------------------------------------

TrickHouseCorridor_EventScript_PokemonTable::
	
	end

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
	@
	@ TODO
	msgbox TrickHouseCorridor_Text_RunIntro1
	closemessage
	compare VAR_OBJ_GFX_ID_0, EVENT_OBJ_GFX_TRICK_MASTER
	call_if_eq TrickHouseCorridor_TriggerScript_RunIntro_TrickMasterOut
	call_if_ne TrickHouseCorridor_TriggerScript_RunIntro_CompanionLeaves
	@
	setvar VAR_PUZZLE_STATE, 1
	call TrickHouseCorridor_OpenPuzzleDoor
	releaseall
	end

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
	
	return

TrickHouseCorridor_Text_RunIntro1:
	.string "The next challenge I collected off\n"
	.string "someone named {STR_VAR_1}.\p"
	.string "I'd call it a {STR_VAR_2} puzzle.\p"
	.string "See you on the other side!$"

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
