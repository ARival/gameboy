# GameBoy Emulator Makefile

BIN = gameboy
SOURCES = gameboy.c platform.c sound.c screen.c inspector.c font.c

CFLAGS = -Wall -Wextra -Og -g -std=c99 $(shell sdl2-config --cflags)
LDLIBS = -lm $(shell sdl2-config --libs)

ifeq ($(ENABLE_DMG_BIOS),1)
	CFLAGS += -D DMG_BIOS_ENABLE
endif

ifeq ($(ENABLE_ASSERT),1)
	CFLAGS += -D SDL_ASSERT_LEVEL=3
endif

all: $(BIN)
gameboy: $(SOURCES)

clean:
	$(RM) $(BIN)

help:
	@echo Use \"OPTION=1\" to enable each of the following features.
	@echo \	ENABLE_DMG_BIOS=1
	@echo \	\	Enables BIOS. BIOS file must be provided on compile.
	@echo \	ENABLE_ASSERT=1
	@echo \	\	Enables asserts to help test code before release.
