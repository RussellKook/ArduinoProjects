//remote comms
//not a task, but a function that checks for remote input, if it is detected, reports to keypad
char remoteListen() {
  if(Serial.available() > 0) { 
    delay(50);
    char data[2];
    Bool done = FALSE;
    while(Serial.available() > 0) {
      char next = Serial.read();
      if (next == '$') {
        data[0] = Serial.read();
        data[1] = Serial.read();
        done = TRUE;
      } else if ((next == 10) && done) {
        return parseIn(data[0],data[1]);
      }
    }
  }
  return 'E';
}

void measureAck(char id) {
  if(enableRemote) {
    Serial.println("$"); // start of message
    Serial.println("M"); // Keypad for option
    Serial.println(id); // o for options
    Serial.println("==========================================");
    Serial.println("Measurement Successful");
    Serial.println("==========================================");
  Serial.println("&");
  }
}


void remoteMenu(int menu) {
  Serial.println("$"); // start of message
  Serial.println("K"); // Keypad for option
  Serial.println("O"); // o for options
  Serial.println("==========================================");
  Serial.println("Available commands");
  if( menu == 0) {
     Serial.println("KM - Select Measure menu");
     Serial.println("KA - View Measurement Results");
  } else if (menu == 10) {
     Serial.println("MT - Measure Temperature");
     Serial.println("MP - Measure Pulse");
     Serial.println("MS - Measure Pressure");
     Serial.println("MR - Measure Respiration");
     Serial.println("KB - Go Back To Menu");
  } else if (menu == 21) {
     Serial.println("KB - Go Back To Menu");
  } else if (menu == -1) {
    Serial.println("Remote Access Is Disabled");
  } else if (menu == 1) {
    Serial.println("Remote Acceess Reenabled");
  }
  Serial.println("==========================================");
  Serial.println("&");
}


// T == measure temp
// P == measure Pressure
// B == Back button
// E == error
// U == Pulse rate
// R == respiration
// M == menu of measures
// A == Annunsiation
char parseIn(char task, char function) {
  if(task == 'K') {
    if(function == 'M') {
      return 'M';
    } else if (function == 'A') {
      return 'A';
    } else if (function == 'B') {
      return 'B';
    }
  } else if (task == 'M') {
    if (function == 'T') {
      return 'T';
    } else if (function == 'P') {
      return 'U';
    } else if (function == 'S') {
      return 'P';
    } else if (function == 'R') {
      return 'R';
    } 
  }
}
