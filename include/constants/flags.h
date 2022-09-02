#ifndef GUARD_CONSTANTS_FLAGS_H
#define GUARD_CONSTANTS_FLAGS_H

#include "constants/opponents.h"

// Temporary Flags
// These temporary flags are are cleared every time a map is loaded. They are used
// for things like shortening an NPCs introduction text if the player already spoke
// to them once.
#define TEMP_FLAGS_START 0x0
#define FLAG_TEMP_1                          0x001
#define FLAG_TEMP_2                          0x002
#define FLAG_TEMP_3                          0x003
#define FLAG_TEMP_4                          0x004
#define FLAG_TEMP_5                          0x005
#define FLAG_TEMP_6                          0x006
#define FLAG_TEMP_7                          0x007
#define FLAG_TEMP_8                          0x008
#define FLAG_TEMP_9                          0x009
#define FLAG_TEMP_A                          0x00A
#define FLAG_TEMP_B                          0x00B
#define FLAG_TEMP_C                          0x00C
#define FLAG_TEMP_D                          0x00D
#define FLAG_TEMP_E                          0x00E
#define FLAG_TEMP_F                          0x00F
#define FLAG_TEMP_10                         0x010
#define FLAG_TEMP_11                         0x011
#define FLAG_TEMP_12                         0x012
#define FLAG_TEMP_13                         0x013
#define FLAG_TEMP_14                         0x014
#define FLAG_TEMP_15                         0x015
#define FLAG_TEMP_16                         0x016
#define FLAG_TEMP_17                         0x017
#define FLAG_TEMP_18                         0x018
#define FLAG_TEMP_19                         0x019
#define FLAG_TEMP_1A                         0x01A
#define FLAG_TEMP_1B                         0x01B
#define FLAG_TEMP_1C                         0x01C
#define FLAG_TEMP_1D                         0x01D
#define FLAG_TEMP_1E                         0x01E
#define FLAG_TEMP_1F                         0x01F
#define TEMP_FLAGS_END                FLAG_TEMP_1F

// Puzzle Flags
// These flags are cleared every time we increment to a new puzzle.
#define FLAG_PUZZLE_20                       0x020
#define FLAG_PUZZLE_21                       0x021
#define FLAG_PUZZLE_22                       0x022
#define FLAG_PUZZLE_23                       0x023
#define FLAG_PUZZLE_24                       0x024
#define FLAG_PUZZLE_25                       0x025
#define FLAG_PUZZLE_26                       0x026
#define FLAG_PUZZLE_27                       0x027
#define FLAG_PUZZLE_28                       0x028
#define FLAG_PUZZLE_29                       0x029
#define FLAG_PUZZLE_2A                       0x02A
#define FLAG_PUZZLE_2B                       0x02B
#define FLAG_PUZZLE_2C                       0x02C
#define FLAG_PUZZLE_2D                       0x02D
#define FLAG_PUZZLE_2E                       0x02E
#define FLAG_PUZZLE_2F                       0x02F
#define FLAG_PUZZLE_30                       0x030
#define FLAG_PUZZLE_31                       0x031
#define FLAG_PUZZLE_32                       0x032
#define FLAG_PUZZLE_33                       0x033
#define FLAG_PUZZLE_34                       0x034
#define FLAG_PUZZLE_35                       0x035
#define FLAG_PUZZLE_36                       0x036
#define FLAG_PUZZLE_37                       0x037
#define FLAG_PUZZLE_38                       0x038
#define FLAG_PUZZLE_39                       0x039
#define FLAG_PUZZLE_3A                       0x03A
#define FLAG_PUZZLE_3B                       0x03B
#define FLAG_PUZZLE_3C                       0x03C
#define FLAG_PUZZLE_3D                       0x03D
#define FLAG_PUZZLE_3E                       0x03E
#define FLAG_PUZZLE_3F                       0x03F
#define FLAG_PUZZLE_40                       0x040
#define FLAG_PUZZLE_41                       0x041
#define FLAG_PUZZLE_42                       0x042
#define FLAG_PUZZLE_43                       0x043
#define FLAG_PUZZLE_44                       0x044
#define FLAG_PUZZLE_45                       0x045
#define FLAG_PUZZLE_46                       0x046
#define FLAG_PUZZLE_47                       0x047
#define FLAG_PUZZLE_48                       0x048
#define FLAG_PUZZLE_49                       0x049
#define FLAG_PUZZLE_4A                       0x04A
#define FLAG_PUZZLE_4B                       0x04B
#define FLAG_PUZZLE_4C                       0x04C
#define FLAG_PUZZLE_4D                       0x04D
#define FLAG_PUZZLE_4E                       0x04E
#define FLAG_PUZZLE_4F                       0x04F

// Puzzle Items
#define FLAG_PUZZLE_ITEM_0                   0x050
#define FLAG_PUZZLE_ITEM_1                   0x051
#define FLAG_PUZZLE_ITEM_2                   0x052
#define FLAG_PUZZLE_ITEM_3                   0x053
#define FLAG_PUZZLE_ITEM_4                   0x054
#define FLAG_PUZZLE_ITEM_5                   0x055
#define FLAG_PUZZLE_ITEM_6                   0x056
#define FLAG_PUZZLE_ITEM_7                   0x057
#define FLAG_PUZZLE_ITEM_8                   0x058
#define FLAG_PUZZLE_ITEM_9                   0x059
#define FLAG_PUZZLE_ITEM_A                   0x05A
#define FLAG_PUZZLE_ITEM_B                   0x05B
#define FLAG_PUZZLE_ITEM_C                   0x05C
#define FLAG_PUZZLE_ITEM_D                   0x05D
#define FLAG_PUZZLE_ITEM_E                   0x05E
#define FLAG_PUZZLE_ITEM_F                   0x05F

// Scripts
#define FLAG_TRICK_HOUSE_SCROLL_READ         0x060
#define FLAG_TRICK_HOUSE_PASSWORD_ENTERED    0x061
#define FLAG_PICKED_UP_CUT_ITEM              0x062
#define FLAG_PICKED_UP_SMASH_ITEM            0x063
#define FLAG_PICKED_UP_STRENGTH_ITEM         0x064
#define FLAG_PICKED_UP_WATERFALL_ITEM        0x065
#define FLAG_PICKED_UP_DIVE_ITEM             0x066
#define FLAG_PICKED_UP_SURF_ITEM             0x067
#define FLAG_PICKED_UP_FLASH_ITEM            0x068
#define FLAG_PICKED_UP_FLY_ITEM              0x069 // never used
#define FLAG_PUZZLE_PARTY_LOCK               0x06A
#define FLAG_PUZZLE_HAS_STARTED              0x06B
#define FLAG_PUZZLE_HAS_COMPLETED            0x06C
#define FLAG_UNUSED_0x06D                    0x06D
#define FLAG_HIDE_ENDROOM_FRIEND             0x06E
#define FLAG_HIDE_DEVELOPER_COMMENTATOR      0x06F


#define FLAG_DECORATION_0                    0x070
#define FLAG_DECORATION_1                    0x071
#define FLAG_DECORATION_2                    0x072
#define FLAG_DECORATION_3                    0x073
#define FLAG_DECORATION_4                    0x074
#define FLAG_DECORATION_5                    0x075
#define FLAG_DECORATION_6                    0x076
#define FLAG_DECORATION_7                    0x077
#define FLAG_DECORATION_8                    0x078
#define FLAG_DECORATION_9                    0x079
#define FLAG_DECORATION_10                   0x07A
#define FLAG_DECORATION_11                   0x07B
#define FLAG_DECORATION_12                   0x07C
#define FLAG_DECORATION_13                   0x07D
#define FLAG_DECORATION_14                   0x07E
#define FLAG_UNUSED_0x07F                    0x07F
#define FLAG_META_PICKUP_ROCK                0x080
#define FLAG_META_PICKUP_ZIGZAG              0x081
#define FLAG_META_PICKUP_LOTAD               0x082
#define FLAG_META_PICKUP_GRASS               0x083
#define FLAG_META_PICKUP_DIAMOND             0x084
#define FLAG_META_PICKUP_SPIN                0x085
#define FLAG_META_PICKUP_DOLL                0x086
#define FLAG_META_PICKUP_BALL                0x087
#define FLAG_META_PICKUP_KISS                0x088
#define FLAG_META_PICKUP_ROUND               0x089
#define FLAG_META_PICKUP_FIRE                0x08A
#define FLAG_META_PICKUP_PIKA                0x08B
#define FLAG_META_PICKUP_DUSKULL             0x08C
#define FLAG_META_PICKUP_WATER               0x08D
#define FLAG_META_PICKUP_SEEDOT              0x08E
#define FLAG_META_PICKUP_CUSHION             0x08F
#define FLAG_META_SUBMITTED_ROCK             0x090
#define FLAG_META_SUBMITTED_ZIGZAG           0x091
#define FLAG_META_SUBMITTED_LOTAD            0x092
#define FLAG_META_SUBMITTED_GRASS            0x093
#define FLAG_META_SUBMITTED_DIAMOND          0x094
#define FLAG_META_SUBMITTED_SPIN             0x095
#define FLAG_META_SUBMITTED_DOLL             0x096
#define FLAG_META_SUBMITTED_BALL             0x097
#define FLAG_META_SUBMITTED_KISS             0x098
#define FLAG_META_SUBMITTED_ROUND            0x099
#define FLAG_META_SUBMITTED_FIRE             0x09A
#define FLAG_META_SUBMITTED_PIKA             0x09B
#define FLAG_META_SUBMITTED_DUSKULL          0x09C
#define FLAG_META_SUBMITTED_WATER            0x09D
#define FLAG_META_SUBMITTED_SEEDOT           0x09E
#define FLAG_META_SUBMITTED_CUSHION          0x09F
#define FLAG_HIDE_EXT_GAME_PLAYERS           0x0A0
#define FLAG_UNUSED_0x0A1                    0x0A1
#define FLAG_UNUSED_0x0A2                    0x0A2
#define FLAG_UNUSED_0x0A3                    0x0A3
#define FLAG_UNUSED_0x0A4                    0x0A4
#define FLAG_UNUSED_0x0A5                    0x0A5
#define FLAG_UNUSED_0x0A6                    0x0A6
#define FLAG_UNUSED_0x0A7                    0x0A7
#define FLAG_UNUSED_0x0A8                    0x0A8
#define FLAG_UNUSED_0x0A9                    0x0A9
#define FLAG_UNUSED_0x0AA                    0x0AA
#define FLAG_UNUSED_0x0AB                    0x0AB
#define FLAG_UNUSED_0x0AC                    0x0AC
#define FLAG_UNUSED_0x0AD                    0x0AD
#define FLAG_UNUSED_0x0AE                    0x0AE
#define FLAG_UNUSED_0x0AF                    0x0AF
#define FLAG_UNUSED_0x0B0                    0x0B0
#define FLAG_UNUSED_0x0B1                    0x0B1
#define FLAG_UNUSED_0x0B2                    0x0B2
#define FLAG_UNUSED_0x0B3                    0x0B3
#define FLAG_UNUSED_0x0B4                    0x0B4
#define FLAG_UNUSED_0x0B5                    0x0B5
#define FLAG_UNUSED_0x0B6                    0x0B6
#define FLAG_UNUSED_0x0B7                    0x0B7
#define FLAG_UNUSED_0x0B8                    0x0B8
#define FLAG_UNUSED_0x0B9                    0x0B9
#define FLAG_UNUSED_0x0BA                    0x0BA
#define FLAG_UNUSED_0x0BB                    0x0BB
#define FLAG_UNUSED_0x0BC                    0x0BC
#define FLAG_UNUSED_0x0BD                    0x0BD
#define FLAG_UNUSED_0x0BE                    0x0BE
#define FLAG_UNUSED_0x0BF                    0x0BF
#define FLAG_UNUSED_0x0C0                    0x0C0
#define FLAG_UNUSED_0x0C1                    0x0C1
#define FLAG_UNUSED_0x0C2                    0x0C2
#define FLAG_UNUSED_0x0C3                    0x0C3
#define FLAG_UNUSED_0x0C4                    0x0C4
#define FLAG_UNUSED_0x0C5                    0x0C5
#define FLAG_UNUSED_0x0C6                    0x0C6
#define FLAG_UNUSED_0x0C7	                 0x0C7
#define FLAG_UNUSED_0x0C8	                 0x0C8
#define FLAG_UNUSED_0x0C9	                 0x0C9
#define FLAG_UNUSED_0x0CA	                 0x0CA
#define FLAG_UNUSED_0x0CB	                 0x0CB
#define FLAG_UNUSED_0x0CC	                 0x0CC
#define FLAG_UNUSED_0x0CD	                 0x0CD
#define FLAG_UNUSED_0x0CE	                 0x0CE
#define FLAG_UNUSED_0x0CF	                 0x0CF
#define FLAG_UNUSED_0x0D0	                 0x0D0
#define FLAG_UNUSED_0x0D1	                 0x0D1
#define FLAG_UNUSED_0x0D2	                 0x0D2 
#define FLAG_UNUSED_0x0D3	                 0x0D3
#define FLAG_UNUSED_0x0D4	                 0x0D4
#define FLAG_UNUSED_0x0D5	                 0x0D5
#define FLAG_ENABLE_WALLY_MATCH_CALL         0x0D6 // Move
#define FLAG_ENABLE_SCOTT_MATCH_CALL         0x0D7 // Move
#define FLAG_ENABLE_MOM_MATCH_CALL           0x0D8 // Move
#define FLAG_UNUSED_0x0D9                    0x0D9
#define FLAG_UNUSED_0x0DA                    0x0DA
#define FLAG_UNUSED_0x0DB                    0x0DB
#define FLAG_UNUSED_0x0DC                    0x0DC
#define FLAG_UNUSED_0x0DD                    0x0DD
#define FLAG_UNUSED_0x0DE                    0x0DE
#define FLAG_UNUSED_0x0DF                    0x0DF
#define FLAG_UNUSED_0x0E0                    0x0E0
#define FLAG_UNUSED_0x0E1                    0x0E1
#define FLAG_UNUSED_0x0E2                    0x0E2
#define FLAG_UNUSED_0x0E3                    0x0E3
#define FLAG_UNUSED_0x0E4                    0x0E4
#define FLAG_UNUSED_0x0E5                    0x0E5
#define FLAG_UNUSED_0x0E6                    0x0E6
#define FLAG_UNUSED_0x0E7                    0x0E7
#define FLAG_UNUSED_0x0E8                    0x0E8
#define FLAG_UNUSED_0x0E9                    0x0E9
#define FLAG_UNUSED_0x0EA                    0x0EA
#define FLAG_UNUSED_0x0EB                    0x0EB
#define FLAG_UNUSED_0x0EC                    0x0EC
#define FLAG_UNUSED_0x0ED                    0x0ED
#define FLAG_UNUSED_0x0EE                    0x0EE
#define FLAG_UNUSED_0x0EF                    0x0EF
#define FLAG_UNUSED_0x0F0                    0x0F0
#define FLAG_UNUSED_0x0F1                    0x0F1
#define FLAG_UNUSED_0x0F2                    0x0F2
#define FLAG_UNUSED_0x0F3                    0x0F3
#define FLAG_UNUSED_0x0F4                    0x0F4
#define FLAG_UNUSED_0x0F5                    0x0F5
#define FLAG_UNUSED_0x0F6                    0x0F6
#define FLAG_UNUSED_0x0F7                    0x0F7
#define FLAG_UNUSED_0x0F8                    0x0F8
#define FLAG_UNUSED_0x0F9                    0x0F9
#define FLAG_UNUSED_0x0FA                    0x0FA
#define FLAG_UNUSED_0x0FB                    0x0FB
#define FLAG_UNUSED_0x0FC                    0x0FC
#define FLAG_ENABLE_RIVAL_MATCH_CALL         0x0FD // Move
#define FLAG_UNUSED_0x0FE                    0x0FE
#define FLAG_LATIOS_OR_LATIAS_ROAMING        0x0FF // Chopping block
#define FLAG_UNUSED_0x100                    0x100
#define FLAG_UNUSED_0x101                    0x101
#define FLAG_UNUSED_0x102                    0x102
#define FLAG_UNUSED_0x103                    0x103
#define FLAG_UNUSED_0x104                    0x104
#define FLAG_UNUSED_0x105                    0x105
#define FLAG_UNUSED_0x106                    0x106
#define FLAG_UNUSED_0x107                    0x107
#define FLAG_UNUSED_0x108                    0x108
#define FLAG_UNUSED_0x109                    0x109
#define FLAG_UNUSED_0x10A                    0x10A
#define FLAG_UNUSED_0x10B                    0x10B
#define FLAG_SECRET_BASE_REGISTRY_ENABLED    0x10C // Move
#define FLAG_UNUSED_0x10D                    0x10D
#define FLAG_CONTEST_SKETCH_CREATED          0x10E  // Set but never read
#define FLAG_UNUSED_0x10F                    0x10F
#define FLAG_UNUSED_0x110                    0x110
#define FLAG_POKERUS_EXPLAINED               0x111 // Move?
#define FLAG_UNUSED_0x112                    0x112
#define FLAG_RECEIVED_QUICK_CLAW             0x113 // Used in Trick House Ext Gatehouse
#define FLAG_UNUSED_0x114                    0x114
#define FLAG_UNUSED_0x115                    0x115
#define FLAG_UNUSED_0x116                    0x116
#define FLAG_UNUSED_0x117                    0x117
#define FLAG_UNUSED_0x118                    0x118
#define FLAG_ENABLE_PROF_BIRCH_MATCH_CALL    0x119 // Move
#define FLAG_UNUSED_0x11A                    0x11A
#define FLAG_UNUSED_0x11B                    0x11B
#define FLAG_UNUSED_0x11C                    0x11C
#define FLAG_UNUSED_0x11D                    0x11D
#define FLAG_UNUSED_0x11E                    0x11E
#define FLAG_UNUSED_0x11F                    0x11F
#define FLAG_UNUSED_0x120                    0x120
#define FLAG_UNUSED_0x121                    0x121
#define FLAG_UNUSED_0x122                    0x122
#define FLAG_RECEIVED_SS_TICKET              0x123 // Chopping block
#define FLAG_UNUSED_0x124                    0x124
#define FLAG_UNUSED_0x125                    0x125
#define FLAG_UNUSED_0x126                    0x126
#define FLAG_KECLEON_FLED_FORTREE            0x127 // Used
#define FLAG_PETALBURG_MART_EXPANDED_ITEMS   0x128 // Chopping block
#define FLAG_UNUSED_0x129                    0x129
#define FLAG_RECEIVED_BELDUM                 0x12A // Chopping block
#define FLAG_UNUSED_0x12B                    0x12B
#define FLAG_UNUSED_0x12C                    0x12C
#define FLAG_UNUSED_0x12D                    0x12D
#define FLAG_UNUSED_0x12E                    0x12E
#define FLAG_HAS_MATCH_CALL                  0x12F // Move
#define FLAG_ADDED_MATCH_CALL_TO_POKENAV     0x130 // Move?
#define FLAG_REGISTERED_STEVEN_POKENAV       0x131 // Chopping block
#define FLAG_ENABLE_NORMAN_MATCH_CALL        0x132 // Chopping block
#define FLAG_UNUSED_0x133                    0x133
#define FLAG_UNUSED_0x134                    0x134
#define FLAG_UNUSED_0x135                    0x135
#define FLAG_UNUSED_0x136                    0x136
#define FLAG_UNUSED_0x137                    0x137
#define FLAG_TTH_NEWS_REPORT                 0x138 // TTH
#define FLAG_UNUSED_0x139                    0x139
#define FLAG_RECEIVED_AURORA_TICKET          0x13A // Chopping block
#define FLAG_RECEIVED_MYSTIC_TICKET          0x13B // Chopping block
#define FLAG_RECEIVED_OLD_SEA_MAP            0x13C // Chopping block
#define FLAG_WONDER_CARD_UNUSED_1            0x13D // These Wonder Card flags are referenced but never set
#define FLAG_WONDER_CARD_UNUSED_2            0x13E // All on the chopping block!
#define FLAG_WONDER_CARD_UNUSED_3            0x13F
#define FLAG_WONDER_CARD_UNUSED_4            0x140
#define FLAG_WONDER_CARD_UNUSED_5            0x141
#define FLAG_WONDER_CARD_UNUSED_6            0x142
#define FLAG_WONDER_CARD_UNUSED_7            0x143
#define FLAG_WONDER_CARD_UNUSED_8            0x144
#define FLAG_WONDER_CARD_UNUSED_9            0x145
#define FLAG_WONDER_CARD_UNUSED_10           0x146
#define FLAG_WONDER_CARD_UNUSED_11           0x147
#define FLAG_WONDER_CARD_UNUSED_12           0x148
#define FLAG_WONDER_CARD_UNUSED_13           0x149
#define FLAG_WONDER_CARD_UNUSED_14           0x14A
#define FLAG_WONDER_CARD_UNUSED_15           0x14B
#define FLAG_WONDER_CARD_UNUSED_16           0x14C
#define FLAG_WONDER_CARD_UNUSED_17           0x14D
#define NUM_WONDER_CARD_FLAGS                (1 + FLAG_WONDER_CARD_UNUSED_17 - FLAG_RECEIVED_AURORA_TICKET)

