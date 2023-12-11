#include "threshold.h"

size_t otsu(SDL_Surface *image_surface, size_t h, size_t w)
{
    float histogram[256] = {0.0F};

    for (size_t y = 0; y < h; y++)
    {
        for (size_t x = 0; x < w; x++)
        {
            Uint32 pixel = getPixel(image_surface, x, y);
            Uint8 r, g, b;
            SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
            size_t graylevel = r;
            histogram[graylevel] += 1;
        }
    }

    int nb_pixels = w * h;

    float sum = 0;

    for (int i = 0; i < 256; i++)
    {
        sum += i * histogram[i];
    }

    float sumB = 0;
    int BackG = 0;
    int ForeG = 0;

    float varMax = 0;
    int threshold = 0;

    for (int t = 0; t < 256; t++)
    {
        BackG += histogram[t];
        if (BackG == 0)
            continue;

        ForeG = nb_pixels - BackG;
        if (ForeG == 0)
            break;

        sumB += (float)(t * histogram[t]);

        float mB = sumB / BackG;
        float mF = (sum - sumB) / ForeG;

        float var_inter =
            (float)BackG * (float)ForeG * (mB - mF) * (mB - mF);

        if (var_inter > varMax)
        {
            varMax = var_inter;
            threshold = t;
        }
    }

    return (size_t)threshold;
}

void binarize(SDL_Surface *image_surface, size_t threshold)
{
    size_t width = image_surface->w;
    size_t height = image_surface->h;

    int black_pixels = 0;
    int white_pixels = 0;

    for (size_t y = 0; y < height; y++)
    {
        for (size_t x = 0; x < width; x++)
        {
            Uint32 pixel = getPixel(image_surface, x, y);
            Uint8 r, g, b;
            SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
            Uint8 bin_pixel_color = 0;
            if ((size_t)r < threshold)
            {
                bin_pixel_color = 255;
                white_pixels++;
            }
            else
            {
                black_pixels++;
            }
            pixel = SDL_MapRGB(image_surface->format,
                               bin_pixel_color, bin_pixel_color, 
                               bin_pixel_color);
            setPixel(image_surface, x, y, pixel);
        }
    }

    if (white_pixels > black_pixels)
        for (size_t y = 0; y < height; y++)
        {
            for (size_t x = 0; x < width; x++)
            {
                Uint32 pixel = getPixel(image_surface, x, y);
                Uint8 r, g, b;
                SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
                Uint8 bin_pixel_color = 255;
                if (r == 0)
                {
                    bin_pixel_color = 0;
                }
                pixel = SDL_MapRGB(image_surface->format,
                                   bin_pixel_color, bin_pixel_color, 
                                   bin_pixel_color);
                setPixel(image_surface, x, y, pixel);
            }
        }
}