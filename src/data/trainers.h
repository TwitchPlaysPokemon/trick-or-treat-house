#define DUMMY_TRAINER(name) \
    { \
        .trainerClass = TRAINER_CLASS_DEVELOPER, \
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE, \
        .trainerPic = TRAINER_PIC_YOUNGSTER, \
        .trainerName = name, \
        .items = {}, \
        .doubleBattle = FALSE, \
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE, \
        .party = NO_ITEM_DEFAULT_MOVES(sParty_Joey), \
    }


const struct Trainer gTrainers[] = {
    [TRAINER_NONE] =
    {
        .trainerClass = TRAINER_CLASS_DEVELOPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("JOEY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_Joey),
    },
    
    [TRAINER_01] = DUMMY_TRAINER( _("DUMMY 01") ),
    [TRAINER_02] = DUMMY_TRAINER( _("DUMMY 02") ),
    [TRAINER_03] = DUMMY_TRAINER( _("DUMMY 03") ),
    [TRAINER_04] = DUMMY_TRAINER( _("DUMMY 04") ),
    [TRAINER_05] = DUMMY_TRAINER( _("DUMMY 05") ),
    [TRAINER_06] = DUMMY_TRAINER( _("DUMMY 06") ),
    [TRAINER_07] = DUMMY_TRAINER( _("DUMMY 07") ),
    [TRAINER_08] = DUMMY_TRAINER( _("DUMMY 08") ),
    [TRAINER_09] = DUMMY_TRAINER( _("DUMMY 09") ),
    [TRAINER_10] = DUMMY_TRAINER( _("DUMMY 10") ),
    [TRAINER_11] = DUMMY_TRAINER( _("DUMMY 11") ),
    [TRAINER_12] = DUMMY_TRAINER( _("DUMMY 12") ),
    [TRAINER_13] = DUMMY_TRAINER( _("DUMMY 13") ),
    [TRAINER_14] = DUMMY_TRAINER( _("DUMMY 14") ),
    [TRAINER_15] = DUMMY_TRAINER( _("DUMMY 15") ),
    [TRAINER_16] = DUMMY_TRAINER( _("DUMMY 16") ),
    [TRAINER_17] = DUMMY_TRAINER( _("DUMMY 17") ),
    [TRAINER_18] = DUMMY_TRAINER( _("DUMMY 18") ),
    [TRAINER_19] = DUMMY_TRAINER( _("DUMMY 19") ),
    [TRAINER_20] = DUMMY_TRAINER( _("DUMMY 20") ),
    [TRAINER_21] = DUMMY_TRAINER( _("DUMMY 21") ),
    [TRAINER_22] = DUMMY_TRAINER( _("DUMMY 22") ),
    [TRAINER_23] = DUMMY_TRAINER( _("DUMMY 23") ),
    [TRAINER_24] = DUMMY_TRAINER( _("DUMMY 24") ),
    [TRAINER_25] = DUMMY_TRAINER( _("DUMMY 25") ),
    [TRAINER_26] = DUMMY_TRAINER( _("DUMMY 26") ),
    [TRAINER_27] = DUMMY_TRAINER( _("DUMMY 27") ),
    [TRAINER_28] = DUMMY_TRAINER( _("DUMMY 28") ),
    [TRAINER_29] = DUMMY_TRAINER( _("DUMMY 29") ),
    [TRAINER_30] = DUMMY_TRAINER( _("DUMMY 30") ),
    [TRAINER_31] = DUMMY_TRAINER( _("DUMMY 31") ),
    
    // Inset non-map-based trainers below. The below will be used for
    // fighting trainers outside the trick house and trainers in Slateport,
    // as well as fighting friends when that opportunity appears

};
