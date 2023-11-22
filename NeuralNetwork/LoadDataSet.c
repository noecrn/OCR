#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    unsigned char* pixels;
    int width;
    int height;
    char* label;
} ImageData;

ImageData loadImage(const char* filename) {
    ImageData imageData;
    imageData.pixels = NULL;
    imageData.width = 0;
    imageData.height = 0;
    imageData.label = NULL;

    SDL_Surface* surface = NULL;
    surface = IMG_Load(filename);

    if (surface == NULL) {
        printf("Failed to load image: %s\n", SDL_GetError());
        return imageData;
    }

    imageData.width = surface->w;
    imageData.height = surface->h;

    imageData.pixels = (unsigned char*)malloc(imageData.width * imageData.height * sizeof(unsigned char));
    if (imageData.pixels == NULL) {
        printf("Failed to allocate memory for pixels\n");
        SDL_FreeSurface(surface);
        return imageData;
    }

    for (int y = 0; y < imageData.height; y++) {
        for (int x = 0; x < imageData.width; x++) {
            Uint32 pixel = ((Uint32*)surface->pixels)[y * imageData.width + x];
            Uint8 r, g, b;
            SDL_GetRGB(pixel, surface->format, &r, &g, &b);
            unsigned char grayscale = (unsigned char)(0.2989 * r + 0.5870 * g + 0.1140 * b);
            imageData.pixels[y * imageData.width + x] = grayscale;
        }
    }

    SDL_FreeSurface(surface);

    // Extract the label from the filename
    char* labelStart = strrchr(filename, '/');
    if (labelStart == NULL) {
        labelStart = strrchr(filename, '\\');
    }
    if (labelStart != NULL) {
        labelStart++; // Move past the last slash or backslash
        char* labelEnd = strchr(labelStart, '.');
        if (labelEnd != NULL) {
            int labelLength = labelEnd - labelStart;
            imageData.label = (char*)malloc((labelLength + 1) * sizeof(char));
            strncpy(imageData.label, labelStart, labelLength);
            imageData.label[labelLength] = '\0';
        }
    }

    return imageData;
}

int main() {
    ImageData* imageData = loadImage("TrainningSets/1.jpg");
    if (imageData != NULL) {
        printf("Label: %d\n", imageData->label);
        printf("Width: %d\n", imageData->width);
        printf("Height: %d\n", imageData->height);
        printf("Pixels: %p\n", imageData->pixels);
        free(imageData->pixels);
        free(imageData);
    }
    return 0;
}