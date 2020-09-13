#include "global.h"
#include "intro_credits_graphics.h"
#include "palette.h"
#include "decompress.h"
#include "gpu_regs.h"
#include "task.h"
#include "main.h"
#include "graphics.h"

struct IntroCreditsSpriteMetadata
{
    u8 animNum:4;
    u8 shape:2;
    u8 size:2;
    u8 x;
    u8 y;
    u8 subpriority;
    u16 xOff;
};

const u16 gIntro2GrassPal_Day[] = INCBIN_U16("graphics/intro/intro2_grass.gbapal");
const u16 gIntro2GrassPal_Afn[] = INCBIN_U16("graphics/intro/intro2_grass_afternoon.gbapal");
const u16 gIntro2GrassPal_Night[] = INCBIN_U16("graphics/intro/intro2_grass_night.gbapal");
const u32 gIntro2GrassGfx[] = INCBIN_U32("graphics/intro/intro2_grass.4bpp.lz");
const u32 gIntro2GrassMap[] = INCBIN_U32("graphics/intro/intro2_grass_map.bin.lz");
const u16 gIntro2SkyPal_Day[] = INCBIN_U16("graphics/intro/85F0CFC.gbapal");
const u16 gIntro2SkyPal_Afn[] = INCBIN_U16("graphics/intro/85F0D5C.gbapal");
const u32 gIntro2CloudsGfx[] = INCBIN_U32("graphics/intro/intro2_bgclouds.4bpp.lz");
const u32 gIntro2CloudsMap[] = INCBIN_U32("graphics/intro/intro2_bgclouds_map.bin.lz");
const u16 gIntro2CloudsPal_Day[] = INCBIN_U16("graphics/intro/intro2_bgclouds.gbapal");
const u16 gIntro2CloudsPal_Afn[] = INCBIN_U16("graphics/intro/intro2_bgclouds_afternoon.gbapal");
const u32 gIntro2Clouds2Gfx[] = INCBIN_U32("graphics/intro/intro2_bgclouds2.4bpp.lz");
const u16 gIntro2Clouds2Pal_Day[] = INCBIN_U16("graphics/intro/intro2_bgtrees2.gbapal");
const u16 gIntro2Clouds2Pal_Afn[] = INCBIN_U16("graphics/intro/intro2_bgtrees2_afternoon.gbapal");
const u32 gIntro2TreesGfx[] = INCBIN_U32("graphics/intro/intro2_bgtrees.4bpp.lz");
const u32 gIntro2TreesMap[] = INCBIN_U32("graphics/intro/intro2_bgtrees_map.bin.lz");
const u16 gIntro2TreesPal[] = INCBIN_U16("graphics/intro/intro2_bgtrees.gbapal");
const u32 gIntro2TreeTiles[] = INCBIN_U32("graphics/intro/intro2_bgtreessmall.4bpp.lz");
const u16 gIntro2SkyPal_Night[] = INCBIN_U16("graphics/intro/85F231C.gbapal");
const u32 gIntro2BuildGfx[] = INCBIN_U32("graphics/intro/intro2_bgnight.4bpp.lz");
const u16 gIntro2BuildPal[] = INCBIN_U16("graphics/intro/intro2_bgnight.gbapal");
const u32 gIntro2BuildMap[] = INCBIN_U32("graphics/intro/intro2_bgnight_map.bin.lz");
const u32 gIntro2NightTiles[] = INCBIN_U32("graphics/intro/intro2_night.4bpp.lz");
const u16 gIntro2BrendanPalette[] = INCBIN_U16("graphics/intro/intro2_brendan.gbapal");
const u32 gIntro2BrendanTiles[] = INCBIN_U32("graphics/intro/intro2_brendan.4bpp.lz");
const u16 gIntro2MayPalette[] = INCBIN_U16("graphics/intro/intro2_may.gbapal");
const u32 gIntro2MayTiles[] = INCBIN_U32("graphics/intro/intro2_may.4bpp.lz");
const u16 gIntro2TreekidPalette[] = INCBIN_U16("graphics/intro/intro2_treekid.gbapal");
const u32 gIntro2TreekidTiles[] = INCBIN_U32("graphics/intro/intro2_treekid.4bpp.lz");
const u32 gIntro2BicycleTiles[] = INCBIN_U32("graphics/intro/intro2_bicycle.4bpp.lz");
const u16 gIntro2LatiosPalette[] = INCBIN_U16("graphics/intro/intro2_latios.gbapal");
const u32 gIntro2LatiosTiles[] = INCBIN_U32("graphics/intro/intro2_latios.4bpp.lz");
const u16 gIntro2LatiasPalette[] = INCBIN_U16("graphics/intro/intro2_latias.gbapal");
const u32 gIntro2LatiasTiles[] = INCBIN_U32("graphics/intro/intro2_latias.4bpp.lz");

static void sub_817B62C(struct Sprite *sprite);
static void nullsub_65(struct Sprite *sprite);
static void sub_817B7C4(struct Sprite *sprite);
static void nullsub_66(struct Sprite *sprite);

static const struct SpriteTemplate gUnknown_085F504C =
{
    .tileTag = 2000,
    .paletteTag = 0xFFFF,
    .oam = &gDummyOamData,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = sub_817B62C
};