#define FLAG_MIRAGE_TOWER_VISIBLE            0x14E // Chopping block
#define FLAG_UNUSED_0x14F                    0x14F 
#define FLAG_UNUSED_0x150                    0x150
#define FLAG_UNUSED_0x151                    0x151
#define FLAG_CHOSEN_MULTI_BATTLE_NPC_PARTNER 0x152 // Chopping block
#define FLAG_UNUSED_0x153                    0x153
#define FLAG_UNUSED_0x154                    0x154
#define FLAG_ENTERED_CONTEST                 0x155 // ???
#define FLAG_UNUSED_0x156                    0x156
#define FLAG_UNUSED_0x157                    0x157
#define FLAG_ENABLE_MR_STONE_POKENAV         0x158 // Move
#define FLAG_NURSE_MENTIONS_GOLD_CARD        0x159 // Chopping block
#define FLAG_UNUSED_0x15A                    0x15A
#define FLAG_UNUSED_0x15B                    0x15B

// Trainer Rematch Flags
#define FLAG_MATCH_CALL_REGISTERED           0x15C
#define FLAG_REMATCH_ROSE                    0x15D
#define FLAG_REMATCH_ANDRES                  0x15E
#define FLAG_REMATCH_DUSTY                   0x15F
#define FLAG_REMATCH_LOLA                    0x160
#define FLAG_REMATCH_RICKY                   0x161
#define FLAG_REMATCH_LILA_AND_ROY            0x162
#define FLAG_REMATCH_CRISTIN                 0x163
#define FLAG_REMATCH_BROOKE                  0x164
#define FLAG_REMATCH_WILTON                  0x165
#define FLAG_REMATCH_VALERIE                 0x166
#define FLAG_REMATCH_CINDY                   0x167
#define FLAG_REMATCH_THALIA                  0x168
#define FLAG_REMATCH_JESSICA                 0x169
#define FLAG_REMATCH_WINSTON                 0x16A
#define FLAG_REMATCH_STEVE                   0x16B
#define FLAG_REMATCH_TONY                    0x16C
#define FLAG_REMATCH_NOB                     0x16D
#define FLAG_REMATCH_KOJI                    0x16E
#define FLAG_REMATCH_FERNANDO                0x16F
#define FLAG_REMATCH_DALTON                  0x170
#define FLAG_REMATCH_BERNIE                  0x171
#define FLAG_REMATCH_ETHAN                   0x172
#define FLAG_REMATCH_JOHN_AND_JAY            0x173
#define FLAG_REMATCH_JEFFREY                 0x174
#define FLAG_REMATCH_CAMERON                 0x175
#define FLAG_REMATCH_JACKI                   0x176
#define FLAG_REMATCH_WALTER                  0x177
#define FLAG_REMATCH_KAREN                   0x178
#define FLAG_REMATCH_JERRY                   0x179
#define FLAG_REMATCH_ANNA_AND_MEG            0x17A
#define FLAG_REMATCH_ISABEL                  0x17B
#define FLAG_REMATCH_MIGUEL                  0x17C
#define FLAG_REMATCH_TIMOTHY                 0x17D
#define FLAG_REMATCH_SHELBY                  0x17E
#define FLAG_REMATCH_CALVIN                  0x17F
#define FLAG_REMATCH_ELLIOT                  0x180
#define FLAG_REMATCH_ISAIAH                  0x181
#define FLAG_REMATCH_MARIA                   0x182
#define FLAG_REMATCH_ABIGAIL                 0x183
#define FLAG_REMATCH_DYLAN                   0x184
#define FLAG_REMATCH_KATELYN                 0x185
#define FLAG_REMATCH_BENJAMIN                0x186
#define FLAG_REMATCH_PABLO                   0x187
#define FLAG_REMATCH_NICOLAS                 0x188
#define FLAG_REMATCH_ROBERT                  0x189
#define FLAG_REMATCH_LAO                     0x18A
#define FLAG_REMATCH_CYNDY                   0x18B
#define FLAG_REMATCH_MADELINE                0x18C
#define FLAG_REMATCH_JENNY                   0x18D
#define FLAG_REMATCH_DIANA                   0x18E
#define FLAG_REMATCH_AMY_AND_LIV             0x18F
#define FLAG_REMATCH_ERNEST                  0x190
#define FLAG_REMATCH_CORY                    0x191
#define FLAG_REMATCH_EDWIN                   0x192
#define FLAG_REMATCH_LYDIA                   0x193
#define FLAG_REMATCH_ISAAC                   0x194
#define FLAG_REMATCH_GABRIELLE               0x195
#define FLAG_REMATCH_CATHERINE               0x196
#define FLAG_REMATCH_JACKSON                 0x197
#define FLAG_REMATCH_HALEY                   0x198
#define FLAG_REMATCH_JAMES                   0x199
#define FLAG_REMATCH_TRENT                   0x19A
#define FLAG_REMATCH_SAWYER                  0x19B
#define FLAG_REMATCH_KIRA_AND_DAN            0x19C
#define FLAG_REMATCH_WALLY                   0x19D
#define FLAG_REMATCH_ROXANNE                 0x19E
#define FLAG_REMATCH_BRAWLY                  0x19F
#define FLAG_REMATCH_WATTSON                 0x1A0
#define FLAG_REMATCH_FLANNERY                0x1A1
#define FLAG_REMATCH_NORMAN                  0x1A2
#define FLAG_REMATCH_WINONA                  0x1A3
#define FLAG_REMATCH_TATE_AND_LIZA           0x1A4
// Note: FLAG_REMATCH_JUAN is handled by FLAG_ENABLE_JUAN_MATCH_CALL instead.
#define FLAG_REMATCH_SIDNEY                  0x1A5
#define FLAG_REMATCH_PHOEBE                  0x1A6
#define FLAG_REMATCH_GLACIA                  0x1A7
#define FLAG_REMATCH_DRAKE                   0x1A8
#define FLAG_REMATCH_WALLACE                 0x1A9
#define FLAG_UNUSED_0x1AA                    0x1AA
#define FLAG_UNUSED_0x1AB                    0x1AB
#define FLAG_UNUSED_0x1AC                    0x1AC
#define FLAG_BATTLED_DEOXYS                  0x1AD // Chopping block
#define FLAG_SHOWN_EON_TICKET                0x1AE // Chopping block
#define FLAG_SHOWN_AURORA_TICKET             0x1AF // Chopping block
#define FLAG_SHOWN_OLD_SEA_MAP               0x1B0 // Chopping block
#define FLAG_MOVE_TUTOR_TAUGHT_SWAGGER       0x1B1 // Chopping block
#define FLAG_MOVE_TUTOR_TAUGHT_ROLLOUT       0x1B2 // Chopping block
#define FLAG_MOVE_TUTOR_TAUGHT_FURY_CUTTER   0x1B3 // Chopping block
#define FLAG_MOVE_TUTOR_TAUGHT_MIMIC         0x1B4 // Chopping block
#define FLAG_MOVE_TUTOR_TAUGHT_METRONOME     0x1B5 // Chopping block
#define FLAG_MOVE_TUTOR_TAUGHT_SLEEP_TALK    0x1B6 // Chopping block
#define FLAG_MOVE_TUTOR_TAUGHT_SUBSTITUTE    0x1B7 // Chopping block
#define FLAG_MOVE_TUTOR_TAUGHT_DYNAMICPUNCH  0x1B8 // Chopping block
#define FLAG_MOVE_TUTOR_TAUGHT_DOUBLE_EDGE   0x1B9 // Chopping block
#define FLAG_MOVE_TUTOR_TAUGHT_EXPLOSION     0x1BA // Chopping block
#define FLAG_UNUSED_0x1BB                    0x1BB
#define FLAG_UNUSED_0x1BC                    0x1BC
#define FLAG_UNUSED_0x1BD                    0x1BD
#define FLAG_UNUSED_0x1BE                    0x1BE
#define FLAG_UNUSED_0x1BF                    0x1BF
#define FLAG_UNUSED_0x1C0                    0x1C0
#define FLAG_UNUSED_0x1C1                    0x1C1
#define FLAG_UNUSED_0x1C2                    0x1C2
#define FLAG_UNUSED_0x1C3                    0x1C3
#define FLAG_UNUSED_0x1C4                    0x1C4
#define FLAG_UNUSED_0x1C5                    0x1C5
#define FLAG_UNUSED_0x1C6                    0x1C6
#define FLAG_UNUSED_0x1C7                    0x1C7
#define FLAG_UNUSED_0x1C8                    0x1C8
#define FLAG_UNUSED_0x1C9                    0x1C9
#define FLAG_CAUGHT_MEW                      0x1CA // Chopping block
#define FLAG_UNUSED_0x1CB                    0x1CB
#define FLAG_UNUSED_0x1CC                    0x1CC
#define FLAG_UNUSED_0x1CD                    0x1CD
#define FLAG_UNUSED_0x1CE                    0x1CE
#define FLAG_UNUSED_0x1CF                    0x1CF
#define FLAG_MET_SCOTT_ON_SS_TIDAL           0x1D0 // Chopping block
#define FLAG_UNUSED_0x1D1                    0x1D1
#define FLAG_UNUSED_0x1D2                    0x1D2
#define FLAG_ENABLE_ROXANNE_MATCH_CALL       0x1D3 // Chopping block
#define FLAG_ENABLE_BRAWLY_MATCH_CALL        0x1D4 // Chopping block
#define FLAG_ENABLE_WATTSON_MATCH_CALL       0x1D5 // Chopping block
#define FLAG_ENABLE_FLANNERY_MATCH_CALL      0x1D6 // Chopping block
#define FLAG_ENABLE_WINONA_MATCH_CALL        0x1D7 // Chopping block
#define FLAG_ENABLE_TATE_AND_LIZA_MATCH_CALL 0x1D8 // Chopping block
#define FLAG_ENABLE_JUAN_MATCH_CALL          0x1D9 // Chopping block
#define FLAG_UNUSED_0x1DA                    0x1DA
#define FLAG_SHOWN_MYSTIC_TICKET             0x1DB // Chopping block
#define FLAG_UNUSED_0x1DC                    0x1DC
#define FLAG_UNUSED_0x1DD                    0x1DD
#define FLAG_UNUSED_0x1DE                    0x1DE
#define FLAG_UNUSED_0x1DF                    0x1DF
#define FLAG_UNUSED_0x1E0                    0x1E0
#define FLAG_UNUSED_0x1E1                    0x1E1
#define FLAG_UNUSED_0x1E2                    0x1E2
#define FLAG_UNUSED_0x1E3                    0x1E3
#define FLAG_UNUSED_0x1E4                    0x1E4
#define FLAG_UNUSED_0x1E5                    0x1E5
#define FLAG_UNUSED_0x1E6                    0x1E6
#define FLAG_UNUSED_0x1E7                    0x1E7
#define FLAG_UNUSED_0x1E8                    0x1E8
#define FLAG_UNUSED_0x1E9                    0x1E9
#define FLAG_UNUSED_0x1EA                    0x1EA
#define FLAG_UNUSED_0x1EB                    0x1EB
#define FLAG_UNUSED_0x1EC                    0x1EC
#define FLAG_UNUSED_0x1ED                    0x1ED
#define FLAG_UNUSED_0x1EE                    0x1EE
#define FLAG_UNUSED_0x1EF                    0x1EF

// #define FLAG_TRICK_HOUSE_END_ROOM            0x1F5 // Trick House End Room Flag

