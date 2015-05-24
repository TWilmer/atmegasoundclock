#display.h oddebug.h requests.h usbconfig.h usbdrv.h usbportability.h
# to produce the wav files
.PHONY: clean all
clean:
	rm -rf *.o clock.elf clock.hex  *.u8 *.u8.h wav2c
all: clock.elf
CC=avr-gcc
CFLAGS=-O2 -I. -DF_CPU=12000000UL -ffunction-sections -fdata-sections
MCU=atmega328p
TARGET_ARCH = -mmcu=$(MCU)
SOURCE=hw.c demo.c  display.c time.c sound.c
OBJ=$(SOURCE:.c=.o) 
DEPS = display.h   time.h hw.h  clock.u8.h  clock.u8.h  finished.u8.h  go.u8.h  hour.u8.h  minute.u8.h  timer.u8.h
sound.o:finished.u8.h  go.u8.h  hour.u8.h  minute.u8.h  timer.u8.h clock.u8.h
%.o: %.c 
	$(CC) $(TARGET_ARCH) -c -o $@ $< $(CFLAGS)
BCD2bin8.o: BCD2bin8.s
	$(CC) $(TARGET_ARCH) -c -o $@ $< $(CFLAGS)
    
clock.elf: $(OBJ) BCD2bin8.o
	$(CC) $(TARGET_ARCH) -o $@ $^  $(CFLAGS) -Wl,--gc-sections
%.hex: clock.elf
	avr-objcopy -j .text -j .data -O ihex $< $@
	@avr-size $<
flash: clock.hex
	gpio -g mode 22 out
	gpio -g write 22 0
	/usr/local/avrdude/bin/avrdude -p m328 -P /dev/spidev0.0 -c linuxspi -b 1000000	 -U flash:w:clock.hex:i
	gpio -g write 22 1
fuse:
	gpio -g mode 22 out
	gpio -g write 22 0
#Target 12 Mhz

#L 0xE6
#H 0xD9
#E 0x07

#CKDIV8 - off  1
#CKOUT  - off  1
#SUT1   - off  1
#SUT0   - on   0

#CKSEL3 - on   0
#CKSEL2 - off  1
#CKSEL1 - off  1
#CKSEL0 - on   0	
	/usr/local/avrdude/bin/avrdude -p m328 -P /dev/spidev0.0 -c linuxspi -b 1000000	 -U lfuse:w:0xe6:m
	gpio -g write 22 1
%.wav: 
	espeak  -w $@  `basename $@ .wav`
%.u8:  %.wav
	sox  $<  -b 8 -e unsigned-integer -c 1 -r 8000 $@
wav2c: wav2c.cpp
	g++ -std=gnu++0x -O2 -o wav2c wav2c.cpp
	
%.u8.h: %.u8 wav2c
	./wav2c $<
    
	








