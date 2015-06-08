
const int SER = 8;
const int RCLK = 9;
const int SRCLK = 10;

void setup() {
  pinMode(SER,OUTPUT);
  pinMode(RCLK,OUTPUT);
  pinMode(SRCLK,OUTPUT);
}

byte digits[10] = {
  0b11111100,  
  0b01100000,
  0b11011010,  
  0b11110010,
  0b01100110, 
  0b10110110,
  0b10111110,
  0b11100000,
  0b11111110,  
  0b11110110,
};

void writeDigit(int display, int digit) {
   byte bits = digits[digit];
   digitalWrite(RCLK,LOW);
   // First, write the display selector
   for(int i=1;i!=5;++i) {
     digitalWrite(SRCLK,LOW);     
     digitalWrite(SER,i == display ? LOW : HIGH);
     digitalWrite(SRCLK,HIGH);     
   }
   // Ssecond, write the segmenet selectors
   for(int i=0;i!=8;++i) {
     digitalWrite(SRCLK,LOW);
     digitalWrite(SER,(bits&1) != 0 ? HIGH : LOW);
     digitalWrite(SRCLK,HIGH);
     bits = bits >> 1;
   }
   digitalWrite(RCLK,HIGH);  
   //
}

int counter = 0;
int clock = 0;

void loop() {
  // put your main code here, to run repeatedly:
  int tmp = counter;
  for(int i=1;i!=5;++i) {
    writeDigit(i,tmp % 10);  
    //delay(5);
    tmp = tmp / 10;
  }
  clock = (clock + 1) % 1000;
  if(clock == 0) {
    counter = counter + 1;
  }
  //delay(100);
}


