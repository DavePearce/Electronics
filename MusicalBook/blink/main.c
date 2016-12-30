// main.c
// 
// A simple blinky program for MusicalBook board (ATMega328)
// Connect red LED at pin 15 (PB1)
//
// electronut.in

#include <avr/io.h>
#include <util/delay.h>
 
 
int main (void)
{
  // set PB1 to be output
  DDRB = 0b00000010;
  while (1) {
    
    // flash# 1:
    // set PB0 high
    PORTB = 0b00000010; 
    _delay_ms(200);
    // set all low
    PORTB = 0b00000000;
    _delay_ms(200);

    // set PB0 high
    PORTB = 0b00000010; 
    _delay_ms(2000);
    // set all low
    PORTB = 0b00000010;
    _delay_ms(2000);
  }
 
  return 1;
}
