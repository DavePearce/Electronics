# Makefile for programming the ATtiny85 via micronucleous USB
# bootloader
DEVICE      = attiny85
CLOCK      = 16000000UL
PROGRAMMER = -c usbtiny 
AVRDUDE = avrdude $(PROGRAMMER) -p $(DEVICE)
COMPILE = avr-gcc -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE)

OBJECTS    = main.s

all:	main.hex

%.s : %.c
	$(COMPILE) -S -o $@ $<

%.o : %.c
	$(COMPILE) -c -o $@ $<

main.elf: $(OBJECTS)
	$(COMPILE) -o main.elf $(OBJECTS)

main.hex: main.elf
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex
	avr-size --format=avr --mcu=$(DEVICE) main.elf

install:	all
	micronucleus main.hex

clean:
	rm -f main.hex main.elf $(OBJECTS)
