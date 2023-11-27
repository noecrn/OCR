#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "solver.h"

typedef int Grid[9][9];

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("ERROR TOO FEW OR TOO MANY ARGUMENTS");
	}

//------File lecture----------------------------------------------
	//file content stocked in fileContent 
	
	FILE* fichier = NULL;

	fichier = fopen(argv[1], "r");

	if (fichier == NULL)//manage error if file not ok 
	{
		printf("ERREUR: Impossible file opening");
		fclose(fichier);
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
	
	int check_line(int line, int x) //if x can be on line return 1, 
					//else return 0
	{
		int i = 0;
		while (i < 9 && grid[line][i] != x)
		{
			i++;
		}
		
		return i == 9;
	}
	
	int check_col(int col, int x)//if x can be on the col return 1,
				     //else return 0
	{
		int i = 0;
		while(i < 9 && grid[i][col] != x)i++;
		return i == 9;
	}

	
	int check_bloc(int x, int y, int t)//if t can be in the block 
					   //of the case in y,x return 1
	{
		//printf("x = %i   y = %i   t = %i", x,y,t);
		int bloc_xd = x;
		int bloc_yd = y;
		while(bloc_xd % 3 != 0)bloc_xd--; 
		while(bloc_yd % 3 != 0)bloc_yd--;
		
		int bloc_xf = bloc_xd + 3;
		int bloc_yf = bloc_yd + 3;
			
		while(bloc_yd < bloc_yf)
		{ 
			int temp = bloc_xd;
			//printf("y=%i\n", bloc_yd);
			while(temp < bloc_xf)
			{	
				//printf("x=%i\n", temp);
				if (grid[bloc_yd][temp] == t)return 0;
				temp++;
			}
			bloc_yd++;
		}
		
		return 1;
	} 
	
	void grid_printer(char* p, Grid grid)
	{
		for (int y = 0; y < 9; y++)
    		{
        		if (y == 3 || y == 6)strcat(p, "\n");
        		for (int x = 0; x < 9; x++)
		        {
           			 if (x == 3 || x == 6)strcat(p, " ");

            				int temp = grid[y][x];
            				char s[2]; 
            				snprintf(s, sizeof(s), "%d", temp);
            				strcat(p, s);
        		}
        		strcat(p, "\n");
    		}
	}

	int findEmpty(int* x_vide, int* y_vide)
	{	
		*x_vide = 0;
		*y_vide = 0;
		int flag = 0;
		while (flag == 0 && *y_vide < 9)
		{
			while (flag == 0 && *x_vide < 9)
			{
				if(grid[*y_vide][*x_vide] == 0)
				{
					flag = 1;
					break;
				}
			
				*x_vide += 1;
			}
			if(flag == 0)
			{
				 *y_vide += 1;
 				 *x_vide = 0; 
			}
		}
		return flag;
	}
	
	int solve()
	{
	    int line = 0;
       	int col = 0;
		if(findEmpty(&col, &line) == 0) return 1;
		for(int i = 1; i < 10; i++)
		{
			if(check_line(line, i) == 1 
					&& check_col(col, i) == 1 
					&& check_bloc(col, line, i) == 1)
			{
				grid[line][col] = i;
				if (solve()) return 1;
				grid[line][col] = 0;
			}		
		}
		return 0;		
	}
	


	char s[105] = "";
	int res = solve();
	grid_printer(s, grid);
	
	FILE* fichier1 = NULL;
 
	fichier1 = fopen(strcat(argv[1], ".result"), "w");
 
	if (fichier1 != NULL)
    	{
        	fputs(s, fichier1);
       		fclose(fichier1);
    	}

	return res;
}

