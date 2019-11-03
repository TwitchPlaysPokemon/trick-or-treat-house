#include "global.h"
#include "palette.h"
#include "main.h"
#include "task.h"
#include "bg.h"
#include "alloc.h"
#include "window.h"
#include "text.h"
#include "menu.h"
#include "international_string_util.h"
#include "constants/songs.h"
#include "gpu_regs.h"
#include "m4a.h"
#include "constants/rgb.h"
#include "trainer_pokemon_sprites.h"
#include "starter_choose.h"
#include "decompress.h"
#include "intro_credits_graphics.h"
#include "sound.h"
#include "trig.h"
#include "graphics.h"
#include "pokedex.h"
#include "constants/vars.h"
#include "constants/trainers.h"
#include "constants/species.h"
#include "event_data.h"
#include "random.h"

enum
{
    PAGE_TITLE,
    PAGE_DIRECTOR,
    PAGE_ART_DIRECTOR,
    PAGE_WORLD_DIRECTOR,
    PAGE_LEAD_PROGRAMMER,
    PAGE_PROGRAMMERS_1,
    PAGE_PROGRAMMERS_2,
    PAGE_PROGRAMMERS_3,
    PAGE_PROGRAMMERS_4,
    PAGE_GRAPHIC_DESIGNERS_1,
    PAGE_GRAPHIC_DESIGNERS_2,
    PAGE_GRAPHIC_DESIGNERS_3,
    PAGE_MUSIC_COMPOSITION,
    PAGE_SOUND_EFFECTS,
    PAGE_GAME_DESIGNERS_1,
    PAGE_GAME_DESIGNERS_2,
    PAGE_GAME_DESIGNERS_3,
    PAGE_SCENARIO_PLOT,
    PAGE_SCENARIO,
    PAGE_SCRIPT_DESIGNERS,
    PAGE_MAP_DESIGNERS,
    PAGE_BATTLE_FRONTIER_DATA,
    PAGE_PARAMETRIC_DESIGNERS,
    PAGE_POKEDEX_TEXT,
    PAGE_ENVIRONMENT_AND_TOOL_PROGRAMS_1,
    PAGE_PKMN_DESIGNERS_1,
    PAGE_PKMN_DESIGNERS_2,
    PAGE_PKMN_DESIGNERS_3,
    PAGE_PKMN_DESIGNERS_4,
    PAGE_SUPPORT_PROGRAMMERS,
    PAGE_NCL_PRODUCT_TESTING,
    PAGE_PACKAGE_AND_MANUAL,
    PAGE_SPECIAL_THANKS_1,
    PAGE_SPECIAL_THANKS_2,
    PAGE_SPECIAL_THANKS_3,
    PAGE_SPECIAL_THANKS_4,
    PAGE_INFORMATION_SUPERVISORS,
    PAGE_ARTWORK_1,
    PAGE_ARTWORK_2,
    PAGE_ARTWORK_3,
    PAGE_COORDINATORS,
    PAGE_ENGLISH_VERSION,
    PAGE_TRANSLATOR,
    PAGE_TEXT_EDITOR,
    PAGE_NCL_COORDINATOR,
    PAGE_PROGRAMMERS_5,
    PAGE_GRAPHIC_DESIGNER,
    PAGE_ENVIRONMENT_AND_TOOL_PROGRAMS_2,
    PAGE_NOA_TESTING,
    PAGE_BRAILLE_CODE_CHECK_1,
    PAGE_BRAILLE_CODE_CHECK_2,
    PAGE_SPECIAL_THANKS_5,
    PAGE_TASK_MANAGERS,
    PAGE_PRODUCERS,
    PAGE_EXECUTIVE_DIRECTOR,
    PAGE_EXECUTIVE_PRODUCERS_1,
    PAGE_EXECUTIVE_PRODUCERS_2,
    PAGE_COUNT
};

#define COLOR_DARK_GREEN RGB(7, 11, 6)
#define COLOR_LIGHT_GREEN RGB(13, 20, 12)

enum
{
    TDA_0 = 0,
    TDA_TASK_C_ID = 1,
    TDA_TASK_E_ID = 2,
    TDA_TASK_D_ID = 3,
    TDA_4 = 4,
    TDA_PLAYER_CYCLIST = 5,
    TDA_RIVAL_CYCLIST = 6,
    TDA_7 = 7, // Has something to do with the bike scene
    TDA_11 = 11, // Gets set depending on whether the bike or the grass scene should be shown
    TDA_12 = 12,
    TDA_13 = 13,
    TDA_14 = 14,
    TDA_TASK_B_ID = 15,

    // Appears to be responsible for text
    TDB_0 = 0,
    TDB_TASK_A_ID = 1,
    TDB_CURRENT_PAGE = 2,
    TDB_3 = 3,

    TDC_0 = 0,
    TDC_1 = 1,
    TDC_2 = 2,
    TDC_3 = 3,
    TDC_4 = 4,
    TDC_5 = 5,

    TDD_STATE = 0,
    TDD_TASK_A_ID = 1,
    TDD_2 = 2,
    TDD_3 = 3,

    TDE_0 = 0,
    TDE_1 = 1,
    TDE_TASK_A_ID = 2,
};

struct CreditsData
{
    u16 pkmnToShow[71];
    u16 imgCounter;
    u16 nextImgPos;
    u16 currShownPkmn;
    u16 numPkmnToShow;
    u16 caughtPkmnIds[NATIONAL_DEX_COUNT];
    u16 numCaughtPkmn;
    u16 unk39C[7];
};

struct CreditsEntry
{
    u8 var_0;
    bool8 isTitle;
    const u8 *text;
};

static EWRAM_DATA s16 gUnknown_0203BCE0 = 0;
static EWRAM_DATA u16 gUnknown_0203BCE2 = 0; // TASK A
EWRAM_DATA bool8 gHasHallOfFameRecords = 0;
static EWRAM_DATA u8 gUnknown_0203BCE5 = 0;
static EWRAM_DATA struct CreditsData *sCreditsData = {0};

static const u16 gUnknown_085E56F0[][16] =
{
    INCBIN_U16("graphics/credits/credits_1.gbapal"),
    INCBIN_U16("graphics/credits/credits_2.gbapal"),
    INCBIN_U16("graphics/credits/credits_3.gbapal"),
    INCBIN_U16("graphics/credits/credits_4.gbapal"),
};

static const u32 gCreditsCopyrightEnd_Gfx[] = INCBIN_U32("graphics/credits/the_end_copyright.4bpp.lz");

static void sub_81772B8(struct Sprite *sprite);

static const u8 sTheEnd_LetterTMap[] =
{
    0,    1, 0,
    0xFF, 1, 0xFF,
    0xFF, 1, 0xFF,
    0xFF, 1, 0xFF,
    0xFF, 1, 0xFF,
};

static const u8 sTheEnd_LetterHMap[] =
{
    1, 0xFF, 1,
    1, 0xFF, 1,
    1, 2,    1,
    1, 0xFF, 1,
    1, 0xFF, 1,
};

static const u8 sTheEnd_LetterEMap[] =
{
    1, 0, 0,
    1, 0xFF, 0xFF,
    1, 2,    2,
    1, 0xFF, 0xFF,
    1, 0x80, 0x80,
};

static const u8 sTheEnd_LetterNMap[] =
{
    1, 3, 1,
    1, 4, 1,
    1, 5, 1,
    1, 0xC4, 1,
    1, 0xC3, 1,
};

static const u8 sTheEnd_LetterDMap[] =
{
    1, 6, 7,
    1, 8, 9,
    1, 0xFF, 1,
    1, 0x88, 0x89,
    1, 0x86, 0x87,
};

#include "constants/credits_text.h"

static const struct BgTemplate sBackgroundTemplates[] =
{
    {
        .bg = 0,
        .charBaseIndex = 2,
        .mapBaseIndex = 28,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0
    },
};
static const struct WindowTemplate sWindowTemplates[] =
{
    {
        .bg = 0,
        .tilemapLeft = 0,
        .tilemapTop = 9,
        .width = 30,
        .height = 12,
        .paletteNum = 8,
        .baseBlock = 1
    },
    DUMMY_WIN_TEMPLATE,
};
static const u8 sMonSpritePos[][2] =
{
    {104, 36},
    {120, 36},
    {136, 36},
};

