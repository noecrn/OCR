#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "grid_detect.h"
#include "grid_draw.h"
#include "grid_extract.h"

// extern void grid (int *xf0,int *yf0,int *xf1,int *yf1,int *xf2,int *yf2,int *xf3,int *yf3,int *lf0,int *lf1,int *lf2,int *lf3,char * imagePath);




int main(int argc, char *argv[])
{

//// uniquement pour mettre les bonnes photos en place
    SDL_Surface *Surface = NULL;
    Surface = IMG_Load(argv[1]);
    if (!Surface) errx(EXIT_FAILURE, "Failed to load image: %s", 
    IMG_GetError());
    IMG_SavePNG(Surface, "filtered.png");


    Surface = IMG_Load(argv[2]);
    if (!Surface) errx(EXIT_FAILURE, "Failed to load image: %s", 
    IMG_GetError());
    IMG_SavePNG(Surface, "original.png"); 
///////////////////////////////////////////////////////////////////////


    int x[4];
    int y[4];
    int l[4];
    for (int j=0;j<4;j++)
    {
        x[j]=-1;
        y[j]=-1;
        l[j]=-1;
    }

    int tab[82][4]; // récupération des coordonnées de chaque case
    for (int i = 0; i < 82 ; i++)
    {
        for (int j = 0; j < 4 ; j++)
        {
            tab[i][j]=-1;
        }
    }
    
    grid (&x[0],&y[0],&x[1],&y[1],&x[2],&y[2],&x[3],&y[3],&l[0],&l[1],
    &l[2],&l[3]);

    draw (x,y);

    extract (x,y,&tab);





    FILE *co;
    co = fopen("co", "w");

    fprintf(co, "%d\n", x[0]);
    fprintf(co, "%d\n", y[0]);
    fprintf(co, "%d\n", x[1]);
    fprintf(co, "%d\n", y[1]);
    fprintf(co, "%d\n", x[2]);
    fprintf(co, "%d\n", y[2]);
    fprintf(co, "%d\n", x[3]);
    fprintf(co, "%d\n", y[3]);





    fclose(co);






    printf("MAIN      ###########################\n");


for (int t=0; t<82;t+=8){
    int x0=tab[t][0];
    int y0=tab[t][1];
    int x1=tab[t][2];
    int y1=tab[t][3];

    for (int xx=x0; xx<x1;xx++)
        {
            for (int j=-2; j<3;j++)
            {
                *(Uint32 *)
                    ((Uint8 *)Surface->pixels + (y0+j) * 
                    Surface->pitch + xx *
                    Surface->format->BytesPerPixel)
                    = SDL_MapRGB(Surface->format, 255, 255, 0);

                *(Uint32 *)
                    ((Uint8 *)Surface->pixels + (y1+j) * 
                    Surface->pitch + xx *
                    Surface->format->BytesPerPixel)
                    = SDL_MapRGB(Surface->format, 255, 255, 0);
            }
        }
}
    
    IMG_SavePNG(Surface, "original1.png");  



    return EXIT_SUCCESS;
}
