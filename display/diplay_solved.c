#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace cv;
using namespace std;

typedef int Grid[9][9];

int main(int argc, char* argv[]) {

	// if in argument there is a file with the coordinates of the grid we use it
	// else we display the grid in full screen

    // Check if filenames are provided
    if (argc < 2) {
        printf("Please provide an image filename and a grid filename\n");
        return 1;
    }
	

    // The filenames are the first and second arguments
    const char* imageFilename = argv[1];
    const char* gridFilename = argv[2];
	const char* cooFilenamle = argv[3];

    // Load Sudoku grid image
    Mat sudokuImage = imread(imageFilename, IMREAD_COLOR);

    // Check if the image is loaded successfully
    if (sudokuImage.empty()) {
        printf("Error loading image\n");
        return -1;
    }

//------File lecture----------------------------------------------

    // Open the grid file
    FILE* fichier = fopen(gridFilename, "r");

    // Check if the file is opened successfully
    if (fichier == NULL) {
        printf("Error opening grid file\n");
        return 1;
    }

	
	char fileContent[105] = "";
	char temp[11];

	while(fgets(temp, 11, fichier) != NULL)
	{	
		strcat(fileContent, temp);
	}

	//printf("%s", fileContent);
	char str[82] = "";
	size_t k = 0;
	size_t q = 0;

	while(fileContent[k] != '\0')
	{
		if(fileContent[k] >= 46 && fileContent[k] <= 57)
		{
			str[q] = fileContent[k];
			q++;
		}
		k++;
	}

	//printf("%s", str);

	fclose(fichier);
//------End of file lecture--------------------------------------

//------Creation of the grid-------------------------------------
	//from 1 to 9 on X an Y
	//0 unused
	
	Grid grid;  // X Y VAL&POS
	
	size_t index = 0; // index for the string

	for(size_t y = 0; y < 9; y++)
	{
		for (size_t x = 0; x < 9; x++)
		{
			if (str[index] == '.')
				grid[y][x] = 0;

			else
				grid[y][x] = str[index]-48;
			index++;
		}
	}
//------End of Creation of the grid--------------------------------	

//------Read the coo file and asign x0, y0... variables------------
	int x0, y0, x1, y1, x2, y2, x3, y3;

	if (argc == 4)
	{
		printf("argc = 4\n");
		std::string filename = cooFilenamle;
		std::ifstream file(filename);
		if (!file) {
			std::cerr << "Unable to open file: " << filename << std::endl;
			return 1;  // Return an error code
		}

		if (!(file >> x0 >> y0 >> x1 >> y1 >> x2 >> y2 >> x3 >> y3)) {
			std::cerr << "Error: file doesn't contain 8 integers" << std::endl;
			return 1;  // Return an error code
		}

		// Print the values
		std::cout << x0 << '\n' << y0 << '\n' << x1 << '\n' << y1 << '\n' << x2 << '\n' << y2 << '\n' << x3 << '\n' << y3 << '\n';
	}
	else
	{
		printf("argc = 3\n");
		//display the grid in full screen
		x0 = 0;
		y0 = 0;
		x1 = sudokuImage.cols;
		y1 = 0;
		x2 = 0;
		y2 = sudokuImage.rows;
		x3 = sudokuImage.cols;
		y3 = sudokuImage.rows;
	}
	
	
//------End of reading the coo file--------------------------------


    // Font settings for displaying digits
    int fontFace = FONT_HERSHEY_SIMPLEX;
    double fontScale = 2;
    int thickness = 3;

	// Assume x0, y0, x1, y1, x2, y2, x3, y3 are defined and initialized

	// Calculate the width and height of the grid
	int gridWidth = x1 - x0;
	int gridHeight = y3 - y0;

	// Calculate the width and height of a cell
	int cellWidth = gridWidth / 9;
	int cellHeight = gridHeight / 9;

	// Loop through each cell in the Sudoku grid and display the digit on the image
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (grid[i][j] != 0) {
				// Convert row and column indices to pixel coordinates
				int x = x0 + j * cellWidth;
				int y = y0 + i * cellHeight;

				// Display the digit on the image
				string digit = to_string(grid[i][j]);
				Point textOrg(x + cellWidth / 2, y + cellHeight / 2);
				putText(sudokuImage, digit, textOrg, fontFace, fontScale, Scalar(150, 150, 150), thickness);
			}
		}
	}

    // Display the Sudoku grid image with digits
    //namedWindow("Sudoku Grid", WINDOW_NORMAL);
    //imshow("Sudoku Grid", sudokuImage);

    // Save the Sudoku grid image with digits
    if (!imwrite("sudoku_grid.jpg", sudokuImage)) {
        cout << "Error saving image" << endl;
        return -1;
    }

    //waitKey(0);

    return 0;
}
