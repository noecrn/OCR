#ifndef GRID_DETECT_H
#define GRID_DETECT_H


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <err.h>


void grid (int *xf0,int *yf0,int *xf1,int *yf1,int *xf2,int *yf2,int *xf3,
        int *yf3,int *lf0,int *lf1,int *lf2,int *lf3);
void rotate(double angle,char * inputPath,int color);
void line(float *a, float *b , float x0, float y0, float x1, float y1);
void resizeImage(const char* inputPath, const char* outputPath, int minSideSize);





#endif
