#include <stdio.h>
#include <stdlib.h>
#include "init_NN.h"
#include <math.h>




//generate a double following a Gaussian distribution, with mean 0 and variance 1
double generateGaussian() 
{
    	double u1 = (double)rand() / RAND_MAX; // Generate a random number between 0 and 1
    	double u2 = (double)rand() / RAND_MAX; // Generate another random number between 0 and 1

    	double z = sqrt(-2 * log(u1)) * cos(2 * M_PI * u2);

    	return z;
}


Neuron init_neuron(size_t nbr_weight)
{
    	double *begin_weight = malloc(nbr_weight * sizeof(double));
    	double *end_weight = begin_weight + nbr_weight;
	for(double *i = begin_weight; i < end_weight; i++)
    	{
       		*i = generateGaussian();
    	}
    	double biais = generateGaussian();
    	struct Neuron neuron = {nbr_weight, begin_weight, end_weight, biais, 
		0.0, 0.0};
    	int j = 0;
    	for(double *i = begin_weight; i < end_weight; i++)
    	{
        	j++;
    	}
    	return neuron;
}

void free_neuron(Neuron neuron)
{
    	free(neuron.weight);
}


Layer init_layer(int nbr_weight, int nbr_neurons)
{
    	Neuron *begin_layer = malloc(nbr_neurons * sizeof(Neuron));
    	Neuron *end_layer = begin_layer + nbr_neurons;
    	for(Neuron *i = begin_layer; i < end_layer; i++)
    	{
        	Neuron neuron = init_neuron(nbr_weight);
        	*i = neuron;
    	}
    	Layer layer = {nbr_neurons, begin_layer, end_layer};
    	return layer;
}


void free_layer(Layer layer)
{
    	for(Neuron *i = layer.neuron; i < layer.end; i++)
    	{
        	free_neuron(*i);
    	}
    	free(layer.neuron);
}


NeuralNetwork init_neuralNetwork(int nbr_inputs, int layers[], int len)
{

    	Layer *begin_neuralnetwork = malloc(len * sizeof(Layer));
    	Layer *end_neuralnetwork = begin_neuralnetwork + len;
    	int j = 0;
    	for(Layer *i = begin_neuralnetwork; i < end_neuralnetwork ; i++)
    	{
        	if (j == 0)
        	{
            		Layer layer = init_layer(nbr_inputs, layers[0]);
            		*i = layer;
        	}
        	else
        	{
            		Layer layer = init_layer((i-1)->nbr_neurons, layers[j]);
            		*i = layer;
        	}
        	j += 1;
    	}
    	NeuralNetwork neuralnetwork = {j, nbr_inputs, begin_neuralnetwork, 
		end_neuralnetwork};
    	return neuralnetwork;
}


void free_neuralNetwork(NeuralNetwork neuralnetwork)
{
    	for(Layer *i = neuralnetwork.layer; i < neuralnetwork.end; i++)
    	{
        	free_layer(*i);
    	}
    	free(neuralnetwork.layer);
}
