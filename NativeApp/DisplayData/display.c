#include "display.h"

void initDisplayPins()
{
  pinMode(DATA_PIN, OUTPUT);
  digitalWrite(DATA_PIN, LOW);
  pinMode(CP_PIN, OUTPUT);
  digitalWrite(CP_PIN, LOW);
  pinMode(DOTS_PIN,OUTPUT);
  digitalWrite(DOTS_PIN,LOW);
//printf("init");
}

void enableDots()
{
	digitalWrite(DOTS_PIN,HIGH);
}

void disableDots()
{
	digitalWrite(DOTS_PIN,LOW);
}

void writeBit(uint8_t databit)
{
//printf("wr bit");
  digitalWrite(CP_PIN, LOW);

  digitalWrite(DATA_PIN, databit);
  delayMicroseconds(10);
  digitalWrite(CP_PIN, HIGH);
  delayMicroseconds(10);
}

void writeByte(uint8_t databyte) {
//printf("wr byte");
  for (uint8_t i = 0; i < 8; i++) {
    writeBit((databyte >> i) & 0x01);
  }
}
void writeData(uint8_t* data, uint8_t datalength) {
//printf("wr data");
  for (int i = 0; i < datalength; i++) {
    writeByte(data[i]);
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
      return 0b11110010;
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
