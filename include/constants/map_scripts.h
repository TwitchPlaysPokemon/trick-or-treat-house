#ifndef GUARD_CONSTANTS_MAP_SCRIPTS_H
#define GUARD_CONSTANTS_MAP_SCRIPTS_H

/*
    IDs for special scripts that can be run for a particular map.
    For the functions that handle when they are run, see these constants' uses in src/script.c

    Below describes when a script of this kind will be called, and what it typically does.
    They are numbered in the order that they will be called when entering a map (from a warp or camera transition).
    NOTE: These descriptions are just of what they generally do, not what they always or have to do

    3. ON_LOAD: Run after the layout is loaded (but not drawn yet).
                Almost exclusively used to set metatiles on the map before it's first drawn

    6. ON_FRAME_TABLE: Run every frame after the map has faded in, before player input is processed.
                       This is a table of scripts; only the first script whose condition is satisfied is run.
                       Used to trigger an event, such as the player exiting the cable car or the SS Tidal sailor announcing progress

    2. ON_TRANSITION: Run during the transition to the map
                      Used to set map-specific flags/vars, update object positions/movement types, set weather, etc
                      The EventObjects have NOT yet been set up, so only expect to change the EventObjectTemplates

    5. ON_WARP_INTO_MAP_TABLE: Run after the map's objects are loaded.
                               This is a table of scripts; only the first script whose condition is satisfied is run.
                               Used to add objects to the scene or update something about the player as they warp in (e.g. their facing dir or visibility)
                               Note that ON_TRANSITION may also handle object visibility, but would do so by modifying a flag or var

    4. ON_RESUME: Run at the end of map load, and again any time upon returning to field (e.g. exiting the Bag menu, or finishing a battle)
                  Used to hide defeated static pokemon, or maintain some map state (e.g. the Trainer Hill timer, or the cycling road challenge)
                  In some maps this takes the metatile setting job of ON_LOAD

    1. ON_DIVE_WARP: Run after the player chooses to dive/emerge.
                     Only used once, to determine whether or not the player should emerge in the Sealed Chamber

    x. ON_RETURN_TO_FIELD: Run exlusively upon returning to the field, shortly after ON_RESUME (as opposed to ON_RESUME, which also runs once on entering the map)
                           Used rarely, when something must only happen on reload (e.g. making sure Mew is above the grass after battling it on Faraway Island)

*/

#define MAP_SCRIPT_ON_LOAD                      0x01
#define MAP_SCRIPT_ON_FRAME_TABLE               0x02
#define MAP_SCRIPT_ON_TRANSITION                0x03
#define MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE       0x04
#define MAP_SCRIPT_ON_RESUME                    0x05
#define MAP_SCRIPT_ON_DIVE_WARP                 0x06
#define MAP_SCRIPT_ON_RETURN_TO_FIELD           0x07
#define MAP_SCRIPT_ON_SPAWN_OBJECT_EVENT        0x08
#define MAP_SCRIPT_ON_PLAY_MAP_MUSIC            0x09
#define MAP_SCRIPT_ON_UNLOAD                    0x0A

#define MAP_SCRIPT_PUZZLE_HEADER_NAME           0x20
#define MAP_SCRIPT_PUZZLE_HEADER_AUTHOR         0x21
#define MAP_SCRIPT_PUZZLE_HEADER_AUTHOR_INTRO   0x22
#define MAP_SCRIPT_PUZZLE_HEADER_FLAGS          0x23
#define MAP_SCRIPT_PUZZLE_HEADER_PREREQ_LIST    0x24
#define MAP_SCRIPT_PUZZLE_HEADER_POST_LIST      0x25
#define MAP_SCRIPT_PUZZLE_HEADER_ADJECTIVE      0x26
#define MAP_SCRIPT_PUZZLE_HEADER_QUIP           0x27
#define MAP_SCRIPT_PUZZLE_META_VARIABLES        0x28
#define MAP_SCRIPT_PUZZLE_CANDY_LIST            0x29
#define MAP_SCRIPT_PUZZLE_CUSTOM_INTRO          0x2A
#define MAP_SCRIPT_PUZZLE_DEV_COMMENTARY        0x2B
#define MAP_SCRIPT_PUZZLE_FRIEND_COMMENTARY     0x2C
#define MAP_SCRIPT_PUZZLE_HEADER_QUIP_SPEAKER   0x2D

#define MAP_SCRIPT_ON_PUZZLE_CUSTOM_INTRO       0x40
#define MAP_SCRIPT_ON_PUZZLE_SETUP              0x41
#define MAP_SCRIPT_ON_PUZZLE_TEARDOWN           0x42
#define MAP_SCRIPT_ON_PUZZLE_EXIT               0x43
#define MAP_SCRIPT_ON_PUZZLE_BLACKOUT           0x44
#define MAP_SCRIPT_ON_PUZZLE_ESCAPE             0x45
#define MAP_SCRIPT_ON_EXIT_PUZZLE_WITH_PARTNER  0x46


#define PUZZLE_FLAGS_AUTHORSHIP   0b00000000000000000000000000000111
#define PUZZLE_FLAG_AUTHORED      0
#define PUZZLE_FLAG_INSPIRED_BY   1
#define PUZZLE_FLAG_BUILT_BY      2
#define PUZZLE_FLAG_GAME_FREAK    3


#endif // GUARD_CONSTANTS_MAP_SCRIPTS_H
