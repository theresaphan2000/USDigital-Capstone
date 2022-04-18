void setup() {
  pinMode(D7, OUTPUT); // Digital pin D7 as output - RELAY D1 
  pinMode(D6, OUTPUT); // Digital pin D6 as output - RELAY D2
  pinMode(D5, OUTPUT); // Digital pin D5 as output - RELAY D3
}


void loop() {

  if (D1 == 1) {
    digitalWrite(D7, HIGH); // Digital pin D7 ON 
  }

  else if (D2 == 1) {
    digitalWrite(D6, HIGH); // Digital pin D6 ON 
  }

  else if (D3 == 1) {
    digitalWrite(D5, HIGH); // Digital pin D5 ON 
  }

} 
