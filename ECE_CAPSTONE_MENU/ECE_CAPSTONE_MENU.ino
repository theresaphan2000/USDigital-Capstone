#include <LiquidCrystal.h>

// Menu Array
String measurementType[] = {{"VOLTAGE:"}, {"R-CURRENT:"}, {"POWER:"}};  // Text on the bottom line

// Pins being used
//const int OnButtonPin = 0;       // Pin 5 for Power command
const int MeasurementButtonPin = 1;      // Pin 6 for measurement command
const int ModeButtonPin = 0;         // Pin 7 for encoder type command


// Counters for menu and button presses
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

const int rs = 23, en = 22, d4 = 21, d5 = 20, d6 = 19, d7 = 18; //LCD PIN CONNECTIONS
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  lcd.begin(16, 2);
  pinMode(MeasurementButtonPin, INPUT_PULLUP);   
  pinMode(ModeButtonPin, INPUT_PULLUP);      
}


void loop() {

  lcd.setCursor(0,1);                  
  lcd.print(measurementType[measurementCounter]); 

  currentButtonStateMeasurement = digitalRead(MeasurementButtonPin);          
  currentButtonStateEncoderMode = digitalRead(ModeButtonPin); 
     
  
  if (currentButtonStateMeasurement != lastButtonStateMeasurement || currentButtonStateEncoderMode != lastButtonStateEncoderMode){
    lastDebounceTime = millis();      
  }  

  if ((millis() - lastDebounceTime) > debounceDelay){                                             
    // Measurement button press
    if (currentButtonStateMeasurement != buttonStateMeasurement){        
     
      buttonStateMeasurement = currentButtonStateMeasurement;  
      lcd.print("               "); //Clearing first line of code 
      if (buttonStateMeasurement == LOW){                        
                                                       
        measurementCounter++;
      }
          
      if (measurementCounter > 2){                           
                                                      
        measurementCounter = 0;
      }
   
    }
    
    // Encoder type button press
    if (currentButtonStateEncoderMode != buttonStateEncoderMode){        
      
      buttonStateEncoderMode = currentButtonStateEncoderMode;  
                 
      if (buttonStateEncoderMode == LOW){                         
                                                       
        ModePressCount++;
      }
  
        if (ModePressCount > 1){                         
                                                
          ModePressCount = 0;
        }
        
        if (ModePressCount == 0){      // Enters the Mode and writes a brief message.                         
                                                              
          lcd.setCursor(0,0); 
          lcd.print("------EM1--------");
          delay(20); 
        }

        else if (ModePressCount == 1){      // Enters the Mode and writes a brief message.                         
                                                              
         lcd.setCursor(0,0); 
         lcd.print("------EM2--------");
         delay(20); 
        }
    }

  }   
  // states are reset back to low
  lastButtonStateMeasurement = currentButtonStateMeasurement;       // resets the left button state to LOW
  lastButtonStateEncoderMode = currentButtonStateEncoderMode;     // resets the right button state to LOW
 
}
