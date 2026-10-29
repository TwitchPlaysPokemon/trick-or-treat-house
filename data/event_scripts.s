#include "config.h"
#include "constants/global.h"
#include "constants/battle.h"
#include "constants/battle_arena.h"
#include "constants/battle_dome.h"
#include "constants/battle_factory.h"
#include "constants/battle_frontier.h"
#include "constants/battle_palace.h"
#include "constants/battle_pike.h"
#include "constants/battle_pyramid.h"
#include "constants/battle_setup.h"
#include "constants/battle_tent.h"
#include "constants/battle_tower.h"
#include "constants/berry.h"
#include "constants/cable_club.h"
#include "constants/coins.h"
#include "constants/contest.h"
#include "constants/daycare.h"
#include "constants/decorations.h"
#include "constants/easy_chat.h"
#include "constants/event_objects.h"
#include "constants/event_object_movement.h"
#include "constants/field_effects.h"
#include "constants/field_poison.h"
#include "constants/field_specials.h"
#include "constants/field_tasks.h"
#include "constants/field_weather.h"
#include "constants/flags.h"
#include "constants/frontier_util.h"
#include "constants/game_stat.h"
@ #include "constants/item.h"
#include "constants/items.h"
#include "constants/heal_locations.h"
#include "constants/layouts.h"
#include "constants/lilycove_lady.h"
#include "constants/map_scripts.h"
#include "constants/map_groups.h"
#include "constants/maps.h"
#include "constants/mauville_old_man.h"
#include "constants/metatile_labels.h"
#include "constants/moves.h"
#include "constants/party_menu.h"
#include "constants/pokemon.h"
#include "constants/roulette.h"
#include "constants/script_menu.h"
#include "constants/secret_bases.h"
#include "constants/songs.h"
#include "constants/sound.h"
#include "constants/species.h"
#include "constants/trade.h"
#include "constants/trainer_hill.h"
#include "constants/trainers.h"
#include "constants/tv.h"
#include "constants/union_room.h"
#include "constants/vars.h"
#include "constants/game_stat.h"
#include "constants/weather.h"
#include "constants/trainer_hill.h"
#include "constants/trainer_types.h"
#include "constants/field_tasks.h"
#include "constants/battle.h"
#include "constants/metatile_labels.h"
#include "constants/day_night.h"
#include "constants/follow_me.h"
	.include "asm/macros.inc"
	.include "asm/macros/event.inc"
	.include "asm/macros/puzzle.inc"
	.include "constants/constants.inc"

	.section script_data, "aw", %progbits

	.include "data/script_cmd_table.inc"

gSpecialVars::
	.4byte gSpecialVar_0x8000
	.4byte gSpecialVar_0x8001
	.4byte gSpecialVar_0x8002
	.4byte gSpecialVar_0x8003
	.4byte gSpecialVar_0x8004
	.4byte gSpecialVar_0x8005
	.4byte gSpecialVar_0x8006
	.4byte gSpecialVar_0x8007
	.4byte gSpecialVar_0x8008
	.4byte gSpecialVar_0x8009
	.4byte gSpecialVar_0x800A
	.4byte gSpecialVar_0x800B
	.4byte gSpecialVar_Facing
	.4byte gSpecialVar_Result
	.4byte gSpecialVar_ItemId
	.4byte gSpecialVar_LastTalked
	.4byte gSpecialVar_ContestRank
	.4byte gSpecialVar_ContestCategory
	.4byte gSpecialVar_MonBoxId
	.4byte gSpecialVar_MonBoxPos
	.4byte gSpecialVar_LastErrorNo
	.4byte gTrainerBattleOpponent_A
	.4byte gSpecialVar_InteractX
	.4byte gSpecialVar_InteractY
	.4byte gSpecialVar_MetatileX
	.4byte gSpecialVar_MetatileY
	.4byte gSpecialVar_LastWarpId
	.4byte gSpecialVar_SysForceStep
	.4byte gSpecialVar_BattleMod
	.4byte gSpecialVar_SpeakerPalOverride

	.include "data/specials.inc"

gStdScripts::
	.4byte Std_ObtainItem              @ STD_OBTAIN_ITEM
	.4byte Std_FindItem                @ STD_FIND_ITEM
	.4byte Std_MsgboxNPC               @ MSGBOX_NPC
	.4byte Std_MsgboxSign              @ MSGBOX_SIGN
	.4byte Std_MsgboxDefault           @ MSGBOX_DEFAULT
	.4byte Std_MsgboxYesNo             @ MSGBOX_YESNO
	.4byte Std_MsgboxAutoclose         @ MSGBOX_AUTOCLOSE
	.4byte Std_ObtainDecoration        @ STD_OBTAIN_DECORATION
	.4byte Std_RegisteredInMatchCall   @ STD_REGISTER_MATCH_CALL
	.4byte Std_MsgboxGetPoints         @ MSGBOX_GETPOINTS
	.4byte Std_MsgboxPokenav           @ MSGBOX_POKENAV