static const union AnimCmd gUnknown_085E6F84[] =
{
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_FRAME(64, 8),
    ANIMCMD_FRAME(128, 8),
    ANIMCMD_FRAME(192, 8),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd gUnknown_085E6F98[] =
{
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_FRAME(64, 4),
    ANIMCMD_FRAME(128, 4),
    ANIMCMD_FRAME(192, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd gUnknown_085E6FAC[] =
{
    ANIMCMD_FRAME(256, 4),
    ANIMCMD_FRAME(320, 4),
    ANIMCMD_FRAME(384, 4),
    ANIMCMD_END,
};

static const union AnimCmd gUnknown_085E6FBC[] =
{
    ANIMCMD_FRAME(384, 30),
    ANIMCMD_FRAME(320, 30),
    ANIMCMD_FRAME(256, 30),
    ANIMCMD_FRAME(256, 30),
    ANIMCMD_END,
};

static const union AnimCmd *const gUnknown_085E6FD0[] =
{
    gUnknown_085E6F84,
    gUnknown_085E6F98,
    gUnknown_085E6FAC,
    gUnknown_085E6FBC,
};

static const union AnimCmd gUnknown_085E6FE0[] =
{
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_FRAME(64, 8),
    ANIMCMD_FRAME(128, 8),
    ANIMCMD_FRAME(192, 8),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd gUnknown_085E6FF4[] =
{
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_FRAME(64, 4),
    ANIMCMD_FRAME(128, 4),
    ANIMCMD_FRAME(192, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd gUnknown_085E7008[] =
{
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_END,
};

static const union AnimCmd *const gUnknown_085E7010[] =
{
    gUnknown_085E6FE0,
    gUnknown_085E6FF4,
    gUnknown_085E7008,
};

static const struct SpriteSheet gUnknown_085E701C[] = {
    { gDecompressionBuffer, 6144, 1001 },
    { NULL },
};
static const struct SpritePalette gUnknown_085E702C[] = {
    { (const u16 *)(gDecompressionBuffer + 0x1800), 1001 },
    { NULL },
};

static const struct OamData gUnknown_085E703C =
{
    .y = 160,
    .affineMode = 0,
    .objMode = 0,
    .mosaic = 0,
    .bpp = 0,
    .shape = SPRITE_SHAPE(64x64),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(64x64),
    .tileNum = 0,
    .priority = 1,
    .paletteNum = 0,
    .affineParam = 0,
};

static const union AnimCmd gUnknown_085E7044[] =
{
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_END,
};

static const union AnimCmd gUnknown_085E704C[] =
{
    ANIMCMD_FRAME(64, 8),
    ANIMCMD_END,
};

static const union AnimCmd gUnknown_085E7054[] =
{
    ANIMCMD_FRAME(128, 8),
    ANIMCMD_END,
};

static const union AnimCmd *const gUnknown_085E705C[] =
{
    gUnknown_085E7044,
    gUnknown_085E704C,
    gUnknown_085E7054,
};

static const struct SpriteTemplate gUnknown_085E7068 =
{
    .tileTag = 1001,
    .paletteTag = 1001,
    .oam = &gUnknown_085E703C,
    .anims = gUnknown_085E705C,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = sub_81772B8,
};

static void Task_WaitPaletteFade(u8 taskIdA);
static void Task_ProgressCreditTasks(u8 taskIdA);
static void sub_8175808(u8 taskIdA);
static void c2_080C9BFC(u8 taskIdA);
static void Task_CreditsLoadGrassScene(u8 taskIdA);
static void sub_81758A4(u8 taskIdA);
static void Task_CreditsTheEnd1(u8 taskIdA);
static void Task_CreditsTheEnd2(u8 taskIdA);
static void Task_CreditsTheEnd3(u8 taskIdA);
static void Task_CreditsTheEnd4(u8 taskIdA);
static void Task_CreditsTheEnd5(u8 taskIdA);
static void Task_CreditsTheEnd6(u8 taskIdA);
static void Task_CreditsSoftReset(u8 taskIdA);
static void ResetGpuAndVram(void);
static void sub_8175DA0(u8 taskIdB);
static u8 CheckChangeScene(u8 page, u8 taskIdA);
static void sub_81760FC(u8 taskIdA);
static void sub_817651C(u8 taskIdA);
static void sub_817624C(u8 taskIdA);
static bool8 sub_8176AB0(u8 data, u8 taskIdA);
static void ResetCreditsTasks(u8 taskIdA);
static void LoadTheEndScreen(u16, u16, u16);
static void sub_8176E40(u16 arg0, u16 palette);
static void sub_8176EE8(struct Sprite *sprite);
static void sub_8176F90(struct Sprite *sprite);
static u8 MakeMonSprite(u16 species, s16 x, s16 y, u16 position);
static void DeterminePokemonToShow(void);

static void CreditsVBlankCallback(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static void CB2_RunCreditsSequence(void)
{
    RunTasks();
    AnimateSprites();

    if ((gMain.heldKeys & B_BUTTON)
     && gHasHallOfFameRecords != 0
     && gTasks[gUnknown_0203BCE2].func == Task_ProgressCreditTasks)
    {
        CreditsVBlankCallback();
        RunTasks();
        AnimateSprites();
        gUnknown_0203BCE5 = 1;
    }
    BuildOamBuffer();
    UpdatePaletteFade();
}

static void sub_8175548(void)
{
    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, sBackgroundTemplates, 1);
    SetBgTilemapBuffer(0, AllocZeroed(0x800));
    LoadPalette(gUnknown_085E56F0, 0x80, 0x40);
    InitWindows(sWindowTemplates);
    DeactivateAllTextPrinters();
    PutWindowTilemap(0);
    CopyWindowToVram(0, 3);
    ShowBg(0);
}

static void sub_81755A4(void)
{
    void *ptr;
    FreeAllWindowBuffers();
    ptr = GetBgTilemapBuffer(0);
    if (ptr)
        Free(ptr);
}

static void PrintCreditsText(const u8 *string, u8 y, bool8 isTitle)
{
    u8 x;
    u8 color[3];

    color[0] = 0;

    if (isTitle == TRUE)
    {
        color[1] = 3;
        color[2] = 4;
    }
    else
    {
        color[1] = 1;
        color[2] = 2;
    }

    x = GetStringCenterAlignXOffsetWithLetterSpacing(1, string, 0xF0, 1);
    AddTextPrinterParameterized4(0, 1, x, y, 1, 0, color, -1, string);
}

#ifdef MULTI_COLUMN_MODE
static void PrintCreditsText2(const u8 *string, u8 y, bool8 isTitle, bool8 isLeft)
{
    u8 x;
    u8 color[3];

    color[0] = 0;

    if (isTitle == 1)
    {
        color[1] = 3;
        color[2] = 4;
    }
    else
    {
        color[1] = 1;
        color[2] = 2;
    }
    x = (isLeft)? 8 : 0xF0 - 8 - GetStringWidth(1, string, 1);
    AddTextPrinterParameterized4(0, 1, x, y, 1, 0, color, -1, string);
}
#endif

void CB2_StartCreditsSequence(void)
{
    u8 taskIdA;
    s16 taskIdC;
    u8 taskIdB;

    ResetGpuAndVram();
    SetVBlankCallback(NULL);
    InitHeap(gHeap, HEAP_SIZE);
    ResetPaletteFade();
    ResetTasks();
    sub_8175548();

    taskIdA = CreateTask(Task_WaitPaletteFade, 0);

    gTasks[taskIdA].data[TDA_4] = 0;
    gTasks[taskIdA].data[TDA_7] = 0;
    gTasks[taskIdA].data[TDA_11] = 0;
    gTasks[taskIdA].data[TDA_13] = 1;

    while (TRUE)
    {
        if (sub_8176AB0(0, taskIdA))
            break;
    }

    taskIdC = gTasks[taskIdA].data[TDA_TASK_C_ID];
    gTasks[taskIdC].data[TDC_0] = 40;

    SetGpuReg(REG_OFFSET_BG0VOFS, 0xFFFC);

    taskIdB = CreateTask(sub_8175DA0, 0);

    gTasks[taskIdB].data[TDB_TASK_A_ID] = taskIdA;
    gTasks[taskIdA].data[TDA_TASK_B_ID] = taskIdB;

    BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, RGB_BLACK);
    EnableInterrupts(INTR_FLAG_VBLANK);
    SetVBlankCallback(CreditsVBlankCallback);
    m4aSongNumStart(MUS_THANKFOR);
    SetMainCallback2(CB2_RunCreditsSequence);
    gUnknown_0203BCE5 = 0;
    sCreditsData = AllocZeroed(sizeof(struct CreditsData));

    DeterminePokemonToShow();

    sCreditsData->imgCounter = 0;
    sCreditsData->nextImgPos = 0;
    sCreditsData->currShownPkmn = 0;

    gUnknown_0203BCE2 = taskIdA;
}

static void Task_WaitPaletteFade(u8 taskIdA)
{
    if (!gPaletteFade.active)
        gTasks[taskIdA].func = Task_ProgressCreditTasks;
}

static void Task_ProgressCreditTasks(u8 taskIdA)
{
    u16 data1;

    if (gTasks[taskIdA].data[TDA_4])
    {
        s16 taskIdC;

        taskIdC = gTasks[taskIdA].data[TDA_TASK_C_ID];
        gTasks[taskIdC].data[TDC_0] = 30;

        gTasks[taskIdA].data[TDA_12] = 0x100;
        gTasks[taskIdA].func = Task_CreditsTheEnd1;
        return;
    }

    gUnknown_0203BCE0 = 0;
    data1 = gTasks[taskIdA].data[TDA_11];

    if (gTasks[taskIdA].data[TDA_11] == 1)
    {
        gTasks[taskIdA].data[TDA_13] = data1;
        gTasks[taskIdA].data[TDA_11] = 0;
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
        gTasks[taskIdA].func = sub_8175808;
    }
    else if (gTasks[taskIdA].data[TDA_11] == 2)
    {
        gTasks[taskIdA].data[TDA_13] = data1;
        gTasks[taskIdA].data[TDA_11] = 0;
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
        gTasks[taskIdA].func = sub_81758A4;
    }
}

static void sub_8175808(u8 taskIdA)
{
    if (!gPaletteFade.active)
    {
        SetGpuReg(REG_OFFSET_DISPCNT, 0);
        ResetCreditsTasks(taskIdA);
        gTasks[taskIdA].func = c2_080C9BFC;
    }
}

static void c2_080C9BFC(u8 taskIdA)
{
    u16 backup;

    SetVBlankCallback(NULL);

    if (sub_8176AB0(gTasks[taskIdA].data[TDA_7], taskIdA))
    {
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, RGB_BLACK);
        EnableInterrupts(INTR_FLAG_VBLANK);
        SetVBlankCallback(CreditsVBlankCallback);
        gTasks[taskIdA].func = Task_WaitPaletteFade;
    }
}

static void sub_81758A4(u8 taskIdA)
{
    if (!gPaletteFade.active)
    {
        SetGpuReg(REG_OFFSET_DISPCNT, 0);
        ResetCreditsTasks(taskIdA);
        gTasks[taskIdA].func = Task_CreditsLoadGrassScene;
    }
}

static void Task_CreditsLoadGrassScene(u8 taskIdA)
{
    switch (gMain.state)
    {
    default:
    case 0:
    {
        u16 i;
        u16 *temp;

        ResetSpriteData();
        ResetAllPicSprites();
        FreeAllSpritePalettes();
        gReservedSpritePaletteCount = 8;
        LZ77UnCompVram(gBirchHelpGfx, (void *)VRAM);
        LZ77UnCompVram(gBirchGrassTilemap, (void *)(BG_SCREEN_ADDR(7)));
        LoadPalette(gBirchBagGrassPal[0] + 1, 1, 31 * 2);

        for (i = 0; i < 0x800; i++)
            gDecompressionBuffer[i] = 0x11;
        for (i = 0; i < 0x800; i++)
            (gDecompressionBuffer + 0x800)[i] = 0x22;
        for (i = 0; i < 0x800; i++)
            (gDecompressionBuffer + 0x1000)[i] = 0x33;

        temp = (u16 *)(&gDecompressionBuffer[0x1800]);
        temp[0] = RGB_BLACK;
        temp[1] = RGB(31, 31, 20); // light yellow
        temp[2] = RGB(31, 20, 20); // light red
        temp[3] = RGB(20, 20, 31); // light blue

        LoadSpriteSheet(gUnknown_085E701C);
        LoadSpritePalette(gUnknown_085E702C);

        gMain.state += 1;
        break;
    }
    case 1:
        gTasks[taskIdA].data[TDA_TASK_D_ID] = CreateTask(sub_81760FC, 0);
        gTasks[gTasks[taskIdA].data[TDA_TASK_D_ID]].data[TDD_STATE] = 1;
        gTasks[gTasks[taskIdA].data[TDA_TASK_D_ID]].data[TDD_TASK_A_ID] = taskIdA;
        gTasks[gTasks[taskIdA].data[TDA_TASK_D_ID]].data[TDD_2] = gTasks[taskIdA].data[TDA_7];

        BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, RGB_BLACK);
        SetGpuReg(REG_OFFSET_BG3HOFS, 0);
        SetGpuReg(REG_OFFSET_BG3VOFS, 32);
        SetGpuReg(REG_OFFSET_BG3CNT, BGCNT_PRIORITY(3)
                                   | BGCNT_CHARBASE(0)
                                   | BGCNT_SCREENBASE(7)
                                   | BGCNT_16COLOR
                                   | BGCNT_TXT256x256);
        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_MODE_0
                                    | DISPCNT_OBJ_1D_MAP
                                    | DISPCNT_BG0_ON
                                    | DISPCNT_BG3_ON
                                    | DISPCNT_OBJ_ON);

        gMain.state = 0;
        gUnknown_0203BD28 = 0;
        gTasks[taskIdA].func = Task_WaitPaletteFade;
        break;
    }
}

static void Task_CreditsTheEnd1(u8 taskIdA)
{
    if (gTasks[taskIdA].data[TDA_12])
    {
        gTasks[taskIdA].data[TDA_12] -= 1;
        return;
    }

    BeginNormalPaletteFade(0xFFFFFFFF, 12, 0, 16, RGB_BLACK);
    gTasks[taskIdA].func = Task_CreditsTheEnd2;
}

static void Task_CreditsTheEnd2(u8 taskIdA)
{
    if (!gPaletteFade.active)
    {
        ResetCreditsTasks(taskIdA);
        gTasks[taskIdA].func = Task_CreditsTheEnd3;
    }
}

static void Task_CreditsTheEnd3(u8 taskIdA)
{
    ResetGpuAndVram();
    ResetPaletteFade();
    LoadTheEndScreen(0, 0x3800, 0);
    ResetSpriteData();
    FreeAllSpritePalettes();
    BeginNormalPaletteFade(0xFFFFFFFF, 8, 16, 0, RGB_BLACK);

    SetGpuReg(REG_OFFSET_BG0CNT, BGCNT_PRIORITY(0)
                               | BGCNT_CHARBASE(0)
                               | BGCNT_SCREENBASE(7)
                               | BGCNT_16COLOR
                               | BGCNT_TXT256x256);
    EnableInterrupts(INTR_FLAG_VBLANK);
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_MODE_0
                                | DISPCNT_OBJ_1D_MAP
                                | DISPCNT_BG0_ON);

    gTasks[taskIdA].data[TDA_0] = 215; //set this to 215 to actually show "THE END" in time to the last song beat
    gTasks[taskIdA].func = Task_CreditsTheEnd4;
}

static void Task_CreditsTheEnd4(u8 taskIdA)
{
    if (gTasks[taskIdA].data[TDA_0])
    {
        gTasks[taskIdA].data[TDA_0] -= 1;
        return;
    }

    BeginNormalPaletteFade(0xFFFFFFFF, 6, 0, 16, RGB_BLACK);
    gTasks[taskIdA].func = Task_CreditsTheEnd5;
}

static void Task_CreditsTheEnd5(u8 taskIdA)
{
    if (!gPaletteFade.active)
    {
        sub_8176E40(0x3800, 0);

        BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 0, RGB_BLACK);
        gTasks[taskIdA].data[TDA_0] = 7200;
        gTasks[taskIdA].func = Task_CreditsTheEnd6;
    }
}

