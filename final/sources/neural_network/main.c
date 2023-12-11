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
        fprintf(stderr, 
        "Format: %s <Generation number> <Save path>\n", argv[0]);
        return 1;
    }

    int numTraining = 28000;//atoi(argv[1]);
    int numTesting = 1000;//atoi(argv[2]);

/*if(numTraining+numTesting > 29000)
    {
        fprintf(stderr, "database <= 29000\n");
        return 1;
    }*/
    printf("Training a digit-recognization neural network...\n");
    clock_t start = clock();

    int nboutput = 10;
    int layer[3] = {12, 25, nboutput};
    NeuralNetwork neuralnetwork = init_neuralNetwork(784, layer, 3);

    size_t maxgen = (size_t)atoi(argv[1]);
    for(size_t nnn = 0; nnn < maxgen; nnn++)
    {
        printf("\nGeneration %li :\n", nnn);

        // Allocation dynamique pour le tableau de pointeurs
        double **training = (double **)malloc(numTraining * 
        sizeof(double *));
        double *expectedTrain = malloc(numTraining * 
        sizeof(double));
        double **testing = (double **)malloc(numTesting * 
        sizeof(double *));
        double *expectedTest = malloc(numTesting * 
        sizeof(double));

        printf("Testing...\n");

        data(numTraining, numTesting, training, 
        expectedTrain, testing, expectedTest);

        for(size_t i = 0; i < (size_t)numTraining; i++)
        {
            double expec[nboutput];
            for(size_t k = 0; k < (size_t)nboutput; k++) expec[k] = 0.0;
            expec[(int)(expectedTrain[i])] = 1.0;

            feedForward(neuralnetwork, training[i], 784);
            backPropagation(neuralnetwork, expec);
            updateWeigth(neuralnetwork, training[i], 784, 0.15);
        }


        //Neuron maximum;
        size_t right = 0;
        for(size_t i = 0; i < (size_t)numTesting; i++)
        {
            feedForward(neuralnetwork, testing[i], 784);
            Layer *layer = neuralnetwork.end -1;
            size_t maxindex = 0;
            Neuron *maximum = layer->neuron;
            size_t counter = 0;
            for(Neuron *i = layer->neuron; i < layer->end; i++)//for each neuron in the last layer
            {
        //      printf("%f\n", i->output);
                if(i->output > maximum->output)
                {
                    maximum = i;
                    maxindex = counter;
                }
                counter++;
            }
        //  printf("res : %f\n", (double)maxindex);
        //  printf("expected : %f\n", expectedTest[i]);
            right += (expectedTest[i] == (double)maxindex);
        }
        //free_neuron(maximum);
        printf("Results of the testing : %li / %d found. (%f%%)\n", 
        right, numTesting, (double)right * 100 / 1000);

        freeData(numTraining, numTesting, training, expectedTrain, 
        testing, expectedTest);
    }

    clock_t end = clock();
    double timer = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\nTraining competed in %fs\n", timer);

    save(neuralnetwork, argv[2]);

    free_neuralNetwork(neuralnetwork);

    NeuralNetwork network = load("saved_network/theone.txt");

    numTesting = 29000;
    numTraining = 0;

    double **trainin = (double **)malloc(numTraining * sizeof(double *));
    double *expectedTrai = malloc(numTraining * sizeof(double));
    double **testin = (double **)malloc(numTesting * sizeof(double *));
    double *expectedTes = malloc(numTesting * sizeof(double));

    data(numTraining, numTesting, trainin, expectedTrai, testin, expectedTes);

    size_t right = 0;
    for(size_t i = 0; i < (size_t)numTesting; i++)
    {
        feedForward(network, testin[i], 784);
        Layer *layer = network.end -1;
        size_t maxindex = 0;
        Neuron *maximum = layer->neuron;
        size_t counter = 0;
        for(Neuron *i = layer->neuron; i < layer->end; i++)//for each neuron in the last layer
        {
    //      printf("%f\n", i->output);
            if(i->output > maximum->output)
            {
                maximum = i;
                maxindex = counter;
            }
            counter++;
        }
    //  printf("res : %f\n", (double)maxindex);
    //  printf("expected : %f\n", expectedTest[i]);
        right += (expectedTes[i] == (double)maxindex);
    }

    printf("\nLoaded results : %li / %d found.\n", right, numTesting);
    printf("(%f%%)\n",100*(double)right/29000);

    freeData(numTraining, numTesting, trainin, expectedTrai, testin, 
    expectedTes);

    free_neuralNetwork(network);

    return EXIT_SUCCESS;
}


