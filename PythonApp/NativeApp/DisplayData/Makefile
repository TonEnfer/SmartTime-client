TARGET = DisplayData
SRCS = main.c display.c
OBJS = $(SRCS:.c=.o)
CFLAGS = -O2 -Wall -lwiringPi -lpthread

.PHONY: all clean

all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(CFLAGS)
 
.c.o:
	$(CC) $(CFLAGS)  -c $< -o $@

clean:
	rm -rf $(TARGET) $(OBJS)