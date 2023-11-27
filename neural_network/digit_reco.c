
#include "digit_reco.h"
#include <math.h>
#include "init_NN.h"
#include "NN_fun.h"
#include <stdio.h>
#include <stdlib.h>
#include "data_set_reader.h"
#include <math.h>
#include <time.h>


void save_weights(NeuralNetwork neuralnetwork, const char *filename) {
	// Open the file
	FILE *file = fopen(filename, "w");
	if (file == NULL) {
		printf("Error opening file\n");
		return;
	}

	// Iterate over each layer
	for (int l = 0; l < neuralnetwork.nbr_layers; l++) {
		Layer layer = neuralnetwork.layer[l];

		// Iterate over each neuron
		for (int n = 0; n < layer.nbr_neurons; n++) {
			Neuron neuron = layer.neuron[n];

			// Write the weights to the file
			for (int i = 0; i < neuron.nbr_weight; i++) {
				fprintf(file, "%f ", neuron.weight[i]);
			}
			fprintf(file, "\n");
		}
	}

	// Close the file
	fclose(file);
}


int main(int argc, char* argv[])
{

    if (argc != 2) {
        fprintf(stderr, "Format: %s <Generation number>\n", argv[0]);
        return 1;
    }

    int numTraining = 19000;//atoi(argv[1]);
    int numTesting = 10000;//atoi(argv[2]);

    /*if(numTraining+numTesting > 29000)
    {
	    fprintf(stderr, "database <= 29000\n");
	    return 1;
    }*/
    printf("Training a digit-recognization neural network...\n");
    clock_t start = clock();

    int nboutput = 10;
    int layer[2] = {25, nboutput};
    NeuralNetwork neuralnetwork = init_neuralNetwork(784, layer, 2);

    size_t maxgen = (size_t)atoi(argv[1]);
    for(size_t nnn = 0; nnn < maxgen; nnn++)
    {
        printf("\nGeneration %li :\n", nnn);

        // Allocation dynamique pour le tableau de pointeurs
        double **training = (double **)malloc(numTraining * sizeof(double *));
        double *expectedTrain = malloc(numTraining * sizeof(double));
        double **testing = (double **)malloc(numTesting * sizeof(double *));
        double *expectedTest = malloc(numTesting * sizeof(double));

        printf("Testing...\n");

        data(numTraining, numTesting, training, expectedTrain, testing, expectedTest);

        for(size_t i = 0; i < numTraining; i++)
        {
            double expec[nboutput];
            for(size_t k = 0; k < nboutput; k++) expec[k] = 0.0;
            expec[(int)(expectedTrain[i])] = 1.0;

            feedForward(neuralnetwork, training[i], 784);
            backPropagation(neuralnetwork, expec);
            updateWeigth(neuralnetwork, training[i], 784, 1);
        }



        size_t right = 0;
        for(size_t i = 0; i < numTesting; i++)
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
    }

    clock_t end = clock();
	double timer = (double)(end - start) / CLOCKS_PER_SEC;

    save_weights(neuralnetwork, "save.txt");
    
    printf("\nTraining competed in %fs\n", timer);

    return EXIT_SUCCESS;
}

