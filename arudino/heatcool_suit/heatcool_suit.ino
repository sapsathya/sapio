#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;

LiquidCrystal_I2C lcd(0x27,16,2);

TinyGPSPlus gps;

#define LM35 A0

SoftwareSerial ss(RXPin, TXPin);

float lm_value;
float tempc;

unsigned long previousMillis = 0;
const long interval = 1000;


void setup() {
  Serial.begin(9600);
  ss.begin(GPSBaud);
  pinMode(8,OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(2,0);
  lcd.print("INITIALISING");
  lcd.setCursor(5,1);
  lcd.print("SYSTEM");
  delay(2000);
  lcd.clear();
}

void loop() {
  lm_value = analogRead(LM35);
  tempc = (lm_value * 500) / 1023;
  lcd.setCursor(0,0);
  lcd.print("TEMP = ");
  lcd.print(tempc);
  lcd.print(" C");
  Serial.println(tempc);

  
  if (tempc > 60) {
    lcd.setCursor(0,1);
    lcd.print("OVER-HEATING");
    digitalWrite(8, HIGH);
  }
  else {
    lcd.setCursor(0,1);
    lcd.print("NORMAL TEMP");
    digitalWrite(8, LOW);
  }
   unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    gpsensor();
      delay(500);
  lcd.clear();
    previousMillis = currentMillis;
  }
}
void gpsensor()
{
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
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
  }
  else
  {
    Serial.println(F("INVALID"));
  }
  
}
