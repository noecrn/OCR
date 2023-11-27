/*#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>

SDL_Surface *Surface = NULL;





int main(int argc, char** argv)
{
    if (argc != 2)
    {
        errx(EXIT_FAILURE, "more arguments needed");
    }

    char *imagePath = argv[1];

    Surface = IMG_Load(imagePath);

    if (!Surface)
    {
        errx(EXIT_FAILURE, "Failed to load image: %s", IMG_GetError());
    }

    int h=Surface->h;
    int w=Surface->w;

    for (int y = 0; y < h ; ++y)
        {
            for (int x = 0; x < w ; ++x)
            {
                Uint8 r, g, b;
                SDL_GetRGB(*(Uint32 *)
                        ((Uint8 *)Surface->pixels + y * Surface->pitch + x *
                        Surface->format->BytesPerPixel), Surface->format, &r, &g, &b);


                if (r > 100 && g > 100 && b > 100)//white pixel -> line to detect
                {
                *(Uint32 *)
                    ((Uint8 *)Surface->pixels + y * Surface->pitch + x *
                    Surface->format->BytesPerPixel) 
                    = SDL_MapRGB(Surface->format, 1, 0,255);

                }
                else
                {
                *(Uint32 *)
                    ((Uint8 *)Surface->pixels + y * Surface->pitch + x *
                    Surface->format->BytesPerPixel) 
                    = SDL_MapRGB(Surface->format, 0, 0 ,0);
                }
            }
        }





    int resTemp1[100][3];
    float resTemp2[100][3];
    float resTemp3[100][3];
    int count[100][3];

    for (int i =0; i<100;i++)
    {
        for (int j=0;j<2;j++)
        {
            resTemp1[i][j]=-1;
            resTemp2[i][j]=-1;
            resTemp3[i][j]=-1;
            count[i][j]=0;
        }
    }

    int y=h/4;
    int iMax=0;
    while (y<h/4*3)
    {
        int c=0;

        for (int yy=y;yy<y+3;yy++)
        {
            for (int x=w/4; x<w/4*3;x++)
            {
                Uint8 r, g, b;
                SDL_GetRGB(*(Uint32 *)
                        ((Uint8 *)Surface->pixels + yy * Surface->pitch + x *
                        Surface->format->BytesPerPixel), Surface->format, &r, &g, &b);
                if (r==1) {c+=1;}
            }
        }    
        if (c>iMax){iMax=c;}

       y+=1;
    }

    y=h/4;
    int pos=0;
    while (y<h/4*3)
    {
        int c=0;

        for (int yy=y;yy<y+3;yy++)
        {
            for (int x=w/4; x<w/4*3;x++)
            {
                Uint8 r, g, b;
                SDL_GetRGB(*(Uint32 *)
                        ((Uint8 *)Surface->pixels + yy * Surface->pitch + x *
                        Surface->format->BytesPerPixel), Surface->format, &r, &g, &b);
                if (r==1) {c+=1;}
            }
        }    
        if (c>w*0.4 && c>iMax*0.1)
            {
                resTemp1[pos][0]=y+1;
                resTemp1[pos][1]=c;
                y+=w/20;
                pos+=1;
            }


        y+=1;
    }

    // for (int i=0;i<20;i++)
    // {
    //     printf("y=%i     next=%i    ecart=%i\n",resTemp1[i][0],resTemp1[i][1], resTemp1[i][2]);
    // }

    
    int nbValue=0;
    float d=1;
    float delta=0;
    float r1=0;
    float r2=0;
    for (int i=0;i<100;i++) { 
        if (resTemp1[i][0]!=-1){nbValue+=1;}}
    pos=0;   

    // printf("value=%i\n",nbValue);
    int i =0;

    while (i<nbValue/2+1) 
    {    
        d=resTemp1[i+1][0]-resTemp1[i][0];
        int j=i;
        while (j<nbValue)
            {   
                r1= abs(resTemp1[j][0]-resTemp1[i][0])/d;
                r2=roundf(r1);
                delta=fabs(r2-r1)*100;
                if ( delta <11)
                {
                    resTemp2[pos][0]=resTemp1[i][0];
                    resTemp2[pos][1]=resTemp1[j][0];
                    resTemp2[pos][2]=r1;
                    pos+=1;
                }
                j+=1;
            }
        i+=1;
    }


    // for (int i=0;i<100;i++)
    // {
    //     printf("restemp2 y=%f     next=%f    ecart=%f\n",resTemp2[i][0],resTemp2[i][1], resTemp2[i][2]);
    // }
    pos=0;
    int find=0;
    for (int i=0;i<100;i++)
    {
        for (int j=0;j<100;j++)
        {
            if (resTemp2[i][0]==count[j][0] && resTemp2[i][0]>-1 )
            {
                count[j][1]+=1;
                find=1;
            }
        }
        if (find==0)
        {
            count[pos][0]=resTemp2[i][0];
            count[pos][1]+=1;
            pos+=1;
        }
        find=0;
    }

//    for (int i=0;i<15;i++)
//     {
//         printf("y===========%i     next=%i    ecart=%i\n",count[i][0],count[i][1], count[i][2]);
//     }


    int maxi=0;
    int val=0;
    pos=0;
    for (int i=0; i<100;i++)
    {
        if (count[i][1]>maxi)
        {
            maxi=count[i][1];
            val=count[i][0];
        }
    }

    for (int i=0; i<100;i++)
    {
        if (resTemp2[i][0]==val)
        {
            resTemp3[pos][0]=val;
            resTemp3[pos][1]=resTemp2[i][1];
            resTemp3[pos][2]=resTemp2[i][2];
            pos +=1;
        }
    }

    // for (int i=0;i<15;i++)
    // {
    //     printf("restemp3   y=%f     next=%f    ecart=%f\n",resTemp3[i][0],resTemp3[i][1], resTemp3[i][2]);
    // }



    i=0;
    maxi=0;
    while (i<100)
    {
        if (resTemp3[i][0]!=-1)
        {
            maxi+=1;
            i+=1;
        }
        else {i=100;}
    }

    // printf("maxi=%i\n\n",maxi);

    float lines[maxi][3];
    for (int i=0;i<maxi;i++)
    {
        lines[i][0]=resTemp3[i][0];
        lines[i][1]=resTemp3[i][1];
        lines[i][2]=resTemp3[i][2];
    }


    float caseY=(lines[maxi-1][1]-lines[maxi-1][0])/roundf(lines[maxi-1][2]);

    for (int i=0;i<maxi;i++)
    {
        printf("y=%f     next=%f    ecart=%f\n",lines[i][0],lines[i][1], lines[i][2]);
    }

    printf ("case=%f",caseY);


    for (int y = lines[0][0]; y < h ; y+=caseY)
            {
                for (int x = 0; x < w ; ++x)
                {
                         *(Uint32 *)
                        ((Uint8 *)Surface->pixels + y * Surface->pitch + x *
                        Surface->format->BytesPerPixel) 
                        = SDL_MapRGB(Surface->format, 255, 255, 0);
                }
            }
    for (int y = lines[0][0]; y >0 ; y-=caseY)
            {
                for (int x = 0; x < w ; ++x)
                {
                         *(Uint32 *)
                        ((Uint8 *)Surface->pixels + y * Surface->pitch + x *
                        Surface->format->BytesPerPixel) 
                        = SDL_MapRGB(Surface->format, 255, 255, 0);
                }
            }


    IMG_SavePNG(Surface, "out.png");


    return EXIT_SUCCESS;
}*/








