Feature Merging:
- [X] Update from modern pokeemerald
	- [X] Update from modern porymap
- [X] Pull in music expansion
- [X] Pull in RHH Expansion
	- [X] Grab graphics for Pret + RHH intro from speedchoice-ex
	- [X] Insert this after the gamefreak logo, during intro.
	- [X] Switch pokemon in intro to Gourgeist (possibly randomly selects the size?)
- [X] Convert to Triple Layer metatiles
	- [X] Fix broken metatile in Water Temple, finally
- [ ] Feature branch: Follow Me:  https://github.com/ghoulslash/pokeemerald/tree/follow_me 
- [ ] Feature branch: Sideways Stairs
- [ ] Feature branch: overworld expansion (double check that this is all correct in TTH from this)
- [X] Feature branch: dynamic overworld palettes (double check ditto)
- [ ] Feature branch: Item descriptions on pickup: https://github.com/ghoulslash/pokeemerald/tree/item_desc_header 
- [X] Feature branch: Pokemon decryption and compression: https://github.com/ghoulslash/pokeemerald/tree/box_expansion
- [ ] Tutorial: Improve loading of battle terrain (possibly)
- [ ] Tutorial: Fix snow weather
- [ ] Tutorial: Missing text function RESET_SIZE
- [ ] Tutorial: Improve WaitForVBlank
- [ ] Tutorial: EWRAM summary screen improvements?
- [ ] Tutorial: Custom Border Dimensions (porymap supported)
- [ ] Tutorial: Trigger map scripts by flag
- [ ] Tutorial: Run Custom Script on Trainer Sight?
- [ ] Port soaring? https://github.com/camthesaxman/pokeruby/tree/soar_2
- [ ] https://msikma.github.tio/pokesprite/overview/inventory.html
	- [ ] Check to see if the items from RHH need updated sprites? See if there's any I could use?
	- [ ] The TR icons could be useful, as well as the EXP candy.
	- [ ] Possibly use some curry ingredients for candy?