static void Task_CreditsTheEnd6(u8 taskIdA)
{
    if (!gPaletteFade.active)
    {
        if (gTasks[taskIdA].data[TDA_0] == 0 || gMain.newKeys)
        {
            FadeOutBGM(4);
            BeginNormalPaletteFade(0xFFFFFFFF, 8, 0, 16, RGB_WHITEALPHA);
            gTasks[taskIdA].func = Task_CreditsSoftReset;
            return;
        }

        if (gTasks[taskIdA].data[TDA_0] == 7144)
            FadeOutBGM(8);

        if (gTasks[taskIdA].data[TDA_0] == 6840)
            m4aSongNumStart(MUS_END);

        gTasks[taskIdA].data[TDA_0] -= 1;
    }
}

static void Task_CreditsSoftReset(u8 taskIdA)
{
    if (!gPaletteFade.active)
        SoftReset(0xFF);
}

static void ResetGpuAndVram(void)
{
    SetGpuReg(REG_OFFSET_DISPCNT, 0);

    SetGpuReg(REG_OFFSET_BG3HOFS, 0);
    SetGpuReg(REG_OFFSET_BG3VOFS, 0);
    SetGpuReg(REG_OFFSET_BG2HOFS, 0);
    SetGpuReg(REG_OFFSET_BG2VOFS, 0);
    SetGpuReg(REG_OFFSET_BG1HOFS, 0);
    SetGpuReg(REG_OFFSET_BG1VOFS, 0);
    SetGpuReg(REG_OFFSET_BG0HOFS, 0);
    SetGpuReg(REG_OFFSET_BG0VOFS, 0);

    SetGpuReg(REG_OFFSET_BLDCNT, 0);
    SetGpuReg(REG_OFFSET_BLDALPHA, 0);
    SetGpuReg(REG_OFFSET_BLDY, 0);

    DmaFill16(3, 0, (void *)VRAM, VRAM_SIZE);
    DmaFill32(3, 0, (void *)OAM, OAM_SIZE);
    DmaFill16(3, 0, (void *)(PLTT + 2), PLTT_SIZE - 2);
}

