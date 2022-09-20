#include "global.h"
#include "string_util.h"
#include "event_data.h"
#include "text.h"
#include "script.h"
#include "trickhouse.h"
#include "overworld.h"
#include "constants/map_groups.h"
#include "constants/maps.h"
#include "constants/map_scripts.h"
#include "constants/vars.h"
#include "strings.h"

EWRAM_DATA u8 gStringVar1[0x100] = {0};
EWRAM_DATA u8 gStringVar2[0x100] = {0};
EWRAM_DATA u8 gStringVar3[0x100] = {0};
EWRAM_DATA u8 gStringVar4[0x100] = {0};
EWRAM_DATA u8 gStringVar5[0x100] = {0};
EWRAM_DATA u8 gStringVar6[0x100] = {0};
EWRAM_DATA u8 gStringBuffer[0x3E8] = {0};

EWRAM_DATA u8 gStringWorking[0x100] = {0};

static const u8 sDigits[] = __("0123456789ABCDEF");

static const s32 sPowersOfTen[] =
{
             1,
            10,
           100,
          1000,
         10000,
        100000,
       1000000,
      10000000,
     100000000,
    1000000000,
};

u8 *StringCopy_Nickname(u8 *dest, const u8 *src)
{
    u8 i;
    u32 limit = POKEMON_NAME_LENGTH;

    for (i = 0; i < limit; i++)
    {
        dest[i] = src[i];

        if (dest[i] == EOS)
            return &dest[i];
    }

    dest[i] = EOS;
    return &dest[i];
}

u8 *StringGet_Nickname(u8 *str)
{
    u8 i;
    u32 limit = POKEMON_NAME_LENGTH;

    for (i = 0; i < limit; i++)
        if (str[i] == EOS)
            return &str[i];

    str[i] = EOS;
    return &str[i];
}

u8 *StringCopy_PlayerName(u8 *dest, const u8 *src)
{
    s32 i;
    s32 limit = PLAYER_NAME_LENGTH;

    for (i = 0; i < limit; i++)
    {
        dest[i] = src[i];

        if (dest[i] == EOS)
            return &dest[i];
    }

    dest[i] = EOS;
    return &dest[i];
}

u8 *StringCopy(u8 *dest, const u8 *src)
{
    while (*src != EOS)
    {
        *dest = *src;
        dest++;
        src++;
    }

    *dest = EOS;
    return dest;
}

u8 *StringAppend(u8 *dest, const u8 *src)
{
    while (*dest != EOS)
        dest++;

    return StringCopy(dest, src);
}

u8 *StringCopyN(u8 *dest, const u8 *src, u8 n)
{
    u16 i;

    for (i = 0; i < n; i++)
        dest[i] = src[i];

    return &dest[n];
}

u8 *StringAppendN(u8 *dest, const u8 *src, u8 n)
{
    while (*dest != EOS)
        dest++;

    return StringCopyN(dest, src, n);
}

u16 StringLength(const u8 *str)
{
    u16 length = 0;

    while (str[length] != EOS)
        length++;

    return length;
}

s32 StringCompare(const u8 *str1, const u8 *str2)
{
    while (*str1 == *str2)
    {
        if (*str1 == EOS)
            return 0;
        str1++;
        str2++;
    }

    return *str1 - *str2;
}

s32 StringCompareN(const u8 *str1, const u8 *str2, u32 n)
{
    while (*str1 == *str2)
    {
        if (*str1 == EOS)
            return 0;
        str1++;
        str2++;
        if (--n == 0)
            return 0;
    }

    return *str1 - *str2;
}

bool8 IsStringLengthAtLeast(const u8 *str, s32 n)
{
    u8 i;

    for (i = 0; i < n; i++)
        if (str[i] && str[i] != EOS)
            return TRUE;

    return FALSE;
}

extern const u8 gText_The[];
extern const u8 gText_Num1[];
extern const u8 gText_Num2[];
extern const u8 gText_Num3[];
extern const u8 gText_Num4[];
extern const u8 gText_Num5[];
u8 *ConvertIntToTheNameStringN(u8 *dest, s32 value, enum StringConvertMode mode, u8 n)
{
    switch (value) {
        case 1: return StringCopy(dest, gText_The);
        default: return ConvertIntToNameStringN(dest, value, mode, n);
    }
}

