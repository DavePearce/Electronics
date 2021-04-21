#include <avr/io.h>
#include <util/delay.h>

// Minimal example for blinking a LED 
int main(void) {
  // Configure pin for output
  DDRB |= 1 << PB5;
  // Loop indefinitely
  while(1) {
    PORTB |= 0b00100000;
    _delay_ms(500);
    PORTB &= 0b11011111;
    _delay_ms(500);
  }
}