const struct CompressedSpriteSheet gIntro2CloudSpritesheet[] =
{
    {
        .data = gIntro2Clouds2Gfx,
        .size = 0x400,
        .tag = 2000
    },
    {}
};

static const union AnimCmd gIntro2BigCloudAnim[] =
{
    ANIMCMD_FRAME( 0, 30),
    ANIMCMD_END
};

static const union AnimCmd gIntro2MedCloudAnim[] =
{
    ANIMCMD_FRAME(16, 30),
    ANIMCMD_END
};

static const union AnimCmd gIntro2SmallCloudAnim[] =
{
    ANIMCMD_FRAME(20, 30),
    ANIMCMD_END
};

static const union AnimCmd gIntro2WispCloudAnim[] =
{
    ANIMCMD_FRAME(22, 30),
    ANIMCMD_END
};

static const union AnimCmd *const gIntro2CloudSpriteAnimations[] =
{
    gIntro2BigCloudAnim,
    gIntro2MedCloudAnim,
    gIntro2SmallCloudAnim,
    gIntro2WispCloudAnim
};

static const struct IntroCreditsSpriteMetadata gIntro2CloudSpriteTemplates[] =
{
    {
        .animNum = 0,
        .shape = SPRITE_SHAPE(32x32),
        .size = SPRITE_SIZE(32x32),
        .x = 72,
        .y = 32,
        .subpriority = 100,
        .xOff = 0xc00
    },
    {
        .animNum = 0,
        .shape = SPRITE_SHAPE(32x32),
        .size = SPRITE_SIZE(32x32),
        .x = 158,
        .y = 32,
        .subpriority = 100,
        .xOff = 0xc00
    },
    {
        .animNum = 1,
        .shape = SPRITE_SHAPE(16x16),
        .size = SPRITE_SIZE(16x16),
        .x = 192,
        .y = 40,
        .subpriority = 101,
        .xOff = 0x800
    },
    {
        .animNum = 1,
        .shape = SPRITE_SHAPE(16x16),
        .size = SPRITE_SIZE(16x16),
        .x = 56,
        .y = 40,
        .subpriority = 101,
        .xOff = 0x800
    },
    {
        .animNum = 2,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .x = 100,
        .y = 44,
        .subpriority = 102,
        .xOff = 0x400
    },
    {
        .animNum = 2,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .x = 152,
        .y = 44,
        .subpriority = 102,
        .xOff = 0x400
    },
    {
        .animNum = 3,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .x = 8,
        .y = 46,
        .subpriority = 103,
        .xOff = 0x100
    },
    {
        .animNum = 3,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .x = 56,
        .y = 46,
        .subpriority = 103,
        .xOff = 0x100
    },
    {
        .animNum = 3,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .x = 240,
        .y = 46,
        .subpriority = 103,
        .xOff = 0x100
    },
};

static const struct CompressedSpriteSheet gIntro2TreeSpritesheet[] =
{
    {
        .data = gIntro2TreeTiles,
        .size = 0x400,
        .tag = 2000
    },
    {}
};

static const union AnimCmd gIntro2BigTreeAnim[] =
{
    ANIMCMD_FRAME( 0, 30),
    ANIMCMD_END
};

static const union AnimCmd gIntro2MedTreeAnim[] =
{
    ANIMCMD_FRAME(16, 30),
    ANIMCMD_END
};

static const union AnimCmd gIntro2SmallTreeAnim[] =
{
    ANIMCMD_FRAME(24, 30),
    ANIMCMD_END
};

static const union AnimCmd *const gIntro2TreeAnims[] =
{
    gIntro2BigTreeAnim,
    gIntro2MedTreeAnim,
    gIntro2SmallTreeAnim
};

static const struct IntroCreditsSpriteMetadata gIntro2TreeSpriteTemplates[] =
{
    {
        .animNum = 0,
        .shape = SPRITE_SHAPE(32x32),
        .size = SPRITE_SIZE(32x32),
        .x = 16,
        .y = 88,
        .subpriority = 100,
        .xOff = 0x2000,
    },
    {
        .animNum = 0,
        .shape = SPRITE_SHAPE(32x32),
        .size = SPRITE_SIZE(32x32),
        .x = 80,
        .y = 88,
        .subpriority = 100,
        .xOff = 0x2000,
    },
    {
        .animNum = 0,
        .shape = SPRITE_SHAPE(32x32),
        .size = SPRITE_SIZE(32x32),
        .x = 144,
        .y = 88,
        .subpriority = 100,
        .xOff = 0x2000,
    },
    {
        .animNum = 0,
        .shape = SPRITE_SHAPE(32x32),
        .size = SPRITE_SIZE(32x32),
        .x = 208,
        .y = 88,
        .subpriority = 100,
        .xOff = 0x2000,
    },
    {
        .animNum = 1,
        .shape = SPRITE_SHAPE(16x32),
        .size = SPRITE_SIZE(16x32),
        .x = 40,
        .y = 88,
        .subpriority = 101,
        .xOff = 0x1000,
    },
    {
        .animNum = 1,
        .shape = SPRITE_SHAPE(16x32),
        .size = SPRITE_SIZE(16x32),
        .x = 104,
        .y = 88,
        .subpriority = 101,
        .xOff = 0x1000,
    },
    {
        .animNum = 1,
        .shape = SPRITE_SHAPE(16x32),
        .size = SPRITE_SIZE(16x32),
        .x = 168,
        .y = 88,
        .subpriority = 101,
        .xOff = 0x1000,
    },
    {
        .animNum = 1,
        .shape = SPRITE_SHAPE(16x32),
        .size = SPRITE_SIZE(16x32),
        .x = 232,
        .y = 88,
        .subpriority = 101,
        .xOff = 0x1000,
    },
    {
        .animNum = 2,
        .shape = SPRITE_SHAPE(16x32),
        .size = SPRITE_SIZE(16x32),
        .x = 56,
        .y = 88,
        .subpriority = 102,
        .xOff = 0x800,
    },
    {
        .animNum = 2,
        .shape = SPRITE_SHAPE(16x32),
        .size = SPRITE_SIZE(16x32),
        .x = 120,
        .y = 88,
        .subpriority = 102,
        .xOff = 0x800,
    },
    {
        .animNum = 2,
        .shape = SPRITE_SHAPE(16x32),
        .size = SPRITE_SIZE(16x32),
        .x = 184,
        .y = 88,
        .subpriority = 102,
        .xOff = 0x800,
    },
    {
        .animNum = 2,
        .shape = SPRITE_SHAPE(16x32),
        .size = SPRITE_SIZE(16x32),
        .x = 248,
        .y = 88,
        .subpriority = 102,
        .xOff = 0x800,
    }
};

