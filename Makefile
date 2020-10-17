TOOLCHAIN := $(DEVKITARM)

ifeq ($(CC),)
HOSTCC := gcc
else
HOSTCC := $(CC)
endif

ifeq ($(CXX),)
HOSTCXX := g++
else
HOSTCXX := $(CXX)
endif

ifneq (,$(wildcard $(TOOLCHAIN)/base_tools))
include $(TOOLCHAIN)/base_tools
else
export PATH := $(TOOLCHAIN)/bin:$(PATH)
PREFIX := arm-none-eabi-
OBJCOPY := $(PREFIX)objcopy
export CC := $(PREFIX)gcc
export AS := $(PREFIX)as
endif
export CPP := $(PREFIX)cpp
export LD := $(PREFIX)ld

# Build Variables
DISABLE_DEBUG	?= 0
TPP_MODE		?= 1

# Version branch
VERSION	:= v1.1.0

ifeq ($(TPP_MODE),1)
VERSION_STR := $(VERSION)*TPP
else
VERSION_STR := $(VERSION)
endif

ifeq ($(OS),Windows_NT)
EXE := .exe
EXE2 := .exe
else 
EXE :=
ifeq ($(shell uname),Darwin)
EXE2 := -mac
else
EXE2 := -nix
endif
endif

TITLE       := TRICKTREAT H
GAME_CODE   := BPEE
GAME_NAME	:= Trick or Treat House (English)
MAKER_CODE  := 01
REVISION    := 0
MODERN      ?= 0

SHELL := /bin/bash -o pipefail

ELF = $(ROM:.gba=.elf)
MAP = $(ROM:.gba=.map)
SYM = $(ROM:.gba=.sym)
PGEINI = $(ROM:.gba=.pge.ini)

C_SUBDIR = src
ASM_SUBDIR = asm
DATA_SRC_SUBDIR = src/data
DATA_ASM_SUBDIR = data
SONG_SUBDIR = sound/songs
MID_SUBDIR = sound/songs/midi

C_BUILDDIR = $(OBJ_DIR)/$(C_SUBDIR)
ASM_BUILDDIR = $(OBJ_DIR)/$(ASM_SUBDIR)
DATA_ASM_BUILDDIR = $(OBJ_DIR)/$(DATA_ASM_SUBDIR)
SONG_BUILDDIR = $(OBJ_DIR)/$(SONG_SUBDIR)
MID_BUILDDIR = $(OBJ_DIR)/$(MID_SUBDIR)

ASFLAGS := -mcpu=arm7tdmi --defsym MODERN=$(MODERN) --defsym DISABLE_DEBUG=$(DISABLE_DEBUG) --defsym TPP_MODE=$(TPP_MODE)

GCC_VER = $(shell $(CC) -dumpversion)

ifeq ($(MODERN),0)
CC1             := tools/agbcc/bin/agbcc$(EXE)
override CFLAGS += -mthumb-interwork -Wimplicit -Wparentheses -Werror -O2 -fhex-asm
ROM := tricktreat.gba
OBJ_DIR := build/emerald
LIBPATH := -L ../../tools/agbcc/lib
else
CC1              = $(shell $(CC) --print-prog-name=cc1) -quiet
override CFLAGS += -mthumb -mthumb-interwork -O2 -mabi=apcs-gnu -mtune=arm7tdmi -march=armv4t -fno-toplevel-reorder -fno-aggressive-loop-optimizations -Wno-pointer-to-int-cast
ROM := tricktreat_modern.gba
OBJ_DIR := build/modern
LIBPATH := -L $(TOOLCHAIN)/lib/gcc/arm-none-eabi/$(GCC_VER)/thumb -L $(TOOLCHAIN)/arm-none-eabi/lib/thumb
endif

CPPFLAGS := -iquote include -Wno-trigraphs -DMODERN=$(MODERN) -DDISABLE_DEBUG=$(DISABLE_DEBUG) -DTPP_MODE=$(TPP_MODE)
ifeq ($(MODERN),0)
CPPFLAGS += -I tools/agbcc/include -I tools/agbcc
endif

# LDFLAGS = -Map ../../$(MAP)

LIB := $(LIBPATH) -lgcc -lc