- [ ] Pull from merrp's stuff: https://github.com/aarant/pokeemerald
	- [ ] Dynamic overworld palettes & reflections compatable with vanilla berry trees (from followers)
	- [ ] (look into "detect newer emulators/hardware)
	- [ ] Day/Night + window lights + lamp lights from the lighting branch



Known issues:
- [X] Pokemon Says: RAM Script is not functioning with applymovement.
	- [X] Test if applymovement for the note emotes is working at all. It's probably not the ramscript aspect.
- [ ] Manectric on the intro screen is yellow instead of blue for some reason.
- [ ] Fall grass overworld effect is broken.
- [X] Puzzle name tag is thinner than it should be, and it's cutting off the puzzle titles.
- [ ] Pokemon Says: When the high note is used, the azuril breaking out of the jar counts as a bad note, but talking to it after it breaks out isn't counted as a bad note.
- [ ] Farfetch'd Forest: When the farfetch'd flies, do hideReflection=true and add a shadow field effect or something; also disable ripples
- [ ] Breeder in the Den doesn't look at you when talking.
- [x] PC in den does not use the dynamic menu system, needs to be updated with such.
- [ ] Trick-Or-Treating: The hopping out of the ground to battle bug is back!
- [ ] Ice Path: GAME BREAKING!! Something happened to the rocks on the ice, and now they don't collide.
- [ ] Twin Memories: GAME BREAKING!! The boulders are not showing up??
- [X] Intimidate uses the The Big Chocolate Slab message. Also, the big chocolate slab maybe should use the ability slide.
- [ ] Mountain Trail: mapping error in a corner of the ledge. Either collision is needed or move to lower layer.

Changes:
- [ ] Add newer-gen mons to the rental sequence.
- [ ] Lost Woods 1: Use Amongous instead of electrode?
- [ ] Towers: Change up pokemon to be more diverse?
- [ ] Towers: Possibly add follower friend to help?
- [ ] Change the emerald text border to orange themed.
	- [ ] Also add an optional text box for person's name using short/narrow text
- [ ] BORT: Go over the sGrammarMoveUsedTable and see if there's an updated version.
- [ ] Wild Pokemon should drop items, if only so a wild battle doesn't just end without the victory music.

Others:
- [ ] Scripting Overhaul
	- [ ] Add command which prints to mgba. 
		- [ ] In poryscript, may need to specifically make ascii strings.
		- [ ] Possibly make one version of command print encoded
- [ ] Reorganize save file, so that version check is first, before trainer name.
- [ ] Add map script for getting map overworld music
- [ ] Add map script for getting battle music
- [ ] Add enhancement where something tells the player if they got the scroll already.
	- I was thinking the costume could change, but that would likely require a map reload of figuring out how to change the graphic without a reload.
	- Could just add it to the pause screen, in a side window
- [ ] ITEM0_DIRE_HIT -> ITEM0_HIGH_CRIT
- [ ] trainers.h -> change encounterMusic_gender to encounterMusic (any music) and split off gender.
- [ ] Change Relic items descriptions to instead say that "collectors may value it highly", as it needs to be specially sold in order to have value.
- [ ] Change some mulch to KEEP to allow use for the growing puzzle element puzzle.
- [ ] Implement GAME_STAT_NUM_CANDY_TRADES
- [X] TryDoEventsBeforeFirstTurn add
	if (!HasMonInParty())
	{
		PrepareStringBattle(STRINGID_PLAYERNOPKMN, GetBattlerAtPosition(position));
		gBattleMainFunc = TryDoEventsBeforeFirstTurn;
		return;
	}
- [X] Fix the following in battle_main.c
	if (ItemId_GetPocket(gLastUsedItem) == POCKET_POKE_BALLS)
		gBattleStruct->throwingPokeBall = TRUE;
- [ ] In battle_util.c
	case ABILITYEFFECT_ON_SWITCHIN: // 0
		// HACK:
		if (ItemId_GetHoldEffect(gBattleMons[battler].item) == HOLD_EFFECT_INTIMIDATE) {
			if (!(gSpecialStatuses[battler].intimidatedMon))
			{
				gStatuses3[battler] |= STATUS3_INTIMIDATE_POKES;
				gSpecialStatuses[battler].intimidatedMon = 1;
			}
		}
	// ....
	case ABILITYEFFECT_INTIMIDATE1:
		if (|| ItemId_GetHoldEffect(gBattleMons[i].item) == HOLD_EFFECT_INTIMIDATE))
			gBattleCommunication[MULTISTRING_CHOOSER] = (ItemId_GetHoldEffect(gBattleMons[i].item) == HOLD_EFFECT_INTIMIDATE);
- [ ] In battle_util.c, implement HOLD_EFFECT_CURE_PAR_HP and others
- [ ] Remove all sText_* from battle_strings_elf.h table and change the lookup function to fallback to the normal table in case of null pointer
- [X] Double check that gIntimidateStringIds is being used to look up for slab stuff.
- [ ] Syncronize the changes to BufferStringBattle with BORT mode
- [x] Check Makefile over
- [X] eventObject->unk3_3 -> disableReflection -> hideReflection
- [X] gRamScriptRetAddr -> gRamScriptPtr
- [X] Layouts.json and map_groups.json - double check
- [x] Check m4a_1.s. We replaced it with a new version and they moved it into src. But also we're gonna merge in the music expansion, which also changes it.
- [X] VAR_ICE_STEP_COUNT -> VAR_STEP_TRIGGER
- [X] Remove apprentice
- [X] constants/items.h - Convert tabs to spaces
- [-] GetCollisionFlagsAtCoords - make flag for mismatch == 2
- [ ] MovementAction_RevealTrainer_Step0 - is it MOVEMENT_TYPE_HIDDEN2 or MOVEMENT_TYPE_BURIED?
- [ ] Rename MOVEMENT_TYPE_HIDDEN2 to something else?
- [ ] Search through MUS_ABANDONED_SHIP and replace them all
- [ ] graphics/shop/candy.png does not say "candy".
- [X] mosstiles:
	.4byte ScrCmd_mosstiles_moveEvents     .4byte ScrCmd_moverotatingtileobjects   @ 0xd3
	.4byte ScrCmd_mosstiles_turnEvents     .4byte ScrCmd_turnrotatingtileobjects   @ 0xd4
	.4byte ScrCmd_mosstiles_initTiles      .4byte ScrCmd_initrotatingtilepuzzle    @ 0xd5
	.4byte ScrCmd_mosstiles_finishTiles    .4byte ScrCmd_freerotatingtilepuzzle    @ 0xd6