// Hidden Items -- sorted by location
#define FLAG_HIDDEN_ITEMS_START                               0x1F0
#define FLAG_HIDDEN_ITEM_PUZZLE_0x00                         (FLAG_HIDDEN_ITEMS_START + 0x00)
#define FLAG_HIDDEN_ITEM_PUZZLE_0x01                         (FLAG_HIDDEN_ITEMS_START + 0x01)
#define FLAG_HIDDEN_ITEM_PUZZLE_0x02                         (FLAG_HIDDEN_ITEMS_START + 0x02)
#define FLAG_HIDDEN_ITEM_PUZZLE_0x03                         (FLAG_HIDDEN_ITEMS_START + 0x03)
#define FLAG_HIDDEN_ITEM_PUZZLE_0x04                         (FLAG_HIDDEN_ITEMS_START + 0x04)
#define FLAG_HIDDEN_ITEM_PUZZLE_0x05                         (FLAG_HIDDEN_ITEMS_START + 0x05)
#define FLAG_HIDDEN_ITEM_PUZZLE_0x06                         (FLAG_HIDDEN_ITEMS_START + 0x06)
#define FLAG_HIDDEN_ITEM_PUZZLE_0x07                         (FLAG_HIDDEN_ITEMS_START + 0x07)
#define FLAG_HIDDEN_ITEM_PUZZLE_0x08                         (FLAG_HIDDEN_ITEMS_START + 0x08)
#define FLAG_HIDDEN_ITEM_PUZZLE_0x09                         (FLAG_HIDDEN_ITEMS_START + 0x09)
#define FLAG_HIDDEN_ITEM_PUZZLE_0x0A                         (FLAG_HIDDEN_ITEMS_START + 0x0A)
#define FLAG_HIDDEN_ITEM_PUZZLE_0x0B                         (FLAG_HIDDEN_ITEMS_START + 0x0B)
#define FLAG_HIDDEN_ITEM_PUZZLE_0x0C                         (FLAG_HIDDEN_ITEMS_START + 0x0C)
#define FLAG_HIDDEN_ITEM_PUZZLE_0x0D                         (FLAG_HIDDEN_ITEMS_START + 0x0D)
#define FLAG_HIDDEN_ITEM_PUZZLE_0x0E                         (FLAG_HIDDEN_ITEMS_START + 0x0E)
#define FLAG_HIDDEN_ITEM_PUZZLE_0x0F                         (FLAG_HIDDEN_ITEMS_START + 0x0F)
#define FLAG_HIDDEN_ITEM_PUZZLE_0x10                         (FLAG_HIDDEN_ITEMS_START + 0x10)
#define FLAG_HIDDEN_ITEM_PUZZLE_0x11                         (FLAG_HIDDEN_ITEMS_START + 0x11)
#define FLAG_HIDDEN_ITEM_PUZZLE_0x12                         (FLAG_HIDDEN_ITEMS_START + 0x12)
#define FLAG_HIDDEN_ITEM_PUZZLE_0x13                         (FLAG_HIDDEN_ITEMS_START + 0x13)
#define FLAG_HIDDEN_ITEM_PUZZLE_0x14                         (FLAG_HIDDEN_ITEMS_START + 0x14)
#define FLAG_HIDDEN_ITEM_PUZZLE_0x15                         (FLAG_HIDDEN_ITEMS_START + 0x15)
#define FLAG_HIDDEN_ITEM_PUZZLE_0x16                         (FLAG_HIDDEN_ITEMS_START + 0x16)
#define FLAG_HIDDEN_ITEM_PUZZLE_0x17                         (FLAG_HIDDEN_ITEMS_START + 0x17)
#define FLAG_HIDDEN_ITEM_PUZZLE_0x18                         (FLAG_HIDDEN_ITEMS_START + 0x18)
#define FLAG_HIDDEN_ITEM_PUZZLE_0x19                         (FLAG_HIDDEN_ITEMS_START + 0x19)
#define FLAG_HIDDEN_ITEM_PUZZLE_0x1A                         (FLAG_HIDDEN_ITEMS_START + 0x1A)
#define FLAG_HIDDEN_ITEM_PUZZLE_0x1B                         (FLAG_HIDDEN_ITEMS_START + 0x1B)
#define FLAG_HIDDEN_ITEM_PUZZLE_0x1C                         (FLAG_HIDDEN_ITEMS_START + 0x1C)
#define FLAG_HIDDEN_ITEM_PUZZLE_0x1D                         (FLAG_HIDDEN_ITEMS_START + 0x1D)
#define FLAG_HIDDEN_ITEM_PUZZLE_0x1E                         (FLAG_HIDDEN_ITEMS_START + 0x1E)
#define FLAG_HIDDEN_ITEM_PUZZLE_0x1F                         (FLAG_HIDDEN_ITEMS_START + 0x1F)
#define FLAG_HIDDEN_ITEM_TRICK_HOUSE_0x20                    (FLAG_HIDDEN_ITEMS_START + 0x20)
#define FLAG_HIDDEN_ITEM_UNUSED_0x21                         (FLAG_HIDDEN_ITEMS_START + 0x21)
#define FLAG_HIDDEN_ITEM_UNUSED_0x22                         (FLAG_HIDDEN_ITEMS_START + 0x22)
#define FLAG_HIDDEN_ITEM_UNUSED_0x23                         (FLAG_HIDDEN_ITEMS_START + 0x23)
#define FLAG_HIDDEN_ITEM_UNUSED_0x24                         (FLAG_HIDDEN_ITEMS_START + 0x24)
#define FLAG_HIDDEN_ITEM_UNUSED_0x25                         (FLAG_HIDDEN_ITEMS_START + 0x25)
#define FLAG_HIDDEN_ITEM_UNUSED_0x26                         (FLAG_HIDDEN_ITEMS_START + 0x26)
#define FLAG_ITEM_ROUTE_110_ITEMFINDER                       (FLAG_HIDDEN_ITEMS_START + 0x27)
#define FLAG_HIDDEN_ITEM_TRICK_HOUSE_0x28                    (FLAG_HIDDEN_ITEMS_START + 0x28)
#define FLAG_HIDDEN_ITEM_TRICK_HOUSE_0x29                    (FLAG_HIDDEN_ITEMS_START + 0x29)
#define FLAG_HIDDEN_ITEM_TRICK_HOUSE_0x2A                    (FLAG_HIDDEN_ITEMS_START + 0x2A)
#define FLAG_HIDDEN_ITEM_TRICK_HOUSE_0x2B                    (FLAG_HIDDEN_ITEMS_START + 0x2B)
#define FLAG_HIDDEN_ITEM_TRICK_HOUSE_0x2C                    (FLAG_HIDDEN_ITEMS_START + 0x2C)
#define FLAG_HIDDEN_ITEM_TRICK_HOUSE_0x2D                    (FLAG_HIDDEN_ITEMS_START + 0x2D)
#define FLAG_HIDDEN_ITEM_TRICK_HOUSE_0x2E                    (FLAG_HIDDEN_ITEMS_START + 0x2E)
#define FLAG_HIDDEN_ITEM_TRICK_HOUSE_0x2F                    (FLAG_HIDDEN_ITEMS_START + 0x2F)
#define FLAG_HIDDEN_ITEM_TRICK_HOUSE_0x30                    (FLAG_HIDDEN_ITEMS_START + 0x30)
#define FLAG_HIDDEN_ITEM_TRICK_HOUSE_0x31                    (FLAG_HIDDEN_ITEMS_START + 0x31)
#define FLAG_HIDDEN_ITEM_TRICK_HOUSE_0x32                    (FLAG_HIDDEN_ITEMS_START + 0x32)
#define FLAG_HIDDEN_ITEM_TRICK_HOUSE_0x33                    (FLAG_HIDDEN_ITEMS_START + 0x33)
#define FLAG_HIDDEN_ITEM_TRICK_HOUSE_0x34                    (FLAG_HIDDEN_ITEMS_START + 0x34)
#define FLAG_HIDDEN_ITEM_TRICK_HOUSE_0x35                    (FLAG_HIDDEN_ITEMS_START + 0x35)
#define FLAG_HIDDEN_ITEM_TRICK_HOUSE_0x36                    (FLAG_HIDDEN_ITEMS_START + 0x36)
#define FLAG_HIDDEN_ITEM_TRICK_HOUSE_0x37                    (FLAG_HIDDEN_ITEMS_START + 0x37)
#define FLAG_HIDDEN_ITEM_TRICK_HOUSE_0x38                    (FLAG_HIDDEN_ITEMS_START + 0x38)
#define FLAG_HIDDEN_ITEM_UNUSED_0x39                         (FLAG_HIDDEN_ITEMS_START + 0x39)
#define FLAG_HIDDEN_ITEM_UNUSED_0x3A                         (FLAG_HIDDEN_ITEMS_START + 0x3A)
#define FLAG_HIDDEN_ITEM_UNUSED_0x3B                         (FLAG_HIDDEN_ITEMS_START + 0x3B)
#define FLAG_HIDDEN_ITEM_UNUSED_0x3C                         (FLAG_HIDDEN_ITEMS_START + 0x3C)
#define FLAG_HIDDEN_ITEM_UNUSED_0x3D                         (FLAG_HIDDEN_ITEMS_START + 0x3D)
#define FLAG_HIDDEN_ITEM_UNUSED_0x3E                         (FLAG_HIDDEN_ITEMS_START + 0x3E)
#define FLAG_HIDDEN_ITEM_UNUSED_0x3F                         (FLAG_HIDDEN_ITEMS_START + 0x3F)
#define FLAG_HIDDEN_ITEM_UNUSED_0x40                         (FLAG_HIDDEN_ITEMS_START + 0x40)
#define FLAG_HIDDEN_ITEM_UNUSED_0x41                         (FLAG_HIDDEN_ITEMS_START + 0x41)
#define FLAG_HIDDEN_ITEM_UNUSED_0x42                         (FLAG_HIDDEN_ITEMS_START + 0x42)
#define FLAG_HIDDEN_ITEM_UNUSED_0x43                         (FLAG_HIDDEN_ITEMS_START + 0x43)
#define FLAG_HIDDEN_ITEM_UNUSED_0x44                         (FLAG_HIDDEN_ITEMS_START + 0x44)
#define FLAG_HIDDEN_ITEM_UNUSED_0x45                         (FLAG_HIDDEN_ITEMS_START + 0x45)
#define FLAG_HIDDEN_ITEM_UNUSED_0x46                         (FLAG_HIDDEN_ITEMS_START + 0x46)
#define FLAG_HIDDEN_ITEM_UNUSED_0x47                         (FLAG_HIDDEN_ITEMS_START + 0x47)
#define FLAG_HIDDEN_ITEM_UNUSED_0x48                         (FLAG_HIDDEN_ITEMS_START + 0x48)
#define FLAG_HIDDEN_ITEM_UNUSED_0x49                         (FLAG_HIDDEN_ITEMS_START + 0x49)
#define FLAG_HIDDEN_ITEM_UNUSED_0x4A                         (FLAG_HIDDEN_ITEMS_START + 0x4A)
#define FLAG_HIDDEN_ITEM_UNUSED_0x4B                         (FLAG_HIDDEN_ITEMS_START + 0x4B)
#define FLAG_HIDDEN_ITEM_UNUSED_0x4C                         (FLAG_HIDDEN_ITEMS_START + 0x4C)
#define FLAG_HIDDEN_ITEM_UNUSED_0x4D                         (FLAG_HIDDEN_ITEMS_START + 0x4D)
#define FLAG_HIDDEN_ITEM_UNUSED_0x4E                         (FLAG_HIDDEN_ITEMS_START + 0x4E)
#define FLAG_HIDDEN_ITEM_UNUSED_0x4F                         (FLAG_HIDDEN_ITEMS_START + 0x4F)
#define FLAG_HIDDEN_ITEM_UNUSED_0x50                         (FLAG_HIDDEN_ITEMS_START + 0x50)
#define FLAG_HIDDEN_ITEM_UNUSED_0x51                         (FLAG_HIDDEN_ITEMS_START + 0x51)
#define FLAG_HIDDEN_ITEM_UNUSED_0x52                         (FLAG_HIDDEN_ITEMS_START + 0x52)
#define FLAG_HIDDEN_ITEM_UNUSED_0x53                         (FLAG_HIDDEN_ITEMS_START + 0x53)
#define FLAG_HIDDEN_ITEM_UNUSED_0x54                         (FLAG_HIDDEN_ITEMS_START + 0x54)
#define FLAG_HIDDEN_ITEM_UNUSED_0x55                         (FLAG_HIDDEN_ITEMS_START + 0x55)
#define FLAG_HIDDEN_ITEM_UNUSED_0x56                         (FLAG_HIDDEN_ITEMS_START + 0x56)
#define FLAG_HIDDEN_ITEM_UNUSED_0x57                         (FLAG_HIDDEN_ITEMS_START + 0x57)
#define FLAG_HIDDEN_ITEM_UNUSED_0x58                         (FLAG_HIDDEN_ITEMS_START + 0x58)
#define FLAG_HIDDEN_ITEM_UNUSED_0x59                         (FLAG_HIDDEN_ITEMS_START + 0x59)
#define FLAG_HIDDEN_ITEM_UNUSED_0x5A                         (FLAG_HIDDEN_ITEMS_START + 0x5A)
#define FLAG_HIDDEN_ITEM_UNUSED_0x5B                         (FLAG_HIDDEN_ITEMS_START + 0x5B)
#define FLAG_HIDDEN_ITEM_UNUSED_0x5C                         (FLAG_HIDDEN_ITEMS_START + 0x5C)
#define FLAG_HIDDEN_ITEM_UNUSED_0x5D                         (FLAG_HIDDEN_ITEMS_START + 0x5D)
#define FLAG_HIDDEN_ITEM_UNUSED_0x5E                         (FLAG_HIDDEN_ITEMS_START + 0x5E)
#define FLAG_HIDDEN_ITEM_UNUSED_0x5F                         (FLAG_HIDDEN_ITEMS_START + 0x5F)
#define FLAG_HIDDEN_ITEM_UNUSED_0x60                         (FLAG_HIDDEN_ITEMS_START + 0x60)
#define FLAG_HIDDEN_ITEM_UNUSED_0x61                         (FLAG_HIDDEN_ITEMS_START + 0x61)
#define FLAG_HIDDEN_ITEM_UNUSED_0x62                         (FLAG_HIDDEN_ITEMS_START + 0x62)
#define FLAG_HIDDEN_ITEM_UNUSED_0x63                         (FLAG_HIDDEN_ITEMS_START + 0x63)
#define FLAG_HIDDEN_ITEM_UNUSED_0x64                         (FLAG_HIDDEN_ITEMS_START + 0x64)
#define FLAG_HIDDEN_ITEM_UNUSED_0x65                         (FLAG_HIDDEN_ITEMS_START + 0x65)
#define FLAG_HIDDEN_ITEM_UNUSED_0x66                         (FLAG_HIDDEN_ITEMS_START + 0x66)
#define FLAG_HIDDEN_ITEM_UNUSED_0x67                         (FLAG_HIDDEN_ITEMS_START + 0x67)
#define FLAG_HIDDEN_ITEM_UNUSED_0x68                         (FLAG_HIDDEN_ITEMS_START + 0x68)
#define FLAG_HIDDEN_LIMITED_CANDY_0x69                       (FLAG_HIDDEN_ITEMS_START + 0x69)
#define FLAG_HIDDEN_LIMITED_CANDY_0x6A                       (FLAG_HIDDEN_ITEMS_START + 0x6A)
#define FLAG_HIDDEN_LIMITED_CANDY_0x6B                       (FLAG_HIDDEN_ITEMS_START + 0x6B)
#define FLAG_HIDDEN_LIMITED_CANDY_0x6C                       (FLAG_HIDDEN_ITEMS_START + 0x6C)
#define FLAG_HIDDEN_LIMITED_CANDY_0x6D                       (FLAG_HIDDEN_ITEMS_START + 0x6D)
#define FLAG_HIDDEN_LIMITED_CANDY_0x6E                       (FLAG_HIDDEN_ITEMS_START + 0x6E)
#define FLAG_HIDDEN_LIMITED_CANDY_0x6F                       (FLAG_HIDDEN_ITEMS_START + 0x6F)

