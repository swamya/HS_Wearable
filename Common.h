#ifndef Common_h
#define Common_h

// Slave select for real time clock
const int RTC_SELECT=10; 

// Slave select for SD card
const int SD_SELECT=9; // SPI chip select for SD Card

// UV data enters on this pin
const int ANALOG_PIN = 2; 

// Pins for accessing the RGB LED
const int BLUE_LED = 3;
const int GREEN_LED = 5;
const int RED_LED = 6;

// 0 (sec), 1 (min), 2 (hour), 3 (weekday 1-mon, 7-sun)
// 4 (day), 5 (month), 6 (year)
int TimeDate[7];

// This is the counter for the amount of time spend outside on a given day
int total_seconds = 0;

int global_time;
int local_time;
#endif
