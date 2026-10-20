@ The Master Puzzle List
@ This should be organized in the order of presentation. There should be
@ a slow rising level of difficulty of the puzzle, but also there should
@ be easy puzzles after particularly hard puzzles for a bit of respite.

.macro declare_puzzle puz:req, e
.ifb \e
    inc __enum__
.else
    enum \e
.endif
.2byte \puz
.endm

enum_start
.align 2
gPuzzleList::                                           @ Puzzle Type(s)
    declare_puzzle MAP_PUZZLE_TRICK_HOUSE_CUT           @  ITEM/TUTORIAL    (Must be first)
    declare_puzzle MAP_PUZZLE_MUSIC_NOTE_TILES          @  LOGIC
    declare_puzzle MAP_PUZZLE_ILEX_FOREST               @  ITEM/MAZE
    declare_puzzle MAP_PUZZLE_TRICK_HOUSE_ORIGINAL2     @  BATTLE/MAZE (Trapdoors)
    declare_puzzle MAP_PUZZLE_LOST_WOODS1_ENTRANCE      @  MAZE
    declare_puzzle MAP_PUZZLE_WILKE                     @  FOLLOW/TUTORIAL
    declare_puzzle MAP_PUZZLE_TRAINER_HILL1             @  BATTLE/MAZE
    
    declare_puzzle MAP_TRICK_TREAT_PETALBURG_CITY, ID_TRICK_TREAT_PETALBURG       @  TRICK
    
    declare_puzzle MAP_PUZZLE_TRICK_HOUSE_ORIGINAL3     @  LOGIC (Toggle Doors)
    declare_puzzle MAP_PUZZLE_ICE_PATH                  @  MAZE
    declare_puzzle MAP_PUZZLE_TWIN_MEMORIES             @  LOGIC
    declare_puzzle MAP_PUZZLE_LEDGE_MOUNTAIN, ID_PUZZLE_LEDGE_MOUNTAIN @  WILD/MOVEMENT
    declare_puzzle MAP_PUZZLE_TRAINER_HILL2             @  BATTLE/MAZE
    declare_puzzle MAP_PUZZLE_TRICK_HOUSE_ORIGINAL4     @  BATTLE/MOVEMENT (Boulders)
    declare_puzzle MAP_PUZZLE_TIN_TOWER_CLIMB           @  WILD/MAZE
    declare_puzzle MAP_PUZZLE_ROUTE110                  @  ITEM/MAZE
    declare_puzzle MAP_PUZZLE_FALLING_WATER             @  ITEM/MOVEMENT
    declare_puzzle MAP_PUZZLE_SOOTOPOLIS_GYM            @  MOVEMENT
    
    declare_puzzle MAP_TRICK_TREAT_FORTREE_CITY, ID_TRICK_TREAT_FORTREE         @  TRICK
    
    declare_puzzle MAP_PUZZLE_TRICK_HOUSE_ORIGINAL5     @  MOVEMENT/MAZE (RSE Slide Tiles)
    declare_puzzle MAP_PUZZLE_HIDDEN_MAZE               @  BATTLE/MAZE
    declare_puzzle MAP_PUZZLE_LOSS_FLOOR1, ID_PUZZLE_LOSS_FLOOR1  @  MEME/LOGIC
    declare_puzzle MAP_PUZZLE_TRICK_HOUSE_SLIP_SLIDING  @  BATTLE/MOVEMENT
    declare_puzzle MAP_PUZZLE_SUSPENDED_MAZE            @  MAZE
    declare_puzzle MAP_PUZZLE_SPOT_DIFFERENCE_HALLWAY   @  BATTLE/LOGIC
    declare_puzzle MAP_PUZZLE_STEALTH_MISSION           @  MOVEMENT/MAZE
    declare_puzzle MAP_PUZZLE_TRAINER_HILL3             @  BATTLE/MAZE
    declare_puzzle MAP_PUZZLE_TRICK_HOUSE_ORIGINAL6     @  MOVEMENT/MAZE (Rot Gates)
    
    declare_puzzle MAP_TRICK_TREAT_MOSSDEEP_CITY, ID_TRICK_TREAT_MOSSDEEP       @  TRICK
    
    declare_puzzle MAP_PUZZLE_TIC_RAC_TOE               @  FOLLOW/BATTLE
    declare_puzzle MAP_PUZZLE_ELITE_FLOOR               @  MOVEMENT/MAZE
    declare_puzzle MAP_PUZZLE_TRICK_HOUSE_ORIGINAL7     @  BATTLE/MAZE (Double Battles)
    declare_puzzle MAP_PUZZLE_WATER_TEMPLE              @  LOGIC/MAZE
    declare_puzzle MAP_PUZZLE_BLOCK_PUSHING             @  MOVEMENT
    declare_puzzle MAP_PUZZLE_TRAINER_HILL4             @  BATTLE/MAZE
    declare_puzzle MAP_PUZZLE_TRICK_HOUSE_ORIGINAL8     @  BATTLE/MOVEMENT (Ice Floor)
    declare_puzzle MAP_PUZZLE_LOST_WOODS4_ENTRANCE      @  MAZE
    @ 37
    declare_puzzle MAP_PUZZLE_SAFARI_IMPOSTERS, ID_PUZZLE_SAFARI          @  LOGIC
    declare_puzzle MAP_PUZZLE_META_PUZZLE, ID_PUZZLE_META
    declare_puzzle MAP_PUZZLE_CREDITS                   @  MINIGAME (Must be last)
@   .2byte MAP_TRICK_TREAT_SLATEPORT_CITY1  @ (Not actually a puzzle)
    .2byte 0xFFFF

enum NUM_PUZZLES

@ Below puzzles don't appear in the main puzzle list, and must be accessed
@ from the dev room.
.align 2
gDebugPuzzles::
    .2byte MAP_EMPTY_PUZZLE
    .2byte MAP_TRICK_TREAT_ALTO_MARE1                   @  TRICK (after Mossdeep)
    .2byte MAP_PUZZLE_TRICK_HOUSE_ORIGINAL1             @  BATTLE/MAZE
    .2byte MAP_PUZZLE_TRICK_HOUSE_TRAPDOORS             @  BATTLE/MAZE
    .2byte MAP_PUZZLE_DESERT_OASIS
@   .2byte MAP_PUZZLE_LOST_WOODS2_ENTRANCE              @  MAZE
@   .2byte MAP_PUZZLE_LOST_WOODS3_ENTRANCE              @  MAZE
    .2byte MAP_PUZZLE_SKY_PILLAR_1F                     @  WILD/MOVEMENT
    .2byte MAP_PUZZLE_MIRAGE_TOWER_1F                   @  WILD/MOVEMENT
    .2byte MAP_PUZZLE_KECLEON_CHASE                     @  FOLLOW
    .2byte 0xFFFF