static const struct CompressedSpriteSheet gIntro2BuildingSpritesheet[] =
{
    {
        .data = gIntro2NightTiles,
        .size = 0x400,
        .tag = 2000
    },
    {}
};

static const union AnimCmd gIntro2BuildingAnim[] =
{
    ANIMCMD_FRAME(0, 30),
    ANIMCMD_END
};

static const union AnimCmd *const gIntro2BuildingAnims[] =
{
    gIntro2BuildingAnim
};

static const struct IntroCreditsSpriteMetadata gIntro2TownSpriteTemplates[] =
{
    {
        .animNum = 0,
        .shape = SPRITE_SHAPE(32x32),
        .size = SPRITE_SIZE(32x32),
        .x = 24,
        .y = 88,
        .subpriority = 100,
        .xOff = 0x1000,
    },
    {
        .animNum = 0,
        .shape = SPRITE_SHAPE(32x32),
        .size = SPRITE_SIZE(32x32),
        .x = 64,
        .y = 88,
        .subpriority = 100,
        .xOff = 0x1000,
    },
    {
        .animNum = 0,
        .shape = SPRITE_SHAPE(32x32),
        .size = SPRITE_SIZE(32x32),
        .x = 104,
        .y = 88,
        .subpriority = 100,
        .xOff = 0x1000,
    },
    {
        .animNum = 0,
        .shape = SPRITE_SHAPE(32x32),
        .size = SPRITE_SIZE(32x32),
        .x = 144,
        .y = 88,
        .subpriority = 100,
        .xOff = 0x1000,
    },
    {
        .animNum = 0,
        .shape = SPRITE_SHAPE(32x32),
        .size = SPRITE_SIZE(32x32),
        .x = 184,
        .y = 88,
        .subpriority = 100,
        .xOff = 0x1000,
    },
    {
        .animNum = 0,
        .shape = SPRITE_SHAPE(32x32),
        .size = SPRITE_SIZE(32x32),
        .x = 224,
        .y = 88,
        .subpriority = 100,
        .xOff = 0x1000,
    }
};

static const struct OamData gOamData_85F51CC =
{
    .y = 160,
    .shape = SPRITE_SHAPE(64x64),
    .size = SPRITE_SIZE(64x64),
    .priority = 1
};

static const union AnimCmd gUnknown_085F51D4[] =
{
    ANIMCMD_FRAME(  0, 8),
    ANIMCMD_FRAME( 64, 8),
    ANIMCMD_FRAME(128, 8),
    ANIMCMD_FRAME(192, 8),
    ANIMCMD_JUMP(0)
};

static const union AnimCmd *const gUnknown_085F51E8[] =
{
    gUnknown_085F51D4
};

static const struct SpriteTemplate gUnknown_085F51EC =
{
    .tileTag = 1002,
    .paletteTag = 1002,
    .oam = &gOamData_85F51CC,
    .anims = gUnknown_085F51E8,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = nullsub_65
};

static const struct SpriteTemplate gUnknown_085F5204 =
{
    .tileTag = 1003,
    .paletteTag = 1003,
    .oam = &gOamData_85F51CC,
    .anims = gUnknown_085F51E8,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = nullsub_65
};

static const struct SpriteTemplate gUnknown_085F5204a =
{
    .tileTag = 1006,
    .paletteTag = 1006,
    .oam = &gOamData_85F51CC,
    .anims = gUnknown_085F51E8,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = nullsub_65
};

static const struct OamData gUnknown_085F521C =
{
    .y = 160,
    .shape = SPRITE_SHAPE(64x32),
    .size = SPRITE_SIZE(64x32),
    .priority = 1
};

static const union AnimCmd gUnknown_085F5224[] =
{
    ANIMCMD_FRAME(  0, 8),
    ANIMCMD_FRAME( 32, 8),
    ANIMCMD_FRAME( 64, 8),
    ANIMCMD_FRAME( 96, 8),
    ANIMCMD_JUMP(0)
};

