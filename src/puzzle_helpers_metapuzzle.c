#include "global.h"
#include "global.fieldmap.h"
#include "event_data.h"
#include "malloc.h"
#include "puzzle_helpers.h"
#include "decompress.h"
#include "field_camera.h"
#include "global.fieldmap.h"
#include "field_message_box.h"
#include "field_player_avatar.h"
#include "fieldmap.h"
#include "palette.h"
#include "random.h"
#include "strings.h"
#include "string_util.h"
#include "sound.h"
#include "script.h"
#include "text.h"
#include "task.h"
#include "item.h"
#include "mgba.h"
#include "trickhouse.h"
#include "bg.h"
#include "script.h"
#include "window.h"
#include "io_reg.h"
#include "menu.h"
#include "gpu_regs.h"
#include "overworld.h"
#include "graphics.h"
#include "scanline_effect.h"
#include "text_window.h"
#include "constants/global.h"
#include "constants/rgb.h"
#include "constants/maps.h"
#include "constants/flags.h"
#include "constants/metatile_labels.h"
#include "constants/event_object_movement.h"
#include "constants/songs.h"
#include "constants/event_objects.h"
#include "constants/map_groups.h"
#include "constants/vars.h"
#include "constants/species.h"
#include "constants/items.h"

// Reference to an assembly defined constant, the start of the ROM
// We don't actually use the value, just the address it's at.
extern const int Start;

// width = lower 8bits, height = upper 8 bits
#define VAR_GRID_SIZE              VAR_PUZZLE_00
#define VAR_ROOM_ID_0_0            VAR_PUZZLE_01
#define VAR_ROOM_RESERVE_END       VAR_PUZZLE_10
#define VAR_BACKUP_ID_0_0          VAR_PUZZLE_30
#define VAR_BACKUP_RESERVE_END     VAR_PUZZLE_3F

#define FLAG_VISITED_RM0      FLAG_PUZZLE_20
// FLAG_PUZZLE_20 (+25) = Visited/Finished room flags
// ...FLAG_PUZZLE_39
// 
#define FLAG_MET_TRICK_MASTER  FLAG_PUZZLE_4F 
#define FLAG_HIDE_SCROLL       FLAG_PUZZLE_4E


#define VAR_LOC_SCROLL        VAR_PUZZLE_11
#define VAR_LOC_CUT           VAR_PUZZLE_12
#define VAR_LOC_ROCK_SMASH    VAR_PUZZLE_13
#define VAR_LOC_STRENGTH      VAR_PUZZLE_14
#define VAR_LOC_DIVE          VAR_PUZZLE_15
#define VAR_LOC_WATERFALL     VAR_PUZZLE_16
#define VAR_LOC_SURF          VAR_PUZZLE_17
// First pedestal is always in Lavaridge
#define VAR_LOC_PEDESTAL2     VAR_PUZZLE_18
#define VAR_LOC_PEDESTAL3     VAR_PUZZLE_19
#define VAR_LOC_PEDESTAL4     VAR_PUZZLE_1A

#define MAP_PLACEHOLDER_N     MAP_META_EMPTY_SW
#define MAP_PLACEHOLDER_S     MAP_META_EMPTY_NE
#define MAP_PLACEHOLDER_W     MAP_META_EMPTY_SE
#define MAP_PLACEHOLDER_E     MAP_META_EMPTY_NW
#define MAP_PLACEHOLDER_NW    MAP_META_EMPTY_S
#define MAP_PLACEHOLDER_NE    MAP_META_EMPTY_NS
#define MAP_PLACEHOLDER_SW    MAP_META_EMPTY_WE
#define MAP_PLACEHOLDER_SE    MAP_META_EMPTY_FILLED

#define TILE_SPEED  Q_8_8(3.0)
#define TILE_SPREAD 32
#define TILE_ORIGIN_X 72
#define TILE_ORIGIN_Y 32

#define tTileId data[0]
#define tCurrX data[1]
#define tCurrY data[2]

enum {
	SS_TILE_BACK,
	SS_TILE_NORTH_EXIT,
	SS_TILE_SOUTH_EXIT,
	SS_TILE_WEST_EXIT,
	SS_TILE_EAST_EXIT,
};
enum {
	TAG_TILE_BASE = 0x10,
	TAG_TILE_LOCKED,
	TAG_TILE_VISITED,
	TAG_ICON_UNKNOWN,
	TAG_ICON_LAVARIDGE,
	TAG_ICON_FINAL,
	TAG_ICON_LEDGE,
	TAG_ICON_ICE,
	TAG_ICON_LOG,
	TAG_ICON_BIKE,
	TAG_ICON_STAGE,
	TAG_ICON_ZIGGY,
	TAG_ICON_FOREST,
	TAG_ICON_ZIP,
	TAG_ICON_KOGA,
	TAG_ICON_FIRE,
	TAG_ICON_DIVE,
	TAG_ICON_BERRY,
	TAG_PAL_NPC1,
	TAG_PAL_NPC2,
	TAG_PAL_NPC3,
	TAG_PAL_NPC4,
};

static void CB2_LoadSlidingTile(void);
static void CB2_SlidingTileMain(void);
static void CB2_EndSlidingTile(void);
static void VBlankCB_SlidingTile(void);

static void Task_WaitForFade(u8 taskId);
static void Task_HandleSlidingTileInput(u8 taskId);

static void SpriteCB_TileSlide(struct Sprite *sprite);

#pragma region 
///////////////////////////////////////////////////////////////////////////////
// Puzzle: Secret Caverns
// MAP_PUZZLE_META_PUZZLE

#pragma push_macro("MAP_GROUP")
#pragma push_macro("MAP_NUM")

#undef MAP_GROUP
#undef MAP_NUM

#define MAP_GROUP(map) (map >> 8)
#define MAP_NUM(map) (map & 0xFF)

static EWRAM_DATA struct MapConnection sWorkingConnection = {0};

struct MetaRoomInfo {
	u8 tileTag;
	u8 palTag;
	u16 requiredItem;
	bool32 north:1;
	bool32 south:1;
	bool32 west:1;
	bool32 east:1;
	bool32 supplies_pedestal:1;
	bool32 supplies_item:1;
	bool32 requires_scroll:1;
	bool32 requires_cut:1;
	bool32 requires_rocksmash:1;
	bool32 requires_strength:1;
	bool32 requires_surf:1;
	bool32 requires_dive:1;
	bool32 requires_waterfall:1;
	const struct ObjectEventTemplate* connObj;
};

// In-connection objects
static const struct ObjectEventTemplate sConnObject_EndDoor = {
	.graphicsId = OBJ_EVENT_GFX_TRICK_DOOR_STONE_ROOM,
	.x = 18, .y = 1, .elevation = 3,
};
static const struct ObjectEventTemplate sConnObject_RegiIce = {
	.graphicsId = OBJ_EVENT_GFX_BIG_REGICE_DOLL,
	.x = 36, .y = 19, .elevation = 3,
};
static const struct ObjectEventTemplate sConnObject_Ziggy = {
	.graphicsId = OBJ_EVENT_GFX_ZIGZAGOON_1,
	.movementType = MOVEMENT_TYPE_LOOK_AROUND,
	.x = 16, .y = 1, .elevation = 3,
};
static const struct ObjectEventTemplate sConnObject_Submarine = {
	.graphicsId = OBJ_EVENT_GFX_SUBMARINE_SHADOW,
	.movementType = MOVEMENT_TYPE_FACE_RIGHT,
	.x = 35, .y = 18, .elevation = 3,
};

