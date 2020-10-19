#include "global.h"
#include "palette.h"
#include "main.h"
#include "alloc.h"
#include "bg.h"
#include "decompress.h"
#include "event_data.h"
#include "gpu_regs.h"
#include "graphics.h"
#include "event_object_movement.h"
#include "international_string_util.h"
#include "intro_credits_graphics.h"
#include "m4a.h"
#include "menu.h"
#include "pokedex.h"
#include "random.h"
#include "sound.h"
#include "sprite.h"
#include "starter_choose.h"
#include "string_util.h"
#include "task.h"
#include "text.h"
#include "trainer_pokemon_sprites.h"
#include "trig.h"
#include "window.h"
#include "constants/rgb.h"
#include "constants/songs.h"
#include "constants/species.h"
#include "constants/trainers.h"
#include "constants/vars.h"
#include "constants/event_objects.h"


///////////////////////////////////////////////////////////////////////////////

#define PLAYER_SPEED       1
#define ITEM_SPEED         2
#define NUM_CANDY_SPRITES  6

#define SPRITE_OFFSET_PLAYER_X   32
#define SPRITE_OFFSET_PLAYER_Y   46
#define SPRITE_OFFSET_ITEM_X     0
#define SPRITE_OFFSET_ITEM_Y     64
#define PLAY_AREA_MIN_Y    0
#define PLAY_AREA_MAX_Y    (PLAY_AREA_MIN_Y+30)
#define PLAY_AREA_MIN_X    8
#define PLAY_AREA_MAX_X    (PLAY_AREA_MIN_X+160)

// Frame Counts: 
//   725 = End of Opening Measures
//  2100 = End of First Phrase
//  3660 = End of Second Phrase
//  5100 = End of Third Phrase
//  6500 = End of Fourth Phrase
//  8090 = End of Fifth Phrase
//  9500 = End of Sixth Phrase
// 12480 = Start of Ending Phrase
// 15192 = Start of Pokemon Leitmotif
#define FRAMETIME_LEITMOTIF    15192
// 15570 = Start of Denouement
#define FRAMETIME_DENOUEMENT   15570
// 16300 = Final Note
#define FRAMETIME_FINAL_NOTE   16300
// 16500 = End of Song
#define FRAMETIME_SONG_OVER    16500


#define COLOR_GRASS               RGB(23, 18, 9)
#define CREDITS_START_DELAY       72
// #define CREDITS_DISPLAY_TIME   170
#define CREDITS_DISPLAY_TIME      (((FRAMETIME_DENOUEMENT - CREDITS_START_DELAY)/ARRAY_COUNT(gCreditsEntryPointerTable))-45)


#define WIN_MAIN   0
#define WIN_SCORE  1


extern void LoadCreditsMinigameBackground1();

void LoadCandyGraphics();

enum
{
	// Task A: Display Credits
	TDA_STATE = 0,
	TDA_DISPLAY_TIMER,
	TDA_CURR_PAGE,
	
	// Task B: Move Cyclist
	TDB_STATE = 0,
	TDB_PLAYER_CYCLIST,
    TDB_NEXT_ITEM_ID,
	TDB_TIMEOUT,
	TDB_FRAME_COUNT,
	
	// Task C: Animate Background
	TDC_0 = 0,
	
	// Task E: Flicker Background Palette
	
	// Sprite Data
	SPD_CURR_ANIM = 0,
	SPD_DESTX,
	SPD_DESTY,
    
    SPI_ITEM_STATE = 0,
    SPI_PAL_ID,
    SPI_TILE_ID,
    
    ITEM_STATE_DISABLED = 0,
    ITEM_STATE_SPAWNED,
};
struct CreditsData
{
	u16 taskIdA;
	u16 taskIdB;
	u16 taskIdC;
	u16 taskIdD;
	u16 taskIdE;
	u8 itemSprites[NUM_CANDY_SPRITES];
};
struct CreditsEntry
{
    u8 var_0;
    bool8 isTitle;
    const u8 *text;
};

EWRAM_DATA bool8 gHasHallOfFameRecords = 0;
static EWRAM_DATA struct CreditsData *sCreditsData = {0};

