//Updates the raw values stored with new one after requesting them from the UNO
void measureMethod(void* dataPtr) {
  measureDataStruct* measureDataPtr = (measureDataStruct*)(dataPtr);

  int n = *(measureDataPtr->tempIndex);
  int p = *(measureDataPtr->pressIndex);
  int q = *(measureDataPtr->rateIndex);
  int m = *(measureDataPtr->respirationIndex);
  unsigned int unoReturn = local_comms('M', *(measureDataPtr->whichData), 0);


  if (*(measureDataPtr->whichData) == 80) {//pulse
    double pulses = (double) unoReturn;
    if (pulses > *(measureDataPtr->pulseRateRaw + q) * 1.15 || pulses < *(measureDataPtr->pulseRateRaw + q) * 0.85) {
      *(measureDataPtr->rateIndex) = (q + 1) % 8; 
      q = *(measureDataPtr->rateIndex);
      *(measureDataPtr->measurePulse) = 1;
      *(measureDataPtr->pulseRateRaw + q) = (unsigned int)pulses;
    }
  } else if (*(measureDataPtr->whichData) == 66) {//Btemp
    double heat = (double) unoReturn;
    if (heat > *(measureDataPtr->temperatureRaw + n) * 1.15 || heat < *(measureDataPtr->temperatureRaw + n) * 0.85) {
      *(measureDataPtr->tempIndex) = (n + 1) % 8;
      *(measureDataPtr->temperatureRaw + *(measureDataPtr->tempIndex)) = unoReturn;
      *(measureDataPtr->measureTemp) = 1;
    }
  } else if (*(measureDataPtr->whichData) == 83) {//S
    *(measureDataPtr->measureSystolic) = 1;
    *(measureDataPtr->pressIndex) = (p + 1) % 8;
    p = *(measureDataPtr->pressIndex);
    *(measureDataPtr->pressRaw + p) = unoReturn;
    *(measureDataPtr->pressRaw + p + 8) = local_comms('M', 'D',0);
  } else if (*(measureDataPtr->whichData) == 82) {
    double breaths = (double) unoReturn;
    if (breaths > *(measureDataPtr->respirationRaw + m) * 1.15 || breaths < *(measureDataPtr->respirationRaw + m) * 0.85) {
    
      *(measureDataPtr->respirationIndex) = (m+1) % 8;
      *(measureDataPtr->respirationRaw + m) = unoReturn;
      *(measureDataPtr->measureRes) = 1;
    }
  }
  measureAck(*(measureDataPtr->whichData));
  insert(computeTask);
  insert(warningTask);
}
