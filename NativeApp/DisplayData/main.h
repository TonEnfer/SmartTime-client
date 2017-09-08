#ifndef _MAIN
#define _MAIN
//#define PC
#ifndef PC
#include <wiringPi.h>
#else
#include <unistd.h>
#define delay(i) sleep(i/1000)
#endif
#include <stdint.h>
#include <stdio.h>
#include "display.h"
#include <stdlib.h>

#define TIME 0
#define DATE 1
#define INT 2



#endif
