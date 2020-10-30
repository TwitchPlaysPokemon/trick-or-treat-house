
const u8 gBort_BattleMenu[] = _("FIGH{CLEAR_TO 56}BAG\nELF{CLEAR_TO 56}GO");
const u8 gBort_WhatWillPkmnDo[] = _("{B_ACTIVE_NAME_WITH_PREFIX}\nWHAT?");

static const u8 sBort_OpponentMon1Appeared[] = _("{B_OPPONENT_MON1_NAME}\nJUMP OUT\p");
static const u8 sBort_WildPkmnAppeared[] = _("WILD {B_OPPONENT_MON1_NAME}\nJUMP OUT\p");
static const u8 sBort_WildPkmnAppeared2[] = _("WILD {B_OPPONENT_MON1_NAME}\nJUMP OUT\p");
static const u8 sBort_WildPkmnAppearedPause[] = _("WILD {B_OPPONENT_MON1_NAME}\nJUMP OUT{PAUSE 127}");
static const u8 sBort_TwoWildPkmnAppeared[] = _("WILD {B_OPPONENT_MON1_NAME}\n{B_OPPONENT_MON2_NAME} JUMP OUT\p");
static const u8 sBort_Trainer1WantsToBattle[] = _("{B_TRAINER1_CLASS}'S{B_TRAINER1_NAME}\nTO COMPETE\p");
static const u8 sBort_TwoTrainersWantToBattle[] = _("{B_TRAINER1_CLASS}'S{B_TRAINER1_NAME}\n{B_TRAINER2_CLASS}'S{B_TRAINER2_NAME}\lTO COMPETE\p");
static const u8 sBort_Trainer1SentOutPkmn[] = _("{B_TRAINER1_CLASS}'S{B_TRAINER1_NAME}\n{B_OPPONENT_MON1_NAME} START");
static const u8 sBort_Trainer1SentOutTwoPkmn[] = _("{B_TRAINER1_CLASS}'S{B_TRAINER1_NAME}\n{B_OPPONENT_MON1_NAME} {B_OPPONENT_MON2_NAME} START");
static const u8 sBort_Trainer1SentOutPkmn2[] = _("{B_TRAINER1_CLASS}'S{B_TRAINER1_NAME}\n{B_BUFF1} START");
static const u8 sBort_TwoTrainersSentPkmn[] = _("{B_TRAINER1_CLASS}'S{B_TRAINER1_NAME}\n{B_OPPONENT_MON1_NAME} START\p{B_TRAINER2_CLASS}'S{B_TRAINER2_NAME}\n{B_OPPONENT_MON2_NAME} START");
static const u8 sBort_Trainer2SentOutPkmn[] = _("{B_TRAINER2_CLASS}'S{B_TRAINER2_NAME}\n{B_BUFF1} START");
static const u8 sBort_GoPkmn[] = _("GO AWAY");
static const u8 sBort_GoTwoPkmn[] = _("GO AWAY TOO");
static const u8 sBort_PlayerUsedItem[] = _("{B_PLAYER_NAME}\n{B_LAST_ITEM}   USED!");
static const u8 sBort_FoePkmnPrefix[] = _("EN'S");
static const u8 sBort_WildPkmnPrefix[] = _("WILD ");
static const u8 sBort_EnemyAboutToSwitchPkmn[] = _("{B_TRAINER1_CLASS}'S{B_TRAINER1_NAME}\n{B_BUFF2} START {B_PLAYER_NAME}\lEXCHANGE ELF TOO?");
static const u8 sBort_ItDoesntAffect[] = _("{B_DEF_NAME_WITH_PREFIX}\nNO EFFECTIVE");
static const u8 sBort_NotVeryEffective[] = _("ONE RESULT");
static const u8 sBort_SuperEffective[] = _("EFFECTIVELY!");
static const u8 sBort_GotAwaySafely[] = _("{PLAY_SE 0x0011}ESCAPED PERFECTLY\p");
static const u8 sBort_AttackerFainted[] = _("{B_ATK_NAME_WITH_PREFIX}?\nFALLED\p");
static const u8 sBort_TargetFainted[] = _("{B_DEF_NAME_WITH_PREFIX}?\nFALLED\p");
static const u8 sBort_CriticalHit[] = _("HIT TO KEY");
static const u8 sBort_PkmnThatsEnough[] = _("{B_BUFF1} HAVE A PILLORY");
static const u8 sBort_PkmnComeBack[] = _("{B_BUFF1} BACK");
static const u8 sBort_PkmnOkComeBack[] = _("{B_BUFF1} DO WELL");
static const u8 sBort_PkmnGoodComeBack[] = _("{B_BUFF1} GOOD");
static const u8 sBort_DoItPkmn[] = _("GO AWAY");
static const u8 sBort_GoForItPkmn[] = _("TRY HARD");
static const u8 sBort_YourFoesWeakGetEmPkmn[] = _("IT'S A CHANCE!");
static const u8 sBort_PlayerDefeatedTrainer[] = _("{B_TRAINER1_CLASS}'S{B_TRAINER1_NAME}\nWON\p");
static const u8 sBort_PlayerDefeatedLinkTrainer[] = _("{B_LINK_OPPONENT1_NAME}\nWON\p");
static const u8 sBort_PlayerGotMoney[] = _("{B_PLAYER_NAME}!AS\nPRIZE {B_BUFF1}\p");
static const u8 sBort_PlayerWhiteout[] = _("THOUGH {B_PLAYER_NAME}\nTRY HARD, THE\lPOCKET MONSTER\lISN'T IN HERE!\p");
static const u8 sBort_PlayerWhiteout2[] = _("{B_PLAYER_NAME} SCENE\nOF BLANK\lAT PRESENT!{PAUSE_UNTIL_PRESS}");
static const u8 sBort_UseNextPkmn[] = _("USE ELF NEXT?");
static const u8 sBort_CantEscape[] = _("CAN'T ESCAPE!\p");
static const u8 sBort_AttackerCantEscape[] = _("{B_ATK_NAME_WITH_PREFIX}\nCAN'T ESCAPE!");
static const u8 sBort_WildFled[] = _("{PLAY_SE 0x0011}{B_LINK_OPPONENT1_NAME} ESCAPED!");
static const u8 sBort_TwoWildFled[] = _("{PLAY_SE 0x0011}{B_LINK_OPPONENT1_NAME}\n{B_LINK_OPPONENT2_NAME} ESCAPED!");


static const u8 sBort_YouMissedPkmn[] = _("MISSED ELF!");
static const u8 sBort_PkmnBrokeFree[] = _("NO!ELF COME OUT");
static const u8 sBort_ItAppearedCaught[] = _("REGARD AS HAVING CAUGHT AT FIRST");
static const u8 sBort_AarghAlmostHadIt[] = _("TOO REGRET,ALMOST CAUGHT IT");
static const u8 sBort_ShootSoClose[] = _("REGRET!ALMOST...");
static const u8 sBort_GotchaPkmnCaught[] = _("SUCCESS {B_OPPONENT_MON1_NAME}\nCAUGHT{WAIT_SE}{PLAY_BGM MUS_KACHI22}\p");
static const u8 sBort_GotchaPkmnCaught2[] = _("SUCCESS {B_OPPONENT_MON1_NAME}\nCAUGHT{WAIT_SE}{PLAY_BGM MUS_KACHI22}{PAUSE 127}");

static const u8 sBort_TrainerBlockedBall[] = _("BALL SPRING TO ELF");
static const u8 sBort_DontBeAThief[] = _("??? ??? ???? ???Y!");

