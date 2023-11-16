#include "rotation.h"

SDL_Surface *Surface = NULL;
int angl = 0;

void saveRotatedImage(const char *outputPath)
{
    IMG_SavePNG(Surface, outputPath);
    printf("Rotated image saved to: %s\n", outputPath);
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        errx(EXIT_FAILURE, "more arguments needed");
    }

    char *imagePath = argv[1];
    int angle = atoi(argv[2]);

    // Charger l'image
    Surface = IMG_Load(imagePath);
    if (!Surface)
    {
        errx(EXIT_FAILURE, "Failed to load image: %s", IMG_GetError());
    }

    Surface = rotate(Surface, angle);

    saveRotatedImage(argv[3]);

    return 0;
}
