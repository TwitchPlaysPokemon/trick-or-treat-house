TrickHouseDevEntrance_MapScripts::
	.byte 0

TrickHouseDevEntrance_EventScript_Red::
	msgbox TrickHouseDevEntrance_EventScript_Red_Text_0, MSGBOX_NPC
	return


TrickHouseDevEntrance_EventScript_Pokeball::
	lock
	goto_if_unset FLAG_SYS_POKEMON_GET, TrickHouseDevEntrance_EventScript_Pokeball_2
	goto TrickHouseDevEntrance_EventScript_Pokeball_1

TrickHouseDevEntrance_EventScript_Pokeball_1:
	release
	return

TrickHouseDevEntrance_EventScript_Pokeball_2:
	givemon SPECIES_QUILAVA, 50, 0, 0, 0, 0
	setflag FLAG_SYS_POKEMON_GET
	msgbox TrickHouseDevEntrance_EventScript_Pokeball_Text_0
	goto TrickHouseDevEntrance_EventScript_Pokeball_1


TrickHouseDevEntrance_EventScript_Red_Text_0:
	.string "This is the dev room. You can change\n"
	.string "the current puzzle at the TV.\p"
	.string "If you didn't get here via the door\n"
	.string "outside, something went wrong;\l"
	.string "Please report this to the devs.$"

TrickHouseDevEntrance_EventScript_Pokeball_Text_0:
	.string "Got a Quilava!$"