static void sub_8175DA0(u8 taskIdB)
{
    int i;

    switch (gTasks[taskIdB].data[TDB_0])
    {
    case 0:
    case 6:
    case 7:
    case 8:
    case 9:
    default:
        if (!gPaletteFade.active)
        {
            gTasks[taskIdB].data[TDB_0] = 1;
            gTasks[taskIdB].data[TDB_3] = 0x48;
            gTasks[gTasks[taskIdB].data[TDB_TASK_A_ID]].data[TDA_14] = 0;
            gUnknown_0203BCE0 = 0;
        }
        return;
    case 1:
        if (gTasks[taskIdB].data[TDB_3] != 0)
        {
            gTasks[taskIdB].data[TDB_3] -= 1;
            return;
        }
        gTasks[taskIdB].data[TDB_0] += 1;
        return;
    case 2:
        if (gTasks[gTasks[taskIdB].data[TDB_TASK_A_ID]].func == Task_ProgressCreditTasks)
        {
            if (gTasks[taskIdB].data[TDB_CURRENT_PAGE] < PAGE_COUNT)
            {
#ifndef MULTI_COLUMN_MODE
                for (i = 0; i < 5; i++)
                    PrintCreditsText(
                        gCreditsEntryPointerTable[gTasks[taskIdB].data[TDB_CURRENT_PAGE]][i]->text, 
                        5 + i * 16, 
                        gCreditsEntryPointerTable[gTasks[taskIdB].data[TDB_CURRENT_PAGE]][i]->isTitle);
#else
                int card = gTasks[taskIdB].data[TDB_CURRENT_PAGE];
                for (i = 0; i < 5; i++)
                {
                    if (gCreditsEntryPointerTable[card][i+5] == NULL)
                    {
                        PrintCreditsText(
                            gCreditsEntryPointerTable[card][i]->text,
                            5 + i * 16,
                            gCreditsEntryPointerTable[card][i]->isTitle);
                    }
                    else
                    {
                        PrintCreditsText2(
                            gCreditsEntryPointerTable[card][i]->text,
                            5 + i * 16,
                            gCreditsEntryPointerTable[card][i]->isTitle, 
                            TRUE);
                        PrintCreditsText2(
                            gCreditsEntryPointerTable[card][i+5]->text,
                            5 + i * 16,
                            gCreditsEntryPointerTable[card][i+5]->isTitle, 
                            FALSE);
                    }
                }
#endif

                CopyWindowToVram(0, 2);

                gTasks[taskIdB].data[TDB_CURRENT_PAGE] += 1;
                gTasks[taskIdB].data[TDB_0] += 1;

                gTasks[gTasks[taskIdB].data[TDB_TASK_A_ID]].data[TDA_14] = 1;

                if (gTasks[gTasks[taskIdB].data[TDB_TASK_A_ID]].data[TDA_13] == 1)
                    BeginNormalPaletteFade(0x00000300, 0, 16, 0, COLOR_LIGHT_GREEN);
                else
                    BeginNormalPaletteFade(0x00000300, 0, 16, 0, COLOR_DARK_GREEN);
                return;
            }
            gTasks[taskIdB].data[TDB_0] = 10;
            return;
        }
        gTasks[gTasks[taskIdB].data[TDB_TASK_A_ID]].data[TDA_14] = 0;
        return;
    case 3:
        if (!gPaletteFade.active)
        {
            gTasks[taskIdB].data[TDB_3] = 0x73;
            gTasks[taskIdB].data[TDB_0] += 1;
        }
        return;
    case 4:
        if (gTasks[taskIdB].data[TDB_3] != 0)
        {
            gTasks[taskIdB].data[TDB_3] -= 1;
            return;
        }

        if (CheckChangeScene((u8)gTasks[taskIdB].data[TDB_CURRENT_PAGE], (u8)gTasks[taskIdB].data[TDB_TASK_A_ID]))
        {
            gTasks[taskIdB].data[TDB_0] += 1;
            return;
        }
        gTasks[taskIdB].data[TDB_0] += 1;
        if (gTasks[gTasks[taskIdB].data[TDB_TASK_A_ID]].data[TDA_13] == 1)
            BeginNormalPaletteFade(0x00000300, 0, 0, 16, COLOR_LIGHT_GREEN);
        else
            BeginNormalPaletteFade(0x00000300, 0, 0, 16, COLOR_DARK_GREEN);
        return;
    case 5:
        if (!gPaletteFade.active)
        {
            FillWindowPixelBuffer(0, PIXEL_FILL(0));
            CopyWindowToVram(0, 2);
            gTasks[taskIdB].data[TDB_0] = 2;
        }
        return;
    case 10:
        gTasks[gTasks[taskIdB].data[TDB_TASK_A_ID]].data[TDA_4] = 1;
        DestroyTask(taskIdB);
        sub_81755A4();
        FREE_AND_SET_NULL(sCreditsData);
        return;
    }
}

static u8 CheckChangeScene(u8 page, u8 taskIdA)
{
    // Starts with bike + ocean + morning

    if (page == 6)
    {
        // Grass patch
        gTasks[taskIdA].data[TDA_11] = 2;
    }

    if (page == 12)
    {
        // Bike + ocean + sunset
        gTasks[taskIdA].data[TDA_7] = 1;
        gTasks[taskIdA].data[TDA_11] = 1;
    }

    if (page == 18)
    {
        // Grass patch
        gTasks[taskIdA].data[TDA_11] = 2;
    }

    if (page == 24)
    {
        // Bike + forest + sunset
        gTasks[taskIdA].data[TDA_7] = 2;
        gTasks[taskIdA].data[TDA_11] = 1;
    }

    if (page == 30)
    {
        // Grass patch
        gTasks[taskIdA].data[TDA_11] = 2;
    }

    if (page == 36)
    {
        // Bike + forest + sunset
        gTasks[taskIdA].data[TDA_7] = 3;
        gTasks[taskIdA].data[TDA_11] = 1;
    }

    if (page == 42)
    {
        // Grass patch
        gTasks[taskIdA].data[TDA_11] = 2;
    }

    if (page == 48)
    {
        // Bike + town + night
        gTasks[taskIdA].data[TDA_7] = 4;
        gTasks[taskIdA].data[TDA_11] = 1;
    }

    if (gTasks[taskIdA].data[TDA_11] != 0)
    {
        // Returns true if changed?
        return TRUE;
    }

    return FALSE;
}

