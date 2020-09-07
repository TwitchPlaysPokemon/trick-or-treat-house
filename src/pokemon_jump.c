#include "global.h"
#include "alloc.h"
#include "battle_anim.h"
#include "bg.h"
#include "data.h"
#include "decompress.h"
#include "dynamic_placeholder_text_util.h"
#include "event_data.h"
#include "international_string_util.h"
#include "item.h"
#include "link.h"
#include "link_rfu.h"
#include "main.h"
#include "menu.h"
#include "palette.h"
#include "random.h"
#include "rom_8034C54.h"
#include "save.h"
#include "script.h"
#include "sound.h"
#include "sprite.h"
#include "string_util.h"
#include "strings.h"
#include "task.h"
#include "text_window.h"
#include "trig.h"
#include "pokemon.h"
#include "pokemon_jump.h"
#include "constants/rgb.h"
#include "constants/songs.h"
#include "constants/species.h"

struct PokemonJump1_MonInfo
{
    u16 species;
    u32 otId;
    u32 personality;
};

struct PokemonJump1_82E4
{
    int unk0;
    int unk4;
    u8 filler8[0x4];
    u16 unkC;
    u16 unkE;
    u16 unk10;
    u16 unk12;
    int unk14;
    int unk18;
    u8 unk1C[11];
};

struct PokemonJump2
{
    int unk0;
    u16 unk4;
    u8 unk6;
    u8 filler7[0xa - 0x7];
    u8 unkA;
    u8 unkB;
    u8 unkC;
    u8 unkD;
    u8 unkE;
    u8 unkF;
    u16 filler10;
    u16 unk12;
    u16 unk14;
    u32 unk18;
    u16 unk1C[5];
    u8 txtBuff[2][0x40];
    u8 strBuff[0x100];
    u16 tilemapBuffer[(0x81a8 - 0x1a6) / 2]; // 0x1A6
    struct Sprite *unk81A8[MAX_RFU_PLAYERS];
    struct Sprite *unk81BC[MAX_RFU_PLAYERS];
    struct Sprite *unk81D0[8];
    u8 filler81F0[0xC];
    u8 unk81FC[MAX_RFU_PLAYERS];
};

struct PokemonJump1Sub
{
    u8 unk0;
    u8 unk1;
    u16 unk2;
    u16 unk4;
    u32 unk8;
};

struct PokemonJump1
{
    MainCallback returnCallback;
    u8 unk4;
    u8 unk5;
    u8 unk6;
    u8 unk7;
    u16 unk8;
    u16 unkA;
    u16 unkC;
    u16 unkE;
    int unk10;
    u32 unk14;
    u32 unk18;
    int unk1C;
    u32 unk20;
    u32 unk24;
    u32 unk28;
    int unk2C;
    u32 unk30;
    u16 unk34;
    u16 unk36;
    u8 filler38[0x2];
    u16 unk3A;
    u16 unk3C;
    u16 unk3E;
    u16 unk40;
    u16 unk42;
    u8 unk44;
    u8 unk45;
    u8 unk46;
    u8 isLeader;
    u8 unk48;
    u8 unk49;
    u16 unk4A;
    u8 unk4C;
    u8 unk4D;
    u16 unk4E;
    u8 unk50;
    u8 unk51;
    u8 filler52[0x2];
    int unk54;
    int unk58;
    int unk5C;
    int unk60;
    int unk64;
    int unk68;
    int unk6C;
    struct PokemonJump1Sub unk70;
    u8 unk7C[MAX_RFU_PLAYERS];
    u8 unk81[MAX_RFU_PLAYERS];
    u8 unk86[MAX_RFU_PLAYERS];
    u8 unk8B[MAX_RFU_PLAYERS];
    u16 unk90[MAX_RFU_PLAYERS];
    u16 unk9A[MAX_RFU_PLAYERS];
    struct PokemonJump2 unkA4;
    struct PokemonJump1_MonInfo unk82A8[MAX_RFU_PLAYERS];
    struct PokemonJump1_82E4 unk82E4[MAX_RFU_PLAYERS];
    struct PokemonJump1_82E4 *unk83AC;
};

struct PokemonJumpMons
{
    u16 species;
    u16 unk2;
};

static void sub_802AA60(struct PokemonJump1 *);
static void sub_802AA94(struct PokemonJump1 *);
static void sub_802AB20(void);
static void sub_802AB98(void);
static s16 sub_802AC00(u16 species);
static void sub_802AC2C(struct PokemonJump1_MonInfo *monInfo, struct Pokemon *mon);
static void sub_802AC6C(void);
static void sub_802ACA0(u8 taskId);
static void sub_802AF80(u8 taskId);
static void sub_802B008(void);
static void sub_802B194(u8 taskId);
static void sub_802B1FC(void);
static bool32 sub_802B248(void);
static bool32 sub_802B2D4(void);
static bool32 sub_802B368(void);
static bool32 sub_802B3D4(void);
static bool32 sub_802B470(void);
static bool32 sub_802B4CC(void);
static bool32 sub_802B568(void);
static bool32 sub_802B5C8(void);
static bool32 sub_802B628(void);
static bool32 sub_802B664(void);
static bool32 sub_802B6B8(void);
static bool32 sub_802B704(void);
static bool32 sub_802B720(void);
static bool32 sub_802B7E0(void);
static bool32 sub_802B8CC(void);
static bool32 sub_802B964(void);
static bool32 sub_802B29C(void);
static bool32 sub_802B31C(void);
static bool32 sub_802B3B4(void);
static bool32 sub_802BA58(void);
static bool32 sub_802BB84(void);
static bool32 sub_802BC60(void);
static bool32 sub_802BD30(void);
static void sub_802BD84(u8 taskId);
static void sub_802BE60(TaskFunc func, u8 taskPriority);
static void sub_802BE80(void);
static void sub_802BEA0(void);
static void sub_802BEE4(void);
static int sub_802BF48(void);
static void sub_802BF7C(void);
static int sub_802C098(void);
static void sub_802C0B8(void);
static void sub_802C0E8(void);
static void sub_802C114(void);
static bool32 sub_802C130(u16);
static void sub_802C164(void);
static void sub_802C1DC(void);
static void sub_802C240(void);
static void sub_802C260(void);
static void sub_802C270(void);
static void sub_802C280(void);
static void sub_802C398(int);
static void sub_802C43C(void);
static bool32 sub_802C538(void);
static bool32 sub_802C5DC(void);
static bool32 sub_802C618(void);
static bool32 sub_802C650(void);
static void sub_802C688(int);
static int sub_802C6B0(void);
static bool32 sub_802C70C(void);
static int sub_802C73C(u8 *);
static void sub_802C780(void);
static int sub_802C790(int);
static void sub_802C7A0(u16);
static bool32 sub_802C7BC(void);
static u16 sub_802C7E0(void);
static void sub_802C808(u16, u16 *, u16 *);
static u16 sub_802C818(void);
static u16 sub_802C838(void);
static u16 sub_802C880(u16 item, u16 quantity);
static void sub_802CB7C(struct Sprite *sprite);
static void sub_802CC40(struct Sprite *sprite);
static void sub_802CD08(struct Sprite *sprite);
static void sub_802CDD4(struct Sprite *sprite);
static void sub_802DC9C(int id);
static void sub_802D074(struct PokemonJump2 *);
static void sub_802D0BC(struct PokemonJump2 *);
static void sub_802D0AC(void);
static void sub_802D0C8(int);
static bool32 sub_802D0F0(void);
static void sub_802D764(void);
static bool32 sub_802D788(void);
static void sub_802D7E8(u16 itemId, u16 quantity);
static void sub_802D884(u16 itemId);
static void sub_802D8FC(u16 itemId);
static bool32 sub_802D974(void);
static void sub_802DA14(void);
static void sub_802DC80(u32 id, s16 y);
static void sub_802DD88(u8 multiplayerId);
static bool32 sub_802DA44(void);
static void sub_802DD64(int);
static s8 sub_802DA8C(void);
static int sub_802DCCC(u8 flags);
static void sub_802DD74(u16);
static void sub_802DDA0(u8 multiplayerId);
static int sub_802DDB8(int multiplayerId);
static void sub_802DDCC(void);
static void sub_802DDE0(void);
static void sub_802DDF4(int);
static int sub_802DE08(void);
static void sub_802E0AC(struct PokemonJump1_MonInfo *arg0);
static bool32 sub_802E0D0(int multiplayerId, struct PokemonJump1_MonInfo *arg0);
static void sub_802E138(struct PokemonJump1_82E4 *arg0, struct PokemonJump1Sub *arg1);
static bool32 sub_802E1BC(struct PokemonJump1_82E4 *arg0, struct PokemonJump1Sub *arg1);
static void sub_802E234(struct PokemonJump1_82E4 *arg0, u8 arg1, u16 arg2);
static bool32 sub_802E264(struct PokemonJump1_82E4 *arg0, int multiplayerId, u8 *arg2, u16 *arg3);
static bool32 sub_802E2D0(struct PokemonJump1_82E4 *arg0, int multiplayerId);
static bool32 sub_802E354(u32 jumpScore, u16 jumpsInRow, u16 excellentsInRow);
static void sub_802E3A8(void);
static void sub_802D12C(u8 taskId);
static void sub_802E00C(u8 arg0);
static void sub_802E090(u8 taskId);
static void sub_802D150(void);
static void sub_802DD08(void);
static void sub_802DB8C(void);
static void sub_802DBF8(void);
static void sub_802DE1C(void);
static void sub_802DFD4(void);
static void sub_802D108(void (*func)(void));
static void sub_802DF70(bool32 arg0);
static u32 sub_802DA9C(u32 left, u32 top, u32 width, u32 height);
static void sub_802DB18(u16 left, u16 top, u8 cursorPos);
static void sub_802D150(void);
static void sub_802D2E4(void);
static void sub_802D350(void);
static void sub_802D3BC(void);
static void sub_802D448(void);
static void sub_802D4F4(void);
static void sub_802D598(void);
static void sub_802D5E4(void);
static void sub_802D72C(void);
static void sub_802D688(void);
static void sub_802E3E4(u8 taskId);
static void sub_802E6D0(u8 taskId);
static void sub_802EB98(u8 taskId);
static void sub_802E500(u16 windowId, int width);
static void TruncateToFirstWordOnly(u8 *str);
static void sub_802EF50(u16 tileTag, u16 palTag);
static u8 sub_802EFA8(u16 tileTag, u16 palTag, s16 x, s16 y, u8 subpriority);
static void sub_802EFFC(u16 tileTag, u16 palTag, s16 x, s16 y, u8 subpriority, s16 *spriteId1, s16 *spriteId2);
static bool32 sub_802EC98(u8 spriteId);
static bool32 sub_802EE30(u8 spriteId);
static void sub_802EDCC(u8 spriteId1, u8 spriteId2, u8 spriteId3);
static void sub_802EE5C(struct Sprite *sprite);
static void sub_802E83C(u8 taskId);
static void sub_802E8C8(u8 taskId);
static void sub_802EA50(u8 taskId);
static void sub_802EAB0(u8 taskId);

EWRAM_DATA static struct PokemonJump1 *gUnknown_02022CFC = NULL;
EWRAM_DATA static struct PokemonJump2 *gUnknown_02022D00 = NULL;

static const struct PokemonJumpMons gPkmnJumpSpecies[] =
{
    { .species = SPECIES_BULBASAUR,  .unk2 = 2, },
    { .species = SPECIES_CHARMANDER, .unk2 = 1, },
    { .species = SPECIES_SQUIRTLE,   .unk2 = 0, },
    { .species = SPECIES_CATERPIE,   .unk2 = 1, },
    { .species = SPECIES_METAPOD,    .unk2 = 1, },
    { .species = SPECIES_WEEDLE,     .unk2 = 1, },
    { .species = SPECIES_KAKUNA,     .unk2 = 1, },
    { .species = SPECIES_RATTATA,    .unk2 = 1, },
    { .species = SPECIES_RATICATE,   .unk2 = 1, },
    { .species = SPECIES_PIKACHU,    .unk2 = 0, },
    { .species = SPECIES_SANDSHREW,  .unk2 = 0, },
    { .species = SPECIES_NIDORAN_F,  .unk2 = 0, },
    { .species = SPECIES_NIDORAN_M,  .unk2 = 0, },
    { .species = SPECIES_CLEFAIRY,   .unk2 = 0, },
    { .species = SPECIES_VULPIX,     .unk2 = 0, },
    { .species = SPECIES_JIGGLYPUFF, .unk2 = 2, },
    { .species = SPECIES_ODDISH,     .unk2 = 2, },
    { .species = SPECIES_PARAS,      .unk2 = 1, },
    { .species = SPECIES_MEOWTH,     .unk2 = 0, },
    { .species = SPECIES_PSYDUCK,    .unk2 = 2, },
    { .species = SPECIES_MANKEY,     .unk2 = 1, },
    { .species = SPECIES_GROWLITHE,  .unk2 = 1, },
    { .species = SPECIES_POLIWAG,    .unk2 = 2, },
    { .species = SPECIES_BELLSPROUT, .unk2 = 2, },
    { .species = SPECIES_SHELLDER,   .unk2 = 1, },
    { .species = SPECIES_KRABBY,     .unk2 = 1, },
    { .species = SPECIES_EXEGGCUTE,  .unk2 = 2, },
    { .species = SPECIES_CUBONE,     .unk2 = 0, },
    { .species = SPECIES_DITTO,      .unk2 = 2, },
    { .species = SPECIES_EEVEE,      .unk2 = 0, },
    { .species = SPECIES_OMANYTE,    .unk2 = 1, },
    { .species = SPECIES_KABUTO,     .unk2 = 1, },
    { .species = SPECIES_CHIKORITA,  .unk2 = 2, },
    { .species = SPECIES_CYNDAQUIL,  .unk2 = 1, },
    { .species = SPECIES_TOTODILE,   .unk2 = 0, },
    { .species = SPECIES_SPINARAK,   .unk2 = 1, },
    { .species = SPECIES_PICHU,      .unk2 = 0, },
    { .species = SPECIES_CLEFFA,     .unk2 = 0, },
    { .species = SPECIES_IGGLYBUFF,  .unk2 = 2, },
    { .species = SPECIES_TOGEPI,     .unk2 = 2, },
    { .species = SPECIES_MAREEP,     .unk2 = 0, },
    { .species = SPECIES_BELLOSSOM,  .unk2 = 2, },
    { .species = SPECIES_MARILL,     .unk2 = 2, },
    { .species = SPECIES_SUNKERN,    .unk2 = 2, },
    { .species = SPECIES_WOOPER,     .unk2 = 2, },
    { .species = SPECIES_PINECO,     .unk2 = 2, },
    { .species = SPECIES_SNUBBULL,   .unk2 = 0, },
    { .species = SPECIES_SHUCKLE,    .unk2 = 2, },
    { .species = SPECIES_TEDDIURSA,  .unk2 = 0, },
    { .species = SPECIES_SLUGMA,     .unk2 = 2, },
    { .species = SPECIES_SWINUB,     .unk2 = 0, },
    { .species = SPECIES_HOUNDOUR,   .unk2 = 1, },
    { .species = SPECIES_PHANPY,     .unk2 = 0, },
    { .species = SPECIES_PORYGON2,   .unk2 = 0, },
    { .species = SPECIES_TYROGUE,    .unk2 = 1, },
    { .species = SPECIES_SMOOCHUM,   .unk2 = 2, },
    { .species = SPECIES_ELEKID,     .unk2 = 1, },
    { .species = SPECIES_MAGBY,      .unk2 = 1, },
    { .species = SPECIES_LARVITAR,   .unk2 = 1, },
    { .species = SPECIES_TREECKO,    .unk2 = 1, },
    { .species = SPECIES_TORCHIC,    .unk2 = 2, },
    { .species = SPECIES_MUDKIP,     .unk2 = 0, },
    { .species = SPECIES_MARSHTOMP,  .unk2 = 0, },
    { .species = SPECIES_POOCHYENA,  .unk2 = 1, },
    { .species = SPECIES_ZIGZAGOON,  .unk2 = 0, },
    { .species = SPECIES_LINOONE,    .unk2 = 0, },
    { .species = SPECIES_WURMPLE,    .unk2 = 1, },
    { .species = SPECIES_SILCOON,    .unk2 = 2, },
    { .species = SPECIES_CASCOON,    .unk2 = 2, },
    { .species = SPECIES_LOTAD,      .unk2 = 2, },
    { .species = SPECIES_SEEDOT,     .unk2 = 1, },
    { .species = SPECIES_RALTS,      .unk2 = 0, },
    { .species = SPECIES_KIRLIA,     .unk2 = 0, },
    { .species = SPECIES_SURSKIT,    .unk2 = 2, },
    { .species = SPECIES_SHROOMISH,  .unk2 = 2, },
    { .species = SPECIES_NINCADA,    .unk2 = 1, },
    { .species = SPECIES_WHISMUR,    .unk2 = 0, },
    { .species = SPECIES_AZURILL,    .unk2 = 2, },
    { .species = SPECIES_SKITTY,     .unk2 = 0, },
    { .species = SPECIES_SABLEYE,    .unk2 = 0, },
    { .species = SPECIES_MAWILE,     .unk2 = 0, },
    { .species = SPECIES_ARON,       .unk2 = 1, },
    { .species = SPECIES_MEDITITE,   .unk2 = 2, },
    { .species = SPECIES_ELECTRIKE,  .unk2 = 1, },
    { .species = SPECIES_PLUSLE,     .unk2 = 1, },
    { .species = SPECIES_MINUN,      .unk2 = 1, },
    { .species = SPECIES_VOLBEAT,    .unk2 = 0, },
    { .species = SPECIES_ILLUMISE,   .unk2 = 0, },
    { .species = SPECIES_ROSELIA,    .unk2 = 2, },
    { .species = SPECIES_GULPIN,     .unk2 = 2, },
    { .species = SPECIES_NUMEL,      .unk2 = 2, },
    { .species = SPECIES_TORKOAL,    .unk2 = 2, },
    { .species = SPECIES_SPOINK,     .unk2 = 0, },
    { .species = SPECIES_TRAPINCH,   .unk2 = 2, },
    { .species = SPECIES_CACNEA,     .unk2 = 2, },
    { .species = SPECIES_ANORITH,    .unk2 = 1, },
    { .species = SPECIES_WYNAUT,     .unk2 = 0, },
    { .species = SPECIES_SNORUNT,    .unk2 = 0, },
    { .species = SPECIES_CLAMPERL,   .unk2 = 1, },
    { .species = SPECIES_BAGON,      .unk2 = 1, },
};

