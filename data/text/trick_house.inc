PuzzleCommon_Text_GameIntro::
	.string "Behold!\n"
	.string "For I am the greatest living mystery\l"
	.string "of a man in all of HOENN!\p"
	.string "They call me… The {TRICK_MASTER}!{PAUSE 40}\n"
	.string "Wahahaha!\p"
	.string "You! You there!\p"
	.string "You heard about my wonderful event\n"
	.string "the TRICK-OR-TREAT HOUSE, haven't you?\p"
	.string "That's why you're here! To CHALLENGE it!\n"
	.string "Yes! Yes, it is!\p"
	.string "You see, I have gone on a journey\n"
	.string "of discovery, all around the world!\p"
	.string "I have discovered tricks and puzzles the\n"
	.string "likes of which you've never seen before!\p"
	.string "And I have compiled them all!\n"
	.string "A menagerie of puzzles!\p"
	.string "Puzzles that will take you FAR!\n"
	.string "Tricks that will take you WIDE!\l"
	.string "Glory is to be had! Candy is to be had!\l"
	.string "Can you make it through ALL of them?!\p"
	.string "Come! Through this scroll!\n"
	.string "Back there, we shall begin!$"
			@ Trick master shoots off screen
			
PuzzleCommon_Text_FirstPuzzleIntro::
	.string "Usually, a {TRICK_MASTER} such as\n"
	.string "myself never reveals his secrets!\p"
	.string "But this is a special occasion!\p"
	.string "Behold! My special door!\p"
	.string "You need not know how it works!\n"
	.string "But know that instantly you will travel\l"
	.string "to the location of the puzzle!\p"
	.string "There, you will find a SCROLL, somewhere,\n"
	.string "hidden, telling you a SECRET CODE!\p"
	.string "And on the other end, a STONE DOOR,\n"
	.string "onto which you write the SECRET CODE.\p"
	.string "The door opens! Instantly, back,\n"
	.string "you shall come, to my TRICK HOUSE!\p"
	.string "You shall see! With this first puzzle!\p"
	.string "A shadow of one of my old puzzles,\n"
	.string "but useful for weeding out those\l"
	.string "unworthy to behold the greatness\l"
	.string "of the puzzles to come!\p"
	.string "I shall be waiting in the back!$"

PuzzleCommon_Text_FirstPuzzleAfterword::
	.string "Ah ha! You've made it to me!\n"
	.string "I knew you were sharp!\p"
	.string "Previously I would lament how you've\n"
	.string "bested me, but not tonight!\p"
	.string "For you see, that was simply the tip\n"
	.string "of the iceberg!\p"
	.string "My wonderful door affords me multiple\n"
	.string "tricks to be had all in a row!\p"
	.string "But the night is young!\n"
	.string "Rest a moment if you wish.\p"
	.string "The lady to the left will heal your\n"
	.string "RENTAL {POKEMON}. Or sit and chat here\l"
	.string "with friends involved with the puzzle.\p"
	.string "I await you in the front corridor\n"
	.string "for your next challenge!$"

PuzzleCommon_Text_PuzzleIntro_CommonBye::
	.string "See you on the other side!$"
PuzzleCommon_Text_PuzzleIntro_GivenItems:
	.string "You're handed {STR_VAR_1}!{PAUSE 20}$"

@ -----------------------------------------------------

.align 2
PuzzleCommon_TextArray_PuzzleIntro_NoItems::
	.4byte PuzzleCommon_TextArray_PuzzleIntro_NoItems00
	.4byte PuzzleCommon_TextArray_PuzzleIntro_NoItems01
	.4byte PuzzleCommon_TextArray_PuzzleIntro_NoItems02
	.4byte PuzzleCommon_TextArray_PuzzleIntro_NoItems03
	.4byte 0

PuzzleCommon_TextArray_PuzzleIntro_NoItems00:
	.string "Hah! You've returned for another\n"
	.string "challenge!\p"
	.string "This next one is a {PUZZLE_ADJECTIVE}\n"
	.string "puzzle to be sure!\p"
	.string "I collected it off a fellow who called\n"
	.string "themself {PUZZLE_AUTHOR}.\p"
	.string "Let us see how you do with it!$"
