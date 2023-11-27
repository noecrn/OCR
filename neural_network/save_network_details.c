#include <stdio.h>
#include <stdlib.h>
#include "data_set_reader.h"
#include "NN_fun.h"
#include "init_NN.h"

#include "init_NN.h"

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