#ifndef GAUSSIAN_BLUR_H
#define GAUSSIAN_BLUR_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <err.h>


void gaussian_blur(SDL_Surface *image, int range, int sigma);

#endif