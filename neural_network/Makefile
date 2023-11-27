CC = gcc
CFLAGS = -Wall
LDFLAGS = -lm -ljpeg
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
EXECUTABLE = mon_programme

all: $(EXECUTABLE)
	./$(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(EXECUTABLE)
