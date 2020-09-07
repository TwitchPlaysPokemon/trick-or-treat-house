#ifndef GUARD_FIELD_SCREEN_EFFECT_H
#define GUARD_FIELD_SCREEN_EFFECT_H

void WarpFadeInScreen(void);
void FadeInFromBlack(void);
void WarpFadeOutScreen(void);
void FieldCB_ContinueScriptUnionRoom(void);
void FieldCB_ContinueScriptHandleMusic(void);
void FieldCB_ContinueScript(void);
void FieldCB_ReturnToFieldCableLink(void);
void Task_ReturnToFieldRecordMixing(u8 taskId);
void FieldCB_ReturnToFieldWirelessLink(void);
void FieldCB_DefaultWarpExit(void);
void FieldCB_WarpExitFadeFromWhite(void);
void FieldCB_WarpExitFadeFromBlack(void);
void FieldCB_TeleportTileWarpExit(void);
void FieldCB_MossdeepGymWarpExit(void);
void sub_80AF688(void);
bool8 sub_80AF6A4(void);
void sub_80AF6D4(void);
void sub_80AF6F0(void);
void DoWarp(void);
void DoDiveWarp(void);
void DoCustomWarp(void);
void DoSootopolisLegendWarp(void);
void DoDoorWarp(void);
void DoFallWarp(void);
void DoEscalatorWarp(u8 metatileBehavior);
void DoLavaridgeGymB1FWarp(void);
void DoLavaridgeGym1FWarp(void);
void DoTeleportTileWarp(void);
void DoMossdeepGymWarp(void);
void DoPortholeWarp(void);
void sub_80AF948(void);
void sub_80AF9F8(void);
void DoContestHallWarp(void);
void sub_80B009C(u8 flashLevel);
void WriteBattlePyramidViewScanlineEffectBuffer(void);
void sub_80B0244(void);
void sub_80B0268(void);
void sub_80B0534(void);
void sub_80B058C(void);
void sub_80B05B4(void);
void WriteFlashScanlineEffectBuffer(u8 flashLevel);
bool8 walkrun_is_standing_still(void);

#endif // GUARD_FIELD_SCREEN_EFFECT_H
