#ifndef CONTRAST_H
#define CONTRAST_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "operation.h"

void adjust_contrast(SDL_Surface *surface);
double clamp(double d, double min, double max);

#endif