void sub_802A9A8(u16 partyIndex, MainCallback callback)
{
    u8 taskId;

    if (gReceivedRemoteLinkPlayers)
    {
        gUnknown_02022CFC = Alloc(sizeof(*gUnknown_02022CFC));
        if (gUnknown_02022CFC)
        {
            ResetTasks();
            taskId = CreateTask(sub_802ACA0, 1);
            gUnknown_02022CFC->unk8 = 0;
            gUnknown_02022CFC->returnCallback = callback;
            gUnknown_02022CFC->unk4 = taskId;
            gUnknown_02022CFC->unk6 = GetMultiplayerId();
            sub_802AC2C(&gUnknown_02022CFC->unk82A8[gUnknown_02022CFC->unk6], &gPlayerParty[partyIndex]);
            sub_802AA60(gUnknown_02022CFC);
            SetWordTaskArg(taskId, 2, (u32)gUnknown_02022CFC);
            SetMainCallback2(sub_802AC6C);
            return;
        }
    }

    SetMainCallback2(callback);
}

static void sub_802AA48(void)
{
    sub_802D0AC();
    Free(gUnknown_02022CFC);
}

static void sub_802AA60(struct PokemonJump1 *arg0)
{
    arg0->unk5 = GetLinkPlayerCount();
    arg0->unk70.unk0 = 5;
    arg0->unk70.unk2 = 0;
    sub_802AB20();
    sub_802AA94(arg0);
    if (arg0->unk5 == MAX_RFU_PLAYERS)
        sub_802E3A8();
}

static void sub_802AA94(struct PokemonJump1 *arg0)
{
    int i;

    arg0->unk14 = 6;
    arg0->unk18 = 6;
    arg0->unk4A = 0;
    arg0->unk1C = 0;
    arg0->unk5C = 0;
    arg0->isLeader = GetMultiplayerId() == 0;
    arg0->unk8 = 0;
    arg0->unkA = 0;
    arg0->unkC = 0;
    arg0->unkE = 0;
    arg0->unk58 = 0;
    arg0->unk3A = 0;
    arg0->unk44 = 0;
    arg0->unk54 = 0;
    arg0->unk46 = 0;
    arg0->unk49 = 0;
    arg0->unk48 = 1;
    arg0->unk70.unk8 = 0;
    arg0->unk70.unk1 = 0;
    arg0->unk70.unk4 = 0;
    arg0->unk60 = 1;
    arg0->unk4D = 0;
    arg0->unk68 = 0;
    arg0->unk64 = 0;
    arg0->unk2C = 0;
    arg0->unk30 = 0;
    sub_802AB98();
    sub_802C0E8();

    for (i = 0; i < MAX_RFU_PLAYERS; i++)
    {
        arg0->unk7C[i] = 0;
        arg0->unk9A[i] = 0;
    }
}

static void sub_802AB20(void)
{
    int i, index;

    for (i = 0; i < MAX_RFU_PLAYERS; i++)
    {
        index = sub_802AC00(gUnknown_02022CFC->unk82A8[i].species);
        gUnknown_02022CFC->unk82E4[i].unkC = gPkmnJumpSpecies[index].unk2;
    }

    gUnknown_02022CFC->unk83AC = &gUnknown_02022CFC->unk82E4[gUnknown_02022CFC->unk6];
}

static void sub_802AB98(void)
{
    int i;

    for (i = 0; i < MAX_RFU_PLAYERS; i++)
    {
        gUnknown_02022CFC->unk82E4[i].unkE = 0;
        gUnknown_02022CFC->unk82E4[i].unk10 = 0;
        gUnknown_02022CFC->unk82E4[i].unk12 = 0;
        gUnknown_02022CFC->unk82E4[i].unk0 = 0;
        gUnknown_02022CFC->unk82E4[i].unk4 = 0x7FFFFFFF;
        gUnknown_02022CFC->unk82E4[i].unk14 = 0;
        gUnknown_02022CFC->unk8B[i] = 9;
    }
}

static s16 sub_802AC00(u16 species)
{
    u32 i;
    for (i = 0; i < ARRAY_COUNT(gPkmnJumpSpecies); i++)
    {
        if (gPkmnJumpSpecies[i].species == species)
            return i;
    }

    return -1;
}

static void sub_802AC2C(struct PokemonJump1_MonInfo *monInfo, struct Pokemon *mon)
{
    monInfo->species = GetMonData(mon, MON_DATA_SPECIES);
    monInfo->otId = GetMonData(mon, MON_DATA_OT_ID);
    monInfo->personality = GetMonData(mon, MON_DATA_PERSONALITY);
}

static void sub_802AC58(void)
{
    TransferPlttBuffer();
    LoadOam();
    ProcessSpriteCopyRequests();
}

