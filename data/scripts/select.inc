
EventScript_SelectWithoutRegisteredItem:: @ 82736B3
	lockall
	incrementgamestat GAME_STAT_SELECT_PRESSES
	callnative SetSelectVariables
	compare VAR_0x800A, 1
	call_if_le EventScript_SelectWithoutRegisteredItem_First
	
	selectpointer_clamp gSelect_RulesTable, VAR_0x800B
	bufferstring 1, 0
	addvar VAR_0x800B, 1
	buffernumberstring 0, VAR_0x800B
	
	message gSelect_RuleTemplate
	waitmessage
	waitbuttonpress
	
	releaseall
	end
	
EventScript_SelectWithoutRegisteredItem_First:
	message gText_SelectWithoutRegisteredItem
	waitmessage
	waitbuttonpress
	return
	end

gText_SelectWithoutRegisteredItem:: @ 8272C98
	.string "An item in the BAG can be\n"
	.string "registered to SELECT for easy use.\p"
	.string "But you already knew that, so instead,\n"
	.string "in the future, let's refer to the\l"
	.string "TRICK OR TREATING HANDBOOK.$"

gSelect_RuleTemplate:
	.string "{TOT_RULE}{STR_VAR_1}:\n{STR_VAR_2}$"

.align 2
gSelect_RulesTable::
	.4byte gSelect_Rule01
	.4byte gSelect_Rule02
	.4byte gSelect_Rule03
	
	.4byte gSelect_Rule04
	.4byte gSelect_Rule05
	.4byte gSelect_Rule06
	.4byte gSelect_Rule07
	.4byte gSelect_Rule08
	.4byte gSelect_Rule09
	.4byte gSelect_Rule10
	.4byte gSelect_Rule11
	.4byte gSelect_Rule12
	.4byte gSelect_Rule13
	.4byte gSelect_Rule14
	.4byte gSelect_Rule15
	.4byte gSelect_Rule16
	.4byte gSelect_Rule17
	.4byte gSelect_Rule18
	.4byte gSelect_Rule19
	.4byte gSelect_Rule20
	.4byte gSelect_Rule21
	.4byte gSelect_Rule22
	.4byte gSelect_Rule23
	.4byte gSelect_Rule24
	.4byte gSelect_Rule25
	.4byte gSelect_Rule26
	.4byte gSelect_Rule27
	.4byte gSelect_Rule28
	.4byte gSelect_Rule29
	.4byte gSelect_Rule30
	.4byte gSelect_Rule31
	.4byte gSelect_Rule32
	.4byte gSelect_Rule33
	.4byte gSelect_Rule34
	.4byte gSelect_Rule35
	.4byte gSelect_Rule36
	.4byte gSelect_Rule37
	.4byte gSelect_Rule38
	.4byte gSelect_Rule39
	.4byte gSelect_Rule40
	.4byte gSelect_Rule41
	.4byte gSelect_Rule42
	.4byte gSelect_Rule43
	.4byte gSelect_Rule44
	.4byte gSelect_Rule45
	.4byte gSelect_Rule46
	.4byte gSelect_Rule47
	.4byte gSelect_Rule48
	.4byte gSelect_Rule49
	.4byte gSelect_Rule50
	.4byte gSelect_Rule51
	.4byte gSelect_Rule52
	.4byte gSelect_Rule53
	.4byte gSelect_Rule54
	.4byte gSelect_Rule55
	.4byte gSelect_Rule56
	.4byte gSelect_Rule57
	.4byte gSelect_Rule58
	.4byte gSelect_Rule59
	.4byte gSelect_Rule60
	.4byte gSelect_Rule61
	.4byte gSelect_Rule62
	.4byte gSelect_Rule63
	.4byte gSelect_Rule64
	.4byte gSelect_Rule65
	.4byte gSelect_Rule66
	.4byte gSelect_Rule67
	.4byte gSelect_Rule68
	.4byte gSelect_Rule69
	.4byte gSelect_Rule70
	.4byte gSelect_Rule71
	.4byte gSelect_Rule72
	.4byte gSelect_Rule73
	.4byte gSelect_Rule74
	.4byte gSelect_Rule75
	.4byte gSelect_Rule76
	.4byte gSelect_Rule77
	.4byte gSelect_Rule78
	.4byte gSelect_Rule79
	.4byte gSelect_Rule80
	.4byte gSelect_Rule81
	.4byte gSelect_Rule82
	.4byte gSelect_Rule83
	.4byte gSelect_Rule84
	.4byte gSelect_Rule85
	.4byte gSelect_Rule86
	.4byte gSelect_Rule87
	.4byte gSelect_Rule88
	.4byte gSelect_Rule89
	.4byte gSelect_Rule90
	.4byte gSelect_Rule91
	.4byte gSelect_Rule92
	.4byte gSelect_Rule93
	.4byte gSelect_Rule94
	.4byte gSelect_Rule95
	.4byte gSelect_Rule96
	.4byte gSelect_Rule97
	.4byte gSelect_Rule98
	.4byte gSelect_Rule99
	.4byte gSelect_RuleA0
	.4byte gSelect_RuleA1
	.4byte gSelect_RuleA2
	.4byte gSelect_RuleA3
	.4byte gSelect_RuleA4
	.4byte gSelect_RuleA5
	.4byte gSelect_RuleA6
	.4byte gSelect_RuleA7
	.4byte gSelect_RuleA8
	.4byte gSelect_RuleA9
	.4byte gSelect_RuleB0
	.4byte gSelect_RuleB1
	.4byte gSelect_RuleB2
	.4byte gSelect_RuleB3
	.4byte gSelect_RuleB4
	.4byte gSelect_RuleB5
	.4byte gSelect_RuleB6
	.4byte gSelect_RuleB7
	.4byte gSelect_RuleB8
	.4byte gSelect_RuleB9
	.4byte gSelect_RuleC0
	.4byte gSelect_RuleC1
	.4byte gSelect_RuleC2
	.4byte gSelect_RuleC3
	.4byte gSelect_RuleC4
	.4byte gSelect_RuleC5
	.4byte gSelect_RuleC6
	.4byte gSelect_RuleC7
	.4byte gSelect_RuleC8
	.4byte gSelect_RuleC9
	.4byte gSelect_RuleD0
	.4byte gSelect_RuleD1
	.4byte gSelect_RuleD2
	.4byte gSelect_RuleD3
	.4byte gSelect_RuleD4
	.4byte gSelect_RuleD5
	.4byte gSelect_RuleD6
	.4byte gSelect_RuleD7
	.4byte gSelect_RuleD8
	.4byte gSelect_RuleD9
	.4byte gSelect_RuleE0
	.4byte gSelect_RuleE1
	.4byte gSelect_RuleE2
	.4byte gSelect_RuleE3
	.4byte gSelect_RuleE4
	.4byte gSelect_RuleE5
	.4byte gSelect_RuleE6
	.4byte gSelect_RuleE7
	.4byte gSelect_RuleE8
	.4byte gSelect_RuleE9
	.4byte gSelect_RuleF0
	.4byte gSelect_RuleF1
	.4byte gSelect_RuleF2
	.4byte gSelect_RuleF3
	.4byte gSelect_RuleF4
	.4byte gSelect_RuleF5
	.4byte gSelect_RuleF6
	.4byte gSelect_RuleF7
	.4byte gSelect_RuleF8
	.4byte gSelect_RuleF9
