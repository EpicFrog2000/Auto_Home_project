// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // print out the value you read:
  int mappedValue = map(sensorValue, 0, 1023, 0, 100);
  Serial.println(mappedValue);
  delay(50);  // delay in between reads for stability
}