u8 *ConvertIntToNameStringN(u8 *dest, s32 value, enum StringConvertMode mode, u8 n)
{
    switch (value) {
        case 1: return StringCopy(dest, gText_Num1);
        case 2: return StringCopy(dest, gText_Num2);
        case 3: return StringCopy(dest, gText_Num3);
        case 4: return StringCopy(dest, gText_Num4);
        case 5: return StringCopy(dest, gText_Num5);
        default: return ConvertIntToDecimalStringN(dest, value, mode, n);
    }
}

u8 *ConvertIntToDecimalStringN(u8 *dest, s32 value, enum StringConvertMode mode, u8 n)
{
    enum { WAITING_FOR_NONZERO_DIGIT, WRITING_DIGITS, WRITING_SPACES } state;
    s32 powerOfTen;
    s32 largestPowerOfTen = sPowersOfTen[n - 1];

    state = WAITING_FOR_NONZERO_DIGIT;

    if (mode == STR_CONV_MODE_RIGHT_ALIGN)
        state = WRITING_SPACES;

    if (mode == STR_CONV_MODE_LEADING_ZEROS)
        state = WRITING_DIGITS;

    for (powerOfTen = largestPowerOfTen; powerOfTen > 0; powerOfTen /= 10)
    {
        u8 c;
        u16 digit = value / powerOfTen;
        s32 temp = value - (powerOfTen * digit);

        if (state == WRITING_DIGITS)
        {
            u8 *out = dest++;

            if (digit <= 9)
                c = sDigits[digit];
            else
                c = CHAR_QUESTION_MARK;

            *out = c;
        }
        else if (digit != 0 || powerOfTen == 1)
        {
            u8 *out;
            state = WRITING_DIGITS;
            out = dest++;

            if (digit <= 9)
                c = sDigits[digit];
            else
                c = CHAR_QUESTION_MARK;

            *out = c;
        }
        else if (state == WRITING_SPACES)
        {
            *dest++ = CHAR_SPACER;
        }

        value = temp;
    }

    *dest = EOS;
    return dest;
}

u8 *ConvertUIntToDecimalStringN(u8 *dest, u32 value, enum StringConvertMode mode, u8 n)
{
    enum { WAITING_FOR_NONZERO_DIGIT, WRITING_DIGITS, WRITING_SPACES } state;
    s32 powerOfTen;
    s32 largestPowerOfTen = sPowersOfTen[n - 1];

    state = WAITING_FOR_NONZERO_DIGIT;

    if (mode == STR_CONV_MODE_RIGHT_ALIGN)
        state = WRITING_SPACES;

    if (mode == STR_CONV_MODE_LEADING_ZEROS)
        state = WRITING_DIGITS;

    for (powerOfTen = largestPowerOfTen; powerOfTen > 0; powerOfTen /= 10)
    {
        u8 c;
        u16 digit = value / powerOfTen;
        u32 temp = value - (powerOfTen * digit);

        if (state == WRITING_DIGITS)
        {
            u8 *out = dest++;

            if (digit <= 9)
                c = sDigits[digit];
            else
                c = CHAR_QUESTION_MARK;

            *out = c;
        }
        else if (digit != 0 || powerOfTen == 1)
        {
            u8 *out;
            state = WRITING_DIGITS;
            out = dest++;

            if (digit <= 9)
                c = sDigits[digit];
            else
                c = CHAR_QUESTION_MARK;

            *out = c;
        }
        else if (state == WRITING_SPACES)
        {
            *dest++ = CHAR_SPACER;
        }

        value = temp;
    }

    *dest = EOS;
    return dest;
}