SHA1 := $(shell { command -v sha1sum || command -v shasum; } 2>/dev/null) -c
GFX := tools/gbagfx/gbagfx$(EXE)
AIF := tools/aif2pcm/aif2pcm$(EXE)
MID := tools/mid2agb/mid2agb$(EXE)
SCANINC := tools/scaninc/scaninc$(EXE)
PREPROC := tools/preproc/preproc$(EXE)
RAMSCRGEN := tools/ramscrgen/ramscrgen$(EXE)
FIX := tools/gbafix/gbafix$(EXE)
MAPJSON := tools/mapjson/mapjson$(EXE)
JSONPROC := tools/jsonproc/jsonproc$(EXE)
SCRIPT := tools/poryscript/poryscript$(EXE2)
COPYSTAMP := tools/copystamp/copystamp$(EXE)
PGEGEN := tools/pgegen/pgegen$(EXE)


TOOLDIRS := $(filter-out tools/agbcc tools/binutils tools/porymap.app tools/poryscript tools/pgegen tools/creditor,$(wildcard tools/*))
TOOLBASE = $(TOOLDIRS:tools/%=%)
TOOLS = $(foreach tool,$(TOOLBASE),tools/$(tool)/$(tool)$(EXE))

MAKEFLAGS += --no-print-directory

# Clear the default suffixes
.SUFFIXES:
# Don't delete intermediate files
.SECONDARY:
# Delete files that weren't built properly
.DELETE_ON_ERROR:

# Secondary expansion is required for dependency variables in object rules.
.SECONDEXPANSION:

.PHONY: all rom clean compare tidy tools mostlyclean clean-tools $(TOOLDIRS)

infoshell = $(foreach line, $(shell $1 | sed "s/ /__SPACE__/g"), $(info $(subst __SPACE__, ,$(line))))

# Build tools when building the rom
# Disable dependency scanning for clean/tidy/tools
ifeq (,$(filter-out all compare,$(MAKECMDGOALS)))
$(call infoshell, $(MAKE) tools)
else
NODEP := 1
endif

C_SRCS := $(wildcard $(C_SUBDIR)/*.c $(C_SUBDIR)/*/*.c $(C_SUBDIR)/*/*/*.c)
C_OBJS := $(patsubst $(C_SUBDIR)/%.c,$(C_BUILDDIR)/%.o,$(C_SRCS))

ASM_SRCS := $(wildcard $(ASM_SUBDIR)/*.s)
ASM_OBJS := $(patsubst $(ASM_SUBDIR)/%.s,$(ASM_BUILDDIR)/%.o,$(ASM_SRCS))

DATA_ASM_SRCS := $(wildcard $(DATA_ASM_SUBDIR)/*.s)
DATA_ASM_OBJS := $(patsubst $(DATA_ASM_SUBDIR)/%.s,$(DATA_ASM_BUILDDIR)/%.o,$(DATA_ASM_SRCS))

SONG_SRCS := $(wildcard $(SONG_SUBDIR)/*.s)
SONG_OBJS := $(patsubst $(SONG_SUBDIR)/%.s,$(SONG_BUILDDIR)/%.o,$(SONG_SRCS))

MID_SRCS := $(wildcard $(MID_SUBDIR)/*.mid)
MID_OBJS := $(patsubst $(MID_SUBDIR)/%.mid,$(MID_BUILDDIR)/%.o,$(MID_SRCS))

OBJS     := $(C_OBJS) $(ASM_OBJS) $(DATA_ASM_OBJS) $(SONG_OBJS) $(MID_OBJS)
OBJS_REL := $(patsubst $(OBJ_DIR)/%,%,$(OBJS))

SUBDIRS  := $(sort $(dir $(OBJS)))

AUTO_GEN_TARGETS :=

$(shell mkdir -p $(SUBDIRS))

all: rom

tools: $(TOOLDIRS)

$(TOOLDIRS):
	@$(MAKE) -C $@ CC=$(HOSTCC) CXX=$(HOSTCXX)

rom: $(ROM)

ini: $(PGEINI)

# For contributors to make sure a change didn't affect the contents of the ROM.
compare: all
	@$(SHA1) rom.sha1

clean: mostlyclean cleanmaps clean-tools

clean-tools:
	@$(foreach tooldir,$(TOOLDIRS),$(MAKE) clean -C $(tooldir);)

mostlyclean: tidy
	rm -f sound/direct_sound_samples/*.bin
	rm -f $(MID_SUBDIR)/*.s
	find . \( -iname '*.1bpp' -o -iname '*.4bpp' -o -iname '*.8bpp' -o -iname '*.gbapal' -o -iname '*.lz' -o -iname '*.latfont' -o -iname '*.hwjpnfont' -o -iname '*.fwjpnfont' \) -exec rm {} +
	rm -f $(AUTO_GEN_TARGETS)
	rm -f $(patsubst %.pory,%.inc,$(shell find data/ -type f -name '*.pory'))

cleanmaps:
	rm -f $(DATA_ASM_BUILDDIR)/maps.o $(DATA_ASM_BUILDDIR)/map_events.o
	rm -f $(DATA_ASM_SUBDIR)/layouts/layouts.inc $(DATA_ASM_SUBDIR)/layouts/layouts_table.inc
	rm -f $(DATA_ASM_SUBDIR)/maps/connections.inc $(DATA_ASM_SUBDIR)/maps/events.inc $(DATA_ASM_SUBDIR)/maps/groups.inc $(DATA_ASM_SUBDIR)/maps/headers.inc
	find $(DATA_ASM_SUBDIR)/maps \( -iname 'connections.inc' -o -iname 'events.inc' -o -iname 'header.inc' -o -iname 'scripts.inc' \) -exec rm {} +
	rm -f $(ROM) $(ELF) $(MAP)

tidy:
	rm -f $(ROM) $(ELF) $(MAP)
	rm -r $(OBJ_DIR)
ifeq ($(MODERN),0)
	@$(MAKE) tidy MODERN=1
endif

ifneq ($(MODERN),0)
$(C_BUILDDIR)/berry_crush.o: override CFLAGS += -Wno-address-of-packed-member
endif

include graphics_file_rules.mk
include map_data_rules.mk
include spritesheet_rules.mk
include json_data_rules.mk
include songs.mk

%.s: ;
%.png: ;
%.pal: ;
%.aif: ;
%.pory: ;

%.1bpp: %.png  ; $(GFX) $< $@
%.4bpp: %.png  ; $(GFX) $< $@
%.8bpp: %.png  ; $(GFX) $< $@
%.gbapal: %.pal ; $(GFX) $< $@
%.gbapal: %.png ; $(GFX) $< $@
%.lz: % ; $(GFX) $< $@
%.rl: % ; $(GFX) $< $@
sound/direct_sound_samples/cry_%.bin: sound/direct_sound_samples/cry_%.aif ; $(AIF) $< $@ --compress
sound/%.bin: sound/%.aif ; $(AIF) $< $@
data/%.inc: data/%.pory; $(SCRIPT) -i $< -o $@ -s TPP_MODE=$(TPP_MODE)

$(OBJ_DIR)/copystamped.bin: .git/index
	$(COPYSTAMP) $(OBJ_DIR)/copystamped.bin `git log -1 --format="-18:s $(VERSION_STR)*%h -19:t %ct"`
$(OBJ_DIR)/copystamped.bin.lz: $(OBJ_DIR)/copystamped.bin
	$(GFX) $(OBJ_DIR)/copystamped.bin $@

ifeq ($(MODERN),0)
$(C_BUILDDIR)/libc.o: CC1 := tools/agbcc/bin/old_agbcc
$(C_BUILDDIR)/libc.o: CFLAGS := -O2

$(C_BUILDDIR)/siirtc.o: CFLAGS := -mthumb-interwork

$(C_BUILDDIR)/agb_flash.o: CFLAGS := -O -mthumb-interwork
$(C_BUILDDIR)/agb_flash_1m.o: CFLAGS := -O -mthumb-interwork
$(C_BUILDDIR)/agb_flash_mx.o: CFLAGS := -O -mthumb-interwork

$(C_BUILDDIR)/m4a.o: CC1 := tools/agbcc/bin/old_agbcc

$(C_BUILDDIR)/record_mixing.o: CFLAGS += -ffreestanding
endif

ifeq ($(NODEP),1)
$(C_BUILDDIR)/%.o: c_dep :=
else
$(C_BUILDDIR)/%.o: c_dep = $(shell $(SCANINC) -I include -I tools/agbcc/include -I "" $(C_SUBDIR)/$*.c)
endif

ifeq ($(DINFO),1)
override CFLAGS += -g
endif

$(C_BUILDDIR)/%.o : $(C_SUBDIR)/%.c $$(c_dep)
	@$(CPP) $(CPPFLAGS) $< -o $(C_BUILDDIR)/$*.i
	@$(PREPROC) $(C_BUILDDIR)/$*.i charmap.txt | $(CC1) $(CFLAGS) -o $(C_BUILDDIR)/$*.s
	@echo -e ".text\n\t.align\t2, 0\n" >> $(C_BUILDDIR)/$*.s
	$(AS) $(ASFLAGS) -o $@ $(C_BUILDDIR)/$*.s

ifeq ($(NODEP),1)
$(ASM_BUILDDIR)/%.o: asm_dep :=
else
$(ASM_BUILDDIR)/%.o: asm_dep = $(shell $(SCANINC) -I "" $(ASM_SUBDIR)/$*.s)
endif

$(ASM_BUILDDIR)/%.o: $(ASM_SUBDIR)/%.s $$(asm_dep)
	$(AS) $(ASFLAGS) -o $@ $<

ifeq ($(NODEP),1)
$(DATA_ASM_BUILDDIR)/%.o: data_dep :=
else
$(DATA_ASM_BUILDDIR)/%.o: data_dep = $(shell $(SCANINC) -I include -I "" $(DATA_ASM_SUBDIR)/$*.s)
endif

$(DATA_ASM_BUILDDIR)/%.o: $(DATA_ASM_SUBDIR)/%.s $$(data_dep)
	$(PREPROC) $< charmap.txt | $(CPP) -I include | $(AS) $(ASFLAGS) -o $@

$(SONG_BUILDDIR)/%.o: $(SONG_SUBDIR)/%.s
	$(AS) $(ASFLAGS) -I sound -o $@ $<

$(OBJ_DIR)/sym_bss.ld: sym_bss.txt
	$(RAMSCRGEN) .bss $< ENGLISH > $@

$(OBJ_DIR)/sym_common.ld: sym_common.txt $(C_OBJS) $(wildcard common_syms/*.txt)
	$(RAMSCRGEN) COMMON $< ENGLISH -c $(C_BUILDDIR),common_syms > $@

$(OBJ_DIR)/sym_ewram.ld: sym_ewram.txt
	$(RAMSCRGEN) ewram_data $< ENGLISH > $@

ifeq ($(MODERN),0)
LD_SCRIPT := ld_script.txt
LD_SCRIPT_DEPS := $(OBJ_DIR)/sym_bss.ld $(OBJ_DIR)/sym_common.ld $(OBJ_DIR)/sym_ewram.ld
else
LD_SCRIPT := ld_script_modern.txt
LD_SCRIPT_DEPS := 
endif

$(OBJ_DIR)/ld_script.ld: $(LD_SCRIPT) $(LD_SCRIPT_DEPS)
	cd $(OBJ_DIR) && sed "s#tools/#../../tools/#g" ../../$(LD_SCRIPT) > ld_script.ld

$(ELF): $(OBJ_DIR)/ld_script.ld $(OBJS)
	cd $(OBJ_DIR) && $(LD) -Map ../../$(MAP) $(LDFLAGS) -T ld_script.ld -o ../../$@ $(OBJS_REL) $(LIB)
	$(FIX) $@ -t"$(TITLE)" -c$(GAME_CODE) -m$(MAKER_CODE) -r$(REVISION) --silent

$(ROM): $(ELF)
	$(OBJCOPY) -O binary $< $@
	$(FIX) $@ -p --silent
	nm -SBgn $< > $(ROM:.gba=.sym)

$(PGEINI): $(ELF)
	$(PGEGEN) $< $@ --code $(GAME_CODE) --name "$(GAME_NAME)"

modern: ; @$(MAKE) MODERN=1

