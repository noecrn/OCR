#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INPUT_SIZE 784
#define HIDDEN_SIZE 30
#define OUTPUT_SIZE 10
#define NUM_IMAGES 4
#define EPOCHS 30
#define LEARNING_RATE 3.0f

double hiddenLayer[HIDDEN_SIZE];
double outputLayer[OUTPUT_SIZE];
    
double hiddenLayerBias[HIDDEN_SIZE];
double outputLayerBias[OUTPUT_SIZE];

double hiddenWeights[INPUT_SIZE][HIDDEN_SIZE];
double outputWeights[HIDDEN_SIZE][OUTPUT_SIZE];

double training_inputs[NUM_IMAGES][INPUT_SIZE];
double training_outputs[NUM_IMAGES][OUTPUT_SIZE];

void forward_propagation(double training_inputs[], double hiddenLayer[], double outputLayer[]);
void back_propagation(double training_inputs[], double hiddenLayer[], double outputLayer[], double training_outputs[]);
double sigmoid(double x);
double dSigmoid(double x);
double init_weight();

int main () {
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
    
    for(int epochs = 0; epochs < EPOCHS; epochs++) {
        //shuffle(trainingSetOrder,NUM_IMAGES);

        for (int x = 0; x < NUM_IMAGES; x++) {
            
            forward_propagation(training_inputs[x], hiddenLayer, outputLayer);
            
            // Print the results from forward propagation
            printf ("Output:%g    Expected Output: %g\n",
                    outputLayer[0], training_outputs[x][0]);

            back_propagation(training_inputs[x], hiddenLayer, outputLayer, training_outputs[x]);
        }
    }

    return 0;
}

void forward_propagation(double training_inputs[], double hiddenLayer[], double outputLayer[]){
    // Forward propagation input -> hidden
    for (int i = 0; i < HIDDEN_SIZE; i++) {
        double activation = hiddenLayerBias[i];
         for (int j = 0; j < INPUT_SIZE; j++) {
            activation += training_inputs[j] * hiddenWeights[j][i];
        }
        hiddenLayer[i] = sigmoid(activation + hiddenLayerBias[i]);
    }
            
    // Forward propagation hidden -> output
    for (int i = 0; i < OUTPUT_SIZE; i++) {
        double activation = outputLayerBias[i];
        for (int j = 0; j < HIDDEN_SIZE; j++) {
            activation += hiddenLayer[j] * outputWeights[j][i];
        }
        outputLayer[i] = sigmoid(activation + outputLayerBias[i]);
    }
}

void back_propagation(double training_inputs[], double hiddenLayer[], double outputLayer[], double training_outputs[]){
    // Backpropagation output -> hidden
    double deltaOutput[OUTPUT_SIZE];
    for (int i = 0; i < OUTPUT_SIZE; i++) {
        double errorOutput = (training_outputs[i] - outputLayer[i]);
        deltaOutput[i] = errorOutput * dSigmoid(outputLayer[i]);
    }

    double deltaHidden[HIDDEN_SIZE];
    for (int i = 0; i < HIDDEN_SIZE; i++) {
        double errorHidden = 0.0f;
        for(int j = 0; j < OUTPUT_SIZE; j++) {
            errorHidden += deltaOutput[j] * outputWeights[i][j];
        }
        deltaHidden[i] = errorHidden * dSigmoid(hiddenLayer[i]);
    }
            
    // Backpropagation hidden -> input
    for (int i = 0; i < OUTPUT_SIZE; i++) {
        outputLayerBias[i] += deltaOutput[i] * LEARNING_RATE;
        for (int j = 0; j < HIDDEN_SIZE; j++) {
            outputWeights[j][i] += hiddenLayer[j] * deltaOutput[i] * LEARNING_RATE;
        }
    }

    for (int i = 0; i < HIDDEN_SIZE; i++) {
        hiddenLayerBias[i] += deltaHidden[i] * LEARNING_RATE;
        for(int j = 0; j < INPUT_SIZE; j++) {
            hiddenWeights[j][i] += training_inputs[j] * deltaHidden[i] * LEARNING_RATE;
        }
    }
}

// void shuffle(int *array, size_t n)
// {
//     if (n > 1)
//     {
//         size_t i;
//         for (i = 0; i < n - 1; i++)
//         {
//             size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
//             int t = array[j];
//             array[j] = array[i];
//             array[i] = t;
//         }
//     }
// }

double sigmoid(double x) {
    return 1 / (1 + exp(-x)); 
}
double dSigmoid(double x) {
    return x * (1 - x);
}
double init_weight() {
    return ((double)rand())/((double)RAND_MAX);
}