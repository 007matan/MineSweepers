/***Including***/
#include "minesweepers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*********FunctionsPrototype**********/
void Init(MineSweeperNode territory[][14]);
void InsertMines(MineSweeperNode field[][14]);
void InsertMinesAround(MineSweeperNode field[][14]);
OnMine Print(MineSweeperNode  field[][14]);
void ZeroMinesAround(MineSweeperNode  field[][14], int row, int col);
void DiscoverdAll (MineSweeperNode territory[][14]);

/**********FunctionsBody***********/
//The function initializes the matrix.
//So that each cells of the matrix is not mine and not visible.
//Function accepts a matrix.
//The function does not return anything.
void Init(MineSweeperNode territory[][14])
{
	int i, j;
	for(i = 0; i < 14; i++)
	{
		for(j = 0; j < 14; j++)
		{
			(*(*(territory +i)+j)).thereIs = NOTMINES;
			(*(*(territory +i)+j)).dis = NOTDISCOVERD;
		}
	}
}
//The function enter mines to the matrix.
//The function receives row and column and displays the mine and point at the specific location point. 
//Function accepts a matrix. The function does not return anything.
void InsertMines(MineSweeperNode field[][14])
{
	int row, col;
	FILE *minesFile = fopen("mines.txt","r");
    if (minesFile == NULL) 
	{
       printf("Error opening file\n");
	   return;
	}
	while (!feof(minesFile))
	{
		fscanf(minesFile,"%d %d ", &row, &col);
		(*(*(field + row) + col)).thereIs = MINES;
		(*(*(field + row) + col)).ItemNode.mine = '.';
	}
}
//The function puts numbers to cells when they are not mines.
//The function passes the entire matrix and places all cells that are not mines
//Numbers as the number of mines around.
//Function accepts a matrix.
//The function does not return anything.
void InsertMinesAround(MineSweeperNode field[][14])//מכניסה מספרים 
{
	int i, j, k;
	int const DIR_MATRIX[][2] = {{-1,-1}, {-1,0}, {-1,1}, {0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}};
	int nrow;
	int ncol;
	int count;
	MinesAround x;
	for(i=1; i<=12; i++)
	{
		for(j=1; j<=12 ;j++)
		{
			if(field[i][j].thereIs == NOTMINES)
			{
				count = 0;
				for (k = 0; k < 8; k++)
				{
					nrow = i +DIR_MATRIX[k][0];
					ncol = j +DIR_MATRIX[k][1];
					count += (field[nrow][ncol].thereIs == MINES);
				}
				field[i][j].ItemNode.minesCount = (MinesAround) count;
			}
		}
	}

}
//Matrix printing function and checks whether a mine has been one of the cells we've discovered
//(meaning, the last cell we chosen)
//The function passes on all matrix print each cell according to its features,
//If we pressed on mine so we'll mark this.
//Function takes a matrix.
//The function returns if we pressed on a mine or not.
OnMine Print(MineSweeperNode  field[][14])
{
	int i, j;
	OnMine push = FALSE;
	MinesAround count;
	for(i=1; i<=12; i++)
	{
		printf("\n_ _ _ _ _ _ _ _ _ _ _ _\n");
		for(j=1; j<=12 ;j++)
		{
			if(field[i][j].dis == NOTDISCOVERD)
				printf(" +");
			else
			{
			    if(field[i][j].thereIs == NOTMINES)
					printf(" %d", field[i][j].ItemNode.minesCount);
				else
				{
					printf(" %c", field[i][j].ItemNode.mine);
					push = TRUE;
				}
			}
		}
	}
	printf("\n");
	return push;
}
//The function discover all cells around the selected cell if those not mines,
//and each cell that discovered, whose number is (the number of mines surrounding it) is zero if those not mines,
//do the same test and so on recursively.
//Function takes a matrix, row and column, pointing to cell whose number is zero.
//The function does not return anything
void ZeroMinesAround(MineSweeperNode  field[][14], int row, int col)
{
	int const DIR_MATRIX[][2] = {{-1,-1}, {-1,0}, {-1,1}, {0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}};
	int i;
	int nrow;
	int ncol;
	if((row > 0)&&(row < 13)&&(col > 0)&&(col < 13) && (field[row][col].thereIs == NOTMINES))
	{
		field[row][col].dis = DISCOVERD; //הופך את הנתון לגלוי... לאחר מכן שולח לפרינט עם עוד איבר חשוףת והפרינט עושה את הבדיקה עם הוא מוקש או מספר
		if(field[row][col].ItemNode.minesCount == ZERO)
		{
			for (i = 0; i < 8; i++)
			{
				nrow = row +DIR_MATRIX[i][0];
				ncol = col +DIR_MATRIX[i][1];
				if (field[nrow][ncol].dis == NOTDISCOVERD)
					ZeroMinesAround(field, nrow, ncol);
			}
		}
	}
}
//The function discovers all cells.
//The function passes each cell in the matrix makes it visible.
//Function takes a matrix.
//The function does not return anything.
void DiscoverdAll (MineSweeperNode territory[][14])
{
	int i, j;
	for(i=1; i<=12; i++)
	{
		for(j=1; j<=12 ;j++)
		{
			territory[i][j].dis = DISCOVERD;
		}
	}
}