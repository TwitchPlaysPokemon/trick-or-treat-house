import argparse
import configparser
from elf import Elf


def pgegen(args):
    config = configparser.ConfigParser()
    config.optionxform = str

    elf = args.elf

    def sym_get(name):
        return f'{elf.get_sym(name).st_value & 0xFFFFFF:X}'

    def config_set(name, value):
        config.set(args.code, name, value)

    def get_size_rawasm(sym):
        i = elf.symbols_sorted.index(sym) + 1
        while elf.symbols_sorted[i].st_value == sym.st_value:
            i += 1
        return elf.symbols_sorted[i].st_value - sym.st_value

    print('Building config... ', end='', flush=True)
    config.add_section(args.code)
    config_set('ROMName', args.name)
    gItems = elf.get_sym('gItems')
    config_set('ItemData', f'{gItems.st_value & 0xFFFFFF:X}')
    gMoveNames = elf.get_sym('gMoveNames')
    config_set('AttackNames', f'{gMoveNames.st_value & 0xFFFFFF:X}')
    TMHMMoves = elf.get_sym('gTMHMMoves')
    config_set('TMData', f'{TMHMMoves.st_value & 0xFFFFFF:X}')
    config_set('TotalTMsPlusHMs', f'{TMHMMoves.st_size // 2}')
    config_set('TotalTMs', f'{TMHMMoves.st_size // 2 - 8}')
    config_set('NumberOfItems', f'{gItems.st_size // 44}')
    config_set('NumberOfAttacks', f'{gMoveNames.st_size // 13}')
    gSpeciesNames = elf.get_sym('gSpeciesNames')
    config_set('PokemonNames', f'{gSpeciesNames.st_value & 0xFFFFFF:X}')
    npokes = gSpeciesNames.st_size // 11
    config_set('NumberOfPokemon', f'{npokes}')
    config_set('NationalDexTable', sym_get('gSpeciesToNationalPokedexNum'))
    config_set('SecondDexTable', sym_get('gSpeciesToHoennPokedexNum'))
    gPokedexEntries = elf.get_sym('gPokedexEntries')
    config_set('PokedexData', f'{gPokedexEntries.st_value & 0xFFFFFF:X}')
    config_set('NumberOfDexEntries', f'{gPokedexEntries.st_size // 36}')
    config_set('PokemonData', sym_get('gBaseStats'))
    gAbilityNames = elf.get_sym('gAbilityNames')
    config_set('AbilityNames', f'{gAbilityNames.st_value & 0xFFFFFF:X}')
    config_set('NumberOfAbilities', f'{get_size_rawasm(gAbilityNames) // 13}')
    gMapGroups = elf.get_sym('gMapGroups')
    config_set('Pointer2PointersToMapBanks', f'{gMapGroups.st_value & 0xFFFFFF:X}')
    ptrs = []
    while True:
        grp = elf.get_sym(f'gMapGroup{len(ptrs)}')
        if grp.st_name is None:
            break
        config_set(f'OriginalBankPointer{len(ptrs)}', f'{grp.st_value & 0xFFFFFF:X}')
        ptrs.append(grp.st_value)
    ptrs.append(gMapGroups.st_value)
    sorted_ptrs = sorted(ptrs)
    for i, ptr in enumerate(ptrs[:-1]):
        j = sorted_ptrs.index(ptr)
        size = sorted_ptrs[j + 1] - ptr - 4
        config_set(f'NumberOfMapsInBank{i}', f'{size // 4}')
    gRegionMapEntries = elf.get_sym('gRegionMapEntries')
    config_set('MapLabelData', f'{gRegionMapEntries.st_value & 0xFFFFFF:X}')
    config_set('NumberOfMapLabels', f'{gRegionMapEntries.st_size // 8}')

    config_set('PokemonFrontSprites', sym_get('gMonFrontPicTable'))
    config_set('PokemonBackSprites', sym_get('gMonBackPicTable'))
    config_set('PokemonNormalPal', sym_get('gMonPaletteTable'))
    config_set('PokemonShinyPal', sym_get('gMonShinyPaletteTable'))
    config_set('IconPointerTable', sym_get('gMonIconTable'))
    config_set('IconPalTable', sym_get('gMonIconPaletteIndices'))
    config_set('CryTable', sym_get('gCryTable'))
    config_set('CryTable2', sym_get('gCryTable2'))
    config_set('FootPrintTable', sym_get('sMonFootprintTable'))
    config_set('PokemonAttackTable', sym_get('gLevelUpLearnsets'))
    gEvolutionTable = elf.get_sym('gEvolutionTable')
    config_set('PokemonEvolutions', f'{gEvolutionTable.st_value & 0xFFFFFF:X}')
    gTMHMLearnsets = elf.get_sym('gTMHMLearnsets')
    config_set('TMHMCompatibility', f'{gTMHMLearnsets.st_value & 0xFFFFFF:X}')
    config_set('TMHMLenPerPoke', f'{gTMHMLearnsets.st_size // npokes}')
    config_set('EnemyYTable', sym_get('gMonFrontPicCoords'))
    config_set('PlayerYTable', sym_get('gMonBackPicCoords'))
    config_set('EnemyAltitudeTable', sym_get('gEnemyMonElevation'))
    config_set('AttackData', sym_get('gBattleMoves'))
    config_set('ContestMoveData', sym_get('gContestMoves'))
    config_set('ContestMoveEffectData', sym_get('gContestEffects'))
    config_set('AttackDescriptionTable', sym_get('gMoveDescriptionPointers'))
    config_set('AbilityDescriptionTable', sym_get('gAbilityDescriptionPointers'))
    try:
        config_set('StarterPokemon', sym_get('sStarterMon'))
    except AttributeError:
        config_set('StarterPokemon', '')
    config_set('StarterPokemonLevel', '')
    config_set('StarterEncounterPokemon', '')
    config_set('StarterEncounterPokemonLevel', '')
    config_set('AttackAnimationTable', sym_get('gBattleAnims_Moves'))

    # This breaks, not needed for Pokemon HUD anyway
    # general_tileset = elf.get_sym('gTileset_General')
    # tileset_no = 0
    # while True:
    #     sym = elf.symbols[elf.symbols.index(general_tileset.st_value + 0x18 * (tileset_no + 1))]
    #     if sym is None or not (sym.st_name and sym.st_name.startswith('gTileset_')):
    #         break
    #     sh = sym.st_sh
    #     elf.seek(sh.sh_offset + sym.st_value - sh.sh_addr + 12)
    #     val = int.from_bytes(elf.read(4), 'little', signed=False)
    #     val2 = int.from_bytes(elf.read(4), 'little', signed=False)
    #     config_set(f'NumberOfTilesInTilset{0x286D0C + 0x18 * tileset_no:6X}', f'{(val2 - val) // 16:X}')
    #     tileset_no += 1

    # Hardcode this for now, something's definitely fishy
    config_set('NumberOfTilesInTilset286D0C', '90')
    config_set('NumberOfTilesInTilset286D24', '15D')
    config_set('NumberOfTilesInTilset286D3C', '90')
    config_set('NumberOfTilesInTilset286D54', '16C')
    config_set('NumberOfTilesInTilset286D6C', '1B2')
    config_set('NumberOfTilesInTilset286D84', '11E')
    config_set('NumberOfTilesInTilset286D9C', '152')
    config_set('NumberOfTilesInTilset286DB4', '10B')
    config_set('NumberOfTilesInTilset286DCC', '15F')
    config_set('NumberOfTilesInTilset286DE4', '16B')
    config_set('NumberOfTilesInTilset286DFC', 'A8')
    config_set('NumberOfTilesInTilset286E14', 'BF')
    config_set('NumberOfTilesInTilset286E2C', 'FE')
    config_set('NumberOfTilesInTilset286E44', '118')
    config_set('NumberOfTilesInTilset286E5C', 'C6')
    config_set('NumberOfTilesInTilset286E74', '19E')
    config_set('NumberOfTilesInTilset286E8C', '3A')
    config_set('NumberOfTilesInTilset286EA4', '68')
    config_set('NumberOfTilesInTilset286EBC', '01')
    config_set('NumberOfTilesInTilset286ED4', '9F')
    config_set('NumberOfTilesInTilset286EEC', '65')
    config_set('NumberOfTilesInTilset286F04', '100')
    config_set('NumberOfTilesInTilset286F1C', '87')
    config_set('NumberOfTilesInTilset286F34', '48')
    config_set('NumberOfTilesInTilset286F4C', '44')
    config_set('NumberOfTilesInTilset286F64', '1FE')
    config_set('NumberOfTilesInTilset286F7C', 'F8')
    config_set('NumberOfTilesInTilset286F94', '53')
    config_set('NumberOfTilesInTilset286FAC', '144')
    config_set('NumberOfTilesInTilset286FC4', '144')
    config_set('NumberOfTilesInTilset286FDC', '144')
    config_set('NumberOfTilesInTilset286FF4', '144')
    config_set('NumberOfTilesInTilset28700C', '144')
    config_set('NumberOfTilesInTilset287024', '144')
    config_set('NumberOfTilesInTilset28703C', '26')
    config_set('NumberOfTilesInTilset287054', '3A')
    config_set('NumberOfTilesInTilset28706C', 'E0')
    config_set('NumberOfTilesInTilset287084', '8F')
    config_set('NumberOfTilesInTilset28709C', 'AB')
    config_set('NumberOfTilesInTilset2870B4', '9A')
    config_set('NumberOfTilesInTilset2870CC', 'EC')
    config_set('NumberOfTilesInTilset2870E4', '8C')
    config_set('NumberOfTilesInTilset2870FC', '63')
    config_set('NumberOfTilesInTilset287114', '60')
    config_set('NumberOfTilesInTilset28712C', '38')
    config_set('NumberOfTilesInTilset287144', '3D')
    config_set('NumberOfTilesInTilset28715C', '52')
    config_set('NumberOfTilesInTilset287174', '2A')
    config_set('NumberOfTilesInTilset28718C', '95')
    config_set('NumberOfTilesInTilset2871A4', '35')
    config_set('NumberOfTilesInTilset2871BC', '49')
    config_set('NumberOfTilesInTilset2871D4', 'FC')
    config_set('NumberOfTilesInTilset2871EC', '14B')
    config_set('NumberOfTilesInTilset287204', '83')

    config_set('IconPals', sym_get('gMonIconPalettes'))
    config_set('JamboLearnableMovesTerm', '0000FF')  # ??????????????
    config_set('StartSearchingForSpaceOffset', '800000')  # ??????????????
    config_set('FreeSpaceSearchInterval', '100')  # ???????????????
    config_set('NumberOfEvolutionsPerPokemon', f'{gEvolutionTable.st_size // (npokes * 8)}')
    # Hardcode these
    config_set('NumberOfEvolutionTypes', '15')
    config_set('EvolutionName0', 'None')
    config_set('EvolutionName1', 'Happiness')
    config_set('EvolutionName2', 'Happiness (Day)')
    config_set('EvolutionName3', 'Happiness (Night)')
    config_set('EvolutionName4', 'Level')
    config_set('EvolutionName5', 'Trade')
    config_set('EvolutionName6', 'Trade w/ Item')
    config_set('EvolutionName7', 'Item')
    config_set('EvolutionName8', 'Atk > Def')
    config_set('EvolutionName9', 'Atk = Def')
    config_set('EvolutionName10', 'Atk < Def')
    config_set('EvolutionName11', 'High Personality')
    config_set('EvolutionName12', 'Low Personality')
    config_set('EvolutionName13', 'Allow Pokemon Creation')
    config_set('EvolutionName14', 'Create Extra Pokemon')
    config_set('EvolutionName15', 'Max Beauty')
    config_set('Evolution0Param', 'none')
    config_set('Evolution1Param', 'evolvesbutnoparms')
    config_set('Evolution2Param', 'evolvesbutnoparms')
    config_set('Evolution3Param', 'evolvesbutnoparms')
    config_set('Evolution4Param', 'level')
    config_set('Evolution5Param', 'evolvesbutnoparms')
    config_set('Evolution6Param', 'item')
    config_set('Evolution7Param', 'item')
    config_set('Evolution8Param', 'level')
    config_set('Evolution9Param', 'level')
    config_set('Evolution10Param', 'level')
    config_set('Evolution11Param', 'level')
    config_set('Evolution12Param', 'level')
    config_set('Evolution13Param', 'evolvesbutnoparms')
    config_set('Evolution14Param', 'level')
    config_set('Evolution15Param', 'evolvesbasedonvalue')

    config_set('MoveTutorAttacks', '0')
    config_set('CryConversionTable', sym_get('gSpeciesIdToCryId'))
    config_set('MoveTutorCompatibility', '0')
    config_set('EggMoveTable', sym_get('gEggMoves'))
    config_set('EggMoveTableLimiter', sym_get('GetEggMoves'))  # static function
    gTrainers = elf.get_sym('gTrainers')
    config_set('TrainerTable', f'{gTrainers.st_value & 0xFFFFFF:X}')
    config_set('NumberOfTrainers', f'{gTrainers.st_size // 40 - 1}')
    gTrainerClassNames = elf.get_sym('gTrainerClassNames')
    config_set('TrainerClasses', f'{gTrainerClassNames.st_value & 0xFFFFFF:X}')
    config_set('NumberOfTrainerClasses', f'{gTrainerClassNames.st_size // 13}')
    gTrainerFrontPicTable = elf.get_sym('gTrainerFrontPicTable')
    gTrainerFrontPicPaletteTable = elf.get_sym('gTrainerFrontPicPaletteTable')
    config_set('TrainerImageTable', f'{gTrainerFrontPicTable.st_value & 0xFFFFFF:X}')
    size = gTrainerFrontPicPaletteTable.st_value - gTrainerFrontPicTable.st_value
    config_set('NumberOfTrainerImages', f'{size // 8}')
    config_set('TrainerPaletteTable', f'{gTrainerFrontPicPaletteTable.st_value & 0xFFFFFF:X}')
    config_set('DexSizeTrainerSprite', '0')
    gIngameTrades = elf.get_sym('gIngameTrades')
    config_set('TradeData', f'{gIngameTrades.st_value & 0xFFFFFF:X}')
    config_set('NumberOfTrades', f'{gIngameTrades.st_size // 60}')

    # RAM locations
    gPlayerParty = elf.get_sym('gPlayerParty')
    config_set('gPlayerParty', f'{gPlayerParty.st_value:X}')
    config_set('PartyBytes', f'{gPlayerParty.st_size:X}')

    gPokemonStoragePtr = elf.get_sym('gPokemonStoragePtr')
    gSaveBlock1Ptr = elf.get_sym('gSaveBlock1Ptr')
    gSaveBlock2Ptr = elf.get_sym('gSaveBlock2Ptr')

    gPokemonStorage = elf.get_sym('gPokemonStorage')

    is_rs = None in (gPokemonStoragePtr.st_name, gSaveBlock1Ptr.st_name, gSaveBlock2Ptr.st_name)

    if is_rs:
        # RS
        config_set('PCBlockAddress', f'{gPokemonStorage.st_value:X}')
        config_set('SaveBlock1Address', f'{elf.get_sym("gSaveBlock1").st_value:X}')
        config_set('SaveBlock2Address', f'{elf.get_sym("gSaveBlock2").st_value:X}')
    else:
        # Emerald
        config_set('PCBlockAddress', f'*{gPokemonStoragePtr.st_value:X}')
        config_set('SaveBlock1Address', f'*{gSaveBlock1Ptr.st_value:X}')
        config_set('SaveBlock2Address', f'*{gSaveBlock2Ptr.st_value:X}')
    config_set('PCBytes', f'{gPokemonStorage.st_size:X}')

    # Assume these offsets are unchanged from vanilla
    if is_rs:
        config_set('DaycareOffset', '2F9C')
        config_set('MoneyOffset', '490')
        # Skip encryption key offset
        config_set('ItemPCOffset', '498')
        config_set('ItemPCCount', '32')
        config_set('ItemPocketOffset', '560')
        config_set('ItemPocketCount', '14')
        config_set('ItemKeyOffset', '5B0')
        config_set('ItemKeyCount', '14')
        config_set('ItemBallOffset', '600')
        config_set('ItemBallCount', '10')
        config_set('ItemTMOffset', '640')
        config_set('ItemTMCount', '40')
        config_set('ItemBerriesOffset', '740')
        config_set('ItemBerriesCount', '2E')
        config_set('FlagsOffset', '1220')
        config_set('BadgeFlag', '807')  # 100:7
        config_set('IwramMusicAddr', sym_get('sCurrentMapMusic'))
        config_set('EvolutionMusicIds', '178 179')
        # Skip rival name
    else:
        # Assume Emerald for now
        config_set('DaycareOffset', '3030')
        config_set('MoneyOffset', '490')
        config_set('EncryptionKeyOffset', 'AC')
        config_set('ItemPCOffset', '498')
        config_set('ItemPCCount', '32')
        config_set('ItemPocketOffset', '560')
        config_set('ItemPocketCount', '1E')
        config_set('ItemKeyOffset', '5D8')
        config_set('ItemKeyCount', '1E')
        config_set('ItemBallOffset', '650')
        config_set('ItemBallCount', '10')
        config_set('ItemTMOffset', '690')
        config_set('ItemTMCount', '40')
        config_set('ItemBerriesOffset', '790')
        config_set('ItemBerriesCount', '2E')
        config_set('FlagsOffset', '1270')
        config_set('BadgeFlag', '867')  # 10E:7
        config_set('IwramMusicAddr', sym_get('sCurrentMapMusic'))
        config_set('EvolutionMusicIds', '178 179')
        # Skip rival name
    config_set('CurrentAreaAddr', f'{elf.get_sym("gMapHeader").st_value:X}+14')
    config_set('gBattleTypeFlags', f'{elf.get_sym("gBattleTypeFlags").st_value:X}')
    config_set('gTrainerBattleOpponent_A', f'{(elf.get_sym("gTrainerBattleOpponent_A") or elf.get_sym("gTrainerBattleOpponent")).st_value:X}')
    config_set('gEnemyParty', f'{elf.get_sym("gEnemyParty").st_value:X}')
    config_set('gBattlersCount', f'{elf.get_sym("gBattlersCount").st_value:X}')
    config_set('gBattlerPartyIndexes', f'{elf.get_sym("gBattlerPartyIndexes").st_value:X}')
    config_set('gBattlerPositions', f'{(elf.get_sym("gBattlerPositions") or elf.get_sym("gBanksBySide")).st_value:X}')
    gBattleMons = elf.get_sym("gBattleMons")
    config_set('gBattleMons', f'{gBattleMons.st_value:X}')
    config_set('gBattleMonsBytes', f'{get_size_rawasm(gBattleMons):X}')
    if is_rs:
        config_set('InBattleAddr', f'{elf.get_sym("gMain").st_value:X}+43D')
    else:
        config_set('InBattleAddr', f'{elf.get_sym("gMain").st_value:X}+439')

    print('done')

    print('writing config... ', end='', flush=True)
    config.write(args.output, space_around_delimiters=False)
    print('done')
    print('Process complete!')


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('elf', type=Elf.from_filename)
    parser.add_argument('output', type=argparse.FileType('w'))
    parser.add_argument('--code', default='BPEE')
    parser.add_argument('--name', default='TriHard Emerald (English)')
    args = parser.parse_args()
    pgegen(args)


if __name__ == '__main__':
    main()
