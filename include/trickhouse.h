#ifndef GUARD_TRICKHOUSE_H
#define GUARD_TRICKHOUSE_H

u16 GetCurrentPuzzleMapId();
void RunPuzzleSetupScript();
void RunPuzzleIntro();
void RunPuzzleTeardownScript();
void RunPuzzleBlackoutScript();
void RunPuzzleEscapeRopeScript();
bool8 CheckForPuzzleEscapeRopeScript();

#endif // GUARD_TRICKHOUSE_H
