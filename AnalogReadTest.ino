#include <LiquidCrystal.h> 

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int sensorVal;   
int resis1 = A7; //reading analog pin 

void setup() {
  // put your setup code here, to run once:
  
  pinMode(resis1, INPUT); 
  Serial.begin(19200); 
 
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.

}

void loop() {
  
   sensorVal = analogRead(resis1); //read resistor value two
   float voltage = sensorVal * (5.0/1023.0); 
   float current = voltage/sensorVal; 
 
  Serial.print("Voltage: "); 
  Serial.println(voltage); 

  lcd.setCursor(0,0); w
  lcd.print("Voltage: " + String(voltage)); 

  lcd.setCursor(1,0); 
  lcd.print("Current: " + String(current)); 
  delay(1000); 
  
  lcd.clear(); 
}
