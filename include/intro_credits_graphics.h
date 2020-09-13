#ifndef GUARD_INTRO_CREDITS_GRAPHICS_H
#define GUARD_INTRO_CREDITS_GRAPHICS_H

extern u16 gSkyBgPanY;
extern s16 gSkyBgPanYAdjust;
extern s16 gSpriteDestroyFlag;

extern const struct CompressedSpriteSheet gIntro2BrendanSpriteSheet[];
extern const struct CompressedSpriteSheet gIntro2MaySpriteSheet[];
extern const struct CompressedSpriteSheet gIntro2TreekidSpriteSheet[];
extern const struct CompressedSpriteSheet gIntro2BicycleSpriteSheet[];
extern const struct CompressedSpriteSheet gIntro2FlygonSpriteSheet[];
extern const struct SpritePalette gIntroBikeAndFlygonPalette[];
extern const struct CompressedSpriteSheet gIntroBrendanBikeSpritesheet[];
extern const struct CompressedSpriteSheet gIntroMayBikeSpritesheet[];
extern const struct CompressedSpriteSheet gIntroTreekidBikeSpritesheet[];
extern const struct CompressedSpriteSheet gIntroBikeSpritesheet[];
// extern const struct CompressedSpriteSheet gIntro2BrendanSpriteSheet[];
// extern const struct CompressedSpriteSheet gIntro2MaySpriteSheet[];
// extern const struct CompressedSpriteSheet gIntro2TreekidSpriteSheet[];
extern const struct SpritePalette gIntroBikeSpritePalettes[];

void load_intro_part2_graphics(u8 a);
void sub_817B150(u8 a);
void LoadCreditsBackgroundScenery(u8);
void SetGpuRegistersForBikeScene(u8);
u8 CreateBikeBackgroundAnimationTask(u8 a, u16 b, u16 c, u16 d);
void Intro2FlickerPalette(u8);
u8 intro_create_brendan_sprite(s16 a, s16 b);
u8 intro_create_may_sprite(s16 a, s16 b);
u8 intro_create_treekid_sprite(s16 a, s16 b);
u8 intro_create_flygon_sprite(s16 a, s16 b);

#endif // GUARD_INTRO_CREDITS_GRAPHICS_H
