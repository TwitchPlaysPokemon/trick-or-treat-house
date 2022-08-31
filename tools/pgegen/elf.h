#ifndef PGEGEN_ELF_H
#define PGEGEN_ELF_H

#include "elf-internal.h"
#include "global.h"

extern unsigned int nSymbols;

Elf32_Sym * GetSymbol(unsigned int st_idx);
Elf32_Sym * GetSymbolByName(const char * name);
Elf32_Sym * GetSymbolOrNullByName(const char * name);
Elf32_Shdr * GetSectionHeader(unsigned int sh_idx);
Elf32_Phdr * GetProgramHeader(unsigned int ph_idx);
const char * GetSymbolName(Elf32_Sym *);
const char * GetSectionName(Elf32_Shdr *);
void InitElf(FILE * elfFile);
void DestroyResources(void);

#endif //PGEGEN_ELF_H