static const u8 sBort_PkmnFellAsleep[] = _("{B_EFF_NAME_WITH_PREFIX}\nSLEEP");
static const u8 sBort_PkmnMadeSleep[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} {B_SCR_ACTIVE_ABILITY}\n{B_EFF_NAME_WITH_PREFIX} SLEEP");
static const u8 sBort_PkmnAlreadyAsleep[] = _("{B_DEF_NAME_WITH_PREFIX}\nSLEPT");
static const u8 sBort_PkmnAlreadyAsleep2[] = _("{B_ATK_NAME_WITH_PREFIX}\nSLEPT");
static const u8 sBort_PkmnFastAsleep[] = _("{B_ATK_NAME_WITH_PREFIX}\nSNORING");
static const u8 sBort_PkmnWokeUp[] = _("{B_ATK_NAME_WITH_PREFIX}\nAWAKED");
static const u8 sBort_PkmnUproarKeptAwake[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} UPROAR\nLOUD");
static const u8 sBort_PkmnWokeUpInUproar[] = _("{B_ATK_NAME_WITH_PREFIX}\nAWAKED LOUD");
static const u8 sBort_PkmnWasntAffected[] = _("BUT\nNOT DECIDED");
static const u8 sBort_PkmnWasPoisoned[] = _("{B_EFF_NAME_WITH_PREFIX}\nKILLED");
static const u8 sBort_PkmnPoisonedBy[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} {B_SCR_ACTIVE_ABILITY}\n{B_EFF_NAME_WITH_PREFIX} KILLED");
static const u8 sBort_PkmnHurtByPoison[] = _("{B_ATK_NAME_WITH_PREFIX}\nTO BE POISONING");
static const u8 sBort_PkmnAlreadyPoisoned[] = _("{B_DEF_NAME_WITH_PREFIX}POSIONING");
static const u8 sBort_PkmnBadlyPoisoned[] = _("{B_EFF_NAME_WITH_PREFIX}\nKILLED BAD");
static const u8 sBort_PkmnEnergyDrained[] = _("{B_DEF_NAME_WITH_PREFIX} had its\nenergy drained!");
static const u8 sBort_PkmnWasBurned[] = _("{B_EFF_NAME_WITH_PREFIX}\nBURNED");
static const u8 sBort_PkmnBurnedBy[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} {B_SCR_ACTIVE_ABILITY}\nBURNED {B_EFF_NAME_WITH_PREFIX}!");
static const u8 sBort_PkmnHurtByBurn[] = _("{B_ATK_NAME_WITH_PREFIX}\nTO BE BURNING");
static const u8 sBort_PkmnAlreadyHasBurn[] = _("{B_DEF_NAME_WITH_PREFIX}\nBURNING OUT");
static const u8 sBort_PkmnWasFrozen[] = _("{B_EFF_NAME_WITH_PREFIX}\nFREEZE");
static const u8 sBort_PkmnFrozenBy[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} {B_SCR_ACTIVE_ABILITY}\n{B_EFF_NAME_WITH_PREFIX} FREEZE");
static const u8 sBort_PkmnIsFrozen[] = _("{B_ATK_NAME_WITH_PREFIX}\nFROZ");
static const u8 sBort_PkmnWasDefrosted[] = _("{B_DEF_NAME_WITH_PREFIX}\nUNFROZTED");
static const u8 sBort_PkmnWasDefrosted2[] = _("{B_ATK_NAME_WITH_PREFIX}\nUNFROZTED");
static const u8 sBort_PkmnWasDefrostedBy[] = _("{B_ATK_NAME_WITH_PREFIX}\n{B_CURRENT_MOVE} UNFROZTED");
static const u8 sBort_PkmnWasParalyzed[] = _("{B_EFF_NAME_WITH_PREFIX} NUMBED\nCAN'T DO");
static const u8 sBort_PkmnWasParalyzedBy[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} {B_SCR_ACTIVE_ABILITY}\nNUMBED {B_EFF_NAME_WITH_PREFIX}\lCAN'T DO");
static const u8 sBort_PkmnIsParalyzed[] = _("{B_ATK_NAME_WITH_PREFIX}\nCANN'T MOVE");
static const u8 sBort_PkmnIsAlreadyParalyzed[] = _("{B_DEF_NAME_WITH_PREFIX}\nNUMBED OUT");
static const u8 sBort_PkmnHealedParalysis[] = _("{B_DEF_NAME_WITH_PREFIX}\nUNNUMBED");
static const u8 sBort_PkmnIsConfused[] = _("{B_ATK_NAME_WITH_PREFIX} MESSED!");
static const u8 sBort_PkmnHealedConfusion[] = _("{B_ATK_NAME_WITH_PREFIX}\nORDERED");
static const u8 sBort_PkmnWasConfused[] = _("{B_EFF_NAME_WITH_PREFIX}\nTO ORDER");
static const u8 sBort_PkmnAlreadyConfused[] = _("{B_DEF_NAME_WITH_PREFIX}\nORDERED STILL");
static const u8 sBort_ItHurtConfusion[] = _("BE CONFUSED");
static const u8 sBort_NoPPLeft[] = _("KEY TO UNLEFT!\p");
static const u8 sBory_ButNoPPLeft[] = _("BUT\nKEY TO UNLEFT!");
// static const u8 sBort_ButItFailed[] = _("BUT\nNOT DECIDED");
static const u8 sBort_ButItFailed[] = _("BUT\n{B_DEF_NAME_WITH_PREFIX} UNHEARING");
static const u8 sBort_PkmnUnaffected[] = _("BUT\n{B_DEF_NAME_WITH_PREFIX} UNHEARING");
static const u8 sBort_AttackMissed[] = _("BUT\n{B_ATK_NAME_WITH_PREFIX} MISSED");
static const u8 sBort_AvoidedDamage[] = _("{B_DEF_NAME_WITH_PREFIX}\n{B_DEF_ABILITY} DODGE");
static const u8 sBort_PkmnMoveWasDisabled[] = _("{B_DEF_NAME_WITH_PREFIX}\n{B_BUFF1} ENCLOSE");
static const u8 sBort_PkmnMoveDisabledNoMore[] = _("{B_ATK_NAME_WITH_PREFIX}\nOPENED");
static const u8 sBort_PkmnMoveIsDisabled[] = _("STUNT LOCKED\p");
static const u8 sBort_PkmnRegainedHealth[] = _("{B_DEF_NAME_WITH_PREFIX}\nCOME BACK!");

static const u8 sBort_HitXTimes[] = _("{B_BUFF1}EFFECT");
static const u8 sBort_PkmnProtectedItself[] = _("{B_DEF_NAME_WITH_PREFIX}\nDEFENSE SYSTEM");
static const u8 sBort_PkmnProtectedItself2[] = _("BUT {B_ATK_NAME_WITH_PREFIX}\nDEFENCED\lMISSED");
static const u8 sBort_PkmnRaisedSpDef[] = _("{B_ATK_PREFIX2}\nUSING {B_CURRENT_MOVE}\lTO MAKE MAGIC STRONGER");
static const u8 sBort_PkmnRaisedSpDefALittle[] = _("{B_ATK_PREFIX2}\nUSING {B_CURRENT_MOVE}\lTO MAKE MAGIC STRONK");
static const u8 sBort_PkmnRaisedDef[] = _("{B_ATK_PREFIX2}\nUSING {B_CURRENT_MOVE}\lTO MAKE ATTACKING STRONGER");
static const u8 sBort_PkmnRaisedDefALittle[] = _("{B_ATK_PREFIX2}\nUSING {B_CURRENT_MOVE}\lTO MAKE ATTACKING STRONK");
static const u8 sBort_PkmnUsedSafeguard[] = _("{B_DEF_NAME_WITH_PREFIX}\nENCLOSED BY\lCURTAIN");
static const u8 sBort_PkmnSafeguardExpired[] = _("{B_ATK_PREFIX3}\nOPENED FROM\lCURTAIN");
static const u8 sBort_PkmnDugHole[] = _("{B_ATK_NAME_WITH_PREFIX}DRILL HOLE INTO\nTHE EARTH");
static const u8 sBort_PkmnRageBuilding[] = _("{B_DEF_NAME_WITH_PREFIX} FEELING\nIS STRONGER!");
static const u8 sBort_PkmnIdentified[] = _("{B_ATK_NAME_WITH_PREFIX}\nSEE {B_DEF_NAME_WITH_PREFIX}'S\lREAL FACE");
static const u8 sBort_PkmnRaisedSpeed[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} {B_SCR_ACTIVE_ABILITY}\nMADE SPED STRONGER!");
static const u8 sBort_PkmnRaisedFirePowerWith[] = _("{B_DEF_NAME_WITH_PREFIX} {B_DEF_ABILITY}\nMADE FIRE POWER!");

static const u8 sBort_PkmnsItemCuredParalysis[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} IS {B_LAST_ITEM}\nUNNUMED");
static const u8 sBort_PkmnsItemCuredPoison[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} IS {B_LAST_ITEM}\nKILLED");
static const u8 sBort_PkmnsItemHealedBurn[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} IS {B_LAST_ITEM}\nBURNT");
static const u8 sBort_PkmnsItemDefrostedIt[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} IS {B_LAST_ITEM}\nHEAT");
static const u8 sBort_PkmnsItemWokeIt[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} IS {B_LAST_ITEM}\nWAKE");
static const u8 sBort_PkmnsItemSnappedOut[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} IS {B_LAST_ITEM}\nsnapped it out of confusion!");
static const u8 sBort_PkmnsItemCuredProblem[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} IS {B_LAST_ITEM}\nRECOVER {B_BUFF1}");
static const u8 sBort_PkmnsItemNormalizedStatus[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} IS {B_LAST_ITEM}\nJUMP NORMAL");
static const u8 sBort_PkmnsItemRestoredHealth[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} IS {B_LAST_ITEM}\nRECOVER");
static const u8 sBort_PkmnsItemRestoredPP[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} IS {B_LAST_ITEM}\nRECOVER");
static const u8 sBort_PkmnsItemRestoredStatus[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} IS {B_LAST_ITEM}\nRECOVER");
static const u8 sBort_PkmnsItemRestoredHPALittle[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} {B_LAST_ITEM}\nREVERSION");

