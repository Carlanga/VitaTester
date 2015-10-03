TARGET = VitaTester
OBJS   = icons/background.o icons/cross.o icons/circle.o icons/square.o icons/triangle.o \
    icons/select.o icons/start.o icons/ltrigger.o icons/rtrigger.o icons/analog.o icons/dpad.o \
    font.o main.o revitalize.o

LIBS = -lUVLoader_stub -lvita2d -lSceDisplay_stub -lSceGxm_stub -lSceCommonDialog_stub \
	-lSceCtrl_stub -lfreetype -lpng -lz -lm

PREFIX  = arm-vita-eabi
CC      = $(PREFIX)-gcc
CFLAGS  = -Wl,-q -Wall -O3
ASFLAGS = $(CFLAGS)

all: $(TARGET).velf

%.velf: %.elf
	$(PREFIX)-strip -g $<
	vita-elf-create $< $@

$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

clean:
	@rm -rf $(TARGET).velf $(TARGET).elf $(OBJS)
