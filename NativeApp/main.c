#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <sqlite3.h>
#include <string.h>
#include <fcntl.h>
#include "bmp180/bmp180.h"
#include "dht/dht22.h"
#include "display/display.h"

//Параметры и переменные базы данных
#define PATH "/var/www/smartTime/PythonApp/DB/db.sqlite"
#define GET_PARAM_QUERY "select * from Parameters"
#define MAX_PARAM 17
int count = 0;
sqlite3 *db; //База
char *zErrMsg = 0; //Код ошибки
int rc; //Результат

int temp = 0, press = 0, hum = 0;

//Тип структуры параметров
typedef struct p{
	pthread_mutex_t mutex;
	char tzName[128],ntp[128];
	bool timerEn;
	int timerTime, maxT, minT, maxH, minH, maxP, minP;
	bool showTime, showDate, showHum, showPress, showTemp,showTimer;
} params_t;

params_t params; //Переменная параметров
bool ntpEn = false;

void setTimeZone(char* name)
{
	char command[256];
	sprintf(command,"ln -sf /usr/share/zoneinfo/%s /etc/localtime",name);
    	system(command);
}

void * syncWithNTP(void * arg)
{
    //bool _ntpEn = (bool)arg;
    while(true)
    {
        bool* _ntpEn = (bool *)arg;
        //printf("SYNC WITH NTP. ntpEn = %i\n",_ntpEn[0]?1:0);
        if(_ntpEn[0])
        {
            char command[256];
            sprintf(command,"ntpdate -u %s",params.ntp);
            system(command);
        }
        sleep(10);
    }
}


static int fillParamsStruct(void *NotUsed, int argc, char **argv, char **azColName){
	int i;
	
	int value = 0;
		for(i=0; i<argc; i++){
			if(!strcmp(azColName[i],"value"))
			{
				
				char *name = calloc(64,sizeof(char));
				strcpy(name,argv[i-1] ? argv[i-1] : "NULL");
				if(!strcmp(name,"TZ"))
				{
                    char * v = calloc(512,sizeof(char));
                    
                    sscanf(argv[i],"%s",v);
                    if(strcmp(params.tzName,v)){
                        strcpy(params.tzName,v);
                        setTimeZone(params.tzName);
                        printf("params.tzName =  %s\n",params.tzName);
                    }
					return 0;
				}else if(!strcmp(name,"NTP")) {
                    char * v = calloc(512,sizeof(char));
                    sscanf(argv[i],"%s",v);
                    //printf("params.ntp =  %s\n",params.ntp);
                    if(strcmp(params.ntp,v)){
                        strcpy(params.ntp,v);
                        ntpEn = true;
                        printf("params.ntp =  %s\n",params.ntp);
                    }
                    return 0;
                }
                else{
				    sscanf(argv[i],"%i",&value);
				}
				if(!strcmp(name,"TimerEn"))
				{
					params.timerEn = value;
					printf("params.timerEn =  %i\n",params.timerEn);
				} else if(!strcmp(name,"TimerTime"))
				{
					params.timerTime = value;
					printf("params.timerTime =  %i\n",params.timerTime);
				} else if(!strcmp(name,"MaxT"))
				{
					params.maxT = value;
					printf("params.maxT =  %i\n",params.maxT);
				} else if(!strcmp(name,"MinT"))
				{
					params.minT = value;
					printf("params.minT =  %i\n",params.minT);
				} else if(!strcmp(name,"MaxH"))
				{
					params.maxH = value;
					printf("params.maxH  =  %i\n",params.maxH );
				} else if(!strcmp(name,"MinH"))
				{
					params.minH = value;
					printf("params.minH  =  %i\n",params.minH );
				} else if(!strcmp(name,"MaxP"))
				{
					params.maxP = value;
					printf("params.maxP =  %i\n",params.maxP);
				} else if(!strcmp(name,"MinP"))
				{
					params.minP = value;
					printf("params.minP =  %i\n",params.minP);
				} else if(!strcmp(name,"showTime"))
				{
					params.showTime = value;
					printf("params.showTime  =  %i\n",params.showTime );
				} else if(!strcmp(name,"showDate"))
				{
					params.showDate = value;
					printf("params.showDate =  %i\n",params.showDate);
				} else if(!strcmp(name,"showHum"))
				{
					params.showHum = value;
					printf("params.showHum =  %i\n",params.showHum);
				} else if(!strcmp(name,"showPress"))
				{
					params.showPress = value;
					printf("params.showPress =  %i\n",params.showPress);
				} else if(!strcmp(name,"showTemp"))
				{
					params.showTemp = value;
					printf("params.showTemp =  %i\n",params.showTemp);
				}
                else if(!strcmp(name,"showTimer"))
				{
					params.showTimer = value;
					printf("params.showTimer =  %i\n",params.showTimer);
				}
			}
		}
	return 0;
}
int oldmin = 99;
void showTime_fn(uint8_t sec)
{
	uint8_t cnt = sec;
	printf("TIME\n");
	time_t rawtime;
    	struct tm * timeinfo;
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
		
	uint8_t h = (uint8_t)timeinfo->tm_hour;
	uint8_t m = (uint8_t)timeinfo->tm_min;
	uint8_t s = (uint8_t)timeinfo->tm_sec;
//	printf("%d:%d:%d\n",h,m,s);
	uint8_t h1 = h/10;
	uint8_t h2 = h%10;
	uint8_t m1 = m/10;
	uint8_t m2 = m%10;
//	printf("%d %d %d %d\n",h1,h2,m1,m2);
	uint8_t data[4] = {getByteCode(m2),getByteCode(m1),getByteCode(h2),getByteCode(h1)};
	writeData(data,4);
	if(s%2)
		enableDots();
	else
		disableDots();
	oldmin = m;
	while(cnt > 0)
	{
		time ( &rawtime );
		timeinfo = localtime ( &rawtime );
		
		uint8_t h = (uint8_t)timeinfo->tm_hour;
		uint8_t m = (uint8_t)timeinfo->tm_min;
		uint8_t s = (uint8_t)timeinfo->tm_sec;
//		printf("%d:%d:%d\n",h,m,s);
		uint8_t h1 = h/10;
		uint8_t h2 = h%10;
		uint8_t m1 = m/10;
		uint8_t m2 = m%10;
//		printf("%d %d %d %d\n",h1,h2,m1,m2);
		if(oldmin != m){
			uint8_t data[4] = {getByteCode(m2),getByteCode(m1),getByteCode(h2),getByteCode(h1)};
			writeData(data,4);
			oldmin = m;
		}
		if(s%2)
			enableDots();
		else
			disableDots();
		printf("s = %i\n",cnt);
		sleep(1);
		cnt-=1;
		
	}
	disableDots();
}

