#ifndef RGB_h
#define RGB_h

#include <SPI.h>
#include "Common.h"

//Initialize the RGB LED
void RGB_init(){
  pinMode(BLUE_LED,OUTPUT);
  pinMode(RED_LED,OUTPUT);
  pinMode(GREEN_LED,OUTPUT);
  analogWrite(BLUE_LED,255);
  analogWrite(GREEN_LED,252);
  analogWrite(RED_LED,92); //default the LED to DARK_RED if total_seconds == 0
}

//This function will change the color of the LED based on the the RGB parameters.
void ledUpdate(int red, int green, int blue){
   int new_red = 255 - red;
   int new_green = 255 - green;
   int new_blue = 255 - blue; 
   analogWrite(BLUE_LED,new_blue);
   analogWrite(GREEN_LED,new_green);
   analogWrite(RED_LED,new_red);   
}

//This function is used to determine which color the LED should 
//be based on the amount of time the user has spent outside.
//It's currently divided into 6 intervals, each 5 minutes long.
int secondsToInterval(int seconds){
   
      if (seconds <= 300){ return 1;}
      else if (seconds <= 600){ return 2;}
      else if (seconds <= 900){ return 3;}
      else if (seconds <= 1200){ return 4;}
      else if (seconds <= 1500){ return 5;}
      else { return 6;}
   
}

//This function will actually set the RGB values of the LED
void changeLedColor(int val){
   switch(val){
     case 1: ledUpdate(255,85,0); //red/orange
             break;
     case 2: ledUpdate(255,185,0); //orange
             break;
     case 3: ledUpdate(237,252,0); //yellow
             break;
     case 4: ledUpdate(189,255,0); //yellow/green
             break;
     case 5: ledUpdate(50,224,0); //green
             break;
     case 6: ledUpdate(14,134,0); //greener green :)
             break;
   }    
}

#endif