u8 *ConvertIntToHexStringN(u8 *dest, s32 value, enum StringConvertMode mode, u8 n)
{
    enum { WAITING_FOR_NONZERO_DIGIT, WRITING_DIGITS, WRITING_SPACES } state;
    u8 i;
    s32 powerOfSixteen;
    s32 largestPowerOfSixteen = 1;

    for (i = 1; i < n; i++)
        largestPowerOfSixteen *= 16;

    state = WAITING_FOR_NONZERO_DIGIT;

    if (mode == STR_CONV_MODE_RIGHT_ALIGN)
        state = WRITING_SPACES;

    if (mode == STR_CONV_MODE_LEADING_ZEROS)
        state = WRITING_DIGITS;

    for (powerOfSixteen = largestPowerOfSixteen; powerOfSixteen > 0; powerOfSixteen /= 16)
    {
        u8 c;
        u32 digit = value / powerOfSixteen;
        s32 temp = value % powerOfSixteen;

        if (state == WRITING_DIGITS)
        {
            char *out = dest++;

            if (digit <= 0xF)
                c = sDigits[digit];
            else
                c = CHAR_QUESTION_MARK;

            *out = c;
        }
        else if (digit != 0 || powerOfSixteen == 1)
        {
            char *out;
            state = WRITING_DIGITS;
            out = dest++;

            if (digit <= 0xF)
                c = sDigits[digit];
            else
                c = CHAR_QUESTION_MARK;

            *out = c;
        }
        else if (state == WRITING_SPACES)
        {
            *dest++ = CHAR_SPACER;
        }

        value = temp;
    }

    *dest = EOS;
    return dest;
}

u8 *StringUppercase(u8 *dest, const u8 *src)
{
    for (;;)
    {
        u8 c = *src++;
        
        switch (c)
        {
            case EXT_CTRL_CODE_BEGIN:
                *dest++ = c;
                c = *src++;
                *dest++ = c;

                switch (c)
                {
                    case EXT_CTRL_CODE_RESET_SIZE:
                    case EXT_CTRL_CODE_PAUSE_UNTIL_PRESS:
                    case EXT_CTRL_CODE_FILL_WINDOW:
                    case EXT_CTRL_CODE_JPN:
                    case EXT_CTRL_CODE_ENG:
                    case EXT_CTRL_CODE_PAUSE_MUSIC:
                    case EXT_CTRL_CODE_RESUME_MUSIC:
                        break;
                    case EXT_CTRL_CODE_COLOR_HIGHLIGHT_SHADOW:
                        *dest++ = *src++;
                    case EXT_CTRL_CODE_PLAY_BGM:
                        *dest++ = *src++;
                    default:
                        *dest++ = *src++;
                }
                break;
            case EOS:
                *dest = EOS;
                return dest;
            case CHAR_a: *dest++ = CHAR_A; break;
            case CHAR_b: *dest++ = CHAR_B; break;
            case CHAR_c: *dest++ = CHAR_C; break;
            case CHAR_d: *dest++ = CHAR_D; break;
            case CHAR_e: *dest++ = CHAR_E; break;
            case CHAR_f: *dest++ = CHAR_F; break;
            case CHAR_g: *dest++ = CHAR_G; break;
            case CHAR_h: *dest++ = CHAR_H; break;
            case CHAR_i: *dest++ = CHAR_I; break;
            case CHAR_j: *dest++ = CHAR_J; break;
            case CHAR_k: *dest++ = CHAR_K; break;
            case CHAR_l: *dest++ = CHAR_L; break;
            case CHAR_m: *dest++ = CHAR_M; break;
            case CHAR_n: *dest++ = CHAR_N; break;
            case CHAR_o: *dest++ = CHAR_O; break;
            case CHAR_p: *dest++ = CHAR_P; break;
            case CHAR_q: *dest++ = CHAR_Q; break;
            case CHAR_r: *dest++ = CHAR_R; break;
            case CHAR_s: *dest++ = CHAR_S; break;
            case CHAR_t: *dest++ = CHAR_T; break;
            case CHAR_u: *dest++ = CHAR_U; break;
            case CHAR_v: *dest++ = CHAR_V; break;
            case CHAR_w: *dest++ = CHAR_W; break;
            case CHAR_x: *dest++ = CHAR_X; break;
            case CHAR_y: *dest++ = CHAR_Y; break;
            case CHAR_z: *dest++ = CHAR_Z; break;
            case CHAR_PROMPT_SCROLL:
            case CHAR_PROMPT_CLEAR:
            case CHAR_NEWLINE:
            default:
                *dest++ = c;
        }
    }
}