static const struct MetaRoomInfo sMetaRoomInfo[] = {
	[MAP_NUM(MAP_META_NULL_ROOM)] = {
		.tileTag=TAG_ICON_UNKNOWN, .palTag=TAG_ICON_UNKNOWN,
	},
	[MAP_NUM(MAP_META_EMPTY_FILLED)] = {
		.tileTag=TAG_ICON_UNKNOWN, .palTag=TAG_ICON_UNKNOWN,
	},
	[MAP_NUM(MAP_META_EMPTY_NW)] = {
		.north=1, .west=1, 
		.tileTag=TAG_ICON_UNKNOWN, .palTag=TAG_ICON_UNKNOWN, 
		.requiredItem=ITEM_NONE,
	},
	[MAP_NUM(MAP_META_EMPTY_NE)] = {
		.north=1, .east=1, 
		.tileTag=TAG_ICON_UNKNOWN, .palTag=TAG_ICON_UNKNOWN, 
		.requiredItem=ITEM_NONE,
	},
	[MAP_NUM(MAP_META_EMPTY_SW)] = {
		.south=1, .west=1, 
		.tileTag=TAG_ICON_UNKNOWN, .palTag=TAG_ICON_UNKNOWN, 
		.requiredItem=ITEM_NONE,
	},
	[MAP_NUM(MAP_META_EMPTY_SE)] = {
		.south=1, .east=1, 
		.tileTag=TAG_ICON_UNKNOWN, .palTag=TAG_ICON_UNKNOWN, 
		.requiredItem=ITEM_NONE,
	},
	[MAP_NUM(MAP_META_EMPTY_NS)] = {
		.north=1, .south=1,
		.tileTag=TAG_ICON_UNKNOWN, .palTag=TAG_ICON_UNKNOWN, 
		.requiredItem=ITEM_NONE,
	},
	[MAP_NUM(MAP_META_EMPTY_WE)] = {
		.west=1,  .east=1, 
		.tileTag=TAG_ICON_UNKNOWN, .palTag=TAG_ICON_UNKNOWN, 
		.requiredItem=ITEM_NONE,
	},
	[MAP_NUM(MAP_META_EMPTY_S)] = {
		.south=1,
		.tileTag=TAG_ICON_UNKNOWN, .palTag=TAG_ICON_UNKNOWN, 
		.requiredItem=ITEM_NONE,
	},
	[MAP_NUM(MAP_META_ENTRANCE)] = {
		.north=1,
		.tileTag=TAG_ICON_UNKNOWN, .palTag=TAG_ICON_UNKNOWN, 
		.requiredItem=ITEM_NONE,
	},
	[MAP_NUM(MAP_META_LAVARIDGE_SPRINGS)] = {
		.south=1, .east=1, 
		.tileTag=TAG_ICON_LAVARIDGE, .palTag=TAG_PAL_NPC1,
		.supplies_pedestal=TRUE,
		.requiredItem=ITEM_META_ITEM_LAVARIDGE,
	},
	[MAP_NUM(MAP_META_LEDGE_ROOM)] = {
		.north=1, .east=1, 
		.tileTag=TAG_ICON_LEDGE, .palTag=TAG_PAL_NPC1,
		.supplies_item=TRUE,
		.requiredItem=ITEM_META_ITEM_LEDGE,
	},
	[MAP_NUM(MAP_META_FINAL_BLUFF)] = {
		.west=1, 
		.tileTag=TAG_ICON_FINAL, .palTag=TAG_PAL_NPC1,
		.requiredItem=ITEM_META_ITEM_FINAL_BLUFF,
		.requires_scroll=TRUE,
		.requires_cut=TRUE,
		.requires_dive=TRUE,
		.requires_rocksmash=TRUE,
		.requires_strength=TRUE,
		.requires_surf=TRUE,
		.requires_waterfall=TRUE,
		.connObj=&sConnObject_EndDoor,
	},
	[MAP_NUM(MAP_META_ICE_CORNER)] = {
		.south=1, .west=1, 
		.tileTag=TAG_ICON_ICE, .palTag=TAG_ICON_ICE,
		.requiredItem=ITEM_META_ITEM_ICE_CORNER,
		.supplies_item=TRUE,
		.connObj=&sConnObject_RegiIce,
	},
	[MAP_NUM(MAP_META_LOG_FLOTILLA)] = {
		.south=1, .east=1, 
		.tileTag=TAG_ICON_LOG, .palTag=TAG_PAL_NPC3,
		.supplies_item=TRUE,
		.requiredItem=ITEM_META_ITEM_LOG_FLOAT,
	},
	[MAP_NUM(MAP_META_BIKE_PATH)] = {
		.south=1, .north=1,
		.tileTag=TAG_ICON_BIKE, .palTag=TAG_PAL_NPC3,
		.supplies_pedestal=TRUE,
		.requiredItem=ITEM_META_ITEM_BIKE_PATH,
	},
	[MAP_NUM(MAP_META_POKE_STAGE)] = {
		.south=1,
		.tileTag=TAG_ICON_STAGE, .palTag=TAG_PAL_NPC1,
		.supplies_item=TRUE,
		.requiredItem=ITEM_META_ITEM_POKE_STAGE,
	},
	[MAP_NUM(MAP_META_ZIGGY_ROOM)] = {
		.south=1, .west=1, 
		.tileTag=TAG_ICON_ZIGGY, .palTag=TAG_PAL_NPC1,
		.supplies_item=TRUE,
		.requires_cut=TRUE,
		.requiredItem=ITEM_META_ITEM_ZIGGY,
		.connObj=&sConnObject_Ziggy,
	},
	[MAP_NUM(MAP_META_FOREST_CLEARING)] = {
		.south=1, .east=1, 
		.tileTag=TAG_ICON_FOREST, .palTag=TAG_PAL_NPC3,
		.supplies_item=TRUE,
		.requiredItem=ITEM_META_ITEM_FOREST,
	},
	[MAP_NUM(MAP_META_ZIP_SLIDE)] = {
		.west=1,  .east=1, 
		.tileTag=TAG_ICON_ZIP, .palTag=TAG_PAL_NPC2,
		.requiredItem=ITEM_META_ITEM_ZIP_SLIDE,
	},
	[MAP_NUM(MAP_META_KOGA_ELBOW)] = {
		.north=1, .west=1, 
		.tileTag=TAG_ICON_KOGA, .palTag=TAG_PAL_NPC4,
		.supplies_item=TRUE,
		.requiredItem=ITEM_META_ITEM_KOGA,
	},
	[MAP_NUM(MAP_META_SUBDUCTION_ZONE)] = {
		.west=1,  .east=1, 
		.tileTag=TAG_ICON_FIRE, .palTag=TAG_PAL_NPC2,
		.requiredItem=ITEM_META_ITEM_FIRE,
	},
	[MAP_NUM(MAP_META_DIVE_MAZE)] = {
		.north=1, .south=1,
		.tileTag=TAG_ICON_DIVE, .palTag=TAG_PAL_NPC1,
		.supplies_item=TRUE,
		.requires_surf=TRUE,
		.requiredItem=ITEM_META_ITEM_DIVE,
		.connObj=&sConnObject_Submarine,
	},
	[MAP_NUM(MAP_META_BERRY_ROOM)] = {
		.north=1, .east=1, 
		.tileTag=TAG_ICON_BERRY, .palTag=TAG_ICON_BERRY,
		.supplies_pedestal=TRUE,
		.requiredItem=ITEM_META_ITEM_BERRY,
	}, /*
	[MAP_NUM(MAP_META_ROOM_15)] = {
		.north=1, .west=1, 
		.tileTag=TAG_ICON_UNKNOWN, .palTag=TAG_ICON_UNKNOWN, 
		.requiredItem=ITEM_META_ITEM_SEEDOT,
	}, //*/
};

const u16 sMetaRoom_FallbackList_s4_1x1[] = { MAP_META_BERRY_ROOM, MAP_META_EMPTY_NE, MAP_NONE }; // Has Pedestal
const u16 sMetaRoom_FallbackList_s4_2x1[] = { MAP_META_LOG_FLOTILLA, MAP_META_EMPTY_SE, MAP_NONE }; // Has Surf
const u16 sMetaRoom_FallbackList_s4_3x1[] = { MAP_META_FINAL_BLUFF, MAP_NONE };
const u16 sMetaRoom_FallbackList_s4_4x1[] = { MAP_META_POKE_STAGE, MAP_META_EMPTY_S, MAP_NONE }; // Has Scroll

const u16 sMetaRoom_FallbackList_s4_1x2[] = { MAP_META_ZIGGY_ROOM, MAP_META_EMPTY_SW, MAP_NONE }; // Has Waterfall
const u16 sMetaRoom_FallbackList_s4_2x2[] = { MAP_META_ICE_CORNER, MAP_META_EMPTY_SW, MAP_NONE };
const u16 sMetaRoom_FallbackList_s4_3x2[] = { /*MAP_META_ROOM_15,*/ MAP_META_EMPTY_NW, MAP_NONE };
const u16 sMetaRoom_FallbackList_s4_4x2[] = { MAP_META_SUBDUCTION_ZONE, MAP_META_EMPTY_WE, MAP_NONE }; // Has Strength

const u16 sMetaRoom_FallbackList_s4_1x3[] = { MAP_META_DIVE_MAZE, MAP_META_EMPTY_NS, MAP_NONE }; // Has Dive
const u16 sMetaRoom_FallbackList_s4_2x3[] = { MAP_META_BIKE_PATH, MAP_META_EMPTY_NS, MAP_NONE }; // Has Pedestal
const u16 sMetaRoom_FallbackList_s4_3x3[] = { MAP_META_FOREST_CLEARING, MAP_META_EMPTY_SE, MAP_NONE }; // Has Pedestal, Cut
const u16 sMetaRoom_FallbackList_s4_4x3[] = { MAP_META_KOGA_ELBOW, MAP_META_EMPTY_NW, MAP_NONE };

const u16 sMetaRoom_FallbackList_s4_1x4[] = { MAP_META_LEDGE_ROOM, MAP_META_EMPTY_NE, MAP_NONE }; // Has Rock Smash
const u16 sMetaRoom_FallbackList_s4_2x4[] = { MAP_META_ZIP_SLIDE, MAP_META_EMPTY_WE, MAP_NONE };
const u16 sMetaRoom_FallbackList_s4_3x4[] = { MAP_META_LAVARIDGE_SPRINGS, MAP_NONE }; // Has Pedestal
const u16 sMetaRoom_FallbackList_s4_4x4[] = { MAP_META_NULL_ROOM, MAP_NONE };


const u16 sMetaRoom_FallbackList_s3_1x1[] = { MAP_META_LOG_FLOTILLA, MAP_META_FOREST_CLEARING, MAP_META_EMPTY_SE, MAP_NONE }; // Has Surf/Cut
const u16 sMetaRoom_FallbackList_s3_2x1[] = { MAP_META_BERRY_ROOM, MAP_META_LEDGE_ROOM, MAP_META_EMPTY_NE, MAP_NONE }; // Has Pedestal, Rock Smash
const u16 sMetaRoom_FallbackList_s3_3x1[] = { MAP_META_ZIP_SLIDE, MAP_META_SUBDUCTION_ZONE, MAP_META_EMPTY_WE, MAP_NONE }; // Has Strength

const u16 sMetaRoom_FallbackList_s3_1x2[] = { MAP_META_FINAL_BLUFF, MAP_NONE }; // Has Scroll
const u16 sMetaRoom_FallbackList_s3_2x2[] = { MAP_META_DIVE_MAZE, MAP_META_BIKE_PATH, MAP_META_EMPTY_NS, MAP_NONE }; // Has Pedestal, Dive
const u16 sMetaRoom_FallbackList_s3_3x2[] = { MAP_META_KOGA_ELBOW, /*MAP_META_ROOM_15,*/ MAP_META_EMPTY_NW, MAP_NONE }; // Has Cut/Surf

const u16 sMetaRoom_FallbackList_s3_1x3[] = { MAP_META_ZIGGY_ROOM, MAP_META_ICE_CORNER, MAP_META_EMPTY_SW, MAP_NONE }; // Has Pedestal, Waterfall
const u16 sMetaRoom_FallbackList_s3_2x3[] = { MAP_META_LAVARIDGE_SPRINGS, MAP_NONE }; // Has Pedestal
const u16 sMetaRoom_FallbackList_s3_3x3[] = { MAP_META_NULL_ROOM, MAP_NONE };

