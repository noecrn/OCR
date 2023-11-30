#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace cv;
using namespace std;

int main() {
    // Load Sudoku grid image
    Mat sudokuImage = imread("sudoku_image.jpg", IMREAD_COLOR);

    // Check if the image is loaded successfully
    if (sudokuImage.empty()) {
        cout << "Error loading image" << endl;
        return -1;
    }

    // Load Sudoku grid from text file
    int sudokuGrid[9][9] = {0};  // Initialize all cells to 0
    ifstream file("grid_00");
    string line;
    int row = 0;

    while (getline(file, line)) {
        // Skip empty lines
        if (line.empty()) continue;

        // Parse characters and convert them to integers
        for (int col = 0; col < 9; col++) {
            if (line[col] >= '1' && line[col] <= '9') {
                sudokuGrid[row][col] = line[col] - '0';  // Convert char to int
            }
        }

        row++;
    }

    file.close();

    for (size_t i = 0; i < 9; i++)
    {
        for (size_t j = 0; j < 9; j++)
        {
            printf("%d ", sudokuGrid[i][j]);
        }
        printf("\n");
    }
    

    // Font settings for displaying digits
    int fontFace = FONT_HERSHEY_SIMPLEX;
    double fontScale = 2;
    int thickness = 3;

    // Loop through each cell in the Sudoku grid and display the digit on the image
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (sudokuGrid[i][j] != 0) {
                // Convert row and column indices to pixel coordinates
                int x = j * sudokuImage.cols / 9 -20;
                int y = i * sudokuImage.rows / 9 +5;

                // Display the digit on the image
                string digit = to_string(sudokuGrid[i][j]);
                Point textOrg(x + sudokuImage.cols / 18, y + sudokuImage.rows / 14);
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