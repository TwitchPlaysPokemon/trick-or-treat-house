#include "global.h"
#include "menu.h"
#include "strings.h"
#include "string_util.h"
#include "palette.h"
#include "task.h"
#include "text.h"
#include "match_call.h"
#include "field_message_box.h"
#include "event_data.h"
#include "mgba.h"
#include "constants/rgb.h"

static EWRAM_DATA struct {
    u8 mode:3;
    u8 loaded:1;
} sFieldMessageBox = {0};

// static EWRAM_DATA u8 sFieldMessageBox.mode = 0;
EWRAM_DATA const u8* gSpeakerName = NULL;

extern const u8 CommonName_BRENDAN[];
extern const u8 CommonName_MAY[]; 
extern const u8 CommonName_ALEX[]; 
extern const u8 CommonName_JOEY[]; 
extern const u8 CommonName_JAMES[]; 
extern const u8 CommonName_IRENE[]; 
extern const u8 CommonName_WALLY[]; 

enum {
    SPEAKER_UNKNOWN,
    SPEAKER_BRENDAN,
    SPEAKER_MAY,
    SPEAKER_ALEX,
    SPEAKER_JOEY,
    SPEAKER_JAMES,
    SPEAKER_IRENE,
    SPEAKER_WALLY,
};

const u16 sSpeakerPalettes[][5] = {
    [SPEAKER_UNKNOWN] = { RGB(28,25,22), RGB_WHITE, RGB(23,10, 0), RGB(25,18, 0), RGB(25,16, 8), },
    [SPEAKER_BRENDAN] = { RGB(28,25,22), RGB_WHITE, RGB( 9,16,25), RGB(30,16, 3), RGB(10,22,28), },
    [SPEAKER_MAY]     = { RGB(28,25,22), RGB_WHITE, RGB(24, 8, 8), RGB(29,20, 8), RGB(28,17, 5), },
    [SPEAKER_ALEX]    = { RGB(28,25,22), RGB_WHITE, RGB(10,14, 7), RGB(18,22, 7), RGB(23,19, 7), },
    [SPEAKER_JOEY]    = { RGB(25,25,28), RGB_WHITE, RGB(11,17,23), RGB(25,20, 1), RGB(18,24,30), },
    [SPEAKER_JAMES]   = { RGB(18,22, 7), RGB_WHITE, RGB( 3,10, 4), RGB(10,21, 5), RGB(10,16, 6), },
    [SPEAKER_IRENE]   = { RGB(28,25,22), RGB_WHITE, RGB(26,10,16), RGB(31,17,20), RGB(26,13,15), },
    [SPEAKER_WALLY]   = { RGB(28,25,25), RGB_WHITE, RGB(11,17,23), RGB(26,26,26), RGB(18,24,30), },
};

static void ExpandStringAndStartDrawFieldMessage(const u8 *, bool32);
static void StartDrawFieldMessage(void);

void InitFieldMessageBox(void)
{
    sFieldMessageBox.mode = FIELD_MESSAGE_BOX_HIDDEN;
    sFieldMessageBox.loaded = FALSE;
    gTextFlags.canABSpeedUpPrint = FALSE;
    gTextFlags.useAlternateDownArrow = FALSE;
    gTextFlags.autoScroll = FALSE;
    gTextFlags.forceMidTextSpeed = FALSE;
}

extern const u16 gStandardMenuPalette[];
static void LoadPaletteForSpeaker()
{
    int idx = SPEAKER_UNKNOWN;
    if (gSpeakerName == NULL) {
        // LoadPalette(&gStandardMenuPalette[13], 0x0FB, 6);
        LoadPalette(sSpeakerPalettes[idx], 0x0FB, 5*2);
        return;
    }
    if (gSpeakerName == CommonName_BRENDAN) idx = SPEAKER_BRENDAN;
    if (gSpeakerName == CommonName_MAY) idx = SPEAKER_MAY;
    if (gSpeakerName == CommonName_ALEX) idx = SPEAKER_ALEX;
    if (gSpeakerName == CommonName_JOEY) idx = SPEAKER_JOEY;
    if (gSpeakerName == CommonName_JAMES) idx = SPEAKER_JAMES;
    if (gSpeakerName == CommonName_IRENE) idx = SPEAKER_IRENE;
    if (gSpeakerName == CommonName_WALLY) idx = SPEAKER_WALLY;
    LoadPalette(sSpeakerPalettes[idx], 0x0FB, 5*2);
}

#define tState data[0]

static void Task_DrawFieldMessage(u8 taskId)
{
    struct Task *task = &gTasks[taskId];

    switch (task->tState)
    {
        case 0:
            if (!sFieldMessageBox.loaded) {
                LoadMessageBoxAndBorderGfx();
                sFieldMessageBox.loaded = TRUE;
            }
            task->tState++;
            break;
        case 1:
            if (gSpeakerName != NULL && !FlagGet(FLAG_SUPPRESS_SPEAKER_NAME)) {
                LoadPaletteForSpeaker();
                // RunTextPrinters();
                DrawDialogueFrameWithFrame(0, TRUE);
                PutWindowTilemap(1);
                CopyWindowToVram(1, COPYWIN_FULL);
            }
            else {
                LoadPaletteForSpeaker();
                DrawDialogueFrame(0, TRUE);
            } 
            task->tState++;
            break;
        case 2:
            if (RunTextPrintersAndIsPrinter0Active() != TRUE)
            {
                sFieldMessageBox.mode = FIELD_MESSAGE_BOX_HIDDEN;
                DestroyTask(taskId);
            }
    }
}

#undef tState

static void CreateTask_DrawFieldMessage(void)
{
    CreateTask(Task_DrawFieldMessage, 0x50);
}

