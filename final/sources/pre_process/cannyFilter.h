#ifndef CANNYFILTER_H
#define CANNYFILTER_H

#include <SDL2/SDL.h>
#include <err.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>

SDL_Surface* cannyFilter(SDL_Surface* source);

#endif