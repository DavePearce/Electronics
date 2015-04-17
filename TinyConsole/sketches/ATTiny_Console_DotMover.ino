
const int DISPLAY_MOSI = 0; // Master Output, Slave Input
const int DISPLAY_CS = 1; // slave select pin
const int DISPLAY_CLK = 2; // clock signal

const int JOYSTICK_X = A3;
const int JOYSTICK_Y = A2;

const int OFF = 0;
const int GREEN = 1;
const int RED = 2;
const int YELLOW = 3;

void setup() {
  pinMode (DISPLAY_CS, OUTPUT);
  pinMode (DISPLAY_MOSI, OUTPUT);
  pinMode (DISPLAY_CLK, OUTPUT);   
  pinMode(JOYSTICK_X, INPUT);
  pinMode(JOYSTICK_Y, INPUT);
}

int data[64] = {
   0,0,0,0,0,0,0,0, 
   0,1,1,1,1,1,1,0, 
   0,1,2,2,2,2,1,0, 
   0,1,2,3,3,2,1,0, 
   0,1,2,3,3,2,1,0, 
   0,1,2,2,2,2,1,0, 
   0,1,1,1,1,1,1,0, 
   0,0,0,0,0,0,0,0,    
};

int offset = 0;

void loop() {
   // take the SS pin low to select the chip:
  int x = analogRead(JOYSTICK_X) >> 7; 
  int y = analogRead(JOYSTICK_Y) >> 7; 
  drawAt(x,y,GREEN);
  delay(25);
}

void drawAt(int x, int y, int color) {
  int location = (y*8)+x;
  digitalWrite(DISPLAY_CS,LOW);
   delay(50);
   for(int i=0;i<64;++i) {
      if(i == location) {
         spiTransfer(color);   
      } else {
        spiTransfer(OFF);   
      }
       delay(1); 
   }
   delay(100);   
   // take the SS pin high to de-select the chip:
   digitalWrite(DISPLAY_CS,HIGH); 
   delay(50); 
}

void spiTransfer(int data) {
   // Assuming MSB first
   for(int i=0;i!=8;++i) {
      int bit = (data & 128) == 0 ? LOW : HIGH;
      digitalWrite(DISPLAY_CLK,LOW);
      digitalWrite(DISPLAY_MOSI,bit);
      digitalWrite(DISPLAY_CLK,HIGH);
      data = data << 1;
   } 
}