gSelect_RulesTable_End::
	
@ Odd numbered rules are tounge-in-cheek or about halloween.
@ Even numbered rules are tips about the game.

gSelect_Rule01:
	.string "Greet candygivers with “Trick or Treat”!$"
gSelect_Rule02:
	.string "To view your candy, open your BAG.$"
gSelect_Rule03:
	.string "Search everywhere for any hidden candy.$"
gSelect_Rule04: @ Before puzzle 1
	.string "Have fun!$"
gSelect_Rule05:
	.string "Always thank the candygivers.$"
gSelect_Rule06: @ After puzzle 1
	.string "Be prepared to battle at any time.$"
gSelect_Rule07:
	.string "Don't eat candy with broken packaging.$"
gSelect_Rule08: @ After puzzle 2
	.string "Give your {POKEMON} candy too!$"
gSelect_Rule09:
	.string "Do not smash the pumpkins.$"
gSelect_Rule10: @ After puzzle 3
	.string "Don't expect to reach Zora's Domain.$"
gSelect_Rule11:
	.string "Always look both ways when crossing\l"
	.string "the street; use a cross walk.$"
gSelect_Rule12: @
	.string "Consider trading your candy to other\l"
	.string "kids. They might offer something good.$"
gSelect_Rule13:
	.string "Don't TP anyone's house.\lUnless they deserve it.$"
gSelect_Rule14: @
	.string "When in doubt, consult the ITEMFINDER.$"
gSelect_Rule15:
	.string "Always brag about how much candy you got.$"
gSelect_Rule16: @ 
	.string "Be sure to check out your candy. Some\l"
	.string "can turn out to be very useful.$"
gSelect_Rule17:
	.string "Do not dress as anyone arrested recently.$"
gSelect_Rule18: @
	.string "Don't forget to visit the Den to heal.$$"
gSelect_Rule19:
	.string "Always praise the {TRICK_MASTER}.$"
gSelect_Rule20: @
	.string "There's no benefit to hoarding candy!\l"
	.string "Don't be afraid to use or trade it!$"