void showDate_fn()
{
	printf("DATE\n");
	time_t rawtime;
    	struct tm * timeinfo;
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	uint8_t d = (uint8_t)timeinfo->tm_mday;
	uint8_t m = (uint8_t)timeinfo->tm_mon + 1;
	int y = (int)timeinfo->tm_year+ 1900;
	uint8_t d1 = d/10;
	uint8_t d2 = d%10;
	uint8_t m1 = m/10;
	uint8_t m2 = m%10;
	printf("d1 = %d, d2 = %d, m1 = %d, m2 = %d\n",d1,d2,m1,m2);
	uint8_t dm[4] = {getByteCode(m2),getByteCode(m1),getByteCode(d2),getByteCode(d1)};
	writeData(dm,4);
	sleep(3);
	uint8_t yr[4];
	yr[0] = y/1000;
	yr[1] = y%1000/100;
	yr[2] = y%100/10;
	yr[3] = y%10;
	printf("y = %i, y1 = %d, y2 = %d, y3 = %d, y4 = %d\n",y,yr[0],yr[1],yr[2],yr[3]);
	uint8_t year[4] = {getByteCode(yr[3]),getByteCode(yr[2]),getByteCode(yr[1]),getByteCode(yr[0])};
	writeData(year,4);
	sleep(3);
}

void showTemp_fn(uint8_t sec)
{
	printf("TEMP\n");
	uint8_t data[4] = {ASCIItoByteCode('C'),getByteCode(temp%10),getByteCode(temp/10),ASCIItoByteCode((temp>0)?'+':'-')};
	writeData(data,4);
	sleep(sec);
}

void showHum_fn(uint8_t sec)
{
	printf("HUM\n");
	if(hum){
		uint8_t data[4] = {ASCIItoByteCode('H'),getByteCode(hum%10),getByteCode(hum%100/10),getByteCode(hum/100)};
		writeData(data,4);
		sleep(sec);
	}
}

void showPress_fn(uint8_t sec)
{
	printf("PRESS\n");
	uint8_t data[4] = {ASCIItoByteCode('P'),getByteCode(press%10),getByteCode(press%100/10),getByteCode(press/100)};
		writeData(data,4);
		sleep(sec);
}

void showTimer_fn()
{
	printf("TIMER\n");
}

enum STATE
{
    TIME = 0,
    DATE,
    TIMER,
    TEMP,
    PRESS,
    HUM
} showState;

void * showData_fn(void *arg) { 
	params_t * param = (params_t *)arg;
    int state = 0;
	while(true){
		param = (params_t *)arg;
		sleep(1);
		printf("Show data\n");
        pthread_mutex_lock(&(param->mutex));
        switch(state){
            case(TIME):
                if(param->showTime){
                    pthread_mutex_unlock(&(param->mutex));
			         showTime_fn(5);
                }
                state++;
            break;
            case(DATE):
                if(param->showDate){
                    pthread_mutex_unlock(&(param->mutex));
                     showDate_fn();
                }
                state++;
            break;
            case(TIMER):
                if(param->showTimer){
                    pthread_mutex_unlock(&(param->mutex));
                     showTimer_fn();}
                state++;
            break;
            case(TEMP):
                if(param->showTemp){
                    pthread_mutex_unlock(&(param->mutex));
                    showTemp_fn(5);
                }
                     
                state++;
            break;
            case(PRESS):
                if(param->showPress){
                    pthread_mutex_unlock(&(param->mutex));
                     showPress_fn(5);}
                state++;
            break;
            case(HUM):
                 if(param->showHum){
                     pthread_mutex_unlock(&(param->mutex));
                     showHum_fn(5);}
            state = 0;
            break;
    }
        pthread_mutex_unlock(&(param->mutex));
		
	}
}

