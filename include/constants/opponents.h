#ifndef GUARD_CONSTANTS_OPPONENTS_H
#define GUARD_CONSTANTS_OPPONENTS_H

#define TRAINER_NONE             0
#define TRAINER_01               1
#define TRAINER_02               2
#define TRAINER_03               3
#define TRAINER_04               4
#define TRAINER_05               5
#define TRAINER_06               6
#define TRAINER_07               7
#define TRAINER_08               8
#define TRAINER_09               9
#define TRAINER_10               10
#define TRAINER_11               11
#define TRAINER_12               12
#define TRAINER_13               13
#define TRAINER_14               14
#define TRAINER_15               15
#define TRAINER_16               16
#define TRAINER_17               17
#define TRAINER_18               18
#define TRAINER_19               19
#define TRAINER_20               20
#define TRAINER_21               21
#define TRAINER_22               22
#define TRAINER_23               23
#define TRAINER_24               24
#define TRAINER_25               25
#define TRAINER_26               26
#define TRAINER_27               27
#define TRAINER_28               28
#define TRAINER_29               29
#define TRAINER_30               30
#define TRAINER_31               31

#define TRAINERS_PERMAP_END      32

#define TRAINER_TRICK_MASTER     32
#define TRAINER_33               33
#define TRAINER_34               34
#define TRAINER_35               35
#define TRAINER_36               36
#define TRAINER_37               37
#define TRAINER_38               38
#define TRAINER_39               39
#define TRAINER_40               40
#define TRAINER_41               41
#define TRAINER_42               42
#define TRAINER_43               43
#define TRAINER_44               44
#define TRAINER_45               45
#define TRAINER_46               46
#define TRAINER_47               47
#define TRAINER_48               48
#define TRAINER_49               49
#define TRAINER_50               50

// NOTE: Because each Trainer uses a flag to determine when they are defeated, there is only space for 9 additional trainers before trainer flag space overflows
//       More space can be made by shifting flags around in constants/flags.h or changing how trainer flags are handled
//       MAX_TRAINERS_COUNT can be increased but will take up additional saveblock space

#define TRAINERS_COUNT          51
#define MAX_TRAINERS_COUNT     864

#endif  // GUARD_CONSTANTS_OPPONENTS_H
