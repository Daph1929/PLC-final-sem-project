/*
The circuit:
 Two devices which communicate serially are needed.
 * First serial device's TX attached to digital pin 10(RX), RX to pin 11(TX)
 * Second serial device's TX attached to digital pin 8(RX), RX to pin 9(TX)
 * note rx of arduino goes to tx
 */
#include <LiquidCrystal.h>
LiquidCrystal lcd( 2, 3, 4, 5, 11, 12);
// initialize the library with the numbers of the interface pins

#include <SoftwareSerial.h>
// software serial #1: RX = digital pin 6, TX = digital pin 7
//PLC
SoftwareSerial portOne(6, 7);

// software serial #2: RX = digital pin 8, TX = digital pin 9
// GSM
SoftwareSerial portTwo(8, 9);
int count=0;

void setup() {
  lcd.begin(16, 2);//lcd
   Serial.begin(9600);
  // Start each software serial port
  portOne.begin(9600);
  portTwo.begin(9600);

 lcd.display();
 lcd.print("PLC RX PART");
 delay(2000);
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print(" GSM INITIALIZATION ");
 //gsm Initialization
 portTwo.print("AT+CNMI=2,2,0,0,0\r"); 
  // blurt out contents of new SMS upon receipt to the GSM shield's serial out
  delay(100);
   portTwo.print("AT+CLIP=1\r"); // turn on caller ID notification
 delay(100);
 //GSM init done
 //lcd prints it
 lcd.clear();
 lcd.print(" READY tO GO... ");
  
  // Open serial communications and wait for port to open:
  
}
void sendmessage1()
{
   portTwo.print("\r");   
  delay(1000);
   portTwo.print("AT+CMGS=\"9850066713\"\r");    //Number to which you want to send the sms
  delay(1000);
   portTwo.print("warning 1 \r");   //The text of the message to be sent
  delay(1000);
  portTwo.write(0x1A);
  delay(1000);
  lcd.clear();
  lcd.print("message 1.. sent ");
 
}
void sendmessage2()
{
   portTwo.print("\r");   
  delay(1000);
 portTwo.print("AT+CMGS=\"9850066713\"\r");    //Number to which you want to send the sms
  delay(1000);
 portTwo.print("warning 2\r");   //The text of the message to be sent
  delay(1000);
   portTwo.write(0x1A);
  delay(1000);
   lcd.print("message 2 sent ");
}
void sendmessage3()
{
   portTwo.print("\r");   
  delay(1000);
   portTwo.print("AT+CMGS=\"9850066713\"\r");    //Number to which you want to send the sms
  delay(1000);
   portTwo.print("warning 3\r");   //The text of the message to be sent
  delay(1000);
   portTwo.write(0x1A);
  delay(1000);
   portOne.print('d');
  delay(1000);
   lcd.print("message 3 sent ");
}

void loop() {
  
  // By default, the last intialized port is listening.
  // when you want to listen on a port, explicitly select it:
  portOne.listen();

  // while there is data coming in, read it
  // and send to the hardware serial port:
 if(portOne.available() > 0) {
    char inByte = portOne.read();
    Serial.print(inByte);
    if(inByte=='a')
    {
      count++;
      if(count==1)
      {
      //digitalWrite(13,HIGH);
      sendmessage1();
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("message 1");
      lcd.setCursor(0,1);
      lcd.print("being sent");
      delay(2000);
      }
      else if(count==2)
      {
        sendmessage2();
        lcd.clear();
        lcd.setCursor(0,0);
      lcd.print("message 2");
      lcd.setCursor(0,1);
      lcd.print("being sent");
      }
       else if(count==3)
      {
        
        sendmessage3();
        lcd.clear();
        lcd.setCursor(0,0);
      lcd.print("message 3");
      lcd.setCursor(0,1);
      lcd.print("being sent");
      
       


        
      }
  }
}
while(count==3)//make sure that it will loop for reply so to save time
{
portTwo.listen();
   if(portTwo.available() > 0) 
   {
    char in = portTwo.read();
    if(in=='s')
    {
      //digitalWrite(13,LOW);
     // delay(10);
      portTwo.print("AT+CMGD=1,4"); // delete all SMS
      count=0;
      //delay(1000);
      portOne.print('c');
      lcd.clear();
      lcd.print("Power back on");
      
    }
   }

}
}





