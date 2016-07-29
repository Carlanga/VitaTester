TITLE_ID = VITATESTR
TARGET = VitaTester
OBJS   = icons/background.o icons/cross.o icons/circle.o icons/square.o icons/triangle.o \
    icons/select.o icons/start.o icons/ltrigger.o icons/rtrigger.o icons/analog.o icons/dpad.o \
    icons/finger_blue.o icons/finger_gray.o font.o main.o

LIBS = -lvita2d -lSceDisplay_stub -lSceGxm_stub -lSceCommonDialog_stub \
	-lSceCtrl_stub -lSceTouch_stub -lSceSysmodule_stub -lfreetype -lpng -lz -lm

PREFIX  = arm-vita-eabi
CC      = $(PREFIX)-gcc
CFLAGS  = -Wl,-q -Wall -O3
ASFLAGS = $(CFLAGS)

all: $(TARGET).vpk

%.vpk: eboot.bin
	vita-mksfoex -s TITLE_ID=$(TITLE_ID) "$(TARGET)" param.sfo
	vita-pack-vpk -s param.sfo -b eboot.bin $@

eboot.bin: $(TARGET).velf
	vita-make-fself $< eboot.bin

%.velf: %.elf
	vita-elf-create $< $@

%.elf: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

clean:
	@rm -rf *.velf *.elf *.vpk $(OBJS) param.sfo eboot.bin
