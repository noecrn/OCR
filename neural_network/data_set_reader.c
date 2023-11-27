#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdint.h>

#include "data_set_reader.h"



// Fonction pour initialiser la structure Image à partir d'une chaîne de caractères
struct Image *initImage(char *line) {
    // Allocation de la structure Image
    struct Image *img = (struct Image *)malloc(sizeof(struct Image));
    if (img == NULL) {
        perror("Erreur d'allocation de mémoire pour la structure Image");
        exit(EXIT_FAILURE);
    }

    // Utilisation de strtok pour diviser la chaîne en éléments
    char *token = strtok(line, ",");

    // Allocation et copie de la chaîne pour l'attribut font
    img->font = strdup(token);
    if (img->font == NULL) {
        perror("Erreur d'allocation de mémoire pour l'attribut font");
        exit(EXIT_FAILURE);
    }

    // Conversion de la chaîne en entier pour l'attribut label
    token = strtok(NULL, ",");
    img->label = atoi(token);

    // Allocation de mémoire pour l'attribut pixels
    img->pixels = (int *)malloc(sizeof(int));
    if (img->pixels == NULL) {
        perror("Erreur d'allocation de mémoire pour l'attribut pixels");
        exit(EXIT_FAILURE);
    }

    // Remplissage de l'attribut pixels avec les valeurs converties
    int i = 0;
    while ((token = strtok(NULL, ",")) != NULL) {
        img->pixels[i++] = atoi(token);
        img->pixels = (int *)realloc(img->pixels, (i + 1) * sizeof(int));
        if (img->pixels == NULL) {
            perror("Erreur de réallocation de mémoire pour l'attribut pixels");
            exit(EXIT_FAILURE);
        }
    }

    return img;
}

// Fonction pour libérer la mémoire allouée à la structure Image
void freeImage(struct Image *img) {
    free(img->font);
    free(img->pixels);
    free(img);
}


//struct Image *processCSVLine(char *ligne)
//{
	//struct Image *res = malloc(sizeof(struct Image));
	//res->font = malloc(50*sizeof(char));
	//res->pixels = malloc(784*sizeof(int));

	//char *token = strtok(ligne, ",");

	//res->font = token;
	//res->label =*token-'0';
	//while(token)
	//{
	//	res->pixels = *token;
	//	token++;
	//}
	//return res;

//}

//void image_free(struct image *image)
//{
//	free(image->font);
//	free(image->pixels);
//}


/*void createJPEG(const char *filename, int *pixels) {
    // Ouvrir le fichier pour écriture binaire
    FILE *file = fopen(filename, "wb");
    if (!file) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s\n", filename);
        return;
    }

    // Initialiser la structure JPEG
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);
    jpeg_stdio_dest(&cinfo, file);

    // Paramètres de l'image
    cinfo.image_width = WIDTH;
    cinfo.image_height = HEIGHT;
    cinfo.input_components = 3;
    cinfo.in_color_space = JCS_RGB;

    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, 90, TRUE);

    // Début de l'écriture
    jpeg_start_compress(&cinfo, TRUE);

    // Écriture des pixels dans l'image
    JSAMPLE *row = (JSAMPLE *)malloc(3 * WIDTH * sizeof(JSAMPLE));
    JSAMPROW rows[1];
    rows[0] = row;

    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            int pixelValue = pixels[y * WIDTH + x];
            
            // Conversion de la valeur du pixel en RGB
            row[3 * x] = row[3 * x + 1] = row[3 * x + 2] = (JSAMPLE)pixelValue;
        }

        // Écrire une ligne d'image
        jpeg_write_scanlines(&cinfo, rows, 1);
    }

    // Fin de l'écriture
    jpeg_finish_compress(&cinfo);
    fclose(file);

    // Libérer la mémoire
    free(row);
    jpeg_destroy_compress(&cinfo);
}*/


