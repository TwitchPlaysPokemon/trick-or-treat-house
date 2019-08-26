
PuzzleDebug_EventScript_ShowPuzzleSelect::
	lockall
	playse SE_SELECT
	message PuzzleDebug_Text_PuzzleSelect
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
	call PuzzleCommon_EventScript_DoDoorEnterAnimation
	warp MAP_TRICK_HOUSE_END, 0, 0xff, 0xff
	waitstate
	release
	end

PuzzleCommon_EventScript_DoDoorEnterAnimation::
	applymovement THIS_EVENT, Common_Movement_ObjectDoorOpen
	waitmovement 0
	applymovement EVENT_OBJ_ID_PLAYER, Common_Movement_WalkUp1
	waitmovement 0
	applymovement EVENT_OBJ_ID_PLAYER, Common_Movement_SetInvisible
	waitmovement 0
	applymovement THIS_EVENT, Common_Movement_ObjectDoorClose
	waitmovement 0
	return


