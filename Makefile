TARGET = VitaKeyTester
OBJS   = main.o

LIBS = -lUVLoader_stub -lvita2d -lSceDisplay_stub -lSceGxm_stub -lSceCommonDialog_stub \
	-lSceCtrl_stub -lfreetype -lpng -lz -lc -lm

PREFIX  = arm-vita-eabi
CC      = $(PREFIX)-gcc
CFLAGS  = -Wl,-q -Wall -O3
ASFLAGS = $(CFLAGS)

all: $(TARGET).velf

%.velf: %.elf
	$(PREFIX)-strip -g $<
	vita-elf-create $< $@ $(VITASDK)/bin/db.json $(VITASDK)/bin/extra.json

$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

clean:
	@rm -rf $(TARGET).velf $(TARGET).elf $(OBJS)
