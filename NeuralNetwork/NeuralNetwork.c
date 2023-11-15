#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INPUT_SIZE 784
#define HIDDEN_SIZE 20
#define OUTPUT_SIZE 10
#define NUM_IMAGES 60000
#define EPOCHS 3
#define LEARNING_RATE 0.01

typedef uint8_t Image[INPUT_SIZE]; // Each image is a 1D array of 784 pixels
typedef uint8_t Label; // Each label is a single integer

double hiddenWeights[HIDDEN_SIZE][INPUT_SIZE];
double outputWeights[OUTPUT_SIZE][HIDDEN_SIZE];
double hiddenLayerBias[HIDDEN_SIZE];
double outputLayerBias[OUTPUT_SIZE];

void load_mnist(Image *images, Label *labels);
void forward_propagation(double img[], double h[], double o[]);
void backpropagation(double img[], double h[], double o[], double l[]);
double sigmoid(double x);
double dSigmoid(double x);
double init_weight();
int argmax(double arr[], int n);

int main() {
    Image images[NUM_IMAGES];
    Label labels[NUM_IMAGES];
    load_mnist(images, labels);

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

    for (int epoch = 0; epoch < EPOCHS; epoch++) {
        int nr_correct = 0;
        for (int i = 0; i < NUM_IMAGES; i++) {
            double h[HIDDEN_SIZE], o[OUTPUT_SIZE];

            // Convert Image and Label to double[]
            double img[INPUT_SIZE];
            for (int j = 0; j < INPUT_SIZE; j++) {
                img[j] = images[i][j] / 255.0; // normalize pixel values to [0, 1]
            }

            double l[OUTPUT_SIZE] = {0};
            l[labels[i]] = 1; // one-hot encode the label

            forward_propagation(img, h, o);
            backpropagation(img, h, o, l);

            nr_correct += (argmax(o, OUTPUT_SIZE) == argmax(l, OUTPUT_SIZE));
        }
        printf("Acc: %.2f%%\n", (double)nr_correct / NUM_IMAGES * 100);
    }

    return 0;
}

void forward_propagation(double img[], double h[], double o[]) {
    // Forward propagation input -> hidden
    for (int i = 0; i < HIDDEN_SIZE; i++) {
        double sum = 0;
        for (int j = 0; j < INPUT_SIZE; j++) {
            sum += hiddenWeights[i][j] * img[j];
        }
        h[i] = sigmoid(sum + hiddenLayerBias[i]);
    }

    // Forward propagation hidden -> output
    for (int i = 0; i < OUTPUT_SIZE; i++) {
        double sum = 0;
        for (int j = 0; j < HIDDEN_SIZE; j++) {
            sum += outputWeights[i][j] * h[j];
        }
        o[i] = sigmoid(sum + outputLayerBias[i]);
    }
}

void backpropagation(double img[], double h[], double o[], double l[]) {
    // Backpropagation output -> hidden
    double delta_o[OUTPUT_SIZE];
    for (int i = 0; i < OUTPUT_SIZE; i++) {
        delta_o[i] = o[i] - l[i]; // error = output - target
    }

    for (int i = 0; i < OUTPUT_SIZE; i++) {
        for (int j = 0; j < HIDDEN_SIZE; j++) {
            outputWeights[i][j] -= LEARNING_RATE * delta_o[i] * h[j]; // update weight
        }
        outputLayerBias[i] -= LEARNING_RATE * delta_o[i]; // update bias
    }

    // Backpropagation hidden -> input
    double delta_h[HIDDEN_SIZE];
    for (int i = 0; i < HIDDEN_SIZE; i++) {
        delta_h[i] = 0.0;
        for (int j = 0; j < OUTPUT_SIZE; j++) {
            delta_h[i] += delta_o[j] * outputWeights[j][i];
        }
        delta_h[i] *= dSigmoid(h[i]); // scale by derivative of activation function
    }

    for (int i = 0; i < HIDDEN_SIZE; i++) {
        for (int j = 0; j < INPUT_SIZE; j++) {
            hiddenWeights[i][j] -= LEARNING_RATE * delta_h[i] * img[j]; // update weight
        }
        hiddenLayerBias[i] -= LEARNING_RATE * delta_h[i]; // update bias
    }
}

double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

double dSigmoid(double x) {
    double y = sigmoid(x);
    return y * (1 - y);
}

double init_weight() {
    return ((double)rand() / RAND_MAX) * 2 - 1; // random value between -1 and 1
}

int argmax(double arr[], int n) {
    int max_idx = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] > arr[max_idx]) {
            max_idx = i;
        }
    }
    return max_idx;
}