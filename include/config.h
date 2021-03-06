#ifndef GUARD_CONFIG_H
#define GUARD_CONFIG_H

// In the Generation 3 games, Asserts were used in various debug builds.
// Ruby/Sapphire and Emerald do not have these asserts while Fire Red
// still has them in the ROM. This is because the developers forgot
// to define NDEBUG before release, however this has been changed as
// Ruby's actual debug build does not use the AGBPrint features.
#define NDEBUG

// To enable print debugging, comment out "#define NDEBUG". This allows
// the various AGBPrint functions to be used. (See include/gba/isagbprint.h).
// Some emulators support a debug console window: uncomment NoCashGBAPrint()
// and NoCashGBAPrintf() in libisagbprn.c to use no$gba's own proprietary
// printing system. Use NoCashGBAPrint() and NoCashGBAPrintf() like you
// would normally use AGBPrint() and AGBPrintf().

// NOTE: Don't try to enable assert right now as many pointers
// still exist in defines and WILL likely result in a broken ROM.

#define ENGLISH

#ifdef ENGLISH
#define UNITS_IMPERIAL
#else
#define UNITS_METRIC
#endif

// Changes trainer class names and sprites to use halloween costumes
#define USE_TRAINER_COSTUMES 1
// Changes money to Candy Corn
#define USE_CANDY_CURRENCY 1
// Disabled EXP gain on all Pokemon
#define DISABLE_EXP_GAIN 0

#endif // GUARD_CONFIG_H
