#include "adjust_gamma.h"

void adjust_gamma(SDL_Surface *surface)
{
    int num_pixels = surface->w * surface->h;

    int sum = 0;

    Uint8 *luminosity = (Uint8 *)malloc(num_pixels * sizeof(Uint8));

    for (int y = 0; y < surface->h; y++)
    {
        for (int x = 0; x < surface->w; x++)
        {
            Uint32 pixel = getPixel(surface, x, y);
            Uint8 r, g, b;
            SDL_GetRGB(pixel, surface->format, &r, &g, &b);
            luminosity[y * surface->w + x] = r;
            sum += r;
        }
    }

    double average_luminosity = (double)sum / num_pixels;

    double *gamma_corrections = (double *)malloc(256 * sizeof(double));
    for (int i = 0; i < 256; i++)
    {
        gamma_corrections[i] = 1.0;
    }

    if (average_luminosity < 100)
    {
        for (int i = 0; i < 256; i++)
        {
            gamma_corrections[i] = 3;
        }
    }
    else if (average_luminosity > 200)
    {
        for (int i = 0; i < 256; i++)
        {
            gamma_corrections[i] = 0.8;
        }
    }
    else if (average_luminosity > 170 && average_luminosity < 175)
    {
        for (int i = 0; i < 256; i++)
        {
            gamma_corrections[i] = 3;
        }
    }
    else if (average_luminosity > 175 && average_luminosity < 180)
    {
        for (int i = 0; i < 256; i++)
        {
            gamma_corrections[i] = 1;
        }
    }
    else if (average_luminosity > 180 && average_luminosity < 200)
    {
        for (int i = 0; i < 256; i++)
        {
            gamma_corrections[i] = 0.479;
        }
    }

    for (int y = 0; y < surface->h; y++)
    {
        for (int x = 0; x < surface->w; x++)
        {
            Uint32 pixel = getPixel(surface, x, y);
            Uint8 r, g, b;
            SDL_GetRGB(pixel, surface->format, &r, &g, &b);

            r = clamp(255 * pow((r / 255.0), 
            1 / gamma_corrections[luminosity[y * surface->w + x]]), 0, 255);
            g = clamp(255 * pow((g / 255.0), 
            1 / gamma_corrections[luminosity[y * surface->w + x]]), 0, 255);
            b = clamp(255 * pow((b / 255.0), 
            1 / gamma_corrections[luminosity[y * surface->w + x]]), 0, 255);

            Uint32 adjusted_pixel = SDL_MapRGB(surface->format, r, g, b);
            setPixel(surface, x, y, adjusted_pixel);
        }
    }

    free(luminosity);
    free(gamma_corrections);
}
