#include "grayscale.h"

// Updates the display.
//
// renderer: Renderer to draw on.
// texture: Texture that contains the image.
void draw(SDL_Renderer *renderer, SDL_Texture *texture)
{
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

SDL_Surface *load_image(const char *path)
{
    SDL_Surface *temp = IMG_Load(path);
    if (!temp)
    {
        errx(EXIT_FAILURE, "Failed: %s", IMG_GetError());
    }

    SDL_Surface *convertedSurface = 
    SDL_ConvertSurfaceFormat(temp, SDL_PIXELFORMAT_RGB888, 0);
    
    SDL_FreeSurface(temp);
    if (!convertedSurface)
    {
        errx(EXIT_FAILURE, "Failed: %s", SDL_GetError());
    }

    return convertedSurface;
}

// Converts a colored pixel into grayscale.
// pixel_color: Color of the pixel to convert in the RGB format.
// format: Format of the pixel used by the surface.
Uint32 pixel_to_grayscale(Uint32 pixel_color, SDL_PixelFormat *format)
{
    Uint8 r, g, b;
    SDL_GetRGB(pixel_color, format, &r, &g, &b);

    Uint32 average = 0.3 * r + 0.59 * g + 0.11 * b;
    r = g = b = average;

    return SDL_MapRGB(format, r, g, b);
}

void surface_to_grayscale(SDL_Surface *surface)
{
    Uint32 *pixels = surface->pixels;
    int len = surface->w * surface->h;

    if (SDL_LockSurface(surface) != 0)
    {
        errx(EXIT_FAILURE, "Failed to lock surface: %s", SDL_GetError());
    }

    for (int i = 0; i < len; i++)
    {
        Uint8 r, g, b;
        SDL_GetRGB(pixels[i], surface->format, &r, &g, &b);

        Uint8 average = (0.3 * r + 0.59 * g + 0.11 * b);
        pixels[i] = SDL_MapRGB(surface->format, average, average, average);
    }

    SDL_UnlockSurface(surface);
}
