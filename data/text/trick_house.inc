PuzzleCommon_Text_GameIntro::
	.string "Behold!\n"
	.string "For I am the greatest living mystery\l"
	.string "of a man in all of HOENN!\p"
	.string "They call me… The {TRICK_MASTER}!{PAUSE 40}\n"
	.string "Wahahaha!{PAUSE 30}\p"
	.string "You! You all here!\p"
	.string "You heard about my wonderful event, the\n"
	.string "TRICK-OR-TREAT HOUSE, haven't you?\p"
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

PuzzleCommon_Text_FirstPuzzleIntroRound2::
	.string "Oh, you're back! Wonderful!\p"
	.string "Unfortunately, I've run out of puzzles\n"
	.string "for you to do! Tragic, I know!\p"
	.string "But I can see you're so awestruck by\n"
	.string "my collection of puzzles that you wish\l"
	.string "to do them again!\p"
	.string "Yes! Excellent! Welcome back to the\n"
	.string "first puzzle!\p"
	.string "A shadow of one of my old puzzles,\n"
	.string "but useful for weeding out those\l"
	.string "unworthy to behold the greatness of\l"
	.string "the puzzles you've experienced tonight!\p"
	.string "See you on the other side!$"

@ -----------------------------------------------------

PuzzleCommon_Text_PuzzleIntro_Generic::
	.string "{DYNAMIC 0}\p" @ Greeting
	.string "{DYNAMIC 2}\p" @ AuthoredBy
	.string "{DYNAMIC 1}$" @ Farewell
PuzzleCommon_Text_PuzzleIntro_GenericItem1::
	.string "{DYNAMIC 0}\p" @ Greeting
	.string "{DYNAMIC 2}\p" @ AuthoredBy
	.string "{DYNAMIC 3}$" @ ItemLede
PuzzleCommon_Text_PuzzleIntro_GenericItem2::
	.string "{DYNAMIC 1}$" @ Farewell

PuzzleCommon_Text_PuzzleIntro_CommonBye::
	.string "See you on the other side!$"
PuzzleCommon_Text_PuzzleIntro_GivenItems::
	.string "You're handed {STR_VAR_1}!{PAUSE 20}$"

@ -----------------------------------------------------

.align 2
PuzzleCommon_TextArray_PuzzleIntro_Greeting::
	.4byte PuzzleCommon_TextArray_PuzzleIntro_GreetingA
	.4byte PuzzleCommon_TextArray_PuzzleIntro_GreetingB
	.4byte PuzzleCommon_TextArray_PuzzleIntro_GreetingC
	.4byte PuzzleCommon_TextArray_PuzzleIntro_GreetingD
	.4byte PuzzleCommon_TextArray_PuzzleIntro_GreetingE
	.4byte PuzzleCommon_TextArray_PuzzleIntro_GreetingF
	.4byte 0
PuzzleCommon_TextArray_PuzzleIntro_GreetingA:
	.string "Hah! You've returned for another\n"
	.string "challenge!$"
PuzzleCommon_TextArray_PuzzleIntro_GreetingB:
	.string "Hah! Back for more?$"
PuzzleCommon_TextArray_PuzzleIntro_GreetingC:
	.string "That last one as a tough one,\n"
	.string "wasn't it? Hah!$"
PuzzleCommon_TextArray_PuzzleIntro_GreetingD:
	.string "Hah! You're doing well tonight?$"
PuzzleCommon_TextArray_PuzzleIntro_GreetingE:
	.string "Hah! Seems like you made it through that\n"
	.string "last one with ease!$"
PuzzleCommon_TextArray_PuzzleIntro_GreetingF:
	.string "Hah! Welcome back!\n"
	.string "How did that last one go?$"

@ -----------------------------------------------------

