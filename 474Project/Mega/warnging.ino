//When this method is called, it will determine if any raw measurement values are out of their
//acceptable ranges
void warningMethod(void* dataPtr) {
  warningDataStruct* warningDataPtr = (warningDataStruct*)(dataPtr);
  int despressedSystolic = *(warningDataPtr->depressedSystolic);
  int depressedPulse = *(warningDataPtr->depressedPulse);
  int depressedTemp = *(warningDataPtr->depressedTemp);
  int depressedRespiration = *(warningDataPtr->depressedRespiration);
  int n = *(warningDataPtr->tempIndex);
  int p = *(warningDataPtr->pressIndex);
  int q = *(warningDataPtr->rateIndex);
  int r = *(warningDataPtr->respirationIndex);
  static int sysCounter = 0;
  static int tempCounter = 0;
  static int pulseCounter = 0;
  static int resCounter = 0;
  if (*(warningDataPtr->temperatureRaw + n) < 390.6 || *(warningDataPtr->temperatureRaw + n) > 462.5) {
    tempHigh = 1;
    if(tempCounter == 4) {
      depressedTemp = 0;
      *(warningDataPtr->depressedTemp) = 0;
      tempCounter = 0;
    }
    if (depressedTemp && *(warningDataPtr->measureTemp)) {
      tempCounter++;
      *(warningDataPtr->measureTemp) = 0;
    }
  } else {
    tempHigh = 0;
    depressedTemp = 0;
    tempCounter = 0;
  }
  
  if (*(warningDataPtr->pulseRateRaw + q) < 16.3 || *(warningDataPtr->pulseRateRaw + q) > 32.3) {
    pulseLow = 1;
    if(pulseCounter == 4) {
      depressedPulse = 0;
      pulseCounter = 0;
    }
    if (depressedPulse && *(warningDataPtr->measurePulse)) {
      pulseCounter++;
      *(warningDataPtr->measurePulse) = 0;
    }
  } else {
    pulseLow = 0;
    depressedPulse = 0;
    pulseCounter = 0;
  }

  //this will be respiration
  
  if (*(warningDataPtr->respirationRaw + r) < 1.5 || *(warningDataPtr->respirationRaw + r) > 6.4) {
    respirationLow = 1;
    if(resCounter == 4) {
      depressedRespiration = 0;
      resCounter = 0;
    }
    if (depressedRespiration && *(warningDataPtr->measureRes)) {
      resCounter++;
      *(warningDataPtr->measureRes) = 0;
    }
  } else {
    respirationLow = 0;
    depressedRespiration = 0;
    resCounter = 0;
  }
  
  if (*(warningDataPtr->pressRaw + p) < 52.5 || *(warningDataPtr->pressRaw + p) > 63.75) {
    if(sysCounter == 4) {
      depressedSystolic = 0;
      sysCounter = 0;
    }
    if (depressedSystolic && *(warningDataPtr->measureSystolic)) {
      sysCounter++;
      *(warningDataPtr->measureSystolic) = 0;
    }
    sBpHigh = 1;
  } else {
    depressedSystolic = 0;
    sysCounter = 0;
    sBpHigh = 0;
  }
  
  if(*(warningDataPtr->pressRaw + p + 8) < 40.3 || *(warningDataPtr->pressRaw + p + 8) > 52) {
    dBpHigh = 1;
  } else {
    dBpHigh = 0;
  }
}
