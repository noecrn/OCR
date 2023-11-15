CC = gcc
CPPFLAGS =
CFLAGS = -Wall -Wextra -O3 `pkg-config --cflags sdl2 SDL2_image`
LDFLAGS =
LDLIBS = `pkg-config --libs sdl2 SDL2_image` -lm

SRC = main.c rotation.c save.c
OBJ = ${SRC:.c=.o}
EXE = ${SRC:.c=}

all: main save

main: rotation.o

rotation: rotation.o main.o

save: save.o rotation.o

.PHONY: clean

clean:
	${RM} ${OBJ}
	${RM} ${EXE}
