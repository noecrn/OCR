# Makefile for XOR project in xor folder

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = -lm

# Source files
SOURCES = ../init_NN.c ../NN_fun.c xor.c main.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = xor.exe

# Targets
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean

