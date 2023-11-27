#ifndef NN_FUN_H_
#define NN_FUN_H_
#include <math.h>
#include "init_NN.h"

double sigmoid(double x);
double sigmoidPrime(double x);
void feedForward(NeuralNetwork neuralnetwork, double *inputs, int len);
double* print_output(NeuralNetwork neuralnetwork);
void backPropagation(NeuralNetwork neuralnetwork, double expected[]);
void updateWeigth(NeuralNetwork neuralnetwork, double *inputs, int len, double coef);

#endif
