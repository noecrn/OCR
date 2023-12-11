#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>
#include "grid_detect.h"
#include "grid_draw.h"
#include "grid_extract.h"
#include "grid_putNumber.h"
#include "../solver/solver.h"


int main(int argc, char *argv[])
{


//// uniquement pour mettre les bonnes photos en place
    SDL_Surface *Surface = NULL;
    Surface = IMG_Load(argv[1]);
    if (!Surface) errx(EXIT_FAILURE, "Failed to load image: %s", IMG_GetError()
    );
    IMG_SavePNG(Surface, "filtered.png");


    Surface = IMG_Load(argv[2]);
    if (!Surface) errx(EXIT_FAILURE, "Failed to load image: %s", IMG_GetError()
    );
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
    
    grid (&x[0],&y[0],&x[1],&y[1],&x[2],&y[2],&x[3],&y[3],&l[0],&l[1],&l[2],
    &l[3]);


    draw (x,y);

    extract (x,y,&tab);
    printf("tab[0] = %i \n\n\n", tab[10][0]);
    printf("tab[0] = %i \n\n\n", tab[10][1]);
    printf("tab[0] = %i \n\n\n", tab[10][2]);
    printf("tab[0] = %i \n\n\n", tab[10][3]);


    // char parser[256];
    // sprintf(parser, "./../pre_process/read_image");
    // int status = system(parser);
    // if(status != 0)printf("c la merde3");

    char solver[256];
    sprintf(solver, "./../solver/solver ../interface/output");
    int status = system(solver);
    //if(status != 0)printf("c la merde4");




    FILE* grid_00 = NULL; 
// Ouverture du fichier "grid_00" en lecture
    grid_00 = fopen("../interface/output", "r");
    
    if (grid_00 == NULL) {
        printf("ERREUR: Impossible d'ouvrir le fichier grid_00\n");
        return 1;
    }

    char gridContent[205] = "";
    char temp[11];

    // Lecture du contenu de "grid_00" dans gridContent
    while (fgets(temp, 11, grid_00) != NULL) {
        strcat(gridContent, temp);
    }

    char gr[82] = "";
    size_t k = 0;
    size_t q = 0;

    // Filtrage des caractères entre 46 et 57 inclus (caractères ASCII entre '.' et '9')
    while (gridContent[k] != '\0') {
        if (gridContent[k] >= 46 && gridContent[k] <= 57) {
            gr[q] = gridContent[k];
            q++;
        }
        k++;
    }

    //printf("grid_00 : %s\n", gr);

    fclose(grid_00);

    FILE* res = NULL; 







    // Ouverture du fichier "grid_00.result" en lecture
    res = fopen("output.result", "r");

    if (res == NULL) {
        printf("ERREUR: Impossible d'ouvrir le fichier grid_00.result\n");
        return 1;
    }

    // Réinitialisation des compteurs k et q
    k = 0;
    q = 0;

    // Réinitialisation du tableau gridContent
    memset(gridContent, 0, sizeof(gridContent));

    // Lecture du contenu de "grid_00.result" dans gridContent
    while (fgets(temp, 11, res) != NULL) {
        strcat(gridContent, temp);
    }

    char rs[82] = "";

    // Filtrage des caractères entre 46 et 57 inclus
    while (gridContent[k] != '\0') {
        if (gridContent[k] >= 46 && gridContent[k] <= 57) {
            if (gridContent[k] == '0'){
                return EXIT_FAILURE;
            }
            rs[q] = gridContent[k];
            q++;
        }
        k++;
    }

    //printf("grid_00.result : %s\n", rs);


    fclose(res);


    //printf("1\n\n\n");

/*
///////// partie pour utiliser les cooredonnées de chaque case
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
                     ((Uint8 *)Surface->pixels + (y0+j) * Surface->pitch + xx *
                     Surface->format->BytesPerPixel)
                     = SDL_MapRGB(Surface->format, 255, 255, 0);

                 *(Uint32 *)
                     ((Uint8 *)Surface->pixels + (y1+j) * Surface->pitch + xx *
                     Surface->format->BytesPerPixel)
                     = SDL_MapRGB(Surface->format, 255, 255, 0);
             }
        }
    }

    IMG_SavePNG(Surface, "toto.png");
*/
    //grid (&x[0],&y[0],&x[1],&y[1],&x[2],&y[2],&x[3],&y[3],&l[0],&l[1],&l[2],&l[3]);
    //extract (x,y,&tab);

    /////////// partie pour mettre une valeur dans une grille. il faut utiliser l'image original.png et la sauvegarder à la fin
     Surface = IMG_Load("original.png");
     if (!Surface) errx(EXIT_FAILURE, "Failed to load image: %s", 
     IMG_GetError());
   

     //printf("1,1\n\n\n");
     //draw(x,y);
     //printf("1,2\n\n\n");
     //int num=1;
     
    //printf("tab[0] = %i \n\n\n", tab[10][0]);

     int index = 0;
     for (int i=1 ; i<82;i++)
     {   
         //printf("num = %i, i = %i\n\n\n", gr[index],i);
             //printf("rs = %i", rs[index]-48);
             putNumber((rs[index]-48), tab[i], Surface);
             //IMG_SavePNG(Surface, "temporaire.png");
         
         index++;
         //putNumber(num,tab[i], Surface);
         //num+=1;
         //if (num>9) num=1;
     }
     IMG_SavePNG(Surface, "original.png");  

    //printf("2\n\n\n");


    printf("MAIN EXECUTE     ###########################\n");


    return EXIT_SUCCESS;
}