u8 *StringExpandPlaceholders(u8 *dest, const u8 *src)
{
    for (;;)
    {
        u8 c = *src++;
        u8 placeholderId;
        const u8 *expandedString;

        switch (c)
        {
        case PLACEHOLDER_BEGIN:
            placeholderId = *src++;
            expandedString = GetExpandedPlaceholder(placeholderId);
            dest = StringExpandPlaceholders(dest, expandedString);
            break;
        case EXT_CTRL_CODE_BEGIN:
            *dest++ = c;
            c = *src++;
            *dest++ = c;

            switch (c)
            {
            case EXT_CTRL_CODE_RESET_SIZE:
            case EXT_CTRL_CODE_PAUSE_UNTIL_PRESS:
            case EXT_CTRL_CODE_FILL_WINDOW:
            case EXT_CTRL_CODE_JPN:
            case EXT_CTRL_CODE_ENG:
            case EXT_CTRL_CODE_PAUSE_MUSIC:
            case EXT_CTRL_CODE_RESUME_MUSIC:
                break;
            case EXT_CTRL_CODE_COLOR_HIGHLIGHT_SHADOW:
                *dest++ = *src++;
            case EXT_CTRL_CODE_PLAY_BGM:
                *dest++ = *src++;
            default:
                *dest++ = *src++;
            }
            break;
        case EOS:
            *dest = EOS;
            return dest;
        case CHAR_PROMPT_SCROLL:
        case CHAR_PROMPT_CLEAR:
        case CHAR_NEWLINE:
        default:
            *dest++ = c;
        }
    }
}

u8 *StringBraille(u8 *dest, const u8 *src)
{
    const u8 setBrailleFont[] = {
        EXT_CTRL_CODE_BEGIN,
        EXT_CTRL_CODE_FONT,
        FONT_BRAILLE,
        EOS
    };
    const u8 gotoLine2[] = {
        CHAR_NEWLINE,
        EXT_CTRL_CODE_BEGIN,
        EXT_CTRL_CODE_SHIFT_DOWN,
        2,
        EOS
    };

    dest = StringCopy(dest, setBrailleFont);

    for (;;)
    {
        u8 c = *src++;

        switch (c)
        {
        case EOS:
            *dest = c;
            return dest;
        case CHAR_NEWLINE:
            dest = StringCopy(dest, gotoLine2);
            break;
        default:
            *dest++ = c;
            *dest++ = c + NUM_BRAILLE_CHARS;
            break;
        }
    }
}

extern const u8 gText_ExpandedPlaceholder_Empty[];
static const u8 *ExpandPlaceholder_Empty(void)
{
    return gText_ExpandedPlaceholder_Empty;
}

static const u8 *ExpandPlaceholder_PlayerName(void)
{
    if (FlagGet(FLAG_SYS_BORT_MODE)) {
        StringUppercase(gStringWorking, gSaveBlock2Ptr->playerName);
        gStringWorking[4] = EOS; // truncate to 4 characters
        return gStringWorking;
    } else {
        return gSaveBlock2Ptr->playerName;
    }
}

static const u8 *ExpandPlaceholder_StringVar1(void)
{
    return gStringVar1;
}

static const u8 *ExpandPlaceholder_StringVar2(void)
{
    return gStringVar2;
}

static const u8 *ExpandPlaceholder_StringVar3(void)
{
    return gStringVar3;
}

static const u8 *ExpandPlaceholder_StringVar4(void)
{
    return gStringVar4;
}

static const u8 *ExpandPlaceholder_StringVar5(void)
{
    return gStringVar5;
}

static const u8 *ExpandPlaceholder_StringVar6(void)
{
    return gStringVar6;
}

extern const u8 gText_ExpandedPlaceholder_Brendan[];
extern const u8 gText_ExpandedPlaceholder_May[];
static const u8 *ExpandPlaceholder_RivalName(void)
{
    if (gSaveBlock2Ptr->playerGender == MALE)
        return gText_ExpandedPlaceholder_May;
    else
        return gText_ExpandedPlaceholder_Brendan;
}

extern const u8 gText_ExpandedPlaceholder_TrickMasterShiny[];
static const u8 *ExpandPlaceholder_TrickMaster(void)
{
    return gText_ExpandedPlaceholder_TrickMasterShiny;
}

extern const u8 gText_ExpandedPlaceholder_Youngster[];
static const u8 *ExpandPlaceholder_Youngster(void)
{
    return gText_ExpandedPlaceholder_Youngster;
}

extern const u8 gText_ExpandedPlaceholder_Wally[];
static const u8 *ExpandPlaceholder_Wally(void)
{
    return gText_ExpandedPlaceholder_Wally;
}

