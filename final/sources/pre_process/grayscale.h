#ifndef GRAYSCALE_H
#define GRAYSCALE_H

#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void draw(SDL_Renderer* renderer, SDL_Texture* texture);
SDL_Surface* load_image(const char* path);
Uint32 pixel_to_grayscale(Uint32 pixel_color, SDL_PixelFormat* format);
void surface_to_grayscale(SDL_Surface* surface);

#endif