.align 2
PuzzleCommon_TextArray_PuzzleIntro_Farewell::
	.4byte PuzzleCommon_TextArray_PuzzleIntro_FarewellA
	.4byte PuzzleCommon_TextArray_PuzzleIntro_FarewellB
	.4byte PuzzleCommon_TextArray_PuzzleIntro_FarewellC
	.4byte PuzzleCommon_TextArray_PuzzleIntro_FarewellD
	.4byte PuzzleCommon_TextArray_PuzzleIntro_FarewellE
	.4byte 0
PuzzleCommon_TextArray_PuzzleIntro_FarewellA:
	.string "See you on the other side!$"
PuzzleCommon_TextArray_PuzzleIntro_FarewellB:
	.string "Let us see how you do with it!$"
PuzzleCommon_TextArray_PuzzleIntro_FarewellC:
	.string "Good luck! Wahahahaha!$"
PuzzleCommon_TextArray_PuzzleIntro_FarewellD:
	.string "Let's see how you handle it!$"
PuzzleCommon_TextArray_PuzzleIntro_FarewellE:
	.string "Wahahahaha!$"

@ -----------------------------------------------------

.align 2
PuzzleCommon_TextArray_PuzzleIntro_ItemsLede::
	.4byte PuzzleCommon_TextArray_PuzzleIntro_ItemsLedeA
	.4byte PuzzleCommon_TextArray_PuzzleIntro_ItemsLedeB
	.4byte PuzzleCommon_TextArray_PuzzleIntro_ItemsLedeC
	.4byte PuzzleCommon_TextArray_PuzzleIntro_ItemsLedeD
	.4byte PuzzleCommon_TextArray_PuzzleIntro_ItemsLedeE
	.4byte 0
PuzzleCommon_TextArray_PuzzleIntro_ItemsLedeA:
	.string "Ah, but you will need a thing or two\n"
	.string "before you start this one.$"
PuzzleCommon_TextArray_PuzzleIntro_ItemsLedeB:
	.string "But before I go, you'll need these.$"
PuzzleCommon_TextArray_PuzzleIntro_ItemsLedeC:
	.string "Ah, but first, you'll need these.$"
PuzzleCommon_TextArray_PuzzleIntro_ItemsLedeD:
	.string "I was given these things, which\n"
	.string "you'll need for the puzzle.$"
PuzzleCommon_TextArray_PuzzleIntro_ItemsLedeE:
	.string "You're going to need these!$"

@ -----------------------------------------------------

.align 2
PuzzleCommon_TextArray_PuzzleIntro_AuthoredBy::
	.4byte PuzzleCommon_TextArray_PuzzleIntro_AuthoredByA
	.4byte PuzzleCommon_TextArray_PuzzleIntro_AuthoredByB
	.4byte PuzzleCommon_TextArray_PuzzleIntro_AuthoredByC
	.4byte PuzzleCommon_TextArray_PuzzleIntro_AuthoredByD
	.4byte PuzzleCommon_TextArray_PuzzleIntro_AuthoredByE
	.4byte 0
PuzzleCommon_TextArray_PuzzleIntro_AuthoredByA:
	.string "This next one is a {PUZZLE_ADJECTIVE}\n"
	.string "puzzle to be sure!\p"
	.string "I collected it off a fellow who called\n"
	.string "themself {PUZZLE_AUTHOR}.$"
PuzzleCommon_TextArray_PuzzleIntro_AuthoredByB:
	.string "This next puzzle is a {PUZZLE_ADJECTIVE}\n"
	.string "one, by one {PUZZLE_AUTHOR}.$"
PuzzleCommon_TextArray_PuzzleIntro_AuthoredByC:
	.string "Let's see how you do with this next\n"
	.string "one, a {PUZZLE_ADJECTIVE} kind of\l"
	.string "puzzle, thought up by {PUZZLE_AUTHOR}.$"
PuzzleCommon_TextArray_PuzzleIntro_AuthoredByD:
	.string "This next one is a {PUZZLE_ADJECTIVE}\n"
	.string "puzzle to be sure.\p"
	.string "It's one I collected it off someone\n"
	.string "called {PUZZLE_AUTHOR}.$"
