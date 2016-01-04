// main.c
// 
// A simple blinky program for ATtiny85
// Connect red LED at pin 2 (PB3)
//
// electronut.in

#include <avr/io.h>
#include <util/delay.h>
 
 
int main (void)
{
  // set PB0 to be output
  DDRB = 0b00000001;
  while (1) {
    
    // flash# 1:
    // set PB0 high
    PORTB = 0b00000001; 
    _delay_ms(20);
    // set all low
    PORTB = 0b00000000;
    _delay_ms(20);

    // set PB0 high
    PORTB = 0b00000001; 
    _delay_ms(200);
    // set all low
    PORTB = 0b00000000;
    _delay_ms(200);
  }
 
  return 1;
}
