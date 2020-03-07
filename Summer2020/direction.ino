void forward() {
  delay(20);
  analogWrite(dc1b, 0);
  analogWrite(dc2b, 0);
  analogWrite(dc2f, 0);
  analogWrite(dc1f, 0);
  delay(20);
  analogWrite(dc1f, overallSpeed);
  analogWrite(dc2f, overallSpeed);
}

void left() {
  delay(20);
  analogWrite(dc1b, 0);
  analogWrite(dc2b, 0);
  analogWrite(dc2f, 0);
  analogWrite(dc1f, 0);
  delay(20);
  analogWrite(dc1f, overallSpeed);
}

void right() {
  delay(20);
  analogWrite(dc1b, 0);
  analogWrite(dc2b, 0);
  analogWrite(dc1f, 0);
  analogWrite(dc2f, 0);
  delay(20);
  analogWrite(dc2f, overallSpeed);
}

void backwards() {
  delay(20);
  analogWrite(dc1b, 0);
  analogWrite(dc2b, 0);
  analogWrite(dc2f, 0);
  analogWrite(dc1f, 0);
  delay(20);
  analogWrite(dc1b, overallSpeed);
  analogWrite(dc2b, overallSpeed);
}

void Stop() {
  analogWrite(dc1b, 0);
  analogWrite(dc1f, 0);
  analogWrite(dc2f, 0);
  analogWrite(dc2b, 0);
}
