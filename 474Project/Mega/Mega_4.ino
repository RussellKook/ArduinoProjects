//MEGA PORJECT 2
// IMPORTANT: ELEGOO_TFTLCD LIBRARY MUST BE SPECIFICALLY
// CONFIGURED FOR EITHER THE TFT SHIELD OR THE BREAKOUT BOARD.
// SEE RELEVANT COMMENTS IN Elegoo_TFTLCD.h FOR SETUP.
//Technical support:goodtft@163.com

#include <Elegoo_GFX.h>    // Core graphics library
#include <Elegoo_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>

#if defined(__SAM3X8E__)
    #undef __FlashStringHelper::F(string_literal)
    #define F(string_literal) string_literal
#endif

// The control pins for the LCD can be assigned to any digital or
// analog pins...but we'll use the analog pins as this allows us to
// double up the pins with the touch screen (see the TFT paint example).
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

// When using the BREAKOUT BOARD only, use these 8 data lines to the LCD:
// For the Arduino Uno, Duemilanove, Diecimila, etc.:
//   D0 connects to digital pin 8  (Notice these are
//   D1 connects to digital pin 9   NOT in order!)
//   D2 connects to digital pin 2
//   D3 connects to digital pin 3
//   D4 connects to digital pin 4
//   D5 connects to digital pin 5
//   D6 connects to digital pin 6
//   D7 connects to digital pin 7
// For the Arduino Mega, use digital pins 22 through 29
// (on the 2-row header at the end of the board).

// Assign human-readable names to some common 16-bit color values:
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define ORANGE  0xFD20

#define YP A3  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin

#define TS_MINX 120
#define TS_MAXX 900

#define TS_MINY 70
#define TS_MAXY 920

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
// optional
#define LCD_RESET A4
Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);


#define BOXSIZE 120
#define PENRADIUS 3


enum _myBool { FALSE = 0, TRUE = 1 };

typedef enum _myBool Bool;


struct myTCB {
    void (*task)(void*);
    void* dataPtr;
    struct myTCB* next;
    struct myTCB* prev;
};

typedef struct myTCB TCB; // new statement to support a propper pointer


typedef struct {
    unsigned int *temperatureRaw, *pressRaw, *pulseRateRaw, *respirationRaw, *measureSystolic,
        *measureTemp, *measurePulse, *measureRes;
    unsigned short *tempIndex, *pressIndex, *rateIndex, *respirationIndex;
    char *whichData; 
} measureDataStruct;

typedef struct {
    unsigned int *temperatureRaw, *pressRaw, *pulseRateRaw, *respirationRaw;
    double *temperatureCorrected, *pressCorrected, *pulseRateCorrected, *respirationCorrected;
    unsigned short *tempIndex, *pressIndex, *rateIndex, *respirationIndex;
} computeDataStruct;

typedef struct {
    double *temperatureCorrected, *pressCorrected, *pulseRateCorrected, *respirationCorrected;
    unsigned short *tempIndex, *pressIndex, *rateIndex, *respirationIndex;
    unsigned short *batteryState;
    unsigned int *depressedSystolic, *depressedTemp, *depressedPulse, *depressedRespiration, *mode, *alarmAckS, *alarmAckT, *alarmAckP, *alarmAckR;
} displayDataStruct;

typedef struct {
    unsigned short *batteryState;
} statusDataStruct;

typedef struct {
    unsigned int *temperatureRaw, *pressRaw, *pulseRateRaw, *respirationRaw, *depressedSystolic, *depressedTemp, *depressedPulse, 
        *depressedRespiration, *measureSystolic, *measureTemp, *measurePulse, *measureRes;;
    unsigned short *tempIndex, *pressIndex, *rateIndex, *respirationIndex, *batteryState;
    int *displaySerial;
} warningDataStruct;

typedef struct {
    unsigned int *depressedSystolic, *depressedTemp, *depressedPulse, *depressedRespiration, *mode, *alarmAckS, *alarmAckT, *alarmAckP, *alarmAckR;
    char *whichData, *remoteInput;
    Bool *enableRemote;
} keypadDataStruct;

typedef struct {
    double *temperatureCorrected, *pressCorrected, *pulseRateCorrected, *respirationCorrected;
    unsigned short *tempIndex, *pressIndex, *rateIndex, *respirationIndex, *batteryState;
    int *displaySerial;
} serialDataStruct;


//systolic is first
unsigned int temperatureRaw[8], pressRaw[16], pulseRateRaw[8], respirationRaw[8], depressedSystolic, mode, alarmAckS, alarmAckT, alarmAckP, alarmAckR, measureSystolic;
unsigned int depressedTemp, depressedPulse, depressedRespiration, measureTemp, measurePulse, measureRes;
double temperatureCorrected[8], pressCorrected[16], pulseRateCorrected[8], respirationCorrected[8];

int displaySerial;
unsigned short batteryState, tempIndex, pressIndex, rateIndex, respirationIndex;
char whichData, remoteInput;

Bool sBpHigh, dBpHigh, tempHigh, pulseLow, respirationLow, enableRemote;


TCB* head;
TCB* tail;

TCB* measureTask;
TCB* displayTask;
TCB* warningTask;
TCB* computeTask;
TCB* statusTask;
TCB* keypadTask;
TCB* serialTask;

//insert
//remove
int initialize();
int startTimeStatus; // may need to delay the mega by 5 seconds or this wont execute on first call
int startTimeMeasure;
int startTimeCompute;
void setupTftDisplay();
void schedule();
void measureMethod(void* dataPtr);
void computeMethod(void* dataPtr);
void displayMethod(void* dataPtr);
void statusMethod(void* dataPtr);
void warningMethod (void* tcbPtr);
void keypadMethod(void* dataPtr);
void serialMethod(void* dataPtr);
void insert(TCB* node);
void removeHead(TCB* node);
void startUp();


void setup() {
  startUp();
  delay(5000);  //a delay is added here to allow the system to settle before beginning the loop
}

void loop() {//while(1)
    schedule();
}

//Schedule determines the order in which the task queue gets executed
void schedule(){
  remoteInput = remoteListen();
  insert(statusTask);
  insert(keypadTask);
   int i = 0;
  while(head != NULL) {//look at signal0 file
    head->task( (head->dataPtr) );
    removeHead(head);
  }
}
