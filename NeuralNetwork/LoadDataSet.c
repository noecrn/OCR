#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "LoadDataSet.h"

#define IMAGE_MAGIC 2051
#define LABEL_MAGIC 2049

void load_mnist(uint8_t images[NUM_IMAGES][IMAGE_SIZE], uint8_t labels[NUM_IMAGES]) {
    FILE *fimg = fopen("/Users/noecrn/Documents/OCR/TrainningSets/train-images.idx3-ubyte", "rb");
    FILE *flabel = fopen("/Users/noecrn/Documents/OCR/TrainningSets/train-labels.idx1-ubyte", "rb");

    if (!fimg || !flabel) {
        printf("Failed to open MNIST files\n");
        exit(1);
    }

    uint32_t magic, num_items;

    // Read image file header
    if (fread(&magic, 4, 1, fimg) != 1 || fread(&num_items, 4, 1, fimg) != 1) {
        printf("Failed to read image file header\n");
        exit(1);
    }

    magic = ntohl(magic);
    num_items = ntohl(num_items);

    if (magic != IMAGE_MAGIC || num_items != NUM_IMAGES) {
        printf("Invalid image file header\n");
        exit(1);
    }

    // Read label file header
    if (fread(&magic, 4, 1, flabel) != 1 || fread(&num_items, 4, 1, flabel) != 1) {
        printf("Failed to read label file header\n");
        exit(1);
    }

    magic = ntohl(magic);
    num_items = ntohl(num_items);

    if (magic != LABEL_MAGIC || num_items != NUM_IMAGES) {
        printf("Invalid label file header\n");
        exit(1);
    }

    // Read images and labels
    for (int i = 0; i < NUM_IMAGES; i++) {
        for (int j = 0; j < IMAGE_SIZE; j++) {
            uint8_t pixel;
            if (fread(&pixel, 1, 1, fimg) != 1) {
                printf("Failed to read pixel data\n");
                exit(1);
            }
            images[i][j] = pixel;
        }
        if (fread(&labels[i], 1, 1, flabel) != 1) {
            printf("Failed to read label data\n");
            exit(1);
        }
    }

    fclose(fimg);
    fclose(flabel);
}