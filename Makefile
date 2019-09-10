# GameBoy Emulator Makefile

BIN = gameboy
SOURCES = gameboy.c platform.c sound.c screen.c inspector.c font.c

CFLAGS = -Wall -Og -g $(shell sdl2-config --cflags)
LDLIBS = -lm $(shell sdl2-config --libs)

all: $(BIN)
gameboy: $(SOURCES)

clean:
	$(RM) $(BIN)

help:
	@echo Use \"-D OPTION\" to enable each of the following features.
	@echo \	DMG_BIOS_ENABLE