void print_pixels(int *pixels)
{
	for(size_t i = 0; i < 784; i++) printf("%d,", pixels[i]);
	printf("\n");
}


void data(int numTraining, int numTesting, double **training, double *expectedTrain, double **testing, double *expectedTest)
{
    /*if(numTraining+numTesting > 29000)
    {
	    fprintf(stderr, "database <= 29000\n");
	    return;
    }*/

    FILE *file = fopen(DATASET, "r");
    char line[5000];
    fgets(line, sizeof(line), file);

    // Allocation dynamique pour chaque tableau d'entiers
    for (int i = 0; i < numTraining%29000; ++i) 
    {
	fgets(line, sizeof(line), file);
	struct Image *img = initImage(line);
        training[i] = (double *)malloc(784 * sizeof(double));

        // Vérification si l'allocation de mémoire a réussi
        if (training[i] == NULL) {
            fprintf(stderr, "Erreur d'allocation de mémoire pour le tableau %d.\n", i);
            return; // Quitter le programme avec un code d'erreur
        }

        // Initialisation des valeurs (vous pouvez le faire selon vos besoins)
    for(size_t j = 0; j < 784; j++)
    {
        training[i][j] = (double)(img->pixels[j]) / 255;
    }
	expectedTrain[i] = (double)img->label;
	free(img);
    }

    // Allocation dynamique pour chaque tableau d'entiers
    for (int i = 0; i < numTesting%29000; ++i) 
    {
	fgets(line, sizeof(line), file);
        struct Image *img = initImage(line);
        testing[i] = (double *)malloc(784 * sizeof(double));

        // Vérification si l'allocation de mémoire a réussi
        if (testing[i] == NULL) {
            fprintf(stderr, "Erreur d'allocation de mémoire pour le tableau %d.\n", i);
            return; // Quitter le programme avec un code d'erreur
        }

        // Initialisation des valeurs (vous pouvez le faire selon vos besoins)
    
	for(size_t j = 0; j < 784; j++)
    {
        testing[i][j] = (double)(img->pixels[j]) / 255;
    }
	expectedTest[i] = (double)img->label;
	free(img);
    }


    // Affichage des valeurs
    /* for (int i = 0; i < numTraining; ++i) {
        for (int j = 0; j < 784; ++j) {
            printf("%f,", training[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < numTesting; ++i) {
        for (int j = 0; j < 784; ++j) {
            printf("%f,", testing[i][j]);
        }
        printf("\n");
    } */
}


void freeData(int numTraining, int numTesting, double **training, double *expectedTrain, double **testing, double *expectedTest)
{
	// Libération de la mémoire
    for (int i = 0; i < numTraining; ++i) {
        free(training[i]);
    }
    free(training);
    free(expectedTrain);

    for (int i = 0; i < numTesting; ++i) {
        free(testing[i]);
    }
    free(testing);
    free(expectedTest);
}

/*
int main(int argc, char *argv[]) 
{
    if (argc != 3) {
        fprintf(stderr, "Using: %s <training number> <testing number>\n", argv[0]);
        return 1;
    }

    int numTraining = atoi(argv[1]);
    int numTesting = atoi(argv[2]);

    // Allocation dynamique pour le tableau de pointeurs
    double **training = (double **)malloc(numTraining * sizeof(double *));
    double *expectedTrain = malloc(numTraining * sizeof(double));
    double **testing = (double **)malloc(numTesting * sizeof(double *));
    double *expectedTest = malloc(numTesting * sizeof(double));

    // Vérification si l'allocation de mémoire a réussi
    if (training == NULL || testing == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire pour le tableau principal.\n");
        return 1; // Quitter le programme avec un code d'erreur
    }

    data(numTraining, numTesting, training, expectedTrain, testing, expectedTest);

    // Libération de la mémoire
    freeData(numTraining, numTesting, training, expectedTrain, testing, expectedTest);

    return 0;
}*/
