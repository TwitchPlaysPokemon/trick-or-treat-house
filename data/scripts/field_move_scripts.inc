@ -----------------------------------------------------

Common_EventScript_ItemCut::
	giveitem_std ITEM_CUT_ITEM, 1, 1
	end

EventScript_CutTree:: @ 82906BB
	lockall
	checkitem ITEM_CUT_ITEM, 1
	compare VAR_RESULT, 0
	goto_if_eq EventScript_CheckTreeCantCut
	@ setfieldeffectargument 0, VAR_RESULT
	@ bufferpartymonnick 0, VAR_RESULT
	buffermovename 1, MOVE_CUT
	msgbox Text_WantToCut, MSGBOX_YESNO
	compare VAR_RESULT, 0
	goto_if_eq EventScript_CancelCut
	msgbox Text_MonUsedHM, MSGBOX_DEFAULT
	closemessage
	dofieldeffect FLDEFF_USE_CUT_ON_TREE
	waitstate
	goto EventScript_CutTreeDown
	end

EventScript_FldEffCut:: @ 8290705
	lockall
	dofieldeffect FLDEFF_USE_CUT_ON_TREE
	waitstate
	goto EventScript_CutTreeDown
	end

EventScript_CutTreeDown:: @ 8290710
	applymovement VAR_LAST_TALKED, Movement_CutTreeDown
	waitmovement 0
	removeobject VAR_LAST_TALKED
	releaseall
	end

Movement_CutTreeDown: @ 829071F
	cut_tree
	step_end

EventScript_CheckTreeCantCut:: @ 8290721
	msgbox Text_CantCut, MSGBOX_DEFAULT
	releaseall
	end

EventScript_CancelCut:: @ 829072B
	closemessage
	releaseall
	end

Text_WantToCut: @ 829072E
	.string "This tree looks like it can be\n"
	.string "CUT down!\p"
	.string "Would you like to CUT it?$"

Text_MonUsedHM: @ 8290771
	.string "You used {STR_VAR_2}!$"

Text_CantCut: @ 829077D
	.string "This tree looks like it can be\n"
	.string "CUT down!$"

@ -----------------------------------------------------

Common_EventScript_ItemRockSmash::
	giveitem_std ITEM_ROCKSMASH_ITEM, 1, 1
	end

EventScript_RockSmash:: @ 82907A6
	lockall
	checkitem ITEM_ROCKSMASH_ITEM, 1
	compare VAR_RESULT, 0
	goto_if_eq EventScript_CantSmashRock
	@ setfieldeffectargument 0, VAR_RESULT
	@ bufferpartymonnick 0, VAR_RESULT
	buffermovename 1, MOVE_ROCK_SMASH
	msgbox Text_WantToSmash, MSGBOX_YESNO
	compare VAR_RESULT, 0
	goto_if_eq EventScript_CancelSmash
	msgbox Text_MonUsedHM, MSGBOX_DEFAULT
	closemessage
	dofieldeffect FLDEFF_USE_ROCK_SMASH
	waitstate
	goto EventScript_SmashRock
	end

EventScript_FldEffRockSmash:: @ 82907F0
	lockall
	dofieldeffect FLDEFF_USE_ROCK_SMASH
	waitstate
	goto EventScript_SmashRock
	end

EventScript_SmashRock:: @ 82907FB
	applymovement VAR_LAST_TALKED, Movement_SmashRock
	waitmovement 0
	removeobject VAR_LAST_TALKED
	specialvar VAR_RESULT, TryUpdateRusturfTunnelState
	compare VAR_RESULT, 1
	goto_if_eq EventScript_EndSmash
	special RockSmashWildEncounter
	compare VAR_RESULT, 0
	goto_if_eq EventScript_EndSmash
	waitstate
	releaseall
	end

EventScript_EndSmash:: @ 8290829
	releaseall
	end

Movement_SmashRock: @ 829082B
	rock_smash_break
	step_end

EventScript_CantSmashRock:: @ 829082D
	msgbox Text_CantSmash, MSGBOX_DEFAULT
	releaseall
	end

EventScript_CancelSmash:: @ 8290837
	closemessage
	releaseall
	end

