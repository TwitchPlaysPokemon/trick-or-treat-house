#if USE_CANDY_CURRENCY
#define CANDY_COST(cost) (cost >> 6) 
#define CANDY_COST2(candy, normal) candy
#else
#define CANDY_COST(cost) cost
#define CANDY_COST2(candy, normal) normal
#endif

#define ItemUseOutOfBattle_CannotUseBall ItemUseOutOfBattle_CannotUse

// All pokeballs are going into the general pocket in this hack
#define POCKET_POKE_BALLS POCKET_GENERAL
// Alias for the moment
#define POCKET_ITEMS POCKET_GENERAL

const struct Item gItems[] =
{
    [ITEM_NONE] =
    {
        .name = sNoItemName,
        .itemId = ITEM_NONE,
        .price = 0,
        .description = sDummyDesc,
        .pocket = POCKET_GENERAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

// #pragma region Poké Balls

    [ITEM_POKE_BALL] =
    {
        .name = sPokeBallName,
        .itemId = ITEM_POKE_BALL,
        .price = CANDY_COST(200),
        .description = sPokeBallDesc,
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_POKE_BALL - FIRST_BALL,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUseBall,
        .battleUsage = ITEM_B_USE_OTHER,
        .battleUseFunc = ItemUseInBattle_PokeBall,
        .secondaryId = ITEM_POKE_BALL - FIRST_BALL,
    },

    [ITEM_GREAT_BALL] =
    {
        .name = sGreatBallName,
        .itemId = ITEM_GREAT_BALL,
        .price = CANDY_COST(600),
        .description = sGreatBallDesc,
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_GREAT_BALL - FIRST_BALL,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUseBall,
        .battleUsage = ITEM_B_USE_OTHER,
        .battleUseFunc = ItemUseInBattle_PokeBall,
        .secondaryId = ITEM_GREAT_BALL - FIRST_BALL,
    },

    [ITEM_ULTRA_BALL] =
    {
        .name = sUltraBallName,
        .itemId = ITEM_ULTRA_BALL,
        .price = CANDY_COST(1200),
        .description = sUltraBallDesc,
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_ULTRA_BALL - FIRST_BALL,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUseBall,
        .battleUsage = ITEM_B_USE_OTHER,
        .battleUseFunc = ItemUseInBattle_PokeBall,
        .secondaryId = ITEM_ULTRA_BALL - FIRST_BALL,
    },

    [ITEM_MASTER_BALL] =
    {
        .name = sMasterBallName,
        .itemId = ITEM_MASTER_BALL,
        .price = 0,
        .description = sMasterBallDesc,
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_MASTER_BALL - FIRST_BALL,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUseBall,
        .battleUsage = ITEM_B_USE_OTHER,
        .battleUseFunc = ItemUseInBattle_PokeBall,
        .secondaryId = ITEM_MASTER_BALL - FIRST_BALL,
    },

    [ITEM_PREMIER_BALL] =
    {
        .name = sPremierBallName,
        .itemId = ITEM_PREMIER_BALL,
        .price = CANDY_COST(20),
        .description = sPremierBallDesc,
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_PREMIER_BALL - FIRST_BALL,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUseBall,
        .battleUsage = ITEM_B_USE_OTHER,
        .battleUseFunc = ItemUseInBattle_PokeBall,
        .secondaryId = ITEM_PREMIER_BALL - FIRST_BALL,
    },

    [ITEM_HEAL_BALL] =
    {
        .name = sHealBallName,
        .itemId = ITEM_HEAL_BALL,
        .price = CANDY_COST(300),
        .description = sHealBallDesc,
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_HEAL_BALL - FIRST_BALL,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUseBall,
        .battleUsage = ITEM_B_USE_OTHER,
        .battleUseFunc = ItemUseInBattle_PokeBall,
        .secondaryId = ITEM_HEAL_BALL - FIRST_BALL,
    },

    [ITEM_NET_BALL] =
    {
        .name = sNetBallName,
        .itemId = ITEM_NET_BALL,
        .price = CANDY_COST(1000),
        .description = sNetBallDesc,
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_NET_BALL - FIRST_BALL,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUseBall,
        .battleUsage = ITEM_B_USE_OTHER,
        .battleUseFunc = ItemUseInBattle_PokeBall,
        .secondaryId = ITEM_NET_BALL - FIRST_BALL,
    },

    [ITEM_NEST_BALL] =
    {
        .name = sNestBallName,
        .itemId = ITEM_NEST_BALL,
        .price = CANDY_COST(1000),
        .description = sNestBallDesc,
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_NEST_BALL - FIRST_BALL,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUseBall,
        .battleUsage = ITEM_B_USE_OTHER,
        .battleUseFunc = ItemUseInBattle_PokeBall,
        .secondaryId = ITEM_NEST_BALL - FIRST_BALL,
    },

    [ITEM_DIVE_BALL] =
    {
        .name = sDiveBallName,
        .itemId = ITEM_DIVE_BALL,
        .price = CANDY_COST(1000),
        .description = sDiveBallDesc,
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_DIVE_BALL - FIRST_BALL,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUseBall,
        .battleUsage = ITEM_B_USE_OTHER,
        .battleUseFunc = ItemUseInBattle_PokeBall,
        .secondaryId = ITEM_DIVE_BALL - FIRST_BALL,
    },

    [ITEM_DUSK_BALL] =
    {
        .name = sDuskBallName,
        .itemId = ITEM_DUSK_BALL,
        .price = CANDY_COST(1000),
        .description = sDuskBallDesc,
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_DUSK_BALL - FIRST_BALL,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUseBall,
        .battleUsage = ITEM_B_USE_OTHER,
        .battleUseFunc = ItemUseInBattle_PokeBall,
        .secondaryId = ITEM_DUSK_BALL - FIRST_BALL,
    },

    [ITEM_TIMER_BALL] =
    {
        .name = sTimerBallName,
        .itemId = ITEM_TIMER_BALL,
        .price = CANDY_COST(1000),
        .description = sTimerBallDesc,
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_TIMER_BALL - FIRST_BALL,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUseBall,
        .battleUsage = ITEM_B_USE_OTHER,
        .battleUseFunc = ItemUseInBattle_PokeBall,
        .secondaryId = ITEM_TIMER_BALL - FIRST_BALL,
    },

    [ITEM_QUICK_BALL] =
    {
        .name = sQuickBallName,
        .itemId = ITEM_QUICK_BALL,
        .price = CANDY_COST(1000),
        .description = sQuickBallDesc,
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_QUICK_BALL - FIRST_BALL,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUseBall,
        .battleUsage = ITEM_B_USE_OTHER,
        .battleUseFunc = ItemUseInBattle_PokeBall,
        .secondaryId = ITEM_QUICK_BALL - FIRST_BALL,
    },

    [ITEM_REPEAT_BALL] =
    {
        .name = sRepeatBallName,
        .itemId = ITEM_REPEAT_BALL,
        .price = CANDY_COST(1000),
        .description = sRepeatBallDesc,
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_REPEAT_BALL - FIRST_BALL,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUseBall,
        .battleUsage = ITEM_B_USE_OTHER,
        .battleUseFunc = ItemUseInBattle_PokeBall,
        .secondaryId = ITEM_REPEAT_BALL - FIRST_BALL,
    },

    [ITEM_LUXURY_BALL] =
    {
        .name = sLuxuryBallName,
        .itemId = ITEM_LUXURY_BALL,
        .price = CANDY_COST(1000),
        .description = sLuxuryBallDesc,
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_LUXURY_BALL - FIRST_BALL,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUseBall,
        .battleUsage = ITEM_B_USE_OTHER,
        .battleUseFunc = ItemUseInBattle_PokeBall,
        .secondaryId = ITEM_LUXURY_BALL - FIRST_BALL,
    },

    [ITEM_LEVEL_BALL] =
    {
        .name = sLevelBallName,
        .itemId = ITEM_LEVEL_BALL,
        .price = 0,
        .description = sLevelBallDesc,
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_LEVEL_BALL - FIRST_BALL,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUseBall,
        .battleUsage = ITEM_B_USE_OTHER,
        .battleUseFunc = ItemUseInBattle_PokeBall,
        .secondaryId = ITEM_LEVEL_BALL - FIRST_BALL,
    },

    [ITEM_LURE_BALL] =
    {
        .name = sLureBallName,
        .itemId = ITEM_LURE_BALL,
        .price = 0,
        .description = sLureBallDesc,
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_LURE_BALL - FIRST_BALL,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUseBall,
        .battleUsage = ITEM_B_USE_OTHER,
        .battleUseFunc = ItemUseInBattle_PokeBall,
        .secondaryId = ITEM_LURE_BALL - FIRST_BALL,
    },

    [ITEM_MOON_BALL] =
    {
        .name = sMoonBallName,
        .itemId = ITEM_MOON_BALL,
        .price = 0,
        .description = sMoonBallDesc,
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_MOON_BALL - FIRST_BALL,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUseBall,
        .battleUsage = ITEM_B_USE_OTHER,
        .battleUseFunc = ItemUseInBattle_PokeBall,
        .secondaryId = ITEM_MOON_BALL - FIRST_BALL,
    },

    [ITEM_FRIEND_BALL] =
    {
        .name = sFriendBallName,
        .itemId = ITEM_FRIEND_BALL,
        .price = 0,
        .description = sFriendBallDesc,
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_FRIEND_BALL - FIRST_BALL,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUseBall,
        .battleUsage = ITEM_B_USE_OTHER,
        .battleUseFunc = ItemUseInBattle_PokeBall,
        .secondaryId = ITEM_FRIEND_BALL - FIRST_BALL,
    },

    [ITEM_LOVE_BALL] =
    {
        .name = sLoveBallName,
        .itemId = ITEM_LOVE_BALL,
        .price = 0,
        .description = sLoveBallDesc,
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_LOVE_BALL - FIRST_BALL,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUseBall,
        .battleUsage = ITEM_B_USE_OTHER,
        .battleUseFunc = ItemUseInBattle_PokeBall,
        .secondaryId = ITEM_LOVE_BALL - FIRST_BALL,
    },

    [ITEM_FAST_BALL] =
    {
        .name = sFastBallName,
        .itemId = ITEM_FAST_BALL,
        .price = 0,
        .description = sFastBallDesc,
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_FAST_BALL - FIRST_BALL,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUseBall,
        .battleUsage = ITEM_B_USE_OTHER,
        .battleUseFunc = ItemUseInBattle_PokeBall,
        .secondaryId = ITEM_FAST_BALL - FIRST_BALL,
    },

    [ITEM_HEAVY_BALL] =
    {
        .name = sHeavyBallName,
        .itemId = ITEM_HEAVY_BALL,
        .price = 0,
        .description = sHeavyBallDesc,
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_HEAVY_BALL - FIRST_BALL,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUseBall,
        .battleUsage = ITEM_B_USE_OTHER,
        .battleUseFunc = ItemUseInBattle_PokeBall,
        .secondaryId = ITEM_HEAVY_BALL - FIRST_BALL,
    },

    [ITEM_DREAM_BALL] =
    {
        .name = sDreamBallName,
        .itemId = ITEM_DREAM_BALL,
        .price = 0,
        .description = sDreamBallDesc,
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_DREAM_BALL - FIRST_BALL,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUseBall,
        .battleUsage = ITEM_B_USE_OTHER,
        .battleUseFunc = ItemUseInBattle_PokeBall,
        .secondaryId = ITEM_DREAM_BALL - FIRST_BALL,
    },

    [ITEM_SAFARI_BALL] =
    {
        .name = sSafariBallName,
        .itemId = ITEM_SAFARI_BALL,
        .price = 0,
        .description = sSafariBallDesc,
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_SAFARI_BALL - FIRST_BALL,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUseBall,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUseBall,
        .battleUsage = ITEM_B_USE_OTHER,
        .battleUseFunc = ItemUseInBattle_PokeBall,
        .secondaryId = ITEM_SAFARI_BALL - FIRST_BALL,
    },

    [ITEM_SPORT_BALL] =
    {
        .name = sSportBallName,
        .itemId = ITEM_SPORT_BALL,
        .price = 0,
        .description = sSportBallDesc,
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_SPORT_BALL - FIRST_BALL,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUseBall,
        .battleUsage = ITEM_B_USE_OTHER,
        .battleUseFunc = ItemUseInBattle_PokeBall,
        .secondaryId = ITEM_SPORT_BALL - FIRST_BALL,
    },

    [ITEM_PARK_BALL] =
    {
        .name = sParkBallName,
        .itemId = ITEM_PARK_BALL,
        .price = 0,
        .description = sParkBallDesc,
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_PARK_BALL - FIRST_BALL,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUseBall,
        .battleUsage = ITEM_B_USE_OTHER,
        .battleUseFunc = ItemUseInBattle_PokeBall,
        .secondaryId = ITEM_PARK_BALL - FIRST_BALL,
    },

    [ITEM_BEAST_BALL] =
    {
        .name = sBeastBallName,
        .itemId = ITEM_BEAST_BALL,
        .price = 0,
        .description = sBeastBallDesc,
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_BEAST_BALL - FIRST_BALL,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUseBall,
        .battleUsage = ITEM_B_USE_OTHER,
        .battleUseFunc = ItemUseInBattle_PokeBall,
        .secondaryId = ITEM_BEAST_BALL - FIRST_BALL,
    },

    [ITEM_CHERISH_BALL] =
    {
        .name = sCherishBallName,
        .itemId = ITEM_CHERISH_BALL,
        .price = 0,
        .description = sCherishBallDesc,
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_CHERISH_BALL - FIRST_BALL,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUseBall,
        .battleUsage = ITEM_B_USE_OTHER,
        .battleUseFunc = ItemUseInBattle_PokeBall,
        .secondaryId = ITEM_CHERISH_BALL - FIRST_BALL,
    },

// #pragma endregion

// #pragma region Medicine

    [ITEM_POTION] =
    {
        .name = sPotionName,
        .itemId = ITEM_POTION,
        .price = CANDY_COST(200),
        .holdEffectParam = 20,
        .description = sPotionDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = ITEM_B_USE_MEDICINE,
        .itemEffect = gItemEffect_HealHP20,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .flingPower = 30,
    },

    [ITEM_SUPER_POTION] =
    {
        .name = sSuperPotionName,
        .itemId = ITEM_SUPER_POTION,
        .price = CANDY_COST(700),
        .description = sSuperPotionDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = ITEM_B_USE_MEDICINE,
#if I_HEALTH_RECOVERY >= GEN_7
        .holdEffectParam = 60,
        .itemEffect = gItemEffect_HealHP60,
#else
        .holdEffectParam = 50,
        .itemEffect = gItemEffect_HealHP50,
#endif
        .battleUseFunc = ItemUseInBattle_Medicine,
        .flingPower = 30,
    },

    [ITEM_HYPER_POTION] =
    {
        .name = sHyperPotionName,
        .itemId = ITEM_HYPER_POTION,
        .price = CANDY_COST(1500),
        .description = sHyperPotionDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = ITEM_B_USE_MEDICINE,
#if I_HEALTH_RECOVERY >= GEN_7
        .holdEffectParam = 120,
        .itemEffect = gItemEffect_HealHP120,
#else
        .holdEffectParam = 200,
        .itemEffect = gItemEffect_HealHP200,
#endif
        .battleUseFunc = ItemUseInBattle_Medicine,
        .flingPower = 30,
    },

    [ITEM_MAX_POTION] =
    {
        .name = sMaxPotionName,
        .itemId = ITEM_MAX_POTION,
        .price = CANDY_COST(2500),
        .holdEffectParam = 255,
        .description = sMaxPotionDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = ITEM_B_USE_MEDICINE,
        .itemEffect = gItemEffect_HealHPAll,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .flingPower = 30,
    },

    [ITEM_FULL_RESTORE] =
    {
        .name = sFullRestoreName, 
        .itemId = ITEM_FULL_RESTORE,
        .price = CANDY_COST(3000),
        .holdEffectParam = 255,
        .description = sFullRestoreDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = ITEM_B_USE_MEDICINE,
        .itemEffect = gItemEffect_FullRestore,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .flingPower = 30,
    },

    [ITEM_REVIVE] =
    {
        .name = sReviveName,
        .itemId = ITEM_REVIVE,
        .price = CANDY_COST(2000),
        .description = sReviveDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = ITEM_B_USE_MEDICINE,
        .itemEffect = gItemEffect_Revive,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .flingPower = 30,
    },

    [ITEM_MAX_REVIVE] =
    {
        .name = sMaxReviveName,
        .itemId = ITEM_MAX_REVIVE,
        .price = CANDY_COST(4000),
        .description = sMaxReviveDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = ITEM_B_USE_MEDICINE,
        .itemEffect = gItemEffect_MaxRevive,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .flingPower = 30,
    },

    [ITEM_FRESH_WATER] =
    {
        .name = sFreshWaterName,
        .quantum = sQuantum_Bottle,
        .itemId = ITEM_FRESH_WATER,
        .price = CANDY_COST(200),
        .description = sFreshWaterDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = ITEM_B_USE_MEDICINE,
#if I_HEALTH_RECOVERY >= GEN_7
        .holdEffectParam = 30,
        .itemEffect = gItemEffect_HealHP30,
#else
        .holdEffectParam = 50,
        .itemEffect = gItemEffect_HealHP50,
#endif
        .battleUseFunc = ItemUseInBattle_Medicine,
        .flingPower = 30,
    },

    [ITEM_SODA_POP] =
    {
        .name = sSodaPopName,
        .quantum = sQuantum_Bottle,
        .itemId = ITEM_SODA_POP,
        .price = CANDY_COST(300),
        .description = sSodaPopDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = ITEM_B_USE_MEDICINE,
#if I_HEALTH_RECOVERY >= GEN_7
        .holdEffectParam = 50,
        .itemEffect = gItemEffect_HealHP50,
#else
        .holdEffectParam = 60,
        .itemEffect = gItemEffect_HealHP60,
#endif
        .battleUseFunc = ItemUseInBattle_Medicine,
        .flingPower = 30,
    },

    [ITEM_LEMONADE] =
    {
        .name = sLemonadeName,
        .quantum = sQuantum_Can,
        .itemId = ITEM_LEMONADE,
        .price = CANDY_COST(400),
        .description = sLemonadeDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = ITEM_B_USE_MEDICINE,
#if I_HEALTH_RECOVERY >= GEN_7
        .holdEffectParam = 70,
        .itemEffect = gItemEffect_HealHP70,
#else
        .holdEffectParam = 80,
        .itemEffect = gItemEffect_HealHP80,
#endif
        .battleUseFunc = ItemUseInBattle_Medicine,
        .flingPower = 30,
    },

    [ITEM_MOOMOO_MILK] =
    {
        .name = sMoomooMilkName,
        .quantum = sQuantum_Bottle,
        .itemId = ITEM_MOOMOO_MILK,
        .price = CANDY_COST(600),
        .holdEffectParam = 100,
        .description = sMoomooMilkDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = ITEM_B_USE_MEDICINE,
        .itemEffect = gItemEffect_HealHP100,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .flingPower = 30,
    },

    [ITEM_ENERGY_POWDER] =
    {
        .name = sEnergyPowderName,
        .quantum = sQuantum_Dose,
        .itemId = ITEM_ENERGY_POWDER,
        .price = CANDY_COST(500),
        .description = sEnergyPowderDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = ITEM_B_USE_MEDICINE,
        .itemEffect = gItemEffect_EnergyPowder,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .flingPower = 30,
    },

    [ITEM_ENERGY_ROOT] =
    {
        .name = sEnergyRootName,
        .itemId = ITEM_ENERGY_ROOT,
        .price = CANDY_COST(800),
        .description = sEnergyRootDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = ITEM_B_USE_MEDICINE,
        .itemEffect = gItemEffect_EnergyRoot,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .flingPower = 30,
    },

    [ITEM_HEAL_POWDER] =
    {
        .name = sHealPowderName,
        .quantum = sQuantum_Dose,
        .itemId = ITEM_HEAL_POWDER,
        .price = CANDY_COST(300),
        .description = sHealPowderDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = ITEM_B_USE_MEDICINE,
        .itemEffect = gItemEffect_HealPowder,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .flingPower = 30,
    },

    [ITEM_REVIVAL_HERB] =
    {
        .name = sRevivalHerbName,
        .itemId = ITEM_REVIVAL_HERB,
        .price = CANDY_COST(2800),
        .description = sRevivalHerbDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = ITEM_B_USE_MEDICINE,
        .itemEffect = gItemEffect_RevivalHerb,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .flingPower = 30,
    },

    [ITEM_ANTIDOTE] =
    {
        .name = sAntidoteName,
        .itemId = ITEM_ANTIDOTE,
        .price = CANDY_COST(200),
        .description = sAntidoteDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = ITEM_B_USE_MEDICINE,
        .itemEffect = gItemEffect_HealPoison,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .flingPower = 30,
    },

    [ITEM_PARALYZE_HEAL] =
    {
        .name = sParalyzeHealName,
        .itemId = ITEM_PARALYZE_HEAL,
        .price = CANDY_COST(300),
        .description = sParalyzeHealDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = ITEM_B_USE_MEDICINE,
        .itemEffect = gItemEffect_HealParalyze,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .flingPower = 30,
    },

    [ITEM_BURN_HEAL] =
    {
        .name = sBurnHealName,
        .itemId = ITEM_BURN_HEAL,
        .price = CANDY_COST(300),
        .description = sBurnHealDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = ITEM_B_USE_MEDICINE,
        .itemEffect = gItemEffect_HealBurn,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .flingPower = 30,
    },

    [ITEM_ICE_HEAL] =
    {
        .name = sIceHealName,
        .itemId = ITEM_ICE_HEAL,
        .price = CANDY_COST(100),
        .description = sIceHealDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = ITEM_B_USE_MEDICINE,
        .itemEffect = gItemEffect_HealFreeze,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .flingPower = 30,
    },

    [ITEM_AWAKENING] =
    {
        .name = sAwakeningName,
        .itemId = ITEM_AWAKENING,
        .price = CANDY_COST(100),
        .description = sAwakeningDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = ITEM_B_USE_MEDICINE,
        .itemEffect = gItemEffect_HealSleep,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .flingPower = 30,
    },

    [ITEM_FULL_HEAL] =
    {
        .name = sFullHealName, 
        .itemId = ITEM_FULL_HEAL,
        .price = CANDY_COST(400),
        .description = sFullHealDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = ITEM_B_USE_MEDICINE,
        .itemEffect = gItemEffect_HealAllStatus,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .flingPower = 30,
    },

    [ITEM_ETHER] =
    {
        .name = sEtherName, 
        .itemId = ITEM_ETHER,
        .price = CANDY_COST(1200),
        .holdEffectParam = 10,
        .description = sEtherDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_PPRecovery,
        .battleUsage = ITEM_B_USE_MEDICINE,
        .itemEffect = gItemEffect_HealPP10,
        .battleUseFunc = ItemUseInBattle_PPRecovery,
        .flingPower = 30,
    },

    [ITEM_MAX_ETHER] =
    {
        .name = sMaxEtherName, 
        .itemId = ITEM_MAX_ETHER,
        .price = CANDY_COST(2000),
        .holdEffectParam = 255,
        .description = sMaxEtherDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_PPRecovery,
        .battleUsage = ITEM_B_USE_MEDICINE,
        .itemEffect = gItemEffect_MaxEther,
        .battleUseFunc = ItemUseInBattle_PPRecovery,
        .flingPower = 30,
    },

    [ITEM_ELIXIR] =
    {
        .name = sElixirName, 
        .itemId = ITEM_ELIXIR,
        .price = CANDY_COST(3000),
        .holdEffectParam = 10,
        .description = sElixirDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_PPRecovery,
        .battleUsage = ITEM_B_USE_MEDICINE,
        .itemEffect = gItemEffect_Elixir,
        .battleUseFunc = ItemUseInBattle_PPRecovery,
        .flingPower = 30,
    },

    [ITEM_MAX_ELIXIR] =
    {
        .name = sMaxElixirName, 
        .itemId = ITEM_MAX_ELIXIR,
        .price = CANDY_COST(4500),
        .holdEffectParam = 255,
        .description = sMaxElixirDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_PPRecovery,
        .battleUsage = ITEM_B_USE_MEDICINE,
        .itemEffect = gItemEffect_MaxElixir,
        .battleUseFunc = ItemUseInBattle_PPRecovery,
        .flingPower = 30,
    },

    [ITEM_BERRY_JUICE] =
    {
        .name = sBerryJuiceName,
        .quantum = sQuantum_Cup,
        .itemId = ITEM_BERRY_JUICE,
        .price = CANDY_COST(200),
        .itemEffect = gItemEffect_HealHP20,
        .holdEffect = HOLD_EFFECT_RESTORE_HP,
        .holdEffectParam = 20,
        .description = sBerryJuiceDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = ITEM_B_USE_MEDICINE,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .flingPower = 30,
    },

    [ITEM_SACRED_ASH] =
    {
        .name = sSacredAshName,
        .quantum = sQuantum_Bag,
        .itemId = ITEM_SACRED_ASH,
        .price = CANDY_COST(50000),
        .description = sSacredAshDesc,
        .pocket = POCKET_GENERAL,
        .type = ITEM_USE_PARTY_MENU,
        .itemEffect = gItemEffect_SacredAsh,
        .fieldUseFunc = ItemUseOutOfBattle_SacredAsh,
        .flingPower = 30,
    },

    [ITEM_SWEET_HEART] =
    {
        .name = sSweetHeartName,
        .itemId = ITEM_SWEET_HEART,
        .price = CANDY_COST(3000),
        .holdEffectParam = 20,
        .description = sSweetHeartDesc,
        .keepItem = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = ITEM_B_USE_MEDICINE,
        .itemEffect = gItemEffect_HealHP20,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .flingPower = 30,
    },

    [ITEM_MAX_HONEY] =
    {
        .name = sMaxHoneyName,
        .quantum = sQuantum_Comb,
        .itemId = ITEM_MAX_HONEY,
        .price = CANDY_COST(8000),
        .description = sMaxHoneyDesc,
        .keepItem = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = ITEM_B_USE_MEDICINE,
        .itemEffect = gItemEffect_MaxRevive,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .flingPower = 30,
    },

// #pragma endregion

// #pragma region Regional Specialties

    [ITEM_PEWTER_CRUNCHIES] =
    {
        .name = sPewterCrunchiesName,
        .quantum = sQuantum_Bag,
        .itemId = ITEM_PEWTER_CRUNCHIES,
        .price = CANDY_COST(250),
        .description = sPewterCrunchiesDesc,
        .keepItem = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = ITEM_B_USE_MEDICINE,
        .itemEffect = gItemEffect_HealAllStatus,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .flingPower = 30,
    },

    [ITEM_RAGE_CANDY_BAR] =
    {
        .name = sRageCandyBarName,
        .itemId = ITEM_RAGE_CANDY_BAR,
        .price = CANDY_COST(350),
        .description = sRageCandyBarDesc,
        .keepItem = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = ITEM_B_USE_MEDICINE,
        .itemEffect = gItemEffect_HealAllStatus,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .flingPower = 30,
    },

    [ITEM_LAVA_COOKIE] =
    {
        .name = sLavaCookieName, 
        .itemId = ITEM_LAVA_COOKIE,
        .price = CANDY_COST(350),
        .description = sLavaCookieDesc,
        .keepItem = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = ITEM_B_USE_MEDICINE,
        .itemEffect = gItemEffect_HealAllStatus,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .flingPower = 30,
    },

    [ITEM_OLD_GATEAU] =
    {
        .name = sOldGateauName,
        .quantum = sQuantum_Pack,
        .itemId = ITEM_OLD_GATEAU,
        .price = CANDY_COST(350),
        .description = sOldGateauDesc,
        .keepItem = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = ITEM_B_USE_MEDICINE,
        .itemEffect = gItemEffect_HealAllStatus,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .flingPower = 30,
    },

    [ITEM_CASTELIACONE] =
    {
        .name = sCasteliaconeName,
        .itemId = ITEM_CASTELIACONE,
        .price = CANDY_COST(350),
        .description = sCasteliaconeDesc,
        .keepItem = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = ITEM_B_USE_MEDICINE,
        .itemEffect = gItemEffect_HealAllStatus,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .flingPower = 30,
    },

    [ITEM_LUMIOSE_GALETTE] =
    {
        .name = sLumioseGaletteName,
        .itemId = ITEM_LUMIOSE_GALETTE,
        .price = CANDY_COST(350),
        .description = sLumioseGaletteDesc,
        .keepItem = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = ITEM_B_USE_MEDICINE,
        .itemEffect = gItemEffect_HealAllStatus,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .flingPower = 30,
    },

    [ITEM_SHALOUR_SABLE] =
    {
        .name = sShalourSableName,
        .itemId = ITEM_SHALOUR_SABLE,
        .price = CANDY_COST(350),
        .description = sShalourSableDesc,
        .keepItem = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = ITEM_B_USE_MEDICINE,
        .itemEffect = gItemEffect_HealAllStatus,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .flingPower = 30,
    },

    [ITEM_BIG_MALASADA] =
    {
        .name = sBigMalasadaName,
        .itemId = ITEM_BIG_MALASADA,
        .price = CANDY_COST(350),
        .description = sBigMalasadaDesc,
        .keepItem = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = ITEM_B_USE_MEDICINE,
        .itemEffect = gItemEffect_HealAllStatus,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .flingPower = 30,
    },
    
// #pragma endregion

// #pragma region Vitamins

    [ITEM_HP_UP] =
    {
        .name = sHPUpName,
        .quantum = sQuantum_Bottle,
        .itemId = ITEM_HP_UP,
        .price = CANDY_COST(10000),
        .keepItem = TRUE,
        .description = sHPUpDesc,
        .pocket = POCKET_GENERAL,
        .type = ITEM_USE_PARTY_MENU,
        .itemEffect = gItemEffect_HPUp,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .flingPower = 30,
    },

    [ITEM_PROTEIN] =
    {
        .name = sProteinName,
        .quantum = sQuantum_Bottle,
        .itemId = ITEM_PROTEIN,
        .price = CANDY_COST(10000),
        .keepItem = TRUE,
        .description = sProteinDesc,
        .pocket = POCKET_GENERAL,
        .type = ITEM_USE_PARTY_MENU,
        .itemEffect = gItemEffect_Protein,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .flingPower = 30,
    },

    [ITEM_IRON] =
    {
        .name = sIronName,
        .quantum = sQuantum_Bottle,
        .itemId = ITEM_IRON,
        .price = CANDY_COST(10000),
        .keepItem = TRUE,
        .description = sIronDesc,
        .pocket = POCKET_GENERAL,
        .type = ITEM_USE_PARTY_MENU,
        .itemEffect = gItemEffect_Iron,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .flingPower = 30,
    },

    [ITEM_CALCIUM] =
    {
        .name = sCalciumName,
        .quantum = sQuantum_Bottle,
        .itemId = ITEM_CALCIUM,
        .price = CANDY_COST(10000),
        .keepItem = TRUE,
        .description = sCalciumDesc,
        .pocket = POCKET_GENERAL,
        .type = ITEM_USE_PARTY_MENU,
        .itemEffect = gItemEffect_Calcium,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .flingPower = 30,
    },

    [ITEM_ZINC] =
    {
        .name = sZincName,
        .quantum = sQuantum_Bottle,
        .itemId = ITEM_ZINC,
        .price = CANDY_COST(10000),
        .keepItem = TRUE,
        .description = sZincDesc,
        .pocket = POCKET_GENERAL,
        .type = ITEM_USE_PARTY_MENU,
        .itemEffect = gItemEffect_Zinc,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .flingPower = 30,
    },

    [ITEM_CARBOS] =
    {
        .name = sCarbosName,
        .quantum = sQuantum_Bottle,
        .itemId = ITEM_CARBOS,
        .price = CANDY_COST(10000),
        .keepItem = TRUE,
        .description = sCarbosDesc,
        .pocket = POCKET_GENERAL,
        .type = ITEM_USE_PARTY_MENU,
        .itemEffect = gItemEffect_Carbos,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .flingPower = 30,
    },

    [ITEM_PP_UP] =
    {
        .name = sPPUpName,
        .quantum = sQuantum_Bottle,
        .itemId = ITEM_PP_UP,
        .price = CANDY_COST(10000),
        .keepItem = TRUE,
        .description = sPPUpDesc,
        .pocket = POCKET_GENERAL,
        .type = ITEM_USE_PARTY_MENU,
        .itemEffect = gItemEffect_PPUp,
        .fieldUseFunc = ItemUseOutOfBattle_PPUp,
        .flingPower = 30,
    },

    [ITEM_PP_MAX] =
    {
        .name = sPPMaxName,
        .quantum = sQuantum_Bottle,
        .itemId = ITEM_PP_MAX,
        .price = CANDY_COST(10000),
        .keepItem = TRUE,
        .description = sPPMaxDesc,
        .pocket = POCKET_GENERAL,
        .type = ITEM_USE_PARTY_MENU,
        .itemEffect = gItemEffect_PPMax,
        .fieldUseFunc = ItemUseOutOfBattle_PPUp,
        .flingPower = 30,
    },

// #pragma endregion

// #pragma region EV Feathers

    [ITEM_HEALTH_FEATHER] =
    {
        .name = sHealthFeatherName,
        .itemId = ITEM_HEALTH_FEATHER,
        .price = CANDY_COST(300),
        .description = sHealthFeatherDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .itemEffect = gItemEffect_HpFeather,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .flingPower = 20,
    },

    [ITEM_MUSCLE_FEATHER] =
    {
        .name = sMuscleFeatherName,
        .itemId = ITEM_MUSCLE_FEATHER,
        .price = CANDY_COST(300),
        .description = sMuscleFeatherDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .itemEffect = gItemEffect_AtkFeather,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .flingPower = 20,
    },

    [ITEM_RESIST_FEATHER] =
    {
        .name = sResistFeatherName,
        .itemId = ITEM_RESIST_FEATHER,
        .price = CANDY_COST(300),
        .description = sResistFeatherDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .itemEffect = gItemEffect_DefFeather,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .flingPower = 20,
    },

    [ITEM_GENIUS_FEATHER] =
    {
        .name = sGeniusFeatherName,
        .itemId = ITEM_GENIUS_FEATHER,
        .price = CANDY_COST(300),
        .description = sGeniusFeatherDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .itemEffect = gItemEffect_SpatkFeather,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .flingPower = 20,
    },

    [ITEM_CLEVER_FEATHER] =
    {
        .name = sCleverFeatherName,
        .itemId = ITEM_CLEVER_FEATHER,
        .price = CANDY_COST(300),
        .description = sCleverFeatherDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .itemEffect = gItemEffect_SpdefFeather,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .flingPower = 20,
    },

    [ITEM_SWIFT_FEATHER] =
    {
        .name = sSwiftFeatherName,
        .itemId = ITEM_SWIFT_FEATHER,
        .price = CANDY_COST(300),
        .description = sSwiftFeatherDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .itemEffect = gItemEffect_SpeedFeather,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .flingPower = 20,
    },

// #pragma endregion

// #pragma region Ability Modifiers

    [ITEM_ABILITY_CAPSULE] =
    {
        .name = sAbilityCapsuleName,
        .itemId = ITEM_ABILITY_CAPSULE,
        .price = CANDY_COST(10000),
        .holdEffectParam = 0,
        .description = sAbilityCapsuleDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_AbilityCapsule,
    },

    [ITEM_ABILITY_PATCH] =
    {
        .name = sAbilityPatchName,
        .itemId = ITEM_ABILITY_PATCH,
        .price = 0,
        .holdEffectParam = 0,
        .description = sAbilityPatchDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_AbilityPatch,
    },

// #pragma endregion

// #pragma region Mints

    [ITEM_LONELY_MINT] =
    {
        .name = sLonelyMintName,
        .quantum = sQuantum_Sprig,
        .itemId = ITEM_LONELY_MINT,
        .price = CANDY_COST(20),
        .description = sLonelyMintDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse, // Todo
        .flingPower = 10,
    },

    [ITEM_ADAMANT_MINT] =
    {
        .name = sAdamantMintName,
        .quantum = sQuantum_Sprig,
        .itemId = ITEM_ADAMANT_MINT,
        .price = CANDY_COST(20),
        .description = sAdamantMintDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse, // Todo
        .flingPower = 10,
    },

    [ITEM_NAUGHTY_MINT] =
    {
        .name = sNaughtyMintName,
        .quantum = sQuantum_Sprig,
        .itemId = ITEM_NAUGHTY_MINT,
        .price = CANDY_COST(20),
        .description = sNaughtyMintDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse, // Todo
        .flingPower = 10,
    },

    [ITEM_BRAVE_MINT] =
    {
        .name = sBraveMintName,
        .quantum = sQuantum_Sprig,
        .itemId = ITEM_BRAVE_MINT,
        .price = CANDY_COST(20),
        .description = sBraveMintDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse, // Todo
        .flingPower = 10,
    },

    [ITEM_BOLD_MINT] =
    {
        .name = sBoldMintName,
        .quantum = sQuantum_Sprig,
        .itemId = ITEM_BOLD_MINT,
        .price = CANDY_COST(20),
        .description = sBoldMintDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse, // Todo
        .flingPower = 10,
    },

    [ITEM_IMPISH_MINT] =
    {
        .name = sImpishMintName,
        .quantum = sQuantum_Sprig,
        .itemId = ITEM_IMPISH_MINT,
        .price = CANDY_COST(20),
        .description = sImpishMintDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse, // Todo
        .flingPower = 10,
    },

    [ITEM_LAX_MINT] =
    {
        .name = sLaxMintName,
        .quantum = sQuantum_Sprig,
        .itemId = ITEM_LAX_MINT,
        .price = CANDY_COST(20),
        .description = sLaxMintDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse, // Todo
        .flingPower = 10,
    },

    [ITEM_RELAXED_MINT] =
    {
        .name = sRelaxedMintName,
        .quantum = sQuantum_Sprig,
        .itemId = ITEM_RELAXED_MINT,
        .price = CANDY_COST(20),
        .description = sRelaxedMintDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse, // Todo
        .flingPower = 10,
    },

    [ITEM_MODEST_MINT] =
    {
        .name = sModestMintName,
        .quantum = sQuantum_Sprig,
        .itemId = ITEM_MODEST_MINT,
        .price = CANDY_COST(20),
        .description = sModestMintDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse, // Todo
        .flingPower = 10,
    },

    [ITEM_MILD_MINT] =
    {
        .name = sMildMintName,
        .quantum = sQuantum_Sprig,
        .itemId = ITEM_MILD_MINT,
        .price = CANDY_COST(20),
        .description = sMildMintDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse, // Todo
        .flingPower = 10,
    },

    [ITEM_RASH_MINT] =
    {
        .name = sRashMintName,
        .quantum = sQuantum_Sprig,
        .itemId = ITEM_RASH_MINT,
        .price = CANDY_COST(20),
        .description = sRashMintDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse, // Todo
        .flingPower = 10,
    },

    [ITEM_QUIET_MINT] =
    {
        .name = sQuietMintName,
        .quantum = sQuantum_Sprig,
        .itemId = ITEM_QUIET_MINT,
        .price = CANDY_COST(20),
        .description = sQuietMintDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse, // Todo
        .flingPower = 10,
    },

    [ITEM_CALM_MINT] =
    {
        .name = sCalmMintName,
        .quantum = sQuantum_Sprig,
        .itemId = ITEM_CALM_MINT,
        .price = CANDY_COST(20),
        .description = sCalmMintDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse, // Todo
        .flingPower = 10,
    },

    [ITEM_GENTLE_MINT] =
    {
        .name = sGentleMintName,
        .quantum = sQuantum_Sprig,
        .itemId = ITEM_GENTLE_MINT,
        .price = CANDY_COST(20),
        .description = sGentleMintDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse, // Todo
        .flingPower = 10,
    },

    [ITEM_CAREFUL_MINT] =
    {
        .name = sCarefulMintName,
        .quantum = sQuantum_Sprig,
        .itemId = ITEM_CAREFUL_MINT,
        .price = CANDY_COST(20),
        .description = sCarefulMintDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse, // Todo
        .flingPower = 10,
    },

    [ITEM_SASSY_MINT] =
    {
        .name = sSassyMintName,
        .quantum = sQuantum_Sprig,
        .itemId = ITEM_SASSY_MINT,
        .price = CANDY_COST(20),
        .description = sSassyMintDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse, // Todo
        .flingPower = 10,
    },

    [ITEM_TIMID_MINT] =
    {
        .name = sTimidMintName,
        .quantum = sQuantum_Sprig,
        .itemId = ITEM_TIMID_MINT,
        .price = CANDY_COST(20),
        .description = sTimidMintDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse, // Todo
        .flingPower = 10,
    },

    [ITEM_HASTY_MINT] =
    {
        .name = sHastyMintName,
        .quantum = sQuantum_Sprig,
        .itemId = ITEM_HASTY_MINT,
        .price = CANDY_COST(20),
        .description = sHastyMintDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse, // Todo
        .flingPower = 10,
    },

    [ITEM_JOLLY_MINT] =
    {
        .name = sJollyMintName,
        .quantum = sQuantum_Sprig,
        .itemId = ITEM_JOLLY_MINT,
        .price = CANDY_COST(20),
        .description = sJollyMintDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse, // Todo
        .flingPower = 10,
    },

    [ITEM_NAIVE_MINT] =
    {
        .name = sNaiveMintName,
        .quantum = sQuantum_Sprig,
        .itemId = ITEM_NAIVE_MINT,
        .price = CANDY_COST(20),
        .description = sNaiveMintDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse, // Todo
        .flingPower = 10,
    },

    [ITEM_SERIOUS_MINT] =
    {
        .name = sSeriousMintName,
        .quantum = sQuantum_Sprig,
        .itemId = ITEM_SERIOUS_MINT,
        .price = CANDY_COST(20),
        .description = sSeriousMintDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse, // Todo
        .flingPower = 10,
    },

// #pragma endregion

// #pragma region Candy

    [ITEM_RARE_CANDY] =
    {
        .name = sRareCandyName,
        .plural = sRareCandyPluralName,
        .itemId = ITEM_RARE_CANDY,
        .price = CANDY_COST(10000),
        .description = sRareCandyDesc,
        .keepItem = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_PARTY_MENU,
        .itemEffect = gItemEffect_RareCandy,
        .fieldUseFunc = ItemUseOutOfBattle_RareCandy,
        .flingPower = 30,
    },

    [ITEM_EXP_CANDY_XS] =
    {
        .name = sExpCandyXSName,
        .plural = sExpCandyXSPluralName,
        .itemId = ITEM_EXP_CANDY_XS,
        .price = CANDY_COST(20),
        .holdEffectParam = EXP_100,
        .description = sExpCandyXSDesc,
        .keepItem = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_PARTY_MENU,
        .itemEffect = gItemEffect_RareCandy,
        .fieldUseFunc = ItemUseOutOfBattle_RareCandy,
        .flingPower = 30,
    },

    [ITEM_EXP_CANDY_S] =
    {
        .name = sExpCandySName,
        .plural = sExpCandySPluralName,
        .itemId = ITEM_EXP_CANDY_S,
        .price = CANDY_COST(240),
        .holdEffectParam = EXP_800,
        .description = sExpCandyXSDesc,
        .keepItem = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_PARTY_MENU,
        .itemEffect = gItemEffect_RareCandy,
        .fieldUseFunc = ItemUseOutOfBattle_RareCandy,
        .flingPower = 30,
    },

    [ITEM_EXP_CANDY_M] =
    {
        .name = sExpCandyMName,
        .plural = sExpCandyMPluralName,
        .itemId = ITEM_EXP_CANDY_M,
        .price = CANDY_COST(1000),
        .holdEffectParam = EXP_3000,
        .description = sExpCandyMDesc,
        .keepItem = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_PARTY_MENU,
        .itemEffect = gItemEffect_RareCandy,
        .fieldUseFunc = ItemUseOutOfBattle_RareCandy,
        .flingPower = 30,
    },

    [ITEM_EXP_CANDY_L] =
    {
        .name = sExpCandyLName,
        .plural = sExpCandyLPluralName,
        .itemId = ITEM_EXP_CANDY_L,
        .price = CANDY_COST(3000),
        .holdEffectParam = EXP_10000,
        .description = sExpCandyLDesc,
        .keepItem = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_PARTY_MENU,
        .itemEffect = gItemEffect_RareCandy,
        .fieldUseFunc = ItemUseOutOfBattle_RareCandy,
        .flingPower = 30,
    },

    [ITEM_EXP_CANDY_XL] =
    {
        .name = sExpCandyXLName,
        .plural = sExpCandyXLPluralName,
        .itemId = ITEM_EXP_CANDY_XL,
        .price = CANDY_COST(10000),
        .holdEffectParam = EXP_30000,
        .description = sExpCandyXLDesc,
        .keepItem = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_PARTY_MENU,
        .itemEffect = gItemEffect_RareCandy,
        .fieldUseFunc = ItemUseOutOfBattle_RareCandy,
        .flingPower = 30,
    },

    [ITEM_DYNAMAX_CANDY] =
    {
        .name = sDynamaxCandyName,
        .plural = sDynamaxCandyPluralName,
        .itemId = ITEM_DYNAMAX_CANDY,
        .price = 0,
        .description = sDynamaxCandyDesc,
        .keepItem = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse, // Todo
        .flingPower = 30,
    },

// #pragma endregion

// #pragma region Flutes
// Medicinal Flutes

    [ITEM_BLUE_FLUTE] =
    {
        .name = sBlueFluteName,
        .itemId = ITEM_BLUE_FLUTE,
        .price = CANDY_COST(20),
        .description = sBlueFluteDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = ITEM_B_USE_MEDICINE,
        .itemEffect = gItemEffect_HealSleep,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .flingPower = 30,
    },

    [ITEM_YELLOW_FLUTE] =
    {
        .name = sYellowFluteName,
        .itemId = ITEM_YELLOW_FLUTE,
        .price = CANDY_COST(20),
        .description = sYellowFluteDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = ITEM_B_USE_MEDICINE,
        .itemEffect = gItemEffect_HealConfusion,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .flingPower = 30,
    },

    [ITEM_RED_FLUTE] =
    {
        .name = sRedFluteName,
        .itemId = ITEM_RED_FLUTE,
        .price = CANDY_COST(20),
        .description = sRedFluteDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = ITEM_B_USE_MEDICINE,
        .itemEffect = gItemEffect_HealInfatuation,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .flingPower = 30,
    },

// Encounter-modifying Flutes

    [ITEM_BLACK_FLUTE] =
    {
        .name = sBlackFluteName,
        .itemId = ITEM_BLACK_FLUTE,
        .price = CANDY_COST(20),
        .holdEffectParam = 50,
        .keepItem = TRUE,
        .description = sBlackFluteDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_BlackWhiteFlute,
        .flingPower = 30,
    },

    [ITEM_WHITE_FLUTE] =
    {
        .name = sWhiteFluteName,
        .itemId = ITEM_WHITE_FLUTE,
        .price = CANDY_COST(20),
        .holdEffectParam = 150,
        .keepItem = TRUE,
        .description = sWhiteFluteDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_BlackWhiteFlute,
        .flingPower = 30,
    },

// #pragma endregion

// #pragma region Encounter Modifiers

    [ITEM_REPEL] =
    {
        .name = sRepelName,
        .itemId = ITEM_REPEL,
        .price = CANDY_COST(400),
        .holdEffectParam = 100,
        .description = sRepelDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Repel,
        .flingPower = 30,
    },

    [ITEM_SUPER_REPEL] =
    {
        .name = sSuperRepelName,
        .itemId = ITEM_SUPER_REPEL,
        .price = CANDY_COST(700),
        .holdEffectParam = 200,
        .description = sSuperRepelDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Repel,
        .flingPower = 30,
    },

    [ITEM_MAX_REPEL] =
    {
        .name = sMaxRepelName,
        .itemId = ITEM_MAX_REPEL,
        .price = CANDY_COST(900),
        .holdEffectParam = 250,
        .description = sMaxRepelDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Repel,
        .flingPower = 30,
    },

    [ITEM_LURE] =
    {
        .name = sLureName,
        .itemId = ITEM_LURE,
        .price = CANDY_COST(350),
        .holdEffectParam = 100,
        .description = sLureDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
        .flingPower = 30,
    },

    [ITEM_SUPER_LURE] =
    {
        .name = sSuperLureName,
        .itemId = ITEM_SUPER_LURE,
        .price = CANDY_COST(500),
        .holdEffectParam = 200,
        .description = sSuperLureDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
        .flingPower = 30,
    },

    [ITEM_MAX_LURE] =
    {
        .name = sMaxLureName,
        .itemId = ITEM_MAX_LURE,
        .price = CANDY_COST(700),
        .holdEffectParam = 250,
        .description = sMaxLureDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
        .flingPower = 30,
    },

    [ITEM_ESCAPE_ROPE] =
    {
        .name = sEscapeRopeName,
        .itemId = ITEM_ESCAPE_ROPE,
        .description = sEscapeRopeDesc,
        .keepItem = TRUE,
#if I_KEY_ESCAPE_ROPE >= GEN_8
        .price = 0,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
#else
        .price = CANDY_COST(1000),
        .pocket = POCKET_ITEMS,
#endif
        .type = ITEM_USE_FIELD,
        .fieldUseFunc = ItemUseOutOfBattle_EscapeRope,
        .flingPower = 30,
    },

// #pragma endregion

// #pragma region X Items

    [ITEM_X_ATTACK] =
    {
        .name = sXAttackName,
        .itemId = ITEM_X_ATTACK,
        .price = CANDY_COST(1000),
        .description = sXAttackDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = ITEM_B_USE_OTHER,
        .itemEffect = gItemEffect_XAttack,
        .battleUseFunc = ItemUseInBattle_StatIncrease,
        .flingPower = 30,
    },

    [ITEM_X_DEFENSE] =
    {
        .name = sXDefenseName,
        .itemId = ITEM_X_DEFENSE,
        .price = CANDY_COST(2000),
        .description = sXDefenseDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = ITEM_B_USE_OTHER,
        .itemEffect = gItemEffect_XDefense,
        .battleUseFunc = ItemUseInBattle_StatIncrease,
        .flingPower = 30,
    },

    [ITEM_X_SP_ATK] =
    {
        .name = sXSpAtkName,
        .itemId = ITEM_X_SP_ATK,
        .price = CANDY_COST(1000),
        .description = sXSpAtkDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = ITEM_B_USE_OTHER,
        .itemEffect = gItemEffect_XSpecialAttack,
        .battleUseFunc = ItemUseInBattle_StatIncrease,
        .flingPower = 30,
    },

    [ITEM_X_SP_DEF] =
    {
        .name = sXSpDefName,
        .itemId = ITEM_X_SP_DEF,
        .price = CANDY_COST(2000),
        .description = sXSpDefDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = ITEM_B_USE_OTHER,
        .itemEffect = gItemEffect_XSpecialDefense,
        .battleUseFunc = ItemUseInBattle_StatIncrease,
        .flingPower = 30,
    },

    [ITEM_X_SPEED] =
    {
        .name = sXSpeedName,
        .itemId = ITEM_X_SPEED,
        .price = CANDY_COST(1000),
        .description = sXSpeedDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = ITEM_B_USE_OTHER,
        .itemEffect = gItemEffect_XSpeed,
        .battleUseFunc = ItemUseInBattle_StatIncrease,
        .flingPower = 30,
    },

    [ITEM_X_ACCURACY] =
    {
        .name = sXAccuracyName,
        .itemId = ITEM_X_ACCURACY,
        .price = CANDY_COST(1000),
        .description = sXAccuracyDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = ITEM_B_USE_OTHER,
        .itemEffect = gItemEffect_XAccuracy,
        .battleUseFunc = ItemUseInBattle_StatIncrease,
        .flingPower = 30,
    },

    [ITEM_DIRE_HIT] =
    {
        .name = sDireHitName,
        .itemId = ITEM_DIRE_HIT,
        .price = CANDY_COST(1000),
        .description = sDireHitDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = ITEM_B_USE_OTHER,
        .itemEffect = gItemEffect_DireHit,
        .battleUseFunc = ItemUseInBattle_StatIncrease,
        .flingPower = 30,
    },

    [ITEM_GUARD_SPEC] =
    {
        .name = sGuardSpecName,
        .itemId = ITEM_GUARD_SPEC,
        .price = CANDY_COST(1500),
        .description = sGuardSpecDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = ITEM_B_USE_OTHER,
        .itemEffect = gItemEffect_GuardSpec,
        .battleUseFunc = ItemUseInBattle_StatIncrease,
        .flingPower = 30,
    },

    [ITEM_POKE_DOLL] =
    {
        .name = sPokeDollName,
        .itemId = ITEM_POKE_DOLL,
        .price = CANDY_COST(100),
        .description = sPokeDollDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = ITEM_B_USE_OTHER,
        .battleUseFunc = ItemUseInBattle_Escape,
        .flingPower = 30,
    },

    [ITEM_FLUFFY_TAIL] =
    {
        .name = sFluffyTailName,
        .itemId = ITEM_FLUFFY_TAIL,
        .price = CANDY_COST(100),
        .description = sFluffyTailDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = ITEM_B_USE_OTHER,
        .battleUseFunc = ItemUseInBattle_Escape,
        .flingPower = 30,
    },

    [ITEM_POKE_TOY] =
    {
        .name = sPokeToyName,
        .itemId = ITEM_POKE_TOY,
        .price = CANDY_COST(100),
        .description = sPokeToyDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = ITEM_B_USE_OTHER,
        .battleUseFunc = ItemUseInBattle_Escape,
        .flingPower = 30,
    },

    [ITEM_MAX_MUSHROOMS] =
    {
        .name = sMaxMushroomsName,
        .quantum = sQuantum_Cluster,
        .itemId = ITEM_MAX_MUSHROOMS,
        .price = CANDY_COST(8000),
        .description = sMaxMushroomsDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = ITEM_B_USE_OTHER,
        .battleUseFunc = ItemUseInBattle_StatIncrease, // Todo
        .flingPower = 30,
    },

// #pragma endregion

// #pragma region Treasures

    [ITEM_BOTTLE_CAP] =
    {
        .name = sBottleCapName,
        .itemId = ITEM_BOTTLE_CAP,
        .price = CANDY_COST(5000),
        .description = sBottleCapDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_GOLD_BOTTLE_CAP] =
    {
        .name = sGoldBottleCapName,
        .itemId = ITEM_GOLD_BOTTLE_CAP,
        .price = CANDY_COST(10000),
        .description = sGoldBottleCapDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_NUGGET] =
    {
        .name = sNuggetName,
        .itemId = ITEM_NUGGET,
        .price = CANDY_COST(10000),
        .description = sNuggetDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_BIG_NUGGET] =
    {
        .name = sBigNuggetName,
        .itemId = ITEM_BIG_NUGGET,
        .price = CANDY_COST(40000),
        .description = sBigNuggetDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_TINY_MUSHROOM] =
    {
        .name = sTinyMushroomName,
        .itemId = ITEM_TINY_MUSHROOM,
        .price = CANDY_COST(500),
        .description = sTinyMushroomDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_BIG_MUSHROOM] =
    {
        .name = sBigMushroomName,
        .itemId = ITEM_BIG_MUSHROOM,
        .price = CANDY_COST(5000),
        .description = sBigMushroomDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_BALM_MUSHROOM] =
    {
        .name = sBalmMushroomName,
        .itemId = ITEM_BALM_MUSHROOM,
        .price = CANDY_COST(15000),
        .description = sBalmMushroomDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_PEARL] =
    {
        .name = sPearlName,
        .itemId = ITEM_PEARL,
        .price = CANDY_COST(2000),
        .description = sPearlDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_BIG_PEARL] =
    {
        .name = sBigPearlName,
        .itemId = ITEM_BIG_PEARL,
        .price = CANDY_COST(8000),
        .description = sBigPearlDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_PEARL_STRING] =
    {
        .name = sPearlStringName,
        .itemId = ITEM_PEARL_STRING,
        .price = CANDY_COST(20000),
        .description = sPearlStringDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_STARDUST] =
    {
        .name = sStardustName,
        .quantum = sQuantum_Bag,
        .itemId = ITEM_STARDUST,
        .price = CANDY_COST(3000),
        .description = sStardustDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_STAR_PIECE] =
    {
        .name = sStarPieceName,
        .itemId = ITEM_STAR_PIECE,
        .price = CANDY_COST(12000),
        .description = sStarPieceDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_COMET_SHARD] =
    {
        .name = sCometShardName,
        .itemId = ITEM_COMET_SHARD,
        .price = CANDY_COST(25000),
        .description = sCometShardDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_SHOAL_SALT] =
    {
        .name = sShoalSaltName,
        .quantum = sQuantum_Pile,
        .itemId = ITEM_SHOAL_SALT,
        .price = CANDY_COST(20),
        .description = sShoalSaltDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_SHOAL_SHELL] =
    {
        .name = sShoalShellName,
        .itemId = ITEM_SHOAL_SHELL,
        .price = CANDY_COST(20),
        .description = sShoalShellDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_RED_SHARD] =
    {
        .name = sRedShardName,
        .itemId = ITEM_RED_SHARD,
        .price = CANDY_COST(1000),
        .description = sRedShardDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_BLUE_SHARD] =
    {
        .name = sBlueShardName,
        .itemId = ITEM_BLUE_SHARD,
        .price = CANDY_COST(1000),
        .description = sBlueShardDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_YELLOW_SHARD] =
    {
        .name = sYellowShardName,
        .itemId = ITEM_YELLOW_SHARD,
        .price = CANDY_COST(1000),
        .description = sYellowShardDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_GREEN_SHARD] =
    {
        .name = sGreenShardName,
        .itemId = ITEM_GREEN_SHARD,
        .price = CANDY_COST(1000),
        .description = sGreenShardDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_HEART_SCALE] =
    {
        .name = sHeartScaleName,
        .itemId = ITEM_HEART_SCALE,
        .price = CANDY_COST(100),
        .description = sHeartScaleDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_HONEY] =
    {
        .name = sHoneyName,
        .quantum = sQuantum_Jar,
        .itemId = ITEM_HONEY,
        .price = CANDY_COST(300),
        .description = sHoneyDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_RARE_BONE] =
    {
        .name = sRareBoneName,
        .itemId = ITEM_RARE_BONE,
        .price = CANDY_COST(5000),
        .description = sRareBoneDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 100,
    },

    [ITEM_ODD_KEYSTONE] =
    {
        .name = sOddKeystoneName,
        .itemId = ITEM_ODD_KEYSTONE,
        .price = CANDY_COST(2100),
        .description = sOddKeystoneDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_PRETTY_FEATHER] =
    {
        .name = sPrettyFeatherName,
        .itemId = ITEM_PRETTY_FEATHER,
        .price = CANDY_COST(1000),
        .description = sPrettyFeatherDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 20,
    },

    [ITEM_RELIC_COPPER] =
    {
        .name = sRelicCopperName,
        .itemId = ITEM_RELIC_COPPER,
        .price = CANDY_COST(0),
        .description = sRelicCopperDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_RELIC_SILVER] =
    {
        .name = sRelicSilverName,
        .itemId = ITEM_RELIC_SILVER,
        .price = CANDY_COST(0),
        .description = sRelicSilverDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_RELIC_GOLD] =
    {
        .name = sRelicGoldName,
        .itemId = ITEM_RELIC_GOLD,
        .price = CANDY_COST(0),
        .description = sRelicGoldDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_RELIC_VASE] =
    {
        .name = sRelicVaseName,
        .itemId = ITEM_RELIC_VASE,
        .price = CANDY_COST(0),
        .description = sRelicVaseDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_RELIC_BAND] =
    {
        .name = sRelicBandName,
        .itemId = ITEM_RELIC_BAND,
        .price = CANDY_COST(0),
        .description = sRelicBandDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_RELIC_STATUE] =
    {
        .name = sRelicStatueName,
        .itemId = ITEM_RELIC_STATUE,
        .price = CANDY_COST(0),
        .description = sRelicStatueDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_RELIC_CROWN] =
    {
        .name = sRelicCrownName,
        .itemId = ITEM_RELIC_CROWN,
        .price = CANDY_COST(0),
        .description = sRelicCrownDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_STRANGE_SOUVENIR] =
    {
        .name = sStrangeSouvenirName,
        .itemId = ITEM_STRANGE_SOUVENIR,
        .price = CANDY_COST(3000),
        .description = sStrangeSouvenirDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

// #pragma endregion

// #pragma region Fossils

    [ITEM_HELIX_FOSSIL] =
    {
        .name = sHelixFossilName,
        .itemId = ITEM_HELIX_FOSSIL,
        .description = sHelixFossilDesc,
#if I_KEY_FOSSILS >= GEN_4
        .price = CANDY_COST(7000),
        .pocket = POCKET_ITEMS,
#else
        .price = 0,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
#endif
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 100,
    },

    [ITEM_DOME_FOSSIL] =
    {
        .name = sDomeFossilName,
        .itemId = ITEM_DOME_FOSSIL,
        .description = sDomeFossilDesc,
#if I_KEY_FOSSILS >= GEN_4
        .price = CANDY_COST(7000),
        .pocket = POCKET_ITEMS,
#else
        .price = 0,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
#endif
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 100,
    },

    [ITEM_OLD_AMBER] =
    {
        .name = sOldAmberName,
        .itemId = ITEM_OLD_AMBER,
        .description = sOldAmberDesc,
#if I_KEY_FOSSILS >= GEN_4
        .price = 10000,
        .pocket = POCKET_ITEMS,
#else
        .price = 0,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
#endif
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 100,
    },

    [ITEM_ROOT_FOSSIL] =
    {
        .name = sRootFossilName,
        .itemId = ITEM_ROOT_FOSSIL,
        .description = sRootFossilDesc,
#if I_KEY_FOSSILS >= GEN_4
        .price = CANDY_COST(7000),
        .pocket = POCKET_ITEMS,
#else
        .price = 0,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
#endif
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 100,
    },

    [ITEM_CLAW_FOSSIL] =
    {
        .name = sClawFossilName,
        .itemId = ITEM_CLAW_FOSSIL,
        .description = sClawFossilDesc,
#if I_KEY_FOSSILS >= GEN_4
        .price = CANDY_COST(7000),
        .pocket = POCKET_ITEMS,
#else
        .price = 0,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
#endif
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 100,
    },

    [ITEM_ARMOR_FOSSIL] =
    {
        .name = sArmorFossilName,
        .itemId = ITEM_ARMOR_FOSSIL,
        .price = CANDY_COST(7000),
        .description = sArmorFossilDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 100,
    },

    [ITEM_SKULL_FOSSIL] =
    {
        .name = sSkullFossilName,
        .itemId = ITEM_SKULL_FOSSIL,
        .price = CANDY_COST(7000),
        .description = sSkullFossilDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 100,
    },

    [ITEM_COVER_FOSSIL] =
    {
        .name = sCoverFossilName,
        .itemId = ITEM_COVER_FOSSIL,
        .price = CANDY_COST(7000),
        .description = sCoverFossilDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 100,
    },

    [ITEM_PLUME_FOSSIL] =
    {
        .name = sPlumeFossilName,
        .itemId = ITEM_PLUME_FOSSIL,
        .price = CANDY_COST(7000),
        .description = sPlumeFossilDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 100,
    },

    [ITEM_JAW_FOSSIL] =
    {
        .name = sJawFossilName,
        .itemId = ITEM_JAW_FOSSIL,
        .price = CANDY_COST(7000),
        .description = sJawFossilDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 100,
    },

    [ITEM_SAIL_FOSSIL] =
    {
        .name = sSailFossilName,
        .itemId = ITEM_SAIL_FOSSIL,
        .price = CANDY_COST(7000),
        .description = sSailFossilDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 100,
    },

    [ITEM_FOSSILIZED_BIRD] =
    {
        .name = sFossilizedBirdName,
        .quantum = sQuantum_Sample,
        .itemId = ITEM_FOSSILIZED_BIRD,
        .price = CANDY_COST(5000),
        .description = sFossilizedBirdDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 100,
    },

    [ITEM_FOSSILIZED_FISH] =
    {
        .name = sFossilizedFishName,
        .quantum = sQuantum_Sample,
        .itemId = ITEM_FOSSILIZED_FISH,
        .price = CANDY_COST(5000),
        .description = sFossilizedFishDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 100,
    },

    [ITEM_FOSSILIZED_DRAKE] =
    {
        .name = sFossilizedDrakeName,
        .quantum = sQuantum_Sample,
        .itemId = ITEM_FOSSILIZED_DRAKE,
        .price = CANDY_COST(5000),
        .description = sFossilizedDrakeDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 100,
    },

    [ITEM_FOSSILIZED_DINO] =
    {
        .name = sFossilizedDinoName,
        .quantum = sQuantum_Sample,
        .itemId = ITEM_FOSSILIZED_DINO,
        .price = CANDY_COST(5000),
        .description = sFossilizedDinoDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 100,
    },

// #pragma endregion

// #pragma region Mulch

    [ITEM_GROWTH_MULCH] =
    {
        .name = sGrowthMulchName,
        .quantum = sQuantum_Bag,
        .itemId = ITEM_GROWTH_MULCH,
        .price = CANDY_COST(200),
        .description = sGrowthMulchDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse, // Todo
        .flingPower = 30,
    },

    [ITEM_DAMP_MULCH] =
    {
        .name = sDampMulchName,
        .quantum = sQuantum_Bag,
        .itemId = ITEM_DAMP_MULCH,
        .price = CANDY_COST(200),
        .description = sDampMulchDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse, // Todo
        .flingPower = 30,
    },

    [ITEM_STABLE_MULCH] =
    {
        .name = sStableMulchName,
        .quantum = sQuantum_Bag,
        .itemId = ITEM_STABLE_MULCH,
        .price = CANDY_COST(200),
        .description = sStableMulchDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse, // Todo
        .flingPower = 30,
    },

    [ITEM_GOOEY_MULCH] =
    {
        .name = sGooeyMulchName,
        .quantum = sQuantum_Bag,
        .itemId = ITEM_GOOEY_MULCH,
        .price = CANDY_COST(200),
        .description = sGooeyMulchDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse, // Todo
        .flingPower = 30,
    },

    [ITEM_RICH_MULCH] =
    {
        .name = sRichMulchName,
        .quantum = sQuantum_Bag,
        .itemId = ITEM_RICH_MULCH,
        .price = CANDY_COST(200),
        .description = sRichMulchDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse, // Todo
        .flingPower = 30,
    },

    [ITEM_SURPRISE_MULCH] =
    {
        .name = sSurpriseMulchName,
        .quantum = sQuantum_Bag,
        .itemId = ITEM_SURPRISE_MULCH,
        .price = CANDY_COST(200),
        .description = sSurpriseMulchDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse, // Todo
        .flingPower = 30,
    },

    [ITEM_BOOST_MULCH] =
    {
        .name = sBoostMulchName,
        .quantum = sQuantum_Bag,
        .itemId = ITEM_BOOST_MULCH,
        .price = CANDY_COST(200),
        .description = sBoostMulchDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse, // Todo
        .flingPower = 30,
    },

    [ITEM_AMAZE_MULCH] =
    {
        .name = sAmazeMulchName,
        .quantum = sQuantum_Bag,
        .itemId = ITEM_AMAZE_MULCH,
        .price = CANDY_COST(200),
        .description = sAmazeMulchDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse, // Todo
        .flingPower = 30,
    },
    
// #pragma endregion

// #pragma region Apricorns

    [ITEM_RED_APRICORN] =
    {
        .name = sRedApricornName,
        .itemId = ITEM_RED_APRICORN,
        .price = CANDY_COST(200),
        .description = sRedApricornDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

    [ITEM_BLUE_APRICORN] =
    {
        .name = sBlueApricornName,
        .itemId = ITEM_BLUE_APRICORN,
        .price = CANDY_COST(200),
        .description = sBlueApricornDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

    [ITEM_YELLOW_APRICORN] =
    {
        .name = sYellowApricornName,
        .itemId = ITEM_YELLOW_APRICORN,
        .price = CANDY_COST(200),
        .description = sYellowApricornDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

    [ITEM_GREEN_APRICORN] =
    {
        .name = sGreenApricornName,
        .itemId = ITEM_GREEN_APRICORN,
        .price = CANDY_COST(200),
        .description = sGreenApricornDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

    [ITEM_PINK_APRICORN] =
    {
        .name = sPinkApricornName,
        .itemId = ITEM_PINK_APRICORN,
        .price = CANDY_COST(200),
        .description = sPinkApricornDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

    [ITEM_WHITE_APRICORN] =
    {
        .name = sWhiteApricornName,
        .itemId = ITEM_WHITE_APRICORN,
        .price = CANDY_COST(200),
        .description = sWhiteApricornDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

    [ITEM_BLACK_APRICORN] =
    {
        .name = sBlackApricornName,
        .itemId = ITEM_BLACK_APRICORN,
        .price = CANDY_COST(200),
        .description = sBlackApricornDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

    [ITEM_WISHING_PIECE] =
    {
        .name = sWishingPieceName,
        .itemId = ITEM_WISHING_PIECE,
        .price = CANDY_COST(20),
        .description = sWishingPieceDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse, // Todo
        .flingPower = 50,
    },

    [ITEM_GALARICA_TWIG] =
    {
        .name = sGalaricaTwigName,
        .itemId = ITEM_GALARICA_TWIG,
        .price = CANDY_COST(40),
        .description = sGalaricaTwigDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_ARMORITE_ORE] =
    {
        .name = sArmoriteOreName,
        .itemId = ITEM_ARMORITE_ORE,
        .price = CANDY_COST(40),
        .description = sArmoriteOreDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_DYNITE_ORE] =
    {
        .name = sDyniteOreName,
        .itemId = ITEM_DYNITE_ORE,
        .price = CANDY_COST(20),
        .description = sDyniteOreDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

// #pragma endregion

// #pragma region Mail

    [ITEM_ORANGE_MAIL] =
    {
        .name = sOrangeMailName,
        .quantum = sQuantum_Mail,
        .itemId = ITEM_ORANGE_MAIL,
        .price = CANDY_COST(50),
        .description = sOrangeMailDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_MAIL,
        .fieldUseFunc = ItemUseOutOfBattle_Mail,
        .secondaryId = ITEM_TO_MAIL(ITEM_ORANGE_MAIL),
    },

    [ITEM_HARBOR_MAIL] =
    {
        .name = sHarborMailName,
        .quantum = sQuantum_Mail,
        .itemId = ITEM_HARBOR_MAIL,
        .price = CANDY_COST(50),
        .description = sHarborMailDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_MAIL,
        .fieldUseFunc = ItemUseOutOfBattle_Mail,
        .secondaryId = ITEM_TO_MAIL(ITEM_HARBOR_MAIL),
    },

    [ITEM_GLITTER_MAIL] =
    {
        .name = sGlitterMailName,
        .quantum = sQuantum_Mail,
        .itemId = ITEM_GLITTER_MAIL,
        .price = CANDY_COST(50),
        .description = sGlitterMailDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_MAIL,
        .fieldUseFunc = ItemUseOutOfBattle_Mail,
        .secondaryId = ITEM_TO_MAIL(ITEM_GLITTER_MAIL),
    },

    [ITEM_MECH_MAIL] =
    {
        .name = sMechMailName,
        .quantum = sQuantum_Mail,
        .itemId = ITEM_MECH_MAIL,
        .price = CANDY_COST(50),
        .description = sMechMailDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_MAIL,
        .fieldUseFunc = ItemUseOutOfBattle_Mail,
        .secondaryId = ITEM_TO_MAIL(ITEM_MECH_MAIL),
    },

    [ITEM_WOOD_MAIL] =
    {
        .name = sWoodMailName,
        .quantum = sQuantum_Mail,
        .itemId = ITEM_WOOD_MAIL,
        .price = CANDY_COST(50),
        .description = sWoodMailDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_MAIL,
        .fieldUseFunc = ItemUseOutOfBattle_Mail,
        .secondaryId = ITEM_TO_MAIL(ITEM_WOOD_MAIL),
    },

    [ITEM_WAVE_MAIL] =
    {
        .name = sWaveMailName,
        .quantum = sQuantum_Mail,
        .itemId = ITEM_WAVE_MAIL,
        .price = CANDY_COST(50),
        .description = sWaveMailDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_MAIL,
        .fieldUseFunc = ItemUseOutOfBattle_Mail,
        .secondaryId = ITEM_TO_MAIL(ITEM_WAVE_MAIL),
    },

    [ITEM_BEAD_MAIL] =
    {
        .name = sBeadMailName,
        .quantum = sQuantum_Mail,
        .itemId = ITEM_BEAD_MAIL,
        .price = CANDY_COST(50),
        .description = sBeadMailDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_MAIL,
        .fieldUseFunc = ItemUseOutOfBattle_Mail,
        .secondaryId = ITEM_TO_MAIL(ITEM_BEAD_MAIL),
    },

    [ITEM_SHADOW_MAIL] =
    {
        .name = sShadowMailName,
        .quantum = sQuantum_Mail,
        .itemId = ITEM_SHADOW_MAIL,
        .price = CANDY_COST(50),
        .description = sShadowMailDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_MAIL,
        .fieldUseFunc = ItemUseOutOfBattle_Mail,
        .secondaryId = ITEM_TO_MAIL(ITEM_SHADOW_MAIL),
    },

    [ITEM_TROPIC_MAIL] =
    {
        .name = sTropicMailName,
        .quantum = sQuantum_Mail,
        .itemId = ITEM_TROPIC_MAIL,
        .price = CANDY_COST(50),
        .description = sTropicMailDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_MAIL,
        .fieldUseFunc = ItemUseOutOfBattle_Mail,
        .secondaryId = ITEM_TO_MAIL(ITEM_TROPIC_MAIL),
    },

    [ITEM_DREAM_MAIL] =
    {
        .name = sDreamMailName,
        .quantum = sQuantum_Mail,
        .itemId = ITEM_DREAM_MAIL,
        .price = CANDY_COST(50),
        .description = sDreamMailDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_MAIL,
        .fieldUseFunc = ItemUseOutOfBattle_Mail,
        .secondaryId = ITEM_TO_MAIL(ITEM_DREAM_MAIL),
    },

    [ITEM_FAB_MAIL] =
    {
        .name = sFabMailName,
        .quantum = sQuantum_Mail,
        .itemId = ITEM_FAB_MAIL,
        .price = CANDY_COST(50),
        .description = sFabMailDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_MAIL,
        .fieldUseFunc = ItemUseOutOfBattle_Mail,
        .secondaryId = ITEM_TO_MAIL(ITEM_FAB_MAIL),
    },

    [ITEM_RETRO_MAIL] =
    {
        .name = sRetroMailName,
        .quantum = sQuantum_Mail,
        .itemId = ITEM_RETRO_MAIL,
        .price = CANDY_COST(50),
        .description = sRetroMailDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_MAIL,
        .fieldUseFunc = ItemUseOutOfBattle_Mail,
        .secondaryId = ITEM_TO_MAIL(ITEM_RETRO_MAIL),
    },

// #pragma endregion

// #pragma region Evolution Items

    [ITEM_FIRE_STONE] =
    {
        .name = sFireStoneName,
        .itemId = ITEM_FIRE_STONE,
        .price = CANDY_COST(3000),
        .description = sFireStoneDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .itemEffect = gItemEffect_EvoItem,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .flingPower = 30,
    },

    [ITEM_WATER_STONE] =
    {
        .name = sWaterStoneName,
        .itemId = ITEM_WATER_STONE,
        .price = CANDY_COST(3000),
        .description = sWaterStoneDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .itemEffect = gItemEffect_EvoItem,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .flingPower = 30,
    },

    [ITEM_THUNDER_STONE] =
    {
        .name = sThunderStoneName,
        .itemId = ITEM_THUNDER_STONE,
        .price = CANDY_COST(3000),
        .description = sThunderStoneDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .itemEffect = gItemEffect_EvoItem,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .flingPower = 30,
    },

    [ITEM_LEAF_STONE] =
    {
        .name = sLeafStoneName,
        .itemId = ITEM_LEAF_STONE,
        .price = CANDY_COST(3000),
        .description = sLeafStoneDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .itemEffect = gItemEffect_EvoItem,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .flingPower = 30,
    },

    [ITEM_ICE_STONE] =
    {
        .name = sIceStoneName,
        .itemId = ITEM_ICE_STONE,
        .price = CANDY_COST(3000),
        .description = sIceStoneDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .itemEffect = gItemEffect_EvoItem,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .flingPower = 30,
    },

    [ITEM_SUN_STONE] =
    {
        .name = sSunStoneName,
        .itemId = ITEM_SUN_STONE,
        .price = CANDY_COST(3000),
        .description = sSunStoneDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .itemEffect = gItemEffect_EvoItem,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .flingPower = 30,
    },

    [ITEM_MOON_STONE] =
    {
        .name = sMoonStoneName,
        .itemId = ITEM_MOON_STONE,
        .price = CANDY_COST(3000),
        .description = sMoonStoneDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .itemEffect = gItemEffect_EvoItem,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .flingPower = 30,
    },

    [ITEM_SHINY_STONE] =
    {
        .name = sShinyStoneName,
        .itemId = ITEM_SHINY_STONE,
        .price = CANDY_COST(3000),
        .description = sShinyStoneDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .itemEffect = gItemEffect_EvoItem,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .flingPower = 30,
    },

    [ITEM_DUSK_STONE] =
    {
        .name = sDuskStoneName,
        .itemId = ITEM_DUSK_STONE,
        .price = CANDY_COST(3000),
        .description = sDuskStoneDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .itemEffect = gItemEffect_EvoItem,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .flingPower = 80,
    },

    [ITEM_DAWN_STONE] =
    {
        .name = sDawnStoneName,
        .itemId = ITEM_DAWN_STONE,
        .price = CANDY_COST(3000),
        .description = sDawnStoneDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .itemEffect = gItemEffect_EvoItem,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .flingPower = 80,
    },

    [ITEM_SWEET_APPLE] =
    {
        .name = sSweetAppleName,
        .itemId = ITEM_SWEET_APPLE,
        .price = CANDY_COST(2200),
        .description = sSweetAppleDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .itemEffect = gItemEffect_EvoItem,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .flingPower = 30,
    },

    [ITEM_TART_APPLE] =
    {
        .name = sTartAppleName,
        .itemId = ITEM_TART_APPLE,
        .price = CANDY_COST(2200),
        .description = sTartAppleDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .itemEffect = gItemEffect_EvoItem,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .flingPower = 30,
    },

    [ITEM_CRACKED_POT] =
    {
        .name = sCrackedPotName,
        .itemId = ITEM_CRACKED_POT,
        .price = CANDY_COST(1600),
        .description = sCrackedPotDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .itemEffect = gItemEffect_EvoItem,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .flingPower = 80,
    },

    [ITEM_CHIPPED_POT] =
    {
        .name = sChippedPotName,
        .itemId = ITEM_CHIPPED_POT,
        .price = CANDY_COST(38000),
        .description = sChippedPotDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .itemEffect = gItemEffect_EvoItem,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .flingPower = 80,
    },

    [ITEM_GALARICA_CUFF] =
    {
        .name = sGalaricaCuffName,
        .itemId = ITEM_GALARICA_CUFF,
        .price = CANDY_COST(6000),
        .description = sGalaricaCuffDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .itemEffect = gItemEffect_EvoItem,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .flingPower = 30,
    },

    [ITEM_GALARICA_WREATH] =
    {
        .name = sGalaricaWreathName,
        .itemId = ITEM_GALARICA_WREATH,
        .price = CANDY_COST(6000),
        .description = sGalaricaWreathDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .itemEffect = gItemEffect_EvoItem,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .flingPower = 30,
    },

    [ITEM_DRAGON_SCALE] =
    {
        .name = sDragonScaleName,
        .itemId = ITEM_DRAGON_SCALE,
        .price = CANDY_COST(2000),
        .holdEffect = HOLD_EFFECT_DRAGON_SCALE,
        .keepItem = TRUE,
        .holdEffectParam = 10,
        .description = sDragonScaleDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_UPGRADE] =
    {
        .name = sUpgradeName,
        .itemId = ITEM_UPGRADE,
        .price = CANDY_COST(2000),
        .holdEffect = HOLD_EFFECT_UPGRADE,
        .keepItem = TRUE,
        .description = sUpgradeDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_PROTECTOR] =
    {
        .name = sProtectorName,
        .itemId = ITEM_PROTECTOR,
        .price = CANDY_COST(2000),
        .description = sProtectorDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_ELECTIRIZER] =
    {
        .name = sElectirizerName,
        .itemId = ITEM_ELECTIRIZER,
        .price = CANDY_COST(2000),
        .description = sElectirizerDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_MAGMARIZER] =
    {
        .name = sMagmarizerName,
        .itemId = ITEM_MAGMARIZER,
        .price = CANDY_COST(2000),
        .description = sMagmarizerDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_DUBIOUS_DISC] =
    {
        .name = sDubiousDiscName,
        .itemId = ITEM_DUBIOUS_DISC,
        .price = CANDY_COST(2000),
        .description = sDubiousDiscDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 50,
    },

    [ITEM_REAPER_CLOTH] =
    {
        .name = sReaperClothName,
        .quantum = sQuantum_Scrap,
        .itemId = ITEM_REAPER_CLOTH,
        .price = CANDY_COST(2000),
        .description = sReaperClothDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_PRISM_SCALE] =
    {
        .name = sPrismScaleName,
        .itemId = ITEM_PRISM_SCALE,
        .price = CANDY_COST(2000),
        .description = sPrismScaleDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_WHIPPED_DREAM] =
    {
        .name = sWhippedDreamName,
        .quantum = sQuantum_Dollop,
        .plural = ITEM_NAME_PLURAL_ES,
        .itemId = ITEM_WHIPPED_DREAM,
        .price = CANDY_COST(2000),
        .description = sWhippedDreamDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_SACHET] =
    {
        .name = sSachetName,
        .itemId = ITEM_SACHET,
        .price = CANDY_COST(2000),
        .description = sSachetDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_OVAL_STONE] =
    {
        .name = sOvalStoneName,
        .itemId = ITEM_OVAL_STONE,
        .price = CANDY_COST(2000),
        .description = sOvalStoneDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_STRAWBERRY_SWEET] =
    {
        .name = sStrawberrySweetName,
        .itemId = ITEM_STRAWBERRY_SWEET,
        .price = CANDY_COST(500),
        .description = sStrawberrySweetDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_LOVE_SWEET] =
    {
        .name = sLoveSweetName,
        .itemId = ITEM_LOVE_SWEET,
        .price = CANDY_COST(500),
        .description = sLoveSweetDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_BERRY_SWEET] =
    {
        .name = sBerrySweetName,
        .itemId = ITEM_BERRY_SWEET,
        .price = CANDY_COST(500),
        .description = sBerrySweetDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_CLOVER_SWEET] =
    {
        .name = sCloverSweetName,
        .itemId = ITEM_CLOVER_SWEET,
        .price = CANDY_COST(500),
        .description = sCloverSweetDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_FLOWER_SWEET] =
    {
        .name = sFlowerSweetName,
        .itemId = ITEM_FLOWER_SWEET,
        .price = CANDY_COST(500),
        .description = sFlowerSweetDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_STAR_SWEET] =
    {
        .name = sStarSweetName,
        .itemId = ITEM_STAR_SWEET,
        .price = CANDY_COST(500),
        .description = sStarSweetDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_RIBBON_SWEET] =
    {
        .name = sRibbonSweetName,
        .itemId = ITEM_RIBBON_SWEET,
        .price = CANDY_COST(500),
        .description = sRibbonSweetDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_EVERSTONE] =
    {
        .name = sEverstoneName,
        .itemId = ITEM_EVERSTONE,
        .price = CANDY_COST(3000),
        .holdEffect = HOLD_EFFECT_PREVENT_EVOLVE,
        .description = sEverstoneDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

// #pragma endregion

// #pragma region Nectars

    [ITEM_RED_NECTAR] =
    {
        .name = sRedNectarName,
        .quantum = sQuantum_Jar,
        .itemId = ITEM_RED_NECTAR,
        .price = CANDY_COST(300),
        .holdEffectParam = 0,
        .description = sRedNectarDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_FormChange_ConsumedOnUse,
        .secondaryId = FORM_ITEM_USE,
        .flingPower = 10,
    },

    [ITEM_YELLOW_NECTAR] =
    {
        .name = sYellowNectarName,
        .quantum = sQuantum_Jar,
        .itemId = ITEM_YELLOW_NECTAR,
        .price = CANDY_COST(300),
        .holdEffectParam = 0,
        .description = sYellowNectarDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_FormChange_ConsumedOnUse,
        .secondaryId = FORM_ITEM_USE,
        .flingPower = 10,
    },

    [ITEM_PINK_NECTAR] =
    {
        .name = sPinkNectarName,
        .quantum = sQuantum_Jar,
        .itemId = ITEM_PINK_NECTAR,
        .price = CANDY_COST(300),
        .holdEffectParam = 0,
        .description = sPinkNectarDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_FormChange_ConsumedOnUse,
        .secondaryId = FORM_ITEM_USE,
        .flingPower = 10,
    },

    [ITEM_PURPLE_NECTAR] =
    {
        .name = sPurpleNectarName,
        .quantum = sQuantum_Jar,
        .itemId = ITEM_PURPLE_NECTAR,
        .price = CANDY_COST(300),
        .holdEffectParam = 0,
        .description = sPurpleNectarDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_FormChange_ConsumedOnUse,
        .secondaryId = FORM_ITEM_USE,
        .flingPower = 10,
    },

// #pragma endregion

// #pragma region Plates

    [ITEM_FLAME_PLATE] =
    {
        .name = sFlamePlateName,
        .itemId = ITEM_FLAME_PLATE,
        .price = CANDY_COST(1000),
        .holdEffect = HOLD_EFFECT_PLATE,
        .holdEffectParam = 20,
        .description = sFlamePlateDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FIRE,
        .flingPower = 90,
    },

    [ITEM_SPLASH_PLATE] =
    {
        .name = sSplashPlateName,
        .itemId = ITEM_SPLASH_PLATE,
        .price = CANDY_COST(1000),
        .holdEffect = HOLD_EFFECT_PLATE,
        .holdEffectParam = 20,
        .description = sSplashPlateDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_WATER,
        .flingPower = 90,
    },

    [ITEM_ZAP_PLATE] =
    {
        .name = sZapPlateName,
        .itemId = ITEM_ZAP_PLATE,
        .price = CANDY_COST(1000),
        .holdEffect = HOLD_EFFECT_PLATE,
        .holdEffectParam = 20,
        .description = sZapPlateDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_ELECTRIC,
        .flingPower = 90,
    },

    [ITEM_MEADOW_PLATE] =
    {
        .name = sMeadowPlateName,
        .itemId = ITEM_MEADOW_PLATE,
        .price = CANDY_COST(1000),
        .holdEffect = HOLD_EFFECT_PLATE,
        .holdEffectParam = 20,
        .description = sMeadowPlateDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_GRASS,
        .flingPower = 90,
    },

    [ITEM_ICICLE_PLATE] =
    {
        .name = sIciclePlateName,
        .itemId = ITEM_ICICLE_PLATE,
        .price = CANDY_COST(1000),
        .holdEffect = HOLD_EFFECT_PLATE,
        .holdEffectParam = 20,
        .description = sIciclePlateDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_ICE,
        .flingPower = 90,
    },

    [ITEM_FIST_PLATE] =
    {
        .name = sFistPlateName,
        .itemId = ITEM_FIST_PLATE,
        .price = CANDY_COST(1000),
        .holdEffect = HOLD_EFFECT_PLATE,
        .holdEffectParam = 20,
        .description = sFistPlateDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FIGHTING,
        .flingPower = 90,
    },

    [ITEM_TOXIC_PLATE] =
    {
        .name = sToxicPlateName,
        .itemId = ITEM_TOXIC_PLATE,
        .price = CANDY_COST(1000),
        .holdEffect = HOLD_EFFECT_PLATE,
        .holdEffectParam = 20,
        .description = sToxicPlateDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_POISON,
        .flingPower = 90,
    },

    [ITEM_EARTH_PLATE] =
    {
        .name = sEarthPlateName,
        .itemId = ITEM_EARTH_PLATE,
        .price = CANDY_COST(1000),
        .holdEffect = HOLD_EFFECT_PLATE,
        .holdEffectParam = 20,
        .description = sEarthPlateDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_GROUND,
        .flingPower = 90,
    },

    [ITEM_SKY_PLATE] =
    {
        .name = sSkyPlateName,
        .itemId = ITEM_SKY_PLATE,
        .price = CANDY_COST(1000),
        .holdEffect = HOLD_EFFECT_PLATE,
        .holdEffectParam = 20,
        .description = sSkyPlateDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FLYING,
        .flingPower = 90,
    },

    [ITEM_MIND_PLATE] =
    {
        .name = sMindPlateName,
        .itemId = ITEM_MIND_PLATE,
        .price = CANDY_COST(1000),
        .holdEffect = HOLD_EFFECT_PLATE,
        .holdEffectParam = 20,
        .description = sMindPlateDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_PSYCHIC,
        .flingPower = 90,
    },

    [ITEM_INSECT_PLATE] =
    {
        .name = sInsectPlateName,
        .itemId = ITEM_INSECT_PLATE,
        .price = CANDY_COST(1000),
        .holdEffect = HOLD_EFFECT_PLATE,
        .holdEffectParam = 20,
        .description = sInsectPlateDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_BUG,
        .flingPower = 90,
    },

    [ITEM_STONE_PLATE] =
    {
        .name = sStonePlateName,
        .itemId = ITEM_STONE_PLATE,
        .price = CANDY_COST(1000),
        .holdEffect = HOLD_EFFECT_PLATE,
        .holdEffectParam = 20,
        .description = sStonePlateDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_ROCK,
        .flingPower = 90,
    },

    [ITEM_SPOOKY_PLATE] =
    {
        .name = sSpookyPlateName,
        .itemId = ITEM_SPOOKY_PLATE,
        .price = CANDY_COST(1000),
        .holdEffect = HOLD_EFFECT_PLATE,
        .holdEffectParam = 20,
        .description = sSpookyPlateDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_GHOST,
        .flingPower = 90,
    },

    [ITEM_DRACO_PLATE] =
    {
        .name = sDracoPlateName,
        .itemId = ITEM_DRACO_PLATE,
        .price = CANDY_COST(1000),
        .holdEffect = HOLD_EFFECT_PLATE,
        .holdEffectParam = 20,
        .description = sDracoPlateDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_DRAGON,
        .flingPower = 90,
    },

    [ITEM_DREAD_PLATE] =
    {
        .name = sDreadPlateName,
        .itemId = ITEM_DREAD_PLATE,
        .price = CANDY_COST(1000),
        .holdEffect = HOLD_EFFECT_PLATE,
        .holdEffectParam = 20,
        .description = sDreadPlateDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_DARK,
        .flingPower = 90,
    },

    [ITEM_IRON_PLATE] =
    {
        .name = sIronPlateName,
        .itemId = ITEM_IRON_PLATE,
        .price = CANDY_COST(1000),
        .holdEffect = HOLD_EFFECT_PLATE,
        .holdEffectParam = 20,
        .description = sIronPlateDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_STEEL,
        .flingPower = 90,
    },

    [ITEM_PIXIE_PLATE] =
    {
        .name = sPixiePlateName,
        .itemId = ITEM_PIXIE_PLATE,
        .price = CANDY_COST(1000),
        .holdEffect = HOLD_EFFECT_PLATE,
        .holdEffectParam = 20,
        .description = sPixiePlateDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FAIRY,
        .flingPower = 90,
    },

// #pragma endregion

// #pragma region Drives

    [ITEM_DOUSE_DRIVE] =
    {
        .name = sDouseDriveName,
        .itemId = ITEM_DOUSE_DRIVE,
        .price = 0,
        .holdEffect = HOLD_EFFECT_DRIVE,
        .description = sDouseDriveDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_WATER,
        .flingPower = 70,
    },

    [ITEM_SHOCK_DRIVE] =
    {
        .name = sShockDriveName,
        .itemId = ITEM_SHOCK_DRIVE,
        .price = 0,
        .holdEffect = HOLD_EFFECT_DRIVE,
        .description = sShockDriveDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_ELECTRIC,
        .flingPower = 70,
    },

    [ITEM_BURN_DRIVE] =
    {
        .name = sBurnDriveName,
        .itemId = ITEM_BURN_DRIVE,
        .price = 0,
        .holdEffect = HOLD_EFFECT_DRIVE,
        .description = sBurnDriveDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FIRE,
        .flingPower = 70,
    },

    [ITEM_CHILL_DRIVE] =
    {
        .name = sChillDriveName,
        .itemId = ITEM_CHILL_DRIVE,
        .price = 0,
        .holdEffect = HOLD_EFFECT_DRIVE,
        .description = sChillDriveDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_ICE,
        .flingPower = 70,
    },

// #pragma endregion

// #pragma region Memories

    [ITEM_FIRE_MEMORY] =
    {
        .name = sFireMemoryName,
        .itemId = ITEM_FIRE_MEMORY,
        .price = 1000,
        .holdEffect = HOLD_EFFECT_MEMORY,
        .holdEffectParam = 0,
        .description = sFireMemoryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FIRE,
        .flingPower = 50,
    },

    [ITEM_WATER_MEMORY] =
    {
        .name = sWaterMemoryName,
        .itemId = ITEM_WATER_MEMORY,
        .price = 1000,
        .holdEffect = HOLD_EFFECT_MEMORY,
        .holdEffectParam = 0,
        .description = sWaterMemoryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_WATER,
        .flingPower = 50,
    },

    [ITEM_ELECTRIC_MEMORY] =
    {
        .name = sElectricMemoryName,
        .itemId = ITEM_ELECTRIC_MEMORY,
        .price = 1000,
        .holdEffect = HOLD_EFFECT_MEMORY,
        .holdEffectParam = 0,
        .description = sElectricMemoryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_ELECTRIC,
        .flingPower = 50,
    },

    [ITEM_GRASS_MEMORY] =
    {
        .name = sGrassMemoryName,
        .itemId = ITEM_GRASS_MEMORY,
        .price = 1000,
        .holdEffect = HOLD_EFFECT_MEMORY,
        .holdEffectParam = 0,
        .description = sGrassMemoryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_GRASS,
        .flingPower = 50,
    },

    [ITEM_ICE_MEMORY] =
    {
        .name = sIceMemoryName,
        .itemId = ITEM_ICE_MEMORY,
        .price = 1000,
        .holdEffect = HOLD_EFFECT_MEMORY,
        .holdEffectParam = 0,
        .description = sIceMemoryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_ICE,
        .flingPower = 50,
    },

    [ITEM_FIGHTING_MEMORY] =
    {
        .name = sFightingMemoryName,
        .itemId = ITEM_FIGHTING_MEMORY,
        .price = 1000,
        .holdEffect = HOLD_EFFECT_MEMORY,
        .holdEffectParam = 0,
        .description = sFightingMemoryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FIGHTING,
        .flingPower = 50,
    },

    [ITEM_POISON_MEMORY] =
    {
        .name = sPoisonMemoryName,
        .itemId = ITEM_POISON_MEMORY,
        .price = 1000,
        .holdEffect = HOLD_EFFECT_MEMORY,
        .holdEffectParam = 0,
        .description = sPoisonMemoryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_POISON,
        .flingPower = 50,
    },

    [ITEM_GROUND_MEMORY] =
    {
        .name = sGroundMemoryName,
        .itemId = ITEM_GROUND_MEMORY,
        .price = 1000,
        .holdEffect = HOLD_EFFECT_MEMORY,
        .holdEffectParam = 0,
        .description = sGroundMemoryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_GROUND,
        .flingPower = 50,
    },

    [ITEM_FLYING_MEMORY] =
    {
        .name = sFlyingMemoryName,
        .itemId = ITEM_FLYING_MEMORY,
        .price = 1000,
        .holdEffect = HOLD_EFFECT_MEMORY,
        .holdEffectParam = 0,
        .description = sFlyingMemoryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FLYING,
        .flingPower = 50,
    },

    [ITEM_PSYCHIC_MEMORY] =
    {
        .name = sPsychicMemoryName,
        .itemId = ITEM_PSYCHIC_MEMORY,
        .price = 1000,
        .holdEffect = HOLD_EFFECT_MEMORY,
        .holdEffectParam = 0,
        .description = sPsychicMemoryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_PSYCHIC,
        .flingPower = 50,
    },

    [ITEM_BUG_MEMORY] =
    {
        .name = sBugMemoryName,
        .itemId = ITEM_BUG_MEMORY,
        .price = 1000,
        .holdEffect = HOLD_EFFECT_MEMORY,
        .holdEffectParam = 0,
        .description = sBugMemoryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_BUG,
        .flingPower = 50,
    },

    [ITEM_ROCK_MEMORY] =
    {
        .name = sRockMemoryName,
        .itemId = ITEM_ROCK_MEMORY,
        .price = 1000,
        .holdEffect = HOLD_EFFECT_MEMORY,
        .holdEffectParam = 0,
        .description = sRockMemoryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_ROCK,
        .flingPower = 50,
    },

    [ITEM_GHOST_MEMORY] =
    {
        .name = sGhostMemoryName,
        .itemId = ITEM_GHOST_MEMORY,
        .price = 1000,
        .holdEffect = HOLD_EFFECT_MEMORY,
        .holdEffectParam = 0,
        .description = sGhostMemoryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_GHOST,
        .flingPower = 50,
    },

    [ITEM_DRAGON_MEMORY] =
    {
        .name = sDragonMemoryName,
        .itemId = ITEM_DRAGON_MEMORY,
        .price = 1000,
        .holdEffect = HOLD_EFFECT_MEMORY,
        .holdEffectParam = 0,
        .description = sDragonMemoryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_DRAGON,
        .flingPower = 50,
    },

    [ITEM_DARK_MEMORY] =
    {
        .name = sDarkMemoryName,
        .itemId = ITEM_DARK_MEMORY,
        .price = 1000,
        .holdEffect = HOLD_EFFECT_MEMORY,
        .holdEffectParam = 0,
        .description = sDarkMemoryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_DARK,
        .flingPower = 50,
    },

    [ITEM_STEEL_MEMORY] =
    {
        .name = sSteelMemoryName,
        .itemId = ITEM_STEEL_MEMORY,
        .price = 1000,
        .holdEffect = HOLD_EFFECT_MEMORY,
        .holdEffectParam = 0,
        .description = sSteelMemoryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_STEEL,
        .flingPower = 50,
    },

    [ITEM_FAIRY_MEMORY] =
    {
        .name = sFairyMemoryName,
        .itemId = ITEM_FAIRY_MEMORY,
        .price = 1000,
        .holdEffect = HOLD_EFFECT_MEMORY,
        .holdEffectParam = 0,
        .description = sFairyMemoryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FAIRY,
        .flingPower = 50,
    },

    [ITEM_RUSTED_SWORD] =
    {
        .name = sRustedSwordName,
        .itemId = ITEM_RUSTED_SWORD,
        .price = 0,
        .description = sRustedSwordDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

    [ITEM_RUSTED_SHIELD] =
    {
        .name = sRustedShieldName,
        .itemId = ITEM_RUSTED_SHIELD,
        .price = 0,
        .description = sRustedShieldDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

// #pragma endregion

// #pragma region Mega Stones

    [ITEM_RED_ORB] =
    {
        .name = sRedOrbName,
        .itemId = ITEM_RED_ORB,
        .price = 0,
        .holdEffect = HOLD_EFFECT_PRIMAL_ORB,
        .description = sRedOrbDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

    [ITEM_BLUE_ORB] =
    {
        .name = sBlueOrbName,
        .itemId = ITEM_BLUE_ORB,
        .price = 0,
        .holdEffect = HOLD_EFFECT_PRIMAL_ORB,
        .description = sBlueOrbDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },
    
    [ITEM_VENUSAURITE] =
    {
        .name = sVenusauriteName,
        .quantum = sQuantum_MegaStone,
        .itemId = ITEM_VENUSAURITE,
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sVenusauriteDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_CHARIZARDITE_X] =
    {
        .name = sCharizarditeXName,
        .quantum = sQuantum_MegaStone,
        .itemId = ITEM_CHARIZARDITE_X,
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sCharizarditeDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_CHARIZARDITE_Y] =
    {
        .name = sCharizarditeYName,
        .quantum = sQuantum_MegaStone,
        .itemId = ITEM_CHARIZARDITE_Y,
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sCharizarditeDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_BLASTOISINITE] =
    {
        .name = sBlastoisiniteName,
        .quantum = sQuantum_MegaStone,
        .itemId = ITEM_BLASTOISINITE,
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sBlastoisiniteDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_BEEDRILLITE] =
    {
        .name = sBeedrilliteName,
        .quantum = sQuantum_MegaStone,
        .itemId = ITEM_BEEDRILLITE,
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sBeedrilliteDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_PIDGEOTITE] =
    {
        .name = sPidgeotiteName,
        .quantum = sQuantum_MegaStone,
        .itemId = ITEM_PIDGEOTITE,
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sPidgeotiteDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_ALAKAZITE] =
    {
        .name = sAlakaziteName,
        .quantum = sQuantum_MegaStone,
        .itemId = ITEM_ALAKAZITE,
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sAlakaziteDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_SLOWBRONITE] =
    {
        .name = sSlowbroniteName,
        .quantum = sQuantum_MegaStone,
        .itemId = ITEM_SLOWBRONITE,
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sSlowbroniteDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_GENGARITE] =
    {
        .name = sGengariteName,
        .quantum = sQuantum_MegaStone,
        .itemId = ITEM_GENGARITE,
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sGengariteDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_KANGASKHANITE] =
    {
        .name = sKangaskhaniteName,
        .quantum = sQuantum_MegaStone,
        .itemId = ITEM_KANGASKHANITE,
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sKangaskhaniteDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_PINSIRITE] =
    {
        .name = sPinsiriteName,
        .quantum = sQuantum_MegaStone,
        .itemId = ITEM_PINSIRITE,
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sPinsiriteDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_GYARADOSITE] =
    {
        .name = sGyaradositeName,
        .quantum = sQuantum_MegaStone,
        .itemId = ITEM_GYARADOSITE,
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sGyaradositeDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_AERODACTYLITE] =
    {
        .name = sAerodactyliteName,
        .quantum = sQuantum_MegaStone,
        .itemId = ITEM_AERODACTYLITE,
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sAerodactyliteDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_MEWTWONITE_X] =
    {
        .name = sMewtwoniteXName,
        .quantum = sQuantum_MegaStone,
        .itemId = ITEM_MEWTWONITE_X,
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sMewtwoniteDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_MEWTWONITE_Y] =
    {
        .name = sMewtwoniteYName,
        .quantum = sQuantum_MegaStone,
        .itemId = ITEM_MEWTWONITE_Y,
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sMewtwoniteDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_AMPHAROSITE] =
    {
        .name = sAmpharositeName,
        .quantum = sQuantum_MegaStone,
        .itemId = ITEM_AMPHAROSITE,
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sAmpharositeDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_STEELIXITE] =
    {
        .name = sSteelixiteName,
        .quantum = sQuantum_MegaStone,
        .itemId = ITEM_STEELIXITE,
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sSteelixiteDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_SCIZORITE] =
    {
        .name = sScizoriteName,
        .quantum = sQuantum_MegaStone,
        .itemId = ITEM_SCIZORITE,
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sScizoriteDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_HERACRONITE] =
    {
        .name = sHeracroniteName,
        .quantum = sQuantum_MegaStone,
        .itemId = ITEM_HERACRONITE,
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sHeracroniteDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_HOUNDOOMINITE] =
    {
        .name = sHoundoominiteName,
        .quantum = sQuantum_MegaStone,
        .itemId = ITEM_HOUNDOOMINITE,
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sHoundoominiteDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_TYRANITARITE] =
    {
        .name = sTyranitariteName,
        .quantum = sQuantum_MegaStone,
        .itemId = ITEM_TYRANITARITE,
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sTyranitariteDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_SCEPTILITE] =
    {
        .name = sSceptiliteName,
        .quantum = sQuantum_MegaStone,
        .itemId = ITEM_SCEPTILITE,
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sSceptiliteDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_BLAZIKENITE] =
    {
        .name = sBlazikeniteName,
        .quantum = sQuantum_MegaStone,
        .itemId = ITEM_BLAZIKENITE,
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sBlazikeniteDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_SWAMPERTITE] =
    {
        .name = sSwampertiteName,
        .quantum = sQuantum_MegaStone,
        .itemId = ITEM_SWAMPERTITE,
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sSwampertiteDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_GARDEVOIRITE] =
    {
        .name = sGardevoiriteName,
        .quantum = sQuantum_MegaStone,
        .itemId = ITEM_GARDEVOIRITE,
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sGardevoiriteDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_SABLENITE] =
    {
        .name = sSableniteName,
        .quantum = sQuantum_MegaStone,
        .itemId = ITEM_SABLENITE,
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sSableniteDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_MAWILITE] =
    {
        .name = sMawiliteName,
        .quantum = sQuantum_MegaStone,
        .itemId = ITEM_MAWILITE,
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sMawiliteDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_AGGRONITE] =
    {
        .name = sAggroniteName,
        .quantum = sQuantum_MegaStone,
        .itemId = ITEM_AGGRONITE,
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sAggroniteDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_MEDICHAMITE] =
    {
        .name = sMedichamiteName,
        .quantum = sQuantum_MegaStone,
        .itemId = ITEM_MEDICHAMITE,
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sMedichamiteDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_MANECTITE] =
    {
        .name = sManectiteName,
        .quantum = sQuantum_MegaStone,
        .itemId = ITEM_MANECTITE,
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sManectiteDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_SHARPEDONITE] =
    {
        .name = sSharpedoniteName,
        .quantum = sQuantum_MegaStone,
        .itemId = ITEM_SHARPEDONITE,
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sSharpedoniteDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_CAMERUPTITE] =
    {
        .name = sCameruptiteName,
        .quantum = sQuantum_MegaStone,
        .itemId = ITEM_CAMERUPTITE,
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sCameruptiteDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_ALTARIANITE] =
    {
        .name = sAltarianiteName,
        .quantum = sQuantum_MegaStone,
        .itemId = ITEM_ALTARIANITE,
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sAltarianiteDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_BANETTITE] =
    {
        .name = sBanettiteName,
        .quantum = sQuantum_MegaStone,
        .itemId = ITEM_BANETTITE,
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sBanettiteDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_ABSOLITE] =
    {
        .name = sAbsoliteName,
        .quantum = sQuantum_MegaStone,
        .itemId = ITEM_ABSOLITE,
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sAbsoliteDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_GLALITITE] =
    {
        .name = sGlalititeName,
        .quantum = sQuantum_MegaStone,
        .itemId = ITEM_GLALITITE,
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sGlalititeDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_SALAMENCITE] =
    {
        .name = sSalamenciteName,
        .quantum = sQuantum_MegaStone,
        .itemId = ITEM_SALAMENCITE,
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sSalamenciteDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_METAGROSSITE] =
    {
        .name = sMetagrossiteName,
        .quantum = sQuantum_MegaStone,
        .itemId = ITEM_METAGROSSITE,
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sMetagrossiteDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_LATIASITE] =
    {
        .name = sLatiasiteName,
        .quantum = sQuantum_MegaStone,
        .itemId = ITEM_LATIASITE,
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sLatiasiteDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_LATIOSITE] =
    {
        .name = sLatiositeName,
        .quantum = sQuantum_MegaStone,
        .itemId = ITEM_LATIOSITE,
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sLatiositeDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_LOPUNNITE] =
    {
        .name = sLopunniteName,
        .quantum = sQuantum_MegaStone,
        .itemId = ITEM_LOPUNNITE,
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sLopunniteDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_GARCHOMPITE] =
    {
        .name = sGarchompiteName,
        .quantum = sQuantum_MegaStone,
        .itemId = ITEM_GARCHOMPITE,
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sGarchompiteDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_LUCARIONITE] =
    {
        .name = sLucarioniteName,
        .quantum = sQuantum_MegaStone,
        .itemId = ITEM_LUCARIONITE,
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sLucarioniteDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_ABOMASITE] =
    {
        .name = sAbomasiteName,
        .quantum = sQuantum_MegaStone,
        .itemId = ITEM_ABOMASITE,
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sAbomasiteDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_GALLADITE] =
    {
        .name = sGalladiteName,
        .quantum = sQuantum_MegaStone,
        .itemId = ITEM_GALLADITE,
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sGalladiteDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_AUDINITE] =
    {
        .name = sAudiniteName,
        .quantum = sQuantum_MegaStone,
        .itemId = ITEM_AUDINITE,
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sAudiniteDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_DIANCITE] =
    {
        .name = sDianciteName,
        .quantum = sQuantum_MegaStone,
        .itemId = ITEM_DIANCITE,
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sDianciteDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

// #pragma endregion

// #pragma region Gems

    [ITEM_NORMAL_GEM] =
    {
        .name = sNormalGemName,
        .itemId = ITEM_NORMAL_GEM,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_GEMS,
        .holdEffectParam = 30,
        .description = sNormalGemDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_NORMAL,
    },

    [ITEM_FIRE_GEM] =
    {
        .name = sFireGemName,
        .itemId = ITEM_FIRE_GEM,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_GEMS,
        .holdEffectParam = 30,
        .description = sFireGemDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FIRE,
    },

    [ITEM_WATER_GEM] =
    {
        .name = sWaterGemName,
        .itemId = ITEM_WATER_GEM,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_GEMS,
        .holdEffectParam = 30,
        .description = sWaterGemDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_WATER,
    },

    [ITEM_ELECTRIC_GEM] =
    {
        .name = sElectricGemName,
        .itemId = ITEM_ELECTRIC_GEM,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_GEMS,
        .holdEffectParam = 30,
        .description = sElectricGemDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_ELECTRIC,
    },

    [ITEM_GRASS_GEM] =
    {
        .name = sGrassGemName,
        .itemId = ITEM_GRASS_GEM,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_GEMS,
        .holdEffectParam = 30,
        .description = sGrassGemDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_GRASS,
    },

    [ITEM_ICE_GEM] =
    {
        .name = sIceGemName,
        .itemId = ITEM_ICE_GEM,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_GEMS,
        .holdEffectParam = 30,
        .description = sIceGemDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_ICE,
    },

    [ITEM_FIGHTING_GEM] =
    {
        .name = sFightingGemName,
        .itemId = ITEM_FIGHTING_GEM,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_GEMS,
        .holdEffectParam = 30,
        .description = sFightingGemDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FIGHTING,
    },

    [ITEM_POISON_GEM] =
    {
        .name = sPoisonGemName,
        .itemId = ITEM_POISON_GEM,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_GEMS,
        .holdEffectParam = 30,
        .description = sPoisonGemDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_POISON,
    },

    [ITEM_GROUND_GEM] =
    {
        .name = sGroundGemName,
        .itemId = ITEM_GROUND_GEM,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_GEMS,
        .holdEffectParam = 30,
        .description = sGroundGemDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_GROUND,
    },

    [ITEM_FLYING_GEM] =
    {
        .name = sFlyingGemName,
        .itemId = ITEM_FLYING_GEM,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_GEMS,
        .holdEffectParam = 30,
        .description = sFlyingGemDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FLYING,
    },

    [ITEM_PSYCHIC_GEM] =
    {
        .name = sPsychicGemName,
        .itemId = ITEM_PSYCHIC_GEM,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_GEMS,
        .holdEffectParam = 30,
        .description = sPsychicGemDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_PSYCHIC,
    },

    [ITEM_BUG_GEM] =
    {
        .name = sBugGemName,
        .itemId = ITEM_BUG_GEM,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_GEMS,
        .holdEffectParam = 30,
        .description = sBugGemDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_BUG,
    },

    [ITEM_ROCK_GEM] =
    {
        .name = sRockGemName,
        .itemId = ITEM_ROCK_GEM,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_GEMS,
        .holdEffectParam = 30,
        .description = sRockGemDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_ROCK,
    },

    [ITEM_GHOST_GEM] =
    {
        .name = sGhostGemName,
        .itemId = ITEM_GHOST_GEM,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_GEMS,
        .holdEffectParam = 30,
        .description = sGhostGemDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_GHOST,
    },

    [ITEM_DRAGON_GEM] =
    {
        .name = sDragonGemName,
        .itemId = ITEM_DRAGON_GEM,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_GEMS,
        .holdEffectParam = 30,
        .description = sDragonGemDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_DRAGON,
    },

    [ITEM_DARK_GEM] =
    {
        .name = sDarkGemName,
        .itemId = ITEM_DARK_GEM,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_GEMS,
        .holdEffectParam = 30,
        .description = sDarkGemDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_DARK,
    },

    [ITEM_STEEL_GEM] =
    {
        .name = sSteelGemName,
        .itemId = ITEM_STEEL_GEM,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_GEMS,
        .holdEffectParam = 30,
        .description = sSteelGemDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_STEEL,
    },

    [ITEM_FAIRY_GEM] =
    {
        .name = sFairyGemName,
        .itemId = ITEM_FAIRY_GEM,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_GEMS,
        .holdEffectParam = 30,
        .description = sFairyGemDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FAIRY,
    },

// #pragma endregion

// #pragma region Z-Crystals

    [ITEM_NORMALIUM_Z] =
    {
        .name = sNormaliumZName,
        .quantum = sQuantum_ZCrystal,
        .itemId = ITEM_NORMALIUM_Z,
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = sNormaliumZDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_NORMAL
    },

    [ITEM_FIRIUM_Z] =
    {
        .name = sFiriumZName,
        .quantum = sQuantum_ZCrystal,
        .itemId = ITEM_FIRIUM_Z,
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = sFiriumZDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FIRE
    },

    [ITEM_WATERIUM_Z] =
    {
        .name = sWateriumZName,
        .quantum = sQuantum_ZCrystal,
        .itemId = ITEM_WATERIUM_Z,
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = sWateriumZDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_WATER
    },

    [ITEM_ELECTRIUM_Z] =
    {
        .name = sElectriumZName,
        .quantum = sQuantum_ZCrystal,
        .itemId = ITEM_ELECTRIUM_Z,
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = sElectriumZDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_ELECTRIC
    },

    [ITEM_GRASSIUM_Z] =
    {
        .name = sGrassiumZName,
        .quantum = sQuantum_ZCrystal,
        .itemId = ITEM_GRASSIUM_Z,
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = sGrassiumZDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_GRASS
    },

    [ITEM_ICIUM_Z] =
    {
        .name = sIciumZName,
        .quantum = sQuantum_ZCrystal,
        .itemId = ITEM_ICIUM_Z,
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = sIciumZDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_ICE
    },

    [ITEM_FIGHTINIUM_Z] =
    {
        .name = sFightiniumZName,
        .quantum = sQuantum_ZCrystal,
        .itemId = ITEM_FIGHTINIUM_Z,
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = sFightiniumZDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FIGHTING
    },

    [ITEM_POISONIUM_Z] =
    {
        .name = sPoisoniumZName,
        .quantum = sQuantum_ZCrystal,
        .itemId = ITEM_POISONIUM_Z,
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = sPoisoniumZDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_POISON
    },

    [ITEM_GROUNDIUM_Z] =
    {
        .name = sGroundiumZName,
        .quantum = sQuantum_ZCrystal,
        .itemId = ITEM_GROUNDIUM_Z,
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = sGroundiumZDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_GROUND
    },

    [ITEM_FLYINIUM_Z] =
    {
        .name = sFlyiniumZName,
        .quantum = sQuantum_ZCrystal,
        .itemId = ITEM_FLYINIUM_Z,
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = sFlyiniumZDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FLYING
    },

    [ITEM_PSYCHIUM_Z] =
    {
        .name = sPsychiumZName,
        .quantum = sQuantum_ZCrystal,
        .itemId = ITEM_PSYCHIUM_Z,
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = sPsychiumZDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_PSYCHIC
    },

    [ITEM_BUGINIUM_Z] =
    {
        .name = sBuginiumZName,
        .quantum = sQuantum_ZCrystal,
        .itemId = ITEM_BUGINIUM_Z,
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = sBuginiumZDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_BUG
    },

    [ITEM_ROCKIUM_Z] =
    {
        .name = sRockiumZName,
        .quantum = sQuantum_ZCrystal,
        .itemId = ITEM_ROCKIUM_Z,
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = sRockiumZDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_ROCK
    },

    [ITEM_GHOSTIUM_Z] =
    {
        .name = sGhostiumZName,
        .quantum = sQuantum_ZCrystal,
        .itemId = ITEM_GHOSTIUM_Z,
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = sGhostiumZDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_GHOST
    },

    [ITEM_DRAGONIUM_Z] =
    {
        .name = sDragoniumZName,
        .quantum = sQuantum_ZCrystal,
        .itemId = ITEM_DRAGONIUM_Z,
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = sDragoniumZDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_DRAGON
    },

    [ITEM_DARKINIUM_Z] =
    {
        .name = sDarkiniumZName,
        .quantum = sQuantum_ZCrystal,
        .itemId = ITEM_DARKINIUM_Z,
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = sDarkiniumZDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_DARK
    },

    [ITEM_STEELIUM_Z] =
    {
        .name = sSteeliumZName,
        .quantum = sQuantum_ZCrystal,
        .itemId = ITEM_STEELIUM_Z,
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = sSteeliumZDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_STEEL
    },

    [ITEM_FAIRIUM_Z] =
    {
        .name = sFairiumZName,
        .quantum = sQuantum_ZCrystal,
        .itemId = ITEM_FAIRIUM_Z,
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = sFairiumZDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FAIRY
    },

    [ITEM_PIKANIUM_Z] =
    {
        .name = sPikaniumZName,
        .quantum = sQuantum_ZCrystal,
        .itemId = ITEM_PIKANIUM_Z,
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = sPikaniumZDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 255  // signature z move
    },

    [ITEM_EEVIUM_Z] =
    {
        .name = sEeviumZName,
        .quantum = sQuantum_ZCrystal,
        .itemId = ITEM_EEVIUM_Z,
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = sEeviumZDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 255  // signature z move
    },

    [ITEM_SNORLIUM_Z] =
    {
        .name = sSnorliumZName,
        .quantum = sQuantum_ZCrystal,
        .itemId = ITEM_SNORLIUM_Z,
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = sSnorliumZDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 255  // signature z move
    },

    [ITEM_MEWNIUM_Z] =
    {
        .name = sMewniumZName,
        .quantum = sQuantum_ZCrystal,
        .itemId = ITEM_MEWNIUM_Z,
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = sMewniumZDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 255  // signature z move
    },

    [ITEM_DECIDIUM_Z] =
    {
        .name = sDecidiumZName,
        .quantum = sQuantum_ZCrystal,
        .itemId = ITEM_DECIDIUM_Z,
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = sDecidiumZDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 255  // signature z move
    },

    [ITEM_INCINIUM_Z] =
    {
        .name = sInciniumZName,
        .quantum = sQuantum_ZCrystal,
        .itemId = ITEM_INCINIUM_Z,
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = sInciniumZDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 255  // signature z move
    },

    [ITEM_PRIMARIUM_Z] =
    {
        .name = sPrimariumZName,
        .quantum = sQuantum_ZCrystal,
        .itemId = ITEM_PRIMARIUM_Z,
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = sPrimariumZDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 255  // signature z move
    },

    [ITEM_LYCANIUM_Z] =
    {
        .name = sLycaniumZName,
        .quantum = sQuantum_ZCrystal,
        .itemId = ITEM_LYCANIUM_Z,
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = sLycaniumZDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 255  // signature z move
    },

    [ITEM_MIMIKIUM_Z] =
    {
        .name = sMimikiumZName,
        .quantum = sQuantum_ZCrystal,
        .itemId = ITEM_MIMIKIUM_Z,
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = sMimikiumZDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 255  // signature z move
    },

    [ITEM_KOMMONIUM_Z] =
    {
        .name = sKommoniumZName,
        .quantum = sQuantum_ZCrystal,
        .itemId = ITEM_KOMMONIUM_Z,
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = sKommoniumZDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 255  // signature z move
    },

    [ITEM_TAPUNIUM_Z] =
    {
        .name = sTapuniumZName,
        .quantum = sQuantum_ZCrystal,
        .itemId = ITEM_TAPUNIUM_Z,
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = sTapuniumZDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 255  //signature z move
    },

    [ITEM_SOLGANIUM_Z] =
    {
        .name = sSolganiumZName,
        .quantum = sQuantum_ZCrystal,
        .itemId = ITEM_SOLGANIUM_Z,
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = sSolganiumZDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 255  // signature z move
    },

    [ITEM_LUNALIUM_Z] =
    {
        .name = sLunaliumZName,
        .quantum = sQuantum_ZCrystal,
        .itemId = ITEM_LUNALIUM_Z,
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = sLunaliumZDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 255  // signature z move
    },

    [ITEM_MARSHADIUM_Z] =
    {
        .name = sMarshadiumZName,
        .quantum = sQuantum_ZCrystal,
        .itemId = ITEM_MARSHADIUM_Z,
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = sMarshadiumZDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 255  // signature z move
    },

    [ITEM_ALORAICHIUM_Z] =
    {
        .name = sAloraichiumZName,
        .quantum = sQuantum_ZCrystal,
        .itemId = ITEM_ALORAICHIUM_Z,
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = sAloraichiumZDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 255  // signature z move
    },

    [ITEM_PIKASHUNIUM_Z] =
    {
        .name = sPikashuniumZName,
        .quantum = sQuantum_ZCrystal,
        .itemId = ITEM_PIKASHUNIUM_Z,
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = sPikashuniumZDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 255  // signature z move
    },

    [ITEM_ULTRANECROZIUM_Z] =
    {
        .name = sUltranecroziumZName,
        .quantum = sQuantum_ZCrystal,
        .itemId = ITEM_ULTRANECROZIUM_Z,
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = sUltranecroziumZDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 255  //signature z move
    },

// #pragma endregion

// #pragma region Species-specific Held Items

    [ITEM_LIGHT_BALL] =
    {
        .name = sLightBallName,
        .itemId = ITEM_LIGHT_BALL,
        .price = CANDY_COST(1000),
        .holdEffect = HOLD_EFFECT_LIGHT_BALL,
        .description = sLightBallDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_LEEK] =
    {
        .name = sLeekName,
        .itemId = ITEM_LEEK,
        .price = CANDY_COST(1000),
        .holdEffect = HOLD_EFFECT_LEEK,
        .description = sLeekDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 60,
    },

    [ITEM_THICK_CLUB] =
    {
        .name = sThickClubName,
        .itemId = ITEM_THICK_CLUB,
        .price = CANDY_COST(1000),
        .holdEffect = HOLD_EFFECT_THICK_CLUB,
        .description = sThickClubDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 90,
    },

    [ITEM_LUCKY_PUNCH] =
    {
        .name = sLuckyPunchName,
        .itemId = ITEM_LUCKY_PUNCH,
        .price = CANDY_COST(1000),
        .holdEffect = HOLD_EFFECT_LUCKY_PUNCH,
        .description = sLuckyPunchDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 40,
    },

    [ITEM_METAL_POWDER] =
    {
        .name = sMetalPowderName,
        .quantum = sQuantum_Bag,
        .itemId = ITEM_METAL_POWDER,
        .price = CANDY_COST(1000),
        .holdEffect = HOLD_EFFECT_METAL_POWDER,
        .description = sMetalPowderDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_QUICK_POWDER] =
    {
        .name = sQuickPowderName,
        .quantum = sQuantum_Bag,
        .itemId = ITEM_QUICK_POWDER,
        .price = CANDY_COST(1000),
        .holdEffect = HOLD_EFFECT_QUICK_POWDER,
        .description = sQuickPowderDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_DEEP_SEA_SCALE] =
    {
        .name = sDeepSeaScaleName,
        .itemId = ITEM_DEEP_SEA_SCALE,
        .price = CANDY_COST(2000),
        .holdEffect = HOLD_EFFECT_DEEP_SEA_SCALE,
        .description = sDeepSeaScaleDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_DEEP_SEA_TOOTH] =
    {
        .name = sDeepSeaToothName,
        .plural = sDeepSeaToothPluralName,
        .itemId = ITEM_DEEP_SEA_TOOTH,
        .price = CANDY_COST(2000),
        .holdEffect = HOLD_EFFECT_DEEP_SEA_TOOTH,
        .description = sDeepSeaToothDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 90,
    },

    [ITEM_SOUL_DEW] =
    {
        .name = sSoulDewName,
        .itemId = ITEM_SOUL_DEW,
        .price = CANDY_COST(0),
        .holdEffect = HOLD_EFFECT_SOUL_DEW,
#if B_SOUL_DEW_BOOST >= GEN_7
        .holdEffectParam = 20,
#else
        .holdEffectParam = 50,
#endif
        .description = sSoulDewDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_ADAMANT_ORB] =
    {
        .name = sAdamantOrbName,
        .itemId = ITEM_ADAMANT_ORB,
        .price = CANDY_COST(0),
        .holdEffect = HOLD_EFFECT_ADAMANT_ORB,
        .holdEffectParam = 20,
        .description = sAdamantOrbDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 60,
    },

    [ITEM_LUSTROUS_ORB] =
    {
        .name = sLustrousOrbName,
        .itemId = ITEM_LUSTROUS_ORB,
        .price = CANDY_COST(0),
        .holdEffect = HOLD_EFFECT_LUSTROUS_ORB,
        .holdEffectParam = 20,
        .description = sLustrousOrbDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 60,
    },

    [ITEM_GRISEOUS_ORB] =
    {
        .name = sGriseousOrbName,
        .itemId = ITEM_GRISEOUS_ORB,
        .price = CANDY_COST(0),
        .holdEffect = HOLD_EFFECT_GRISEOUS_ORB,
        .holdEffectParam = 20,
        .description = sGriseousOrbDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 60,
    },

// #pragma endregion

// #pragma region Incenses

    [ITEM_SEA_INCENSE] =
    {
        .name = sSeaIncenseName,
        .quantum = sQuantum_Jar,
        .itemId = ITEM_SEA_INCENSE,
        .price = CANDY_COST(2000),
        .holdEffect = HOLD_EFFECT_WATER_POWER,
        .holdEffectParam = 20,
        .description = sSeaIncenseDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_LAX_INCENSE] =
    {
        .name = sLaxIncenseName,
        .quantum = sQuantum_Jar,
        .itemId = ITEM_LAX_INCENSE,
        .price = CANDY_COST(5000),
        .holdEffect = HOLD_EFFECT_EVASION_UP,
        .holdEffectParam = 10,
        .description = sLaxIncenseDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_ODD_INCENSE] =
    {
        .name = sOddIncenseName,
        .quantum = sQuantum_Jar,
        .itemId = ITEM_ODD_INCENSE,
        .price = CANDY_COST(2000),
        .holdEffect = HOLD_EFFECT_PSYCHIC_POWER,
        .holdEffectParam = 20,
        .description = sOddIncenseDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_ROCK_INCENSE] =
    {
        .name = sRockIncenseName,
        .quantum = sQuantum_Jar,
        .itemId = ITEM_ROCK_INCENSE,
        .price = CANDY_COST(2000),
        .holdEffect = HOLD_EFFECT_ROCK_POWER,
        .holdEffectParam = 20,
        .description = sRockIncenseDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_FULL_INCENSE] =
    {
        .name = sFullIncenseName,
        .quantum = sQuantum_Jar,
        .itemId = ITEM_FULL_INCENSE,
        .price = CANDY_COST(5000),
        .holdEffect = HOLD_EFFECT_LAGGING_TAIL,
        .holdEffectParam = 5,
        .description = sFullIncenseDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_WAVE_INCENSE] =
    {
        .name = sWaveIncenseName,
        .quantum = sQuantum_Jar,
        .itemId = ITEM_WAVE_INCENSE,
        .price = CANDY_COST(2000),
        .holdEffect = HOLD_EFFECT_WATER_POWER,
        .holdEffectParam = 20,
        .description = sWaveIncenseDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_ROSE_INCENSE] =
    {
        .name = sRoseIncenseName,
        .quantum = sQuantum_Jar,
        .itemId = ITEM_ROSE_INCENSE,
        .price = CANDY_COST(2000),
        .holdEffect = HOLD_EFFECT_GRASS_POWER,
        .holdEffectParam = 20,
        .description = sRoseIncenseDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_LUCK_INCENSE] =
    {
        .name = sLuckIncenseName,
        .quantum = sQuantum_Jar,
        .itemId = ITEM_LUCK_INCENSE,
        .price = CANDY_COST(11000),
        .holdEffect = HOLD_EFFECT_DOUBLE_PRIZE,
        .holdEffectParam = 10,
        .description = sLuckIncenseDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_PURE_INCENSE] =
    {
        .name = sPureIncenseName,
        .quantum = sQuantum_Jar,
        .itemId = ITEM_PURE_INCENSE,
        .price = CANDY_COST(6000),
        .holdEffect = HOLD_EFFECT_REPEL,
        .description = sPureIncenseDesc,
        .pocket = POCKET_ITEMS,
        .keepItem = TRUE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

// #pragma endregion

// #pragma region Contest Scarves

    [ITEM_RED_SCARF] =
    {
        .name = sRedScarfName,
        .plural = sRedScarfPluralName,
        .itemId = ITEM_RED_SCARF,
        .price = CANDY_COST(100),
        .description = sRedScarfDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_BLUE_SCARF] =
    {
        .name = sBlueScarfName,
        .plural = sBlueScarfPluralName,
        .itemId = ITEM_BLUE_SCARF,
        .price = CANDY_COST(100),
        .description = sBlueScarfDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_PINK_SCARF] =
    {
        .name = sPinkScarfName,
        .plural = sPinkScarfPluralName,
        .itemId = ITEM_PINK_SCARF,
        .price = CANDY_COST(100),
        .description = sPinkScarfDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_GREEN_SCARF] =
    {
        .name = sGreenScarfName,
        .plural = sGreenScarfPluralName,
        .itemId = ITEM_GREEN_SCARF,
        .price = CANDY_COST(100),
        .description = sGreenScarfDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_YELLOW_SCARF] =
    {
        .name = sYellowScarfName,
        .plural = sYellowScarfPluralName,
        .itemId = ITEM_YELLOW_SCARF,
        .price = CANDY_COST(100),
        .description = sYellowScarfDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

// #pragma endregion

// #pragma region EV Gain Modifiers

    [ITEM_MACHO_BRACE] =
    {
        .name = sMachoBraceName,
        .itemId = ITEM_MACHO_BRACE,
        .price = CANDY_COST(3000),
        .holdEffect = HOLD_EFFECT_MACHO_BRACE,
        .description = sMachoBraceDesc,
        .pocket = POCKET_ITEMS,
        .keepItem = TRUE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 60,
    },

    [ITEM_POWER_WEIGHT] =
    {
        .name = sPowerWeightName,
        .itemId = ITEM_POWER_WEIGHT,
        .price = CANDY_COST(3000),
        .holdEffect = HOLD_EFFECT_POWER_ITEM,
        .holdEffectParam = 8,
        .description = sPowerWeightDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = STAT_HP,
        .flingPower = 70,
    },

    [ITEM_POWER_BRACER] =
    {
        .name = sPowerBracerName,
        .itemId = ITEM_POWER_BRACER,
        .price = CANDY_COST(3000),
        .holdEffect = HOLD_EFFECT_POWER_ITEM,
        .holdEffectParam = 8,
        .description = sPowerBracerDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = STAT_ATK,
        .flingPower = 70,
    },

    [ITEM_POWER_BELT] =
    {
        .name = sPowerBeltName,
        .itemId = ITEM_POWER_BELT,
        .price = CANDY_COST(3000),
        .holdEffect = HOLD_EFFECT_POWER_ITEM,
        .holdEffectParam = 8,
        .description = sPowerBeltDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = STAT_DEF,
        .flingPower = 70,
    },

    [ITEM_POWER_LENS] =
    {
        .name = sPowerLensName,
        .plural = ITEM_NAME_PLURAL_ES,
        .itemId = ITEM_POWER_LENS,
        .price = CANDY_COST(3000),
        .holdEffect = HOLD_EFFECT_POWER_ITEM,
        .holdEffectParam = 8,
        .description = sPowerLensDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = STAT_SPATK,
        .flingPower = 70,
    },

    [ITEM_POWER_BAND] =
    {
        .name = sPowerBandName,
        .itemId = ITEM_POWER_BAND,
        .price = CANDY_COST(3000),
        .holdEffect = HOLD_EFFECT_POWER_ITEM,
        .holdEffectParam = 8,
        .description = sPowerBandDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = STAT_SPDEF,
        .flingPower = 70,
    },

    [ITEM_POWER_ANKLET] =
    {
        .name = sPowerAnkletName,
        .itemId = ITEM_POWER_ANKLET,
        .price = CANDY_COST(3000),
        .holdEffect = HOLD_EFFECT_POWER_ITEM,
        .holdEffectParam = 8,
        .description = sPowerAnkletDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = STAT_SPEED,
        .flingPower = 70,
    },

// #pragma endregion

// #pragma region Type-boosting Held Items

    [ITEM_SILK_SCARF] =
    {
        .name = sSilkScarfName,
        .plural = sSilkScarfPluralName,
        .itemId = ITEM_SILK_SCARF,
        .price = CANDY_COST(1000),
        .holdEffect = HOLD_EFFECT_NORMAL_POWER,
        .holdEffectParam = 20,
        .description = sSilkScarfDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_CHARCOAL] =
    {
        .name = sCharcoalName,
#if USE_VANILLA_QUANTUMS
        .quantum = sQuantum_Piece,
#else
        .quantum = sQuantum_Lump,
#endif
        .itemId = ITEM_CHARCOAL,
        .price = CANDY_COST(1000),
        .holdEffect = HOLD_EFFECT_FIRE_POWER,
        .holdEffectParam = 20,
        .description = sCharcoalDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_MYSTIC_WATER] =
    {
        .name = sMysticWaterName,
        .quantum = sQuantum_Vial,
        .itemId = ITEM_MYSTIC_WATER,
        .price = CANDY_COST(1000),
        .holdEffect = HOLD_EFFECT_WATER_POWER,
        .holdEffectParam = 20,
        .description = sMysticWaterDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_MAGNET] =
    {
        .name = sMagnetName,
        .itemId = ITEM_MAGNET,
        .price = CANDY_COST(1000),
        .holdEffect = HOLD_EFFECT_ELECTRIC_POWER,
        .holdEffectParam = 20,
        .description = sMagnetDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_MIRACLE_SEED] =
    {
        .name = sMiracleSeedName,
        .itemId = ITEM_MIRACLE_SEED,
        .price = CANDY_COST(1000),
        .holdEffect = HOLD_EFFECT_GRASS_POWER,
        .holdEffectParam = 20,
        .description = sMiracleSeedDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_NEVER_MELT_ICE] =
    {
        .name = sNeverMeltIceName,
#if USE_VANILLA_QUANTUMS
        .quantum = sQuantum_Piece,
#else
        .quantum = sQuantum_Lump,
#endif
        .itemId = ITEM_NEVER_MELT_ICE,
        .price = CANDY_COST(1000),
        .holdEffect = HOLD_EFFECT_ICE_POWER,
        .holdEffectParam = 20,
        .description = sNeverMeltIceDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_BLACK_BELT] =
    {
        .name = sBlackBeltName,
        .itemId = ITEM_BLACK_BELT,
        .price = CANDY_COST(1000),
        .holdEffect = HOLD_EFFECT_FIGHTING_POWER,
        .holdEffectParam = 20,
        .description = sBlackBeltDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_POISON_BARB] =
    {
        .name = sPoisonBarbName,
        .itemId = ITEM_POISON_BARB,
        .price = CANDY_COST(1000),
        .holdEffect = HOLD_EFFECT_POISON_POWER,
        .holdEffectParam = 20,
        .description = sPoisonBarbDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 70,
    },

    [ITEM_SOFT_SAND] =
    {
        .name = sSoftSandName,
        .quantum = sQuantum_Bag,
        .itemId = ITEM_SOFT_SAND,
        .price = CANDY_COST(1000),
        .holdEffect = HOLD_EFFECT_GROUND_POWER,
        .holdEffectParam = 20,
        .description = sSoftSandDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_SHARP_BEAK] =
    {
        .name = sSharpBeakName,
        .itemId = ITEM_SHARP_BEAK,
        .price = CANDY_COST(1000),
        .holdEffect = HOLD_EFFECT_FLYING_POWER,
        .holdEffectParam = 20,
        .description = sSharpBeakDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 50,
    },

    [ITEM_TWISTED_SPOON] =
    {
        .name = sTwistedSpoonName,
        .itemId = ITEM_TWISTED_SPOON,
        .price = CANDY_COST(1000),
        .holdEffect = HOLD_EFFECT_PSYCHIC_POWER,
        .holdEffectParam = 20,
        .description = sTwistedSpoonDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_SILVER_POWDER] =
    {
        .name = sSilverPowderName,
#if USE_VANILLA_QUANTUMS
        .quantum = sQuantum_Pile,
#else
        .quantum = sQuantum_Bag,
#endif
        .itemId = ITEM_SILVER_POWDER,
        .price = CANDY_COST(1000),
        .holdEffect = HOLD_EFFECT_BUG_POWER,
        .holdEffectParam = 20,
        .description = sSilverPowderDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_HARD_STONE] =
    {
        .name = sHardStoneName,
        .itemId = ITEM_HARD_STONE,
        .price = CANDY_COST(1000),
        .holdEffect = HOLD_EFFECT_ROCK_POWER,
        .holdEffectParam = 20,
        .description = sHardStoneDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 100,
    },

    [ITEM_SPELL_TAG] =
    {
        .name = sSpellTagName,
        .itemId = ITEM_SPELL_TAG,
        .price = CANDY_COST(1000),
        .holdEffect = HOLD_EFFECT_GHOST_POWER,
        .holdEffectParam = 20,
        .description = sSpellTagDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_DRAGON_FANG] =
    {
        .name = sDragonFangName,
        .itemId = ITEM_DRAGON_FANG,
        .price = CANDY_COST(1000),
        .holdEffect = HOLD_EFFECT_DRAGON_POWER,
        .holdEffectParam = 20,
        .description = sDragonFangDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 70,
    },

    [ITEM_BLACK_GLASSES] =
    {
        .name = sBlackGlassesName,
        .quantum = sQuantum_Pair,
        .itemId = ITEM_BLACK_GLASSES,
        .price = CANDY_COST(1000),
        .holdEffect = HOLD_EFFECT_DARK_POWER,
        .holdEffectParam = 20,
        .description = sBlackGlassesDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_METAL_COAT] =
    {
        .name = sMetalCoatName,
        .quantum = sQuantum_Lump,
        .itemId = ITEM_METAL_COAT,
        .price = CANDY_COST(2000),
        .holdEffect = HOLD_EFFECT_STEEL_POWER,
        .holdEffectParam = 20,
        .description = sMetalCoatDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

// #pragma endregion

// #pragma region Choice Items

    [ITEM_CHOICE_BAND] =
    {
        .name = sChoiceBandName,
        .itemId = ITEM_CHOICE_BAND,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_CHOICE_BAND,
        .description = sChoiceBandDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_CHOICE_SPECS] =
    {
        .name = sChoiceSpecsName,
        .plural = sQuantum_Pair,
        .itemId = ITEM_CHOICE_SPECS,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_CHOICE_SPECS,
        .description = sChoiceSpecsDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_CHOICE_SCARF] =
    {
        .name = sChoiceScarfName,
        .plural = sChoiceScarfPluralName,
        .itemId = ITEM_CHOICE_SCARF,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_CHOICE_SCARF,
        .description = sChoiceScarfDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

// #pragma endregion

// #pragma region Other Battle Items

// Status Orbs

    [ITEM_FLAME_ORB] =
    {
        .name = sFlameOrbName,
        .itemId = ITEM_FLAME_ORB,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_FLAME_ORB,
        .description = sFlameOrbDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_TOXIC_ORB] =
    {
        .name = sToxicOrbName,
        .itemId = ITEM_TOXIC_ORB,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_TOXIC_ORB,
        .description = sToxicOrbDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

// Weather Rocks

    [ITEM_DAMP_ROCK] =
    {
        .name = sDampRockName,
        .itemId = ITEM_DAMP_ROCK,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_DAMP_ROCK,
        .description = sDampRockDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 60,
    },

    [ITEM_HEAT_ROCK] =
    {
        .name = sHeatRockName,
        .itemId = ITEM_HEAT_ROCK,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_HEAT_ROCK,
        .description = sHeatRockDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 60,
    },

    [ITEM_SMOOTH_ROCK] =
    {
        .name = sSmoothRockName,
        .itemId = ITEM_SMOOTH_ROCK,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_SMOOTH_ROCK,
        .description = sSmoothRockDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_ICY_ROCK] =
    {
        .name = sIcyRockName,
        .itemId = ITEM_ICY_ROCK,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_ICY_ROCK,
        .description = sIcyRockDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 40,
    },

// Terrain Seeds

    [ITEM_ELECTRIC_SEED] =
    {
        .name = sElectricSeedName,
        .itemId = ITEM_ELECTRIC_SEED,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_SEEDS,
        .holdEffectParam = HOLD_EFFECT_PARAM_ELECTRIC_TERRAIN,
        .description = sElectricSeedDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_PSYCHIC_SEED] =
    {
        .name = sPsychicSeedName,
        .itemId = ITEM_PSYCHIC_SEED,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_SEEDS,
        .holdEffectParam = HOLD_EFFECT_PARAM_PSYCHIC_TERRAIN,
        .description = sPsychicSeedDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_MISTY_SEED] =
    {
        .name = sMistySeedName,
        .itemId = ITEM_MISTY_SEED,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_SEEDS,
        .holdEffectParam = HOLD_EFFECT_PARAM_MISTY_TERRAIN,
        .description = sMistySeedDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_GRASSY_SEED] =
    {
        .name = sGrassySeedName,
        .itemId = ITEM_GRASSY_SEED,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_SEEDS,
        .holdEffectParam = HOLD_EFFECT_PARAM_GRASSY_TERRAIN,
        .description = sGrassySeedDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },
    

// Type-activated Stat Modifiers

    [ITEM_ABSORB_BULB] =
    {
        .name = sAbsorbBulbName,
        .itemId = ITEM_ABSORB_BULB,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_ABSORB_BULB,
        .holdEffectParam = 0,
        .description = sAbsorbBulbDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_CELL_BATTERY] =
    {
        .name = sCellBatteryName,
        .plural = sCellBatteryPluralName,
        .itemId = ITEM_CELL_BATTERY,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_CELL_BATTERY,
        .holdEffectParam = 0,
        .description = sCellBatteryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_LUMINOUS_MOSS] =
    {
        .name = sLuminousMossName,
        .quantum = sQuantum_Lump,
        .itemId = ITEM_LUMINOUS_MOSS,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_LUMINOUS_MOSS,
        .holdEffectParam = 0,
        .description = sLuminousMossDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_SNOWBALL] =
    {
        .name = sSnowballName,
        .itemId = ITEM_SNOWBALL,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_SNOWBALL,
        .holdEffectParam = 0,
        .description = sSnowballDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

// Misc. Held Items

    [ITEM_BRIGHT_POWDER] =
    {
        .name = sBrightPowderName,
        .quantum = sQuantum_Bag,
        .itemId = ITEM_BRIGHT_POWDER,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_EVASION_UP,
        .holdEffectParam = 10,
        .description = sBrightPowderDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_WHITE_HERB] =
    {
        .name = sWhiteHerbName,
        .itemId = ITEM_WHITE_HERB,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_RESTORE_STATS,
        .description = sWhiteHerbDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_EXP_SHARE] =
    {
        .name = sExpShareName,
        .itemId = ITEM_EXP_SHARE,
        .price = CANDY_COST(3000),
        .holdEffect = HOLD_EFFECT_EXP_SHARE,
        .description = sExpShareDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_QUICK_CLAW] =
    {
        .name = sQuickClawName,
        .itemId = ITEM_QUICK_CLAW,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_QUICK_CLAW,
        .holdEffectParam = 20,
        .keepItem = TRUE,
        .description = sQuickClawDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_SOOTHE_BELL] =
    {
        .name = sSootheBellName,
        .itemId = ITEM_SOOTHE_BELL,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_FRIENDSHIP_UP,
        .description = sSootheBellDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_MENTAL_HERB] =
    {
        .name = sMentalHerbName,
        .itemId = ITEM_MENTAL_HERB,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_MENTAL_HERB,
        .description = sMentalHerbDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_KINGS_ROCK] =
    {
        .name = sKingsRockName,
        .itemId = ITEM_KINGS_ROCK,
        .price = CANDY_COST(5000),
        .holdEffect = HOLD_EFFECT_FLINCH,
        .holdEffectParam = 10,
        .keepItem = TRUE,
        .description = sKingsRockDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_AMULET_COIN] =
    {
        .name = sAmuletCoinName,
        .itemId = ITEM_AMULET_COIN,
        .price = CANDY_COST(10000),
        .holdEffect = HOLD_EFFECT_DOUBLE_PRIZE,
        .holdEffectParam = 10,
        .keepItem = TRUE,
        .description = sAmuletCoinDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_CLEANSE_TAG] =
    {
        .name = sCleanseTagName,
        .itemId = ITEM_CLEANSE_TAG,
        .price = CANDY_COST(5000),
        .holdEffect = HOLD_EFFECT_REPEL,
        .description = sCleanseTagDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_SMOKE_BALL] =
    {
        .name = sSmokeBallName,
        .itemId = ITEM_SMOKE_BALL,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_CAN_ALWAYS_RUN,
        .description = sSmokeBallDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_FOCUS_BAND] =
    {
        .name = sFocusBandName,
        .itemId = ITEM_FOCUS_BAND,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_FOCUS_BAND,
        .holdEffectParam = 10,
        .keepItem = TRUE,
        .description = sFocusBandDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_LUCKY_EGG] =
    {
        .name = sLuckyEggName,
        .itemId = ITEM_LUCKY_EGG,
        .price = CANDY_COST(10000),
        .holdEffect = HOLD_EFFECT_LUCKY_EGG,
        .description = sLuckyEggDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_SCOPE_LENS] =
    {
        .name = sScopeLensName,
        .plural = ITEM_NAME_PLURAL_ES,
        .itemId = ITEM_SCOPE_LENS,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_SCOPE_LENS,
        .description = sScopeLensDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_LEFTOVERS] =
    {
        .name = sLeftoversName,
        .quantum = sQuantum_Serving,
        .itemId = ITEM_LEFTOVERS,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_LEFTOVERS,
        .holdEffectParam = 10,
        .keepItem = TRUE,
        .description = sLeftoversDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_SHELL_BELL] =
    {
        .name = sShellBellName,
        .itemId = ITEM_SHELL_BELL,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_SHELL_BELL,
        .holdEffectParam = 8,
        .keepItem = TRUE,
        .description = sShellBellDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_WIDE_LENS] =
    {
        .name = sWideLensName,
        .plural = ITEM_NAME_PLURAL_ES,
        .itemId = ITEM_WIDE_LENS,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_WIDE_LENS,
        .holdEffectParam = 10,
        .keepItem = TRUE,
        .description = sWideLensDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_MUSCLE_BAND] =
    {
        .name = sMuscleBandName,
        .itemId = ITEM_MUSCLE_BAND,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_MUSCLE_BAND,
        .holdEffectParam = 10,
        .keepItem = TRUE,
        .description = sMuscleBandDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_WISE_GLASSES] =
    {
        .name = sWiseGlassesName,
        .quantum = sQuantum_Pair,
        .itemId = ITEM_WISE_GLASSES,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_WISE_GLASSES,
        .holdEffectParam = 10,
        .keepItem = TRUE,
        .description = sWiseGlassesDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_EXPERT_BELT] =
    {
        .name = sExpertBeltName,
        .itemId = ITEM_EXPERT_BELT,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_EXPERT_BELT,
        .holdEffectParam = 20,
        .keepItem = TRUE,
        .description = sExpertBeltDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_LIGHT_CLAY] =
    {
        .name = sLightClayName,
        .quantum = sQuantum_Lump,
        .itemId = ITEM_LIGHT_CLAY,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_LIGHT_CLAY,
        .description = sLightClayDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_LIFE_ORB] =
    {
        .name = sLifeOrbName,
        .itemId = ITEM_LIFE_ORB,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_LIFE_ORB,
        .description = sLifeOrbDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_POWER_HERB] =
    {
        .name = sPowerHerbName,
        .itemId = ITEM_POWER_HERB,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_POWER_HERB,
        .description = sPowerHerbDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_FOCUS_SASH] =
    {
        .name = sFocusSashName,
        .plural = ITEM_NAME_PLURAL_ES,
        .itemId = ITEM_FOCUS_SASH,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_FOCUS_SASH,
        .description = sFocusSashDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_ZOOM_LENS] =
    {
        .name = sZoomLensName,
        .plural = ITEM_NAME_PLURAL_ES,
        .itemId = ITEM_ZOOM_LENS,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_ZOOM_LENS,
        .holdEffectParam = 20,
        .keepItem = TRUE,
        .description = sZoomLensDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_METRONOME] =
    {
        .name = sMetronomeName,
        .itemId = ITEM_METRONOME,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_METRONOME,
        .holdEffectParam = 20,
        .keepItem = TRUE,
        .description = sMetronomeDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_IRON_BALL] =
    {
        .name = sIronBallName,
        .itemId = ITEM_IRON_BALL,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_IRON_BALL,
        .description = sIronBallDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 130,
    },

    [ITEM_LAGGING_TAIL] =
    {
        .name = sLaggingTailName,
        .itemId = ITEM_LAGGING_TAIL,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_LAGGING_TAIL,
        .description = sLaggingTailDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_DESTINY_KNOT] =
    {
        .name = sDestinyKnotName,
        .itemId = ITEM_DESTINY_KNOT,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_DESTINY_KNOT,
        .description = sDestinyKnotDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_BLACK_SLUDGE] =
    {
        .name = sBlackSludgeName,
        .quantum = sQuantum_Blob,
        .itemId = ITEM_BLACK_SLUDGE,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_BLACK_SLUDGE,
        .description = sBlackSludgeDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_GRIP_CLAW] =
    {
        .name = sGripClawName,
        .itemId = ITEM_GRIP_CLAW,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_GRIP_CLAW,
        .description = sGripClawDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 90,
    },

    [ITEM_STICKY_BARB] =
    {
        .name = sStickyBarbName,
        .itemId = ITEM_STICKY_BARB,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_STICKY_BARB,
        .description = sStickyBarbDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_SHED_SHELL] =
    {
        .name = sShedShellName,
        .itemId = ITEM_SHED_SHELL,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_SHED_SHELL,
        .description = sShedShellDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_BIG_ROOT] =
    {
        .name = sBigRootName,
        .itemId = ITEM_BIG_ROOT,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_BIG_ROOT,
        .holdEffectParam = 30,
        .keepItem = TRUE,
        .description = sBigRootDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_RAZOR_CLAW] =
    {
        .name = sRazorClawName,
        .itemId = ITEM_RAZOR_CLAW,
        .price = CANDY_COST(5000),
        .holdEffect = HOLD_EFFECT_SCOPE_LENS,
        .description = sRazorClawDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_RAZOR_FANG] =
    {
        .name = sRazorFangName,
        .itemId = ITEM_RAZOR_FANG,
        .price = CANDY_COST(5000),
        .holdEffect = HOLD_EFFECT_FLINCH,
        .holdEffectParam = 10,
        .keepItem = TRUE,
        .description = sRazorFangDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_EVIOLITE] =
    {
        .name = sEvioliteName,
        .itemId = ITEM_EVIOLITE,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_EVIOLITE,
        .holdEffectParam = 50,
        .keepItem = TRUE,
        .description = sEvioliteDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 40,
    },

    [ITEM_FLOAT_STONE] =
    {
        .name = sFloatStoneName,
        .itemId = ITEM_FLOAT_STONE,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_FLOAT_STONE,
        .description = sFloatStoneDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_ROCKY_HELMET] =
    {
        .name = sRockyHelmetName,
        .itemId = ITEM_ROCKY_HELMET,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_ROCKY_HELMET,
        .holdEffectParam = 0,
        .keepItem = TRUE,
        .description = sRockyHelmetDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 60,
    },

    [ITEM_AIR_BALLOON] =
    {
        .name = sAirBalloonName,
        .itemId = ITEM_AIR_BALLOON,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_AIR_BALLOON,
        .holdEffectParam = 0,
        .keepItem = TRUE,
        .description = sAirBalloonDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_RED_CARD] =
    {
        .name = sRedCardName,
        .itemId = ITEM_RED_CARD,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_RED_CARD,
        .holdEffectParam = 0,
        .keepItem = TRUE,
        .description = sRedCardDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_RING_TARGET] =
    {
        .name = sRingTargetName,
        .itemId = ITEM_RING_TARGET,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_RING_TARGET,
        .holdEffectParam = 0,
        .keepItem = TRUE,
        .description = sRingTargetDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_BINDING_BAND] =
    {
        .name = sBindingBandName,
        .itemId = ITEM_BINDING_BAND,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_BINDING_BAND,
        .description = sBindingBandDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_EJECT_BUTTON] =
    {
        .name = sEjectButtonName,
        .itemId = ITEM_EJECT_BUTTON,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_EJECT_BUTTON,
        .holdEffectParam = 0,
        .keepItem = TRUE,
        .description = sEjectButtonDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_WEAKNESS_POLICY] =
    {
        .name = sWeaknessPolicyName,
        .plural = sWeaknessPolicyPluralName,
        .itemId = ITEM_WEAKNESS_POLICY,
        .price = CANDY_COST(1000),
        .holdEffect = HOLD_EFFECT_WEAKNESS_POLICY,
        .holdEffectParam = 0,
        .keepItem = TRUE,
        .description = sWeaknessPolicyDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_ASSAULT_VEST] =
    {
        .name = sAssaultVestName,
        .itemId = ITEM_ASSAULT_VEST,
        .price = CANDY_COST(1000),
        .holdEffect = HOLD_EFFECT_ASSAULT_VEST,
        .holdEffectParam = 50,
        .keepItem = TRUE,
        .description = sAssaultVestDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_SAFETY_GOGGLES] =
    {
        .name = sSafetyGogglesName,
        .quantum = sQuantum_Pair,
        .itemId = ITEM_SAFETY_GOGGLES,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_SAFETY_GOGGLES,
        .description = sSafetyGogglesDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_ADRENALINE_ORB] =
    {
        .name = sAdrenalineOrbName,
        .itemId = ITEM_ADRENALINE_ORB,
        .price = CANDY_COST(300),
        .holdEffect = HOLD_EFFECT_ADRENALINE_ORB,
        .description = sAdrenalineOrbDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_TERRAIN_EXTENDER] =
    {
        .name = sTerrainExtenderName,
        .itemId = ITEM_TERRAIN_EXTENDER,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_TERRAIN_EXTENDER,
        .description = sTerrainExtenderDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 60,
    },

    [ITEM_PROTECTIVE_PADS] =
    {
        .name = sProtectivePadsName,
        .quantum = sQuantum_Set,
        .itemId = ITEM_PROTECTIVE_PADS,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_PROTECTIVE_PADS,
        .description = sProtectivePadsDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_THROAT_SPRAY] =
    {
        .name = sThroatSprayName,
        .quantum = sQuantum_Bottle,
        .itemId = ITEM_THROAT_SPRAY,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_THROAT_SPRAY,
        .description = sThroatSprayDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
    },

    [ITEM_EJECT_PACK] =
    {
        .name = sEjectPackName,
        .itemId = ITEM_EJECT_PACK,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_EJECT_PACK,
        .description = sEjectPackDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 50,
    },

    [ITEM_HEAVY_DUTY_BOOTS] =
    {
        .name = sHeavyDutyBootsName,
        .quantum = sQuantum_Pair,
        .itemId = ITEM_HEAVY_DUTY_BOOTS,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_HEAVY_DUTY_BOOTS,
        .description = sHeavyDutyBootsDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_BLUNDER_POLICY] =
    {
        .name = sBlunderPolicyName,
        .plural = sBlunderPolicyPluralName,
        .itemId = ITEM_BLUNDER_POLICY,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_BLUNDER_POLICY,
        .description = sBlunderPolicyDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
    },

    [ITEM_ROOM_SERVICE] =
    {
        .name = sRoomServiceName,
        .quantum = sQuantum_VoucherFor,
        .plural = sQuantum_VouchersFor,
        .altQuantum = TRUE,
        .itemId = ITEM_ROOM_SERVICE,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_ROOM_SERVICE,
        .description = sRoomServiceDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 100,
    },

    [ITEM_UTILITY_UMBRELLA] =
    {
        .name = sUtilityUmbrellaName,
        .itemId = ITEM_UTILITY_UMBRELLA,
        .price = CANDY_COST(4000),
        .holdEffect = HOLD_EFFECT_UTILITY_UMBRELLA,
        .description = sUtilityUmbrellaDesc,
        .keepItem = TRUE,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 60,
    },

// #pragma endregion

// #pragma region Berries

    [ITEM_CHERI_BERRY] =
    {
        .name = sCheriBerryName,
        .itemId = ITEM_CHERI_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_CURE_PAR,
        .description = sCheriBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = ITEM_B_USE_MEDICINE,
        .itemEffect = gItemEffect_CheriBerry,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .flingPower = 10,
    },

    [ITEM_CHESTO_BERRY] =
    {
        .name = sChestoBerryName,
        .itemId = ITEM_CHESTO_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_CURE_SLP,
        .description = sChestoBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = ITEM_B_USE_MEDICINE,
        .itemEffect = gItemEffect_ChestoBerry,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .flingPower = 10,
    },

    [ITEM_PECHA_BERRY] =
    {
        .name = sPechaBerryName,
        .itemId = ITEM_PECHA_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_CURE_PSN,
        .description = sPechaBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = ITEM_B_USE_MEDICINE,
        .itemEffect = gItemEffect_PechaBerry,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .flingPower = 10,
    },

    [ITEM_RAWST_BERRY] =
    {
        .name = sRawstBerryName,
        .itemId = ITEM_RAWST_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_CURE_BRN,
        .description = sRawstBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = ITEM_B_USE_MEDICINE,
        .itemEffect = gItemEffect_RawstBerry,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .flingPower = 10,
    },

    [ITEM_ASPEAR_BERRY] =
    {
        .name = sAspearBerryName,
        .itemId = ITEM_ASPEAR_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_CURE_FRZ,
        .description = sAspearBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = ITEM_B_USE_MEDICINE,
        .itemEffect = gItemEffect_AspearBerry,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .flingPower = 10,
    },

    [ITEM_LEPPA_BERRY] =
    {
        .name = sLeppaBerryName,
        .itemId = ITEM_LEPPA_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_RESTORE_PP,
        .holdEffectParam = 10,
        .description = sLeppaBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_PPRecovery,
        .battleUsage = ITEM_B_USE_MEDICINE,
        .itemEffect = gItemEffect_LeppaBerry,
        .battleUseFunc = ItemUseInBattle_PPRecovery,
        .flingPower = 10,
    },

    [ITEM_ORAN_BERRY] =
    {
        .name = sOranBerryName,
        .itemId = ITEM_ORAN_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_RESTORE_HP,
        .holdEffectParam = 10,
        .description = sOranBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = ITEM_B_USE_MEDICINE,
        .itemEffect = gItemEffect_OranBerry,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .flingPower = 10,
    },

    [ITEM_PERSIM_BERRY] =
    {
        .name = sPersimBerryName,
        .itemId = ITEM_PERSIM_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_CURE_CONFUSION,
        .description = sPersimBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = ITEM_B_USE_MEDICINE,
        .itemEffect = gItemEffect_PersimBerry,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .flingPower = 10,
    },

    [ITEM_LUM_BERRY] =
    {
        .name = sLumBerryName,
        .itemId = ITEM_LUM_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_CURE_STATUS,
        .description = sLumBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = ITEM_B_USE_MEDICINE,
        .itemEffect = gItemEffect_HealAllStatus,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .flingPower = 10,
    },

    [ITEM_SITRUS_BERRY] =
    {
        .name = sSitrusBerryName,
        .itemId = ITEM_SITRUS_BERRY,
        .price = CANDY_COST(20),
#if I_SITRUS_BERRY_HEAL >= GEN_4
        .holdEffect = HOLD_EFFECT_RESTORE_PCT_HP,
        .holdEffectParam = 25,
#else
        .holdEffect = HOLD_EFFECT_RESTORE_HP,
        .holdEffectParam = 30,
#endif
        .description = sSitrusBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = ITEM_B_USE_MEDICINE,
        .itemEffect = gItemEffect_SitrusBerry,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .flingPower = 10,
    },

#if B_CONFUSE_BERRIES_HEAL >= GEN_8
    #define CONFUSE_BERRY_HEAL_FRACTION 3
#elif B_CONFUSE_BERRIES_HEAL == GEN_7
    #define CONFUSE_BERRY_HEAL_FRACTION 2
#else
    #define CONFUSE_BERRY_HEAL_FRACTION 8
#endif

    [ITEM_FIGY_BERRY] =
    {
        .name = sFigyBerryName,
        .itemId = ITEM_FIGY_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_CONFUSE_SPICY,
        .holdEffectParam = CONFUSE_BERRY_HEAL_FRACTION,
        .description = sFigyBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_WIKI_BERRY] =
    {
        .name = sWikiBerryName,
        .itemId = ITEM_WIKI_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_CONFUSE_DRY,
        .holdEffectParam = CONFUSE_BERRY_HEAL_FRACTION,
        .description = sWikiBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_MAGO_BERRY] =
    {
        .name = sMagoBerryName,
        .itemId = ITEM_MAGO_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_CONFUSE_SWEET,
        .holdEffectParam = CONFUSE_BERRY_HEAL_FRACTION,
        .description = sMagoBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_AGUAV_BERRY] =
    {
        .name = sAguavBerryName,
        .itemId = ITEM_AGUAV_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_CONFUSE_BITTER,
        .holdEffectParam = CONFUSE_BERRY_HEAL_FRACTION,
        .description = sAguavBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_IAPAPA_BERRY] =
    {
        .name = sIapapaBerryName,
        .itemId = ITEM_IAPAPA_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_CONFUSE_SOUR,
        .holdEffectParam = CONFUSE_BERRY_HEAL_FRACTION,
        .description = sIapapaBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

#undef CONFUSE_BERRY_HEAL_FRACTION

    [ITEM_RAZZ_BERRY] =
    {
        .name = sRazzBerryName,
        .itemId = ITEM_RAZZ_BERRY,
        .price = CANDY_COST(20),
        .description = sRazzBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_BLUK_BERRY] =
    {
        .name = sBlukBerryName,
        .itemId = ITEM_BLUK_BERRY,
        .price = CANDY_COST(20),
        .description = sBlukBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_NANAB_BERRY] =
    {
        .name = sNanabBerryName,
        .itemId = ITEM_NANAB_BERRY,
        .price = CANDY_COST(20),
        .description = sNanabBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_WEPEAR_BERRY] =
    {
        .name = sWepearBerryName,
        .itemId = ITEM_WEPEAR_BERRY,
        .price = CANDY_COST(20),
        .description = sWepearBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_PINAP_BERRY] =
    {
        .name = sPinapBerryName,
        .itemId = ITEM_PINAP_BERRY,
        .price = CANDY_COST(20),
        .description = sPinapBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_POMEG_BERRY] =
    {
        .name = sPomegBerryName,
        .itemId = ITEM_POMEG_BERRY,
        .price = CANDY_COST(20),
        .description = sPomegBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_PARTY_MENU,
        .itemEffect = gItemEffect_PomegBerry,
        .fieldUseFunc = ItemUseOutOfBattle_ReduceEV,
        .flingPower = 10,
    },

    [ITEM_KELPSY_BERRY] =
    {
        .name = sKelpsyBerryName,
        .itemId = ITEM_KELPSY_BERRY,
        .price = CANDY_COST(20),
        .description = sKelpsyBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_PARTY_MENU,
        .itemEffect = gItemEffect_KelpsyBerry,
        .fieldUseFunc = ItemUseOutOfBattle_ReduceEV,
        .flingPower = 10,
    },

    [ITEM_QUALOT_BERRY] =
    {
        .name = sQualotBerryName,
        .itemId = ITEM_QUALOT_BERRY,
        .price = CANDY_COST(20),
        .description = sQualotBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_PARTY_MENU,
        .itemEffect = gItemEffect_QualotBerry,
        .fieldUseFunc = ItemUseOutOfBattle_ReduceEV,
        .flingPower = 10,
    },

    [ITEM_HONDEW_BERRY] =
    {
        .name = sHondewBerryName,
        .itemId = ITEM_HONDEW_BERRY,
        .price = CANDY_COST(20),
        .description = sHondewBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_PARTY_MENU,
        .itemEffect = gItemEffect_HondewBerry,
        .fieldUseFunc = ItemUseOutOfBattle_ReduceEV,
        .flingPower = 10,
    },

    [ITEM_GREPA_BERRY] =
    {
        .name = sGrepaBerryName,
        .itemId = ITEM_GREPA_BERRY,
        .price = CANDY_COST(20),
        .description = sGrepaBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_PARTY_MENU,
        .itemEffect = gItemEffect_GrepaBerry,
        .fieldUseFunc = ItemUseOutOfBattle_ReduceEV,
        .flingPower = 10,
    },

    [ITEM_TAMATO_BERRY] =
    {
        .name = sTamatoBerryName,
        .itemId = ITEM_TAMATO_BERRY,
        .price = CANDY_COST(20),
        .description = sTamatoBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_PARTY_MENU,
        .itemEffect = gItemEffect_TamatoBerry,
        .fieldUseFunc = ItemUseOutOfBattle_ReduceEV,
        .flingPower = 10,
    },

    [ITEM_CORNN_BERRY] =
    {
        .name = sCornnBerryName,
        .itemId = ITEM_CORNN_BERRY,
        .price = CANDY_COST(20),
        .description = sCornnBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_MAGOST_BERRY] =
    {
        .name = sMagostBerryName,
        .itemId = ITEM_MAGOST_BERRY,
        .price = CANDY_COST(20),
        .description = sMagostBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_RABUTA_BERRY] =
    {
        .name = sRabutaBerryName,
        .itemId = ITEM_RABUTA_BERRY,
        .price = CANDY_COST(20),
        .description = sRabutaBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_NOMEL_BERRY] =
    {
        .name = sNomelBerryName,
        .itemId = ITEM_NOMEL_BERRY,
        .price = CANDY_COST(20),
        .description = sNomelBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_SPELON_BERRY] =
    {
        .name = sSpelonBerryName,
        .itemId = ITEM_SPELON_BERRY,
        .price = CANDY_COST(20),
        .description = sSpelonBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_PAMTRE_BERRY] =
    {
        .name = sPamtreBerryName,
        .itemId = ITEM_PAMTRE_BERRY,
        .price = CANDY_COST(20),
        .description = sPamtreBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_WATMEL_BERRY] =
    {
        .name = sWatmelBerryName,
        .itemId = ITEM_WATMEL_BERRY,
        .price = CANDY_COST(20),
        .description = sWatmelBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_DURIN_BERRY] =
    {
        .name = sDurinBerryName,
        .itemId = ITEM_DURIN_BERRY,
        .price = CANDY_COST(20),
        .description = sDurinBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_BELUE_BERRY] =
    {
        .name = sBelueBerryName,
        .itemId = ITEM_BELUE_BERRY,
        .price = CANDY_COST(20),
        .description = sBelueBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_CHILAN_BERRY] =
    {
        .name = sChilanBerryName,
        .itemId = ITEM_CHILAN_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_RESIST_BERRY,
        .holdEffectParam = TYPE_NORMAL,
        .description = sChilanBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_OCCA_BERRY] =
    {
        .name = sOccaBerryName,
        .itemId = ITEM_OCCA_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_RESIST_BERRY,
        .holdEffectParam = TYPE_FIRE,
        .description = sOccaBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_PASSHO_BERRY] =
    {
        .name = sPasshoBerryName,
        .itemId = ITEM_PASSHO_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_RESIST_BERRY,
        .holdEffectParam = TYPE_WATER,
        .description = sPasshoBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_WACAN_BERRY] =
    {
        .name = sWacanBerryName,
        .itemId = ITEM_WACAN_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_RESIST_BERRY,
        .holdEffectParam = TYPE_ELECTRIC,
        .description = sWacanBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_RINDO_BERRY] =
    {
        .name = sRindoBerryName,
        .itemId = ITEM_RINDO_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_RESIST_BERRY,
        .holdEffectParam = TYPE_GRASS,
        .description = sRindoBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_YACHE_BERRY] =
    {
        .name = sYacheBerryName,
        .itemId = ITEM_YACHE_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_RESIST_BERRY,
        .holdEffectParam = TYPE_ICE,
        .description = sYacheBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_CHOPLE_BERRY] =
    {
        .name = sChopleBerryName,
        .itemId = ITEM_CHOPLE_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_RESIST_BERRY,
        .holdEffectParam = TYPE_FIGHTING,
        .description = sChopleBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_KEBIA_BERRY] =
    {
        .name = sKebiaBerryName,
        .itemId = ITEM_KEBIA_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_RESIST_BERRY,
        .holdEffectParam = TYPE_POISON,
        .description = sKebiaBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_SHUCA_BERRY] =
    {
        .name = sShucaBerryName,
        .itemId = ITEM_SHUCA_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_RESIST_BERRY,
        .holdEffectParam = TYPE_GROUND,
        .description = sShucaBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_COBA_BERRY] =
    {
        .name = sCobaBerryName,
        .itemId = ITEM_COBA_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_RESIST_BERRY,
        .holdEffectParam = TYPE_FLYING,
        .description = sCobaBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_PAYAPA_BERRY] =
    {
        .name = sPayapaBerryName,
        .itemId = ITEM_PAYAPA_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_RESIST_BERRY,
        .holdEffectParam = TYPE_PSYCHIC,
        .description = sPayapaBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_TANGA_BERRY] =
    {
        .name = sTangaBerryName,
        .itemId = ITEM_TANGA_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_RESIST_BERRY,
        .holdEffectParam = TYPE_BUG,
        .description = sTangaBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_CHARTI_BERRY] =
    {
        .name = sChartiBerryName,
        .itemId = ITEM_CHARTI_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_RESIST_BERRY,
        .holdEffectParam = TYPE_ROCK,
        .description = sChartiBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_KASIB_BERRY] =
    {
        .name = sKasibBerryName,
        .itemId = ITEM_KASIB_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_RESIST_BERRY,
        .holdEffectParam = TYPE_GHOST,
        .description = sKasibBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_HABAN_BERRY] =
    {
        .name = sHabanBerryName,
        .itemId = ITEM_HABAN_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_RESIST_BERRY,
        .holdEffectParam = TYPE_DRAGON,
        .description = sHabanBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_COLBUR_BERRY] =
    {
        .name = sColburBerryName,
        .itemId = ITEM_COLBUR_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_RESIST_BERRY,
        .holdEffectParam = TYPE_DARK,
        .description = sColburBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_BABIRI_BERRY] =
    {
        .name = sBabiriBerryName,
        .itemId = ITEM_BABIRI_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_RESIST_BERRY,
        .holdEffectParam = TYPE_STEEL,
        .description = sBabiriBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_ROSELI_BERRY] =
    {
        .name = sRoseliBerryName,
        .itemId = ITEM_ROSELI_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_RESIST_BERRY,
        .holdEffectParam = TYPE_FAIRY,
        .description = sRoseliBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_LIECHI_BERRY] =
    {
        .name = sLiechiBerryName,
        .itemId = ITEM_LIECHI_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_ATTACK_UP,
        .holdEffectParam = 4,
        .description = sLiechiBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_GANLON_BERRY] =
    {
        .name = sGanlonBerryName,
        .itemId = ITEM_GANLON_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_DEFENSE_UP,
        .holdEffectParam = 4,
        .description = sGanlonBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_SALAC_BERRY] =
    {
        .name = sSalacBerryName,
        .itemId = ITEM_SALAC_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_SPEED_UP,
        .holdEffectParam = 4,
        .description = sSalacBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_PETAYA_BERRY] =
    {
        .name = sPetayaBerryName,
        .itemId = ITEM_PETAYA_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_SP_ATTACK_UP,
        .holdEffectParam = 4,
        .description = sPetayaBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_APICOT_BERRY] =
    {
        .name = sApicotBerryName,
        .itemId = ITEM_APICOT_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_SP_DEFENSE_UP,
        .holdEffectParam = 4,
        .description = sApicotBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_LANSAT_BERRY] =
    {
        .name = sLansatBerryName,
        .itemId = ITEM_LANSAT_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_CRITICAL_UP,
        .holdEffectParam = 4,
        .description = sLansatBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_STARF_BERRY] =
    {
        .name = sStarfBerryName,
        .itemId = ITEM_STARF_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_RANDOM_STAT_UP,
        .holdEffectParam = 4,
        .description = sStarfBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_ENIGMA_BERRY] =
    {
        .name = sEnigmaBerryName,
        .itemId = ITEM_ENIGMA_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_ENIGMA_BERRY,
        .description = sEnigmaBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_MICLE_BERRY] =
    {
        .name = sMicleBerryName,
        .itemId = ITEM_MICLE_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_MICLE_BERRY,
        .holdEffectParam = 4,
        .description = sMicleBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_CUSTAP_BERRY] =
    {
        .name = sCustapBerryName,
        .itemId = ITEM_CUSTAP_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_CUSTAP_BERRY,
        .holdEffectParam = 4,
        .description = sCustapBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_JABOCA_BERRY] =
    {
        .name = sJabocaBerryName,
        .itemId = ITEM_JABOCA_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_JABOCA_BERRY,
        .description = sJabocaBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_ROWAP_BERRY] =
    {
        .name = sRowapBerryName,
        .itemId = ITEM_ROWAP_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_ROWAP_BERRY,
        .description = sRowapBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_KEE_BERRY] =
    {
        .name = sKeeBerryName,
        .itemId = ITEM_KEE_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_KEE_BERRY,
        .description = sKeeBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_MARANGA_BERRY] =
    {
        .name = sMarangaBerryName,
        .itemId = ITEM_MARANGA_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_MARANGA_BERRY,
        .description = sMarangaBerryDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
    },

    [ITEM_ENIGMA_BERRY_E_READER] =
    {
        .name = sEnigmaBerryEReaderName,
        .itemId = ITEM_ENIGMA_BERRY,
        .price = CANDY_COST(20),
        .description = sEnigmaBerryEReaderDesc,
        .keepItem = TRUE,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU, // Type handled by ItemUseOutOfBattle_EnigmaBerry
        .fieldUseFunc = ItemUseOutOfBattle_EnigmaBerry,
        .battleUsage = ITEM_B_USE_MEDICINE,
        .battleUseFunc = ItemUseInBattle_EnigmaBerry,
        .flingPower = 10,
    },

// #pragma endregion

// #pragma region TMs/HMs
// They don't have a set flingPower, as that's handled by GetFlingPowerFromItemId.
    [ITEM_TM01_FOCUS_PUNCH] =
    {
        .name = sTM01Name,
        .itemId = ITEM_TM01_FOCUS_PUNCH,
        .price = CANDY_COST(3000),
        .description = sTM01Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM02_DRAGON_CLAW] =
    {
        .name = sTM02Name,
        .itemId = ITEM_TM02_DRAGON_CLAW,
        .price = CANDY_COST(3000),
        .description = sTM02Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM03_WATER_PULSE] =
    {
        .name = sTM03Name,
        .itemId = ITEM_TM03_WATER_PULSE,
        .price = CANDY_COST(3000),
        .description = sTM03Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM04_CALM_MIND] =
    {
        .name = sTM04Name,
        .itemId = ITEM_TM04_CALM_MIND,
        .price = CANDY_COST(3000),
        .description = sTM04Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM05_ROAR] =
    {
        .name = sTM05Name,
        .itemId = ITEM_TM05_ROAR,
        .price = CANDY_COST(1000),
        .description = sTM05Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM06_TOXIC] =
    {
        .name = sTM06Name,
        .itemId = ITEM_TM06_TOXIC,
        .price = CANDY_COST(3000),
        .description = sTM06Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM07_HAIL] =
    {
        .name = sTM07Name,
        .itemId = ITEM_TM07_HAIL,
        .price = CANDY_COST(3000),
        .description = sTM07Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM08_BULK_UP] =
    {
        .name = sTM08Name,
        .itemId = ITEM_TM08_BULK_UP,
        .price = CANDY_COST(3000),
        .description = sTM08Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM09_BULLET_SEED] =
    {
        .name = sTM09Name,
        .itemId = ITEM_TM09_BULLET_SEED,
        .price = CANDY_COST(3000),
        .description = sTM09Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM10_HIDDEN_POWER] =
    {
        .name = sTM10Name,
        .itemId = ITEM_TM10_HIDDEN_POWER,
        .price = CANDY_COST(3000),
        .description = sTM10Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM11_SUNNY_DAY] =
    {
        .name = sTM11Name,
        .itemId = ITEM_TM11_SUNNY_DAY,
        .price = CANDY_COST(2000),
        .description = sTM11Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM12_TAUNT] =
    {
        .name = sTM12Name,
        .itemId = ITEM_TM12_TAUNT,
        .price = CANDY_COST(3000),
        .description = sTM12Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM13_ICE_BEAM] =
    {
        .name = sTM13Name,
        .itemId = ITEM_TM13_ICE_BEAM,
        .price = CANDY_COST(3000),
        .description = sTM13Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM14_BLIZZARD] =
    {
        .name = sTM14Name,
        .itemId = ITEM_TM14_BLIZZARD,
        .price = CANDY_COST(5500),
        .description = sTM14Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM15_HYPER_BEAM] =
    {
        .name = sTM15Name,
        .itemId = ITEM_TM15_HYPER_BEAM,
        .price = CANDY_COST(7500),
        .description = sTM15Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM16_LIGHT_SCREEN] =
    {
        .name = sTM16Name,
        .itemId = ITEM_TM16_LIGHT_SCREEN,
        .price = CANDY_COST(3000),
        .description = sTM16Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM17_PROTECT] =
    {
        .name = sTM17Name,
        .itemId = ITEM_TM17_PROTECT,
        .price = CANDY_COST(3000),
        .description = sTM17Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM18_RAIN_DANCE] =
    {
        .name = sTM18Name,
        .itemId = ITEM_TM18_RAIN_DANCE,
        .price = CANDY_COST(2000),
        .description = sTM18Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM19_GIGA_DRAIN] =
    {
        .name = sTM19Name,
        .itemId = ITEM_TM19_GIGA_DRAIN,
        .price = CANDY_COST(3000),
        .description = sTM19Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM20_SAFEGUARD] =
    {
        .name = sTM20Name,
        .itemId = ITEM_TM20_SAFEGUARD,
        .price = CANDY_COST(3000),
        .description = sTM20Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM21_FRUSTRATION] =
    {
        .name = sTM21Name,
        .itemId = ITEM_TM21_FRUSTRATION,
        .price = CANDY_COST(1000),
        .description = sTM21Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM22_SOLAR_BEAM] =
    {
        .name = sTM22Name,
        .itemId = ITEM_TM22_SOLAR_BEAM,
        .price = CANDY_COST(3000),
        .description = sTM22Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM23_IRON_TAIL] =
    {
        .name = sTM23Name,
        .itemId = ITEM_TM23_IRON_TAIL,
        .price = CANDY_COST(3000),
        .description = sTM23Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM24_THUNDERBOLT] =
    {
        .name = sTM24Name,
        .itemId = ITEM_TM24_THUNDERBOLT,
        .price = CANDY_COST(3000),
        .description = sTM24Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM25_THUNDER] =
    {
        .name = sTM25Name,
        .itemId = ITEM_TM25_THUNDER,
        .price = CANDY_COST(5500),
        .description = sTM25Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM26_EARTHQUAKE] =
    {
        .name = sTM26Name,
        .itemId = ITEM_TM26_EARTHQUAKE,
        .price = CANDY_COST(3000),
        .description = sTM26Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM27_RETURN] =
    {
        .name = sTM27Name,
        .itemId = ITEM_TM27_RETURN,
        .price = CANDY_COST(1000),
        .description = sTM27Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM28_DIG] =
    {
        .name = sTM28Name,
        .itemId = ITEM_TM28_DIG,
        .price = CANDY_COST(2000),
        .description = sTM28Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM29_PSYCHIC] =
    {
        .name = sTM29Name,
        .itemId = ITEM_TM29_PSYCHIC,
        .price = CANDY_COST(2000),
        .description = sTM29Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM30_SHADOW_BALL] =
    {
        .name = sTM30Name,
        .itemId = ITEM_TM30_SHADOW_BALL,
        .price = CANDY_COST(3000),
        .description = sTM30Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM31_BRICK_BREAK] =
    {
        .name = sTM31Name,
        .itemId = ITEM_TM31_BRICK_BREAK,
        .price = CANDY_COST(3000),
        .description = sTM31Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM32_DOUBLE_TEAM] =
    {
        .name = sTM32Name,
        .itemId = ITEM_TM32_DOUBLE_TEAM,
        .price = CANDY_COST(2000),
        .description = sTM32Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM33_REFLECT] =
    {
        .name = sTM33Name,
        .itemId = ITEM_TM33_REFLECT,
        .price = CANDY_COST(3000),
        .description = sTM33Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM34_SHOCK_WAVE] =
    {
        .name = sTM34Name,
        .itemId = ITEM_TM34_SHOCK_WAVE,
        .price = CANDY_COST(3000),
        .description = sTM34Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM35_FLAMETHROWER] =
    {
        .name = sTM35Name,
        .itemId = ITEM_TM35_FLAMETHROWER,
        .price = CANDY_COST(3000),
        .description = sTM35Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM36_SLUDGE_BOMB] =
    {
        .name = sTM36Name,
        .itemId = ITEM_TM36_SLUDGE_BOMB,
        .price = CANDY_COST(1000),
        .description = sTM36Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM37_SANDSTORM] =
    {
        .name = sTM37Name,
        .itemId = ITEM_TM37_SANDSTORM,
        .price = CANDY_COST(2000),
        .description = sTM37Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM38_FIRE_BLAST] =
    {
        .name = sTM38Name,
        .itemId = ITEM_TM38_FIRE_BLAST,
        .price = CANDY_COST(5500),
        .description = sTM38Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM39_ROCK_TOMB] =
    {
        .name = sTM39Name,
        .itemId = ITEM_TM39_ROCK_TOMB,
        .price = CANDY_COST(3000),
        .description = sTM39Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM40_AERIAL_ACE] =
    {
        .name = sTM40Name,
        .itemId = ITEM_TM40_AERIAL_ACE,
        .price = CANDY_COST(3000),
        .description = sTM40Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM41_TORMENT] =
    {
        .name = sTM41Name,
        .itemId = ITEM_TM41_TORMENT,
        .price = CANDY_COST(3000),
        .description = sTM41Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM42_FACADE] =
    {
        .name = sTM42Name,
        .itemId = ITEM_TM42_FACADE,
        .price = CANDY_COST(3000),
        .description = sTM42Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM43_SECRET_POWER] =
    {
        .name = sTM43Name,
        .itemId = ITEM_TM43_SECRET_POWER,
        .price = CANDY_COST(3000),
        .description = sTM43Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM44_REST] =
    {
        .name = sTM44Name,
        .itemId = ITEM_TM44_REST,
        .price = CANDY_COST(3000),
        .description = sTM44Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM45_ATTRACT] =
    {
        .name = sTM45Name,
        .itemId = ITEM_TM45_ATTRACT,
        .price = CANDY_COST(3000),
        .description = sTM45Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM46_THIEF] =
    {
        .name = sTM46Name,
        .itemId = ITEM_TM46_THIEF,
        .price = CANDY_COST(3000),
        .description = sTM46Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM47_STEEL_WING] =
    {
        .name = sTM47Name,
        .itemId = ITEM_TM47_STEEL_WING,
        .price = CANDY_COST(3000),
        .description = sTM47Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM48_SKILL_SWAP] =
    {
        .name = sTM48Name,
        .itemId = ITEM_TM48_SKILL_SWAP,
        .price = CANDY_COST(3000),
        .description = sTM48Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM49_SNATCH] =
    {
        .name = sTM49Name,
        .itemId = ITEM_TM49_SNATCH,
        .price = CANDY_COST(3000),
        .description = sTM49Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM50_OVERHEAT] =
    {
        .name = sTM50Name,
        .itemId = ITEM_TM50_OVERHEAT,
        .price = CANDY_COST(3000),
        .description = sTM50Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM51] =
    {
        .name = sTM51Name,
        .itemId = ITEM_TM51,
        .price = CANDY_COST(3000),
        .description = sTM51Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM52] =
    {
        .name = sTM52Name,
        .itemId = ITEM_TM52,
        .price = CANDY_COST(3000),
        .description = sTM52Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM53] =
    {
        .name = sTM53Name,
        .itemId = ITEM_TM53,
        .price = CANDY_COST(3000),
        .description = sTM53Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM54] =
    {
        .name = sTM54Name,
        .itemId = ITEM_TM54,
        .price = CANDY_COST(3000),
        .description = sTM54Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM55] =
    {
        .name = sTM55Name,
        .itemId = ITEM_TM55,
        .price = CANDY_COST(3000),
        .description = sTM55Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM56] =
    {
        .name = sTM56Name,
        .itemId = ITEM_TM56,
        .price = CANDY_COST(3000),
        .description = sTM56Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM57] =
    {
        .name = sTM57Name,
        .itemId = ITEM_TM57,
        .price = CANDY_COST(3000),
        .description = sTM57Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM58] =
    {
        .name = sTM58Name,
        .itemId = ITEM_TM58,
        .price = CANDY_COST(3000),
        .description = sTM58Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM59] =
    {
        .name = sTM59Name,
        .itemId = ITEM_TM59,
        .price = CANDY_COST(3000),
        .description = sTM59Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM60] =
    {
        .name = sTM60Name,
        .itemId = ITEM_TM60,
        .price = CANDY_COST(3000),
        .description = sTM60Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM61] =
    {
        .name = sTM61Name,
        .itemId = ITEM_TM61,
        .price = CANDY_COST(3000),
        .description = sTM61Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM62] =
    {
        .name = sTM62Name,
        .itemId = ITEM_TM62,
        .price = CANDY_COST(3000),
        .description = sTM62Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM63] =
    {
        .name = sTM63Name,
        .itemId = ITEM_TM63,
        .price = CANDY_COST(3000),
        .description = sTM63Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM64] =
    {
        .name = sTM64Name,
        .itemId = ITEM_TM64,
        .price = CANDY_COST(3000),
        .description = sTM64Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM65] =
    {
        .name = sTM65Name,
        .itemId = ITEM_TM65,
        .price = CANDY_COST(3000),
        .description = sTM65Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM66] =
    {
        .name = sTM66Name,
        .itemId = ITEM_TM66,
        .price = CANDY_COST(3000),
        .description = sTM66Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM67] =
    {
        .name = sTM67Name,
        .itemId = ITEM_TM67,
        .price = CANDY_COST(3000),
        .description = sTM67Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM68] =
    {
        .name = sTM68Name,
        .itemId = ITEM_TM68,
        .price = CANDY_COST(3000),
        .description = sTM68Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM69] =
    {
        .name = sTM69Name,
        .itemId = ITEM_TM69,
        .price = CANDY_COST(3000),
        .description = sTM69Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM70] =
    {
        .name = sTM70Name,
        .itemId = ITEM_TM70,
        .price = CANDY_COST(3000),
        .description = sTM70Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM71] =
    {
        .name = sTM71Name,
        .itemId = ITEM_TM71,
        .price = CANDY_COST(3000),
        .description = sTM71Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM72] =
    {
        .name = sTM72Name,
        .itemId = ITEM_TM72,
        .price = CANDY_COST(3000),
        .description = sTM72Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM73] =
    {
        .name = sTM73Name,
        .itemId = ITEM_TM73,
        .price = CANDY_COST(3000),
        .description = sTM73Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM74] =
    {
        .name = sTM74Name,
        .itemId = ITEM_TM74,
        .price = CANDY_COST(3000),
        .description = sTM74Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM75] =
    {
        .name = sTM75Name,
        .itemId = ITEM_TM75,
        .price = CANDY_COST(3000),
        .description = sTM75Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM76] =
    {
        .name = sTM76Name,
        .itemId = ITEM_TM76,
        .price = CANDY_COST(3000),
        .description = sTM76Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM77] =
    {
        .name = sTM77Name,
        .itemId = ITEM_TM77,
        .price = CANDY_COST(3000),
        .description = sTM77Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM78] =
    {
        .name = sTM78Name,
        .itemId = ITEM_TM78,
        .price = CANDY_COST(3000),
        .description = sTM78Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM79] =
    {
        .name = sTM79Name,
        .itemId = ITEM_TM79,
        .price = CANDY_COST(3000),
        .description = sTM79Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM80] =
    {
        .name = sTM80Name,
        .itemId = ITEM_TM80,
        .price = CANDY_COST(3000),
        .description = sTM80Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM81] =
    {
        .name = sTM81Name,
        .itemId = ITEM_TM81,
        .price = CANDY_COST(3000),
        .description = sTM81Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM82] =
    {
        .name = sTM82Name,
        .itemId = ITEM_TM82,
        .price = CANDY_COST(3000),
        .description = sTM82Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM83] =
    {
        .name = sTM83Name,
        .itemId = ITEM_TM83,
        .price = CANDY_COST(3000),
        .description = sTM83Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM84] =
    {
        .name = sTM84Name,
        .itemId = ITEM_TM84,
        .price = CANDY_COST(3000),
        .description = sTM84Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM85] =
    {
        .name = sTM85Name,
        .itemId = ITEM_TM85,
        .price = CANDY_COST(3000),
        .description = sTM85Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM86] =
    {
        .name = sTM86Name,
        .itemId = ITEM_TM86,
        .price = CANDY_COST(3000),
        .description = sTM86Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM87] =
    {
        .name = sTM87Name,
        .itemId = ITEM_TM87,
        .price = CANDY_COST(3000),
        .description = sTM87Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM88] =
    {
        .name = sTM88Name,
        .itemId = ITEM_TM88,
        .price = CANDY_COST(3000),
        .description = sTM88Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM89] =
    {
        .name = sTM89Name,
        .itemId = ITEM_TM89,
        .price = CANDY_COST(3000),
        .description = sTM89Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM90] =
    {
        .name = sTM90Name,
        .itemId = ITEM_TM90,
        .price = CANDY_COST(3000),
        .description = sTM90Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM91] =
    {
        .name = sTM91Name,
        .itemId = ITEM_TM91,
        .price = CANDY_COST(3000),
        .description = sTM91Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM92] =
    {
        .name = sTM92Name,
        .itemId = ITEM_TM92,
        .price = CANDY_COST(3000),
        .description = sTM92Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM93] =
    {
        .name = sTM93Name,
        .itemId = ITEM_TM93,
        .price = CANDY_COST(3000),
        .description = sTM93Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM94] =
    {
        .name = sTM94Name,
        .itemId = ITEM_TM94,
        .price = CANDY_COST(3000),
        .description = sTM94Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM95] =
    {
        .name = sTM95Name,
        .itemId = ITEM_TM95,
        .price = CANDY_COST(3000),
        .description = sTM95Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM96] =
    {
        .name = sTM96Name,
        .itemId = ITEM_TM96,
        .price = CANDY_COST(3000),
        .description = sTM96Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM97] =
    {
        .name = sTM97Name,
        .itemId = ITEM_TM97,
        .price = CANDY_COST(3000),
        .description = sTM97Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM98] =
    {
        .name = sTM98Name,
        .itemId = ITEM_TM98,
        .price = CANDY_COST(3000),
        .description = sTM98Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM99] =
    {
        .name = sTM99Name,
        .itemId = ITEM_TM99,
        .price = CANDY_COST(3000),
        .description = sTM99Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM100] =
    {
        .name = sTM100Name,
        .itemId = ITEM_TM100,
        .price = CANDY_COST(3000),
        .description = sTM100Desc,
        .keepItem = TRUE,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_HM01_CUT] =
    {
        .name = sHM01Name,
        .itemId = ITEM_HM01_CUT,
        .price = CANDY_COST(0),
        .description = sHM01Desc,
        .keepItem = TRUE,
        .importance = 1,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_HM02_FLY] =
    {
        .name = sHM02Name,
        .itemId = ITEM_HM02_FLY,
        .price = CANDY_COST(0),
        .description = sHM02Desc,
        .keepItem = TRUE,
        .importance = 1,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_HM03_SURF] =
    {
        .name = sHM03Name,
        .itemId = ITEM_HM03_SURF,
        .price = CANDY_COST(0),
        .description = sHM03Desc,
        .keepItem = TRUE,
        .importance = 1,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_HM04_STRENGTH] =
    {
        .name = sHM04Name,
        .itemId = ITEM_HM04_STRENGTH,
        .price = CANDY_COST(0),
        .description = sHM04Desc,
        .keepItem = TRUE,
        .importance = 1,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_HM05_FLASH] =
    {
        .name = sHM05Name,
        .itemId = ITEM_HM05_FLASH,
        .price = CANDY_COST(0),
        .description = sHM05Desc,
        .keepItem = TRUE,
        .importance = 1,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_HM06_ROCK_SMASH] =
    {
        .name = sHM06Name,
        .itemId = ITEM_HM06_ROCK_SMASH,
        .price = CANDY_COST(0),
        .description = sHM06Desc,
        .keepItem = TRUE,
        .importance = 1,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_HM07_WATERFALL] =
    {
        .name = sHM07Name,
        .itemId = ITEM_HM07_WATERFALL,
        .price = CANDY_COST(0),
        .description = sHM07Desc,
        .keepItem = TRUE,
        .importance = 1,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_HM08_DIVE] =
    {
        .name = sHM08Name,
        .itemId = ITEM_HM08_DIVE,
        .price = CANDY_COST(0),
        .description = sHM08Desc,
        .keepItem = TRUE,
        .importance = 1,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

// #pragma endregion

// #pragma region Charms

    [ITEM_OVAL_CHARM] =
    {
        .name = sOvalCharmName,
        .itemId = ITEM_OVAL_CHARM,
        .price = 0,
        .importance = 1,
        .description = sOvalCharmDesc,
        .keepItem = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

    [ITEM_SHINY_CHARM] =
    {
        .name = sShinyCharmName,
        .itemId = ITEM_SHINY_CHARM,
        .price = 0,
        .importance = 1,
        .description = sShinyCharmDesc,
        .keepItem = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

    [ITEM_CATCHING_CHARM] =
    {
        .name = sCatchingCharmName,
        .itemId = ITEM_CATCHING_CHARM,
        .price = 0,
        .importance = 1,
        .description = sCatchingCharmDesc,
        .keepItem = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

    [ITEM_EXP_CHARM] =
    {
        .name = sExpCharmName,
        .itemId = ITEM_EXP_CHARM,
        .price = 0,
        .importance = 1,
        .description = sExpCharmDesc,
        .keepItem = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

// #pragma endregion

// #pragma region Form-changing Key Items

    [ITEM_ROTOM_CATALOG] =
    {
        .name = sRotomCatalogName,
        .itemId = ITEM_ROTOM_CATALOG,
        .price = 0,
        .importance = 1,
        .description = sRotomCatalogDesc,
        .keepItem = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse, // Todo
    },

    [ITEM_GRACIDEA] =
    {
        .name = sGracideaName,
        .itemId = ITEM_GRACIDEA,
        .price = 0,
        .description = sGracideaDesc,
        .keepItem = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_FormChange,
        .secondaryId = FORM_ITEM_USE_TIME,
    },

    [ITEM_REVEAL_GLASS] =
    {
        .name = sRevealGlassName,
        .itemId = ITEM_REVEAL_GLASS,
        .price = 0,
        .description = sRevealGlassDesc,
        .keepItem = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_FormChange,
        .secondaryId = FORM_ITEM_USE,
    },

    [ITEM_DNA_SPLICERS] =
    {
        .name = sDNASplicersName,
        .itemId = ITEM_DNA_SPLICERS,
        .price = 0,
        .description = sDNASplicersDesc,
        .keepItem = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_FormChange,
        .secondaryId = FORM_ITEM_USE,
    },

    [ITEM_ZYGARDE_CUBE] =
    {
        .name = sZygardeCubeName,
        .itemId = ITEM_ZYGARDE_CUBE,
        .price = 0,
        .importance = 1,
        .description = sZygardeCubeDesc,
        .keepItem = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse, // Todo
    },

    [ITEM_PRISON_BOTTLE] =
    {
        .name = sPrisonBottleName,
        .itemId = ITEM_PRISON_BOTTLE,
        .price = 0,
        .description = sPrisonBottleDesc,
        .keepItem = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_FormChange,
        .secondaryId = FORM_ITEM_USE,
    },

    [ITEM_N_SOLARIZER] =
    {
        .name = sNSolarizerName,
        .itemId = ITEM_N_SOLARIZER,
        .price = 0,
        .description = sNSolarizerDesc,
        .keepItem = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_FormChange,
        .secondaryId = FORM_ITEM_USE,
    },

    [ITEM_N_LUNARIZER] =
    {
        .name = sNLunarizerName,
        .itemId = ITEM_N_LUNARIZER,
        .price = 0,
        .description = sNLunarizerDesc,
        .keepItem = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_FormChange,
        .secondaryId = FORM_ITEM_USE,
    },

    [ITEM_REINS_OF_UNITY] =
    {
        .name = sReinsOfUnityName,
        .quantum = sQuantum_Set,
        .itemId = ITEM_REINS_OF_UNITY,
        .price = 0,
        .description = sReinsOfUnityDesc,
        .keepItem = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_FormChange,
        .secondaryId = FORM_ITEM_USE,
    },

// #pragma endregion

// #pragma region Battle Mechanic Key Items

    [ITEM_MEGA_RING] =
    {
        .name = sMegaRingName,
        .itemId = ITEM_MEGA_RING,
        .price = 0,
        .importance = 1,
        .description = sMegaRingDesc,
        .keepItem = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

    [ITEM_Z_POWER_RING] =
    {
        .name = sZPowerRingName,
        .itemId = ITEM_Z_POWER_RING,
        .price = 0,
        .importance = 1,
        .description = sZPowerRingDesc,
        .keepItem = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

    [ITEM_DYNAMAX_BAND] =
    {
        .name = sDynamaxBandName,
        .itemId = ITEM_DYNAMAX_BAND,
        .price = 0,
        .description = sDynamaxBandDesc,
        .keepItem = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

// #pragma endregion

// #pragma region Misc. Key Items

    [ITEM_BICYCLE] =
    {
        .name = sBicycleName,
        .itemId = ITEM_BICYCLE,
        .price = 0,
        .description = sBicycleDesc,
        .importance = 1,
        .registrability = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_FIELD,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

    [ITEM_MACH_BIKE] =
    {
        .name = sMachBikeName,
        .itemId = ITEM_MACH_BIKE,
        .price = 0,
        .description = sMachBikeDesc,
        .importance = 1,
        .registrability = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_FIELD,
        .fieldUseFunc = ItemUseOutOfBattle_Bike,
        .secondaryId = MACH_BIKE,
    },

    [ITEM_ACRO_BIKE] =
    {
        .name = sAcroBikeName,
        .itemId = ITEM_ACRO_BIKE,
        .price = 0,
        .description = sAcroBikeDesc,
        .importance = 1,
        .registrability = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_FIELD,
        .fieldUseFunc = ItemUseOutOfBattle_Bike,
        .secondaryId = ACRO_BIKE,
    },

    [ITEM_OLD_ROD] =
    {
        .name = sOldRodName,
        .itemId = ITEM_OLD_ROD,
        .price = 0,
        .description = sOldRodDesc,
        .importance = 1,
        .registrability = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_FIELD,
        .fieldUseFunc = ItemUseOutOfBattle_Rod,
        .secondaryId = OLD_ROD,
    },

    [ITEM_GOOD_ROD] =
    {
        .name = sGoodRodName,
        .itemId = ITEM_GOOD_ROD,
        .price = 0,
        .description = sGoodRodDesc,
        .importance = 1,
        .registrability = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_FIELD,
        .fieldUseFunc = ItemUseOutOfBattle_Rod,
        .secondaryId = GOOD_ROD,
    },

    [ITEM_SUPER_ROD] =
    {
        .name = sSuperRodName,
        .itemId = ITEM_SUPER_ROD,
        .price = 0,
        .description = sSuperRodDesc,
        .importance = 1,
        .registrability = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_FIELD,
        .fieldUseFunc = ItemUseOutOfBattle_Rod,
        .secondaryId = SUPER_ROD,
    },

    [ITEM_DOWSING_MACHINE] =
    {
        .name = sDowsingMachineName,
        .itemId = ITEM_DOWSING_MACHINE,
        .price = 0,
        .description = sDowsingMachineDesc,
        .keepItem = TRUE,
        .importance = 1,
        .registrability = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_FIELD,
        .fieldUseFunc = ItemUseOutOfBattle_Itemfinder,
    },

    [ITEM_TOWN_MAP] =
    {
        .name = sTownMapName,
        .itemId = ITEM_TOWN_MAP,
        .price = 0,
        .description = sTownMapDesc,
        .importance = 1,
        .registrability = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

    [ITEM_VS_SEEKER] =
    {
        .name = sVsSeekerName,
        .itemId = ITEM_VS_SEEKER,
        .price = 0,
        .description = sVsSeekerDesc,
        .importance = 1,
        .registrability = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_FIELD,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

    [ITEM_TM_CASE] =
    {
        .name = sTMCaseName,
        .itemId = ITEM_TM_CASE,
        .price = 0,
        .description = sTMCaseDesc,
        .importance = 1,
        .registrability = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

    [ITEM_BERRY_POUCH] =
    {
        .name = sBerryPouchName,
        .itemId = ITEM_BERRY_POUCH,
        .price = 0,
        .description = sBerryPouchDesc,
        .importance = 1,
        .registrability = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

    [ITEM_POKEMON_BOX_LINK] =
    {
        .name = sPokemonBoxLinkName,
        .itemId = ITEM_POKEMON_BOX_LINK,
        .price = 0,
        .description = sPokemonBoxLinkDesc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse, // Todo
    },

    [ITEM_COIN_CASE] =
    {
        .name = sCoinCaseName,
        .itemId = ITEM_COIN_CASE,
        .price = 0,
        .description = sCoinCaseDesc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CoinCase,
    },

    [ITEM_POWDER_JAR] =
    {
        .name = sPowderJarName,
        .itemId = ITEM_POWDER_JAR,
        .price = 0,
        .description = sPowderJarDesc,
        .importance = 1,
        .registrability = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_PowderJar,
    },

    [ITEM_WAILMER_PAIL] =
    {
        .name = sWailmerPailName,
        .itemId = ITEM_WAILMER_PAIL,
        .price = 0,
        .description = sWailmerPailDesc,
        .importance = 1,
        .keepItem = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_FIELD,
        .fieldUseFunc = ItemUseOutOfBattle_WailmerPail,
    },

    [ITEM_POKE_RADAR] =
    {
        .name = sPokeRadarName,
        .itemId = ITEM_POKE_RADAR,
        .price = 0,
        .description = sPokeRadarDesc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse, // Todo
    },

    [ITEM_POKEBLOCK_CASE] =
    {
        .name = sPokeblockCaseName,
        .itemId = ITEM_POKEBLOCK_CASE,
        .price = 0,
        .description = sPokeblockCaseDesc,
        .importance = 1,
        .registrability = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_PBLOCK_CASE,
        .fieldUseFunc = ItemUseOutOfBattle_PokeblockCase,
    },

    [ITEM_SOOT_SACK] =
    {
        .name = sSootSackName,
        .itemId = ITEM_SOOT_SACK,
        .price = 0,
        .description = sSootSackDesc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

    [ITEM_POKE_FLUTE] =
    {
        .name = sPokeFluteName,
        .itemId = ITEM_POKE_FLUTE,
        .price = 0,
        .description = sPokeFluteDesc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

    [ITEM_FAME_CHECKER] =
    {
        .name = sFameCheckerName,
        .itemId = ITEM_FAME_CHECKER,
        .price = 0,
        .description = sFameCheckerDesc,
        .importance = 1,
        .registrability = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

    [ITEM_TEACHY_TV] =
    {
        .name = sTeachyTVName,
        .itemId = ITEM_TEACHY_TV,
        .price = 0,
        .description = sTeachyTVDesc,
        .importance = 1,
        .registrability = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_FIELD,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

// #pragma endregion

// #pragma region Story Key Items

    [ITEM_SS_TICKET] =
    {
        .name = sSSTicketName,
        .itemId = ITEM_SS_TICKET,
        .price = 0,
        .description = sSSTicketDesc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

    [ITEM_EON_TICKET] =
    {
        .name = sEonTicketName,
        .itemId = ITEM_EON_TICKET,
        .price = 0,
        .description = sEonTicketDesc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 1,
    },

    [ITEM_MYSTIC_TICKET] =
    {
        .name = sMysticTicketName,
        .itemId = ITEM_MYSTIC_TICKET,
        .price = 0,
        .description = sMysticTicketDesc,
        .importance = 1,
        .registrability = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

    [ITEM_AURORA_TICKET] =
    {
        .name = sAuroraTicketName,
        .itemId = ITEM_AURORA_TICKET,
        .price = 0,
        .description = sAuroraTicketDesc,
        .importance = 1,
        .registrability = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

    [ITEM_OLD_SEA_MAP] =
    {
        .name = sOldSeaMapName,
        .itemId = ITEM_OLD_SEA_MAP,
        .price = 0,
        .description = sOldSeaMapDesc,
        .importance = 1,
        .registrability = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

    [ITEM_LETTER] =
    {
        .name = sLetterName,
        .itemId = ITEM_LETTER,
        .price = 0,
        .description = sLetterDesc,
        .importance = 2,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

    [ITEM_DEVON_PARTS] =
    {
        .name = sDevonPartsName,
        .quantum = sQuantum_Case,
        .itemId = ITEM_DEVON_PARTS,
        .price = 0,
        .description = sDevonPartsDesc,
        .importance = 2,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

    [ITEM_GO_GOGGLES] =
    {
        .name = sGoGogglesName,
        .itemId = ITEM_GO_GOGGLES,
        .price = 0,
        .description = sGoGogglesDesc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

    [ITEM_DEVON_SCOPE] =
    {
        .name = sDevonScopeName,
        .itemId = ITEM_DEVON_SCOPE,
        .price = 0,
        .description = sDevonScopeDesc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

    [ITEM_BASEMENT_KEY] =
    {
        .name = sBasementKeyName,
        .itemId = ITEM_BASEMENT_KEY,
        .price = 0,
        .description = sBasementKeyDesc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

    [ITEM_SCANNER] =
    {
        .name = sScannerName,
        .itemId = ITEM_SCANNER,
        .price = 0,
        .description = sScannerDesc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

    [ITEM_STORAGE_KEY] =
    {
        .name = sStorageKeyName,
        .itemId = ITEM_STORAGE_KEY,
        .price = 0,
        .description = sStorageKeyDesc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

    [ITEM_KEY_TO_ROOM_1] =
    {
        .name = sKeyToRoom1Name,
        .itemId = ITEM_KEY_TO_ROOM_1,
        .price = 0,
        .description = sKeyToRoom1Desc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

    [ITEM_KEY_TO_ROOM_2] =
    {
        .name = sKeyToRoom2Name,
        .itemId = ITEM_KEY_TO_ROOM_2,
        .price = 0,
        .description = sKeyToRoom2Desc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

    [ITEM_KEY_TO_ROOM_4] =
    {
        .name = sKeyToRoom4Name,
        .itemId = ITEM_KEY_TO_ROOM_4,
        .price = 0,
        .description = sKeyToRoom4Desc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

    [ITEM_KEY_TO_ROOM_6] =
    {
        .name = sKeyToRoom6Name,
        .itemId = ITEM_KEY_TO_ROOM_6,
        .price = 0,
        .description = sKeyToRoom6Desc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

    [ITEM_METEORITE] =
    {
        .name = sMeteoriteName,
        .itemId = ITEM_METEORITE,
        .price = 0,
        .description = sMeteoriteDesc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

    [ITEM_MAGMA_EMBLEM] =
    {
        .name = sMagmaEmblemName,
        .itemId = ITEM_MAGMA_EMBLEM,
        .price = 0,
        .description = sMagmaEmblemDesc,
        .importance = 1,
        .registrability = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

    [ITEM_CONTEST_PASS] =
    {
        .name = sContestPassName,
        .itemId = ITEM_CONTEST_PASS,
        .price = 0,
        .description = sContestPassDesc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

    [ITEM_OAKS_PARCEL] =
    {
        .name = sOaksParcelName,
        .itemId = ITEM_OAKS_PARCEL,
        .price = 0,
        .description = sOaksParcelDesc,
        .importance = 2,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

    [ITEM_SECRET_KEY] =
    {
        .name = sSecretKeyName,
        .itemId = ITEM_SECRET_KEY,
        .price = 0,
        .description = sSecretKeyDesc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

    [ITEM_BIKE_VOUCHER] =
    {
        .name = sBikeVoucherName,
        .itemId = ITEM_BIKE_VOUCHER,
        .price = 0,
        .description = sBikeVoucherDesc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

    [ITEM_GOLD_TEETH] =
    {
        .name = sGoldTeethName,
        .quantum = sQuantum_Set,
        .itemId = ITEM_GOLD_TEETH,
        .price = 0,
        .description = sGoldTeethDesc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

    [ITEM_CARD_KEY] =
    {
        .name = sCardKeyName,
        .itemId = ITEM_CARD_KEY,
        .price = 0,
        .description = sCardKeyDesc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

    [ITEM_LIFT_KEY] =
    {
        .name = sLiftKeyName,
        .itemId = ITEM_LIFT_KEY,
        .price = 0,
        .description = sLiftKeyDesc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

    [ITEM_SILPH_SCOPE] =
    {
        .name = sSilphScopeName,
        .itemId = ITEM_SILPH_SCOPE,
        .price = 0,
        .description = sSilphScopeDesc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

    [ITEM_TRI_PASS] =
    {
        .name = sTriPassName,
        .itemId = ITEM_TRI_PASS,
        .price = 0,
        .description = sTriPassDesc,
        .importance = 1,
        .registrability = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

    [ITEM_RAINBOW_PASS] =
    {
        .name = sRainbowPassName,
        .itemId = ITEM_RAINBOW_PASS,
        .price = 0,
        .description = sRainbowPassDesc,
        .importance = 1,
        .registrability = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

    [ITEM_TEA] =
    {
        .name = sTeaName,
        .quantum = sQuantum_Cup,
        .itemId = ITEM_TEA,
        .price = 0,
        .description = sTeaDesc,
        .importance = 1,
        .registrability = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

    [ITEM_RUBY] =
    {
        .name = sRubyName,
        .itemId = ITEM_RUBY,
        .price = 0,
        .description = sRubyDesc,
        .importance = 1,
        .registrability = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

    [ITEM_SAPPHIRE] =
    {
        .name = sSapphireName,
        .itemId = ITEM_SAPPHIRE,
        .price = 0,
        .description = sSapphireDesc,
        .importance = 1,
        .registrability = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

// #pragma endregion

// #pragma region TTH HM Items


    [ITEM_META_ITEM_FINAL_BLUFF] =
    {
        .name = sMetaItemRockName,
        .itemId = ITEM_META_ITEM_FINAL_BLUFF,
        .price = 0,
        .description = sMetaItemRockDesc,
        .importance = 1,
        .keepItem = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = 2,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_META_ITEM_ZIGGY] =
    {
        .name = sMetaItemZigzagName,
        .itemId = ITEM_META_ITEM_ZIGGY,
        .price = 0,
        .description = sMetaItemZigzagDesc,
        .importance = 1,
        .keepItem = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = 2,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_META_ITEM_LOG_FLOAT] =
    {
        .name = sMetaItemLotadName,
        .itemId = ITEM_META_ITEM_LOG_FLOAT,
        .price = 0,
        .description = sMetaItemLotadDesc,
        .importance = 1,
        .keepItem = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = 2,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_META_ITEM_FOREST] =
    {
        .name = sMetaItemGrassName,
        .itemId = ITEM_META_ITEM_FOREST,
        .price = 0,
        .description = sMetaItemGrassDesc,
        .importance = 1,
        .keepItem = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = 2,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_META_ITEM_ICE_CORNER] =
    {
        .name = sMetaItemDiamondName,
        .itemId = ITEM_META_ITEM_ICE_CORNER,
        .price = 0,
        .description = sMetaItemDiamondDesc,
        .importance = 1,
        .keepItem = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = 2,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_META_ITEM_LEDGE] =
    {
        .name = sMetaItemSpinName,
        .itemId = ITEM_META_ITEM_LEDGE,
        .price = 0,
        .description = sMetaItemSpinDesc,
        .importance = 1,
        .keepItem = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = 2,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_META_ITEM_POKE_STAGE] =
    {
        .name = sMetaItemDollName,
        .itemId = ITEM_META_ITEM_POKE_STAGE,
        .price = 0,
        .description = sMetaItemDollDesc,
        .importance = 1,
        .keepItem = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = 2,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_META_ITEM_BIKE_PATH] =
    {
        .name = sMetaItemWheelName,
        .itemId = ITEM_META_ITEM_BIKE_PATH,
        .price = 0,
        .description = sMetaItemWheelDesc,
        .importance = 1,
        .keepItem = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = 2,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_META_ITEM_BERRY] =
    {
        .name = sMetaItemKissName,
        .itemId = ITEM_META_ITEM_BERRY,
        .price = 0,
        .description = sMetaItemKissDesc,
        .importance = 1,
        .keepItem = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = 2,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_META_ITEM_LAVARIDGE] =
    {
        .name = sMetaItemRoundName,
        .itemId = ITEM_META_ITEM_LAVARIDGE,
        .price = 0,
        .description = sMetaItemRoundDesc,
        .importance = 1,
        .keepItem = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = 2,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_META_ITEM_FIRE] =
    {
        .name = sMetaItemFireName,
        .itemId = ITEM_META_ITEM_FIRE,
        .price = 0,
        .description = sMetaItemFireDesc,
        .importance = 1,
        .keepItem = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = 2,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_META_ITEM_ZIP_SLIDE] =
    {
        .name = sMetaItemPikaName,
        .itemId = ITEM_META_ITEM_ZIP_SLIDE,
        .price = 0,
        .description = sMetaItemPikaDesc,
        .importance = 1,
        .keepItem = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = 2,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_META_ITEM_KOGA] =
    {
        .name = sMetaItemDuskullName,
        .itemId = ITEM_META_ITEM_KOGA,
        .price = 0,
        .description = sMetaItemDuskullDesc,
        .importance = 1,
        .keepItem = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = 2,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_META_ITEM_DIVE] =
    {
        .name = sMetaItemWaterName,
        .itemId = ITEM_META_ITEM_DIVE,
        .price = 0,
        .description = sMetaItemWaterDesc,
        .importance = 1,
        .keepItem = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = 2,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_META_ITEM_SEEDOT] =
    {
        .name = sMetaItemSeedotName,
        .itemId = ITEM_META_ITEM_SEEDOT,
        .price = 0,
        .description = sMetaItemSeedotDesc,
        .importance = 1,
        .keepItem = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = 2,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_META_ITEM_CUSHION] =
    {
        .name = sMetaItemCushionName,
        .itemId = ITEM_META_ITEM_CUSHION,
        .price = 0,
        .description = sMetaItemCushionDesc,
        .importance = 1,
        .keepItem = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = 2,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },
    
// #pragma endregion

// #pragma region TTH Meta Items

    [ITEM_CUT_ITEM] =
    {
        .name = sCutItemName,
        .itemId = ITEM_CUT_ITEM,
        .price = 0,
        .description = sCutItemDesc,
        .pocket = POCKET_KEY_ITEMS,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_FLASH_ITEM] =
    {
        .name = sFlashItemName,
        .itemId = ITEM_FLASH_ITEM,
        .price = 0,
        .description = sFlashItemDesc,
        .pocket = POCKET_KEY_ITEMS,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_ROCKSMASH_ITEM] =
    {
        .name = sRockSmashItemName,
        .itemId = ITEM_ROCKSMASH_ITEM,
        .price = 0,
        .description = sRockSmashItemDesc,
        .pocket = POCKET_KEY_ITEMS,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_STRENGTH_ITEM] =
    {
        .name = sStrengthItemName,
        .itemId = ITEM_STRENGTH_ITEM,
        .price = 0,
        .description = sStrengthItemDesc,
        .pocket = POCKET_KEY_ITEMS,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_SURF_ITEM] =
    {
        .name = sSurfItemName,
        .itemId = ITEM_SURF_ITEM,
        .price = 0,
        .description = sSurfItemDesc,
        .pocket = POCKET_KEY_ITEMS,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_FLY_ITEM] =
    {
        .name = sFlyItemName,
        .itemId = ITEM_FLY_ITEM,
        .price = 0,
        .description = sFlyItemDesc,
        .pocket = POCKET_KEY_ITEMS,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_DIVE_ITEM] =
    {
        .name = sDiveItemName,
        .itemId = ITEM_DIVE_ITEM,
        .price = 0,
        .description = sDiveItemDesc,
        .pocket = POCKET_KEY_ITEMS,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_WATERFALL_ITEM] =
    {
        .name = sWaterfallItemName,
        .itemId = ITEM_WATERFALL_ITEM,
        .price = 0,
        .description = sWaterfallItemDesc,
        .pocket = POCKET_KEY_ITEMS,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

// #pragma endregion

// #pragma region TTH Candy
    
    [ITEM_CANDY_CHOCOLATE] =
    {   // +20HP
        .name = sChocolateName,
        .quantum = sQuantum_Bar,
        .itemId = ITEM_CANDY_CHOCOLATE,
        .price = CANDY_COST(200),
        .itemEffect = gItemEffect_HealHP20,
        .holdEffect = HOLD_EFFECT_RESTORE_HP,
        .holdEffectParam = 20,
        .description = sChocolateDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_CHOCOWHITE] =
    {   // +50HP
        .name = sChocoWhiteName,
        .quantum = sQuantum_Bar,
        .itemId = ITEM_CANDY_CHOCOWHITE,
        .price = CANDY_COST(500),
        .itemEffect = gItemEffect_HealHP50,
        .holdEffect = HOLD_EFFECT_RESTORE_HP,
        .holdEffectParam = 50,
        .description = sChocoWhiteDesc,
        .keepItem = TRUE,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_CHOCOSLAB] = 
    {   // Held item: Intimidate
        .name = sChocoSlabName,
        .itemId = ITEM_CANDY_CHOCOSLAB,
        .price = CANDY_COST(2000),
        .holdEffect = HOLD_EFFECT_INTIMIDATE,
        .description = sChocoSlabDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_STARBURST] =
    {   // Heal Psn
        .name = sStarburstName,
        .itemId = ITEM_CANDY_STARBURST,
        .price = CANDY_COST(100),
        .itemEffect = gItemEffect_HealPoison,
        .holdEffect = HOLD_EFFECT_CURE_PSN,
        .description = sAntidoteDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_LEMONDROP] =
    {   // Heal Brn
        .name = sLemonDropName,
        .itemId = ITEM_CANDY_LEMONDROP,
        .price = CANDY_COST(250),
        .itemEffect = gItemEffect_HealBurn,
        .holdEffect = HOLD_EFFECT_CURE_BRN,
        .description = sBurnHealDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_WARHEAD] =
    {   // Heal Frz
        .name = sWarheadName,
        .itemId = ITEM_CANDY_WARHEAD,
        .price = CANDY_COST(200),
        .itemEffect = gItemEffect_HealFreeze,
        .holdEffect = HOLD_EFFECT_CURE_FRZ,
        .description = sIceHealDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_PRETZEL] =
    {   // Heal Slp
        .name = sPretzelName,
        .itemId = ITEM_CANDY_PRETZEL,
        .price = CANDY_COST(250),
        .itemEffect = gItemEffect_HealSleep,
        .holdEffect = HOLD_EFFECT_CURE_SLP,
        .description = sAwakeningDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_VEROMANGO] =
    {   // Heal Prz
        .name = sVeroMangoName,
        .itemId = ITEM_CANDY_VEROMANGO,
        .price = CANDY_COST(200),
        .itemEffect = gItemEffect_HealParalyze,
        .holdEffect = HOLD_EFFECT_CURE_PAR,
        .description = sParalyzeHealDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_VIOLETCRUMBLE] =
    {   // Heal Confusion
        .name = sVioletCrumbleName,
        .itemId = ITEM_CANDY_VIOLETCRUMBLE,
        .price = CANDY_COST(200),
        .itemEffect = gItemEffect_HealConfusion,
        .holdEffect = HOLD_EFFECT_CURE_CONFUSION,
        .description = sVioletCrumbleDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = 1,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_GALAXY] =
    {   // Heal Attract
        .name = sGalaxyName,
        .itemId = ITEM_CANDY_GALAXY,
        .price = CANDY_COST(200),
        .itemEffect = gItemEffect_HealInfatuation,
        .holdEffect = HOLD_EFFECT_CURE_ATTRACT,
        .description = sGalaxyDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = 1,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_TWIXLEFT] =
    {   // +30HP
        .name = sTwixLeftName,
        .quantum = sQuantum_Bar,
        .itemId = ITEM_CANDY_TWIXLEFT,
        .price = CANDY_COST(250),
        .itemEffect = gItemEffect_HealHP30,
        .holdEffect = HOLD_EFFECT_RESTORE_HP,
        .holdEffectParam = 30,
        .description = sTwixLeftDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_TWIXRIGHT] =
    {   // +4PP
        .name = sTwixRightName,
        .quantum = sQuantum_Bar,
        .itemId = ITEM_CANDY_TWIXRIGHT,
        .price = CANDY_COST(250),
        .holdEffect = HOLD_EFFECT_RESTORE_PP,
        .holdEffectParam = 4,
        .description = sTwixRightDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_PPRecovery,
        .battleUsage = 1,
        .itemEffect = gItemEffect_HealPP4,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_MMMINI] =
    {   // +20HP
        .name = sMMMinisName,
        .quantum = sQuantum_Tube,
        .itemId = ITEM_CANDY_MMMINI,
        .price = CANDY_COST(150),
        .itemEffect = gItemEffect_HealHP20,
        .holdEffect = HOLD_EFFECT_RESTORE_HP,
        .holdEffectParam = 20,
        .description = sMMMinisDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_MMPEANUT] =
    {   // +50HP
        .name = sMMPeanutName,
        .quantum = sQuantum_Packet,
        .itemId = ITEM_CANDY_MMPEANUT,
        .price = CANDY_COST(400),
        .itemEffect = gItemEffect_HealHP50,
        .holdEffect = HOLD_EFFECT_RESTORE_HP,
        .holdEffectParam = 50,
        .description = sMMPeanutDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_KINGCHOCNUT] =
    {   // +30HP
        .name = sKingChocName,
        .quantum = sQuantum_Box,
        .plural = ITEM_NAME_PLURAL_ES,
        .itemId = ITEM_CANDY_KINGCHOCNUT,
        .price = CANDY_COST(400),
        .itemEffect = gItemEffect_HealHP30,
        .holdEffect = HOLD_EFFECT_RESTORE_HP,
        .holdEffectParam = 30,
        .description = sKingChocDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_GUMMYBEAR] =
    {   // Raise single random stat when eaten in battle
        .name = sGummyBearName,
        .quantum = sQuantum_Packet,
        .itemId = ITEM_CANDY_GUMMYBEAR,
        .price = 1, //CANDY_COST(50),
        .holdEffect = HOLD_EFFECT_RANDOM_STAT_UP,
        .holdEffectParam = 1,
        .description = sGummyBearDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = 2,
        .itemEffect = gItemEffect_XRandom,
        .battleUseFunc = ItemUseInBattle_StatIncrease,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_REESES] =
    {   // Heals statuses
        .name = sReeseCupName,
        .itemId = ITEM_CANDY_REESES,
        .price = CANDY_COST(500),
        .holdEffect = HOLD_EFFECT_CURE_STATUS,
        .description = sReeseCupDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .itemEffect = gItemEffect_HealAllStatus,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_BUTTERFINGER] =
    {   // +60HP
        .name = sButterfingerName,
        .itemId = ITEM_CANDY_BUTTERFINGER,
        .price = CANDY_COST(600),
        .itemEffect = gItemEffect_HealHP60,
        .holdEffect = HOLD_EFFECT_RESTORE_HP,
        .holdEffectParam = 60,
        .description = sButterfingerDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_MILKYWAY] =
    {   // +80HP
        .name = sMilkyWayName,
        .itemId = ITEM_CANDY_MILKYWAY,
        .price = CANDY_COST(800),
        .itemEffect = gItemEffect_HealHP80,
        .holdEffect = HOLD_EFFECT_RESTORE_HP,
        .holdEffectParam = 80,
        .description = sMilkyWayDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_MILKALUFLEE] =
    {   // +100HP
        .name = sMilkaLufleeName,
        .quantum = sQuantum_Bar,
        .itemId = ITEM_CANDY_MILKALUFLEE,
        .price = CANDY_COST(1000),
        .itemEffect = gItemEffect_HealHP100,
        .holdEffect = HOLD_EFFECT_RESTORE_HP,
        .holdEffectParam = 100,
        .description = sMilkaLufleeDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_100GRAND] =
    {   // +100HP
        .name = s100GrandName,
        .itemId = ITEM_CANDY_100GRAND,
        .price = CANDY_COST(1000),
        .itemEffect = gItemEffect_HealHP100,
        .holdEffect = HOLD_EFFECT_RESTORE_HP,
        .holdEffectParam = 100,
        .description = s100GrandDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_MALTESERS] =
    {   // +10PP one move
        .name = sMalteserName,
        .itemId = ITEM_CANDY_MALTESERS,
        .price = CANDY_COST(1000),
        .holdEffect = HOLD_EFFECT_RESTORE_PP,
        .holdEffectParam = 10,
        .description = sMalteserDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_PPRecovery,
        .battleUsage = 1,
        .itemEffect = gItemEffect_HealPP10,
        .battleUseFunc = ItemUseInBattle_PPRecovery,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_CADBURYCREME] =
    {   // +All PP one move
        .name = sCadburyCremeName,
        .itemId = ITEM_CANDY_CADBURYCREME,
        .price = CANDY_COST(1200),
        .holdEffect = HOLD_EFFECT_RESTORE_PP,
        .holdEffectParam = 255,
        .description = sCadburyCremeDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_PPRecovery,
        .battleUsage = 1,
        .itemEffect = gItemEffect_MaxEther,
        .battleUseFunc = ItemUseInBattle_PPRecovery,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_WUNDERBAR] =
    {   // +All PP all moves. TODO: Hold Effect needs to be applied to all moves
        .name = sWunderbarName,
        .itemId = ITEM_CANDY_WUNDERBAR,
        .price = CANDY_COST(1400),
        .holdEffect = HOLD_EFFECT_RESTORE_ALLPP,
        .holdEffectParam = 255,
        .description = sWunderbarDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_PPRecovery,
        .battleUsage = 1,
        .itemEffect = gItemEffect_MaxElixir,
        .battleUseFunc = ItemUseInBattle_PPRecovery,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_OREO] =
    {   // Heals status
        .name = sOreoCookiesName,
        .quantum = sQuantum_Pack,
        .itemId = ITEM_CANDY_OREO,
        .price = CANDY_COST(500),
        .holdEffect = HOLD_EFFECT_CURE_STATUS,
        .description = sOreoCookiesDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .itemEffect = gItemEffect_HealAllStatus,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_COFFEECRISP] =
    {   // 60 HP + Cure Slp/Frz
        .name = sCoffeeCrispName,
        .itemId = ITEM_CANDY_COFFEECRISP,
        .price = CANDY_COST(1000),
        .holdEffect = HOLD_EFFECT_CURE_STATUS_HP,
        .holdEffectParam = 60,
        .description = sCoffeeCrispDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .itemEffect = gItemEffect_HealStatusAndHP,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_SAMBOPRISTUR] =
    {   // 60 HP + Cure Brn/Prz
        .name = sSamboPristurName,
        .itemId = ITEM_CANDY_SAMBOPRISTUR,
        .price = CANDY_COST(1000),
        .holdEffect = HOLD_EFFECT_CURE_STATUS_HP,
        .holdEffectParam = 60,
        .description = sSamboPristurDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .itemEffect = gItemEffect_HealStatusAndHP,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_SNICKERS] =
    {   // Poke Doll, Smokeball
        .name = sSnickersName,
        .plural = sSnickersName,
        .itemId = ITEM_CANDY_SNICKERS,
        .price = CANDY_COST(1000),
        .holdEffect = HOLD_EFFECT_CAN_ALWAYS_RUN,
        .description = sSnickersDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = 2,
        .battleUseFunc = ItemUseInBattle_Escape,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_MARSBAR] =
    {   // Full Restore
        .name = sMarsBarName,
        .itemId = ITEM_CANDY_MARSBAR,
        .price = CANDY_COST(2500),
        .holdEffect = HOLD_EFFECT_CURE_STATUS_HP,
        .holdEffectParam = 255,
        .description = sMarsBarDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .itemEffect = gItemEffect_FullRestore,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_KITKAT] =
    { // Revive
        .name = sKitKatBarName,
        .itemId = ITEM_CANDY_KITKAT,
        .price = CANDY_COST(2000),
        .description = sKitKatBarDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .itemEffect = gItemEffect_Revive,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_PIXIESTICK] =
    { // Bright Powder
        .name = sPixieStickName,
        .itemId = ITEM_CANDY_PIXIESTICK,
        .price = CANDY_COST(500),
        .holdEffect = HOLD_EFFECT_EVASION_UP,
        .holdEffectParam = 10,
        .description = sPixieStickDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_TURKISHDELIGHT] =
    { // Elixer
        .name = sTurkishDelightName,
        .itemId = ITEM_CANDY_TURKISHDELIGHT,
        .price = CANDY_COST(800),
        .holdEffect = HOLD_EFFECT_RESTORE_ALLPP, // TEST
        .holdEffectParam = 10,
        .description = sTurkishDelightDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_PPRecovery,
        .battleUsage = 1,
        .itemEffect = gItemEffect_Elixir,
        .battleUseFunc = ItemUseInBattle_PPRecovery,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_GOBSTOPPER] =
    { // Leftovers
        .name = sGobstopperName,
        .itemId = ITEM_CANDY_GOBSTOPPER,
        .price = CANDY_COST(200),
        .holdEffect = HOLD_EFFECT_LEFTOVERS,
        .holdEffectParam = 10,
        .description = sGobstopperDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_BLACKTHUNDER] =
    { // Full Restore
        .name = sBlackThunderName,
        .itemId = ITEM_CANDY_BLACKTHUNDER,
        .price = CANDY_COST(800),
        .holdEffect = HOLD_EFFECT_CURE_STATUS_HP,
        .holdEffectParam = 255,
        .description = sBlackThunderDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .itemEffect = gItemEffect_FullRestore,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_TOBLERONE] =
    {// + Critical Hit
        .name = sTobleroneName,
        .itemId = ITEM_CANDY_TOBLERONE,
        .price = CANDY_COST(200),
        .holdEffect = HOLD_EFFECT_CRITICAL_UP,
        .holdEffectParam = 4,
        .description = sTobleroneDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = 2,
        .itemEffect = gItemEffect_DireHit,
        .battleUseFunc = ItemUseInBattle_StatIncrease,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_FERREROROCHER] =
    {// Full Restore
        .name = sFerreroRocherName,
        .itemId = ITEM_CANDY_FERREROROCHER,
        .price = CANDY_COST(800),
        .holdEffect = HOLD_EFFECT_CURE_STATUS_HP,
        .holdEffectParam = 255,
        .description = sFerreroRocherDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .itemEffect = gItemEffect_FullRestore,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_EGGS] =
    {// TODO: Weapon
        .name = sEggName,
        .itemId = ITEM_CANDY_EGGS,
        .price = CANDY_COST(200),
        .description = sEggDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_EGGDEVILED] =
    {// TODO: Weapon
        .name = sEggDeviledName,
        .itemId = ITEM_CANDY_EGGDEVILED,
        .price = CANDY_COST(500),
        .description = sEggDeviledDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_CARROT] =
    { // +40HP, cure Prz
        .name = sCarrotName,
        .quantum = sQuantum_Bag,
        .itemId = ITEM_CANDY_CARROT,
        .price = CANDY_COST(400),
        .holdEffect = HOLD_EFFECT_CURE_PAR_HP,
        .holdEffectParam = 40,
        .description = sCarrotDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .itemEffect = gItemEffect_HealParalyzeAndHP,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_APPLE] =
    { // +40HP, cure Brn
        .name = sAppleName,
        .quantum = sQuantum_Bag,
        .itemId = ITEM_CANDY_APPLE,
        .price = CANDY_COST(400),
        .holdEffect = HOLD_EFFECT_CURE_BRN_HP,
        .holdEffectParam = 40,
        .description = sAppleDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .itemEffect = gItemEffect_HealBurnAndHP,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_PRUNE] =
    { // +40HP, cure Psn
        .name = sPruneName,
        .itemId = ITEM_CANDY_PRUNE,
        .price = CANDY_COST(400),
        .holdEffect = HOLD_EFFECT_CURE_PSN_HP,
        .holdEffectParam = 40,
        .description = sPruneDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .itemEffect = gItemEffect_HealPoisonAndHP,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_CELERY] =
    { // +40HP, cure Frz
        .name = sCeleryName,
        .quantum = sQuantum_Bag,
        .itemId = ITEM_CANDY_CELERY,
        .price = CANDY_COST(400),
        .holdEffect = HOLD_EFFECT_CURE_FRZ_HP,
        .holdEffectParam = 40,
        .description = sCeleryDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .itemEffect = gItemEffect_HealFreezeAndHP,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_SNAPPEAS] =
    { // +40HP, cure Slp
        .name =  sSnapPeasName,
        .quantum = sQuantum_Box,
        .plural = ITEM_NAME_PLURAL_ES,
        .itemId = ITEM_CANDY_SNAPPEAS,
        .price = CANDY_COST(400),
        .holdEffect = HOLD_EFFECT_CURE_SLP_HP,
        .holdEffectParam = 40,
        .description =  sSnapPeasDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .itemEffect = gItemEffect_HealSleepAndHP,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_RAISIN] =
    { // +6pp
        .name = sRaisinsName,
        .quantum = sQuantum_Box,
        .plural = ITEM_NAME_PLURAL_ES,
        .itemId = ITEM_CANDY_RAISIN,
        .price = CANDY_COST(400),
        .holdEffect = HOLD_EFFECT_RESTORE_PP,
        .holdEffectParam = 6,
        .description = sRaisinsDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_PPRecovery,
        .battleUsage = 1,
        .itemEffect = gItemEffect_HealPP6,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_KALE] =
    { // Revives
        .name = sKaleChipsName,
        .quantum = sQuantum_Bag,
        .itemId = ITEM_CANDY_KALE,
        .price = CANDY_COST(700),
        .description = sKaleChipsDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .itemEffect = gItemEffect_RevivalHerb,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_LOVEHEARTS] =
    { // Infatuates on Contact (Cute Charm)
        .name = sLoveHeartsName,
        .quantum = sQuantum_Packet,
        .itemId = ITEM_CANDY_LOVEHEARTS,
        .holdEffect = HOLD_EFFECT_INFATUATION,
        .price = CANDY_COST(1500),
        .description = sLoveHeartsDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },
    
// #pragma endregion
    
};

static const u16 gItemTable_CandyAbundant[] = {
    ITEM_CANDY_CHOCOLATE,
    ITEM_CANDY_STARBURST,
    ITEM_CANDY_LEMONDROP,
    ITEM_CANDY_WARHEAD,
    ITEM_CANDY_PRETZEL,
    ITEM_CANDY_VEROMANGO,
    ITEM_CANDY_VIOLETCRUMBLE,
    ITEM_CANDY_TWIXLEFT,
    ITEM_CANDY_TWIXRIGHT,
    ITEM_CANDY_MMMINI,
    ITEM_CANDY_KINGCHOCNUT,
    ITEM_CANDY_GUMMYBEAR,
    ITEM_SWEET_HEART,
};
static const u16 gItemTable_CandyCommon[] = {
    ITEM_CANDY_CHOCOWHITE,
    ITEM_CANDY_MMPEANUT,
    ITEM_CANDY_REESES,
    ITEM_CANDY_BUTTERFINGER,
    ITEM_CANDY_MILKYWAY,
    ITEM_CANDY_MILKALUFLEE,
    ITEM_CANDY_100GRAND,
    ITEM_CANDY_MALTESERS,
    ITEM_CANDY_CADBURYCREME,
    ITEM_CANDY_OREO,
    // ITEM_CANDY_EGGS,
};
static const u16 gItemTable_CandyUncommon[] = {
    ITEM_CANDY_WUNDERBAR,
    ITEM_CANDY_COFFEECRISP,
    ITEM_CANDY_SAMBOPRISTUR,
    ITEM_CANDY_SNICKERS,
    ITEM_CANDY_MARSBAR,
    ITEM_CANDY_KITKAT,
    ITEM_CANDY_GALAXY,
    ITEM_CANDY_PIXIESTICK,
    // ITEM_CANDY_EGGDEVILED,
};
static const u16 gItemTable_CandyRare[] = {
    ITEM_CANDY_CHOCOSLAB,
    ITEM_CANDY_TURKISHDELIGHT,
    ITEM_CANDY_GOBSTOPPER,
    ITEM_CANDY_BLACKTHUNDER,
    ITEM_CANDY_TOBLERONE,
    ITEM_CANDY_FERREROROCHER,
    ITEM_CANDY_LOVEHEARTS,
    ITEM_MAX_HONEY,
    ITEM_EXP_CANDY_M,
};
static const u16 gItemTable_CandyHealthy[] = {
    ITEM_CANDY_CARROT,
    ITEM_CANDY_APPLE,
    ITEM_CANDY_PRUNE,
    ITEM_CANDY_CELERY,
    ITEM_CANDY_SNAPPEAS,
    ITEM_CANDY_RAISIN,
    ITEM_CANDY_KALE,
};

#define MUL_1(x) x
#define MUL_2(x) x, x
#define MUL_3(x) x, x, x
#define MUL_4(x) x, x, x, x
#define MUL_6(x) x, x, x, x, x, x
#define MUL_8(x) x, x, x, x, x, x, x, x

static const u16 gItemTable_RandomA[] = {
    MUL_8(ITEM_TABLE_CANDY_ABUNDANT),
    MUL_4(ITEM_TABLE_CANDY_COMMON),
    MUL_3(ITEM_TABLE_CANDY_HEALTHY),
    MUL_2(ITEM_TABLE_CANDY_UNCOMMON),
    MUL_6(ITEM_ANTIDOTE),
    MUL_6(ITEM_PEWTER_CRUNCHIES),
    MUL_4(ITEM_RAGE_CANDY_BAR),
    MUL_4(ITEM_FRESH_WATER),
    MUL_4(ITEM_CHERI_BERRY),
    MUL_4(ITEM_ORAN_BERRY),
    MUL_2(ITEM_POTION),
    MUL_2(ITEM_SWEET_HEART),
    MUL_1(ITEM_HP_UP),
    MUL_1(ITEM_CANDY_CHOCOSLAB),
    MUL_1(ITEM_EXP_CANDY_XS),
    MUL_1(ITEM_X_ATTACK),
    MUL_1(ITEM_BRIGHT_POWDER),
    MUL_1(ITEM_SHELL_BELL),
    MUL_1(ITEM_FLOAT_STONE),
    MUL_2(ITEM_TABLE_TM),
    MUL_1(ITEM_TABLE_MEGA_STONE),
};
static const u16 gItemTable_RandomB[] = {
    MUL_8(ITEM_TABLE_CANDY_ABUNDANT),
    MUL_4(ITEM_TABLE_CANDY_COMMON),
    MUL_3(ITEM_TABLE_CANDY_HEALTHY),
    MUL_2(ITEM_TABLE_CANDY_UNCOMMON),
    MUL_6(ITEM_PARALYZE_HEAL),
    MUL_6(ITEM_RAGE_CANDY_BAR),
    MUL_4(ITEM_OLD_GATEAU),
    MUL_4(ITEM_SODA_POP),
    MUL_4(ITEM_CHESTO_BERRY),
    MUL_4(ITEM_PERSIM_BERRY),
    MUL_2(ITEM_ETHER),
    MUL_2(ITEM_REVIVE),
    MUL_1(ITEM_PROTEIN),
    MUL_1(ITEM_CANDY_TURKISHDELIGHT),
    MUL_1(ITEM_EXP_CANDY_XS),
    MUL_1(ITEM_X_DEFENSE),
    MUL_1(ITEM_QUICK_CLAW),
    MUL_1(ITEM_WISE_GLASSES),
    MUL_1(ITEM_ROCKY_HELMET),
    MUL_2(ITEM_TABLE_TM),
    MUL_1(ITEM_TABLE_POWER_GEM),
};
static const u16 gItemTable_RandomC[] = {
    MUL_8(ITEM_TABLE_CANDY_ABUNDANT),
    MUL_4(ITEM_TABLE_CANDY_COMMON),
    MUL_3(ITEM_TABLE_CANDY_HEALTHY),
    MUL_2(ITEM_TABLE_CANDY_UNCOMMON),
    MUL_6(ITEM_BURN_HEAL),
    MUL_6(ITEM_LAVA_COOKIE),
    MUL_4(ITEM_CASTELIACONE),
    MUL_4(ITEM_LEMONADE),
    MUL_4(ITEM_PECHA_BERRY),
    MUL_4(ITEM_LUM_BERRY),
    MUL_2(ITEM_ETHER),
    MUL_2(ITEM_BERRY_JUICE),
    MUL_1(ITEM_IRON),
    MUL_1(ITEM_CANDY_GOBSTOPPER),
    MUL_1(ITEM_EXP_CANDY_S),
    MUL_1(ITEM_X_SP_ATK),
    MUL_1(ITEM_SOOTHE_BELL),
    MUL_1(ITEM_EXPERT_BELT),
    MUL_1(ITEM_AIR_BALLOON),
    MUL_2(ITEM_TABLE_TM),
    MUL_1(ITEM_TABLE_Z_CRYSTAL),
};
static const u16 gItemTable_RandomD[] = {
    MUL_8(ITEM_TABLE_CANDY_ABUNDANT),
    MUL_4(ITEM_TABLE_CANDY_COMMON),
    MUL_3(ITEM_TABLE_CANDY_HEALTHY),
    MUL_2(ITEM_TABLE_CANDY_UNCOMMON),
    MUL_6(ITEM_ICE_HEAL),
    MUL_6(ITEM_OLD_GATEAU),
    MUL_4(ITEM_LUMIOSE_GALETTE),
    MUL_4(ITEM_FRESH_WATER),
    MUL_4(ITEM_RAWST_BERRY),
    MUL_4(ITEM_SITRUS_BERRY),
    MUL_2(ITEM_ELIXIR),
    MUL_2(ITEM_SWEET_HEART),
    MUL_1(ITEM_CALCIUM),
    MUL_1(ITEM_CANDY_BLACKTHUNDER),
    MUL_1(ITEM_EXP_CANDY_S),
    MUL_1(ITEM_X_SP_DEF),
    MUL_1(ITEM_MENTAL_HERB),
    MUL_1(ITEM_POWER_HERB),
    MUL_1(ITEM_ASSAULT_VEST),
    MUL_2(ITEM_TABLE_TM),
    MUL_1(ITEM_TABLE_MEGA_STONE),
};
static const u16 gItemTable_RandomE[] = {
    MUL_8(ITEM_TABLE_CANDY_ABUNDANT),
    MUL_4(ITEM_TABLE_CANDY_COMMON),
    MUL_3(ITEM_TABLE_CANDY_HEALTHY),
    MUL_2(ITEM_TABLE_CANDY_UNCOMMON),
    MUL_6(ITEM_AWAKENING),
    MUL_6(ITEM_PEWTER_CRUNCHIES),
    MUL_4(ITEM_SHALOUR_SABLE),
    MUL_4(ITEM_SODA_POP),
    MUL_4(ITEM_ASPEAR_BERRY),
    MUL_4(ITEM_FIGY_BERRY),
    MUL_2(ITEM_ETHER),
    MUL_2(ITEM_REVIVE),
    MUL_1(ITEM_ZINC),
    MUL_1(ITEM_CANDY_TOBLERONE),
    MUL_1(ITEM_EXP_CANDY_M),
    MUL_1(ITEM_X_SPEED),
    MUL_1(ITEM_AMULET_COIN),
    MUL_1(ITEM_FOCUS_SASH),
    MUL_1(ITEM_SAFETY_GOGGLES),
    MUL_2(ITEM_TABLE_TM),
    MUL_1(ITEM_TABLE_POWER_GEM),
};
static const u16 gItemTable_RandomF[] = {
    MUL_8(ITEM_TABLE_CANDY_ABUNDANT),
    MUL_4(ITEM_TABLE_CANDY_COMMON),
    MUL_3(ITEM_TABLE_CANDY_HEALTHY),
    MUL_2(ITEM_TABLE_CANDY_UNCOMMON),
    MUL_6(ITEM_FULL_HEAL),
    MUL_6(ITEM_LAVA_COOKIE),
    MUL_4(ITEM_BIG_MALASADA),
    MUL_4(ITEM_LEMONADE),
    MUL_4(ITEM_LEPPA_BERRY),
    MUL_4(ITEM_WIKI_BERRY),
    MUL_2(ITEM_ELIXIR),
    MUL_2(ITEM_REVIVE),
    MUL_1(ITEM_CARBOS),
    MUL_1(ITEM_CANDY_FERREROROCHER),
    MUL_1(ITEM_EXP_CANDY_S),
    MUL_1(ITEM_X_ACCURACY),
    MUL_1(ITEM_LEFTOVERS),
    MUL_1(ITEM_BIG_ROOT),
    MUL_1(ITEM_HEAVY_DUTY_BOOTS),
    MUL_2(ITEM_TABLE_TM),
    MUL_1(ITEM_TABLE_Z_CRYSTAL),
};

#undef CANDY_COST
#undef CANDY_COST2
#undef POCKET_POKE_BALLS