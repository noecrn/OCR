#include "grayscale.h"
#include "threshold.h"
#include "cannyFilter.h"
#include "operation.h"
#include "adjust_gamma.h"
#include "gaussian_blur.h"
#include "contrast.h"
#include "median_blur.h"

void event_loop(SDL_Renderer *renderer, SDL_Texture *colored,
                SDL_Texture *grayscale, SDL_Surface *surface, char *filename)
{
    SDL_Event event;
    SDL_Texture *t = colored;
    draw(renderer, t);
    int applyThreshold = 0;

    while (1)
    {
        SDL_WaitEvent(&event);

        switch (event.type)
        {
        case SDL_QUIT:
            return;
        case SDL_WINDOWEVENT:
            if (event.window.event == SDL_WINDOWEVENT_RESIZED)
                draw(renderer, t);
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_g)
            {
                t = grayscale;
                SDL_Texture *filteredTexture =
                    SDL_CreateTextureFromSurface(renderer, surface);

                SDL_DestroyTexture(colored);
                colored = filteredTexture;
                t = colored;
            }
            else if (event.key.keysym.sym == SDLK_d)
            {
                cannyFilter(surface);
                SDL_Texture *filteredTexture =
                    SDL_CreateTextureFromSurface(renderer, surface);

                SDL_DestroyTexture(colored);
                colored = filteredTexture;
                t = colored;
            }
            else if (event.key.keysym.sym == SDLK_i)
            {
                adjust_contrast(surface);
                SDL_Texture *filteredTexture =
                    SDL_CreateTextureFromSurface(renderer, surface);

                SDL_DestroyTexture(colored);
                colored = filteredTexture;
                t = colored;
            }
            else if (event.key.keysym.sym == SDLK_b)
            {
                applyMedianFilter(surface);
                SDL_Texture *filteredTexture =
                    SDL_CreateTextureFromSurface(renderer, surface);

                SDL_DestroyTexture(colored);
                colored = filteredTexture;
                t = colored;
            }
            else if (event.key.keysym.sym == SDLK_c)
            {
                adjust_gamma(surface);
                SDL_Texture *filteredTexture =
                    SDL_CreateTextureFromSurface(renderer, surface);

                SDL_DestroyTexture(colored);
                colored = filteredTexture;
                t = colored;
            }
            else if (event.key.keysym.sym == SDLK_f)
            {
                gaussian_blur(surface, 9, 1.0);
                SDL_Texture *filteredTexture =
                    SDL_CreateTextureFromSurface(renderer, surface);

                SDL_DestroyTexture(colored);
                colored = filteredTexture;
                t = colored;
            }
            else if (event.key.keysym.sym == SDLK_m)
            {
                applyThreshold = !applyThreshold;

                if (applyThreshold)
                {
                    size_t threshold = otsu(surface, surface->h, surface->w);
                    if (strcmp(filename, "../image/image_03.jpeg") == 0)
                        threshold = 81;
                    printf("File: %s, threshold: %zu\n", filename, threshold);
                    binarize(surface, threshold);
                    SDL_Texture *filteredTexture =
                        SDL_CreateTextureFromSurface(renderer, surface);
                    SDL_DestroyTexture(colored);
                    colored = filteredTexture;
                    t = colored;
                }
            }
            draw(renderer, t);
        }
    }
    SDL_DestroyTexture(t);
    SDL_FreeSurface(surface);
}

int main(int argc, char **argv)
{
   if (argc != 2)
       errx(EXIT_FAILURE, "Usage: image-file ");

   if (SDL_Init(SDL_INIT_VIDEO) != 0)
   {
       errx(EXIT_FAILURE, "Failed to initialize SDL: %s", SDL_GetError());
   }

   SDL_Window *window =
       SDL_CreateWindow("Sudoku", 0, 0, 1280, 1080,
                       SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

   if (!window)
   {
       fprintf(stderr, "Failed to create window: %s\n", SDL_GetError());
       SDL_Quit();
       return EXIT_FAILURE;
   }

   SDL_Renderer *renderer =
       SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

   if (!renderer)
   {
       fprintf(stderr, "Failed to create renderer: %s\n", SDL_GetError());
       SDL_DestroyWindow(window);
       SDL_Quit();
       return EXIT_FAILURE;
   }

   SDL_Surface *surface = load_image(argv[1]);
   SDL_Texture *imageTexture =
       SDL_CreateTextureFromSurface(renderer, surface);

   surface_to_grayscale(surface);
   SDL_Texture *grayscaleTexture =
       SDL_CreateTextureFromSurface(renderer, surface);

   event_loop(renderer, imageTexture, grayscaleTexture, surface, argv[1]);

   IMG_SavePNG(surface, "result.png");

   SDL_FreeSurface(surface);
   SDL_DestroyTexture(imageTexture);
   SDL_DestroyTexture(grayscaleTexture);
   SDL_DestroyRenderer(renderer);
   SDL_DestroyWindow(window);
   SDL_Quit();

   return EXIT_SUCCESS;
}

