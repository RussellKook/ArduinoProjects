//This method is to AtoDC the incoming square wave 
//will read incoming wave for 10 seconds and return
//beats per minute

void readAnalogWave(unsigned int *pulseRateRaw, const byte interruptPin) {
  long startTime = millis();
  pulseCounter = 0;
  attachInterrupt(digitalPinToInterrupt(interruptPin), countPulse, RISING);
  while(millis() - startTime < 10000) {
    
  }
  detachInterrupt(digitalPinToInterrupt(interruptPin));
  *pulseRateRaw = pulseCounter * 6;
  sender(pulseRateRaw);
}

void countPulse(){
   pulseCounter++;
}