static void sub_81760FC(u8 taskIdD)
{
    u8 r2;

    switch (gTasks[taskIdD].data[TDD_STATE])
    {
    case 0:
        break;
    case 1:
        if (sCreditsData->nextImgPos == 0 && gTasks[gTasks[taskIdD].data[TDD_TASK_A_ID]].data[TDA_14] == 0)
            break;
        gTasks[taskIdD].data[TDD_STATE]++;
        break;
    case 2:
        if (sCreditsData->imgCounter == 71 || gTasks[gTasks[taskIdD].data[TDD_TASK_A_ID]].func != Task_ProgressCreditTasks)
            break;
        r2 = MakeMonSprite(sCreditsData->pkmnToShow[sCreditsData->currShownPkmn], sMonSpritePos[sCreditsData->nextImgPos][0], sMonSpritePos[sCreditsData->nextImgPos][1], sCreditsData->nextImgPos);
        if (sCreditsData->currShownPkmn < sCreditsData->numPkmnToShow - 1)
        {
            sCreditsData->currShownPkmn++;
            gSprites[r2].data[3] = 50;
        }
        else
        {
            sCreditsData->currShownPkmn = 0;
            gSprites[r2].data[3] = 512;
        }
        sCreditsData->imgCounter++;
        if (sCreditsData->nextImgPos == 2)
            sCreditsData->nextImgPos = 0;
        else
            sCreditsData->nextImgPos++;
        gTasks[taskIdD].data[TDD_3] = 50;
        gTasks[taskIdD].data[TDD_STATE]++;
        break;
    case 3:
        if (gTasks[taskIdD].data[TDD_3] != 0)
            gTasks[taskIdD].data[TDD_3]--;
        else
            gTasks[taskIdD].data[TDD_STATE] = 1;
        break;
    }
}

static void sub_817624C(u8 taskIdC)
{
    switch (gTasks[taskIdC].data[TDC_0])
    {
    case 0:
        gUnknown_0203BD26 = Sin((gTasks[taskIdC].data[TDC_5] >> 1) & 0x7F, 12);
        gTasks[taskIdC].data[TDC_5]++;
        break;
    case 1:
        if (gUnknown_0203BD26 != 0)
        {
            gUnknown_0203BD26 = Sin((gTasks[taskIdC].data[TDC_5] >> 1) & 0x7F, 12);
            gTasks[taskIdC].data[TDC_5]++;
        }
        else
        {
            gSprites[gTasks[taskIdC].data[TDC_2]].data[0] = 2;
            gTasks[taskIdC].data[TDC_5] = 0;
            gTasks[taskIdC].data[TDC_0]++;
        }
        break;
    case 2:
        if (gTasks[taskIdC].data[TDC_5] < 64)
        {
            gTasks[taskIdC].data[TDC_5]++;
            gUnknown_0203BD26 = Sin(gTasks[taskIdC].data[TDC_5] & 0x7F, 20);
        }
        else
        {
            gTasks[taskIdC].data[TDC_0]++;
        }
        break;
    case 3:
        gSprites[gTasks[taskIdC].data[TDC_2]].data[0] = 3;
        gSprites[gTasks[taskIdC].data[TDC_3]].data[0] = 1;
        gTasks[taskIdC].data[TDC_4] = 120;
        gTasks[taskIdC].data[TDC_0]++;
        break;
    case 4:
        if (gTasks[taskIdC].data[TDC_4] != 0)
        {
            gTasks[taskIdC].data[TDC_4]--;
        }
        else
        {
            gTasks[taskIdC].data[TDC_5] = 64;
            gTasks[taskIdC].data[TDC_0]++;
        }
        break;
    case 5:
        if (gTasks[taskIdC].data[TDC_5] > 0)
        {
            gTasks[taskIdC].data[TDC_5]--;
            gUnknown_0203BD26 = Sin(gTasks[taskIdC].data[TDC_5] & 0x7F, 20);
        }
        else
        {
            gSprites[gTasks[taskIdC].data[TDC_2]].data[0] = 1;
            gTasks[taskIdC].data[TDC_0]++;
        }
        break;
    case 6:
        gTasks[taskIdC].data[TDC_0] = 50;
        break;
    case 10:
        gSprites[gTasks[taskIdC].data[TDC_3]].data[0] = 2;
        gTasks[taskIdC].data[TDC_0] = 50;
        break;
    case 20:
        gSprites[gTasks[taskIdC].data[TDC_2]].data[0] = 4;
        gTasks[taskIdC].data[TDC_0] = 50;
        break;
    case 30:
        gSprites[gTasks[taskIdC].data[TDC_2]].data[0] = 5;
        gSprites[gTasks[taskIdC].data[TDC_3]].data[0] = 3;
        gTasks[taskIdC].data[TDC_0] = 50;
        break;
    case 50:
        gTasks[taskIdC].data[TDC_0] = 0;
        break;
    }
}

static void sub_817651C(u8 taskIdE)
{
    s16 taskIdC;

    switch (gTasks[taskIdE].data[TDE_0])
    {
    default:
    case 0:
        if (gTasks[taskIdE].data[TDE_1] != 0x7FFF)
        {

            if (gTasks[gTasks[gTasks[taskIdE].data[TDE_TASK_A_ID]].data[TDA_TASK_B_ID]].data[TDB_CURRENT_PAGE] == 2)
            {
                gTasks[gTasks[gTasks[taskIdE].data[TDE_TASK_A_ID]].data[TDA_TASK_C_ID]].data[TDC_0] = 20;
                gTasks[taskIdE].data[TDE_1] = 0x7FFF;
            }
        }
        sub_817B540(0);
        break;
    case 1:
        sub_817B540(0);
        break;
    case 2:
        if (gTasks[taskIdE].data[TDE_1] != 0x7FFF)
        {
            taskIdC = gTasks[gTasks[taskIdE].data[TDE_TASK_A_ID]].data[TDA_TASK_C_ID];

            // Floor to multiple of 128
            if ((gTasks[taskIdC].data[TDC_5] & -128) == 640)
            {
                gTasks[taskIdC].data[TDC_0] = 1;
                gTasks[taskIdE].data[TDE_1] = 0x7FFF;
            }
        }
        sub_817B540(1);
        break;
    case 3:
        if (gTasks[taskIdE].data[TDE_1] != 0x7FFF)
        {

            if (gTasks[taskIdE].data[TDE_1] == 0x248)
            {
                gTasks[gTasks[gTasks[taskIdE].data[TDE_TASK_A_ID]].data[TDA_TASK_C_ID]].data[TDC_0] = 10;
                gTasks[taskIdE].data[TDE_1] = 0x7FFF;
            }
            else
            {
                gTasks[taskIdE].data[TDE_1] += 1;
            }
        }
        sub_817B540(1);
        break;
    case 4:
        sub_817B540(2);
        break;
    }
}