static const union AnimCmd *const gUnknown_085F5238[] =
{
    gUnknown_085F5224
};

static const struct SpriteTemplate gUnknown_085F523C =
{
    .tileTag = 1001,
    .paletteTag = 1002,
    .oam = &gUnknown_085F521C,
    .anims = gUnknown_085F5238,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = sub_817B7C4
};

static const struct SpriteTemplate gUnknown_085F5254 =
{
    .tileTag = 1001,
    .paletteTag = 1003,
    .oam = &gUnknown_085F521C,
    .anims = gUnknown_085F5238,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = sub_817B7C4
};

static const struct SpriteTemplate gUnknown_085F5254a =
{
    .tileTag = 1001,
    .paletteTag = 1006,
    .oam = &gUnknown_085F521C,
    .anims = gUnknown_085F5238,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = sub_817B7C4
};

static const struct OamData gUnknown_085F526C =
{
    .y = 160,
    .shape = SPRITE_SHAPE(64x64),
    .size = SPRITE_SIZE(64x64),
    .priority = 1
};

static const union AnimCmd gUnknown_085F5274[] =
{
    ANIMCMD_FRAME(  0, 16),
    ANIMCMD_END
};

static const union AnimCmd gUnknown_085F527C[] =
{
    ANIMCMD_FRAME( 64, 16),
    ANIMCMD_END
};

static const union AnimCmd *const gUnknown_085F5284[] =
{
    gUnknown_085F5274,
    gUnknown_085F527C
};

static const struct SpriteTemplate gUnknown_085F528C =
{
    .tileTag = 1004,
    .paletteTag = 1004,
    .oam = &gUnknown_085F526C,
    .anims = gUnknown_085F5284,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = nullsub_66
};

static const struct SpriteTemplate gUnknown_085F52A4 =
{
    .tileTag = 1005,
    .paletteTag = 1005,
    .oam = &gUnknown_085F526C,
    .anims = gUnknown_085F5284,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = nullsub_66
};

// const struct CompressedSpriteSheet gIntro2BrendanSpriteSheet[] =
// {
//     {
//         // .data = gIntro2BrendanNoTurnGfx,
//         .data = gIntro2BrendanTiles,
//         .size = 0x2000,
//         .tag = 1002
//     },
//     {}
// };

// const struct CompressedSpriteSheet gIntro2MaySpriteSheet[] =
// {
//     {
//         // .data = gIntro2MayNoTurnGfx,
//         .data = gIntro2MayTiles,
//         .size = 0x2000,
//         .tag = 1003
//     },
//     {}
// };

// const struct CompressedSpriteSheet gIntro2TreekidSpriteSheet[] =
// {
//     {
//         // .data = gIntro2TreekidNoTurnGfx,
//         .data = gIntro2TreekidTiles,
//         .size = 0x2000,
//         .tag = 1003
//     },
//     {}
// };

const struct CompressedSpriteSheet gIntro2BicycleSpriteSheet[] =
{
    {
        .data = gIntro2BicycleTiles,
        .size = 0x1000,
        .tag = 1001
    },
    {}
};

static const struct CompressedSpriteSheet gUnknown_085F52EC[] =
{
    {
        .data = gIntro2FlygonGfx,
        .size = 0x1000,
        .tag = 1004
    },
    {}
};

const struct CompressedSpriteSheet gIntro2FlygonSpriteSheet[] =
{
    {
        .data = gIntro2FlygonGfx,
        .size = 0x1000,
        .tag = 1005
    },
    {}
};

const struct SpritePalette gIntroBikeAndFlygonPalette[] =
{
    { .data = gIntro2BrendanNoTurnPal, .tag = 1002 },
    { .data = gIntro2BrendanNoTurnPal, .tag = 1003 },
    { .data = gIntro2FlygonPal,        .tag = 1004 },
    { .data = gIntro2FlygonPal,        .tag = 1005 },
    { .data = gIntro2BrendanNoTurnPal, .tag = 1006 }, //?
    {}
};

const struct CompressedSpriteSheet gIntroBrendanBikeSpritesheet[] =
{
    {
        .data = gIntro2BrendanTiles,
        .size = 0x3800,
        .tag = 1002
    },
    {}
};

const struct CompressedSpriteSheet gIntroMayBikeSpritesheet[] =
{
    {
        .data = gIntro2MayTiles,
        .size = 0x3800,
        .tag = 1003
    },
    {}
};

const struct CompressedSpriteSheet gIntroTreekidBikeSpritesheet[] =
{
    {
        .data = gIntro2TreekidTiles,
        .size = 0x3800,
        .tag = 1006
    },
    {}
};

const struct CompressedSpriteSheet gIntroBikeSpritesheet[] =
{
    {
        .data = gIntro2BicycleTiles,
        .size = 0x1000,
        .tag = 1001
    },
    {}
};

static const struct CompressedSpriteSheet gUnknown_085F5364[] =
{
    {
        .data = gIntro2LatiosTiles,
        .size = 0x1000,
        .tag = 1004
    },
    {}
};