extern const u8 gText_ExpandedPlaceholder_Link[];
static const u8 *ExpandPlaceholder_Link(void)
{
    return gText_ExpandedPlaceholder_Link;
}

extern const u8 gText_ExpandedPlaceholder_FairyGirl[];
static const u8 *ExpandPlaceholder_FairyGirl(void)
{
    return gText_ExpandedPlaceholder_FairyGirl;
}

extern const u8 gText_ExpandedPlaceholder_Brendan[];
static const u8 *ExpandPlaceholder_Brendan(void)
{
    return gText_ExpandedPlaceholder_Brendan;
}

extern const u8 gText_ExpandedPlaceholder_May[];
static const u8 *ExpandPlaceholder_May(void)
{
    return gText_ExpandedPlaceholder_May;
}

extern const u8 gText_ExpandedPlaceholder_Alex[];
static const u8 *ExpandPlaceholder_Alex(void)
{
    return gText_ExpandedPlaceholder_Alex;
}

extern const u8 gText_ExpandedPlaceholder_ToTRuleNo[];
static const u8 *ExpandPlaceholder_ToTRuleNo(void)
{
    return gText_ExpandedPlaceholder_ToTRuleNo;
}

extern const u8 gText_ExpandedPlaceholder_Boulder[];
extern const u8 gText_ExpandedPlaceholder_Crate[];
static const u8 *ExpandPlaceholder_Boulder(void)
{
    if (CurrentMapIs(MAP_PUZZLE_STEALTH_MISSION)) {
        return gText_ExpandedPlaceholder_Crate;
    }
    return gText_ExpandedPlaceholder_Boulder;
}

extern const u8 PuzzleCommon_Text_UntitledPuzzleName[];
static const u8 *ExpandPlaceholder_PuzzleName(void)
{
    u16 currPuzzle = GetCurrentPuzzleMapId();
	const u8 *str = GetMapHeaderString(currPuzzle, MAP_SCRIPT_PUZZLE_HEADER_NAME);
	if (str == NULL)
	{
		str = PuzzleCommon_Text_UntitledPuzzleName;
	}
    return str;
}

extern const u8 PuzzleCommon_Text_DefaultAuthor[];
static const u8 *ExpandPlaceholder_PuzzleAuthor(void)
{
    u16 currPuzzle = GetCurrentPuzzleMapId();
	const u8 *str = GetMapHeaderString(currPuzzle, MAP_SCRIPT_PUZZLE_HEADER_AUTHOR);
	if (str == NULL)
	{
		str = PuzzleCommon_Text_DefaultAuthor;
	}
    return str;
}

extern const u8 PuzzleCommon_Text_DefaultAdjective[];
static const u8 *ExpandPlaceholder_PuzzleAdjective(void)
{
    u16 currPuzzle = GetCurrentPuzzleMapId();
	const u8 *str = GetMapHeaderString(currPuzzle, MAP_SCRIPT_PUZZLE_HEADER_ADJECTIVE);
	if (str == NULL)
	{
		str = PuzzleCommon_Text_DefaultAdjective;
	}
    return str;
}

extern const u8 PuzzleCommon_Text_DefaultQuip[];
static const u8 *ExpandPlaceholder_PuzzleQuip(void)
{
    u16 currPuzzle = GetCurrentPuzzleMapId();
	const u8 *str = GetMapHeaderString(currPuzzle, MAP_SCRIPT_PUZZLE_HEADER_QUIP);
	if (str == NULL)
	{
		str = PuzzleCommon_Text_DefaultQuip;
	}
    return str;
}

