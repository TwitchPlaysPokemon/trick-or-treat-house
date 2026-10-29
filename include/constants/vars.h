#ifndef GUARD_CONSTANTS_VARS_H
#define GUARD_CONSTANTS_VARS_H

#define VARS_START 0x4000

// temporary vars
// The first 0x10 vars are are temporary--they are cleared every time a map is loaded.
#define TEMP_VARS_START            0x4000
#define VAR_TEMP_0                 (TEMP_VARS_START + 0x0)
#define VAR_TEMP_1                 (TEMP_VARS_START + 0x1)
#define VAR_TEMP_2                 (TEMP_VARS_START + 0x2)
#define VAR_TEMP_3                 (TEMP_VARS_START + 0x3)
#define VAR_TEMP_4                 (TEMP_VARS_START + 0x4)
#define VAR_TEMP_5                 (TEMP_VARS_START + 0x5)
#define VAR_TEMP_6                 (TEMP_VARS_START + 0x6)
#define VAR_TEMP_7                 (TEMP_VARS_START + 0x7)
#define VAR_TEMP_8                 (TEMP_VARS_START + 0x8)
#define VAR_TEMP_9                 (TEMP_VARS_START + 0x9)
#define VAR_TEMP_A                 (TEMP_VARS_START + 0xA)
#define VAR_TEMP_B                 (TEMP_VARS_START + 0xB)
#define VAR_TEMP_C                 (TEMP_VARS_START + 0xC)
#define VAR_TEMP_D                 (TEMP_VARS_START + 0xD)
#define VAR_TEMP_E                 (TEMP_VARS_START + 0xE)
#define VAR_TEMP_F                 (TEMP_VARS_START + 0xF)
#define TEMP_VARS_END              VAR_TEMP_F

// object gfx id vars
// These 0x10 vars are used to dynamically control a map object's sprite.
// For example, the rival's sprite id is dynamically set based on the player's gender.
// See VarGetObjectEventGraphicsId().
#define VAR_OBJ_GFX_ID_0           0x4010
#define VAR_OBJ_GFX_ID_1           0x4011
#define VAR_OBJ_GFX_ID_2           0x4012
#define VAR_OBJ_GFX_ID_3           0x4013
#define VAR_OBJ_GFX_ID_4           0x4014
#define VAR_OBJ_GFX_ID_5           0x4015
#define VAR_OBJ_GFX_ID_6           0x4016
#define VAR_OBJ_GFX_ID_7           0x4017
#define VAR_OBJ_GFX_ID_8           0x4018
#define VAR_OBJ_GFX_ID_9           0x4019
#define VAR_OBJ_GFX_ID_A           0x401A
#define VAR_OBJ_GFX_ID_B           0x401B
#define VAR_OBJ_GFX_ID_C           0x401C
#define VAR_OBJ_GFX_ID_D           0x401D
#define VAR_OBJ_GFX_ID_E           0x401E
#define VAR_OBJ_GFX_ID_F           0x401F

#define VAR_INTRO_PERSON           VAR_OBJ_GFX_ID_0
#define VAR_QUIP_PERSON            VAR_OBJ_GFX_ID_1
#define VAR_DEV_COMMENTATOR        VAR_OBJ_GFX_ID_2
#define VAR_ENDROOM_FRIEND         VAR_OBJ_GFX_ID_3
#define VAR_ENDROOM_PARTNER_ID     VAR_TEMP_F

