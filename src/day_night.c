// The day/night system is a slightly-modified port from Sierraffinity's CrystalDust project.
// The debug features are stripped out, along with some field effects that preserve original palette for emote bubbles.
// Trihard is also not currently taking advantage of the palette override system, which lets you
// do things like lit windows at night--the functionality is all there, though, and it's slightly modified from CrystalDust, in that
// you only specify the time of day enum, rather than an hour range.
// Trihard also does not take advantage of the Daylight Savings Time functionality, but it is functional.

#include "global.h"
#include "day_night.h"
#include "decompress.h"
#include "event_data.h"
#include "field_tasks.h"
#include "field_weather.h"
#include "overworld.h"
#include "palette.h"
#include "rtc.h"
#include "strings.h"
#include "string_util.h"
#include "script.h"
#include "constants/day_night.h"
#include "constants/rgb.h"

// #define GET_TIME_PERIOD() (gLocalTime.hours * 6 + gLocalTime.minutes / 10);
#define TINT(r,g,b)      {r, g, b}
#define TINT_DAY         TINT(256, 256, 256)
#define TINT_NIGHT       TINT(153, 140, 256)

EWRAM_DATA u16 gPlttBufferPreDN[PLTT_BUFFER_SIZE] = {0};
static EWRAM_DATA u8 sOldTimePeriod = 0;
static EWRAM_DATA bool8 sRetintPhase = FALSE;
EWRAM_DATA struct PaletteOverride *gPaletteOverrides[4] = {NULL};

static const u16 sTimeOfDayTints[][3] = {
    TINT_NIGHT,    // Midnight
    TINT_NIGHT,    
    TINT_NIGHT,    
    TINT_NIGHT,    
    TINT_NIGHT,    
    TINT_NIGHT,    
    TINT_NIGHT,    // 1 AM
    TINT_NIGHT,    
    TINT_NIGHT,    
    TINT_NIGHT,    
    TINT_NIGHT,    
    TINT_NIGHT,    
    TINT_NIGHT,    // 2 AM
    TINT_NIGHT,    
    TINT_NIGHT,    
    TINT_NIGHT,    
    TINT_NIGHT,    
    TINT_NIGHT,    
    TINT_NIGHT,    // 3 AM
    TINT_NIGHT,    
    TINT_NIGHT,    
    TINT_NIGHT,    
    TINT_NIGHT,    
    TINT_NIGHT,    
    TINT(153, 140, 255),     // 4 AM
    TINT(155, 142, 254),     
    TINT(158, 144, 252),     
    TINT(162, 147, 250),     
    TINT(165, 149, 248),     
    TINT(169, 152, 245),     
    TINT(173, 155, 243),     // 5 AM - Morning
    TINT(177, 158, 240),     
    TINT(182, 162, 237),     
    TINT(187, 165, 235),     
    TINT(191, 169, 233),     
    TINT(196, 172, 231),     
    TINT(201, 176, 230),     // 6 AM
    TINT(204, 180, 230),     
    TINT(207, 181, 230),     
    TINT(210, 184, 231),     
    TINT(213, 187, 231),     
    TINT(216, 190, 232),     
    TINT(219, 193, 234),     // 7 AM
    TINT(222, 195, 235),     
    TINT(226, 199, 237),     
    TINT(229, 201, 238),     
    TINT(232, 205, 241),     
    TINT(235, 207, 242),     
    TINT(237, 210, 244),     // 8 AM
    TINT(240, 213, 246),     
    TINT(243, 216, 248),     
    TINT(245, 219, 249),     
    TINT(249, 221, 251),     
    TINT(250, 224, 253),     
    TINT(252, 226, 253),     // 9 AM
    TINT(254, 229, 254),     
    TINT(255, 232, 255),     
    TINT(256, 238, 256),     
    TINT(256, 244, 256),     
    TINT(256, 248, 256),     
    TINT(256, 252, 256),         // 10 AM - Daytime
    TINT_DAY,         
    TINT_DAY,         
    TINT_DAY,         
    TINT_DAY,         
    TINT_DAY,         
    TINT_DAY,         // 11 AM
    TINT_DAY,         
    TINT_DAY,         
    TINT_DAY,         
    TINT_DAY,         
    TINT_DAY,         
    TINT_DAY,         // 12 PM
    TINT_DAY,         
    TINT_DAY,         
    TINT_DAY,         
    TINT_DAY,         
    TINT_DAY,         
    TINT_DAY,         // 1 PM
    TINT_DAY,         
    TINT_DAY,         
    TINT_DAY,         
    TINT_DAY,         
    TINT_DAY,         
    TINT_DAY,         // 2 PM
    TINT_DAY,         
    TINT_DAY,         
    TINT_DAY,         
    TINT_DAY,         
    TINT_DAY,         
    TINT_DAY,         // 3 PM
    TINT_DAY,         
    TINT_DAY,         
    TINT_DAY,         
    TINT_DAY,         
    TINT_DAY,         
    TINT(256, 255, 255), // 4 PM
    TINT(256, 253, 252),         
    TINT(256, 252, 248),         
    TINT(256, 251, 245),         
    TINT(256, 250, 240),         
    TINT(256, 248, 234),         
    TINT(256, 247, 229),   // 5 PM - Evening
    TINT(256, 244, 224),   
    TINT(256, 241, 219),   
    TINT(256, 238, 213),   
    TINT(256, 234, 209),   
    TINT(255, 230, 205),   
    TINT(254, 223, 198),  // 6 PM
    TINT(251, 211, 192),  
    TINT(248, 199, 185),  
    TINT(245, 187, 179),  
    TINT(241, 174, 174),  
    TINT(237, 163, 171),  
    TINT(232, 155, 171),   // 7 PM
    TINT(219, 153, 180),   
    TINT(199, 153, 204),   
    TINT(181, 153, 228),   
    TINT(168, 150, 241),   
    TINT(159, 144, 250),   
    TINT_NIGHT,   // 8 PM - Night
    TINT_NIGHT,   
    TINT_NIGHT,   
    TINT_NIGHT,   
    TINT_NIGHT,   
    TINT_NIGHT,   
    TINT_NIGHT,   // 9 PM
    TINT_NIGHT,   
    TINT_NIGHT,   
    TINT_NIGHT,   
    TINT_NIGHT,   
    TINT_NIGHT,   
    TINT_NIGHT,   // 10 PM
    TINT_NIGHT,   
    TINT_NIGHT,   
    TINT_NIGHT,   
    TINT_NIGHT,   
    TINT_NIGHT,   
    TINT_NIGHT,   // 11 PM
    TINT_NIGHT,       
    TINT_NIGHT,       
    TINT_NIGHT,       
    TINT_NIGHT,       
    TINT_NIGHT,       
};

