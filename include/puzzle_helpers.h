#ifndef GUARD_PUZZLE_HELPERS
#define GUARD_PUZZLE_HELPERS

extern void HandlePuzzleMusicTileStep(u32 metatileId);
extern struct MapConnection* MetaPuzzle_ResolveMapConnection(struct MapConnection* connection);
extern struct MapHeader const *const MetaPuzzle_GetMapConnection(struct MapConnection *connection);

#endif // GUARD_PUZZLE_HELPERS
