#ifndef GUARD_CONSTANTS_BERRY_H
#define GUARD_CONSTANTS_BERRY_H

#define BERRY_NONE 0

#define BERRY_FIRMNESS_UNKNOWN     0
#define BERRY_FIRMNESS_VERY_SOFT   1
#define BERRY_FIRMNESS_SOFT        2
#define BERRY_FIRMNESS_HARD        3
#define BERRY_FIRMNESS_VERY_HARD   4
#define BERRY_FIRMNESS_SUPER_HARD  5

#define FLAVOR_SPICY   0
#define FLAVOR_DRY     1
#define FLAVOR_SWEET   2
#define FLAVOR_BITTER  3
#define FLAVOR_SOUR    4
#define FLAVOR_COUNT   5

#define BERRY_STAGE_NO_BERRY    0  // there is no tree planted and the soil is completely flat.
#define BERRY_STAGE_PLANTED     1
#define BERRY_STAGE_SPROUTED    2
#define BERRY_STAGE_TALLER      3
#define BERRY_STAGE_FLOWERING   4
#define BERRY_STAGE_BERRIES     5
#define BERRY_STAGE_SPARKLING   255

// Berries can be watered in the following stages:
// - BERRY_STAGE_PLANTED
// - BERRY_STAGE_SPROUTED
// - BERRY_STAGE_TALLER
// - BERRY_STAGE_FLOWERING
#define NUM_WATER_STAGES 4

// IDs for berry tree objects, indexes into berryTrees in SaveBlock1
// Named for whatever berry is initially planted there on a new game
// Those with no initial berry are named "soil"
#define BERRY_TREE_TRICKHOUSE_EXT_1   1
#define BERRY_TREE_TRICKHOUSE_EXT_2   2
#define BERRY_TREE_TRICKHOUSE_EXT_3   3
#define BERRY_TREE_META_ROOM_04       4
#define BERRY_TREE_META_ROOM_05       5
#define BERRY_TREE_META_ROOM_06       6
#define BERRY_TREE_META_ROOM_07       7
#define BERRY_TREE_META_ROOM_08       8
#define BERRY_TREE_META_ROOM_09       9
#define BERRY_TREE_META_ROOM_10      10
#define BERRY_TREE_META_ROOM_11      11
#define BERRY_TREE_META_ROOM_12      12
#define BERRY_TREE_META_ROOM_13      13
#define BERRY_TREE_META_ROOM_14      14
#define BERRY_TREE_META_ROOM_15      15
#define BERRY_TREE_META_ROOM_16      16
#define BERRY_TREE_META_ROOM_17      17
#define BERRY_TREE_META_ROOM_18      18
#define BERRY_TREE_META_ROOM_19      19
#define BERRY_TREE_PETALBURG         20
#define BERRY_TREE_UNUSED_21         21
#define BERRY_TREE_UNUSED_22         22
#define BERRY_TREE_UNUSED_23         23
#define BERRY_TREE_UNUSED_24         24
#define BERRY_TREE_UNUSED_25         25
#define BERRY_TREE_UNUSED_26         26
#define BERRY_TREE_UNUSED_27         27
#define BERRY_TREE_UNUSED_28         28
#define BERRY_TREE_UNUSED_29         29
#define BERRY_TREE_UNUSED_30         30
#define BERRY_TREE_UNUSED_31         31
#define BERRY_TREE_UNUSED_32         32
#define BERRY_TREE_UNUSED_33         33
#define BERRY_TREE_UNUSED_34         34
#define BERRY_TREE_UNUSED_35         35
#define BERRY_TREE_UNUSED_36         36
#define BERRY_TREE_UNUSED_37         37
#define BERRY_TREE_UNUSED_38         38
#define BERRY_TREE_UNUSED_39         39
#define BERRY_TREE_UNUSED_40         40
#define BERRY_TREE_UNUSED_41         41
#define BERRY_TREE_UNUSED_42         42
#define BERRY_TREE_UNUSED_43         43
#define BERRY_TREE_UNUSED_44         44
#define BERRY_TREE_UNUSED_45         45
#define BERRY_TREE_UNUSED_46         46
#define BERRY_TREE_UNUSED_47         47
#define BERRY_TREE_UNUSED_48         48
#define BERRY_TREE_UNUSED_49         49
#define BERRY_TREE_UNUSED_50         50
#define BERRY_TREE_UNUSED_51         51
#define BERRY_TREE_UNUSED_52         52
#define BERRY_TREE_UNUSED_53         53
#define BERRY_TREE_UNUSED_54         54
#define BERRY_TREE_UNUSED_55         55
#define BERRY_TREE_UNUSED_56         56
#define BERRY_TREE_UNUSED_57         57
#define BERRY_TREE_UNUSED_58         58
#define BERRY_TREE_UNUSED_59         59
#define BERRY_TREE_UNUSED_60         60
#define BERRY_TREE_UNUSED_61         61
#define BERRY_TREE_UNUSED_62         62
#define BERRY_TREE_UNUSED_63         63
#define BERRY_TREE_UNUSED_64         64
#define BERRY_TREE_UNUSED_65         65
#define BERRY_TREE_UNUSED_66         66
#define BERRY_TREE_UNUSED_67         67
#define BERRY_TREE_UNUSED_68         68
#define BERRY_TREE_UNUSED_69         69
#define BERRY_TREE_UNUSED_70         70
#define BERRY_TREE_UNUSED_71         71
#define BERRY_TREE_UNUSED_72         72
#define BERRY_TREE_UNUSED_73         73
#define BERRY_TREE_UNUSED_74         74
#define BERRY_TREE_UNUSED_75         75
#define BERRY_TREE_UNUSED_76         76
#define BERRY_TREE_UNUSED_77         77
#define BERRY_TREE_UNUSED_78         78
#define BERRY_TREE_UNUSED_79         79
#define BERRY_TREE_UNUSED_80         80
#define BERRY_TREE_UNUSED_81         81
#define BERRY_TREE_UNUSED_82         82
#define BERRY_TREE_UNUSED_83         83
#define BERRY_TREE_UNUSED_84         84
#define BERRY_TREE_UNUSED_85         85
#define BERRY_TREE_UNUSED_86         86
#define BERRY_TREE_UNUSED_87         87
#define BERRY_TREE_UNUSED_88         88
#define BERRY_TREE_UNUSED_89         89

// Remainder are unused

#define BERRY_TREES_COUNT 128

#endif // GUARD_CONSTANTS_BERRY_H
