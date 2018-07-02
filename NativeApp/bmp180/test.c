#include "bmp180.h"
#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv){
	char *i2c_device = "/dev/i2c-0";
	int address = 0x77;
	
	void *bmp = bmp180_init(address, i2c_device);
	bmp180_eprom_t eprom;
	bmp180_dump_eprom(bmp, &eprom);
	
	
	bmp180_set_oss(bmp, 1);
	
	if(bmp != NULL){
		int i;
		for(i = 0; i < 10; i++) {
			float t = bmp180_temperature(bmp);
			float p = bmp180_pressure(bmp)*0.00750062f;
			float alt = bmp180_altitude(bmp);
			printf("t = %2.2f, p = %3.2f, a= %3.2f\n", t, p, alt);
			sleep(2);
		}
	
		bmp180_close(bmp);
	}
	
	return 0;
}