/*
Final Bluff Skips:
Cut => Bike over trees
Strength => Remove Strength Boulder
Rock Smash => Remove Rock Smash Rock
Surf => <cannot skip>
Dive => Bike over trees?
Waterfall => Rocky Ridge climb
*/

static u16 MetaPuzzle_GetRoomForSlot(const u16* fallbackList) {
	mgba_printf(MGBA_LOG_INFO, "MetaPuzzle_GetRoomForSlot (%x)", fallbackList);
	for(; TRUE; fallbackList++) {
		u16 roomId = fallbackList[0];
		if (roomId == MAP_NONE) {
			// Reached end of list sentinel, error out!
			mgba_printf(MGBA_LOG_INFO, "Reached end of list sentinel, error out!");
			VarSet(VAR_RESULT, 0);
			VarSet(VAR_GRID_SIZE, 0);
			return 0xFFFF;
		}
		// sanity check
		mgba_printf(MGBA_LOG_INFO, "mapnum=%d tileTag=%d", MAP_NUM(roomId), sMetaRoomInfo[MAP_NUM(roomId)].tileTag);
		MGBA_ASSERT(sMetaRoomInfo[MAP_NUM(roomId)].tileTag >= TAG_ICON_UNKNOWN);
		
		u16 item = sMetaRoomInfo[MAP_NUM(roomId)].requiredItem;
		if (item == ITEM_NONE) return roomId;
		if (CheckBagHasItem(item, 1)) return roomId;
	}
}

static void MetaPuzzle_SetupPatheticLayout() {
	VarSet(VAR_RESULT, 1);
	VarSet(VAR_GRID_SIZE, 0);
	for (int i = 0; VAR_ROOM_ID_0_0 + i < VAR_ROOM_RESERVE_END; i++) {
		VarSet(VAR_ROOM_ID_0_0 + i, 0);
	}
}

static void MetaPuzzle_Setup2x1Layout() {
	VarSet(VAR_RESULT, 2);
	VarSet(VAR_GRID_SIZE, (1 << 8) | (2));
	VarSet(VAR_ROOM_ID_0_0 + 0, MAP_META_LAVARIDGE_SPRINGS);
	VarSet(VAR_ROOM_ID_0_0 + 1, MAP_META_FINAL_BLUFF);
	for (int i = 2; VAR_ROOM_ID_0_0 + i < VAR_ROOM_RESERVE_END; i++) {
		VarSet(VAR_ROOM_ID_0_0 + i, 0);
	}
	
	VarSet(VAR_LOC_SCROLL, MAP_META_LAVARIDGE_SPRINGS);
	VarSet(VAR_LOC_CUT, 0);
	VarSet(VAR_LOC_ROCK_SMASH, 0);
	VarSet(VAR_LOC_STRENGTH, 0);
	VarSet(VAR_LOC_DIVE, 0);
	VarSet(VAR_LOC_WATERFALL, 0);
	VarSet(VAR_LOC_SURF, 0);
	VarSet(VAR_LOC_PEDESTAL2, 0);
	VarSet(VAR_LOC_PEDESTAL3, 0);
	VarSet(VAR_LOC_PEDESTAL4, 0);
	
	for (int i = 0; VAR_BACKUP_ID_0_0 + i < VAR_BACKUP_RESERVE_END; i++) {
		VarSet(VAR_BACKUP_ID_0_0 + i, VarGet(VAR_ROOM_ID_0_0 + i));
	}
}

static void MetaPuzzle_Setup3x3Layout() {
	VarSet(VAR_RESULT, 3);
	VarSet(VAR_GRID_SIZE, (3 << 8) | (3));
	
	VarSet(VAR_ROOM_ID_0_0 + 0, MetaPuzzle_GetRoomForSlot(sMetaRoom_FallbackList_s3_1x1));
	VarSet(VAR_ROOM_ID_0_0 + 1, MetaPuzzle_GetRoomForSlot(sMetaRoom_FallbackList_s3_2x1));
	VarSet(VAR_ROOM_ID_0_0 + 2, MetaPuzzle_GetRoomForSlot(sMetaRoom_FallbackList_s3_3x1));
	
	VarSet(VAR_ROOM_ID_0_0 + 3, MetaPuzzle_GetRoomForSlot(sMetaRoom_FallbackList_s3_1x2));
	VarSet(VAR_ROOM_ID_0_0 + 4, MetaPuzzle_GetRoomForSlot(sMetaRoom_FallbackList_s3_2x2));
	VarSet(VAR_ROOM_ID_0_0 + 5, MetaPuzzle_GetRoomForSlot(sMetaRoom_FallbackList_s3_3x2));
	
	VarSet(VAR_ROOM_ID_0_0 + 6, MetaPuzzle_GetRoomForSlot(sMetaRoom_FallbackList_s3_1x3));
	VarSet(VAR_ROOM_ID_0_0 + 7, MetaPuzzle_GetRoomForSlot(sMetaRoom_FallbackList_s3_2x3));
	VarSet(VAR_ROOM_ID_0_0 + 8, MetaPuzzle_GetRoomForSlot(sMetaRoom_FallbackList_s3_3x3));
	
	for (int i = 9; VAR_ROOM_ID_0_0 + i < VAR_ROOM_RESERVE_END; i++) {
		VarSet(VAR_ROOM_ID_0_0 + i, 0);
	}
	
	VarSet(VAR_LOC_SCROLL, MAP_META_FINAL_BLUFF);
	VarSet(VAR_LOC_ROCK_SMASH, VarGet(VAR_ROOM_ID_0_0 + 1));
	VarSet(VAR_LOC_STRENGTH, VarGet(VAR_ROOM_ID_0_0 + 2));
	VarSet(VAR_LOC_DIVE, VarGet(VAR_ROOM_ID_0_0 + 4));
	VarSet(VAR_LOC_WATERFALL, VarGet(VAR_ROOM_ID_0_0 + 6));
	// Put cut in forest clearing and surf in Log Flotilla, and Koga gets the leftover
	if (VarGet(VAR_ROOM_ID_0_0 + 0) == MAP_META_FOREST_CLEARING) {
		VarSet(VAR_LOC_CUT, VarGet(VAR_ROOM_ID_0_0 + 0));
		VarSet(VAR_LOC_SURF, VarGet(VAR_ROOM_ID_0_0 + 5));
	} else {
		VarSet(VAR_LOC_CUT, VarGet(VAR_ROOM_ID_0_0 + 5));
		VarSet(VAR_LOC_SURF, VarGet(VAR_ROOM_ID_0_0 + 0));
	}
	
	VarSet(VAR_LOC_PEDESTAL2, VarGet(VAR_ROOM_ID_0_0 + 1));
	VarSet(VAR_LOC_PEDESTAL3, VarGet(VAR_ROOM_ID_0_0 + 4));
	VarSet(VAR_LOC_PEDESTAL4, VarGet(VAR_ROOM_ID_0_0 + 6));
	
	for (int i = 0; VAR_BACKUP_ID_0_0 + i < VAR_BACKUP_RESERVE_END; i++) {
		VarSet(VAR_BACKUP_ID_0_0 + i, VarGet(VAR_ROOM_ID_0_0 + i));
	}
}

static void MetaPuzzle_Setup4x4Layout() {
	VarSet(VAR_RESULT, 4);
	VarSet(VAR_GRID_SIZE, (4 << 8) | (4));
	
	VarSet(VAR_ROOM_ID_0_0 + 0, MetaPuzzle_GetRoomForSlot(sMetaRoom_FallbackList_s4_1x1));
	VarSet(VAR_ROOM_ID_0_0 + 1, MetaPuzzle_GetRoomForSlot(sMetaRoom_FallbackList_s4_2x1));
	VarSet(VAR_ROOM_ID_0_0 + 2, MetaPuzzle_GetRoomForSlot(sMetaRoom_FallbackList_s4_3x1));
	VarSet(VAR_ROOM_ID_0_0 + 3, MetaPuzzle_GetRoomForSlot(sMetaRoom_FallbackList_s4_4x1));
	
	VarSet(VAR_ROOM_ID_0_0 + 4, MetaPuzzle_GetRoomForSlot(sMetaRoom_FallbackList_s4_1x2));
	VarSet(VAR_ROOM_ID_0_0 + 5, MetaPuzzle_GetRoomForSlot(sMetaRoom_FallbackList_s4_2x2));
	VarSet(VAR_ROOM_ID_0_0 + 6, MetaPuzzle_GetRoomForSlot(sMetaRoom_FallbackList_s4_3x2));
	VarSet(VAR_ROOM_ID_0_0 + 7, MetaPuzzle_GetRoomForSlot(sMetaRoom_FallbackList_s4_4x2));
	
	VarSet(VAR_ROOM_ID_0_0 + 8, MetaPuzzle_GetRoomForSlot(sMetaRoom_FallbackList_s4_1x3));
	VarSet(VAR_ROOM_ID_0_0 + 9, MetaPuzzle_GetRoomForSlot(sMetaRoom_FallbackList_s4_2x3));
	VarSet(VAR_ROOM_ID_0_0 +10, MetaPuzzle_GetRoomForSlot(sMetaRoom_FallbackList_s4_3x3));
	VarSet(VAR_ROOM_ID_0_0 +11, MetaPuzzle_GetRoomForSlot(sMetaRoom_FallbackList_s4_4x3));
	
	VarSet(VAR_ROOM_ID_0_0 +12, MetaPuzzle_GetRoomForSlot(sMetaRoom_FallbackList_s4_1x4));
	VarSet(VAR_ROOM_ID_0_0 +13, MetaPuzzle_GetRoomForSlot(sMetaRoom_FallbackList_s4_2x4));
	VarSet(VAR_ROOM_ID_0_0 +14, MetaPuzzle_GetRoomForSlot(sMetaRoom_FallbackList_s4_3x4));
	VarSet(VAR_ROOM_ID_0_0 +15, MetaPuzzle_GetRoomForSlot(sMetaRoom_FallbackList_s4_4x4));
	
	for (int i = 16; VAR_ROOM_ID_0_0 + i < VAR_ROOM_RESERVE_END; i++) { // this loop probably never runs
		VarSet(VAR_ROOM_ID_0_0 + i, 0);
	}
	
	VarSet(VAR_LOC_SCROLL, VarGet(VAR_ROOM_ID_0_0 + 3));
	if (VarGet(VAR_ROOM_ID_0_0 + 3) == MAP_META_POKE_STAGE) {
		FlagSet(FLAG_HIDE_SCROLL);
	}
	VarSet(VAR_LOC_CUT, VarGet(VAR_ROOM_ID_0_0 + 10));
	VarSet(VAR_LOC_ROCK_SMASH, VarGet(VAR_ROOM_ID_0_0 + 12));
	VarSet(VAR_LOC_STRENGTH, VarGet(VAR_ROOM_ID_0_0 + 7));
	VarSet(VAR_LOC_DIVE, VarGet(VAR_ROOM_ID_0_0 + 8));
	VarSet(VAR_LOC_WATERFALL, VarGet(VAR_ROOM_ID_0_0 + 4));
	VarSet(VAR_LOC_SURF, VarGet(VAR_ROOM_ID_0_0 + 1));
	VarSet(VAR_LOC_PEDESTAL2, VarGet(VAR_ROOM_ID_0_0 + 0));
	VarSet(VAR_LOC_PEDESTAL3, VarGet(VAR_ROOM_ID_0_0 + 9));
	VarSet(VAR_LOC_PEDESTAL4, VarGet(VAR_ROOM_ID_0_0 + 10));
	
	for (int i = 0; VAR_BACKUP_ID_0_0 + i < VAR_BACKUP_RESERVE_END; i++) {
		VarSet(VAR_BACKUP_ID_0_0 + i, VarGet(VAR_ROOM_ID_0_0 + i));
	}
}

