//This function decrements the battery value as often as five seconds
//PARAMS:
//dataPtr: the void pointer to status's datastruct
void statusMethod(void* dataPtr){

  statusDataStruct* statusDataPtr = (statusDataStruct*)(dataPtr);
  if ((millis()/100 - startTimeStatus) >= 50) {
    startTimeStatus = millis()/100;
    unsigned short* battery = statusDataPtr->batteryState;
    *(statusDataPtr->batteryState) = *(statusDataPtr->batteryState) - 1;
    if (*(statusDataPtr->batteryState) > 250) {
      *(statusDataPtr->batteryState) = 0;
    }
  }

}
