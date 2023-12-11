#ifndef ROTATION_H
#define ROTATION_H

#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>

Uint32 get_pixel(SDL_Surface *image, int x, int y);
void render();
void set_pixel(SDL_Surface *image, int x, int y, Uint32 pixel);
void cleanup();
void handleEvents(int angl);
int initSDL(const char* imagePath);
SDL_Surface* rotate(SDL_Surface* source, double angle);

#endif