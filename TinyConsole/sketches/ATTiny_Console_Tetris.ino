
/* === Tiny Console Setup & Library === */

const int DISPLAY_MOSI = 0; // Master Output, Slave Input
const int DISPLAY_CS = 1; // slave select pin
const int DISPLAY_CLK = 2; // clock signal

const int JOYSTICK_X = A2;
const int JOYSTICK_Y = A3;

const int OFF = 0;
const int GREEN = 1;
const int RED = 2;
const int YELLOW = 3;

void setup() {
  pinMode(DISPLAY_CS, OUTPUT);
  pinMode(DISPLAY_MOSI, OUTPUT);
  pinMode(DISPLAY_CLK, OUTPUT);   
  pinMode(JOYSTICK_X, INPUT);
  pinMode(JOYSTICK_Y, INPUT);
}

// Holds data to be drawn to display
int display[8][8];

// Redraw the Tiny Console Display
void refresh() {
  digitalWrite(DISPLAY_CS,LOW);
  delay(50);
  for(int i=7;i>=0;--i) {
     for(int j=0;j<8;++j) {     
       spiTransfer(display[i][j]);   
       delay(1); 
     }  
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

// read joystick axis as number between 0 and 7
int read_joystick(int axis) {
  return analogRead(axis) >> 7; 
}

/* === Piece Definitions === */

const int I_PIECE = 0;
const int J_PIECE = 1;
const int L_PIECE = 2;
const int O_PIECE = 3;
const int S_PIECE = 4;
const int Z_PIECE = 5;

int piece_array[6][16] = {
  /* I Piece */
  {
   0,0,0,0,  
   1,1,1,1,
   0,0,0,0,
   0,0,0,0   
  },
  /* J Piece */
  {
   0,0,0,0,  
   1,1,1,0,
   0,0,1,0,
   0,0,0,0   
  },
  /* L Piece */
  {
   0,0,0,0,
   0,0,1,0,
   1,1,1,0,
   0,0,0,0
  },
  /* O Piece */
  {
   0,0,0,0,
   0,1,1,0, 
   0,1,1,0,
   0,0,0,0
  },
  /* S Piece */
  {
   0,0,0,0,
   0,1,1,0,
   1,1,0,0,
   0,0,0,0
  },
  /* Z Piece */
  {
   0,0,0,0,
   1,1,0,0,
   0,1,1,0,
   0,0,0,0
  }
};

/* === Tetris Functions === */

void initialise_piece(int data[], int piece) {
  for(int i=0;i!=16;++i) {
     data[i] = piece_array[piece][i]; 
  }
}

void draw_at(int x, int y, int data[], int color) {
   // Center the piece data
   int sx = x - 1;
   int sy = y - 1;
   // Now blast it to the display
   y = sy;
   for(int i=0;i!=4;++i) {
     x = sx;
     for(int j=0;j!=4;++j) {
         // need to clip
         if(x >= 0 && x < 8 && y >= 0 && y < 8) {       
           if(data[(i*4)+j] == 1) {
             display[x][y] = color;
           } 
         }
         x = x + 1;
     }
     y = y + 1;
   }    
}

int has_landed(int data[], int x, int y) {
   // Center the piece data
   int sx = x - 1;
   // Now read the display
   int is_full = 0;
   for(int i=0;i!=4;++i) {
     x = sx;
     for(int j=0;j!=4;++j) {
         // need to clip
         if(data[(i*4)+j] == 1) {   
            if(y == 1) { is_full = 1; }              
            if(y == 8) { 
              // In this case, have reached ground
               return 1; 
            } else if(x >= 0 && x < 8 && y >= 0 
                      && y < 8 && display[x][y] != OFF) {   
              // In this case, have touched existing piece
              return 1 + is_full;               
            }
         }
         x = x + 1;
     }
     y = y + 1;
   }
   return 0;
}

void rotate(int data[]) {
  int tmp[16];
  for(int i=0;i<16;++i) {
     tmp[i] = data[i]; 
  }
  for(int i=0;i<4;++i) {
    for(int j=0;j<4;++j) {
      data[(i*4)+j] = tmp[(j*4)+i];
    }   
  }
}

void fill(int col) {
  for(int i=0;i<8;++i) {
    for(int j=0;j<8;++j) {
       display[i][j] = col; 
    } 
  }
}

void fill_if(int from, int to) {
  for(int i=0;i<8;++i) {
    for(int j=0;j<8;++j) {
      if(display[i][j] == from) {
         display[i][j] = to; 
      }
    } 
  }
}

void end_sequence() {
  fill_if(OFF,YELLOW);
  refresh();
  delay(100);
  fill_if(YELLOW,RED);
  refresh();
  delay(100);
  fill_if(RED,GREEN);
  refresh();
  delay(500);
}

/* === Game Loop === */

int landed = 1; // indicates whether current drop finished
int piece_num = 0;
int piece_col = 0;
int piece[16];
int x = 3;
int y = -2;

void loop() {
  if(landed == 2) {
    // Game over
    end_sequence();
    fill(OFF);
    landed = 1; // reset         
  } else if(landed == 1) {
    initialise_piece(piece,piece_num);
    piece_num = (piece_num + 1) % 6;
    piece_col = (piece_col + 1) % 3;
    landed = 0;
    x = 3;
    y = -2;
  } else {
    // First, take piece off board
    draw_at(x,y,piece,OFF);
    // Now, apply user actions
    int joy_x = read_joystick(JOYSTICK_X);
    if(joy_x < 2) {
       x = x + 1;
    } else if(joy_x > 6) {
       x = x - 1; 
    }
    int joy_y = read_joystick(JOYSTICK_Y);
    if(joy_y > 6) {
       rotate(piece); 
    }
    // Now, apply gravity (if possible)
    landed = has_landed(piece,x,y);
    if(landed == 0) {
      // Gravity applies!
      y = (y + 1) % 8;
    }
    // Third put piece on board in 
    // new position
    draw_at(x,y,piece,piece_col+1);
    // Refresh display
    refresh();  
  }
  // Add pause
  delay(25);
}
