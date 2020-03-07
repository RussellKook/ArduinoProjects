#define MINPRESSURE 10
#define MAXPRESSURE 1000

void keypadMethod(void* dataPtr)
{
  keypadDataStruct *keypadDataPtr = (keypadDataStruct*)dataPtr;
  //Serial.println("kepyad");
  //states
  int s0 = 0;

  int menu = 10;
  int calc = 100;

  int stats = 21;

  int displayTime;

  static int last = 50; // just needs to not be equal to s0
  static int current = s0;
  static int cycle = 1;
  static int cycleM = 1;
  static int cycleS = 1;
  static int toggle = 0;

  char choice = 'E';

  if (*(keypadDataPtr->enableRemote) && (*(keypadDataPtr->remoteInput) != 'E')) {
    choice = *(keypadDataPtr->remoteInput);
    *(keypadDataPtr->remoteInput) = 'E' ;
  }
  
  if ((last != current) && *(keypadDataPtr->enableRemote) && (current != calc)) {
    last = current;
    remoteMenu(last);
    if (last == stats) {
      insert(serialTask);
    }
  } 
  
  if(current == calc)
  {
      current = s0;
      tft.fillScreen(BLACK);
      cycle = 1;
  }
  
  if (current == s0)
  {
    //Serial.println("how");
     if(cycle)
     {
         tft.fillRect(0, 0, BOXSIZE, BOXSIZE, MAGENTA);
         tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, WHITE);
         tft.fillRect(0, BOXSIZE, BOXSIZE, BOXSIZE, WHITE);
         tft.fillRect(BOXSIZE, BOXSIZE, BOXSIZE, BOXSIZE, MAGENTA);
    
         tft.setTextSize(2);
         tft.setTextColor(BLACK);
         
         tft.setCursor(12, 45);
         tft.print("Menu");
    
         tft.setCursor(BOXSIZE + 12, 45);
         tft.print("Stats");
    
         tft.setCursor(12, BOXSIZE + 45);
         tft.print("Other...");
    
         tft.setCursor(BOXSIZE + 12, BOXSIZE + 45);
         tft.print("Other...");
  
         tft.drawRect(0, 2*BOXSIZE, 2*BOXSIZE, 80, WHITE);

         cycle = 0;
         cycleM = 1;
         cycleS = 1;
     }
      tft.setTextColor(WHITE);
      if (*(keypadDataPtr->enableRemote) != toggle) {
        if(*(keypadDataPtr->enableRemote))
        {
          tft.setCursor(12, 2*BOXSIZE + 45);
          tft.setTextColor(BLACK);
          tft.print("Enable Remote Comm");
          tft.setCursor(12, 2*BOXSIZE + 45);
          tft.setTextColor(WHITE);
          tft.print("Disable Remote Comm");
        }
        else
        {
          tft.setCursor(12, 2*BOXSIZE + 45);
          tft.setTextColor(BLACK);
          tft.print("Disable Remote Comm");
          tft.setTextColor(WHITE);
          tft.setCursor(12, 2*BOXSIZE + 45);
          tft.print("Enable Remote Comm");
        }
        toggle = *(keypadDataPtr->enableRemote);
      }
      tft.setTextColor(BLACK);

    digitalWrite(13, HIGH);
    TSPoint p = ts.getPoint();
    digitalWrite(13, LOW);
  
    // if sharing pins, you'll need to fix the directions of the touchscreen pins
    //pinMode(XP, OUTPUT);
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    //pinMode(YM, OUTPUT);
  
     if ((p.z > MINPRESSURE && p.z < MAXPRESSURE) || (choice != 'E'))
     {
       
        // scale from 0->1023 to tft.width
        p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
        //p.x = tft.width()-map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
        p.y = (tft.height()-map(p.y, TS_MINY, TS_MAXY, tft.height(), 0));
        //p.y = map(p.y, TS_MINY, TS_MAXY, tft.height(), 0);

        if((p.y < BOXSIZE) || (choice == 'M') || (choice == 'A'))
        {
            if((p.x < BOXSIZE) || (choice == 'M'))
            {
                current = menu;
                choice = 'E';
                tft.fillScreen(BLACK);
                toggle = 2;
            }
            else
            {
                current = stats;
                tft.fillScreen(BLACK);
                toggle = 2;
            }
        }
        else if(p.y < (BOXSIZE * 2) /*specific 12*/)
        {
            if(p.x < BOXSIZE /*specific*/)
            {
                //placeholder
            }
            else
            {
                //placeholder
            }
        }
        else /*if(specific)*/
        {
          if(*(keypadDataPtr->enableRemote)) {
              *(keypadDataPtr->enableRemote) = 0;
              remoteMenu(-1);
          } else {
             *(keypadDataPtr->enableRemote) = 1;
             remoteMenu(1);
             remoteMenu(0);
          }
        }
     } 
  }

  if(current == menu)
  {
     if(cycleM)
     {
         *(keypadDataPtr->mode) = 0;
         insert(displayTask);
         cycleM = 0;

     }

    digitalWrite(13, HIGH);
    TSPoint p = ts.getPoint();
    digitalWrite(13, LOW);
  
    // if sharing pins, you'll need to fix the directions of the touchscreen pins
    //pinMode(XP, OUTPUT);
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    //pinMode(YM, OUTPUT);

     if ((p.z > MINPRESSURE && p.z < MAXPRESSURE) || (choice != 'E'))
     {
        // scale from 0->1023 to tft.width
        p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
        //p.x = tft.width()-map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
        p.y = (tft.height()-map(p.y, TS_MINY, TS_MAXY, tft.height(), 0));
        //p.y = map(p.y, TS_MINY, TS_MAXY, tft.height(), 0);
        if (choice != 'E') {
          p.y = 3*BOXSIZE; // if there is a remote input, the tft may read noise, this line clears it
        }
        if((p.y < (BOXSIZE/2)) || (choice == 'T'))
        {
            current = calc;
            tft.fillScreen(BLACK);
            tft.setTextColor(WHITE);
            tft.setCursor(0,0);
            tft.print("Calculating Temperature...");
            *(keypadDataPtr->whichData) = 66;
            insert(measureTask);
        }
        else if((p.y < BOXSIZE)|| (choice == 'P')) 
        {
            current = calc;
            tft.fillScreen(BLACK);
            tft.setTextColor(WHITE);
            tft.setCursor(0,0);
            tft.print("Calculating Blood Pressure...");
            *(keypadDataPtr->whichData) = 83;
            insert(measureTask);
        }
        else if((p.y < (3* BOXSIZE/2))|| (choice == 'U'))
        {
            current = calc;
            tft.fillScreen(BLACK);
            tft.setTextColor(WHITE);
            tft.setCursor(0,0);
            tft.print("Calculating Pulse Rate...");
            *(keypadDataPtr->whichData) = 80;
            insert(measureTask);
        }
        else if((p.y < (2* BOXSIZE)) || (choice == 'R'))
        {
            current = calc;
            tft.fillScreen(BLACK);
            tft.setTextColor(WHITE);
            tft.setCursor(0,0);
            tft.print("Calculating Respiration Rate...");
            *(keypadDataPtr->whichData) = 82;
            insert(measureTask);
        }
        else if((p.x < BOXSIZE && p.y < 5*BOXSIZE/2) || (choice == 'B'))
        {
            current = s0;
            tft.fillScreen(BLACK);
            cycle = 1;
        }
     }  
  }

  if(current == stats)
  {
     if(cycleS)
     {
         *(keypadDataPtr->mode) = 1;
         tft.fillScreen(BLACK);
         insert(displayTask);

         cycleS = 0;

     }

    digitalWrite(13, HIGH);
    TSPoint p = ts.getPoint();
    digitalWrite(13, LOW);
  
    // if sharing pins, you'll need to fix the directions of the touchscreen pins
    //pinMode(XP, OUTPUT);
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    //pinMode(YM, OUTPUT);

     if ((p.z > MINPRESSURE && p.z < MAXPRESSURE) || (choice != 'E'))
     {
        // scale from 0->1023 to tft.width
        p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
        //p.x = tft.width()-map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
        p.y = (tft.height()-map(p.y, TS_MINY, TS_MAXY, tft.height(), 0));
        //p.y = map(p.y, TS_MINY, TS_MAXY, tft.height(), 0);



        if((p.x < BOXSIZE && p.y > (3*BOXSIZE/2) && p.y < (5*BOXSIZE/2)) || (choice == 'B'))
        {
            current = s0;
            tft.fillScreen(BLACK);
            displayTime = millis()/100;
            cycle = 1;
        }
        else if(p.x > BOXSIZE && p.y > BOXSIZE && p.y < (4*BOXSIZE/3) && *(keypadDataPtr->alarmAckS))
        {
            *(keypadDataPtr->depressedSystolic) = 1;
            *(keypadDataPtr->mode) = 1;
            tft.fillScreen(BLACK);
            insert(displayTask);

        }
        else if(p.x > BOXSIZE && p.y > (4*BOXSIZE/3) && p.y < (5*BOXSIZE/3) && *(keypadDataPtr->alarmAckT))
        {
            *(keypadDataPtr->depressedTemp) = 1;
            *(keypadDataPtr->mode) = 1;
            tft.fillScreen(BLACK);
            insert(displayTask);


        }
        else if(p.x > BOXSIZE && p.y > (5*BOXSIZE/3) && p.y < (2*BOXSIZE) && *(keypadDataPtr->alarmAckP))
        {
            *(keypadDataPtr->depressedPulse) = 1;
            *(keypadDataPtr->mode) = 1;
            tft.fillScreen(BLACK);
            insert(displayTask);


        }
        else if(p.x > BOXSIZE && p.y > (2*BOXSIZE) && p.y < (7*BOXSIZE/3) && *(keypadDataPtr->alarmAckR))
        {
            *(keypadDataPtr->depressedRespiration) = 1;
            *(keypadDataPtr->mode) = 1;
            tft.fillScreen(BLACK);
            insert(displayTask);


        }
     }
     else if((millis()/100 - displayTime) >= 5)
        {
            displayTime = millis()/100;
            insert(displayTask);
        }
  }
  choice = 'E';
}
