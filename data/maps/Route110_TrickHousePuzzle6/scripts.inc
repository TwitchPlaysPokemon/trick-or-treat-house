Route110_TrickHousePuzzle6_MapScripts:: @ 826DDA7
	map_script MAP_SCRIPT_ON_TRANSITION, Route110_TrickHousePuzzle6_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, Route110_TrickHousePuzzle6_MapTable
	map_script MAP_SCRIPT_PUZZLE_TEARDOWN_SCRIPT, Route110_TrickHousePuzzle6_PuzzleTeardown
	.byte 0

@ -----------------------------------------------------

.align 2
Route110_TrickHousePuzzle6_GateSetup::
	gate_puzzle_config 14,  5, GATE_SHAPE_T1, GATE_ORIENTATION_90
    gate_puzzle_config 10,  6, GATE_SHAPE_L2, GATE_ORIENTATION_180
    gate_puzzle_config  6,  6, GATE_SHAPE_L4, GATE_ORIENTATION_90
    gate_puzzle_config 14,  8, GATE_SHAPE_T1, GATE_ORIENTATION_90
    gate_puzzle_config  3, 10, GATE_SHAPE_L3, GATE_ORIENTATION_270
    gate_puzzle_config  9, 14, GATE_SHAPE_L1, GATE_ORIENTATION_90
    gate_puzzle_config  3, 15, GATE_SHAPE_T3, GATE_ORIENTATION_0
    gate_puzzle_config  2, 17, GATE_SHAPE_L2, GATE_ORIENTATION_180
    gate_puzzle_config 12, 18, GATE_SHAPE_T3, GATE_ORIENTATION_270
    gate_puzzle_config  5, 18, GATE_SHAPE_L4, GATE_ORIENTATION_90
    gate_puzzle_config 10, 19, GATE_SHAPE_L3, GATE_ORIENTATION_180


Route110_TrickHousePuzzle6_OnTransition: @ 826DDB2
	loadword 0, Route110_TrickHousePuzzle6_GateSetup
	loadword 1, 11
	callnative RotatingGate_InitPuzzle
	end

Route110_TrickHousePuzzle6_PuzzleTeardown:
	callnative RotatingGate_DestroyPuzzle
	end

Route110_TrickHousePuzzle6_MapTable: @ 826DDB6
	map_script_2 VAR_TEMP_0, 16384, Route110_TrickHousePuzzle6_EventScript_26DDC0
	.2byte 0

Route110_TrickHousePuzzle6_EventScript_26DDC0:: @ 826DDC0
	@ loadword 0, Route110_TrickHousePuzzle6_GateSetup
	@ loadword 1, 11
	callnative_noctx RotatingGate_InitPuzzleAndGraphics
	end

@ -----------------------------------------------------


Route110_TrickHousePuzzle6_EventScript_26DDE1:: @ 826DDE1
	@ trainerbattle_single TRAINER_SOPHIA, Route110_TrickHousePuzzle6_Text_26DE93, Route110_TrickHousePuzzle6_Text_26DED2
	@ msgbox Route110_TrickHousePuzzle6_Text_26DEF3, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle6_EventScript_26DDF8:: @ 826DDF8
	@ trainerbattle_single TRAINER_BENNY, Route110_TrickHousePuzzle6_Text_26DF55, Route110_TrickHousePuzzle6_Text_26DF8D
	@ msgbox Route110_TrickHousePuzzle6_Text_26DFA0, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle6_EventScript_26DE0F:: @ 826DE0F
	@ trainerbattle_single TRAINER_SEBASTIAN, Route110_TrickHousePuzzle6_Text_26DFD7, Route110_TrickHousePuzzle6_Text_26E004
	@ msgbox Route110_TrickHousePuzzle6_Text_26E048, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle6_Text_26DE93: @ 826DE93
	.string "When I heard there was a strange\n"
	.string "house, I had to check it out.$"

Route110_TrickHousePuzzle6_Text_26DED2: @ 826DED2
	.string "I've discovered a tough TRAINER!$"

Route110_TrickHousePuzzle6_Text_26DEF3: @ 826DEF3
	.string "I'm sure having a good time checking\n"
	.string "this place out.\p"
	.string "It's a challenge I've found worth\n"
	.string "repeating!$"

Route110_TrickHousePuzzle6_Text_26DF55: @ 826DF55
	.string "Maybe I could get my BIRD POKéMON\n"
	.string "to fly over the wall…$"

Route110_TrickHousePuzzle6_Text_26DF8D: @ 826DF8D
	.string "Gwaaah! I blew it!$"

Route110_TrickHousePuzzle6_Text_26DFA0: @ 826DFA0
	.string "Ehehehe… I guess I lost because\n"
	.string "I was trying to cheat.$"

Route110_TrickHousePuzzle6_Text_26DFD7: @ 826DFD7
	.string "I'm getting dizzy from these rotating\n"
	.string "doors…$"

Route110_TrickHousePuzzle6_Text_26E004: @ 826E004
	.string "Everything's spinning around and\n"
	.string "around. I can't take this anymore…$"

Route110_TrickHousePuzzle6_Text_26E048: @ 826E048
	.string "You don't seem to be affected at all.\n"
	.string "Or do you have your poker face on?$"

