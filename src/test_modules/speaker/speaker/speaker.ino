#include <notes.h>

#define Cn6 1046.50

#define SPKR 8     // pin for speaker power
#define BPM 134    // beats per minute
#define TIMESIG 4  // quarter note is one beat
#define NUM_NOTES 11

double note[] = {Cn5, En5, Fn5, Gn5, Cn6, Bn5, REST, An5, Bn5, An5, REST};
double dur[] = {8, 4, 4, 4, 4, 4, 8, 16, 16, 4, 4};

void setup(){
  Serial.begin(9600);
}

void loop(){
  double us_per_beat = 60*1000.0/BPM*1000;
  
  for(int i = 0; i < NUM_NOTES; i++){
    if(note[i]){
      tone(SPKR, note[i]);
    }else{
      noTone(SPKR);
    }
    
    double notes_per_beat = dur[i]/TIMESIG;
    long us_per_note = round(us_per_beat/notes_per_beat);
    unsigned int us_remainder = us_per_note % 1000;
    unsigned int ms_quotient = us_per_note / 1000;
    
    delay(ms_quotient);
    delayMicroseconds(us_per_note);
  }
  
  noTone(SPKR);
  delay(750);
}
