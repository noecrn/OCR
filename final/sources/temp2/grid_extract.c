#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <err.h>
#include "grid_detect.h"





// External function to resize an image without preserving aspect ratio to (28,28)
void resizeImageWithoutRatio(SDL_Surface* originalSurface) {
     // Create a new surface 
    SDL_Surface * resizedSurface = 
    SDL_CreateRGBSurfaceWithFormat(0, 28, 28,
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
 

void extract(int x[],int y[],int * t)
{
    void aux (int *xx,int *yy,float s0,float s1,float y0_intercept,
    float y1_intercept)    // calcul les coordonnées d'intersection de deux droites
        {
            float x=(y1_intercept-y0_intercept)/(s0-s1);
            *xx=(int)x;
            float y=s0*x+y0_intercept;
            *yy=(int)y;
        }

    int tab[82][4]; // contient les coordonnées (x0,y0),(x1,y1) de chaque case
    for (int i = 0; i < 82 ; i++)
    {
        for (int j = 0; j < 4 ; j++) tab[i][j]=0;
    }

    SDL_Surface *Surface = NULL;
    Surface = IMG_Load("out.png");
    if (!Surface) errx(EXIT_FAILURE, "Failed to load image: %s", IMG_GetError()
    );
    int h1=Surface->h;
    int w1=Surface->w;

    Surface = IMG_Load("filtered.png");
    if (!Surface) errx(EXIT_FAILURE, "Failed to load image: %s", IMG_GetError()
    );
    int h0=Surface->h;
    int w0=Surface->w;
      
    float ratioX=(float)w0/w1;
    float ratioY=(float)h0/h1;
    float slope=0;
    float y_intercept=0;


    // recalcule des coordonnées de toutes les droites de la grille
    // coordonates[0]=ligne haut    (1er ligne)
    // coordonates[9]=ligne bas     (10ème ligne)
    // coordonates[10]=ligne colonne gauche    (1er ligne)
    // coordonates[19]=ligne colonne droite    (10ème ligne)
    // coordonates[][0]=slope
    // coordonates[][1]=y_intercept
    float coordonates[20][2]; 
    for (int a=0;a<20;a++)
    {
        for (int b=0;b<2;b++) coordonates[a][b]=-999;
    }
    line (&slope,&y_intercept,(float) x[0]*ratioX,(float) y[0]*ratioY,
    (float) x[1]*ratioX,(float) y[1]*ratioY);
    coordonates[0][0]=slope;
    coordonates[0][1]=y_intercept;
    line (&slope,&y_intercept,(float) x[0]*ratioX,(float) y[0]*ratioY,
    (float) x[3]*ratioX,(float) y[3]*ratioY);
    coordonates[10][0]=slope;
    coordonates[10][1]=y_intercept;   
    line (&slope,&y_intercept,(float) x[2]*ratioX,(float) y[2]*ratioY,
    (float) x[1]*ratioX,(float) y[1]*ratioY);
    coordonates[19][0]=slope;
    coordonates[19][1]=y_intercept;
    line (&slope,&y_intercept,(float) x[2]*ratioX,(float) y[2]*ratioY,
    (float) x[3]*ratioX,(float) y[3]*ratioY);
    coordonates[9][0]=slope;
    coordonates[9][1]=y_intercept;

    for (int i=1; i<9; i++)
    {
        float x0= x[0]*ratioX+(x[1]*ratioX-x[0]*ratioX)/9*i;
        float y0= y[0]*ratioY+(y[1]*ratioY-y[0]*ratioY)/9*i;
        float x1= x[3]*ratioX+(x[2]*ratioX-x[3]*ratioX)/9*i;
        float y1= y[3]*ratioY+(y[2]*ratioY-y[3]*ratioY)/9*i;
        line (&slope,&y_intercept,x0,y0,x1,y1);
        coordonates[10+i][0]=slope;
        coordonates[10+i][1]=y_intercept;
    }

 
    for (int i=1; i<9; i++)
    {
        float x0=(x[0]*ratioX+(x[3]*ratioX-x[0]*ratioX)/9*i);
        float y0=(y[0]*ratioY+(y[3]*ratioY-y[0]*ratioY)/9*i);
        float x1=(x[1]*ratioX+(x[2]*ratioX-x[1]*ratioX)/9*i);
        float y1=(y[1]*ratioY+(y[2]*ratioY-y[1]*ratioY)/9*i);
        line (&slope,&y_intercept,x0,y0,x1,y1);
        coordonates[i][0]=slope;
        coordonates[i][1]=y_intercept;
    } 

    // extraction des images
    int image=1;

    for (int xx=0; xx<9;xx++)
    {
        for (int yy=10; yy<19;yy++)
        {
            int xd=0; //  x départ  (xd,yd) pixel haut à gauche de la case
            int yd=0; //  y départ
            int xa=0; //  x arrivé  (xa,ya) pixel bas à droite de la case
            int ya=0; // y arrivé
            
            aux(&xd,&yd,coordonates[xx][0],coordonates[yy][0],
            coordonates[xx][1],coordonates[yy][1]);
            aux(&xa,&ya,coordonates[xx+1][0],coordonates[yy+1][0],
            coordonates[xx+1][1],coordonates[yy+1][1]);
            int longX=(xa-xd);
            int longY=(ya-yd);
            tab[image][0]=(float) xd;
            tab[image][1]=(float)yd;
            tab[image][2]=(float)xa;
            tab[image][3]=(float)ya;

            SDL_Surface *Number = SDL_CreateRGBSurface(0, longX+1, 
            longY+1, 32, 0, 0, 0, 0);
            for (int x = xd; x < xa ; x++)
            {
                for (int y = yd; y < ya ; y++)
                {
                    Uint8 r, g, b;

                    SDL_GetRGB(*(Uint32 *)
                            ((Uint8 *)Surface->pixels + (int)(y) * 
                            Surface->pitch + (int)(x) *
                            Surface->format->BytesPerPixel), 
                            Surface->format, &r, &g, &b);

                    if (x-xd>-1 && x-xd<(longX) && y-yd>-1 && 
                    y-yd<longY-1){
                        *(Uint32 *)
                            ((Uint8 *)Number->pixels + 
                            (int)((y-yd)) * Number->pitch + (int)((x-xd)) *
                            Number->format->BytesPerPixel)
                            = SDL_MapRGB(Number->format, r, g, b);
                    }                
                }
            }

            for (int y = 0; y < longY/2 ; y++) // supprime les traits de ligne en haut
            {
                int count=0;
                for (int x = 0; x < longX ; x++)
                {
                    Uint8 r, empty;

                    SDL_GetRGB(*(Uint32 *)
                            ((Uint8 *)Number->pixels + (y) * Number->pitch 
                            + (x) *
                            Number->format->BytesPerPixel), Number->format, 
                            &r, &empty, &empty);

                    if (r==255) count+=1;
                }
                if (longX-count <longX/3)
                {
                    for (int ytemp=0; ytemp<y+1;ytemp++)
                    {
                        for (int x = 0; x < longX ; x++)
                        {
                            *(Uint32 *)
                                ((Uint8 *)Number->pixels + ytemp * 
                                Number->pitch + x *
                                Number->format->BytesPerPixel)
                                = SDL_MapRGB(Number->format, 0,0,0);
                        }
                    }   
                }
            }


            for (int y = longY-1; y > longY/2 ; y--) // supprime les traits de ligne en bas
            {
                int count=0;
                for (int x = 0; x < longX ; x++)
                {
                    Uint8 r, empty;

                    SDL_GetRGB(*(Uint32 *)
                            ((Uint8 *)Number->pixels + (y) * 
                            Number->pitch + (x) *
                            Number->format->BytesPerPixel), 
                            Number->format, &r, &empty, &empty);

                    if (r==255) count+=1;
                }
                if (longX-count <longX/3)
                {
                    for (int ytemp=y; ytemp<longY;ytemp++)
                    {
                        for (int x = 0; x < longX ; x++)
                        {
                            *(Uint32 *)
                                ((Uint8 *)Number->pixels + ytemp * 
                                Number->pitch + x *
                                Number->format->BytesPerPixel)
                                = SDL_MapRGB(Number->format, 0,0,0);
                        }
                    }   
                }
            }


            for (int x = 0; x < longX/2 ; x++)  // supprime les traits de ligne à gauche
            {
                int count=0;
                for (int y = 0; y < longY ; y++)
                {
                    Uint8 r, empty;

                    SDL_GetRGB(*(Uint32 *)
                            ((Uint8 *)Number->pixels + (y) * 
                            Number->pitch + (x) *
                            Number->format->BytesPerPixel), 
                            Number->format, &r, &empty, &empty);

                    if (r==255) count+=1;
                }
                if (longY-count <longY/3)
                {
                    for (int xtemp=0; xtemp<x+1;xtemp++)
                    {
                        for (int y = 0; y < longY ; y++)
                        {
                            *(Uint32 *)
                                ((Uint8 *)Number->pixels + y * 
                                Number->pitch + xtemp *
                                Number->format->BytesPerPixel)
                                = SDL_MapRGB(Number->format, 0,0,0);
                        }
                    }   
                }
            }

            for (int x = longX-1; x > longX/2 ; x--)  // supprime les traits de ligne à droite
            {
                int count=0;
                for (int y = 0; y < longY ; y++)
                {
                    Uint8 r, empty;

                    SDL_GetRGB(*(Uint32 *)
                            ((Uint8 *)Number->pixels + (y) * 
                            Number->pitch + (x) *
                            Number->format->BytesPerPixel), 
                            Number->format, &r, &empty, &empty);

                    if (r==255) count+=1;
                }
                if (longY-count <longY/3)
                {
                    for (int xtemp=x; xtemp<longX;xtemp++)
                    {
                        for (int y = 0; y < longY ; y++)
                        {
                            *(Uint32 *)
                                ((Uint8 *)Number->pixels + y * 
                                Number->pitch + xtemp *
                                Number->format->BytesPerPixel)
                                = SDL_MapRGB(Number->format, 0,0,0);
                        }
                    }   
                }
            }


            resizeImageWithoutRatio(Number);

            int digit0=image/10;
            int digit1=image%10;
            char num[]= "cases/XX.png";
            num[6]=digit0+'0';
            num[7]=digit1+'0';
            image+=1;
            IMG_SavePNG(Number, num);
            SDL_FreeSurface(Number);
        }

    }

    int ind=0;
    for (int i = 0; i < 82 ; i++)
    {
        for (int j = 0; j < 4 ; j++)
        {
            *(t+ind) = tab[i][j];
            ind+=1;
        }
    }
}


