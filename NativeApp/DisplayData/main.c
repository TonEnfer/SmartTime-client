#include "main.h"
typedef uint8_t dataType;

int main(int argc,char ** argv)
{
#ifndef PC
	wiringPiSetup();
#endif
	initDisplayPins();

	dataType type;
   sscanf(argv[1],"%hhu",&type);
    	
   printf("type is %u\n",type);
	char * dt = argv[2];
	switch (type)
	{
		case (TIME):{
		uint8_t h;
		uint8_t m;
		uint8_t s;
		sscanf(dt,"%hhu:%hhu:%hhu",&h,&m,&s);
		uint8_t h1 = h/10;
		uint8_t h2 = h%10;
		uint8_t m1 = m/10;
		uint8_t m2 = m%10;
		uint8_t data[4] = {
			getByteCode(m2),
			getByteCode(m1),
			getByteCode(h2),
			getByteCode(h1)
			};
		writeData(data,4);
		if(s%2)
			enableDots();
		else
			disableDots();
		break;}
		case (DATE):{
		uint8_t d,m;
		uint16_t y;
		sscanf(dt,"%hhu.%hhu.%hu",&d,&m,&y);
		uint8_t d1,d2,m1,m2,y1,y2,y3,y4;
		d1 = d/10;
		d2 = d%10;
		m1 = m/10;
		m2 = m%10;
		y1 = y/1000;
		y2 = y%1000/100;
		y3 = y%100/10;
		y4 = y%10;
		uint8_t data[4] = {
			getByteCode(m2),
			getByteCode(m1),
			getByteCode(d2),
			getByteCode(d1)
			};
		writeData(data,4);
		delay(1000);
		uint8_t yearData [4]= 	{
			getByteCode(y4),
			getByteCode(y3),
			getByteCode(y2),
			getByteCode(y1)
			};
		writeData(yearData,4);
		break;
		case(INT):{
			int d;
			sscanf(dt,"%i",d);
		
			if(d <= 9999 && d >= -999)
			{
				char * buf = (char*)calloc(4,sizeof(char));
				sprintf(buf,"%d",d);
				uint8_t data[4];
				for(uint8_t i = 0; i < 4; i++)
				{
					data[i] = ASCIItoByteCode(buf[4-i]);
				}
				writeData(data,4);
			}
		}
		break;
		default:
		return 0;
	}
return 0;
}}