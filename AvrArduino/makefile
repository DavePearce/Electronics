# Makefile for programming the ATtiny85 via micronucleous USB
# bootloader
ARDUINO_HOME = /vol/x6/arduino-1.8.13
PORT = /dev/ttyACM0
DEVICE      = atmega328p # attiny85
CLOCK      = 16000000UL
PROGRAMMER = -c arduino #usbtiny 
AVRDUDE = avrdude -C${ARDUINO_HOME}/hardware/tools/avr/etc/avrdude.conf $(PROGRAMMER) -p $(DEVICE) -P${PORT}
COMPILE = avr-gcc -Wall -Os -std=c99 -DF_CPU=${CLOCK} -mmcu=$(DEVICE)

TARGETS = blink.hex

all: $(TARGETS)

%.s : %.c
	$(COMPILE) -S -o $@ $<

%.o : %.c
	$(COMPILE) -c -o $@ $<

%.elf: %.o
	$(COMPILE) -o $@ $< 

%.hex: %.elf
	avr-objcopy -j .text -j .data -O ihex $< $@
	avr-size --format=avr --mcu=$(DEVICE) $<
%.install: %.hex
	$(AVRDUDE) -Uflash:w:$<:i 

clean:
	rm -f *.hex *.elf *.o