PuzzleCommon_TextArray_PuzzleIntro_AuthoredByE:
	.string "This next puzzle I borrowed from one\n"
	.string "{PUZZLE_AUTHOR} who I met on my travels.\p"
	.string "I'd call it {PUZZLE_ADJECTIVE}.$"

@ -----------------------------------------------------

.align 2
PuzzleCommon_TextArray_PuzzleIntro_InspiredBy::
	.4byte PuzzleCommon_TextArray_PuzzleIntro_InspiredByA
	.4byte PuzzleCommon_TextArray_PuzzleIntro_InspiredByB
	.4byte PuzzleCommon_TextArray_PuzzleIntro_InspiredByC
	.4byte PuzzleCommon_TextArray_PuzzleIntro_InspiredByD
	.4byte PuzzleCommon_TextArray_PuzzleIntro_InspiredByE
	.4byte 0
@ Note: PUZZLE_AUTHOR is the inspiration in this instance
PuzzleCommon_TextArray_PuzzleIntro_InspiredByA:
	.string "This next one is a {PUZZLE_ADJECTIVE}\n"
	.string "puzzle to be sure!\p"
	.string "It was inspired by {PUZZLE_AUTHOR}.$"
PuzzleCommon_TextArray_PuzzleIntro_InspiredByB:
	.string "This next puzzle is a {PUZZLE_ADJECTIVE}\n"
	.string "one, inspired by {PUZZLE_AUTHOR}!$"
PuzzleCommon_TextArray_PuzzleIntro_InspiredByC:
	.string "Let's see how you do with this next\n"
	.string "one, a {PUZZLE_ADJECTIVE} kind of\l"
	.string "puzzle, thanks to the inspiration\l"
	.string "{PUZZLE_AUTHOR} provided.$"
PuzzleCommon_TextArray_PuzzleIntro_InspiredByD:
	.string "This next one is a {PUZZLE_ADJECTIVE}\n"
	.string "puzzle to be sure.\p"
	.string "I was inspired by {PUZZLE_AUTHOR}.$"
PuzzleCommon_TextArray_PuzzleIntro_InspiredByE:
	.string "This next puzzle was inspired by my\n"
	.string "interactions with {PUZZLE_AUTHOR}.\p"
	.string "I'd call it {PUZZLE_ADJECTIVE}.$"

@ -----------------------------------------------------

.align 2
PuzzleCommon_TextArray_PuzzleIntro_BuiltBy::
	.4byte PuzzleCommon_TextArray_PuzzleIntro_BuiltByA
	.4byte PuzzleCommon_TextArray_PuzzleIntro_BuiltByB
	.4byte PuzzleCommon_TextArray_PuzzleIntro_BuiltByC
	.4byte PuzzleCommon_TextArray_PuzzleIntro_BuiltByD
	.4byte PuzzleCommon_TextArray_PuzzleIntro_BuiltByE
	.4byte 0
PuzzleCommon_TextArray_PuzzleIntro_BuiltByA:
	.string "This next one is a {PUZZLE_ADJECTIVE}\n"
	.string "puzzle, built by {PUZZLE_AUTHOR}!$"
PuzzleCommon_TextArray_PuzzleIntro_BuiltByB:
	.string "This next puzzle is a {PUZZLE_ADJECTIVE}\n"
	.string "one, put together by {PUZZLE_AUTHOR}.$"
PuzzleCommon_TextArray_PuzzleIntro_BuiltByC:
	.string "Let's see how you do with this next\n"
	.string "one, a {PUZZLE_ADJECTIVE} kind of\l"
	.string "puzzle, compiled by {PUZZLE_AUTHOR}.$"
PuzzleCommon_TextArray_PuzzleIntro_BuiltByD:
	.string "This next one is a {PUZZLE_ADJECTIVE}\n"
	.string "puzzle to be sure.\p"
	.string "Someone called {PUZZLE_AUTHOR} put\n"
	.string "it together for me!$"
