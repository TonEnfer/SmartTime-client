#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
 
#define MAX_TIMINGS	85
#define DHT_PIN		3	/* GPIO-22 */

float read_dht_data();
