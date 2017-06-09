#ifndef _DISPLAY
#define _DISPLAY

#include <wiringPi.h>
#include <stdio.h>
#include <stdint.h>

#define DATA_PIN 2
#define CP_PIN 0
#define DOTS_PIN 7

void initDisplayPins();

void enableDots();
void disableDots();

void writeBit(uint8_t databit);
void writeByte(uint8_t databyte);
void writeData(uint8_t* data, uint8_t datalength);
uint8_t getByteCode(uint8_t number);
void testDisplay();




#endif