gStdScripts_End::
	
	.include "data/puzzle_list.inc"
	.include "data/scripts/common_scripts.inc"
	.include "data/scripts/trick_house.inc"
	.include "data/text/trick_house.inc"


	.include "data/maps/TrickHouseDevEntrance/scripts.inc"
	.include "data/maps/TrickHouseExt/scripts.inc"
	.include "data/maps/TrickHouseEntrance/scripts.inc"
	.include "data/maps/TrickHouseEnd/scripts.inc"
	.include "data/maps/TrickHouseCorridor/scripts.inc"
	.include "data/maps/TrickHouseTreeHouse/scripts.inc"
	.include "data/maps/TrickHouseRestroom/scripts.inc"
	.include "data/maps/TrickHouseRestroom/scenes.inc"
	
	@ -------------------------------------------------
	
	.include "data/maps/MauvilleCity_Cutscene/scripts.inc"
	.include "data/maps/RustboroCity_Cutscene/scripts.inc"
	
	@ -------------------------------------------------
	
	.include "data/maps/Puzzle_TrickHouseOriginal1/scripts.inc"
	.include "data/maps/Puzzle_TrickHouseOriginal2/scripts.inc"
	.include "data/maps/Puzzle_TrickHouseOriginal3/scripts.inc"
	.include "data/maps/Puzzle_TrickHouseOriginal4/scripts.inc"
	.include "data/maps/Puzzle_TrickHouseOriginal5/scripts.inc"
	.include "data/maps/Puzzle_TrickHouseOriginal6/scripts.inc"
	.include "data/maps/Puzzle_TrickHouseOriginal7/scripts.inc"
	.include "data/maps/Puzzle_TrickHouseOriginal8/scripts.inc"
	
	.include "data/maps/Puzzle_TrickHouseCut/scripts.inc"
	.include "data/maps/Puzzle_TrickHouseTrapdoors/scripts.inc"
	.include "data/maps/Puzzle_TrickHouseSpintiles/scripts.inc"
	.include "data/maps/Puzzle_TinTowerClimb/scripts.inc"

	.include "data/maps/Puzzle_WaterTemple/scripts.inc"
	.include "data/maps/WaterTemple_Lv1/scripts.inc"
	.include "data/maps/WaterTemple_Lv2/scripts.inc"
	.include "data/maps/WaterTemple_Secret/scripts.inc"
	
	.include "data/maps/Puzzle_LostWoods1_Entrance/scripts.inc"
	.include "data/maps/LostWoods1_Exit/scripts.inc"
	.include "data/maps/LostWoods1_Room0/scripts.inc"
	.include "data/maps/LostWoods1_Room1/scripts.inc"
	.include "data/maps/LostWoods1_Room2/scripts.inc"
	.include "data/maps/LostWoods1_Room3/scripts.inc"
	.include "data/maps/LostWoods1_Room4/scripts.inc"
	.include "data/maps/LostWoods1_Room5/scripts.inc"
	.include "data/maps/LostWoods1_Room6/scripts.inc"
	.include "data/maps/LostWoods1_Room7/scripts.inc"
	.include "data/maps/LostWoods1_Room8/scripts.inc"
	.include "data/maps/LostWoods1_Room9/scripts.inc"
	.include "data/maps/LostWoods1_Room10/scripts.inc"
	.include "data/maps/LostWoods1_Underwater/scripts.inc"

	.include "data/maps/Puzzle_LostWoods2_Entrance/scripts.inc"
	.include "data/maps/LostWoods2_Exit/scripts.inc"

	.include "data/maps/Puzzle_LostWoods3_Entrance/scripts.inc"
	.include "data/maps/LostWoods3_Exit/scripts.inc"

	.include "data/maps/Puzzle_LostWoods4_Entrance/scripts.inc"
	.include "data/maps/LostWoods4_Exit/scripts.inc"

	.include "data/maps/Puzzle_Loss_Floor1/scripts.inc"
	.include "data/maps/Puzzle_Loss_Floor2/scripts.inc"

	.include "data/maps/Puzzle_MusicNoteTiles/scripts.inc"
	
	.include "data/maps/Puzzle_LedgeMountain/scripts.inc"
	.include "data/maps/LedgeMountain_Support/scripts.inc"
	
	.include "data/maps/Puzzle_Wilke/scripts.inc"
	
	.include "data/maps/Puzzle_Route110/scripts.inc"
	
	.include "data/maps/Puzzle_TwinMemories/scripts.inc"
	
	.include "data/maps/Puzzle_SpotDifference_Hallway/scripts.inc"
	.include "data/maps/Puzzle_SpotDifference_1_Left/scripts.inc"
	.include "data/maps/Puzzle_SpotDifference_1_Right/scripts.inc"
	.include "data/maps/Puzzle_SpotDifference_2_Left/scripts.inc"
	.include "data/maps/Puzzle_SpotDifference_2_Right/scripts.inc"
	.include "data/maps/Puzzle_SpotDifference_3_Left/scripts.inc"
	.include "data/maps/Puzzle_SpotDifference_3_Right/scripts.inc"

	.include "data/maps/Puzzle_HiddenMaze/scripts.inc"

	.include "data/maps/Puzzle_Desert_Oasis/scripts.inc"
	.include "data/maps/Desert_East/scripts.inc"
	.include "data/maps/Desert_North/scripts.inc"
	.include "data/maps/Desert_West/scripts.inc"
	.include "data/maps/Desert_South/scripts.inc"
	
	.include "data/maps/Puzzle_IlexForest/scripts.inc"

	.include "data/maps/Puzzle_SootSackMaze/scripts.inc"

	.include "data/maps/Puzzle_TrickHouseSlipSliding/scripts.inc"

	.include "data/maps/Puzzle_FallingWater/scripts.inc"
	
	.include "data/maps/TrainerHillTemplate/scripts.inc"
	.include "data/maps/Puzzle_TrainerHill1/scripts.inc"
	.include "data/maps/Puzzle_TrainerHill2/scripts.inc"
	.include "data/maps/Puzzle_TrainerHill3/scripts.inc"
	.include "data/maps/Puzzle_TrainerHill4/scripts.inc"
	
	.include "data/maps/Puzzle_DiveMaze/scripts.inc"
	.include "data/maps/DiveMaze_Underwater/scripts.inc"
	
	.include "data/maps/Puzzle_SuspendedMaze/scripts.inc"
	.include "data/maps/SuspendedMaze_B1/scripts.inc"

	.include "data/maps/Puzzle_IcePath/scripts.inc"

	.include "data/maps/Puzzle_TicRacToe/scripts.inc"
	
	.include "data/maps/Puzzle_StealthMission/scripts.inc"

	.include "data/maps/Puzzle_MurderExpress/scripts.inc"
	
	.include "data/maps/LostWoods4_Room0/scripts.inc"
	.include "data/maps/LostWoods4_RoomA1/scripts.inc"
	.include "data/maps/LostWoods4_RoomA2/scripts.inc"
	.include "data/maps/LostWoods4_RoomA3/scripts.inc"
	.include "data/maps/LostWoods4_RoomA4/scripts.inc"
	.include "data/maps/LostWoods4_RoomA5/scripts.inc"
	.include "data/maps/LostWoods4_RoomA6/scripts.inc"
	.include "data/maps/LostWoods4_RoomB1/scripts.inc"
	.include "data/maps/LostWoods4_RoomB2/scripts.inc"
	.include "data/maps/LostWoods4_RoomB3/scripts.inc"
	.include "data/maps/LostWoods4_RoomB4/scripts.inc"
	.include "data/maps/LostWoods4_RoomB5/scripts.inc"
	.include "data/maps/LostWoods4_RoomB6/scripts.inc"
	.include "data/maps/LostWoods4_RoomB7/scripts.inc"
	.include "data/maps/LostWoods4_RoomB8/scripts.inc"
	.include "data/maps/LostWoods4_RoomB9/scripts.inc"
	.include "data/maps/LostWoods4_RoomC1/scripts.inc"
	.include "data/maps/LostWoods4_RoomC2/scripts.inc"
	.include "data/maps/LostWoods4_RoomC3/scripts.inc"
	.include "data/maps/LostWoods4_RoomC4/scripts.inc"
	.include "data/maps/LostWoods4_RoomC5/scripts.inc"
	.include "data/maps/LostWoods4_RoomC6/scripts.inc"
	.include "data/maps/LostWoods4_RoomD1/scripts.inc"
	.include "data/maps/LostWoods4_RoomD2/scripts.inc"
	.include "data/maps/LostWoods4_RoomD3/scripts.inc"
	.include "data/maps/LostWoods4_RoomD4/scripts.inc"
	.include "data/maps/LostWoods4_RoomD5/scripts.inc"
	
	.include "data/maps/Puzzle_EliteFloor/scripts.inc"
	
	.include "data/maps/Puzzle_SafariImposters/scripts.inc"
	.include "data/maps/Puzzle_SafariImposters/text.inc"
	.include "data/maps/SafariZone_Northeast/scripts.inc"
	.include "data/maps/SafariZone_North/scripts.inc"
	.include "data/maps/SafariZone_Northwest/scripts.inc"
	.include "data/maps/SafariZone_Southeast/scripts.inc"
	.include "data/maps/SafariZone_South/scripts.inc"
	.include "data/maps/SafariZone_Southwest/scripts.inc"
	.include "data/maps/SafariZone_RestHouse/scripts.inc"
	
	.include "data/maps/Puzzle_ImposterReflection/scripts.inc"
	
	.include "data/maps/Puzzle_SootopolisGym/scripts.inc"
	.include "data/maps/SootopolisGym_B1F/scripts.inc"
	
	.include "data/maps/MetaPuzzle_StrengthRoom/scripts.inc"
	
	@ -------------------------------------------------

	.include "data/maps/Puzzle_MetaPuzzle/scripts.inc"
	
	.include "data/maps/Meta_EmptyNW/scripts.inc"
	.include "data/maps/Meta_EmptyNE/scripts.inc"
	.include "data/maps/Meta_EmptySW/scripts.inc"
	.include "data/maps/Meta_EmptySE/scripts.inc"
	.include "data/maps/Meta_EmptyNS/scripts.inc"
	.include "data/maps/Meta_EmptyWE/scripts.inc"
	.include "data/maps/Meta_EmptyS/scripts.inc"
	.include "data/maps/Meta_EmptyFilled/scripts.inc"
	
	.include "data/maps/Meta_Entrance/scripts.inc"
	.include "data/maps/Meta_LavaridgeSprings/scripts.inc"
	.include "data/maps/Meta_LedgeRoom/scripts.inc"
	.include "data/maps/Meta_FinalBluff/scripts.inc"
	.include "data/maps/Meta_IceCorner/scripts.inc"
	.include "data/maps/Meta_LogFlotilla/scripts.inc"
	.include "data/maps/Meta_BikePath/scripts.inc"
	.include "data/maps/Meta_PokeStage/scripts.inc"
	.include "data/maps/Meta_ZiggyRoom/scripts.inc"
	.include "data/maps/Meta_ForestClearing/scripts.inc"
	.include "data/maps/Meta_ZipSlide/scripts.inc"
	.include "data/maps/Meta_KogaElbow/scripts.inc"
	.include "data/maps/Meta_SubductionZone/scripts.inc"
	.include "data/maps/Meta_DiveMaze/scripts.inc"
	.include "data/maps/Meta_BerryRoom/scripts.inc"

	.include "data/maps/FinalBluff_Dive/scripts.inc"
	.include "data/maps/MetaDiveMaze_Dive/scripts.inc"
	
	.include "data/maps/Meta_NullRoom/scripts.inc"
	
	@ -------------------------------------------------
	
	.include "data/maps/TrickTreat_PetalburgCity/scripts.inc"
	
	.include "data/maps/TrickTreat_MossdeepCity/scripts.inc"
	
	.include "data/maps/TrickTreat_FortreeCity/scripts.inc"

	.include "data/maps/TrickTreat_AltoMare1/scripts.inc"
	.include "data/maps/TrickTreat_AltoMare2/scripts.inc"
	
	.include "data/maps/TrickTreat_SlateportCity1/scripts.inc"
	.include "data/maps/TrickTreat_SlateportCity2/scripts.inc"

	.include "data/maps/TrickTreat_GoldenrodCity/scripts.inc"
	
	@ -------------------------------------------------
	
	.include "data/maps/EmptyPuzzle/scripts.inc"
	
	.include "data/maps/TestMapHallway/scripts.inc"
	.include "data/maps/TestLayoutSwitching/scripts.inc"
	.include "data/maps/TestLayoutSwitching2/scripts.inc"
	.include "data/maps/TestMirrorMovement/scripts.inc"
	.include "data/maps/TestCopyMovement/scripts.inc"
	.include "data/maps/IndoorMap/scripts.inc"
	.include "data/maps/TestMusicRoom/scripts.inc"
	.include "data/maps/TestAcroBikeMap/scripts.inc"
	
	.include "data/maps/FakeSecretBaseCave/scripts.inc"
	
	.include "data/maps/PetalburgCity/scripts.inc"
	.include "data/maps/SlateportCity/scripts.inc"
	.include "data/maps/MauvilleCity/scripts.inc"
	.include "data/maps/RustboroCity/scripts.inc"
	.include "data/maps/FortreeCity/scripts.inc"
	.include "data/maps/LilycoveCity/scripts.inc"
	.include "data/maps/SootopolisCity/scripts.inc"
	.include "data/maps/EverGrandeCity/scripts.inc"
	.include "data/maps/LittlerootTown/scripts.inc"
	.include "data/maps/OldaleTown/scripts.inc"
	.include "data/maps/DewfordTown/scripts.inc"
	.include "data/maps/LavaridgeTown/scripts.inc"
	.include "data/maps/FallarborTown/scripts.inc"
	.include "data/maps/VerdanturfTown/scripts.inc"
	.include "data/maps/PacifidlogTown/scripts.inc"
	.include "data/maps/Route101/scripts.inc"
	.include "data/maps/Route102/scripts.inc"
	.include "data/maps/Route103/scripts.inc"
	.include "data/maps/Route104/scripts.inc"
	.include "data/maps/Route105/scripts.inc"
	.include "data/maps/Route106/scripts.inc"
	.include "data/maps/Route107/scripts.inc"
	.include "data/maps/Route108/scripts.inc"
	.include "data/maps/Route109/scripts.inc"
	.include "data/maps/Route111/scripts.inc"
	.include "data/maps/Route112/scripts.inc"
	.include "data/maps/Route113/scripts.inc"
	.include "data/maps/Route114/scripts.inc"
	.include "data/maps/Route115/scripts.inc"
	.include "data/maps/Route116/scripts.inc"
	.include "data/maps/Route117/scripts.inc"
	.include "data/maps/Route118/scripts.inc"
	.include "data/maps/Route119/scripts.inc"
	.include "data/maps/Route120/scripts.inc"
	.include "data/maps/Route121/scripts.inc"
	.include "data/maps/Route122/scripts.inc"
	.include "data/maps/Route123/scripts.inc"
	.include "data/maps/Route124/scripts.inc"
	.include "data/maps/Route125/scripts.inc"
	.include "data/maps/Route126/scripts.inc"
	.include "data/maps/Route127/scripts.inc"
	.include "data/maps/Route128/scripts.inc"
	.include "data/maps/Route129/scripts.inc"
	.include "data/maps/Route130/scripts.inc"
	.include "data/maps/Route131/scripts.inc"
	.include "data/maps/Route132/scripts.inc"
	.include "data/maps/Route133/scripts.inc"
	.include "data/maps/Route134/scripts.inc"
	.include "data/scripts/shared_secret_base.inc"

	.include "data/scripts/std_msgbox.inc"
	.include "data/scripts/trainer_battle.inc"
	.include "data/scripts/new_game.inc"