static void DestroyTask_DrawFieldMessage(void)
{
    u8 taskId = FindTaskIdByFunc(Task_DrawFieldMessage);
    if (taskId != TASK_NONE) {
        DestroyTask(taskId);
        sFieldMessageBox.loaded = FALSE;
    }
}

bool8 ShowFieldMessage(const u8 *str)
{
    if (sFieldMessageBox.mode != FIELD_MESSAGE_BOX_HIDDEN)
        return FALSE;
    ExpandStringAndStartDrawFieldMessage(str, TRUE);
    sFieldMessageBox.mode = FIELD_MESSAGE_BOX_NORMAL;
    return TRUE;
}

static void Task_HidePokenavMessageWhenDone(u8 taskId)
{
    if (!IsMatchCallTaskActive())
    {
        sFieldMessageBox.mode = FIELD_MESSAGE_BOX_HIDDEN;
        DestroyTask(taskId);
        sFieldMessageBox.loaded = FALSE;
    }
}

bool8 ShowPokenavFieldMessage(const u8 *str)
{
    if (sFieldMessageBox.mode != FIELD_MESSAGE_BOX_HIDDEN)
        return FALSE;
    StringExpandPlaceholders(gStringBuffer, str);
    CreateTask(Task_HidePokenavMessageWhenDone, 0);
    StartMatchCallFromScript(str);
    sFieldMessageBox.mode = 2;
    return TRUE;
}

bool8 ShowFieldAutoScrollMessage(const u8 *str)
{
    if (sFieldMessageBox.mode != FIELD_MESSAGE_BOX_HIDDEN)
        return FALSE;
    sFieldMessageBox.mode = FIELD_MESSAGE_BOX_AUTO_SCROLL;
    ExpandStringAndStartDrawFieldMessage(str, FALSE);
    return TRUE;
}

// Unused
static bool8 ForceShowFieldAutoScrollMessage(const u8 *str)
{
    sFieldMessageBox.mode = FIELD_MESSAGE_BOX_AUTO_SCROLL;
    ExpandStringAndStartDrawFieldMessage(str, TRUE);
    return TRUE;
}

// Same as ShowFieldMessage, but instead of accepting a
// string arg it just prints whats already in gStringBuffer
bool8 ShowFieldMessageFromBuffer(void)
{
    if (sFieldMessageBox.mode != FIELD_MESSAGE_BOX_HIDDEN)
        return FALSE;
    sFieldMessageBox.mode = FIELD_MESSAGE_BOX_NORMAL;
    StartDrawFieldMessage();
    return TRUE;
}

extern void FillDialogFramePlate();
extern int GetDialogFramePlateWidth();
static void ExpandStringAndStartDrawFieldMessage(const u8 *str, bool32 allowSkippingDelayWithButtonPress)
{
    if (FlagGet(FLAG_SYS_BORT_MODE)) gSpeakerName = NULL; // Don't show names in BORT mode
    if (gSpeakerName != NULL && !FlagGet(FLAG_SUPPRESS_SPEAKER_NAME)) {
        // mgba_printf(MGBA_LOG_INFO, "DRAWING SPEAKER NAME: ");
        // mgba_printEncoded(MGBA_LOG_INFO, gSpeakerName);
        int strLen = GetStringWidth(FONT_SMALL, gSpeakerName, -1);
        if (strLen > 0) {
            strLen = GetDialogFramePlateWidth()/2 - strLen/2;
            gNamePlateBuffer[0] = EXT_CTRL_CODE_BEGIN;
            gNamePlateBuffer[1] = EXT_CTRL_CODE_CLEAR_TO;
            gNamePlateBuffer[2] = strLen;
            StringExpandPlaceholders(&gNamePlateBuffer[3], gSpeakerName);
        } else {
            StringExpandPlaceholders(&gNamePlateBuffer[0], gSpeakerName);
        }
        FillDialogFramePlate();
        LoadPaletteForSpeaker();
        AddTextPrinterParameterized2(1, FONT_SMALL, gNamePlateBuffer, 0, NULL, 1, 0, 2);
        PutWindowTilemap(1);
        CopyWindowToVram(1, COPYWIN_FULL);
    }
    StringExpandPlaceholders(gStringBuffer, str);
    AddTextPrinterForMessage(allowSkippingDelayWithButtonPress);
    CreateTask_DrawFieldMessage();
}

static void StartDrawFieldMessage(void)
{
    AddTextPrinterForMessage(TRUE);
    CreateTask_DrawFieldMessage();
}

void HideFieldMessageBox(void)
{
    DestroyTask_DrawFieldMessage();
    ClearDialogWindowAndFrame(0, TRUE);
    sFieldMessageBox.mode = FIELD_MESSAGE_BOX_HIDDEN;
    gSpeakerName = NULL;
}

u8 GetFieldMessageBoxMode(void)
{
    return sFieldMessageBox.mode;
}

bool8 IsFieldMessageBoxHidden(void)
{
    if (sFieldMessageBox.mode == FIELD_MESSAGE_BOX_HIDDEN)
        return TRUE;
    return FALSE;
}

// Unused
static void ReplaceFieldMessageWithFrame(void)
{
    DestroyTask_DrawFieldMessage();
    DrawStdWindowFrame(0, TRUE);
    sFieldMessageBox.mode = FIELD_MESSAGE_BOX_HIDDEN;
}

void StopFieldMessage(void)
{
    DestroyTask_DrawFieldMessage();
    sFieldMessageBox.mode = FIELD_MESSAGE_BOX_HIDDEN;
}

void SetSpeakerName(const u8* name)
{
    gSpeakerName = name;
}
