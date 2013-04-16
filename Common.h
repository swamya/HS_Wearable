#ifndef Common_h
#define Common_h

// Slave select for real time clock
const int RTC_SELECT=10; 

// Slave select for SD card
const int SD_SELECT=9; // SPI chip select for SD Card

// 0 (sec), 1 (min), 2 (hour), 3 (weekday 1-mon, 7-sun)
// 4 (day), 5 (month), 6 (year)
int TimeDate[7];

#endif