static const u8 sBort_PkmnCutsAttackWithSlab[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} BIG CANDY\n{B_DEF_NAME_WITH_PREFIX} MAKE SAD");

static const u8 sBort_PkmnMadeItRain[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} {B_SCR_ACTIVE_ABILITY}\nRAIN ENDLES");
static const u8 sBort_StartedToRain[] = _("RAIN ENDLES");
static const u8 sBort_DownpourStarted[] = _("DOWN RAIN");
static const u8 sBort_RainContinues[] = _("RAIN ENDLES");
static const u8 sBort_DownpourContinues[] = _("DOWN RAIN");
static const u8 sBort_RainStopped[] = _("RAIN STOP");
static const u8 sBort_SandstormBrewed[] = _("SAND RAGE");
static const u8 sBort_SandstormRages[] = _("SAND RAGE");
static const u8 sBort_SandstormSubsided[] = _("SAND STOP");
static const u8 sBort_SandstormIsRaging[] = _("SAND RAGE");


static const u8 sBort_StatSharply[] = _("BAD ");
static const u8 sBort_StatRose[] = _("W??X");
static const u8 sBort_StatHarshly[] = _("VERY ");
static const u8 sBort_StatFell[] = _("WORK");

const u8 * const gElfBattleStringsTable[BATTLESTRINGS_COUNT] =
{
    [STRINGID_TRAINER1LOSETEXT - 12] = sText_Trainer1LoseText,
    [STRINGID_PKMNGAINEDEXP - 12] = sText_PkmnGainedEXP,
    [STRINGID_PKMNGREWTOLV - 12] = sText_PkmnGrewToLv,
    [STRINGID_PKMNLEARNEDMOVE - 12] = sText_PkmnLearnedMove,
    [STRINGID_TRYTOLEARNMOVE1 - 12] = sText_TryToLearnMove1,
    [STRINGID_TRYTOLEARNMOVE2 - 12] = sText_TryToLearnMove2,
    [STRINGID_TRYTOLEARNMOVE3 - 12] = sText_TryToLearnMove3,
    [STRINGID_PKMNFORGOTMOVE - 12] = sText_PkmnForgotMove,
    [STRINGID_STOPLEARNINGMOVE - 12] = sText_StopLearningMove,
    [STRINGID_DIDNOTLEARNMOVE - 12] = sText_DidNotLearnMove,
    [STRINGID_PKMNLEARNEDMOVE2 - 12] = sText_PkmnLearnedMove2,
    [STRINGID_ATTACKMISSED - 12] = sBort_AttackMissed,
    [STRINGID_PKMNPROTECTEDITSELF - 12] = sBort_PkmnProtectedItself,
    [STRINGID_STATSWONTINCREASE2 - 12] = sText_StatsWontIncrease2,
    [STRINGID_AVOIDEDDAMAGE - 12] = sBort_AvoidedDamage,
    [STRINGID_ITDOESNTAFFECT - 12] = sBort_ItDoesntAffect,
    [STRINGID_ATTACKERFAINTED - 12] = sBort_AttackerFainted,
    [STRINGID_TARGETFAINTED - 12] = sBort_TargetFainted,
    [STRINGID_PLAYERGOTMONEY - 12] = sBort_PlayerGotMoney,
    [STRINGID_PLAYERNOPKMN - 12] = sText_PlayerNoPkmn,
    [STRINGID_PLAYERWHITEOUT - 12] = sBort_PlayerWhiteout,
    [STRINGID_PLAYERWHITEOUT2 - 12] = sBort_PlayerWhiteout2,
    [STRINGID_PREVENTSESCAPE - 12] = sText_PreventsEscape,
    [STRINGID_HITXTIMES - 12] = sBort_HitXTimes,
    [STRINGID_PKMNFELLASLEEP - 12] = sBort_PkmnFellAsleep,
    [STRINGID_PKMNMADESLEEP - 12] = sBort_PkmnMadeSleep,
    [STRINGID_PKMNALREADYASLEEP - 12] = sBort_PkmnAlreadyAsleep,
    [STRINGID_PKMNALREADYASLEEP2 - 12] = sBort_PkmnAlreadyAsleep2,
    [STRINGID_PKMNWASNTAFFECTED - 12] = sBort_PkmnWasntAffected,
    [STRINGID_PKMNWASPOISONED - 12] = sBort_PkmnWasPoisoned,
    [STRINGID_PKMNPOISONEDBY - 12] = sBort_PkmnPoisonedBy,
    [STRINGID_PKMNHURTBYPOISON - 12] = sBort_PkmnHurtByPoison,
    [STRINGID_PKMNALREADYPOISONED - 12] = sBort_PkmnAlreadyPoisoned,
    [STRINGID_PKMNBADLYPOISONED - 12] = sBort_PkmnBadlyPoisoned,
    [STRINGID_PKMNENERGYDRAINED - 12] = sBort_PkmnEnergyDrained,
    [STRINGID_PKMNWASBURNED - 12] = sBort_PkmnWasBurned,
    [STRINGID_PKMNBURNEDBY - 12] = sBort_PkmnBurnedBy,
    [STRINGID_PKMNHURTBYBURN - 12] = sBort_PkmnHurtByBurn,
    [STRINGID_PKMNWASFROZEN - 12] = sBort_PkmnWasFrozen,
    [STRINGID_PKMNFROZENBY - 12] = sBort_PkmnFrozenBy,
    [STRINGID_PKMNISFROZEN - 12] = sBort_PkmnIsFrozen,
    [STRINGID_PKMNWASDEFROSTED - 12] = sBort_PkmnWasDefrosted,
    [STRINGID_PKMNWASDEFROSTED2 - 12] = sBort_PkmnWasDefrosted2,
    [STRINGID_PKMNWASDEFROSTEDBY - 12] = sBort_PkmnWasDefrostedBy,
    [STRINGID_PKMNWASPARALYZED - 12] = sBort_PkmnWasParalyzed,
    [STRINGID_PKMNWASPARALYZEDBY - 12] = sBort_PkmnWasParalyzedBy,
    [STRINGID_PKMNISPARALYZED - 12] = sBort_PkmnIsParalyzed,
    [STRINGID_PKMNISALREADYPARALYZED - 12] = sBort_PkmnIsAlreadyParalyzed,
    [STRINGID_PKMNHEALEDPARALYSIS - 12] = sBort_PkmnHealedParalysis,
    [STRINGID_PKMNDREAMEATEN - 12] = sText_PkmnDreamEaten,
    [STRINGID_STATSWONTINCREASE - 12] = sText_StatsWontIncrease,
    [STRINGID_STATSWONTDECREASE - 12] = sText_StatsWontDecrease,
    [STRINGID_TEAMSTOPPEDWORKING - 12] = sText_TeamStoppedWorking,
    [STRINGID_FOESTOPPEDWORKING - 12] = sText_FoeStoppedWorking,
    [STRINGID_PKMNISCONFUSED - 12] = sBort_PkmnIsConfused,
    [STRINGID_PKMNHEALEDCONFUSION - 12] = sBort_PkmnHealedConfusion,
    [STRINGID_PKMNWASCONFUSED - 12] = sBort_PkmnWasConfused,
    [STRINGID_PKMNALREADYCONFUSED - 12] = sBort_PkmnAlreadyConfused,
    [STRINGID_PKMNFELLINLOVE - 12] = sText_PkmnFellInLove,
    [STRINGID_PKMNINLOVE - 12] = sText_PkmnInLove,
    [STRINGID_PKMNIMMOBILIZEDBYLOVE - 12] = sText_PkmnImmobilizedByLove,
    [STRINGID_PKMNBLOWNAWAY - 12] = sText_PkmnBlownAway,
    [STRINGID_PKMNCHANGEDTYPE - 12] = sText_PkmnChangedType,
    [STRINGID_PKMNFLINCHED - 12] = sText_PkmnFlinched,
    [STRINGID_PKMNREGAINEDHEALTH - 12] = sBort_PkmnRegainedHealth,
    [STRINGID_PKMNHPFULL - 12] = sText_PkmnHPFull,
    [STRINGID_PKMNRAISEDSPDEF - 12] = sBort_PkmnRaisedSpDef,
    [STRINGID_PKMNRAISEDDEF - 12] = sBort_PkmnRaisedDef,
    [STRINGID_PKMNCOVEREDBYVEIL - 12] = sText_PkmnCoveredByVeil,
    [STRINGID_PKMNUSEDSAFEGUARD - 12] = sBort_PkmnUsedSafeguard,
    [STRINGID_PKMNSAFEGUARDEXPIRED - 12] = sBort_PkmnSafeguardExpired,
    [STRINGID_PKMNWENTTOSLEEP - 12] = sText_PkmnWentToSleep,
    [STRINGID_PKMNSLEPTHEALTHY - 12] = sText_PkmnSleptHealthy,
    [STRINGID_PKMNWHIPPEDWHIRLWIND - 12] = sText_PkmnWhippedWhirlwind,
    [STRINGID_PKMNTOOKSUNLIGHT - 12] = sText_PkmnTookSunlight,
    [STRINGID_PKMNLOWEREDHEAD - 12] = sText_PkmnLoweredHead,
    [STRINGID_PKMNISGLOWING - 12] = sText_PkmnIsGlowing,
    [STRINGID_PKMNFLEWHIGH - 12] = sText_PkmnFlewHigh,
    [STRINGID_PKMNDUGHOLE - 12] = sBort_PkmnDugHole,
    [STRINGID_PKMNSQUEEZEDBYBIND - 12] = sText_PkmnSqueezedByBind,
    [STRINGID_PKMNTRAPPEDINVORTEX - 12] = sText_PkmnTrappedInVortex,
    [STRINGID_PKMNWRAPPEDBY - 12] = sText_PkmnWrappedBy,
    [STRINGID_PKMNCLAMPED - 12] = sText_PkmnClamped,
    [STRINGID_PKMNHURTBY - 12] = sText_PkmnHurtBy,
    [STRINGID_PKMNFREEDFROM - 12] = sText_PkmnFreedFrom,
    [STRINGID_PKMNCRASHED - 12] = sText_PkmnCrashed,
    [STRINGID_PKMNSHROUDEDINMIST - 12] = gText_PkmnShroudedInMist,
    [STRINGID_PKMNPROTECTEDBYMIST - 12] = sText_PkmnProtectedByMist,
    [STRINGID_PKMNGETTINGPUMPED - 12] = gText_PkmnGettingPumped,
    [STRINGID_PKMNHITWITHRECOIL - 12] = sText_PkmnHitWithRecoil,
    [STRINGID_PKMNPROTECTEDITSELF2 - 12] = sBort_PkmnProtectedItself2,
    [STRINGID_PKMNBUFFETEDBYSANDSTORM - 12] = sText_PkmnBuffetedBySandstorm,
    [STRINGID_PKMNPELTEDBYHAIL - 12] = sText_PkmnPeltedByHail,
    [STRINGID_PKMNSEEDED - 12] = sText_PkmnSeeded,
    [STRINGID_PKMNEVADEDATTACK - 12] = sText_PkmnEvadedAttack,
    [STRINGID_PKMNSAPPEDBYLEECHSEED - 12] = sText_PkmnSappedByLeechSeed,
    [STRINGID_PKMNFASTASLEEP - 12] = sBort_PkmnFastAsleep,
    [STRINGID_PKMNWOKEUP - 12] = sBort_PkmnWokeUp,
    [STRINGID_PKMNUPROARKEPTAWAKE - 12] = sBort_PkmnUproarKeptAwake,
    [STRINGID_PKMNWOKEUPINUPROAR - 12] = sBort_PkmnWokeUpInUproar,
    [STRINGID_PKMNCAUSEDUPROAR - 12] = sText_PkmnCausedUproar,
    [STRINGID_PKMNMAKINGUPROAR - 12] = sText_PkmnMakingUproar,
    [STRINGID_PKMNCALMEDDOWN - 12] = sText_PkmnCalmedDown,
    [STRINGID_PKMNCANTSLEEPINUPROAR - 12] = sText_PkmnCantSleepInUproar,
    [STRINGID_PKMNSTOCKPILED - 12] = sText_PkmnStockpiled,
    [STRINGID_PKMNCANTSTOCKPILE - 12] = sText_PkmnCantStockpile,
    [STRINGID_PKMNCANTSLEEPINUPROAR2 - 12] = sText_PkmnCantSleepInUproar2,
    [STRINGID_UPROARKEPTPKMNAWAKE - 12] = sText_UproarKeptPkmnAwake,
    [STRINGID_PKMNSTAYEDAWAKEUSING - 12] = sText_PkmnStayedAwakeUsing,
    [STRINGID_PKMNSTORINGENERGY - 12] = sText_PkmnStoringEnergy,
    [STRINGID_PKMNUNLEASHEDENERGY - 12] = sText_PkmnUnleashedEnergy,
    [STRINGID_PKMNFATIGUECONFUSION - 12] = sText_PkmnFatigueConfusion,
    [STRINGID_PKMNPICKEDUPITEM - 12] = sText_PkmnPickedUpItem,
    [STRINGID_PKMNUNAFFECTED - 12] = sBort_PkmnUnaffected,
    [STRINGID_PKMNTRANSFORMEDINTO - 12] = sText_PkmnTransformedInto,
    [STRINGID_PKMNMADESUBSTITUTE - 12] = sText_PkmnMadeSubstitute,
    [STRINGID_PKMNHASSUBSTITUTE - 12] = sText_PkmnHasSubstitute,
    [STRINGID_SUBSTITUTEDAMAGED - 12] = sText_SubstituteDamaged,
    [STRINGID_PKMNSUBSTITUTEFADED - 12] = sText_PkmnSubstituteFaded,
    [STRINGID_PKMNMUSTRECHARGE - 12] = sText_PkmnMustRecharge,
    [STRINGID_PKMNRAGEBUILDING - 12] = sBort_PkmnRageBuilding,
    [STRINGID_PKMNMOVEWASDISABLED - 12] = sBort_PkmnMoveWasDisabled,
    [STRINGID_PKMNMOVEISDISABLED - 12] = sBort_PkmnMoveIsDisabled,
    [STRINGID_PKMNMOVEDISABLEDNOMORE - 12] = sBort_PkmnMoveDisabledNoMore,
    [STRINGID_PKMNGOTENCORE - 12] = sText_PkmnGotEncore,
    [STRINGID_PKMNENCOREENDED - 12] = sText_PkmnEncoreEnded,
    [STRINGID_PKMNTOOKAIM - 12] = sText_PkmnTookAim,
    [STRINGID_PKMNSKETCHEDMOVE - 12] = sText_PkmnSketchedMove,
    [STRINGID_PKMNTRYINGTOTAKEFOE - 12] = sText_PkmnTryingToTakeFoe,
    [STRINGID_PKMNTOOKFOE - 12] = sText_PkmnTookFoe,
    [STRINGID_PKMNREDUCEDPP - 12] = sText_PkmnReducedPP,
    [STRINGID_PKMNSTOLEITEM - 12] = sText_PkmnStoleItem,
    [STRINGID_TARGETCANTESCAPENOW - 12] = sText_TargetCantEscapeNow,
    [STRINGID_PKMNFELLINTONIGHTMARE - 12] = sText_PkmnFellIntoNightmare,
    [STRINGID_PKMNLOCKEDINNIGHTMARE - 12] = sText_PkmnLockedInNightmare,
    [STRINGID_PKMNLAIDCURSE - 12] = sText_PkmnLaidCurse,
    [STRINGID_PKMNAFFLICTEDBYCURSE - 12] = sText_PkmnAfflictedByCurse,
    [STRINGID_SPIKESSCATTERED - 12] = sText_SpikesScattered,
    [STRINGID_PKMNHURTBYSPIKES - 12] = sText_PkmnHurtBySpikes,
    [STRINGID_PKMNIDENTIFIED - 12] = sBort_PkmnIdentified,
    [STRINGID_PKMNPERISHCOUNTFELL - 12] = sText_PkmnPerishCountFell,
    [STRINGID_PKMNBRACEDITSELF - 12] = sText_PkmnBracedItself,
    [STRINGID_PKMNENDUREDHIT - 12] = sText_PkmnEnduredHit,
    [STRINGID_MAGNITUDESTRENGTH - 12] = sText_MagnitudeStrength,
    [STRINGID_PKMNCUTHPMAXEDATTACK - 12] = sText_PkmnCutHPMaxedAttack,
    [STRINGID_PKMNCOPIEDSTATCHANGES - 12] = sText_PkmnCopiedStatChanges,
    [STRINGID_PKMNGOTFREE - 12] = sText_PkmnGotFree,
    [STRINGID_PKMNSHEDLEECHSEED - 12] = sText_PkmnShedLeechSeed,
    [STRINGID_PKMNBLEWAWAYSPIKES - 12] = sText_PkmnBlewAwaySpikes,
    [STRINGID_PKMNFLEDFROMBATTLE - 12] = sText_PkmnFledFromBattle,
    [STRINGID_PKMNFORESAWATTACK - 12] = sText_PkmnForesawAttack,
    [STRINGID_PKMNTOOKATTACK - 12] = sText_PkmnTookAttack,
    [STRINGID_PKMNATTACK - 12] = sText_PkmnAttack,
    [STRINGID_PKMNCENTERATTENTION - 12] = sText_PkmnCenterAttention,
    [STRINGID_PKMNCHARGINGPOWER - 12] = sText_PkmnChargingPower,
    [STRINGID_NATUREPOWERTURNEDINTO - 12] = sText_NaturePowerTurnedInto,
    [STRINGID_PKMNSTATUSNORMAL - 12] = sText_PkmnStatusNormal,
    [STRINGID_PKMNHASNOMOVESLEFT - 12] = sText_PkmnHasNoMovesLeft,
    [STRINGID_PKMNSUBJECTEDTOTORMENT - 12] = sText_PkmnSubjectedToTorment,
    [STRINGID_PKMNCANTUSEMOVETORMENT - 12] = sText_PkmnCantUseMoveTorment,
    [STRINGID_PKMNTIGHTENINGFOCUS - 12] = sText_PkmnTighteningFocus,
    [STRINGID_PKMNFELLFORTAUNT - 12] = sText_PkmnFellForTaunt,
    [STRINGID_PKMNCANTUSEMOVETAUNT - 12] = sText_PkmnCantUseMoveTaunt,
    [STRINGID_PKMNREADYTOHELP - 12] = sText_PkmnReadyToHelp,
    [STRINGID_PKMNSWITCHEDITEMS - 12] = sText_PkmnSwitchedItems,
    [STRINGID_PKMNCOPIEDFOE - 12] = sText_PkmnCopiedFoe,
    [STRINGID_PKMNMADEWISH - 12] = sText_PkmnMadeWish,
    [STRINGID_PKMNWISHCAMETRUE - 12] = sText_PkmnWishCameTrue,
    [STRINGID_PKMNPLANTEDROOTS - 12] = sText_PkmnPlantedRoots,
    [STRINGID_PKMNABSORBEDNUTRIENTS - 12] = sText_PkmnAbsorbedNutrients,
    [STRINGID_PKMNANCHOREDITSELF - 12] = sText_PkmnAnchoredItself,
    [STRINGID_PKMNWASMADEDROWSY - 12] = sText_PkmnWasMadeDrowsy,
    [STRINGID_PKMNKNOCKEDOFF - 12] = sText_PkmnKnockedOff,
    [STRINGID_PKMNSWAPPEDABILITIES - 12] = sText_PkmnSwappedAbilities,
    [STRINGID_PKMNSEALEDOPPONENTMOVE - 12] = sText_PkmnSealedOpponentMove,
    [STRINGID_PKMNCANTUSEMOVESEALED - 12] = sText_PkmnCantUseMoveSealed,
    [STRINGID_PKMNWANTSGRUDGE - 12] = sText_PkmnWantsGrudge,
    [STRINGID_PKMNLOSTPPGRUDGE - 12] = sText_PkmnLostPPGrudge,
    [STRINGID_PKMNSHROUDEDITSELF - 12] = sText_PkmnShroudedItself,
    [STRINGID_PKMNMOVEBOUNCED - 12] = sText_PkmnMoveBounced,
    [STRINGID_PKMNWAITSFORTARGET - 12] = sText_PkmnWaitsForTarget,
    [STRINGID_PKMNSNATCHEDMOVE - 12] = sText_PkmnSnatchedMove,
    [STRINGID_PKMNMADEITRAIN - 12] = sBort_PkmnMadeItRain,
    [STRINGID_PKMNRAISEDSPEED - 12] = sBort_PkmnRaisedSpeed,
    [STRINGID_PKMNPROTECTEDBY - 12] = sText_PkmnProtectedBy,
    [STRINGID_PKMNPREVENTSUSAGE - 12] = sText_PkmnPreventsUsage,
    [STRINGID_PKMNRESTOREDHPUSING - 12] = sText_PkmnRestoredHPUsing,
    [STRINGID_PKMNCHANGEDTYPEWITH - 12] = sText_PkmnChangedTypeWith,
    [STRINGID_PKMNPREVENTSPARALYSISWITH - 12] = sText_PkmnPreventsParalysisWith,
    [STRINGID_PKMNPREVENTSROMANCEWITH - 12] = sText_PkmnPreventsRomanceWith,
    [STRINGID_PKMNPREVENTSPOISONINGWITH - 12] = sText_PkmnPreventsPoisoningWith,
    [STRINGID_PKMNPREVENTSCONFUSIONWITH - 12] = sText_PkmnPreventsConfusionWith,
    [STRINGID_PKMNRAISEDFIREPOWERWITH - 12] = sBort_PkmnRaisedFirePowerWith,
    [STRINGID_PKMNANCHORSITSELFWITH - 12] = sText_PkmnAnchorsItselfWith,
    [STRINGID_PKMNCUTSATTACKWITH - 12] = sText_PkmnCutsAttackWith,
    [STRINGID_INTIMIDATESLAB - 12] = sBort_PkmnCutsAttackWithSlab,
    [STRINGID_PKMNPREVENTSSTATLOSSWITH - 12] = sText_PkmnPreventsStatLossWith,
    [STRINGID_PKMNHURTSWITH - 12] = sText_PkmnHurtsWith,
    [STRINGID_PKMNTRACED - 12] = sText_PkmnTraced,
    [STRINGID_STATSHARPLY - 12] = sBort_StatSharply,
    [STRINGID_STATROSE - 12] = sBort_StatRose,
    [STRINGID_STATHARSHLY - 12] = sBort_StatHarshly,
    [STRINGID_STATFELL - 12] = sBort_StatFell,
    [STRINGID_PKMNSSTATCHANGED - 12] = sText_PkmnsStatChanged,
    [STRINGID_PKMNSSTATCHANGED2 - 12] = gText_PkmnsStatChanged2,
    [STRINGID_PKMNSSTATCHANGED3 - 12] = sText_PkmnsStatChanged3,
    [STRINGID_PKMNSSTATCHANGED4 - 12] = sText_PkmnsStatChanged4,
    [STRINGID_CRITICALHIT - 12] = sBort_CriticalHit,
    [STRINGID_ONEHITKO - 12] = sText_OneHitKO,
    [STRINGID_123POOF - 12] = sText_123Poof,
    [STRINGID_ANDELLIPSIS - 12] = sText_AndEllipsis,
    [STRINGID_NOTVERYEFFECTIVE - 12] = sBort_NotVeryEffective,
    [STRINGID_SUPEREFFECTIVE - 12] = sBort_SuperEffective,
    [STRINGID_GOTAWAYSAFELY - 12] = sBort_GotAwaySafely,
    [STRINGID_WILDPKMNFLED - 12] = sText_WildPkmnFled,
    [STRINGID_NORUNNINGFROMTRAINERS - 12] = sText_NoRunningFromTrainers,
    [STRINGID_CANTESCAPE - 12] = sBort_CantEscape,
    [STRINGID_DONTLEAVEBIRCH - 12] = sText_DontLeaveBirch,
    [STRINGID_BUTNOTHINGHAPPENED - 12] = sText_ButNothingHappened,
    [STRINGID_BUTITFAILED - 12] = sBort_ButItFailed,
    [STRINGID_ITHURTCONFUSION - 12] = sBort_ItHurtConfusion,
    [STRINGID_MIRRORMOVEFAILED - 12] = sText_MirrorMoveFailed,
    [STRINGID_STARTEDTORAIN - 12] = sBort_StartedToRain,
    [STRINGID_DOWNPOURSTARTED - 12] = sBort_DownpourStarted,
    [STRINGID_RAINCONTINUES - 12] = sBort_RainContinues,
    [STRINGID_DOWNPOURCONTINUES - 12] = sBort_DownpourContinues,
    [STRINGID_RAINSTOPPED - 12] = sBort_RainStopped,
    [STRINGID_SANDSTORMBREWED - 12] = sBort_SandstormBrewed,
    [STRINGID_SANDSTORMRAGES - 12] = sBort_SandstormRages,
    [STRINGID_SANDSTORMSUBSIDED - 12] = sBort_SandstormSubsided,
    [STRINGID_SUNLIGHTGOTBRIGHT - 12] = sText_SunlightGotBright,
    [STRINGID_SUNLIGHTSTRONG - 12] = sText_SunlightStrong,
    [STRINGID_SUNLIGHTFADED - 12] = sText_SunlightFaded,
    [STRINGID_STARTEDHAIL - 12] = sText_StartedHail,
    [STRINGID_HAILCONTINUES - 12] = sText_HailContinues,
    [STRINGID_HAILSTOPPED - 12] = sText_HailStopped,
    [STRINGID_FAILEDTOSPITUP - 12] = sText_FailedToSpitUp,
    [STRINGID_FAILEDTOSWALLOW - 12] = sText_FailedToSwallow,
    [STRINGID_WINDBECAMEHEATWAVE - 12] = sText_WindBecameHeatWave,
    [STRINGID_STATCHANGESGONE - 12] = sText_StatChangesGone,
    [STRINGID_COINSSCATTERED - 12] = sText_CoinsScattered,
    [STRINGID_TOOWEAKFORSUBSTITUTE - 12] = sText_TooWeakForSubstitute,
    [STRINGID_SHAREDPAIN - 12] = sText_SharedPain,
    [STRINGID_BELLCHIMED - 12] = sText_BellChimed,
    [STRINGID_FAINTINTHREE - 12] = sText_FaintInThree,
    [STRINGID_NOPPLEFT - 12] = sBort_NoPPLeft,
    [STRINGID_BUTNOPPLEFT - 12] = sBory_ButNoPPLeft,
    [STRINGID_PLAYERUSEDITEM - 12] = sBort_PlayerUsedItem,
    [STRINGID_WALLYUSEDITEM - 12] = sText_WallyUsedItem,
    [STRINGID_TRAINERBLOCKEDBALL - 12] = sBort_TrainerBlockedBall,
    [STRINGID_DONTBEATHIEF - 12] = sBort_DontBeAThief,
    [STRINGID_ITDODGEDBALL - 12] = sText_ItDodgedBall,
    [STRINGID_YOUMISSEDPKMN - 12] = sBort_YouMissedPkmn,
    [STRINGID_PKMNBROKEFREE - 12] = sBort_PkmnBrokeFree,
    [STRINGID_ITAPPEAREDCAUGHT - 12] = sBort_ItAppearedCaught,
    [STRINGID_AARGHALMOSTHADIT - 12] = sBort_AarghAlmostHadIt,
    [STRINGID_SHOOTSOCLOSE - 12] = sBort_ShootSoClose,
    [STRINGID_GOTCHAPKMNCAUGHT - 12] = sBort_GotchaPkmnCaught,
    [STRINGID_GOTCHAPKMNCAUGHT2 - 12] = sBort_GotchaPkmnCaught2,
    [STRINGID_GIVENICKNAMECAPTURED - 12] = sText_GiveNicknameCaptured,
    [STRINGID_PKMNSENTTOPC - 12] = sText_PkmnSentToPC,
    [STRINGID_PKMNDATAADDEDTODEX - 12] = sText_PkmnDataAddedToDex,
    [STRINGID_ITISRAINING - 12] = sText_ItIsRaining,
    [STRINGID_SANDSTORMISRAGING - 12] = sBort_SandstormIsRaging,
    [STRINGID_CANTESCAPE2 - 12] = sBort_CantEscape,
    [STRINGID_PKMNIGNORESASLEEP - 12] = sText_PkmnIgnoresAsleep,
    [STRINGID_PKMNIGNOREDORDERS - 12] = sText_PkmnIgnoredOrders,
    [STRINGID_PKMNBEGANTONAP - 12] = sText_PkmnBeganToNap,
    [STRINGID_PKMNLOAFING - 12] = sText_PkmnLoafing,
    [STRINGID_PKMNWONTOBEY - 12] = sText_PkmnWontObey,
    [STRINGID_PKMNTURNEDAWAY - 12] = sText_PkmnTurnedAway,
    [STRINGID_PKMNPRETENDNOTNOTICE - 12] = sText_PkmnPretendNotNotice,
    [STRINGID_ENEMYABOUTTOSWITCHPKMN - 12] = sBort_EnemyAboutToSwitchPkmn,
    [STRINGID_CREPTCLOSER - 12] = sText_CreptCloser,
    [STRINGID_CANTGETCLOSER - 12] = sText_CantGetCloser,
    [STRINGID_PKMNWATCHINGCAREFULLY - 12] = sText_PkmnWatchingCarefully,
    [STRINGID_PKMNCURIOUSABOUTX - 12] = sText_PkmnCuriousAboutX,
    [STRINGID_PKMNENTHRALLEDBYX - 12] = sText_PkmnEnthralledByX,
    [STRINGID_PKMNIGNOREDX - 12] = sText_PkmnIgnoredX,
    [STRINGID_THREWPOKEBLOCKATPKMN - 12] = sText_ThrewPokeblockAtPkmn,
    [STRINGID_OUTOFSAFARIBALLS - 12] = sText_OutOfSafariBalls,
    [STRINGID_PKMNSITEMCUREDPARALYSIS - 12] = sBort_PkmnsItemCuredParalysis,
    [STRINGID_PKMNSITEMCUREDPOISON - 12] = sBort_PkmnsItemCuredPoison,
    [STRINGID_PKMNSITEMHEALEDBURN - 12] = sBort_PkmnsItemHealedBurn,
    [STRINGID_PKMNSITEMDEFROSTEDIT - 12] = sBort_PkmnsItemDefrostedIt,
    [STRINGID_PKMNSITEMWOKEIT - 12] = sBort_PkmnsItemWokeIt,
    [STRINGID_PKMNSITEMSNAPPEDOUT - 12] = sBort_PkmnsItemSnappedOut,
    [STRINGID_PKMNSITEMCUREDPROBLEM - 12] = sBort_PkmnsItemCuredProblem,
    [STRINGID_PKMNSITEMRESTOREDHEALTH - 12] = sBort_PkmnsItemRestoredHealth,
    [STRINGID_PKMNSITEMRESTOREDPP - 12] = sBort_PkmnsItemRestoredPP,
    [STRINGID_PKMNSITEMRESTOREDSTATUS - 12] = sBort_PkmnsItemRestoredStatus,
    [STRINGID_PKMNSITEMRESTOREDHPALITTLE - 12] = sBort_PkmnsItemRestoredHPALittle,
    [STRINGID_ITEMALLOWSONLYYMOVE - 12] = sText_ItemAllowsOnlyYMove,
    [STRINGID_PKMNHUNGONWITHX - 12] = sText_PkmnHungOnWithX,
    [STRINGID_EMPTYSTRING3 - 12] = gText_EmptyString3,
    [STRINGID_PKMNSXPREVENTSBURNS - 12] = sText_PkmnsXPreventsBurns,
    [STRINGID_PKMNSXBLOCKSY - 12] = sText_PkmnsXBlocksY,
    [STRINGID_PKMNSXRESTOREDHPALITTLE2 - 12] = sText_PkmnsXRestoredHPALittle2,
    [STRINGID_PKMNSXWHIPPEDUPSANDSTORM - 12] = sText_PkmnsXWhippedUpSandstorm,
    [STRINGID_PKMNSXPREVENTSYLOSS - 12] = sText_PkmnsXPreventsYLoss,
    [STRINGID_PKMNSXINFATUATEDY - 12] = sText_PkmnsXInfatuatedY,
    [STRINGID_PKMNSXMADEYINEFFECTIVE - 12] = sText_PkmnsXMadeYIneffective,
    [STRINGID_PKMNSXCUREDYPROBLEM - 12] = sText_PkmnsXCuredYProblem,
    [STRINGID_ITSUCKEDLIQUIDOOZE - 12] = sText_ItSuckedLiquidOoze,
    [STRINGID_PKMNTRANSFORMED - 12] = sText_PkmnTransformed,
    [STRINGID_ELECTRICITYWEAKENED - 12] = sText_ElectricityWeakened,
    [STRINGID_FIREWEAKENED - 12] = sText_FireWeakened,
    [STRINGID_PKMNHIDUNDERWATER - 12] = sText_PkmnHidUnderwater,
    [STRINGID_PKMNSPRANGUP - 12] = sText_PkmnSprangUp,
    [STRINGID_HMMOVESCANTBEFORGOTTEN - 12] = sText_HMMovesCantBeForgotten,
    [STRINGID_XFOUNDONEY - 12] = sText_XFoundOneY,
    [STRINGID_PLAYERDEFEATEDTRAINER1 - 12] = sBort_PlayerDefeatedTrainer,
    [STRINGID_SOOTHINGAROMA - 12] = sText_SoothingAroma,
    [STRINGID_ITEMSCANTBEUSEDNOW - 12] = sText_ItemsCantBeUsedNow,
    [STRINGID_FORXCOMMAYZ - 12] = sText_ForXCommaYZ,
    [STRINGID_USINGXTHEYOFZN - 12] = sText_UsingXTheYOfZN,
    [STRINGID_PKMNUSEDXTOGETPUMPED - 12] = sText_PkmnUsedXToGetPumped,
    [STRINGID_PKMNSXMADEYUSELESS - 12] = sText_PkmnsXMadeYUseless,
    [STRINGID_PKMNTRAPPEDBYSANDTOMB - 12] = sText_PkmnTrappedBySandTomb,
    [STRINGID_EMPTYSTRING4 - 12] = sText_EmptyString4,
    [STRINGID_ABOOSTED - 12] = sText_ABoosted,
    [STRINGID_PKMNSXINTENSIFIEDSUN - 12] = sText_PkmnsXIntensifiedSun,
    [STRINGID_PKMNMAKESGROUNDMISS - 12] = sText_PkmnMakesGroundMiss,
    [STRINGID_YOUTHROWABALLNOWRIGHT - 12] = sText_YouThrowABallNowRight,
    [STRINGID_PKMNSXTOOKATTACK - 12] = sText_PkmnsXTookAttack,
    [STRINGID_PKMNCHOSEXASDESTINY - 12] = sText_PkmnChoseXAsDestiny,
    [STRINGID_PKMNLOSTFOCUS - 12] = sText_PkmnLostFocus,
    [STRINGID_USENEXTPKMN - 12] = sBort_UseNextPkmn,
    [STRINGID_PKMNFLEDUSINGSNICKERS - 12] = sText_PkmnFledUsingSnickers,
    [STRINGID_PKMNFLEDUSINGITS - 12] = sText_PkmnFledUsingIts,
    [STRINGID_PKMNFLEDUSING - 12] = sText_PkmnFledUsing,
    [STRINGID_PKMNWASDRAGGEDOUT - 12] = sText_PkmnWasDraggedOut,
    [STRINGID_PREVENTEDFROMWORKING - 12] = sText_PreventedFromWorking,
    [STRINGID_PKMNSITEMNORMALIZEDSTATUS - 12] = sBort_PkmnsItemNormalizedStatus,
    [STRINGID_TRAINER1USEDITEM - 12] = sText_Trainer1UsedItem,
    [STRINGID_BOXISFULL - 12] = sText_BoxIsFull,
    [STRINGID_PKMNAVOIDEDATTACK - 12] = sText_PkmnAvoidedAttack,
    [STRINGID_PKMNSXMADEITINEFFECTIVE - 12] = sText_PkmnsXMadeItIneffective,
    [STRINGID_PKMNSXPREVENTSFLINCHING - 12] = sText_PkmnsXPreventsFlinching,
    [STRINGID_PKMNALREADYHASBURN - 12] = sText_PkmnAlreadyHasBurn,
    [STRINGID_STATSWONTDECREASE2 - 12] = sText_StatsWontDecrease2,
    [STRINGID_PKMNSXBLOCKSY2 - 12] = sText_PkmnsXBlocksY2,
    [STRINGID_PKMNSXWOREOFF - 12] = sText_PkmnsXWoreOff,
    [STRINGID_PKMNRAISEDDEFALITTLE - 12] = sBort_PkmnRaisedDefALittle,
    [STRINGID_PKMNRAISEDSPDEFALITTLE - 12] = sBort_PkmnRaisedSpDefALittle,
    [STRINGID_THEWALLSHATTERED - 12] = sText_TheWallShattered,
    [STRINGID_PKMNSXPREVENTSYSZ - 12] = sText_PkmnsXPreventsYsZ,
    [STRINGID_PKMNSXCUREDITSYPROBLEM - 12] = sText_PkmnsXCuredItsYProblem,
    [STRINGID_ATTACKERCANTESCAPE - 12] = sBort_AttackerCantEscape,
    [STRINGID_PKMNOBTAINEDX - 12] = sText_PkmnObtainedX,
    [STRINGID_PKMNOBTAINEDX2 - 12] = sText_PkmnObtainedX2,
    [STRINGID_PKMNOBTAINEDXYOBTAINEDZ - 12] = sText_PkmnObtainedXYObtainedZ,
    [STRINGID_BUTNOEFFECT - 12] = sText_ButNoEffect,
    [STRINGID_PKMNSXHADNOEFFECTONY - 12] = sText_PkmnsXHadNoEffectOnY,
    [STRINGID_TWOENEMIESDEFEATED - 12] = sText_TwoInGameTrainersDefeated,
    [STRINGID_TRAINER2LOSETEXT - 12] = sText_Trainer2LoseText,
    [STRINGID_PKMNINCAPABLEOFPOWER - 12] = sText_PkmnIncapableOfPower,
    [STRINGID_GLINTAPPEARSINEYE - 12] = sText_GlintAppearsInEye,
    [STRINGID_PKMNGETTINGINTOPOSITION - 12] = sText_PkmnGettingIntoPosition,
    [STRINGID_PKMNBEGANGROWLINGDEEPLY - 12] = sText_PkmnBeganGrowlingDeeply,
    [STRINGID_PKMNEAGERFORMORE - 12] = sText_PkmnEagerForMore,
    [STRINGID_DEFEATEDOPPONENTBYREFEREE - 12] = sText_DefeatedOpponentByReferee,
    [STRINGID_LOSTTOOPPONENTBYREFEREE - 12] = sText_LostToOpponentByReferee,
    [STRINGID_TIEDOPPONENTBYREFEREE - 12] = sText_TiedOpponentByReferee,
    [STRINGID_QUESTIONFORFEITMATCH - 12] = sText_QuestionForfeitMatch,
    [STRINGID_FORFEITEDMATCH - 12] = sText_ForfeitedMatch,
    [STRINGID_PKMNTRANSFERREDSOMEONESPC - 12] = gText_PkmnTransferredSomeonesPC,
    [STRINGID_PKMNTRANSFERREDLANETTESPC - 12] = gText_PkmnTransferredLanettesPC,
    [STRINGID_PKMNBOXSOMEONESPCFULL - 12] = gText_PkmnBoxSomeonesPCFull,
    [STRINGID_PKMNBOXLANETTESPCFULL - 12] = gText_PkmnBoxLanettesPCFull,
    [STRINGID_TRAINER1WINTEXT - 12] = sText_Trainer1WinText,
    [STRINGID_TRAINER2WINTEXT - 12] = sText_Trainer2WinText,
    [STRINGID_POKEMONATECANDY - 12] = sText_OpponentAteCandy,
};

