#include <LiquidCrystal.h>

//////////////////////Function Prototypes///////////////////////////
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

//Relays 
const int D1 = 7; //10v Reverse or GND for 5V
const int D2 = 6; // 2nd Relay for 5V input
const int D3 = 5; // Forward Voltage Reading 

//Button Pins
const int measureButton = 0;
const int encoderButton = 1;

int measurementCounter = 0;   // Used to cycle through measurements
int ModePressCount = 0;       // Used to decide which encoder is being measured 

boolean buttonStateMeasurement = LOW;            
boolean lastButtonStateMeasurement = LOW;                
boolean currentButtonStateMeasurement = LOW;
boolean buttonStateEncoderMode = LOW;           
boolean lastButtonStateEncoderMode = LOW;                
boolean currentButtonStateEncoderMode = LOW;

// Debounce
unsigned long lastDebounceTime = 0;      
unsigned long debounceDelay = 50;

/////////////////////////LCD INIT FUNCTION//////////////////////
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
// Menu Array
String measurementType[] = {{"VOLTAGE:"}, {"R-CURRENT:"}, {"POWER:"}};  // Text on the bottom line

//////////////////////////////////////////////////////////////////WRITE FUNCTIONS HERE///////////////////////////////////////////////////////////////////////

float currentRead(){
// float i = analogRead(pin); //Will be 0 to 1023 ( 1-5)
// Input RCurrent_10k, RCurrent_1k, RCurrent_100
// Output reverseCurrent
  return .0001; //for testing purposes
}

float voltageRead(){
  return .0002; //for testing purposes
}

/*For powerRead, I took the current and power that Len gave us and found voltage in excel. I then used that to make an equal corresponding to power. 
 * 
 */
float powerRead(){
//  float output = 0; 
//  float input = analogRead(readPowerPin); 
//  
//  input = input*(5.0 / 1023.0); //converting to a legible value 
  //need to convert the voltage to power reading 
  //output = SOME EQUATION   
  
//  return output; 
  return .0003; //for testing purposes
}

/////////////////////////////////////////////////////////////////////////VOID SETUP PORTION////////////////////////////////////////////////////
void setup() {
  ///////////////////PIN INITIALIZATION/////////////////////////
  pinMode(readPowerPin, INPUT);
  pinMode(readCurrentPin, INPUT);
  pinMode(readVoltagePin, INPUT);
////relay for resistors
//  pinMode(RCurrent_10k, OUTPUT);
//  pinMode(RCurrent_1k, OUTPUT);
//  pinMode(RCurrent_100, OUTPUT);
////relay for parameter mode
//  pinMode(D1, OUTPUT);
//  pinMode(D2, OUTPUT);
//  pinMode(D3, OUTPUT);
//all buttons are pulled up 
  pinMode(measureButton, INPUT_PULLUP); 
  pinMode(encoderButton, INPUT_PULLUP);

  Serial.begin(19200);

  lcd.begin(16, 2);
  lcd.print("   US DIGITAL");
  delay(5000); 
}

////////////////////////////////////////////////////////////////////////////////////MAIN LOOP///////////////////////////////////////////////////////////////////////

void loop() {
  float reverseCurrent = 0; 
  float forwardVoltage = 0; 
  float powerUsage = 0; 
  
//  lcd.setCursor(0,1);                  

  currentButtonStateMeasurement = digitalRead(measureButton);          
  currentButtonStateEncoderMode = digitalRead(encoderButton); 

  //Debouncer line 
  if (currentButtonStateMeasurement != lastButtonStateMeasurement || currentButtonStateEncoderMode != lastButtonStateEncoderMode){
    lastDebounceTime = millis();      
  }  

  if ((millis() - lastDebounceTime) > debounceDelay){    
                                             
    // Measurement button press
    if (currentButtonStateMeasurement != buttonStateMeasurement){        
     
      buttonStateMeasurement = currentButtonStateMeasurement;  
      
      if (buttonStateMeasurement == LOW){                        
        measurementCounter++;
        lcd.setCursor(0,1);     
        lcd.print("                "); //Clearing first line of code 
      }
      
      lcd.setCursor(0,1);     
                   
      switch(measurementCounter){
        case 0: //case 0, Forward Voltage is read
          forwardVoltage = voltageRead(); 
          lcd.print(measurementType[measurementCounter]); 
          lcd.print(forwardVoltage,5); //have to do this to get floating point 5 digit percision
          break;
        case 1: //case 1, Reverse Current is read
          reverseCurrent = currentRead(); 
          lcd.print(measurementType[measurementCounter]);
          lcd.print(reverseCurrent,5);
          break;
        case 2: //case 2, Power is read 
          powerUsage = powerRead(); 
          lcd.print(measurementType[measurementCounter]);
          lcd.print(powerUsage,5);
          break; 
        case 3: 
          measurementCounter = 0;
          break;
        default:
          break;
      }
    }
    
    // Encoder type button press
    if (currentButtonStateEncoderMode != buttonStateEncoderMode){        
      
      buttonStateEncoderMode = currentButtonStateEncoderMode;  
                 
      if (buttonStateEncoderMode == LOW){                                                  
        ModePressCount = !ModePressCount;
      }
      
      switch(ModePressCount){
        case 0: 
          lcd.setCursor(0,0); 
          lcd.print("------EM1--------");
          delay(20);
          break;
        case 1: 
          lcd.setCursor(0,0); 
          lcd.print("------EM2--------");
          delay(20); 
          break;
      }
    }
  }   
  // states are reset back to low
  lastButtonStateMeasurement = currentButtonStateMeasurement;       // resets the left button state to LOW
  lastButtonStateEncoderMode = currentButtonStateEncoderMode;     // resets the right button state to LOW
}
