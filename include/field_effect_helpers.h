#ifndef GUARD_FIELD_EFFECT_HELPERS_H
#define GUARD_FIELD_EFFECT_HELPERS_H

// Exported type declarations

// Exported RAM declarations

// Exported ROM declarations
u8 CreateWarpArrowSprite(void);
u8 sub_8155800(u8 oldSpriteId);
void sub_81555AC(u8, u8);
bool8 sub_8155DA0(struct EventObject *);
void sub_8155D78(struct EventObject *);
void StartAshFieldEffect(s16, s16, u16, s16);
void SetUpReflection(struct EventObject*, struct Sprite*, u8);
u32 StartFieldEffectForEventObject(u8, struct EventObject*);
u8 FindTallGrassFieldEffectSpriteId(u8 localId, u8 mapNum, u8 mapGroup, s16 x, s16 y);
u8 FindFallGrassFieldEffectSpriteId(u8 localId, u8 mapNum, u8 mapGroup, s16 x, s16 y);
void sub_8155F80(struct Sprite*);
void UpdateShadowFieldEffect(struct Sprite*);
void UpdateTallGrassFieldEffect(struct Sprite*);
void UpdateFallGrassFieldEffect(struct Sprite*);
void WaitFieldEffectSpriteAnim(struct Sprite*);
void UpdateAshFieldEffect(struct Sprite*);
void UpdateSurfBlobFieldEffect(struct Sprite*);
void sub_8156194(struct Sprite*);
void UpdateFootprintsTireTracksFieldEffect(struct Sprite*);
void UpdateSplashFieldEffect(struct Sprite*);
void UpdateLongGrassFieldEffect(struct Sprite*);
void UpdateSandPileFieldEffect(struct Sprite*);
void UpdateDisguiseFieldEffect(struct Sprite*);
void UpdateShortGrassFieldEffect(struct Sprite*);
void UpdateHotSpringsWaterFieldEffect(struct Sprite*);
void UpdateBubblesFieldEffect(struct Sprite*);
void UpdateSparkleFieldEffect(struct Sprite*);
void SetSpriteInvisible(u8 spriteId);
void ShowWarpArrowSprite(u8 spriteId, u8 direction, s16 x, s16 y);
void sub_8155604(u8 spriteId, u8 value, s16 data1);
void sub_81555D8(u8 spriteId, u8 value);

#endif //GUARD_FIELD_EFFECT_HELPERS_H