EventScript_WhiteOut:: @ 8271857
	end


	.include "data/scripts/pkmn_center_nurse.inc"
	.include "data/scripts/obtain_item.inc"
	.include "data/scripts/record_mix.inc"
	.include "data/scripts/pc.inc"

Common_EventScript_ReadyPetalburgGymForBattle::
	return

Common_EventScript_BufferTrendyPhrase::
	dotimebasedevents
	setvar VAR_0x8004, 0
	special BufferTrendyPhraseString
	return

	@ .include "data/scripts/surf.inc"
	.include "data/scripts/rival_graphics.inc"
	@ .include "data/scripts/set_gym_trainers.inc"

Common_EventScript_ShowNoRoomForDecor::
	msgbox gText_NoRoomLeftForAnother, MSGBOX_DEFAULT
	release
	end

Common_EventScript_NoRoomForDecor::
	msgbox gText_NoRoomLeftForAnother, MSGBOX_DEFAULT
	return

Common_EventScript_SetAbnormalWeather::
	setweather WEATHER_ABNORMAL
	return

Common_EventScript_OutOfCenterPartyHeal::
	fadescreen FADE_TO_BLACK
	playfanfare MUS_HEAL
	waitfanfare
	special HealPlayerParty
	fadescreen FADE_FROM_BLACK
	return

