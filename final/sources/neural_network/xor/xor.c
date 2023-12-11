#include <stdio.h>
#include <stdlib.h>
#include "xor.h"
#include <math.h>


void XORtraining(int times, NeuralNetwork neuralnetwork)
{
    	double inputs[4][2] = {{1.0, 0.0}, {0.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}};
    	double expected[4][1] = {{1.0}, {0.0}, {0.0}, {1.0}};
    	for(int i = 0; i < times; i++)
    	{

        	for(int j = 0; j < 4; j++)
        	{
            	feedForward(neuralnetwork, inputs[j], 2);
            	backPropagation(neuralnetwork, expected[j]);
            	updateWeigth(neuralnetwork, inputs[j], 2, 0.1);
        	}
    	}
}


void XOR(NeuralNetwork neuralnetwork, double x, double y)
{
    	double values[2] = {x, y};
    	feedForward(neuralnetwork, values, 2);
        Layer *layer = neuralnetwork.end -1;
    	for(Neuron *i = layer->neuron; i < layer->end; i++)//for each neuron in the last layer
    	{
        	printf("%f\n", i->output);
        	printf("----------------\n");
    	}
}