static const u16 sCreditsPalettes[][16] =
{
    INCBIN_U16("graphics/credits/credits_1.gbapal"),
    INCBIN_U16("graphics/credits/credits_2.gbapal"),
    INCBIN_U16("graphics/credits/credits_3.gbapal"),
    INCBIN_U16("graphics/credits/credits_4.gbapal"),
};

static const u32 gCreditsCopyrightEnd_Gfx[] = INCBIN_U32("graphics/credits/the_end_copyright.4bpp.lz");

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
    {
        .bg = 0,
        .tilemapLeft = 0,
        .tilemapTop = 0,
        .width = 16,
        .height = 2,
        .paletteNum = 9,
        .baseBlock = 512
    },
    DUMMY_WIN_TEMPLATE,
};

static const union AnimCmd gUnknown_085E6F84[] =
{
    ANIMCMD_FRAME(0, 6),
    ANIMCMD_FRAME(64, 6),
    ANIMCMD_FRAME(128, 6),
    ANIMCMD_FRAME(192, 6),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd gUnknown_085E6F8H[] =
{
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_FRAME(64, 8),
    ANIMCMD_FRAME(128, 8),
    ANIMCMD_FRAME(192, 8),
	ANIMCMD_LOOP(8),
    ANIMCMD_FRAME(0, 80),
    ANIMCMD_FRAME(0, 80),
	ANIMCMD_LOOP(8),
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
static const union AnimCmd gUnknown_085E6F9i[] =
{
    ANIMCMD_FRAME(0, 8),
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
	gUnknown_085E6F8H,
	gUnknown_085E6F9i,
    gUnknown_085E6F98,
    gUnknown_085E6FAC,
    gUnknown_085E6FBC,
};

///////////////////////////////////////////////////////////////////////////////

static void Task_WaitPaletteFade(u8 taskIdA);
static void Task_WaitStartGame(u8 taskIdA);
static void Task_DisplayCredits(u8 taskIdB);
static void Task_FlickerPalette(u8 taskId);
static void Task_PlayGame(u8 taskId);

///////////////////////////////////////////////////////////////////////////////
// Helper Functions

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

static void SpriteCB_Player(struct Sprite *sprite)
{
	StartSpriteAnimIfDifferent(sprite, sprite->data[SPD_CURR_ANIM]);
    
	if (sprite->pos1.x > sprite->data[SPD_DESTX])
	{
		sprite->pos1.x -= PLAYER_SPEED;
	}
	else if (sprite->pos1.x < sprite->data[SPD_DESTX])
	{
		sprite->pos1.x += PLAYER_SPEED;
	}
	if (sprite->pos1.y > sprite->data[SPD_DESTY])
	{
		sprite->pos1.y -= PLAYER_SPEED;
	}
	else if (sprite->pos1.y < sprite->data[SPD_DESTY])
	{
		sprite->pos1.y += PLAYER_SPEED;
	}
}

static void SpriteCB_CandyItem(struct Sprite *sprite)
{
    switch (sprite->data[SPI_ITEM_STATE]) {
        case ITEM_STATE_DISABLED:
            break;
        case ITEM_STATE_SPAWNED:
            sprite->pos1.x += ITEM_SPEED;
            if (sprite->pos1.x > DISPLAY_WIDTH+16) {
                sprite->data[SPI_ITEM_STATE] = ITEM_STATE_DISABLED;
                break;
            }
            break;
    }
}

static bool8 LoadInitialBikingScene(u8 taskId)
{
	u8 spriteId;

    switch (gMain.state)
    {
    default:
    case 0:
		// Reset everything
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
		// Load Background elements
		gSkyBgPanY = 24; //34;
        gSkyBgPanYAdjust = 10;
		LoadCreditsMinigameBackground1();
        gMain.state += 1;
        break;
    case 2:
		// Load player character
        switch (gSaveBlock2Ptr->playerGender) {
            default:
            case GENDER_M:
                LoadCompressedSpriteSheet(gIntro2BrendanExtendedSpriteSheet);
                // LoadCompressedSpriteSheet(gIntro2MaySpriteSheet);
                LoadCompressedSpriteSheet(gIntro2BikeSpriteSheet);
                LoadSpritePalettes(gIntroBikeAndFlygonPalette);

                spriteId = intro_create_brendan_sprite(120, 46);
                gTasks[taskId].data[TDB_PLAYER_CYCLIST] = spriteId;
                gSprites[spriteId].callback = SpriteCB_Player;
                gSprites[spriteId].anims = gUnknown_085E6FD0;
                break;
            case GENDER_F:
                LoadCompressedSpriteSheet(gIntro2MayExtendedSpriteSheet);
                // LoadCompressedSpriteSheet(gIntro2BrendanSpriteSheet);
                LoadCompressedSpriteSheet(gIntro2BikeSpriteSheet);
                LoadSpritePalettes(gIntroBikeAndFlygonPalette);

                spriteId = intro_create_may_sprite(120, 46);
                gTasks[taskId].data[TDB_PLAYER_CYCLIST] = spriteId;
                gSprites[spriteId].callback = SpriteCB_Player;
                gSprites[spriteId].anims = gUnknown_085E6FD0;
                break;
            case GENDER_N:
                LoadCompressedSpriteSheet(gIntro2TreekidExtendedSpriteSheet);
                // LoadCompressedSpriteSheet(gIntro2TreekidSpriteSheet);
                LoadCompressedSpriteSheet(gIntro2BikeSpriteSheet);
                LoadSpritePalettes(gIntroBikeAndFlygonPalette);

                spriteId = intro_create_treekid_sprite(120, 46);
                gTasks[taskId].data[TDB_PLAYER_CYCLIST] = spriteId;
                gSprites[spriteId].callback = SpriteCB_Player;
                gSprites[spriteId].anims = gUnknown_085E6FD0;
                break;
        }
        gMain.state += 1;
        break;
    case 3:
        LoadCandyGraphics();
        gMain.state += 1;
        break;
    case 4:
		gSprites[gTasks[taskId].data[TDB_PLAYER_CYCLIST]].invisible = FALSE;
		gSprites[gTasks[taskId].data[TDB_PLAYER_CYCLIST]].pos1.x = 240;
		gSprites[gTasks[taskId].data[TDB_PLAYER_CYCLIST]].pos1.y = 0;
		gSprites[gTasks[taskId].data[TDB_PLAYER_CYCLIST]].pos2.x = SPRITE_OFFSET_PLAYER_X;
		gSprites[gTasks[taskId].data[TDB_PLAYER_CYCLIST]].pos2.y = SPRITE_OFFSET_PLAYER_Y;
		gSprites[gTasks[taskId].data[TDB_PLAYER_CYCLIST]].data[SPD_CURR_ANIM] = 0;
		gSprites[gTasks[taskId].data[TDB_PLAYER_CYCLIST]].data[SPD_DESTX] = 240;
		gSprites[gTasks[taskId].data[TDB_PLAYER_CYCLIST]].data[SPD_DESTY] = 0;
        
        
        SetGpuRegistersForBikeScene(0);
        gMain.state = 0;
        return TRUE;
    }
    return FALSE;
}

extern void MakeObjectTemplateFromEventObjectGraphicsInfo(u16 graphicsId, void (*callback)(struct Sprite *), struct SpriteTemplate *spriteTemplate, const struct SubspriteTable **subspriteTables);

// This is a copy and modification of AddPseudoEventObject
void LoadCandyGraphics()
{
    struct SpriteTemplate *spriteTemplate;
    const struct SubspriteTable *subspriteTables;
    struct Sprite *sprite;
    u8 spriteId, i;
    
    spriteTemplate = malloc(sizeof(struct SpriteTemplate));
    MakeObjectTemplateFromEventObjectGraphicsInfo(EVENT_OBJ_GFX_ITEM_BALL, SpriteCB_CandyItem, spriteTemplate, &subspriteTables);
    if (spriteTemplate->paletteTag != 0xFFFF)
    {
        LoadEventObjectPalette(spriteTemplate->paletteTag);
    }
    for (i = 0; i < NUM_CANDY_SPRITES; i++) {
        spriteId = CreateSprite(spriteTemplate, 0, 0, 6);
        if (spriteId == MAX_SPRITES) break;
        sCreditsData->itemSprites[i] = spriteId;
        
        sprite = &gSprites[spriteId];
        sprite->pos1.x = -32;
        sprite->pos1.y = 0;
        sprite->pos2.x = SPRITE_OFFSET_ITEM_X;
        sprite->pos2.y = SPRITE_OFFSET_ITEM_Y;
        sprite->oam.priority = 1;
        // With the below, we won't need the sprite template, which will be freed at the end of this funciton
        sprite->data[SPI_PAL_ID] = spriteTemplate->paletteTag;
        sprite->data[SPI_TILE_ID] = spriteTemplate->tileTag;
        
        if (subspriteTables != NULL)
        {
            SetSubspriteTables(sprite, subspriteTables);
            sprite->subspriteMode = 2;
        }
    }
    free(spriteTemplate);
}


///////////////////////////////////////////////////////////////////////////////

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
    BuildOamBuffer();
    UpdatePaletteFade();
}

static void PrepareCreditsGraphics(void)
{
    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, sBackgroundTemplates, 1);
    SetBgTilemapBuffer(0, AllocZeroed(0x800));
    LoadPalette(sCreditsPalettes, 0x80, 0x40);
    InitWindows(sWindowTemplates);
    DeactivateAllTextPrinters();
    PutWindowTilemap(WIN_MAIN);
    PutWindowTilemap(WIN_SCORE);
    CopyWindowToVram(WIN_MAIN, 3);
    CopyWindowToVram(WIN_SCORE, 3);
    ShowBg(0);
}
static void CleanupCreditsGraphics(void)
{
    void *ptr;
    FreeAllWindowBuffers();
    ptr = GetBgTilemapBuffer(0);
    if (ptr)
        Free(ptr);
}