static void sub_802AC6C(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

static void sub_802AC84(TaskFunc func)
{
    gUnknown_02022CFC->unk4 = CreateTask(func, 1);
    gUnknown_02022CFC->unk8 = 0;
}

static void sub_802ACA0(u8 taskId)
{
    switch (gUnknown_02022CFC->unk8)
    {
    case 0:
        SetVBlankCallback(NULL);
        ResetSpriteData();
        FreeAllSpritePalettes();
        sub_802BE60(sub_802BD84, 5);
        FadeOutMapMusic(4);
        gUnknown_02022CFC->unk8++;
        break;
    case 1:
        if (!FuncIsActiveTask(sub_802BD84))
        {
            sub_802D074(&gUnknown_02022CFC->unkA4);
            LoadWirelessStatusIndicatorSpriteGfx();
            CreateWirelessStatusIndicatorSprite(0, 0);
            gUnknown_02022CFC->unk8++;
        }
        break;
    case 2:
        if (!sub_802D0F0() && IsNotWaitingForBGMStop() == TRUE)
        {
            FadeOutAndPlayNewMapMusic(MUS_RG_JUMP, 8);
            gUnknown_02022CFC->unk8++;
        }
        break;
    case 3:
        if (IsLinkTaskFinished())
        {
            BlendPalettes(0xFFFFFFFF, 16, RGB_BLACK);
            BeginNormalPaletteFade(0xFFFFFFFF, -1, 16, 0, RGB_BLACK);
            SetVBlankCallback(sub_802AC58);
            gUnknown_02022CFC->unk8++;
        }
        break;
    case 4:
        UpdatePaletteFade();
        if (!gPaletteFade.active)
        {
            gUnknown_02022CFC->unk7 = 0;
            gUnknown_02022CFC->unk8++;
        }
        break;
    case 5:
        gUnknown_02022CFC->unk7++;
        if (gUnknown_02022CFC->unk7 >= 20)
        {
            if (gUnknown_02022CFC->isLeader)
                sub_802AC84(sub_802AF80);
            else
                sub_802AC84(sub_802B194);

            sub_802BE80();
            DestroyTask(taskId);
        }
        break;
    }
}

static void sub_802AE14(int arg0)
{
    if (arg0 == 0)
    {
        gUnknown_02022CFC->unk30 = 0x1111;
        gUnknown_02022CFC->unk2C = 1;
    }
    else
    {
        gUnknown_02022CFC->unk30 = (1 << (arg0 - 1)) - 1;
        gUnknown_02022CFC->unk2C = 0;
    }
}

static void sub_802AE50(u8 arg0)
{
    int i;

    gUnknown_02022CFC->unk70.unk0 = arg0;
    gUnknown_02022CFC->unk8 = 0;
    gUnknown_02022CFC->unkA = 0;
    gUnknown_02022CFC->unk48 = 1;
    gUnknown_02022CFC->unk49 = 0;
    for (i = 1; i < gUnknown_02022CFC->unk5; i++)
        gUnknown_02022CFC->unk82E4[i].unk18 = 0;
}

static void sub_802AEA4(void)
{
    int i;
    int count;
    u16 var0;
    u8 var1;
    u16 var2;

    for (i = 1, count = 0; i < gUnknown_02022CFC->unk5; i++)
    {
        var0 = gUnknown_02022CFC->unk82E4[i].unk10;
        if (sub_802E264(&gUnknown_02022CFC->unk82E4[i], i, &var1, &var2))
        {
            gUnknown_02022CFC->unk90[i] = var2;
            gUnknown_02022CFC->unk8B[i] = var1;
            gUnknown_02022CFC->unk82E4[i].unk12 = var0;
        }

        if (gUnknown_02022CFC->unk82E4[i].unk18 && gUnknown_02022CFC->unk8B[i] == gUnknown_02022CFC->unk70.unk0)
            count++;
    }

    if (count == gUnknown_02022CFC->unk5 - 1)
        gUnknown_02022CFC->unk49 = 1;
}

static bool32 (* const gUnknown_082FB5F4[])(void) =
{
    sub_802B248,
    sub_802B2D4,
    sub_802B368,
    sub_802B3D4,
    sub_802B4CC,
    sub_802B5C8,
    sub_802B664,
    sub_802B6B8,
    sub_802B720,
};

static void sub_802AF80(u8 taskId)
{
    sub_802AEA4();
    sub_802C43C();
    if (!gUnknown_02022CFC->unk48 && gUnknown_02022CFC->unk49)
    {
        sub_802AE50(gUnknown_02022CFC->unk4C);
        sub_802AE14(3);
    }

    if (gUnknown_02022CFC->unk48 == 1)
    {
        if (!gUnknown_082FB5F4[gUnknown_02022CFC->unk70.unk0]())
        {
            gUnknown_02022CFC->unk48 = 0;
            gUnknown_02022CFC->unk82E4[gUnknown_02022CFC->unk6].unk18 = 1;
        }
    }

    sub_802C1DC();
    sub_802B008();
}

static void sub_802B008(void)
{
    if (!gUnknown_02022CFC->unk2C)
        sub_802E138(gUnknown_02022CFC->unk82E4, &gUnknown_02022CFC->unk70);

    if (gUnknown_02022CFC->unk30 != 0x1111)
    {
        gUnknown_02022CFC->unk2C++;
        gUnknown_02022CFC->unk2C &= gUnknown_02022CFC->unk30;
    }
}

static void sub_802B044(u8 arg0)
{
    gUnknown_02022CFC->unk70.unk0 = arg0;
    gUnknown_02022CFC->unk8 = 0;
    gUnknown_02022CFC->unkA = 0;
    gUnknown_02022CFC->unk48 = 1;
    gUnknown_02022CFC->unk82E4[gUnknown_02022CFC->unk6].unk18 = 0;
}

static void sub_802B078(void)
{
    int i;
    u16 var0;
    struct PokemonJump1Sub sp0;

    var0 = gUnknown_02022CFC->unk82E4[0].unk10;
    if (sub_802E1BC(gUnknown_02022CFC->unk82E4, &sp0))
    {
        if (gUnknown_02022CFC->unk82E4[gUnknown_02022CFC->unk6].unk18 == 1
         && sp0.unk0 != gUnknown_02022CFC->unk70.unk0)
        {
            sub_802B044(sp0.unk0);
        }

        if (gUnknown_02022CFC->unk70.unk8 != sp0.unk8)
        {
            gUnknown_02022CFC->unk70.unk8 = sp0.unk8;
            gUnknown_02022CFC->unk5C = 1;
            gUnknown_02022CFC->unk70.unk1 = sp0.unk1;
            if (gUnknown_02022CFC->unk70.unk1)
                gUnknown_02022CFC->unk4D = 1;
            else
                gUnknown_02022CFC->unk4D = 0;
        }

        gUnknown_02022CFC->unk70.unk2 = sp0.unk2;
        gUnknown_02022CFC->unk70.unk4 = sp0.unk4;
        gUnknown_02022CFC->unk82E4[0].unk12 = var0;
    }

    for (i = 1; i < gUnknown_02022CFC->unk5; i++)
    {
        if (i != gUnknown_02022CFC->unk6)
        {
            var0 = gUnknown_02022CFC->unk82E4[i].unk10;
            if (sub_802E2D0(&gUnknown_02022CFC->unk82E4[i], i))
                gUnknown_02022CFC->unk82E4[i].unk12 = var0;
        }
    }
}

static bool32 (* const gUnknown_082FB618[])(void) =
{
    sub_802B29C,
    sub_802B31C,
    sub_802B3B4,
    sub_802B470,
    sub_802B568,
    sub_802B628,
    sub_802B664,
    sub_802B704,
    sub_802B720,
};

static void sub_802B194(u8 taskId)
{
    sub_802B078();
    if (gUnknown_02022CFC->unk48)
    {
        if (!gUnknown_082FB618[gUnknown_02022CFC->unk70.unk0]())
        {
            gUnknown_02022CFC->unk48 = 0;
            gUnknown_02022CFC->unk82E4[gUnknown_02022CFC->unk6].unk18 = 1;
            sub_802AE14(3);
        }
    }

    sub_802C1DC();
    sub_802B1FC();
}

static void sub_802B1FC(void)
{
    if (!gUnknown_02022CFC->unk2C)
        sub_802E234(&gUnknown_02022CFC->unk82E4[gUnknown_02022CFC->unk6], gUnknown_02022CFC->unk70.unk0, gUnknown_02022CFC->unk42);

    if (gUnknown_02022CFC->unk30 != 0x1111)
    {
        gUnknown_02022CFC->unk2C++;
        gUnknown_02022CFC->unk2C &= gUnknown_02022CFC->unk30;
    }
}

static bool32 sub_802B248(void)
{
    switch (gUnknown_02022CFC->unk8)
    {
    case 0:
        sub_802AE14(3);
        gUnknown_02022CFC->unk8++;
        // fall through
    case 1:
        if (!sub_802B7E0())
        {
            gUnknown_02022CFC->unk70.unk2 = gUnknown_02022CFC->unk4A;
            gUnknown_02022CFC->unk4C = 1;
            return FALSE;
        }
        break;
    }

    return TRUE;
}

static bool32 sub_802B29C(void)
{
    switch (gUnknown_02022CFC->unk8)
    {
    case 0:
        sub_802AE14(0);
        gUnknown_02022CFC->unk24 = gUnknown_02022CFC->unk70.unk2;
        gUnknown_02022CFC->unk8++;
        // fall through
    case 1:
        return sub_802B7E0();
    }

    return TRUE;
}

static bool32 sub_802B2D4(void)
{
    switch (gUnknown_02022CFC->unk8)
    {
    case 0:
        sub_802C0E8();
        sub_802AE14(5);
        gUnknown_02022CFC->unk8++;
        break;
    case 1:
        if (gUnknown_02022CFC->unk49)
        {
            gUnknown_02022CFC->unk4C = 2;
            return FALSE;
        }
        break;
    }

    return TRUE;
}

static bool32 sub_802B31C(void)
{
    switch (gUnknown_02022CFC->unk8)
    {
    case 0:
        sub_802C0E8();
        sub_802AE14(0);
        gUnknown_02022CFC->unk4A = gUnknown_02022CFC->unk70.unk2;
        gUnknown_02022CFC->unk8++;
        // fall through
    case 1:
        if (sub_802C70C())
            return FALSE;
        break;
    }

    return TRUE;
}

static bool32 sub_802B368(void)
{
    if (!sub_802B8CC())
    {
        gUnknown_02022CFC->unk70.unk2 = gUnknown_02022CFC->unk4A;
        gUnknown_02022CFC->unk4C = 1;
    }
    else if (sub_802C538())
    {
        return TRUE;
    }
    else
    {
        sub_802C0B8();
        gUnknown_02022CFC->unk4C = 3;
    }

    return FALSE;
}

static bool32 sub_802B3B4(void)
{
    if (!sub_802B8CC())
        ;
    else if (sub_802C538())
        return TRUE;
    else
        sub_802C0B8();

    return FALSE;
}

static bool32 sub_802B3D4(void)
{
    switch (gUnknown_02022CFC->unk8)
    {
    case 0:
        sub_802C538();
        if (sub_802C5DC())
            gUnknown_02022CFC->unk8++;
        break;
    case 1:
        if (!sub_802B964())
        {
            if (sub_802C7BC())
            {
                gUnknown_02022CFC->unk70.unk2 = sub_802C7E0();
                gUnknown_02022CFC->unk4C = 7;
            }
            else if (gUnknown_02022CFC->unk70.unk4 >= 200)
            {
                gUnknown_02022CFC->unk70.unk2 = gUnknown_02022CFC->unkE;
                gUnknown_02022CFC->unk4C = 8;
            }
            else
            {
                gUnknown_02022CFC->unk70.unk2 = gUnknown_02022CFC->unkE;
                gUnknown_02022CFC->unk4C = 4;
            }

            gUnknown_02022CFC->unk8++;
            return FALSE;
        }
        break;
    case 2:
        return FALSE;
    }

    return TRUE;
}

static bool32 sub_802B470(void)
{
    switch (gUnknown_02022CFC->unk8)
    {
    case 0:
        if (!sub_802C538())
            sub_802C0B8();
        if (sub_802C5DC())
            gUnknown_02022CFC->unk8++;
        break;
    case 1:
        if (!sub_802B964())
        {
            gUnknown_02022CFC->unk8++;
            return FALSE;
        }
        break;
    case 2:
        return FALSE;
    }

    return TRUE;
}

static bool32 sub_802B4CC(void)
{
    switch (gUnknown_02022CFC->unk8)
    {
    case 0:
        sub_802AE14(4);
        gUnknown_02022CFC->unk8++;
        // fall through
    case 1:
        if (!sub_802BB84())
        {
            sub_802E354(gUnknown_02022CFC->unk70.unk8, gUnknown_02022CFC->unk70.unk4, gUnknown_02022CFC->unk70.unk2);
            gUnknown_02022CFC->unk8++;
        }
        break;
    case 2:
        if (gUnknown_02022CFC->unk49)
        {
            if (sub_802C650())
                gUnknown_02022CFC->unk4C = 5;
            else
                gUnknown_02022CFC->unk4C = 6;

            gUnknown_02022CFC->unk8++;
            return FALSE;
        }
        break;
    case 3:
        return FALSE;
    }

    return TRUE;
}

static bool32 sub_802B568(void)
{
    switch (gUnknown_02022CFC->unk8)
    {
    case 0:
        sub_802AE14(0);
        gUnknown_02022CFC->unk8++;
        // fall through
    case 1:
        if (!sub_802BB84())
        {
            sub_802E354(gUnknown_02022CFC->unk70.unk8, gUnknown_02022CFC->unk70.unk4, gUnknown_02022CFC->unk70.unk2);
            gUnknown_02022CFC->unk42 = gUnknown_02022CFC->unk45;
            return FALSE;
        }
        break;
    }

    return TRUE;
}

static bool32 sub_802B5C8(void)
{
    switch (gUnknown_02022CFC->unk8)
    {
    case 0:
        if (!sub_802BD30())
            gUnknown_02022CFC->unk8++;
        break;
    case 1:
        if (gUnknown_02022CFC->unk49)
        {
            sub_802AA94(gUnknown_02022CFC);
            gUnknown_02022CFC->unk24 = Random();
            gUnknown_02022CFC->unk70.unk2 = gUnknown_02022CFC->unk24;
            gUnknown_02022CFC->unk4C = 0;
            return FALSE;
        }
        break;
    }

    return TRUE;
}

static bool32 sub_802B628(void)
{
    switch (gUnknown_02022CFC->unk8)
    {
    case 0:
        if (!sub_802BD30())
        {
            sub_802AA94(gUnknown_02022CFC);
            gUnknown_02022CFC->unk8++;
            return FALSE;
        }
        break;
    case 1:
        return FALSE;
    }

    return TRUE;
}

static bool32 sub_802B664(void)
{
    switch (gUnknown_02022CFC->unk8)
    {
    case 0:
        gUnknown_02022CFC->unk8 = 1;
        break;
    case 1:
        sub_802AE14(0);
        gUnknown_02022CFC->unk8++;
        break;
    case 2:
        if (!sub_802BC60())
        {
            SetMainCallback2(gUnknown_02022CFC->returnCallback);
            sub_802AA48();
        }
        break;
    }

    return TRUE;
}

static bool32 sub_802B6B8(void)
{
    switch (gUnknown_02022CFC->unk8)
    {
    case 0:
        sub_802AE14(4);
        gUnknown_02022CFC->unk8++;
        break;
    case 1:
        if (!sub_802BA58())
        {
            gUnknown_02022CFC->unk70.unk2 = gUnknown_02022CFC->unkE;
            gUnknown_02022CFC->unk4C = 8;
            return FALSE;
        }
        break;
    }

    return TRUE;
}

static bool32 sub_802B704(void)
{
    sub_802AE14(0);
    if (!sub_802BA58())
        return FALSE;
    else
        return TRUE;
}

static bool32 sub_802B720(void)
{
    switch (gUnknown_02022CFC->unk8)
    {
    case 0:
        sub_802E354(gUnknown_02022CFC->unk70.unk8, gUnknown_02022CFC->unk70.unk4, gUnknown_02022CFC->unk70.unk2);
        sub_802D0C8(5);
        gUnknown_02022CFC->unk8++;
        break;
    case 1:
        if (!sub_802D0F0())
        {
            sub_802AE14(0);
            gUnknown_02022CFC->unk8++;
        }
        break;
    case 2:
        if (sub_802C70C())
        {
            CreateTask(sub_8153688, 6);
            gUnknown_02022CFC->unk8++;
        }
        break;
    case 3:
        if (!FuncIsActiveTask(sub_8153688))
        {
            sub_802DA14();
            gUnknown_02022CFC->unk8++;
        }
        break;
    case 4:
        if (!sub_802DA44())
        {
            gUnknown_02022CFC->unk4C = 4;
            return FALSE;
        }
        break;
    }

    return TRUE;
}

static bool32 sub_802B7E0(void)
{
    switch (gUnknown_02022CFC->unkA)
    {
    case 0:
        sub_802D0C8(2);
        sub_802DDE0();
        gUnknown_02022CFC->unkA++;
        break;
    case 1:
        if (!sub_802D0F0())
        {
            sub_802DDF4(gUnknown_02022CFC->unk6);
            gUnknown_02022CFC->unk3C = 0;
            gUnknown_02022CFC->unkA++;
        }
        break;
    case 2:
        if (++gUnknown_02022CFC->unk3C > 120)
        {
            sub_802D0C8(3);
            gUnknown_02022CFC->unkA++;
        }
        break;
    case 3:
        if (sub_802D0F0() != 1 && sub_802DE08() != 1)
            gUnknown_02022CFC->unkA++;
        break;
    case 4:
        sub_802D0C8(9);
        gUnknown_02022CFC->unkA++;
        break;
    case 5:
        if (!sub_802D0F0())
        {
            sub_802C260();
            sub_802D764();
            gUnknown_02022CFC->unkA++;
        }
        break;
    case 6:
        if (!sub_802D788())
        {
            sub_802C270();
            sub_802BEA0();
            gUnknown_02022CFC->unkA++;
            return FALSE;
        }
        break;
    case 7:
        return FALSE;
    }

    return TRUE;
}

static bool32 sub_802B8CC(void)
{
    sub_802BEE4();
    if (gUnknown_02022CFC->unk36)
    {
        gUnknown_02022CFC->unk36 = 0;
        return FALSE;
    }

    switch (gUnknown_02022CFC->unkA)
    {
    case 0:
        if (sub_802C130(0))
            gUnknown_02022CFC->unkA++;
        else
            break;
        // fall through
    case 1:
        if (gMain.newKeys & A_BUTTON)
        {
            sub_802C164();
            sub_802AE14(3);
            gUnknown_02022CFC->unkA++;
        }
        break;
    case 2:
        if (sub_802C130(1) == TRUE)
            gUnknown_02022CFC->unkA++;
        break;
    case 3:
        if (sub_802C130(0) == TRUE)
            gUnknown_02022CFC->unkA = 0;
        break;
    }

    return TRUE;
}

static bool32 sub_802B964(void)
{
    int i;

    switch (gUnknown_02022CFC->unkA)
    {
    case 0:
        for (i = 0; i < gUnknown_02022CFC->unk5; i++)
        {
            if (sub_802DDB8(i) == 1)
                return TRUE;
        }

        gUnknown_02022CFC->unkA++;
        break;
    case 1:
        for (i = 0; i < gUnknown_02022CFC->unk5; i++)
        {
            if (gUnknown_02022CFC->unk82E4[i].unk10 == 2)
                sub_802DDA0(i);
        }

        sub_802D0C8(1);
        gUnknown_02022CFC->unk3C = 0;
        gUnknown_02022CFC->unkA++;
        break;
    case 2:
        if (++gUnknown_02022CFC->unk3C > 100)
        {
            sub_802D0C8(3);
            gUnknown_02022CFC->unk3C = 0;
            gUnknown_02022CFC->unkA++;
        }
        break;
    case 3:
        if (!sub_802D0F0())
        {
            sub_802DDCC();
            gUnknown_02022CFC->unk70.unk1 = 0;
            sub_802C114();
            gUnknown_02022CFC->unkA++;
            return FALSE;
        }
        break;
    case 4:
        return FALSE;
    }

    return TRUE;
}

static bool32 sub_802BA58(void)
{
    switch (gUnknown_02022CFC->unkA)
    {
    case 0:
        sub_802C808(gUnknown_02022CFC->unk70.unk2, &gUnknown_02022CFC->unk3E, &gUnknown_02022CFC->unk40);
        sub_802D7E8(gUnknown_02022CFC->unk3E, gUnknown_02022CFC->unk40);
        gUnknown_02022CFC->unkA++;
        break;
    case 1:
    case 4:
        if (!sub_802D974())
        {
            gUnknown_02022CFC->unk3C = 0;
            gUnknown_02022CFC->unkA++;
        }
        break;
    case 2:
    case 5:
        gUnknown_02022CFC->unk3C++;
        if (gMain.newKeys & (A_BUTTON | B_BUTTON) || gUnknown_02022CFC->unk3C > 180)
        {
            sub_802DA14();
            gUnknown_02022CFC->unkA++;
        }
        break;
    case 3:
        if (!sub_802DA44())
        {
            gUnknown_02022CFC->unk40 = sub_802C880(gUnknown_02022CFC->unk3E, gUnknown_02022CFC->unk40);
            if (gUnknown_02022CFC->unk40 && AddBagItem(gUnknown_02022CFC->unk3E, gUnknown_02022CFC->unk40))
            {
                if (!CheckBagHasSpace(gUnknown_02022CFC->unk3E, 1))
                {
                    sub_802D884(gUnknown_02022CFC->unk3E);
                    gUnknown_02022CFC->unkA = 4;
                }
                else
                {
                    gUnknown_02022CFC->unkA = 6;
                    break;
                }
            }
            else
            {
                sub_802D8FC(gUnknown_02022CFC->unk3E);
                gUnknown_02022CFC->unkA = 4;
            }
        }
        break;
    case 6:
        if (!sub_802DA44())
            return FALSE;
        break;
    }

    return TRUE;
}

static bool32 sub_802BB84(void)
{
    s8 input;

    switch (gUnknown_02022CFC->unkA)
    {
    case 0:
        sub_802D0C8(4);
        gUnknown_02022CFC->unkA++;
        break;
    case 1:
        if (!sub_802D0F0())
            gUnknown_02022CFC->unkA++;
        break;
    case 2:
        input = sub_802DA8C();
        switch (input)
        {
        case MENU_B_PRESSED:
        case 1:
            gUnknown_02022CFC->unk45 = 1;
            sub_802D0C8(6);
            gUnknown_02022CFC->unkA++;
            break;
        case 0:
            gUnknown_02022CFC->unk45 = 2;
            sub_802D0C8(6);
            gUnknown_02022CFC->unkA++;
            break;
        }
        break;
    case 3:
        if (!sub_802D0F0())
            gUnknown_02022CFC->unkA++;
        break;
    case 4:
        sub_802D0C8(8);
        gUnknown_02022CFC->unkA++;
        break;
    case 5:
        if (!sub_802D0F0())
        {
            gUnknown_02022CFC->unkA++;
            return FALSE;
        }
        break;
    case 6:
        return FALSE;
    }

    return TRUE;
}

static bool32 sub_802BC60(void)
{
    int var0;

    switch (gUnknown_02022CFC->unkA)
    {
    case 0:
        sub_802DA14();
        gUnknown_02022CFC->unkA++;
        break;
    case 1:
        if (!sub_802DA44())
        {
            sub_802D0C8(7);
            gUnknown_02022CFC->unkA++;
        }
        break;
    case 2:
        var0 = sub_802D0F0();
        if (!var0)
        {
            gUnknown_02022CFC->unk3C = var0;
            gUnknown_02022CFC->unkA++;
        }
        break;
    case 3:
        if (++gUnknown_02022CFC->unk3C > 120)
        {
            BeginNormalPaletteFade(0xFFFFFFFF, -1, 0, 16, RGB_BLACK);
            gUnknown_02022CFC->unkA++;
        }
        break;
    case 4:
        if (!gPaletteFade.active)
        {
            SetCloseLinkCallback();
            gUnknown_02022CFC->unkA++;
        }
        break;
    case 5:
        if (!gReceivedRemoteLinkPlayers)
            return FALSE;
        break;
    }

    return TRUE;
}

static bool32 sub_802BD30(void)
{
    switch (gUnknown_02022CFC->unkA)
    {
    case 0:
        sub_802DA14();
        sub_802DD64(0);
        gUnknown_02022CFC->unkA++;
        break;
    case 1:
        if (!sub_802DA44())
        {
            gUnknown_02022CFC->unkA++;
            return FALSE;
        }
        break;
    case 2:
        return FALSE;
    }

    return TRUE;
}

static void sub_802BD84(u8 taskId)
{
    int i;
    s16 *taskData = gTasks[taskId].data;
    struct PokemonJump1 *ptr = (struct PokemonJump1 *)GetWordTaskArg(taskId, 14);

    switch (taskData[0])
    {
    case 0:
        for (i = 0; i < MAX_RFU_PLAYERS; i++)
            taskData[i + 2] = 0;

        taskData[0]++;
        // fall through
    case 1:
        sub_802E0AC(&ptr->unk82A8[ptr->unk6]);
        for (i = 0; i < MAX_RFU_PLAYERS; i++)
        {
            if (!taskData[i + 2] && sub_802E0D0(i, &ptr->unk82A8[i]))
            {
                StringCopy(ptr->unk82E4[i].unk1C, gLinkPlayers[i].name);
                taskData[i + 2] = 1;
                taskData[1]++;
                if (taskData[1] == ptr->unk5)
                {
                    sub_802AB20();
                    DestroyTask(taskId);
                    break;
                }
            }
        }
        break;
    }
}

static void sub_802BE60(TaskFunc func, u8 taskPriority)
{
    u8 taskId = CreateTask(func, taskPriority);
    SetWordTaskArg(taskId, 14, (u32)gUnknown_02022CFC);
}

static void sub_802BE80(void)
{
    gUnknown_02022CFC->unk4A = 0;
    gUnknown_02022CFC->unk14 = 6;
    gUnknown_02022CFC->unk34 = 0;
    gUnknown_02022CFC->unk1C = 0;
    gUnknown_02022CFC->unk36 = 0;
    gUnknown_02022CFC->unk10 = 0;
}

static void sub_802BEA0(void)
{
    gUnknown_02022CFC->unk4A = 0;
    gUnknown_02022CFC->unk34 = 0x6FF;
    gUnknown_02022CFC->unk14 = 7;
    gUnknown_02022CFC->unk36 = 0;
    gUnknown_02022CFC->unk10 = 0;
    gUnknown_02022CFC->unk51 = 0;
    gUnknown_02022CFC->unk50 = 0;
    gUnknown_02022CFC->unk20 = 0;
    gUnknown_02022CFC->unk4E = 0;
    gUnknown_02022CFC->unk6C = 0;
    sub_802BF7C();
}

static void sub_802BEE4(void)
{
    if (gUnknown_02022CFC->unk46)
    {
        gUnknown_02022CFC->unk4A++;
        gUnknown_02022CFC->unk34 += sub_802BF48();
        if (gUnknown_02022CFC->unk34 >= 0x9FF)
            gUnknown_02022CFC->unk34 -= 0x9FF;

        gUnknown_02022CFC->unk18 = gUnknown_02022CFC->unk14;
        gUnknown_02022CFC->unk14 = gUnknown_02022CFC->unk34 >> 8;
        if (gUnknown_02022CFC->unk14 > 6 && gUnknown_02022CFC->unk18 < 7)
        {
            gUnknown_02022CFC->unk36++;
            sub_802BF7C();
        }
    }
}

static int sub_802BF48(void)
{
    int result;

    if (gUnknown_02022CFC->unk10)
        return 0;

    result = gUnknown_02022CFC->unk1C;
    if (gUnknown_02022CFC->unk34 <= 0x5FF)
    {
        gUnknown_02022CFC->unk20 += 80;
        result += gUnknown_02022CFC->unk20 >> 8;
    }

    return result;
}

static const u16 gUnknown_082FB63C[] = {0x1a, 0x1f, 0x24, 0x29, 0x2e, 0x33, 0x38, 0x3d};
static const u16 gUnknown_082FB64C[] = {0, 1, 1, 2};

static void sub_802BF7C(void)
{
    int var0;

    gUnknown_02022CFC->unk20 = 0;
    if (gUnknown_02022CFC->unk4E)
    {
        gUnknown_02022CFC->unk4E--;
        if (gUnknown_02022CFC->unk6C)
        {
            if (sub_802C098() % 4 != 0)
            {
                gUnknown_02022CFC->unk1C = gUnknown_02022CFC->unk28;
            }
            else
            {
                if (gUnknown_02022CFC->unk28 > 54)
                    gUnknown_02022CFC->unk1C = 30;
                else
                    gUnknown_02022CFC->unk1C = 82;
            }
        }
    }
    else
    {
        if (!(gUnknown_02022CFC->unk50 & 8))
        {
            gUnknown_02022CFC->unk28 = gUnknown_082FB63C[gUnknown_02022CFC->unk50] + (gUnknown_02022CFC->unk51 * 7);
            gUnknown_02022CFC->unk4E = gUnknown_082FB64C[sub_802C098() % ARRAY_COUNT(gUnknown_082FB64C)] + 2;
            gUnknown_02022CFC->unk50++;
        }
        else
        {
            if (gUnknown_02022CFC->unk50 == 8)
            {
                if (gUnknown_02022CFC->unk51 < 3)
                    gUnknown_02022CFC->unk51++;
                else
                    gUnknown_02022CFC->unk6C = 1;
            }

            var0 = gUnknown_082FB63C[15 - gUnknown_02022CFC->unk50];
            gUnknown_02022CFC->unk28 = var0 + (gUnknown_02022CFC->unk51 * 7);
            if (++gUnknown_02022CFC->unk50 > 15)
            {
                if (sub_802C098() % 4 == 0)
                    gUnknown_02022CFC->unk28 -= 5;

                gUnknown_02022CFC->unk50 = 0;
            }
        }

        gUnknown_02022CFC->unk1C = gUnknown_02022CFC->unk28;
    }
}

static int sub_802C098(void)
{
    // The number 1103515245 comes from the example implementation of rand and srand
    gUnknown_02022CFC->unk24 = gUnknown_02022CFC->unk24 * 1103515245 + 24691;
    return gUnknown_02022CFC->unk24 >> 16;
}

static void sub_802C0B8(void)
{
    gUnknown_02022CFC->unk10 = 1;
    gUnknown_02022CFC->unk14 = 6;
    gUnknown_02022CFC->unk34 = 0x5FF;
    sub_802C270();
}

static int sub_802C0DC(void)
{
    return gUnknown_02022CFC->unk10;
}

static void sub_802C0E8(void)
{
    int i;
    for (i = 0; i < MAX_RFU_PLAYERS; i++)
        gUnknown_02022CFC->unk82E4[i].unk14 = 0;
}

static void sub_802C114(void)
{
    gUnknown_02022CFC->unk83AC->unk10 = 0;
    gUnknown_02022CFC->unk83AC->unk12 = 0;
}

static bool32 sub_802C130(u16 arg0)
{
    if (gUnknown_02022CFC->unk82E4[gUnknown_02022CFC->unk6].unk10 == arg0)
        return TRUE;
    else
        return FALSE;
}

static void sub_802C164(void)
{
    gUnknown_02022CFC->unk83AC->unkE = gUnknown_02022CFC->unk4A;
    gUnknown_02022CFC->unk83AC->unk12 = gUnknown_02022CFC->unk83AC->unk10;
    gUnknown_02022CFC->unk83AC->unk10 = 1;
}

static void sub_802C18C(void)
{
    gUnknown_02022CFC->unk83AC->unk12 = gUnknown_02022CFC->unk83AC->unk10;
    gUnknown_02022CFC->unk83AC->unk10 = 2;
    gUnknown_02022CFC->unk83AC->unkE = gUnknown_02022CFC->unk4A;
    gUnknown_02022CFC->unk83AC->unk14 = 2;
}

static void sub_802C1BC(void)
{
    gUnknown_02022CFC->unk83AC->unk12 = gUnknown_02022CFC->unk83AC->unk10;
    gUnknown_02022CFC->unk83AC->unk10 = 0;
}

static const u16 gUnknown_082FB654[] = {SE_REGI, SE_REAPOKE, SE_W234, SE_RG_EXCELLENT};

static void sub_802C1DC(void)
{
    if (gUnknown_02022CFC->unk5C)
    {
        sub_802DD64(gUnknown_02022CFC->unk70.unk8);
        gUnknown_02022CFC->unk5C = 0;
        if (gUnknown_02022CFC->unk4D)
        {
            int index = sub_802DCCC(gUnknown_02022CFC->unk70.unk1);
            PlaySE(gUnknown_082FB654[index - 2]);
            gUnknown_02022CFC->unk4D = 0;
        }
    }

    sub_802DD74(gUnknown_02022CFC->unk70.unk4);
    sub_802C280();
    sub_802C240();
}

static void sub_802C240(void)
{
    if (gUnknown_02022CFC->unk46)
        sub_802DC9C(gUnknown_02022CFC->unk14);
}

static void sub_802C260(void)
{
    gUnknown_02022CFC->unk46 = 0;
}

static void sub_802C270(void)
{
    gUnknown_02022CFC->unk46 = 1;
}

static void sub_802C280(void)
{
    int i;
    int whichSound = 0;
    int numLinkPlayers = gUnknown_02022CFC->unk5;

    for (i = 0; i < numLinkPlayers; i++)
    {
        switch (gUnknown_02022CFC->unk82E4[i].unk10)
        {
        case 0:
            sub_802DC80(i, 0);
            break;
        case 1:
            if (gUnknown_02022CFC->unk82E4[i].unk12 != 1 || gUnknown_02022CFC->unk82E4[i].unkE != gUnknown_02022CFC->unk9A[i])
            {
                if (i == gUnknown_02022CFC->unk6)
                    gUnknown_02022CFC->unk82E4[i].unk12 = 1;

                whichSound |= 0x1;
                gUnknown_02022CFC->unk82E4[i].unk4 = 0x7FFFFFFF;
                gUnknown_02022CFC->unk9A[i] = gUnknown_02022CFC->unk82E4[i].unkE;
            }

            sub_802C398(i);
            break;
        case 2:
            if (gUnknown_02022CFC->unk82E4[i].unk12 != 2)
            {
                if (i == gUnknown_02022CFC->unk6)
                    gUnknown_02022CFC->unk82E4[i].unk12 = 2;

                whichSound |= 0x2;
                sub_802DD88(i);
            }
            break;
        }
    }

    if (whichSound & 0x2)
        PlaySE(SE_RG_NAWAMISS);
    else if (whichSound & 0x1)
        PlaySE(SE_DANSA);
}

static const s8 gUnknown_082FB65C[][48] =
{
    {-3, -6, -8, -10, -13, -15, -17, -19, -21, -23, -25, -27, -28, -29, -30, -30, -30, -28, -27,
    -26, -25, -23, -22, -20, -18, -17, -15, -13, -11, -8, -6, -4, -1},

    {-3, -6, -9, -11, -14, -16, -18, -20, -22, -24, -26, -28, -29, -30, -30, -28, -26, -24, -22,
    -20, -18, -16, -14, -11, -9, -6, -4, -1},

    {-3, -6, -9, -11, -13, -15, -17, -19, -21, -23, -25, -27, -28, -29, -30, -30, -30, -30, -29,
    -29, -28, -28, -27, -27, -26, -25, -24, -22, -20, -18, -16, -14,
    -12, -11, -9, -6, -4, -1},
};

static void sub_802C398(int multiplayerId)
{
    int var0;
    int var1;
    struct PokemonJump1_82E4 *player;

    if (gUnknown_02022CFC->unk68)
        return;

    player = &gUnknown_02022CFC->unk82E4[multiplayerId];
    if (player->unk4 != 0x7FFFFFFF)
    {
        player->unk4++;
        var0 = player->unk4;
    }
    else
    {
        var0 = gUnknown_02022CFC->unk4A - player->unkE;
        if (var0 >= 65000)
        {
            var0 -= 65000;
            var0 += gUnknown_02022CFC->unk4A;
        }

        player->unk4 = var0;
    }

    if (var0 < 4)
        return;

    var0 -= 4;
    if (var0 < 48)
        var1 = gUnknown_082FB65C[player->unkC][var0];
    else
        var1 = 0;

    sub_802DC80(multiplayerId, var1);
    if (!var1 && multiplayerId == gUnknown_02022CFC->unk6)
        sub_802C1BC();

    player->unk0 = var1;
}

static void sub_802C43C(void)
{
    if (gUnknown_02022CFC->unk14 == 8 && gUnknown_02022CFC->unk18 == 7)
    {
        if (gUnknown_02022CFC->unk58 == 0)
        {
            sub_802C780();
            gUnknown_02022CFC->unk54 = 0;
            gUnknown_02022CFC->unk58 = 1;
            gUnknown_02022CFC->unk70.unk1 = 0;
        }
        else
        {
            if (gUnknown_02022CFC->unk54 == 5)
            {
                gUnknown_02022CFC->unkC++;
                sub_802C7A0(gUnknown_02022CFC->unkC);
            }
            else
            {
                gUnknown_02022CFC->unkC = 0;
            }

            if (gUnknown_02022CFC->unk54 > 1)
            {
                gUnknown_02022CFC->unk64 = 1;
                memcpy(gUnknown_02022CFC->unk86, gUnknown_02022CFC->unk81, sizeof(u8) * MAX_RFU_PLAYERS);
            }

            sub_802C780();
            gUnknown_02022CFC->unk54 = 0;
            gUnknown_02022CFC->unk58 = 1;
            gUnknown_02022CFC->unk70.unk1 = 0;
            if (gUnknown_02022CFC->unk70.unk4 < 9999)
                gUnknown_02022CFC->unk70.unk4++;

            sub_802C688(10);
            sub_802AE14(3);
        }
    }

    if (gUnknown_02022CFC->unk64 && (sub_802C618() == TRUE || !gUnknown_02022CFC->unk14))
    {
        int var0 = sub_802C73C(gUnknown_02022CFC->unk86);
        sub_802C688(sub_802C790(var0));
        sub_802AE14(3);
        gUnknown_02022CFC->unk64 = 0;
    }

    if (gUnknown_02022CFC->unk58)
    {
        int var1 = sub_802C6B0();
        if (var1 > gUnknown_02022CFC->unk54)
        {
            gUnknown_02022CFC->unk54 = var1;
            memcpy(gUnknown_02022CFC->unk81, gUnknown_02022CFC->unk7C, sizeof(u8) * MAX_RFU_PLAYERS);
        }
    }
}

static bool32 sub_802C538(void)
{
    int i;

    if (gUnknown_02022CFC->unk14 == 6 && !gUnknown_02022CFC->unk83AC->unk0)
    {
        if (gUnknown_02022CFC->unk83AC->unk12 == 1 && sub_802C0DC() == 1)
        {
            gUnknown_02022CFC->unk83AC->unk14 = 1;
        }
        else
        {
            sub_802C18C();
            sub_802AE14(3);
        }
    }

    if (gUnknown_02022CFC->unk14 == 7
     && gUnknown_02022CFC->unk18 == 6
     && gUnknown_02022CFC->unk83AC->unk10 != 2)
    {
        gUnknown_02022CFC->unk83AC->unk14 = 1;
        sub_802AE14(3);
    }

    for (i = 0; i < gUnknown_02022CFC->unk5; i++)
    {
        if (gUnknown_02022CFC->unk82E4[i].unk10 == 2)
            return FALSE;
    }

    return TRUE;
}

static bool32 sub_802C5DC(void)
{
    int i;
    int numPlayers = gUnknown_02022CFC->unk5;
    int count = 0;
    for (i = 0; i < numPlayers; i++)
    {
        if (gUnknown_02022CFC->unk82E4[i].unk14)
            count++;
    }

    return count == numPlayers;
}

static bool32 sub_802C618(void)
{
    int i;
    for (i = 0; i < gUnknown_02022CFC->unk5; i++)
    {
        if (gUnknown_02022CFC->unk82E4[i].unk14 != 1)
            return FALSE;
    }

    return TRUE;
}

static bool32 sub_802C650(void)
{
    int i;

    if (gUnknown_02022CFC->unk45 == 1)
        return FALSE;

    for (i = 1; i < gUnknown_02022CFC->unk5; i++)
    {
        if (gUnknown_02022CFC->unk90[i] == 1)
            return FALSE;
    }

    return TRUE;
}

static void sub_802C688(int arg0)
{
    gUnknown_02022CFC->unk70.unk8 += arg0;
    gUnknown_02022CFC->unk5C = 1;
    if (gUnknown_02022CFC->unk70.unk8 >= 99990)
        gUnknown_02022CFC->unk70.unk8 = 99990;
}

static int sub_802C6B0(void)
{
    int i;
    int count = 0;
    int numPlayers = gUnknown_02022CFC->unk5;

    for (i = 0; i < numPlayers; i++)
    {
        if (gUnknown_02022CFC->unk82E4[i].unk0 == -30)
        {
            gUnknown_02022CFC->unk7C[i] = 1;
            count++;
        }
        else
        {
            gUnknown_02022CFC->unk7C[i] = 0;
        }
    }

    return count;
}

static bool32 sub_802C70C(void)
{
    return !gUnknown_03005000.unk_124.unk_8c2 && !gUnknown_03005000.unk_9e8.unk_232;
}

static int sub_802C73C(u8 *arg0)
{
    int i;
    int flags;
    int count;

    for (i = 0, flags = 0, count = 0; i < MAX_RFU_PLAYERS; i++)
    {
        if (arg0[i])
        {
            flags |= 1 << i;
            count++;
        }
    }

    gUnknown_02022CFC->unk70.unk1 = flags;
    if (flags)
        gUnknown_02022CFC->unk4D = 1;

    return count;
}

static void sub_802C780(void)
{
    gUnknown_02022CFC->unk44 = 0;
}

static const int gUnknown_082FB6EC[] = {0, 0, 0x32, 0x64, 0xc8, 0x1f4};

static int sub_802C790(int arg0)
{
    return gUnknown_082FB6EC[arg0];
}

static void sub_802C7A0(u16 arg0)
{
    if (arg0 > gUnknown_02022CFC->unkE)
        gUnknown_02022CFC->unkE = arg0;
}

static const u16 gUnknown_082FB704[] = {0x8a, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93};
static const u32 gUnknown_082FB714[][2] =
{
    {0x1388, 1},
    {0x1f40, 2},
    {0x2ee0, 3},
    {0x3e80, 4},
    {0x4e20, 5},
};

static bool32 sub_802C7BC(void)
{
    if (gUnknown_02022CFC->unk70.unk8 >= gUnknown_082FB714[0][0])
        return TRUE;
    else
        return FALSE;
}

static u16 sub_802C7E0(void)
{
    u16 lo = sub_802C818();
    u16 hi = sub_802C838();
    return (hi << 12) | (lo & 0xFFF);
}

static void sub_802C808(u16 arg0, u16 *arg1, u16 *arg2)
{
    *arg2 = arg0 >> 12;
    *arg1 = arg0 & 0xFFF;
}

static u16 sub_802C818(void)
{
    u16 index = Random() % ARRAY_COUNT(gUnknown_082FB704);
    return gUnknown_082FB704[index];
}

#ifdef NONMATCHING
// Impossible to match.
static u16 sub_802C838(void)
{
    u32 val, i;

    val = 0;
    for (i = 0; i < 5; val = gUnknown_082FB714[i][1], i++)
    {
        if (gUnknown_02022CFC->unk70.unk8 < gUnknown_082FB714[i][0])
            break;
    }

    return val;
}
#else
NAKED
static u16 sub_802C838(void)
{
    asm_unified("\n\
    push {r4-r6,lr}\n\
    movs r5, 0\n\
    movs r4, 0\n\
    ldr r3, =gUnknown_02022CFC\n\
    ldr r0, [r3]\n\
    ldr r2, =gUnknown_082FB714\n\
    ldr r1, [r0, 0x78]\n\
    ldr r0, [r2]\n\
    cmp r1, r0\n\
    bcc _0802C874\n\
    ldr r5, [r2, 0x4]\n\
    adds r6, r3, 0\n\
    adds r3, r2, 0x4\n\
_0802C852:\n\
    adds r3, 0x8\n\
    adds r2, 0x8\n\
    adds r4, 0x1\n\
    cmp r4, 0x4\n\
    bhi _0802C874\n\
    ldr r0, [r6]\n\
    ldr r1, [r0, 0x78]\n\
    ldr r0, [r2]\n\
    cmp r1, r0\n\
    bcc _0802C874\n\
    ldr r5, [r3]\n\
    b _0802C852\n\
    .pool\n\
_0802C874:\n\
    lsls r0, r5, 16\n\
    lsrs r0, 16\n\
    pop {r4-r6}\n\
    pop {r1}\n\
    bx r1");
}
#endif

static u16 sub_802C880(u16 item, u16 quantity)
{
    while (quantity && !CheckBagHasSpace(item, quantity))
        quantity--;

    return quantity;
}

static u16 sub_802C8AC(void)
{
    return GetLinkPlayerCount();
}

static u16 sub_802C8BC(void)
{
    return gUnknown_02022CFC->unk6;
}

static struct PokemonJump1_MonInfo *sub_802C8C8(u8 multiplayerId)
{
    return &gUnknown_02022CFC->unk82A8[multiplayerId];
}

static u8 *sub_802C8E8(u8 multiplayerId)
{
    return gUnknown_02022CFC->unk82E4[multiplayerId].unk1C;
}

bool32 sub_802C908(u16 species)
{
    return sub_802AC00(species) > -1;
}

void sub_802C920(void)
{
    int i;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (GetMonData(&gPlayerParty[i], MON_DATA_SANITY_HAS_SPECIES))
        {
            u16 species = GetMonData(&gPlayerParty[i], MON_DATA_SPECIES2);
            if (sub_802C908(species))
            {
                gSpecialVar_Result = 1;
                return;
            }
        }
    }

    gSpecialVar_Result = 0;
}

