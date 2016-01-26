#include <avr/io.h>
#include <util/delay.h>

#define HIGH 1
#define LOW 0

const int SER = 3;
const int RCLK = 4;
const int SRCLK = 0;

void digitalWrite(int pin, int value) {
  int mask = 0b00000001 << pin;
  if(value) {
    PORTB |= mask;
  } else {
    PORTB ^= ~mask;
  }
}

void pinMode(int pin, int value) {
  int mask = 0b00000001 << pin;
  if(value) {
    DDRB |= mask;
  } else {
    DDRB ^= ~mask;
  }  
}

char digits[10] = {
  0b11111100,  // 0
  0b01100000,  // 1
  0b11011010,  // 2
  0b11110010,  // 3
  0b01100110,  // 4
  0b10110110,  // 5
  0b10111110,  // 6
  0b11100000,  // 7
  0b11111110,  // 8
  0b11110110,  // 9
};

void writeDigit(int display, int digit) {
   char bits = digits[digit];
   digitalWrite(RCLK,LOW);   
   // Second, write the display selector
   for(int i=0;i!=4;++i) {
     digitalWrite(SRCLK,LOW);     
     digitalWrite(SER,i == display ? HIGH : LOW);
     digitalWrite(SRCLK,HIGH);     
   }
   // First, write dummy bit and col selectors
   for(int i=0;i!=4;++i) {
     digitalWrite(SRCLK,LOW);     
     digitalWrite(SER,LOW);
     digitalWrite(SRCLK,HIGH);         
   }
   // Third, write the segmenet selectors
   for(int i=0;i!=8;++i) {
     digitalWrite(SRCLK,LOW);
     digitalWrite(SER,(bits&1) != 0 ? LOW : HIGH);
     digitalWrite(SRCLK,HIGH);
     bits = bits >> 1;
   }
   digitalWrite(RCLK,HIGH);  
   //
}

int main (void)
{
  // set PB0 to be output
  pinMode(SER,HIGH);
  pinMode(RCLK,HIGH);
  pinMode(SRCLK,HIGH);

  // loop
  int counter = 0;
  int clock = 0;

  int tmp = counter;
  for(int i=0;i!=4;++i) {
    writeDigit(i,tmp % 10);  
    tmp = tmp / 10;
  }
  clock = (clock + 1) % 50;
  if(clock == 0) {
    counter = counter + 1;
  }
}
