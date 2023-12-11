#include "contrast.h"

double clamp(double d, double min, double max)
{
    const double t = d < min ? min : d;
    return t > max ? max : t;
}

void adjust_contrast(SDL_Surface *surface)
{
    int width = surface->w;
    int height = surface->h;

    int minGray = 255, maxGray = 0;

    Uint8 *grayValues = (Uint8 *)malloc(width * height * 
    sizeof(Uint8));

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            Uint32 pixel = getPixel(surface, x, y);
            Uint8 r, g, b;
            SDL_GetRGB(pixel, surface->format, &r, &g, &b);
            grayValues[y * width + x] = r;
            minGray = (grayValues[y * width + x] < minGray) 
            ? grayValues[y * width + x] : minGray;
            maxGray = (grayValues[y * width + x] > maxGray) 
            ? grayValues[y * width + x] : maxGray;
        }
    }

    double contrastFactor = 255.0 / (maxGray - minGray);
    SDL_LockSurface(surface);

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int grayValue = grayValues[y * width + x];
            int adjustedValue = (int)(contrastFactor * (grayValue - minGray));

            adjustedValue = (adjustedValue < 0) ? 0 : ((adjustedValue > 255) 
            ? 255 : adjustedValue);
            Uint32 pixel = SDL_MapRGB(surface->format, adjustedValue, 
            adjustedValue, adjustedValue);
            setPixel(surface, x, y, pixel);
        }
    }

    SDL_UnlockSurface(surface);

    free(grayValues);
}
