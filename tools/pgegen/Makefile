CC := gcc

CFLAGS := -Wall -O2

SRCS := pgegen.c elf.c util.c

HEADERS := global.h elf.h util.h

.PHONY: all clean

all: pgegen
	@:

pgegen: $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) $(SRCS) -o $@ $(LDFLAGS)

clean:
	$(RM) pgegen pgegen.exe