// Trick Or Treat House vars
#define PUZZLE_VARS_START                    0x4020
#define VAR_PUZZLE_00                        0x4020
#define VAR_PUZZLE_01                        0x4021
#define VAR_PUZZLE_02                        0x4022
#define VAR_PUZZLE_03                        0x4023
#define VAR_PUZZLE_04                        0x4024
#define VAR_PUZZLE_05                        0x4025
#define VAR_PUZZLE_06                        0x4026
#define VAR_PUZZLE_07                        0x4027
#define VAR_PUZZLE_08                        0x4028
#define VAR_PUZZLE_09                        0x4029
#define VAR_PUZZLE_0A                        0x402A
#define VAR_PUZZLE_0B                        0x402B
#define VAR_PUZZLE_0C                        0x402C
#define VAR_PUZZLE_0D                        0x402D
#define VAR_PUZZLE_0E                        0x402E
#define VAR_PUZZLE_0F                        0x402F
#define VAR_PUZZLE_10                        0x4030
#define VAR_PUZZLE_11                        0x4031
#define VAR_PUZZLE_12                        0x4032
#define VAR_PUZZLE_13                        0x4033
#define VAR_PUZZLE_14                        0x4034
#define VAR_PUZZLE_15                        0x4035
#define VAR_PUZZLE_16                        0x4036
#define VAR_PUZZLE_17                        0x4037
#define VAR_PUZZLE_18                        0x4038
#define VAR_PUZZLE_19                        0x4039
#define VAR_PUZZLE_1A                        0x403A
#define VAR_PUZZLE_1B                        0x403B
#define VAR_PUZZLE_1C                        0x403C
#define VAR_PUZZLE_1D                        0x403D
#define VAR_PUZZLE_1E                        0x403E
#define VAR_PUZZLE_1F                        0x403F
#define VAR_PUZZLE_20                        0x4040
#define VAR_PUZZLE_21                        0x4041
#define VAR_PUZZLE_22                        0x4042
#define VAR_PUZZLE_23                        0x4043
#define VAR_PUZZLE_24                        0x4044
#define VAR_PUZZLE_25                        0x4045
#define VAR_PUZZLE_26                        0x4046
#define VAR_PUZZLE_28                        0x4048
#define VAR_PUZZLE_28                        0x4048
#define VAR_PUZZLE_29                        0x4049
#define VAR_PUZZLE_2A                        0x404A
#define VAR_PUZZLE_2B                        0x404B
#define VAR_PUZZLE_2C                        0x404C
#define VAR_PUZZLE_2D                        0x404D
#define VAR_PUZZLE_2E                        0x404E
#define VAR_PUZZLE_2F                        0x404F
#define VAR_PUZZLE_30                        0x4050
#define VAR_PUZZLE_31                        0x4051
#define VAR_PUZZLE_32                        0x4052
#define VAR_PUZZLE_33                        0x4053
#define VAR_PUZZLE_34                        0x4054
#define VAR_PUZZLE_35                        0x4055
#define VAR_PUZZLE_36                        0x4056
#define VAR_PUZZLE_37                        0x4057
#define VAR_PUZZLE_38                        0x4058
#define VAR_PUZZLE_39                        0x4059
#define VAR_PUZZLE_3A                        0x405A
#define VAR_PUZZLE_3B                        0x405B
#define VAR_PUZZLE_3C                        0x405C
#define VAR_PUZZLE_3D                        0x405D
#define VAR_PUZZLE_3E                        0x405E
#define VAR_PUZZLE_3F                        0x405F
#define PUZZLE_VARS_END                      VAR_PUZZLE_3F

// trick house system variables
#define VAR_CURRENT_PUZZLE                   0x4060 
#define VAR_PUZZLE_STATE                     0x4061 // 0 = before puzzle, 1 = puzzle underway, 2 = after puzzle
#define VAR_INTRO_COUNTER                    0x4062 // 0 = before intro, 1 = outside intro, 2 = inside intro 1, 
#define VAR_DEN_BLOCKED_EXCUSE               0x4063
#define VAR_TRICK_MASTER_INTRO               0x4064

