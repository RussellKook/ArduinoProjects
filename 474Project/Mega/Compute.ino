//translates the raw values from measurements to human readable values in the appropriate units
void computeMethod(void* dataPtr){
  computeDataStruct* computeDataPtr = (computeDataStruct*)(dataPtr);
  
  int n = *(computeDataPtr->tempIndex);
  int p = *(computeDataPtr->pressIndex);
  int q = *(computeDataPtr->rateIndex);
  int m = *(computeDataPtr->respirationIndex);
  
  *(computeDataPtr->temperatureCorrected + n) = (5 + .75 * ( *(computeDataPtr->temperatureRaw + n) / 10));
  *(computeDataPtr->pressCorrected + p) = 9 + 2.0 * *(computeDataPtr->pressRaw + p);
  *(computeDataPtr->pressCorrected + p + 8) = (6 + 1.5 * *(computeDataPtr->pressRaw + p + 8));
  *(computeDataPtr->pulseRateCorrected + q) = 8 + (3.0 * *(computeDataPtr->pulseRateRaw + q)); 
  *(computeDataPtr->respirationCorrected + m) = 7 + (3.0 * *(computeDataPtr->respirationRaw + m));
  
}
