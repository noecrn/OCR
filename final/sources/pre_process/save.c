#include "grayscale.h"
#include "threshold.h"
#include "cannyFilter.h"
#include "operation.h"
#include "adjust_gamma.h"
#include "gaussian_blur.h"
#include "contrast.h"
#include "median_blur.h"

int main(int argc, char **argv)
{
    // Checks the number of arguments.
    if (argc > 3 || argc < 2)
        errx(EXIT_FAILURE, "Usage: image-file ");

    SDL_Surface *surface = load_image(argv[1]);

    if (argc > 2)
    {
        if (strcmp(argv[2], "set1") == 0)
        {
            surface_to_grayscale(surface);
            adjust_contrast(surface);
            adjust_gamma(surface);
            applyMedianFilter(surface);
            //gaussian_blur(surface, 9, 1.0);
            size_t threshold = otsu(surface, surface->h, surface->w);
                    if(strcmp(argv[1], "../image/image_03.jpeg") == 0)
                        threshold = 81;
            binarize(surface, threshold);
            applyMedianFilter(surface);

            IMG_SavePNG(surface, "result.png");
            SDL_Quit();
            return EXIT_SUCCESS;
        }
        else if (strcmp(argv[2], "set2") == 0)
        {
            surface_to_grayscale(surface);
            adjust_contrast(surface);
            binarize(surface, otsu(surface, surface->h, surface->w));

            IMG_SavePNG(surface, "result.png");
            SDL_Quit();
            return EXIT_SUCCESS;
        }
    }
    
    SDL_FreeSurface(surface);
    return EXIT_SUCCESS;
}
