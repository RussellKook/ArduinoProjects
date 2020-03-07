//UNO PORJECT 2 FOR EE 474
//This code is meant to have the UNO communicate with the MEGA board, pretending the UNO
//is a medical measureing device, simulating all such functionality.

//note temperatureRaw is *10 time normal amount

int incomingByte;
int pulseInterruptPin = 2;
int pressureInterruptPin = 3;
int switchPin = 4;
int potPin = 14;
int incrementAmount = 10; // change this to represent a change for the "person"

unsigned int temperatureRaw; // 4 bytes 0 - huge
unsigned int systolicPressRaw;
unsigned int diastolicPressRaw;
unsigned int pulseRateRaw;
unsigned int respirationRateRaw;
unsigned int pressCalls;
unsigned int tempCalls;
volatile int pulseCounter = 0;
volatile int currentPressure = 0;
unsigned short batteryState; //2 bytes 0-65535



void initialize(unsigned short *batteryState, unsigned int *temperatureRaw, unsigned int *systolicPressRaw, unsigned int *diastolicPressRaw, 
   unsigned int *pulseRateRaw, unsigned int *pressCalls, unsigned int *tempCalls, unsigned int *respirationRateRaw);
void readAnalogWave(unsigned int *pulseRateRaw, const byte pulseInterruptPin); 
void tempMeasure(unsigned int *temperatureRaw, unsigned int *tempCalls); 
void pressMeasure(unsigned int *systolicPressRaw, unsigned int *diastolicPressRaw, unsigned int *pressCalls);

char context[2];

void setup() {
  Serial.begin(9600);
  pinMode(pulseInterruptPin, INPUT_PULLUP); //for pulse
  pinMode(pressureInterruptPin, INPUT_PULLUP); //for pressure
  pinMode(switchPin, INPUT); //for switch for pressure
  pinMode(potPin, INPUT); //for temp

}

void loop() {
  // reads in information if available
  if(Serial.available() > 0) { 
    delay(50);

     requestReader();

     if (context[0] == 'I') {

      initialize(&batteryState, &temperatureRaw, &systolicPressRaw, &diastolicPressRaw, &pulseRateRaw, &pressCalls, &tempCalls, &respirationRateRaw);
     } else if (context[0] == 'M') {
        if (context[1] == 'P' || context[1] == 'R') {
          readAnalogWave(&pulseRateRaw, pulseInterruptPin);
        } else if (context[1] == 'B') {
          tempMeasure(&temperatureRaw, &tempCalls);
        } else if (context[1] == 'S') {
          pressMeasure(&systolicPressRaw, &diastolicPressRaw, &pressCalls);
        } else if (context[1] == 'D') {
          sender(diastolicPressRaw);
        }
        
     } else {
      context[0] = 'E';
      context[1] = 'E';
     }
     
  }
}
