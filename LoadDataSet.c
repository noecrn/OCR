#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "LoadDataSet.h"

#define IMAGE_MAGIC 2051
#define LABEL_MAGIC 2049
#define NUM_IMAGES 60000
#define IMAGE_SIZE 784 // 28x28 pixels

uint8_t images[NUM_IMAGES][IMAGE_SIZE];
uint8_t labels[NUM_IMAGES];

void load_mnist() {
    FILE *fimg = fopen("/Users/noecrn/Documents/OCR/TrainningSets/train-images.idx3-ubyte", "rb");
    FILE *flabel = fopen("/Users/noecrn/Documents/OCR/TrainningSets/train-labels.idx1-ubyte", "rb");

    if (!fimg || !flabel) {
        printf("Failed to open MNIST files\n");
        exit(1);
    }

    uint32_t magic, num_items;

    // Read image file header
    fread(&magic, 4, 1, fimg);
    fread(&num_items, 4, 1, fimg);

    magic = ntohl(magic);
    num_items = ntohl(num_items);

    if (magic != IMAGE_MAGIC || num_items != NUM_IMAGES) {
        printf("Invalid image file header\n");
        exit(1);
    }

    // Read label file header
    fread(&magic, 4, 1, flabel);
    fread(&num_items, 4, 1, flabel);

    magic = ntohl(magic);
    num_items = ntohl(num_items);

    if (magic != LABEL_MAGIC || num_items != NUM_IMAGES) {
        printf("Invalid label file header\n");
        exit(1);
    }

    // Read images and labels
    for (int i = 0; i < NUM_IMAGES; i++) {
        fread(images[i], IMAGE_SIZE, 1, fimg);
        fread(&labels[i], 1, 1, flabel);
    }

    fclose(fimg);
    fclose(flabel);
}