static void sub_817664C(u8 data, u8 taskIdA)
{
    switch (data)
    {
    case 0:
        gSprites[gTasks[taskIdA].data[TDA_PLAYER_CYCLIST]].invisible = FALSE;
        gSprites[gTasks[taskIdA].data[TDA_RIVAL_CYCLIST]].invisible = FALSE;
        gSprites[gTasks[taskIdA].data[TDA_PLAYER_CYCLIST]].pos1.x = 272;
        gSprites[gTasks[taskIdA].data[TDA_RIVAL_CYCLIST]].pos1.x = 272;
        gSprites[gTasks[taskIdA].data[TDA_PLAYER_CYCLIST]].pos1.y = 46;
        gSprites[gTasks[taskIdA].data[TDA_RIVAL_CYCLIST]].pos1.y = 46;
        gSprites[gTasks[taskIdA].data[TDA_PLAYER_CYCLIST]].data[0] = 0;
        gSprites[gTasks[taskIdA].data[TDA_RIVAL_CYCLIST]].data[0] = 0;
        gTasks[taskIdA].data[TDA_0] = CreateBicycleAnimationTask(0, 0x2000, 0x20, 8);
        break;
    case 1:
        gSprites[gTasks[taskIdA].data[TDA_PLAYER_CYCLIST]].invisible = FALSE;
        gSprites[gTasks[taskIdA].data[TDA_RIVAL_CYCLIST]].invisible = FALSE;
        gSprites[gTasks[taskIdA].data[TDA_PLAYER_CYCLIST]].pos1.x = 120;
        gSprites[gTasks[taskIdA].data[TDA_RIVAL_CYCLIST]].pos1.x = 272;
        gSprites[gTasks[taskIdA].data[TDA_PLAYER_CYCLIST]].pos1.y = 46;
        gSprites[gTasks[taskIdA].data[TDA_RIVAL_CYCLIST]].pos1.y = 46;
        gSprites[gTasks[taskIdA].data[TDA_PLAYER_CYCLIST]].data[0] = 0;
        gSprites[gTasks[taskIdA].data[TDA_RIVAL_CYCLIST]].data[0] = 0;
        gTasks[taskIdA].data[TDA_0] = CreateBicycleAnimationTask(0, 0x2000, 0x20, 8);
        break;
    case 2:
        gSprites[gTasks[taskIdA].data[TDA_PLAYER_CYCLIST]].invisible = FALSE;
        gSprites[gTasks[taskIdA].data[TDA_RIVAL_CYCLIST]].invisible = FALSE;
        gSprites[gTasks[taskIdA].data[TDA_PLAYER_CYCLIST]].pos1.x = 120;
        gSprites[gTasks[taskIdA].data[TDA_RIVAL_CYCLIST]].pos1.x = 272;
        gSprites[gTasks[taskIdA].data[TDA_PLAYER_CYCLIST]].pos1.y = 46;
        gSprites[gTasks[taskIdA].data[TDA_RIVAL_CYCLIST]].pos1.y = 46;
        gSprites[gTasks[taskIdA].data[TDA_PLAYER_CYCLIST]].data[0] = 0;
        gSprites[gTasks[taskIdA].data[TDA_RIVAL_CYCLIST]].data[0] = 0;
        gTasks[taskIdA].data[TDA_0] = CreateBicycleAnimationTask(1, 0x2000, 0x200, 8);
        break;
    case 3:
        gSprites[gTasks[taskIdA].data[TDA_PLAYER_CYCLIST]].invisible = FALSE;
        gSprites[gTasks[taskIdA].data[TDA_RIVAL_CYCLIST]].invisible = FALSE;
        gSprites[gTasks[taskIdA].data[TDA_PLAYER_CYCLIST]].pos1.x = 120;
        gSprites[gTasks[taskIdA].data[TDA_RIVAL_CYCLIST]].pos1.x = -32;
        gSprites[gTasks[taskIdA].data[TDA_PLAYER_CYCLIST]].pos1.y = 46;
        gSprites[gTasks[taskIdA].data[TDA_RIVAL_CYCLIST]].pos1.y = 46;
        gSprites[gTasks[taskIdA].data[TDA_PLAYER_CYCLIST]].data[0] = 0;
        gSprites[gTasks[taskIdA].data[TDA_RIVAL_CYCLIST]].data[0] = 0;
        gTasks[taskIdA].data[TDA_0] = CreateBicycleAnimationTask(1, 0x2000, 0x200, 8);
        break;
    case 4:
        gSprites[gTasks[taskIdA].data[TDA_PLAYER_CYCLIST]].invisible = FALSE;
        gSprites[gTasks[taskIdA].data[TDA_RIVAL_CYCLIST]].invisible = FALSE;
        gSprites[gTasks[taskIdA].data[TDA_PLAYER_CYCLIST]].pos1.x = 88;
        gSprites[gTasks[taskIdA].data[TDA_RIVAL_CYCLIST]].pos1.x = 152;
        gSprites[gTasks[taskIdA].data[TDA_PLAYER_CYCLIST]].pos1.y = 46;
        gSprites[gTasks[taskIdA].data[TDA_RIVAL_CYCLIST]].pos1.y = 46;
        gSprites[gTasks[taskIdA].data[TDA_PLAYER_CYCLIST]].data[0] = 0;
        gSprites[gTasks[taskIdA].data[TDA_RIVAL_CYCLIST]].data[0] = 0;
        gTasks[taskIdA].data[TDA_0] = CreateBicycleAnimationTask(2, 0x2000, 0x200, 8);
        break;
    }

    gTasks[taskIdA].data[TDA_TASK_E_ID] = CreateTask(sub_817651C, 0);
    gTasks[gTasks[taskIdA].data[TDA_TASK_E_ID]].data[TDE_0] = data;
    gTasks[gTasks[taskIdA].data[TDA_TASK_E_ID]].data[TDE_1] = 0;
    gTasks[gTasks[taskIdA].data[TDA_TASK_E_ID]].data[TDE_TASK_A_ID] = taskIdA;

    gTasks[taskIdA].data[TDA_TASK_C_ID] = CreateTask(sub_817624C, 0);
    gTasks[gTasks[taskIdA].data[TDA_TASK_C_ID]].data[TDC_0] = 0;
    gTasks[gTasks[taskIdA].data[TDA_TASK_C_ID]].data[TDC_1] = taskIdA;
    gTasks[gTasks[taskIdA].data[TDA_TASK_C_ID]].data[TDC_2] = gTasks[taskIdA].data[TDA_PLAYER_CYCLIST];
    gTasks[gTasks[taskIdA].data[TDA_TASK_C_ID]].data[TDC_3] = gTasks[taskIdA].data[TDA_RIVAL_CYCLIST];
    gTasks[gTasks[taskIdA].data[TDA_TASK_C_ID]].data[TDC_4] = 0;

    if (data == 2)
        gTasks[gTasks[taskIdA].data[TDA_TASK_C_ID]].data[TDC_5] = 0x45;
}

static bool8 sub_8176AB0(u8 data, u8 taskIdA)
{
    u8 spriteId;

    switch (gMain.state)
    {
    default:
    case 0:
        SetGpuReg(REG_OFFSET_DISPCNT, 0);
        SetGpuReg(REG_OFFSET_BG3HOFS, 8);
        SetGpuReg(REG_OFFSET_BG3VOFS, 0);
        SetGpuReg(REG_OFFSET_BG2HOFS, 0);
        SetGpuReg(REG_OFFSET_BG2VOFS, 0);
        SetGpuReg(REG_OFFSET_BG1HOFS, 0);
        SetGpuReg(REG_OFFSET_BG1VOFS, 0);
        SetGpuReg(REG_OFFSET_BLDCNT, 0);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        ResetSpriteData();
        FreeAllSpritePalettes();
        gMain.state = 1;
        break;
    case 1:
        gUnknown_0203BD24 = 34;
        gUnknown_0203BD26 = 0;
        sub_817B1C8(data);
        gMain.state += 1;
        break;
    case 2:
        if (gSaveBlock2Ptr->playerGender == MALE)
        {
            LoadCompressedSpriteSheet(gUnknown_085F5334);
            LoadCompressedSpriteSheet(gUnknown_085F53BC);
            LoadCompressedSpriteSheet(gUnknown_085F5354);
            LoadSpritePalettes(gUnknown_085F5384);

            spriteId = intro_create_brendan_sprite(120, 46);
            gTasks[taskIdA].data[TDA_PLAYER_CYCLIST] = spriteId;
            gSprites[spriteId].callback = sub_8176EE8;
            gSprites[spriteId].anims = gUnknown_085E6FD0;

            spriteId = intro_create_may_sprite(272, 46);
            gTasks[taskIdA].data[TDA_RIVAL_CYCLIST] = spriteId;
            gSprites[spriteId].callback = sub_8176F90;
            gSprites[spriteId].anims = gUnknown_085E7010;
        }
        else
        {
            LoadCompressedSpriteSheet(gUnknown_085F5344);
            LoadCompressedSpriteSheet(gUnknown_085F53AC);
            LoadCompressedSpriteSheet(gUnknown_085F5354);
            LoadSpritePalettes(gUnknown_085F5384);

            spriteId = intro_create_may_sprite(120, 46);
            gTasks[taskIdA].data[TDA_PLAYER_CYCLIST] = spriteId;
            gSprites[spriteId].callback = sub_8176EE8;
            gSprites[spriteId].anims = gUnknown_085E6FD0;

            spriteId = intro_create_brendan_sprite(272, 46);
            gTasks[taskIdA].data[TDA_RIVAL_CYCLIST] = spriteId;
            gSprites[spriteId].callback = sub_8176F90;
            gSprites[spriteId].anims = gUnknown_085E7010;
        };
        gMain.state += 1;
        break;
    case 3:
        sub_817664C(data, taskIdA);
        sub_817B3A8(data);
        gMain.state = 0;
        return TRUE;
    }
    return FALSE;
}

