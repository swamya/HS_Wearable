#ifndef SD_Card_h
#define SD_Card_h

#include <SD.h>
#include <SPI.h>
#include "Common.h"

int SD_init(){

  Serial.print("Initializing SD card...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(10, OUTPUT);

  // see if the card is present and can be initialized:
  if (!SD.begin(SD_SELECT)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return 0;
  }
  Serial.println("card initialized.");
}

int SD_write_val(String dataString){

  SPI.setDataMode(SPI_MODE0);
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  //if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
  }  
  else {
    Serial.println("error opening datalog.txt");
  }   
}

#endif
