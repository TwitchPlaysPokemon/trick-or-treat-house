
//-------------------------------------------------------------------
#include "elf/battle_strings.h"
#include "elf/species_names.h"
#include "elf/move_names.h"
#include "elf/ability_names.h"

#define BORT_REPLACEMENT

//-------------------------------------------------------------------
// Placeholders:

const u8 gBort_Types[][4+1] =
{
    [TYPE_NORMAL]   = _("NORM"), // verified
    [TYPE_FIGHTING] = _("FIG"),
    [TYPE_FLYING]   = _("FLY"), // verified
    [TYPE_POISON]   = _("POI"), // verified
    [TYPE_GROUND]   = _("GRO"), // verified
    [TYPE_ROCK]     = _("RK"), // verified
    [TYPE_BUG]      = _("BUG"),
    [TYPE_GHOST]    = _("GHO"),
    [TYPE_STEEL]    = _("STEE"),
    [TYPE_MYSTERY]  = _("????"),
    [TYPE_FIRE]     = _("FLA"), // verified
    [TYPE_WATER]    = _("WAT"), // verified
    [TYPE_GRASS]    = _("GRA"),
    [TYPE_ELECTRIC] = _("ELE"),
    [TYPE_PSYCHIC]  = _("ABLE"), // verified
    [TYPE_ICE]      = _("ICY"),
    [TYPE_DRAGON]   = _("DRA"),
    [TYPE_DARK]     = _("DAR"),
    [TYPE_FAIRY]    = _("FIA"),
};


//-------------------------------------------------------------------
// Below are copies from the battle_messages.c file, with their explainations on how they
// were used in Japanese. Since Viet Crystal was a poor translation of the japanese, we're
// going to use these functions to their original effect to poorly translate the line.
static const u8 gBort_SpaceIs[] = _(" IS");
static const u8 gBort_ApostropheS[] = _("");//EN'S");

static const u8 gBort_ExclamationMark[] = _("!");
static const u8 gBort_ExclamationMark2[] = _(" USED!");
static const u8 gBort_ExclamationMark3[] = _("AH!");
static const u8 gBort_ExclamationMark4[] = _(" AH!");
static const u8 gBort_ExclamationMark5[] = _(" AH!");

static const u8 gBort_AttackerUsedX[] = _("{B_BUFF1}{B_ATK_NAME_WITH_PREFIX}\n{B_BUFF3}");

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
            StringCopy(textBuff, gBort_SpaceIs); // is
        else if (counter <= MAX_MON_MOVES)
            StringCopy(textBuff, gBort_ApostropheS); // 's
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
        StringCopy(dst, gBort_ExclamationMark);
        break;
    case 1:
        StringCopy(dst, gBort_ExclamationMark2);
        break;
    case 2:
        StringCopy(dst, gBort_ExclamationMark3);
        break;
    case 3:
        StringCopy(dst, gBort_ExclamationMark4);
        break;
    case 4:
        StringCopy(dst, gBort_ExclamationMark5);
        break;
    }
}


const u8* CopyMoveName(u16 moveId);