static void ResetCreditsTasks(u8 taskIdA)
{
    if (gTasks[taskIdA].data[TDA_0] != 0)
    {
        DestroyTask(gTasks[taskIdA].data[TDA_0]);
        gTasks[taskIdA].data[TDA_0] = 0;
    }

    if (gTasks[taskIdA].data[TDA_TASK_C_ID] != 0)
    {
        DestroyTask(gTasks[taskIdA].data[TDA_TASK_C_ID]);
        gTasks[taskIdA].data[TDA_TASK_C_ID] = 0;
    }

    if (gTasks[taskIdA].data[TDA_TASK_E_ID] != 0)
    {
        DestroyTask(gTasks[taskIdA].data[TDA_TASK_E_ID]);
        gTasks[taskIdA].data[TDA_TASK_E_ID] = 0;
    }

    if (gTasks[taskIdA].data[TDA_TASK_D_ID] != 0)
    {
        DestroyTask(gTasks[taskIdA].data[TDA_TASK_D_ID]);
        gTasks[taskIdA].data[TDA_TASK_D_ID] = 0;
    }

    gUnknown_0203BD28 = 1;
}

static void LoadTheEndScreen(u16 arg0, u16 arg1, u16 arg2)
{
    u16 baseTile;
    u16 i;

    LZ77UnCompVram(gCreditsCopyrightEnd_Gfx, (void *)(VRAM + arg0));
    LoadPalette(gIntroCopyright_Pal, arg2, sizeof(gIntroCopyright_Pal));

    baseTile = (arg2 / 16) << 12;

    for (i = 0; i < 32 * 32; i++)
        ((u16 *) (VRAM + arg1))[i] = baseTile + 1;
}

static u16 sub_8176D78(u8 arg0)
{
    u16 out = (arg0 & 0x3F) + 80;

    if (arg0 == 0xFF)
        return 1;

    if (arg0 & (1 << 7))
        out |= 1 << 11;
    if (arg0 & (1 << 6))
        out |= 1 << 10;

    return out;
}

static void sub_8176DBC(const u8 arg0[], u8 baseX, u8 baseY, u16 arg3, u16 palette)
{
    u8 y, x;
    const u16 tileOffset = (palette / 16) << 12;

    for (y = 0; y < 5; y++)
    {
        for (x = 0; x < 3; x++)
            ((u16 *) (VRAM + arg3 + (baseY + y) * 64))[baseX + x] = tileOffset + sub_8176D78(arg0[y * 3 + x]);
    }
}

static void sub_8176E40(u16 arg0, u16 palette)
{
    u16 pos;
    u16 baseTile = (palette / 16) << 12;

    for (pos = 0; pos < 32 * 32; pos++)
        ((u16 *) (VRAM + arg0))[pos] = baseTile + 1;

    sub_8176DBC(sTheEnd_LetterTMap, 3, 7, arg0, palette);
    sub_8176DBC(sTheEnd_LetterHMap, 7, 7, arg0, palette);
    sub_8176DBC(sTheEnd_LetterEMap, 11, 7, arg0, palette);
    sub_8176DBC(sTheEnd_LetterEMap, 16, 7, arg0, palette);
    sub_8176DBC(sTheEnd_LetterNMap, 20, 7, arg0, palette);
    sub_8176DBC(sTheEnd_LetterDMap, 24, 7, arg0, palette);
}

static void sub_8176EE8(struct Sprite *sprite)
{
    if (gUnknown_0203BD28 != 0)
    {
        DestroySprite(sprite);
        return;
    }

    switch (sprite->data[0])
    {
    case 0:
        StartSpriteAnimIfDifferent(sprite, 0);
        break;
    case 1:
        StartSpriteAnimIfDifferent(sprite, 1);
        if (sprite->pos1.x > -32)
            sprite->pos1.x -= 1;
        break;
    case 2:
        StartSpriteAnimIfDifferent(sprite, 2);
        break;
    case 3:
        StartSpriteAnimIfDifferent(sprite, 3);
        break;
    case 4:
        StartSpriteAnimIfDifferent(sprite, 0);
        if (sprite->pos1.x > 120)
            sprite->pos1.x -= 1;
        break;
    case 5:
        StartSpriteAnimIfDifferent(sprite, 0);
        if (sprite->pos1.x > -32)
            sprite->pos1.x -= 1;
        break;
    }
}

static void sub_8176F90(struct Sprite *sprite)
{
    if (gUnknown_0203BD28 != 0)
    {
        DestroySprite(sprite);
        return;
    }

    switch (sprite->data[0])
    {
    case 0:
        sprite->pos2.y = 0;
        StartSpriteAnimIfDifferent(sprite, 0);
        break;
    case 1:
        if (sprite->pos1.x > 200)
            StartSpriteAnimIfDifferent(sprite, 1);
        else
            StartSpriteAnimIfDifferent(sprite, 2);
        if (sprite->pos1.x > -32)
            sprite->pos1.x -= 2;
        sprite->pos2.y = -gUnknown_0203BD26;
        break;
    case 2:
        sprite->data[7] += 1;
        StartSpriteAnimIfDifferent(sprite, 0);
        if ((sprite->data[7] & 3) == 0)
            sprite->pos1.x += 1;
        break;
    case 3:
        StartSpriteAnimIfDifferent(sprite, 0);
        if (sprite->pos1.x > -32)
            sprite->pos1.x -= 1;
        break;
    }
}

static void sub_8177050(struct Sprite *sprite)
{
    if (gUnknown_0203BD28)
    {
        FreeAndDestroyMonPicSprite(sprite->data[6]);
        return;
    }

    sprite->data[7] += 1;
    switch (sprite->data[0])
    {
    case 0:
    default:
        sprite->oam.affineMode = 1;
        sprite->oam.matrixNum = sprite->data[1];
        sprite->data[2] = 16;
        SetOamMatrix(sprite->data[1], 0x10000 / sprite->data[2], 0, 0, 0x10000 / sprite->data[2]);
        sprite->invisible = FALSE;
        sprite->data[0] = 1;
        break;
    case 1:
        if (sprite->data[2] < 256)
        {
            sprite->data[2] += 8;
            SetOamMatrix(sprite->data[1], 0x10000 / sprite->data[2], 0, 0, 0x10000 / sprite->data[2]);
        }
        else
        {
            sprite->data[0] += 1;
        }
        switch (sprite->data[1])
        {
        case 1:
            if ((sprite->data[7] & 3) == 0)
                sprite->pos1.y += 1;
            sprite->pos1.x -= 2;
            break;
        case 2:
            break;
        case 3:
            if ((sprite->data[7] & 3) == 0)
                sprite->pos1.y += 1;
            sprite->pos1.x += 2;
            break;
        }
        break;
    case 2:
        if (sprite->data[3] != 0)
        {
            sprite->data[3] -= 1;
        }
        else
        {
            SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_BG0 | BLDCNT_TGT2_BG1 | BLDCNT_TGT2_BG2 | BLDCNT_TGT2_BG3);
            SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(16, 0));
            sprite->oam.objMode = 1;
            sprite->data[3] = 16;
            sprite->data[0] += 1;
        }
        break;
    case 3:
        if (sprite->data[3] != 0)
        {
            int data3;

            sprite->data[3] -= 1;

            data3 = 16 - sprite->data[3];
            SetGpuReg(REG_OFFSET_BLDALPHA, (data3 << 8) + sprite->data[3]);
        }
        else
        {
            sprite->invisible = TRUE;
            sprite->data[0] = 9;
        }
        break;
    case 9:
        sprite->data[0] += 1;
        break;
    case 10:
        SetGpuReg(REG_OFFSET_BLDCNT, 0);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        FreeAndDestroyMonPicSprite(sprite->data[6]);
        break;
    }
}