// general purpose vars
#define VAR_REPEL_STEP_COUNT                 0x4065
#define VAR_STEP_TRIGGER                     0x4066 // Used for the ice cracking puzzle, the mach bike floor cracking puzzle, and npc triggers
#define VAR_STARTER_MON                      0x4067
#define VAR_FRIENDSHIP_STEP_COUNTER          0x4068
#define VAR_CONTEST_TYPE                     0x4069
#define VAR_SECRET_BASE_MAP                  0x406A
#define VAR_CYCLING_ROAD_RECORD_COLLISIONS   0x406B
#define VAR_CYCLING_ROAD_RECORD_TIME_L       0x406C
#define VAR_CYCLING_ROAD_RECORD_TIME_H       0x406D
#define VAR_SYS_REFLECTION_OFFSET            0x406E // Offset of reflection, in pixels
#define VAR_POISON_STEP_COUNTER              0x406F
#define VAR_RESET_RTC_ENABLE                 0x4070
#define VAR_CURRENT_SECRET_BASE              0x4071
#define VAR_FOLLOWER_STATE                   0x4072
#define VAR_FOLLOWER_IDENTITY                0x4073
#define VAR_UNUSED_0x4054                    0x4074
#define VAR_UNUSED_0x4055                    0x4075
#define VAR_UNUSED_0x4056                    0x4076
#define VAR_UNUSED_0x4057                    0x4077
#define VAR_DEOXYS_ROCK_STEP_COUNT           0x4078
#define VAR_DEOXYS_ROCK_LEVEL                0x4079
#define VAR_PC_BOX_TO_SEND_MON               0x407A
#define VAR_UNUSED_0x405B                    0x407B
#define VAR_UNUSED_0x405C                    0x407C
#define VAR_UNUSED_0x405D                    0x407D
#define VAR_FARAWAY_ISLAND_STEP_COUNTER      0x407E // On Chopping Block
#define VAR_ALTERING_CAVE_WILD_SET           0x407F // On Chopping Block
#define VAR_UNUSED_0x4060                    0x4080
#define VAR_DAYS                             0x4081
#define VAR_UNUSED_0x4062                    0x4082
#define VAR_UNUSED_0x4063                    0x4083
#define VAR_UNUSED_0x4064                    0x4084
#define VAR_POKELOT_PRIZE_ITEM               0x4085 // On Chopping Block
#define VAR_UNUSED_0x4066                    0x4086
#define VAR_SEEDOT_SIZE_RECORD               0x4087
#define VAR_ASH_GATHER_COUNT                 0x4088
#define VAR_UNUSED_0x4069                    0x4089
#define VAR_UNUSED_0x406A                    0x408A
#define VAR_POKELOT_RND1                     0x408B // On Chopping Block
#define VAR_POKELOT_RND2                     0x408C // On Chopping Block
#define VAR_POKELOT_PRIZE_PLACE              0x408D // On Chopping Block
#define VAR_TIMES_SEEN_BY_TRAINER            0x408E
#define VAR_LOTAD_SIZE_RECORD                0x408F
#define VAR_CANDY_TRADE_MASTER               0x4090
#define VAR_CANDY_TRADE_1                    0x4091
#define VAR_CANDY_TRADE_2                    0x4092
#define VAR_CANDY_TRADE_3                    0x4093
#define VAR_CANDY_TRADE_4                    0x4094
#define VAR_CANDY_TRADE_5                    0x4095
#define VAR_CANDY_TRADE_6                    0x4096
#define VAR_CANDY_TRADE_7                    0x4097
#define VAR_CANDY_TRADE_8                    0x4098
#define VAR_CANDY_TRADE_9                    0x4099
#define VAR_CANDY_TRADE_A                    0x409A
#define VAR_CANDY_TRADE_B                    0x409B
#define VAR_CANDY_TRADE_C                    0x409C
#define VAR_CANDY_TRADE_D                    0x409D
#define VAR_CANDY_TRADE_E                    0x409E
#define VAR_CANDY_TRADE_F                    0x409F
#define VAR_MISTRESS_STATE                   0x40A0 // Trick Mistress
#define VAR_UNUSED_0x4081                    0x40A1
#define VAR_UNUSED_0x4082                    0x40A2
#define VAR_UNUSED_0x4083                    0x40A3
#define VAR_UNUSED_0x4084                    0x40A4
#define VAR_UNUSED_0x4085                    0x40A5
#define VAR_UNUSED_0x4086                    0x40A6
#define VAR_UNUSED_0x4087                    0x40A7
#define VAR_UNUSED_0x4088                    0x40A8
#define VAR_UNUSED_0x4089                    0x40A9
#define VAR_UNUSED_0x408A                    0x40AA
#define VAR_UNUSED_0x408B                    0x40AB
#define VAR_UNUSED_0x408C                    0x40AC
#define VAR_UNUSED_0x408D                    0x40AD
#define VAR_UNUSED_0x408E                    0x40AE
#define VAR_NEW_ROCK_STATE                   0x40AF
#define VAR_UNUSED_0x40B0                    0x40B0
#define VAR_UNUSED_0x40B1                    0x40B1
#define VAR_UNUSED_0x40B2                    0x40B2
#define VAR_UNUSED_0x40B3                    0x40B3
#define VAR_UNUSED_0x40B4                    0x40B4
#define VAR_UNUSED_0x40B5                    0x40B5
#define VAR_UNUSED_0x40B6                    0x40B6
#define VAR_UNUSED_0x40B7                    0x40B7
#define VAR_UNUSED_0x40B8                    0x40B8
#define VAR_UNUSED_0x40B9                    0x40B9
#define VAR_UNUSED_0x40BA                    0x40BA
#define VAR_UNUSED_0x40BB                    0x40BB
#define VAR_UNUSED_0x40BC                    0x40BC
#define VAR_UNUSED_0x40BD                    0x40BD
#define VAR_UNUSED_0x40BE                    0x40BE
#define VAR_UNUSED_0x40BF                    0x40BF
#define VAR_UNUSED_0x40C0                    0x40C0
#define VAR_UNUSED_0x40C1                    0x40C1
#define VAR_UNUSED_0x40C2                    0x40C2
#define VAR_UNUSED_0x40C3                    0x40C3
#define VAR_BRAVO_TRAINER_BATTLE_TOWER_ON    0x40C4 // On Chopping Block
#define VAR_UNUSED_0x40C5                    0x40C5
#define VAR_UNUSED_0x40C6                    0x40C6
#define VAR_UNUSED_0x40C7                    0x40C7
#define VAR_UNUSED_0x40C8                    0x40C8
#define VAR_PACIFIDLOG_TM_RECEIVED_DAY       0x40C9 // On Chopping Block
#define VAR_UNUSED_0x40CA                    0x40CA
#define VAR_UNUSED_0x40CB                    0x40CB
#define VAR_LILYCOVE_CONTEST_LOBBY_STATE     0x40CC // On Chopping Block
#define VAR_STEVENS_HOUSE_STATE              0x40CD // On Chopping Block
#define VAR_UNUSED_0x40CE                    0x40CE
#define VAR_SECRET_BASE_INITIALIZED          0x40CF
#define VAR_INIT_SECRET_BASE                 0x40D0
#define VAR_SKY_PILLAR_STATE                 0x40D1 // On Chopping Block
#define VAR_MIRAGE_TOWER_STATE               0x40D2 // On Chopping Block
#define VAR_FOSSIL_MANIAC_STATE              0x40D3 // On Chopping Block
#define VAR_CABLE_CLUB_TUTORIAL_STATE        0x40D4 // On Chopping Block
#define VAR_FRONTIER_BATTLE_MODE             0x40D5
#define VAR_FRONTIER_FACILITY                0x40D6
#define VAR_HAS_ENTERED_BATTLE_FRONTIER      0x40D7 // On Chopping Block
#define VAR_CABLE_CLUB_STATE                 0x40D8 // On Chopping Block
#define VAR_UNUSED_0x40D9                    0x40D9
#define VAR_CONTEST_PRIZE_PICKUP             0x40DA
#define VAR_SS_TIDAL_SCOTT_STATE             0x40DB // On Chopping Block
#define VAR_ROAMER_POKEMON                   0x40DC // 0 = Latias, 1 = Latios
#define VAR_CROSS_MAP_TRIGGER                0x40DD
#define VAR_UNUSED_0x40DE                    0x40DE
#define VAR_UNUSED_0x40DF                    0x40DF
#define VAR_UNUSED_0x40E0                    0x40E0
#define VAR_UNUSED_0x40E1                    0x40E1
#define VAR_UNUSED_0x40E2                    0x40E2
#define VAR_UNUSED_0x40E3                    0x40E3
#define VAR_UNUSED_0x40E4                    0x40E4
#define VAR_UNUSED_0x40E5                    0x40E5
#define VAR_UNUSED_0x40E6                    0x40E6
#define VAR_UNUSED_0x40E7                    0x40E7
#define VAR_UNUSED_0x40E8                    0x40E8
#define VAR_UNUSED_0x40E9                    0x40E9
#define VAR_UNUSED_0x40EA                    0x40EA
#define VAR_UNUSED_0x40EB                    0x40EB
#define VAR_CONTEST_HALL_STATE               0x40EC
#define VAR_DAILY_SLOTS                      0x40ED
#define VAR_DAILY_WILDS                      0x40EE
#define VAR_DAILY_BLENDER                    0x40EF
#define VAR_DAILY_PLANTED_BERRIES            0x40F0
#define VAR_DAILY_PICKED_BERRIES             0x40F1
#define VAR_DAILY_ROULETTE                   0x40F2
#define VAR_SECRET_BASE_STEP_COUNTER         0x40F3 // Used by Secret Base TV programs
#define VAR_SECRET_BASE_LAST_ITEM_USED       0x40F4 // Used by Secret Base TV programs
#define VAR_SECRET_BASE_LOW_TV_FLAGS         0x40F5 // Used by Secret Base TV programs
#define VAR_SECRET_BASE_HIGH_TV_FLAGS        0x40F6 // Used by Secret Base TV programs
#define VAR_SECRET_BASE_IS_NOT_LOCAL         0x40F7 // Set to TRUE while in another player's secret base.
#define VAR_DAILY_BP                         0x40F8
#define VAR_UNUSED_0x40F2                    0x40F9
#define VAR_UNUSED_0x40F3                    0x40FA
#define VAR_UNUSED_0x40F4                    0x40FB
#define VAR_UNUSED_0x40F5                    0x40FC
#define VAR_UNUSED_0x40F6                    0x40FD
#define VAR_UNUSED_0x40F7                    0x40FE
#define VAR_UNUSED_0x40F8                    0x40FF

