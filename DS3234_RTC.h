#ifndef DS3234_RTC_h
#define DS3234_RTC_h

#include <SPI.h>
#include "Common.h"

int RTC_init(){
  
  // Initialize the real-time-clock
  pinMode(RTC_SELECT,OUTPUT); // chip select
  // start the SPI library:
  SPI.begin();
  SPI.setBitOrder(MSBFIRST); 
  SPI.setDataMode(SPI_MODE1); // both mode 1 & 3 should work 
  //set control register 
  digitalWrite(RTC_SELECT, LOW);  
  SPI.transfer(0x8E);
  SPI.transfer(0x60); //60= disable Oscillator and Battery SQ wave @1hz, temp compensation, Alarms disabled
  digitalWrite(RTC_SELECT, HIGH);
  delay(10);

}

int setTimeDate(int d, int mo, int y, int h, int mi, int s, int wd){ 
  
int TimeDate [7] = { s,mi,h,wd,d,mo,y };
  
  for(int i=0; i<=6;i++){  
    int b= TimeDate[i]/10;
    int a= TimeDate[i]-b*10;
    if(i==2){
      if (b==2)
        b=B00000010;
      else if (b==1)
        b=B00000001;
    }	
    TimeDate[i]= a+(b<<4);

    digitalWrite(RTC_SELECT, LOW);
    SPI.setDataMode(SPI_MODE1);
    SPI.transfer(i+0x80); 
    SPI.transfer(TimeDate[i]);        
    digitalWrite(RTC_SELECT, HIGH);
  }
}

byte bcdToDec(byte val) {
  // convert binary coded decimal to normal decimal numbers
  // right shift by 4 is the same as dividing by 16
  return ( ((val >>4) *10) + (val%16) ); 
}

void readTimeDate(){
  
  SPI.setDataMode(SPI_MODE1);
  for (int i = 0; i < 7; i++){
    digitalWrite(RTC_SELECT, LOW);
    SPI.transfer(i+0x00); 

    if (i == 2)
      TimeDate[i] = bcdToDec(SPI.transfer(0x00 & 0b111111));  
    else
      TimeDate[i] = bcdToDec(SPI.transfer(0x00)); 
  
    digitalWrite(RTC_SELECT, HIGH);

  }
}

String timeDateToString(){
  String temp = "";

  temp.concat(TimeDate[5]); //month
  temp.concat("/") ;
  temp.concat(TimeDate[4]); //day
  temp.concat("/") ;
  temp.concat(TimeDate[6]); //year
  temp.concat("     ") ;
  temp.concat(TimeDate[2]); //hour
  temp.concat(":") ;
  temp.concat(TimeDate[1]); //min
  temp.concat(":") ;
  temp.concat(TimeDate[0]); //sec
  temp.concat(":");
  temp.concat(TimeDate[3]); //weekday 1 (mon) - 7(sun)

  return(temp);

}

#endif

