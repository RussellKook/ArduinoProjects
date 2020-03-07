/*
  Software serial multple serial test

 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.

 The circuit:
 * RX is digital pin 10 (connect to TX of other device)
 * TX is digital pin 11 (connect to RX of other device)

 Note:
 Not all pins on the Mega and Mega 2560 support change interrupts,
 so only the following can be used for RX:
 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69

 Not all pins on the Leonardo and Micro support change interrupts,
 so only the following can be used for RX:
 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).

 created back in the mists of time
 modified 25 May 2012
 by Tom Igoe
 based on Mikal Hart's example

 This example code is in the public domain.

 */
#include <SoftwareSerial.h>
#include <math.h>
char input;
SoftwareSerial mySerial(2, 3); // RX, TX

struct myTCB {
  void (*task)(void*);
  void* dataPtr;
  struct myTCB* next;
  struct myTCB* prev;
};
typedef struct myTCB TCB;

typedef struct {
  
} lineFollowerDataStruct;

typedef struct {
  
} freeRoamDataStruct;

TCB* head;
TCB* tail;
TCB* freeRoamTask;
TCB* lineFollowerTask;

void lineFollower(void* dataPtr);
void freeRoam(void* dataPtr);
void insert(TCB* node);
void removeHead(TCB* node);
void schedule();
void startUp();

int dc1b = 11; //dc1 backwards
int dc1f = 10; //dc1 forward
int dc2f = 9; //dc2 forward
int dc2b = 6; //dc2 backwards
int overallSpeed = 0;
int analogInput1 = A1;
int analogInput2 = A2;
int analogInput3 = A3;
int val1 = 0;
int val2 = 0;
int val3 = 0;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Arduino to computer test");
  // set the data rate for the SoftwareSerial port
  mySerial.begin(115200);
  mySerial.println("Bluetooth to computer test");
  pinMode(dc1b, OUTPUT);
  pinMode(dc1f, OUTPUT);
  pinMode(dc2f, OUTPUT);
  pinMode(dc2b, OUTPUT);
  startUp();
  mySerial.println("Welcome commands are as follows");
  mySerial.println("MODE: '1' = Linefollower... '2' = Free Roam");
  mySerial.println("SPEED: 'f' = fast... 's' = slow... anything else is default speed");
  mySerial.println("COMMANDS: 'a' = left... 'w' = forward... 'd' = right... 's' = backwards... spacebar = stop");
}

void loop() { // run over and over
  delay(100);
  schedule();
}

void schedule() {
  mySerial.println("Welcome commands are as follows");
  mySerial.println("MODE: '1' = Linefollower... '2' = Free Roam");
  if (mySerial.available()) {//Software serial buffer
    input = mySerial.read();//read the next char
    Serial.write(input);//write to serial monitor the char recieved
    if (input == '1') {
      mySerial.println("line Follower Mode");
      mySerial.println("Select Speed.... 'f' = fast ... 's' = slow");
      while (!mySerial.available()) {
      }
      input = mySerial.read();
      if (input == 'f') {
        overallSpeed = 255;
        mySerial.println("fast speed selected");
      } else if (input == 's') {
        overallSpeed = 100;
        mySerial.println("slow speed selected");
      } else {
        overallSpeed = 128;
        mySerial.println("default speed selected");
      }
      insert(lineFollowerTask);
    } else if (input == '2') {
      mySerial.println("free Roam Mode");
      mySerial.println("Select Speed.... 'f' = fast ... 's' = slow");
      while (!mySerial.available()) {
      }
      input = mySerial.read();
      if (input == 'f') {
        overallSpeed = 255;
        mySerial.println("fast speed selected");
      } else if (input == 's') {
        overallSpeed = 64;
        mySerial.println("slow speed selected");
      } else {
        overallSpeed = 128;
        mySerial.println("default speed selected");
      }
      insert(freeRoamTask);
    } else {
      mySerial.println("command not recognized");
    }
  }
  while(head != NULL) {//look at signal0 file
    head->task( (head->dataPtr) );
    removeHead(head);
  }
}
