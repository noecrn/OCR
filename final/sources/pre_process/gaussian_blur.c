#include "gaussian_blur.h"
#include "operation.h"

void gaussian_blur(SDL_Surface *image, int range, int sigma)
{
    int height = image->h;
    int width = image->w;

    if (range % 2 == 0)
        range++;
    int midrange = range / 2;

    SDL_LockSurface(image);

    double *kernel = calloc(range * range, sizeof(double));
    double sum = 0;

    for (int x = -midrange; x < midrange; x++)
    {
        for (int y = -midrange; y < midrange; y++)
        {
            double value = (1 / (2 * M_PI * sigma * sigma)) * 
            exp(-(x * x + y * y) / (2 * sigma * sigma));
            kernel[(x + midrange) * range + (y + midrange)] = value;
            sum += value;
        }
    }

    for (int i = 0; i < range * range; i++)
    {
        kernel[i] /= sum;
    }

    SDL_Surface *output = SDL_CreateRGBSurface(0, width, height, 
    32, 0, 0, 0, 0);

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {

            double r = 0, g = 0, b = 0, a = 0;

            for (int fx = -midrange; fx < midrange; fx++)
            {
                int xx = x + fx;

                for (int fy = -midrange; fy < midrange; fy++)
                {
                    int yy = y + fy;

                    if (xx < 0 || xx >= width || yy < 0 || yy >= height)
                        continue;

                    Uint32 *pixel = (Uint32 *)image->pixels + 
                    yy * image->w + xx;
                    double value = kernel[(fx + midrange) * 
                    range + (fy + midrange)];

                    r += ((double)((*pixel >> 16) & 0xff)) * value;
                    g += ((double)((*pixel >> 8) & 0xff)) * value;
                    b += ((double)((*pixel >> 0) & 0xff)) * value;
                    a += ((double)((*pixel >> 24) & 0xff)) * value;
                }
            }

            Uint32 *output_pixel = (Uint32 *)output->pixels + y * output->w + x;
            *output_pixel = ((int)a << 24) | ((int)r << 16) | 
            ((int)g << 8) | ((int)b << 0);
            setPixel(image, x, y, *output_pixel);
        }
    }
            
}