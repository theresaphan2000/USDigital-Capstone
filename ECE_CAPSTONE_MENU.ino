

#include <LiquidCrystal.h>

// Menu Array
String measurementType[] = {{"[VOLTAGE]:"}, {"[REVERSE LEAKAGE CURRENT]:"}, {"[POWER]:"}};  // Text on the bottom line

// Pins being used
const int OnButtonPin = 5;       // Pin 5 for Power command
const int MeasurementButtonPin = 6;      // Pin 6 for measurement command
const int ModeButtonPin = 7;         // Pin 7 for encoder type command


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

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() {

  pinMode(OnButtonPin, INPUT); 
  pinMode(MeasurementButtonPin, INPUT);   
  pinMode(ModeButtonPin, INPUT);      
  delay(1000);

}


void loop() {

  lcd.setCursor(0,0);                  
  lcd.print(measurementType[measurementCounter]); 

  currentButtonStateMeasurement = digitalRead(MeasurementButtonPin);          
  currentButtonStateEncoderMode = digitalRead(ModeButtonPin); 
     
  
  if (currentButtonStateMeasurement != lastButtonStateMeasurement || currentButtonStateEncoderMode != lastButtonStateEncoderMode)        
  {
  lastDebounceTime = millis();      
  }  

  if ((millis() - lastDebounceTime) > debounceDelay)    
  {                                             
    
    // Measurement button press
    if (currentButtonStateMeasurement != buttonStateMeasurement)        
    { 
    buttonStateMeasurement = currentButtonStateMeasurement;  
                 
      if (buttonStateMeasurement == LOW)                        
      {                                                 
      measurementCounter++;
      }
          
        if (measurementCounter > 2)                           
        {                                                
        measurementCounter = 0;
        }
   
    }

    // Encoder type button press
    if (currentButtonStateEncoderMode != buttonStateEncoderMode)        
    { 
    buttonStateEncoderMode = currentButtonStateEncoderMode;  
                 
      if (buttonStateEncoderMode == LOW)                         
      {                                                 
        ModePressCount++;
      }
  
        if (ModePressCount > 1)                         
        {                                        
        ModePressCount = 0;
        }
        
        if (ModePressCount == 0)      // Enters the Mode and writes a brief message.                         
        {                                                      
        lcd.clear();
        lcd.setCursor(0,0); 
        lcd.print("EM1");
        delay(2000); 
        }

        if (ModePressCount == 1)      // Enters the Mode and writes a brief message.                         
        {                                                      
        lcd.clear();
        lcd.setCursor(0,0); 
        lcd.print("EM2");
        delay(2000); 
        }
    }

  }   
  // states are reset back to low
  lastButtonStateMeasurement = currentButtonStateMeasurement;       // resets the left button state to LOW
  lastButtonStateEncoderMode = currentButtonStateEncoderMode;     // resets the right button state to LOW
 
}