/*


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <err.h>


SDL_Surface *Surface = NULL;




// External function to resize an image while preserving aspect ratio
void resizeImage(const char* inputPath, const char* outputPath, int minSideSize) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init error: %s\n", SDL_GetError());
        return;
    }

    // Initialize SDL_image
    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
        fprintf(stderr, "IMG_Init error: %s\n", IMG_GetError());
        SDL_Quit();
        return;
    }

    // Load image
    SDL_Surface* originalSurface = IMG_Load(inputPath);
    if (!originalSurface) {
        fprintf(stderr, "Failed to load image: %s\n", IMG_GetError());
        IMG_Quit();
        SDL_Quit();
        return;
    }

    // Calculate new dimensions while preserving aspect ratio
    int newWidth, newHeight;
    if (originalSurface->w < originalSurface->h) {
        newWidth = minSideSize;
        newHeight = (int)((float)newWidth / originalSurface->w * originalSurface->h);
    } else {
        newHeight = minSideSize;
        newWidth = (int)((float)newHeight / originalSurface->h * originalSurface->w);
    }

    // Create a new surface with the calculated dimensions
    SDL_Surface* resizedSurface = SDL_CreateRGBSurfaceWithFormat(0, newWidth, newHeight,
                                                                originalSurface->format->BitsPerPixel,
                                                                originalSurface->format->format);

    // Scale the image to the new surface
    if (SDL_BlitScaled(originalSurface, NULL, resizedSurface, NULL) != 0) {
        fprintf(stderr, "SDL_BlitScaled error: %s\n", SDL_GetError());
        SDL_FreeSurface(originalSurface);
        SDL_FreeSurface(resizedSurface);
        IMG_Quit();
        SDL_Quit();
        return;
    }

    // Save the resized image
    if (SDL_SaveBMP(resizedSurface, outputPath) != 0) {
        fprintf(stderr, "SDL_SaveBMP error: %s\n", SDL_GetError());
        SDL_FreeSurface(originalSurface);
        SDL_FreeSurface(resizedSurface);
        IMG_Quit();
        SDL_Quit();
        return;
    }

    // Free surfaces and quit SDL
    SDL_FreeSurface(originalSurface);
    SDL_FreeSurface(resizedSurface);
    IMG_Quit();
    SDL_Quit();
}






int main(int argc, char *argv[]) {
    //printf("0kshvdchjsv\n\n\n\n ");
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image_path>\n", argv[0]);
        return EXIT_FAILURE;
    }
    //printf("1\n\n\n\n\n");
    
    char *imagePath = argv[1];
    
    
    resizeImage(imagePath, "temp.jpeg", 500);//500 ca marche
    


    Surface = IMG_Load("temp.jpeg");
    //Surface = IMG_Load(imagePath);


    if (!Surface)
    {
        errx(EXIT_FAILURE, "Failed to load image: %s", IMG_GetError());
    }
    
    //printf("2\n\n\n\n\n");

    int h=Surface->h;
    int w=Surface->w;

    int tab[h][w]; 
   /*
    void temp(int y, int x, int cpt)
    {
        if(x < 0 || x > w || y < 0 || y > h)return;//pixel or de l'image

        if(tab[y][x] == -1) return; //le pixel a deja été visité;

        if (tab[y][x] == 0)//le pixel appartient au fond, on le marque en visité et on arrete le parcours;
        {
            tab[y][x] = -1;
            return;
        }
        if (tab[y][x] == 1)//le pixel est un bord et n'a jamais été visité, on le marque comme appartenant au trait numero cpt
                           //on rappelle la fonction sur ses 8 voisins
        {
                tab[y][x] = cpt;
        }
    }//////////////////////////////////////////////////////////////////////////////////////


    void recursive(int y, int x, int cpt)
    {
        //printf("%i\n", cpt);

        //printf("11111111111111111jerngoiekngoinergioenkr\n\n\n\n\n\n");
        if(x < 1 || x > w-1 || y < 1 || y > h-1)return;//pixel or de l'image

        if(tab[y][x] == -1) return; //le pixel a deja été visité;

        if (tab[y][x] == 0)//le pixel appartient au fond, on le marque en visité et on arrete le parcours;
        {
            tab[y][x] = -1;
            return;
        }
        if (tab[y][x] == 1)//le pixel est un bord et n'a jamais été visité, on le marque comme appartenant au trait numero cpt
                           //on rappelle la fonction sur ses 8 voisins
        {
                tab[y][x] = cpt;
                
                recursive(y-1, x-1, cpt);
                recursive(y-1, x, cpt);
                recursive(y-1, x+1, cpt);
                recursive(y, x-1, cpt);
                recursive(y, x+1, cpt);
                recursive(y+1, x-1, cpt);
                recursive(y+1, x, cpt);
                recursive(y+1, x+1, cpt);
                /*
                temp(y-1, x-1, cpt);
                temp(y-1, x, cpt);
                temp(y-1, x+1, cpt);
                temp(y, x-1, cpt);
                temp(y, x+1, cpt);
                temp(y+1, x+1, cpt);
                temp(y+1, x, cpt);
                temp(y+1, x-1, cpt);
                ///////////////////////////////////////////////////////////////////////

        }
    }




    for (int y = 0; y < h ; y++)
    {
            for (int x = 0; x < w ; x++)
            {
                Uint8 r, g, b;
                SDL_GetRGB(*(Uint32 *)
                        ((Uint8 *)Surface->pixels + y * Surface->pitch + x *
                        Surface->format->BytesPerPixel), Surface->format, &r, &g, &b);

                if (r>200 && g>200 && b>200) //1 = contour, 0 = fond, -1 = fond et deja passé
                {
                    tab[y][x] = 1;
                }
                else tab[y][x] = 0;
            }
    }
    
    //printf("3\n\n\n\n\n\n");

    int cpt = 2;//nombre de traits differents

    for (int y = 0; y < h ; y++)
    {
        for (int x = 0; x < w ; x++)
        {
            if (tab[y][x] == 0) tab[y][x] = -1; //-1 : on est deja passé dessus, pas la peine de le retraité 
            if (tab[y][x] == 1)//pixel de contour: appel de la fonction recursive;
            {
                recursive(y, x, cpt);
                cpt += 1;
            }
        }
    }

    //printf("4");

    int i;
    
    for (int y = 0; y < h ; y++)//reconstitution de l'image
    {
        for (int x = 0; x < w ; x++)
        {
            i = tab[y][x];

            if(i!=-1 && i!=0 && i!=1)
            {
                *(Uint32 *)
                    ((Uint8 *)Surface->pixels + y * Surface->pitch + x *
                    Surface->format->BytesPerPixel) 
                    = SDL_MapRGB(Surface->format, (i*i + 425)%255, (i*17+43)%255, (i*i*i + 1234)%255);
            }            
        }
    }
    
    //printf("5");

    IMG_SavePNG(Surface, "out.png");
    
    return EXIT_SUCCESS;
}

*/




















