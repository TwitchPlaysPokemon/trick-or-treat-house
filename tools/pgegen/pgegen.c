#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "elf.h"
#include "util.h"

static const char * default_name = "TriHard Emerald (English)";
static const char * default_code = "BPEE";

typedef struct {
    size_t nitems;
    uint32_t data[0];
} vector_u32;

static vector_u32 * push_back(vector_u32 * orig, uint32_t value)
{
    orig = realloc(orig, sizeof(vector_u32) + (orig->nitems + 1) * sizeof(uint32_t));
    orig->data[orig->nitems] = value;
    orig->nitems++;
    return orig;
}

static int compare_u32(const void * a, const void * b)
{
    return *(const uint32_t *)a > *(const uint32_t *)b;
}

static unsigned int get_size_rawasm(Elf32_Sym * sym)
{
    Elf32_Sym * next = sym + 1;
    while (next->st_value == sym->st_value || (next->st_shndx & 0xFF00) == 0xFF00) {
        next++;
    }
    return next->st_value - sym->st_value;
}

int main(int argc, char ** argv)
{
    const char * romName = default_name;
    const char * romCode = default_code;
    FILE * elfFile = NULL;
    FILE * outFile = NULL;


    for (int i = 1; i < argc; i++) {
        char * arg = argv[i];
        if (strcmp(arg, "--name") == 0) {
            i++;
            if (i == argc) {
                FATAL_ERROR("missing argument to --name\n");
            }
            romName = argv[i];
        } else if (strcmp(arg, "--code") == 0) {
            i++;
            if (i == argc) {
                FATAL_ERROR("missing argument to --code\n");
            }
            romCode = argv[i];
        } else if (arg[0] == '-') {
            FATAL_ERROR("unrecognized option: \"%s\"\n", arg);
        } else if (elfFile == NULL) {
            elfFile = fopen(arg, "rb");
            if (elfFile == NULL) {
                FATAL_ERROR("unable to open file \"%s\" for reading\n", arg);
            }
        } else if (outFile == NULL) {
            outFile = fopen(arg, "w");
            if (outFile == NULL) {
                FATAL_ERROR("unable to open file \"%s\" for writing\n", arg);
            }
        } else {
            FATAL_ERROR("usage: %s ELF OUTPUT [--name NAME] [--code CODE]\n", argv[0]);
        }
    }

    if (outFile == NULL) {
        FATAL_ERROR("usage: %s ELF OUTPUT [--name NAME] [--code CODE]\n", argv[0]);
    }

    InitElf(elfFile);

    fprintf(outFile, "[%s]\n", romCode);
    fprintf(outFile, "ROMName = %s\n", romName);

#define config_set(name, value) (fprintf(outFile, "%s = %X\n", (name), (value)))
#define config_set_dec(name, value) (fprintf(outFile, "%s = %i\n", (name), (value)))
#define sym_get(name) (GetSymbolByName((name))->st_value)
#define rom_sym_get(name) (GetSymbolByName((name))->st_value - 0x8000000)

    Elf32_Sym * gItems = GetSymbolByName("gItems");
    config_set("ItemData", gItems->st_value - 0x8000000);
    Elf32_Sym * gMoveNames = GetSymbolByName("gMoveNames");
    config_set("AttackNames", gMoveNames->st_value - 0x8000000);
    Elf32_Sym * TMHMMoves = GetSymbolByName("gTMHMMoves");
    config_set("TMData", TMHMMoves->st_value - 0x8000000);
    config_set_dec("TotalTMsPlusHMs", TMHMMoves->st_size / 2);
    config_set_dec("TotalTMs", TMHMMoves->st_size / 2);
    config_set("ItemIMGData", rom_sym_get("gItemIcon_MasterBall"));
    config_set_dec("NumberOfItems", gItems->st_size / 44);
    config_set_dec("NumberOfAttacks", gMoveNames->st_size / 13);
    Elf32_Sym * gSpeciesNames = GetSymbolByName("gSpeciesNames");
    config_set("PokemonNames", gSpeciesNames->st_value - 0x8000000);
    uint16_t npokes = gSpeciesNames->st_size / 11;
    config_set_dec("NumberOfPokemon", npokes);
    config_set("NationalDexTable", rom_sym_get("gSpeciesToNationalPokedexNum"));
    config_set("SecondDexTable", rom_sym_get("gSpeciesToHoennPokedexNum"));
    Elf32_Sym * gPokedexEntries = GetSymbolByName("gPokedexEntries");
    config_set("PokedexData", gPokedexEntries->st_value - 0x8000000);
    config_set_dec("NumberOfDexEntries", gPokedexEntries->st_size / 36);
    config_set("PokemonData", rom_sym_get("gBaseStats"));
    Elf32_Sym * gAbilityNames = GetSymbolByName("gAbilityNames");
    config_set("AbilityNames", gAbilityNames->st_value - 0x8000000);
    config_set_dec("NumberOfAbilities", gAbilityNames->st_size / 13);
    Elf32_Sym * gMapGroups = GetSymbolByName("gMapGroups");
    config_set("Pointer2PointersToMapBanks", gMapGroups->st_value - 0x8000000);
    vector_u32 * ptrs = malloc(sizeof(vector_u32));
    ptrs->nitems = 0;
    char buffer[256];
    while (1) {
        sprintf(buffer, "gMapGroup%lu", ptrs->nitems);
        Elf32_Sym * grp = GetSymbolOrNullByName(buffer);
        if (grp == NULL) break;
        sprintf(buffer, "OriginalBankPointer%lu", ptrs->nitems);
        config_set(buffer, grp->st_value - 0x8000000);
        ptrs = push_back(ptrs, grp->st_value);
    }
    ptrs = push_back(ptrs, gMapGroups->st_value);
    vector_u32 * sorted_ptrs = malloc(sizeof(vector_u32) + ptrs->nitems * sizeof(uint32_t));
    memcpy(sorted_ptrs, ptrs, sizeof(vector_u32) + ptrs->nitems * sizeof(uint32_t));
    msort(sorted_ptrs->data, sorted_ptrs->nitems, sizeof(uint32_t), compare_u32);
    for (int i = 0; i < ptrs->nitems - 1; i++) {
        int j;
        for (j = 0; j < sorted_ptrs->nitems; j++) {
            if (ptrs->data[i] == sorted_ptrs->data[j]) {
                sprintf(buffer, "NumberOfMapsInBank%d", i);
                config_set_dec(buffer, (sorted_ptrs->data[j + 1] - ptrs->data[i] - 4) / 4);
                break;
            }
        }
    }
    free(ptrs);
    free(sorted_ptrs);
    Elf32_Sym * gRegionMapEntries = GetSymbolByName("gRegionMapEntries");
    config_set("MapLabelData", gRegionMapEntries->st_value - 0x8000000);
    config_set_dec("NumberOfMapLabels", gRegionMapEntries->st_size / 8);
    config_set("PokemonFrontSprites", rom_sym_get("gMonFrontPicTable"));
    config_set("PokemonBackSprites", rom_sym_get("gMonBackPicTable"));
    config_set("PokemonNormalPal", rom_sym_get("gMonPaletteTable"));
    config_set("PokemonShinyPal", rom_sym_get("gMonShinyPaletteTable"));
    config_set("PokemonAnimations", rom_sym_get("gMonFrontPicTable"));
    config_set("FrontAnimationTable", rom_sym_get("gTrainerFrontAnimsPtrTable"));
    config_set("BackAnimTable", rom_sym_get("gTrainerBackAnimsPtrTable"));
    //config_set("AnimDelayTable", rom_sym_get(""));
    config_set("IconPointerTable", rom_sym_get("gMonIconTable"));
    config_set("IconPalTable", rom_sym_get("gMonIconPaletteIndices"));
    config_set("CryTable", rom_sym_get("gCryTable"));
    config_set("CryTable2", rom_sym_get("gCryTable2"));
    config_set("FootPrintTable", rom_sym_get("gMonFootprintTable"));
    config_set("PokemonAttackTable", rom_sym_get("gLevelUpLearnsets"));
    Elf32_Sym * gEvolutionTable = GetSymbolByName("gEvolutionTable");
    config_set("PokemonEvolutions", gEvolutionTable->st_value - 0x8000000);
    Elf32_Sym * gTMHMLearnsets = GetSymbolByName("gTMHMLearnsets");
    config_set("TMHMCompatibility", gTMHMLearnsets->st_value - 0x8000000);
    config_set_dec("TMHMLenPerPoke", gTMHMLearnsets->st_size / npokes);
    config_set("EnemyYTable", rom_sym_get("gMonFrontPicCoords"));
    config_set("PlayerYTable", rom_sym_get("gMonBackPicCoords"));
    config_set("EnemyAltitudeTable", rom_sym_get("gEnemyMonElevation"));
    config_set("AttackData", rom_sym_get("gBattleMoves"));
    config_set("ContestMoveData", rom_sym_get("gContestMoves"));
    config_set("ContestMoveEffectData", rom_sym_get("gContestEffects"));
    config_set("AttackDescriptionTable", rom_sym_get("gMoveDescriptionPointers"));
    config_set("AbilityDescriptionTable", rom_sym_get("gAbilityDescriptionPointers"));
    Elf32_Sym * StarterMons = GetSymbolByName("sStarterMon");
    if (StarterMons != NULL) {
        config_set("StarterPokemon", StarterMons->st_value - 0x8000000);
    } else {
        fputs("StarterPokemon = \n", outFile);
    }
    fputs("StarterPokemonLevel = \n", outFile);
    fputs("StarterEncounterPokemon = \n", outFile);
    fputs("StarterEncounterPokemonLevel = \n", outFile);
    config_set("AttackAnimationTable", sym_get("gBattleAnims_Moves"));
    
    // TODO: Tilests


    config_set("IconPals", rom_sym_get("gMonIconPalettes"));
    config_set("JamboLearnableMovesTerm", 0x0000FF);  // ??????????????
    config_set("StartSearchingForSpaceOffset", 0x800000);  // ??????????????
    config_set("FreeSpaceSearchInterval", 0x100);  // ???????????????
    config_set("NumberOfEvolutionsPerPokemon", gEvolutionTable->st_size / (npokes * 8));
// Hardcode these
    fputs("NumberOfEvolutionTypes = 15\n", outFile);
    fputs("EvolutionName0 = None\n", outFile);
    fputs("EvolutionName1 = Happiness\n", outFile);
    fputs("EvolutionName2 = Happiness (Day)\n", outFile);
    fputs("EvolutionName3 = Happiness (Night)\n", outFile);
    fputs("EvolutionName4 = Level\n", outFile);
    fputs("EvolutionName5 = Trade\n", outFile);
    fputs("EvolutionName6 = Trade w/ Item\n", outFile);
    fputs("EvolutionName7 = Item\n", outFile);
    fputs("EvolutionName8 = Atk > Def\n", outFile);
    fputs("EvolutionName9 = Atk = Def\n", outFile);
    fputs("EvolutionName10 = Atk < Def\n", outFile);
    fputs("EvolutionName11 = High Personality\n", outFile);
    fputs("EvolutionName12 = Low Personality\n", outFile);
    fputs("EvolutionName13 = Allow Pokemon Creation\n", outFile);
    fputs("EvolutionName14 = Create Extra Pokemon\n", outFile);
    fputs("EvolutionName15 = Max Beauty\n", outFile);
    fputs("Evolution0Param = none\n", outFile);
    fputs("Evolution1Param = evolvesbutnoparms\n", outFile);
    fputs("Evolution2Param = evolvesbutnoparms\n", outFile);
    fputs("Evolution3Param = evolvesbutnoparms\n", outFile);
    fputs("Evolution4Param = level\n", outFile);
    fputs("Evolution5Param = evolvesbutnoparms\n", outFile);
    fputs("Evolution6Param = item\n", outFile);
    fputs("Evolution7Param = item\n", outFile);
    fputs("Evolution8Param = level\n", outFile);
    fputs("Evolution9Param = level\n", outFile);
    fputs("Evolution10Param = level\n", outFile);
    fputs("Evolution11Param = level\n", outFile);
    fputs("Evolution12Param = level\n", outFile);
    fputs("Evolution13Param = evolvesbutnoparms\n", outFile);
    fputs("Evolution14Param = level\n", outFile);
    fputs("Evolution15Param = evolvesbasedonvalue\n", outFile);


    config_set("MoveTutorAttacks", 0);
    config_set("CryConversionTable", rom_sym_get("gSpeciesIdToCryId"));
    config_set("MoveTutorCompatibility", 0);
    config_set("EggMoveTable", rom_sym_get("gEggMoves"));
    config_set("EggMoveTableLimiter", rom_sym_get("GetEggMoves")); // static function
    Elf32_Sym * gTrainers = GetSymbolByName("gTrainers");
    config_set("TrainerTable", gTrainers->st_value - 0x8000000);
    config_set_dec("NumberOfTrainers", gTrainers->st_size / 40 - 1);
    Elf32_Sym * gTrainerClassNames = GetSymbolByName("gTrainerClassNames");
    config_set("TrainerClasses", gTrainerClassNames->st_value - 0x8000000);
    config_set_dec("NumberOfTrainerClasses", gTrainerClassNames->st_size / 13);
    Elf32_Sym * gTrainerFrontPicTable = GetSymbolByName("gTrainerFrontPicTable");
    Elf32_Sym * gTrainerFrontPicPaletteTable = GetSymbolByName("gTrainerFrontPicPaletteTable");
    config_set("TrainerImageTable", gTrainerFrontPicTable->st_value - 0x8000000);
    unsigned size = gTrainerFrontPicPaletteTable->st_value - gTrainerFrontPicTable->st_value;
    config_set("NumberOfTrainerImages", size / 8);
    config_set("TrainerPaletteTable", gTrainerFrontPicPaletteTable->st_value - 0x8000000);
    config_set("DexSizeTrainerSprite", 0);
    Elf32_Sym * gIngameTrades = GetSymbolByName("gIngameTrades");
    config_set("TradeData", gIngameTrades->st_value - 0x8000000);
    config_set_dec("NumberOfTrades", gIngameTrades->st_size / 60);


// RAM locations
    Elf32_Sym * gPlayerParty = GetSymbolByName("gPlayerParty");
    config_set("gPlayerParty", gPlayerParty->st_value);
    config_set("PartyBytes", gPlayerParty->st_size);

    Elf32_Sym * gPokemonStoragePtr = GetSymbolByName("gPokemonStoragePtr");
    Elf32_Sym * gSaveBlock1Ptr = GetSymbolByName("gSaveBlock1Ptr");
    Elf32_Sym * gSaveBlock2Ptr = GetSymbolByName("gSaveBlock2Ptr");

    Elf32_Sym * gPokemonStorage = GetSymbolByName("gPokemonStorage");

    int is_rs = gPokemonStoragePtr == NULL ? 1 : 0;

    if (is_rs) {
// RS
        config_set("PCBlockAddress", gPokemonStorage->st_value);
        config_set("SaveBlock1Address", GetSymbolByName("gSaveBlock1")->st_value);
        config_set("SaveBlock2Address", GetSymbolByName("gSaveBlock2")->st_value);
    } else {
// Emerald
        fprintf(outFile, "PCBlockAddress = *%X\n", gPokemonStoragePtr->st_value);
        fprintf(outFile, "SaveBlock1Address = *%X\n", gSaveBlock1Ptr->st_value);
        fprintf(outFile, "SaveBlock2Address = *%X\n", gSaveBlock2Ptr->st_value);
    }
    config_set("PCBytes", gPokemonStorage->st_size);

// Assume these offsets are unchanged from vanilla
    if (is_rs) {
        config_set("DaycareOffset", 0x2F9C);
        config_set("MoneyOffset", 0x490);
// Skip encryption key offset
        config_set("ItemPCOffset", 0x498);
        config_set("ItemPCCount", 0x32);
        config_set("ItemPocketOffset", 0x560);
        config_set("ItemPocketCount", 0x14);
        config_set("ItemKeyOffset", 0x5B0);
        config_set("ItemKeyCount", 0x14);
        config_set("ItemBallOffset", 0x600);
        config_set("ItemBallCount", 0x10);
        config_set("ItemTMOffset", 0x640);
        config_set("ItemTMCount", 0x40);
        config_set("ItemBerriesOffset", 0x740);
        config_set("ItemBerriesCount", 0x2E);
        config_set("FlagsOffset", 0x1220);
        config_set("BadgeFlag", 0x807);
        config_set("IwramMusicAddr", sym_get("sCurrentMapMusic"));
        fputs("EvolutionMusicIds = 178 179\n", outFile);
// Skip rival name
    } else {
// Assume Emerald for now
        config_set("FlagsOffset", 0x1270);
        config_set("FlagsBytes", 0x12C);
        config_set("VarsOffset", 0x139C);
        config_set("GameStatsOffset", 0x159C);
        config_set("GameStatsBytes", 0x100);
        config_set("DaycareOffset", 0x3030);
        config_set("MoneyOffset", 0x490);
        config_set("EncryptionKeyOffset", 0xAC);
        config_set("ItemPCOffset", 0x498);
        config_set("ItemPCCount", 1); //TriHard
        config_set("ItemPocketOffset", 0x49C); //TriHard
        config_set("ItemPocketCount", 79); //TriHard
        config_set("ItemKeyOffset", 0x5D8);
        config_set("ItemKeyCount", 0x1E);
        config_set("ItemBallOffset", 0x650);
        config_set("ItemBallCount", 0x10);
        config_set("ItemTMOffset", 0x690);
        config_set("ItemTMCount", 0x40);
        config_set("ItemBerriesOffset", 0x790);
        config_set("ItemBerriesCount", 0x2E);
        config_set("BadgesOffset", 0x10C);
        config_set("IwramClockAddr", sym_get("gLocalTime"));
        config_set("IwramMusicAddr", sym_get("sCurrentMapMusic"));
        fputs("EvolutionMusicIds = 178 179\n", outFile);
// Skip rival name
    }
    config_set("CurrentAreaAddr", GetSymbolByName("gMapHeader")->st_value + 0x14);
    config_set("gBattleTypeFlags", GetSymbolByName("gBattleTypeFlags")->st_value);
    Elf32_Sym * gTrainerBattleOpponent_A = GetSymbolByName("gTrainerBattleOpponent_A");
    if (gTrainerBattleOpponent_A == NULL) {
        gTrainerBattleOpponent_A = GetSymbolByName("gTrainerBattleOpponent");
    }
    config_set("gTrainerBattleOpponent_A", gTrainerBattleOpponent_A->st_value);
    config_set("gEnemyParty", GetSymbolByName("gEnemyParty")->st_value);
    config_set("gBattlersCount", GetSymbolByName("gBattlersCount")->st_value);
    config_set("gBattlerPartyIndexes", GetSymbolByName("gBattlerPartyIndexes")->st_value);
    Elf32_Sym * gBattlerPositions = GetSymbolByName("gBattlerPositions");
    if (gBattlerPositions == NULL) {
        gBattlerPositions = GetSymbolByName("gBanksBySide");
    }
    config_set("gBattlerPositions", gBattlerPositions->st_value);
    Elf32_Sym * gBattleMons = GetSymbolByName("gBattleMons");
    config_set("gBattleMons", gBattleMons->st_value);
    config_set("gBattleMonsBytes", get_size_rawasm(gBattleMons));
    if (is_rs) {
        config_set("InBattleAddr", GetSymbolByName("gMain")->st_value + 0x43D);
    } else {
        config_set("InBattleAddr", GetSymbolByName("gMain")->st_value + 0x439);
    }

    DestroyResources();
    fclose(outFile);
    fclose(elfFile);
    return 0;
}
