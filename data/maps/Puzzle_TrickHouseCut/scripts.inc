Puzzle_TrickHouseCut_MapScripts::
	puzzle_info Puzzle_TrickHouseCut_Name, Puzzle_TrickHouseCut_Author
	puzzle_adjective Puzzle_TrickHouseCut_Adjective
	puzzle_quip Puzzle_TrickHouseCut_Quip
	puzzle_remove_after Puzzle_TrickHouseCut_RemoveItems
	.byte 0

Puzzle_TrickHouseCut_Name:
	.string "Shrub Shredding$"
Puzzle_TrickHouseCut_Author:
	.string "Tustin2121$"
Puzzle_TrickHouseCut_Adjective:
	.string "slicing$"
Puzzle_TrickHouseCut_Quip:
	.string "Sometimes it's better to just do the\n"
	.string "field moves yourself, you know?$"

.align 2
Puzzle_TrickHouseCut_RemoveItems:
	.2byte ITEM_CUT_ITEM
	.2byte 0

@ -----------------------------------------------------