void BufferStringBattle_BORT(u16 stringID)
{
    s32 i;
    const u8 *stringPtr = NULL;
    
    switch (stringID)
    {
    case STRINGID_INTROMSG: // first battle msg
        
        if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)
        {
            if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED_LINK))
            {
                if (gBattleTypeFlags & BATTLE_TYPE_TOWER_LINK_MULTI)
                {
                    stringPtr = gBort_TwoTrainersWantToBattle;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
                {
                    if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
                        stringPtr = gBort_TwoLinkTrainersWantToBattlePause;
                    else
                        stringPtr = gBort_TwoLinkTrainersWantToBattle;
                }
                else
                {
                    if (gTrainerBattleOpponent_A == TRAINER_UNION_ROOM)
                        stringPtr = gBort_Trainer1WantsToBattle;
                    else if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
                        stringPtr = gBort_LinkTrainerWantsToBattlePause;
                    else
                        stringPtr = gBort_LinkTrainerWantsToBattle;
                }
            }
            else
            {
                if (BATTLE_TWO_VS_ONE_OPPONENT)
                    stringPtr = gBort_Trainer1WantsToBattle;
                else if (gBattleTypeFlags & (BATTLE_TYPE_MULTI | BATTLE_TYPE_INGAME_PARTNER))
                    stringPtr = gBort_TwoTrainersWantToBattle;
                else if (gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS)
                    stringPtr = gBort_TwoTrainersWantToBattle;
                else
                    stringPtr = gBort_Trainer1WantsToBattle;
            }
        }
        else
        {
            if (gBattleTypeFlags & BATTLE_TYPE_LEGENDARY)
                stringPtr = gBort_LegendaryPkmnAppeared;
            else if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE && IsValidForBattle(&gEnemyParty[gBattlerPartyIndexes[BATTLE_PARTNER(gActiveBattler)]])) // interesting, looks like they had something planned for wild double battles
                stringPtr = gBort_TwoWildPkmnAppeared;
            else if (gBattleTypeFlags & BATTLE_TYPE_WALLY_TUTORIAL)
                stringPtr = gBort_WildPkmnAppearedPause;
            else
                stringPtr = gBort_WildPkmnAppeared;
        }
        break;
    case STRINGID_INTROSENDOUT: // poke first send-out
        if (GetBattlerSide(gActiveBattler) == B_SIDE_PLAYER)
        {
            if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE && IsValidForBattle(&gPlayerParty[gBattlerPartyIndexes[BATTLE_PARTNER(gActiveBattler)]]))
            {
                if (gBattleTypeFlags & BATTLE_TYPE_INGAME_PARTNER)
                    stringPtr = gBort_InGamePartnerSentOutZGoN;
                else if (gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS)
                    stringPtr = gBort_GoTwoPkmn;
                else if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
                    stringPtr = gBort_LinkPartnerSentOutPkmnGoPkmn;
                else
                    stringPtr = gBort_GoTwoPkmn;
            }
            else
            {
                stringPtr = gBort_GoPkmn;
            }
        }
        else
        {
            if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE && IsValidForBattle(&gEnemyParty[gBattlerPartyIndexes[BATTLE_PARTNER(gActiveBattler)]]))
            {
                if (BATTLE_TWO_VS_ONE_OPPONENT)
                    stringPtr = gBort_Trainer1SentOutTwoPkmn;
                else if (gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS)
                    stringPtr = gBort_TwoTrainersSentPkmn;
                else if (gBattleTypeFlags & BATTLE_TYPE_TOWER_LINK_MULTI)
                    stringPtr = gBort_TwoTrainersSentPkmn;
                else if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
                    stringPtr = gBort_TwoLinkTrainersSentOutPkmn;
                else if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED_LINK))
                    stringPtr = gBort_LinkTrainerSentOutTwoPkmn;
                else
                    stringPtr = gBort_Trainer1SentOutTwoPkmn;
            }
            else
            {
                if (!(gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED_LINK)))
                    stringPtr = gBort_Trainer1SentOutPkmn;
                else if (gTrainerBattleOpponent_A == TRAINER_UNION_ROOM)
                    stringPtr = gBort_Trainer1SentOutPkmn;
                else
                    stringPtr = gBort_LinkTrainerSentOutPkmn;
            }
        }
        break;
    case STRINGID_RETURNMON: // sending poke to ball msg
        if (GetBattlerSide(gActiveBattler) == B_SIDE_PLAYER)
        {
            if (*(&gBattleStruct->hpScale) == 0)
                stringPtr = gBort_PkmnThatsEnough;
            else if (*(&gBattleStruct->hpScale) == 1 || gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
                stringPtr = gBort_PkmnComeBack;
            else if (*(&gBattleStruct->hpScale) == 2)
                stringPtr = gBort_PkmnOkComeBack;
            else
                stringPtr = gBort_PkmnGoodComeBack;
        }
        else
        {
            if (gTrainerBattleOpponent_A == TRAINER_LINK_OPPONENT || gBattleTypeFlags & BATTLE_TYPE_RECORDED_LINK)
            {
                if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
                    stringPtr = gBort_LinkTrainer2WithdrewPkmn;
                else
                    stringPtr = gBort_LinkTrainer1WithdrewPkmn;
            }
            else
            {
                stringPtr = gBort_Trainer1WithdrewPkmn;
            }
        }
        break;
    case STRINGID_SWITCHINMON: // switch-in msg
        if (GetBattlerSide(gBattleScripting.battler) == B_SIDE_PLAYER)
        {
            if (*(&gBattleStruct->hpScale) == 0 || gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
                stringPtr = gBort_GoPkmn2;
            else if (*(&gBattleStruct->hpScale) == 1)
                stringPtr = gBort_DoItPkmn;
            else if (*(&gBattleStruct->hpScale) == 2)
                stringPtr = gBort_GoForItPkmn;
            else
                stringPtr = gBort_YourFoesWeakGetEmPkmn;
        }
        else
        {
            if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED_LINK))
            {
                if (gBattleTypeFlags & BATTLE_TYPE_TOWER_LINK_MULTI)
                {
                    if (gBattleScripting.battler == 1)
                        stringPtr = gBort_Trainer1SentOutPkmn2;
                    else
                        stringPtr = gBort_Trainer2SentOutPkmn;
                }
                else
                {
                    if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
                        stringPtr = gBort_LinkTrainerMultiSentOutPkmn;
                    else if (gTrainerBattleOpponent_A == TRAINER_UNION_ROOM)
                        stringPtr = gBort_Trainer1SentOutPkmn2;
                    else
                        stringPtr = gBort_LinkTrainerSentOutPkmn2;
                }
            }
            else
            {
                if (gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS)
                {
                    if (gBattleScripting.battler == 1)
                        stringPtr = gBort_Trainer1SentOutPkmn2;
                    else
                        stringPtr = gBort_Trainer2SentOutPkmn;
                }
                else
                {
                    stringPtr = gBort_Trainer1SentOutPkmn2;
                }
            }
        }
        break;
    case STRINGID_USEDMOVE: // pokemon used a move msg
        ChooseMoveUsedParticle_BORT(gBattleTextBuff1);
        
        StringCopy(gBattleTextBuff3, CopyMoveName(gBattleMsgDataPtr->currentMove));
        // if (gBattleStruct->zmove.active && gBattleStruct->zmove.activeSplit != SPLIT_STATUS)
        //     StringCopy(gBattleTextBuff3, GetZMoveName(gBattleMsgDataPtr->currentMove));
        // else if (gBattleMsgDataPtr->currentMove >= MOVES_COUNT)
        //     StringCopy(gBattleTextBuff3, sATypeMove_Table[*(&gBattleStruct->stringMoveType)]);
        // else
        //     StringCopy(gBattleTextBuff3, gMoveNames[gBattleMsgDataPtr->currentMove]);

        ChooseTypeOfMoveUsedString_BORT(gBattleTextBuff3);
        stringPtr = gBort_AttackerUsedX;
        break;
    case STRINGID_BATTLEEND: // battle end
        if (gBattleTextBuff1[0] & B_OUTCOME_LINK_BATTLE_RAN)
        {
            gBattleTextBuff1[0] &= ~(B_OUTCOME_LINK_BATTLE_RAN);
            if (GetBattlerSide(gActiveBattler) == B_SIDE_OPPONENT && gBattleTextBuff1[0] != B_OUTCOME_DREW)
                gBattleTextBuff1[0] ^= (B_OUTCOME_LOST | B_OUTCOME_WON);

            if (gBattleTextBuff1[0] == B_OUTCOME_LOST || gBattleTextBuff1[0] == B_OUTCOME_DREW)
                stringPtr = gBort_GotAwaySafely;
            else if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
                stringPtr = gBort_TwoWildFled;
            else
                stringPtr = gBort_WildFled;
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
                    if (gBattleTypeFlags & BATTLE_TYPE_TOWER_LINK_MULTI)
                        stringPtr = gBort_TwoInGameTrainersDefeated;
                    else
                        stringPtr = gBort_TwoLinkTrainersDefeated;
                    break;
                case B_OUTCOME_LOST:
                    stringPtr = gBort_PlayerLostToTwo;
                    break;
                case B_OUTCOME_DREW:
                    stringPtr = gBort_PlayerBattledToDrawVsTwo;
                    break;
                }
            }
            // else if (gTrainerBattleOpponent_A == TRAINER_UNION_ROOM)
            // {
            //     switch (gBattleTextBuff1[0])
            //     {
            //     case B_OUTCOME_WON:
            //         stringPtr = gBort_PlayerDefeatedLinkTrainerTrainer1;
            //         break;
            //     case B_OUTCOME_LOST:
            //         stringPtr = gBort_PlayerLostAgainstTrainer1;
            //         break;
            //     case B_OUTCOME_DREW:
            //         stringPtr = gBort_PlayerBattledToDrawTrainer1;
            //         break;
            //     }
            // }
            else
            {
                switch (gBattleTextBuff1[0])
                {
                case B_OUTCOME_WON:
                    stringPtr = gBort_PlayerDefeatedLinkTrainer;
                    break;
                case B_OUTCOME_LOST:
                    stringPtr = gBort_PlayerLostAgainstLinkTrainer;
                    break;
                case B_OUTCOME_DREW:
                    stringPtr = gBort_PlayerBattledToDrawLinkTrainer;
                    break;
                }
            }
        }
        break;
    case STRINGID_TRAINERSLIDE:
        stringPtr = gBattleStruct->trainerSlideMsg;
        break;
    default: // load a string from the table
        if (stringID >= BATTLESTRINGS_COUNT + BATTLESTRINGS_ID_ADDER)
        {
            gDisplayedStringBattle[0] = EOS;
            return;
        }
        else
        {
            stringPtr = gElfBattleStringsTable[stringID - BATTLESTRINGS_ID_ADDER];
            if (stringPtr == NULL) 
            {   // Fallback to normal string table if elf doesn't handle it
                stringPtr = gNormalBattleStringsTable[stringID - BATTLESTRINGS_TABLE_START];
            }
        }
        break;
    }

    BattleStringExpandPlaceholdersToDisplayedString(stringPtr);
}