// detection grille fond noir trait blancs qui marche
/*

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <err.h>


SDL_Surface *Surface = NULL;




// External function to resize an image while preserving aspect ratio
void resizeImage(const char* inputPath, const char* outputPath, int minSideSize) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init error: %s\n", SDL_GetError());
        return;
    }

    // Initialize SDL_image
    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
        fprintf(stderr, "IMG_Init error: %s\n", IMG_GetError());
        SDL_Quit();
        return;
    }

    // Load image
    SDL_Surface* originalSurface = IMG_Load(inputPath);
    if (!originalSurface) {
        fprintf(stderr, "Failed to load image: %s\n", IMG_GetError());
        IMG_Quit();
        SDL_Quit();
        return;
    }

    // Calculate new dimensions while preserving aspect ratio
    int newWidth, newHeight;
    if (originalSurface->w < originalSurface->h) {
        newWidth = minSideSize;
        newHeight = (int)((float)newWidth / originalSurface->w * originalSurface->h);
    } else {
        newHeight = minSideSize;
        newWidth = (int)((float)newHeight / originalSurface->h * originalSurface->w);
    }

    // Create a new surface with the calculated dimensions
    SDL_Surface* resizedSurface = SDL_CreateRGBSurfaceWithFormat(0, newWidth, newHeight,
                                                                originalSurface->format->BitsPerPixel,
                                                                originalSurface->format->format);

    // Scale the image to the new surface
    if (SDL_BlitScaled(originalSurface, NULL, resizedSurface, NULL) != 0) {
        fprintf(stderr, "SDL_BlitScaled error: %s\n", SDL_GetError());
        SDL_FreeSurface(originalSurface);
        SDL_FreeSurface(resizedSurface);
        IMG_Quit();
        SDL_Quit();
        return;
    }

    // Save the resized image
    if (SDL_SaveBMP(resizedSurface, outputPath) != 0) {
        fprintf(stderr, "SDL_SaveBMP error: %s\n", SDL_GetError());
        SDL_FreeSurface(originalSurface);
        SDL_FreeSurface(resizedSurface);
        IMG_Quit();
        SDL_Quit();
        return;
    }

    // Free surfaces and quit SDL
    SDL_FreeSurface(originalSurface);
    SDL_FreeSurface(resizedSurface);
    IMG_Quit();
    SDL_Quit();
}






int main(int argc, char *argv[]) {
    printf("toto\n\n\n\n ");
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image_path>\n", argv[0]);
        return EXIT_FAILURE;
    }
    printf("1\n\n\n\n\n");
   
    char *imagePath = argv[1];
   
   
    resizeImage(imagePath, "temp.png", 500);
   


    Surface = IMG_Load("temp.png");
    // Surface = IMG_Load(imagePath);


    if (!Surface)
    {
        errx(EXIT_FAILURE, "Failed to load image: %s", IMG_GetError());
    }
   
    printf("2\n\n\n\n\n");

    int h=Surface->h;
    int w=Surface->w;

    int tab[h][w];

    /////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////


    void recursive(int y, int x, int cpt)
    {
        //printf("%i\n", cpt);

        //printf("11111111111111111jerngoiekngoinergioenkr\n\n\n\n\n\n");
        if(x < 1 || x > w-2 || y < 1 || y > h-2)return;//pixel or de l'image



        if (tab[y][x] == 0)//le pixel appartient au fond, on le marque en visité et on arrete le parcours;
        {

            return;
        }
        if (tab[y][x] == 1)//le pixel est un bord et n'a jamais été visité, on le marque comme appartenant au trait numero cpt
                           //on rappelle la fonction sur ses 8 voisins
        {
                tab[y][x] = cpt;
               
                recursive(y-1, x-1, cpt);
                recursive(y-1, x, cpt);
                recursive(y-1, x+1, cpt);
                recursive(y, x-1, cpt);
                recursive(y+1, x-1, cpt);
                recursive(y+1, x, cpt);
                recursive(y+1, x+1, cpt);
                recursive(y, x+1, cpt);  
        }

        return;     /////////////////////////////////////////////////////////////////////////////////////////////

    }




    for (int y = 0; y < h ; y++)
    {
            for (int x = 0; x < w ; x++)
            {
                Uint8 r, g, b;
                SDL_GetRGB(*(Uint32 *)
                        ((Uint8 *)Surface->pixels + y * Surface->pitch + x *
                        Surface->format->BytesPerPixel), Surface->format, &r, &g, &b);

                if (r>200 && g>200 && b>200) //1 = contour, 0 = fond
                {
                    tab[y][x] = 1;
                }
                else tab[y][x] = 0;
            }
    }
   
    printf("3\n\n\n\n\n\n");

    int cpt = 2;//nombre de traits differents

    for (int y = 0; y < h ; y++)
    {
        for (int x = 0; x < w ; x++)
        {
            
            if (tab[y][x] == 1)//pixel de contour: appel de la fonction recursive;
            {
                recursive(y, x, cpt);
                cpt+= 1;
            }
        }
    }
    printf("cpt=%i\n",cpt);
    printf("4\n");

    // int i;
    int resTemp1 [250000];
    for (int j=0; j< 250000;j++){resTemp1[j]=0;}


    for (int y = 0; y < h ; y++)//création resTemp1
    {
        for (int x = 0; x < w ; x++)
        {

            int i = tab[y][x];

            if(i!=0)
            {
                 /*  *(Uint32 *)//sert à rien
                     ((Uint8 *)Surface->pixels + y * Surface->pitch + x *
                     Surface->format->BytesPerPixel)
                     = SDL_MapRGB(Surface->format, (i*i + 425)%255, (i*17+43)%255, (i*i*i + 1234)%255);
            
                resTemp1[i]+=1;
                // if (i==1) printf("i=%i    restemp1=%i\n",i,resTemp1[i+1]);
            }            
        }
    }
   


    for (int j=0; j< 10;j++){
        printf("%i   = %i  fois\n",j,resTemp1[j]);
    }


    int maxTemp1=0;     /////////////////////////////////////////////////////////////////////////////////////////////

    int posTemp1=0;
    for (int j=0; j<cpt+1;j++)
    {
        if (resTemp1[j]>maxTemp1){
            maxTemp1=resTemp1[j];
            posTemp1=j;     /////////////////////////////////////////////////////////////////////////////////////////////

        }
    }

    printf("max=%i\n\n",maxTemp1);

    for (int y = 0; y < h ; y++)
    {
        for (int x = 0; x < w ; x++)
        {

            if(tab[y][x]==posTemp1)
            {
                *(Uint32 *)
                    ((Uint8 *)Surface->pixels + y * Surface->pitch + x *
                    Surface->format->BytesPerPixel)
                    = SDL_MapRGB(Surface->format, 255, 0, 0);

            }           
            // else{
            //     *(Uint32 *)
            //         ((Uint8 *)Surface->pixels + y * Surface->pitch + x *
            //         Surface->format->BytesPerPixel)
            //         = SDL_MapRGB(Surface->format, 0,0,0); 
            // } 
        }
    }

    IMG_SavePNG(Surface, "out.png");
   
    return EXIT_SUCCESS;
}*/






















