const u8 *const gDayOfWeekTable[] = 
{
    gText_Sunday,
    gText_Monday,
    gText_Tuesday,
    gText_Wednesday,
    gText_Thursday,
    gText_Friday,
    gText_Saturday
};

inline u8 GET_TIME_PERIOD() {
	return Q_8_8_TO_INT(gSaveBlock2Ptr->sunOffset);
}

void AdvanceSunOffset(struct ScriptContext *ctx)
{
	gSaveBlock2Ptr->sunOffset += Q_8_8(0.5);
}

void DebugGetSunOffset(struct ScriptContext *ctx)
{
	gSpecialVar_Result = ctx->data[0] = gSaveBlock2Ptr->sunOffset;
}

void DebugSetSunOffset(struct ScriptContext *ctx)
{
	gSaveBlock2Ptr->sunOffset = ctx->data[0];
}

u8 GetCurrentTimeOfDay(void)
{
	return Q_8_8_TO_INT(gSaveBlock2Ptr->sunOffset) / 6;
    // return GetTimeOfDay(gLocalTime.hours);
}

u8 GetTimeOfDay(s8 hours)
{
    if (hours < TIME_MORNING_HOUR)
        return TIME_NIGHT;
    else if (hours < TIME_DAY_HOUR)
        return TIME_MORNING;
    else if (hours < TIME_NIGHT_HOUR)
        return TIME_DAY;
    else
        return TIME_NIGHT;
}

const u8 *GetDayOfWeekString(u8 dayOfWeek)
{
    return gDayOfWeekTable[dayOfWeek];
}

void CopyDayOfWeekStringToVar1(void)
{
    if (gSpecialVar_0x8004 <= DAY_SATURDAY)
        StringCopy(gStringVar1, gDayOfWeekTable[gSpecialVar_0x8004]);
    else
        StringCopy(gStringVar1, gText_None);
}

void CopyCurrentDayOfWeekStringToVar1(void)
{
    RtcCalcLocalTime();
    if (gLocalTime.dayOfWeek <= DAY_SATURDAY)
        StringCopy(gStringVar1, gDayOfWeekTable[gLocalTime.dayOfWeek]);
    else
        StringCopy(gStringVar1, gText_None);
}

