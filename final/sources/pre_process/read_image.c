#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include "grayscale.h"
#include "operation.h"
#include "../neural_network/digit_reco.h"

#define NB_IMAGES 81

static double *lireImageJPEG(const char *cheminImage)
{
    SDL_Surface *image = IMG_Load(cheminImage);
    if (image == NULL)
    {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s\n", 
        cheminImage);
        exit(EXIT_FAILURE);
    }

    double *pixels = (double *)malloc(image->w * image->h * sizeof(double));

    for (int i = 0; i < image->w; i++)
    {
        for (int j = 0; j < image->h; j++)
        {
            Uint32 pixel = getPixel(image, i, j);
            Uint8 r, g, b;
            SDL_GetRGB(pixel, image->format, &r, &g, &b);
            pixels[i * image->w + j] = (double)r/255.0;
        }
    }
    SDL_FreeSurface(image);
    return pixels;
}

int numberDetection(char *path, char *path2)
{
    double *pixels = lireImageJPEG(path2);
    /* for(int i = 0; i < 784; i++)
    {
        printf("%d ", (int)pixels[i]);
    }
    printf("\n"); */
    NeuralNetwork network = load(path);
    feedForward(network, pixels, 784);
    Layer *layer = network.end - 1;
    size_t maxindex = 0;
    Neuron maximum = init_neuron(1);
    size_t counter = 0;
    for (Neuron *i = layer->neuron; i < layer->end; i++)
    {
        printf("Neuron %li : %f\n", counter, i->output);
        if (i->output > maximum.output)
        {
            maximum = *i;
            maxindex = counter;
        }
        counter++;
    }
    printf("%li\n", maxindex);
    free(pixels);

    return maxindex;
}

int estVide2(SDL_Surface *image)
{
    // int nbPixels = image->w * image->h;
    int nbPixelsBlancs = 0;

    int centerX = image->w / 2;
    int centerY = image->h / 2;

    for (int i = centerX - 2; i <= centerX + 2; ++i)
    {
        for (int j = centerY - 2; j <= centerY + 2; ++j)
        {
            Uint8 r, g, b;
            Uint32 pixel = getPixel(image, i, j);
            SDL_GetRGB(pixel, image->format, &r, &g, &b);

            if (r == 255 && g == 255 && b == 255)
            {
                nbPixelsBlancs++;
            }
        }
    }

    /* printf("Nb pixels blancs : %d\n", nbPixelsBlancs);
    printf("resulat : %d\n", nbPixelsBlancs >= 3); */

    return nbPixelsBlancs >= 3;
}

int estVide(SDL_Surface *image)
{
    //int nbPixels = image->w * image->h;
    int nbPixelsBlancs = 0;

    for (int i = 5; i < image->w - 5; ++i)
    {
        for (int j = 2; j < image->h - 2; ++j)
        {
            Uint8 r, g, b;
            Uint32 pixel = getPixel(image, i, j);
            SDL_GetRGB(pixel, image->format, &r, &g, &b);

            // printf("Pixel %d %d : %d %d %d\n", i, j, r, g, b);

            if (r == 255 && g == 255 && b == 255)
            {
                nbPixelsBlancs++;
            }
        }
    }

/*     printf("Nb pixels blancs : %d\n", nbPixelsBlancs);
    printf("Nb pixels : %d\n", 20);
    printf("resulat : %d\n", nbPixelsBlancs >= 20); */

    return nbPixelsBlancs >= 20;
}

int main()
{
    FILE *fichier = fopen("output", "w");

    if (fichier == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier.");
        return 1;
    }

    int count = 0;

    for (int i = 1; i <= NB_IMAGES; ++i)
    {
        char imagePath[50];
        sprintf(imagePath, "../interface/cases/%02d.png", i);

        if (i != 1 && i % 9 == 1)
        {
            fprintf(fichier, "\n");
            count++;
            if (count % 3 == 0)
            {
                fprintf(fichier, "\n");
            }
        }
        else if (i != 1 && i % 3 == 1)
        {
            fprintf(fichier, " ");
        }
        SDL_Surface *surface = load_image(imagePath);
        if (surface == NULL)
        {
            printf("Erreur lors du chargement de l'image %d.\n", i);
            continue;
        }
        if ((!estVide(surface) && estVide2(surface)) || (estVide(surface) 
        && !estVide2(surface)))
        {
            printf("Path : %s\n", imagePath);
            int resultat = 
            numberDetection("../neural_network/saved_network/scoobydoo.txt",
            imagePath);
            fprintf(fichier, "%d", resultat);
            continue;
        }
        if (!estVide2(surface))
        {
	    char sysCall[200];
            fprintf(fichier, ".");
	    sprintf(sysCall, "rm -rf %s", imagePath);
	    system(sysCall);
        }
        else
        {
            printf("Path : %s\n", imagePath);
            int resultat = 
            numberDetection("../neural_network/saved_network/scoobydoo.txt",
            imagePath);
            fprintf(fichier, "%d", resultat);
        }
        printf("Image %d traitée.\n", i);
        SDL_FreeSurface(surface);
    }
    fprintf(fichier, "\n");
    fclose(fichier);
    return 0;
}
