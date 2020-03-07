//the initialize methd which takes in pointers to all measruement variables and sets them
//to their initial values, and returns them to the MEGA
void initialize(unsigned short *batteryState, unsigned int *temperatureRaw, unsigned int *systolicPressRaw, unsigned int *diastolicPressRaw, unsigned int *pulseRateRaw,
    unsigned int *pressCalls, unsigned int *tempCalls, unsigned int *respirationRateRaw) { 
  *tempCalls = 0;
  *pressCalls = 0;
  *temperatureRaw = 75 * 10; 
  *systolicPressRaw = 80;
  *diastolicPressRaw = 80;
  *pulseRateRaw = 50;
  *respirationRateRaw = 0;
  *batteryState = 200;
  sender(0);
}