const u8 *GetExpandedPlaceholder(u32 id)
{
    typedef const u8 *(*ExpandPlaceholderFunc)(void);

    static const ExpandPlaceholderFunc funcs[] =
    {
        [0x00] = ExpandPlaceholder_Empty,
        [0x01] = ExpandPlaceholder_PlayerName,
        [0x02] = ExpandPlaceholder_StringVar1,
        [0x03] = ExpandPlaceholder_StringVar2,
        [0x04] = ExpandPlaceholder_StringVar3,
        [0x05] = ExpandPlaceholder_StringVar4,
        [0x06] = ExpandPlaceholder_StringVar5,
        [0x07] = ExpandPlaceholder_StringVar6,
        [0x08] = ExpandPlaceholder_Empty,
        [0x09] = ExpandPlaceholder_Empty,
        [0x0A] = ExpandPlaceholder_Empty,
        [0x0B] = ExpandPlaceholder_Empty,
        [0x0C] = ExpandPlaceholder_Empty,
        [0x0D] = ExpandPlaceholder_Empty,
        [0x0E] = ExpandPlaceholder_Empty,
        [0x0F] = ExpandPlaceholder_TrickMaster,
        
        [0x10] = ExpandPlaceholder_RivalName,
        [0x11] = ExpandPlaceholder_Brendan,
        [0x12] = ExpandPlaceholder_May,
        [0x13] = ExpandPlaceholder_Alex,
        [0x14] = ExpandPlaceholder_Wally,
        [0x15] = ExpandPlaceholder_Youngster,
        [0x16] = ExpandPlaceholder_Link,
        [0x17] = ExpandPlaceholder_FairyGirl,
        [0x18] = ExpandPlaceholder_Empty,
        [0x19] = ExpandPlaceholder_Empty,
        [0x1A] = ExpandPlaceholder_Empty,
        [0x1B] = ExpandPlaceholder_Empty,
        [0x1C] = ExpandPlaceholder_Empty,
        [0x1D] = ExpandPlaceholder_Empty,
        [0x1E] = ExpandPlaceholder_Empty,
        [0x1F] = ExpandPlaceholder_Empty,
        
        [0x20] = ExpandPlaceholder_PuzzleName,
        [0x21] = ExpandPlaceholder_PuzzleAuthor,
        [0x22] = ExpandPlaceholder_PuzzleAdjective,
        [0x23] = ExpandPlaceholder_PuzzleQuip,
        [0x24] = ExpandPlaceholder_ToTRuleNo,
        [0x25] = ExpandPlaceholder_Boulder,
        
    };

    if (id >= ARRAY_COUNT(funcs))
        return gText_ExpandedPlaceholder_Empty;
    else
        return funcs[id]();
}

u8 *StringFill(u8 *dest, u8 c, u16 n)
{
    u16 i;

    for (i = 0; i < n; i++)
        *dest++ = c;

    *dest = EOS;
    return dest;
}

u8 *StringCopyPadded(u8 *dest, const u8 *src, u8 c, u16 n)
{
    while (*src != EOS)
    {
        *dest++ = *src++;

        if (n)
            n--;
    }

    n--;

    while (n != (u16)-1)
    {
        *dest++ = c;
        n--;
    }

    *dest = EOS;
    return dest;
}

u8 *StringFillWithTerminator(u8 *dest, u16 n)
{
    return StringFill(dest, EOS, n);
}

u8 *StringCopyN_Multibyte(u8 *dest, u8 *src, u32 n)
{
    u32 i;

    for (i = n - 1; i != (u32)-1; i--)
    {
        if (*src == EOS)
        {
            break;
        }
        else
        {
            *dest++ = *src++;
            if (*(src - 1) == CHAR_EXTRA_SYMBOL)
                *dest++ = *src++;
        }
    }

    *dest = EOS;
    return dest;
}

u32 StringLength_Multibyte(const u8 *str)
{
    u32 length = 0;

    while (*str != EOS)
    {
        if (*str == CHAR_EXTRA_SYMBOL)
            str++;
        str++;
        length++;
    }

    return length;
}

u8 *WriteColorChangeControlCode(u8 *dest, u32 colorType, u8 color)
{
    *dest = EXT_CTRL_CODE_BEGIN;
    dest++;

    switch (colorType)
    {
    case 0:
        *dest = EXT_CTRL_CODE_COLOR;
        dest++;
        break;
    case 1:
        *dest = EXT_CTRL_CODE_SHADOW;
        dest++;
        break;
    case 2:
        *dest = EXT_CTRL_CODE_HIGHLIGHT;
        dest++;
        break;
    }

    *dest = color;
    dest++;
    *dest = EOS;
    return dest;
}

bool32 IsStringJapanese(u8 *str)
{
    while (*str != EOS)
    {
        if (*str <= JAPANESE_CHAR_END)
            if (*str != CHAR_SPACE)
                return TRUE;
        str++;
    }

    return FALSE;
}