void MetaPuzzle_DeterminePuzzleSetup(struct ScriptContext* ctx)
{
	// Count all the objects collected, by exit configuration
	// - If there's any configurations which have 0, then this has to be a 3x3 puzzle
	// - Otherwise, this can be a 4x4 puzzle
	// - If either Final Bluff or Lavaridge Springs are missing (should never happen), goto pathetic configuration as failsafe
	u8 nw=0, ne=0, sw=0, se=0, ns=0, we=0, ss=0;
	u8 req=0, opt=0;
	
	VarSet(VAR_RESULT, 0);
	
	for (int i=0; i < ARRAY_COUNT(sMetaRoomInfo); i++) {
		u16 item = sMetaRoomInfo[i].requiredItem;
		if (item == ITEM_NONE) continue;
		if (!CheckBagHasItem(item, 1)) continue;
		
		if (i == MAP_NUM(MAP_META_LAVARIDGE_SPRINGS)) req++;
		else if (i == MAP_NUM(MAP_META_FINAL_BLUFF)) req++;
		else if (i == MAP_NUM(MAP_META_POKE_STAGE)) ss++;
		else if (sMetaRoomInfo[i].north && sMetaRoomInfo[i].west) nw++;
		else if (sMetaRoomInfo[i].north && sMetaRoomInfo[i].east) ne++;
		else if (sMetaRoomInfo[i].south && sMetaRoomInfo[i].west) sw++;
		else if (sMetaRoomInfo[i].south && sMetaRoomInfo[i].east) se++;
		else if (sMetaRoomInfo[i].north && sMetaRoomInfo[i].south) ns++;
		else if (sMetaRoomInfo[i].west && sMetaRoomInfo[i].east) we++;
	}
	
	mgba_printf(MGBA_LOG_INFO, "Results:  nw=%d, ne=%d, sw=%d, se=%d, ns=%d, we=%d, ss=%d", nw, ne, sw, se, ns, we, ss);
	mgba_printf(MGBA_LOG_INFO, "Results2: req=%d, opt=%d", req, opt);
	
	// The two required rooms are somehow not present, goto failsafe
	if (req < 2) {
		MetaPuzzle_SetupPatheticLayout();
		return;
	}
	// Check for how many room configurations we have
	if (nw > 0) opt++;
	if (ne > 0) opt++;
	if (sw > 0) opt++;
	if (se > 0) opt++;
	if (ns > 0) opt++;
	if (we > 0) opt++;
	// If we have to fill in too many rooms with empty rooms, goto failsafe
	if (opt + req < 5) { // out of 8 rooms, 4+ need to be empty
		MetaPuzzle_Setup2x1Layout();
		return;
	}
	if (opt + req < 8) { // Out of 8 rooms, 1+ need to be empty
		MetaPuzzle_Setup3x3Layout();
		return;
	}
	// Check for multi configurations
	if (ss > 0) opt++;
	if (nw > 1) opt++;
	if (ne > 1) opt++;
	if (sw > 1) opt++;
	if (se > 1) opt++;
	if (ns > 1) opt++;
	if (we > 1) opt++;
	if (opt + req < 11) { // Out of 15 rooms, 4+ need to be empty
		MetaPuzzle_Setup3x3Layout();
		return;
	}
	MetaPuzzle_Setup4x4Layout();
	return;
}

void MetaPuzzle_RestorePuzzleLayout(struct ScriptContext* ctx)
{
	for (int i = 0; VAR_BACKUP_ID_0_0 + i < VAR_BACKUP_RESERVE_END; i++) {
		VarSet(VAR_ROOM_ID_0_0 + i, VarGet(VAR_BACKUP_ID_0_0 + i));
	}
	InitMap();
}


#pragma endregion

#pragma region 
//-----------------------------------------------------------------------------
// Engine Helper Functions

u16* MetaPuzzle_GetRoomGridVarPointer(int x, int y) {
	u8 width  = (VarGet(VAR_GRID_SIZE) >> 0) & 0xFF;
	u8 height = (VarGet(VAR_GRID_SIZE) >> 8) & 0xFF;
	
	if (0 <= x && x < width && 0 <= y && y < height) {
		return &GetVarPointer(VAR_ROOM_ID_0_0)[(y * width) + x];
	}
	return NULL;
}

u16 MetaPuzzle_GetRoomGridValue(int x, int y) {
	u8 width  = (VarGet(VAR_GRID_SIZE) >> 0) & 0xFF;
	u8 height = (VarGet(VAR_GRID_SIZE) >> 8) & 0xFF;
	
	if (0 <= x && x < width && 0 <= y && y < height) {
		return GetVarPointer(VAR_ROOM_ID_0_0)[(y * width) + x];
	}
	if (x == width-2 && y == height) { // special case for entrance
		return MAP_META_ENTRANCE;
	}
	return MAP_META_EMPTY_FILLED;
}

u16 MetaPuzzle_FindCurrentRoomLocation() {
	u8 width  = (VarGet(VAR_GRID_SIZE) >> 0) & 0xFF;
	u8 height = (VarGet(VAR_GRID_SIZE) >> 8) & 0xFF;
	u16* grid = GetVarPointer(VAR_ROOM_ID_0_0);
	u16 mapId = (gSaveBlock1Ptr->location.mapGroup << 8) | gSaveBlock1Ptr->location.mapNum;
	// mgba_printf(MGBA_LOG_INFO, "Current Room Location (%x)", mapId);
	
	if (mapId == MAP_META_ENTRANCE) { // Special case: entrance is below the grid
		return (height * width) + (width - 2);
	}
	for (int i = 0; i < (width * height); i++) {
		if (grid[i] == mapId) return i;
	}
	return -1;
}

struct MapConnection* MetaPuzzle_ResolveMapConnection(struct MapConnection* connection) {
	if (gSaveBlock1Ptr->location.mapGroup != MAP_GROUP(MAP_PLACEHOLDER_N)) return connection;
	if (connection->resolved) return connection; // don't do double the work if we don't have to
	sWorkingConnection = *connection;
	u8 width  = (VarGet(VAR_GRID_SIZE) >> 0) & 0xFF;
	u8 height = (VarGet(VAR_GRID_SIZE) >> 8) & 0xFF;
	int i = MetaPuzzle_FindCurrentRoomLocation();
	int x = i % width; 
	int y = i / width;
	u16 mapId = MAP_META_EMPTY_FILLED;
	switch(connection->mapNum) {
		case MAP_NUM(MAP_PLACEHOLDER_N):   mapId = MetaPuzzle_GetRoomGridValue(x + 0, y - 1); /*mgba_printf(MGBA_LOG_INFO, "CONN: N = %x", mapId);*/ break;
		case MAP_NUM(MAP_PLACEHOLDER_S):   mapId = MetaPuzzle_GetRoomGridValue(x + 0, y + 1); /*mgba_printf(MGBA_LOG_INFO, "CONN: S = %x", mapId);*/ break;
		case MAP_NUM(MAP_PLACEHOLDER_W):   mapId = MetaPuzzle_GetRoomGridValue(x - 1, y + 0); /*mgba_printf(MGBA_LOG_INFO, "CONN: W = %x", mapId);*/ break;
		case MAP_NUM(MAP_PLACEHOLDER_E):   mapId = MetaPuzzle_GetRoomGridValue(x + 1, y + 0); /*mgba_printf(MGBA_LOG_INFO, "CONN: E = %x", mapId);*/ break;
		case MAP_NUM(MAP_PLACEHOLDER_NW):  mapId = MetaPuzzle_GetRoomGridValue(x - 1, y - 1); /*mgba_printf(MGBA_LOG_INFO, "CONN: NW = %x", mapId);*/ break;
		case MAP_NUM(MAP_PLACEHOLDER_NE):  mapId = MetaPuzzle_GetRoomGridValue(x + 1, y - 1); /*mgba_printf(MGBA_LOG_INFO, "CONN: NE = %x", mapId);*/ break;
		case MAP_NUM(MAP_PLACEHOLDER_SW):  mapId = MetaPuzzle_GetRoomGridValue(x - 1, y + 1); /*mgba_printf(MGBA_LOG_INFO, "CONN: SW = %x", mapId);*/ break;
		case MAP_NUM(MAP_PLACEHOLDER_SE):  mapId = MetaPuzzle_GetRoomGridValue(x + 1, y + 1); /*mgba_printf(MGBA_LOG_INFO, "CONN: SE = %x", mapId);*/ break;
	}
	sWorkingConnection.mapGroup = MAP_GROUP(mapId);
	sWorkingConnection.mapNum = MAP_NUM(mapId);
	sWorkingConnection.resolved = 1;
	return &sWorkingConnection;
}


