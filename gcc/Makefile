CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
LD = arm-none-eabi-ld
BIN = arm-none-eabi-objcopy
STL = st-flash
CFLAGS = -mthumb -mcpu=cortex-m7 -O0 -e core_SysEntry -nostartfiles -nostdlib -nodefaultlibs

all: app.bin

app.elf:
	$(CC) $(CFLAGS) -T ../generic/linker.ld -o app.elf ../startUp.c ../led_blinker/IntVect.c ../led_blinker/main.c
app.bin: app.elf
	$(BIN) -O binary app.elf app.bin
