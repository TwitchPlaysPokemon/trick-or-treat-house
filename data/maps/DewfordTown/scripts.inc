DewfordTown_MapScripts:: @ 81E9507
	.byte 0

DewfordTown_OnTransition: @ 81E950D
	setflag FLAG_VISITED_DEWFORD_TOWN
	end

DewfordTown_EventScript_1E95BA:: @ 81E95BA
	msgbox DewfordTown_Text_1E9A0F, MSGBOX_SIGN
	end
DewfordTown_Text_1E9A0F: @ 81E9A0F
	.string "DEWFORD TOWN\n"
	.string "“A tiny island in the blue sea.”$"

DewfordTown_EventScript_1E95C3:: @ 81E95C3
	msgbox DewfordTown_Text_1E9A3D, MSGBOX_SIGN
	end
DewfordTown_Text_1E9A3D: @ 81E9A3D
	.string "DEWFORD TOWN POKéMON GYM\n"
	.string "LEADER: BRAWLY\l"
	.string "“A big wave in fighting!”$"

DewfordTown_EventScript_1E95CC:: @ 81E95CC
	msgbox DewfordTown_Text_1E9A7F, MSGBOX_SIGN
	end
DewfordTown_Text_1E9A7F: @ 81E9A7F
	.string "DEWFORD HALL\n"
	.string "“Everyone's information exchange!”$"