///////////////////////////////////////////////////////////////////////////////

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
    AddTextPrinterParameterized4(WIN_MAIN, 1, x, y, 1, 0, color, -1, string);
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
    AddTextPrinterParameterized4(WIN_MAIN, 1, x, y, 1, 0, color, -1, string);
}
#endif

static void PrintScore(const u32 score)
{
    u8 color[] = {0, 2, 1};
    ConvertUIntToDecimalStringN(gStringVar4, score, STR_CONV_MODE_RIGHT_ALIGN, 6);
	FillWindowPixelBuffer(WIN_SCORE, PIXEL_FILL(0));
    AddTextPrinterParameterized4(WIN_SCORE, 1, 10, 0, 1, 0, color, -1, gStringVar4);
	CopyWindowToVram(WIN_SCORE, 2);
}

static void PrintScoreStringVar4()
{
    u8 color[] = {0, 2, 1};
	FillWindowPixelBuffer(WIN_SCORE, PIXEL_FILL(0));
    AddTextPrinterParameterized4(WIN_SCORE, 1, 10, 0, 1, 0, color, -1, gStringVar4);
	CopyWindowToVram(WIN_SCORE, 2);
}

///////////////////////////////////////////////////////////////////////////////

void CB2_StartCreditsSequence(void)
{
	u8 taskIdA, taskIdB;
	
	ResetGpuAndVram();
	SetVBlankCallback(NULL);
	InitHeap(gHeap, HEAP_SIZE);
	ResetPaletteFade();
	ResetTasks();
	
	PrepareCreditsGraphics();
	sCreditsData = AllocZeroed(sizeof(struct CreditsData));
	sCreditsData->taskIdA = CreateTask(Task_DisplayCredits, 0);
	sCreditsData->taskIdB = CreateTask(Task_WaitPaletteFade, 0);
		
    while (TRUE)
    {
        if (LoadInitialBikingScene(sCreditsData->taskIdB))
            break;
    }
	
	sCreditsData->taskIdC = CreateBikeBackgroundAnimationTask(0, 0x2000, 0x20, 8);
	sCreditsData->taskIdD = CreateTask(Task_FlickerPalette, 0);
	
	BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, RGB_BLACK);
	EnableInterrupts(INTR_FLAG_VBLANK);
	SetVBlankCallback(CreditsVBlankCallback);
	m4aSongNumStart(MUS_THANKFOR);
	SetMainCallback2(CB2_RunCreditsSequence);
}