bool32 IsStringNJapanese(u8 *str, s32 n)
{
    s32 i;

    for (i = 0; *str != EOS && i < n; i++)
    {
        if (*str <= JAPANESE_CHAR_END)
            if (*str != CHAR_SPACE)
                return TRUE;
        str++;
    }

    return FALSE;
}

u8 GetExtCtrlCodeLength(u8 code)
{
    static const u8 lengths[] =
    {
        [0]                                    = 1,
        [EXT_CTRL_CODE_COLOR]                  = 2,
        [EXT_CTRL_CODE_HIGHLIGHT]              = 2,
        [EXT_CTRL_CODE_SHADOW]                 = 2,
        [EXT_CTRL_CODE_COLOR_HIGHLIGHT_SHADOW] = 4,
        [EXT_CTRL_CODE_PALETTE]                = 2,
        [EXT_CTRL_CODE_FONT]                   = 2,
        [EXT_CTRL_CODE_RESET_SIZE]             = 1,
        [EXT_CTRL_CODE_PAUSE]                  = 2,
        [EXT_CTRL_CODE_PAUSE_UNTIL_PRESS]      = 1,
        [EXT_CTRL_CODE_WAIT_SE]                = 1,
        [EXT_CTRL_CODE_PLAY_BGM]               = 3,
        [EXT_CTRL_CODE_ESCAPE]                 = 2,
        [EXT_CTRL_CODE_SHIFT_TEXT]             = 2,
        [EXT_CTRL_CODE_SHIFT_DOWN]             = 2,
        [EXT_CTRL_CODE_FILL_WINDOW]            = 1,
        [EXT_CTRL_CODE_PLAY_SE]                = 3,
        [EXT_CTRL_CODE_CLEAR]                  = 2,
        [EXT_CTRL_CODE_SKIP]                   = 2,
        [EXT_CTRL_CODE_CLEAR_TO]               = 2,
        [EXT_CTRL_CODE_MIN_LETTER_SPACING]     = 2,
        [EXT_CTRL_CODE_JPN]                    = 1,
        [EXT_CTRL_CODE_ENG]                    = 1,
        [EXT_CTRL_CODE_PAUSE_MUSIC]            = 1,
        [EXT_CTRL_CODE_RESUME_MUSIC]           = 1,
        [EXT_CTRL_CODE_PLAY_MON_CRY]           = 2,
    };

    u8 length = 0;
    if (code < ARRAY_COUNT(lengths))
        length = lengths[code];
    return length;
}

static const u8 *SkipExtCtrlCode(const u8 *s)
{
    while (*s == EXT_CTRL_CODE_BEGIN)
    {
        s++;
        s += GetExtCtrlCodeLength(*s);
    }

    return s;
}

s32 StringCompareWithoutExtCtrlCodes(const u8 *str1, const u8 *str2)
{
    s32 retVal = 0;

    while (1)
    {
        str1 = SkipExtCtrlCode(str1);
        str2 = SkipExtCtrlCode(str2);

        if (*str1 > *str2)
            break;

        if (*str1 < *str2)
        {
            retVal = -1;
            if (*str2 == EOS)
                retVal = 1;
        }

        if (*str1 == EOS)
            return retVal;

        str1++;
        str2++;
    }

    retVal = 1;

    if (*str1 == EOS)
        retVal = -1;

    return retVal;
}

void ConvertInternationalString(u8 *s, u8 language)
{
    if (language == LANGUAGE_JAPANESE)
    {
        u8 i;

        StripExtCtrlCodes(s);
        i = StringLength(s);
        s[i++] = EXT_CTRL_CODE_BEGIN;
        s[i++] = EXT_CTRL_CODE_ENG;
        s[i++] = EOS;

        i--;

        while (i != (u8)-1)
        {
            s[i + 2] = s[i];
            i--;
        }

        s[0] = EXT_CTRL_CODE_BEGIN;
        s[1] = EXT_CTRL_CODE_JPN;
    }
}

void StripExtCtrlCodes(u8 *str)
{
    u16 srcIndex = 0;
    u16 destIndex = 0;
    while (str[srcIndex] != EOS)
    {
        if (str[srcIndex] == EXT_CTRL_CODE_BEGIN)
        {
            srcIndex++;
            srcIndex += GetExtCtrlCodeLength(str[srcIndex]);
        }
        else
        {
            str[destIndex++] = str[srcIndex++];
        }
    }
    str[destIndex] = EOS;
}
