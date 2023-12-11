// detection grille par couleurs Clément

// fonction recherche grille 2 si longueurs pas égales

#include "grid_detect.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <err.h>



SDL_Surface *Surface = NULL;

    


void rotate(double angle,char * inputPath,int color)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        errx(EXIT_FAILURE, "Failed to initialize SDL: %s", SDL_GetError());
    }

    SDL_Surface *imageSurface = IMG_Load(inputPath);
    if (!imageSurface)
    {
        errx(EXIT_FAILURE, "Failed to load image: %s", IMG_GetError());
    }

    // int imageWidth = imageSurface->w;
    // int imageHeight = imageSurface->h;

 
    double angle_rad = angle * M_PI / 180;
    int new_width = ceil(fabs(imageSurface->w * cos(angle_rad)) + 
    fabs(imageSurface->h * sin(angle_rad)));
    int new_height = ceil(fabs(imageSurface->w * sin(angle_rad)) + 
    fabs(imageSurface->h * cos(angle_rad)));
    SDL_Surface *rotated = SDL_CreateRGBSurface(0, new_width, new_height, 
    32, 0, 0, 0, 0);

    SDL_Renderer *renderer = SDL_CreateSoftwareRenderer(rotated);
    SDL_SetRenderDrawColor(renderer, color, color, color, 255);
    SDL_RenderClear(renderer);

    SDL_Rect dstRect = {(new_width-(imageSurface->w))/2, 
    (new_height-(imageSurface->h))/2, imageSurface->w, imageSurface->h};
    SDL_RenderCopyEx(renderer, 
    SDL_CreateTextureFromSurface(renderer, imageSurface), 
    NULL, &dstRect, angle, NULL, SDL_FLIP_NONE);
    SDL_RenderPresent(renderer);

    SDL_DestroyRenderer(renderer);
    IMG_SavePNG(rotated, inputPath); 
    SDL_FreeSurface(rotated);
}


void line(float *a, float *b , float x0, float y0, float x1, float y1)
{
    if (x0!=x1)
    {
       *a = (y1-y0)/(x1-x0);
       *b =  -(*a)*x0+y0;
    }
    else
    {
       *a = (y1-y0)/(0.001); // 0.001 = différence de 1 pixel tous les 1000 pixels
       *b =  -(*a)*x0+y0;
    }    
}