void * getHum_fn(void *arg){
	while(true){
		printf("get hum\n");
		float h = read_dht_data();
		printf("h = %f\n",h);
		if(h > 0.0)
		{
			//printf("h = %f\n",h);
			hum = (int)h;
			char tmp[512];
			sprintf(tmp,"insert into Humidity(date,value) values ('%ld','%f')",time(NULL),h);
			rc = sqlite3_exec(db, tmp,NULL, 0, &zErrMsg);
			if( rc!=SQLITE_OK ){
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
				sqlite3_free(zErrMsg);
			}
		}
		sleep(13);
	}
}
void * getPress_fn(void *arg){
	char *i2c_device = "/dev/i2c-0";
	int address = 0x77;
	
	void *bmp = bmp180_init(address, i2c_device);
	bmp180_eprom_t eprom;
	bmp180_dump_eprom(bmp, &eprom);
	
	
	bmp180_set_oss(bmp, 1);
	
	if(bmp != NULL){
		while(true){
			printf("get press\n");
			float t = bmp180_temperature(bmp);
			temp = (int)t;
			char tmp[512];
			sprintf(tmp,"insert into Temperature(date,value) values ('%ld','%f')",time(NULL),t);
			rc = sqlite3_exec(db, tmp,NULL, 0, &zErrMsg);
		if( rc!=SQLITE_OK ){
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		}
			float p = (bmp180_pressure(bmp)*0.00750062f);
			sprintf(tmp,"insert into Pressure(date,value) values ('%ld','%f')",time(NULL),p);
			rc = sqlite3_exec(db, tmp,NULL, 0, &zErrMsg);
		if( rc!=SQLITE_OK ){
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		}
			press = (int)p;
			printf("t = %f; p = %f\n",t,p);
			sleep(13);
		}
	}
}


void * getParams_fn(void*arg)
{	
	params_t * param = (params_t *)arg;
	while(true)
	{
	
		param = (params_t *)arg;
		pthread_mutex_lock(&(param->mutex));
		printf("get Param\n");
		rc = sqlite3_exec(db, GET_PARAM_QUERY, fillParamsStruct, 0, &zErrMsg);
		if( rc!=SQLITE_OK ){
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		}
		pthread_mutex_unlock(&(param->mutex));
		sleep(10);
	}
}

int openDB(char* path)
{
   rc = sqlite3_open(path, &db);
   if( rc ){
     fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      sqlite3_close(db);
      return 0;
    }
    return 1;
}

int main(int argc, char * argv[]){
    //sleep(10);
	if ( wiringPiSetup() == -1 )
		exit( 1 );
	int result;
	initDisplayPins();
	testDisplay();

	pthread_mutex_init(&(params.mutex), NULL);
	
	pthread_t getHum_th, getPress_th, showData_th, getParams_th,syncWithNTP_th;
	
	if(!openDB(PATH)){
		perror("DB not open");
		return EXIT_FAILURE;
	}
    
    result = pthread_create(&syncWithNTP_th, NULL, syncWithNTP,&ntpEn);
	if (result != 0) {
		perror("Creating getHum thread");
		return EXIT_FAILURE;
	}
	
	result = pthread_create(&getHum_th, NULL, getHum_fn, NULL);
	if (result != 0) {
		perror("Creating getHum thread");
		return EXIT_FAILURE;
	}
	
	result = pthread_create(&getPress_th, NULL, getPress_fn, NULL);
	if (result != 0) {
		perror("Creating the getPress thread");
		return EXIT_FAILURE;
	}
	
	result = pthread_create(&showData_th,NULL,showData_fn,&params);
		if (result != 0) {
		perror("Creating the showData thread");
		return EXIT_FAILURE;
	}
	
	result = pthread_create(&getParams_th,NULL,getParams_fn,&params);
		if (result != 0) {
		perror("Creating the showData thread");
		return EXIT_FAILURE;
	}
	result = pthread_join(getHum_th, NULL);
	if (result != 0) {
		perror("Joining the getHum thread");
		return EXIT_FAILURE;
	}
	
	result = pthread_join(getPress_th, NULL);
	if (result != 0) {
		perror("Joining the getPress thread");
		return EXIT_FAILURE;
	}
	
	result = pthread_join(showData_th, NULL);
	if (result != 0) {
		perror("Joining the showData thread");
		return EXIT_FAILURE;
	}
	result = pthread_join(getParams_th, NULL);
	if (result != 0) {
		perror("Joining the showData thread");
		return EXIT_FAILURE;
	}
	
	printf("Exit\n");
	return EXIT_SUCCESS;
}