#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <err.h>


SDL_Surface *Surface = NULL;




// External function to resize an image while preserving aspect ratio
void resizeImage(const char* inputPath, const char* outputPath, int minSideSize) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init error: %s\n", SDL_GetError());
        return;
    }

    // Initialize SDL_image
    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
        fprintf(stderr, "IMG_Init error: %s\n", IMG_GetError());
        SDL_Quit();
        return;
    }

    // Load image
    SDL_Surface* originalSurface = IMG_Load(inputPath);
    if (!originalSurface) {
        fprintf(stderr, "Failed to load image: %s\n", IMG_GetError());
        IMG_Quit();
        SDL_Quit();
        return;
    }

    // Calculate new dimensions while preserving aspect ratio
    int newWidth, newHeight;
    if (originalSurface->w < originalSurface->h) {
        newWidth = minSideSize;
        newHeight = (int)((float)newWidth / originalSurface->w * originalSurface->h);
    } else {
        newHeight = minSideSize;
        newWidth = (int)((float)newHeight / originalSurface->h * originalSurface->w);
    }

    // Create a new surface with the calculated dimensions
    SDL_Surface* resizedSurface = SDL_CreateRGBSurfaceWithFormat(0, newWidth, newHeight,
                                                                originalSurface->format->BitsPerPixel,
                                                                originalSurface->format->format);

    // Scale the image to the new surface
    if (SDL_BlitScaled(originalSurface, NULL, resizedSurface, NULL) != 0) {
        fprintf(stderr, "SDL_BlitScaled error: %s\n", SDL_GetError());
        SDL_FreeSurface(originalSurface);
        SDL_FreeSurface(resizedSurface);
        IMG_Quit();
        SDL_Quit();
        return;
    }

    // Save the resized image
    if (SDL_SaveBMP(resizedSurface, outputPath) != 0) {
        fprintf(stderr, "SDL_SaveBMP error: %s\n", SDL_GetError());
        SDL_FreeSurface(originalSurface);
        SDL_FreeSurface(resizedSurface);
        IMG_Quit();
        SDL_Quit();
        return;
    }

    // Free surfaces and quit SDL
    SDL_FreeSurface(originalSurface);
    SDL_FreeSurface(resizedSurface);
    IMG_Quit();
    SDL_Quit();
}






