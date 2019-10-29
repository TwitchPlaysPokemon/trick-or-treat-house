#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "elf.h"
#include "util.h"

static char * strtab = NULL;
static char * shstrtab = NULL;
static Elf32_Sym * symbols = NULL;
static Elf32_Shdr * sectionHeaders = NULL;
static Elf32_Phdr * programHeaders = NULL;
static Elf32_Ehdr elfHeader = {};
static int initialized = 0;
unsigned int nSymbols = 0;
static FILE * elfFile = NULL;

static const char ElfMagic[4] = {'\x7F', 'E', 'L', 'F'};

#ifdef _MSC_VER
#define DEBUG_MSG(fmt, ...) // fprintf(stderr, fmt, __VA_ARGS__)
#else
#define DEBUG_MSG(fmt, ...) // fprintf(stderr, fmt, ##__VA_ARGS__)
#endif

static void ReadElfHeader(void)
{
    DEBUG_MSG("ReadElfHeader\n");

    fseek(elfFile, 0, SEEK_SET);
    fread(&elfHeader, sizeof(elfHeader), 1, elfFile);
    if (memcmp(elfHeader.e_ident, ElfMagic, sizeof(ElfMagic)) != 0) {
        FATAL_ERROR("malformed ELF header\n");
    }
    initialized = 1;
}

static void ReadProgramHeaders(void)
{
    DEBUG_MSG("ReadProgramHeaders\n");

    if (!initialized) {
        FATAL_ERROR("ELF not initialized\n");
    }
    programHeaders = malloc(elfHeader.e_phentsize * elfHeader.e_phnum);
    if (programHeaders == NULL) {
        FATAL_ERROR("failed to allocate programs table\n");
    }
    fseek(elfFile, elfHeader.e_phoff, SEEK_SET);
    fread(programHeaders, elfHeader.e_phentsize, elfHeader.e_phnum, elfFile);
}

static void ReadSectionHeaders(void)
{
    DEBUG_MSG("ReadSectionHeaders\n");

    if (!initialized) {
        FATAL_ERROR("ELF not initialized\n");
    }
    sectionHeaders = malloc(elfHeader.e_shentsize * elfHeader.e_shnum);
    if (sectionHeaders == NULL) {
        FATAL_ERROR("failed to allocate section table\n");
    }
    fseek(elfFile, elfHeader.e_shoff, SEEK_SET);
    fread(sectionHeaders, elfHeader.e_shentsize, elfHeader.e_shnum, elfFile);
}

static char * read_strings(Elf32_Shdr * section)
{
    DEBUG_MSG("read_strings\n"
              "offset: %X, size: %X\n", section->sh_offset, section->sh_size);

    char * dest = malloc(section->sh_size);
    if (dest == NULL) {
        FATAL_ERROR("failed to allocate string table\n");
    }
    fseek(elfFile, section->sh_offset, SEEK_SET);
    fread(dest, 1, section->sh_size, elfFile);
    return dest;
}

static void ReadStringTables(void)
{
    DEBUG_MSG("ReadStringTables\n");

    if (sectionHeaders == NULL) {
        FATAL_ERROR("need to read section headers first\n");
    }
    shstrtab = read_strings(&sectionHeaders[elfHeader.e_shstrndx]);
    for (int i = 0; i < elfHeader.e_shnum; i++)
    {
        if (i == elfHeader.e_shstrndx) continue;
        if (sectionHeaders[i].sh_type == SHT_STRTAB) {
            strtab = read_strings(&sectionHeaders[i]);
            break;
        }
    }
    if (strtab == NULL) {
        FATAL_ERROR("failed to find strings table\n");
    }
}

static int symcmp(const void * a, const void * b)
{
    const Elf32_Sym * aa = (const Elf32_Sym *)a;
    const Elf32_Sym * bb = (const Elf32_Sym *)b;
    return aa->st_value > bb->st_value;
}

