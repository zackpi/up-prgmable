#define INSTR LOW
#define DATA HIGH

#define RS 3
#define RW 4
#define E 5

#define DB4 6
#define DB5 7
#define DB6 8
#define DB7 9

void setup() {
  pinMode(RS, OUTPUT);
  pinMode(RW, OUTPUT);
  pinMode(E, OUTPUT);
  
  pinMode(DB4, OUTPUT);
  pinMode(DB5, OUTPUT);
  pinMode(DB6, OUTPUT);
  pinMode(DB7, OUTPUT);
  
  lcdInit();
}
  
void loop() {
  
}


bool lcdBusy(){
  // setup read from Busy Flag
  digitalWrite(RS, LOW);
  digitalWrite(RW, HIGH);
  digitalWrite(E, HIGH);
  
  // read BF
  bool busy = digitalRead(DB7);
  
  // complete operation
  digitalWrite(E, LOW);
  digitalWrite(E, HIGH);
  digitalWrite(E, LOW);
  
  return busy;
}

void lcdWriteNibb(bits4, rs){
  digitalWrite(RS, rs);
  digitalWrite(RW, LOW);
   
  digitalWrite(E, HIGH);
  digitalWrite(DB4, bits4 & 0x1);
  digitalWrite(DB5, bits4 & 0x2);
  digitalWrite(DB6, bits4 & 0x4);
  digitalWrite(DB7, bits4 & 0x8);
  digitalWrite(E, LOW);
}

void lcdWriteByte(bits8, rs){
  lcdWriteNibb((bits8 & 0xF0) >> 4, rs);
  lcdWriteNibb(bits8 & 0xF, rs);
}

void lcdWriteString(char str[], int len){
  for(int i = 0; i < len; i++){
    lcdWriteByte(str[i], DATA);
  }
}

void lcdInit(){
  /*
  run this before interacting with the LCD
  and only run it once (best to use it during setup)
  */

  // intercept 8-bit operation during startup
  delay(50);
  lcdWriteNibb(0x3, INSTR);
  delay(10);
  lcdWriteNibb(0x3, INSTR);
  delay(1);
  lcdWriteNibb(0x3, INSTR);
  
  // enable 4-bit operation
  lcdWriteNibb(0x2, INSTR);
  
  // Function Set: 0 0 1 DL N F X X    (X = dont care)
  // DL=0 for 4-bit op, N=1 for 2 lines, F=0 for 5x8 font
  while(lcdBusy());
  lcdWriteByte(0x28, INSTR);
  
  // Display On/Off: 0 0 0 0 1 D C B
  // D=1 for display on, C=1 for cursor on, B=1 for blinking cursor char
  while(lcdBusy());
  lcdWriteByte(0x0F, INSTR);
  
  // Display Clear: 0 0 0 0 0 0 0 1
  while(lcdBusy());
  lcdWriteByte(0x01, INSTR);
  
  
  // Entry Mode Set: 0 0 0 0 0 1 I/D S
  // I/D = 1 for inc DDRAM addr, S=0 for no screen-shift
  while(lcdBusy());
  lcdWriteByte(0x06, INSTR);
}

