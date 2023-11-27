#ifndef DATA_SET_READER_H_
#define DATA_SET_READER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdint.h>

#define PIXEL_COUNT 784
#define HEIGHT 28
#define WIDTH 28
#define FILENAME "image"
#define DATASET "../../data_set.csv"

struct Image {
    char *font;
    int label;
    int *pixels;
};


struct Image *initImage(char *line);
void freeImage(struct Image *img);
void createJPEG(const char *filename, int *pixels);
void data(int numTraining, int numTesting, double **training, double *expectedTrain, double **testing, double *expectedTest);
void freeData(int numTraining, int numTesting, double **training, double *expectedTrain, double **testing, double *expectedTest);


#endif

