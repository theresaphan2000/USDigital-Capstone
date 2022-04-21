void setup() {
  // put your setup code here, to run once:

}

void loop() {

int sensorValue = analogRead(A0);

float voltage = sensorValue * (5.0 / 1023.0);

Serial.println(voltage);

Current = voltage / 10000; // I = V/R 

Power = 0.0184*(Current) + 0.061; // Table relationship - given

// Help - plz send value to LCD.
}