const u8* GetBortSpecies(u16 species)
{
    const u8* bname = gBort_SpeciesNames[species];
    if (bname == NULL || species >= ARRAY_COUNT(gBort_SpeciesNames) || *bname == 0x00) {
        return gSpeciesNames[species];
    }
    return bname;
}

void GetBortifiedPokemonName(struct Pokemon* mon, u8* dst)
{
    if (FlagGet(FLAG_SYS_BORT_MODE)) {
        // In BORT mode, ignore nicknames and get species names
        u16 species = GetMonData(mon, MON_DATA_SPECIES);
        const u8* bname = gBort_SpeciesNames[species];
        if (bname == NULL || species >= ARRAY_COUNT(gBort_SpeciesNames) || *bname == 0x00) {
            // Get nickname if the species name is not available
            GetMonData(mon, MON_DATA_NICKNAME, gBattleTextBuff7);
            StringGet_Nickname(gBattleTextBuff7);
            StringUppercase(dst, gBattleTextBuff7);
            dst[5] = EOS; // truncate name
        } else {
            StringCopy(dst, bname);
        }
    } else {
        GetMonData(mon, MON_DATA_NICKNAME, dst);
        StringGet_Nickname(dst);
    }
}

// Replacement that does BORT mode
static void GetBattlerNick(u32 battlerId, u8 *dst)
{
    struct Pokemon *mon, *illusionMon;
    bool8 BORT = FlagGet(FLAG_SYS_BORT_MODE);

    if (GET_BATTLER_SIDE(battlerId) == B_SIDE_PLAYER)
        mon = &gPlayerParty[gBattlerPartyIndexes[battlerId]];
    else
        mon = &gEnemyParty[gBattlerPartyIndexes[battlerId]];

    illusionMon = GetIllusionMonPtr(battlerId);
    if (illusionMon != NULL)
        mon = illusionMon;
    GetBortifiedPokemonName(mon, dst);
}

