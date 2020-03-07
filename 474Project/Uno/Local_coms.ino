char requestReader() {
  while (Serial.available() > 0) {
    char next = Serial.read();
    if (next == '$') { // start reading in the message
      context[0] = Serial.read();
      context[1] = Serial.read();
    } else if (next == 10) { // stop reading once the message is over
      return 10;
    }
  }
}

void sender(unsigned int data) {
  Serial.print('$');
  Serial.print(context[0]);
  Serial.print(context[1]);
  Serial.println(data);
}