#define FLAG_UNUSED_0x264                                    0x264
#define FLAG_UNUSED_0x265                                    0x265
#define FLAG_UNUSED_0x266                                    0x266
#define FLAG_UNUSED_0x267                                    0x267
#define FLAG_UNUSED_0x268                                    0x268
#define FLAG_UNUSED_0x269                                    0x269
#define FLAG_UNUSED_0x26A                                    0x26A
#define FLAG_UNUSED_0x26B                                    0x26B
#define FLAG_UNUSED_0x26C                                    0x26C
#define FLAG_UNUSED_0x26D                                    0x26D
#define FLAG_UNUSED_0x26E                                    0x26E
#define FLAG_UNUSED_0x26F                                    0x26F
#define FLAG_UNUSED_0x270                                    0x270
#define FLAG_UNUSED_0x271                                    0x271
#define FLAG_UNUSED_0x272                                    0x272
#define FLAG_UNUSED_0x273                                    0x273
#define FLAG_UNUSED_0x274                                    0x274
#define FLAG_UNUSED_0x275                                    0x275
#define FLAG_UNUSED_0x276                                    0x276
#define FLAG_UNUSED_0x277                                    0x277
#define FLAG_UNUSED_0x278                                    0x278
#define FLAG_UNUSED_0x279                                    0x279
#define FLAG_UNUSED_0x27A                                    0x27A
#define FLAG_UNUSED_0x27B                                    0x27B
#define FLAG_UNUSED_0x27C                                    0x27C
#define FLAG_UNUSED_0x27D                                    0x27D
#define FLAG_UNUSED_0x27E                                    0x27E
#define FLAG_UNUSED_0x27F                                    0x27F
#define FLAG_UNUSED_0x280                                    0x280
#define FLAG_UNUSED_0x281                                    0x281
#define FLAG_UNUSED_0x282                                    0x282
#define FLAG_UNUSED_0x283                                    0x283
#define FLAG_UNUSED_0x284                                    0x284
#define FLAG_UNUSED_0x285                                    0x285
#define FLAG_UNUSED_0x286                                    0x286
#define FLAG_UNUSED_0x287                                    0x287
#define FLAG_UNUSED_0x288                                    0x288
#define FLAG_UNUSED_0x289                                    0x289
#define FLAG_UNUSED_0x28A                                    0x28A
#define FLAG_UNUSED_0x28B                                    0x28B
#define FLAG_UNUSED_0x28C                                    0x28C
#define FLAG_UNUSED_0x28D                                    0x28D
#define FLAG_UNUSED_0x28E                                    0x28E
#define FLAG_UNUSED_0x28F                                    0x28F
#define FLAG_UNUSED_0x290                                    0x290
#define FLAG_UNUSED_0x291                                    0x291
#define FLAG_UNUSED_0x292                                    0x292
#define FLAG_UNUSED_0x293                                    0x293
#define FLAG_UNUSED_0x294                                    0x294
#define FLAG_UNUSED_0x295                                    0x295
#define FLAG_UNUSED_0x296                                    0x296
#define FLAG_UNUSED_0x297                                    0x297
#define FLAG_UNUSED_0x298                                    0x298
#define FLAG_UNUSED_0x299                                    0x299
#define FLAG_UNUSED_0x29A                                    0x29A
#define FLAG_UNUSED_0x29B                                    0x29B
#define FLAG_UNUSED_0x29C                                    0x29C
#define FLAG_UNUSED_0x29D                                    0x29D
#define FLAG_UNUSED_0x29E                                    0x29E
#define FLAG_UNUSED_0x29F                                    0x29F
#define FLAG_UNUSED_0x2A0                                    0x2A0
#define FLAG_UNUSED_0x2A1                                    0x2A1
#define FLAG_UNUSED_0x2A2                                    0x2A2
#define FLAG_UNUSED_0x2A3                                    0x2A3
#define FLAG_UNUSED_0x2A4                                    0x2A4
#define FLAG_UNUSED_0x2A5                                    0x2A5
#define FLAG_UNUSED_0x2A6                                    0x2A6
#define FLAG_UNUSED_0x2A7                                    0x2A7
#define FLAG_UNUSED_0x2A8                                    0x2A8
#define FLAG_UNUSED_0x2A9                                    0x2A9
#define FLAG_UNUSED_0x2AA                                    0x2AA
#define FLAG_UNUSED_0x2AB                                    0x2AB
#define FLAG_UNUSED_0x2AC                                    0x2AC
#define FLAG_UNUSED_0x2AD                                    0x2AD
#define FLAG_UNUSED_0x2AE                                    0x2AE
#define FLAG_UNUSED_0x2AF                                    0x2AF
#define FLAG_UNUSED_0x2B0                                    0x2B0
#define FLAG_UNUSED_0x2B1                                    0x2B1
#define FLAG_UNUSED_0x2B2                                    0x2B2
#define FLAG_UNUSED_0x2B3                                    0x2B3
#define FLAG_UNUSED_0x2B4                                    0x2B4
#define FLAG_UNUSED_0x2B5                                    0x2B5
#define FLAG_UNUSED_0x2B6                                    0x2B6
#define FLAG_UNUSED_0x2B7                                    0x2B7
#define FLAG_UNUSED_0x2B8                                    0x2B8
#define FLAG_UNUSED_0x2B9                                    0x2B9
#define FLAG_UNUSED_0x2BA                                    0x2BA
#define FLAG_UNUSED_0x2BB                                    0x2BB

// Event Flags
#define FLAG_HIDE_TRICK_MASTER_ENDROOM                               0x2BC
#define FLAG_HIDE_TRICK_HOUSE_INTRO_CHAR                             0x2BD
#define FLAG_HIDE_TRICK_HOUSE_ENTRANCE_MAN                           0x2BE
#define FLAG_HIDE_TRICK_HOUSE_END_MAN                                0x2BF
#define FLAG_HIDE_DEBUG_OBJECTS                                      0x2C0
#define FLAG_HIDE_INTRO_CHARACTERS                                   0x2C1
#define FLAG_HIDE_TRICK_HOUSE_INTRO_CHARACTERS                       0x2C2
#define FLAG_HIDE_UNUSED_0x2C3                                       0x2C3
#define FLAG_HIDE_UNUSED_0x2C4                                       0x2C4
#define FLAG_HIDE_UNUSED_0x2C5                                       0x2C5
#define FLAG_HIDE_UNUSED_0x2C6                                       0x2C6
#define FLAG_HIDE_UNUSED_0x2C7                                       0x2C7
#define FLAG_HIDE_UNUSED_0x2C8                                       0x2C8
#define FLAG_HIDE_UNUSED_0x2C9                                       0x2C9
#define FLAG_HIDE_UNUSED_0x2CA                                       0x2CA
#define FLAG_HIDE_UNUSED_0x2CB                                       0x2CB
#define FLAG_HIDE_UNUSED_0x2CC                                       0x2CC
#define FLAG_HIDE_UNUSED_0x2CD                                       0x2CD
#define FLAG_HIDE_UNUSED_0x2CE                                       0x2CE
#define FLAG_HIDE_UNUSED_0x2CF                                       0x2CF
#define FLAG_HIDE_UNUSED_0x2D0                                       0x2D0
#define FLAG_HIDE_UNUSED_0x2D1                                       0x2D1
#define FLAG_HIDE_UNUSED_0x2D2                                       0x2D2
#define FLAG_HIDE_UNUSED_0x2D3                                       0x2D3
#define FLAG_HIDE_UNUSED_0x2D4                                       0x2D4
#define FLAG_HIDE_UNUSED_0x2D5                                       0x2D5
#define FLAG_HIDE_UNUSED_0x2D6                                       0x2D6
#define FLAG_HIDE_UNUSED_0x2D7                                       0x2D7
#define FLAG_HIDE_UNUSED_0x2D8                                       0x2D8
#define FLAG_HIDE_UNUSED_0x2D9                                       0x2D9
#define FLAG_HIDE_UNUSED_0x2DA                                       0x2DA
#define FLAG_HIDE_UNUSED_0x2DB                                       0x2DB
#define FLAG_HIDE_UNUSED_0x2DC                                       0x2DC
#define FLAG_HIDE_UNUSED_0x2DD                                       0x2DD
#define FLAG_HIDE_UNUSED_0x2DE                                       0x2DE
#define FLAG_HIDE_UNUSED_0x2DF                                       0x2DF
#define FLAG_HIDE_UNUSED_0x2E0                                       0x2E0
#define FLAG_HIDE_UNUSED_0x2E1                                       0x2E1
#define FLAG_HIDE_UNUSED_0x2E2                                       0x2E2
#define FLAG_HIDE_UNUSED_0x2E3                                       0x2E3
#define FLAG_HIDE_UNUSED_0x2E4                                       0x2E4
#define FLAG_HIDE_UNUSED_0x2E5                                       0x2E5
#define FLAG_HIDE_UNUSED_0x2E6                                       0x2E6
#define FLAG_HIDE_UNUSED_0x2E7                                       0x2E7
#define FLAG_HIDE_UNUSED_0x2E8                                       0x2E8
#define FLAG_HIDE_UNUSED_0x2E9                                       0x2E9
#define FLAG_HIDE_UNUSED_0x2EA                                       0x2EA
#define FLAG_HIDE_UNUSED_0x2EB                                       0x2EB
#define FLAG_HIDE_UNUSED_0x2EC                                       0x2EC
#define FLAG_HIDE_UNUSED_0x2ED                                       0x2ED
#define FLAG_HIDE_UNUSED_0x2EE                                       0x2EE
#define FLAG_HIDE_UNUSED_0x2EF                                       0x2EF
#define FLAG_HIDE_UNUSED_0x2F0                                       0x2F0
#define FLAG_HIDE_UNUSED_0x2F1                                       0x2F1
#define FLAG_HIDE_UNUSED_0x2F2                                       0x2F2
#define FLAG_HIDE_UNUSED_0x2F3                                       0x2F3
#define FLAG_HIDE_UNUSED_0x2F4                                       0x2F4
#define FLAG_HIDE_UNUSED_0x2F5                                       0x2F5
#define FLAG_HIDE_UNUSED_0x2F6                                       0x2F6
#define FLAG_HIDE_UNUSED_0x2F7                                       0x2F7
#define FLAG_HIDE_UNUSED_0x2F8                                       0x2F8
#define FLAG_HIDE_UNUSED_0x2F9                                       0x2F9
#define FLAG_HIDE_UNUSED_0x2FA                                       0x2FA
#define FLAG_HIDE_UNUSED_0x2FB                                       0x2FB
#define FLAG_HIDE_UNUSED_0x2FC                                       0x2FC
#define FLAG_HIDE_UNUSED_0x2FD                                       0x2FD
#define FLAG_HIDE_UNUSED_0x2FE                                       0x2FE
#define FLAG_HIDE_UNUSED_0x2FF                                       0x2FF
#define FLAG_HIDE_UNUSED_0x300                                       0x300
#define FLAG_HIDE_UNUSED_0x301                                       0x301
#define FLAG_HIDE_UNUSED_0x302                                       0x302
#define FLAG_HIDE_UNUSED_0x303                                       0x303
#define FLAG_HIDE_UNUSED_0x304                                       0x304
#define FLAG_HIDE_UNUSED_0x305                                       0x305
#define FLAG_HIDE_UNUSED_0x306                                       0x306
#define FLAG_HIDE_UNUSED_0x307                                       0x307
#define FLAG_HIDE_UNUSED_0x308                                       0x308
#define FLAG_HIDE_UNUSED_0x309                                       0x309
#define FLAG_HIDE_UNUSED_0x30A                                       0x30A
#define FLAG_HIDE_UNUSED_0x30B                                       0x30B
#define FLAG_HIDE_UNUSED_0x30C                                       0x30C
#define FLAG_HIDE_UNUSED_0x30D                                       0x30D
#define FLAG_HIDE_UNUSED_0x30E                                       0x30E
#define FLAG_HIDE_UNUSED_0x30F                                       0x30F
#define FLAG_HIDE_UNUSED_0x310                                       0x310
#define FLAG_HIDE_UNUSED_0x311                                       0x311
#define FLAG_HIDE_UNUSED_0x312                                       0x312
#define FLAG_HIDE_UNUSED_0x313                                       0x313
#define FLAG_HIDE_UNUSED_0x314                                       0x314
#define FLAG_HIDE_UNUSED_0x315                                       0x315
#define FLAG_HIDE_UNUSED_0x316                                       0x316
#define FLAG_HIDE_UNUSED_0x317                                       0x317
#define FLAG_HIDE_UNUSED_0x318                                       0x318
#define FLAG_HIDE_UNUSED_0x319                                       0x319
#define FLAG_HIDE_UNUSED_0x31A                                       0x31A
#define FLAG_HIDE_UNUSED_0x31B                                       0x31B
#define FLAG_HIDE_UNUSED_0x31C                                       0x31C
#define FLAG_HIDE_UNUSED_0x31D                                       0x31D
#define FLAG_HIDE_UNUSED_0x31E                                       0x31E
#define FLAG_HIDE_UNUSED_0x31F                                       0x31F
#define FLAG_HIDE_UNUSED_0x320                                       0x320
#define FLAG_HIDE_UNUSED_0x321                                       0x321
#define FLAG_HIDE_UNUSED_0x322                                       0x322
#define FLAG_HIDE_UNUSED_0x323                                       0x323
#define FLAG_HIDE_UNUSED_0x324                                       0x324
#define FLAG_HIDE_UNUSED_0x325                                       0x325
#define FLAG_HIDE_UNUSED_0x326                                       0x326
#define FLAG_HIDE_UNUSED_0x327                                       0x327
#define FLAG_HIDE_UNUSED_0x328                                       0x328
#define FLAG_HIDE_UNUSED_0x329                                       0x329
#define FLAG_HIDE_UNUSED_0x32A                                       0x32A
#define FLAG_HIDE_UNUSED_0x32B                                       0x32B
#define FLAG_HIDE_UNUSED_0x32C                                       0x32C
#define FLAG_HIDE_UNUSED_0x32D                                       0x32D
#define FLAG_HIDE_UNUSED_0x32E                                       0x32E
#define FLAG_HIDE_UNUSED_0x32F                                       0x32F
#define FLAG_HIDE_UNUSED_0x330                                       0x330
#define FLAG_HIDE_UNUSED_0x331                                       0x331
#define FLAG_HIDE_UNUSED_0x332                                       0x332
#define FLAG_HIDE_UNUSED_0x333                                       0x333
#define FLAG_HIDE_UNUSED_0x334                                       0x334
#define FLAG_HIDE_UNUSED_0x335                                       0x335
#define FLAG_HIDE_UNUSED_0x336                                       0x336
#define FLAG_HIDE_UNUSED_0x337                                       0x337
#define FLAG_HIDE_UNUSED_0x338                                       0x338
#define FLAG_HIDE_UNUSED_0x339                                       0x339
#define FLAG_HIDE_UNUSED_0x33A                                       0x33A
#define FLAG_HIDE_UNUSED_0x33B                                       0x33B
#define FLAG_HIDE_UNUSED_0x33C                                       0x33C
#define FLAG_HIDE_UNUSED_0x33D                                       0x33D
#define FLAG_HIDE_UNUSED_0x33E                                       0x33E
#define FLAG_HIDE_UNUSED_0x33F                                       0x33F
#define FLAG_HIDE_UNUSED_0x340                                       0x340
#define FLAG_HIDE_UNUSED_0x341                                       0x341
#define FLAG_HIDE_UNUSED_0x342                                       0x342
#define FLAG_HIDE_UNUSED_0x343                                       0x343
#define FLAG_HIDE_UNUSED_0x344                                       0x344
#define FLAG_HIDE_UNUSED_0x345                                       0x345
#define FLAG_HIDE_UNUSED_0x346                                       0x346
#define FLAG_HIDE_UNUSED_0x347                                       0x347
#define FLAG_HIDE_UNUSED_0x348                                       0x348
#define FLAG_HIDE_UNUSED_0x349                                       0x349
#define FLAG_HIDE_UNUSED_0x34A                                       0x34A
#define FLAG_HIDE_UNUSED_0x34B                                       0x34B
#define FLAG_HIDE_UNUSED_0x34C                                       0x34C
#define FLAG_HIDE_UNUSED_0x34D                                       0x34D
#define FLAG_HIDE_UNUSED_0x34E                                       0x34E
#define FLAG_HIDE_UNUSED_0x34F                                       0x34F
#define FLAG_HIDE_UNUSED_0x350                                       0x350
#define FLAG_HIDE_UNUSED_0x351                                       0x351
#define FLAG_HIDE_UNUSED_0x352                                       0x352
#define FLAG_HIDE_UNUSED_0x353                                       0x353
#define FLAG_HIDE_UNUSED_0x354                                       0x354
#define FLAG_HIDE_UNUSED_0x355                                       0x355
#define FLAG_HIDE_UNUSED_0x356                                       0x356
#define FLAG_HIDE_UNUSED_0x357                                       0x357
#define FLAG_HIDE_UNUSED_0x358                                       0x358
#define FLAG_HIDE_UNUSED_0x359                                       0x359
#define FLAG_HIDE_UNUSED_0x35A                                       0x35A
#define FLAG_HIDE_UNUSED_0x35B                                       0x35B
#define FLAG_HIDE_UNUSED_0x35C                                       0x35C
#define FLAG_HIDE_UNUSED_0x35D                                       0x35D
#define FLAG_HIDE_UNUSED_0x35E                                       0x35E
#define FLAG_HIDE_UNUSED_0x35F                                       0x35F
#define FLAG_HIDE_UNUSED_0x360                                       0x360
#define FLAG_HIDE_UNUSED_0x361                                       0x361
#define FLAG_HIDE_UNUSED_0x362                                       0x362
#define FLAG_HIDE_UNUSED_0x363                                       0x363
#define FLAG_HIDE_UNUSED_0x364                                       0x364
#define FLAG_HIDE_UNUSED_0x365                                       0x365
#define FLAG_HIDE_UNUSED_0x366                                       0x366
#define FLAG_HIDE_UNUSED_0x367                                       0x367
#define FLAG_HIDE_UNUSED_0x368                                       0x368
#define FLAG_HIDE_UNUSED_0x369                                       0x369
#define FLAG_HIDE_UNUSED_0x36A                                       0x36A
#define FLAG_HIDE_UNUSED_0x36B                                       0x36B
#define FLAG_HIDE_UNUSED_0x36C                                       0x36C
#define FLAG_HIDE_UNUSED_0x36D                                       0x36D
#define FLAG_HIDE_UNUSED_0x36E                                       0x36E
#define FLAG_HIDE_UNUSED_0x36F                                       0x36F
#define FLAG_HIDE_UNUSED_0x370                                       0x370
#define FLAG_HIDE_UNUSED_0x371                                       0x371
#define FLAG_HIDE_UNUSED_0x372                                       0x372
#define FLAG_HIDE_UNUSED_0x373                                       0x373
#define FLAG_HIDE_UNUSED_0x374                                       0x374
#define FLAG_HIDE_UNUSED_0x375                                       0x375
#define FLAG_HIDE_UNUSED_0x376                                       0x376
#define FLAG_HIDE_UNUSED_0x377                                       0x377
#define FLAG_HIDE_UNUSED_0x378                                       0x378
#define FLAG_HIDE_UNUSED_0x379                                       0x379
#define FLAG_HIDE_UNUSED_0x37A                                       0x37A
#define FLAG_HIDE_UNUSED_0x37B                                       0x37B
#define FLAG_HIDE_UNUSED_0x37C                                       0x37C
#define FLAG_HIDE_UNUSED_0x37D                                       0x37D
#define FLAG_HIDE_UNUSED_0x37E                                       0x37E
#define FLAG_HIDE_UNUSED_0x37F                                       0x37F
#define FLAG_HIDE_UNUSED_0x380                                       0x380
#define FLAG_HIDE_UNUSED_0x381                                       0x381
#define FLAG_HIDE_UNUSED_0x382                                       0x382
#define FLAG_HIDE_UNUSED_0x383                                       0x383
#define FLAG_HIDE_UNUSED_0x384                                       0x384
#define FLAG_HIDE_UNUSED_0x385                                       0x385
#define FLAG_HIDE_UNUSED_0x386                                       0x386
#define FLAG_HIDE_UNUSED_0x387                                       0x387
#define FLAG_HIDE_UNUSED_0x388                                       0x388
#define FLAG_HIDE_UNUSED_0x389                                       0x389
#define FLAG_HIDE_UNUSED_0x38A                                       0x38A
#define FLAG_HIDE_UNUSED_0x38B                                       0x38B
#define FLAG_HIDE_UNUSED_0x38C                                       0x38C
#define FLAG_HIDE_UNUSED_0x38D                                       0x38D
#define FLAG_HIDE_UNUSED_0x38E                                       0x38E
#define FLAG_HIDE_UNUSED_0x38F                                       0x38F
#define FLAG_HIDE_UNUSED_0x390                                       0x390
#define FLAG_HIDE_UNUSED_0x391                                       0x391
#define FLAG_HIDE_UNUSED_0x392                                       0x392
#define FLAG_HIDE_UNUSED_0x393                                       0x393
#define FLAG_HIDE_UNUSED_0x394                                       0x394
#define FLAG_HIDE_UNUSED_0x395                                       0x395
#define FLAG_HIDE_UNUSED_0x396                                       0x396
#define FLAG_HIDE_UNUSED_0x397                                       0x397
#define FLAG_HIDE_UNUSED_0x398                                       0x398
#define FLAG_HIDE_UNUSED_0x399                                       0x399
#define FLAG_HIDE_UNUSED_0x39A                                       0x39A
#define FLAG_HIDE_UNUSED_0x39B                                       0x39B
#define FLAG_HIDE_UNUSED_0x39C                                       0x39C
#define FLAG_HIDE_UNUSED_0x39D                                       0x39D
#define FLAG_HIDE_UNUSED_0x39E                                       0x39E
#define FLAG_HIDE_UNUSED_0x39F                                       0x39F
#define FLAG_HIDE_UNUSED_0x3A0                                       0x3A0
#define FLAG_HIDE_UNUSED_0x3A1                                       0x3A1
#define FLAG_HIDE_UNUSED_0x3A2                                       0x3A2
#define FLAG_HIDE_UNUSED_0x3A3                                       0x3A3
#define FLAG_HIDE_UNUSED_0x3A4                                       0x3A4
#define FLAG_HIDE_UNUSED_0x3A5                                       0x3A5
#define FLAG_HIDE_UNUSED_0x3A6                                       0x3A6
#define FLAG_HIDE_UNUSED_0x3A7                                       0x3A7
#define FLAG_HIDE_UNUSED_0x3A8                                       0x3A8
#define FLAG_HIDE_UNUSED_0x3A9                                       0x3A9
#define FLAG_HIDE_UNUSED_0x3AA                                       0x3AA
#define FLAG_HIDE_UNUSED_0x3AB                                       0x3AB
#define FLAG_HIDE_UNUSED_0x3AC                                       0x3AC
#define FLAG_HIDE_UNUSED_0x3AD                                       0x3AD
#define FLAG_HIDE_UNUSED_0x3AE                                       0x3AE
#define FLAG_HIDE_UNUSED_0x3AF                                       0x3AF
#define FLAG_HIDE_UNUSED_0x3B0                                       0x3B0
#define FLAG_HIDE_UNUSED_0x3B1                                       0x3B1
#define FLAG_HIDE_UNUSED_0x3B2                                       0x3B2
#define FLAG_HIDE_UNUSED_0x3B3                                       0x3B3
#define FLAG_HIDE_UNUSED_0x3B4                                       0x3B4
#define FLAG_HIDE_UNUSED_0x3B5                                       0x3B5
#define FLAG_HIDE_UNUSED_0x3B6                                       0x3B6
#define FLAG_HIDE_UNUSED_0x3B7                                       0x3B7
#define FLAG_HIDE_UNUSED_0x3B8                                       0x3B8
#define FLAG_HIDE_UNUSED_0x3B9                                       0x3B9
#define FLAG_HIDE_UNUSED_0x3BA                                       0x3BA
#define FLAG_HIDE_UNUSED_0x3BB                                       0x3BB
#define FLAG_HIDE_UNUSED_0x3BC                                       0x3BC
#define FLAG_HIDE_UNUSED_0x3BD                                       0x3BD
#define FLAG_HIDE_UNUSED_0x3BE                                       0x3BE
#define FLAG_HIDE_UNUSED_0x3BF                                       0x3BF
#define FLAG_HIDE_UNUSED_0x3C0                                       0x3C0
#define FLAG_HIDE_UNUSED_0x3C1                                       0x3C1
#define FLAG_HIDE_UNUSED_0x3C2                                       0x3C2
#define FLAG_HIDE_UNUSED_0x3C3                                       0x3C3
#define FLAG_HIDE_UNUSED_0x3C4                                       0x3C4
#define FLAG_HIDE_UNUSED_0x3C5                                       0x3C5
#define FLAG_HIDE_UNUSED_0x3C6                                       0x3C6
#define FLAG_HIDE_UNUSED_0x3C7                                       0x3C7
#define FLAG_HIDE_UNUSED_0x3C8                                       0x3C8
#define FLAG_HIDE_UNUSED_0x3C9                                       0x3C9
#define FLAG_HIDE_UNUSED_0x3CA                                       0x3CA
#define FLAG_HIDE_UNUSED_0x3CB                                       0x3CB
#define FLAG_HIDE_UNUSED_0x3CC                                       0x3CC
#define FLAG_HIDE_UNUSED_0x3CD                                       0x3CD
#define FLAG_HIDE_UNUSED_0x3CE                                       0x3CE
#define FLAG_HIDE_UNUSED_0x3CF                                       0x3CF
#define FLAG_HIDE_UNUSED_0x3D0                                       0x3D0
#define FLAG_HIDE_UNUSED_0x3D1                                       0x3D1
#define FLAG_HIDE_UNUSED_0x3D2                                       0x3D2
#define FLAG_HIDE_UNUSED_0x3D3                                       0x3D3
#define FLAG_HIDE_UNUSED_0x3D4                                       0x3D4
#define FLAG_HIDE_UNUSED_0x3D5                                       0x3D5
#define FLAG_HIDE_UNUSED_0x3D6                                       0x3D6
#define FLAG_HIDE_UNUSED_0x3D7                                       0x3D7
#define FLAG_HIDE_UNUSED_0x3D8                                       0x3D8
#define FLAG_HIDE_UNUSED_0x3D9                                       0x3D9
#define FLAG_HIDE_UNUSED_0x3DA                                       0x3DA
#define FLAG_HIDE_UNUSED_0x3DB                                       0x3DB
#define FLAG_HIDE_UNUSED_0x3DC                                       0x3DC
#define FLAG_HIDE_UNUSED_0x3DD                                       0x3DD
#define FLAG_HIDE_UNUSED_0x3DE                                       0x3DE
#define FLAG_HIDE_UNUSED_0x3DF                                       0x3DF
#define FLAG_HIDE_UNUSED_0x3E0                                       0x3E0
#define FLAG_HIDE_UNUSED_0x3E1                                       0x3E1
#define FLAG_HIDE_UNUSED_0x3E2                                       0x3E2
#define FLAG_HIDE_UNUSED_0x3E3                                       0x3E3
#define FLAG_SLATEPORT_CANDY_LASS                                    0x3E4
#define FLAG_SLATEPORT_CANDY_BUGCATCHER                              0x3E5
#define FLAG_SLATEPORT_CANDY_WATTSON                                 0x3E6
#define FLAG_SLATEPORT_CANDY_NURSE                                   0x3E7

