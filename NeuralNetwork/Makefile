CC=gcc
CFLAGS=-I. `sdl2-config --cflags`
LIBS=`sdl2-config --libs`
DEPS = NeuralNetwork.h LoadDataSet.h
OBJ = NeuralNetwork.o LoadDataSet.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

NeuralNetwork: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)