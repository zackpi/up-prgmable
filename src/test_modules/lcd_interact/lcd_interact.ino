#define INSTR LOW
#define DATA HIGH

#define RS 3
#define RW 4
#define E 5

#define DB4 10
#define DB5 11
#define DB6 12
#define DB7 13

unsigned long sec = 0;
int c = 0;

boolean lcdBusy(){
  // setup read from Busy Flag
  digitalWrite(RS, LOW);
  digitalWrite(RW, HIGH);
  digitalWrite(E, HIGH);
  
  // read BF
  boolean busy = digitalRead(DB7);
  
  // complete operation
  digitalWrite(E, LOW);
  digitalWrite(E, HIGH);
  digitalWrite(E, LOW);
  
  return busy;
}

void lcdSendNibb(byte bits4, int rs){
  digitalWrite(RS, rs);
  digitalWrite(RW, LOW);
   
  digitalWrite(DB4, bits4 & 0x1);
  digitalWrite(DB5, bits4 & 0x2);
  digitalWrite(DB6, bits4 & 0x4);
  digitalWrite(DB7, bits4 & 0x8);
  
  digitalWrite(E, HIGH);
  digitalWrite(E, LOW);
}

void lcdWriteByte(byte bits8, int rs){
  if(rs == DATA && (bits8 < 0x20 || (bits8 > 0x7F && bits8 < 0xA1))){
    lcdSendNibb(0xF, DATA);
    lcdSendNibb(0xF, DATA);
  }else{
    lcdSendNibb((bits8 & 0xF0) >> 4, rs);
    lcdSendNibb(bits8 & 0xF, rs);
  }
  lcdBusy();
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
  delay(100);
  lcdSendNibb(0x3, INSTR);
  delay(10);
  lcdSendNibb(0x3, INSTR);
  delay(5);
  lcdSendNibb(0x3, INSTR);
  
  // enable 4-bit operation
  lcdSendNibb(0x2, INSTR);
  
  // Function Set: 0 0 1 DL N F X X    (X = dont care)
  // DL=0 for 4-bit op, N=1 for 2 lines, F=0 for 5x8 font
  lcdSendNibb(0x2, INSTR);
  lcdSendNibb(0x8, INSTR);
  
  // Display On/Off: 0 0 0 0 1 D C B
  // D=1 for display on, C=1 for cursor on, B=1 for blinking cursor char
  lcdSendNibb(0x0, INSTR);
  lcdSendNibb(0xF, INSTR);
  
  // Display Clear: 0 0 0 0 0 0 0 1
  lcdSendNibb(0x0, INSTR);
  lcdSendNibb(0x1, INSTR);
  
  // Entry Mode Set: 0 0 0 0 0 1 I/D S
  // I/D = 1 for inc DDRAM addr, S=0 for no screen-shift
  lcdSendNibb(0x0, INSTR);
  lcdSendNibb(0x6, INSTR);
}

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
  for(int i = 0; i < 16; i++)
    lcdWriteString("Jenna", 5);
  
  lcdWriteByte(0x20, DATA);
  delay(250);
}