#define VARS_END                             0x40FF
#define VARS_COUNT                           (VARS_END - VARS_START + 1)

#define SPECIAL_VARS_START            0x8000
// special vars
// They are commonly used as parameters to commands, or return values from commands.
#define VAR_0x8000                    0x8000
#define VAR_0x8001                    0x8001
#define VAR_0x8002                    0x8002
#define VAR_0x8003                    0x8003
#define VAR_0x8004                    0x8004
#define VAR_0x8005                    0x8005
#define VAR_0x8006                    0x8006
#define VAR_0x8007                    0x8007
#define VAR_0x8008                    0x8008
#define VAR_0x8009                    0x8009
#define VAR_0x800A                    0x800A
#define VAR_0x800B                    0x800B
#define VAR_FACING                    0x800C
#define VAR_RESULT                    0x800D
#define VAR_ITEM_ID                   0x800E
#define VAR_LAST_TALKED               0x800F
#define VAR_CONTEST_RANK              0x8010
#define VAR_CONTEST_CATEGORY          0x8011
#define VAR_MON_BOX_ID                0x8012
#define VAR_MON_BOX_POS               0x8013
#define VAR_LAST_ERROR_NO             0x8014
#define VAR_TRAINER_BATTLE_OPPONENT_A 0x8015 // Alias of gTrainerBattleOpponent_A
#define VAR_INTERACT_X                0x8016
#define VAR_INTERACT_Y                0x8017
#define VAR_METATILE_X                0x8018
#define VAR_METATILE_Y                0x8019
#define VAR_LAST_WARP_ID              0x801A
#define VAR_SYS_FORCE_STEP            0x801B
#define VAR_BATTLE_MOD                0x801C
#define VAR_SPEAKER_PAL_OVERRIDE      0x801D

#define SPECIAL_VARS_END              0x801D

// If an overworld trigger uses this pseudo-variable as the trigger check,
// then the script will be run using RunScriptImmediately instead of in the
// global script context. This means it will run faster, but cannot do any
// cutscenes nor call a wait command. Used for weather effects in vanilla.
#define VAR_RUN_TRIGGER_IMMEDIATELY        0

#define THIS_EVENT                    0x800F //alias to VAR_LAST_TALKED

#define BATTLEMOD_NO_WHITEOUT         0x0001

#endif // GUARD_CONSTANTS_VARS_H
