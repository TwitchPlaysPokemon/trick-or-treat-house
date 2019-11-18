#ifndef GUARD_CONSTANTS_GLOBAL_H
#define GUARD_CONSTANTS_GLOBAL_H
// Invalid Versions show as "----------" in Gen 4 and Gen 5's summary screen.
// In Gens 6 and 7, invalid versions instead show "a distant land" in the summary screen.
// In Gen 4 only, migrated Pokemon with Diamond, Pearl, or Platinum's ID show as "----------".
// Gen 5 and up read Diamond, Pearl, or Platinum's ID as "Sinnoh".
// In Gen 4 and up, migrated Pokemon with HeartGold or SoulSilver's ID show the otherwise unused "Johto" string.
#define VERSION_SAPPHIRE     1
#define VERSION_RUBY         2
#define VERSION_EMERALD      3
#define VERSION_FIRE_RED     4
#define VERSION_LEAF_GREEN   5
#define VERSION_HEART_GOLD   7
#define VERSION_SOUL_SILVER  8
#define VERSION_DIAMOND     10
#define VERSION_PEARL       11
#define VERSION_PLATINUM    12
#define VERSION_GAMECUBE    15

// TTH Version Detection
#define VERSION_TTH_2019     0  // The game version detection was not in the 2019 release
#define VERSION_TTH_2020    20

#define LANGUAGE_JAPANESE    1
#define LANGUAGE_ENGLISH     2
#define LANGUAGE_FRENCH      3
#define LANGUAGE_ITALIAN     4
#define LANGUAGE_GERMAN      5
#define LANGUAGE_KOREAN      6 // 6 goes unused but the theory is it was meant to be Korean
#define LANGUAGE_SPANISH     7

#define GAME_VERSION (VERSION_TTH_2020) //(VERSION_EMERALD)
#define GAME_LANGUAGE (LANGUAGE_ENGLISH)

// capacities of various saveblock objects
#define DAYCARE_MON_COUNT 2
#define POKEBLOCKS_COUNT 40
#define EVENT_OBJECTS_COUNT 16
#define BERRY_TREES_COUNT 128
#define FLAGS_COUNT 300
#define VARS_COUNT 256
#define MAIL_COUNT 16
#define SECRET_BASES_COUNT 20
#define TV_SHOWS_COUNT 25
#define POKE_NEWS_COUNT 16
#define PC_ITEMS_COUNT 1
#define BAG_ITEMS_COUNT 79
#define BAG_KEYITEMS_COUNT 30
#define BAG_POKEBALLS_COUNT 16
#define BAG_TMHM_COUNT 64
#define BAG_BERRIES_COUNT 46
#define EVENT_OBJECT_TEMPLATES_COUNT 64

#define PYRAMID_BAG_ITEMS_COUNT 10
#define HALL_FACILITIES_COUNT 9 // 7 facilities for single mode + tower double mode + tower multi mode.

// string lengths
#define ITEM_NAME_LENGTH 14
#define POKEMON_NAME_LENGTH 10
#define PLAYER_NAME_LENGTH 7
#define MAIL_WORDS_COUNT 9
#define MOVE_NAME_LENGTH 12

#define MALE 0
#define FEMALE 1

#define OPTIONS_BUTTON_MODE_NORMAL 0
#define OPTIONS_BUTTON_MODE_LR 1
#define OPTIONS_BUTTON_MODE_L_EQUALS_A 2

#define OPTIONS_TEXT_SPEED_SLOW 0
#define OPTIONS_TEXT_SPEED_MID 1
#define OPTIONS_TEXT_SPEED_FAST 2

#define OPTIONS_SOUND_MONO 0
#define OPTIONS_SOUND_STEREO 1

#define OPTIONS_BATTLE_STYLE_SHIFT 0
#define OPTIONS_BATTLE_STYLE_SET 1

#define DIR_NONE       0
#define DIR_SOUTH      1
#define DIR_NORTH      2
#define DIR_WEST       3
#define DIR_EAST       4
#define DIR_SOUTHWEST  5
#define DIR_SOUTHEAST  6
#define DIR_NORTHWEST  7
#define DIR_NORTHEAST  8

#endif // GUARD_CONSTANTS_GLOBAL_H
