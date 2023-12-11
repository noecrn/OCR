#ifndef THRESHOLD_H
#define THRESHOLD_H

#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include "operation.h"

size_t otsu(SDL_Surface *image_surface, size_t h, size_t w);
void binarize(SDL_Surface *image_surface, size_t threshold);
#endif