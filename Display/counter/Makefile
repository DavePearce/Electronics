# Makefile for programming the ATtiny85 via micronucleous USB
# bootloader
DEVICE      = attiny85
CLOCK      = 16000000UL
PROGRAMMER = -c usbtiny 
AVRDUDE =  /usr/local/lib/arduino-1.6.4/hardware/tools/avr/bin/avrdude $(PROGRAMMER) -p $(DEVICE)
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
	$(AVRDUDE) main.hex

clean:
	rm -f main.hex main.elf $(OBJECTS)
