//lk
void freeRoam(void* dataPtr) {
  mySerial.println("in freeRoam method");
  while(1) {
    if (mySerial.available()) {//Software serial buffer
      input = mySerial.read();//read the next char
      Serial.println(input);
      if (input == '1') {
        insert(lineFollowerTask);
        break;
      } else if (input == '2') {
        mySerial.println("already in Free Roam mode");
      } else if (input == 'a') {
        mySerial.println("left");
        left();
      } else if (input == 'w') {
        mySerial.println("forward");
        forward();
      } else if (input == 'd') {
        mySerial.println("right");
        right();
      } else if (input == 's') {
        mySerial.println("backwards");
        backwards();
      } else if (input == 32) {
        mySerial.println("stop");
        Stop();
      } else {
        mySerial.println("command not recognized");
      }
    }
  }
}
