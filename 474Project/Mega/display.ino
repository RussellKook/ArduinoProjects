//The display function
//When called this function will replace what is on the screen with whatever information
//is currently stored in the display tcb
void displayMethod(void* dataPtr) {//i am passing in the variable struct pointer
  displayDataStruct* displayDataPtr = (displayDataStruct*)(dataPtr);
  
  if(*(displayDataPtr->mode))
  {
    tft.setCursor(0, 0);//set curser to top left
    tft.setTextSize(1);//size 1
    tft.setTextColor(GREEN);
  
    int n = *(displayDataPtr->tempIndex);
    int p = *(displayDataPtr->pressIndex);
    int q = *(displayDataPtr->rateIndex);
    int r = *(displayDataPtr->respirationIndex);

    static int timesCalled = 0;
    static int cP = 0;
    static int cT = 0;
    static int cPR = 0;
    static int cRR = 0;
    
    timesCalled = timesCalled + 1;

    if(cP)
      cP = 0;
    else
      cP = 1;

    if(timesCalled % 2 == 0)
    {
      if(cT) 
        cT = 0;
      else
        cT = 1;
    }

    if(timesCalled % 4 == 0)
    {
      if(cPR) 
        cPR = 0;
      else
        cPR = 1;
    }

    if(timesCalled % 3 == 0)
    {
      if(cRR) 
        cRR = 0;
      else
        cRR = 1;
    }
    
    double* temper = displayDataPtr->temperatureCorrected + n;
    double* systolic = displayDataPtr->pressCorrected + p;
    double* diastolic = displayDataPtr->pressCorrected + p + 8;
    double* pulse = displayDataPtr->pulseRateCorrected + q;
    double* respiration = displayDataPtr->respirationCorrected + r;
    unsigned short* battery = displayDataPtr->batteryState;
    
    *(displayDataPtr->alarmAckS) = (*(systolic) > 156 || *(systolic) < 96) && !*(displayDataPtr->depressedSystolic);
    *(displayDataPtr->alarmAckT) = (*(temper) > 43.47 || *(temper) < 30.685) && !*(displayDataPtr->depressedTemp);
    *(displayDataPtr->alarmAckP) = (*(pulse) > 115 || *(pulse) < 51)  && !*(displayDataPtr->depressedPulse);
    *(displayDataPtr->alarmAckR) = (*(respiration) > 28.75 || *(respiration) < 10.2) && !*(displayDataPtr->depressedRespiration);

    //systolic
    if(sBpHigh)
    {
      if(*(displayDataPtr->alarmAckS))
      {
        tft.setTextColor(RED);
        tft.print("Systolic pressure: ");
        tft.print(*(systolic),0);
        tft.println("mm Hg");
      } 
      else if((*(systolic) > 156 || *(systolic) < 96) && *(displayDataPtr->depressedSystolic))
      {
        tft.setTextColor(ORANGE);
        tft.print("Systolic pressure: ");
        tft.print(*(systolic),0);
        tft.println("mm Hg");
      }
      else if(cP)
      {
        tft.setTextColor(ORANGE);
        tft.print("Systolic pressure: ");
        tft.print(*(systolic),0);
        tft.println("mm Hg");
      }
      else
      {
        tft.setTextColor(WHITE);
        tft.print("Systolic pressure: ");
        tft.print(*(systolic),0);
        tft.println("mm Hg");
      }
    }
    else
    {
      tft.setTextColor(GREEN);
      tft.print("Systolic pressure: ");
      tft.print(*(systolic),0);
      tft.println("mm Hg");
    }

    //diastolic
    if (dBpHigh) {//bad
      if(cP){
        tft.setTextColor(ORANGE);
        tft.print("Diastolic pressure: ");
        tft.print(*(diastolic),0);
        tft.println("mm Hg");
      } else{//good
        tft.setTextColor(WHITE);
        tft.print("Diastolic pressure: ");
        tft.print(*(diastolic),0);
        tft.println("mm Hg");
      }
    }
    else {
      tft.setTextColor(GREEN);
      tft.print("Diastolic pressure: ");
      tft.print(*(diastolic),0);
      tft.println("mm Hg");
    }

    //temperature
    if (tempHigh) {//bad
      if(*(displayDataPtr->alarmAckT)) {
        tft.setTextColor(RED);
        tft.print("Temperature: ");
        tft.print(*(temper),0);
        tft.println("C");
      } else if((*(temper) > 43.47 || *(temper) < 30.685) && *(displayDataPtr->depressedTemp)){//good
        tft.setTextColor(ORANGE);
        tft.print("Temperature: ");
        tft.print(*(temper),0);
        tft.println("C");
      } else if(cT){
        tft.setTextColor(ORANGE);
        tft.print("Temperature: ");
        tft.print(*(temper),0);
        tft.println("C");
      } else {
        tft.setTextColor(WHITE);
        tft.print("Temperature: ");
        tft.print(*(temper),0);
        tft.println("C");
      }
    }
    else {
        tft.setTextColor(GREEN);
        tft.print("Temperature: ");
        tft.print(*(temper),0);
        tft.println("C");
      }

    //pulse
    if (pulseLow) {
      if(*(displayDataPtr->alarmAckP)){
        tft.setTextColor(RED);
        tft.print("Pulse rate: ");
        tft.print(*(pulse),0);
        tft.println("bpm");
      } else if((*(pulse) > 115 || *(pulse) < 51)  && *(displayDataPtr->depressedPulse)) {//good
        tft.setTextColor(ORANGE);
        tft.print("Pulse rate: ");
        tft.print(*(pulse),0);
        tft.println("bpm");
      } else if(cPR){
        tft.setTextColor(ORANGE);
        tft.print("Pulse rate: ");
        tft.print(*(pulse),0);
        tft.println("bpm");
      } else {
        tft.setTextColor(WHITE);
        tft.print("Pulse rate: ");
        tft.print(*(pulse),0);
        tft.println("bpm");
      }
    } else{
        tft.setTextColor(GREEN);
        tft.print("Pulse rate: ");
        tft.print(*(pulse),0);
        tft.println("bpm");
    }

    //respiration
    if (respirationLow) {
      if(*(displayDataPtr->alarmAckR)){
        tft.setTextColor(RED);
        tft.print("Respiration Rate: ");
        tft.print(*(respiration),0);
        tft.println("bpm");
      } else if((*(respiration) > 28.75 || *(respiration) < 10.2) && *(displayDataPtr->depressedRespiration)) {//good
        tft.setTextColor(ORANGE);
        tft.print("Respiration Rate: ");
        tft.print(*(respiration),0);
        tft.println("bpm");
      } else if(cRR){
        tft.setTextColor(ORANGE);
        tft.print("Respiration Rate: ");
        tft.print(*(respiration),0);
        tft.println("bpm");
      } else {
        tft.setTextColor(WHITE);
        tft.print("Respiration Rate: ");
        tft.print(*(respiration),0);
        tft.println("bpm");
      }
    } else{
        tft.setTextColor(GREEN);
        tft.print("Respiration Rate: ");
        tft.print(*(respiration),0);
        tft.println("bpm");
    }

    //battery
    if (*battery <= 40) {
      tft.setTextColor(RED);
      tft.print("Battery: ");
      tft.setTextColor(BLACK);
      tft.print(*(battery));
      tft.setCursor(0, 0);
      tft.print("\n\n\n\n\n");
      tft.setTextColor(RED);
      tft.print("Battery: ");
      tft.setTextColor(BLACK);
      tft.print(*(battery) + 1);
      tft.setCursor(0, 0);
      tft.print("\n\n\n\n\n");
      tft.setTextColor(RED);
      tft.print("Battery: ");
      tft.print(*(battery));
    } else {//good
      tft.setTextColor(GREEN);
      tft.print("Battery: ");
      tft.setTextColor(BLACK);
      tft.print(*(battery));
      tft.setCursor(0, 0);
      tft.print("\n\n\n\n\n");
      tft.setTextColor(GREEN);
      tft.print("Battery: ");
      tft.setTextColor(BLACK);
      tft.print(*(battery) + 1);
      tft.setCursor(0, 0);
      tft.print("\n\n\n\n\n");
      tft.setTextColor(GREEN);
      tft.print("Battery: ");
      tft.print(*(battery));
    }

    tft.drawRect(0, 3*BOXSIZE/2, BOXSIZE, BOXSIZE, WHITE);
    tft.drawRect(BOXSIZE, BOXSIZE, BOXSIZE, BOXSIZE/3, WHITE);
    tft.drawRect(BOXSIZE, 4*BOXSIZE/3, BOXSIZE, BOXSIZE/3, WHITE);
    tft.drawRect(BOXSIZE, 5*BOXSIZE/3, BOXSIZE, BOXSIZE/3, WHITE);
    tft.drawRect(BOXSIZE, 2*BOXSIZE, BOXSIZE, BOXSIZE/3, WHITE);
    
    tft.setTextSize(3);
    tft.setTextColor(WHITE);
    
    tft.setCursor(8,45 + 3*BOXSIZE/2);
    tft.print("BACK");

    tft.setTextSize(1);
    
    if(*(displayDataPtr->alarmAckS))
    {
      tft.setCursor(8 + BOXSIZE,12 + BOXSIZE);
      tft.print("Systolic!");
    }
    if(*(displayDataPtr->alarmAckT))
    {
      tft.setCursor(8 + BOXSIZE,12 + 4*BOXSIZE/3);
      tft.print("Temperature!");
    }
    if(*(displayDataPtr->alarmAckP))
    {
      tft.setCursor(8 + BOXSIZE,12 + 5*BOXSIZE/3);
      tft.print("Pulse!");
    }
    if(*(displayDataPtr->alarmAckR))
    {
      tft.setCursor(8 + BOXSIZE,12 + 2*BOXSIZE);
      tft.print("Respiration!");
    }
  }
  else
  {
    int n = *(displayDataPtr->tempIndex);
    int p = *(displayDataPtr->pressIndex);
    int q = *(displayDataPtr->rateIndex);
    int r = *(displayDataPtr->respirationIndex);

    double* temper = displayDataPtr->temperatureCorrected + n;
    double* systolic = displayDataPtr->pressCorrected + p;
    double* diastolic = displayDataPtr->pressCorrected + p + 8;
    double* pulse = displayDataPtr->pulseRateCorrected + q;
    double* respiration = displayDataPtr->respirationCorrected + r;
     
     tft.fillRect(0, 0, BOXSIZE*2, BOXSIZE/2, MAGENTA);
     tft.fillRect(0, BOXSIZE/2, BOXSIZE*2, BOXSIZE/2, WHITE);
     tft.fillRect(0, BOXSIZE, BOXSIZE*2, BOXSIZE/2, MAGENTA);
     tft.fillRect(0, 3*BOXSIZE/2, BOXSIZE*2, BOXSIZE/2, WHITE);
    
     tft.setTextSize(2);
     tft.setTextColor(BLACK);
    
     tft.setCursor(8, 12);
     tft.println("Temperature");
     tft.setTextSize(1);
     tft.print(*(temper),0);
     tft.print("C");
    
     tft.setTextSize(2);
     tft.setCursor(8, 12 + BOXSIZE/2);
     tft.println("Blood Pressure");
     tft.setTextSize(1);
     tft.print(*(systolic),0);
     tft.print("/");
     tft.print(*(diastolic),0);
     tft.print("mm Hg");
    
     tft.setTextSize(2);
     tft.setCursor(8, 12 + BOXSIZE);
     tft.println("Pulse Rate");
     tft.setTextSize(1);
     tft.print(*(pulse),0);
     tft.print("bpm");

     tft.setTextSize(2);
     tft.setCursor(8, 12 + 3*BOXSIZE/2);
     tft.println("Respiration Rate");
     tft.setTextSize(1);
     tft.print(*(respiration),0);
     tft.print("bpm");

     tft.drawRect(0, 2*BOXSIZE, BOXSIZE, BOXSIZE/2, WHITE);
    
     tft.setTextSize(3);
     tft.setTextColor(WHITE);
    
     tft.setCursor(8,20 + 2*BOXSIZE);
     tft.print("BACK");

     tft.setTextColor(BLACK);

     tft.setTextSize(1);
    }
}
