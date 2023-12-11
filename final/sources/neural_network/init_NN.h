#ifndef INIT_NN_H_
#define INIT_NN_H_
#include <math.h>
#include <stddef.h>

//The typedef keyword is used to create an alias for the struct, enabling the use of it as a type name without the need to explicitly mention struct each time.
typedef struct Neuron
{
	int nbr_weight;
    double *weight;
  	double *end;
	double bias;
   	double error;
   	double output;
}Neuron;

typedef struct Layer
{
	int nbr_neurons;
   	Neuron *neuron;
   	Neuron *end;
}Layer;

typedef struct NeuralNetwork 
{
   	int nbr_layers;
   	int nbr_inputs; 
   	Layer *layer;
   	Layer *end;
}NeuralNetwork;

double generateGaussian();
Neuron init_neuron(size_t nbr_weight);
void free_neuron(Neuron neuron);
Layer init_layer(int nbr_weight, int nbr_neurons);
void free_layer(Layer layer);
NeuralNetwork init_neuralNetwork(int nbr_inputs, int layers[], int len);
void free_neuralNetwork(NeuralNetwork neuralnetwork);

#endif