static const struct CompressedSpriteSheet gUnknown_085F5374[] =
{
    {
        .data = gIntro2LatiasTiles,
        .size = 0x1000,
        .tag = 1005
    },
    {}
};

const struct SpritePalette gIntroBikeSpritePalettes[] =
{
    { .data = gIntro2BrendanPalette, .tag = 1002 },
    { .data = gIntro2MayPalette,     .tag = 1003 },
    { .data = gIntro2LatiosPalette,  .tag = 1004 },
    { .data = gIntro2LatiasPalette,  .tag = 1005 },
    { .data = gIntro2TreekidPalette, .tag = 1006 },
    {}
};

const struct CompressedSpriteSheet gIntro2BrendanSpriteSheet[] =
{
    {
        .data = gIntro2BrendanTiles,
        .size = 0x2000,
        .tag = 1002
    },
    {}
};

const struct CompressedSpriteSheet gIntro2MaySpriteSheet[] =
{
    {
        .data = gIntro2MayTiles,
        .size = 0x2000,
        .tag = 1003
    },
    {}
};

const struct CompressedSpriteSheet gIntro2TreekidSpriteSheet[] =
{
    {
        .data = gIntro2TreekidTiles,
        .size = 0x2000,
        .tag = 1006
    },
    {}
};

EWRAM_DATA u16 gSkyBgPanY = 0;
EWRAM_DATA s16 gSkyBgPanYAdjust = 0;
EWRAM_DATA s16 gSpriteDestroyFlag = 0;

static void LoadIntro2CloudSprites(void);
static void LoadIntro2TreeSprites(void);
static void LoadIntro2TownSprites(void);
static void Task_BikeBackgroundAnimation(u8);

void load_intro_part2_graphics(u8 a)
{
    LZ77UnCompVram(gIntro2GrassGfx, (void *)(BG_CHAR_ADDR(1)));
    LZ77UnCompVram(gIntro2GrassMap, (void *)(BG_SCREEN_ADDR(15)));
    LoadPalette(&gIntro2GrassPal_Day, 240, 32);
    switch (a)
    {
    case 0:
    default:
        LZ77UnCompVram(gIntro2CloudsGfx, (void *)(VRAM));
        LZ77UnCompVram(gIntro2CloudsMap, (void *)(BG_SCREEN_ADDR(6)));
        LoadPalette(&gIntro2SkyPal_Day, 0, 96);
        LoadCompressedSpriteSheet(gIntro2CloudSpritesheet);
        LoadPalette(&gIntro2CloudsPal_Day, 256, 32);
        LoadIntro2CloudSprites();
        break;
    case 1:
        LZ77UnCompVram(gIntro2TreesGfx, (void *)(VRAM));
        LZ77UnCompVram(gIntro2TreesMap, (void *)(BG_SCREEN_ADDR(6)));
        LoadPalette(&gIntro2Clouds2Pal_Day, 0, 32);
        LoadCompressedSpriteSheet(gIntro2TreeSpritesheet);
        LoadPalette(&gIntro2TreesPal, 256, 32);
        LoadIntro2TreeSprites();
        break;
    }
    gSpriteDestroyFlag = 0;
    gReservedSpritePaletteCount = 8;
}

// Note: This is only called with a=1.
void sub_817B150(u8 a)
{
    switch (a)
    {
    default:
    case 0:
        SetGpuReg(REG_OFFSET_BG3CNT, BGCNT_PRIORITY(3)
                                   | BGCNT_CHARBASE(0)
                                   | BGCNT_16COLOR
                                   | BGCNT_SCREENBASE(6)
                                   | BGCNT_TXT256x256);
        SetGpuReg(REG_OFFSET_BG2CNT, BGCNT_PRIORITY(2)
                                   | BGCNT_CHARBASE(0)
                                   | BGCNT_16COLOR
                                   | BGCNT_SCREENBASE(7)
                                   | BGCNT_TXT256x256);
        SetGpuReg(REG_OFFSET_BG1CNT, BGCNT_PRIORITY(1)
                                   | BGCNT_CHARBASE(1)
                                   | BGCNT_16COLOR
                                   | BGCNT_SCREENBASE(15)
                                   | BGCNT_TXT256x256);
        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_MODE_0
                                    | DISPCNT_OBJ_1D_MAP
                                    | DISPCNT_BG1_ON
                                    | DISPCNT_BG2_ON
                                    | DISPCNT_BG3_ON
                                    | DISPCNT_OBJ_ON);
        break;
    case 1:
        SetGpuReg(REG_OFFSET_BG3CNT, BGCNT_PRIORITY(3)
                                   | BGCNT_CHARBASE(0)
                                   | BGCNT_16COLOR
                                   | BGCNT_SCREENBASE(6)
                                   | BGCNT_TXT256x256);
        SetGpuReg(REG_OFFSET_BG2CNT, BGCNT_PRIORITY(2)
                                   | BGCNT_CHARBASE(0)
                                   | BGCNT_16COLOR
                                   | BGCNT_SCREENBASE(7)
                                   | BGCNT_TXT256x256);
        SetGpuReg(REG_OFFSET_BG1CNT, BGCNT_PRIORITY(1)
                                   | BGCNT_CHARBASE(1)
                                   | BGCNT_16COLOR
                                   | BGCNT_SCREENBASE(15)
                                   | BGCNT_TXT256x256);
        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_MODE_0
                                    | DISPCNT_OBJ_1D_MAP
                                    | DISPCNT_BG1_ON
                                    | DISPCNT_BG2_ON
                                    | DISPCNT_BG3_ON
                                    | DISPCNT_OBJ_ON);
        break;
    case 2:
        SetGpuReg(REG_OFFSET_BG3CNT, BGCNT_PRIORITY(3)
                                   | BGCNT_CHARBASE(0)
                                   | BGCNT_16COLOR
                                   | BGCNT_SCREENBASE(6)
                                   | BGCNT_TXT256x256);
        SetGpuReg(REG_OFFSET_BG2CNT, BGCNT_PRIORITY(2)
                                   | BGCNT_CHARBASE(0)
                                   | BGCNT_16COLOR
                                   | BGCNT_SCREENBASE(7)
                                   | BGCNT_TXT256x256);
        SetGpuReg(REG_OFFSET_BG1CNT, BGCNT_PRIORITY(1)
                                   | BGCNT_CHARBASE(1)
                                   | BGCNT_16COLOR
                                   | BGCNT_SCREENBASE(15)
                                   | BGCNT_TXT256x256);
        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_MODE_0
                                    | DISPCNT_OBJ_1D_MAP
                                    | DISPCNT_BG1_ON
                                    | DISPCNT_BG2_ON
                                    | DISPCNT_BG3_ON
                                    | DISPCNT_OBJ_ON);
        break;
    }
}
///////////////////////////////////////////////////////////////////////////////
// Credits Minigame

