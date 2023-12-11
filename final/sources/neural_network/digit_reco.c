
#include "digit_reco.h"
#include <math.h>
#include "init_NN.h"
#include "NN_fun.h"
#include <stdio.h>
#include <stdlib.h>
#include "data_set_reader.h"
#include <math.h>
#include <time.h>

void save(struct NeuralNetwork network, char *filename)
{
	FILE *fp;

	fp = fopen(filename, "w");
	//stores the number of inputs"
	fprintf(fp, "%d\n", network.nbr_inputs);

	//stores the number of layers
	fprintf(fp, "%d\n", network.nbr_layers);


	for (Layer *i = network.layer; i < network.layer + network.nbr_layers; i++)
	{
		//stores the number of neuronnes for each layers
		fprintf(fp, "%d\n", i->nbr_neurons);
	}
	

	for(int i = 0; i < network.nbr_layers; i++)
	{
		Layer *layer = network.layer + i;


		for(int j = 0; j < layer->nbr_neurons; j++)
		{
			Neuron *neuron = (layer->neuron) + j;

			// ecrit le biais
			fprintf(fp, "%f\n", neuron->bias);
			for(int k = 0; k < neuron->nbr_weight; k++)
			{
				//ecris le poids
				double *weight = (neuron->weight) + k;
				fprintf(fp, "%f\n", *weight);
			}
		}
	}

	fclose(fp);
}

/*!
 * Load a neural network from a file 
 * @param filename the path of the file where the neural network is save 
 */
struct NeuralNetwork load(char *filename)
{
	FILE *fp;
	char * line = NULL;
	size_t len = 0;
	size_t read;

	fp = fopen(filename, "r");

	if (fp == NULL)
		exit(EXIT_FAILURE);
	int nbr_inputs;
	int nbr_layer = 1;
	//double biais_du_neurone;

	read = getline(&line, &len, fp);
	line = strtok(line, "\n");
	read -= 1;
	nbr_inputs = strtol(line, NULL, 10);

	read = getline(&line, &len, fp);
	line = strtok(line, "\n");
	read -= 1;
	nbr_layer = strtol(line, NULL, 10);

	int layers[nbr_layer];
	for (int i = 0; i < nbr_layer; i++)
	{
		read = getline(&line, &len, fp);
		line = strtok(line, "\n");
		read -= 1;
		layers[i] = strtol(line, NULL, 10);
	}
	Layer *layer = malloc(nbr_layer * sizeof(Layer));
	Layer *l = layer; 
	for(int i = 0; i < nbr_layer; i++)
	{
		int length;
		if(i == 0)
		{
			length = nbr_inputs;
		}
		else
		{
			length = layers[i-1];
		}
		Neuron *neuron = malloc(layers[i] * sizeof(Neuron));
		Neuron *n = neuron;

		for (int j = 0; j < layers[i]; j++)
		{
			read = getline(&line, &len, fp);
			line = strtok(line, "\n");
			read -= 1;
			char *biais = strtok(line, "\n");
			double biais_d = atof(biais);
			double *weigth = malloc(length * sizeof(double));
			double *w = weigth;
			for (int k = 0; k < length; k++)
			{
				read = getline(&line, &len, fp);
				line = strtok(line, "\n");
				read -= 1;
				char *weight_i = strtok(line, "\n");
				*w = atof(weight_i);
				w += 1;
			}
			Neuron neuronne = {length, weigth, w, biais_d, 0, 0}; 
			*n = neuronne;
			n ++;
		}
		Layer l_i = {layers[i], neuron, n};
		*l = l_i;
		l++;
	}
	NeuralNetwork neuralnetwork = {nbr_layer, nbr_inputs, layer, l};
	fclose(fp);
	return neuralnetwork;
}

/*
int main(int argc, char* argv[])
{

    if (argc != 3) {
        fprintf(stderr, "Format: %s <Generation number> <Save path>\n", argv[0]);
        return 1;
    }

    int numTraining = 28000;//atoi(argv[1]);
    int numTesting = 1000;//atoi(argv[2]);

if(numTraining+numTesting > 29000)
    {
	    fprintf(stderr, "database <= 29000\n");
	    return 1;
    }
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
        double **training = (double **)malloc(numTraining * sizeof(double *));
        double *expectedTrain = malloc(numTraining * sizeof(double));
        double **testing = (double **)malloc(numTesting * sizeof(double *));
        double *expectedTest = malloc(numTesting * sizeof(double));

        printf("Testing...\n");

        data(numTraining, numTesting, training, expectedTrain, testing, expectedTest);

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
        //	    printf("%f\n", i->output);
                if(i->output > maximum->output)
                {
                    maximum = i;
                    maxindex = counter;
                }
                counter++;
        	}
        //	printf("res : %f\n", (double)maxindex);
        //	printf("expected : %f\n", expectedTest[i]);
            right += (expectedTest[i] == (double)maxindex);
        }
		//free_neuron(maximum);
        printf("Results of the testing : %li / %d found. (%f%%)\n", right, numTesting, (double)right * 100 / 1000);

        freeData(numTraining, numTesting, training, expectedTrain, testing, expectedTest);
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
    //	    printf("%f\n", i->output);
            if(i->output > maximum->output)
            {
                maximum = i;
                maxindex = counter;
            }
            counter++;
        }
    //	printf("res : %f\n", (double)maxindex);
    //	printf("expected : %f\n", expectedTest[i]);
        right += (expectedTes[i] == (double)maxindex);
    }

    printf("\nLoaded results : %li / %d found.\n", right, numTesting);
    printf("(%f%%)\n",100*(double)right/29000);

    freeData(numTraining, numTesting, trainin, expectedTrai, testin, expectedTes);

    free_neuralNetwork(network);

    return EXIT_SUCCESS;
}
*/