gSelect_Rule21:
	.string "Do not taunt the skeletons.$"
gSelect_Rule22: @
	.string "The lady in the end room will say if you\l"
	.string "managed to find all the puzzle's candy.$"
gSelect_Rule23:
	.string "Always look both ways when crossing\l"
	.string "the path of a Alolan Meowth.$"
gSelect_Rule24: @
gSelect_Rule25:
	.string "Never suddenly pull a prop weapon on\l"
	.string "an elderly relative.$"
gSelect_Rule26: @
gSelect_Rule27:
	.string "When in doubt, consult the HELIX FOSSIL.$"
gSelect_Rule28: @
gSelect_Rule29:
gSelect_Rule30: @
gSelect_Rule31:
	.string "Never engage in a land war in Asia.$"
gSelect_Rule32: @
gSelect_Rule33:
gSelect_Rule34: @
gSelect_Rule35:
gSelect_Rule36: @
gSelect_Rule37:
	.string "Never use candy to attempt to wake a\l"
	.string "long-sleeping ancient legendary {POKEMON}.$"
gSelect_Rule38: @
gSelect_Rule39:
	.string "Don't eat candy with your mouth full.$"
gSelect_Rule40:
gSelect_Rule41:
gSelect_Rule42:
gSelect_Rule43:
gSelect_Rule44:
gSelect_Rule45:
gSelect_Rule46:
gSelect_Rule47:
gSelect_Rule48:
gSelect_Rule49:
gSelect_Rule50:
gSelect_Rule51:
gSelect_Rule52:
gSelect_Rule53:
gSelect_Rule54:
gSelect_Rule55:
gSelect_Rule56:
gSelect_Rule57:
gSelect_Rule58:
gSelect_Rule59:
	.string "Don't eat candy under the full moon\l"
	.string "during the autumnal equinox.$"
gSelect_Rule60:
gSelect_Rule61:
gSelect_Rule62:
gSelect_Rule63:
gSelect_Rule64:
gSelect_Rule65:
gSelect_Rule66:
gSelect_Rule67:
gSelect_Rule68:
gSelect_Rule69:
gSelect_Rule70:
gSelect_Rule71:
gSelect_Rule72:
gSelect_Rule73:
gSelect_Rule74:
gSelect_Rule75:
gSelect_Rule76:
gSelect_Rule77:
gSelect_Rule78:
gSelect_Rule79:
gSelect_Rule80:
gSelect_Rule81:
gSelect_Rule82:
gSelect_Rule83:
gSelect_Rule84:
gSelect_Rule85:
gSelect_Rule86:
gSelect_Rule87:
gSelect_Rule88:
gSelect_Rule89:
gSelect_Rule90:
gSelect_Rule91:
gSelect_Rule92:
gSelect_Rule93:
gSelect_Rule94:
gSelect_Rule95:
gSelect_Rule96:
gSelect_Rule97:
gSelect_Rule98:
gSelect_Rule99:
gSelect_RuleA0:
gSelect_RuleA1:
gSelect_RuleA2:
gSelect_RuleA3:
gSelect_RuleA4:
gSelect_RuleA5:
gSelect_RuleA6:
gSelect_RuleA7:
gSelect_RuleA8:
gSelect_RuleA9:
gSelect_RuleB0:
gSelect_RuleB1:
gSelect_RuleB2:
gSelect_RuleB3:
gSelect_RuleB4:
gSelect_RuleB5:
gSelect_RuleB6:
gSelect_RuleB7:
gSelect_RuleB8:
gSelect_RuleB9:
gSelect_RuleC0:
gSelect_RuleC1:
gSelect_RuleC2:
gSelect_RuleC3:
gSelect_RuleC4:
gSelect_RuleC5:
gSelect_RuleC6:
gSelect_RuleC7:
gSelect_RuleC8:
gSelect_RuleC9:
gSelect_RuleD0:
gSelect_RuleD1:
gSelect_RuleD2:
gSelect_RuleD3:
gSelect_RuleD4:
gSelect_RuleD5:
gSelect_RuleD6:
gSelect_RuleD7:
gSelect_RuleD8:
gSelect_RuleD9:
gSelect_RuleE0:
gSelect_RuleE1:
gSelect_RuleE2:
gSelect_RuleE3:
gSelect_RuleE4:
gSelect_RuleE5:
gSelect_RuleE6:
gSelect_RuleE7:
gSelect_RuleE8:
gSelect_RuleE9:
gSelect_RuleF0:
gSelect_RuleF1:
gSelect_RuleF2:
gSelect_RuleF3:
gSelect_RuleF4:
gSelect_RuleF5:
gSelect_RuleF6:
gSelect_RuleF7:
gSelect_RuleF8:
gSelect_RuleF9:
	.string "Have fun!$"
