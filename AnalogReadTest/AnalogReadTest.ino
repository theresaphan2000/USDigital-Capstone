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
// Begins assuming all 3 resistor relays are originally high...
  
  // Inputs: RCurrent_10k, RCurrent_1k, RCurrent_100, readCurrentPin
  // Output: reverseCurrent

  float i;
  i = analogRead(readCurrentPin); // Will be range 0 - 1023
  i = i*(5.0/1023.0);                 // Convert to the 0 - 5 range

  // Starts with checking the 100 Ohm resistor with a multiplication factor of 5,000
 //Converting i to actual value
  if(i >= 0.5){ 
    i = i/100.0; // Reversing the 100 Ohm multiplication
  }
  
  else if(i < 0.5){
    digitalWrite(RCurrent_100, LOW); // Turn off relay to 100, multiplication factor is 50,000
    i = analogRead(readCurrentPin);
    i = i*(5.0/1023.0);

    // Converting i to actual value
    if(i >= 0.5){
      i = i/1000.0;
    }
    
    else if(i < 0.5){
      digitalWrite(RCurrent_1k, LOW);  // Turn off relay to 1k, multiplication factor is 500,000
      i = analogRead(readCurrentPin); // Pulling value from the current A/D pin
      i = i*(5.0/1023.0);                 // Converting value to 0-5 range

      // converting i to actual value
      if( i >= 0.5){
        i = i/10000.0;
      }

      else if(i < 0.5){
        digitalWrite(RCurrent_10k, LOW); // Turn off relay to 10k, multiplication factor is 5,000,000
        i = analogRead(readCurrentPin); // Pulling value from the current A/D pin
        i = i*(5.0/1023.0);                 // Converting value to 0-5 range

        // Converting i to actual value
        i = i/100.0; // Split i/100,000 to avoid floating point issues
        i = i/1000.0; 
      }
    }
  }

  i = i/50.0;
  i = i*1000.0; // Convert to mA
  i = i*1000.0; // Convert to micro-amp
  return i;
  
}

float voltageRead(){
  return .0002; //for testing purposes
}

/*For powerRead, I took the current and power that Len gave us and found voltage in excel. I then used that to make an equal corresponding to power. 
 * 
 */
float powerRead(){
  int sensorValue = analogRead(readPowerPin);
  
  float voltage = (float)sensorValue * (5.0 / 1023.0);
  
  Serial.println(voltage);
  
  float Current = voltage / 10000.0; // I = V/R 
  
  float Power = 0.0184*(Current) + 0.061; // Table relationship - given
  return Power;   
}

/////////////////////////////////////////////////////////////////////////VOID SETUP PORTION////////////////////////////////////////////////////
void setup() {
  ///////////////////PIN INITIALIZATION/////////////////////////
  pinMode(readPowerPin, INPUT);
  pinMode(readCurrentPin, INPUT);
  pinMode(readVoltagePin, INPUT);
//relay for resistors
  pinMode(RCurrent_10k, OUTPUT);
  pinMode(RCurrent_1k, OUTPUT);
  pinMode(RCurrent_100, OUTPUT);
//relay for parameter mode
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
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
