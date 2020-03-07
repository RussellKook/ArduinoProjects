//This functions does the job of doing the bulk of initializeation for the system.
void startUp() {

  TCB Measure;
  TCB Compute;
  TCB Display;
  TCB Status;
  TCB Warning;
  TCB Keypad;
  TCB mySerial;
  
  //declare struct for data
  measureDataStruct measureData; 
  computeDataStruct computeData;
  displayDataStruct displayData;
  statusDataStruct statusData;
  warningDataStruct warningData;
  keypadDataStruct keypadData;
  serialDataStruct serialData;

  //assign dataPtr in TCB to void data structs from signal0 file
  Measure.dataPtr = (void*)&measureData;
  Compute.dataPtr = (void*)&computeData;
  Display.dataPtr = (void*)&displayData;
  Status.dataPtr = (void*)&statusData;
  Warning.dataPtr = (void*)&warningData; 
  Keypad.dataPtr = (void*)&keypadData;
  mySerial.dataPtr = (void*)&serialData;

  //assign task* to the corresponding method
  Measure.task = measureMethod;
  Compute.task = computeMethod;
  Display.task = displayMethod;
  Status.task = statusMethod;
  Warning.task = warningMethod;
  Keypad.task = keypadMethod;
  mySerial.task = serialMethod;
  

  //assign next pointers to null
  Measure.next = NULL;
  Compute.next = NULL;
  Display.next = NULL;
  Status.next = NULL;
  Warning.next = NULL;
  Keypad.next = NULL;
  mySerial.next = NULL;
  tail = NULL;
  
  Measure.prev = NULL;
  Compute.prev = NULL;
  Display.prev = NULL;
  Status.prev = NULL;
  Warning.prev = NULL;
  Keypad.prev = NULL;
  mySerial.next = NULL;
  head = NULL;
  
  /*
  unsigned int temptempraw[8] = {temperatureRaw};
  unsigned int* temppressraw = pressRaw;
  unsigned int temppulseraw[8] = {pulseRateRaw};
  */
  
  // * modified declarations
  //assigning measure variable pointers
  measureData.temperatureRaw = temperatureRaw;
  measureData.pressRaw = pressRaw;
  measureData.pulseRateRaw = pulseRateRaw;
  measureData.respirationRaw = respirationRaw;
  measureData.whichData = &whichData;
  measureData.respirationIndex = &respirationIndex;
  measureData.tempIndex = &tempIndex;
  measureData.pressIndex = &pressIndex;
  measureData.rateIndex = &rateIndex;
  measureData.measureSystolic = &measureSystolic;  
  measureData.measureTemp = &measureTemp; 
  measureData.measurePulse = &measurePulse; 
  measureData.measureRes = &measureRes;
  
  //assigning compute variable pointers
  computeData.temperatureRaw = temperatureRaw;
  computeData.pressRaw = pressRaw;
  computeData.pulseRateRaw = pulseRateRaw;
  computeData.temperatureCorrected = temperatureCorrected;
  computeData.respirationRaw = respirationRaw;
  computeData.pressCorrected = pressCorrected;
  computeData.pulseRateCorrected = pulseRateCorrected;
  computeData.respirationCorrected = respirationCorrected;
  computeData.tempIndex = &tempIndex;
  computeData.pressIndex = &pressIndex;
  computeData.rateIndex = &rateIndex;
  computeData.respirationIndex = &respirationIndex;
  
  //assigning display varaible pointeres
  displayData.temperatureCorrected = temperatureCorrected;
  displayData.pressCorrected = pressCorrected;
  displayData.pulseRateCorrected = pulseRateCorrected;
  displayData.respirationCorrected = respirationCorrected;
  displayData.batteryState = &batteryState;
  displayData.tempIndex = &tempIndex;
  displayData.pressIndex = &pressIndex;
  displayData.rateIndex = &rateIndex;
  displayData.respirationIndex = &respirationIndex;
  displayData.depressedSystolic = &depressedSystolic;
  displayData.depressedRespiration = &depressedRespiration;
  displayData.depressedTemp = &depressedTemp;
  displayData.depressedPulse = &depressedPulse;
  displayData.mode = &mode;
  displayData.alarmAckS =  &alarmAckS;
  displayData.alarmAckP =  &alarmAckP;
  displayData.alarmAckR =  &alarmAckR;
  displayData.alarmAckT =  &alarmAckT;

  
  //assign status variable pointer
  statusData.batteryState = &batteryState;
  
  //assign warning variable pointers
  warningData.temperatureRaw = temperatureRaw;
  warningData.pressRaw = pressRaw;
  warningData.pulseRateRaw = pulseRateRaw;
  warningData.respirationRaw = respirationRaw;
  warningData.tempIndex = &tempIndex;
  warningData.pressIndex = &pressIndex;
  warningData.rateIndex = &rateIndex;
  warningData.respirationIndex = &respirationIndex;
  warningData.depressedSystolic = &depressedSystolic;
  warningData.depressedRespiration = &depressedRespiration;
  warningData.depressedTemp = &depressedTemp;
  warningData.depressedPulse = &depressedPulse;
  warningData.batteryState = &batteryState;
  warningData.displaySerial = &displaySerial;
  warningData.measureSystolic = &measureSystolic;
  warningData.measureTemp = &measureTemp; 
  warningData.measurePulse = &measurePulse; 
  warningData.measureRes = &measureRes;
  
  //keypad
  keypadData.depressedSystolic = &depressedSystolic;
  keypadData.depressedRespiration = &depressedRespiration;
  keypadData.depressedTemp = &depressedTemp;
  keypadData.depressedPulse = &depressedPulse;
  keypadData.mode = &mode;
  keypadData.alarmAckS =  &alarmAckS;
  keypadData.alarmAckT =  &alarmAckT;
  keypadData.alarmAckP =  &alarmAckP;
  keypadData.alarmAckR =  &alarmAckR;
  keypadData.whichData = &whichData;
  keypadData.enableRemote = &enableRemote;
  keypadData.remoteInput = &remoteInput;
  
  //serial
  serialData.temperatureCorrected = temperatureCorrected;
  serialData.pressCorrected = pressCorrected;
  serialData.pulseRateCorrected = pulseRateCorrected;
  serialData.respirationCorrected = respirationCorrected;
  serialData.respirationIndex = &respirationIndex;
  serialData.tempIndex = &tempIndex;
  serialData.pressIndex = &pressIndex;
  serialData.rateIndex = &rateIndex;
  serialData.batteryState = &batteryState;
  serialData.displaySerial = &displaySerial;
  
  displaySerial = 0; 
  depressedSystolic = 0;
  tempIndex = 0;
  rateIndex = 0;
  pressIndex = 0;
  
  //seperate VOID pointer to call the variable structs 
  void *measureDataPtr = (void*)(&measureData);
  void *computeDataPtr = (void*)(&computeData);
  void *displayDataPtr = (void*)(&displayData);
  void *statusDataPtr = (void*)(&statusData);
  void *warningDataPtr = (void*)(&warningData);
  void *keypadDataPtr = (void*)(&keypadData);
  void *serialDataPtr = (void*)(&serialData);
  
  measureTask = &Measure;
  computeTask = &Compute;
  statusTask = &Status;
  warningTask = &Warning;
  displayTask = &Display;
  keypadTask = &Keypad;
  serialTask = &mySerial;
  
  setupTftDisplay(); 
  
  Serial1.begin(9600);
  Serial.begin(9600); // this is for debugging
  int check = initialize();
  insert(computeTask);
  insert(warningTask);

}