// Below are copies from the battle_messages.c file, with their explainations on how they
// were used in Japanese. Since Viet Crystal was a poor translation of the japanese, we're
// going to use these functions to their original effect to poorly translate the line.
static const u8 sBort_SpaceIs[] = _(" IS");
static const u8 sBort_ApostropheS[] = _("");//EN'S");

static const u8 sBort_ExclamationMark[] = _("!");
static const u8 sBort_ExclamationMark2[] = _(" USED!");
static const u8 sBort_ExclamationMark3[] = _("AH!");
static const u8 sBort_ExclamationMark4[] = _(" AH!");
static const u8 sBort_ExclamationMark5[] = _(" AH!");

static const u8 sBort_AttackerUsedX[] = _("{B_BUFF1}{B_ATK_NAME_WITH_PREFIX}\n{B_BUFF2}");

// Loads one of two text strings into the provided buffer. This is functionally
// unused, since the value loaded into the buffer is not read; it loaded one of
// two particles (either "は" or "の") which works in tandem with ChooseTypeOfMoveUsedString
// below to effect changes in the meaning of the line.
static void ChooseMoveUsedParticle_BORT(u8* textBuff)
{
    s32 counter = 0;
    u32 i = 0;

    while (counter != MAX_MON_MOVES)
    {
        if (sGrammarMoveUsedTable[i] == 0)
            counter++;
        if (sGrammarMoveUsedTable[i++] == gBattleMsgDataPtr->currentMove)
            break;
    }

    if (counter >= 0)
    {
        if (counter <= 2)
            StringCopy(textBuff, sBort_SpaceIs); // is
        else if (counter <= MAX_MON_MOVES)
            StringCopy(textBuff, sBort_ApostropheS); // 's
    }
}

