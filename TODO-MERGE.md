Feature Merging:
- [X] Feature branch: Follow Me:  https://github.com/ghoulslash/pokeemerald/tree/follow_me 
- [ ] Feature branch: Sideways Stairs
- [ ] Feature branch: overworld expansion (double check that this is all correct in TTH from this)
- [X] Feature branch: dynamic overworld palettes (double check ditto)
- [ ] Feature branch: Item descriptions on pickup: https://github.com/ghoulslash/pokeemerald/tree/item_desc_header 
- [ ] Tutorial: Improve loading of battle terrain (possibly)
- [X] Tutorial: Fix snow weather
- [ ] Tutorial: Missing text function RESET_SIZE
- [ ] Tutorial: EWRAM summary screen improvements?
- [ ] Tutorial: Run Custom Script on Trainer Sight?
- [ ] Tutorial: Trainer Class Based Poké Balls
- [ ] Port soaring? https://github.com/camthesaxman/pokeruby/tree/soar_2
- [ ] https://msikma.github.tio/pokesprite/overview/inventory.html
	- [ ] Check to see if the items from RHH need updated sprites? See if there's any I could use?
	- [ ] The TR icons could be useful, as well as the EXP candy.
	- [ ] Possibly use some curry ingredients for candy?
- [ ] Pull from merrp's stuff: https://github.com/aarant/pokeemerald
	- [ ] Dynamic overworld palettes & reflections compatable with vanilla berry trees (from followers)
	- [-] (look into "detect newer emulators/hardware)
	- [ ] Day/Night + window lights + lamp lights from the lighting branch


Known issues:
- [ ] Manectric on the intro screen is yellow instead of blue for some reason.
- [ ] Pokemon Says: When the high note is used, the azuril breaking out of the jar counts as a bad note, but talking to it after it breaks out isn't counted as a bad note.
- [ ] Farfetch'd Forest: When the farfetch'd flies, do hideReflection=true and add a shadow field effect or something; also disable ripples
- [ ] Mountain Trail: mapping error in a corner of the ledge. Either collision is needed or move to lower layer.


Changes:
- [ ] When entering/exiting the puzzle door/stone door, custom transition into and out of the door.
	- Look at fldeff_flash.c, copy Task_EnterCaveTransition3 (and related chain), and make a custom transition palette which goes from white, through several colors, to black, and doesn't fade out like the vanilla transition does.
	- Perhaps going into the door, the colors go from inside to out (so opposite Task_EnterCaveTransition3).
		- And then when exiting, they go outside in, return trip.
- [ ] Add newer-gen mons to the rental sequence.
- [ ] Lost Woods 1: Use Amongous instead of electrode?
- [ ] Towers: Change up pokemon to be more diverse?
- [ ] Towers: Possibly add follower friend to help?
- [ ] Change the emerald text border to orange themed.
	- [ ] Also add an optional text box for person's name using short/narrow text
- [ ] Finish BORTizing move names
- [ ] BORTize candy names
- [ ] Potentially add more BORT names for new pokemon, especially ones able to be given out as starters
- [ ] BORT: Go over the sGrammarMoveUsedTable and see if there's an updated version.
- [ ] Wild Pokemon should drop items, if only so a wild battle doesn't just end without the victory music.
- [ ] Change the party screen to only include 3 pokemon if there are only 3 pokemon in the party.
	- [ ] Make all three boxes spread out and large.
- [ ] Followers:
	- [ ] Trick Treat Petalburg: No one joins you
	- [ ] Trick Treat Fortree: Brendan / Treekid joins you.
	- [ ] Trick Treat Mossdeep: Treekid / May joins you.
	- [ ] Tower 1: James joins
	- [ ] Tower 2: Irene joins
	- [ ] Tower 3: Joey joins
	- [ ] Tower 4: Wally joins ("It sounded like you guys were having a lot of fun...")


Others:
- [X] Scripting Overhaul
	- [ ] Add command which prints to mgba. 
		- [ ] In poryscript, may need to specifically make ascii strings.
		- [ ] Possibly make one version of command print encoded
- [ ] Add map script for getting map overworld music
	- [ ] GetLocationMusic -> make map script
- [ ] Add map script for getting battle music
- [ ] Add enhancement where something tells the player if they got the scroll already.
	- I was thinking the costume could change, but that would likely require a map reload of figuring out how to change the graphic without a reload.
	- Could just add it to the pause screen, in a side window
- [ ] trainers.h -> change encounterMusic_gender to encounterMusic (any music) and split off gender.
- [ ] Change Relic items descriptions to instead say that "collectors may value it highly", as it needs to be specially sold in order to have value.
- [ ] Change some mulch to KEEP to allow use for the growing puzzle element puzzle.
- [ ] Implement GAME_STAT_NUM_CANDY_TRADES
- [ ] In battle_util.c, implement HOLD_EFFECT_CURE_PAR_HP and others
- [ ] Remove all sText_* from battle_strings_elf.h table and change the lookup function to fallback to the normal table in case of null pointer
- [ ] Search through MUS_ABANDONED_SHIP and replace them all
- [ ] Specials
- [ ] Convert player_forcestep to new naming scheme, also figure out wtf it's doing again
- [ ] Convert the DoorAnimTiles_TrickScroll to a single image, like the other door animations
- [ ] item effects - clean up and remove duplicated / unused item effects
- [ ] Remove unused event object graphics:
	gObjectEventGraphicsInfo_LinkBrendan
	gObjectEventGraphicsInfo_LinkMay
- [ ] Figure out if sBagSpriteAnimTable and specifically the ex-ball, now candy sprite animation should be moved, 
      and what even is going on with that I don't know...
- [ ] Remove duplicate OBJ_EVENT_PAL_TAG_BRIDGE_REFLECTION when figuring out if day/night is done correctly.
- [ ] Strip out all the match calls.
- [ ] sElevationToPriority and sElevationToSubspriteTableNum comments to pokeemerald
- [ ] Decapitalize contest_hall.inc
- [ ] Fix field moves to instead of saying "Used move!", the text box reads a description of what's happening.
- [ ] map_name_popup.c - Modify and use the defines??
- [X] Reorganize Flags and Vars
	- [X] Remove Temporary Aliases from Vars
- [ ] Add more strings to PuzzleCommon_TextArray_SecretCodes in trick_house.inc

----------------------------------------------------------

Reference changes:
- [X] ITEM0_DIRE_HIT -> ITEM0_HIGH_CRIT
- [X] eventObject->unk3_3 -> disableReflection -> hideReflection
- [X] gRamScriptRetAddr -> gRamScriptPtr
- [X] VAR_ICE_STEP_COUNT -> VAR_STEP_TRIGGER
- [X] gStringVar4 -> gStringBuffer
- [X] Palette Tags:
	OBJ_EVENT_PAL_TAG_BRENDAN                 0x1100       EVENT_OBJ_PAL_TAG_8
	OBJ_EVENT_PAL_TAG_BRENDAN_REFLECTION      0x1101       EVENT_OBJ_PAL_TAG_9
	OBJ_EVENT_PAL_TAG_BRIDGE_REFLECTION       0x1102       EVENT_OBJ_PAL_TAG_10
	OBJ_EVENT_PAL_TAG_NPC_1                   0x1103       EVENT_OBJ_PAL_TAG_0
	OBJ_EVENT_PAL_TAG_NPC_2                   0x1104       EVENT_OBJ_PAL_TAG_1
	OBJ_EVENT_PAL_TAG_NPC_3                   0x1105       EVENT_OBJ_PAL_TAG_2
	OBJ_EVENT_PAL_TAG_NPC_4                   0x1106       EVENT_OBJ_PAL_TAG_3
	OBJ_EVENT_PAL_TAG_NPC_1_REFLECTION        0x1107       EVENT_OBJ_PAL_TAG_4
	OBJ_EVENT_PAL_TAG_NPC_2_REFLECTION        0x1108       EVENT_OBJ_PAL_TAG_5
	OBJ_EVENT_PAL_TAG_NPC_3_REFLECTION        0x1109       EVENT_OBJ_PAL_TAG_6
	OBJ_EVENT_PAL_TAG_NPC_4_REFLECTION        0x110A       EVENT_OBJ_PAL_TAG_7
	OBJ_EVENT_PAL_TAG_QUINTY_PLUMP            0x110B       EVENT_OBJ_PAL_TAG_12
	OBJ_EVENT_PAL_TAG_QUINTY_PLUMP_REFLECTION 0x110C       EVENT_OBJ_PAL_TAG_13
	OBJ_EVENT_PAL_TAG_TRUCK                   0x110D       EVENT_OBJ_PAL_TAG_14
	OBJ_EVENT_PAL_TAG_VIGOROTH                0x110E       EVENT_OBJ_PAL_TAG_15
	OBJ_EVENT_PAL_TAG_ZIGZAGOON               0x110F       EVENT_OBJ_PAL_TAG_16
	OBJ_EVENT_PAL_TAG_MAY                     0x1110       EVENT_OBJ_PAL_TAG_17
	OBJ_EVENT_PAL_TAG_MAY_REFLECTION          0x1111       EVENT_OBJ_PAL_TAG_18
	OBJ_EVENT_PAL_TAG_MOVING_BOX              0x1112       EVENT_OBJ_PAL_TAG_19
	OBJ_EVENT_PAL_TAG_CABLE_CAR               0x1113       EVENT_OBJ_PAL_TAG_20
	OBJ_EVENT_PAL_TAG_SSTIDAL                 0x1114       EVENT_OBJ_PAL_TAG_21
	OBJ_EVENT_PAL_TAG_PLAYER_UNDERWATER       0x1115       EVENT_OBJ_PAL_TAG_11
	OBJ_EVENT_PAL_TAG_KYOGRE                  0x1116       EVENT_OBJ_PAL_TAG_22
	OBJ_EVENT_PAL_TAG_KYOGRE_REFLECTION       0x1117       EVENT_OBJ_PAL_TAG_23
	OBJ_EVENT_PAL_TAG_GROUDON                 0x1118       EVENT_OBJ_PAL_TAG_24
	OBJ_EVENT_PAL_TAG_GROUDON_REFLECTION      0x1119       EVENT_OBJ_PAL_TAG_25
	OBJ_EVENT_PAL_TAG_UNUSED                  0x111A       
	OBJ_EVENT_PAL_TAG_SUBMARINE_SHADOW        0x111B       EVENT_OBJ_PAL_TAG_26
	OBJ_EVENT_PAL_TAG_POOCHYENA               0x111C       EVENT_OBJ_PAL_TAG_27
	OBJ_EVENT_PAL_TAG_RED_LEAF                0x111D       EVENT_OBJ_PAL_TAG_28
	OBJ_EVENT_PAL_TAG_DEOXYS                  0x111E       EVENT_OBJ_PAL_TAG_29
	OBJ_EVENT_PAL_TAG_BIRTH_ISLAND_STONE      0x111F       EVENT_OBJ_PAL_TAG_30
	OBJ_EVENT_PAL_TAG_HO_OH                   0x1120       EVENT_OBJ_PAL_TAG_31
	OBJ_EVENT_PAL_TAG_LUGIA                   0x1121       EVENT_OBJ_PAL_TAG_32
	OBJ_EVENT_PAL_TAG_RS_BRENDAN              0x1122       EVENT_OBJ_PAL_TAG_33
	OBJ_EVENT_PAL_TAG_RS_MAY                  0x1123       EVENT_OBJ_PAL_TAG_34