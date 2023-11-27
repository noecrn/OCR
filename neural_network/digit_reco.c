
#include "digit_reco.h"
#include <math.h>
#include "init_NN.h"
#include "NN_fun.h"
#include <stdio.h>
#include <stdlib.h>
#include "data_set_reader.h"
#include <math.h>
#include <time.h>

int main(int argc, char* argv[])
{

    if (argc != 3) {
        fprintf(stderr, "Format: %s <training number> <testing number>\n", argv[0]);
        return 1;
    }

    int numTraining = atoi(argv[1]);
    int numTesting = atoi(argv[2]);

    /*if(numTraining+numTesting > 29000)
    {
	    fprintf(stderr, "database <= 29000\n");
	    return 1;
    }*/

    int nboutput = 10;
    int layer[3] = {20, 15, nboutput};
    NeuralNetwork neuralnetwork = init_neuralNetwork(784, layer, 2);

    clock_t start = clock();
    printf("Training a digit-recognization neural network...\n");

    // Allocation dynamique pour le tableau de pointeurs
    double **training = (double **)malloc(numTraining * sizeof(double *));
    double *expectedTrain = malloc(numTraining * sizeof(double));
    double **testing = (double **)malloc(numTesting * sizeof(double *));
    double *expectedTest = malloc(numTesting * sizeof(double));

    data(numTraining, numTesting, training, expectedTrain, testing, expectedTest);

    for(size_t i = 0; i < numTraining%29000; i++)
    {
        double expec[nboutput];
        for(size_t k = 0; k < nboutput; k++) expec[k] = 0.0;
        expec[(int)(expectedTrain[i])] = 1.0;

        feedForward(neuralnetwork, training[i], 784);
        backPropagation(neuralnetwork, expec);
        updateWeigth(neuralnetwork, training[i], 784, 0.2);
    }

    clock_t end = clock();
	double timer = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Training competed in %fs\n", timer);

    size_t right = 0;
    printf("Testing...\n");
    for(size_t i = 0; i < numTesting%29000; i++)
    {
        feedForward(neuralnetwork, testing[i], 784);
        Layer *layer = neuralnetwork.end -1;
        size_t maxindex = 0;
        Neuron maximum = init_neuron(1);
        size_t counter = 0;
    	for(Neuron *i = layer->neuron; i < layer->end; i++)//for each neuron in the last layer
    	{
//	    printf("%f\n", i->output);
            if(i->output > maximum.output)
            {
                maximum = *i;
                maxindex = counter;
            }
            counter++;
    	}
//	printf("res : %f\n", (double)maxindex);
//	printf("expected : %f\n", expectedTest[i]);
        right += (expectedTest[i] == (double)maxindex);
    }
    printf("Results of the testing : %li / %d found.\n", right, numTesting);

    freeData(numTraining, numTesting, training, expectedTrain, testing, expectedTest);

    return EXIT_SUCCESS;
}