void LoadCreditsMinigameBackground1()
{
    // Load Grass onto Background 1
    LZ77UnCompVram(gIntro2GrassGfx, (void *)(BG_CHAR_ADDR(1)));
    LZ77UnCompVram(gIntro2GrassMap, (void *)(BG_SCREEN_ADDR(15)));
    LoadPalette(&gIntro2GrassPal_Day, 240, 32);
    
    // Load Sea and Clouds onto Background 2 and 3
    LZ77UnCompVram(gIntro2CloudsGfx, (void *)(VRAM));
    LZ77UnCompVram(gIntro2CloudsMap, (void *)(BG_SCREEN_ADDR(6)));
    LoadPalette(&gIntro2SkyPal_Day, 0, 96);
    
    // Load extra clouds as sprites
    LoadCompressedSpriteSheet(gIntro2CloudSpritesheet);
    LZ77UnCompVram(gIntro2Clouds2Gfx, (void *)(VRAM + 0x10000));
    LoadPalette(&gIntro2CloudsPal_Day, 256, 32);
    LoadIntro2CloudSprites();
    gReservedSpritePaletteCount = 8;
}


///////////////////////////////////////////////////////////////////////////////

void LoadCreditsBackgroundScenery(u8 a)
{
    LZ77UnCompVram(gIntro2GrassGfx, (void *)(BG_CHAR_ADDR(1)));
    LZ77UnCompVram(gIntro2GrassMap, (void *)(BG_SCREEN_ADDR(15)));
    switch (a)
    {
    case 0:
    default:
        LoadPalette(&gIntro2GrassPal_Day, 240, 32);
        LZ77UnCompVram(gIntro2CloudsGfx, (void *)(VRAM));
        LZ77UnCompVram(gIntro2CloudsMap, (void *)(BG_SCREEN_ADDR(6)));
        LoadPalette(&gIntro2SkyPal_Day, 0, 96);
        LoadCompressedSpriteSheet(gIntro2CloudSpritesheet);
        LZ77UnCompVram(gIntro2Clouds2Gfx, (void *)(VRAM + 0x10000));
        LoadPalette(&gIntro2CloudsPal_Day, 256, 32);
        LoadIntro2CloudSprites();
        break;
    case 1:
        LoadPalette(&gIntro2GrassPal_Afn, 240, 32);
        LZ77UnCompVram(gIntro2CloudsGfx, (void *)(VRAM));
        LZ77UnCompVram(gIntro2CloudsMap, (void *)(BG_SCREEN_ADDR(6)));
        LoadPalette(&gIntro2SkyPal_Afn, 0, 96);
        LoadCompressedSpriteSheet(gIntro2CloudSpritesheet);
        LZ77UnCompVram(gIntro2Clouds2Gfx, (void *)(VRAM + 0x10000));
        LoadPalette(&gIntro2CloudsPal_Afn, 256, 32);
        LoadIntro2CloudSprites();
        break;
    case 2:
    case 3:
        LoadPalette(&gIntro2GrassPal_Afn, 240, 32);
        LZ77UnCompVram(gIntro2TreesGfx, (void *)(VRAM));
        LZ77UnCompVram(gIntro2TreesMap, (void *)(BG_SCREEN_ADDR(6)));
        LoadPalette(&gIntro2Clouds2Pal_Afn, 0, 32);
        LoadCompressedSpriteSheet(gIntro2TreeSpritesheet);
        LoadPalette(&gIntro2Clouds2Pal_Afn, 256, 32);
        LoadIntro2TreeSprites();
        break;
    case 4:
        LoadPalette(&gIntro2GrassPal_Night, 240, 32);
        LZ77UnCompVram(gIntro2BuildGfx, (void *)(VRAM));
        LZ77UnCompVram(gIntro2BuildMap, (void *)(BG_SCREEN_ADDR(6)));
        LoadPalette(&gIntro2SkyPal_Night, 0, 64);
        LoadCompressedSpriteSheet(gIntro2BuildingSpritesheet);
        LoadPalette(&gIntro2BuildPal, 256, 32);
        LoadIntro2TownSprites();
        break;
    }
    gReservedSpritePaletteCount = 8;
    gSpriteDestroyFlag = 0;
}