const u8* CopyMoveName(u16 moveId)
{
    if (FlagGet(FLAG_SYS_BORT_MODE))
    {
        if (gBattleStruct->zmove.active) {
            if (IsZMove(moveId))
                return gBort_ZMoveNames[moveId - FIRST_Z_MOVE];
            else
                return gBort_ZMoveNames[0]; // Failsafe
        } 
        else if (moveId >= MOVES_COUNT) {
            u8* txt = gBattleTextBuff6;
            StringCopy(txt, gBort_Types[gBattleStruct->stringMoveType]);
            *txt++ = CHAR_SGL_QUOTE_RIGHT;
            *txt++ = CHAR_M;
            *txt++ = CHAR_QUESTION_MARK;
            *txt++ = EOS;
            return gBattleTextBuff6;
        } 
        else {
            // All of the moves are accounted for
            return gBort_MoveNames[moveId];
        }
    }
    else
    {   // original:
        if (gBattleStruct->zmove.active)
            return GetZMoveName(moveId);
        else if (moveId >= MOVES_COUNT)
            return sATypeMove_Table[gBattleStruct->stringMoveType];
        else
            return gMoveNames[moveId];
    }
}

const u8* CopyAbilityName(u16 id)
{
    if (FlagGet(FLAG_SYS_BORT_MODE))
    {
        return gBort_AbilityNames[id];
    }
    else
        return gAbilityNames[id];
}
