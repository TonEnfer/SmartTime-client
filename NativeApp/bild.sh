#!/bin/sh

gcc -Wall -o timeApp main.c ./display/display.c ./bmp180/bmp180.c ./dht/dht22.c -lwiringPi -lpthread -lsqlite3 -lm
