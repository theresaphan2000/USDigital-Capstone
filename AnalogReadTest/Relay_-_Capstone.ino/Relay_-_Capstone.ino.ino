void setup() {
  pinMode(D7, OUTPUT); // Digital pin D7 as output - RELAY D1 
  pinMode(D6, OUTPUT); // Digital pin D6 as output - RELAY D2
  pinMode(D5, OUTPUT); // Digital pin D5 as output - RELAY D3
  pinMode(D2, OUTPUT); // Digital pin D2 as output - RELAY D4 - R Current 100 
  pinMode(D3, OUTPUT); // Digital pin D3 as output - RELAY D5 - R Current 1K 
  pinMode(D4, OUTPUT); // Digital pin D4 as output - RELAY D6 - R Current 10K 
} 



void loop() {

       if (RelayD1 == 1) {
    digitalWrite(D7, HIGH); // Digital pin D7 ON 
  }

  else if (RelayD2 == 1) {
    digitalWrite(D6, HIGH); // Digital pin D6 ON 
  }

  else if (RelayD3 == 1) {
    digitalWrite(D5, HIGH); // Digital pin D5 ON 
  }

  else if (RelayD6 == 1) {
    digitalWrite(D4, HIGH); // Digital pin D4 ON 
  }

  else if (RelayD5 == 1) {
    digitalWrite(D3, HIGH); // Digital pin D3 ON 
  }

  else if (RelayD4 == 1) {
    digitalWrite(D2, HIGH); // Digital pin D2 ON 
  }

}
