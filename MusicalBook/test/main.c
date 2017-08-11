#include <avr/io.h>
#include <util/delay.h>

#define SPEAKER_PIN PB1
 
int main (void)
{
  // Set speaker pin for output
  DDRB |= (0x1b << SPEAKER_PIN);
  // Set all page pins for input
  DDRD = 0;
  PORTD = 0xFF; // all pull ups enabled
  //
  while (1) {
    PORTB = (0x1b << SPEAKER_PIN);
    if(bit_is_set(PIND,0) && bit_is_set(PIND,1) && bit_is_set(PIND,2)) {
      // Leave LED on
    } else {
      // Turn LED off
      _delay_ms(200);
      PORTB = 0;
      _delay_ms(200);
     }
  }
 
  return 1;
}