Common_EventScript_PlayBrineysBoatMusic::
	setflag FLAG_DONT_TRANSITION_MUSIC
	playbgm MUS_SAILING, FALSE
	return

Common_EventScript_StopBrineysBoatMusic::
	clearflag FLAG_DONT_TRANSITION_MUSIC
	fadedefaultbgm
	return

	.include "data/scripts/prof_birch.inc"

@ Below could be split as ferry.inc aside from the Rusturf tunnel script
Common_EventScript_FerryDepart::
	delay 60
	applymovement VAR_0x8004, Movement_FerryDepart
	waitmovement 0
	return

Movement_FerryDepart:
	walk_slow_right
	walk_slow_right
	walk_slow_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

RusturfTunnel_EventScript_SetRusturfTunnelOpen::
	@ removeobject LOCALID_WANDAS_BF
	@ removeobject LOCALID_WANDA
	@ clearflag FLAG_HIDE_VERDANTURF_TOWN_WANDAS_HOUSE_WANDAS_BOYFRIEND
	@ clearflag FLAG_HIDE_VERDANTURF_TOWN_WANDAS_HOUSE_WANDA
	@ setvar VAR_RUSTURF_TUNNEL_STATE, 6
	@ setflag FLAG_RUSTURF_TUNNEL_OPENED
	return

