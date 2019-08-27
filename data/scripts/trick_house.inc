PuzzleCommon_Text_DefaultAdjective::
	.string "<adjective>$"
PuzzleCommon_Text_DefaultQuip::
	.string "What did you think of my puzzle?$"

PuzzleCommon_DefaultSetupScript::
	setvar VAR_OBJ_GFX_ID_0, EVENT_OBJ_GFX_TRICK_MASTER
	setvar VAR_OBJ_GFX_ID_1, EVENT_OBJ_GFX_TRICK_MASTER
	end


PuzzleDebug_EventScript_ShowPuzzleSelect::
	lockall
	playse SE_SELECT
	message PuzzleDebug_Text_PuzzleSelect
	waitmessage
	callnative ShowPuzzleSelect
	waitstate @ script pauses here until manually reenabled
	closemessage
	releaseall
	end
PuzzleDebug_Text_PuzzleSelect:
	.string "Select puzzle index$"



PuzzleCommon_EventScript_ExitDoorMetatile::
	lock
	@ TODO: Check for scroll
	warp MAP_TRICK_HOUSE_END, 0, 0xff, 0xff
	waitstate
	release
	end

PuzzleCommon_EventScript_ExitDoorObject::
	lock
	@ TODO: Check for scroll
	call PuzzleCommon_EventScript_DoDoorEnterAnimation_Stone
	warp MAP_TRICK_HOUSE_END, 0, 0xff, 0xff
	waitstate
	release
	end

PuzzleCommon_EventScript_DoDoorEnterAnimation_Stone::
	playse SE_W070
	applymovement THIS_EVENT, Common_Movement_ObjectDoorOpen
	waitmovement 0
	applymovement EVENT_OBJ_ID_PLAYER, Common_Movement_WalkUp1
	waitmovement 0
	applymovement EVENT_OBJ_ID_PLAYER, Common_Movement_SetInvisible
	waitmovement 0
	applymovement THIS_EVENT, Common_Movement_ObjectDoorClose
	waitmovement 0
	return

PuzzleCommon_EventScript_DoDoorEnterAnimation::
	playse SE_TRACK_HAIKI
	applymovement THIS_EVENT, Common_Movement_ObjectDoorOpen
	waitmovement 0
	applymovement EVENT_OBJ_ID_PLAYER, Common_Movement_WalkUp1
	waitmovement 0
	applymovement EVENT_OBJ_ID_PLAYER, Common_Movement_SetInvisible
	waitmovement 0
	applymovement THIS_EVENT, Common_Movement_ObjectDoorClose
	waitmovement 0
	return


PuzzleCommon_EventScript_WarpTrickMasterOut:: @ 826AFCF
	applymovement VAR_0x8000, PuzzleCommon_Movement_TrickMasterWarpAway1
	waitmovement 0
	playse SE_W153
	applymovement VAR_0x8000, PuzzleCommon_Movement_TrickMasterWarpAway2
	waitmovement 0
	removeobject VAR_0x8000
	return

PuzzleCommon_Movement_TrickMasterWarpAway1:
	face_up
	delay_4
	face_left
	delay_4
	face_down
	delay_4
	face_right
	delay_4
	step_end
PuzzleCommon_Movement_TrickMasterWarpAway2:
	face_up
	disable_anim
	slide_up
	slide_up
	slide_up
	slide_up
	slide_up
	slide_up
	step_end

