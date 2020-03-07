void pressMeasure(unsigned int *systolicPressRaw, unsigned int *diastolicPressRaw, unsigned int *pressCalls) {
  int complete = 0;
  int systolicDone = 0;
  long startTime = 0;
  currentPressure = 0;

  attachInterrupt(digitalPinToInterrupt(pressureInterruptPin), incrementPressure, RISING);

  while (!complete) {
    if (millis() - startTime > 5) {
      startTime = millis();
      if ((currentPressure > 110 && currentPressure < 150) && !systolicDone) {
        *systolicPressRaw = currentPressure;
        systolicDone = 1;
      }
      if (systolicDone && (currentPressure > 50 && currentPressure < 80)) {
        *diastolicPressRaw = currentPressure;
        complete = 1;
      }
    }
  }
  detachInterrupt(digitalPinToInterrupt(pressureInterruptPin));
  sender(*systolicPressRaw);
}

void incrementPressure() {
  if (digitalRead(switchPin) == HIGH) {
    currentPressure = currentPressure + incrementAmount;
  } else {
    currentPressure = currentPressure - incrementAmount;
  }
}