// The only connection that's ever going to get passed in here is a connection residing in gMapHeader,
// so just assume that gMapHeader is the owner of this connection.
struct MapHeader const *const MetaPuzzle_GetMapConnection(struct MapConnection *connection) {
	if (gSaveBlock1Ptr->location.mapGroup != MAP_GROUP(MAP_PLACEHOLDER_N)) goto error;
	connection = MetaPuzzle_ResolveMapConnection(connection);
	return Overworld_GetMapHeaderByGroupAndId(connection->mapGroup, connection->mapNum);
error:
	return Overworld_GetMapHeaderByGroupAndId(MAP_GROUP(MAP_META_EMPTY_FILLED), MAP_NUM(MAP_META_EMPTY_FILLED));
}

static void MetaPuzzle_AddVertPlanksAt(int x, int y) {
	MapGridSetMetatileIdAt(MAP_OFFSET + x + 0, MAP_OFFSET + y - 2, METATILE_MetaTileset_Planks_VertTop);
	MapGridSetMetatileIdAt(MAP_OFFSET + x + 1, MAP_OFFSET + y - 2, METATILE_MetaTileset_Planks_VertTop);
	MapGridSetMetatileIdAt(MAP_OFFSET + x + 0, MAP_OFFSET + y - 1, METATILE_MetaTileset_Planks_VertMid);
	MapGridSetMetatileIdAt(MAP_OFFSET + x + 1, MAP_OFFSET + y - 1, METATILE_MetaTileset_Planks_VertMid);
	MapGridSetMetatileIdAt(MAP_OFFSET + x + 0, MAP_OFFSET + y + 0, METATILE_MetaTileset_Planks_VertMid);
	MapGridSetMetatileIdAt(MAP_OFFSET + x + 1, MAP_OFFSET + y + 0, METATILE_MetaTileset_Planks_VertMid);
	MapGridSetMetatileIdAt(MAP_OFFSET + x + 0, MAP_OFFSET + y + 1, METATILE_MetaTileset_Planks_VertBot);
	MapGridSetMetatileIdAt(MAP_OFFSET + x + 1, MAP_OFFSET + y + 1, METATILE_MetaTileset_Planks_VertBot);
}

static void MetaPuzzle_AddHorzPlanksAt(int x, int y) {
	MapGridSetMetatileIdAt(MAP_OFFSET + x - 2, MAP_OFFSET + y + 0, METATILE_MetaTileset_Planks_HorzLeft);
	MapGridSetMetatileIdAt(MAP_OFFSET + x - 2, MAP_OFFSET + y + 1, METATILE_MetaTileset_Planks_HorzLeft);
	MapGridSetMetatileIdAt(MAP_OFFSET + x - 1, MAP_OFFSET + y + 0, METATILE_MetaTileset_Planks_HorzMid);
	MapGridSetMetatileIdAt(MAP_OFFSET + x - 1, MAP_OFFSET + y + 1, METATILE_MetaTileset_Planks_HorzMid);
	MapGridSetMetatileIdAt(MAP_OFFSET + x + 0, MAP_OFFSET + y + 0, METATILE_MetaTileset_Planks_HorzMid);
	MapGridSetMetatileIdAt(MAP_OFFSET + x + 0, MAP_OFFSET + y + 1, METATILE_MetaTileset_Planks_HorzMid);
	MapGridSetMetatileIdAt(MAP_OFFSET + x + 1, MAP_OFFSET + y + 0, METATILE_MetaTileset_Planks_HorzRight);
	MapGridSetMetatileIdAt(MAP_OFFSET + x + 1, MAP_OFFSET + y + 1, METATILE_MetaTileset_Planks_HorzRight);
}

static void MetaPuzzle_InsertConnectionObjects(u16 roomId, u8 idx, int offX, int offY) {
	if (sMetaRoomInfo[MAP_NUM(roomId)].connObj == NULL) return;
	
	struct ObjectEventTemplate* obj = NULL;
	const struct ObjectEventTemplate* over = sMetaRoomInfo[MAP_NUM(roomId)].connObj;
	
	for (int i = 0; i < OBJECT_EVENT_TEMPLATES_COUNT; i++) {
		if (gSaveBlock1Ptr->objectEventTemplates[i].graphicsId == (OBJ_EVENT_GFX_VAR_0 + idx)) {
			obj = &gSaveBlock1Ptr->objectEventTemplates[i];
			break;
		}
	}
	if (obj == NULL) return;
	obj->graphicsId = over->graphicsId;
	obj->movementType = over->movementType;
	obj->movementRangeX = over->movementRangeX;
	obj->movementRangeY = over->movementRangeY;
	obj->flagId = over->flagId;
	obj->x = over->x + offX;
	obj->y = over->y + offY;
	obj->elevation = over->elevation;
}

void MetaPuzzle_FillRoomConnections() {
	if (gSaveBlock1Ptr->location.mapGroup != MAP_GROUP(MAP_PLACEHOLDER_N)) return;
	u8 width  = (VarGet(VAR_GRID_SIZE) >> 0) & 0xFF;
	u8 height = (VarGet(VAR_GRID_SIZE) >> 8) & 0xFF;
	int i = MetaPuzzle_FindCurrentRoomLocation();
	int x = i % width; 
	int y = i / width;
	u16 myId = (gSaveBlock1Ptr->location.mapGroup << 8) | gSaveBlock1Ptr->location.mapNum;
	{	//	north
		u16 oid = MetaPuzzle_GetRoomGridValue(x + 0, y - 1);
		if (sMetaRoomInfo[MAP_NUM(myId)].north && sMetaRoomInfo[MAP_NUM(oid)].south) {
			MetaPuzzle_AddVertPlanksAt(19, 0);
		}
		MetaPuzzle_InsertConnectionObjects(oid, 0, 0, -40);
	}
	{	//	south
		u16 oid = MetaPuzzle_GetRoomGridValue(x + 0, y + 1);
		if (sMetaRoomInfo[MAP_NUM(myId)].south && sMetaRoomInfo[MAP_NUM(oid)].north) {
			MetaPuzzle_AddVertPlanksAt(19, 40);
		}
		MetaPuzzle_InsertConnectionObjects(oid, 0, 0, 40);
	}
	{	//	west
		u16 oid = MetaPuzzle_GetRoomGridValue(x - 1, y + 0);
		if (sMetaRoomInfo[MAP_NUM(myId)].west && sMetaRoomInfo[MAP_NUM(oid)].east) {
			MetaPuzzle_AddHorzPlanksAt(0, 19);
		}
		MetaPuzzle_InsertConnectionObjects(oid, 0, -40, 0);
	}
	{	//	east
		u16 oid = MetaPuzzle_GetRoomGridValue(x + 1, y + 0);
		if (sMetaRoomInfo[MAP_NUM(myId)].east && sMetaRoomInfo[MAP_NUM(oid)].west) {
			MetaPuzzle_AddHorzPlanksAt(40, 19);
		}
		MetaPuzzle_InsertConnectionObjects(oid, 0, 40, 0);
	}
}

void MetaPuzzle_CountCollectedItems(struct ScriptContext *ctx) {
	gSpecialVar_Result = 0;
	// gSpecialVar_Result += CheckBagHasItem(FLAG_META_SUBMITTED_FINAL_BLUFF);
	// gSpecialVar_Result += CheckBagHasItem(FLAG_META_SUBMITTED_ZIGGY);
	// gSpecialVar_Result += CheckBagHasItem(FLAG_META_SUBMITTED_LOG_FLOAT);
	// gSpecialVar_Result += CheckBagHasItem(FLAG_META_SUBMITTED_FOREST);
	// gSpecialVar_Result += CheckBagHasItem(FLAG_META_SUBMITTED_ICE_CORNER);
	// gSpecialVar_Result += CheckBagHasItem(FLAG_META_SUBMITTED_LEDGE);
	// gSpecialVar_Result += CheckBagHasItem(FLAG_META_SUBMITTED_POKE_STAGE);
	// gSpecialVar_Result += CheckBagHasItem(FLAG_META_SUBMITTED_BIKE_PATH);
	// gSpecialVar_Result += CheckBagHasItem(FLAG_META_SUBMITTED_BERRY);
	// gSpecialVar_Result += CheckBagHasItem(FLAG_META_SUBMITTED_LAVARIDGE);
	// gSpecialVar_Result += CheckBagHasItem(FLAG_META_SUBMITTED_FIRE);
	// gSpecialVar_Result += CheckBagHasItem(FLAG_META_SUBMITTED_ZIP_SLIDE);
	// gSpecialVar_Result += CheckBagHasItem(FLAG_META_SUBMITTED_KOGA);
	// gSpecialVar_Result += CheckBagHasItem(FLAG_META_SUBMITTED_DIVE);
	// gSpecialVar_Result += CheckBagHasItem(FLAG_META_SUBMITTED_SEEDOT);
	// gSpecialVar_Result += CheckBagHasItem(FLAG_META_SUBMITTED_CUSHION);
}

#pragma endregion
//-----------------------------------------------------------------------------
// Sliding Tile Rearrangement Screen

#define BG_TEXT 0
#define BG_BG  1

struct SlidingTile {
	u8 roomId;
	u8 tileSprite;
	u8 iconSprite;
	u8 locX:4;
	u8 locY:4;
	struct Subsprite subsprites[3];
	struct SubspriteTable subspriteTable;
};

struct SlidingTileScreen {
    u8 lockedIndex:4;
    u8 nullIndex:4;
	u8 gridWidth:3;
	u8 gridHeight:3;
	bool8 isSliding:1;
	u8 numTiles;
	struct SlidingTile tiles[16];
	u8 tilePointers[16];
	u16 bgTilemapBuffers[2][BG_SCREEN_SIZE];
	u16* bgTileMap;
};