static void LoadPaletteOverrides(void)
{
    u8 i, j;
    const u16* src;
    u16* dest;
    u8 curTimeOfDay = GetCurrentTimeOfDay();

    for (i = 0; i < ARRAY_COUNT(gPaletteOverrides); i++)
    {
        const struct PaletteOverride *curr = gPaletteOverrides[i];
        if (curr != NULL)
        {
            while (curr->slot != PALOVER_LIST_TERM && curr->palette != NULL)
            {
                if (curr->timeOfDay == curTimeOfDay)
                {
                    for (j = 0, src = curr->palette, dest = gPlttBufferUnfaded + (curr->slot * 16); j < 16; j++, src++, dest++)
                    {
                        if (*src != RGB_BLACK)
                            *dest = *src;
                    }
                }
                curr++;
            }
        }
    }
}

static bool8 ShouldTintOverworld(void)
{
    if (IsMapTypeOutdoors(gMapHeader.mapType))
        return TRUE;

    // more conditions?
    return FALSE;
}

static void TintPaletteForDayNight(u16 offset, u16 size)
{
    if (ShouldTintOverworld())
    {
        u8 tp;
        RtcCalcLocalTimeFast();
        tp = GET_TIME_PERIOD();
        TintPalette_CustomToneWithCopy(gPlttBufferPreDN + offset, gPlttBufferUnfaded + offset, size / 2, sTimeOfDayTints[tp][0], sTimeOfDayTints[tp][1], sTimeOfDayTints[tp][2], FALSE);
    }
    else
    {
        CpuCopy16(gPlttBufferPreDN + offset, gPlttBufferUnfaded + offset, size);
    }
    LoadPaletteOverrides();
}

void LoadCompressedPaletteDayNight(const void *src, u16 offset, u16 size)
{
    LZDecompressWram(src, gPaletteDecompressionBuffer);
    CpuCopy16(gPaletteDecompressionBuffer, gPlttBufferPreDN + offset, size);
    TintPaletteForDayNight(offset, size);
    CpuCopy16(gPlttBufferUnfaded + offset, gPlttBufferFaded + offset, size);
}

void LoadPaletteDayNight(const void *src, u16 offset, u16 size)
{
    CpuCopy16(src, gPlttBufferPreDN + offset, size);
    TintPaletteForDayNight(offset, size);
    CpuCopy16(gPlttBufferUnfaded + offset, gPlttBufferFaded + offset, size);
}

void CheckClockForImmediateTimeEvents(void)
{
    // if (ShouldTintOverworld() && !sRetintPhase)
    //     RtcCalcLocalTimeFast();
}

void ProcessImmediateTimeEvents(void)
{
    // u8 tp;

    // if (ShouldTintOverworld())
    // {
    //     if (!sRetintPhase)
    //     {
    //         tp = GET_TIME_PERIOD();
    //         if (tp != sOldTimePeriod)
    //         {
    //             sOldTimePeriod = tp;
    //             sRetintPhase = 1;
    //             TintPalette_CustomToneWithCopy(gPlttBufferPreDN, gPlttBufferUnfaded, BG_PLTT_SIZE / 2, sTimeOfDayTints[tp][0], sTimeOfDayTints[tp][1], sTimeOfDayTints[tp][2], TRUE);
    //         }
    //     }
    //     else
    //     {
    //         sRetintPhase = 0;
    //         TintPalette_CustomToneWithCopy(gPlttBufferPreDN + (BG_PLTT_SIZE / 2), gPlttBufferUnfaded + (BG_PLTT_SIZE / 2), OBJ_PLTT_SIZE / 2, sTimeOfDayTints[sOldTimePeriod][0], sTimeOfDayTints[sOldTimePeriod][1], sTimeOfDayTints[sOldTimePeriod][2], TRUE);
    //         LoadPaletteOverrides();
            
    //         if (gWeatherPtr->palProcessingState != WEATHER_PAL_STATE_SCREEN_FADING_IN &&
    //             gWeatherPtr->palProcessingState != WEATHER_PAL_STATE_SCREEN_FADING_OUT)
    //             CpuCopy16(gPlttBufferUnfaded, gPlttBufferFaded, PLTT_SIZE);

    //         ChooseAmbientCrySpecies();  // so a time-of-day appropriate mon is chosen
    //         ForceTimeBasedEvents();     // for misc events that should run on time of day boundaries
    //     }
    // }
}

void DoLoadSpritePaletteDayNight(const u16 *src, u16 paletteOffset)
{
    LoadPaletteDayNight(src, paletteOffset + 0x100, 32);
}