// Appends "!" to the text buffer `dst`. In the original Japanese this looked
// into the table of moves at sGrammarMoveUsedTable and varied the line accordingly.
//
// sText_ExclamationMark was a plain "!", used for any attack not on the list.
// It resulted in the translation "<NAME>'s <ATTACK>!".
//
// sText_ExclamationMark2 was "を つかった！". This resulted in the translation
// "<NAME> used <ATTACK>!", which was used for all attacks in English.
//
// sText_ExclamationMark3 was "した！". This was used for those moves whose
// names were verbs, such as Recover, and resulted in translations like "<NAME>
// recovered itself!".
//
// sText_ExclamationMark4 was "を した！" This resulted in a translation of
// "<NAME> did an <ATTACK>!".
//
// sText_ExclamationMark5 was " こうげき！" This resulted in a translation of
// "<NAME>'s <ATTACK> attack!".
static void ChooseTypeOfMoveUsedString_BORT(u8* dst)
{
    s32 counter = 0;
    s32 i = 0;

    while (*dst != EOS)
        dst++;

    while (counter != MAX_MON_MOVES)
    {
        if (sGrammarMoveUsedTable[i] == MOVE_NONE)
            counter++;
        if (sGrammarMoveUsedTable[i++] == gBattleMsgDataPtr->currentMove)
            break;
    }

    switch (counter)
    {
    case 0:
        StringCopy(dst, sBort_ExclamationMark);
        break;
    case 1:
        StringCopy(dst, sBort_ExclamationMark2);
        break;
    case 2:
        StringCopy(dst, sBort_ExclamationMark3);
        break;
    case 3:
        StringCopy(dst, sBort_ExclamationMark4);
        break;
    case 4:
        StringCopy(dst, sBort_ExclamationMark5);
        break;
    }
}




