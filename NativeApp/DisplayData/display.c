#include "display.h"

void initDisplayPins()
{
#ifndef PC
  pinMode(DATA_PIN, OUTPUT);
  digitalWrite(DATA_PIN, LOW);
  pinMode(CP_PIN, OUTPUT);
  digitalWrite(CP_PIN, LOW);
  pinMode(DOTS_PIN,OUTPUT);
  digitalWrite(DOTS_PIN,LOW);
#endif
printf("init pins\n");
}

void enableDots()
{
#ifndef PC
	digitalWrite(DOTS_PIN,HIGH);
#endif
}

void disableDots()
{
#ifndef PC
	digitalWrite(DOTS_PIN,LOW);
#endif
}

void writeBit(uint8_t databit)
{
//printf("wr bit");
#ifndef PC
  digitalWrite(CP_PIN, LOW);

  digitalWrite(DATA_PIN, databit);
  delayMicroseconds(10);
  digitalWrite(CP_PIN, HIGH);
  delayMicroseconds(10);
#endif
}

void writeByte(uint8_t databyte) {
#ifndef PC
  for (uint8_t i = 0; i < 8; i++) {
    writeBit((databyte >> i) & 0x01);
  }
#endif
}
void writeData(uint8_t* data, uint8_t datalength) {
#ifndef PC
//printf("wr data");
  for (int i = 0; i < datalength; i++) {
    writeByte(data[i]);
  }
#else
	char *c = (char *)calloc(5,sizeof(char));
	for(uint8_t i = 0; i < 4; i++)
		c[i] = ByteCodeToASCII(data[i]);
	printf("%s\n",c);
#endif
}
#ifdef PC
char ByteCodeToASCII(uint8_t code)
{
	switch (code)
	 	{
	    case 0b11111100:
	      return '0';
	    case 0b00001100:
	      return '1';
	    case 0b11011010:
	      return '2';
	    case 0b10011110:
	      return '3';
	    case 0b00101110:
	      return '4';
	    case 0b10110110:
	      return '5';
	    case 0b11110110:
	      return '6';
	    case 0b00011100:
	      return '7';
	    case 0b11111110:
	      return '8';
	    case 0b10111110:
	      return '9';
	    case 0b00100000:
		return '-';
	    default:
	      return 0;
		
		}
}
#endif
uint8_t ASCIItoByteCode(char c)
{
	switch (c)
 	{
    case '0':
      return 0b11111100;
    case '1':
      return 0b00001100;
    case '2':
      return 0b11011010;
    case '3':
      return 0b10011110;
    case '4':
      return 0b00101110;
    case '5':
      return 0b10110110;
    case '6':
      return 0b11110110;
    case '7':
      return 0b00011100;
    case '8':
      return 0b11111110;
    case '9':
      return 0b10111110;
    case '-':
	return 0b00100000;
    default:
      return 0;
		
	}
}

uint8_t getByteCode(uint8_t number)
{
//printf("get byte code for %d",number);
  switch (number)
  {
    case 0:
      return 0b11111100;
    case 1:
      return 0b00001100;
    case 2:
      return 0b11011010;
    case 3:
      return 0b10011110;
    case 4:
      return 0b00101110;
    case 5:
      return 0b10110110;
    case 6:
      return 0b11110110;
    case 7:
      return 0b00011100;
    case 8:
      return 0b11111110;
    case 9:
      return 0b10111110;
    default:
      return 0;
  }
}
void testDisplay()
{
  uint8_t data[4] = {0, 0, 0, 0};
  for (uint8_t i = 0; i < 11; i++)
  {
    for (uint8_t j = 0; j < 4; j++)
      data[j] = getByteCode(i);
    writeData(data, 4);
    delay(500);

  }
}
