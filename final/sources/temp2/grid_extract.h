#ifndef GRID_DRAW_H
#define GRID_DRAW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <err.h>
#include "grid_detect.h"

void resizeImageWithoutRatio(SDL_Surface* originalSurface);
void extract(int x[],int y[],int * t);




#endif
