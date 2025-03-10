#include <TinyGPS++.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(3,2);
static const int RXPin = 5, TXPin = 4;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

void setup()
{
  Serial.begin(9600);
   mySerial.begin(9600);
  ss.begin(GPSBaud);
  Serial.println();
  pinMode(12,OUTPUT);  
  pinMode(A0,INPUT);
  digitalWrite(12,LOW);
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
    Serial.println(F("No GPS detected: check wiring."));
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
  mySerial.println("ATD+916281859271;"); 
}
 void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+916281859271\"\r"); // Replace x with mobile number
  delay(500);
  mySerial.println("");// The SMS text you want to sen
  mySerial.println((char)26);// ASCII code of CTRL+Z
}