EventScript_UnusedBoardFerry::
	delay 30
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceUp
	waitmovement 0
	showobjectat OBJ_EVENT_ID_PLAYER, 0
	delay 30
	applymovement OBJ_EVENT_ID_PLAYER, Movement_UnusedBoardFerry
	waitmovement 0
	delay 30
	return

Movement_UnusedBoardFerry:
	walk_up
	step_end

Common_EventScript_FerryDepartIsland::
	@ call_if_eq VAR_FACING, DIR_SOUTH, Ferry_EventScript_DepartIslandSouth
	@ call_if_eq VAR_FACING, DIR_WEST, Ferry_EventScript_DepartIslandWest
	@ delay 30
	@ hideobjectat OBJ_EVENT_ID_PLAYER, 0
	@ call Common_EventScript_FerryDepart
	return

	.include "data/scripts/cave_of_origin.inc"
	.include "data/scripts/kecleon.inc"

Common_EventScript_NameReceivedPartyMon::
	fadescreen FADE_TO_BLACK
	special ChangePokemonNickname
	waitstate
	return

Common_EventScript_PlayerHandedOverTheItem::
	bufferitemname STR_VAR_1, VAR_0x8004
	playfanfare MUS_OBTAIN_TMHM
	message gText_PlayerHandedOverTheItem
	waitmessage
	waitfanfare
	removeitem VAR_0x8004
	return

	.include "data/scripts/elite_four.inc"
	.include "data/scripts/check_furniture.inc"
	.include "data/text/record_mix.inc"
	.include "data/text/pc.inc"
	.include "data/text/pkmn_center_nurse.inc"
	.include "data/text/mart_clerk.inc"
	.include "data/text/obtain_item.inc"