static EWRAM_DATA struct SlidingTileScreen *sSlidingTileScene = NULL;

const struct BgTemplate sBgTemplates[] = {
    {
        .bg = BG_TEXT,
        .charBaseIndex = 2,
        .mapBaseIndex = 30,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0
    },
    // {
    //     .bg = BG_MON,
    //     .charBaseIndex = 0,
    //     .mapBaseIndex = 28,
    //     .screenSize = 0,
    //     .paletteMode = 0,
    //     .priority = 1,
    //     .baseTile = 0
    // },
    {
        .bg = BG_BG,
        .charBaseIndex = 1,
        .mapBaseIndex = 31,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 2,
        .baseTile = 0
    },
};

static const struct WindowTemplate sWindows[] =
{
    {
        .bg = BG_TEXT,
        .tilemapLeft = 1,
        .tilemapTop = 15,
        .width = 28,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0x1,
    },
    DUMMY_WIN_TEMPLATE
};

static const struct WindowTemplate sYesNoWindow =
{
    .bg = BG_TEXT,
    .tilemapLeft = 21,
    .tilemapTop = 9,
    .width = 5,
    .height = 4,
    .paletteNum = 13,
    .baseBlock = 0x71,
};

static const struct OamData sOam_Icon =
{
    .y = DISPLAY_HEIGHT,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(16x16),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(16x16),
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
    .affineParam = 0,
};

static const struct SpriteTemplate sTileTemplate = {
	.tileTag = TAG_TILE_BASE,
	.paletteTag = TAG_TILE_BASE,
	.oam = &gDummyOamData,
	.anims = gDummySpriteAnimTable,
	.images = NULL,
	.affineAnims = gDummySpriteAffineAnimTable,
	.callback = SpriteCB_TileSlide, //TODO
};

static const struct SpriteTemplate sIconTemplate = {
	.tileTag = 0,
	.paletteTag = 0,
	.oam = &sOam_Icon,
	.anims = gDummySpriteAnimTable,
	.images = NULL,
	.affineAnims = gDummySpriteAffineAnimTable,
	.callback = SpriteCB_TileSlide, //TODO
};

const u32 sTileBg_Gfx[] = INCBIN_U32("graphics/meta_puzzle/slide_tile_base.4bpp.lz");
const u32 sIcon_Unknown_Gfx[] = INCBIN_U32("graphics/meta_puzzle/question_mark.4bpp.lz");

const u16 sTileBg_Pal[] = INCBIN_U16("graphics/meta_puzzle/slide_tile_base.gbapal");
const u16 sTileLocked_Pal[] = INCBIN_U16("graphics/meta_puzzle/slide_tile_locked.gbapal");
const u16 sTileVisited_Pal[] = INCBIN_U16("graphics/meta_puzzle/slide_tile_visited.gbapal");
const u16 sIcon_Unknown_Pal[] = INCBIN_U16("graphics/meta_puzzle/question_mark.gbapal");

const u32 sPedestalBg_Gfx[] = INCBIN_U32("graphics/meta_puzzle/slidebg.4bpp.lz");
const u32 sPedestalBg_Pal[] = INCBIN_U32("graphics/meta_puzzle/slidebg.gbapal.lz");
static const u8 sPedestalBg_2x1_Tilemap[] = INCBIN_U8("graphics/meta_puzzle/slidebg_2x1.tilemap.lz");
static const u8 sPedestalBg_3x3_Tilemap[] = INCBIN_U8("graphics/meta_puzzle/slidebg_3x3.tilemap.lz");
// static const u8 sPedestalBg_4x4_Tilemap[] = INCBIN_U8("graphics/meta_puzzle/slidebg_4x4.tilemap.lz");
static const u32 sPedestalBg_4x4_Tilemap[] = INCBIN_U32("graphics/meta_puzzle/slidebg_4x4.tilemap.lz");

static const struct CompressedSpriteSheet sCompressedSpriteSheets[] = {
	{ sTileBg_Gfx, (32*40/2), TAG_TILE_BASE },
	{ sIcon_Unknown_Gfx, (16*16/2), TAG_ICON_UNKNOWN },
    { },
};

static const struct SpriteSheet sSpriteSheets[] = {
	{ gObjectEventPic_MetaItem_Lavaridge, (16*16/2), TAG_ICON_LAVARIDGE },
	{ gObjectEventPic_MetaItem_FinalBluff, (16*16/2), TAG_ICON_FINAL },
	{ gObjectEventPic_MetaItem_LedgeValley, (16*16/2), TAG_ICON_LEDGE },
	{ gObjectEventPic_MetaItem_IceCorner, (16*16/2), TAG_ICON_ICE },
	{ gObjectEventPic_MetaItem_LogFlotilla, (16*16/2), TAG_ICON_LOG },
	{ gObjectEventPic_MetaItem_BikePath, (16*16/2), TAG_ICON_BIKE },
	{ gObjectEventPic_MetaItem_PokeStage, (16*16/2), TAG_ICON_STAGE },
	{ gObjectEventPic_MetaItem_ZiggyRoom, (16*16/2), TAG_ICON_ZIGGY },
	{ gObjectEventPic_MetaItem_ForestRoom, (16*16/2), TAG_ICON_FOREST },
	{ gObjectEventPic_MetaItem_ZipRoom, (16*16/2), TAG_ICON_ZIP },
	{ gObjectEventPic_MetaItem_KogaRoom, (16*16/2), TAG_ICON_KOGA },
	{ gObjectEventPic_MetaItem_FireRoom, (16*16/2), TAG_ICON_FIRE },
	{ gObjectEventPic_MetaItem_DiveMaze, (16*16/2), TAG_ICON_DIVE },
	{ gObjectEventPic_MetaItem_BerryRoom, (16*16/2), TAG_ICON_BERRY },
	{ gObjectEventPic_MetaItem_Room15, (16*16/2), TAG_ICON_BERRY },
	{ },
};

static const struct SpritePalette sSpritePalettes[] = {
	{ sTileBg_Pal, TAG_TILE_BASE },
	{ sTileLocked_Pal, TAG_TILE_LOCKED },
	{ sTileVisited_Pal, TAG_TILE_VISITED },
	{ sIcon_Unknown_Pal, TAG_ICON_UNKNOWN },
	{ gObjectEventPal_Npc1, TAG_PAL_NPC1 },
	{ gObjectEventPal_Npc2, TAG_PAL_NPC2 },
	{ gObjectEventPal_Npc3, TAG_PAL_NPC3 },
	{ gObjectEventPal_Npc4, TAG_PAL_NPC4 },
	// { gObjectEventPal_MetaItem_Lavaridge, TAG_ICON_LAVARIDGE },
	// { gObjectEventPal_MetaItem_FinalBluff, TAG_ICON_FINAL },
	// { gObjectEventPal_MetaItem_LedgeValley, TAG_ICON_LEDGE },
	{ gObjectEventPal_MetaItem_IceCorner, TAG_ICON_ICE },
	// { gObjectEventPal_MetaItem_LogFlotilla, TAG_ICON_LOG },
	// { gObjectEventPal_MetaItem_BikePath, TAG_ICON_BIKE },
	// { gObjectEventPal_MetaItem_PokeStage, TAG_ICON_STAGE },
	// { gObjectEventPal_MetaItem_ZiggyRoom, TAG_ICON_ZIGGY },
	// { gObjectEventPal_MetaItem_ForestRoom, TAG_ICON_FOREST },
	// { gObjectEventPal_MetaItem_ZipRoom, TAG_ICON_ZIP },
	// { gObjectEventPal_MetaItem_KogaRoom, TAG_ICON_KOGA },
	// { gObjectEventPal_MetaItem_FireRoom, TAG_ICON_FIRE },
	// { gObjectEventPal_MetaItem_DiveMaze, TAG_ICON_DIVE },
	{ gObjectEventPal_MetaItem_BerryRoom, TAG_ICON_BERRY },
	{ gObjectEventPal_MetaItem_Room15, TAG_ICON_BERRY },
    { },
};

static const struct Subsprite sTileSubsprites[] = {
	[SS_TILE_BACK] = { 
		.x = -16, .y = -16, 
		.shape = SPRITE_SHAPE(32x32), .size = SPRITE_SIZE(32x32),
		.priority = 1, .tileOffset = 0,
	},
	[SS_TILE_NORTH_EXIT] = {
		.x = -4, .y = -16, 
		// .shape = SPRITE_SHAPE(8x16), .size = SPRITE_SIZE(8x16),
		.shape = SPRITE_SHAPE(8x8), .size = SPRITE_SIZE(8x8),
		.priority = 0, .tileOffset = 17,
	},
	[SS_TILE_SOUTH_EXIT] = {
		.x = -4, .y = 16-8, 
		// .shape = SPRITE_SHAPE(8x16), .size = SPRITE_SIZE(8x16),
		.shape = SPRITE_SHAPE(8x8), .size = SPRITE_SIZE(8x8),
		.priority = 0, .tileOffset = 16,
	},
	[SS_TILE_WEST_EXIT] = {
		.x = -16, .y = -4, 
		// .shape = SPRITE_SHAPE(16x8), .size = SPRITE_SIZE(16x8),
		.shape = SPRITE_SHAPE(8x8), .size = SPRITE_SIZE(8x8),
		.priority = 0, .tileOffset = 19,
	},
	[SS_TILE_EAST_EXIT] = {
		.x = 16-8, .y = -4, 
		// .shape = SPRITE_SHAPE(16x8), .size = SPRITE_SIZE(16x8),
		.shape = SPRITE_SHAPE(8x8), .size = SPRITE_SIZE(8x8),
		.priority = 0, .tileOffset = 18,
	},
};


static void Task_LoadSlidingTile(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        SetMainCallback2(CB2_LoadSlidingTile);
        DestroyTask(taskId);
    }
}

