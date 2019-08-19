PacifidlogTown_MapScripts:: @ 81EBAB1
	map_script MAP_SCRIPT_ON_RESUME, PacifidlogTown_OnResume
	.byte 0

PacifidlogTown_OnResume: @ 81EBAC0
	setstepcallback 3
	end

PacifidlogTown_EventScript_1EBADE:: @ 81EBADE
	msgbox PacifidlogTown_Text_1EBC7A, MSGBOX_SIGN
	end
PacifidlogTown_Text_1EBC7A: @ 81EBC7A
	.string "PACIFIDLOG TOWN\p"
	.string "“Where the morning sun smiles upon\n"
	.string "the waters.”$"

