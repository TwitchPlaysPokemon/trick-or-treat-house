#ifndef GUARD_ROTATING_GATE_H
#define GUARD_ROTATING_GATE_H

void RotatingGatePuzzleCameraUpdate(s16, s16);
void RotatingGate_InitPuzzleAndGraphics(void);
bool8 CheckForRotatingGatePuzzleCollision(u8, s16, s16);
bool8 CheckForRotatingGatePuzzleCollisionWithoutAnimation(u8, s16, s16);

#endif // GUARD_ROTATING_GATE_H
