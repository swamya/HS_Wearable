#include <SPI.h>
#include <SD.h>
#include "Common.h"
#include "DS3234_RTC.h"
#include "SD_Card.h"
#include "RGB.h"

void setup() {
  Serial.begin(9600);
  RTC_init();
  SD_init();
  analogReference(INTERNAL);
  RGB_init();
  readTimeDate();
  global_time = TimeDate[3]; //grab the current day of the week
  //day(1-31), month(1-12), year(0-99), hour(0-23), minute(0-59), second(0-59), weekday(1-7)
  //setTimeDate(1,4,13,17,13,00,1); 
}

void loop() {
  int analog_val = analogRead(ANALOG_PIN);
  String dataString = "";
  SPI.setDataMode(SPI_MODE1);
  readTimeDate();
  dataString = timeDateToString();
  SD_write_val(dataString);
  Serial.println(dataString); //For Testing - may be removed
  Serial.println(analog_val); //For Testing - may be removed
  
  local_time = TimeDate[3]; //grab the current day of the week
  
  if(analog_val > 0) { //User is receiving UV at this point    
    total_seconds++;    
    Serial.print("Number of seconds outside: "); //For Testing - may be removed
    Serial.println(total_seconds); //For Testing - may be removed
  }
  
  if(total_seconds > 0){
     //update the LED color. Should be dispersed over a 30 minute interval 
     int interval = secondsToInterval(total_seconds); //this will decide which color to light the LED
     changeLedColor(interval);       
  } 
  
  //Now let's handle a potential write to the SD card
  if(local_time != global_time){ //this should indicate a new day
    SPI.setDataMode(SPI_MODE0);
    File dataFile = SD.open("datalog.txt", FILE_WRITE);

    //if the file is available, write to it:
    if (dataFile) {
      dataFile.println(dataString);
      dataFile.close();
      // print to the serial port too:
    } else {
      Serial.println("error opening datalog.txt");
    } 
    resetVisualization(); //reset any necessary parameters for a new day
  }
  
  delay(1000);
}




