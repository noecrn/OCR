#include <err.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "rotation.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *texture = NULL;
SDL_Surface *imageSurface = NULL;
int angle = 0;

Uint32 getPixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch (bpp)
    {
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16 *)p;
        break;

    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
        break;

    case 4:
        return *(Uint32 *)p;
        break;

    default:
        return 0;
    }
}

void setPixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch (bpp)
    {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
        {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        }
        else
        {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}

void cleanup()
{
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

int initSDL(const char *imagePath)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        errx(EXIT_FAILURE, "Failed to initialize SDL: %s", SDL_GetError());
    }

    imageSurface = IMG_Load(imagePath);
    if (!imageSurface)
    {
        errx(EXIT_FAILURE, "Failed to load image: %s", IMG_GetError());
    }

    int imageWidth = imageSurface->w;
    int imageHeight = imageSurface->h;

    window = SDL_CreateWindow("Image Viewer", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, imageWidth, imageHeight,
                              SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (!window)
    {
        errx(EXIT_FAILURE, "Failed to create window: %s", SDL_GetError());
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED 
    | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer)
    {
        errx(EXIT_FAILURE, "Failed to create renderer: %s", SDL_GetError());
    }

    IMG_Init(IMG_INIT_JPG);
    texture = IMG_LoadTexture(renderer, imagePath);
    if (!texture)
    {
        errx(EXIT_FAILURE, "Failed to load image texture: %s", IMG_GetError());
    }

    return 0;
}

void handleEvents(int angl)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            cleanup();
            exit(0);
        }
        else if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                cleanup();
                exit(0);
            }
        }
    }

    imageSurface = rotate(imageSurface, angl);
    angle = angl;
    render();
}

void render()
{
    SDL_RenderClear(renderer);

    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    int centerX = windowWidth / 2;
    int centerY = windowHeight / 2;

    float scaleFactor = 0.5f;

    SDL_Rect dstRect = {centerX - (int)(imageSurface->w * scaleFactor) / 2, 
    centerY - (int)(imageSurface->h * scaleFactor) / 2, (int)(imageSurface->w * 
    scaleFactor), (int)(imageSurface->h * scaleFactor)};

    SDL_RenderCopyEx(renderer, texture, NULL, &dstRect, angle, NULL, 
    SDL_FLIP_NONE);
    
    SDL_RenderPresent(renderer);
}

SDL_Surface *rotate(SDL_Surface *origine, double angle)
{
    SDL_Surface *destination;
    int i;
    int j;
    Uint32 couleur;
    int mx, my, mxdest, mydest;
    int bx, by;
    float radians;
    double largeurdest;
    double hauteurdest;

    radians = -angle * M_PI / 180.0;

    largeurdest = ceil(origine->w * fabs(cos(radians)) + origine->h *
                                                             fabs(sin(
                                                                radians))),
    hauteurdest = ceil(origine->w * fabs(sin(radians)) + origine->h *
                                                             fabs(cos(
                                                                radians))),

    destination = SDL_CreateRGBSurface(SDL_SWSURFACE, largeurdest, hauteurdest,
                                       origine->format->BitsPerPixel,
                                       origine->format->Rmask, 
                                       origine->format->Gmask,
                                       origine->format->Bmask, 
                                       origine->format->Amask);

    if (destination == NULL)
        return NULL;

    mxdest = destination->w / 2.;
    mydest = destination->h / 2.;
    mx = origine->w / 2.;
    my = origine->h / 2.;

    for (j = 0; j < destination->h; j++)
        for (i = 0; i < destination->w; i++)
        {
            bx = (ceil(cos(radians) * (i - mxdest) + sin(radians) * (j - mydest)
             + mx));

            by = (ceil(-sin(radians) * (i - mxdest) + cos(radians) * (j - mydest)
             + my));

            if (bx >= 0 && bx < origine->w && by >= 0 && by < origine->h)
            {
                couleur = getPixel(origine, bx, by);
                setPixel(destination, i, j, couleur);
            }
        }


    return destination;
}