int main(int argc, char *argv[]) {
    printf("toto\n\n\n\n ");
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image_path>\n", argv[0]);
        return EXIT_FAILURE;
    }
    printf("1\n\n\n\n\n");
   
    char *imagePath = argv[1];
   
   
    resizeImage(imagePath, "temp.png", 500);
   


    Surface = IMG_Load("temp.png");
    // Surface = IMG_Load(imagePath);


    if (!Surface)
    {
        errx(EXIT_FAILURE, "Failed to load image: %s", IMG_GetError());
    }
   
    printf("2\n\n\n\n\n");

    int h=Surface->h;
    int w=Surface->w;

    int tab[h][w];

    /////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////


    void recursive(int y, int x, int cpt)
    {
        //printf("%i\n", cpt);

        //printf("11111111111111111jerngoiekngoinergioenkr\n\n\n\n\n\n");
        if(x < 1 || x > w-2 || y < 1 || y > h-2)return;//pixel or de l'image



        if (tab[y][x] == 0)//le pixel appartient au fond, on le marque en visité et on arrete le parcours;
        {

            return;
        }
        if (tab[y][x] == 1)//le pixel est un bord et n'a jamais été visité, on le marque comme appartenant au trait numero cpt
                           //on rappelle la fonction sur ses 8 voisins
        {
                tab[y][x] = cpt;
               
                recursive(y-1, x-1, cpt);
                recursive(y-1, x, cpt);
                recursive(y-1, x+1, cpt);
                recursive(y, x-1, cpt);
                recursive(y+1, x-1, cpt);
                recursive(y+1, x, cpt);
                recursive(y+1, x+1, cpt);
                recursive(y, x+1, cpt);  
        }

        return;     /////////////////////////////////////////////////////////////////////////////////////////////

    }




    for (int y = 0; y < h ; y++)
    {
            for (int x = 0; x < w ; x++)
            {
                Uint8 r, g, b;
                SDL_GetRGB(*(Uint32 *)
                        ((Uint8 *)Surface->pixels + y * Surface->pitch + x *
                        Surface->format->BytesPerPixel), Surface->format, &r, &g, &b);

                if (r<200 && g<200 && b<200) //1 = contour, 0 = fond
                {
                    tab[y][x] = 1;
                }
                else tab[y][x] = 0;
            }
    }
   
    printf("3\n\n\n\n\n\n");

    int cpt = 2;//nombre de traits differents

    for (int y = 0; y < h ; y++)
    {
        for (int x = 0; x < w ; x++)
        {
            
            if (tab[y][x] == 1)//pixel de contour: appel de la fonction recursive;
            {
                recursive(y, x, cpt);
                cpt+= 1;
            }
        }
    }
    printf("cpt=%i\n",cpt);
    printf("4\n");

    // int i;
    int resTemp1 [250000];
    for (int j=0; j< 250000;j++){resTemp1[j]=0;}


    for (int y = 0; y < h ; y++)//création resTemp1
    {
        for (int x = 0; x < w ; x++)
        {

            int i = tab[y][x];

            if(i!=0)
            {
                 /*  *(Uint32 *)//sert à rien
                     ((Uint8 *)Surface->pixels + y * Surface->pitch + x *
                     Surface->format->BytesPerPixel)
                     = SDL_MapRGB(Surface->format, (i*i + 425)%255, (i*17+43)%255, (i*i*i + 1234)%255);
            */
                resTemp1[i]+=1;
                // if (i==1) printf("i=%i    restemp1=%i\n",i,resTemp1[i+1]);
            }            
        }
    }
   


    for (int j=0; j< 10;j++){
        printf("%i   = %i  fois\n",j,resTemp1[j]);
    }


    int maxTemp1=0;     /////////////////////////////////////////////////////////////////////////////////////////////

    int posTemp1=0;
    for (int j=0; j<cpt+1;j++)
    {
        if (resTemp1[j]>maxTemp1){
            maxTemp1=resTemp1[j];
            posTemp1=j;     /////////////////////////////////////////////////////////////////////////////////////////////

        }
    }

    printf("max=%i\n\n",maxTemp1);

    for (int y = 0; y < h ; y++)
    {
        for (int x = 0; x < w ; x++)
        {

            if(tab[y][x]==posTemp1)
            {
                *(Uint32 *)
                    ((Uint8 *)Surface->pixels + y * Surface->pitch + x *
                    Surface->format->BytesPerPixel)
                    = SDL_MapRGB(Surface->format, 255, 0, 0);

            }           
            // else{
            //     *(Uint32 *)
            //         ((Uint8 *)Surface->pixels + y * Surface->pitch + x *
            //         Surface->format->BytesPerPixel)
            //         = SDL_MapRGB(Surface->format, 0,0,0); 
            // } 
        }
    }

    IMG_SavePNG(Surface, "out.png");
   
    return EXIT_SUCCESS;
}


