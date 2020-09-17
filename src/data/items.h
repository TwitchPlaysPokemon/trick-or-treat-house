#if USE_CANDY_CURRENCY
#define CANDY_COST(cost) (cost >> 6) 
#define CANDY_COST2(candy, normal) candy
#else
#define CANDY_COST(cost) cost
#define CANDY_COST2(candy, normal) normal
#endif

#define ItemUseOutOfBattle_CannotUseBall ItemUseOutOfBattle_CannotUse

const struct Item gItems[] =
{
    [ITEM_NONE] =
    {
        .name = sNoItemName,
        .itemId = ITEM_NONE,
        .price = 0,
        .description = sDummyDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

// Pokeballs

    [ITEM_MASTER_BALL] =
    {
        .name = sMasterBallName,
        .itemId = ITEM_MASTER_BALL,
        .price = 0,
        .description = sMasterBallDesc,
        .pocket = POCKET_GENERAL,
        .type = 0,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUseBall,
        .battleUsage = 2,
        .battleUseFunc = ItemUseInBattle_PokeBall,
        .secondaryId = 0,
    },

    [ITEM_ULTRA_BALL] =
    {
        .name = sUltraBallName,
        .itemId = ITEM_ULTRA_BALL,
        .price = CANDY_COST(1200),
        .description = sUltraBallDesc,
        .pocket = POCKET_GENERAL,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUseBall,
        .battleUsage = 2,
        .battleUseFunc = ItemUseInBattle_PokeBall,
        .secondaryId = 1,
    },

    [ITEM_GREAT_BALL] =
    {
        .name = sGreatBallName,
        .itemId = ITEM_GREAT_BALL,
        .price = CANDY_COST(600),
        .description = sGreatBallDesc,
        .pocket = POCKET_GENERAL,
        .type = 2,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUseBall,
        .battleUsage = 2,
        .battleUseFunc = ItemUseInBattle_PokeBall,
        .secondaryId = 2,
    },

    [ITEM_POKE_BALL] =
    {
        .name = sPokeBallName,
        .itemId = ITEM_POKE_BALL,
        .price = CANDY_COST(200),
        .description = sPokeBallDesc,
        .pocket = POCKET_GENERAL,
        .type = 3,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUseBall,
        .battleUsage = 2,
        .battleUseFunc = ItemUseInBattle_PokeBall,
        .secondaryId = 3,
    },

    [ITEM_SAFARI_BALL] =
    {
        .name = sSafariBallName,
        .itemId = ITEM_SAFARI_BALL,
        .price = 0,
        .description = sSafariBallDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUseBall,
        .battleUsage = 2,
        .battleUseFunc = ItemUseInBattle_PokeBall,
        .secondaryId = 4,
    },

    [ITEM_NET_BALL] =
    {
        .name = sNetBallName,
        .itemId = ITEM_NET_BALL,
        .price = CANDY_COST(1000),
        .description = sNetBallDesc,
        .pocket = POCKET_GENERAL,
        .type = 5,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUseBall,
        .battleUsage = 2,
        .battleUseFunc = ItemUseInBattle_PokeBall,
        .secondaryId = 5,
    },

    [ITEM_DIVE_BALL] =
    {
        .name = sDiveBallName,
        .itemId = ITEM_DIVE_BALL,
        .price = CANDY_COST(1000),
        .description = sDiveBallDesc,
        .pocket = POCKET_GENERAL,
        .type = 6,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUseBall,
        .battleUsage = 2,
        .battleUseFunc = ItemUseInBattle_PokeBall,
        .secondaryId = 6,
    },

    [ITEM_NEST_BALL] =
    {
        .name = sNestBallName,
        .itemId = ITEM_NEST_BALL,
        .price = CANDY_COST(1000),
        .description = sNestBallDesc,
        .pocket = POCKET_GENERAL,
        .type = 7,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUseBall,
        .battleUsage = 2,
        .battleUseFunc = ItemUseInBattle_PokeBall,
        .secondaryId = 7,
    },

    [ITEM_REPEAT_BALL] =
    {
        .name = sRepeatBallName,
        .itemId = ITEM_REPEAT_BALL,
        .price = CANDY_COST(1000),
        .description = sRepeatBallDesc,
        .pocket = POCKET_GENERAL,
        .type = 8,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUseBall,
        .battleUsage = 2,
        .battleUseFunc = ItemUseInBattle_PokeBall,
        .secondaryId = 8,
    },

    [ITEM_TIMER_BALL] =
    {
        .name = sTimerBallName,
        .itemId = ITEM_TIMER_BALL,
        .price = CANDY_COST(1000),
        .description = sTimerBallDesc,
        .pocket = POCKET_GENERAL,
        .type = 9,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUseBall,
        .battleUsage = 2,
        .battleUseFunc = ItemUseInBattle_PokeBall,
        .secondaryId = 9,
    },

    [ITEM_LUXURY_BALL] =
    {
        .name = sLuxuryBallName,
        .itemId = ITEM_LUXURY_BALL,
        .price = CANDY_COST(1000),
        .description = sLuxuryBallDesc,
        .pocket = POCKET_GENERAL,
        .type = 10,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUseBall,
        .battleUsage = 2,
        .battleUseFunc = ItemUseInBattle_PokeBall,
        .secondaryId = 10,
    },

    [ITEM_PREMIER_BALL] =
    {
        .name = sPremierBallName,
        .itemId = ITEM_PREMIER_BALL,
        .price = CANDY_COST(200),
        .description = sPremierBallDesc,
        .pocket = POCKET_GENERAL,
        .type = 11,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUseBall,
        .battleUsage = 2,
        .battleUseFunc = ItemUseInBattle_PokeBall,
        .secondaryId = 11,
    },

// Medicine

    [ITEM_POTION] =
    {
        .name = sPotionName,
        .itemId = ITEM_POTION,
        .price = CANDY_COST(300),
        .holdEffectParam = 20,
        .description = sPotionDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .itemEffect = gItemEffect_HealHP20,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },

    [ITEM_ANTIDOTE] =
    {
        .name = sAntidoteName,
        .itemId = ITEM_ANTIDOTE,
        .price = CANDY_COST(100),
        .description = sAntidoteDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .itemEffect = gItemEffect_HealPoison,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },

    [ITEM_BURN_HEAL] =
    {
        .name = sBurnHealName,
        .itemId = ITEM_BURN_HEAL,
        .price = CANDY_COST(250),
        .description = sBurnHealDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .itemEffect = gItemEffect_HealBurn,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },

    [ITEM_ICE_HEAL] =
    {
        .name = sIceHealName,
        .itemId = ITEM_ICE_HEAL,
        .price = CANDY_COST(250),
        .description = sIceHealDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .itemEffect = gItemEffect_HealFreeze,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },

    [ITEM_AWAKENING] =
    {
        .name = sAwakeningName,
        .itemId = ITEM_AWAKENING,
        .price = CANDY_COST(250),
        .description = sAwakeningDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .itemEffect = gItemEffect_HealSleep,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },

    [ITEM_PARALYZE_HEAL] =
    {
        .name = sParalyzeHealName,
        .itemId = ITEM_PARALYZE_HEAL,
        .price = CANDY_COST(200),
        .description = sParalyzeHealDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .itemEffect = gItemEffect_HealParalyze,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
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
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .itemEffect = gItemEffect_FullRestore,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
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
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .itemEffect = gItemEffect_HealHPAll,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },

    [ITEM_HYPER_POTION] =
    {
        .name = sHyperPotionName,
        .itemId = ITEM_HYPER_POTION,
        .price = CANDY_COST(1200),
        .holdEffectParam = 200,
        .description = sHyperPotionDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .itemEffect = gItemEffect_HealHP200,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },

    [ITEM_SUPER_POTION] =
    {
        .name = sSuperPotionName,
        .itemId = ITEM_SUPER_POTION,
        .price = CANDY_COST(700),
        .holdEffectParam = 50,
        .description = sSuperPotionDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .itemEffect = gItemEffect_HealHP50,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },

    [ITEM_FULL_HEAL] =
    {
        .name = sFullHealName, 
        .itemId = ITEM_FULL_HEAL,
        .price = CANDY_COST(600),
        .description = sFullHealDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .itemEffect = gItemEffect_HealAllStatus,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },

    [ITEM_REVIVE] =
    {
        .name = sReviveName,
        .itemId = ITEM_REVIVE,
        .price = CANDY_COST(1500),
        .description = sReviveDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .itemEffect = gItemEffect_Revive,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },

    [ITEM_MAX_REVIVE] =
    {
        .name = sMaxReviveName,
        .itemId = ITEM_MAX_REVIVE,
        .price = CANDY_COST(4000),
        .description = sMaxReviveDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .itemEffect = gItemEffect_MaxRevive,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },

    [ITEM_FRESH_WATER] =
    {
        .name = sFreshWaterName,
        .quantum = sQuantumStrBottle,
        .itemId = ITEM_FRESH_WATER,
        .price = CANDY_COST(200),
        .holdEffectParam = 50,
        .description = sFreshWaterDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .itemEffect = gItemEffect_HealHP50,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },

    [ITEM_SODA_POP] =
    {
        .name = sSodaPopName,
        .quantum = sSodaPopQuantum,
        .itemId = ITEM_SODA_POP,
        .price = CANDY_COST(300),
        .holdEffectParam = 60,
        .description = sSodaPopDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .itemEffect = gItemEffect_HealHP60,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },

    [ITEM_LEMONADE] =
    {
        .name = sLemonadeName,
        .quantum = sQuantumStrBottle,
        .itemId = ITEM_LEMONADE,
        .price = CANDY_COST(350),
        .holdEffectParam = 80,
        .description = sLemonadeDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .itemEffect = gItemEffect_HealHP80,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },

    [ITEM_MOOMOO_MILK] =
    {
        .name = sMoomooMilkName,
        .quantum = sQuantumStrBottle,
        .itemId = ITEM_MOOMOO_MILK,
        .price = CANDY_COST(500),
        .holdEffectParam = 100,
        .description = sMoomooMilkDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .itemEffect = gItemEffect_HealHP100,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },

    [ITEM_ENERGY_POWDER] =
    {
        .name = sEnergyPowderName,
        .quantum = sQuantumStrDose,
        .itemId = ITEM_ENERGY_POWDER,
        .price = CANDY_COST(500),
        .description = sEnergyPowderDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .itemEffect = gItemEffect_EnergyPowder,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },

    [ITEM_ENERGY_ROOT] =
    {
        .name = sEnergyRootName,
        .itemId = ITEM_ENERGY_ROOT,
        .price = CANDY_COST(800),
        .description = sEnergyRootDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .itemEffect = gItemEffect_EnergyRoot,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },

    [ITEM_HEAL_POWDER] =
    {
        .name = sHealPowderName,
        .itemId = ITEM_HEAL_POWDER,
        .price = CANDY_COST(450),
        .description = sHealPowderDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .itemEffect = gItemEffect_HealPowder,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },

    [ITEM_REVIVAL_HERB] =
    {
        .name = sRevivalHerbName,
        .itemId = ITEM_REVIVAL_HERB,
        .price = CANDY_COST(2800),
        .description = sRevivalHerbDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .itemEffect = gItemEffect_RevivalHerb,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
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
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_PPRecovery,
        .battleUsage = 1,
        .itemEffect = gItemEffect_HealPP10,
        .battleUseFunc = ItemUseInBattle_PPRecovery,
        .secondaryId = 0,
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
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_PPRecovery,
        .battleUsage = 1,
        .itemEffect = gItemEffect_MaxEther,
        .battleUseFunc = ItemUseInBattle_PPRecovery,
        .secondaryId = 0,
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
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_PPRecovery,
        .battleUsage = 1,
        .itemEffect = gItemEffect_Elixir,
        .battleUseFunc = ItemUseInBattle_PPRecovery,
        .secondaryId = 0,
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
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_PPRecovery,
        .battleUsage = 1,
        .itemEffect = gItemEffect_MaxElixir,
        .battleUseFunc = ItemUseInBattle_PPRecovery,
        .secondaryId = 0,
    },

    [ITEM_LAVA_COOKIE] =
    {
        .name = sLavaCookieName, 
        .itemId = ITEM_LAVA_COOKIE,
        .price = CANDY_COST(200),
        .description = sLavaCookieDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .itemEffect = gItemEffect_HealAllStatus,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },

    [ITEM_BLUE_FLUTE] =
    {
        .name = sBlueFluteName,
        .itemId = ITEM_BLUE_FLUTE,
        .price = CANDY_COST(100),
        .description = sBlueFluteDesc,
        .pocket = POCKET_GENERAL,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .itemEffect = gItemEffect_HealSleep,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },

    [ITEM_YELLOW_FLUTE] =
    {
        .name = sYellowFluteName,
        .itemId = ITEM_YELLOW_FLUTE,
        .price = CANDY_COST(200),
        .description = sYellowFluteDesc,
        .pocket = POCKET_GENERAL,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = 1,
        .itemEffect = gItemEffect_HealConfusion,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },

    [ITEM_RED_FLUTE] =
    {
        .name = sRedFluteName,
        .itemId = ITEM_RED_FLUTE,
        .price = CANDY_COST(300),
        .description = sRedFluteDesc,
        .pocket = POCKET_GENERAL,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = 1,
        .itemEffect = gItemEffect_HealInfatuation,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },

    [ITEM_BLACK_FLUTE] =
    {
        .name = sBlackFluteName,
        .itemId = ITEM_BLACK_FLUTE,
        .price = CANDY_COST(400),
        .holdEffectParam = 50,
        .description = sBlackFluteDesc,
        .pocket = POCKET_GENERAL,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_BlackWhiteFlute,
        .secondaryId = 0,
    },

    [ITEM_WHITE_FLUTE] =
    {
        .name = sWhiteFluteName,
        .itemId = ITEM_WHITE_FLUTE,
        .price = CANDY_COST(500),
        .holdEffectParam = 150,
        .description = sWhiteFluteDesc,
        .pocket = POCKET_GENERAL,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_BlackWhiteFlute,
        .secondaryId = 0,
    },

    [ITEM_BERRY_JUICE] =
    {
        .name = sBerryJuiceName,
        .quantum = sBerryJuiceQuantum,
        .itemId = ITEM_BERRY_JUICE,
        .price = CANDY_COST(100),
        .itemEffect = gItemEffect_HealHP20,
        .holdEffect = HOLD_EFFECT_RESTORE_HP,
        .holdEffectParam = 20,
        .description = sBerryJuiceDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },

    [ITEM_SACRED_ASH] =
    {
        .name = sSacredAshName,
        .quantum = sQuantumStrBag,
        .itemId = ITEM_SACRED_ASH,
        .price = CANDY_COST(200),
        .description = sSacredAshDesc,
        .pocket = POCKET_GENERAL,
        .type = 1,
        .itemEffect = gItemEffect_SacredAsh,
        .fieldUseFunc = ItemUseOutOfBattle_SacredAsh,
        .secondaryId = 0,
    },

// Collectibles

    [ITEM_SHOAL_SALT] =
    {
        .name = sShoalSaltName,
        .quantum = sQuantumStrDose,
        .itemId = ITEM_SHOAL_SALT,
        .price = CANDY_COST(20),
        .description = sShoalSaltDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_SHOAL_SHELL] =
    {
        .name = sShoalShellName,
        .itemId = ITEM_SHOAL_SHELL,
        .price = CANDY_COST(20),
        .description = sShoalShellDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_RED_SHARD] =
    {
        .name = sRedShardName,
        .itemId = ITEM_RED_SHARD,
        .price = CANDY_COST(200),
        .description = sRedShardDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_BLUE_SHARD] =
    {
        .name = sBlueShardName,
        .itemId = ITEM_BLUE_SHARD,
        .price = CANDY_COST(200),
        .description = sBlueShardDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_YELLOW_SHARD] =
    {
        .name = sYellowShardName,
        .itemId = ITEM_YELLOW_SHARD,
        .price = CANDY_COST(200),
        .description = sYellowShardDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_GREEN_SHARD] =
    {
        .name = sGreenShardName,
        .itemId = ITEM_GREEN_SHARD,
        .price = CANDY_COST(200),
        .description = sGreenShardDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_034] =
    {
        .name = sDummyName,
        .itemId = ITEM_NONE,
        .price = 0,
        .description = sDummyDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_035] =
    {
        .name = sDummyName,
        .itemId = ITEM_NONE,
        .price = 0,
        .description = sDummyDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_036] =
    {
        .name = sDummyName,
        .itemId = ITEM_NONE,
        .price = 0,
        .description = sDummyDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_037] =
    {
        .name = sDummyName,
        .itemId = ITEM_NONE,
        .price = 0,
        .description = sDummyDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_038] =
    {
        .name = sDummyName,
        .itemId = ITEM_NONE,
        .price = 0,
        .description = sDummyDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_039] =
    {
        .name = sDummyName,
        .itemId = ITEM_NONE,
        .price = 0,
        .description = sDummyDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_03A] =
    {
        .name = sDummyName,
        .itemId = ITEM_NONE,
        .price = 0,
        .description = sDummyDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_03B] =
    {
        .name = sDummyName,
        .itemId = ITEM_NONE,
        .price = 0,
        .description = sDummyDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_03C] =
    {
        .name = sDummyName,
        .itemId = ITEM_NONE,
        .price = 0,
        .description = sDummyDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_03D] =
    {
        .name = sDummyName,
        .itemId = ITEM_NONE,
        .price = 0,
        .description = sDummyDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_03E] =
    {
        .name = sDummyName,
        .itemId = ITEM_NONE,
        .price = 0,
        .description = sDummyDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

// Vitamins

    [ITEM_HP_UP] =
    {
        .name = sHPUpName,
        .quantum = sQuantumStrDose,
        .itemId = ITEM_HP_UP,
        .price = CANDY_COST(9800),
        .description = sHPUpDesc,
        .pocket = POCKET_GENERAL,
        .type = 1,
        .itemEffect = gItemEffect_HPUp,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .secondaryId = 0,
    },

    [ITEM_PROTEIN] =
    {
        .name = sProteinName,
        .quantum = sQuantumStrDose,
        .itemId = ITEM_PROTEIN,
        .price = CANDY_COST(9800),
        .description = sProteinDesc,
        .pocket = POCKET_GENERAL,
        .type = 1,
        .itemEffect = gItemEffect_Protein,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .secondaryId = 0,
    },

    [ITEM_IRON] =
    {
        .name = sIronName,
        .quantum = sQuantumStrDose,
        .itemId = ITEM_IRON,
        .price = CANDY_COST(9800),
        .description = sIronDesc,
        .pocket = POCKET_GENERAL,
        .type = 1,
        .itemEffect = gItemEffect_Iron,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .secondaryId = 0,
    },

    [ITEM_CARBOS] =
    {
        .name = sCarbosName,
        .quantum = sQuantumStrDose,
        .itemId = ITEM_CARBOS,
        .price = CANDY_COST(9800),
        .description = sCarbosDesc,
        .pocket = POCKET_GENERAL,
        .type = 1,
        .itemEffect = gItemEffect_Carbos,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .secondaryId = 0,
    },

    [ITEM_CALCIUM] =
    {
        .name = sCalciumName,
        .quantum = sQuantumStrDose,
        .itemId = ITEM_CALCIUM,
        .price = CANDY_COST(9800),
        .description = sCalciumDesc,
        .pocket = POCKET_GENERAL,
        .type = 1,
        .itemEffect = gItemEffect_Calcium,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .secondaryId = 0,
    },

    [ITEM_RARE_CANDY] =
    {
        .name = sRareCandyName,
        .plural = sRareCandyPluralName,
        .itemId = ITEM_RARE_CANDY,
        .price = CANDY_COST(4800),
        .description = sRareCandyDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = 1,
        .itemEffect = gItemEffect_RareCandy,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse, //ItemUseOutOfBattle_RareCandy,
        .secondaryId = 0,
    },

    [ITEM_PP_UP] =
    {
        .name = sPPUpName,
        .quantum = sQuantumStrDose,
        .itemId = ITEM_PP_UP,
        .price = CANDY_COST(9800),
        .description = sPPUpDesc,
        .pocket = POCKET_GENERAL,
        .type = 1,
        .itemEffect = gItemEffect_PPUp,
        .fieldUseFunc = ItemUseOutOfBattle_PPUp,
        .secondaryId = 0,
    },

    [ITEM_ZINC] =
    {
        .name = sZincName,
        .quantum = sQuantumStrDose,
        .itemId = ITEM_ZINC,
        .price = CANDY_COST(9800),
        .description = sZincDesc,
        .pocket = POCKET_GENERAL,
        .type = 1,
        .itemEffect = gItemEffect_Zinc,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .secondaryId = 0,
    },

    [ITEM_PP_MAX] =
    {
        .name = sPPMaxName,
        .quantum = sQuantumStrDose,
        .itemId = ITEM_PP_MAX,
        .price = CANDY_COST(9800),
        .description = sPPMaxDesc,
        .pocket = POCKET_GENERAL,
        .type = 1,
        .itemEffect = gItemEffect_PPMax,
        .fieldUseFunc = ItemUseOutOfBattle_PPUp,
        .secondaryId = 0,
    },

    [ITEM_048] =
    {
        .name = sDummyName,
        .itemId = ITEM_NONE,
        .price = 0,
        .description = sDummyDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

// Battle items

    [ITEM_GUARD_SPEC] =
    {
        .name = sGuardSpecName,
        .itemId = ITEM_GUARD_SPEC,
        .price = CANDY_COST(700),
        .description = sGuardSpecDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = 2,
        .itemEffect = gItemEffect_GuardSpec,
        .battleUseFunc = ItemUseInBattle_StatIncrease,
        .secondaryId = 0,
    },

    [ITEM_DIRE_HIT] =
    {
        .name = sDireHitName,
        .itemId = ITEM_DIRE_HIT,
        .price = CANDY_COST(650),
        .description = sDireHitDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = 2,
        .itemEffect = gItemEffect_DireHit,
        .battleUseFunc = ItemUseInBattle_StatIncrease,
        .secondaryId = 0,
    },

    [ITEM_X_ATTACK] =
    {
        .name = sXAttackName,
        .itemId = ITEM_X_ATTACK,
        .price = CANDY_COST(500),
        .description = sXAttackDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = 2,
        .itemEffect = gItemEffect_XAttack,
        .battleUseFunc = ItemUseInBattle_StatIncrease,
        .secondaryId = 0,
    },

    [ITEM_X_DEFEND] =
    {
        .name = sXDefendName,
        .itemId = ITEM_X_DEFEND,
        .price = CANDY_COST(550),
        .description = sXDefendDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = 2,
        .itemEffect = gItemEffect_XDefend,
        .battleUseFunc = ItemUseInBattle_StatIncrease,
        .secondaryId = 0,
    },

    [ITEM_X_SPEED] =
    {
        .name = sXSpeedName,
        .itemId = ITEM_X_SPEED,
        .price = CANDY_COST(350),
        .description = sXSpeedDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = 2,
        .itemEffect = gItemEffect_XSpeed,
        .battleUseFunc = ItemUseInBattle_StatIncrease,
        .secondaryId = 0,
    },

    [ITEM_X_ACCURACY] =
    {
        .name = sXAccuracyName,
        .plural = sXAccuracyPluralName,
        .itemId = ITEM_X_ACCURACY,
        .price = CANDY_COST(950),
        .description = sXAccuracyDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = 2,
        .itemEffect = gItemEffect_XAccuracy,
        .battleUseFunc = ItemUseInBattle_StatIncrease,
        .secondaryId = 0,
    },

    [ITEM_X_SPECIAL] =
    {
        .name = sXSpecialName,
        .itemId = ITEM_X_SPECIAL,
        .price = CANDY_COST(350),
        .description = sXSpecialDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = 2,
        .itemEffect = gItemEffect_XSpecial,
        .battleUseFunc = ItemUseInBattle_StatIncrease,
        .secondaryId = 0,
    },

    [ITEM_POKE_DOLL] =
    {
        .name = sPokeDollName,
        .itemId = ITEM_POKE_DOLL,
        .price = CANDY_COST(1000),
        .description = sPokeDollDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = 2,
        .battleUseFunc = ItemUseInBattle_Escape,
        .secondaryId = 0,
    },

    [ITEM_FLUFFY_TAIL] =
    {
        .name = sFluffyTailName,
        .itemId = ITEM_FLUFFY_TAIL,
        .price = CANDY_COST(1000),
        .description = sFluffyTailDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = 2,
        .battleUseFunc = ItemUseInBattle_Escape,
        .secondaryId = 0,
    },

    [ITEM_052] =
    {
        .name = sDummyName,
        .itemId = ITEM_NONE,
        .price = 0,
        .description = sDummyDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

// Field items

    [ITEM_SUPER_REPEL] =
    {
        .name = sSuperRepelName,
        .itemId = ITEM_SUPER_REPEL,
        .price = CANDY_COST(500),
        .holdEffectParam = 200,
        .description = sSuperRepelDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_Repel,
        .secondaryId = 0,
    },

    [ITEM_MAX_REPEL] =
    {
        .name = sMaxRepelName,
        .itemId = ITEM_MAX_REPEL,
        .price = CANDY_COST(700),
        .holdEffectParam = 250,
        .description = sMaxRepelDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_Repel,
        .secondaryId = 0,
    },

    [ITEM_ESCAPE_ROPE] =
    {
        .name = sEscapeRopeName,
        .itemId = ITEM_ESCAPE_ROPE,
        .price = 0, //CANDY_COST(550),
        .description = sEscapeRopeDesc,
        .importance = 1,
        .keepItem = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = 2,
        .fieldUseFunc = ItemUseOutOfBattle_EscapeRope,
        .secondaryId = 0,
    },

    [ITEM_REPEL] =
    {
        .name = sRepelName,
        .itemId = ITEM_REPEL,
        .price = CANDY_COST(350),
        .holdEffectParam = 100,
        .description = sRepelDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_Repel,
        .secondaryId = 0,
    },

    [ITEM_CANDY_ABUNDANT] =
    {
        .name = sDummyName,
        .itemId = ITEM_NONE,
        .price = 0,
        .description = sDummyDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_CANDY_COMMON] =
    {
        .name = sDummyName,
        .itemId = ITEM_NONE,
        .price = 0,
        .description = sDummyDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_CANDY_UNCOMMON] =
    {
        .name = sDummyName,
        .itemId = ITEM_NONE,
        .price = 0,
        .description = sDummyDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_CANDY_RARE] =
    {
        .name = sDummyName,
        .itemId = ITEM_NONE,
        .price = 0,
        .description = sDummyDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_CANDY_HEALTHY] =
    {
        .name = sDummyName,
        .itemId = ITEM_NONE,
        .price = 0,
        .description = sDummyDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_05C] =
    {
        .name = sDummyName,
        .itemId = ITEM_NONE,
        .price = 0,
        .description = sDummyDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

// Evolution stones

    [ITEM_SUN_STONE] =
    {
        .name = sSunStoneName,
        .itemId = ITEM_SUN_STONE,
        .price = CANDY_COST(2100),
        .description = sSunStoneDesc,
        .pocket = POCKET_GENERAL,
        .type = 1,
        .itemEffect = gItemEffect_EvoStone,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .secondaryId = 0,
    },

    [ITEM_MOON_STONE] =
    {
        .name = sMoonStoneName,
        .itemId = ITEM_MOON_STONE,
        .price = 0,
        .description = sMoonStoneDesc,
        .pocket = POCKET_GENERAL,
        .type = 1,
        .itemEffect = gItemEffect_EvoStone,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .secondaryId = 0,
    },

    [ITEM_FIRE_STONE] =
    {
        .name = sFireStoneName,
        .itemId = ITEM_FIRE_STONE,
        .price = CANDY_COST(2100),
        .description = sFireStoneDesc,
        .pocket = POCKET_GENERAL,
        .type = 1,
        .itemEffect = gItemEffect_EvoStone,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .secondaryId = 0,
    },

    [ITEM_THUNDER_STONE] =
    {
        .name = sThunderStoneName,
        .itemId = ITEM_THUNDER_STONE,
        .price = CANDY_COST(2100),
        .description = sThunderStoneDesc,
        .pocket = POCKET_GENERAL,
        .type = 1,
        .itemEffect = gItemEffect_EvoStone,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .secondaryId = 0,
    },

    [ITEM_WATER_STONE] =
    {
        .name = sWaterStoneName,
        .itemId = ITEM_WATER_STONE,
        .price = CANDY_COST(2100),
        .description = sWaterStoneDesc,
        .pocket = POCKET_GENERAL,
        .type = 1,
        .itemEffect = gItemEffect_EvoStone,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .secondaryId = 0,
    },

    [ITEM_LEAF_STONE] =
    {
        .name = sLeafStoneName,
        .itemId = ITEM_LEAF_STONE,
        .price = CANDY_COST(2100),
        .description = sLeafStoneDesc,
        .pocket = POCKET_GENERAL,
        .type = 1,
        .itemEffect = gItemEffect_EvoStone,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .secondaryId = 0,
    },

    [ITEM_063] =
    {
        .name = sDummyName,
        .itemId = ITEM_NONE,
        .price = 0,
        .description = sDummyDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_064] =
    {
        .name = sDummyName,
        .itemId = ITEM_NONE,
        .price = 0,
        .description = sDummyDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_065] =
    {
        .name = sDummyName,
        .itemId = ITEM_NONE,
        .price = 0,
        .description = sDummyDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_066] =
    {
        .name = sDummyName,
        .itemId = ITEM_NONE,
        .price = 0,
        .description = sDummyDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

// Valuable items

    [ITEM_TINY_MUSHROOM] =
    {
        .name = sTinyMushroomName, 
        .itemId = ITEM_TINY_MUSHROOM,
        .price = CANDY_COST(500),
        .description = sTinyMushroomDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_BIG_MUSHROOM] =
    {
        .name = sBigMushroomName, 
        .itemId = ITEM_BIG_MUSHROOM,
        .price = CANDY_COST(5000),
        .description = sBigMushroomDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_069] =
    {
        .name = sDummyName,
        .itemId = ITEM_NONE,
        .price = 0,
        .description = sDummyDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_PEARL] =
    {
        .name = sPearlName, 
        .itemId = ITEM_PEARL,
        .price = CANDY_COST(1400),
        .description = sPearlDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_BIG_PEARL] =
    {
        .name = sBigPearlName, 
        .itemId = ITEM_BIG_PEARL,
        .price = CANDY_COST(7500),
        .description = sBigPearlDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_STARDUST] =
    {
        .name = sStardustName, 
        .itemId = ITEM_STARDUST,
        .price = CANDY_COST(2000),
        .description = sStardustDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_STAR_PIECE] =
    {
        .name = sStarPieceName, 
        .itemId = ITEM_STAR_PIECE,
        .price = CANDY_COST(9800),
        .description = sStarPieceDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_NUGGET] =
    {
        .name = sNuggetName, 
        .itemId = ITEM_NUGGET,
        .price = CANDY_COST(10000),
        .description = sNuggetDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_HEART_SCALE] =
    {
        .name = sHeartScaleName, 
        .itemId = ITEM_HEART_SCALE,
        .price = CANDY_COST(100),
        .description = sHeartScaleDesc,
        .keepItem = TRUE,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_070] =
    {
        .name = sDummyName,
        .itemId = ITEM_NONE,
        .price = 0,
        .description = sDummyDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_071] =
    {
        .name = sDummyName,
        .itemId = ITEM_NONE,
        .price = 0,
        .description = sDummyDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_072] =
    {
        .name = sDummyName,
        .itemId = ITEM_NONE,
        .price = 0,
        .description = sDummyDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_073] =
    {
        .name = sDummyName,
        .itemId = ITEM_NONE,
        .price = 0,
        .description = sDummyDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_074] =
    {
        .name = sDummyName,
        .itemId = ITEM_NONE,
        .price = 0,
        .description = sDummyDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_075] =
    {
        .name = sDummyName,
        .itemId = ITEM_NONE,
        .price = 0,
        .description = sDummyDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_076] =
    {
        .name = sDummyName,
        .itemId = ITEM_NONE,
        .price = 0,
        .description = sDummyDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_077] =
    {
        .name = sDummyName,
        .itemId = ITEM_NONE,
        .price = 0,
        .description = sDummyDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_078] =
    {
        .name = sDummyName,
        .itemId = ITEM_NONE,
        .price = 0,
        .description = sDummyDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

// Mail
    [ITEM_ORANGE_MAIL] =
    {
        .name = sOrangeMailName,
        .itemId = ITEM_ORANGE_MAIL,
        .price = CANDY_COST(50),
        .description = sOrangeMailDesc,
        .pocket = POCKET_GENERAL,
        .type = 0,
        .fieldUseFunc = ItemUseOutOfBattle_Mail,
        .secondaryId = 0,
    },

    [ITEM_HARBOR_MAIL] =
    {
        .name = sHarborMailName,
        .itemId = ITEM_HARBOR_MAIL,
        .price = CANDY_COST(50),
        .description = sHarborMailDesc,
        .pocket = POCKET_GENERAL,
        .type = 0,
        .fieldUseFunc = ItemUseOutOfBattle_Mail,
        .secondaryId = 1,
    },

    [ITEM_GLITTER_MAIL] =
    {
        .name = sGlitterMailName,
        .itemId = ITEM_GLITTER_MAIL,
        .price = CANDY_COST(50),
        .description = sGlitterMailDesc,
        .pocket = POCKET_GENERAL,
        .type = 0,
        .fieldUseFunc = ItemUseOutOfBattle_Mail,
        .secondaryId = 2,
    },

    [ITEM_MECH_MAIL] =
    {
        .name = sMechMailName,
        .itemId = ITEM_MECH_MAIL,
        .price = CANDY_COST(50),
        .description = sMechMailDesc,
        .pocket = POCKET_GENERAL,
        .type = 0,
        .fieldUseFunc = ItemUseOutOfBattle_Mail,
        .secondaryId = 3,
    },

    [ITEM_WOOD_MAIL] =
    {
        .name = sWoodMailName,
        .itemId = ITEM_WOOD_MAIL,
        .price = CANDY_COST(50),
        .description = sWoodMailDesc,
        .pocket = POCKET_GENERAL,
        .type = 0,
        .fieldUseFunc = ItemUseOutOfBattle_Mail,
        .secondaryId = 4,
    },

    [ITEM_WAVE_MAIL] =
    {
        .name = sWaveMailName,
        .itemId = ITEM_WAVE_MAIL,
        .price = CANDY_COST(50),
        .description = sWaveMailDesc,
        .pocket = POCKET_GENERAL,
        .type = 0,
        .fieldUseFunc = ItemUseOutOfBattle_Mail,
        .secondaryId = 5,
    },

    [ITEM_BEAD_MAIL] =
    {
        .name = sBeadMailName,
        .itemId = ITEM_BEAD_MAIL,
        .price = CANDY_COST(50),
        .description = sBeadMailDesc,
        .pocket = POCKET_GENERAL,
        .type = 0,
        .fieldUseFunc = ItemUseOutOfBattle_Mail,
        .secondaryId = 6,
    },

    [ITEM_SHADOW_MAIL] =
    {
        .name = sShadowMailName,
        .itemId = ITEM_SHADOW_MAIL,
        .price = CANDY_COST(50),
        .description = sShadowMailDesc,
        .pocket = POCKET_GENERAL,
        .type = 0,
        .fieldUseFunc = ItemUseOutOfBattle_Mail,
        .secondaryId = 7,
    },

    [ITEM_TROPIC_MAIL] =
    {
        .name = sTropicMailName,
        .itemId = ITEM_TROPIC_MAIL,
        .price = CANDY_COST(50),
        .description = sTropicMailDesc,
        .pocket = POCKET_GENERAL,
        .type = 0,
        .fieldUseFunc = ItemUseOutOfBattle_Mail,
        .secondaryId = 8,
    },

    [ITEM_DREAM_MAIL] =
    {
        .name = sDreamMailName,
        .itemId = ITEM_DREAM_MAIL,
        .price = CANDY_COST(50),
        .description = sDreamMailDesc,
        .pocket = POCKET_GENERAL,
        .type = 0,
        .fieldUseFunc = ItemUseOutOfBattle_Mail,
        .secondaryId = 9,
    },

    [ITEM_FAB_MAIL] =
    {
        .name = sFabMailName,
        .itemId = ITEM_FAB_MAIL,
        .price = CANDY_COST(50),
        .description = sFabMailDesc,
        .pocket = POCKET_GENERAL,
        .type = 0,
        .fieldUseFunc = ItemUseOutOfBattle_Mail,
        .secondaryId = 10,
    },

    [ITEM_RETRO_MAIL] =
    {
        .name = sRetroMailName,
        .itemId = ITEM_RETRO_MAIL,
        .price = 0,
        .description = sRetroMailDesc,
        .pocket = POCKET_GENERAL,
        .type = 0,
        .fieldUseFunc = ItemUseOutOfBattle_Mail,
        .secondaryId = 11,
    },

// Berries

    [ITEM_CHERI_BERRY] =
    {
        .name = sCheriBerryName,
        .itemId = ITEM_CHERI_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_CURE_PAR,
        .description = sCheriBerryDesc,
        .pocket = POCKET_BERRIES,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .itemEffect = gItemEffect_HealParalyze,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },

    [ITEM_CHESTO_BERRY] =
    {
        .name = sChestoBerryName,
        .itemId = ITEM_CHESTO_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_CURE_SLP,
        .description = sChestoBerryDesc,
        .pocket = POCKET_BERRIES,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .itemEffect = gItemEffect_HealSleep,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },

    [ITEM_PECHA_BERRY] =
    {
        .name = sPechaBerryName,
        .itemId = ITEM_PECHA_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_CURE_PSN,
        .description = sPechaBerryDesc,
        .pocket = POCKET_BERRIES,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .itemEffect = gItemEffect_HealPoison,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },

    [ITEM_RAWST_BERRY] =
    {
        .name = sRawstBerryName,
        .itemId = ITEM_RAWST_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_CURE_BRN,
        .description = sRawstBerryDesc,
        .pocket = POCKET_BERRIES,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .itemEffect = gItemEffect_HealBurn,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },

    [ITEM_ASPEAR_BERRY] =
    {
        .name = sAspearBerryName,
        .itemId = ITEM_ASPEAR_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_CURE_FRZ,
        .description = sAspearBerryDesc,
        .pocket = POCKET_BERRIES,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .itemEffect = gItemEffect_HealFreeze,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },

    [ITEM_LEPPA_BERRY] =
    {
        .name = sLeppaBerryName,
        .itemId = ITEM_LEPPA_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_RESTORE_PP,
        .holdEffectParam = 10,
        .description = sLeppaBerryDesc,
        .pocket = POCKET_BERRIES,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_PPRecovery,
        .battleUsage = 1,
        .itemEffect = gItemEffect_HealPP10,
        .battleUseFunc = ItemUseInBattle_PPRecovery,
        .secondaryId = 0,
    },

    [ITEM_ORAN_BERRY] =
    {
        .name = sOranBerryName,
        .itemId = ITEM_ORAN_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_RESTORE_HP,
        .holdEffectParam = 10,
        .description = sOranBerryDesc,
        .pocket = POCKET_BERRIES,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .itemEffect = gItemEffect_HealHP10,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },

    [ITEM_PERSIM_BERRY] =
    {
        .name = sPersimBerryName,
        .itemId = ITEM_PERSIM_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_CURE_CONFUSION,
        .description = sPersimBerryDesc,
        .pocket = POCKET_BERRIES,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = 1,
        .itemEffect = gItemEffect_HealConfusion,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },

    [ITEM_LUM_BERRY] =
    {
        .name = sLumBerryName,
        .itemId = ITEM_LUM_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_CURE_STATUS,
        .description = sLumBerryDesc,
        .pocket = POCKET_BERRIES,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .itemEffect = gItemEffect_HealAllStatus,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },

    [ITEM_SITRUS_BERRY] =
    {
        .name = sSitrusBerryName,
        .itemId = ITEM_SITRUS_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_RESTORE_HP,
        .holdEffectParam = 30,
        .description = sSitrusBerryDesc,
        .pocket = POCKET_BERRIES,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .itemEffect = gItemEffect_HealHP30,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },

    [ITEM_FIGY_BERRY] =
    {
        .name = sFigyBerryName,
        .itemId = ITEM_FIGY_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_CONFUSE_SPICY,
        .holdEffectParam = 8,
        .description = sFigyBerryDesc,
        .pocket = POCKET_BERRIES,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_WIKI_BERRY] =
    {
        .name = sWikiBerryName,
        .itemId = ITEM_WIKI_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_CONFUSE_DRY,
        .holdEffectParam = 8,
        .description = sWikiBerryDesc,
        .pocket = POCKET_BERRIES,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_MAGO_BERRY] =
    {
        .name = sMagoBerryName,
        .itemId = ITEM_MAGO_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_CONFUSE_SWEET,
        .holdEffectParam = 8,
        .description = sMagoBerryDesc,
        .pocket = POCKET_BERRIES,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_AGUAV_BERRY] =
    {
        .name = sAguavBerryName,
        .itemId = ITEM_AGUAV_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_CONFUSE_BITTER,
        .holdEffectParam = 8,
        .description = sAguavBerryDesc,
        .pocket = POCKET_BERRIES,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_IAPAPA_BERRY] =
    {
        .name = sIapapaBerryName,
        .itemId = ITEM_IAPAPA_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_CONFUSE_SOUR,
        .holdEffectParam = 8,
        .description = sIapapaBerryDesc,
        .pocket = POCKET_BERRIES,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_RAZZ_BERRY] =
    {
        .name = sRazzBerryName,
        .itemId = ITEM_RAZZ_BERRY,
        .price = CANDY_COST(20),
        .description = sRazzBerryDesc,
        .pocket = POCKET_BERRIES,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_BLUK_BERRY] =
    {
        .name = sBlukBerryName,
        .itemId = ITEM_BLUK_BERRY,
        .price = CANDY_COST(20),
        .description = sBlukBerryDesc,
        .pocket = POCKET_BERRIES,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_NANAB_BERRY] =
    {
        .name = sNanabBerryName,
        .itemId = ITEM_NANAB_BERRY,
        .price = CANDY_COST(20),
        .description = sNanabBerryDesc,
        .pocket = POCKET_BERRIES,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_WEPEAR_BERRY] =
    {
        .name = sWepearBerryName,
        .itemId = ITEM_WEPEAR_BERRY,
        .price = CANDY_COST(20),
        .description = sWepearBerryDesc,
        .pocket = POCKET_BERRIES,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_PINAP_BERRY] =
    {
        .name = sPinapBerryName,
        .itemId = ITEM_PINAP_BERRY,
        .price = CANDY_COST(20),
        .description = sPinapBerryDesc,
        .pocket = POCKET_BERRIES,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_POMEG_BERRY] =
    {
        .name = sPomegBerryName,
        .itemId = ITEM_POMEG_BERRY,
        .price = CANDY_COST(20),
        .description = sPomegBerryDesc,
        .pocket = POCKET_BERRIES,
        .type = 1,
        .itemEffect = gItemEffect_PomegBerry,
        .fieldUseFunc = ItemUseOutOfBattle_ReduceEV,
        .secondaryId = 0,
    },

    [ITEM_KELPSY_BERRY] =
    {
        .name = sKelpsyBerryName,
        .itemId = ITEM_KELPSY_BERRY,
        .price = CANDY_COST(20),
        .description = sKelpsyBerryDesc,
        .pocket = POCKET_BERRIES,
        .type = 1,
        .itemEffect = gItemEffect_KelpsyBerry,
        .fieldUseFunc = ItemUseOutOfBattle_ReduceEV,
        .secondaryId = 0,
    },

    [ITEM_QUALOT_BERRY] =
    {
        .name = sQualotBerryName,
        .itemId = ITEM_QUALOT_BERRY,
        .price = CANDY_COST(20),
        .description = sQualotBerryDesc,
        .pocket = POCKET_BERRIES,
        .type = 1,
        .itemEffect = gItemEffect_QualotBerry,
        .fieldUseFunc = ItemUseOutOfBattle_ReduceEV,
        .secondaryId = 0,
    },

    [ITEM_HONDEW_BERRY] =
    {
        .name = sHondewBerryName,
        .itemId = ITEM_HONDEW_BERRY,
        .price = CANDY_COST(20),
        .description = sHondewBerryDesc,
        .pocket = POCKET_BERRIES,
        .type = 1,
        .itemEffect = gItemEffect_HondrewBerry,
        .fieldUseFunc = ItemUseOutOfBattle_ReduceEV,
        .secondaryId = 0,
    },

    [ITEM_GREPA_BERRY] =
    {
        .name = sGrepaBerryName,
        .itemId = ITEM_GREPA_BERRY,
        .price = CANDY_COST(20),
        .description = sGrepaBerryDesc,
        .pocket = POCKET_BERRIES,
        .type = 1,
        .itemEffect = gItemEffect_GrepaBerry,
        .fieldUseFunc = ItemUseOutOfBattle_ReduceEV,
        .secondaryId = 0,
    },

    [ITEM_TAMATO_BERRY] =
    {
        .name = sTamatoBerryName,
        .itemId = ITEM_TAMATO_BERRY,
        .price = CANDY_COST(20),
        .description = sTamatoBerryDesc,
        .pocket = POCKET_BERRIES,
        .type = 1,
        .itemEffect = gItemEffect_TamatoBerry,
        .fieldUseFunc = ItemUseOutOfBattle_ReduceEV,
        .secondaryId = 0,
    },

    [ITEM_CORNN_BERRY] =
    {
        .name = sCornnBerryName,
        .itemId = ITEM_CORNN_BERRY,
        .price = CANDY_COST(20),
        .description = sCornnBerryDesc,
        .pocket = POCKET_BERRIES,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_MAGOST_BERRY] =
    {
        .name = sMagostBerryName,
        .itemId = ITEM_MAGOST_BERRY,
        .price = CANDY_COST(20),
        .description = sMagostBerryDesc,
        .pocket = POCKET_BERRIES,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_RABUTA_BERRY] =
    {
        .name = sRabutaBerryName,
        .itemId = ITEM_RABUTA_BERRY,
        .price = CANDY_COST(20),
        .description = sRabutaBerryDesc,
        .pocket = POCKET_BERRIES,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_NOMEL_BERRY] =
    {
        .name = sNomelBerryName,
        .itemId = ITEM_NOMEL_BERRY,
        .price = CANDY_COST(20),
        .description = sNomelBerryDesc,
        .pocket = POCKET_BERRIES,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_SPELON_BERRY] =
    {
        .name = sSpelonBerryName,
        .itemId = ITEM_SPELON_BERRY,
        .price = CANDY_COST(20),
        .description = sSpelonBerryDesc,
        .pocket = POCKET_BERRIES,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_PAMTRE_BERRY] =
    {
        .name = sPamtreBerryName,
        .itemId = ITEM_PAMTRE_BERRY,
        .price = CANDY_COST(20),
        .description = sPamtreBerryDesc,
        .pocket = POCKET_BERRIES,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_WATMEL_BERRY] =
    {
        .name = sWatmelBerryName,
        .itemId = ITEM_WATMEL_BERRY,
        .price = CANDY_COST(20),
        .description = sWatmelBerryDesc,
        .pocket = POCKET_BERRIES,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_DURIN_BERRY] =
    {
        .name = sDurinBerryName,
        .itemId = ITEM_DURIN_BERRY,
        .price = CANDY_COST(20),
        .description = sDurinBerryDesc,
        .pocket = POCKET_BERRIES,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_BELUE_BERRY] =
    {
        .name = sBelueBerryName,
        .itemId = ITEM_BELUE_BERRY,
        .price = CANDY_COST(20),
        .description = sBelueBerryDesc,
        .pocket = POCKET_BERRIES,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_LIECHI_BERRY] =
    {
        .name = sLiechiBerryName,
        .itemId = ITEM_LIECHI_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_ATTACK_UP,
        .holdEffectParam = 4,
        .description = sLiechiBerryDesc,
        .pocket = POCKET_BERRIES,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_GANLON_BERRY] =
    {
        .name = sGanlonBerryName,
        .itemId = ITEM_GANLON_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_DEFENSE_UP,
        .holdEffectParam = 4,
        .description = sGanlonBerryDesc,
        .pocket = POCKET_BERRIES,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_SALAC_BERRY] =
    {
        .name = sSalacBerryName,
        .itemId = ITEM_SALAC_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_SPEED_UP,
        .holdEffectParam = 4,
        .description = sSalacBerryDesc,
        .pocket = POCKET_BERRIES,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_PETAYA_BERRY] =
    {
        .name = sPetayaBerryName,
        .itemId = ITEM_PETAYA_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_SP_ATTACK_UP,
        .holdEffectParam = 4,
        .description = sPetayaBerryDesc,
        .pocket = POCKET_BERRIES,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_APICOT_BERRY] =
    {
        .name = sApicotBerryName,
        .itemId = ITEM_APICOT_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_SP_DEFENSE_UP,
        .holdEffectParam = 4,
        .description = sApicotBerryDesc,
        .pocket = POCKET_BERRIES,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_LANSAT_BERRY] =
    {
        .name = sLansatBerryName,
        .itemId = ITEM_LANSAT_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_CRITICAL_UP,
        .holdEffectParam = 4,
        .description = sLansatBerryDesc,
        .pocket = POCKET_BERRIES,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_STARF_BERRY] =
    {
        .name = sStarfBerryName,
        .itemId = ITEM_STARF_BERRY,
        .price = CANDY_COST(20),
        .holdEffect = HOLD_EFFECT_RANDOM_STAT_UP,
        .holdEffectParam = 4,
        .description = sStarfBerryDesc,
        .pocket = POCKET_BERRIES,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_ENIGMA_BERRY] =
    {
        .name = sEnigmaBerryName,
        .itemId = ITEM_ENIGMA_BERRY,
        .price = CANDY_COST(20),
        .description = sEnigmaBerryDesc,
        .pocket = POCKET_BERRIES,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_EnigmaBerry,
        .battleUsage = 1,
        // .itemEffect = gItemEffect_ParalyzeHeal,
        .battleUseFunc = ItemUseInBattle_EnigmaBerry,
        .secondaryId = 0,
    },

    [ITEM_0B0] =
    {
        .name = sDummyName,
        .itemId = ITEM_NONE,
        .price = 0,
        .description = sDummyDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_0B1] =
    {
        .name = sDummyName,
        .itemId = ITEM_NONE,
        .price = 0,
        .description = sDummyDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_0B2] =
    {
        .name = sDummyName,
        .itemId = ITEM_NONE,
        .price = 0,
        .description = sDummyDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

// Hold items

    [ITEM_BRIGHT_POWDER] =
    {
        .name = sBrightPowderName,
        .quantum = sQuantumStrBag,
        .itemId = ITEM_BRIGHT_POWDER,
        .price = CANDY_COST(10),
        .holdEffect = HOLD_EFFECT_EVASION_UP,
        .holdEffectParam = 10,
        .description = sBrightPowderDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_WHITE_HERB] =
    {
        .name = sWhiteHerbName,
        .itemId = ITEM_WHITE_HERB,
        .price = CANDY_COST(100),
        .holdEffect = HOLD_EFFECT_RESTORE_STATS,
        .description = sWhiteHerbDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_MACHO_BRACE] =
    {
        .name = sMachoBraceName,
        .itemId = ITEM_MACHO_BRACE,
        .price = CANDY_COST(3000),
        .holdEffect = HOLD_EFFECT_MACHO_BRACE,
        .description = sMachoBraceDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_EXP_SHARE] =
    {
        .name = sExpShareName,
        .itemId = ITEM_EXP_SHARE,
        .price = CANDY_COST(3000),
        .holdEffect = HOLD_EFFECT_EXP_SHARE,
        .description = sExpShareDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_QUICK_CLAW] =
    {
        .name = sQuickClawName,
        .itemId = ITEM_QUICK_CLAW,
        .price = CANDY_COST(100),
        .holdEffect = HOLD_EFFECT_QUICK_CLAW,
        .holdEffectParam = 20,
        .description = sQuickClawDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_SOOTHE_BELL] =
    {
        .name = sSootheBellName,
        .itemId = ITEM_SOOTHE_BELL,
        .price = CANDY_COST(100),
        .holdEffect = HOLD_EFFECT_HAPPINESS_UP,
        .description = sSootheBellDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_MENTAL_HERB] =
    {
        .name = sMentalHerbName,
        .itemId = ITEM_MENTAL_HERB,
        .price = CANDY_COST(100),
        .holdEffect = HOLD_EFFECT_CURE_ATTRACT,
        .description = sMentalHerbDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_CHOICE_BAND] =
    {
        .name = sChoiceBandName,
        .itemId = ITEM_CHOICE_BAND,
        .price = CANDY_COST(100),
        .holdEffect = HOLD_EFFECT_CHOICE_BAND,
        .description = sChoiceBandDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_KINGS_ROCK] =
    {
        .name = sKingsRockName,
        .itemId = ITEM_KINGS_ROCK,
        .price = CANDY_COST(100),
        .holdEffect = HOLD_EFFECT_FLINCH,
        .holdEffectParam = 10,
        .description = sKingsRockDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_SILVER_POWDER] =
    {
        .name = sSilverPowderName,
        .quantum = sQuantumStrBag,
        .itemId = ITEM_SILVER_POWDER,
        .price = CANDY_COST(100),
        .holdEffect = HOLD_EFFECT_BUG_POWER,
        .holdEffectParam = 10,
        .description = sSilverPowderDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_AMULET_COIN] =
    {
        .name = sAmuletCoinName,
        .itemId = ITEM_AMULET_COIN,
        .price = CANDY_COST(100),
        .holdEffect = HOLD_EFFECT_DOUBLE_PRIZE,
        .holdEffectParam = 10,
        .description = sAmuletCoinDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_CLEANSE_TAG] =
    {
        .name = sCleanseTagName,
        .itemId = ITEM_CLEANSE_TAG,
        .price = CANDY_COST(200),
        .holdEffect = HOLD_EFFECT_REPEL,
        .description = sCleanseTagDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_SOUL_DEW] =
    {
        .name = sSoulDewName,
        .itemId = ITEM_SOUL_DEW,
        .price = CANDY_COST(200),
        .holdEffect = HOLD_EFFECT_SOUL_DEW,
        .description = sSoulDewDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_DEEP_SEA_TOOTH] =
    {
        .name = sDeepSeaToothName,
        .itemId = ITEM_DEEP_SEA_TOOTH,
        .price = CANDY_COST(200),
        .holdEffect = HOLD_EFFECT_DEEP_SEA_TOOTH,
        .description = sDeepSeaToothDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_DEEP_SEA_SCALE] =
    {
        .name = sDeepSeaScaleName,
        .itemId = ITEM_DEEP_SEA_SCALE,
        .price = CANDY_COST(200),
        .holdEffect = HOLD_EFFECT_DEEP_SEA_SCALE,
        .description = sDeepSeaScaleDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_SMOKE_BALL] =
    {
        .name = sSmokeBallName,
        .itemId = ITEM_SMOKE_BALL,
        .price = CANDY_COST(200),
        .holdEffect = HOLD_EFFECT_CAN_ALWAYS_RUN,
        .description = sSmokeBallDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_EVERSTONE] =
    {
        .name = sEverstoneName,
        .itemId = ITEM_EVERSTONE,
        .price = CANDY_COST(200),
        .holdEffect = HOLD_EFFECT_PREVENT_EVOLVE,
        .description = sEverstoneDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_FOCUS_BAND] =
    {
        .name = sFocusBandName,
        .itemId = ITEM_FOCUS_BAND,
        .price = CANDY_COST(200),
        .holdEffect = HOLD_EFFECT_FOCUS_BAND,
        .holdEffectParam = 10,
        .description = sFocusBandDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_LUCKY_EGG] =
    {
        .name = sLuckyEggName,
        .itemId = ITEM_LUCKY_EGG,
        .price = CANDY_COST(200),
        .holdEffect = HOLD_EFFECT_LUCKY_EGG,
        .description = sLuckyEggDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_SCOPE_LENS] =
    {
        .name = sScopeLensName,
        .plural = sScopeLensPluralName,
        .itemId = ITEM_SCOPE_LENS,
        .price = CANDY_COST(200),
        .holdEffect = HOLD_EFFECT_SCOPE_LENS,
        .description = sScopeLensDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_METAL_COAT] =
    {
        .name = sMetalCoatName,
        .itemId = ITEM_METAL_COAT,
        .price = CANDY_COST(100),
        .holdEffect = HOLD_EFFECT_STEEL_POWER,
        .holdEffectParam = 10,
        .description = sMetalCoatDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_LEFTOVERS] =
    {
        .name = sLeftoversName,
        .quantum = sLeftoversQuantum,
        .itemId = ITEM_LEFTOVERS,
        .price = CANDY_COST(200),
        .holdEffect = HOLD_EFFECT_LEFTOVERS,
        .holdEffectParam = 10,
        .description = sLeftoversDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_DRAGON_SCALE] =
    {
        .name = sDragonScaleName,
        .itemId = ITEM_DRAGON_SCALE,
        .price = CANDY_COST(2100),
        .holdEffect = HOLD_EFFECT_DRAGON_SCALE,
        .holdEffectParam = 10,
        .description = sDragonScaleDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_LIGHT_BALL] =
    {
        .name = sLightBallName,
        .itemId = ITEM_LIGHT_BALL,
        .price = CANDY_COST(100),
        .holdEffect = HOLD_EFFECT_LIGHT_BALL,
        .description = sLightBallDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_SOFT_SAND] =
    {
        .name = sSoftSandName,
        .quantum = sQuantumStrBag,
        .itemId = ITEM_SOFT_SAND,
        .price = CANDY_COST(100),
        .holdEffect = HOLD_EFFECT_GROUND_POWER,
        .holdEffectParam = 10,
        .description = sSoftSandDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_HARD_STONE] =
    {
        .name = sHardStoneName,
        .itemId = ITEM_HARD_STONE,
        .price = CANDY_COST(100),
        .holdEffect = HOLD_EFFECT_ROCK_POWER,
        .holdEffectParam = 10,
        .description = sHardStoneDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_MIRACLE_SEED] =
    {
        .name = sMiracleSeedName,
        .itemId = ITEM_MIRACLE_SEED,
        .price = CANDY_COST(100),
        .holdEffect = HOLD_EFFECT_GRASS_POWER,
        .holdEffectParam = 10,
        .description = sMiracleSeedDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_BLACK_GLASSES] =
    {
        .name = sBlackGlassesName,
        .plural = sBlackGlassesName,
        .itemId = ITEM_BLACK_GLASSES,
        .price = CANDY_COST(100),
        .holdEffect = HOLD_EFFECT_DARK_POWER,
        .holdEffectParam = 10,
        .description = sBlackGlassesDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_BLACK_BELT] =
    {
        .name = sBlackBeltName,
        .itemId = ITEM_BLACK_BELT,
        .price = CANDY_COST(100),
        .holdEffect = HOLD_EFFECT_FIGHTING_POWER,
        .holdEffectParam = 10,
        .description = sBlackBeltDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_MAGNET] =
    {
        .name = sMagnetName,
        .itemId = ITEM_MAGNET,
        .price = CANDY_COST(100),
        .holdEffect = HOLD_EFFECT_ELECTRIC_POWER,
        .holdEffectParam = 10,
        .description = sMagnetDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_MYSTIC_WATER] =
    {
        .name = sMysticWaterName,
        .quantum = sMysticWaterQuantum,
        .itemId = ITEM_MYSTIC_WATER,
        .price = CANDY_COST(100),
        .holdEffect = HOLD_EFFECT_WATER_POWER,
        .holdEffectParam = 10,
        .description = sMysticWaterDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_SHARP_BEAK] =
    {
        .name = sSharpBeakName,
        .itemId = ITEM_SHARP_BEAK,
        .price = CANDY_COST(100),
        .holdEffect = HOLD_EFFECT_FLYING_POWER,
        .holdEffectParam = 10,
        .description = sSharpBeakDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_POISON_BARB] =
    {
        .name = sPoisonBarbName,
        .itemId = ITEM_POISON_BARB,
        .price = CANDY_COST(100),
        .holdEffect = HOLD_EFFECT_POISON_POWER,
        .holdEffectParam = 10,
        .description = sPoisonBarbDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_NEVER_MELT_ICE] =
    {
        .name = sNeverMeltIceName,
        .itemId = ITEM_NEVER_MELT_ICE,
        .price = CANDY_COST(100),
        .holdEffect = HOLD_EFFECT_ICE_POWER,
        .holdEffectParam = 10,
        .description = sNeverMeltIceDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_SPELL_TAG] =
    {
        .name = sSpellTagName,
        .itemId = ITEM_SPELL_TAG,
        .price = CANDY_COST(100),
        .holdEffect = HOLD_EFFECT_GHOST_POWER,
        .holdEffectParam = 10,
        .description = sSpellTagDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_TWISTED_SPOON] =
    {
        .name = sTwistedSpoonName,
        .itemId = ITEM_TWISTED_SPOON,
        .price = CANDY_COST(100),
        .holdEffect = HOLD_EFFECT_PSYCHIC_POWER,
        .holdEffectParam = 10,
        .description = sTwistedSpoonDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_CHARCOAL] =
    {
        .name = sCharcoalName,
        .itemId = ITEM_CHARCOAL,
        .price = CANDY_COST(9800),
        .holdEffect = HOLD_EFFECT_FIRE_POWER,
        .holdEffectParam = 10,
        .description = sCharcoalDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_DRAGON_FANG] =
    {
        .name = sDragonFangName,
        .itemId = ITEM_DRAGON_FANG,
        .price = CANDY_COST(100),
        .holdEffect = HOLD_EFFECT_DRAGON_POWER,
        .holdEffectParam = 10,
        .description = sDragonFangDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_SILK_SCARF] =
    {
        .name = sSilkScarfName,
        .itemId = ITEM_SILK_SCARF,
        .price = CANDY_COST(100),
        .holdEffect = HOLD_EFFECT_NORMAL_POWER,
        .holdEffectParam = 10,
        .description = sSilkScarfDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_UP_GRADE] =
    {
        .name = sUpGradeName,
        .itemId = ITEM_UP_GRADE,
        .price = CANDY_COST(2100),
        .holdEffect = HOLD_EFFECT_UP_GRADE,
        .description = sUpGradeDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_SHELL_BELL] =
    {
        .name = sShellBellName,
        .itemId = ITEM_SHELL_BELL,
        .price = CANDY_COST(200),
        .holdEffect = HOLD_EFFECT_SHELL_BELL,
        .holdEffectParam = 8,
        .description = sShellBellDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_SEA_INCENSE] =
    {
        .name = sSeaIncenseName,
        .itemId = ITEM_SEA_INCENSE,
        .price = CANDY_COST(9600),
        .holdEffect = HOLD_EFFECT_WATER_POWER,
        .holdEffectParam = 5,
        .description = sSeaIncenseDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_LAX_INCENSE] =
    {
        .name = sLaxIncenseName,
        .itemId = ITEM_LAX_INCENSE,
        .price = CANDY_COST(9600),
        .holdEffect = HOLD_EFFECT_EVASION_UP,
        .holdEffectParam = 5,
        .description = sLaxIncenseDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_LUCKY_PUNCH] =
    {
        .name = sLuckyPunchName,
        .plural = sLuckyPunchPluralName,
        .itemId = ITEM_LUCKY_PUNCH,
        .price = CANDY_COST(10),
        .holdEffect = HOLD_EFFECT_LUCKY_PUNCH,
        .description = sLuckyPunchDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_METAL_POWDER] =
    {
        .name = sMetalPowderName,
        .itemId = ITEM_METAL_POWDER,
        .price = CANDY_COST(10),
        .holdEffect = HOLD_EFFECT_METAL_POWDER,
        .description = sMetalPowderDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_THICK_CLUB] =
    {
        .name = sThickClubName,
        .itemId = ITEM_THICK_CLUB,
        .price = CANDY_COST(500),
        .holdEffect = HOLD_EFFECT_THICK_CLUB,
        .description = sThickClubDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_STICK] =
    {
        .name = sStickName,
        .itemId = ITEM_STICK,
        .price = CANDY_COST(200),
        .holdEffect = HOLD_EFFECT_STICK,
        .description = sStickDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_0E2] =
    {
        .name = sDummyName,
        .itemId = ITEM_NONE,
        .price = 0,
        .description = sDummyDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_0E3] =
    {
        .name = sDummyName,
        .itemId = ITEM_NONE,
        .price = 0,
        .description = sDummyDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_0E4] =
    {
        .name = sDummyName,
        .itemId = ITEM_NONE,
        .price = 0,
        .description = sDummyDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_0E5] =
    {
        .name = sDummyName,
        .itemId = ITEM_NONE,
        .price = 0,
        .description = sDummyDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_META_ITEM_ROCK] =
    {
        .name = sMetaItemRockName,
        .itemId = ITEM_META_ITEM_ROCK,
        .price = 0,
        .description = sMetaItemRockDesc,
        .importance = 1,
        .keepItem = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = 2,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_META_ITEM_ZIGZAG] =
    {
        .name = sMetaItemZigzagName,
        .itemId = ITEM_META_ITEM_ZIGZAG,
        .price = 0,
        .description = sMetaItemZigzagDesc,
        .importance = 1,
        .keepItem = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = 2,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_META_ITEM_LOTAD] =
    {
        .name = sMetaItemLotadName,
        .itemId = ITEM_META_ITEM_LOTAD,
        .price = 0,
        .description = sMetaItemLotadDesc,
        .importance = 1,
        .keepItem = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = 2,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_META_ITEM_GRASS] =
    {
        .name = sMetaItemGrassName,
        .itemId = ITEM_META_ITEM_GRASS,
        .price = 0,
        .description = sMetaItemGrassDesc,
        .importance = 1,
        .keepItem = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = 2,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_META_ITEM_DIAMOND] =
    {
        .name = sMetaItemDiamondName,
        .itemId = ITEM_META_ITEM_DIAMOND,
        .price = 0,
        .description = sMetaItemDiamondDesc,
        .importance = 1,
        .keepItem = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = 2,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_META_ITEM_SPIN] =
    {
        .name = sMetaItemSpinName,
        .itemId = ITEM_META_ITEM_SPIN,
        .price = 0,
        .description = sMetaItemSpinDesc,
        .importance = 1,
        .keepItem = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = 2,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_META_ITEM_DOLL] =
    {
        .name = sMetaItemDollName,
        .itemId = ITEM_META_ITEM_DOLL,
        .price = 0,
        .description = sMetaItemDollDesc,
        .importance = 1,
        .keepItem = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = 2,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_META_ITEM_BALL] =
    {
        .name = sMetaItemBallName,
        .itemId = ITEM_META_ITEM_BALL,
        .price = 0,
        .description = sMetaItemBallDesc,
        .importance = 1,
        .keepItem = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = 2,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_META_ITEM_KISS] =
    {
        .name = sMetaItemKissName,
        .itemId = ITEM_META_ITEM_KISS,
        .price = 0,
        .description = sMetaItemKissDesc,
        .importance = 1,
        .keepItem = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = 2,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_META_ITEM_ROUND] =
    {
        .name = sMetaItemRoundName,
        .itemId = ITEM_META_ITEM_ROUND,
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

    [ITEM_META_ITEM_PIKA] =
    {
        .name = sMetaItemPikaName,
        .itemId = ITEM_META_ITEM_PIKA,
        .price = 0,
        .description = sMetaItemPikaDesc,
        .importance = 1,
        .keepItem = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = 2,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_META_ITEM_DUSKULL] =
    {
        .name = sMetaItemDuskullName,
        .itemId = ITEM_META_ITEM_DUSKULL,
        .price = 0,
        .description = sMetaItemDuskullDesc,
        .importance = 1,
        .keepItem = TRUE,
        .pocket = POCKET_KEY_ITEMS,
        .type = 2,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_META_ITEM_WATER] =
    {
        .name = sMetaItemWaterName,
        .itemId = ITEM_META_ITEM_WATER,
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

    [ITEM_RED_SCARF] =
    {
        .name = sRedScarfName,
        .plural = sRedScarfPluralName,
        .itemId = ITEM_RED_SCARF,
        .price = CANDY_COST(100),
        .description = sRedScarfDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_BLUE_SCARF] =
    {
        .name = sBlueScarfName,
        .plural = sBlueScarfPluralName,
        .itemId = ITEM_BLUE_SCARF,
        .price = CANDY_COST(100),
        .description = sBlueScarfDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_PINK_SCARF] =
    {
        .name = sPinkScarfName,
        .plural = sPinkScarfPluralName,
        .itemId = ITEM_PINK_SCARF,
        .price = CANDY_COST(100),
        .description = sPinkScarfDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_GREEN_SCARF] =
    {
        .name = sGreenScarfName,
        .plural = sGreenScarfPluralName,
        .itemId = ITEM_GREEN_SCARF,
        .price = CANDY_COST(100),
        .description = sGreenScarfDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_YELLOW_SCARF] =
    {
        .name = sYellowScarfName,
        .plural = sYellowScarfPluralName,
        .itemId = ITEM_YELLOW_SCARF,
        .price = CANDY_COST(100),
        .description = sYellowScarfDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

// Key items

    [ITEM_MACH_BIKE] =
    {
        .name = sMachBikeName,
        .itemId = ITEM_MACH_BIKE,
        .price = 0,
        .description = sMachBikeDesc,
        .importance = 1,
        .unk19 = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = 2,
        .fieldUseFunc = ItemUseOutOfBattle_Bike,
        .secondaryId = 0,
    },

    [ITEM_COIN_CASE] =
    {
        .name = sCoinCaseName,
        .itemId = ITEM_COIN_CASE,
        .price = 0,
        .description = sCoinCaseDesc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CoinCase,
        .secondaryId = 0,
    },

    [ITEM_ITEMFINDER] =
    {
        .name = sItemfinderName,
        .itemId = ITEM_ITEMFINDER,
        .price = 0,
        .description = sItemfinderDesc,
        .keepItem = TRUE,
        .importance = 1,
        .unk19 = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = 2,
        .fieldUseFunc = ItemUseOutOfBattle_Itemfinder,
        .secondaryId = 0,
    },

    [ITEM_OLD_ROD] =
    {
        .name = sOldRodName,
        .itemId = ITEM_OLD_ROD,
        .price = 0,
        .description = sOldRodDesc,
        .importance = 1,
        .unk19 = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = 2,
        .fieldUseFunc = ItemUseOutOfBattle_Rod,
        .secondaryId = 0,
    },

    [ITEM_GOOD_ROD] =
    {
        .name = sGoodRodName,
        .itemId = ITEM_GOOD_ROD,
        .price = 0,
        .description = sGoodRodDesc,
        .importance = 1,
        .unk19 = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = 2,
        .fieldUseFunc = ItemUseOutOfBattle_Rod,
        .secondaryId = 1,
    },

    [ITEM_SUPER_ROD] =
    {
        .name = sSuperRodName,
        .itemId = ITEM_SUPER_ROD,
        .price = 0,
        .description = sSuperRodDesc,
        .importance = 1,
        .unk19 = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = 2,
        .fieldUseFunc = ItemUseOutOfBattle_Rod,
        .secondaryId = 2,
    },

    [ITEM_SS_TICKET] =
    {
        .name = sSSTicketName,
        .itemId = ITEM_SS_TICKET,
        .price = 0,
        .description = sSSTicketDesc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_CONTEST_PASS] =
    {
        .name = sContestPassName,
        .itemId = ITEM_CONTEST_PASS,
        .price = 0,
        .description = sContestPassDesc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_10B] =
    {
        .name = sDummyName,
        .itemId = ITEM_NONE,
        .price = 0,
        .description = sDummyDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_WAILMER_PAIL] =
    {
        .name = sWailmerPailName,
        .itemId = ITEM_WAILMER_PAIL,
        .price = 0,
        .description = sWailmerPailDesc,
        .keepItem = TRUE,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = 2,
        .fieldUseFunc = ItemUseOutOfBattle_WailmerPail,
        .secondaryId = 0,
    },

    [ITEM_DEVON_GOODS] =
    {
        .name = sDevonGoodsName,
        .itemId = ITEM_DEVON_GOODS,
        .price = 0,
        .description = sDevonGoodsDesc,
        .importance = 2,
        .pocket = POCKET_KEY_ITEMS,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_SOOT_SACK] =
    {
        .name = sSootSackName,
        .itemId = ITEM_SOOT_SACK,
        .price = 0,
        .description = sSootSackDesc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_BASEMENT_KEY] =
    {
        .name = sBasementKeyName,
        .itemId = ITEM_BASEMENT_KEY,
        .price = 0,
        .description = sBasementKeyDesc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_ACRO_BIKE] =
    {
        .name = sAcroBikeName,
        .itemId = ITEM_ACRO_BIKE,
        .price = 0,
        .description = sAcroBikeDesc,
        .importance = 1,
        .unk19 = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = 2,
        .fieldUseFunc = ItemUseOutOfBattle_Bike,
        .secondaryId = 1,
    },

    [ITEM_POKEBLOCK_CASE] =
    {
        .name = sPokeblockCaseName,
        .itemId = ITEM_POKEBLOCK_CASE,
        .price = 0,
        .description = sPokeblockCaseDesc,
        .importance = 1,
        .unk19 = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = 3,
        .fieldUseFunc = ItemUseOutOfBattle_PokeblockCase,
        .secondaryId = 0,
    },

    [ITEM_LETTER] =
    {
        .name = sLetterName,
        .itemId = ITEM_LETTER,
        .price = 0,
        .description = sLetterDesc,
        .importance = 2,
        .pocket = POCKET_KEY_ITEMS,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_EON_TICKET] =
    {
        .name = sEonTicketName,
        .itemId = ITEM_EON_TICKET,
        .price = 0,
        .description = sEonTicketDesc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 1,
    },

    [ITEM_RED_ORB] =
    {
        .name = sRedOrbName,
        .itemId = ITEM_RED_ORB,
        .price = 0,
        .description = sRedOrbDesc,
        .importance = 2,
        .pocket = POCKET_KEY_ITEMS,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_BLUE_ORB] =
    {
        .name = sBlueOrbName,
        .itemId = ITEM_BLUE_ORB,
        .price = 0,
        .description = sBlueOrbDesc,
        .importance = 2,
        .pocket = POCKET_KEY_ITEMS,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_SCANNER] =
    {
        .name = sScannerName,
        .itemId = ITEM_SCANNER,
        .price = 0,
        .description = sScannerDesc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_GO_GOGGLES] =
    {
        .name = sGoGogglesName,
        .itemId = ITEM_GO_GOGGLES,
        .price = 0,
        .description = sGoGogglesDesc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_METEORITE] =
    {
        .name = sMeteoriteName,
        .itemId = ITEM_METEORITE,
        .price = 0,
        .description = sMeteoriteDesc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_ROOM_1_KEY] =
    {
        .name = sRoom1KeyName,
        .itemId = ITEM_ROOM_1_KEY,
        .price = 0,
        .description = sRoom1KeyDesc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_ROOM_2_KEY] =
    {
        .name = sRoom2KeyName,
        .itemId = ITEM_ROOM_2_KEY,
        .price = 0,
        .description = sRoom2KeyDesc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_ROOM_4_KEY] =
    {
        .name = sRoom4KeyName,
        .itemId = ITEM_ROOM_4_KEY,
        .price = 0,
        .description = sRoom4KeyDesc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_ROOM_6_KEY] =
    {
        .name = sRoom6KeyName,
        .itemId = ITEM_ROOM_6_KEY,
        .price = 0,
        .description = sRoom6KeyDesc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_STORAGE_KEY] =
    {
        .name = sStorageKeyName,
        .itemId = ITEM_STORAGE_KEY,
        .price = 0,
        .description = sStorageKeyDesc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_ROOT_FOSSIL] =
    {
        .name = sRootFossilName,
        .itemId = ITEM_ROOT_FOSSIL,
        .price = 0,
        .description = sRootFossilDesc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_CLAW_FOSSIL] =
    {
        .name = sClawFossilName,
        .itemId = ITEM_CLAW_FOSSIL,
        .price = 0,
        .description = sClawFossilDesc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_DEVON_SCOPE] =
    {
        .name = sDevonScopeName,
        .itemId = ITEM_DEVON_SCOPE,
        .price = 0,
        .description = sDevonScopeDesc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

// TMs/HMs

    [ITEM_TM01_FOCUS_PUNCH] =
    {
        .name = sTM01Name,
        .itemId = ITEM_TM01_FOCUS_PUNCH,
        .price = CANDY_COST(3000),
        .description = sTM01Desc,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_TM02_DRAGON_CLAW] =
    {
        .name = sTM02Name,
        .itemId = ITEM_TM02_DRAGON_CLAW,
        .price = CANDY_COST(3000),
        .description = sTM02Desc,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_TM03_WATER_PULSE] =
    {
        .name = sTM03Name,
        .itemId = ITEM_TM03_WATER_PULSE,
        .price = CANDY_COST(3000),
        .description = sTM03Desc,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_TM04_CALM_MIND] =
    {
        .name = sTM04Name,
        .itemId = ITEM_TM04_CALM_MIND,
        .price = CANDY_COST(3000),
        .description = sTM04Desc,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_TM05_ROAR] =
    {
        .name = sTM05Name,
        .itemId = ITEM_TM05_ROAR,
        .price = CANDY_COST(1000),
        .description = sTM05Desc,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_TM06_TOXIC] =
    {
        .name = sTM06Name,
        .itemId = ITEM_TM06_TOXIC,
        .price = CANDY_COST(3000),
        .description = sTM06Desc,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_TM07_HAIL] =
    {
        .name = sTM07Name,
        .itemId = ITEM_TM07_HAIL,
        .price = CANDY_COST(3000),
        .description = sTM07Desc,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_TM08_BULK_UP] =
    {
        .name = sTM08Name,
        .itemId = ITEM_TM08_BULK_UP,
        .price = CANDY_COST(3000),
        .description = sTM08Desc,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_TM09_BULLET_SEED] =
    {
        .name = sTM09Name,
        .itemId = ITEM_TM09_BULLET_SEED,
        .price = CANDY_COST(3000),
        .description = sTM09Desc,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_TM10_HIDDEN_POWER] =
    {
        .name = sTM10Name,
        .itemId = ITEM_TM10_HIDDEN_POWER,
        .price = CANDY_COST(3000),
        .description = sTM10Desc,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_TM11_SUNNY_DAY] =
    {
        .name = sTM11Name,
        .itemId = ITEM_TM11_SUNNY_DAY,
        .price = CANDY_COST(2000),
        .description = sTM11Desc,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_TM12_TAUNT] =
    {
        .name = sTM12Name,
        .itemId = ITEM_TM12_TAUNT,
        .price = CANDY_COST(3000),
        .description = sTM12Desc,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_TM13_ICE_BEAM] =
    {
        .name = sTM13Name,
        .itemId = ITEM_TM13_ICE_BEAM,
        .price = CANDY_COST(3000),
        .description = sTM13Desc,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_TM14_BLIZZARD] =
    {
        .name = sTM14Name,
        .itemId = ITEM_TM14_BLIZZARD,
        .price = CANDY_COST(5500),
        .description = sTM14Desc,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_TM15_HYPER_BEAM] =
    {
        .name = sTM15Name,
        .itemId = ITEM_TM15_HYPER_BEAM,
        .price = CANDY_COST(7500),
        .description = sTM15Desc,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_TM16_LIGHT_SCREEN] =
    {
        .name = sTM16Name,
        .itemId = ITEM_TM16_LIGHT_SCREEN,
        .price = CANDY_COST(3000),
        .description = sTM16Desc,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_TM17_PROTECT] =
    {
        .name = sTM17Name,
        .itemId = ITEM_TM17_PROTECT,
        .price = CANDY_COST(3000),
        .description = sTM17Desc,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_TM18_RAIN_DANCE] =
    {
        .name = sTM18Name,
        .itemId = ITEM_TM18_RAIN_DANCE,
        .price = CANDY_COST(2000),
        .description = sTM18Desc,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_TM19_GIGA_DRAIN] =
    {
        .name = sTM19Name,
        .itemId = ITEM_TM19_GIGA_DRAIN,
        .price = CANDY_COST(3000),
        .description = sTM19Desc,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_TM20_SAFEGUARD] =
    {
        .name = sTM20Name,
        .itemId = ITEM_TM20_SAFEGUARD,
        .price = CANDY_COST(3000),
        .description = sTM20Desc,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_TM21_FRUSTRATION] =
    {
        .name = sTM21Name,
        .itemId = ITEM_TM21_FRUSTRATION,
        .price = CANDY_COST(1000),
        .description = sTM21Desc,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_TM22_SOLARBEAM] =
    {
        .name = sTM22Name,
        .itemId = ITEM_TM22_SOLARBEAM,
        .price = CANDY_COST(3000),
        .description = sTM22Desc,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_TM23_IRON_TAIL] =
    {
        .name = sTM23Name,
        .itemId = ITEM_TM23_IRON_TAIL,
        .price = CANDY_COST(3000),
        .description = sTM23Desc,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_TM24_THUNDERBOLT] =
    {
        .name = sTM24Name,
        .itemId = ITEM_TM24_THUNDERBOLT,
        .price = CANDY_COST(3000),
        .description = sTM24Desc,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_TM25_THUNDER] =
    {
        .name = sTM25Name,
        .itemId = ITEM_TM25_THUNDER,
        .price = CANDY_COST(5500),
        .description = sTM25Desc,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_TM26_EARTHQUAKE] =
    {
        .name = sTM26Name,
        .itemId = ITEM_TM26_EARTHQUAKE,
        .price = CANDY_COST(3000),
        .description = sTM26Desc,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_TM27_RETURN] =
    {
        .name = sTM27Name,
        .itemId = ITEM_TM27_RETURN,
        .price = CANDY_COST(1000),
        .description = sTM27Desc,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_TM28_DIG] =
    {
        .name = sTM28Name,
        .itemId = ITEM_TM28_DIG,
        .price = CANDY_COST(2000),
        .description = sTM28Desc,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_TM29_PSYCHIC] =
    {
        .name = sTM29Name,
        .itemId = ITEM_TM29_PSYCHIC,
        .price = CANDY_COST(2000),
        .description = sTM29Desc,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_TM30_SHADOW_BALL] =
    {
        .name = sTM30Name,
        .itemId = ITEM_TM30_SHADOW_BALL,
        .price = CANDY_COST(3000),
        .description = sTM30Desc,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_TM31_BRICK_BREAK] =
    {
        .name = sTM31Name,
        .itemId = ITEM_TM31_BRICK_BREAK,
        .price = CANDY_COST(3000),
        .description = sTM31Desc,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_TM32_DOUBLE_TEAM] =
    {
        .name = sTM32Name,
        .itemId = ITEM_TM32_DOUBLE_TEAM,
        .price = CANDY_COST(2000),
        .description = sTM32Desc,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_TM33_REFLECT] =
    {
        .name = sTM33Name,
        .itemId = ITEM_TM33_REFLECT,
        .price = CANDY_COST(3000),
        .description = sTM33Desc,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_TM34_SHOCK_WAVE] =
    {
        .name = sTM34Name,
        .itemId = ITEM_TM34_SHOCK_WAVE,
        .price = CANDY_COST(3000),
        .description = sTM34Desc,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_TM35_FLAMETHROWER] =
    {
        .name = sTM35Name,
        .itemId = ITEM_TM35_FLAMETHROWER,
        .price = CANDY_COST(3000),
        .description = sTM35Desc,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_TM36_SLUDGE_BOMB] =
    {
        .name = sTM36Name,
        .itemId = ITEM_TM36_SLUDGE_BOMB,
        .price = CANDY_COST(1000),
        .description = sTM36Desc,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_TM37_SANDSTORM] =
    {
        .name = sTM37Name,
        .itemId = ITEM_TM37_SANDSTORM,
        .price = CANDY_COST(2000),
        .description = sTM37Desc,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_TM38_FIRE_BLAST] =
    {
        .name = sTM38Name,
        .itemId = ITEM_TM38_FIRE_BLAST,
        .price = CANDY_COST(5500),
        .description = sTM38Desc,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_TM39_ROCK_TOMB] =
    {
        .name = sTM39Name,
        .itemId = ITEM_TM39_ROCK_TOMB,
        .price = CANDY_COST(3000),
        .description = sTM39Desc,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_TM40_AERIAL_ACE] =
    {
        .name = sTM40Name,
        .itemId = ITEM_TM40_AERIAL_ACE,
        .price = CANDY_COST(3000),
        .description = sTM40Desc,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_TM41_TORMENT] =
    {
        .name = sTM41Name,
        .itemId = ITEM_TM41_TORMENT,
        .price = CANDY_COST(3000),
        .description = sTM41Desc,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_TM42_FACADE] =
    {
        .name = sTM42Name,
        .itemId = ITEM_TM42_FACADE,
        .price = CANDY_COST(3000),
        .description = sTM42Desc,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_TM43_SECRET_POWER] =
    {
        .name = sTM43Name,
        .itemId = ITEM_TM43_SECRET_POWER,
        .price = CANDY_COST(3000),
        .description = sTM43Desc,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_TM44_REST] =
    {
        .name = sTM44Name,
        .itemId = ITEM_TM44_REST,
        .price = CANDY_COST(3000),
        .description = sTM44Desc,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_TM45_ATTRACT] =
    {
        .name = sTM45Name,
        .itemId = ITEM_TM45_ATTRACT,
        .price = CANDY_COST(3000),
        .description = sTM45Desc,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_TM46_THIEF] =
    {
        .name = sTM46Name,
        .itemId = ITEM_TM46_THIEF,
        .price = CANDY_COST(3000),
        .description = sTM46Desc,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_TM47_STEEL_WING] =
    {
        .name = sTM47Name,
        .itemId = ITEM_TM47_STEEL_WING,
        .price = CANDY_COST(3000),
        .description = sTM47Desc,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_TM48_SKILL_SWAP] =
    {
        .name = sTM48Name,
        .itemId = ITEM_TM48_SKILL_SWAP,
        .price = CANDY_COST(3000),
        .description = sTM48Desc,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_TM49_SNATCH] =
    {
        .name = sTM49Name,
        .itemId = ITEM_TM49_SNATCH,
        .price = CANDY_COST(3000),
        .description = sTM49Desc,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_TM50_OVERHEAT] =
    {
        .name = sTM50Name,
        .itemId = ITEM_TM50_OVERHEAT,
        .price = CANDY_COST(3000),
        .description = sTM50Desc,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_HM01_CUT] =
    {
        .name = sHM01Name,
        .itemId = ITEM_HM01_CUT,
        .price = 0,
        .description = sHM01Desc,
        .importance = 1,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_HM02_FLY] =
    {
        .name = sHM02Name,
        .itemId = ITEM_HM02_FLY,
        .price = 0,
        .description = sHM02Desc,
        .importance = 1,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_HM03_SURF] =
    {
        .name = sHM03Name,
        .itemId = ITEM_HM03_SURF,
        .price = 0,
        .description = sHM03Desc,
        .importance = 1,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_HM04_STRENGTH] =
    {
        .name = sHM04Name,
        .itemId = ITEM_HM04_STRENGTH,
        .price = 0,
        .description = sHM04Desc,
        .importance = 1,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_HM05_FLASH] =
    {
        .name = sHM05Name,
        .itemId = ITEM_HM05_FLASH,
        .price = 0,
        .description = sHM05Desc,
        .importance = 1,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_HM06_ROCK_SMASH] =
    {
        .name = sHM06Name,
        .itemId = ITEM_HM06_ROCK_SMASH,
        .price = 0,
        .description = sHM06Desc,
        .importance = 1,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_HM07_WATERFALL] =
    {
        .name = sHM07Name,
        .itemId = ITEM_HM07_WATERFALL,
        .price = 0,
        .description = sHM07Desc,
        .importance = 1,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_HM08_DIVE] =
    {
        .name = sHM08Name,
        .itemId = ITEM_HM08_DIVE,
        .price = 0,
        .description = sHM08Desc,
        .importance = 1,
        .pocket = POCKET_TM_HM,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
        .secondaryId = 0,
    },

    [ITEM_15B] =
    {
        .name = sDummyName,
        .itemId = ITEM_NONE,
        .price = 0,
        .description = sDummyDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_15C] =
    {
        .name = sDummyName,
        .itemId = ITEM_NONE,
        .price = 0,
        .description = sDummyDesc,
        .pocket = POCKET_GENERAL,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

// FireRed/LeafGreen key items

    [ITEM_OAKS_PARCEL] =
    {
        .name = sOaksParcelName,
        .itemId = ITEM_OAKS_PARCEL,
        .price = 0,
        .description = sOaksParcelDesc,
        .importance = 2,
        .pocket = POCKET_KEY_ITEMS,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_POKE_FLUTE] =
    {
        .name = sPokeFluteName,
        .itemId = ITEM_POKE_FLUTE,
        .price = 0,
        .description = sPokeFluteDesc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_SECRET_KEY] =
    {
        .name = sSecretKeyName,
        .itemId = ITEM_SECRET_KEY,
        .price = 0,
        .description = sSecretKeyDesc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_BIKE_VOUCHER] =
    {
        .name = sBikeVoucherName,
        .itemId = ITEM_BIKE_VOUCHER,
        .price = 0,
        .description = sBikeVoucherDesc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_GOLD_TEETH] =
    {
        .name = sGoldTeethName,
        .itemId = ITEM_GOLD_TEETH,
        .price = 0,
        .description = sGoldTeethDesc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_OLD_AMBER] =
    {
        .name = sOldAmberName,
        .itemId = ITEM_OLD_AMBER,
        .price = 0,
        .description = sOldAmberDesc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_CARD_KEY] =
    {
        .name = sCardKeyName,
        .itemId = ITEM_CARD_KEY,
        .price = 0,
        .description = sCardKeyDesc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_LIFT_KEY] =
    {
        .name = sLiftKeyName,
        .itemId = ITEM_LIFT_KEY,
        .price = 0,
        .description = sLiftKeyDesc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_HELIX_FOSSIL] =
    {
        .name = sHelixFossilName,
        .itemId = ITEM_HELIX_FOSSIL,
        .price = 0,
        .description = sHelixFossilDesc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_DOME_FOSSIL] =
    {
        .name = sDomeFossilName,
        .itemId = ITEM_DOME_FOSSIL,
        .price = 0,
        .description = sDomeFossilDesc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_SILPH_SCOPE] =
    {
        .name = sSilphScopeName,
        .itemId = ITEM_SILPH_SCOPE,
        .price = 0,
        .description = sSilphScopeDesc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_BICYCLE] =
    {
        .name = sBicycleName,
        .itemId = ITEM_BICYCLE,
        .price = 0,
        .description = sBicycleDesc,
        .importance = 1,
        .unk19 = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = 2,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_TOWN_MAP] =
    {
        .name = sTownMapName,
        .itemId = ITEM_TOWN_MAP,
        .price = 0,
        .description = sTownMapDesc,
        .importance = 1,
        .unk19 = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_VS_SEEKER] =
    {
        .name = sVSSeekerName,
        .itemId = ITEM_VS_SEEKER,
        .price = 0,
        .description = sVSSeekerDesc,
        .importance = 1,
        .unk19 = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = 2,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_FAME_CHECKER] =
    {
        .name = sFameCheckerName,
        .itemId = ITEM_FAME_CHECKER,
        .price = 0,
        .description = sFameCheckerDesc,
        .importance = 1,
        .unk19 = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_TM_CASE] =
    {
        .name = sTMCaseName,
        .itemId = ITEM_TM_CASE,
        .price = 0,
        .description = sTMCaseDesc,
        .importance = 1,
        .unk19 = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_BERRY_POUCH] =
    {
        .name = sBerryPouchName,
        .itemId = ITEM_BERRY_POUCH,
        .price = 0,
        .description = sBerryPouchDesc,
        .importance = 1,
        .unk19 = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_TEACHY_TV] =
    {
        .name = sTeachyTVName,
        .itemId = ITEM_TEACHY_TV,
        .price = 0,
        .description = sTeachyTVDesc,
        .importance = 1,
        .unk19 = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = 2,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_TRI_PASS] =
    {
        .name = sTriPassName,
        .itemId = ITEM_TRI_PASS,
        .price = 0,
        .description = sTriPassDesc,
        .importance = 1,
        .unk19 = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_RAINBOW_PASS] =
    {
        .name = sRainbowPassName,
        .itemId = ITEM_RAINBOW_PASS,
        .price = 0,
        .description = sRainbowPassDesc,
        .importance = 1,
        .unk19 = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_TEA] =
    {
        .name = sTeaName,
        .itemId = ITEM_TEA,
        .price = 0,
        .description = sTeaDesc,
        .importance = 1,
        .unk19 = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_MYSTIC_TICKET] =
    {
        .name = sMysticTicketName,
        .itemId = ITEM_MYSTIC_TICKET,
        .price = 0,
        .description = sMysticTicketDesc,
        .importance = 1,
        .unk19 = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_AURORA_TICKET] =
    {
        .name = sAuroraTicketName,
        .itemId = ITEM_AURORA_TICKET,
        .price = 0,
        .description = sAuroraTicketDesc,
        .importance = 1,
        .unk19 = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_POWDER_JAR] =
    {
        .name = sPowderJarName,
        .itemId = ITEM_POWDER_JAR,
        .price = 0,
        .description = sPowderJarDesc,
        .importance = 1,
        .unk19 = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_PowderJar,
        .secondaryId = 0,
    },

    [ITEM_RUBY] =
    {
        .name = sRubyName,
        .itemId = ITEM_RUBY,
        .price = 0,
        .description = sRubyDesc,
        .importance = 1,
        .unk19 = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_SAPPHIRE] =
    {
        .name = sSapphireName,
        .itemId = ITEM_SAPPHIRE,
        .price = 0,
        .description = sSapphireDesc,
        .importance = 1,
        .unk19 = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

// Emerald-specific key items

    [ITEM_MAGMA_EMBLEM] =
    {
        .name = sMagmaEmblemName,
        .itemId = ITEM_MAGMA_EMBLEM,
        .price = 0,
        .description = sMagmaEmblemDesc,
        .importance = 1,
        .unk19 = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

    [ITEM_OLD_SEA_MAP] =
    {
        .name = sOldSeaMapName,
        .itemId = ITEM_OLD_SEA_MAP,
        .price = 0,
        .description = sOldSeaMapDesc,
        .importance = 1,
        .unk19 = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },

// TTH Candy
    
    [ITEM_CANDY_CHOCOLATE] =
    {
        .name = sChocolateName,
        .quantum = sBarQuantum,
        .itemId = ITEM_CANDY_CHOCOLATE,
        .price = CANDY_COST(200),
        .itemEffect = gItemEffect_HealHP20,
        .holdEffect = HOLD_EFFECT_RESTORE_HP,
        .holdEffectParam = 20,
        .description = sChocolateDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_CHOCOWHITE] =
    {
        .name = sChocoWhiteName,
        .quantum = sBarQuantum,
        .itemId = ITEM_CANDY_CHOCOWHITE,
        .price = CANDY_COST(500),
        .itemEffect = gItemEffect_HealHP50,
        .holdEffect = HOLD_EFFECT_RESTORE_HP,
        .holdEffectParam = 50,
        .description = sChocoWhiteDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_CHOCOSLAB] =
    {
        .name = sChocoSlabName,
        .itemId = ITEM_CANDY_CHOCOSLAB,
        .price = CANDY_COST(2000),
        .description = sChocoSlabDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_STARBURST] =
    {
        .name = sStarburstName,
        .itemId = ITEM_CANDY_STARBURST,
        .price = CANDY_COST(100),
        .itemEffect = gItemEffect_HealPoison,
        .holdEffect = HOLD_EFFECT_CURE_PSN,
        .description = sAntidoteDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_LEMONDROP] =
    {
        .name = sLemonDropName,
        .itemId = ITEM_CANDY_LEMONDROP,
        .price = CANDY_COST(250),
        .itemEffect = gItemEffect_HealBurn,
        .holdEffect = HOLD_EFFECT_CURE_BRN,
        .description = sBurnHealDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_WARHEAD] =
    {
        .name = sWarheadName,
        .itemId = ITEM_CANDY_WARHEAD,
        .price = CANDY_COST(200),
        .itemEffect = gItemEffect_HealFreeze,
        .holdEffect = HOLD_EFFECT_CURE_FRZ,
        .description = sIceHealDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_PRETZEL] =
    {
        .name = sPretzelName,
        .itemId = ITEM_CANDY_PRETZEL,
        .price = CANDY_COST(250),
        .itemEffect = gItemEffect_HealSleep,
        .holdEffect = HOLD_EFFECT_CURE_SLP,
        .description = sAwakeningDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_VEROMANGO] =
    {
        .name = sVeroMangoName,
        .itemId = ITEM_CANDY_VEROMANGO,
        .price = CANDY_COST(200),
        .itemEffect = gItemEffect_HealParalyze,
        .holdEffect = HOLD_EFFECT_CURE_PAR,
        .description = sParalyzeHealDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_VIOLETCRUMBLE] =
    {
        .name = sVioletCrumbleName,
        .itemId = ITEM_CANDY_VIOLETCRUMBLE,
        .price = CANDY_COST(200),
        .itemEffect = gItemEffect_HealConfusion,
        .holdEffect = HOLD_EFFECT_CURE_CONFUSION,
        .description = sVioletCrumbleDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_GALAXY] =
    {
        .name = sGalaxyName,
        .itemId = ITEM_CANDY_GALAXY,
        .price = CANDY_COST(200),
        .itemEffect = gItemEffect_HealInfatuation,
        .holdEffect = HOLD_EFFECT_CURE_ATTRACT,
        .description = sGalaxyDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_TWIXLEFT] =
    {
        .name = sTwixLeftName,
        .quantum = sBarQuantum,
        .itemId = ITEM_CANDY_TWIXLEFT,
        .price = CANDY_COST(250),
        .itemEffect = gItemEffect_HealHP30,
        .holdEffect = HOLD_EFFECT_RESTORE_HP,
        .holdEffectParam = 30,
        .description = sTwixLeftDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_TWIXRIGHT] =
    {
        .name = sTwixRightName,
        .quantum = sBarQuantum,
        .itemId = ITEM_CANDY_TWIXRIGHT,
        .price = CANDY_COST(250),
        .itemEffect = gItemEffect_HealPP4,
        .holdEffect = HOLD_EFFECT_RESTORE_PP,
        .description = sTwixRightDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_MMMINI] =
    {
        .name = sMMMinisName,
        .quantum = sMMMinisQuantum,
        .itemId = ITEM_CANDY_MMMINI,
        .price = CANDY_COST(150),
        .itemEffect = gItemEffect_HealHP20,
        .holdEffect = HOLD_EFFECT_RESTORE_HP,
        .holdEffectParam = 20,
        .description = sMMMinisDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_MMPEANUT] =
    {
        .name = sMMPeanutName,
        .quantum = sPacketQuantum,
        .itemId = ITEM_CANDY_MMPEANUT,
        .price = CANDY_COST(400),
        .itemEffect = gItemEffect_HealHP50,
        .holdEffect = HOLD_EFFECT_RESTORE_HP,
        .holdEffectParam = 50,
        .description = sMMPeanutDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_KINGCHOCNUT] =
    {
        .name = sKingChocName,
        .quantum = sBoxQuantum,
        .plural = sBoxQuantumPlural,
        .itemId = ITEM_CANDY_KINGCHOCNUT,
        .price = CANDY_COST(300),
        .itemEffect = gItemEffect_HealHP30,
        .holdEffect = HOLD_EFFECT_RESTORE_HP,
        .holdEffectParam = 30,
        .description = sKingChocDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_GUMMYBEAR] =
    {
        .name = sGummyBearName,
        .quantum = sPacketQuantum,
        .itemId = ITEM_CANDY_GUMMYBEAR,
        .price = CANDY_COST(50),
        .description = sGummyBearDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = 4,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = 2,
        .itemEffect = gItemEffect_XRandom,
        .battleUseFunc = ItemUseInBattle_StatIncrease,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_REESES] =
    {
        .name = sReeseCupName,
        .itemId = ITEM_CANDY_REESES,
        .price = CANDY_COST(500),
        .description = sReeseCupDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = 1,
        .itemEffect = gItemEffect_HealAllStatus,
        .battleUseFunc = ItemUseInBattle_Medicine,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_BUTTERFINGER] =
    {
        .name = sButterfingerName,
        .itemId = ITEM_CANDY_BUTTERFINGER,
        .price = CANDY_COST(200),
        .description = sButterfingerDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_MILKYWAY] =
    {
        .name = sMilkyWayName,
        .itemId = ITEM_CANDY_MILKYWAY,
        .price = CANDY_COST(200),
        .description = sMilkyWayDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_MILKALUFLEE] =
    {
        .name = sMilkaLufleeName,
        .quantum = sBarQuantum,
        .itemId = ITEM_CANDY_MILKALUFLEE,
        .price = CANDY_COST(200),
        .description = sMilkaLufleeDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_100GRAND] =
    {
        .name = s100GrandName,
        .itemId = ITEM_CANDY_100GRAND,
        .price = CANDY_COST(200),
        .description = s100GrandDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_MALTESERS] =
    {
        .name = sMalteserName,
        .itemId = ITEM_CANDY_MALTESERS,
        .price = CANDY_COST(200),
        .description = sMalteserDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_CADBURYCREME] =
    {
        .name = sCadburyCremeName,
        .itemId = ITEM_CANDY_CADBURYCREME,
        .price = CANDY_COST(200),
        .description = sCadburyCremeDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_WUNDERBAR] =
    {
        .name = sWunderbarName,
        .itemId = ITEM_CANDY_WUNDERBAR,
        .price = CANDY_COST(200),
        .description = sWunderbarDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_OREO] =
    {
        .name = sOreoCookiesName,
        .quantum = sOreoCookiesQuantum,
        .itemId = ITEM_CANDY_OREO,
        .price = CANDY_COST(200),
        .description = sOreoCookiesDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_COFFEECRISP] =
    {
        .name = sCoffeeCrispName,
        .itemId = ITEM_CANDY_COFFEECRISP,
        .price = CANDY_COST(200),
        .description = sCoffeeCrispDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_SAMBOPRISTUR] =
    {
        .name = sSamboPristurName,
        .itemId = ITEM_CANDY_SAMBOPRISTUR,
        .price = CANDY_COST(200),
        .description = sSamboPristurDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_SNICKERS] =
    {
        .name = sSnickersName,
        .itemId = ITEM_CANDY_SNICKERS,
        .price = CANDY_COST(200),
        .description = sSnickersDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = 1,
        // .battleUsage = 2,
        // .battleUseFunc = ItemUseInBattle_Escape,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_MARSBAR] =
    {
        .name = sMarsBarName,
        .itemId = ITEM_CANDY_MARSBAR,
        .price = CANDY_COST(200),
        .description = sMarsBarDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_KITKAT] =
    {
        .name = sKitKatBarName,
        .itemId = ITEM_CANDY_KITKAT,
        .price = CANDY_COST(200),
        .description = sKitKatBarDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_PIXIESTICK] =
    {
        .name = sPixieStickName,
        .itemId = ITEM_CANDY_PIXIESTICK,
        .price = CANDY_COST(200),
        .description = sPixieStickDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_TURKISHDELIGHT] =
    {
        .name = sTurkishDelightName,
        .itemId = ITEM_CANDY_TURKISHDELIGHT,
        .price = CANDY_COST(200),
        .description = sTurkishDelightDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_GOBSTOPPER] =
    {
        .name = sGobstopperName,
        .itemId = ITEM_CANDY_GOBSTOPPER,
        .price = CANDY_COST(200),
        .description = sGobstopperDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_BLACKTHUNDER] =
    {
        .name = sBlackThunderName,
        .itemId = ITEM_CANDY_BLACKTHUNDER,
        .price = CANDY_COST(200),
        .description = sBlackThunderDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_TOBLERONE] =
    {
        .name = sTobleroneName,
        .itemId = ITEM_CANDY_TOBLERONE,
        .price = CANDY_COST(200),
        .description = sTobleroneDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_FERREROROCHER] =
    {
        .name = sFerreroRocherName,
        .itemId = ITEM_CANDY_FERREROROCHER,
        .price = CANDY_COST(200),
        .description = sFerreroRocherDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_EGGS] =
    {
        .name = sEggName,
        .itemId = ITEM_CANDY_EGGS,
        .price = CANDY_COST(200),
        .description = sEggDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_EGGDEVILED] =
    {
        .name = sEggDeviledName,
        .itemId = ITEM_CANDY_EGGDEVILED,
        .price = CANDY_COST(200),
        .description = sEggDeviledDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_CARROT] =
    {
        .name = sCarrotName,
        .quantum = sBarQuantum,
        .itemId = ITEM_CANDY_CARROT,
        .price = CANDY_COST(200),
        .description = sCarrotDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_APPLE] =
    {
        .name = sAppleName,
        .quantum = sBarQuantum,
        .itemId = ITEM_CANDY_APPLE,
        .price = CANDY_COST(200),
        .description = sAppleDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_PRUNE] =
    {
        .name = sPruneName,
        .quantum = sBarQuantum,
        .itemId = ITEM_CANDY_PRUNE,
        .price = CANDY_COST(200),
        .description = sPruneDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_CELERY] =
    {
        .name = sCeleryName,
        .quantum = sBarQuantum,
        .itemId = ITEM_CANDY_CELERY,
        .price = CANDY_COST(200),
        .description = sCeleryDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_SNAPPEAS] =
    {
        .name =  sSnapPeasName,
        .quantum = sBoxQuantum,
        .plural = sBoxQuantumPlural,
        .itemId = ITEM_CANDY_SNAPPEAS,
        .price = CANDY_COST(200),
        .description =  sSnapPeasDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_RAISIN] =
    {
        .name = sRaisensName,
        .quantum = sBoxQuantum,
        .plural = sBoxQuantumPlural,
        .itemId = ITEM_CANDY_RAISIN,
        .price = CANDY_COST(200),
        .description = sRaisensDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },
    
    [ITEM_CANDY_KALE] =
    {
        .name = sKaleChipsName,
        .quantum = sBagQuantum,
        .itemId = ITEM_CANDY_KALE,
        .price = CANDY_COST(200),
        .description = sKaleChipsDesc,
        .keepItem = TRUE,
        .isCandy = TRUE,
        .pocket = POCKET_CANDY,
        .type = 1,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 0,
    },
    
};

static const u16 gCandyAbundantIds[] = {
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
};
static const u16 gCandyCommonIds[] = {
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
    ITEM_CANDY_EGGS,
};
static const u16 gCandyUncommonIds[] = {
    ITEM_CANDY_WUNDERBAR,
    ITEM_CANDY_COFFEECRISP,
    ITEM_CANDY_SAMBOPRISTUR,
    ITEM_CANDY_SNICKERS,
    ITEM_CANDY_MARSBAR,
    ITEM_CANDY_KITKAT,
    ITEM_CANDY_PIXIESTICK,
    ITEM_CANDY_EGGDEVILED,
};
static const u16 gCandyRareIds[] = {
    ITEM_CANDY_CHOCOSLAB,
    ITEM_CANDY_TURKISHDELIGHT,
    ITEM_CANDY_GOBSTOPPER,
    ITEM_CANDY_BLACKTHUNDER,
    ITEM_CANDY_TOBLERONE,
    ITEM_CANDY_FERREROROCHER,
};
static const u16 gCandyHealthyIds[] = {
    ITEM_CANDY_CARROT,
    ITEM_CANDY_APPLE,
    ITEM_CANDY_PRUNE,
    ITEM_CANDY_CELERY,
    ITEM_CANDY_SNAPPEAS,
    ITEM_CANDY_RAISIN,
    ITEM_CANDY_KALE,
};

#undef CANDY_COST
#undef CANDY_COST2