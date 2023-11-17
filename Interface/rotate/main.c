#include "rotation.h"
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        errx(EXIT_FAILURE, "3 parameters are required: image path and angle");
    }

    char *imagePath = argv[1];
    int angle = atoi(argv[2]);

    initSDL(imagePath);
    render();

    int rotationPerformed = 0;

    int quit = 0;
    while (!quit)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = 1;
            }
        }

        if (!rotationPerformed)
        {
            handleEvents(angle);
            rotationPerformed = 1;
        }
    }

    cleanup();

    return 0;
}