@ The below and surf.inc could be split into some text/notices.inc
gText_MomOrDadMightLikeThisProgram::
	.string "{STR_VAR_1} might like this program.\n"
	.string "… … … … … … … … … … … … … … … …\p"
	.string "Better get going!$"

gText_WhichFloorWouldYouLike::
	.string "Welcome to LILYCOVE DEPARTMENT STORE.\p"
	.string "Which floor would you like?$"

gText_SandstormIsVicious::
	.string "The sandstorm is vicious.\n"
	.string "It's impossible to keep going.$"

gText_PokemonTrainerSchoolEmail::
	.string "There's an e-mail from POKéMON TRAINER\n"
	.string "SCHOOL.\p"
	.string "… … … … … …\p"
	.string "A POKéMON may learn up to four moves.\p"
	.string "A TRAINER's expertise is tested on the\n"
	.string "move sets chosen for POKéMON.\p"
	.string "… … … … … …$"

gText_PlayerHouseBootPC::
	.string "{PLAYER} booted up the PC.$"

gText_PokeblockLinkCanceled::
	.string "The link was canceled.$"

gText_UnusedNicknameReceivedPokemon::
	.string "Want to give a nickname to\n"
	.string "the {STR_VAR_2} you received?$"

gText_PlayerWhitedOut::
	.string "{PLAYER} is out of usable\n"
	.string "POKéMON!\p{PLAYER} whited out!$"

gText_RegisteredTrainerinPokeNav::
	.string "Registered {STR_VAR_1} {STR_VAR_2}\n"
	.string "in the POKéNAV.$"

gText_ComeBackWithSecretPower::
	.string "Do you know the TM SECRET POWER?\p"
	.string "Our group, we love the TM SECRET\n"
	.string "POWER.\p"
	.string "One of our members will give it to you.\n"
	.string "Come back and show me if you get it.\p"
	.string "We'll accept you as a member and sell\n"
	.string "you good stuff in secrecy.$"