PuzzleCommon_TextArray_PuzzleIntro_NoItems01:
	.string "Hah! Back for more then?\p"
	.string "This next puzzle is a {PUZZLE_ADJECTIVE}\n"
	.string "by one {PUZZLE_AUTHOR}.\p"
	.string "Can you handle it? Wahahahaha!$"
PuzzleCommon_TextArray_PuzzleIntro_NoItems02:
	.string "That last one was a pushover for you,\n"
	.string "it seems!\p"
	.string "Let's see how you do with this next\n"
	.string "one, a {PUZZLE_ADJECTIVE} kind of\l"
	.string "puzzle, thought up by {PUZZLE_AUTHOR}.\p"
	.string "Good luck! Wahahahaha!$"
PuzzleCommon_TextArray_PuzzleIntro_NoItems03:
	.string "You're good at these puzzles, aren't you?\p"
	.string "But this next one is a {PUZZLE_ADJECTIVE}\n"
	.string "one to be sure.\p"
	.string "It's one I collected it off someone\n"
	.string "called {PUZZLE_AUTHOR}.\p"
	.string "See you on the other side!$"

@ -----------------------------------------------------

.align 2
PuzzleCommon_TextArray_PuzzleIntro_Items::
	.4byte PuzzleCommon_TextArray_PuzzleIntro_Items00
	.4byte PuzzleCommon_TextArray_PuzzleIntro_Items01
	.4byte PuzzleCommon_TextArray_PuzzleIntro_Items02
	.4byte PuzzleCommon_TextArray_PuzzleIntro_Items03
	.4byte 0
PuzzleCommon_TextArray_PuzzleIntro_Items_Bye::
	.4byte PuzzleCommon_TextArray_PuzzleIntro_Items00b
	.4byte PuzzleCommon_TextArray_PuzzleIntro_Items01b
	.4byte PuzzleCommon_TextArray_PuzzleIntro_Items02b
	.4byte PuzzleCommon_TextArray_PuzzleIntro_Items03b
	.4byte 0

PuzzleCommon_TextArray_PuzzleIntro_Items00:
	.string "Hah! You've returned for another\n"
	.string "challenge!\p"
	.string "This next one is a {PUZZLE_ADJECTIVE}\n"
	.string "puzzle to be sure!\p"
	.string "I collected it off a fellow who called\n"
	.string "themself {PUZZLE_AUTHOR}.\p"
	.string "Ah, but this one you will need a thing\n"
	.string "or two before you start.$"
PuzzleCommon_TextArray_PuzzleIntro_Items00b:
	.string "Let us see how you do!$"
PuzzleCommon_TextArray_PuzzleIntro_Items01:
	.string "Hah! Back for more then?\p"
	.string "This next puzzle is a {PUZZLE_ADJECTIVE}\n"
	.string "by one {PUZZLE_AUTHOR}.\p"
	.string "Can you handle it? Wahahahaha!\p"
	.string "But before I go, you'll need these.$"
PuzzleCommon_TextArray_PuzzleIntro_Items01b:
	.string "As I was saying, Wahahahaha!$"
PuzzleCommon_TextArray_PuzzleIntro_Items02:
	.string "That last one was a pushover for you,\n"
	.string "it seems!\p"
	.string "Let's see how you do with this next\l"
	.string "one, a {PUZZLE_ADJECTIVE} kind of\l"
	.string "puzzle, thought up by {PUZZLE_AUTHOR}.\p"
	.string "Here's what you'll need for the puzzle.$"
PuzzleCommon_TextArray_PuzzleIntro_Items02b:
	.string "Good luck! Wahahahaha!$"
PuzzleCommon_TextArray_PuzzleIntro_Items03:
	.string "You're good at these puzzles, aren't you?\p"
	.string "But this next one is a {PUZZLE_ADJECTIVE}\n"
	.string "one to be sure.\p"
	.string "It's one I collected it off someone\n"
	.string "called {PUZZLE_AUTHOR}.\p"
	.string "I also collected these things, which\n"
	.string "you'll need for the puzzle.$"
PuzzleCommon_TextArray_PuzzleIntro_Items03b:
	.string "See you on the other side!$"


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