// Item Ball Flags
#define FLAG_ITEM_UNUSED_0x3E8                                      0x3E8
#define FLAG_ITEM_UNUSED_0x3E9                                      0x3E9
#define FLAG_ITEM_UNUSED_0x3EA                                      0x3EA
#define FLAG_ITEM_UNUSED_0x3EB                                      0x3EB
#define FLAG_ITEM_UNUSED_0x3EC                                      0x3EC
#define FLAG_ITEM_UNUSED_0x3ED                                      0x3ED
#define FLAG_ITEM_UNUSED_0x3EE                                      0x3EE
#define FLAG_ITEM_UNUSED_0x3EF                                      0x3EF
#define FLAG_ITEM_UNUSED_0x3F0                                      0x3F0
#define FLAG_ITEM_UNUSED_0x3F1                                      0x3F1
#define FLAG_ITEM_UNUSED_0x3F2                                      0x3F2
#define FLAG_ITEM_UNUSED_0x3F3                                      0x3F3
#define FLAG_ITEM_UNUSED_0x3F4                                      0x3F4
#define FLAG_ITEM_UNUSED_0x3F5                                      0x3F5
#define FLAG_ITEM_UNUSED_0x3F6                                      0x3F6
#define FLAG_ITEM_UNUSED_0x3F7                                      0x3F7
#define FLAG_ITEM_UNUSED_0x3F8                                      0x3F8
#define FLAG_ITEM_UNUSED_0x3F9                                      0x3F9
#define FLAG_ITEM_UNUSED_0x3FA                                      0x3FA
#define FLAG_ITEM_UNUSED_0x3FB                                      0x3FB
#define FLAG_ITEM_UNUSED_0x3FC                                      0x3FC
#define FLAG_ITEM_UNUSED_0x3FD                                      0x3FD
#define FLAG_ITEM_UNUSED_0x3FE                                      0x3FE
#define FLAG_ITEM_UNUSED_0x3FF                                      0x3FF
#define FLAG_ITEM_UNUSED_0x400                                      0x400
#define FLAG_ITEM_UNUSED_0x401                                      0x401
#define FLAG_ITEM_UNUSED_0x402                                      0x402
#define FLAG_ITEM_UNUSED_0x403                                      0x403
#define FLAG_ITEM_UNUSED_0x404                                      0x404
#define FLAG_ITEM_UNUSED_0x405                                      0x405
#define FLAG_ITEM_UNUSED_0x406                                      0x406
#define FLAG_ITEM_UNUSED_0x407                                      0x407
#define FLAG_ITEM_UNUSED_0x408                                      0x408
#define FLAG_ITEM_UNUSED_0x409                                      0x409 // Unused Flag, leftover from R/S. In Emerald this is a hidden item and uses a different flag
#define FLAG_ITEM_UNUSED_0x40A                                      0x40A
#define FLAG_ITEM_UNUSED_0x40B                                      0x40B
#define FLAG_ITEM_UNUSED_0x40C                                      0x40C
#define FLAG_ITEM_UNUSED_0x40D                                      0x40D
#define FLAG_ITEM_UNUSED_0x40E                                      0x40E
#define FLAG_ITEM_UNUSED_0x40F                                      0x40F
#define FLAG_ITEM_UNUSED_0x410                                      0x410
#define FLAG_ITEM_UNUSED_0x411                                      0x411
#define FLAG_ITEM_UNUSED_0x412                                      0x412
#define FLAG_ITEM_UNUSED_0x413                                      0x413
#define FLAG_ITEM_UNUSED_0x414                                      0x414
#define FLAG_ITEM_UNUSED_0x415                                      0x415
#define FLAG_ITEM_UNUSED_0x416                                      0x416
#define FLAG_ITEM_UNUSED_0x417                                      0x417
#define FLAG_ITEM_UNUSED_0x418                                      0x418
#define FLAG_ITEM_UNUSED_0x419                                      0x419
#define FLAG_ITEM_UNUSED_0x41A                                      0x41A
#define FLAG_ITEM_UNUSED_0x41B                                      0x41B
#define FLAG_ITEM_UNUSED_0x41C                                      0x41C
#define FLAG_ITEM_UNUSED_0x41D                                      0x41D
#define FLAG_ITEM_UNUSED_0x41E                                      0x41E
#define FLAG_ITEM_UNUSED_0x41F                                      0x41F
#define FLAG_ITEM_UNUSED_0x420                                      0x420
#define FLAG_ITEM_UNUSED_0x421                                      0x421
#define FLAG_ITEM_UNUSED_0x422                                      0x422
#define FLAG_ITEM_UNUSED_0x423                                      0x423
#define FLAG_ITEM_UNUSED_0x424                                      0x424
#define FLAG_ITEM_UNUSED_0x425                                      0x425
#define FLAG_ITEM_UNUSED_0x426                                      0x426
#define FLAG_ITEM_UNUSED_0x427                                      0x427
#define FLAG_ITEM_UNUSED_0x428                                      0x428
#define FLAG_ITEM_UNUSED_0x429                                      0x429
#define FLAG_ITEM_UNUSED_0x42A                                      0x42A
#define FLAG_ITEM_UNUSED_0x42B                                      0x42B
#define FLAG_ITEM_UNUSED_0x42C                                      0x42C
#define FLAG_ITEM_UNUSED_0x42D                                      0x42D
#define FLAG_ITEM_UNUSED_0x42E                                      0x42E
#define FLAG_ITEM_UNUSED_0x42F                                      0x42F
#define FLAG_ITEM_UNUSED_0x430                                      0x430
#define FLAG_ITEM_UNUSED_0x431                                      0x431
#define FLAG_ITEM_UNUSED_0x432                                      0x432
#define FLAG_ITEM_UNUSED_0x433                                      0x433
#define FLAG_ITEM_UNUSED_0x434                                      0x434
#define FLAG_ITEM_UNUSED_0x435                                      0x435
#define FLAG_ITEM_UNUSED_0x436                                      0x436
#define FLAG_ITEM_UNUSED_0x437                                      0x437
#define FLAG_ITEM_UNUSED_0x438                                      0x438
#define FLAG_ITEM_UNUSED_0x439                                      0x439
#define FLAG_ITEM_UNUSED_0x43A                                      0x43A
#define FLAG_ITEM_UNUSED_0x43B                                      0x43B
#define FLAG_ITEM_UNUSED_0x43C                                      0x43C
#define FLAG_ITEM_UNUSED_0x43D                                      0x43D
#define FLAG_ITEM_UNUSED_0x43E                                      0x43E
#define FLAG_ITEM_UNUSED_0x43F                                      0x43F
#define FLAG_ITEM_UNUSED_0x440                                      0x440
#define FLAG_ITEM_UNUSED_0x441                                      0x441
#define FLAG_ITEM_UNUSED_0x442                                      0x442
#define FLAG_ITEM_UNUSED_0x443                                      0x443
#define FLAG_ITEM_UNUSED_0x444                                      0x444
#define FLAG_ITEM_UNUSED_0x445                                      0x445
#define FLAG_ITEM_UNUSED_0x446                                      0x446
#define FLAG_ITEM_UNUSED_0x447                                      0x447
#define FLAG_ITEM_UNUSED_0x448                                      0x448
#define FLAG_ITEM_UNUSED_0x449                                      0x449
#define FLAG_ITEM_UNUSED_0x44A                                      0x44A
#define FLAG_ITEM_UNUSED_0x44B                                      0x44B
#define FLAG_ITEM_UNUSED_0x44C                                      0x44C
#define FLAG_ITEM_UNUSED_0x44D                                      0x44D
#define FLAG_ITEM_UNUSED_0x44E                                      0x44E
#define FLAG_ITEM_UNUSED_0x44F                                      0x44F
#define FLAG_ITEM_UNUSED_0x450                                      0x450
#define FLAG_ITEM_UNUSED_0x451                                      0x451
#define FLAG_ITEM_UNUSED_0x452                                      0x452
#define FLAG_ITEM_UNUSED_0x453                                      0x453
#define FLAG_ITEM_UNUSED_0x454                                      0x454
#define FLAG_ITEM_UNUSED_0x455                                      0x455
#define FLAG_ITEM_UNUSED_0x456                                      0x456
#define FLAG_ITEM_UNUSED_0x457                                      0x457
#define FLAG_ITEM_UNUSED_0x458                                      0x458
#define FLAG_ITEM_UNUSED_0x459                                      0x459
#define FLAG_ITEM_UNUSED_0x45A                                      0x45A
#define FLAG_ITEM_UNUSED_0x45B                                      0x45B
#define FLAG_ITEM_UNUSED_0x45C                                      0x45C
#define FLAG_ITEM_UNUSED_0x45D                                      0x45D
#define FLAG_ITEM_UNUSED_0x45E                                      0x45E
#define FLAG_ITEM_UNUSED_0x45F                                      0x45F
#define FLAG_ITEM_UNUSED_0x460                                      0x460
#define FLAG_ITEM_UNUSED_0x461                                      0x461
#define FLAG_ITEM_UNUSED_0x462                                      0x462
#define FLAG_ITEM_UNUSED_0x463                                      0x463
#define FLAG_ITEM_UNUSED_0x464                                      0x464
#define FLAG_ITEM_UNUSED_0x465                                      0x465 // Unused Flag, leftover from the Ruby Magma hideout
#define FLAG_ITEM_UNUSED_0x466                                      0x466 // Unused Flag, leftover from the Ruby Magma hideout
#define FLAG_ITEM_UNUSED_0x467                                      0x467 // Unused Flag, leftover from the Ruby Magma hideout
#define FLAG_ITEM_UNUSED_0x468                                      0x468 // Unused Flag
#define FLAG_ITEM_UNUSED_0x469                                      0x469
#define FLAG_ITEM_UNUSED_0x46A                                      0x46A
#define FLAG_ITEM_UNUSED_0x46B                                      0x46B
#define FLAG_ITEM_UNUSED_0x46C                                      0x46C
#define FLAG_ITEM_UNUSED_0x46D                                      0x46D // Unused Flag, leftover from R/S. HM08 is given to the player directly in Emerald
#define FLAG_ITEM_UNUSED_0x46E                                      0x46E
#define FLAG_ITEM_UNUSED_0x46F                                      0x46F
#define FLAG_ITEM_UNUSED_0x470                                      0x470 // Unused Flag
#define FLAG_ITEM_UNUSED_0x471                                      0x471
#define FLAG_ITEM_UNUSED_0x472                                      0x472 // Unused Flag
#define FLAG_ITEM_UNUSED_0x473                                      0x473
#define FLAG_ITEM_UNUSED_0x474                                      0x474
#define FLAG_ITEM_UNUSED_0x475                                      0x475
#define FLAG_ITEM_UNUSED_0x476                                      0x476
#define FLAG_ITEM_UNUSED_0x477                                      0x477
#define FLAG_ITEM_UNUSED_0x478                                      0x478
#define FLAG_ITEM_UNUSED_0x479                                      0x479 // Unused Flag
#define FLAG_ITEM_UNUSED_0x47A                                      0x47A
#define FLAG_ITEM_UNUSED_0x47B                                      0x47B
#define FLAG_ITEM_UNUSED_0x47C                                      0x47C
#define FLAG_ITEM_UNUSED_0x47D                                      0x47D
#define FLAG_ITEM_UNUSED_0x47E                                      0x47E
#define FLAG_ITEM_UNUSED_0x47F                                      0x47F
#define FLAG_ITEM_UNUSED_0x480                                      0x480
#define FLAG_ITEM_UNUSED_0x481                                      0x481
#define FLAG_ITEM_UNUSED_0x482                                      0x482
#define FLAG_ITEM_UNUSED_0x483                                      0x483
#define FLAG_ITEM_UNUSED_0x484                                      0x484
#define FLAG_ITEM_UNUSED_0x485                                      0x485
#define FLAG_ITEM_UNUSED_0x486                                      0x486
#define FLAG_ITEM_UNUSED_0x487                                      0x487
#define FLAG_ITEM_UNUSED_0x488                                      0x488
#define FLAG_ITEM_UNUSED_0x489                                      0x489
#define FLAG_ITEM_UNUSED_0x48A                                      0x48A
#define FLAG_ITEM_UNUSED_0x48B                                      0x48B
#define FLAG_ITEM_UNUSED_0x48C                                      0x48C
#define FLAG_ITEM_UNUSED_0x48D                                      0x48D
#define FLAG_ITEM_UNUSED_0x48E                                      0x48E
#define FLAG_ITEM_UNUSED_0x48F                                      0x48F
#define FLAG_ITEM_UNUSED_0x490                                      0x490
#define FLAG_ITEM_UNUSED_0x491                                      0x491
#define FLAG_ITEM_UNUSED_0x492                                      0x492

