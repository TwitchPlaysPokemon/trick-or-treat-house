@ The Master Puzzle List
@ This should be organized in the order of presentation. There should be
@ a slow rising level of difficulty of the puzzle, but also there should
@ be easy puzzles after particularly hard puzzles for a bit of respite.
.align 2
gPuzzleList::                                           @ Puzzle Type(s)
    .2byte MAP_PUZZLE_TRICK_HOUSE_CUT                   @  ITEM/TUTORIAL    (Must be first)
    .2byte MAP_PUZZLE_MUSIC_NOTE_TILES                  @  LOGIC
    .2byte MAP_PUZZLE_ILEX_FOREST                       @  ITEM/MAZE
    .2byte MAP_PUZZLE_TRICK_HOUSE_ORIGINAL2             @  BATTLE/MAZE (Trapdoors)
    .2byte MAP_PUZZLE_LOST_WOODS1_ENTRANCE              @  MAZE
    
    .2byte MAP_TRICK_TREAT_PETALBURG_CITY               @  TRICK
    
    .2byte MAP_PUZZLE_WILKE                             @  FOLLOW/TUTORIAL
    .2byte MAP_PUZZLE_TRAINER_HILL1                     @  BATTLE/MAZE
    .2byte MAP_PUZZLE_TRICK_HOUSE_ORIGINAL3             @  LOGIC (Toggle Doors)
    .2byte MAP_PUZZLE_ICE_PATH                          @  MAZE
    .2byte MAP_PUZZLE_TWIN_MEMORIES                     @  LOGIC
    .2byte MAP_PUZZLE_LEDGE_MOUNTAIN                    @  WILD/MOVEMENT
    .2byte MAP_PUZZLE_TRICK_HOUSE_ORIGINAL4             @  BATTLE/MOVEMENT (Boulders)
@   .2byte MAP_PUZZLE_LOST_WOODS2_ENTRANCE              @  MAZE
    
@   .2byte MAP_TRICK_TREAT_FORTREE_CITY                 @  TRICK
    
    .2byte MAP_PUZZLE_SOOTOPOLIS_GYM                    @  MOVEMENT
    .2byte MAP_PUZZLE_TIN_TOWER_CLIMB                   @  WILD/MAZE
    .2byte MAP_PUZZLE_TRICK_HOUSE_ORIGINAL5             @  MOVEMENT/MAZE (RSE Slide Tiles)
    .2byte MAP_PUZZLE_TRAINER_HILL2                     @  BATTLE/MAZE
    .2byte MAP_PUZZLE_ROUTE110                          @  ITEM/MAZE
    .2byte MAP_PUZZLE_HIDDEN_MAZE                       @  BATTLE/MAZE
    .2byte MAP_PUZZLE_LOSS_FLOOR1                       @  MEME/LOGIC
    .2byte MAP_PUZZLE_TRICK_HOUSE_SLIP_SLIDING          @  BATTLE/MOVEMENT
    
    .2byte MAP_TRICK_TREAT_MOSSDEEP_CITY                @  TRICK
    
    .2byte MAP_PUZZLE_SPOT_DIFFERENCE_HALLWAY           @  BATTLE/LOGIC
    .2byte MAP_PUZZLE_STEALTH_MISSION                   @  MOVEMENT/MAZE
    .2byte MAP_PUZZLE_TRAINER_HILL3                     @  BATTLE/MAZE
    .2byte MAP_PUZZLE_TRICK_HOUSE_ORIGINAL6             @  MOVEMENT/MAZE (Rot Gates)
    .2byte MAP_PUZZLE_TIC_RAC_TOE                       @  FOLLOW/BATTLE
    .2byte MAP_PUZZLE_ELITE_FLOOR                       @  MOVEMENT/MAZE
    .2byte MAP_PUZZLE_TRICK_HOUSE_ORIGINAL7             @  BATTLE/MAZE (Double Battles)
@   .2byte MAP_PUZZLE_LOST_WOODS3_ENTRANCE              @  MAZE

@   .2byte MAP_TRICK_TREAT_ALTO_MARE1                   @  TRICK

    .2byte MAP_PUZZLE_WATER_TEMPLE                      @  LOGIC/MAZE
    .2byte MAP_PUZZLE_TRAINER_HILL4                     @  BATTLE/MAZE
    .2byte MAP_PUZZLE_TRICK_HOUSE_ORIGINAL8             @  BATTLE/MOVEMENT (Ice Floor)
    .2byte MAP_PUZZLE_LOST_WOODS4_ENTRANCE              @  MAZE
    
    .2byte MAP_PUZZLE_SAFARI_IMPOSTERS                  @  LOGIC
@   .2byte MAP_META_PUZZLE
@   .2byte MAP_CREDITS                                  @  MINIGAME
@   .2byte MAP_TRICK_TREAT_SLATEPORT_CITY1              @  TRICK    (Must be last)
    .2byte 0xFFFF

@ Below puzzles don't appear in the main puzzle list, and must be accessed
@ from the dev room.
.align 2
gDebugPuzzles::
    .2byte MAP_EMPTY_PUZZLE
    .2byte MAP_PUZZLE_SUSPENDED_MAZE
    .2byte MAP_TRICK_TREAT_ALTO_MARE1                   @  TRICK
    .2byte MAP_TRICK_TREAT_FORTREE_CITY                 @  TRICK
    .2byte MAP_TRICK_TREAT_SLATEPORT_CITY1              @  TRICK    (Must be last)
    .2byte MAP_PUZZLE_FALLING_WATER                     @  ITEM/MOVEMENT
    .2byte MAP_PUZZLE_TRICK_HOUSE_ORIGINAL1             @  BATTLE/MAZE
    .2byte MAP_PUZZLE_TRICK_HOUSE_TRAPDOORS             @  BATTLE/MAZE
    .2byte MAP_PUZZLE_DESERT_OASIS
    .2byte 0xFFFF
