#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <err.h>


// External function to resize an image 
void resizeImagePutNumber(int w,int h, SDL_Surface* originalSurface) {
     // Create a new surface 
    SDL_Surface * resizedSurface = 
    SDL_CreateRGBSurfaceWithFormat(0, w, h,
                                    originalSurface->format->BitsPerPixel,
                                    originalSurface->format->format);

    // Scale the image to the new surface
    if (SDL_BlitScaled(originalSurface, NULL, resizedSurface, NULL) != 0) {
        printf("erreur resize");
        fprintf(stderr, "SDL_BlitScaled error: %s\n", SDL_GetError());
        SDL_FreeSurface(originalSurface);
        SDL_FreeSurface(resizedSurface);
        IMG_Quit();
        SDL_Quit();
        return;
    }
    *originalSurface = *resizedSurface;
}

void putNumber(int number, int coord[],SDL_Surface* Surface)
{
    int x0=coord[0];
    int y0=coord[1];
    int x1=coord[2];
    int y1=coord[3];

    //printf("----------------- x0=%i   y0=%i\n",x0,y0);
    
    char num[]="../temp/X.png";
    if (number==1) num[8]='1';
    if (number==2) num[8]='2';
    if (number==3) num[8]='3';
    if (number==4) num[8]='4';
    if (number==5) num[8]='5';
    if (number==6) num[8]='6';
    if (number==7) num[8]='7';
    if (number==8) num[8]='8';
    if (number==9) num[8]='9';

    SDL_Surface* imageNumber=NULL;
    imageNumber =IMG_Load(num);

    int width=(int)(x1-x0);
    int height=(int) (y1-y0); 
    int shift = (int) (width+height)/2*0.4;
    resizeImagePutNumber((width-shift),(height-shift),imageNumber);
    shift/=2;
    for (int x = (x0+shift); x < x1-shift ; x++)
            {
                for (int y = (y0+shift); y < y1-shift ; y++)
                {
                    Uint8 r, g, b;
                    Uint8 r1, g1, b1;
                    Uint8 r2, g2, b2;

                    SDL_GetRGB(*(Uint32 *)
                            ((Uint8 *)imageNumber->pixels + (y-y0-shift) * 
                            imageNumber->pitch + (x-x0-shift) *
                            imageNumber->format->BytesPerPixel), 
                            imageNumber->format, &r1, &g1, &b1);
                    SDL_GetRGB(*(Uint32 *)
                            ((Uint8 *)Surface->pixels + (y) * 
                            Surface->pitch + (x) *
                            Surface->format->BytesPerPixel), 
                            Surface->format, &r2, &g2, &b2);

                    if (r1+r2>255)r=0;
                    else r=r2;
                    if (g1+g2>255)g=0;
                    else g=g2;
                    if (b1+b2>255)b=0;
                    else b=r2;
                    if (r==0 && g==0 && b==0)r=255;

                        *(Uint32 *)
                            ((Uint8 *)Surface->pixels + 
                            (int)((y)) * Surface->pitch + (int)((x)) *
                            Surface->format->BytesPerPixel)
                            = SDL_MapRGB(Surface->format, r, g, b);
             
                }
            }

}
