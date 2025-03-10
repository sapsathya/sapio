#include <SoftwareSerial.h>
SoftwareSerial mySerial(3,2);
                 
void setup()
{
  mySerial.begin(9600);
  Serial.begin(9600); 
  pinMode(7,INPUT); 
  pinMode(12,OUTPUT);  
}
void loop()
{
int ch=digitalRead(7);

   switch(ch)
  {
    case 0:
    Serial.println("ok");
    break;
    case 1:
     DialCall();
     digitalWrite(12,HIGH);
      delay(10000);
      digitalWrite(12,LOW);
      SendMessage();
      break;
  } 
}
 void DialCall()
{
  mySerial.println("ATD+919347839681;"); 
}
 void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+918247064687\"\r"); // Replace x with mobile number
  delay(500);
  mySerial.println("LAT:27.2032N\nLONG:77.4985E");// The SMS text you want to sen
  mySerial.println((char)26);// ASCII code of CTRL+Z
}
void callreceive()
{
    mySerial.println("ATA");
}
 void HangCall()
 {
  mySerial.println("ATH");
 }
