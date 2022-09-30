#ifndef GUARD_DYNAMIC_PLACEHOLDER_TEXT_UTIL_H
#define GUARD_DYNAMIC_PLACEHOLDER_TEXT_UTIL_H

// Moved to string_util.c
void DynamicPlaceholder_Reset(void);
void DynamicPlaceholder_Set(u8 idx, const u8 *ptr);
u8 *DynamicPlaceholder_Expand(u8 *dest, const u8 *src);
const u8 *DynamicPlaceholder_Get(u8 idx);

#endif //GUARD_DYNAMIC_PLACEHOLDER_TEXT_UTIL_H