#define FLAG_UNUSED_0x493                                           0x493
#define FLAG_UNUSED_0x494                                           0x494
#define FLAG_UNUSED_0x495                                           0x495
#define FLAG_UNUSED_0x496                                           0x496
#define FLAG_UNUSED_0x497                                           0x497
#define FLAG_UNUSED_0x498                                           0x498
#define FLAG_UNUSED_0x499                                           0x499
#define FLAG_UNUSED_0x49A                                           0x49A
#define FLAG_UNUSED_0x49B                                           0x49B
#define FLAG_UNUSED_0x49C                                           0x49C
#define FLAG_UNUSED_0x49D                                           0x49D
#define FLAG_UNUSED_0x49E                                           0x49E
#define FLAG_UNUSED_0x49F                                           0x49F
#define FLAG_UNUSED_0x4A0                                           0x4A0
#define FLAG_UNUSED_0x4A1                                           0x4A1
#define FLAG_UNUSED_0x4A2                                           0x4A2
#define FLAG_UNUSED_0x4A3                                           0x4A3
#define FLAG_UNUSED_0x4A4                                           0x4A4
#define FLAG_UNUSED_0x4A5                                           0x4A5
#define FLAG_UNUSED_0x4A6                                           0x4A6
#define FLAG_UNUSED_0x4A7                                           0x4A7
#define FLAG_UNUSED_0x4A8                                           0x4A8
#define FLAG_UNUSED_0x4A9                                           0x4A9
#define FLAG_UNUSED_0x4AA                                           0x4AA
#define FLAG_UNUSED_0x4AB                                           0x4AB
#define FLAG_UNUSED_0x4AC                                           0x4AC
#define FLAG_UNUSED_0x4AD                                           0x4AD
#define FLAG_UNUSED_0x4AE                                           0x4AE
#define FLAG_UNUSED_0x4AF                                           0x4AF
#define FLAG_UNUSED_0x4B0                                           0x4B0
#define FLAG_UNUSED_0x4B1                                           0x4B1
#define FLAG_UNUSED_0x4B2                                           0x4B2
#define FLAG_UNUSED_0x4B3                                           0x4B3
#define FLAG_UNUSED_0x4B4                                           0x4B4
#define FLAG_UNUSED_0x4B5                                           0x4B5
#define FLAG_UNUSED_0x4B6                                           0x4B6
#define FLAG_UNUSED_0x4B7                                           0x4B7
#define FLAG_UNUSED_0x4B8                                           0x4B8
#define FLAG_UNUSED_0x4B9                                           0x4B9
#define FLAG_UNUSED_0x4BA                                           0x4BA
#define FLAG_UNUSED_0x4BB                                           0x4BB
#define FLAG_UNUSED_0x4BC                                           0x4BC
#define FLAG_UNUSED_0x4BD                                           0x4BD
#define FLAG_UNUSED_0x4BE                                           0x4BE
#define FLAG_UNUSED_0x4BF                                           0x4BF
#define FLAG_UNUSED_0x4C0                                           0x4C0
#define FLAG_UNUSED_0x4C1                                           0x4C1
#define FLAG_UNUSED_0x4C2                                           0x4C2
#define FLAG_UNUSED_0x4C3                                           0x4C3
#define FLAG_UNUSED_0x4C4                                           0x4C4
#define FLAG_UNUSED_0x4C5                                           0x4C5
#define FLAG_UNUSED_0x4C6                                           0x4C6
#define FLAG_UNUSED_0x4C7                                           0x4C7
#define FLAG_UNUSED_0x4C8                                           0x4C8
#define FLAG_UNUSED_0x4C9                                           0x4C9
#define FLAG_UNUSED_0x4CA                                           0x4CA
#define FLAG_UNUSED_0x4CB                                           0x4CB
#define FLAG_UNUSED_0x4CC                                           0x4CC
#define FLAG_UNUSED_0x4CD                                           0x4CD
#define FLAG_UNUSED_0x4CE                                           0x4CE
#define FLAG_UNUSED_0x4CF                                           0x4CF
#define FLAG_UNUSED_0x4D0                                           0x4D0
#define FLAG_UNUSED_0x4D1                                           0x4D1
#define FLAG_UNUSED_0x4D2                                           0x4D2
#define FLAG_UNUSED_0x4D3                                           0x4D3
#define FLAG_UNUSED_0x4D4                                           0x4D4
#define FLAG_UNUSED_0x4D5                                           0x4D5
#define FLAG_UNUSED_0x4D6                                           0x4D6
#define FLAG_UNUSED_0x4D7                                           0x4D7
#define FLAG_UNUSED_0x4D8                                           0x4D8
#define FLAG_UNUSED_0x4D9                                           0x4D9
#define FLAG_UNUSED_0x4DA                                           0x4DA
#define FLAG_UNUSED_0x4DB                                           0x4DB
#define FLAG_UNUSED_0x4DC                                           0x4DC
#define FLAG_UNUSED_0x4DD                                           0x4DD
#define FLAG_HIDE_BATTLE_TOWER_REPORTER                             0x4DE // Chopping block
#define FLAG_HIDE_UNION_ROOM_PLAYER_1                               0x4DF // Chopping block
#define FLAG_HIDE_UNION_ROOM_PLAYER_2                               0x4E0 // Chopping block
#define FLAG_HIDE_UNION_ROOM_PLAYER_3                               0x4E1 // Chopping block
#define FLAG_HIDE_UNION_ROOM_PLAYER_4                               0x4E2 // Chopping block
#define FLAG_HIDE_UNION_ROOM_PLAYER_5                               0x4E3 // Chopping block
#define FLAG_HIDE_UNION_ROOM_PLAYER_6                               0x4E4 // Chopping block
#define FLAG_HIDE_UNION_ROOM_PLAYER_7                               0x4E5 // Chopping block
#define FLAG_HIDE_UNION_ROOM_PLAYER_8                               0x4E6 // Chopping block
#define FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_1               0x4E7 // Chopping block
#define FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_2               0x4E8 // Chopping block
#define FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_3               0x4E9 // Chopping block
#define FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_4               0x4EA // Chopping block
#define FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_5               0x4EB // Chopping block
#define FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_6               0x4EC // Chopping block
#define FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_ALT_1           0x4ED // Chopping block
#define FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_ALT_2           0x4EE // Chopping block
#define FLAG_HIDE_LILYCOVE_CONTEST_HALL_BLEND_MASTER                0x4EF // Chopping block

#define FLAG_DEFEATED_RUSTBORO_GYM                                  0x4F0
#define FLAG_DEFEATED_DEWFORD_GYM                                   0x4F1
#define FLAG_DEFEATED_MAUVILLE_GYM                                  0x4F2
#define FLAG_DEFEATED_LAVARIDGE_GYM                                 0x4F3
#define FLAG_DEFEATED_PETALBURG_GYM                                 0x4F4
#define FLAG_DEFEATED_FORTREE_GYM                                   0x4F5
#define FLAG_DEFEATED_MOSSDEEP_GYM                                  0x4F6
#define FLAG_DEFEATED_SOOTOPOLIS_GYM                                0x4F7
#define FLAG_DEFEATED_METEOR_FALLS_STEVEN                           0x4F8

#define FLAG_UNUSED_0x4F9                                           0x4F9 // Unused Flag
#define FLAG_UNUSED_0x4FA                                           0x4FA // Unused Flag

#define FLAG_DEFEATED_ELITE_4_SIDNEY                                0x4FB
#define FLAG_DEFEATED_ELITE_4_PHOEBE                                0x4FC
#define FLAG_DEFEATED_ELITE_4_GLACIA                                0x4FD
#define FLAG_DEFEATED_ELITE_4_DRAKE                                 0x4FE

#define FLAG_UNUSED_0x4FF                                           0x4FF // Unused Flag

// Trainer Flags
// Trainer flags occupy 0x500 - 0x85F, the last 9 of which are unused
// See constants/opponents.h. The values there + FLAG_TRAINER_FLAG_START are the flag IDs

#define TRAINER_FLAGS_START                                         0x500
#define TRAINER_FLAGS_END                                           (TRAINER_FLAGS_START + MAX_TRAINERS_COUNT - 1) // 0x85F

// System Flags

#define SYSTEM_FLAGS                                   (TRAINER_FLAGS_END + 1) // 0x860

#define FLAG_SYS_POKEMON_GET                           (SYSTEM_FLAGS + 0x0) // FLAG_0x860
#define FLAG_SYS_POKEDEX_GET                           (SYSTEM_FLAGS + 0x1)
#define FLAG_SYS_POKENAV_GET                           (SYSTEM_FLAGS + 0x2)
#define FLAG_SYS_UNUSED_0x03                           (SYSTEM_FLAGS + 0x3)
#define FLAG_SYS_GAME_CLEAR                            (SYSTEM_FLAGS + 0x4)
#define FLAG_SYS_CHAT_USED                             (SYSTEM_FLAGS + 0x5)
#define FLAG_SYS_HIPSTER_MEET                          (SYSTEM_FLAGS + 0x6)

// Badges
#define FLAG_BADGE01_GET                               (SYSTEM_FLAGS + 0x7)
#define FLAG_BADGE02_GET                               (SYSTEM_FLAGS + 0x8)
#define FLAG_BADGE03_GET                               (SYSTEM_FLAGS + 0x9)
#define FLAG_BADGE04_GET                               (SYSTEM_FLAGS + 0xA)
#define FLAG_BADGE05_GET                               (SYSTEM_FLAGS + 0xB)
#define FLAG_BADGE06_GET                               (SYSTEM_FLAGS + 0xC)
#define FLAG_BADGE07_GET                               (SYSTEM_FLAGS + 0xD)
#define FLAG_BADGE08_GET                               (SYSTEM_FLAGS + 0xE)
#define NUM_BADGES                                     (1 + FLAG_BADGE08_GET - FLAG_BADGE01_GET)