void BufferStringBattle_BORT(u16 stringID)
{
    s32 i;
    const u8 *stringPtr = NULL;
    
    switch (stringID)
    {
    case STRINGID_INTROMSG: // first battle msg
        if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)
        {
            if (gBattleTypeFlags & BATTLE_TYPE_INGAME_PARTNER)
                stringPtr = sBort_TwoTrainersWantToBattle;
            else if (gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS)
                stringPtr = sBort_TwoTrainersWantToBattle;
            else
                stringPtr = sBort_Trainer1WantsToBattle;
        }
        else
        {
            if (gBattleTypeFlags & BATTLE_TYPE_LEGENDARY)
                stringPtr = sBort_WildPkmnAppeared2;
            else if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE) // interesting, looks like they had something planned for wild double battles
                stringPtr = sBort_TwoWildPkmnAppeared;
            else if (gBattleTypeFlags & BATTLE_TYPE_WALLY_TUTORIAL)
                stringPtr = sBort_WildPkmnAppearedPause;
            else
                stringPtr = sBort_WildPkmnAppeared;
        }
        break;
    case STRINGID_INTROSENDOUT: // poke first send-out
        if (GetBattlerSide(gActiveBattler) == B_SIDE_PLAYER)
        {
            if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
                stringPtr = sBort_GoTwoPkmn;
            else
                stringPtr = sBort_GoPkmn;
        }
        else
        {
            if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
            {
                if (gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS)
                    stringPtr = sBort_TwoTrainersSentPkmn;
                else
                    stringPtr = sBort_Trainer1SentOutTwoPkmn;
            }
            else
            {
                stringPtr = sBort_Trainer1SentOutPkmn;
            }
        }
        break;
    case STRINGID_RETURNMON: // sending poke to ball msg
        if (GetBattlerSide(gActiveBattler) == B_SIDE_PLAYER)
        {
            if (*(&gBattleStruct->hpScale) == 0)
                stringPtr = sBort_PkmnThatsEnough;
            else if (*(&gBattleStruct->hpScale) == 1 || gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
                stringPtr = sBort_PkmnComeBack;
            else if (*(&gBattleStruct->hpScale) == 2)
                stringPtr = sBort_PkmnOkComeBack;
            else
                stringPtr = sBort_PkmnGoodComeBack;
        }
        else
        {
            if (gTrainerBattleOpponent_A == TRAINER_LINK_OPPONENT || gBattleTypeFlags & BATTLE_TYPE_x2000000)
            {
                if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
                    stringPtr = sText_LinkTrainer2WithdrewPkmn;
                else
                    stringPtr = sText_LinkTrainer1WithdrewPkmn;
            }
            else
            {
                stringPtr = sText_Trainer1WithdrewPkmn;
            }
        }
        break;
    case STRINGID_SWITCHINMON: // switch-in msg
        if (GetBattlerSide(gBattleScripting.battler) == B_SIDE_PLAYER)
        {
            if (*(&gBattleStruct->hpScale) == 0 || gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
                stringPtr = sBort_GoPkmn;
            else if (*(&gBattleStruct->hpScale) == 1)
                stringPtr = sBort_DoItPkmn;
            else if (*(&gBattleStruct->hpScale) == 2)
                stringPtr = sBort_GoForItPkmn;
            else
                stringPtr = sBort_YourFoesWeakGetEmPkmn;
        }
        else
        {
            if (gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS)
            {
                if (gBattleScripting.battler == 1)
                    stringPtr = sBort_Trainer1SentOutPkmn2;
                else
                    stringPtr = sBort_Trainer2SentOutPkmn;
            }
            else
            {
                stringPtr = sBort_Trainer1SentOutPkmn2;
            }
        }
        break;
    case STRINGID_USEDMOVE: // pokemon used a move msg
        ChooseMoveUsedParticle_BORT(gBattleTextBuff1); // buff1 doesn't appear in the string, leftover from japanese move names

        if (gBattleMsgDataPtr->currentMove >= MOVES_COUNT)
            StringCopy(gBattleTextBuff2, sATypeMove_Table[*(&gBattleStruct->stringMoveType)]);
        else
            StringCopy(gBattleTextBuff2, gMoveNames[gBattleMsgDataPtr->currentMove]);

        ChooseTypeOfMoveUsedString_BORT(gBattleTextBuff2);
        stringPtr = sBort_AttackerUsedX;
        break;
    case STRINGID_BATTLEEND: // battle end
        if (gBattleTextBuff1[0] & B_OUTCOME_LINK_BATTLE_RAN)
        {
            gBattleTextBuff1[0] &= ~(B_OUTCOME_LINK_BATTLE_RAN);
            if (GetBattlerSide(gActiveBattler) == B_SIDE_OPPONENT && gBattleTextBuff1[0] != B_OUTCOME_DREW)
                gBattleTextBuff1[0] ^= (B_OUTCOME_LOST | B_OUTCOME_WON);

            if (gBattleTextBuff1[0] == B_OUTCOME_LOST || gBattleTextBuff1[0] == B_OUTCOME_DREW)
                stringPtr = sBort_GotAwaySafely;
            else if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
                stringPtr = sBort_TwoWildFled;
            else
                stringPtr = sBort_WildFled;
        }
        else
        {
            if (GetBattlerSide(gActiveBattler) == B_SIDE_OPPONENT && gBattleTextBuff1[0] != B_OUTCOME_DREW)
                gBattleTextBuff1[0] ^= (B_OUTCOME_LOST | B_OUTCOME_WON);

            if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
            {
                switch (gBattleTextBuff1[0])
                {
                case B_OUTCOME_WON:
                    if (gBattleTypeFlags & BATTLE_TYPE_x800000)
                        stringPtr = sText_TwoInGameTrainersDefeated;
                    else
                        stringPtr = sText_TwoLinkTrainersDefeated;
                    break;
                case B_OUTCOME_LOST:
                    stringPtr = sText_PlayerLostToTwo;
                    break;
                case B_OUTCOME_DREW:
                    stringPtr = sText_PlayerBattledToDrawVsTwo;
                    break;
                }
            }
            else if (gTrainerBattleOpponent_A == TRAINER_OPPONENT_C00)
            {
                switch (gBattleTextBuff1[0])
                {
                case B_OUTCOME_WON:
                    stringPtr = sBort_PlayerDefeatedTrainer;
                    break;
                case B_OUTCOME_LOST:
                    stringPtr = sText_PlayerLostAgainstTrainer1;
                    break;
                case B_OUTCOME_DREW:
                    stringPtr = sText_PlayerBattledToDrawTrainer1;
                    break;
                }
            }
            else
            {
                switch (gBattleTextBuff1[0])
                {
                case B_OUTCOME_WON:
                    stringPtr = sBort_PlayerDefeatedLinkTrainer;
                    break;
                case B_OUTCOME_LOST:
                    stringPtr = sText_PlayerLostAgainstLinkTrainer;
                    break;
                case B_OUTCOME_DREW:
                    stringPtr = sText_PlayerBattledToDrawLinkTrainer;
                    break;
                }
            }
        }
        break;
    default: // load a string from the table
        if (stringID >= BATTLESTRINGS_COUNT + BATTLESTRINGS_ID_ADDER)
        {
            gDisplayedStringBattle[0] = EOS;
            return;
        }
        else
        {
            stringPtr = gBattleStringsTable[stringID - BATTLESTRINGS_ID_ADDER];
        }
        break;
    }

    BattleStringExpandPlaceholdersToDisplayedString(stringPtr);
}

