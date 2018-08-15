#define F_SMP 40000  // 40kHz sample rate allows up to 20kHz frequencies. Human ears can perceive 20Hz - 20kHz range
#define US_PER_SMP 25 // (1M us/s) / (40k smp/s) = 25 us

typedef struct VOICE{
  int state;
  int note;
  int start;
  int dur;
}voice;

voice v1, v2, v3, v4;
unsigned long next, last, count, del;

void setup(){
  v1 = {0, 0, 0, 0};
  v2 = {0, 0, 0, 0};
  v3 = {0, 0, 0, 0};
  v4 = {0, 0, 0, 0};
  
  last = millis();
}

void loop(){
  next = last + US_PER_SMP
  
  // computations
  count++;
  if(count % F_SMP == 0){
    Serial.println(count/F_SMP);
    Serial.println("\t" + del);
    del = 0;
  }
  
  while(millis() < next){
    del++;
  }
}