void SetGpuRegistersForBikeScene(u8 a)
{
    SetGpuReg(REG_OFFSET_BG3CNT, BGCNT_PRIORITY(3)
                               | BGCNT_CHARBASE(0)
                               | BGCNT_16COLOR
                               | BGCNT_SCREENBASE(6)
                               | BGCNT_TXT256x256);
    SetGpuReg(REG_OFFSET_BG2CNT, BGCNT_PRIORITY(2)
                               | BGCNT_CHARBASE(0)
                               | BGCNT_16COLOR
                               | BGCNT_SCREENBASE(7)
                               | BGCNT_TXT256x256);
    SetGpuReg(REG_OFFSET_BG1CNT, BGCNT_PRIORITY(1)
                               | BGCNT_CHARBASE(1)
                               | BGCNT_16COLOR
                               | BGCNT_SCREENBASE(15)
                               | BGCNT_TXT256x256);
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_MODE_0
                                | DISPCNT_OBJ_1D_MAP
                                | DISPCNT_BG_ALL_ON
                                | DISPCNT_OBJ_ON);
}

u8 CreateBikeBackgroundAnimationTask(u8 a, u16 b, u16 c, u16 d)
{
    u8 taskId = CreateTask(&Task_BikeBackgroundAnimation, 0);

    gTasks[taskId].data[0] = a;
    gTasks[taskId].data[1] = b;
    gTasks[taskId].data[2] = 0;
    gTasks[taskId].data[3] = 0;
    gTasks[taskId].data[4] = c;
    gTasks[taskId].data[5] = 0;
    gTasks[taskId].data[6] = 0;
    gTasks[taskId].data[7] = d;
    gTasks[taskId].data[8] = 8;
    gTasks[taskId].data[9] = 0;
    Task_BikeBackgroundAnimation(taskId);
    return taskId;
}

static void Task_BikeBackgroundAnimation(u8 taskId)
{
    s16 data1;
    s16 data4;
    s16 data7;
    s32 r2;

    data1 = gTasks[taskId].data[1];
    if (data1 != 0)
    {
        r2 = (gTasks[taskId].data[2] << 16) + (u16)gTasks[taskId].data[3];
        r2 -= (u16)data1 << 4;
        gTasks[taskId].data[2] = r2 >> 16;
        gTasks[taskId].data[3] = r2;
        SetGpuReg(REG_OFFSET_BG1HOFS, gTasks[taskId].data[2]);
        SetGpuReg(REG_OFFSET_BG1VOFS, gSkyBgPanY + gSkyBgPanYAdjust);
    }

    data4 = gTasks[taskId].data[4];
    if (data4 != 0)
    {
        r2 = (gTasks[taskId].data[5] << 16) + (u16)gTasks[taskId].data[6];
        r2 -= (u16)data4 << 4;
        gTasks[taskId].data[5] = r2 >> 16;
        gTasks[taskId].data[6] = r2;
        SetGpuReg(REG_OFFSET_BG2HOFS, gTasks[taskId].data[5]);
        if (gTasks[taskId].data[0] != 0)
            SetGpuReg(REG_OFFSET_BG2VOFS, gSkyBgPanY + gSkyBgPanYAdjust);
        else
            SetGpuReg(REG_OFFSET_BG2VOFS, gSkyBgPanY);
    }

    data7 = gTasks[taskId].data[7];
    if (data7 != 0)
    {
        r2 = (gTasks[taskId].data[8] << 16) + (u16)gTasks[taskId].data[9];
        r2 -= (u16)data7 << 4;
        gTasks[taskId].data[8] = r2 >> 16;
        gTasks[taskId].data[9] = r2;
        SetGpuReg(REG_OFFSET_BG3HOFS, gTasks[taskId].data[8]);
        SetGpuReg(REG_OFFSET_BG3VOFS, gSkyBgPanY);
    }
}

void Intro2FlickerPalette(u8 mode)
{
    u16 x;
    u16 y;
    switch (mode)
    {
        case 0:
        default:
            /* stuff */
            if (gMain.vblankCounter1 & 3 || gPaletteFade.active)
                break;
            if (gMain.vblankCounter1 & 4)
            {
                x = gPlttBufferUnfaded[9];
                y = gPlttBufferUnfaded[10];
            }
            else
            {
                x = gPlttBufferUnfaded[10];
                y = gPlttBufferUnfaded[9];
            }
            LoadPalette(&x, 9, 2);
            LoadPalette(&y, 10, 2);
            break;
        case 2:
            if (gMain.vblankCounter1 & 3 || gPaletteFade.active)
                break;
            if (gMain.vblankCounter1 & 4)
            {
                x = 0x3D27;
                y = 0x295;
            }
            else
            {
                x = 0x31C;
                y = 0x3D27;
            }
            LoadPalette(&x, 12, 2);
            LoadPalette(&y, 13, 2);
            break;
        case 1:
            break;
    }
}

