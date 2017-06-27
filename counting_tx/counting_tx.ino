#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 6, 5, 4, 3); 

const int buttonPin = 2; //input from meter through octocoupler to pin 2 "Counts Pulses"
const int ledPin = 13;

int buttonPushCounter = 0;
int buttonState = 0;
int lastButtonState = 0;

unsigned long previousMillis = 0;

float watts_used = 0;

const long interval = 5000; 

void setup()

{
 lcd.begin(16, 2);
 Serial.begin(9600);
 
 pinMode(buttonPin, INPUT);
 
 pinMode(ledPin, OUTPUT);
 
 lcd.display();
 lcd.setCursor(5,0);
 lcd.print("Welcome");
 lcd.setCursor(0,1);
 lcd.print(" Power Line Comm. ");

 delay(1500);
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print(" pulses: ");
 lcd.setCursor(0,1);
 lcd.print(" watts used ");



}

void loop()

{
  if(Serial.available() >0)
  {
   char inchar=Serial.read(); 
    if (inchar=='d')
      {   
          lcd.clear();
          lcd.print("3 warning messages rec.");
          lcd.print("cutting power");
          digitalWrite(9,LOW);//input to relay to turn off supply
          //digitalWrite(13, HIGH);
          delay(3000);
          Serial.print('s');/telling plc to pt power back on
       }
        else if(inchar=='c')
        {
          //digitalWrite(13, LOW);
        }
        
  }
 unsigned long currentMillis = millis();
 
 if (currentMillis - previousMillis >= interval){
 
   previousMillis = currentMillis;
   watts_used =0.3125*buttonPushCounter;
   lcd.setCursor(12,1);
   lcd.print(watts_used);
   buttonPushCounter=0;
 
 }
 
 buttonState = digitalRead(buttonPin);
 
 if(buttonState != lastButtonState) {
 
   if(buttonState == HIGH) {
   
   buttonPushCounter++;
   lcd.setCursor(8,0);
   lcd.print(buttonPushCounter);
   
   }
   
   delay(50);
 }
 lastButtonState = buttonState;
 
 
 if (watts_used >= 2) 
 
 {
   Serial.print('a');//send to main station
   lcd.clear();
   lcd.print("Power exceeded");
   delay(1000);
   watts_used=0;
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print(" pulses: ");
   lcd.setCursor(0,1);
   lcd.print(" watts used ");
 }
 

}
