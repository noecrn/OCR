#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "LoadDataSet.h"

#define INPUT_SIZE 784
#define HIDDEN_SIZE 20
#define OUTPUT_SIZE 10
#define LEARNING_RATE 0.01
#define EPOCHS 3

double sigmoid(double x) {
    return 1 / (1 + exp(-x));
}
double dSigmoid(double x) {
    return x * (1 - x);
}
double init_weight() {
    return ((double)rand())/((double)RAND_MAX);
}

int main() {
    double hiddenWeights[HIDDEN_SIZE][INPUT_SIZE];
    double outputWeights[OUTPUT_SIZE][HIDDEN_SIZE];
    double hiddenLayerBias[HIDDEN_SIZE];
    double outputLayerBias[OUTPUT_SIZE];

    // Initialize weights and biases
    for (int i = 0; i < HIDDEN_SIZE; i++) {
        hiddenLayerBias[i] = init_weight();
        for (int j = 0; j < INPUT_SIZE; j++) {
            hiddenWeights[i][j] = init_weight();
        }
    }

    for (int i = 0; i < OUTPUT_SIZE; i++) {
        outputLayerBias[i] = init_weight();
        for (int j = 0; j < HIDDEN_SIZE; j++) {
            outputWeights[i][j] = init_weight();
        }
    }

    // Training loop
    for (int epoch = 0; epoch < EPOCHS; epoch++) {

        // Print the current epoch
        printf("Epoch %d\n", epoch);

        load_mnist();
        
        double img[INPUT_SIZE];
        double label[OUTPUT_SIZE];

        // Forward propagation input -> hidden
        double h_pre[HIDDEN_SIZE];
        double h[HIDDEN_SIZE];
        for (int i = 0; i < HIDDEN_SIZE; i++) {
            h_pre[i] = hiddenLayerBias[i];
            for (int j = 0; j < INPUT_SIZE; j++) {
                h_pre[i] += hiddenWeights[i][j] * img[j];
            }
            h[i] = sigmoid(h_pre[i]);
        }

        // Forward propagation hidden -> output
        double o_pre[OUTPUT_SIZE];
        double o[OUTPUT_SIZE];
        for (int i = 0; i < OUTPUT_SIZE; i++) {
            o_pre[i] = outputLayerBias[i];
            for (int j = 0; j < HIDDEN_SIZE; j++) {
                o_pre[i] += outputWeights[i][j] * h[j];
            }
            o[i] = sigmoid(o_pre[i]);
            printf("Output %d: %g, Expected Output: %g\n", i, o[i], label[i]);
        }

        // Backpropagation
        double delta_o[OUTPUT_SIZE];
        for (int i = 0; i < OUTPUT_SIZE; i++) {
            delta_o[i] = o[i] - label[i]; // error = output - target
        }

        for (int i = 0; i < OUTPUT_SIZE; i++) {
            for (int j = 0; j < HIDDEN_SIZE; j++) {
                outputWeights[i][j] -= LEARNING_RATE * delta_o[i] * h[j]; // update weight
            }
            outputLayerBias[i] -= LEARNING_RATE * delta_o[i]; // update bias
        }

        double delta_h[HIDDEN_SIZE];
        for (int i = 0; i < HIDDEN_SIZE; i++) {
            delta_h[i] = 0.0;
            for (int j = 0; j < OUTPUT_SIZE; j++) {
                delta_h[i] += delta_o[j] * outputWeights[j][i];
            }
            delta_h[i] *= dSigmoid(h_pre[i]); // scale by derivative of activation function
        }

        for (int i = 0; i < HIDDEN_SIZE; i++) {
            for (int j = 0; j < INPUT_SIZE; j++) {
                hiddenWeights[i][j] -= LEARNING_RATE * delta_h[i] * img[j]; // update weight
            }
            hiddenLayerBias[i] -= LEARNING_RATE * delta_h[i]; // update bias
        }
    }

    return 0;
}