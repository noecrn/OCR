# Specify the compiler
CC = gcc

# Specify any compiler flags
CFLAGS = `pkg-config --cflags gtk+-3.0`

# Specify any linker flags
LDFLAGS = `pkg-config --libs gtk+-3.0`

# Specify the source files
SRCS = interface.c

# Specify the output file 
OUT = interface

.PHONY: clean

all: $(OUT)
	@echo Program has been compiled

$(OUT): $(OBJS) 
	$(CC) $(CFLAGS) -o $(OUT) $(SRCS) $(LDFLAGS)

clean:
	$(RM) $(OUT)
