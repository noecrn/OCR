CC=gcc
CFLAGS=-I.
DEPS = NeuralNetwork.h LoadDataSet.h
OBJ = NeuralNetwork.o LoadDataSet.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

NeuralNetwork: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)