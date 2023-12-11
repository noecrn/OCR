#include "median_blur.h"

void applyMedianFilter(SDL_Surface *image)
{
    for (int y = 1; y < image->h - 1; y++)
    {
        for (int x = 1; x < image->w - 1; x++)
        {
            Uint8 red[9], green[9], blue[9];
            int index = 0;

            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    Uint8 *pixel = (Uint8 *)image->pixels + (y + i) * image->pitch + (x + j) * image->format->BytesPerPixel;
                    red[index] = pixel[0];
                    green[index] = pixel[1];
                    blue[index] = pixel[2];
                    index++;
                }
            }

            for (int i = 0; i < 9; i++)
            {
                for (int j = i + 1; j < 9; j++)
                {
                    if (red[i] > red[j])
                    {
                        Uint8 temp = red[i];
                        red[i] = red[j];
                        red[j] = temp;

                        temp = green[i];
                        green[i] = green[j];
                        green[j] = temp;

                        temp = blue[i];
                        blue[i] = blue[j];
                        blue[j] = temp;
                    }
                }
            }

            Uint8 *pixel = (Uint8 *)image->pixels + y * image->pitch + x * image->format->BytesPerPixel;
            pixel[0] = red[4];
            pixel[1] = green[4];
            pixel[2] = blue[4];
        }
    }

}