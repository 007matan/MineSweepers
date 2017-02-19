// Programer    : Matan Ovadia Cohen - Tzedek
// Date         : 14 / 12 / 2015
// Lecturer     : Michael Chernobilsky
// Project Name : Mine Sweeper

/***Including***/
#include <stdio.h>
#include "minesweepers.h"

/***typedef***/
typedef enum{DIS=0, NOTDIS} AllDiscoverd;
 
/*********FunctionsPrototype**********/
void MineSweeperDo (MineSweeperNode territory[][14]);
AllDiscoverd ChackWin(MineSweeperNode territory[][14]);

/***Main***/
int main()
{
	MineSweeperNode territory[14][14];
	MineSweeperDo(territory);
	return 0;
}


/*********FunctionsBody**********/
//The function calling the all functions.  
void MineSweeperDo (MineSweeperNode territory[][14])
{
	AllDiscoverd flag = NOTDIS;
	int row, col;
	OnMine push = FALSE;
	Init(territory);
	InsertMines(territory);
	InsertMinesAround(territory);
	Print(territory);
	while(!push)
	{
		fscanf(stdin,"%d", &row);
		fscanf(stdin,"%d", &col);
		if(territory[row][col].dis == NOTDISCOVERD)
			{
				territory[row][col].dis = DISCOVERD; 
				ZeroMinesAround(territory, row, col);
				push = Print(territory);
				flag = ChackWin(territory);
				if(!flag && push == FALSE)
				{
					printf("You Won");
					DiscoverdAll(territory);
					Print(territory);
					break;
				}
				else if (push == TRUE)
				{
					printf("\n\n\nMine!!!Mine!!!Mine!!!Mine!!!Mine!!!Mine!!!Mine!!!Mine!!!Mine!!!\n\n\n");
					printf("\nYOU LOST!!!\n");
					printf("THIS IS THE REVELED MINESWEEPER: \n");
					DiscoverdAll(territory);
					Print(territory);
				}
			}
	}
}
//The function checks if the player wins.
//The function pass on all the matrix checking all the cells that not mines.
//if them all are discoverd the function return flag that say it.
//Function accepts a matrix.
//The function return true if won and false if still not won.
AllDiscoverd ChackWin(MineSweeperNode territory[][14])
{
	AllDiscoverd flag = DIS;
	int i, j;
	for(i=1; i<=12; i++)
	{
		for(j=1; j<=12 ;j++)
		{
			if(territory[i][j].thereIs == NOTMINES)
			{
				if (territory[i][j].dis == NOTDISCOVERD)
				{
					flag = NOTDIS;
					return flag;
				}
			}
		}
	}
	return flag;
}