Text_WantToSmash: @ 829083A
	.string "This rock appears to be breakable.\n"
	.string "Would you like to use ROCK SMASH?$"

Text_CantSmash: @ 829087F
	.string "It's a rugged rock, but a POKéMON\n"
	.string "may be able to smash it.$"

@ -----------------------------------------------------

Common_EventScript_ItemStrength::
	giveitem_std ITEM_STRENGTH_ITEM, 1, 1
	end

EventScript_StrengthBoulder:: @ 82908BA
	lockall
	goto_if_set FLAG_SYS_USE_STRENGTH, EventScript_CheckActivatedBoulder
	checkitem ITEM_STRENGTH_ITEM, 1
	compare VAR_RESULT, 0
	goto_if_eq EventScript_CantStrength
	setfieldeffectargument 0, VAR_RESULT
	msgbox Text_WantToStrength, MSGBOX_YESNO
	compare VAR_RESULT, 0
	goto_if_eq EventScript_CancelStrength
	closemessage
	dofieldeffect FLDEFF_USE_STRENGTH
	waitstate
	goto EventScript_ActivateStrength
	end

EventScript_FldEffStrength:: @ 82908FD
	lockall
	dofieldeffect FLDEFF_USE_STRENGTH
	waitstate
	goto EventScript_ActivateStrength
	end

EventScript_ActivateStrength:: @ 8290908
	setflag FLAG_SYS_USE_STRENGTH
	msgbox Text_MonUsedStrength, MSGBOX_DEFAULT
	releaseall
	end

EventScript_CantStrength:: @ 8290915
	msgbox Text_CantStrength, MSGBOX_DEFAULT
	releaseall
	end

EventScript_CheckActivatedBoulder:: @ 829091F
	msgbox Text_StrengthActivated, MSGBOX_DEFAULT
	releaseall
	end

EventScript_CancelStrength:: @ 8290929
	closemessage
	releaseall
	end

Text_WantToStrength: @ 829092C
	.string "It's a big boulder, but a POKéMON\n"
	.string "may be able to push it aside.\p"
	.string "Would you like to use STRENGTH?$"

Text_MonUsedStrength: @ 829098C
	.string "You used STRENGTH!\p"
	.string "Your STRENGTH made it\n"
	.string "possible to move boulders around!$"

Text_CantStrength: @ 82909D6
	.string "It's a big boulder, but a POKéMON\n"
	.string "may be able to push it aside.$"

Text_StrengthActivated: @ 8290A16
	.string "STRENGTH made it possible to move\n"
	.string "boulders around.$"

@ -----------------------------------------------------

Common_EventScript_ItemWaterfall::
	giveitem_std ITEM_WATERFALL_ITEM, 1, 1
	end

EventScript_UseWaterfall:: @ 8290A49
	lockall
	checkitem ITEM_WATERFALL_ITEM, 1
	compare VAR_RESULT, 0
	goto_if_eq EventScript_CantWaterfall
	@ bufferpartymonnick 0, VAR_RESULT
	@ setfieldeffectargument 0, VAR_RESULT
	msgbox Text_WantToWaterfall, MSGBOX_YESNO
	compare VAR_RESULT, 0
	goto_if_eq EventScript_EndWaterfall
	msgbox Text_MonUsedWaterfall, MSGBOX_DEFAULT
	dofieldeffect FLDEFF_USE_WATERFALL
	goto EventScript_EndWaterfall

EventScript_CannotUseWaterfall:: @ 8290A83
	lockall

EventScript_CantWaterfall:: @ 8290A84
	msgbox Text_CantWaterfall, MSGBOX_DEFAULT

EventScript_EndWaterfall:: @ 8290A8C
	releaseall
	end

Text_CantWaterfall: @ 8290A8E
	.string "A wall of water is crashing down with\n"
	.string "a mighty roar.$"

Text_WantToWaterfall: @ 8290AC3
	.string "It's a large waterfall.\n"
	.string "Would you like to use WATERFALL?$"

Text_MonUsedWaterfall: @ 8290AFC
	.string "You used WATERFALL.$"

@ -----------------------------------------------------

Common_EventScript_ItemSurf::
	giveitem_std ITEM_SURF_ITEM, 1, 1
	end

