#include "main.h"

int main(int argsc,char ** argsv)
{
	wiringPiSetup();
	initDisplayPins();
	testDisplay();
	time_t rawtime;
    struct tm * timeinfo;

	//uint8_t oldmin = 99;
	while(1)
	{
		time ( &rawtime );
		timeinfo = localtime ( &rawtime );
		
		uint8_t h = (uint8_t)timeinfo->tm_hour;
		uint8_t m = (uint8_t)timeinfo->tm_min;
		uint8_t s = (uint8_t)timeinfo->tm_sec;
		printf("%d:%d:%d\n",h,m,s);
		uint8_t h1 = h/10;
		uint8_t h2 = h%10;
		uint8_t m1 = m/10;
		uint8_t m2 = m%10;
		printf("%d %d %d %d\n",h1,h2,m1,m2);
		if(oldmin != m){
			uint8_t data[4] = {getByteCode(m2),getByteCode(m1),getByteCode(h2),getByteCode(h1)};
			writeData(data,4);
			oldmin = m;
		}
		if(s%2)
			enableDots();
		else
			disableDots();
		delay(100);
	}
}