- [ ] Look into adding Hidden2 after TRSEE_REVEAL_BURIED_WAIT in trainer_see.c
- [ ] Specials
- [ ] Convert player_forcestep to new naming scheme, also figure out wtf it's doing again
- [ ] Convert the DoorAnimTiles_TrickScroll to a single image, like the other door animations
- [ ] item effects - clean up and remove duplicated / unused item effects
- [x] UpdateAllEventObjectsZCoordAndPriority -> update for Elevation
- [X] Moving graphics:
	- const u32 gIntro2BrendanNoTurnGfx[] = INCBIN_U32("graphics/intro/intro2_brendan_noturn.4bpp.lz");
	+ const u32 gIntroBrendan_Gfx[] = INCBIN_U32("graphics/intro/scene_2/brendan.4bpp.lz");
- [ ] Remove unused event object graphics:
	gObjectEventGraphicsInfo_LinkBrendan
	gObjectEventGraphicsInfo_LinkMay
- [ ] Figure out if sBagSpriteAnimTable and specifically the ex-ball, now candy sprite animation should be moved, 
      and what even is going on with that I don't know...
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
- [ ] Remove duplicate OBJ_EVENT_PAL_TAG_BRIDGE_REFLECTION when figuring out if day/night is done correctly.

- [ ] gStringVar4 -> gStringBuffer
- [ ] re_escape_rope -> ItemUseOnFieldCB_EscapeRope
- [ ] intro.c - Remove unused data sUnusedData
- [ ] graphics.c - Remove random garbage at the end and various spacing
- [X] Double check gTrainer is not referenced
- [x] ShowNatureGirlMessage and others below it: need to comment out arrays?
- [X] Add gStringVar4-6, rearrange placeholders to put names into 0x1X
- [ ] Strip out all the match calls.
- [ ] sElevationToPriority and sElevationToSubspriteTableNum comments to pokeemerald
- [ ] GetLocationMusic -> make map script
- [ ] Decapitalize contest_hall.inc
- [ ] Fix field moves to instead of saying "Used move!", the text box reads a description of what's happening.
- [X] Wipe out all {KUN} again
- [x] Intro credit graphics may need to be added to headers.
- [ ] map_name_popup.c - Modify and use the defines??
- [ ] load_save.c - Remove all the DMA stuff, get rid of the DMA structs
- [ ] Reorganize Flags and Vars
	- [ ] Remove Temporary Aliases from Vars
- [ ] /sound/direct_sound_samples/sc88_piano1_36.bin -> /sound/direct_sound_samples/sc88pro_piano1_36.bin
- [ ] graphics/interface/candy.4bpp.lz -> graphics/shop/candy.4bpp.lz
- [X] move mgba and printf into gflib folder.
- [ ] Metatile behavior:
	MetatileBehavior_IsAquaHideoutWarp  ->  MetatileBehavior_IsTeleportWarp
	MetatileBehavior_IsWarpOrBridge -> MetatileBehavior_IsUnionRoomWarp
- [ ] Add more strings to PuzzleCommon_TextArray_SecretCodes in trick_house.inc

