# Makefile

#TARGET = prog
#LIBS = `pkg-config --libs sdl2 SDL2_image` -lm
#CC = gcc
#CFLAGS = -Wall -Wextra -O3 `pkg-config --cflags sdl2 SDL2_image` 

#.PHONY: default all clean

#default: $(TARGET)
#all: default

#OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
#HEADERS = $(wildcard *.h)

#%.o: %.c $(HEADERS)
#	$(CC) $(CFLAGS) -c $< -o $@

#.PRECIOUS: $(TARGET) $(OBJECTS)

#$(TARGET): $(OBJECTS)
#	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

#clean:
#	-rm -f *.o
#	-rm -f $(TARGET)
	
# END


TARGET = prog
LIBS = `pkg-config --libs sdl2 SDL2_image` -lm
CC = gcc
CFLAGS = -Wall -Wextra -O3 `pkg-config --cflags sdl2 SDL2_image`

.PHONY: default all clean

default: $(TARGET)
all: default

SOURCES = grid_detect.c main.c
HEADERS = grid_detect.h
OBJECTS = $(SOURCES:.c=.o)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f $(TARGET)

