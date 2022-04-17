#include <LiquidCrystal.h>

//////////////////////Function Prototypes///////////////////////////
void lcdControl(float reverseCurrent, float forwardVoltage, float powerUsage, const int buttonPressed); //controls LCD and what it prints 

/*For Danielle: controls relays. Use the buttonPressed variable to figure out what relay to open or close.You can use switch or if else. 
 * currentButton = 1, voltage and power reading = 17, and power button = 0.
 */
void relayControl(int buttonPressed);  

float currentRead(); //reads current and will control the relay to the resistors. Will return reverse current reading

float powerRead(); //reads power readings. Will return power readings. 

float voltageRead(); //reads voltage reading. 

//////////////////////Pin Variables////////////////////////////////
const int rs = 23, en = 22, d4 = 21, d5 = 20, d6 = 19, d7 = 18; //LCD PIN CONNECTIONS
const int readPowerPin = A10; // pin where power readings are fed into
const int readCurrentPin = A9; // pin where current readings are fed into
const int readVoltagePin = A8; // pin where voltage readings are fed into

//Reverse Current Reading relay resistor control
const int RCurrent_10k = 4;
const int RCurrent_1k = 3;
const int RCurrent_100 = 2;

//Button Pins
const int powerButton = 0;
const int currentButton = 1;
const int voltageButton = 17;
int buttonState; //check button state 

/////////////////////////LCD INIT FUNCTION//////////////////////
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//////////////////////////////////////////////////////////////////Functions///////////////////////////////////////////////////////////////////////
/* How the LCD function works is it takes in 4 arguments, the readings and the pin number of which button is pressed. It uses a switch case to see 
 *  which button value was passed through and proceeds to print the value corresponding to what the button is supposed to do 
 */
void lcdControl(float reverseCurrent, float forwardVoltage, float powerUsage, const int buttonPressed){
  //case 0 is turn off or on LCD 
  //case 1 is display reverse current 
  //case 17 is display forward voltage 
  
  switch(buttonPressed){
    case 0:
      //idk yet
      break;
      
    case 1: 
      reverseCurrent = reverseCurrent*(5.0 / 1023.0); //converting to a legible value 
      lcd.setCursor(0,0); 
      lcd.print("R-Current: " + String(reverseCurrent));
      //  delay(1000);

      break;
    case 17:
      forwardVoltage = forwardVoltage*(5.0 / 1023.0); //converting to a legible value 
      lcd.setCursor(0,0); 
      lcd.print("F-Voltage: " + String(forwardVoltage)); 

      powerUsage = powerUsage*(5.0 / 1023.0); //converting to a legible value 
      lcd.setCursor(1,0); 
      lcd.print("Power: " + String(powerUsage)); 
      //  delay(1000);

      break;
      
    default: 
      break; 
  }
}

/////////////////////////////////////////////////////////////////////////VOID SETUP PORTION////////////////////////////////////////////////////
void setup() {
  ///////////////////PIN INITIALIZATION/////////////////////////
  pinMode(readPowerPin, INPUT);
  pinMode(readCurrentPin, INPUT);
  pinMode(readVoltagePin, INPUT);

  pinMode(RCurrent_10k, OUTPUT);
  pinMode(RCurrent_1k, OUTPUT);
  pinMode(RCurrent_100, OUTPUT);

  //all buttons are pulled up 
  pinMode(powerButton, INPUT_PULLUP); //to turn LCD screen on or off 
  pinMode(currentButton, INPUT_PULLUP);
  pinMode(voltageButton, INPUT_PULLUP);

  Serial.begin(19200);

  lcd.begin(16, 2);
  lcd.print("EM1 ENCODER READER");

}

////////////////////////////////////////////////////////////////////////////////////MAIN LOOP///////////////////////////////////////////////////////////////////////
void loop() {
  float reverseCurrent = 0; 
  float forwardVoltage = 0; 
  float powerUsage = 0; 
  
  //in main, the loop will continuously check which button is pressed. Depending on which button is pressed, different functions will be used. If voltageButton is pressed,
  //then power and voltage readings will be displayed. else if currentButton is pressed, only current is displayed. 
  //button is checked to see if zero because it is active low, which is why it is pulled high in setup

  //the reason I have seperate if and switch is because the buttons are momentary. if it detects a change, then it'll change the current state button, otherwise itll keep the same functions as before
  if(digitalRead(currentButton) == 0){ 
    buttonState = currentButton; 
  }
  else if(digitalRead(voltageButton) == 0){
     buttonState = voltageButton; 

  }
  else if(digitalRead(powerButton) == 0){
    buttonState = powerButton; 
  }


  switch(buttonState){
    case 0: 
      //dont know what to do yet...
      relayControl(powerButton); 
      lcdControl(0, 0, 0, powerButton); 
      break;
       
    case 1: 
      //calls relay control to switch over the relay
      relayControl(currentButton); 
      //
      reverseCurrent = currentRead(); //call current read function 
      lcdControl(reverseCurrent, 0, 0, currentButton); 
      break;
      
    case 17: 
      //calls relay control to switch over the relay
      relayControl(voltageButton); 
      //
      forwardVoltage = voltageRead(); 
      powerUsage = powerRead(); 
      lcdControl(0, forwardVoltage, powerUsage, voltageButton);
      break; 
  }
  
  lcd.clear();
}