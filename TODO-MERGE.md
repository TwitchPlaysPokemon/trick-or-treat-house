- [x] Check Makefile over
- [X] eventObject->unk3_3 -> disableReflection -> hideReflection
- [X] gRamScriptRetAddr -> gRamScriptPtr
- [ ] Layouts.json and map_groups.json - double check
- [ ] Check m4a_1.s. We replaced it with a new version and they moved it into src. But also we're gonna merge in the music expansion, which also changes it.
- [X] VAR_ICE_STEP_COUNT -> VAR_STEP_TRIGGER
- [X] Remove apprentice
- [ ] constants/items.h - Convert tabs to spaces
- [ ] GetCollisionFlagsAtCoords - make flag for mismatch == 2
- [ ] MovementAction_RevealTrainer_Step0 - is it MOVEMENT_TYPE_HIDDEN2 or MOVEMENT_TYPE_BURIED?
- [ ] Rename MOVEMENT_TYPE_HIDDEN2 to something else?
- [ ] mosstiles:
	.4byte ScrCmd_mosstiles_moveEvents     .4byte ScrCmd_moverotatingtileobjects   @ 0xd3
	.4byte ScrCmd_mosstiles_turnEvents     .4byte ScrCmd_turnrotatingtileobjects   @ 0xd4
	.4byte ScrCmd_mosstiles_initTiles      .4byte ScrCmd_initrotatingtilepuzzle    @ 0xd5
	.4byte ScrCmd_mosstiles_finishTiles    .4byte ScrCmd_freerotatingtilepuzzle    @ 0xd6
- [ ] Redo the scripting
- [ ] Look into adding Hidden2 after TRSEE_REVEAL_BURIED_WAIT in trainer_see.c
- [ ] Specials
- [ ] Convert player_forcestep to new naming scheme, also figure out wtf it's doing again
- [ ] Convert the DoorAnimTiles_TrickScroll to a single image, like the other door animations
- [ ] item effects - clean up and remove duplicated / unused item effects
- [ ] UpdateAllEventObjectsZCoordAndPriority -> update for Elevation
- [ ] Moving graphics:
	- const u32 gIntro2BrendanNoTurnGfx[] = INCBIN_U32("graphics/intro/intro2_brendan_noturn.4bpp.lz");
	+ const u32 gIntroBrendan_Gfx[] = INCBIN_U32("graphics/intro/scene_2/brendan.4bpp.lz");
- [ ] Remove unused event object graphics:
	gObjectEventGraphicsInfo_LinkBrendan
	gObjectEventGraphicsInfo_LinkMay
- [ ] Palette Tags:
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
- [ ] Double check gTrainer is not referenced
- [ ] ShowNatureGirlMessage and others below it: need to comment out arrays?
- [ ] Add gStringVar4-6, rearrange placeholders to put names into 0x1X
- [ ] Strip out all the match calls.
- [ ] sElevationToPriority and sElevationToSubspriteTableNum comments to pokeemerald
- [ ] GetLocationMusic -> make map script
- [ ] Decapitalize contest_hall.inc
- [ ] Fix field moves to instead of saying "Used move!", the text box reads a description of what's happening.
- [ ] Wipe out all {KUN} again
- [ ] Intro credit graphics may need to be added to headers.
- [ ] map_name_popup.c - Modify and use the defines??
- [ ] load_save.c - Remove all the DMA stuff, get rid of the DMA structs
- [ ] Reorganize Flags and Vars
	- [ ] Remove Temporary Aliases from Vars
- [ ] /sound/direct_sound_samples/sc88_piano1_36.bin -> /sound/direct_sound_samples/sc88pro_piano1_36.bin
- [ ] graphics/interface/candy.4bpp.lz -> graphics/shop/candy.4bpp.lz
- [ ] move mgba and printf into gflib folder.
- [ ] Metatile behavior:
	MetatileBehavior_IsAquaHideoutWarp  ->  MetatileBehavior_IsTeleportWarp
	MetatileBehavior_IsWarpOrBridge -> MetatileBehavior_IsUnionRoomWarp

- [ ] Recreate script_menu.c:
	extern const u8 PokemonAdoption_Choose[];
	extern const u8 PokemonAdoption_Status[];
	extern const u8 PokemonAdoption_Exit[];
	const struct MenuAction MultichoiceList_MonAdoption[] =
	{
		{PokemonAdoption_Choose, NULL},
		{PokemonAdoption_Status, NULL},
		{PokemonAdoption_Exit, NULL},
	};

	extern const u8 Puzzle_SafariImposters_Menu_Report[];
	extern const u8 Puzzle_SafariImposters_Menu_Battle[];
	extern const u8 Puzzle_SafariImposters_Menu_Cancel[];
	const struct MenuAction MultichoiceList_SafariImposter[] =
	{
		{Puzzle_SafariImposters_Menu_Report, NULL},
		{Puzzle_SafariImposters_Menu_Battle, NULL},
		{Puzzle_SafariImposters_Menu_Cancel, NULL},
	};

	// defined in TrickHouseDevEntrance/scripts.pory
	extern const u8 PuzzleDebug_TustinsMenu_PuzzlesCompleted[];
	extern const u8 PuzzleDebug_TustinsMenu_SunOffset[];
	const struct MenuAction MultichoiceList_TustinsMenu[] =
	{
		{PuzzleDebug_TustinsMenu_PuzzlesCompleted, NULL},
		{PuzzleDebug_TustinsMenu_SunOffset, NULL},
	};