//prepares the TFT display
void setupTftDisplay() {
  Serial.println(F("TFT LCD test"));
  
  
  #ifdef USE_Elegoo_SHIELD_PINOUT
    Serial.println(F("Using Elegoo 2.4\" TFT Arduino Shield Pinout"));
  #else
    Serial.println(F("Using Elegoo 2.4\" TFT Breakout Board Pinout"));
  #endif
  
    Serial.print("TFT size is "); Serial.print(tft.width()); Serial.print("x"); Serial.println(tft.height());
  
    tft.reset();
  
     uint16_t identifier = tft.readID();
     if(identifier == 0x9325) {
      Serial.println(F("Found ILI9325 LCD driver"));
    } else if(identifier == 0x9328) {
      Serial.println(F("Found ILI9328 LCD driver"));
    } else if(identifier == 0x4535) {
      Serial.println(F("Found LGDP4535 LCD driver"));
    }else if(identifier == 0x7575) {
      Serial.println(F("Found HX8347G LCD driver"));
    } else if(identifier == 0x9341) {
      Serial.println(F("Found ILI9341 LCD driver"));
    } else if(identifier == 0x8357) {
      Serial.println(F("Found HX8357D LCD driver"));
    } else if(identifier==0x0101)
    {     
        identifier=0x9341;
         Serial.println(F("Found 0x9341 LCD driver"));
    }
    else if(identifier==0x1111)
    {     
        identifier=0x9328;
         Serial.println(F("Found 0x9328 LCD driver"));
    }
    else {
      Serial.print(F("Unknown LCD driver chip: "));
      Serial.println(identifier, HEX);
      Serial.println(F("If using the Elegoo 2.8\" TFT Arduino shield, the line:"));
      Serial.println(F("  #define USE_Elegoo_SHIELD_PINOUT"));
      Serial.println(F("should appear in the library header (Elegoo_TFT.h)."));
      Serial.println(F("If using the breakout board, it should NOT be #defined!"));
      Serial.println(F("Also if using the breakout, double-check that all wiring"));
      Serial.println(F("matches the tutorial."));
      identifier=0x9328;
    
    }
    tft.begin(identifier);
  tft.setRotation(2);

  tft.fillScreen(BLACK);

  pinMode(13, OUTPUT);
}

//gives variables their propper initial values by calling the UNO to do the same
//the UNO keeps the record of propper initial values.
int initialize() {
  local_comms('I','I', 0);
  temperatureRaw[0] = 750;
  pressRaw[0] = 80;
  pressRaw[8] = 80;
  pulseRateRaw[0] = 50;
  respirationRaw[0] = 0;
  batteryState = 200;
  enableRemote = 1;
  remoteInput = 'E';
}
