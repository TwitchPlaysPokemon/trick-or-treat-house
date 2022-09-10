
MAKEFLAGS += --no-print-directory

TOOLDIRS := $(filter-out tools/agbcc tools/binutils tools/reference tools/poryscript tools/creditor,$(wildcard tools/*))

.PHONY: all $(TOOLDIRS)

all: $(TOOLDIRS)

$(TOOLDIRS):
	@$(MAKE) -C $@