void MetaPuzzle_OpenSlidingPuzzle(const struct ScriptContext* ctx) 
{
	for (int i = VAR_PUZZLE_00; i <= VAR_PUZZLE_1F; i++)
		mgba_printf(MGBA_LOG_INFO, "VAR_PUZZLE_%x (%x) = %x", i-VAR_PUZZLE_00, i, VarGet(i));
	
	
	LockPlayerFieldControls();
	CreateTask(Task_LoadSlidingTile, 1);
	BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB(0, 0, 0));
}

static void SetupSlidingTiles() {
	// Stack-based sprite template so we don't have to have multiple
    // in-ROM templates. This should be fine as long as we ensure that
    // the created sprite points instead to the ROM-based template.
    struct SpriteTemplate template;
	u8 width  = (VarGet(VAR_GRID_SIZE) >> 0) & 0xFF;
	u8 height = (VarGet(VAR_GRID_SIZE) >> 8) & 0xFF;
	sSlidingTileScene->gridWidth = width;
	sSlidingTileScene->gridHeight = height;
	sSlidingTileScene->numTiles = width * height;
	mgba_printf(MGBA_LOG_WARN, "SetupSlidingTiles: VAR=%x %x => w=%d, h=%d", VAR_GRID_SIZE, VarGet(VAR_GRID_SIZE), width, height);
	MGBA_ASSERT(width > 0 && width <= 4);
	MGBA_ASSERT(height > 0 && height <= 4);
	
	for (int i = 0; i < width*height; i++) {
		int x = VarGet(VAR_ROOM_ID_0_0 + i);
		MGBA_ASSERT(MAP_GROUP(VarGet(VAR_ROOM_ID_0_0 + i)) == MAP_GROUP(MAP_PLACEHOLDER_S));
		
		struct SlidingTile* tile = &sSlidingTileScene->tiles[i];
		tile->roomId = MAP_NUM(VarGet(VAR_ROOM_ID_0_0 + i));
		MGBA_ASSERT(tile->roomId > 0 && tile->roomId < ARRAY_COUNT(sMetaRoomInfo));
		// mgba_printf(MGBA_LOG_WARN, "Tile %d: VAR=%x %x / %x => (%d == %d)", i, VAR_ROOM_ID_0_0+i, VarGet(VAR_ROOM_ID_0_0+i), tile->roomId, MAP_GROUP(tile->roomId), MAP_GROUP(MAP_PLACEHOLDER_S));
		
		sSlidingTileScene->tilePointers[i] = i;
		if (tile->roomId == MAP_NUM(MAP_META_NULL_ROOM)) {
			sSlidingTileScene->nullIndex = i;
			continue;
		}
		// Build subsprite table for the tile
		x = 0;
		const struct MetaRoomInfo* room = &sMetaRoomInfo[MAP_NUM(tile->roomId)];
		tile->subsprites[x++] = sTileSubsprites[SS_TILE_BACK];
		if (room->north) {
			tile->subsprites[x++] = sTileSubsprites[SS_TILE_NORTH_EXIT];
		}
		if (room->south) {
			tile->subsprites[x++] = sTileSubsprites[SS_TILE_SOUTH_EXIT];
		}
		if (room->west) {
			tile->subsprites[x++] = sTileSubsprites[SS_TILE_WEST_EXIT];
		}
		if (room->east) {
			tile->subsprites[x++] = sTileSubsprites[SS_TILE_EAST_EXIT];
		}
		// mgba_printf(MGBA_LOG_WARN, "Tile %d: x=%d", i, x);
		MGBA_ASSERT(x <= ARRAY_COUNT(tile->subsprites));
		tile->subspriteTable.subspriteCount = x; 
		tile->subspriteTable.subsprites = tile->subsprites;
		
		tile->locX = i % width;
		tile->locY = i / width;
		
		template = sTileTemplate;
		if (gSaveBlock1Ptr->location.mapNum == tile->roomId) {
			sSlidingTileScene->lockedIndex = i;
			template.paletteTag = TAG_TILE_LOCKED;
		}
		else if (FlagGet(FLAG_VISITED_RM0 + tile->roomId)) {
			template.paletteTag = TAG_TILE_VISITED;
		} 
		tile->tileSprite = CreateSprite(&template, 0, 0, 0);
		CalcCenterToCornerVec(&gSprites[tile->tileSprite], SPRITE_SHAPE(32x32), SPRITE_SIZE(32x32), ST_OAM_AFFINE_OFF);
		SetSubspriteTables(&gSprites[tile->tileSprite], &tile->subspriteTable);
		gSprites[tile->iconSprite].template = &sTileTemplate;
		gSprites[tile->tileSprite].tTileId = i;
		gSprites[tile->tileSprite].tCurrX = Q_8_8(TILE_SPREAD * tile->locX);
		gSprites[tile->tileSprite].tCurrY = Q_8_8(TILE_SPREAD * tile->locY);
		gSprites[tile->tileSprite].x = TILE_SPREAD * tile->locX;
		gSprites[tile->tileSprite].y = TILE_SPREAD * tile->locY;
		gSprites[tile->tileSprite].x2 = TILE_ORIGIN_X;
		gSprites[tile->tileSprite].y2 = TILE_ORIGIN_Y;
		
		template = sIconTemplate;
		template.tileTag = room->tileTag;
		template.paletteTag = room->palTag;
		tile->iconSprite = CreateSprite(&template, 0, 0, 0);
		CalcCenterToCornerVec(&gSprites[tile->iconSprite], SPRITE_SHAPE(16x16), SPRITE_SIZE(16x16), ST_OAM_AFFINE_OFF);
		gSprites[tile->iconSprite].template = &sIconTemplate;
		gSprites[tile->iconSprite].tTileId = i;
		gSprites[tile->iconSprite].tCurrX = Q_8_8(TILE_SPREAD * tile->locX);
		gSprites[tile->iconSprite].tCurrY = Q_8_8(TILE_SPREAD * tile->locY);
		gSprites[tile->iconSprite].x = TILE_SPREAD * tile->locX;
		gSprites[tile->iconSprite].y = TILE_SPREAD * tile->locY;
		gSprites[tile->iconSprite].x2 = TILE_ORIGIN_X;
		gSprites[tile->iconSprite].y2 = TILE_ORIGIN_Y;
	}
}

static int GetNullIndex()
{
	for (int i = 0; i < sSlidingTileScene->numTiles; i++) {
		if (sSlidingTileScene->tilePointers[i] == sSlidingTileScene->nullIndex) return i;
	}
	return -1;
}

static bool8 SwitchTiles(int a, int b)
{
	// Check bounds
	if (a < 0 || a >= sSlidingTileScene->numTiles) return FALSE;
	if (b < 0 || b >= sSlidingTileScene->numTiles) return FALSE;
	// Check that neither tile is locked
	if (a == sSlidingTileScene->lockedIndex) return FALSE;
	if (b == sSlidingTileScene->lockedIndex) return FALSE;
	
	int ax = sSlidingTileScene->tilePointers[a];
	int bx = sSlidingTileScene->tilePointers[b];
	
	sSlidingTileScene->tilePointers[a] = bx;
	sSlidingTileScene->tilePointers[b] = ax;
	
	sSlidingTileScene->tiles[ax].locX = b % sSlidingTileScene->gridWidth;
	sSlidingTileScene->tiles[ax].locY = b / sSlidingTileScene->gridWidth;
	
	sSlidingTileScene->tiles[bx].locX = a % sSlidingTileScene->gridWidth;
	sSlidingTileScene->tiles[bx].locY = a / sSlidingTileScene->gridWidth;
	sSlidingTileScene->isSliding = TRUE;
	return TRUE;
}


// Main Callback 2 functions

