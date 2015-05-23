#display.h oddebug.h requests.h usbconfig.h usbdrv.h usbportability.h
#usbdrvasm.S

CC=avr-gcc
CFLAGS=-O2 -I. -DF_CPU=12000000UL -ffunction-sections -fdata-sections
MCU=atmega328p
TARGET_ARCH = -mmcu=$(MCU)
SOURCE=display.c demo.c 
OBJ=$(SOURCE:.c=.o) 
DEPS = display.h 
%.o: %.c  $(DEPS)
	$(CC) $(TARGET_ARCH) -c -o $@ $< $(CFLAGS)

clock.elf: $(OBJ) 
	$(CC) $(TARGET_ARCH) -o $@ $^ $(CFLAGS) -Wl,--gc-sections
%.hex: clock.elf
	avr-objcopy -j .text -j .data -O ihex $< $@
	@avr-size $<
flash: clock.hex
	gpio -g mode 22 out
	gpio -g write 22 0
	/usr/local/avrdude/bin/avrdude -p m328 -P /dev/spidev0.0 -c linuxspi -b 1000000	 -U flash:w:clock.hex:i
	gpio -g write 22 1

clean:
	rm -rf *.o clock.elf clock.hex
.PHONY: clean clock.elf flash