gText_PokerusExplanation::
	.string "Your POKéMON may be infected with\n"
	.string "POKéRUS.\p"
	.string "Little is known about the POKéRUS\n"
	.string "except that they are microscopic life-\l"
	.string "forms that attach to POKéMON.\p"
	.string "While infected, POKéMON are said to\n"
	.string "grow exceptionally well.$"

gText_DoorOpenedFarAway::
	.string "It sounded as if a door opened\n"
	.string "somewhere far away.$"

gText_BigHoleInTheWall::
	.string "There is a big hole in the wall.$"

gText_SorryWirelessClubAdjustments::
	.string "I'm terribly sorry.\n"
	.string "The POKéMON WIRELESS CLUB is\l"
	.string "undergoing adjustments now.$"

gText_UndergoingAdjustments::
	.string "It appears to be undergoing\n"
	.string "adjustments…$"

@ Unused
gText_SorryTradeCenterInspections::
	.string "I'm terribly sorry. The TRADE CENTER\n"
	.string "is undergoing inspections.$"

@ Unused
gText_SorryRecordCornerPreparation::
	.string "I'm terribly sorry. The RECORD CORNER\n"
	.string "is under preparation.$"

gText_PlayerHandedOverTheItem::
	.string "{PLAYER} handed over the\n"
	.string "{STR_VAR_1}.$"

gText_ThankYouForAccessingMysteryGift::
	.string "Thank you for accessing the\n"
	.string "MYSTERY GIFT System.$"

gText_Sudowoodo_Attacked::
	.string "The weird tree doesn't like the\n"
	.string "WAILMER PAIL!\p"
	.string "The weird tree attacked!$"

gText_LegendaryFlewAway::
	.string "The {STR_VAR_1} flew away!$"

	.include "data/text/pc_transfer.inc"
	.include "data/text/questionnaire.inc"

	.include "data/scripts/select.inc"

	.include "data/scripts/field_poison.inc"

@ Unused
EventScript_CableClub_SetVarResult1::
	setvar VAR_RESULT, 1
	return

EventScript_CableClub_SetVarResult0::
	setvar VAR_RESULT, 0
	return

Common_EventScript_UnionRoomAttendant::
	@ call CableClub_EventScript_UnionRoomAttendant
	end

Common_EventScript_WirelessClubAttendant::
	@ call CableClub_EventScript_WirelessClubAttendant
	end

Common_EventScript_DirectCornerAttendant::
	@ call CableClub_EventScript_DirectCornerAttendant
	end

Common_EventScript_RemoveStaticPokemon::
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject VAR_LAST_TALKED
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

Common_EventScript_LegendaryFlewAway::
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject VAR_LAST_TALKED
	fadescreenswapbuffers FADE_FROM_BLACK
	bufferspeciesname STR_VAR_1, VAR_0x8004
	msgbox gText_LegendaryFlewAway, MSGBOX_DEFAULT
	release
	end


EventScript_WaterSudowoodo::
	@ lock
	@ faceplayer
	@ special DoWateringBerryTreeAnim
	@ waitstate
	@ waitse
	@ playse SE_SUDOWOODO_SHAKE
	@ applymovement LOCALID_SUDOWOODO, Movement_SudowoodoShake
	@ waitmovement 0
	@ msgbox gText_Sudowoodo_Attacked, MSGBOX_DEFAULT
	@ closemessage
	@ waitse
	@ playmoncry SPECIES_SUDOWOODO, CRY_MODE_ENCOUNTER
	@ delay 40
	@ waitmoncry
	@ setvar VAR_LAST_TALKED, LOCALID_SUDOWOODO
	@ setwildbattle SPECIES_SUDOWOODO, 40
	@ setflag FLAG_SYS_CTRL_OBJ_DELETE
	@ dowildbattle
	@ clearflag FLAG_SYS_CTRL_OBJ_DELETE
	@ specialvar VAR_RESULT, GetBattleOutcome
	@ goto_if_eq VAR_RESULT, B_OUTCOME_WON, EventScript_DefeatedSudowoodo
	@ goto_if_eq VAR_RESULT, B_OUTCOME_RAN, EventScript_DefeatedSudowoodo
	@ goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, EventScript_DefeatedSudowoodo
	@ setflag FLAG_DEFEATED_SUDOWOODO
	@ release
	end

EventScript_DefeatedSudowoodo::
	@ setflag FLAG_DEFEATED_SUDOWOODO
	@ goto Common_EventScript_RemoveStaticPokemon
	end

Movement_SudowoodoShake:
	face_right
	delay_8
	face_down
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_down
	delay_8
	face_left
	delay_8
	face_down
	step_end

gText_LinkStandby3::
	.string "Link standby…$"
