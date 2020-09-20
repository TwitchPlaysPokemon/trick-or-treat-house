PuzzleCommon_Text_UntitledPuzzleName::
	.string "<untitled puzzle>$"
PuzzleCommon_Text_DefaultAuthor::
	.string "<author>$"
PuzzleCommon_Text_DefaultAdjective::
	.string "<adjective>$"
PuzzleCommon_Text_DefaultQuip::
	.string "{PUZZLE_AUTHOR}: What did you think\nof my puzzle?$"
PuzzleCommon_Text_DefaultDevCommentary::
	.string "Tustin2121: Uh, this isn't supposed to\n"
	.string "happen… Ignore this, please.$"
PuzzleCommon_Text_DefaultFriendCommentary::
	.string "Sorry, just hanging around.$"
PuzzleCommon_DefaultSetupScript::
	end
PuzzleCommon_DefaultTeardownScript::
	end

@ -----------------------------------------------------

CommonAuthor_Trickmaster::
	.string "Trick Master$"
CommonAuthor_GameFreak::
	.string "GAME FREAK$"
CommonAuthor_Tustin2121::
	.string "Tustin2121$"
CommonAuthor_M4UsedRollout::
	.string "M4UsedRollout$"

@ -----------------------------------------------------

PuzzleDebug_EventScript_ShowPuzzleSelect::
	lockall
	playse SE_SELECT
	message3 PuzzleDebug_Text_PuzzleSelect
	waitmessage
	callnative ShowPuzzleSelect
	waitstate @ script pauses here until manually reenabled
	closemessage
	releaseall
	end
PuzzleDebug_Text_PuzzleSelect:
	.string "Select puzzle index.\n"
	.string "{START_BUTTON} Switch Debug/Main Puzzles$"

@ -----------------------------------------------------

PuzzleCommon_EventScript_IncrementPuzzle::
	addvar VAR_CURRENT_PUZZLE, 1
	setvar VAR_PUZZLE_STATE, 0
	incrementgamestat GAME_STAT_NUM_PUZZLES_COMPLETED
	callnative CheckIfNoMorePuzzles
	@ fallthrough
PuzzleCommon_EventScript_ClearPuzzleData::
	callnative ClearPuzzleEventData
	setvar VAR_TIMES_SEEN_BY_TRAINER, 0
	return

@ -----------------------------------------------------

PuzzleCommon_EventScript_EntranceDoorObject::
	lock
	@ Check for facing the correct direction
	compare VAR_FACING, 2 @north
	goto_if_ne PuzzleCommon_EventScript_EntranceDoorObject_Backside
	goto_if_set FLAG_IS_BUMP_INTERACTION, PuzzleCommon_EventScript_EntranceDoorObject_WarpToCorridor
	msgbox PuzzleCommon_Text_DoorFrontside
	release
	end
PuzzleCommon_Text_DoorFrontside:
	.string "The scroll reads\n“The TRICK MASTER is the GREATEST!$"

PuzzleCommon_EventScript_EntranceDoorObject_WarpToCorridor:
	call PuzzleCommon_EventScript_DoDoorEnterAnimation
	warp MAP_TRICK_HOUSE_CORRIDOR, 0, -1, -1
	waitstate
	release
	end

PuzzleCommon_EventScript_EntranceDoorObject_Backside:
	goto_if_set FLAG_IS_BUMP_INTERACTION, Common_EventScript_ReleaseEnd
	msgbox PuzzleCommon_Text_DoorBackside
	release
	end
PuzzleCommon_Text_DoorBackside:
	.string "There's just a blank wall on this side.\n"
	.string "No door. How does this even work?!$"

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
	@ Check for facing the correct direction
	compare VAR_FACING, 2 @north
	goto_if_ne PuzzleCommon_EventScript_EntranceDoorObject_Backside
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
	goto_if_set FLAG_IS_BUMP_INTERACTION, Common_EventScript_ReleaseEnd
	goto_if_unset FLAG_TRICK_HOUSE_SCROLL_READ, PuzzleCommon_EventScript_NoScrollReject
	random 256
	selectpointer_wrap PuzzleCommon_TextArray_SecretCodes, VAR_RESULT
	bufferselectedstring 0
	msgbox PuzzleCommon_Text_WriteDownCode
	setflag FLAG_TRICK_HOUSE_PASSWORD_ENTERED
	release
	end
PuzzleCommon_Text_WriteDownCode:
	.string "{PLAYER} wrote down the secret code\n"
	.string "on the door.\p"
	.string "“{STR_VAR_1}”\p"
	.string "… … … … … … … …\n"
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

Common_Movement_ObjectDoorOpen: @ 82725A6
	walk_in_place_up
	step_end

Common_Movement_ObjectDoorClose: @ 82725A6
	walk_in_place_down
	step_end


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

@ -----------------------------------------------------

PuzzleCommon_EventScript_StandingCandyGiverLeave::
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceUp
	waitmovement 0
	subvar VAR_METATILE_Y, 1
	opendoor VAR_METATILE_X, VAR_METATILE_Y
	waitdooranim
	applymovement VAR_LAST_TALKED, Common_Movement_WalkUp1
	waitmovement 0
	playse SE_KAIDAN
	removeobject VAR_LAST_TALKED
	closedoor VAR_METATILE_X, VAR_METATILE_Y
	waitdooranim
	delay 10
	return

PuzzleCommon_EventScript_DoorCandyGiverShow::
	opendoor VAR_METATILE_X, VAR_METATILE_Y
	waitdooranim
	applymovement VAR_LAST_TALKED, Common_Movement_SetVisible
	waitmovement 0
	delay 10
	return
PuzzleCommon_EventScript_DoorCandyGiverHide::
	closemessage
	removeobject VAR_LAST_TALKED
	closedoor VAR_METATILE_X, VAR_METATILE_Y
	waitdooranim
	delay 10
	setvar VAR_METATILE_X, 0
	return
	
PuzzleCommon_EventScript_PokecenterHeal::
	lock
	goto_if_unset FLAG_IS_BUMP_INTERACTION, Common_EventScript_ReleaseEnd
	@ Open door, walk in
	opendoor VAR_METATILE_X, VAR_METATILE_Y
	waitdooranim
	applymovement EVENT_OBJ_ID_PLAYER, Common_Movement_EnterCenter
	waitmovement 0
	closedoor VAR_METATILE_X, VAR_METATILE_Y
	waitdooranim
	delay 10
	@ Fade screen, heal
	fadescreen 1
	playfanfare MUS_ME_ASA
	special HealPlayerParty
	waitfanfare
	fadescreen 0
	@ Open door, walk out
	opendoor VAR_METATILE_X, VAR_METATILE_Y
	waitdooranim
	applymovement EVENT_OBJ_ID_PLAYER, Common_Movement_ExitCenter
	waitmovement 0
	closedoor VAR_METATILE_X, VAR_METATILE_Y
	waitdooranim
	release
	end
Common_Movement_EnterCenter: @ 82725C9
	walk_up
	set_invisible
	step_end
Common_Movement_ExitCenter:
	set_visible
	walk_down
	step_end