static u8 MakeMonSprite(u16 nationalDexNum, s16 x, s16 y, u16 position)
{
    u8 spriteId;
    u8 spriteId2;
    
    if (nationalDexNum > 0x1FFF) {
        spriteId = CreateTrainerPicSprite(nationalDexNum-0x1FFF, TRUE, x, y, position, 0xFFFF);
    } else {
        spriteId = CreateMonSpriteFromNationalDexNumber(nationalDexNum, x, y, position);
    }
    gSprites[spriteId].oam.priority = 1;
    gSprites[spriteId].data[1] = position + 1;
    gSprites[spriteId].invisible = TRUE;
    gSprites[spriteId].callback = sub_8177050;
    gSprites[spriteId].data[6] = spriteId;
    spriteId2 = CreateSprite(&gUnknown_085E7068, gSprites[spriteId].pos1.x, gSprites[spriteId].pos1.y, 1);
    gSprites[spriteId2].data[0] = spriteId;

    StartSpriteAnimIfDifferent(&gSprites[spriteId2], position);

    return spriteId;
}

static void sub_81772B8(struct Sprite *sprite)
{
    if (gSprites[sprite->data[0]].data[0] == 10 || gUnknown_0203BD28)
    {
        DestroySprite(sprite);
        return;
    }

    sprite->invisible = gSprites[sprite->data[0]].invisible;
    sprite->oam.objMode = gSprites[sprite->data[0]].oam.objMode;
    sprite->oam.affineMode = gSprites[sprite->data[0]].oam.affineMode;
    sprite->oam.matrixNum = gSprites[sprite->data[0]].oam.matrixNum;
    sprite->pos1.x = gSprites[sprite->data[0]].pos1.x;
    sprite->pos1.y = gSprites[sprite->data[0]].pos1.y;
}

#define TRAINER_PIC(pic) (TRAINER_PIC_##pic + 0x1FFF)

static void DeterminePokemonToShow(void)
{
    // TTH: Force "starter" pokemon to something
    u16 starter = SpeciesToNationalPokedexNum(SPECIES_HAUNTER);//GetStarterPokemon(VarGet(VAR_STARTER_MON)));
    u16 page;
    u16 dexNum;
    u16 j;
    
    GetSetPokedexFlag(NATIONAL_DEX_QUILAVA, FLAG_SET_SEEN);
    
    // Go through the Pokedex, and anything that has gotten caught we put into our massive array.
    // This basically packs all of the caught pokemon into the front of the array
    for (dexNum = 1, j = 0; dexNum < NATIONAL_DEX_COUNT; dexNum++)
    {
        if (GetSetPokedexFlag(dexNum, FLAG_GET_SEEN)) //TTH: use SEEN instead of CAUGHT, since we'll only ever catch 3 mon
        {
            sCreditsData->caughtPkmnIds[j] = dexNum;
            j++;
        }
    }
    
    // Fill the rest of the array with zeroes
    for (dexNum = j; dexNum < NATIONAL_DEX_COUNT; dexNum++)
        sCreditsData->caughtPkmnIds[dexNum] = 0;

    // Cap the number of pokemon we care about to 71, the max we show in the credits scene (-1 for the starter)
    sCreditsData->numCaughtPkmn = j;
    if (sCreditsData->numCaughtPkmn < 71)
        sCreditsData->numPkmnToShow = j;
    else
        sCreditsData->numPkmnToShow = 71;
    
    // Loop through our list of caught pokemon and select randomly from it to fill the images to show
    j = 0;
    do
    {
        // Select a random mon, insert into array
        page = Random() % sCreditsData->numCaughtPkmn;
        sCreditsData->pkmnToShow[j] = sCreditsData->caughtPkmnIds[page];

        // Remove the select mon from the array, and condense array entries
        j++;
        sCreditsData->caughtPkmnIds[page] = 0;
        sCreditsData->numCaughtPkmn--;
        if (page != sCreditsData->numCaughtPkmn) 
        {
            //instead of looping through and moving everything down, just take from the end. Order doesn't matter after all.
            sCreditsData->caughtPkmnIds[page] = sCreditsData->caughtPkmnIds[sCreditsData->numCaughtPkmn];
            sCreditsData->caughtPkmnIds[sCreditsData->numCaughtPkmn] = 0;
        }
    }
    while (sCreditsData->numCaughtPkmn != 0 && j < 71);

    // If we don't have enough pokemon in the dex to fill everything, copy the selected mon into the end of the array, to loop
    if (sCreditsData->numPkmnToShow < 71)
    {
        for (j = sCreditsData->numPkmnToShow, page = 0; j < 71; j++)
        {
            sCreditsData->pkmnToShow[j] = sCreditsData->pkmnToShow[page];

            page++;
            if (page == sCreditsData->numPkmnToShow)
                page = 0;
        }
        // Ensure the last pokemon is our starter
        sCreditsData->pkmnToShow[70] = starter;
    }
    else
    {
        // Check to see if our starter has already appeared in this list, break if it has
        for (dexNum = 0; sCreditsData->pkmnToShow[dexNum] != starter && dexNum < 71; dexNum++);

        // If it has, swap it with the last pokemon, to ensure our starter is the last image
        if (dexNum < sCreditsData->numPkmnToShow - 1)
        {
            sCreditsData->pkmnToShow[dexNum] = sCreditsData->pkmnToShow[70];
            sCreditsData->pkmnToShow[70] = starter;
        }
        else
        {
            // Ensure the last pokemon is our starter
            sCreditsData->pkmnToShow[70] = starter;
        }
    }
    sCreditsData->numPkmnToShow = 71;
    
    //TTH: Hardcoding showing some costumed trainers at the start
    sCreditsData->pkmnToShow[ 0] = TRAINER_PIC(AQUA_LEADER_ARCHIE);
    sCreditsData->pkmnToShow[ 1] = TRAINER_PIC(TARZAN);
    sCreditsData->pkmnToShow[ 2] = TRAINER_PIC(CORPSE_BRIDE);
    sCreditsData->pkmnToShow[ 3] = TRAINER_PIC(ALIEN);
    sCreditsData->pkmnToShow[ 4] = TRAINER_PIC(MASKED_BOY);
    sCreditsData->pkmnToShow[ 5] = TRAINER_PIC(GHETSIS);
    sCreditsData->pkmnToShow[ 6] = TRAINER_PIC(POKEMANIAC);
    sCreditsData->pkmnToShow[ 7] = TRAINER_PIC(PLASMA_KID);
    sCreditsData->pkmnToShow[ 8] = TRAINER_PIC(MERMAID);
    sCreditsData->pkmnToShow[ 9] = TRAINER_PIC(FROGGER);
    sCreditsData->pkmnToShow[10] = TRAINER_PIC(TWINS_PM);
    sCreditsData->pkmnToShow[11] = TRAINER_PIC(NINJA_BOY);
    sCreditsData->pkmnToShow[12] = TRAINER_PIC(FAIRY_GIRL);
    sCreditsData->pkmnToShow[13] = TRAINER_PIC(HERO_OF_TIME);
    sCreditsData->pkmnToShow[14] = TRAINER_PIC(YOUNGSTER);
    sCreditsData->pkmnToShow[15] = TRAINER_PIC(WALLY);
    sCreditsData->pkmnToShow[16] = TRAINER_PIC(BRENDAN);
    sCreditsData->pkmnToShow[17] = TRAINER_PIC(MAY);
}
