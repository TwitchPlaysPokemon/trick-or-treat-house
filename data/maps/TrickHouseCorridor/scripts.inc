TrickHouseCorridor_MapScripts:: @ 826B903
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, TrickHouseCorridor_MapTable
	map_script MAP_SCRIPT_ON_FRAME_TABLE, TrickHouseCorridor_FrameTable
	map_script MAP_SCRIPT_ON_TRANSITION, TrickHouseCorridor_Transition
	.byte 0

@ -----------------------------------------------------

TrickHouseCorridor_Transition:
	callnative RunPuzzleSetupScript
	end

@ -----------------------------------------------------

TrickHouseCorridor_MapTable:
	map_script_2 VAR_PUZZLE_STATE, 0, TrickHouseCorridor_CloseBackDoor
	map_script_2 VAR_PUZZLE_STATE, 1, TrickHouseCorridor_CloseBackDoor
	.2byte 0

TrickHouseCorridor_CloseBackDoor:
	setmetatile 4, 6, 0x21B, TRUE
	end

@ -----------------------------------------------------

TrickHouseCorridor_FrameTable:
	map_script_2 VAR_PUZZLE_STATE, 2, TrickHouseCorridor_IncrementPuzzle
	.2byte 0

TrickHouseCorridor_IncrementPuzzle:
	setvar VAR_PUZZLE_STATE, 0
	addvar VAR_CURRENT_PUZZLE, 1
	goto TrickHouseCorridor_CloseBackDoor
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
	@ Open the door to the puzzle
	opendoor 22, 2
	waitdooranim
	@
	
	setvar VAR_PUZZLE_STATE, 1
	releaseall
	end

TrickHouseCorridor_Text_RunIntro1:
	.string "For the $"

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