static void sub_817B62C(struct Sprite *sprite)
{
    s32 var;
    s16 var2 = gSpriteDestroyFlag;
    
    if (var2 != 2)
    {
        switch (var2)
        {
        default:
            DestroySprite(sprite);
            break;
        case 0:
            var = ((sprite->pos1.x << 16) | (u16)sprite->data[2]) + (u16)sprite->data[1];
            sprite->pos1.x = var >> 16;
            sprite->data[2] = var;
            if (sprite->pos1.x > 0xFF)
                sprite->pos1.x = -0x20;
            if (sprite->data[0])
                sprite->pos2.y = -(gSkyBgPanY + gSkyBgPanYAdjust);
            else
                sprite->pos2.y = -gSkyBgPanY;
            break;
        }
    }
}

static void LoadIntro2SpritesFromTemplates(u8 a, const struct IntroCreditsSpriteMetadata *b, const union AnimCmd *const *c, u8 d)
{
    u8 i;

    for(i = 0; i < d; i++)
    {
        u8 sprite = CreateSprite(&gUnknown_085F504C, b[i].x, b[i].y, b[i].subpriority);
        CalcCenterToCornerVec(&gSprites[sprite], b[i].shape, b[i].size, 0);
        gSprites[sprite].oam.priority = 3;
        gSprites[sprite].oam.shape = b[i].shape;
        gSprites[sprite].oam.size = b[i].size;
        gSprites[sprite].oam.paletteNum = 0;
        gSprites[sprite].anims = c;
        StartSpriteAnim(&gSprites[sprite], b[i].animNum);
        gSprites[sprite].data[0] = a;
        gSprites[sprite].data[1] = b[i].xOff;
        gSprites[sprite].data[2] = 0;
    }
}

static void LoadIntro2CloudSprites(void)
{
    LoadIntro2SpritesFromTemplates(0, gIntro2CloudSpriteTemplates, gIntro2CloudSpriteAnimations, 9);
}

static void LoadIntro2TreeSprites(void)
{
    LoadIntro2SpritesFromTemplates(1, gIntro2TreeSpriteTemplates, gIntro2TreeAnims, 12);
}

static void LoadIntro2TownSprites(void)
{
    LoadIntro2SpritesFromTemplates(1, gIntro2TownSpriteTemplates, gIntro2BuildingAnims, 6);
}

static void nullsub_65(struct Sprite *sprite)
{
}

static void sub_817B7C4(struct Sprite* sprite)
{
    sprite->invisible = gSprites[sprite->data[0]].invisible;
    sprite->pos1.x = gSprites[sprite->data[0]].pos1.x;
    sprite->pos1.y = gSprites[sprite->data[0]].pos1.y + 8;
    sprite->pos2.x = gSprites[sprite->data[0]].pos2.x;
    sprite->pos2.y = gSprites[sprite->data[0]].pos2.y;
}

u8 intro_create_brendan_sprite(s16 a, s16 b)
{
    u8 sprite = CreateSprite(&gUnknown_085F51EC, a, b, 2);
    u8 brendan = CreateSprite(&gUnknown_085F523C, a, b + 8, 3);
    gSprites[brendan].data[0] = sprite;
    return sprite;
}

u8 intro_create_may_sprite(s16 a, s16 b)
{
    u8 sprite = CreateSprite(&gUnknown_085F5204, a, b, 2);
    u8 may = CreateSprite(&gUnknown_085F5254, a, b + 8, 3);
    gSprites[may].data[0] = sprite;
    return sprite;
}

u8 intro_create_treekid_sprite(s16 a, s16 b)
{
    u8 sprite = CreateSprite(&gUnknown_085F5204a, a, b, 2);
    u8 may = CreateSprite(&gUnknown_085F5254a, a, b + 8, 3);
    gSprites[may].data[0] = sprite;
    return sprite;
}

static void nullsub_66(struct Sprite *sprite)
{
}

static void sub_817B8E8(struct Sprite* sprite)
{
    sprite->invisible = gSprites[sprite->data[0]].invisible;
    sprite->pos1.y = gSprites[sprite->data[0]].pos1.y;
    sprite->pos2.x = gSprites[sprite->data[0]].pos2.x;
    sprite->pos2.y = gSprites[sprite->data[0]].pos2.y;
}

static u8 sub_817B948(s16 a, s16 b)
{
    u8 sprite = CreateSprite(&gUnknown_085F528C, a - 32, b, 5);
    u8 latios = CreateSprite(&gUnknown_085F528C, a + 32, b, 6);
    gSprites[latios].data[0] = sprite;
    StartSpriteAnim(&gSprites[latios], 1);
    gSprites[latios].callback = &sub_817B8E8;
    return sprite;
}

u8 intro_create_flygon_sprite(s16 a, s16 b)
{
    u8 sprite = CreateSprite(&gUnknown_085F52A4, a - 32, b, 5);
    u8 flygon = CreateSprite(&gUnknown_085F52A4, a + 32, b, 6);
    gSprites[flygon].data[0] = sprite;
    StartSpriteAnim(&gSprites[flygon], 1);
    gSprites[flygon].callback = &sub_817B8E8;
    return sprite;
}