// Towns and Cities
#define FLAG_VISITED_LITTLEROOT_TOWN                (SYSTEM_FLAGS + 0xF)
#define FLAG_VISITED_OLDALE_TOWN                    (SYSTEM_FLAGS + 0x10)
#define FLAG_VISITED_DEWFORD_TOWN                   (SYSTEM_FLAGS + 0x11)
#define FLAG_VISITED_LAVARIDGE_TOWN                 (SYSTEM_FLAGS + 0x12)
#define FLAG_VISITED_FALLARBOR_TOWN                 (SYSTEM_FLAGS + 0x13)
#define FLAG_VISITED_VERDANTURF_TOWN                (SYSTEM_FLAGS + 0x14)
#define FLAG_VISITED_PACIFIDLOG_TOWN                (SYSTEM_FLAGS + 0x15)
#define FLAG_VISITED_PETALBURG_CITY                 (SYSTEM_FLAGS + 0x16)
#define FLAG_VISITED_SLATEPORT_CITY                 (SYSTEM_FLAGS + 0x17)
#define FLAG_VISITED_MAUVILLE_CITY                  (SYSTEM_FLAGS + 0x18)
#define FLAG_VISITED_RUSTBORO_CITY                  (SYSTEM_FLAGS + 0x19)
#define FLAG_VISITED_FORTREE_CITY                   (SYSTEM_FLAGS + 0x1A)
#define FLAG_VISITED_LILYCOVE_CITY                  (SYSTEM_FLAGS + 0x1B)
#define FLAG_VISITED_MOSSDEEP_CITY                  (SYSTEM_FLAGS + 0x1C)
#define FLAG_VISITED_SOOTOPOLIS_CITY                (SYSTEM_FLAGS + 0x1D)
#define FLAG_VISITED_EVER_GRANDE_CITY               (SYSTEM_FLAGS + 0x1E)
#define FLAG_IS_CHAMPION                            (SYSTEM_FLAGS + 0x1F)
#define FLAG_NURSE_UNION_ROOM_REMINDER              (SYSTEM_FLAGS + 0x20)
#define FLAG_PENDING_DAYCARE_EGG                    (SYSTEM_FLAGS + 0x21)
#define FLAG_RECEIVED_SECRET_POWER                  (SYSTEM_FLAGS + 0x22)
#define FLAG_RECEIVED_POKEBLOCK_CASE                (SYSTEM_FLAGS + 0x23)
#define FLAG_SYS_RANDOM_DISABLED                    (SYSTEM_FLAGS + 0x24) // TTH
#define FLAG_SYS_FAST_BONK                          (SYSTEM_FLAGS + 0x25) // TTH
#define FLAG_SYS_KEEP_OBJECTS_WITHIN_MAP            (SYSTEM_FLAGS + 0x26) // TTH, Disables object template loading as long as the destination warp is within the same map
#define FLAG_SYS_UNUSED_0x27                        (SYSTEM_FLAGS + 0x27)
#define FLAG_SYS_USE_FLASH                          (SYSTEM_FLAGS + 0x28)
#define FLAG_SYS_USE_STRENGTH                       (SYSTEM_FLAGS + 0x29)
#define FLAG_SYS_WEATHER_CTRL                       (SYSTEM_FLAGS + 0x2A)
#define FLAG_SYS_CYCLING_ROAD                       (SYSTEM_FLAGS + 0x2B)
#define FLAG_SYS_SAFARI_MODE                        (SYSTEM_FLAGS + 0x2C)
#define FLAG_SYS_CRUISE_MODE                        (SYSTEM_FLAGS + 0x2D)
#define FLAG_SYS_BORT_MODE                          (SYSTEM_FLAGS + 0x2E) // TTH, Should use the Elf battle strings table
#define FLAG_SYS_DISABLE_FORCED_TRIGGER             (SYSTEM_FLAGS + 0x2F) // Unused Flag
#define FLAG_SYS_TV_HOME                            (SYSTEM_FLAGS + 0x30)
#define FLAG_SYS_TV_WATCH                           (SYSTEM_FLAGS + 0x31)
#define FLAG_SYS_TV_START                           (SYSTEM_FLAGS + 0x32)
#define FLAG_SYS_CHANGED_DEWFORD_TREND              (SYSTEM_FLAGS + 0x33)
#define FLAG_SYS_MIX_RECORD                         (SYSTEM_FLAGS + 0x34)
#define FLAG_SYS_CLOCK_SET                          (SYSTEM_FLAGS + 0x35)
#define FLAG_SYS_NATIONAL_DEX                       (SYSTEM_FLAGS + 0x36)
#define FLAG_SYS_UNUSED_0x37                        (SYSTEM_FLAGS + 0x37)
#define FLAG_SYS_UNUSED_0x38                        (SYSTEM_FLAGS + 0x38)
#define FLAG_SYS_UNUSED_0x39                        (SYSTEM_FLAGS + 0x39)
#define FLAG_SYS_UNUSED_0x3A                        (SYSTEM_FLAGS + 0x3A)
#define FLAG_SYS_RIBBON_GET                         (SYSTEM_FLAGS + 0x3B)
#define FLAG_LANDMARK_FLOWER_SHOP                   (SYSTEM_FLAGS + 0x3C)
#define FLAG_LANDMARK_MR_BRINEY_HOUSE               (SYSTEM_FLAGS + 0x3D)
#define FLAG_LANDMARK_ABANDONED_SHIP                (SYSTEM_FLAGS + 0x3E)
#define FLAG_LANDMARK_SEASHORE_HOUSE                (SYSTEM_FLAGS + 0x3F)
#define FLAG_LANDMARK_NEW_MAUVILLE                  (SYSTEM_FLAGS + 0x40)
#define FLAG_LANDMARK_OLD_LADY_REST_SHOP            (SYSTEM_FLAGS + 0x41)
#define FLAG_LANDMARK_TRICK_HOUSE                   (SYSTEM_FLAGS + 0x42)
#define FLAG_LANDMARK_WINSTRATE_FAMILY              (SYSTEM_FLAGS + 0x43)
#define FLAG_LANDMARK_GLASS_WORKSHOP                (SYSTEM_FLAGS + 0x44)
#define FLAG_LANDMARK_LANETTES_HOUSE                (SYSTEM_FLAGS + 0x45)
#define FLAG_LANDMARK_POKEMON_DAYCARE               (SYSTEM_FLAGS + 0x46)
#define FLAG_LANDMARK_SEAFLOOR_CAVERN               (SYSTEM_FLAGS + 0x47)
#define FLAG_LANDMARK_BATTLE_FRONTIER               (SYSTEM_FLAGS + 0x48)
#define FLAG_LANDMARK_SOUTHERN_ISLAND               (SYSTEM_FLAGS + 0x49)
#define FLAG_LANDMARK_FIERY_PATH                    (SYSTEM_FLAGS + 0x4A)
#define FLAG_SYS_PC_LANETTE                         (SYSTEM_FLAGS + 0x4B)
#define FLAG_SYS_MYSTERY_EVENT_ENABLE               (SYSTEM_FLAGS + 0x4C)
#define FLAG_SYS_ENC_UP_ITEM                        (SYSTEM_FLAGS + 0x4D)
#define FLAG_SYS_ENC_DOWN_ITEM                      (SYSTEM_FLAGS + 0x4E)
#define FLAG_SYS_BRAILLE_DIG                        (SYSTEM_FLAGS + 0x4F)
#define FLAG_SYS_REGIROCK_PUZZLE_COMPLETED          (SYSTEM_FLAGS + 0x50)
#define FLAG_SYS_BRAILLE_REGICE_COMPLETED           (SYSTEM_FLAGS + 0x51)
#define FLAG_SYS_REGISTEEL_PUZZLE_COMPLETED         (SYSTEM_FLAGS + 0x52)
#define FLAG_ENABLE_SHIP_SOUTHERN_ISLAND            (SYSTEM_FLAGS + 0x53)
#define FLAG_LANDMARK_POKEMON_LEAGUE                (SYSTEM_FLAGS + 0x54)
#define FLAG_LANDMARK_ISLAND_CAVE                   (SYSTEM_FLAGS + 0x55)
#define FLAG_LANDMARK_DESERT_RUINS                  (SYSTEM_FLAGS + 0x56)
#define FLAG_LANDMARK_FOSSIL_MANIACS_HOUSE          (SYSTEM_FLAGS + 0x57)
#define FLAG_LANDMARK_SCORCHED_SLAB                 (SYSTEM_FLAGS + 0x58)
#define FLAG_LANDMARK_ANCIENT_TOMB                  (SYSTEM_FLAGS + 0x59)
#define FLAG_LANDMARK_TUNNELERS_REST_HOUSE          (SYSTEM_FLAGS + 0x5A)
#define FLAG_LANDMARK_HUNTERS_HOUSE                 (SYSTEM_FLAGS + 0x5B)
#define FLAG_LANDMARK_SEALED_CHAMBER                (SYSTEM_FLAGS + 0x5C)
#define FLAG_SYS_TV_LATIAS_LATIOS                   (SYSTEM_FLAGS + 0x5D)
#define FLAG_LANDMARK_SKY_PILLAR                    (SYSTEM_FLAGS + 0x5E)
#define FLAG_SYS_SHOAL_ITEM                         (SYSTEM_FLAGS + 0x5F)
#define FLAG_SYS_B_DASH                             (SYSTEM_FLAGS + 0x60) // RECEIVED Running Shoes
#define FLAG_SYS_CTRL_OBJ_DELETE                    (SYSTEM_FLAGS + 0x61)
#define FLAG_SYS_RESET_RTC_ENABLE                   (SYSTEM_FLAGS + 0x62)
#define FLAG_LANDMARK_BERRY_MASTERS_HOUSE           (SYSTEM_FLAGS + 0x63)
#define FLAG_SYS_TOWER_SILVER                       (SYSTEM_FLAGS + 0x64) // Frontier-related, chopping block
#define FLAG_SYS_TOWER_GOLD                         (SYSTEM_FLAGS + 0x65) // Frontier-related, chopping block
#define FLAG_SYS_DOME_SILVER                        (SYSTEM_FLAGS + 0x66) // Frontier-related, chopping block
#define FLAG_SYS_DOME_GOLD                          (SYSTEM_FLAGS + 0x67) // Frontier-related, chopping block
#define FLAG_SYS_PALACE_SILVER                      (SYSTEM_FLAGS + 0x68) // Frontier-related, chopping block
#define FLAG_SYS_PALACE_GOLD                        (SYSTEM_FLAGS + 0x69) // Frontier-related, chopping block
#define FLAG_SYS_ARENA_SILVER                       (SYSTEM_FLAGS + 0x6A) // Frontier-related, chopping block
#define FLAG_SYS_ARENA_GOLD                         (SYSTEM_FLAGS + 0x6B) // Frontier-related, chopping block
#define FLAG_SYS_FACTORY_SILVER                     (SYSTEM_FLAGS + 0x6C) // Frontier-related, chopping block
#define FLAG_SYS_FACTORY_GOLD                       (SYSTEM_FLAGS + 0x6D) // Frontier-related, chopping block
#define FLAG_SYS_PIKE_SILVER                        (SYSTEM_FLAGS + 0x6E) // Frontier-related, chopping block
#define FLAG_SYS_PIKE_GOLD                          (SYSTEM_FLAGS + 0x6F) // Frontier-related, chopping block
#define FLAG_SYS_PYRAMID_SILVER                     (SYSTEM_FLAGS + 0x70) // Frontier-related, chopping block
#define FLAG_SYS_PYRAMID_GOLD                       (SYSTEM_FLAGS + 0x71) // Frontier-related, chopping block
#define FLAG_SYS_FRONTIER_PASS                      (SYSTEM_FLAGS + 0x72) // Frontier-related, chopping block
#define FLAG_MAP_SCRIPT_CHECKED_DEOXYS              (SYSTEM_FLAGS + 0x73)
#define FLAG_DEOXYS_ROCK_COMPLETE                   (SYSTEM_FLAGS + 0x74)
#define FLAG_ENABLE_SHIP_BIRTH_ISLAND               (SYSTEM_FLAGS + 0x75)
#define FLAG_ENABLE_SHIP_FARAWAY_ISLAND             (SYSTEM_FLAGS + 0x76)
#define FLAG_SHOWN_BOX_WAS_FULL_MESSAGE             (SYSTEM_FLAGS + 0x77)
#define FLAG_ARRIVED_ON_FARAWAY_ISLAND              (SYSTEM_FLAGS + 0x78)
#define FLAG_ARRIVED_AT_MARINE_CAVE_EMERGE_SPOT     (SYSTEM_FLAGS + 0x79)
#define FLAG_ARRIVED_AT_TERRA_CAVE_ENTRANCE         (SYSTEM_FLAGS + 0x7A)
#define FLAG_SYS_MYSTERY_GIFT_ENABLE                (SYSTEM_FLAGS + 0x7B)
#define FLAG_ENTERED_MIRAGE_TOWER                   (SYSTEM_FLAGS + 0x7C)
#define FLAG_LANDMARK_ALTERING_CAVE                 (SYSTEM_FLAGS + 0x7D)
#define FLAG_LANDMARK_DESERT_UNDERPASS              (SYSTEM_FLAGS + 0x7E)
#define FLAG_LANDMARK_ARTISAN_CAVE                  (SYSTEM_FLAGS + 0x7F)
#define FLAG_ENABLE_SHIP_NAVEL_ROCK                 (SYSTEM_FLAGS + 0x80)
#define FLAG_ARRIVED_AT_NAVEL_ROCK                  (SYSTEM_FLAGS + 0x81)
#define FLAG_LANDMARK_TRAINER_HILL                  (SYSTEM_FLAGS + 0x82)
#define FLAG_UNUSED_0x8E3                           (SYSTEM_FLAGS + 0x83) // Unused Flag
#define FLAG_RECEIVED_POKEDEX_FROM_BIRCH            (SYSTEM_FLAGS + 0x84)
#define FLAG_UNUSED_0x8E5                           (SYSTEM_FLAGS + 0x85) // Unused Flag
#define FLAG_UNUSED_0x8E6                           (SYSTEM_FLAGS + 0x86) // Unused Flag
#define FLAG_UNUSED_0x8E7                           (SYSTEM_FLAGS + 0x87) // Unused Flag
#define FLAG_UNUSED_0x8E8                           (SYSTEM_FLAGS + 0x88) // Unused Flag
#define FLAG_UNUSED_0x8E9                           (SYSTEM_FLAGS + 0x89) // Unused Flag
#define FLAG_UNUSED_0x8EA                           (SYSTEM_FLAGS + 0x8A) // Unused Flag
#define FLAG_UNUSED_0x8EB                           (SYSTEM_FLAGS + 0x8B) // Unused Flag
#define FLAG_UNUSED_0x8EC                           (SYSTEM_FLAGS + 0x8C) // Unused Flag
#define FLAG_UNUSED_0x8ED                           (SYSTEM_FLAGS + 0x8D) // Unused Flag
#define FLAG_UNUSED_0x8EE                           (SYSTEM_FLAGS + 0x8E) // Unused Flag
#define FLAG_UNUSED_0x8EF                           (SYSTEM_FLAGS + 0x8F) // Unused Flag
#define FLAG_UNUSED_0x8F0                           (SYSTEM_FLAGS + 0x90) // Unused Flag
#define FLAG_UNUSED_0x8F1                           (SYSTEM_FLAGS + 0x91) // Unused Flag
#define FLAG_UNUSED_0x8F2                           (SYSTEM_FLAGS + 0x92) // Unused Flag
#define FLAG_UNUSED_0x8F3                           (SYSTEM_FLAGS + 0x93) // Unused Flag
#define FLAG_UNUSED_0x8F4                           (SYSTEM_FLAGS + 0x94) // Unused Flag
#define FLAG_UNUSED_0x8F5                           (SYSTEM_FLAGS + 0x95) // Unused Flag
#define FLAG_UNUSED_0x8F6                           (SYSTEM_FLAGS + 0x96) // Unused Flag
#define FLAG_UNUSED_0x8F7                           (SYSTEM_FLAGS + 0x97) // Unused Flag
#define FLAG_UNUSED_0x8F8                           (SYSTEM_FLAGS + 0x98) // Unused Flag
#define FLAG_UNUSED_0x8F9                           (SYSTEM_FLAGS + 0x99) // Unused Flag
#define FLAG_UNUSED_0x8FA                           (SYSTEM_FLAGS + 0x9A) // Unused Flag
#define FLAG_UNUSED_0x8FB                           (SYSTEM_FLAGS + 0x9B) // Unused Flag
#define FLAG_UNUSED_0x8FC                           (SYSTEM_FLAGS + 0x9C) // Unused Flag
#define FLAG_UNUSED_0x8FD                           (SYSTEM_FLAGS + 0x9D) // Unused Flag
#define FLAG_UNUSED_0x8FE                           (SYSTEM_FLAGS + 0x9E) // Unused Flag
#define FLAG_UNUSED_0x8FF                           (SYSTEM_FLAGS + 0x9F) // Unused Flag
#define FLAG_UNUSED_0x900                           (SYSTEM_FLAGS + 0xA0) // Unused Flag
#define FLAG_UNUSED_0x901                           (SYSTEM_FLAGS + 0xA1) // Unused Flag
#define FLAG_UNUSED_0x902                           (SYSTEM_FLAGS + 0xA2) // Unused Flag
#define FLAG_UNUSED_0x903                           (SYSTEM_FLAGS + 0xA3) // Unused Flag
#define FLAG_UNUSED_0x904                           (SYSTEM_FLAGS + 0xA4) // Unused Flag
#define FLAG_UNUSED_0x905                           (SYSTEM_FLAGS + 0xA5) // Unused Flag
#define FLAG_UNUSED_0x906                           (SYSTEM_FLAGS + 0xA6) // Unused Flag
#define FLAG_UNUSED_0x907                           (SYSTEM_FLAGS + 0xA7) // Unused Flag
#define FLAG_UNUSED_0x908                           (SYSTEM_FLAGS + 0xA8) // Unused Flag
#define FLAG_UNUSED_0x909                           (SYSTEM_FLAGS + 0xA9) // Unused Flag
#define FLAG_UNUSED_0x90A                           (SYSTEM_FLAGS + 0xAA) // Unused Flag
#define FLAG_UNUSED_0x90B                           (SYSTEM_FLAGS + 0xAB) // Unused Flag
#define FLAG_UNUSED_0x90C                           (SYSTEM_FLAGS + 0xAC) // Unused Flag
#define FLAG_UNUSED_0x90D                           (SYSTEM_FLAGS + 0xAD) // Unused Flag
#define FLAG_UNUSED_0x90E                           (SYSTEM_FLAGS + 0xAE) // Unused Flag
#define FLAG_UNUSED_0x90F                           (SYSTEM_FLAGS + 0xAF) // Unused Flag
#define FLAG_UNUSED_0x910                           (SYSTEM_FLAGS + 0xB0) // Unused Flag
#define FLAG_UNUSED_0x911                           (SYSTEM_FLAGS + 0xB1) // Unused Flag
#define FLAG_UNUSED_0x912                           (SYSTEM_FLAGS + 0xB2) // Unused Flag
#define FLAG_UNUSED_0x913                           (SYSTEM_FLAGS + 0xB3) // Unused Flag
#define FLAG_UNUSED_0x914                           (SYSTEM_FLAGS + 0xB4) // Unused Flag
#define FLAG_UNUSED_0x915                           (SYSTEM_FLAGS + 0xB5) // Unused Flag
#define FLAG_UNUSED_0x916                           (SYSTEM_FLAGS + 0xB6) // Unused Flag
#define FLAG_UNUSED_0x917                           (SYSTEM_FLAGS + 0xB7) // Unused Flag
#define FLAG_UNUSED_0x918                           (SYSTEM_FLAGS + 0xB8) // Unused Flag
#define FLAG_UNUSED_0x919                           (SYSTEM_FLAGS + 0xB9) // Unused Flag
#define FLAG_UNUSED_0x91A                           (SYSTEM_FLAGS + 0xBA) // Unused Flag
#define FLAG_UNUSED_0x91B                           (SYSTEM_FLAGS + 0xBB) // Unused Flag
#define FLAG_UNUSED_0x91C                           (SYSTEM_FLAGS + 0xBC) // Unused Flag
#define FLAG_UNUSED_0x91D                           (SYSTEM_FLAGS + 0xBD) // Unused Flag
#define FLAG_UNUSED_0x91E                           (SYSTEM_FLAGS + 0xBE) // Unused Flag
#define FLAG_UNUSED_0x91F                           (SYSTEM_FLAGS + 0xBF) // Unused Flag

