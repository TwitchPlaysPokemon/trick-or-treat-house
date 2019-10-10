@ The Master Puzzle List
@ This should be organized in the order of presentation. There should be
@ a slow rising level of difficulty of the puzzle, but also there should
@ be easy puzzles after particularly hard puzzles for a bit of respite.
.align 2                                                @ Estimated Challenge Ratings out of 10
gPuzzleList::                                           @ TPP / Single Player
    .2byte MAP_PUZZLE_TRICK_HOUSE_CUT                   @  2 / 2
    .2byte MAP_PUZZLE_TRICK_HOUSE_TRAPDOORS             @  2 / 2
    .2byte MAP_PUZZLE_MUSIC_NOTE_TILES                  @  6 / 3
    .2byte MAP_PUZZLE_ROUTE110                          @  1 / 1
    .2byte MAP_PUZZLE_LOST_WOODS1_ENTRANCE              @  3 / 2
    .2byte MAP_PUZZLE_TWIN_MEMORIES                     @  7 / 4
    .2byte MAP_PUZZLE_WATER_TEMPLE                      @  5 / 4
    .2byte MAP_PUZZLE_LOSS_FLOOR1                       @  1 / 1
    .2byte MAP_PUZZLE_TIN_TOWER_CLIMB                   @  6 / 4
    .2byte MAP_PUZZLE_HIDDEN_MAZE                       @  5 / 7
    .2byte MAP_PUZZLE_LEDGE_MOUNTAIN                    @  8 / 4
    .2byte MAP_PUZZLE_WILKE                             @ 10 / 8
    .2byte 0xFFFF

@ Below puzzles don't appear in the main puzzle list, and must be accessed
@ from the dev room.
.align 2
gDebugPuzzles::
    .2byte MAP_EMPTY_PUZZLE
    .2byte MAP_TRICK_TREAT_PETALBURG_CITY
    .2byte MAP_TRICK_TREAT_MOSSDEEP_CITY
    .2byte MAP_PUZZLE_TRICK_HOUSE_ORIGINAL1             @  3 / 1
    .2byte MAP_PUZZLE_TRICK_HOUSE_ORIGINAL2             @  3 / 3
    .2byte MAP_PUZZLE_TRICK_HOUSE_ORIGINAL3             @  3 / 3
    .2byte MAP_PUZZLE_TRICK_HOUSE_ORIGINAL4             @  3 / 3
    .2byte MAP_PUZZLE_TRICK_HOUSE_ORIGINAL6             @  3 / 3
    .2byte MAP_PUZZLE_TRICK_HOUSE_ORIGINAL7             @  3 / 3
    .2byte MAP_PUZZLE_TRICK_HOUSE_ORIGINAL8             @  3 / 3
    .2byte MAP_PUZZLE_DESERT_OASIS
    .2byte 0xFFFF