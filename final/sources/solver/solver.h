#ifndef SOLVER_H
#define SOLVER_H

int main(int argc, char *argv[]);
void gridPrinter(int grid[][9][9]);
void possibility(int* pos[]);
int check_line (int* begin, int* end, int x);
int check_col(int* begin[9], int* end[9], int col, int x);

#endif