// Large group of data.
static const u16 gPkmnJumpPal1[] = INCBIN_U16("graphics/link_games/pkmnjump_pal1.gbapal");
static const u16 gPkmnJumpPal2[] = INCBIN_U16("graphics/link_games/pkmnjump_pal2.gbapal");

static const u32 gPkmnJumpRopeGfx1[] = INCBIN_U32("graphics/link_games/pkmnjump_rope1.4bpp.lz");
static const u32 gPkmnJumpRopeGfx2[] = INCBIN_U32("graphics/link_games/pkmnjump_rope2.4bpp.lz");
static const u32 gPkmnJumpRopeGfx3[] = INCBIN_U32("graphics/link_games/pkmnjump_rope3.4bpp.lz");
static const u32 gPkmnJumpRopeGfx4[] = INCBIN_U32("graphics/link_games/pkmnjump_rope4.4bpp.lz");

static const u32 gPkmnJumpStarGfx[] = INCBIN_U32("graphics/link_games/pkmnjump_star.4bpp.lz");

static const struct CompressedSpriteSheet gUnknown_082FBE08[] =
{
    {gPkmnJumpRopeGfx1, 0x600, 5},
    {gPkmnJumpRopeGfx2, 0x0c00, 6},
    {gPkmnJumpRopeGfx3, 0x0600, 7},
    {gPkmnJumpRopeGfx4, 0x0600, 8},
    {gPkmnJumpStarGfx, 0x0200, 10},
};

static const struct SpritePalette gUnknown_082FBE30[] =
{
    {gPkmnJumpPal1, 5},
    {gPkmnJumpPal2, 6},
};

