#ifndef GRID_PUTNUMBER_H
#define GRID_PUTNUMBER_H


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <err.h>

void resizeImagePutNumber(int w,int h, SDL_Surface* originalSurface);
void putNumber(int number, int coord[],SDL_Surface* Surface);





#endif