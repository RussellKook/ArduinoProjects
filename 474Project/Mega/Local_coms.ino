unsigned int local_comms (char task, char id, short error) {
  sendTo(id, task);
  unsigned int result = recieve(id, task);
  if (result == 65535) {
    if (error < 10) {
      error += 1;
      return (local_comms(task, id, error));

    } else {
      return 0;
    }
  } else {
    return result;
  }
}

void sendTo(char id, char task) {
  Serial1.print('$');  // $ is the start of message character
  Serial1.print(task); // task is the id of the requesting task
  Serial1.print(id);   // id is the function being requested
  Serial1.println();    // new line character serves as the end of message symbol
}

unsigned int recieve(char id, char task) {
  char buffer[] = {' ',' ',' ',' ',' ',' ',' ',' '};
  while(Serial1.available() == 0) { //while there is nothing in the serial buffer get stuck in this while loop
  }  
  delay(50);
  while (Serial1.available() > 0) {
    char next = Serial1.read();
    if (next == '$') {
      delay(50);
      char section = Serial1.read();
      char function = Serial1.read();
      Serial1.readBytesUntil('\n', buffer, 8);
      unsigned int data = atoi(buffer);
      if ((section == task) && (function == id)) {
        return data; 
      } else {
        return 65535; // return max value an unsigned int can take
      }
      
    }
  }
}
