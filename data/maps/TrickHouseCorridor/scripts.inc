TrickHouseCorridor_MapScripts:: @ 826B903
	map_script MAP_SCRIPT_ON_TRANSITION, TrickHouseCorridor_OnTransition
	.byte 0

TrickHouseCorridor_OnTransition: @ 826B909
	setvar VAR_TRICK_HOUSE_STATE, 1
	end