static void CB2_LoadSlidingTile(void)
{
	SetVBlankCallback(NULL);
	SetGpuReg(REG_OFFSET_DISPCNT, 0);
	SetGpuReg(REG_OFFSET_BG3CNT, 0);
	SetGpuReg(REG_OFFSET_BG2CNT, 0);
	SetGpuReg(REG_OFFSET_BG1CNT, 0);
	SetGpuReg(REG_OFFSET_BG0CNT, 0);
	
	SetGpuReg(REG_OFFSET_WININ, 0);
	SetGpuReg(REG_OFFSET_WINOUT, 0);
	SetGpuReg(REG_OFFSET_WIN0H, 0);
	SetGpuReg(REG_OFFSET_WIN1H, 0);
	SetGpuReg(REG_OFFSET_WIN0V, 0);
	SetGpuReg(REG_OFFSET_WIN1V, 0);
	
	SetGpuReg(REG_OFFSET_BG3HOFS, 0);
	SetGpuReg(REG_OFFSET_BG3VOFS, 0);
	SetGpuReg(REG_OFFSET_BG2HOFS, 0);
	SetGpuReg(REG_OFFSET_BG2VOFS, 0);
	SetGpuReg(REG_OFFSET_BG1HOFS, 0);
	SetGpuReg(REG_OFFSET_BG1VOFS, 0);
	SetGpuReg(REG_OFFSET_BG0HOFS, 0);
	SetGpuReg(REG_OFFSET_BG0VOFS, 0);
	SetGpuReg(REG_OFFSET_BLDCNT, 0);
	
	DmaFillLarge16(3, 0, (void *)VRAM, VRAM_SIZE, 0x1000);
	DmaFill32Defvars(3, 0, (void *)OAM, OAM_SIZE);
	DmaFill16Defvars(3, 0, (void *)PLTT, PLTT_SIZE);
	FillPalette(RGB_BLACK, 0, PLTT_SIZE);
	
	sSlidingTileScene = AllocZeroed(sizeof(*sSlidingTileScene));
	
	// ------------------------------------------------------------------------
	// Init Scene Backgrounds
	
	ResetBgsAndClearDma3BusyFlags(0);
	InitBgsFromTemplates(0, sBgTemplates, ARRAY_COUNT(sBgTemplates));
	SetBgTilemapBuffer(BG_TEXT, sSlidingTileScene->bgTilemapBuffers[BG_TEXT]);
	SetBgTilemapBuffer(BG_BG,   sSlidingTileScene->bgTilemapBuffers[BG_BG]);
	// ResetAllBgsCoordinates();
	
	// ------------------------------------------------------------------------
	// Load Scene Graphics
	
	ResetTempTileDataBuffers();
	DecompressAndCopyTileDataToVram(BG_BG, sPedestalBg_Gfx, 0, 0, 0);
	while (FreeTempTileDataBuffersIfPossible()) {}
	
	LoadCompressedPalette(sPedestalBg_Pal, 0, 0x20);
	
    FillBgTilemapBufferRect_Palette0(BG_TEXT, 0, 0, 0, 0x20, 0x20);
    FillBgTilemapBufferRect_Palette0(BG_BG, 0, 0, 0, 0x20, 0x20);
	
	if (VarGet(VAR_GRID_SIZE) == ((1 << 8) | 2)) {
		CopyToBgTilemapBuffer(BG_BG, sPedestalBg_2x1_Tilemap, 0, 0);
	}
	else if (VarGet(VAR_GRID_SIZE) == ((3 << 8) | 3)) {
		CopyToBgTilemapBuffer(BG_BG, sPedestalBg_3x3_Tilemap, 0, 0);
	}
	else {
		CopyToBgTilemapBuffer(BG_BG, sPedestalBg_4x4_Tilemap, 0, 0);
	}
	CopyBgTilemapBufferToVram(BG_TEXT);
	CopyBgTilemapBufferToVram(BG_BG);
	
	// ------------------------------------------------------------------------
	
	InitWindows(sWindows);
	DeactivateAllTextPrinters();
	LoadMessageBoxGfx(0, 0x200, 0xF0);
    LoadUserWindowBorderGfx(0, 0x214, 0xE0);
	
	ClearScheduledBgCopiesToVram();
    ScanlineEffect_Stop();
    ResetTasks();
    ResetSpriteData();
    FreeAllSpritePalettes();
    ResetPaletteFade();
	ResetTempTileDataBuffers();
	
	LoadPalette(GetOverworldTextboxPalettePtr(), 0xE0, 0x20);
	for (int i = 0; i < ARRAY_COUNT(sCompressedSpriteSheets) - 1; i++) {
		LoadCompressedSpriteSheet(&sCompressedSpriteSheets[i]);
	}
	LoadSpriteSheets(sSpriteSheets);
	LoadSpritePalettes(sSpritePalettes);
	
	SetupSlidingTiles();
	
	BeginNormalPaletteFade(PALETTES_ALL, 0, 0x10, 0, RGB_BLACK);
	EnableInterrupts(DISPSTAT_VBLANK);
	SetVBlankCallback(VBlankCB_SlidingTile);
	SetMainCallback2(CB2_SlidingTileMain);
	
	u8 taskId = CreateTask(NULL, 0);
	SetTaskFuncWithFollowupFunc(taskId, Task_WaitForFade, Task_HandleSlidingTileInput);
	
	SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_MODE_0 | DISPCNT_OBJ_1D_MAP | DISPCNT_OBJ_ON);
	ShowBg(BG_TEXT);
	ShowBg(BG_BG);
}

static void CB2_SlidingTileMain(void)
{
	RunTasks();
	sSlidingTileScene->isSliding = FALSE;
    AnimateSprites(); // isSliding is set to true in sprite callbacks
    BuildOamBuffer();
    RunTextPrinters();
    UpdatePaletteFade();
}

static void CB2_EndSlidingTile(void)
{
	bool8 hasChanged = FALSE;
	for (int i = 0; i < sSlidingTileScene->numTiles; i++) {
		hasChanged |= (sSlidingTileScene->tilePointers[i] != i);
	}
	if (hasChanged) {
		for (int i = 0; i < sSlidingTileScene->numTiles; i++) {
			u8 ptr = sSlidingTileScene->tilePointers[i];
			VarSet(VAR_ROOM_ID_0_0 + i, sSlidingTileScene->tiles[ptr].roomId | (MAP_PLACEHOLDER_N & 0xFF00));
		}
	}
	gSpecialVar_Result = hasChanged;
	
	FreeAllWindowBuffers();
    FreeAllSpritePalettes();
	
    HideBg(0);
    HideBg(1);
    HideBg(2);
    HideBg(3);
	
	SetGpuReg(REG_OFFSET_DISPCNT, 0);
	SetGpuReg(REG_OFFSET_BG3CNT, 0);
	SetGpuReg(REG_OFFSET_BG2CNT, 0);
	SetGpuReg(REG_OFFSET_BG1CNT, 0);
	SetGpuReg(REG_OFFSET_BG0CNT, 0);
	
	SetGpuReg(REG_OFFSET_WININ, 0);
	SetGpuReg(REG_OFFSET_WINOUT, 0);
	SetGpuReg(REG_OFFSET_WIN0H, 0);
	SetGpuReg(REG_OFFSET_WIN1H, 0);
	SetGpuReg(REG_OFFSET_WIN0V, 0);
	SetGpuReg(REG_OFFSET_WIN1V, 0);
	
	SetGpuReg(REG_OFFSET_BG3HOFS, 0);
	SetGpuReg(REG_OFFSET_BG3VOFS, 0);
	SetGpuReg(REG_OFFSET_BG2HOFS, 0);
	SetGpuReg(REG_OFFSET_BG2VOFS, 0);
	SetGpuReg(REG_OFFSET_BG1HOFS, 0);
	SetGpuReg(REG_OFFSET_BG1VOFS, 0);
	SetGpuReg(REG_OFFSET_BG0HOFS, 0);
	SetGpuReg(REG_OFFSET_BG0VOFS, 0);
	SetGpuReg(REG_OFFSET_BLDCNT, 0);

    ResetTasks();
    ResetSpriteData();
    ResetPaletteFade();
    UnsetBgTilemapBuffer(0);
    UnsetBgTilemapBuffer(1);
    UnsetBgTilemapBuffer(2);
    UnsetBgTilemapBuffer(3);
    ResetBgsAndClearDma3BusyFlags(0);
	
    // sCableCar->pylonHookTilemapEntries = NULL;
    // FREE_AND_SET_NULL(sCableCar->pylonStemTilemap);
    // FREE_AND_SET_NULL(sCableCar->bgMountainsTilemap);
    // FREE_AND_SET_NULL(sCableCar->treesTilemap);
    // FREE_AND_SET_NULL(sCableCar->groundTilemap);
    FREE_AND_SET_NULL(sSlidingTileScene->bgTileMap);
    FREE_AND_SET_NULL(sSlidingTileScene);
	
    DmaFillLarge16(3, 0, (void *)VRAM, VRAM_SIZE, 0x1000);
    DmaFill32Defvars(3, 0, (void *)OAM, OAM_SIZE);
    DmaFill16Defvars(3, 0, (void *)PLTT, PLTT_SIZE);
	
    // WarpIntoMap();
    // gFieldCallback = (hasChanged)? FieldCB_ShakeAndRearrangePuzzle : NULL; // TODO: FieldCB_ShakeAndRearrangePuzzle;
    // SetMainCallback2(CB2_LoadMap);
	InitMap();
    SetMainCallback2(CB2_ReturnToFieldContinueScript);
}

// VBlank Callbacks
static void VBlankCB_SlidingTile(void)
{
	LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

// Task Callbacks
static void Task_WaitForFade(u8 taskId)
{
	if (!gPaletteFade.active) {
		SwitchTaskToFollowupFunc(taskId);
	}
}
static void Task_WaitForSlide(u8 taskId)
{
	if (!sSlidingTileScene->isSliding) {
		SwitchTaskToFollowupFunc(taskId);
	}
}
static void Task_ClosePuzzle(u8 taskId)
{
	if (!gPaletteFade.active) {
		SetMainCallback2(CB2_EndSlidingTile);
        DestroyTask(taskId);
	}
}
static void Task_HandleSlidingTileInput(u8 taskId)
{
	int dx = 0, dy = 0;
	if (JOY_NEW(B_BUTTON)) {
		BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
		gTasks[taskId].func = Task_ClosePuzzle;
		return;
	}
	else if (JOY_NEW(DPAD_UP)) {
		dy = +1;
	}
	else if (JOY_NEW(DPAD_DOWN)) {
		dy = -1;
	}
	else if (JOY_NEW(DPAD_LEFT)) {
		dx = +1;
	}
	else if (JOY_NEW(DPAD_RIGHT)) {
		dx = -1;
	}
	
	if (dx != 0 || dy != 0) {
		int a = GetNullIndex();
		if (a < 0) return;
		
		int x = a % sSlidingTileScene->gridWidth;
		int y = a / sSlidingTileScene->gridWidth;
		if (x+dx < 0 || x+dx >= sSlidingTileScene->gridWidth) return;
		if (y+dy < 0 || y+dy >= sSlidingTileScene->gridHeight) return;
		
		if (SwitchTiles(a, ((y+dy) * sSlidingTileScene->gridWidth) + (x+dx))) {
			PlaySE(SE_CLICK);
			SetTaskFuncWithFollowupFunc(taskId, Task_WaitForSlide, Task_HandleSlidingTileInput);
		}
	}
}

// Sprite Callbacks

static void SpriteCB_TileSlide(struct Sprite *sprite)
{
	struct SlidingTile* tile = &sSlidingTileScene->tiles[sprite->data[0]];
	int destX = Q_8_8(TILE_SPREAD * tile->locX);
	int destY = Q_8_8(TILE_SPREAD * tile->locY);
	int moveX = destX - sprite->tCurrX;
	int moveY = destY - sprite->tCurrY;
	
	if (moveX >= 0) moveX = min(moveX, TILE_SPEED);
	else            moveX = max(moveX, -TILE_SPEED);
	
	if (moveY >= 0) moveY = min(moveY, TILE_SPEED);
	else            moveY = max(moveY, -TILE_SPEED);
	
	sprite->tCurrX += moveX;
	sprite->tCurrY += moveY;
	
	sprite->x = Q_8_8_TO_INT(sprite->tCurrX);
	sprite->y = Q_8_8_TO_INT(sprite->tCurrY);
	sSlidingTileScene->isSliding |= moveX != 0 || moveY != 0;
}


#pragma pop_macro("MAP_GROUP")
#pragma pop_macro("MAP_NUM")

