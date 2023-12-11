#include "cannyFilter.h"

SDL_Surface *cannyFilter(SDL_Surface *source)
{
    SDL_LockSurface(source);

    int y = 0;
    while (y < source->h - 1)
    {
        int x = 0;
        while (x < source->w - 1)
        {
            Uint8 red, green, blue;
            SDL_GetRGB(*(Uint32 *)((Uint8 *)source->pixels + y * 
            source->pitch + x * source->format->BytesPerPixel),
                       source->format, &red, &green, &blue);
            Uint8 gray = 0.3 * red + 0.59 * green + 0.11 * blue;

            SDL_GetRGB(*(Uint32 *)((Uint8 *)source->pixels + (y + 1) * 
            source->pitch + (x + 1) * source->format->BytesPerPixel),
                       source->format, &red, &green, &blue);

            Uint8 gray_next = 0.3 * red + 0.59 * green + 0.11 * blue;

            if (abs(gray_next - gray) > 10)
            {
                *(Uint32 *)((Uint8 *)source->pixels + y * source->pitch + 
                x * source->format->BytesPerPixel) =
                    SDL_MapRGB(source->format, 255, 255, 255);
            }
            else
            {
                *(Uint32 *)((Uint8 *)source->pixels + y * source->pitch + 
                x * source->format->BytesPerPixel) =
                    SDL_MapRGB(source->format, 0, 0, 0);
            }

            x++;
        }
        y++;
    }
    SDL_UnlockSurface(source);
    return source;
}
