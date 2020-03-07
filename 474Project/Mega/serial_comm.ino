//This function checks to see if their are any warnings present in the system,
//If there is a warning, all raw measurements are then formatted and sent to the serial moniter
//PARAMS:
//dataPtr: a void pointer to the serial task's datastruct
void serialMethod(void* dataPtr) {
  serialDataStruct* serialDataPtr = (serialDataStruct*)(dataPtr);

  int n = *(serialDataPtr->tempIndex);
  int p = *(serialDataPtr->pressIndex);
  int q = *(serialDataPtr->rateIndex);
  int m = *(serialDataPtr->respirationIndex);
  
  Serial.println("$");
  Serial.println("K");
  Serial.println("A");
  Serial.println("==========================================");
  Serial.print("Temperature: ");
  Serial.print(*(serialDataPtr->temperatureCorrected + n));
  Serial.println(" C");
  Serial.print("Systolic pressure: ");
  Serial.print(*(serialDataPtr->pressCorrected + p));
  Serial.println(" mm HG");
  Serial.print("Diastolic pressure: ");
  Serial.print(*(serialDataPtr->pressCorrected + p + 8));
  Serial.println(" mm HG");
  Serial.print("Pulse rate: ");
  Serial.print(*(serialDataPtr->pulseRateCorrected + q));
  Serial.println(" BPM");
  Serial.print("Respiration Rate: ");
  Serial.print(*(serialDataPtr->respirationCorrected + q));
  Serial.println(" RR");
  Serial.print("Battery:  ");
  Serial.println(*(serialDataPtr->batteryState));
  Serial.println("==========================================");
  Serial.println("&");
  
}
