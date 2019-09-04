Puzzle_TrickHouseCut_MapScripts::
	puzzle_info Puzzle_TrickHouseCut_Name, Puzzle_TrickHouseCut_Author
	puzzle_adjective Puzzle_TrickHouseCut_Adjective
	puzzle_quip Puzzle_TrickHouseCut_Quip
	puzzle_item_prereqs Puzzle_TrickHouseCut_PrereqItems
	puzzle_remove_after Puzzle_TrickHouseCut_RemoveItems
	.byte 0

Puzzle_TrickHouseCut_Name:
	.string "Shrub Shredding$"
Puzzle_TrickHouseCut_Author:
	.string "Tustin2121$"
Puzzle_TrickHouseCut_Adjective:
	.string "slicing good$"
Puzzle_TrickHouseCut_Quip:
	.string "Sometimes it's better to just do the\n"
	.string "field moves yourself, you know?$"

.align 2
Puzzle_TrickHouseCut_RemoveItems:
	.2byte ITEM_CUT_ITEM
	.2byte ITEM_STRENGTH_ITEM
	.2byte 0

.align 2
Puzzle_TrickHouseCut_PrereqItems:
	.2byte ITEM_STRENGTH_ITEM
	.2byte 0

@ -----------------------------------------------------

Puzzle_TrickHouseCut_Trainer1::
	trainerbattle_single TRAINER_01, Puzzle_TrickHouseCut_Trainer1_Intro, Puzzle_TrickHouseCut_Trainer1_Defeat
	msgbox Puzzle_TrickHouseCut_Trainer1_After, MSGBOX_AUTOCLOSE
	end
Puzzle_TrickHouseCut_Trainer1_Intro:
	.string "Nice costume. Were you trick-or-treating\n"
	.string "too?$"
Puzzle_TrickHouseCut_Trainer1_Defeat:
	.string "Ack! My costume got caught!$"
Puzzle_TrickHouseCut_Trainer1_After:
	.string "Battling in costume is something I've\n"
	.string "never done before. How about you?$"


Puzzle_TrickHouseCut_Trainer2::
	trainerbattle_single TRAINER_02, Puzzle_TrickHouseCut_Trainer2_Intro, Puzzle_TrickHouseCut_Trainer2_Defeat
	msgbox Puzzle_TrickHouseCut_Trainer2_After, MSGBOX_AUTOCLOSE
	end
Puzzle_TrickHouseCut_Trainer2_Intro:
	.string "HA!$"
Puzzle_TrickHouseCut_Trainer2_Defeat:
	.string "Ack! My costume got caught!$"
Puzzle_TrickHouseCut_Trainer2_After:
	.string "Battling in costume is something I've\n"
	.string "never done before. How about you?$"

