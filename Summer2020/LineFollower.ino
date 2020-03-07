//lk
void lineFollower(void* dataPtr) {
  mySerial.println("in linefollwer method");
  while (1) {
    if (mySerial.available()) {//Software serial buffer
      input = mySerial.read();//read the next char
      Serial.println(input);
      if (input == '2') {
        insert(freeRoamTask);
        break;
      } else if (input == '1') {
        mySerial.println("already in Line Follower mode");
      } else if (input == 32) {//this isn't actually doing anything
        mySerial.println("stop");
      }
    } else {
      val1 = analogRead(analogInput1);
      if (val1 < 469) {
        val1 = 0;
      } else {
        val1 = 1;
      }
      val2 = analogRead(analogInput2);
      if (val2 < 424) {
        val2 = 0;
      } else {
        val2 = 1;
      }
      val3 = analogRead(analogInput3);
      if (val3 < 414) {
        val3 = 0;
      } else {
        val3 = 1;
      }
      if        (val1 == 0 && val2 == 0 && val3 == 0) {
        forward();
      } else if (val1 == 0 && val2 == 0 && val3 == 1) {
        left();
      } else if (val1 == 0 && val2 == 1 && val3 == 0) {
        forward();
      } else if (val1 == 0 && val2 == 1 && val3 == 1) {
        left();
      } else if (val1 == 1 && val2 == 0 && val3 == 0) {
        right();
      } else if (val1 == 1 && val2 == 0 && val3 == 1) {
        forward();
      } else if (val1 == 1 && val2 == 1 && val3 == 0) {
        right();
      } else if (val1 == 1 && val2 == 1 && val3 == 1) {
        forward();
      } else {
        forward();
      }
    }
  }
}
