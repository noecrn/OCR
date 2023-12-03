#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "grid_detect.h"




int main(int argc, char *argv[])
{
    int x0=-1;
    int y0=-1;
    int x1=-1;
    int y1=-1;
    int x2=-1;
    int y2=-1;
    int x3=-1;
    int y3=-1;
    int l0=-1;
    int l1=-1;
    int l2=-1;
    int l3=-1;

    grid (&x0,&y0,&x1,&y1,&x2,&y2,&x3,&y3,&l0,&l1,&l2,&l3,argv[1]);


    printf("MAIN      ###########################\n");
    printf("x0=%i    y0=%i\n",x0,y0);
    printf("x1=%i    y1=%i\n",x1,y1);
    printf("x2=%i    y2=%i\n",x2,y2);
    printf("x3=%i    y3=%i\n",x3,y3);


    printf("l0=%i\n",l0);    
    printf("l1=%i\n",l1);
    printf("l2=%i\n",l2);
    printf("l3=%i\n",l3);


    return EXIT_SUCCESS;
}