///////////////////////////////////////////////////////////////////////////////
// Task A: Credits Tasks

static void Task_DisplayCredits(u8 taskId)
{
	// u32 frameCount = gTasks[taskIdB].data[0] | (gTasks[taskIdB].data[1] << 16);
	// frameCount++;
	
	// ConvertUIntToDecimalStringN(gStringVar4, frameCount, STR_CONV_MODE_RIGHT_ALIGN, 6);
	// FillWindowPixelBuffer(0, PIXEL_FILL(0));
	// PrintCreditsText(gStringVar4, 5, FALSE);
	// CopyWindowToVram(0, 2);
	
	// gTasks[taskIdB].data[0] = (frameCount & 0x0000FFFF) >>  0; 
	// gTasks[taskIdB].data[1] = (frameCount & 0xFFFF0000) >> 16; 
	
	int i;
	switch (gTasks[taskId].data[TDA_STATE])
	{
	default:
		if (!gPaletteFade.active)
		{
			gTasks[taskId].data[TDA_STATE] = 1;
			gTasks[taskId].data[TDA_DISPLAY_TIMER] = CREDITS_START_DELAY;
		}
		return;
	case 1: // Wait time before first credits
		if (gTasks[taskId].data[TDA_DISPLAY_TIMER] != 0)
		{
			gTasks[taskId].data[TDA_DISPLAY_TIMER] -= 1;
			return;
		}
		gTasks[taskId].data[TDA_STATE] += 1;
		return;
	case 2: // Display next credits
		if (gTasks[taskId].data[TDA_CURR_PAGE] < ARRAY_COUNT(gCreditsEntryPointerTable))
		{
#ifndef MULTI_COLUMN_MODE
			for (i = 0; i < 5; i++) {
				PrintCreditsText(
					gCreditsEntryPointerTable[gTasks[taskId].data[TDA_CURR_PAGE]][i]->text, 
					5 + i * 16, 
					gCreditsEntryPointerTable[gTasks[taskId].data[TDA_CURR_PAGE]][i]->isTitle);
			}
#else
			int card = gTasks[taskId].data[TDA_CURR_PAGE];
			for (i = 0; i < 5; i++) {
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
			CopyWindowToVram(WIN_MAIN, 2);

			gTasks[taskId].data[TDA_CURR_PAGE] += 1;
			gTasks[taskId].data[TDA_STATE] += 1;
			
			BeginNormalPaletteFade(0x00000100, 0, 16, 0, COLOR_GRASS);
			return;
		} 
		else 
		{
			ConvertUIntToDecimalStringN(gStringVar4, gTasks[taskId].data[TDA_CURR_PAGE], STR_CONV_MODE_RIGHT_ALIGN, 3);
			FillWindowPixelBuffer(WIN_MAIN, PIXEL_FILL(0));
			PrintCreditsText(gStringVar4, 5, FALSE);
			CopyWindowToVram(WIN_MAIN, 2);
			gTasks[taskId].data[TDA_CURR_PAGE] += 1;
			gTasks[taskId].data[TDA_STATE] += 1;
			BeginNormalPaletteFade(0x00000100, 0, 16, 0, COLOR_GRASS);
			return;
		}
		// If the current page is past the page count
		gTasks[taskId].data[TDA_STATE] = 10;
		return;
	case 3:
        if (!gPaletteFade.active)
        {
            gTasks[taskId].data[TDA_DISPLAY_TIMER] = CREDITS_DISPLAY_TIME;
            gTasks[taskId].data[TDA_STATE] += 1;
        }
        return;
	case 4:
        if (gTasks[taskId].data[TDA_DISPLAY_TIMER] != 0)
        {
            gTasks[taskId].data[TDA_DISPLAY_TIMER] -= 1;
            return;
        }
		gTasks[taskId].data[TDA_STATE] += 1;
		BeginNormalPaletteFade(0x00000100, 0, 0, 16, COLOR_GRASS);
		return;
	case 5:
        if (!gPaletteFade.active)
        {
            FillWindowPixelBuffer(WIN_MAIN, PIXEL_FILL(0));
            CopyWindowToVram(WIN_MAIN, 2);
            gTasks[taskId].data[TDA_STATE] = 2;
        }
        return;
	case 10:
        // gTasks[gTasks[taskIdB].data[TDB_TASK_A_ID]].data[TDA_4] = 1;
        // DestroyTask(taskId);
        // sub_81755A4();
        // FREE_AND_SET_NULL(sCreditsData);
        return;
	}
	
}

///////////////////////////////////////////////////////////////////////////////
// Task B: Biking Tasks

static void Task_WaitPaletteFade(u8 taskId)
{
    gTasks[taskId].data[TDB_FRAME_COUNT]++;
    if (!gPaletteFade.active)
	{
        gTasks[taskId].func = Task_WaitStartGame;
		gTasks[taskId].data[TDB_TIMEOUT] = CREDITS_START_DELAY*2;
	}
}

static void Task_WaitStartGame(u8 taskId)
{
    gTasks[taskId].data[TDB_FRAME_COUNT]++;
	if (gTasks[taskId].data[TDB_TIMEOUT] != 0)
	{
		gTasks[taskId].data[TDB_TIMEOUT] -= 1;
		return;
	}
	gSprites[gTasks[taskId].data[TDB_PLAYER_CYCLIST]].data[SPD_DESTX] = 120 - SPRITE_OFFSET_PLAYER_X;
	gTasks[taskId].func = Task_PlayGame;
}

static void Task_PlayGame(u8 taskId)
{
    struct Sprite *sprite;
    u8 i, l, r, t, b;
    u16 *itemId = &gTasks[taskId].data[TDB_NEXT_ITEM_ID];
	u16 frameCount = gTasks[taskId].data[TDB_FRAME_COUNT]++;
    
    PrintScore(frameCount);
    
    if (frameCount % 100 == 0) {
        sprite = &gSprites[sCreditsData->itemSprites[*itemId]];
        sprite->pos1.x = -32;
        sprite->pos1.y = PLAY_AREA_MIN_Y;
        sprite->data[SPI_ITEM_STATE] = ITEM_STATE_SPAWNED;
        *itemId = (*itemId + 1) % NUM_CANDY_SPRITES;
    }
	
	sprite = &gSprites[gTasks[taskId].data[TDB_PLAYER_CYCLIST]];
	if (gMain.heldKeys & DPAD_RIGHT) {
		sprite->data[SPD_CURR_ANIM] = 2;
		sprite->data[SPD_DESTX] = min(sprite->data[SPD_DESTX]+1, PLAY_AREA_MAX_X);
	}
	else if (gMain.heldKeys & DPAD_LEFT) {
		sprite->data[SPD_CURR_ANIM] = 0;
		sprite->data[SPD_DESTX] = max(sprite->data[SPD_DESTX]-1, PLAY_AREA_MIN_X);
	}
	else {
		sprite->data[SPD_CURR_ANIM] = 1;
	}
	if (gMain.heldKeys & DPAD_UP) {
		sprite->data[SPD_DESTY] = max(sprite->data[SPD_DESTY]-1, PLAY_AREA_MIN_Y);
	}
	else if (gMain.heldKeys & DPAD_DOWN) {
		sprite->data[SPD_DESTY] = min(sprite->data[SPD_DESTY]+1, PLAY_AREA_MAX_Y);
	}
    l = sprite->pos1.x + 4;
    r = sprite->pos1.x + 38;
    t = sprite->pos1.y - 8;
    b = sprite->pos1.y + 16;
    
    // Check collisions
    for (i = 0; i < NUM_CANDY_SPRITES; i++) {
        sprite = &gSprites[sCreditsData->itemSprites[i]];
        if (sprite->pos1.x < l) continue;
        if (sprite->pos1.x > r) continue;
        if (sprite->pos1.y < t) continue;
        if (sprite->pos1.y > b) continue;
        sprite->data[SPI_ITEM_STATE] = ITEM_STATE_DISABLED;
    }
}

///////////////////////////////////////////////////////////////////////////////
// Task C: Animate Background

///////////////////////////////////////////////////////////////////////////////
// Task D: Flicker Background Palette

static void Task_FlickerPalette(u8 taskId)
{
	Intro2FlickerPalette(0);
}



