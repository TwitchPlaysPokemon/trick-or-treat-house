TrickHouseExt_MapScripts::
	.byte 0


Route110_EventScript_1EF380:: @ 81EF380
	msgbox Route110_Text_1F0992, MSGBOX_SIGN
	end
Route110_Text_1F0992: @ 81F0992
	.string "TRAINER TIPS\p"
	.string "The items in the BAG can be reorganized\n"
	.string "by pressing SELECT.$"


Route110_EventScript_1EF389:: @ 81EF389
	msgbox Route110_Text_1F09DB, MSGBOX_SIGN
	end
Route110_Text_1F09DB: @ 81F09DB
	.string "“Three steps {RIGHT_ARROW} and two steps {UP_ARROW}\n"
	.string "to reach the wondrous TRICK HOUSE.”$"


Route110_EventScript_1EF35C:: @ 81EF35C
	msgbox Route110_Text_1F08CD, MSGBOX_SIGN
	end
Route110_Text_1F08CD: @ 81F08CD
	.string "ROUTE 110\n"
	.string "{LEFT_ARROW} ROUTE 103$"


Route110_EventScript_1EF34A:: @ 81EF34A
	msgbox Route110_Text_1F082D, MSGBOX_SIGN
	end
Route110_Text_1F082D: @ 81F082D
	.string "SEASIDE CYCLING ROAD$"


Route110_EventScript_TestDoor::
	lock
	applymovement THIS_EVENT, Common_Movement_ObjectDoorOpen
	waitmovement 0
	applymovement EVENT_OBJ_ID_PLAYER, Common_Movement_WalkUp1
	waitmovement 0
	applymovement EVENT_OBJ_ID_PLAYER, Common_Movement_SetInvisible
	waitmovement 0
	applymovement THIS_EVENT, Common_Movement_ObjectDoorClose
	waitmovement 0
	warp MAP_ROUTE110_TRICK_HOUSE_ENTRANCE, 0, 0xff, 0xff
	waitstate
	release
	end
