# Makefile for programming the ATtiny85 via micronucleous USB
# bootloader
DEVICE     = atmega328p
PORT       = /dev/cu.usbmodem1411
CLOCK      = 1000000UL
LFUSE      = 0x62
HFUSE      = 0xD9
EFUSE      = 0xFF
PROGRAMMER = -c usbtiny 
AVRDUDE = avrdude $(PROGRAMMER) -p $(DEVICE)
COMPILE = avr-gcc -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE)

OBJECTS    = main.o

all:	main.hex

%.o : %.c
	$(COMPILE) -c -o $@ $<

main.elf: $(OBJECTS)
	$(COMPILE) -o main.elf $(OBJECTS)

main.hex: main.elf
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex
	avr-size --format=avr --mcu=$(DEVICE) main.elf

install:	all
	avrdude -v $(PROGRAMMER) -p $(DEVICE) -U flash:w:main.hex

fuses:
	avrdude -v $(PROGRAMMER) -p $(DEVICE) -U lfuse:w:$(LFUSE):m
	avrdude -v $(PROGRAMMER) -p $(DEVICE) -U hfuse:w:$(HFUSE):m
	avrdude -v $(PROGRAMMER) -p $(DEVICE) -U efuse:w:$(EFUSE):m

clean:
	rm -f main.hex main.elf $(OBJECTS)