gText_LinkRecordCouldntBeSaved::
	.string "There was an error of some sort.\n"
	.string "Your record could not be saved.$"

@------------------------------------------------------

	.include "data/scripts/pc_transfer.inc"
	.include "data/scripts/questionnaire.inc"
	.include "data/scripts/trainer_script.inc"
	.include "data/scripts/berry_tree.inc"
	.include "data/scripts/secret_base.inc"
	.include "data/scripts/cable_club.inc"
	.include "data/text/cable_club.inc"
	.include "data/scripts/contest_hall.inc"
	.include "data/text/contest_strings.inc"
	.include "data/text/contest_link.inc"
	.include "data/text/contest_painting.inc"
	.include "data/text/trick_house_mechadolls.inc"
	.include "data/scripts/tv.inc"
	.include "data/text/tv.inc"
	.include "data/scripts/interview.inc"
	@ .include "data/scripts/gabby_and_ty.inc"
	.include "data/text/pokemon_news.inc"
	.include "data/scripts/mauville_man.inc"
	.include "data/scripts/field_move_scripts.inc"
	.include "data/scripts/item_ball_scripts.inc"
	.include "data/scripts/profile_man.inc"
	.include "data/scripts/day_care.inc"
	.include "data/scripts/flash.inc"
	.include "data/scripts/berry_blender.inc"
	.include "data/text/mauville_man.inc"
	.include "data/text/trainers.inc"
	.include "data/scripts/repel.inc"
	.include "data/scripts/safari_zone.inc"
	.include "data/scripts/roulette.inc"
	.include "data/text/pokedex_rating.inc"
	.include "data/text/lottery_corner.inc"
	.include "data/text/event_ticket_1.inc"
	.include "data/text/braille.inc"
	.include "data/text/berries.inc"
	.include "data/text/shoal_cave.inc"
	.include "data/scripts/lilycove_lady.inc"
	.include "data/text/match_call.inc"
	.include "data/text/battle_dome.inc"
	@ .include "data/scripts/battle_pike.inc"
	.include "data/text/blend_master.inc"
	.include "data/text/battle_tent.inc"
	.include "data/text/event_ticket_2.inc"
	.include "data/text/move_tutors.inc"
	.include "data/scripts/move_tutors.inc"
	@ .include "data/scripts/trainer_hill.inc"
	.include "data/scripts/test_signpost.inc"
	.include "data/text/frontier_brain.inc"
	.include "data/text/save.inc"
	.include "data/text/birch_speech.inc"


	.include "data/maps/TrickHouseExt_Gatehouse/scripts.inc"

	.include "data/maps/Puzzle_Credits/scripts.inc"

	.include "data/maps/Puzzle_ThinIce/scripts.inc"

	.include "data/maps/ThinIce_F2/scripts.inc"

	.include "data/maps/SlateportCity_Harbor/scripts.inc"
	.include "data/maps/SlateportCity_ContestLobby/scripts.inc"
	.include "data/maps/SlateportCity_ContestHall/scripts.inc"

	.include "data/maps/Puzzle_BlockPushing/scripts.inc"

	.include "data/maps/Route110_Cutscene/scripts.inc"

	.include "data/maps/SlateportCity_PokemonFanClub/scripts.inc"

	.include "data/maps/SlateportCity_OceanicMuseum_1F/scripts.inc"

	.include "data/maps/SlateportCity_OceanicMuseum_2F/scripts.inc"

	.include "data/maps/SlateportCity_SeashoreHouse/scripts.inc"

	.include "data/maps/TestFollowerMap/scripts.inc"

	.include "data/maps/TrickHouseRestroomOld/scripts.inc"
	.include "data/maps/TrickHouseRestroom_Choose/scripts.inc"
	.include "data/maps/TrickHouseEntrance_Intro/scripts.inc"


	.include "data/maps/TestPyramidTileset/scripts.inc"

	.include "data/maps/TrickHouseRestroom_Battle/scripts.inc"

	.include "data/maps/TrickHouseEnd_Old/scripts.inc"

	.include "data/maps/Puzzle_Racconnaissance/scripts.inc"

	.include "data/maps/Puzzle_TooHardToSee/scripts.inc"

	.include "data/maps/Puzzle_TooManyPaths/scripts.inc"

	.include "data/maps/Puzzle_TooManyBoulders/scripts.inc"

	.include "data/maps/Puzzle_TooManyGates/scripts.inc"

	.include "data/maps/Puzzle_TooManyArrows/scripts.inc"

	.include "data/maps/Puzzle_TooMuchPolish/scripts.inc"