EventScript_UseSurf:: @ 8271EA0
	checkitem ITEM_SURF_ITEM, 1
	compare VAR_RESULT, 0
	goto_if_eq EventScript_CantSurf
	@ bufferpartymonnick 0, VAR_RESULT
	@ setfieldeffectargument 0, VAR_RESULT
	lockall
	msgbox gText_WantToUseSurf, MSGBOX_YESNO
	compare VAR_RESULT, 0
	goto_if_eq EventScript_CancelSurf
	msgbox gText_PlayerUsedSurf, MSGBOX_DEFAULT
	dofieldeffect FLDEFF_USE_SURF

EventScript_CancelSurf:: @ 8271ED5
	releaseall

EventScript_CantSurf:: @ 8271ED6
	end

gText_WantToUseSurf:: @ 8272FD6
	.string "The water is dyed a deep blue…\nWould you like to SURF?$"

gText_PlayerUsedSurf:: @ 827300D
	.string "You used SURF!$"


@ -----------------------------------------------------

Common_EventScript_ItemDive::
	giveitem_std ITEM_DIVE_ITEM, 1, 1
	end

EventScript_UseDive:: @ 8290B0F
	lockall
	checkitem ITEM_DIVE_ITEM, 1
	compare VAR_RESULT, 0
	goto_if_eq EventScript_CantDive
	@ bufferpartymonnick 0, VAR_RESULT
	@ setfieldeffectargument 0, VAR_RESULT
	setfieldeffectargument 1, 1
	msgbox Text_WantToDive, MSGBOX_YESNO
	compare VAR_RESULT, 0
	goto_if_eq EventScript_EndDive
	msgbox Text_MonUsedDive, MSGBOX_DEFAULT
	dofieldeffect FLDEFF_USE_DIVE
	goto EventScript_EndDive
	end

EventScript_CantDive:: @ 8290B4E
	msgbox Text_CantDive, MSGBOX_DEFAULT
	releaseall
	end

EventScript_EndDive:: @ 8290B58
	releaseall
	end

EventScript_UseDiveUnderwater:: @ 8290B5A
	lockall
	checkitem ITEM_DIVE_ITEM, 1
	compare VAR_RESULT, 0
	goto_if_eq EventScript_CantSurface
	@ bufferpartymonnick 0, VAR_RESULT
	@ setfieldeffectargument 0, VAR_RESULT
	setfieldeffectargument 1, 1
	msgbox Text_WantToSurface, MSGBOX_YESNO
	compare VAR_RESULT, 0
	goto_if_eq EventScript_EndSurface
	msgbox Text_MonUsedDive, MSGBOX_DEFAULT
	dofieldeffect FLDEFF_USE_DIVE
	goto EventScript_EndSurface
	end

EventScript_CantSurface:: @ 8290B99
	lockall
	msgbox Text_CantSurface, MSGBOX_DEFAULT
	goto EventScript_EndSurface
	end

EventScript_EndSurface:: @ 8290BA8
	releaseall
	end

Text_CantDive: @ 8290BAA
	.string "The sea is deep here. A POKéMON\n"
	.string "may be able to go underwater.$"

Text_WantToDive: @ 8290BE8
	.string "The sea is deep here.\n"
	.string "Would you like to use DIVE?$"

Text_MonUsedDive: @ 8290C1A
	.string "You used DIVE.$"

Text_CantSurface: @ 8290C28
	.string "Light is filtering down from above.\n"
	.string "A POKéMON may be able to surface.$"

Text_WantToSurface: @ 8290C6E
	.string "Light is filtering down from above.\n"
	.string "Would you like to use DIVE?$"

@ -----------------------------------------------------

Common_EventScript_ItemFlash::
	giveitem_std ITEM_FLASH_ITEM, 1, 1
	end

Common_EventScript_ItemFly::
	giveitem_std ITEM_FLY_ITEM, 1, 1
	end

EventScript_FailSweetScent:: @ 8290CAE
	msgbox Text_FailSweetScent, MSGBOX_SIGN
	end

Text_FailSweetScent: @ 8290CB7
	.string "Looks like there's nothing here…$"
