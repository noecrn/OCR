#include <stdio.h>
#include <stdlib.h>
#include "init_NN.h"
#include "NN_fun.h"
#include <math.h>


double sigmoid(double x)
{
    	return 1/(1 + exp(-x));
}


double sigmoidPrime(double x)
{
	return x * (1-x);
}


void feedForward(NeuralNetwork neuralnetwork, double *inputs, int len)
{
    for(int i = 0; i < neuralnetwork.nbr_layers; i++) //for each layers
    {
        Layer *layer = neuralnetwork.layer +i;
        for(int j = 0; j < layer->nbr_neurons; j++) //for each neurones for each layers
        {
            Neuron *neuron = (layer->neuron)+j;
            double sum = 0.0;
            int length;
            if (i == 0) //if it's the first layer
            {
                length = len; //the number of before output values is the length of the inputs
            }
            else
            {
                length = (layer-1)->nbr_neurons;  //the number of before output values is the number
                                                    //of neuronne in the layer before
            }
            for(int k = 0; k < length; k++) //for the number of output value before
            {
                double *weight = neuron->weight;

                if(i == 0) //if it's the first layer the before output value is the input given in param
                {
                    sum += *(inputs + k) * (*(weight + k)); //mltiply each input values by the weigth associated
                }
                else
                {
                    Neuron *neuron_prev = (layer-1)->neuron;
                    sum += (neuron_prev + k)->output * (*(weight + k));
                    //multiply each output of neurones from the layer before by the weigth associated
                }

            }
            neuron->output = sigmoid(sum + neuron->bias);
            //set the output value of the neurone by the add of the summ and the biais of the neurone
            //we add to activat it by using the sigmoid function
        }
    }
}



double* print_output(NeuralNetwork neuralnetwork)
{
    	double* output = malloc((neuralnetwork.end -1)->nbr_neurons * 
        sizeof(double));//lock memory for the pointer of output
    //(neuralnetwork.end -1)->nbr_neuronnes numbe of neurone in the last layer
    	double* j = output;
    	Layer *layer = neuralnetwork.end -1;
    	for(Neuron *i = layer->neuron; i < layer->end; i++)//for each neurone in the last layer
    	{
        /*
        printf("%f\n", i->output); //line to uncomment to print the ouput of each neuronne
        printf("_____________\n");
        */
        	*j = i->output;
        	j++;
    	}
    	return output;
}



void backPropagation(NeuralNetwork neuralnetwork, double expected[])
{
    for(int i = neuralnetwork.nbr_layers-1; i >= 0; i--)//for each layer in the neuralnetwork
    {
        Layer *layer = neuralnetwork.layer + i;
        if(i == neuralnetwork.nbr_layers-1) //if it's the last layer (the output layer)
        {
            for(int j = 0; j < layer->nbr_neurons; j++)//for each neuronne of the output layer
            {
                Neuron *neuron = layer->neuron + j;
                neuron->error = (expected[j] - neuron->output) * 
                sigmoidPrime(neuron->output);
                //calculate the error coeff of each neuronne of the output layer
                //compare the value waited and the value we had
            }
        }
        else
        {
            Layer *next_layer = neuralnetwork.layer + i + 1; //the layer after the layer where we are
            for(int j = 0; j < layer->nbr_neurons; j++) //for each neurone in the layer where we are
            {
                double error = 0; //calculate the error
                for(int k = 0; k < next_layer->nbr_neurons; k++) //for each neuonne in the layer after
                {
                    Neuron *neuron = next_layer->neuron+k;
                    error += *(neuron->weight + j) * neuron->error;
                }
                Neuron *neuron = layer->neuron + j;
                neuron->error = error * sigmoidPrime(neuron->output);
            }
        }
    }
}


void updateWeigth(NeuralNetwork neuralnetwork, double *inputs, 
int len, double coef)
{
    for(int i = 0; i < neuralnetwork.nbr_layers; i++)
    {
        Layer *layer = neuralnetwork.layer + i;
        for(int k = 0; k < layer->nbr_neurons; k++)
        {
            Neuron *neuron = layer->neuron + k;
            double* weight = neuron->weight;
            if(i == 0)
            {
                for(int j = 0; j < len; j++)
                {
                    *(weight + j) += coef * neuron->error * *(inputs + j);
                }
            }
            else
            {
                Layer *before_layer = neuralnetwork.layer + i - 1;
                for(int j = 0; j < before_layer->nbr_neurons; j++)
                {
                    Neuron *before_neuron = before_layer->neuron + j;
                    *(weight + j) += coef * neuron->error * 
                    before_neuron->output;
                }
            }
            neuron->bias += coef * neuron->error;
        }
    }
}
