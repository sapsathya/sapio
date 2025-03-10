#include <TinyGPS++.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(3,2);
static const int RXPin = 5, TXPin = 4;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);
 int LED = 9;  
      int ALCOHOL_sensor = A3;// MQ-6 SENSOR  
      int ALCOHOL_detected;  

void setup()
{
  Serial.begin(9600);
   mySerial.begin(9600);
  ss.begin(GPSBaud);
  Serial.println();
  pinMode(12,OUTPUT);  
  pinMode(A0,INPUT);
  digitalWrite(12,LOW);
   pinMode(LED, OUTPUT);  
   pinMode(ALCOHOL_sensor, INPUT);  
}

void loop()
{
  int a=digitalRead(7);
int b=analogRead(A0);{
   if(a==0){
    Serial.println("ok");}
    if(a==1){
     DialCall();
     digitalWrite(12,HIGH);
      delay(10000);
      digitalWrite(12,LOW);
      SendMessage();}
}
  while (ss.available() > 0)
    if (gps.encode(ss.read()))
      displayInfo();

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("MRCET"));
    while(true);
  }
}

void displayInfo()
{
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);Serial.print(" N");
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);Serial.print(" E");
  }
  else
  {
    Serial.print(F("INVALID"));
  }

}
void DialCall()
{
  mySerial.println("ATD+916301255484;"); 
}
 void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+916301255484\"\r"); // Replace x with mobile number
  delay(500);
  mySerial.println("HELP IM IN DANGER MRCET/ 17.561618,78.455512");// The SMS text you want to sen
  mySerial.println((char)26);// ASCII code of CTRL+Z
   {  
         ALCOHOL_detected = analogRead(ALCOHOL_sensor);  
          Serial.println(ALCOHOL_detected);  
         if (ALCOHOL_detected <=450)  
         {  
           Serial.println("ALCOHOL detected...");  
           digitalWrite(LED, HIGH);  
         }  
         else  
         {  
           Serial.println("No ALCOHOL detected ");  
           digitalWrite(LED, LOW);  
         }  
       }  
}  
