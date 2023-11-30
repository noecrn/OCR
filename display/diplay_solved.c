#include <opencv2/opencv.hpp>
#include <iostream>

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

    // Sample Sudoku grid with digits (replace this with your actual data)
    int sudokuGrid[9][9] = {
        {5, 3, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 9}
    };

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