void tempMeasure(unsigned int *temperatureRaw, unsigned int *tempCalls) {
  int temp = 0;
  temp = analogRead(potPin);
  temp = temp;
  *temperatureRaw = temp;
  sender(*temperatureRaw);
}
