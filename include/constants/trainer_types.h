#ifndef GUARD_CONSTANTS_TRAINER_TYPES_H
#define GUARD_CONSTANTS_TRAINER_TYPES_H

#define TRAINER_TYPE_NONE               0
#define TRAINER_TYPE_NORMAL             1
#define TRAINER_TYPE_SEE_ALL_DIRECTIONS 2
#define TRAINER_TYPE_BURIED             3
#define TRAINER_TYPE_UNKNOWN4           4
#define TRAINER_TYPE_BUMP_TO_INTERACT   5
#define TRAINER_TYPE_KEEP_LOADED        0x8000

#define TRAINER_TYPE_NORMAL_KEEP_LOADED (TRAINER_TYPE_KEEP_LOADED|TRAINER_TYPE_NORMAL)

#endif  // GUARD_CONSTANTS_TRAINER_TYPES_H