// Forward declarations.
static const struct OamData sOamData_82FBEC8;
static const struct SpriteTemplate gUnknown_082FBF78;
static const struct SpriteTemplate gUnknown_082FBF90;
static const struct SpriteTemplate gUnknown_082FBFA8;
static const struct SpriteTemplate gUnknown_082FBFC0;

static const struct SpriteTemplate gUnknown_082FBE40 =
{
    .tileTag = 0,
    .paletteTag = 0,
    .oam = &sOamData_82FBEC8,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const s16 gUnknown_082FBE58[][10] =
{
    {0x60, 0x60, 0x60, 0x72, 0x78, 0x78, 0x78, 0x72, 0x60, 0x60},
    {0x46, 0x50, 0x60, 0x72, 0x78, 0x80, 0x78, 0x72, 0x60, 0x50},
    {0x32, 0x48, 0x60, 0x72, 0x80, 0x88, 0x80, 0x72, 0x60, 0x48},
    {0x2a, 0x48, 0x60, 0x72, 0x80, 0x88, 0x80, 0x72, 0x60, 0x48},
};

static const s16 gUnknown_082FBEA8[] = {0x10, 0x28, 0x48, 0x68, 0x88, 0xa8, 0xc8, 0xe0};

static const struct SpriteTemplate *const gUnknown_082FBEB8[] =
{
    &gUnknown_082FBF78,
    &gUnknown_082FBF90,
    &gUnknown_082FBFA8,
    &gUnknown_082FBFC0,
};

static const struct OamData sOamData_82FBEC8 =
{
    .y = 0,
    .affineMode = 0,
    .objMode = 0,
    .mosaic = 0,
    .bpp = 0,
    .shape = 0,
    .x = 0,
    .matrixNum = 0,
    .size = 3,
    .tileNum = 0,
    .priority = 2,
    .paletteNum = 0,
    .affineParam = 0
};

static const struct OamData sOamData_82FBED0 =
{
    .y = 0,
    .affineMode = 0,
    .objMode = 0,
    .mosaic = 0,
    .bpp = 0,
    .shape = 2,
    .x = 0,
    .matrixNum = 0,
    .size = 2,
    .tileNum = 0,
    .priority = 2,
    .paletteNum = 0,
    .affineParam = 0
};

static const struct OamData sOamData_82FBED8 =
{
    .y = 0,
    .affineMode = 0,
    .objMode = 0,
    .mosaic = 0,
    .bpp = 0,
    .shape = 0,
    .x = 0,
    .matrixNum = 0,
    .size = 2,
    .tileNum = 0,
    .priority = 2,
    .paletteNum = 0,
    .affineParam = 0
};

static const struct OamData sOamData_82FBEE0 =
{
    .y = 0,
    .affineMode = 0,
    .objMode = 0,
    .mosaic = 0,
    .bpp = 0,
    .shape = 1,
    .x = 0,
    .matrixNum = 0,
    .size = 2,
    .tileNum = 0,
    .priority = 2,
    .paletteNum = 0,
    .affineParam = 0
};

static const union AnimCmd sSpriteAnim_82FBEE8[] =
{
    ANIMCMD_FRAME(0, 1),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_82FBEF0[] =
{
    ANIMCMD_FRAME(8, 1),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_82FBEF8[] =
{
    ANIMCMD_FRAME(16, 1),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_82FBF00[] =
{
    ANIMCMD_FRAME(24, 1),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_82FBF08[] =
{
    ANIMCMD_FRAME(32, 1),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_82FBF10[] =
{
    ANIMCMD_FRAME(40, 1),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_82FBF18[] =
{
    ANIMCMD_FRAME(0, 1),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_82FBF20[] =
{
    ANIMCMD_FRAME(16, 1),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_82FBF28[] =
{
    ANIMCMD_FRAME(32, 1),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_82FBF30[] =
{
    ANIMCMD_FRAME(48, 1),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_82FBF38[] =
{
    ANIMCMD_FRAME(64, 1),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_82FBF40[] =
{
    ANIMCMD_FRAME(80, 1),
    ANIMCMD_END
};

static const union AnimCmd *const sSpriteAnimTable_82FBF48[] =
{
    sSpriteAnim_82FBEE8,
    sSpriteAnim_82FBEF0,
    sSpriteAnim_82FBEF8,
    sSpriteAnim_82FBF00,
    sSpriteAnim_82FBF08,
    sSpriteAnim_82FBF10
};

static const union AnimCmd *const sSpriteAnimTable_82FBF60[] =
{
    sSpriteAnim_82FBF18,
    sSpriteAnim_82FBF20,
    sSpriteAnim_82FBF28,
    sSpriteAnim_82FBF30,
    sSpriteAnim_82FBF38,
    sSpriteAnim_82FBF40
};

static const struct SpriteTemplate gUnknown_082FBF78 =
{
    .tileTag = 5,
    .paletteTag = 5,
    .oam = &sOamData_82FBED0,
    .anims = sSpriteAnimTable_82FBF48,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate gUnknown_082FBF90 =
{
    .tileTag = 6,
    .paletteTag = 5,
    .oam = &sOamData_82FBED8,
    .anims = sSpriteAnimTable_82FBF60,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate gUnknown_082FBFA8 =
{
    .tileTag = 7,
    .paletteTag = 5,
    .oam = &sOamData_82FBEE0,
    .anims = sSpriteAnimTable_82FBF48,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate gUnknown_082FBFC0 =
{
    .tileTag = 8,
    .paletteTag = 5,
    .oam = &sOamData_82FBEE0,
    .anims = sSpriteAnimTable_82FBF48,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct OamData sOamData_82FBFD8 =
{
    .y = 0,
    .affineMode = 0,
    .objMode = 0,
    .mosaic = 0,
    .bpp = 0,
    .shape = 0,
    .x = 0,
    .matrixNum = 0,
    .size = 1,
    .tileNum = 0,
    .priority = 1,
    .paletteNum = 0,
    .affineParam = 0
};

static const union AnimCmd sSpriteAnim_82FBFE0[] =
{
    ANIMCMD_FRAME(0, 0),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_82FBFE8[] =
{
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_FRAME(4, 4),
    ANIMCMD_FRAME(8, 4),
    ANIMCMD_FRAME(12, 4),
    ANIMCMD_LOOP(1),
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_END
};

static const union AnimCmd *const sSpriteAnimTable_82FC004[] =
{
    sSpriteAnim_82FBFE0,
    sSpriteAnim_82FBFE8
};

static const struct SpriteTemplate gUnknown_082FC00C =
{
    .tileTag = 10,
    .paletteTag = 5,
    .oam = &sOamData_82FBFD8,
    .anims = sSpriteAnimTable_82FC004,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

// Back to code
static void sub_802C974(struct PokemonJump2 *arg0)
{
    int i;

    for (i = 0; i < ARRAY_COUNT(gUnknown_082FBE08); i++)
        LoadCompressedSpriteSheet(&gUnknown_082FBE08[i]);

    for (i = 0; i < ARRAY_COUNT(gUnknown_082FBE30); i++)
        LoadSpritePalette(&gUnknown_082FBE30[i]);

    arg0->unkE = IndexOfSpritePaletteTag(5);
    arg0->unkF = IndexOfSpritePaletteTag(6);
}

static void sub_802C9BC(struct Sprite *sprite)
{
    int i;
    for (i = 0; i < 8; i++)
        sprite->data[i] = 0;
}

static void sub_802C9D4(struct PokemonJump2 *arg0, struct PokemonJump1_MonInfo *jumpMon, s16 x, s16 y, u8 multiplayerId)
{
    struct SpriteTemplate spriteTemplate;
    struct SpriteSheet spriteSheet;
    struct CompressedSpritePalette spritePalette;
    u8 *buffer;
    u8 *unusedBuffer;
    u8 subpriority;
    u8 spriteId;

    spriteTemplate = gUnknown_082FBE40;
    buffer = Alloc(0x2000);
    unusedBuffer = Alloc(0x800);
    if (multiplayerId == sub_802C8BC())
        subpriority = 3;
    else
        subpriority = multiplayerId + 4;

    if (buffer && unusedBuffer)
    {
        HandleLoadSpecialPokePic(
            &gMonStillFrontPicTable[jumpMon->species],
            buffer,
            jumpMon->species,
            jumpMon->personality);

        spriteSheet.data = buffer;
        spriteSheet.tag = multiplayerId;
        spriteSheet.size = 0x800;
        LoadSpriteSheet(&spriteSheet);

        spritePalette.data = GetMonSpritePalFromSpeciesAndPersonality(jumpMon->species, jumpMon->otId, jumpMon->personality);
        spritePalette.tag = multiplayerId;
        LoadCompressedSpritePalette(&spritePalette);

        Free(buffer);
        Free(unusedBuffer);

        spriteTemplate.tileTag += multiplayerId;
        spriteTemplate.paletteTag += multiplayerId;
        spriteId = CreateSprite(&spriteTemplate, x, y, subpriority);
        if (spriteId != MAX_SPRITES)
        {
            arg0->unk81A8[multiplayerId] = &gSprites[spriteId];
            arg0->unk81FC[multiplayerId] = subpriority;
            return;
        }
    }

    arg0->unk81A8[multiplayerId] = NULL;
}

static void sub_802CB14(struct PokemonJump2 *arg0, int multiplayerId)
{
    sub_802C9BC(arg0->unk81BC[multiplayerId]);
    arg0->unk81BC[multiplayerId]->data[7] = arg0->unk81A8[multiplayerId] - gSprites;
    arg0->unk81BC[multiplayerId]->invisible = 0;
    arg0->unk81BC[multiplayerId]->pos1.y = 96;
    arg0->unk81BC[multiplayerId]->callback = sub_802CB7C;
    StartSpriteAnim(arg0->unk81BC[multiplayerId], 1);
}

static void sub_802CB7C(struct Sprite *sprite)
{
    switch (sprite->data[0])
    {
    case 0:
        if (sprite->animEnded)
        {
            sprite->invisible = 1;
            sprite->callback = SpriteCallbackDummy;
        }
        break;
    case 1:
        sprite->pos1.y--;
        sprite->data[1]++;
        if (sprite->pos1.y <= 72)
        {
            sprite->pos1.y = 72;
            sprite->data[0]++;
        }
        break;
    case 2:
        if (++sprite->data[1] >= 48)
        {
            sprite->invisible = 1;
            sprite->callback = SpriteCallbackDummy;
        }
        break;
    }
}

static void sub_802CBF0(struct PokemonJump2 *arg0, int multiplayerId)
{
    arg0->unk81A8[multiplayerId]->callback = sub_802CC40;
    arg0->unk81A8[multiplayerId]->pos2.y = 0;
    sub_802C9BC(arg0->unk81A8[multiplayerId]);
}

static bool32 sub_802CC18(struct PokemonJump2 *arg0, int multiplayerId)
{
    return arg0->unk81A8[multiplayerId]->callback == sub_802CC40;
}

static void sub_802CC40(struct Sprite *sprite)
{
    if (++sprite->data[1] > 1)
    {
        if (++sprite->data[2] & 1)
            sprite->pos2.y = 2;
        else
            sprite->pos2.y = -2;

        sprite->data[1] = 0;
    }

    if (sprite->data[2] > 12)
    {
        sprite->pos2.y = 0;
        sprite->callback = SpriteCallbackDummy;
    }
}

static void sub_802CC88(struct PokemonJump2 *arg0, int multiplayerId)
{
    sub_802C9BC(arg0->unk81A8[multiplayerId]);
    arg0->unk81A8[multiplayerId]->callback = sub_802CD08;
}

static void sub_802CCB0(struct PokemonJump2 *arg0)
{
    int i;
    u16 numPlayers = sub_802C8AC();
    for (i = 0; i < numPlayers; i++)
    {
        if (arg0->unk81A8[i]->callback == sub_802CD08)
        {
            arg0->unk81A8[i]->invisible = 0;
            arg0->unk81A8[i]->callback = SpriteCallbackDummy;
            arg0->unk81A8[i]->subpriority = 10;
        }
    }
}

static void sub_802CD08(struct Sprite *sprite)
{
    if (++sprite->data[0] > 3)
    {
        sprite->data[0] = 0;
        sprite->invisible ^= 1;
    }
}

static void sub_802CD3C(struct PokemonJump2 *arg0)
{
    int i;
    u16 numPlayers = sub_802C8AC();
    for (i = 0; i < numPlayers; i++)
        arg0->unk81A8[i]->subpriority = arg0->unk81FC[i];
}

static void sub_802CD70(struct PokemonJump2 *arg0, int multiplayerId)
{
    sub_802C9BC(arg0->unk81A8[multiplayerId]);
    arg0->unk81A8[multiplayerId]->callback = sub_802CDD4;
}

static bool32 sub_802CD98(struct PokemonJump2 *arg0)
{
    int i;
    u16 numPlayers = sub_802C8AC();
    for (i = 0; i < numPlayers; i++)
    {
        if (arg0->unk81A8[i]->callback == sub_802CDD4)
            return TRUE;
    }

    return FALSE;
}

static void sub_802CDD4(struct Sprite *sprite)
{
    switch (sprite->data[0])
    {
    case 0:
        PlaySE(SE_JITE_PYOKO);
        sprite->data[1] = 0;
        sprite->data[0]++;
        // fall through
    case 1:
        sprite->data[1] += 4;
        if (sprite->data[1] > 0x7F)
            sprite->data[1] = 0;

        sprite->pos2.y = -(gSineTable[sprite->data[1]] >> 3);
        if (sprite->data[1] == 0)
        {
            if (++sprite->data[2] < 2)
                sprite->data[0] = 0;
            else
                sprite->callback = SpriteCallbackDummy;
        }
        break;
    }
}

static void sub_802CE48(struct PokemonJump2 *arg0, s16 x, s16 y, u8 multiplayerId)
{
    u8 spriteId = CreateSprite(&gUnknown_082FC00C, x, y, 1);
    if (spriteId != MAX_SPRITES)
    {
        gSprites[spriteId].invisible = 1;
        arg0->unk81BC[multiplayerId] = &gSprites[spriteId];
    }
}

static void sub_802CE9C(struct PokemonJump2 *arg0)
{
    int i;
    int count;
    u8 spriteId;

    count = 0;
    for (i = 0; i < 4; i++)
    {
        spriteId = CreateSprite(gUnknown_082FBEB8[i], gUnknown_082FBEA8[count], gUnknown_082FBE58[i][0], 2);
        arg0->unk81D0[count] = &gSprites[spriteId];
        count++;
    }

    for (i = 3; i >= 0; i--)
    {
        spriteId = CreateSprite(gUnknown_082FBEB8[i], gUnknown_082FBEA8[count], gUnknown_082FBE58[i][0], 2);
        arg0->unk81D0[count] = &gSprites[spriteId];
        arg0->unk81D0[count]->hFlip = 1;
        count++;
    }
}

static void sub_802CF50(struct PokemonJump2 *arg0, int arg1)
{
    int i, count, palNum;
    int priority;

    if (arg1 > 5)
    {
        arg1 = 10 - arg1;
        priority = 3;
        palNum = arg0->unkF;
    }
    else
    {
        priority = 2;
        palNum = arg0->unkE;
    }

    count = 0;
    for (i = 0; i < 4; i++)
    {
        arg0->unk81D0[count]->pos1.y = gUnknown_082FBE58[i][arg1];
        arg0->unk81D0[count]->oam.priority = priority;
        arg0->unk81D0[count]->oam.paletteNum = palNum;
        StartSpriteAnim(arg0->unk81D0[count], arg1);
        count++;
    }

    for (i = 3; i >= 0; i--)
    {
        arg0->unk81D0[count]->pos1.y = gUnknown_082FBE58[i][arg1];
        arg0->unk81D0[count]->oam.priority = priority;
        arg0->unk81D0[count]->oam.paletteNum = palNum;
        StartSpriteAnim(arg0->unk81D0[count], arg1);
        count++;
    }
}

static void sub_802D044(struct PokemonJump2 *arg0)
{
    sub_802EB24(9, 7, 120, 80, 0);
    sub_802CD3C(arg0);
}

static bool32 sub_802D068(void)
{
    return sub_802EB84();
}

static void sub_802D074(struct PokemonJump2 *arg0)
{
    u8 taskId;

    gUnknown_02022D00 = arg0;
    sub_802D0BC(gUnknown_02022D00);
    taskId = CreateTask(sub_802D12C, 3);
    gUnknown_02022D00->unk6 = taskId;
    SetWordTaskArg(gUnknown_02022D00->unk6, 2, (u32) gUnknown_02022D00);
    sub_802D108(sub_802D150);
}

static void sub_802D0AC(void)
{
    FreeAllWindowBuffers();
    sub_8034CC8();
}

static void sub_802D0BC(struct PokemonJump2 *arg0)
{
    arg0->unk4 = 0;
    arg0->unk0 = 0;
    arg0->unk12 = 0xFF;
}

// Gfx
static const u16 gPkmnJumpPal3[] = INCBIN_U16("graphics/link_games/pkmnjump_pal3.gbapal");

static const u16 gPkmnJumpBgPal[] = INCBIN_U16("graphics/link_games/pkmnjump_bg.gbapal");
static const u32 gPkmnJumpBgGfx[] = INCBIN_U32("graphics/link_games/pkmnjump_bg.4bpp.lz");
static const u32 gPkmnJumpBgTilemap[] = INCBIN_U32("graphics/link_games/pkmnjump_bg.bin.lz");

static const u16 gPkmnJumpVenusaurPal[] = INCBIN_U16("graphics/link_games/pkmnjump_venusaur.gbapal");
static const u32 gPkmnJumpVenusaurGfx[] = INCBIN_U32("graphics/link_games/pkmnjump_venusaur.4bpp.lz");
static const u32 gPkmnJumpVenusaurTilemap[] = INCBIN_U32("graphics/link_games/pkmnjump_venusaur.bin.lz");

static const u16 gPkmnJumpResultsPal[] = INCBIN_U16("graphics/link_games/pkmnjump_results.gbapal");
static const u32 gPkmnJumpResultsGfx[] = INCBIN_U32("graphics/link_games/pkmnjump_results.4bpp.lz");
static const u32 gPkmnJumpResultsTilemap[] = INCBIN_U32("graphics/link_games/pkmnjump_results.bin.lz");

static const struct BgTemplate gUnknown_082FE164[] =
{
    {
        .bg = 0,
        .charBaseIndex = 0,
        .mapBaseIndex = 27,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0
    },
    {
        .bg = 2,
        .charBaseIndex = 1,
        .mapBaseIndex = 30,
        .screenSize = 2,
        .paletteMode = 0,
        .priority = 2,
        .baseTile = 0
    },
    {
        .bg = 1,
        .charBaseIndex = 2,
        .mapBaseIndex = 12,
        .screenSize = 3,
        .paletteMode = 0,
        .priority = 1,
        .baseTile = 0
    },
    {
        .bg = 3,
        .charBaseIndex = 3,
        .mapBaseIndex = 29,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 3,
        .baseTile = 0
    },
};

static const struct WindowTemplate gUnknown_082FE174[] =
{
    {
        .bg = 0,
        .tilemapLeft = 19,
        .tilemapTop = 0,
        .width = 6,
        .height = 2,
        .paletteNum = 2,
        .baseBlock = 0x13,
    },
    {
        .bg = 0,
        .tilemapLeft = 8,
        .tilemapTop = 0,
        .width = 6,
        .height = 2,
        .paletteNum = 2,
        .baseBlock = 0x1F,
    },
    DUMMY_WIN_TEMPLATE,
};

struct
{
    int id;
    void (*func)(void);
} static const gUnknown_082FE18C[] =
{
    {0x00, sub_802D150},
    {0x01, sub_802D2E4},
    {0x02, sub_802D350},
    {0x03, sub_802D3BC},
    {0x04, sub_802D448},
    {0x05, sub_802D4F4},
    {0x06, sub_802D598},
    {0x07, sub_802D5E4},
    {0x09, sub_802D72C},
    {0x08, sub_802D688},
};

static void sub_802D0C8(int arg0)
{
    int i;

    for (i = 0; i < ARRAY_COUNT(gUnknown_082FE18C); i++)
    {
        if (gUnknown_082FE18C[i].id == arg0)
            sub_802D108(gUnknown_082FE18C[i].func);
    }
}

static bool32 sub_802D0F0(void)
{
    return (gUnknown_02022D00->unk0 != 1);
}

static void sub_802D108(void (*func)(void))
{
    SetWordTaskArg(gUnknown_02022D00->unk6, 0, (u32) func);
    gUnknown_02022D00->unk4 = 0;
    gUnknown_02022D00->unk0 = 0;
}

static void sub_802D12C(u8 taskId)
{
    if (!gUnknown_02022D00->unk0)
    {
        void (*func)(void) = (void *)(GetWordTaskArg(taskId, 0));

        func();
    }
}

static void sub_802D150(void)
{
    switch (gUnknown_02022D00->unk4)
    {
    case 0:
        ResetBgsAndClearDma3BusyFlags(0);
        InitBgsFromTemplates(0, gUnknown_082FE164, ARRAY_COUNT(gUnknown_082FE164));
        InitWindows(gUnknown_082FE174);
        reset_temp_tile_data_buffers();
        sub_802C974(gUnknown_02022D00);
        sub_802DD08();
        LoadPalette(gPkmnJumpBgPal, 0, 0x20);
        decompress_and_copy_tile_data_to_vram(3, gPkmnJumpBgGfx, 0, 0, 0);
        decompress_and_copy_tile_data_to_vram(3, gPkmnJumpBgTilemap, 0, 0, 1);
        LoadPalette(gPkmnJumpVenusaurPal, 0x30, 0x20);
        decompress_and_copy_tile_data_to_vram(2, gPkmnJumpVenusaurGfx, 0, 0, 0);
        decompress_and_copy_tile_data_to_vram(2, gPkmnJumpVenusaurTilemap, 0, 0, 1);
        LoadPalette(gPkmnJumpResultsPal, 0x10, 0x20);
        decompress_and_copy_tile_data_to_vram(1, gPkmnJumpResultsGfx, 0, 0, 0);
        decompress_and_copy_tile_data_to_vram(1, gPkmnJumpResultsTilemap, 0, 0, 1);
        LoadPalette(gPkmnJumpPal3, 0x20, 0x20);
        SetBgTilemapBuffer(0, gUnknown_02022D00->tilemapBuffer);
        FillBgTilemapBufferRect_Palette0(0, 0, 0, 0, 0x20, 0x20);
        sub_802DB8C();
        sub_802DD64(0);
        sub_8098C6C(0, 1, 0xE0);
        CopyBgTilemapBufferToVram(0);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(1);
        ResetBgPositions();
        gUnknown_02022D00->unk4++;
        break;
    case 1:
        if (!free_temp_tile_data_buffers_if_possible())
        {
            sub_802DBF8();
            sub_802CE9C(gUnknown_02022D00);
            sub_802CF50(gUnknown_02022D00, 6);
            ShowBg(3);
            ShowBg(0);
            ShowBg(2);
            HideBg(1);
            gUnknown_02022D00->unk4++;
        }
        break;
    case 2:
        gUnknown_02022D00->unk0 = 1;
        break;
    }
}

static void sub_802D2E4(void)
{
    switch (gUnknown_02022D00->unk4)
    {
    case 0:
        sub_802DE1C();
        gUnknown_02022D00->unk4++;
        break;
    case 1:
        if (!IsDma3ManagerBusyWithBgCopy())
        {
            sub_802DF70(FALSE);
            gUnknown_02022D00->unk4++;
        }
        break;
    case 2:
        if (!IsDma3ManagerBusyWithBgCopy())
        {
            sub_802DFD4();
            gUnknown_02022D00->unk4++;
        }
        break;
    case 3:
        if (!IsDma3ManagerBusyWithBgCopy())
            gUnknown_02022D00->unk0 = 1;
        break;
    }
}

static void sub_802D350(void)
{
    switch (gUnknown_02022D00->unk4)
    {
    case 0:
        sub_802DE1C();
        gUnknown_02022D00->unk4++;
        break;
    case 1:
        if (!IsDma3ManagerBusyWithBgCopy())
        {
            sub_802DF70(TRUE);
            gUnknown_02022D00->unk4++;
        }
        break;
    case 2:
        if (!IsDma3ManagerBusyWithBgCopy())
        {
            sub_802DFD4();
            gUnknown_02022D00->unk4++;
        }
        break;
    case 3:
        if (!IsDma3ManagerBusyWithBgCopy())
            gUnknown_02022D00->unk0 = 1;
        break;
    }
}

static void sub_802D3BC(void)
{
    int i, numPlayers;

    numPlayers = sub_802C8AC();
    switch (gUnknown_02022D00->unk4)
    {
    case 0:
        for (i = 0; i < numPlayers; i++)
            ClearWindowTilemap(gUnknown_02022D00->unk1C[i]);

        CopyBgTilemapBufferToVram(0);
        gUnknown_02022D00->unk4++;
        break;
    case 1:
        if (!IsDma3ManagerBusyWithBgCopy())
        {
            for (i = 0; i < numPlayers; i++)
                RemoveWindow(gUnknown_02022D00->unk1C[i]);

            gUnknown_02022D00->unk0 = 1;
        }
        break;
    }
}

static void sub_802D448(void)
{
    switch (gUnknown_02022D00->unk4)
    {
    case 0:
        gUnknown_02022D00->unk12 = sub_802DA9C(1, 8, 20, 2);
        AddTextPrinterParameterized(gUnknown_02022D00->unk12, 1, gText_WantToPlayAgain2, 0, 1, TEXT_SPEED_FF, NULL);
        CopyWindowToVram(gUnknown_02022D00->unk12, 2);
        gUnknown_02022D00->unk4++;
        break;
    case 1:
        if (!IsDma3ManagerBusyWithBgCopy())
        {
            PutWindowTilemap(gUnknown_02022D00->unk12);
            DrawTextBorderOuter(gUnknown_02022D00->unk12, 1, 14);
            sub_802DB18(23, 7, 0);
            CopyBgTilemapBufferToVram(0);
            gUnknown_02022D00->unk4++;
        }
        break;
    case 2:
        if (!IsDma3ManagerBusyWithBgCopy())
            gUnknown_02022D00->unk0 = 1;
        break;
    }
}

static void sub_802D4F4(void)
{
    switch (gUnknown_02022D00->unk4)
    {
    case 0:
        gUnknown_02022D00->unk12 = sub_802DA9C(2, 7, 26, 4);
        AddTextPrinterParameterized(gUnknown_02022D00->unk12, 1, gText_SavingDontTurnOffPower, 0, 1, TEXT_SPEED_FF, NULL);
        CopyWindowToVram(gUnknown_02022D00->unk12, 2);
        gUnknown_02022D00->unk4++;
        break;
    case 1:
        if (!IsDma3ManagerBusyWithBgCopy())
        {
            PutWindowTilemap(gUnknown_02022D00->unk12);
            DrawTextBorderOuter(gUnknown_02022D00->unk12, 1, 14);
            CopyBgTilemapBufferToVram(0);
            gUnknown_02022D00->unk4++;
        }
        break;
    case 2:
        if (!IsDma3ManagerBusyWithBgCopy())
            gUnknown_02022D00->unk0 = 1;
        break;
    }
}

static void sub_802D598(void)
{
    switch (gUnknown_02022D00->unk4)
    {
    case 0:
        sub_802DA14();
        sub_8198C78();
        CopyBgTilemapBufferToVram(0);
        gUnknown_02022D00->unk4++;
        break;
    case 1:
        if (!sub_802DA44() && !IsDma3ManagerBusyWithBgCopy())
            gUnknown_02022D00->unk0 = 1;
        break;
    }
}

static void sub_802D5E4(void)
{
    switch (gUnknown_02022D00->unk4)
    {
    case 0:
        gUnknown_02022D00->unk12 = sub_802DA9C(2, 8, 22, 4);
        AddTextPrinterParameterized(gUnknown_02022D00->unk12, 1, gText_SomeoneDroppedOut2, 0, 1, TEXT_SPEED_FF, NULL);
        CopyWindowToVram(gUnknown_02022D00->unk12, 2);
        gUnknown_02022D00->unk4++;
        break;
    case 1:
        if (!IsDma3ManagerBusyWithBgCopy())
        {
            PutWindowTilemap(gUnknown_02022D00->unk12);
            DrawTextBorderOuter(gUnknown_02022D00->unk12, 1, 14);
            CopyBgTilemapBufferToVram(0);
            gUnknown_02022D00->unk4++;
        }
        break;
    case 2:
        if (!IsDma3ManagerBusyWithBgCopy())
            gUnknown_02022D00->unk0 = 1;
        break;
    }
}

static void sub_802D688(void)
{
    switch (gUnknown_02022D00->unk4)
    {
    case 0:
        gUnknown_02022D00->unk12 = sub_802DA9C(7, 10, 16, 2);
        AddTextPrinterParameterized(gUnknown_02022D00->unk12, 1, gText_CommunicationStandby4, 0, 1, TEXT_SPEED_FF, NULL);
        CopyWindowToVram(gUnknown_02022D00->unk12, 2);
        gUnknown_02022D00->unk4++;
        break;
    case 1:
        if (!IsDma3ManagerBusyWithBgCopy())
        {
            PutWindowTilemap(gUnknown_02022D00->unk12);
            DrawTextBorderOuter(gUnknown_02022D00->unk12, 1, 14);
            CopyBgTilemapBufferToVram(0);
            gUnknown_02022D00->unk4++;
        }
        break;
    case 2:
        if (!IsDma3ManagerBusyWithBgCopy())
            gUnknown_02022D00->unk0 = 1;
        break;
    }
}

static void sub_802D72C(void)
{
    switch (gUnknown_02022D00->unk4)
    {
    case 0:
        sub_802D044(gUnknown_02022D00);
        gUnknown_02022D00->unk4++;
        break;
    case 1:
        if (!sub_802D068())
            gUnknown_02022D00->unk0 = 1;
        break;
    }
}

static void sub_802D764(void)
{
    gUnknown_02022D00->unkA = 0;
    gUnknown_02022D00->unkB = 0;
    gUnknown_02022D00->unkC = 6;
    sub_802DC9C(gUnknown_02022D00->unkC);
}

static bool32 sub_802D788(void)
{
    switch (gUnknown_02022D00->unkA)
    {
    case 0:
        gUnknown_02022D00->unkB++;
        if (gUnknown_02022D00->unkB > 10)
        {
            gUnknown_02022D00->unkB = 0;
            gUnknown_02022D00->unkC++;
            if (gUnknown_02022D00->unkC >= 10)
            {
                gUnknown_02022D00->unkC = 0;
                gUnknown_02022D00->unkA++;
            }
        }
        sub_802DC9C(gUnknown_02022D00->unkC);
        if (gUnknown_02022D00->unkC != 7)
            break;
    case 1:
        return FALSE;
    }

    return TRUE;
}

static void sub_802D7E8(u16 itemId, u16 quantity)
{
    CopyItemNameHandlePlural(itemId, gUnknown_02022D00->txtBuff[0], quantity);
    ConvertIntToDecimalStringN(gUnknown_02022D00->txtBuff[1], quantity, STR_CONV_MODE_LEFT_ALIGN, 1);
    DynamicPlaceholderTextUtil_Reset();
    DynamicPlaceholderTextUtil_SetPlaceholderPtr(0, gUnknown_02022D00->txtBuff[0]);
    DynamicPlaceholderTextUtil_SetPlaceholderPtr(1, gUnknown_02022D00->txtBuff[1]);
    DynamicPlaceholderTextUtil_ExpandPlaceholders(gUnknown_02022D00->strBuff, gText_AwesomeWonF701F700);
    gUnknown_02022D00->unk12 = sub_802DA9C(4, 8, 22, 4);
    AddTextPrinterParameterized(gUnknown_02022D00->unk12, 1, gUnknown_02022D00->strBuff, 0, 1, TEXT_SPEED_FF, NULL);
    CopyWindowToVram(gUnknown_02022D00->unk12, 2);
    gUnknown_02022D00->unk14 = MUS_FANFA1;
    gUnknown_02022D00->unkD = 0;
}

static void sub_802D884(u16 itemId)
{
    CopyItemName(itemId, gUnknown_02022D00->txtBuff[0]);
    DynamicPlaceholderTextUtil_Reset();
    DynamicPlaceholderTextUtil_SetPlaceholderPtr(0, gUnknown_02022D00->txtBuff[0]);
    DynamicPlaceholderTextUtil_ExpandPlaceholders(gUnknown_02022D00->strBuff, gText_FilledStorageSpace2);
    gUnknown_02022D00->unk12 = sub_802DA9C(4, 8, 22, 4);
    AddTextPrinterParameterized(gUnknown_02022D00->unk12, 1, gUnknown_02022D00->strBuff, 0, 1, TEXT_SPEED_FF, NULL);
    CopyWindowToVram(gUnknown_02022D00->unk12, 2);
    gUnknown_02022D00->unk14 = 0;
    gUnknown_02022D00->unkD = 0;
}

static void sub_802D8FC(u16 itemId)
{
    CopyItemName(itemId, gUnknown_02022D00->txtBuff[0]);
    DynamicPlaceholderTextUtil_Reset();
    DynamicPlaceholderTextUtil_SetPlaceholderPtr(0, gUnknown_02022D00->txtBuff[0]);
    DynamicPlaceholderTextUtil_ExpandPlaceholders(gUnknown_02022D00->strBuff, gText_CantHoldMore);
    gUnknown_02022D00->unk12 = sub_802DA9C(4, 9, 22, 2);
    AddTextPrinterParameterized(gUnknown_02022D00->unk12, 1, gUnknown_02022D00->strBuff, 0, 1, TEXT_SPEED_FF, NULL);
    CopyWindowToVram(gUnknown_02022D00->unk12, 2);
    gUnknown_02022D00->unk14 = 0;
    gUnknown_02022D00->unkD = 0;
}

static bool32 sub_802D974(void)
{
    switch (gUnknown_02022D00->unkD)
    {
    case 0:
        if (!IsDma3ManagerBusyWithBgCopy())
        {
            PutWindowTilemap(gUnknown_02022D00->unk12);
            DrawTextBorderOuter(gUnknown_02022D00->unk12, 1, 14);
            CopyBgTilemapBufferToVram(0);
            gUnknown_02022D00->unkD++;
        }
        break;
    case 1:
        if (IsDma3ManagerBusyWithBgCopy())
            break;
        if (gUnknown_02022D00->unk14 == 0)
        {
            gUnknown_02022D00->unkD += 2;
            return FALSE;
        }
        PlayFanfare(gUnknown_02022D00->unk14);
        gUnknown_02022D00->unkD++;
    case 2:
        if (!IsFanfareTaskInactive())
            break;
        gUnknown_02022D00->unkD++;
    case 3:
        return FALSE;
    }

    return TRUE;
}

static void sub_802DA14(void)
{
    if (gUnknown_02022D00->unk12 != 0xFF)
    {
        rbox_fill_rectangle(gUnknown_02022D00->unk12);
        CopyWindowToVram(gUnknown_02022D00->unk12, 1);
        gUnknown_02022D00->unkD = 0;
    }
}

// Can't match this without the ugly GOTO, oh well.
static bool32 sub_802DA44(void)
{
    if (gUnknown_02022D00->unk12 == 0xFF)
    {
    RET_FALSE:
        return FALSE;
    }

    if (gUnknown_02022D00->unkD == 0)
    {
        if (!IsDma3ManagerBusyWithBgCopy())
        {
            RemoveWindow(gUnknown_02022D00->unk12);
            gUnknown_02022D00->unk12 = 0xFF;
            gUnknown_02022D00->unkD++;
            goto RET_FALSE;
        }
    }
    else if (gUnknown_02022D00->unkD == 1)
        goto RET_FALSE;

    return TRUE;
}

static s8 sub_802DA8C(void)
{
    return Menu_ProcessInputNoWrapClearOnChoose();
}

static u32 sub_802DA9C(u32 left, u32 top, u32 width, u32 height)
{
    u32 windowId;
    struct WindowTemplate window;

    window.bg = 0;
    window.tilemapLeft = left;
    window.tilemapTop = top;
    window.width = width;
    window.height = height;
    window.paletteNum = 0xF;
    window.baseBlock = 0x43;

    windowId = AddWindow(&window);
    FillWindowPixelBuffer(windowId, 0x11);
    return windowId;
}

static void sub_802DB18(u16 left, u16 top, u8 cursorPos)
{
    struct WindowTemplate window;
    u8 a = cursorPos;

    window.bg = 0;
    window.tilemapLeft = left;
    window.tilemapTop = top;
    window.width = 6;
    window.height = 4;
    window.paletteNum = 2;
    window.baseBlock = 0x2B;

    CreateYesNoMenu(&window, 1, 0xD, a);
}

static void sub_802DB8C(void)
{
    u8 color[] = {0, 2, 3};

    PutWindowTilemap(0);
    PutWindowTilemap(1);
    FillWindowPixelBuffer(0, 0);
    FillWindowPixelBuffer(1, 0);
    AddTextPrinterParameterized3(0, 0, 0, 1, color, 0, gText_SpacePoints2);
    AddTextPrinterParameterized3(1, 0, 0, 1, color, 0, gText_SpaceTimes3);
}

static const u8 gUnknown_082FE1DF[] = {2, 2, 0, 0, 1, 1, 1, 0, 0, 2, 0, 0, 0};

static const struct CompressedSpriteSheet gUnknown_082FE1EC = {gUnknown_082FF1F8, 0, 0x320};
static const struct SpritePalette gUnknown_082FE1F4 = {gUnknown_082FF1D8, 0x320};

static const u16 gUnknown_082FE1FC[] = {0x06, 0x08, 0x10, 0x08};
static const u16 gUnknown_082FE204[] = {0x06, 0x08, 0x0b, 0x06, 0x10, 0x08};
static const u16 gUnknown_082FE210[] = {0x02, 0x06, 0x06, 0x08, 0x10, 0x08, 0x14, 0x06};
static const u16 gUnknown_082FE220[] = {0x02, 0x06, 0x06, 0x08, 0x0b, 0x06, 0x10, 0x08, 0x14, 0x06};

static const u16 *const gUnknown_082FE234[] =
{
    gUnknown_082FE1FC,
    gUnknown_082FE204,
    gUnknown_082FE210,
    gUnknown_082FE220,
};

static const s16 gUnknown_082FE244[] = {0x0058, 0x0098};
static const s16 gUnknown_082FE248[] = {0x0058, 0x0078, 0x0098};
static const s16 gUnknown_082FE24E[] = {0x0038, 0x0058, 0x0098, 0x00b8};
static const s16 gUnknown_082FE256[] = {0x0038, 0x0058, 0x0078, 0x0098, 0x00b8};

static const s16 *const gUnknown_082FE260[] =
{
    gUnknown_082FE244,
    gUnknown_082FE248,
    gUnknown_082FE24E,
    gUnknown_082FE256,
};

static void sub_802DBF8(void)
{
    int i, y, playersCount = sub_802C8AC();
    const s16 *xCoords = gUnknown_082FE260[playersCount - 2];

    for (i = 0; i < playersCount; i++)
    {
        struct PokemonJump1_MonInfo *info = sub_802C8C8(i);

        y = gMonFrontPicCoords[info->species].y_offset;
        sub_802C9D4(gUnknown_02022D00, info, *xCoords, y + 112, i);
        sub_802CE48(gUnknown_02022D00, *xCoords, 112, i);
        xCoords++;
    }
}

static void sub_802DC80(u32 id, s16 y)
{
    gUnknown_02022D00->unk81A8[id]->pos2.y = y;
}

static void sub_802DC9C(int id)
{
    sub_802CF50(gUnknown_02022D00, id);
    ChangeBgY(2, (gUnknown_082FE1DF[id] * 5) << 0xD, 0);
}

static int sub_802DCCC(u8 flags)
{
    int i, count;

    for (i = 0, count = 0; i < 5; i++)
    {
        if (flags & 1)
        {
            sub_802CB14(gUnknown_02022D00, i);
            count++;
        }
        flags >>= 1;
    }

    sub_802E00C(count - 2);
    return count;
}

static void sub_802DD08(void)
{
    struct UnkStruct3 unkStruct;
    struct UnkStruct3 *ptr = &unkStruct; // This temp variable is needed to match, don't ask me why.

    ptr->shape = 0;
    ptr->size = 0;
    ptr->field_0_0 = 0;
    ptr->priority = 1;
    ptr->field_1 = 5;
    ptr->xDelta = 8;
    ptr->x = 108;
    ptr->y = 6;
    ptr->spriteSheet = (void*) &gUnknown_082FE1EC;
    ptr->spritePal = &gUnknown_082FE1F4;

    sub_8034C54(2);
    sub_8034D14(0, 0, ptr);

    unkStruct.field_1 = 4;
    unkStruct.x = 30;
    unkStruct.y = 6;
    sub_8034D14(1, 0, &unkStruct);
}

static void sub_802DD64(int arg0)
{
    sub_8035044(0, arg0);
}

static void sub_802DD74(u16 arg0)
{
    sub_8035044(1, arg0);
}

static void sub_802DD88(u8 multiplayerId)
{
    sub_802CBF0(gUnknown_02022D00, multiplayerId);
}

static void sub_802DDA0(u8 multiplayerId)
{
    sub_802CC88(gUnknown_02022D00, multiplayerId);
}

static int sub_802DDB8(int multiplayerId)
{
    return sub_802CC18(gUnknown_02022D00, multiplayerId);
}

static void sub_802DDCC(void)
{
    sub_802CCB0(gUnknown_02022D00);
}

static void sub_802DDE0(void)
{
    sub_802CD3C(gUnknown_02022D00);
}

static void sub_802DDF4(int multiplayerId)
{
    sub_802CD70(gUnknown_02022D00, multiplayerId);
}

static int sub_802DE08(void)
{
    return sub_802CD98(gUnknown_02022D00);
}

static void sub_802DE1C(void)
{
    struct WindowTemplate window;
    int i, playersCount = sub_802C8AC();
    const u16 *winCoords = gUnknown_082FE234[playersCount - 2];

    window.bg = 0;
    window.width = 8;
    window.height = 2;
    window.paletteNum = 2;
    window.baseBlock = 0x2B;

    for (i = 0; i < playersCount; i++)
    {
        window.tilemapLeft = winCoords[0];
        window.tilemapTop = winCoords[1];
        gUnknown_02022D00->unk1C[i] = AddWindow(&window);
        ClearWindowTilemap(gUnknown_02022D00->unk1C[i]);
        window.baseBlock += 0x10;
        winCoords += 2;
    }

    CopyBgTilemapBufferToVram(0);
}

static void sub_802DED8(int multiplayerId, u8 clr1, u8 clr2, u8 clr3)
{
    u32 x;
    u8 colors[3] = {clr1, clr2, clr3};

    FillWindowPixelBuffer(gUnknown_02022D00->unk1C[multiplayerId], 0);
    x = 64 - GetStringWidth(1, sub_802C8E8(multiplayerId), -1);
    x /= 2;
    AddTextPrinterParameterized3(gUnknown_02022D00->unk1C[multiplayerId], 1, x, 1, colors, -1, sub_802C8E8(multiplayerId));
    CopyWindowToVram(gUnknown_02022D00->unk1C[multiplayerId], 2);
}

static void sub_802DF70(bool32 arg0)
{
    int i, var, playersCount = sub_802C8AC();

    if (!arg0)
    {
        for (i = 0; i < playersCount; i++)
            sub_802DED8(i, 0, 2, 3);
    }
    else
    {
        var = sub_802C8BC();
        for (i = 0; i < playersCount; i++)
        {
            if (var != i)
                sub_802DED8(i, 0, 2, 3);
            else
                sub_802DED8(i, 0, 4, 5);
        }
    }
}

static void sub_802DFD4(void)
{
    int i, playersCount = sub_802C8AC();

    for (i = 0; i < playersCount; i++)
        PutWindowTilemap(gUnknown_02022D00->unk1C[i]);
    CopyBgTilemapBufferToVram(0);
}

static void sub_802E00C(u8 arg0)
{
    gUnknown_02022D00->unk18 = 0;
    ChangeBgX(1, (arg0 / 2) << 16, 0);
    ChangeBgY(1, (((arg0 % 2) << 8) - 40) << 8, 0);
    ShowBg(1);
    CreateTask(sub_802E090, 4);
}

static bool32 sub_802E058(void)
{
    if (gUnknown_02022D00->unk18 >= 32)
    {
        return FALSE;
    }
    else
    {
        ChangeBgY(1, 128, 1);
        if (++gUnknown_02022D00->unk18 >= 32)
            HideBg(1);
        return TRUE;
    }
}

static void sub_802E090(u8 taskId)
{
    if (!sub_802E058())
        DestroyTask(taskId);
}

struct MonInfoPacket
{
    u8 id; // packet id
    u16 species;
    u32 personality;
    u32 otId;
};

static void sub_802E0AC(struct PokemonJump1_MonInfo *arg0)
{
    struct MonInfoPacket packet;
    packet.id = 1,
    packet.species = arg0->species,
    packet.otId = arg0->otId,
    packet.personality = arg0->personality,
    sub_800FE50(&packet);
}

static bool32 sub_802E0D0(int multiplayerId, struct PokemonJump1_MonInfo *arg0)
{
    struct MonInfoPacket packet;

    if ((gRecvCmds[multiplayerId][0] & 0xFF00) != 0x2F00)
        return FALSE;

    memcpy(&packet, &gRecvCmds[multiplayerId][1], sizeof(packet));
    if (packet.id == 1)
    {
        arg0->species = packet.species;
        arg0->otId = packet.otId;
        arg0->personality = packet.personality;
        return TRUE;
    }

    return FALSE;
}

struct UnkPacket2
{
    u8 id; // packet id
    u32 unk4;
    u32 unk8;
};

static void sub_802E120(u32 arg0)
{
    struct UnkPacket2 packet;
    packet.id = 2;
    packet.unk4 = arg0;
    sub_800FE50(&packet);
}

struct UnkPacket3
{
    u8 id; // packet id
    u8 unk1;
    u8 unk2;
    u8 unk3_0:5;
    u8 unk3_1:3;
    u16 unk4;
    u16 unk6;
    u32 unk8_0:15;
    u32 unk8_1:17;
};

static void sub_802E138(struct PokemonJump1_82E4 *arg0, struct PokemonJump1Sub *arg1)
{
    struct UnkPacket3 packet;
    packet.id = 3;
    packet.unk8_1 = arg1->unk8;
    packet.unk3_0 = arg1->unk1;
    packet.unk1 = arg1->unk0;
    packet.unk6 = arg1->unk2;
    packet.unk8_0 = arg1->unk4;
    packet.unk2 = arg0->unk10;
    packet.unk3_1 = arg0->unk14;
    packet.unk4 = arg0->unkE;
    sub_800FE50(&packet);
}

static bool32 sub_802E1BC(struct PokemonJump1_82E4 *arg0, struct PokemonJump1Sub *arg1)
{
    struct UnkPacket3 packet;

    if ((gRecvCmds[0][0] & 0xFF00) != 0x2F00)
        return FALSE;

    memcpy(&packet, &gRecvCmds[0][1], sizeof(packet));
    if (packet.id != 3)
        return FALSE;

    arg1->unk8 = packet.unk8_1;
    arg1->unk1 = packet.unk3_0;
    arg1->unk0 = packet.unk1;
    arg1->unk2 = packet.unk6;
    arg1->unk4 = packet.unk8_0;
    arg0->unk10 = packet.unk2;
    arg0->unk14 = packet.unk3_1;
    arg0->unkE = packet.unk4;
    return TRUE;
}

struct UnkPacket4
{
    u8 id; // packet id
    u8 unk1;
    u8 unk2;
    u8 unk3;
    u16 unk4;
    u8 unk6;
    u16 unk8;
};

static void sub_802E234(struct PokemonJump1_82E4 *arg0, u8 arg1, u16 arg2)
{
    struct UnkPacket4 packet;
    packet.id = 4;
    packet.unk1 = arg0->unk10;
    packet.unk2 = arg0->unk14;
    packet.unk3 = arg0->unk18;
    packet.unk4 = arg0->unkE;
    packet.unk6 = arg1;
    packet.unk8 = arg2;
    sub_800FE50(&packet);
}

static bool32 sub_802E264(struct PokemonJump1_82E4 *arg0, int multiplayerId, u8 *arg2, u16 *arg3)
{
    struct UnkPacket4 packet;

    if ((gRecvCmds[multiplayerId][0] & 0xFF00) != 0x2F00)
        return FALSE;

    memcpy(&packet, &gRecvCmds[multiplayerId][1], sizeof(packet));
    if (packet.id != 4)
        return FALSE;

    arg0->unk10 = packet.unk1;
    arg0->unk14 = packet.unk2;
    arg0->unk18 = packet.unk3;
    arg0->unkE = packet.unk4;
    *arg2 = packet.unk6;
    *arg3 = packet.unk8;
    return TRUE;
}

static bool32 sub_802E2D0(struct PokemonJump1_82E4 *arg0, int multiplayerId)
{
    struct UnkPacket4 packet;

    if ((gRecvCmds[multiplayerId][0] & 0xFF00) != 0x2F00)
        return FALSE;

    memcpy(&packet, &gRecvCmds[multiplayerId][1], sizeof(packet));
    if (packet.id != 4)
        return FALSE;

    arg0->unk10 = packet.unk1;
    arg0->unk14 = packet.unk2;
    arg0->unk18 = packet.unk3;
    arg0->unkE = packet.unk4;
    return TRUE;
}

static struct PokemonJumpResults *sub_802E32C(void)
{
    return &gSaveBlock2Ptr->pokeJump;
}

void ResetPokeJumpResults(void)
{
    struct PokemonJumpResults *pokeJump = sub_802E32C();
    pokeJump->jumpsInRow = 0;
    pokeJump->bestJumpScore = 0;
    pokeJump->excellentsInRow = 0;
    pokeJump->field6 = 0;
    pokeJump->field8 = 0;
    pokeJump->field2 = 0;
}

static bool32 sub_802E354(u32 jumpScore, u16 jumpsInRow, u16 excellentsInRow)
{
    struct PokemonJumpResults *pokeJump = sub_802E32C();
    bool32 ret = FALSE;

    if (pokeJump->bestJumpScore < jumpScore && jumpScore <= 99990)
        pokeJump->bestJumpScore = jumpScore, ret = TRUE;
    if (pokeJump->jumpsInRow < jumpsInRow && jumpsInRow <= 9999)
        pokeJump->jumpsInRow = jumpsInRow, ret = TRUE;
    if (pokeJump->excellentsInRow < excellentsInRow && excellentsInRow <= 9999)
        pokeJump->excellentsInRow = excellentsInRow, ret = TRUE;

    return ret;
}

static void sub_802E3A8(void)
{
    struct PokemonJumpResults *pokeJump = sub_802E32C();
    if (pokeJump->field6 < 9999)
        pokeJump->field6++;
}

void sub_802E3C4(void)
{
    u8 taskId = CreateTask(sub_802E3E4, 0);
    sub_802E3E4(taskId);
}

static const struct WindowTemplate gUnknown_082FE270 =
{
    .bg = 0,
    .tilemapLeft = 1,
    .tilemapTop = 1,
    .width = 28,
    .height = 9,
    .paletteNum = 15,
    .baseBlock = 0x1,
};

static const u8 *const gUnknown_082FE278[] = {gText_JumpsInARow, gText_BestScore2, gText_ExcellentsInARow};

static void sub_802E3E4(u8 taskId)
{
    struct WindowTemplate window;
    int i, width, widthCurr;
    s16 *data = gTasks[taskId].data;

    switch (data[0])
    {
    case 0:
        window = gUnknown_082FE270;
        width = GetStringWidth(1, gText_PkmnJumpRecords, 0);
        for (i = 0; i < ARRAY_COUNT(gUnknown_082FE278); i++)
        {
            widthCurr = GetStringWidth(1, gUnknown_082FE278[i], 0) + 38;
            if (widthCurr > width)
                width = widthCurr;
        }
        width = (width + 7) / 8;
        if (width & 1)
            width++;
        window.tilemapLeft = (30 - width) / 2;
        window.width = width;
        data[1] = AddWindow(&window);
        sub_802E500(data[1], width);
        CopyWindowToVram(data[1], 3);
        data[0]++;
        break;
    case 1:
        if (!IsDma3ManagerBusyWithBgCopy())
            data[0]++;
        break;
    case 2:
        if (gMain.newKeys & (A_BUTTON | B_BUTTON))
        {
            rbox_fill_rectangle(data[1]);
            CopyWindowToVram(data[1], 1);
            data[0]++;
        }
        break;
    case 3:
        if (!IsDma3ManagerBusyWithBgCopy())
        {
            RemoveWindow(data[1]);
            DestroyTask(taskId);
            EnableBothScriptContexts();
        }
        break;
    }
}

static void sub_802E500(u16 windowId, int width)
{
    int i, x;
    int results[3];
    struct PokemonJumpResults *pokeJump = sub_802E32C();
    results[0] = pokeJump->jumpsInRow;
    results[1] = pokeJump->bestJumpScore;
    results[2] = pokeJump->excellentsInRow;

    LoadUserWindowBorderGfx_(windowId, 0x21D, 0xD0);
    DrawTextBorderOuter(windowId, 0x21D, 0xD);
    FillWindowPixelBuffer(windowId, PIXEL_FILL(1));
    AddTextPrinterParameterized(windowId, 1, gText_PkmnJumpRecords, GetStringCenterAlignXOffset(1, gText_PkmnJumpRecords, width * 8), 1, TEXT_SPEED_FF, NULL);
    for (i = 0; i < ARRAY_COUNT(gUnknown_082FE278); i++)
    {
        AddTextPrinterParameterized(windowId, 1, gUnknown_082FE278[i], 0, 25 + (i * 16), TEXT_SPEED_FF, NULL);
        ConvertIntToDecimalStringN(gStringVar1, results[i], STR_CONV_MODE_LEFT_ALIGN, 5);
        TruncateToFirstWordOnly(gStringVar1);
        x = (width * 8) - GetStringWidth(1, gStringVar1, 0);
        AddTextPrinterParameterized(windowId, 1, gStringVar1, x, 25 + (i * 16), TEXT_SPEED_FF, NULL);
    }
    PutWindowTilemap(windowId);
}

static void TruncateToFirstWordOnly(u8 *str)
{
    for (;*str != EOS; str++)
    {
        if (*str == CHAR_SPACE)
        {
            *str = EOS;
            break;
        }
    }
}

static const u16 gPkmnJump321StartPal1[] = INCBIN_U16("graphics/link_games/pkmnjump_321start1.gbapal");
static const u32 gPkmnJump321StartGfx1[] = INCBIN_U32("graphics/link_games/pkmnjump_321start1.4bpp.lz");

static const struct CompressedSpriteSheet gUnknown_082FE6C8[] =
{
    {gPkmnJump321StartGfx1, 0xC00, 0x2000},
    {},
};

static const struct SpritePalette gUnknown_082FE6D8[] =
{
    {gPkmnJump321StartPal1, 0x2000},
    {},
};

static const union AnimCmd sSpriteAnim_82FE6E8[] =
{
    ANIMCMD_FRAME(0, 0),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_82FE6F0[] =
{
    ANIMCMD_FRAME(16, 0),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_82FE6F8[] =
{
    ANIMCMD_FRAME(32, 0),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_82FE700[] =
{
    ANIMCMD_FRAME(64, 0),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_82FE708[] =
{
    ANIMCMD_FRAME(48, 0),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_82FE710[] =
{
    ANIMCMD_FRAME(80, 0),
    ANIMCMD_END
};

static const union AnimCmd *const sSpriteAnimTable_82FE718[] =
{
    sSpriteAnim_82FE6E8,
    sSpriteAnim_82FE6F0,
    sSpriteAnim_82FE6F8,
    sSpriteAnim_82FE700,
    sSpriteAnim_82FE708,
    sSpriteAnim_82FE710
};

static const struct SpriteTemplate gUnknown_082FE730[] =
{
    {
        .tileTag = 0x2000,
        .paletteTag = 0x2000,
        .oam = &gUnknown_08524914,
        .anims = sSpriteAnimTable_82FE718,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy,
    },
};

static const TaskFunc gUnknown_082FE748[][4] =
{
    {
        sub_802E83C,
        sub_802E8C8,
        sub_802EA50,
        sub_802EAB0
    },
};

// There's only set of task functions.
static u32 sub_802E63C(u8 funcSetId, u8 taskPriority)
{
    u8 taskId = CreateTask(sub_802E6D0, taskPriority);
    struct Task *task = &gTasks[taskId];

    task->data[0] = 1;
    task->data[1] = funcSetId;
    gUnknown_082FE748[funcSetId][0](taskId);
    return taskId;
}

static bool32 sub_802E688(void)
{
    u8 taskId = FindTaskIdByFunc(sub_802E6D0);
    if (taskId == 0xFF)
        return FALSE;

    gTasks[taskId].data[0] = 2;
    return TRUE;
}

static bool32 sub_802E6BC(void)
{
    return FuncIsActiveTask(sub_802E6D0);
}

static void sub_802E6D0(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    switch (data[0])
    {
    case 2:
        gUnknown_082FE748[data[1]][2](taskId);
        data[0] = 3;
        break;
    case 3:
        gUnknown_082FE748[data[1]][3](taskId);
        break;
    case 4:
        gUnknown_082FE748[data[1]][1](taskId);
        DestroyTask(taskId);
        break;
    }
}

static void sub_802E75C(u8 taskId, s16 *data)
{
    u8 i;
    struct Sprite *sprite;

    LoadCompressedSpriteSheet(&gUnknown_082FE6C8[data[3]]);
    LoadSpritePalette(&gUnknown_082FE6D8[data[4]]);
    for (i = 0; i < data[8]; i++)
        data[13 + i] = CreateSprite(&gUnknown_082FE730[data[2]], data[9], data[10], data[7]);
    for (i = 0; i < data[8]; i++)
    {
        sprite = &gSprites[data[13 + i]];
        sprite->oam.priority = data[6];
        sprite->invisible = TRUE;
        sprite->data[1] = data[5];
        sprite->data[3] = taskId;
        sprite->data[4] = i;
        sprite->data[5] = data[13];
    }
}

static void sub_802E83C(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    data[2] = 0;
    data[3] = 0;
    data[4] = 0;
    data[5] = 60;
    data[6] = 0;
    data[7] = 0;
    data[8] = 3;
    data[9] = 120;
    data[10] = 88;
    sub_802E75C(taskId, data);

    StartSpriteAnim(&gSprites[data[14]], 4);
    gSprites[data[14]].pos2.x = -32;

    StartSpriteAnim(&gSprites[data[15]], 5);
    gSprites[data[15]].pos2.x = 32;
}

static void sub_802E8C8(u8 taskId)
{
    u8 i = 0;
    s16 *data = gTasks[taskId].data;

    for (i = 0; i < data[8]; i++)
        DestroySprite(&gSprites[data[13 + i]]);
    FreeSpriteTilesByTag(gUnknown_082FE6C8[data[3]].tag);
    FreeSpritePaletteByTag(gUnknown_082FE6D8[data[4]].tag);
}

static void sub_802E938(struct Sprite *sprite)
{
    s16 *data = gTasks[sprite->data[3]].data;

    if (data[11] % data[5] != 0)
        return;
    if (data[11] == data[10])
        return;

    data[10] = data[11];
    switch (sprite->data[2])
    {
    case 0:
        sprite->invisible = FALSE;
    case 1:
    case 2:
        PlaySE(SE_KON);
        StartSpriteAnim(sprite, sprite->data[2]);
        break;
    case 3:
        PlaySE(SE_PIN);
        StartSpriteAnim(sprite, sprite->data[2]);
        gSprites[data[14]].invisible = FALSE;
        gSprites[data[15]].invisible = FALSE;
        break;
    case 4:
        sprite->invisible = TRUE;
        gSprites[data[14]].invisible = TRUE;
        gSprites[data[15]].invisible = TRUE;
        data[0] = 4;
        return;
    }
    sprite->data[2]++;
}

static void sub_802EA50(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    PlaySE(SE_KON);
    gSprites[data[13]].callback = sub_802E938;
    gSprites[data[13]].invisible = FALSE;
    gTasks[taskId].data[0] = 3;
}

static void sub_802EAB0(u8 taskId)
{
    u16 packet[6];
    s16 *data = gTasks[taskId].data;

    if (gReceivedRemoteLinkPlayers != 0)
    {
        if (gRecvCmds[0][1] == 0x7FFF)
            data[11] = gRecvCmds[0][2];
        if (GetMultiplayerId() == 0)
        {
            data[12]++;
            memset(packet, 0, sizeof(packet));
            packet[0] = 0x7FFF;
            packet[1] = data[12];
            sub_800FE50(packet);
        }
    }
    else
    {
        data[11]++;
    }
}

void sub_802EB24(s16 tileTag, s16 palTag, s16 x, s16 y, u8 subpriority)
{
    u8 taskId = CreateTask(sub_802EB98, 0x50);
    gTasks[taskId].data[2] = tileTag;
    gTasks[taskId].data[3] = palTag;
    gTasks[taskId].data[4] = x;
    gTasks[taskId].data[5] = y;
    gTasks[taskId].data[6] = subpriority;
}

bool32 sub_802EB84(void)
{
    return FuncIsActiveTask(sub_802EB98);
}

static void sub_802EB98(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    switch (data[0])
    {
    case 0:
        sub_802EF50(data[2], data[3]);
        data[7] = sub_802EFA8(data[2], data[3], data[4], data[5], data[6]);
        sub_802EFFC(data[2], data[3], data[4], data[5], data[6], &data[8], &data[9]);
        data[0]++;
        break;
    case 1:
        if (!sub_802EC98(data[7]))
        {
            sub_802EDCC(data[7], data[8], data[9]);
            FreeSpriteOamMatrix(&gSprites[data[7]]);
            DestroySprite(&gSprites[data[7]]);
            data[0]++;
        }
        break;
    case 2:
        if (!sub_802EE30(data[8]))
        {
            DestroySprite(&gSprites[data[8]]);
            DestroySprite(&gSprites[data[9]]);
            FreeSpriteTilesByTag(data[2]);
            FreeSpritePaletteByTag(data[3]);
            DestroyTask(taskId);
        }
        break;
    }
}

static bool32 sub_802EC98(u8 spriteId)
{
    struct Sprite *sprite = &gSprites[spriteId];

    switch (sprite->data[0])
    {
    case 0:
        sub_8007E18(sprite, 0x800, 0x1A);
        sprite->data[0]++;
    case 1:
        if (sprite->data[2] == 0)
            PlaySE(SE_KON2);
        if (++sprite->data[2] >= 20)
        {
            sprite->data[2] = 0;
            StartSpriteAffineAnim(sprite, 1);
            sprite->data[0]++;
        }
        break;
    case 2:
        if (sprite->affineAnimEnded)
            sprite->data[0]++;
        break;
    case 3:
        if (++sprite->data[2] >= 4)
        {
            sprite->data[2] = 0;
            sprite->data[0]++;
            StartSpriteAffineAnim(sprite, 2);
        }
        break;
    case 4:
        sprite->pos1.y -= 4;
        if (++sprite->data[2] >= 8)
        {
            if (sprite->data[4] <= 1)
            {
                StartSpriteAnim(sprite, sprite->data[4] + 1);
                sprite->data[2] = 0;
                sprite->data[0]++;
            }
            else
            {
                sprite->data[0] = 7;
                return FALSE;
            }
        }
        break;
    case 5:
        sprite->pos1.y += 4;
        if (++sprite->data[2] >= 8)
        {
            sprite->data[2] = 0;
            StartSpriteAffineAnim(sprite, 3);
            sprite->data[0]++;
        }
        break;
    case 6:
        if (sprite->affineAnimEnded)
        {
            sprite->data[4]++;
            sprite->data[0] = 1;
        }
        break;
    case 7:
        return FALSE;
    }

    return TRUE;
}

// First argument is unused.
static void sub_802EDCC(u8 spriteId1, u8 spriteId2, u8 spriteId3)
{
    gSprites[spriteId2].pos2.y = -40;
    gSprites[spriteId3].pos2.y = -40;
    gSprites[spriteId2].invisible = FALSE;
    gSprites[spriteId3].invisible = FALSE;
    gSprites[spriteId2].callback = sub_802EE5C;
    gSprites[spriteId3].callback = sub_802EE5C;
}

static bool32 sub_802EE30(u8 spriteId)
{
    return (gSprites[spriteId].callback == sub_802EE5C);
}

static void sub_802EE5C(struct Sprite *sprite)
{
    int y;
    s16 *data = sprite->data;

    switch (data[0])
    {
    case 0:
        data[4] = 64;
        data[5] = sprite->pos2.y << 4;
        data[0]++;
    case 1:
        data[5] += data[4];
        data[4]++;
        sprite->pos2.y = data[5] >> 4;
        if (sprite->pos2.y >= 0)
        {
            PlaySE(SE_KON2);
            sprite->pos2.y = 0;
            data[0]++;
        }
        break;
    case 2:
        data[1] += 12;
        if (data[1] >= 128)
        {
            PlaySE(SE_KON2);
            data[1] = 0;
            data[0]++;
        }
        y = gSineTable[data[1]];
        sprite->pos2.y = -(y >> 4);
        break;
    case 3:
        data[1] += 16;
        if (data[1] >= 128)
        {
            PlaySE(SE_KON2);
            data[1] = 0;
            data[0]++;
        }
        sprite->pos2.y = -(gSineTable[data[1]] >> 5);
        break;
    case 4:
        if (++data[1] > 40)
            sprite->callback = SpriteCallbackDummy;
        break;
    }
}

static const u16 gPkmnJump321StartPal2[] = INCBIN_U16("graphics/link_games/pkmnjump_321start2.gbapal");
static const u32 gPkmnJump321StartGfx2[] = INCBIN_U32("graphics/link_games/pkmnjump_321start2.4bpp.lz");

static void sub_802EF50(u16 tileTag, u16 palTag)
{
    struct CompressedSpriteSheet sprSheet = {gPkmnJump321StartGfx2, 0xE00, 0};
    struct SpritePalette sprPal = {gPkmnJump321StartPal2, 0};

    sprSheet.tag = tileTag;
    sprPal.tag = palTag;

    LoadCompressedSpriteSheet(&sprSheet);
    LoadSpritePalette(&sprPal);
}

static const struct OamData sOamData_82FEBDC =
{
    .y = 0,
    .affineMode = 3,
    .objMode = 0,
    .mosaic = 0,
    .bpp = 0,
    .shape = 0,
    .x = 0,
    .matrixNum = 0,
    .size = 2,
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
    .affineParam = 0
};

static const struct OamData sOamData_82FEBE4 =
{
    .y = 0,
    .affineMode = 0,
    .objMode = 0,
    .mosaic = 0,
    .bpp = 0,
    .shape = 1,
    .x = 0,
    .matrixNum = 0,
    .size = 3,
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
    .affineParam = 0
};

static const union AnimCmd sSpriteAnim_82FEBEC[] =
{
    ANIMCMD_FRAME(0, 1),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_82FEBF4[] =
{
    ANIMCMD_FRAME(16, 1),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_82FEBFC[] =
{
    ANIMCMD_FRAME(32, 1),
    ANIMCMD_END
};

static const union AnimCmd *const sSpriteAnimTable_82FEC04[] =
{
    sSpriteAnim_82FEBEC,
    sSpriteAnim_82FEBF4,
    sSpriteAnim_82FEBFC
};

static const union AnimCmd sSpriteAnim_82FEC10[] =
{
    ANIMCMD_FRAME(48, 1),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_82FEC18[] =
{
    ANIMCMD_FRAME(80, 1),
    ANIMCMD_END
};

static const union AnimCmd *const sSpriteAnimTable_82FEC20[] =
{
    sSpriteAnim_82FEC10,
    sSpriteAnim_82FEC18
};

static const union AffineAnimCmd sSpriteAffineAnim_82FEC28[] =
{
    AFFINEANIMCMD_FRAME(256, 256, 0, 0),
    AFFINEANIMCMD_END
};

static const union AffineAnimCmd sSpriteAffineAnim_82FEC38[] =
{
    AFFINEANIMCMD_FRAME(256, 256, 0, 0),
    AFFINEANIMCMD_FRAME(16, -16, 0, 8),
    AFFINEANIMCMD_END
};

static const union AffineAnimCmd sSpriteAffineAnim_82FEC50[] =
{
    AFFINEANIMCMD_FRAME(-18, 18, 0, 8),
    AFFINEANIMCMD_END
};

static const union AffineAnimCmd sSpriteAffineAnim_82FEC60[] =
{
    AFFINEANIMCMD_FRAME(6, -6, 0, 8),
    AFFINEANIMCMD_FRAME(-4, 4, 0, 8),
    AFFINEANIMCMD_FRAME(256, 256, 0, 0),
    AFFINEANIMCMD_END
};

static const union AffineAnimCmd *const sSpriteAffineAnimTable_82FEC80[] =
{
    sSpriteAffineAnim_82FEC28,
    sSpriteAffineAnim_82FEC38,
    sSpriteAffineAnim_82FEC50,
    sSpriteAffineAnim_82FEC60
};

static u8 sub_802EFA8(u16 tileTag, u16 palTag, s16 x, s16 y, u8 subpriority)
{
    u8 spriteId;
    struct SpriteTemplate sprTemplate =
    {
        .tileTag = 0,
        .paletteTag = 0,
        .oam = &sOamData_82FEBDC,
        .anims = sSpriteAnimTable_82FEC04,
        .images = NULL,
        .affineAnims = sSpriteAffineAnimTable_82FEC80,
        .callback = SpriteCallbackDummy,
    };

    sprTemplate.tileTag = tileTag;
    sprTemplate.paletteTag = palTag;
    spriteId = CreateSprite(&sprTemplate, x, y, subpriority);
    return spriteId;
}

static void sub_802EFFC(u16 tileTag, u16 palTag, s16 x, s16 y, u8 subpriority, s16 *spriteId1, s16 *spriteId2)
{
    struct SpriteTemplate sprTemplate =
    {
        .tileTag = 0,
        .paletteTag = 0,
        .oam = &sOamData_82FEBE4,
        .anims = sSpriteAnimTable_82FEC20,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy,
    };

    sprTemplate.tileTag = tileTag;
    sprTemplate.paletteTag = palTag;
    *spriteId1 = CreateSprite(&sprTemplate, x - 32, y, subpriority);
    *spriteId2 = CreateSprite(&sprTemplate, x + 32, y, subpriority);

    gSprites[*spriteId1].invisible = TRUE;
    gSprites[*spriteId2].invisible = TRUE;
    StartSpriteAnim(&gSprites[*spriteId2], 1);
}
