#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../init_NN.h"
#include "../NN_fun.h"
#include "xor.h"


int main ()
{
	clock_t start = clock();
	printf("Training a new XOR network ...\n");
    	int layer[2] = {10, 1};
    	NeuralNetwork neuralnetwork = init_neuralNetwork(2, layer, 2);
    	XORtraining(100000, neuralnetwork);
	printf("================\n");
        printf("      XOR       \n");
        printf("================\n");
    	printf("1 - 1 : ");
    	XOR(neuralnetwork, 1.0, 1.0);
    	printf("0 - 1 : ");
    	XOR(neuralnetwork, 0.0, 1.0);
    	printf("1 - 0 : ");
    	XOR(neuralnetwork, 1.0, 0.0);
    	printf("0 - 0 : ");
    	XOR(neuralnetwork, 0.0, 0.0);
    	free_neuralNetwork(neuralnetwork);
	clock_t end = clock();
	double timer = (double)(end - start) / CLOCKS_PER_SEC;
	printf("Training completed in %fs\n", timer);
    	return 0;
}