// External function to resize an image while preserving aspect ratio
void resizeImage(const char* inputPath, const char* outputPath, 
int minSideSize) {
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
        newHeight = (int)((float)newWidth / originalSurface->w * 
        originalSurface->h);
    } else {
        newHeight = minSideSize;
        newWidth = (int)((float)newHeight / originalSurface->h * 
        originalSurface->w);
    }

    // Create a new surface with the calculated dimensions
    SDL_Surface* resizedSurface = 
    SDL_CreateRGBSurfaceWithFormat(0, newWidth, newHeight,
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



void grid (int *xf0,int *yf0,int *xf1,int *yf1,int *xf2,int *yf2,int *xf3,
        int *yf3,int *lf0,int *lf1,int *lf2,int *lf3)
{
    resizeImage("filtered.png", "temp.png", 700);
    Surface = IMG_Load("temp.png");
    if (!Surface) errx(EXIT_FAILURE, "Failed to load image: %s", 
    IMG_GetError());
    int h=Surface->h;
    int w=Surface->w;



    int tab[h][w];
    for (int y = 0; y < h ; y++)
    {
        for (int x = 0; x < w ; x++)
        {
            tab[y][x]=0;
        }
    }
  
    void recursive(int y, int x, int cpt)
    {

        // if(x < 2 || x > w-3 || y < 2 || y > h-3)return;//pixel hors de l'image
        if(x < 3 ||  y < 3) return;//pixel hors de l'image
        if(y >h-3 || x >w-3) return;
        if (tab[y][x] == 0) return;  //le pixel appartient au fond et on arrete le parcours;
        if (tab[y][x] == 1)//le pixel est un bord et n'a jamais été visité, on le marque comme appartenant au trait numero cpt
                           //on rappelle la fonction sur ses 8 voisins
        {
                tab[y][x] = cpt;
                recursive(y+1, x+1, cpt);
                recursive(y+1, x, cpt);
                recursive(y+1, x-1, cpt);
                recursive(y, x+1, cpt); 
                recursive(y, x-1, cpt);
                recursive(y-1, x+1, cpt);
                recursive(y-1, x, cpt);
                recursive(y-1, x-1, cpt);
        }
        return;  
    }

    for (int y = 1; y < h-1 ; y++)
    {
            for (int x = 1; x < w-1 ; x++)
            {
                Uint8 r, g, b;
                SDL_GetRGB(*(Uint32 *)
                        ((Uint8 *)Surface->pixels + y * Surface->pitch + x *
                        Surface->format->BytesPerPixel), 
                        Surface->format, &r, &g, &b);

                if (r>200 && g>200 && b>200) tab[y][x] = 1; //1 = contour, 0 = fond
                else tab[y][x] = 0;
            }
    }
 
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
 
    int resTemp1 [250000];
    for (int j=0; j< 250000;j++){resTemp1[j]=0;}


    for (int y = 0; y < h ; y++)//création resTemp1
    {
        for (int x = 0; x < w ; x++)
        {
            int i = tab[y][x];
            if(i!=0) resTemp1[i]+=1;            
        }
    }
   

    int maxTemp1=0;    
    int posTemp1=0;

    int maxTemp2=0;    
    int posTemp2=0;

    int maxTemp3=0;    
    int posTemp3=0;

    int maxTemp4=0;    
    int posTemp4=0;
 
    for (int j=0; j<(cpt+1);j++)
    {
        if (resTemp1[j]>maxTemp1)
        {
            maxTemp4=maxTemp3;
            maxTemp3=maxTemp2;
            maxTemp2=maxTemp1;
            maxTemp1=resTemp1[j];

            posTemp4=posTemp3;
            posTemp3=posTemp2;
            posTemp2=posTemp1;
            posTemp1=j;     
        }
        else
        {
            if (resTemp1[j]>maxTemp2)
            {
                maxTemp4=maxTemp3;
                maxTemp3=maxTemp2;                
                maxTemp2=resTemp1[j];
                
                posTemp4=posTemp3;
                posTemp3=posTemp2;
                posTemp2=j;  
            }
            else
            {
                if (resTemp1[j]>maxTemp3)
                {
                    maxTemp4=maxTemp3;
                    maxTemp3=resTemp1[j];
                   
                    posTemp4=posTemp3;
                    posTemp3=j;  
                }
                else
                {
                    if (resTemp1[j]>maxTemp4)
                    {
                        maxTemp4=resTemp1[j];
                        posTemp4=j;  
                    }
                } 
            }
        }
    }

    for (int y = 0; y < h ; y++)
    {
        for (int x = 0; x < w ; x++)
        {

            if(tab[y][x]==posTemp1)
            {
                *(Uint32 *)
                    ((Uint8 *)Surface->pixels + y * Surface->pitch + x *
                    Surface->format->BytesPerPixel)
                    = SDL_MapRGB(Surface->format, 0, 255, 0);

            }           

            else if(tab[y][x]==posTemp2)
            {
                *(Uint32 *)
                    ((Uint8 *)Surface->pixels + y * Surface->pitch + x *
                    Surface->format->BytesPerPixel)
                    = SDL_MapRGB(Surface->format, 255, 0, 0);
            }
            else if(tab[y][x]==posTemp3)
            {
                *(Uint32 *)
                    ((Uint8 *)Surface->pixels + y * Surface->pitch + x *
                    Surface->format->BytesPerPixel)
                    = SDL_MapRGB(Surface->format, 0, 0, 255);
            }
            else if(tab[y][x]==posTemp4)
            {
                *(Uint32 *)
                    ((Uint8 *)Surface->pixels + y * Surface->pitch + x *
                    Surface->format->BytesPerPixel)
                    = SDL_MapRGB(Surface->format, 255, 255, 0);
            }
        }
    }


    int countPixels (float slope,float y_intercept,int xy)
    {
        int count=0;
        if (xy==0) // line detection
        {
            for (int x=0; x<w-2;x++)
            {
                int y=slope*x+y_intercept;
                if (y>0 && y<h-1)
                {
                    if (tab[y][x]==posTemp1) count+=1;
                }
                
            }
        }
        else //column detection
        {
            for (int y=0; y<h-2;y++)
            {
                int x=(y-y_intercept)/slope;
                if (x>0 && x<w-1)
                {
                    if (tab[y][x]==posTemp1) count+=1;
                }
                
            }
        }
        return count;
    }

    // coordonates[0]=ligne haut    (1er ligne)
    // coordonates[9]=ligne bas     (10ème ligne)
    // coordonates[][0]=slope
    // coordonates[][1]=y_intercept
    // coordonates[][2]=nb pixels trouvés sur la droite
    // oordonates[][3]= valeur y du 1er pixel trouvé
    // coordonates[10]=ligne colonne gauche    (1er ligne)
    // coordonates[19]=ligne colonne droite    (10ème ligne)

    float coordonates[20][3]; 
    for (int a=0;a<20;a++)
    {
        for (int b=0;b<3;b++) coordonates[a][b]=-999;
    }

    int x0=-1;
    int y0=-1;
    int x1=-1;
    int y1=-1;
    int x2=-1;
    int y2=-1;
    int x3=-1;
    int y3=-1;

    int l0=0; // longueur ligne haut
    int l1=0; // longueur ligne droite
    int l2=0; // longueur ligne bas
    int l3=0; // longueur ligne gauche

    float slope = 1;
    float y_intercept=0;
    float *a=&slope;
    float *b=&y_intercept;
    // y = a x + b

    void printLines()
    {
        slope=coordonates[0][0];
        y_intercept=coordonates[0][1];
        for (int xx=0; xx<w-2;xx++)
        {
            int yy=0;
            yy=slope*xx+y_intercept;
            if (yy>0 && yy<h-2)
            {
                *(Uint32 *)
                    ((Uint8 *)Surface->pixels + yy * Surface->pitch + xx *
                    Surface->format->BytesPerPixel)
                    = SDL_MapRGB(Surface->format, 255, 0, 0);
            }
            
        }


        slope=coordonates[9][0];
        y_intercept=coordonates[9][1];
        for (int xx=0; xx<w-2;xx++)
        {
            int yy=0;
            yy=slope*xx+y_intercept;
            if (yy>0 && yy<h-2)
            {
                *(Uint32 *)
                    ((Uint8 *)Surface->pixels + yy * Surface->pitch + xx *
                    Surface->format->BytesPerPixel)
                    = SDL_MapRGB(Surface->format, 255, 0, 0);
            }
        }

        slope=coordonates[10][0];
        y_intercept=coordonates[10][1];
        for (int yy=0; yy<h-2;yy++)
        {
            int xx=0;
            xx=(yy-y_intercept)/slope;
            if (xx>0 && xx<w-2)
            {
                *(Uint32 *)
                    ((Uint8 *)Surface->pixels + yy * Surface->pitch + xx *
                    Surface->format->BytesPerPixel)
                    = SDL_MapRGB(Surface->format, 255, 0, 0);
            }
        } 
    
        slope=coordonates[19][0];
        y_intercept=coordonates[19][1];
        for (int yy=0; yy<h-2;yy++)
        {
            int xx=0;
            xx=(yy-y_intercept)/slope;
            if (xx>0 && xx<w-2)
            {
                *(Uint32 *)
                    ((Uint8 *)Surface->pixels + yy * Surface->pitch + xx *
                    Surface->format->BytesPerPixel)
                    = SDL_MapRGB(Surface->format, 255, 0, 0);
            }
        } 
    IMG_SavePNG(Surface, "out.png");
    }

    void upperLine()
    {
    // détection en haut
        y0=0;
        x0=0;
        x1=w-1;
        y1=0;
        int l=1;
        while (l==1)
        {
            int yy_grid=0;
            int xx_grid=0;
            int is_grid=0;
            int xx=0;
            while (xx<w-1)
            {
                if (tab[y0][xx]==posTemp1 && tab[y0+1][xx]==posTemp1) 
                {
                    is_grid=1;
                    yy_grid=y0;
                    xx_grid=xx;
                    xx=w;
                }
                xx+=1;
            }

            
            if (is_grid ==1) // détection d'un pixel de la grille
            {
                int count=0;
                int orientation=-1; // pour savoir si max à gauche ou à droite
                int yy=yy_grid; 
                int yend=yy_grid+200;
                int max=0;
                int ypos=0;
                while (yy<yend) //on cherche la droite de la grille sur un angle de 45° a gauche et à droite (200 pixels)
                {
                    line (&slope,&y_intercept,xx_grid-200,yy,xx_grid,yy_grid); 
                    count= countPixels(slope,y_intercept,0);
                    if (count>max)
                    {
                        max=count;
                        ypos=yy;
                        orientation=1;
                    }
                    line (&slope,&y_intercept,xx_grid+200,yy,xx_grid,yy_grid); 
                    count= countPixels(slope,y_intercept,0);
                    if (count>max)
                    {
                        max=count;
                        ypos=yy;
                        orientation=0;
                    }
                    yy+=1;

                }
                if (orientation)
                {
                    x1=xx_grid;
                    y1=yy_grid;
                    x0=xx_grid-200;
                    y0=ypos;
                }
                else
                {
                    x1=xx_grid+200;
                    y1=ypos;
                    x0=xx_grid;
                    y0=yy_grid;
                }

                line (&slope,&y_intercept,x0,y0,x1,y1);
                coordonates[0][0]=slope;
                coordonates[0][1]=y_intercept;
                coordonates[0][2]=max;
                l=0; 
            }
            else
            {
                y0+=1;
                if (y0>h-71) l=0;
            }  
        }
    }

    void lowerLine()
    {
        // détection en bas
        y2=h-1;
        x2=w-1;
        y3=h-1;
        x3=0;
        int l=1;
        while (l==1)
        {
            int yy_grid=0;
            int xx_grid=0;
            int is_grid=0;
            int xx=0;
            while (xx<w-1)
            {
                if (tab[y3][xx]==posTemp1 && tab[y3+1][xx]==posTemp1) 
                {
                    is_grid=1;
                    yy_grid=y3;
                    xx_grid=xx;
                    xx=w;
                }
                xx+=1;
            }

            
            if (is_grid ==1) // détection d'un pixel de la grille
            {
                int count=0;
                int orientation=-1; // pour savoir si max à gauche ou à droite
                int yy=yy_grid; 
                int yend=yy_grid-200;
                int max=0;
                int ypos=0;
                while (yy>yend) //on cherche la droite de la grille sur un angle de 45° a gauche et à droite (200 pixels)
                {
                    line (&slope,&y_intercept,xx_grid-200,yy,xx_grid,yy_grid); 
                    count= countPixels(slope,y_intercept,0);
                    if (count>max)
                    {
                        max=count;
                        ypos=yy;
                        orientation=1;
                    }
                    line (&slope,&y_intercept,xx_grid+200,yy,xx_grid,yy_grid); 
                    count= countPixels(slope,y_intercept,0);
                    if (count>max)
                    {
                        max=count;
                        ypos=yy;
                        orientation=0;
                    }
                    yy-=1;

                }
                if (orientation)
                {
                    x2=xx_grid;
                    y2=yy_grid;
                    x3=xx_grid-200;
                    y3=ypos;
                }
                else
                {
                    x2=xx_grid+200;
                    y2=ypos;
                    x3=xx_grid;
                    y3=yy_grid;
                }

                line (&slope,&y_intercept,x3,y3,x2,y2);
                coordonates[9][0]=slope;
                coordonates[9][1]=y_intercept;
                coordonates[9][2]=max;
                l=0; 
            }
            else
            {
                y3-=1;
                if (y3<70) l=0;
            }  
        }

    }

    void leftLine()
    {
    // détection droite du coté gauche
        y0=0;
        x0=0;
        y3=h-1;
        x3=0;
        int l=1;
        while (l==1)
        {
            int yy_grid=0;
            int xx_grid=0;
            int is_grid=0;
            int yy=0;
            while (yy<h-1)
            {
                if (tab[yy][x0]==posTemp1 && tab[yy][x0+1]==posTemp1) 
                {
                    is_grid=1;
                    yy_grid=yy;
                    xx_grid=x0;
                    yy=h;
                }
                yy+=1;
            }

            if (is_grid ==1) // détection d'un pixel de la grille
            {
                int count=0;
                int orientation=-1; // pour savoir si max à gauche ou à droite
                int xx=xx_grid; 
                int xend=xx_grid+200;
                int max=0;
                int xpos=0;
                while (xx<xend) //on cherche la droite de la grille sur un angle de 45° au dessus et en dessous (200 pixels)
                {
                    line (&slope,&y_intercept,xx,yy_grid-200,xx_grid,yy_grid); 
                    count= countPixels(slope,y_intercept,1);
                    if (count>max)
                    {
                        max=count;
                        xpos=xx;
                        orientation=1;
                    }
                    line (&slope,&y_intercept,xx,yy_grid+200,xx_grid,yy_grid); 
                    count= countPixels(slope,y_intercept,1);
                    if (count>max)
                    {
                        max=count;
                        xpos=xx;
                        orientation=0;
                    }
                    xx+=1;
                }
                if (orientation)
                {
                    x3=xx_grid;
                    y3=yy_grid;
                    x0=xpos;
                    y0=yy_grid-200;
                }
                else
                {
                    x0=xx_grid;
                    y0=yy_grid;
                    x3=xpos;
                    y3=yy_grid+200;
                }
                line (&slope,&y_intercept,x0,y0,x3,y3);
                coordonates[10][0]=slope;
                coordonates[10][1]=y_intercept;
                coordonates[10][2]=max;
                l=0; 
            }
            else
            {
                x0+=1;
                if (x0>w-71) l=0;
            }  
        }
    }

    void rightLine()
    {
    // détection droite du coté droit
        y1=0;
        x1=w-1;
        y2=h-1;
        x2=w-1;
        int l=1;
        while (l==1)
        {
            int yy_grid=0;
            int xx_grid=0;
            int is_grid=0;
            int yy=0;
            while (yy<h-1)
            {
                if (tab[yy][x1]==posTemp1 && tab[yy][x1+1]==posTemp1) 
                {
                    is_grid=1;
                    yy_grid=yy;
                    xx_grid=x1;
                    yy=h;
                }
                yy+=1;
            }

            if (is_grid ==1) // détection d'un pixel de la grille
            {
                int count=0;
                int orientation=-1; // pour savoir si max à gauche ou à droite
                int xx=xx_grid; 
                int xend=xx_grid-200;
                int max=0;
                int xpos=0;
                while (xx>xend) //on cherche la droite de la grille sur un angle de 45° au dessus et en dessous (200 pixels)
                {
                    line (&slope,&y_intercept,xx,yy_grid-200,xx_grid,yy_grid); 
                    count= countPixels(slope,y_intercept,1);
                    if (count>max)
                    {
                        max=count;
                        xpos=xx;
                        orientation=1;
                    }
                    line (&slope,&y_intercept,xx,yy_grid+200,xx_grid,yy_grid); 
                    count= countPixels(slope,y_intercept,1);
                    if (count>max)
                    {
                        max=count;
                        xpos=xx;
                        orientation=0;
                    }
                    xx-=1;
                }
                if (orientation)
                {
                    x2=xx_grid;
                    y2=yy_grid;
                    x1=xpos;
                    y1=yy_grid-200;
                }
                else
                {
                    x1=xx_grid;
                    y1=yy_grid;
                    x2=xpos;
                    y2=yy_grid+200;
                }


                line (a,b,x1,y1,x2,y2);
                coordonates[19][0]=slope;
                coordonates[19][1]=y_intercept;
                coordonates[19][2]=max;
                l=0;
            }
            else
            {
                x1-=1;
                if (x1<70) l=0;
            }  
        }
    }

    int colorCheck()
    {
        float l0l1=(float) l0/ (float) l1;
        float l0l2=(float)l0/l2;
        float l0l3=(float)l0/l3;
        float l1l2=(float)l1/l2;
        float l1l3=(float)l1/l3;
        float l2l3=(float)l2/l3;

        int verif = 0;
        float inf=0.8;
        float sup=1.2;
        if (l0l1 < inf || l0l1 > sup) verif =1;
        if (l0l2 < inf || l0l2 > sup) verif =1;
        if (l0l3 < inf || l0l3 > sup) verif =1;
        if (l1l2 < inf || l1l2 > sup) verif =1;
        if (l1l3 < inf || l1l3 > sup) verif =1;
        if (l2l3 < inf || l2l3 > sup) verif =1;

        if (verif==1) //non detection grille
        {
            posTemp1=posTemp2; 
            posTemp2=posTemp3; 
            posTemp3=posTemp4; 
            posTemp4=-1;

            if (posTemp1==-1)
            {
                    printf ("Grid not detected!");
                    return 2; // = grille non détectée
            }
            return 1; // = on doit relancer la recherche sur le max suivant 
        }
        else return 0; // OK
    }

    void angleCheck()
    {
                
        float s0=(coordonates[0][0]+coordonates[9][0])/2;
        int angle=atan(s0)/M_PI*180;
        if (angle>4)angle+=1;
        if (angle<-4)angle-=1;    
        
        if (angle>4||angle<-4)
        {
            // SDL_Surface *Original = IMG_Load("original.png");
            rotate(-angle,"original.png",255); //color =255 (blanc pour image)
            SDL_Surface *tempOriginal=IMG_Load("original.png"); // image agrandie qui doit être rognée
            


            SDL_Surface *Filtered = IMG_Load("filtered.png");
            int h0=Filtered->h;
            int w0=Filtered->w;
            SDL_FreeSurface(Filtered);

            rotate(-angle,"filtered.png",0); //color =0 (noir pour image filtrée)
            SDL_Surface *tempFiltered = IMG_Load("filtered.png"); // image agrandie qui doit être rognée
            int h1=tempFiltered->h;
            int w1=tempFiltered->w;
            int xx=(w1-w0)/2;
            int yy=(h1-h0)/2;

            SDL_Surface *newImageFiltered = 
            SDL_CreateRGBSurface(0, w0, h0, 32, 0, 0, 0, 0);

            SDL_Surface *newImageOriginal = 
            SDL_CreateRGBSurface(0, w0, h0, 32, 0, 0, 0, 0);
            for (int y = 1; y < h0-1 ; y++)
                {
                        for (int x = 1; x < w0-1 ; x++)
                        {
                            Uint8 r, g, b;

                            SDL_GetRGB(*(Uint32 *)
                                    ((Uint8 *)tempFiltered->pixels + 
                                    (y+yy) * tempFiltered->pitch + (x+xx) *
                                    tempFiltered->format->BytesPerPixel), 
                                    tempFiltered->format, &r, &g, &b);

                            *(Uint32 *)
                                ((Uint8 *)newImageFiltered->pixels + y * 
                                newImageFiltered->pitch + x *
                                newImageFiltered->format->BytesPerPixel)
                                = SDL_MapRGB(newImageFiltered->format, r, g, b)
                                ;



                            SDL_GetRGB(*(Uint32 *)
                                    ((Uint8 *)tempOriginal->pixels + 
                                    (y+yy) * tempOriginal->pitch + (x+xx) *
                                    tempOriginal->format->BytesPerPixel), 
                                    tempOriginal->format, &r, &g, &b);

                            *(Uint32 *)
                                ((Uint8 *)newImageOriginal->pixels + y * 
                                newImageOriginal->pitch + x *
                                newImageOriginal->format->BytesPerPixel)
                                = SDL_MapRGB(newImageOriginal->format, r, g, b)
                                ;
                        }
                }
            IMG_SavePNG(newImageFiltered, "filtered.png");
            IMG_SavePNG(newImageOriginal, "original.png");  

            SDL_FreeSurface(newImageFiltered);
            SDL_FreeSurface(newImageOriginal);
            for (int y = 0; y < h ; y++)
                {for (int x = 0; x < w ; x++) {tab[y][x]=0;}}
            for (int a=0;a<20;a++)
                {for (int b=0;b<3;b++) coordonates[a][b]=-999;}
            grid (&x0,&y0,&x1,&y1,&x2,&y2,&x3,&y3,
                    &l0,&l1,&l2,&l3);
        }
    }

    void parallelCheck()
    {
        void aux (int *xx,int *yy,float s0,float s1,float y0_intercept,
        float y1_intercept)    // calcul les coordonnées d'intersection de deux droites
        {
            float x=(y1_intercept-y0_intercept)/(s0-s1);
            *xx=(int)x;
            float y=s0*x+y0_intercept;
            *yy=(int)y;
        }

        int aux1(int x0,int y0,int x1, int y1) //calcul la distance entre deux points
        {
            float res= sqrt((x1-x0)*(x1-x0)+(y1-y0)*(y1-y0));
            return (int) res;
        }
        
        void calculateCoordonates()
        {
            int x=0; //utilisé pour déterminer l'intersection des droites
            int y=0;
            if (coordonates[0][0]!=-999 && coordonates[10][0]!=-999) 
            {
                aux(&x,&y,coordonates[0][0],coordonates[10][0],
                coordonates[0][1],coordonates[10][1]);
                x0=x;
                y0=y;
            }
            if (coordonates[0][0]!=-999 && coordonates[19][0]!=-999) 
            {
                aux(&x,&y,coordonates[0][0],coordonates[19][0],
                coordonates[0][1],coordonates[19][1]);
                x1=x;
                y1=y;
            }
            if (coordonates[9][0]!=-999 && coordonates[19][0]!=-999) 
            {
                aux(&x,&y,coordonates[9][0],coordonates[19][0],
                coordonates[9][1],coordonates[19][1]);
                x2=x;
                y2=y;
            }
            if (coordonates[9][0]!=-999 && coordonates[10][0]!=-999) 
            {
                aux(&x,&y,coordonates[9][0],coordonates[10][0],
                coordonates[9][1],coordonates[10][1]);
                x3=x;
                y3=y;
            }

            if ((x0>-1))
            {
                if (x1>-1) l0=aux1(x0,y0,x1,y1);
                if (x3>-1) l3=aux1(x3,y3,x0,y0);
            }
            if ((x2>-1))
            {
                if (x1>-1) l1=aux1(x1,y1,x2,y2);       
                if (x3>-1) l2=aux1(x3,y3,x2,y2);
            }
        }
  
        upperLine();
        lowerLine();
        leftLine();
        rightLine();
        calculateCoordonates();       

        float max0=coordonates[0][2];
        float max9=coordonates[9][2];
        float s0=coordonates[0][0];
        float s9=coordonates[9][0];

        float max10=coordonates[10][2];
        float max19=coordonates[19][2];
        float s10=coordonates[10][0];
        float s19=coordonates[19][0];

        int l=1; // utilisé pour vérifié que les droites sont parallèles
        int r=1;
        int u=1;
        int d=1;

        // check upper and lower 
        if (s0<0) s0*=(-1);
        if (s9<0) s9*=(-1);
        float diff1=s0-s9;
        if (diff1<0) diff1*=(-1);
        if (diff1>0.05)
        {
            if (max0<100 && max9>100)
            {
                coordonates[0][0]=0;
                coordonates[0][1]=0;
                u=0;
            }
            else if (max0>100 && max9<100)
            {
                coordonates[9][0]=0;
                coordonates[9][1]=0;
                d=0;
            }
        }

        // check left and right 
        if (s10<0) s10*=(-1);
        if (s19<0) s19*=(-1);
        if (s10<30 || s19<30)  // pente <30 pixel = peu vertical
        {
            if (max10<100 && max19>100)
            {
                coordonates[10][0]=0;
                coordonates[10][1]=0;
                l=0;
            }
            else if (max10>100 && max19<100)
            {
                coordonates[19][0]=0;
                coordonates[19][1]=0;
                r=0;
            }
        }

        if (u==0 && d==1) // ligne du haut incorrecte ==> détermination avec longueur bas
        {
            int p=0;
            float a1=coordonates[10][0];
            float b1=coordonates[10][1];
            int yy=y3;
            int xx=x3;
            while (l2-p>0)
            {
                yy-=1;
                xx= (int)(yy-b1)/a1;
                p=aux1(xx,yy,x3,y3);
            }
            x0=xx;
            y0=yy;

            p=0;
            a1=coordonates[19][0];
            b1=coordonates[19][1];
            yy=y2;
            xx=x2;
            while (l2-p>0)
            {
                yy-=1;
                xx= (int)(yy-b1)/a1;
                p=aux1(xx,yy,x2,y2);
            }
            x1=xx;
            y1=yy;
            if (y0<0 || y1<0) // impossible car au delà écran 
            {
                line (a,b,x3,y3-2,x2,y2-2); // valeur bidon pour que les longueurs soient petites
                coordonates[9][0]=slope;
                coordonates[9][1]=y_intercept;
                coordonates[9][2]=-1;
            }
            else
            {
            line (a,b,x0,y0,x1,y1);
            coordonates[0][0]=slope;
            coordonates[0][1]=y_intercept;
            coordonates[0][2]=-1;
            }
        }

        if (u==1 && d==0) // ligne du bas incorrecte ==> détermination avec longueur haut
        {
            int p=0;
            float a1=coordonates[10][0];
            float b1=coordonates[10][1];
            int yy=y0;
            int xx=x0;
            while (l0-p>0)
            {
                yy+=1;
                xx= (int)(yy-b1)/a1;
                p=aux1(xx,yy,x0,y0);
            }
            x3=xx;
            y3=yy;

            p=0;
            a1=coordonates[19][0];
            b1=coordonates[19][1];
            yy=y1;
            xx=x1;
            while (l0-p>0)
            {
                yy+=1;
                xx= (int)(yy-b1)/a1;
                p=aux1(xx,yy,x1,y1);
            }
            x2=xx;
            y2=yy;

            if (y2>h || y3>h) // impossible car au delà écran 
            {
                line (a,b,x0,y0+2,x1,y1+2); // valeur bidon pour que les longueurs soient petites
                coordonates[9][0]=slope;
                coordonates[9][1]=y_intercept;
                coordonates[9][2]=-1;
            }
            else
            {
            line (a,b,x3,y3,x2,y2);
            coordonates[9][0]=slope;
            coordonates[9][1]=y_intercept;
            coordonates[9][2]=-1;
            }
        }

        if (l==0 && r==1) // ligne de gauche incorrecte ==> détermination avec longueur droite
        {
            int p=0;
            float a1=coordonates[0][0];
            float b1=coordonates[0][1];
            int yy=y1;
            int xx=x1;
            while (l1-p>0)
            {
                xx-=1;
                yy= (int)(xx*a1+b1);
                p=aux1(xx,yy,x1,y1);
            }
            x0=xx;
            y0=yy;

            p=0;
            a1=coordonates[9][0];
            b1=coordonates[9][1];
            yy=y2;
            xx=x2;
            while (l1-p>0)
            {
                xx-=1;
                yy= (int)(xx*a1+b1);
                p=aux1(xx,yy,x2,y2);
            }
            x3=xx;
            y3=yy;

            if (x0<0 || x3<0) // impossible car au delà écran 
            {
                line (a,b,x1-2,y1,x2-2,y2); // valeur bidon pour que les longueurs soient petites
                coordonates[9][0]=slope;
                coordonates[9][1]=y_intercept;
                coordonates[9][2]=-1;
            }
            else
            {
            line (a,b,x0,y0,x3,y3);
            coordonates[10][0]=slope;
            coordonates[10][1]=y_intercept;
            coordonates[10][2]=-1;
            }
        }

        if (l==1 && r==0) // ligne de droite incorrecte ==> détermination avec longueur gauche
        {
            int p=0;
            float a1=coordonates[0][0];
            float b1=coordonates[0][1];
            int yy=y0;
            int xx=x0;
            while (l3-p>0)
            {
                xx+=1;
                yy= (int)(xx*a1+b1);
                p=aux1(xx,yy,x0,y0);
            }

            x1=xx+4;
            y1=yy;
            
            p=0;
            a1=coordonates[9][0];
            b1=coordonates[9][1];
            yy=y3;
            xx=x3;
            while (l3-p>0)
            {
                xx+=1;
                yy= (int)(xx*a1+b1);
                p=aux1(xx,yy,x3,y3);
            }
            x2=xx+4;
            y2=yy;

            if (x1>w || x2>w) // impossible car au delà écran 
            {
                line (a,b,x0+2,y0,x3+2,y3); // valeur bidon pour que les longueurs soient petites
                coordonates[9][0]=slope;
                coordonates[9][1]=y_intercept;
                coordonates[9][2]=-1;
            }
            else
            {
            line (&slope,&y_intercept,x1,y1,x2,y2);
            coordonates[19][0]=slope;
            coordonates[19][1]=y_intercept;
            coordonates[19][2]=-1;
            }
        }
        
        
        calculateCoordonates();

        int verification = colorCheck(); // verification des maxima de couleur

        if (verification==1) parallelCheck(); // test la couleur maxi suivante
        else if (verification==2) return; // grille non détectée
        else angleCheck();
        
        if (x0<1)x0=1;
        if (x1<1)x1=1;
        if (x2<1)x2=1;
        if (x3<1)x3=1;
        if (x0>w-1) x0=w-1;
        if (x1>w-1) x1=w-1;
        if (x2>w-1) x2=w-1;
        if (x3>w-1) x3=w-1;
        if (y0<1)y0=1;
        if (y1<1)y1=1;
        if (y2<1)y2=1;
        if (y3<1)y3=1;
        if (y0>h-1)y0=h-1;
        if (y1>h-1)y1=h-1;
        if (y2>h-1)y2=h-1;
        if (y3>h-1)y3=h-1;


        *xf0=x0;
        *yf0=y0;
        *xf1=x1;
        *yf1=y1;
        *xf2=x2;
        *yf2=y2;
        *xf3=x3;
        *yf3=y3;
        *lf0=l0;
        *lf1=l1;
        *lf2=l2;
        *lf3=l3;   
    }

    parallelCheck();

    printLines();


//     printf("coordonates depuis detect\n");
//     for (int i=0; i<20;i++)
// {    printf("coordonates %i=%f\n",i,coordonates[i][0]);
// }

    *xf0=x0;
    *yf0=y0;
    *xf1=x1;
    *yf1=y1;
    *xf2=x2;
    *yf2=y2;
    *xf3=x3;
    *yf3=y3;
    *lf0=l0;
    *lf1=l1;
    *lf2=l2;
    *lf3=l3;   
}



