#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <err.h>
#include "grid_detect.h"






void draw(int x[],int y[])
{

    SDL_Surface *Surface = NULL;
    Surface = IMG_Load("out.png");
    if (!Surface) errx(EXIT_FAILURE, "Failed to load image: %s", IMG_GetError()
    );
    int h1=Surface->h;
    int w1=Surface->w;

    Surface = IMG_Load("original.png");
    if (!Surface) errx(EXIT_FAILURE, "Failed to load image: %s", IMG_GetError()
    );
    int h0=Surface->h;
    int w0=Surface->w;
      


    float ratioX=(float)w0/w1;
    float ratioY=(float)h0/h1;




    // printf("DRAW      ###########################\n");
    // for (int j=0;j<4;j++) printf("x%i=%i    y%i=%i\n",j,x[j],j,y[j]);


    float slope=-999;
    float y_intercept=-999;


    for (int l=0;l<10;l++) // draw lines
    {
        int x0=(x[0]*ratioX+(x[3]*ratioX-x[0]*ratioX)/9*l);
        int y0=(y[0]*ratioY+(y[3]*ratioY-y[0]*ratioY)/9*l);
        int x1=(x[1]*ratioX+(x[2]*ratioX-x[1]*ratioX)/9*l);
        int y1=(y[1]*ratioY+(y[2]*ratioY-y[1]*ratioY)/9*l);
        line (&slope,&y_intercept,x0,y0,x1,y1);
        for (int xx=x0; xx<x1;xx++)
        {
            int yy=0;
            yy=slope*xx+y_intercept;
            if (yy>4 && yy<h0-4)
            {
                int e0=0;
                int e1=1;
                if (l==0 || l==9)
                {
                    e0=-4;
                    e1=5;
                }
                else if (l==3 || l==6)
                {
                    e0=-1;
                    e1=2;
                }
                for (int j=e0; j<e1;j++)
                {
                    *(Uint32 *)
                        ((Uint8 *)Surface->pixels + (yy+j) * Surface->pitch + 
                        xx *
                        Surface->format->BytesPerPixel)
                        = SDL_MapRGB(Surface->format, 255, 0, 0);
                }
            }
        }
    }
            

    for (int l=0;l<10;l++) //draw columns
    {
        int x0=(x[0]*ratioX+(x[1]*ratioX-x[0]*ratioX)/9*l);
        int y0=(y[0]*ratioY+(y[1]*ratioY-y[0]*ratioY)/9*l);
        int x1=(x[3]*ratioX+(x[2]*ratioX-x[3]*ratioX)/9*l);
        int y1=(y[3]*ratioY+(y[2]*ratioY-y[3]*ratioY)/9*l);
        line (&slope,&y_intercept,x0,y0,x1,y1);
        for (int yy=y0; yy<y1;yy++)
        {
            int xx=0;
            xx=(yy-y_intercept)/slope;
            if (xx>4 && xx<w0-4)
            {
                int e0=0;
                int e1=1;
                if (l==0 || l==9)
                {
                    e0=-4;
                    e1=5;
                }
                else if (l==3 || l==6)
                {
                    e0=-1;
                    e1=2;
                }
                for (int j=e0; j<e1;j++)
                {
                    *(Uint32 *)
                        ((Uint8 *)Surface->pixels + (yy) * Surface->pitch + 
                        (xx+j) *
                        Surface->format->BytesPerPixel)
                        = SDL_MapRGB(Surface->format, 255, 0, 0);
                }
            }
        }
    }
    

    IMG_SavePNG(Surface, "original.png");  
}
