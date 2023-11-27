# Makefile

CC = gcc
CPPFLAGS =
CFLAGS = -g -Wall -Wextra -O3 `pkg-config --cflags sdl2 SDL2_image` 
LDFLAGS =
LDLIBS = `pkg-config --libs sdl2 SDL2_image` -lm

all: detection3

SRC = detection3.c
OBJ = ${SRC:.c=.o}
EXE = ${SRC:.c=}

detection: detection3.o

.PHONY: clean

clean:
	${RM} ${OBJ}
	${RM} ${EXE}

# END

