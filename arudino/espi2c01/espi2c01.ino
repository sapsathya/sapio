#include <ESP8266.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  pinMode(2,OUTPUT);
}

void loop() {
  tmElements_t tm;

  if (RTC.read(tm)) {
    Serial.print("clk on");
    //Serial.setCursor(0,0);
    Serial.print("Time: ");
    Serial.print(tm.Hour);
    Serial.print(':');
    Serial.print(tm.Minute);
    Serial.print(':');
    Serial.print(tm.Second);
    //Serial.setCursor(0,1);
    Serial.print("Date: ");
    Serial.print(tm.Day);
    Serial.print('/');
    Serial.print(tm.Month);
    Serial.print('/');
    Serial.print(tmYearToCalendar(tm.Year));
    if(tm.Second>=30)
    {
      digitalWrite(2,HIGH);
    }
    else
    {
      digitalWrite(2,LOW);
    }
  } else {
    if (RTC.chipPresent()) {
      Serial.println("The DS1307 is stopped.  Please run the SetTime");
      Serial.println("example to initialize the time and begin running.");
      Serial.println();
      Serial.print("nop");
    } else {
      Serial.println("DS1307 read error!  Please check the circuitry.");
      Serial.print("err");
      Serial.println();
    }
    delay(9000);
  }
  delay(1000);
  lcd.clear();
}
