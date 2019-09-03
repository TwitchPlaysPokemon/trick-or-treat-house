PuzzleCommon_Text_UntitledPuzzleName::
	.string "<untitled puzzle>$"
PuzzleCommon_Text_DefaultAuthor::
	.string "<author>$"
PuzzleCommon_Text_DefaultAdjective::
	.string "<adjective>$"
PuzzleCommon_Text_DefaultQuip::
	.string "What did you think of my puzzle?$"
PuzzleCommon_DefaultSetupScript::
	end
PuzzleCommon_DefaultTeardownScript::
	end

@ -----------------------------------------------------

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

@ -----------------------------------------------------

PuzzleCommon_EventScript_IncrementPuzzle::
	addvar VAR_CURRENT_PUZZLE, 1
	setvar VAR_PUZZLE_STATE, 0
	callnative ClearPuzzleEventData
	return


@ -----------------------------------------------------

PuzzleCommon_EventScript_Scroll::
	lock
	goto_if_set FLAG_TRICK_HOUSE_SCROLL_READ, PuzzleCommon_EventScript_ScrollExamine
	playfanfare MUS_FANFA4
	message PuzzleCommon_Text_ScrollFound1
	waitfanfare
	setflag FLAG_TRICK_HOUSE_SCROLL_READ
	msgbox PuzzleCommon_Text_ScrollFound2
	release
	end
PuzzleCommon_Text_ScrollFound1:
	.string "{PLAYER} found a scroll.$"
PuzzleCommon_Text_ScrollFound2:
	.string "{PLAYER} memorized the secret code\n"
	.string "written on the scroll.$"
PuzzleCommon_EventScript_ScrollExamine:
	msgbox PuzzleCommon_Text_ScrollExamine
	release
	end
PuzzleCommon_Text_ScrollExamine:
	.string "A secret code is written on it.$"

@ -----------------------------------------------------

PuzzleCommon_EventScript_ExitDoorMetatile::
	lock
	@ Check for scroll
	goto_if_unset FLAG_TRICK_HOUSE_PASSWORD_ENTERED, PuzzleCommon_EventScript_CheckScroll
	goto PuzzleCommon_EventScript_ExamineDoor
	end

PuzzleCommon_EventScript_ExitDoorObject::
	lock
	@ Check for scroll
	goto_if_unset FLAG_TRICK_HOUSE_PASSWORD_ENTERED, PuzzleCommon_EventScript_CheckScroll
	goto_if_unset FLAG_IS_BUMP_INTERACTION, PuzzleCommon_EventScript_ExamineDoor
	@ If the player bumped into this object, make it act like a door
	call PuzzleCommon_EventScript_DoDoorEnterAnimation_Stone
	warp MAP_TRICK_HOUSE_END, 0, 0xff, 0xff
	waitstate
	release
	end

PuzzleCommon_EventScript_CheckScroll:
	goto_if_unset FLAG_TRICK_HOUSE_SCROLL_READ, PuzzleCommon_EventScript_NoScrollReject
	
	msgbox PuzzleCommon_Text_WriteDownCode
	setflag FLAG_TRICK_HOUSE_PASSWORD_ENTERED
	release
	end
PuzzleCommon_Text_WriteDownCode:
	.string "{PLAYER} wrote down the secret code\n"
	.string "on the door.\p"
	.string "“{STR_VAR_1}”\n"
	.string "… … … … … … … …\p"
	.string "{PLAY_SE SE_PIN}The door unsealed!$"

PuzzleCommon_EventScript_ExamineDoor:
	msgbox PuzzleCommon_Text_ExamineDoor
	release
	end
PuzzleCommon_Text_ExamineDoor:
	.string "The door is unsealed.$"

PuzzleCommon_EventScript_NoScrollReject:
	msgbox PuzzleCommon_Text_NoScrollReject
	release
	end
PuzzleCommon_Text_NoScrollReject:
	.string "The stone door is sealed.\p"
	.string "…On closer inspection, this is written\n"
	.string "on it: “Write the secret code here.”$"


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

@ -----------------------------------------------------

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

