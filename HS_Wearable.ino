#include <SPI.h>
#include <SD.h>
#include "Common.h"
#include "DS3234_RTC.h"
#include "SD_Card.h"

void setup() {
  Serial.begin(9600);
  RTC_init();
  SD_init();

  //day(1-31), month(1-12), year(0-99), hour(0-23), minute(0-59), second(0-59), weekday(1-7)
  //setTimeDate(1,4,13,17,13,00,1); 
}

void loop() {

  String dataString = "";
  readTimeDate();
  dataString = timeDateToString();
  SD_write_val(dataString);
  Serial.println(dataString);
  delay(1000);
}