static void ReadSymbols(void)
{
    DEBUG_MSG("ReadSymbols\n");

    if (sectionHeaders == NULL) {
        FATAL_ERROR("need to read section headers first\n");
    }
    for (int i = 0; i < elfHeader.e_shnum; i++)
    {
        if (sectionHeaders[i].sh_type == SHT_SYMTAB) {
            nSymbols = sectionHeaders[i].sh_size / sizeof(Elf32_Sym);
            DEBUG_MSG("nSymbols: %d\n", nSymbols);
            symbols = malloc(sectionHeaders[i].sh_size);
            if (symbols == NULL) {
                FATAL_ERROR("failed to allocate symbol table\n");
            }
            fseek(elfFile, sectionHeaders[i].sh_offset, SEEK_SET);
            fread(symbols, sizeof(Elf32_Sym), nSymbols, elfFile);
            msort(symbols, nSymbols, sizeof(Elf32_Sym), symcmp);
            break;
        }
    }
    if (symbols == NULL) {
        FATAL_ERROR("failed to find symbol table\n");
    }
}

Elf32_Sym * GetSymbol(unsigned int st_idx)
{
    DEBUG_MSG("GetSymbol\n");

    if (symbols == NULL) {
        FATAL_ERROR("must read symbols first\n");
    }
    if (st_idx >= nSymbols) {
        FATAL_ERROR("symbol index out of array\n");
    }
    return &symbols[st_idx];
}

Elf32_Sym * GetSymbolOrNullByName(const char * name) {
    DEBUG_MSG("GetSymbolByName\n");

    if (symbols == NULL) {
        FATAL_ERROR("must read symbols first\n");
    }
    for (unsigned int i = 0; i < nSymbols; i++) {
        const char *checkName = strtab + symbols[i].st_name;
        if (strcmp(checkName, name) == 0) {
            return &symbols[i];
        }
    }
    return NULL;
}

Elf32_Sym * GetSymbolByName(const char * name)
{
    Elf32_Sym *symbol = GetSymbolOrNullByName(name);
    if (symbol == NULL)
        FATAL_ERROR("Cannot find symbol %s\n", name);
    return symbol;
}

Elf32_Shdr * GetSectionHeader(unsigned int sh_idx)
{
    DEBUG_MSG("GetSectionHeader\n");

    if ((sh_idx & 0xFF00) == 0xFF00) {  // reserved indices
        return NULL;
    }
    if (sh_idx >= elfHeader.e_shnum) {
        FATAL_ERROR("section index out of array\n");
    }
    return &sectionHeaders[sh_idx];
}

Elf32_Phdr * GetProgramHeader(unsigned int ph_idx)
{
    DEBUG_MSG("GetProgramHeader\n");

    if (ph_idx >= elfHeader.e_phnum) {
        FATAL_ERROR("program index out of array\n");
    }
    return &programHeaders[ph_idx];
}

const char * GetSymbolName(Elf32_Sym * symbol)
{
    DEBUG_MSG("GetSymbolName\n");

    if (strtab == NULL) {
        FATAL_ERROR("must read strings first\n");
    }
    return strtab + symbol->st_name;
}

const char * GetSectionName(Elf32_Shdr * section)
{
    DEBUG_MSG("GetSectionName\n");

    if (shstrtab == NULL) {
        FATAL_ERROR("must read strings first\n");
    }
    return shstrtab + section->sh_name;
}

void InitElf(FILE * file)
{
    elfFile = file;

    ReadElfHeader();
    ReadProgramHeaders();
    ReadSectionHeaders();
    ReadStringTables();
    ReadSymbols();
}

void DestroyResources(void)
{
    DEBUG_MSG("DestroyResources\n");

    free(strtab);
    strtab = NULL;
    free(shstrtab);
    shstrtab = NULL;
    free(programHeaders);
    programHeaders = NULL;
    free(sectionHeaders);
    sectionHeaders = NULL;
    free(symbols);
    symbols = NULL;
    nSymbols = 0;
    elfHeader = (Elf32_Ehdr){};
    initialized = 0;
    elfFile = NULL;
}
