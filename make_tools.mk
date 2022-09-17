
MAKEFLAGS += --no-print-directory

include tool_dirs.mk
#TOOLDIRS := $(filter-out tools/agbcc tools/binutils tools/reference tools/poryscript tools/creditor,$(wildcard tools/*))

.PHONY: all $(TOOLDIRS)

all: $(TOOLDIRS)

$(TOOLDIRS):
	@$(MAKE) -C $@