PuzzleCommon_TextArray_PuzzleIntro_BuiltByE:
	.string "This next puzzle I borrowed from one\n"
	.string "{PUZZLE_AUTHOR}, who built it for me.\p"
	.string "I'd call it {PUZZLE_ADJECTIVE}.$"

@ -----------------------------------------------------

.align 2
PuzzleCommon_TextArray_PuzzleIntro_GameFreak::
	.4byte PuzzleCommon_TextArray_PuzzleIntro_GameFreakA
	.4byte PuzzleCommon_TextArray_PuzzleIntro_GameFreakB
	.4byte PuzzleCommon_TextArray_PuzzleIntro_GameFreakC
	.4byte PuzzleCommon_TextArray_PuzzleIntro_GameFreakD
	.4byte PuzzleCommon_TextArray_PuzzleIntro_GameFreakE
	.4byte 0
PuzzleCommon_TextArray_PuzzleIntro_GameFreakA:
	.string "I stumbled upon this {PUZZLE_ADJECTIVE}\n"
	.string "puzzle in my travels.$"
PuzzleCommon_TextArray_PuzzleIntro_GameFreakB:
	.string "I found this {PUZZLE_ADJECTIVE} puzzle\n"
	.string "out in the wider world!$"
PuzzleCommon_TextArray_PuzzleIntro_GameFreakC:
	.string "This next puzzle is one I discovered\n"
	.string "on my worldly travels.\p"
	.string "I'd call it {PUZZLE_ADJECTIVE}!$"
PuzzleCommon_TextArray_PuzzleIntro_GameFreakD:
	.string "This next puzzle is inspired by my\n"
	.string "travels to regions far and near!\p"
	.string "It's a {PUZZLE_ADJECTIVE} one\n"
	.string "to be sure!$"
PuzzleCommon_TextArray_PuzzleIntro_GameFreakE:
	.string "While travelling the world, I came\n"
	.string "upon this {PUZZLE_ADJECTIVE} puzzle,\l"
	.string "which I will share with you today!$"

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
	.string "Halloween Haunts!$"
PuzzleCommon_Text_SecretCode02:
	.string "Pumpkaboo Screams!$"
PuzzleCommon_Text_SecretCode03:
	.string "Phantasmal Assailant!$"
PuzzleCommon_Text_SecretCode04:
	.string "Arachnophobia!$"
PuzzleCommon_Text_SecretCode05:
	.string "Eye of Newt!$" @ TODO: Newt Pokemon
PuzzleCommon_Text_SecretCode06:
	.string "Midnight Monster!$"
PuzzleCommon_Text_SecretCode07:
	.string "Hocus Pocus!$"
PuzzleCommon_Text_SecretCode08:
	.string "Nightmare Moon!$"
PuzzleCommon_Text_SecretCode09:
	.string "Nevermore!$"
PuzzleCommon_Text_SecretCode10:
	.string "Trevenant Tricks!$"
PuzzleCommon_Text_SecretCode11:
	.string "Cauldron Boils!$"
PuzzleCommon_Text_SecretCode12:
	.string "Witch's Fancy!$"
PuzzleCommon_Text_SecretCode13:
	.string "Cursed Corvoknight!$"
PuzzleCommon_Text_SecretCode14:
	.string "Yamask Menace!$"
PuzzleCommon_Text_SecretCode15:
	.string "Zombie Paras!$"
PuzzleCommon_Text_SecretCode16:
	.string "Ghastly Vision!$"
PuzzleCommon_Text_SecretCode17:
	.string "Gengar Spite!$"
PuzzleCommon_Text_SecretCode18:
	.string "Misdreavus Malpractice!$"
PuzzleCommon_Text_SecretCode19:
	.string "Hidden Mimikyu!$"
PuzzleCommon_Text_SecretCode20:
	.string "Haunted Mansion!$"
PuzzleCommon_Text_SecretCode21:
	.string "Chandelure Shakes!$"
