PuzzleCommon_Text_FirstPuzzleIntro::
	.string "This first puzzle I whipped up in a\n"
	.string "brilliant haze after collecting all the\l"
	.string "other puzzles you'll see tonight!\p"
	.string "I'd describe it as {PUZZLE_ADJECTIVE}!\p"
	.string "If you can't make it through this one,\n"
	.string "there's no point in even bothering you\l"
	.string "with the rest!\p"
	.string "See you on the other end!$"

@ -----------------------------------------------------

.align 2
PuzzleCommon_TextArray_PuzzleIntro_NoItems::
	.4byte PuzzleCommon_TextArray_PuzzleIntro_NoItems00
	.4byte 0

PuzzleCommon_TextArray_PuzzleIntro_NoItems00:
	.string "The next challenge I collected off\n"
	.string "someone called {PUZZLE_AUTHOR}.\p"
	.string "I'd call it a {PUZZLE_ADJECTIVE} puzzle!\p"
	.string "See you on the other side!$"

@ -----------------------------------------------------

.align 2
PuzzleCommon_TextArray_PuzzleIntro_Items::
	.4byte PuzzleCommon_TextArray_PuzzleIntro_Items00
	.4byte 0

PuzzleCommon_TextArray_PuzzleIntro_Items00:
	.string "The next challenge I collected off\n"
	.string "someone called {PUZZLE_AUTHOR}.\p"
	.string "I'd call it a {PUZZLE_ADJECTIVE} puzzle!\p"
	.string "Here's something you'll need to do\n"
	.string "this puzzle! Good luck!$"


@ -----------------------------------------------------

.align 2
PuzzleCommon_TextArray_SecretCodes::
	.4byte PuzzleCommon_Text_SecretCode01
	.4byte PuzzleCommon_Text_SecretCode02
	.4byte PuzzleCommon_Text_SecretCode03
	.4byte PuzzleCommon_Text_SecretCode04
	.4byte PuzzleCommon_Text_SecretCode05
	.4byte PuzzleCommon_Text_SecretCode06
	.4byte PuzzleCommon_Text_SecretCode07
	.4byte PuzzleCommon_Text_SecretCode08
	.4byte PuzzleCommon_Text_SecretCode09
	.4byte PuzzleCommon_Text_SecretCode10
	.4byte PuzzleCommon_Text_SecretCode11
PuzzleCommon_TextArray_SecretCodes_END::
	.4byte 0

PuzzleCommon_Text_SecretCode01:
	.string "This is Halloween!$"
PuzzleCommon_Text_SecretCode02:
	.string "PUMPKABOO scream in the dead of night…$"
PuzzleCommon_Text_SecretCode03:
	.string "Ride with the moon in the dead of night…$"
PuzzleCommon_Text_SecretCode04:
	.string "I am the shadow on the moon at night…$"
PuzzleCommon_Text_SecretCode05:
	.string "The clown with the tearaway face…$"
PuzzleCommon_Text_SecretCode06:
	.string "Watch out for EKANS!$"
PuzzleCommon_Text_SecretCode07:
	.string "It's just a bunch of Hocus Pocus!$"
PuzzleCommon_Text_SecretCode08:
	.string "Double double, toil and trouble…$"
PuzzleCommon_Text_SecretCode09:
	.string "Nevermore!$"
PuzzleCommon_Text_SecretCode10:
	.string "Something wicked this way comes…$"
PuzzleCommon_Text_SecretCode11:
	.string "Don't look behind you…$"