// Daily Flags
// These flags are cleared once per day
// The start and end are byte-aligned because the flags are cleared in byte increments
#define DAILY_FLAGS_START                           (FLAG_UNUSED_0x91F + (8 - FLAG_UNUSED_0x91F % 8))
#define FLAG_UNUSED_0x920                           (DAILY_FLAGS_START + 0x0)  // Unused Flag
#define FLAG_DAILY_CONTEST_LOBBY_RECEIVED_BERRY     (DAILY_FLAGS_START + 0x1)
#define FLAG_DAILY_SECRET_BASE                      (DAILY_FLAGS_START + 0x2)
#define FLAG_DAILY_UNUSED_0x923                     (DAILY_FLAGS_START + 0x3)
#define FLAG_DAILY_UNUSED_0x924                     (DAILY_FLAGS_START + 0x4)
#define FLAG_DAILY_UNUSED_0x925                     (DAILY_FLAGS_START + 0x5)
#define FLAG_DAILY_UNUSED_0x926                     (DAILY_FLAGS_START + 0x6)
#define FLAG_DAILY_UNUSED_0x927                     (DAILY_FLAGS_START + 0x7)
#define FLAG_DAILY_UNUSED_0x928                     (DAILY_FLAGS_START + 0x8)
#define FLAG_DAILY_UNUSED_0x929                     (DAILY_FLAGS_START + 0x9)
#define FLAG_DAILY_UNUSED_0x92A                     (DAILY_FLAGS_START + 0xA)
#define FLAG_DAILY_UNUSED_0x92B                     (DAILY_FLAGS_START + 0xB)
#define FLAG_DAILY_UNUSED_0x92C                     (DAILY_FLAGS_START + 0xC)
#define FLAG_DAILY_UNUSED_0x92D                     (DAILY_FLAGS_START + 0xD)
#define FLAG_DAILY_UNUSED_0x92E                     (DAILY_FLAGS_START + 0xE)
#define FLAG_DAILY_UNUSED_0x92F                     (DAILY_FLAGS_START + 0xF)
#define FLAG_DAILY_UNUSED_0x930                     (DAILY_FLAGS_START + 0x10)
#define FLAG_DAILY_UNUSED_0x931                     (DAILY_FLAGS_START + 0x11)
#define FLAG_DAILY_UNUSED_0x932                     (DAILY_FLAGS_START + 0x12)
#define FLAG_DAILY_UNUSED_0x933                     (DAILY_FLAGS_START + 0x13)
#define FLAG_DAILY_UNUSED_0x934                     (DAILY_FLAGS_START + 0x14)

#define FLAG_DAILY_UNUSED_0x935                     (DAILY_FLAGS_START + 0x15)
#define FLAG_DAILY_UNUSED_0x936                     (DAILY_FLAGS_START + 0x16)
#define FLAG_DAILY_UNUSED_0x937                     (DAILY_FLAGS_START + 0x17)
#define FLAG_DAILY_UNUSED_0x938                     (DAILY_FLAGS_START + 0x18)
#define FLAG_DAILY_UNUSED_0x939                     (DAILY_FLAGS_START + 0x19)
#define FLAG_DAILY_UNUSED_0x93A                     (DAILY_FLAGS_START + 0x1A)
#define FLAG_DAILY_UNUSED_0x93B                     (DAILY_FLAGS_START + 0x1B)
#define FLAG_DAILY_UNUSED_0x93C                     (DAILY_FLAGS_START + 0x1C)
#define FLAG_DAILY_UNUSED_0x93D                     (DAILY_FLAGS_START + 0x1D)
#define FLAG_DAILY_UNUSED_0x93E                     (DAILY_FLAGS_START + 0x1E)
#define FLAG_DAILY_UNUSED_0x93F                     (DAILY_FLAGS_START + 0x1F)
#define FLAG_DAILY_UNUSED_0x940                     (DAILY_FLAGS_START + 0x20)
#define FLAG_DAILY_UNUSED_0x941                     (DAILY_FLAGS_START + 0x21)
#define FLAG_DAILY_UNUSED_0x942                     (DAILY_FLAGS_START + 0x22)
#define FLAG_DAILY_UNUSED_0x943                     (DAILY_FLAGS_START + 0x23)
#define FLAG_DAILY_UNUSED_0x944                     (DAILY_FLAGS_START + 0x24)
#define FLAG_DAILY_UNUSED_0x945                     (DAILY_FLAGS_START + 0x25)
#define FLAG_DAILY_UNUSED_0x946                     (DAILY_FLAGS_START + 0x26)
#define FLAG_DAILY_UNUSED_0x947                     (DAILY_FLAGS_START + 0x27)
#define FLAG_DAILY_UNUSED_0x948                     (DAILY_FLAGS_START + 0x28)
#define FLAG_DAILY_UNUSED_0x949                     (DAILY_FLAGS_START + 0x29)
#define FLAG_DAILY_UNUSED_0x94A                     (DAILY_FLAGS_START + 0x2A)
#define FLAG_DAILY_UNUSED_0x94B                     (DAILY_FLAGS_START + 0x2B)
#define FLAG_DAILY_UNUSED_0x94C                     (DAILY_FLAGS_START + 0x2C)
#define FLAG_DAILY_UNUSED_0x94D                     (DAILY_FLAGS_START + 0x2D)
#define FLAG_DAILY_UNUSED_0x94E                     (DAILY_FLAGS_START + 0x2E)
#define FLAG_DAILY_UNUSED_0x94F                     (DAILY_FLAGS_START + 0x2F)
#define FLAG_DAILY_UNUSED_0x950                     (DAILY_FLAGS_START + 0x30)
#define FLAG_DAILY_UNUSED_0x951                     (DAILY_FLAGS_START + 0x31)
#define FLAG_DAILY_UNUSED_0x952                     (DAILY_FLAGS_START + 0x32)
#define FLAG_DAILY_UNUSED_0x953                     (DAILY_FLAGS_START + 0x33)
#define FLAG_DAILY_UNUSED_0x954                     (DAILY_FLAGS_START + 0x34)
#define FLAG_DAILY_UNUSED_0x955                     (DAILY_FLAGS_START + 0x35)
#define FLAG_DAILY_UNUSED_0x956                     (DAILY_FLAGS_START + 0x36)
#define FLAG_DAILY_UNUSED_0x957                     (DAILY_FLAGS_START + 0x37)
#define FLAG_DAILY_UNUSED_0x958                     (DAILY_FLAGS_START + 0x38)
#define FLAG_DAILY_UNUSED_0x959                     (DAILY_FLAGS_START + 0x39)
#define FLAG_DAILY_UNUSED_0x95A                     (DAILY_FLAGS_START + 0x3A)
#define FLAG_DAILY_UNUSED_0x95B                     (DAILY_FLAGS_START + 0x3B)
#define FLAG_DAILY_UNUSED_0x95C                     (DAILY_FLAGS_START + 0x3C)
#define FLAG_DAILY_UNUSED_0x95D                     (DAILY_FLAGS_START + 0x3D)
#define FLAG_DAILY_UNUSED_0x95E                     (DAILY_FLAGS_START + 0x3E)
#define FLAG_DAILY_UNUSED_0x95F                     (DAILY_FLAGS_START + 0x3F)
#define DAILY_FLAGS_END                             (FLAG_DAILY_UNUSED_0x95F + (7 - FLAG_DAILY_UNUSED_0x95F % 8))

#define FLAGS_COUNT (DAILY_FLAGS_END + 1)

// Special Flags (Stored in EWRAM (sSpecialFlags), not in the SaveBlock)
#define SPECIAL_FLAGS_START                     0x4000
#define FLAG_HIDE_MAP_NAME_POPUP                0x4000
#define FLAG_DONT_TRANSITION_MUSIC              0x4001
#define FLAG_ENABLE_MULTI_CORRIDOR_DOOR         0x4002
#define FLAG_SPECIAL_FLAG_UNUSED_0x4003         0x4003 // Unused Flag
#define FLAG_STORING_ITEMS_IN_PYRAMID_BAG       0x4004
#define FLAG_IS_BUMP_INTERACTION                0x4005
#define FLAG_IS_PUZZLE_INTRODUCED               0x4006
#define FLAG_PREVENT_EVENT_OBJECT_DESPAWN       0x4007 //Do not despawn event objects when they're off screen
#define FLAG_DISABLE_FADE_INIT                  0x4008
#define FLAG_DISABLE_MAP_MUSIC_CHANGE           0x4009
#define SPECIAL_FLAGS_END                       (SPECIAL_FLAGS_START + 0x7F)

// Candy aliases
#define FLAG_CANDY_ABUNDANT_01        FLAG_HIDDEN_ITEM_PUZZLE_0x00
#define FLAG_CANDY_ABUNDANT_02        FLAG_HIDDEN_ITEM_PUZZLE_0x01
#define FLAG_CANDY_ABUNDANT_03        FLAG_HIDDEN_ITEM_PUZZLE_0x02
#define FLAG_CANDY_ABUNDANT_04        FLAG_HIDDEN_ITEM_PUZZLE_0x03
#define FLAG_CANDY_ABUNDANT_05        FLAG_HIDDEN_ITEM_PUZZLE_0x04
#define FLAG_CANDY_ABUNDANT_06        FLAG_HIDDEN_ITEM_PUZZLE_0x05
#define FLAG_CANDY_ABUNDANT_07        FLAG_HIDDEN_ITEM_PUZZLE_0x06
#define FLAG_CANDY_ABUNDANT_08        FLAG_HIDDEN_ITEM_PUZZLE_0x07
#define FLAG_CANDY_ABUNDANT_09        FLAG_HIDDEN_ITEM_PUZZLE_0x08
#define FLAG_CANDY_ABUNDANT_10        FLAG_HIDDEN_ITEM_PUZZLE_0x09
#define FLAG_CANDY_ABUNDANT_11        FLAG_HIDDEN_ITEM_PUZZLE_0x0A
#define FLAG_CANDY_ABUNDANT_12        FLAG_HIDDEN_ITEM_PUZZLE_0x0B
#define FLAG_CANDY_COMMON_01          FLAG_HIDDEN_ITEM_PUZZLE_0x0C
#define FLAG_CANDY_COMMON_02          FLAG_HIDDEN_ITEM_PUZZLE_0x0D
#define FLAG_CANDY_COMMON_03          FLAG_HIDDEN_ITEM_PUZZLE_0x0E
#define FLAG_CANDY_COMMON_04          FLAG_HIDDEN_ITEM_PUZZLE_0x0F
#define FLAG_CANDY_COMMON_05          FLAG_HIDDEN_ITEM_PUZZLE_0x10
#define FLAG_CANDY_COMMON_06          FLAG_HIDDEN_ITEM_PUZZLE_0x11
#define FLAG_CANDY_COMMON_07          FLAG_HIDDEN_ITEM_PUZZLE_0x12
#define FLAG_CANDY_COMMON_08          FLAG_HIDDEN_ITEM_PUZZLE_0x13
#define FLAG_CANDY_UNCOMMON_01        FLAG_HIDDEN_ITEM_PUZZLE_0x14
#define FLAG_CANDY_UNCOMMON_02        FLAG_HIDDEN_ITEM_PUZZLE_0x15
#define FLAG_CANDY_UNCOMMON_03        FLAG_HIDDEN_ITEM_PUZZLE_0x16
#define FLAG_CANDY_UNCOMMON_04        FLAG_HIDDEN_ITEM_PUZZLE_0x17
#define FLAG_CANDY_UNCOMMON_05        FLAG_HIDDEN_ITEM_PUZZLE_0x18
#define FLAG_CANDY_HEALTHY_01         FLAG_HIDDEN_ITEM_PUZZLE_0x19
#define FLAG_CANDY_HEALTHY_02         FLAG_HIDDEN_ITEM_PUZZLE_0x1A
#define FLAG_CANDY_HEALTHY_03         FLAG_HIDDEN_ITEM_PUZZLE_0x1B
#define FLAG_CANDY_HEALTHY_04         FLAG_HIDDEN_ITEM_PUZZLE_0x1C
#define FLAG_CANDY_RARE_01            FLAG_HIDDEN_ITEM_PUZZLE_0x1D
#define FLAG_CANDY_RARE_02            FLAG_HIDDEN_ITEM_PUZZLE_0x1E
#define FLAG_CANDY_RARE_03            FLAG_HIDDEN_ITEM_PUZZLE_0x1F


#endif // GUARD_CONSTANTS_FLAGS_H
