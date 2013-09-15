/* 
* Naughts and Crosses
* Operating System Principles
* Semester 2 2013
* RMIT
* Christian Rivers s3300619
* Created 14/09/2013
* last edited 15/09/13 CR
* VERSION 0.1
*/

// Need to check input is correct format



#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ROWS 3
#define COLUMNS 3

void printBoard(char board[][3]);
void humanTurn(char board[][COLUMNS]);
void compGenius(char board[][COLUMNS]);
int checkWin(char board[][COLUMNS]);

int main(int argc, char *argv[])
{
	// Create Board
	char board[ROWS][COLUMNS] = {
		{' ', ' ', ' '} , 
		{' ', ' ', ' '} ,
		{' ', ' ', ' '}
	};
	
	// Display Board
	printBoard(board);
	
	// Start game
	humanTurn(board);
	
	return 0;
}

void printBoard(char board[][3])
{
	int i;
	int j;
	printf("    -----------\n");
	for (i = 0; i < ROWS; i++)
	{
		printf("   |");
		for (j = 0; j < COLUMNS; j++)
		{
			printf(" %c |", board[i][j]);	
		}
		printf("\n    -----------\n");
	} 
}

void humanTurn(char board[][COLUMNS])
{
	int x, y;
	do
	{
		do
		{
			printf("Enter row number: ");
			
			// Need to not use scanf, its error checking is shit.
			scanf("%d", &x);
			if (x < 1 || x > 3)
			{
				printf("\nA number between 1 and 3 please!\n");
			}
		} while (x < 1 || x > 3);	
		x--;
		
		do
		{
			printf("Enter column number: ");
			scanf("%d", &y);;
			if (y < 1 || y > 3)
			{
				printf("\nA number between 1 and 3 please!\n");
			}
		} while (y < 1 || y > 3);
		y--;
		
		// Make sure the position entered is empty
		
		if (board[x][y] != ' ')
		{
			printf("\nThat position is filled! Try again!\n");
		}
	} while (board[x][y] != ' ');
	
	board[x][y] = 'X';
	
	if (checkWin(board) == 0)
	{
		return;
	}
	
	printBoard(board);
	compGenius(board);
}

// Computer AI logic
void compGenius(char board[][COLUMNS])
{


	// Check for 2 0s in play, to achieve winning state
	
	if (board[0][0] == '0' && board[0][1] == '0' && board[0][2] == ' '
		|| board[2][0] == '0' && board[1][1] == '0' && board[0][2] == ' '
		|| board[2][2] == '0' && board[1][2] == '0' && board[0][2] == ' ')
	{
		board[0][2] = '0';
	}
	else if
	(board[1][0] == '0' && board[1][1] == '0' && board[1][2] == ' ')
	{
		board[1][2] = '0';
	}
	else if
	(board[2][0] == '0' && board[2][1] == '0' && board[2][2] == ' '
		|| board[0][0] == '0' && board[1][1] == '0' && board[2][2] == ' '
		|| board[0][2] == '0' && board[1][2] == '0' && board[2][2] == ' ')
	{
	 	board[2][2] = '0';
	}	
	else if
	(board[1][1] == '0' && board[2][1] == '0' && board[0][1] == ' '
	|| board[0][0] == '0' && board[0][2] == '0' && board[0][1] == ' ') 
	{
		board[0][1] = '0';	
	}
	else if
	(board[0][0] == '0' && board[2][2] == '0' && board[1][1] == ' '
		|| board[1][0] == '0' && board[1][2] == '0' && board[1][1] == ' '
		|| board[2][0] == '0' && board[0][2] == '0' && board[1][1] == ' '
		|| board[0][1] == '0' && board[2][1] == '0' && board[1][1] == ' ')
	{
	 	board[1][1] = '0';
	}
	else if
	(board[2][0] == '0' && board[2][2] == '0' && board[2][1] == ' '
	|| board[0][1] == '0' && board[1][1] == '0' && board[2][1] == ' ') 
	{
		board[2][1] = '0';	
	}
	else if
	(board[0][1] == '0' && board[0][2] == '0' && board[0][0] == ' '
		|| board[1][0] == '0' && board[2][0] == '0' && board[0][0] == ' '
		|| board[1][1] == '0' && board[2][2] == '0' && board[0][0] == ' ')
	{
	 	board[0][0] = '0';
	}
	else if
	(board[0][0] == '0' && board[2][0] == '0' && board[1][0] == ' '
	|| board[1][1] == '0' && board[1][2] == '0' && board[1][0] == ' ') 
	{
		board[1][0] = '0';	
	}
	else if
	(board[0][0] == '0' && board[1][0] == '0' && board[2][0] == ' '
		|| board[1][1] == '0' && board[0][2] == '0' && board[2][0] == ' '
		|| board[2][1] == '0' && board[2][2] == '0' && board[2][0] == ' ')
	{
	 	board[2][0] = '0';
	}
	
	
	// Check for 2 Xs in play, to avoid losing state
	
	else if (board[0][0] == 'X' && board[0][1] == 'X' && board[0][2] == ' '
		|| board[2][0] == 'X' && board[1][1] == 'X' && board[0][2] == ' '
		|| board[2][2] == 'X' && board[1][2] == 'X' && board[0][2] == ' ')
	{
		board[0][2] = '0';
	}
	else if
	(board[1][0] == 'X' && board[1][1] == 'X' && board[1][2] == ' ')
	{
		board[1][2] = '0';
	}
	else if
	(board[2][0] == 'X' && board[2][1] == 'X' && board[2][2] == ' '
		|| board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == ' '
		|| board[0][2] == 'X' && board[1][2] == 'X' && board[2][2] == ' ')
	{
	 	board[2][2] = '0';
	}	
	else if
	(board[1][1] == 'X' && board[2][1] == 'X' && board[0][1] == ' '
	|| board[0][0] == 'X' && board[0][2] == 'X' && board[0][1] == ' ') 
	{
		board[0][1] = '0';	
	}
	else if
	(board[0][0] == 'X' && board[2][2] == 'X' && board[1][1] == ' '
		|| board[1][0] == 'X' && board[1][2] == 'X' && board[1][1] == ' '
		|| board[2][0] == 'X' && board[0][2] == 'X' && board[1][1] == ' '
		|| board[0][1] == 'X' && board[2][1] == 'X' && board[1][1] == ' ')
	{
	 	board[1][1] = '0';
	}
	else if
	(board[2][0] == 'X' && board[2][2] == 'X' && board[2][1] == ' '
	|| board[0][1] == 'X' && board[1][1] == 'X' && board[2][1] == ' ') 
	{
		board[2][1] = '0';	
	}
	else if
	(board[0][1] == 'X' && board[0][2] == 'X' && board[0][0] == ' '
		|| board[1][0] == 'X' && board[2][0] == 'X' && board[0][0] == ' '
		|| board[1][1] == 'X' && board[2][2] == 'X' && board[0][0] == ' ')
	{
	 	board[0][0] = '0';
	}
	else if
	(board[0][0] == 'X' && board[2][0] == 'X' && board[1][0] == ' '
	|| board[1][1] == 'X' && board[1][2] == 'X' && board[1][0] == ' ') 
	{
		board[1][0] = '0';	
	}
	else if
	(board[0][0] == 'X' && board[1][0] == 'X' && board[2][0] == ' '
		|| board[1][1] == 'X' && board[0][2] == 'X' && board[2][0] == ' '
		|| board[2][1] == 'X' && board[2][2] == 'X' && board[2][0] == ' ')
	{
	 	board[2][0] = '0';
	}
	
	
	// Other moves
	
	else if
	(board[1][1] == ' ')
	{
		board[1][1] = '0';
	}
	else if 
	(board[0][0] == ' ')
	{
		board[0][0] = '0';
	}
	else if 
	(board[0][1] == ' ')
	{
		board[0][1] = '0';
	}
	else if 
	(board[0][2] == ' ')
	{
		board[0][2] = '0';
	}
	else if 
	(board[1][0] == ' ')
	{
		board[1][0] = '0';
	}
	else if 
	(board[1][2] == ' ')
	{
		board[1][2] = '0';
	}
	else if 
	(board[2][0] == ' ')
	{
		board[2][0] = '0';
	}
	else if 
	(board[2][1] == ' ')
	{
		board[2][1] = '0';
	}
	else if 
	(board[2][2] == ' ')
	{
		board[2][2] = '0';
	}
	if (checkWin(board) == 0)
	{
		return;
	}
	printBoard(board);
	humanTurn(board);
}

int checkWin(char board[][COLUMNS])
{
	// Check if X has won, 3 Xs in a row
	
	if (board[0][0] == 'X' && board[0][1] == 'X' && board[0][2] == 'X'
		|| board[2][0] == 'X' && board[1][1] == 'X' && board[0][2] == 'X'
		|| board[2][2] == 'X' && board[1][2] == 'X' && board[0][2] == 'X')
	{
		printBoard(board);
		printf("\nCongratulations player!!! You is winner!\n");
		return 0;
	}
	else if
	(board[1][0] == 'X' && board[1][1] == 'X' && board[1][2] == 'X')
	{
		printBoard(board);
		printf("\nCongratulations player!!! You is winner!\n");
		return 0;
	}
	else if
	(board[2][0] == 'X' && board[2][1] == 'X' && board[2][2] == 'X'
		|| board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == 'X'
		|| board[0][2] == 'X' && board[1][2] == 'X' && board[2][2] == 'X')
	{
		printBoard(board);
	 	printf("\nCongratulations player!!! You is winner!\n");
		return 0;
	}	
	else if
	(board[1][1] == 'X' && board[2][1] == 'X' && board[0][1] == 'X'
	|| board[0][0] == 'X' && board[0][2] == 'X' && board[0][1] == 'X') 
	{
		printBoard(board);
		printf("\nCongratulations player!!! You is winner!\n");
		return 0;	
	}
	else if
	(board[0][0] == 'X' && board[2][2] == 'X' && board[1][1] == 'X'
		|| board[1][0] == 'X' && board[1][2] == 'X' && board[1][1] == 'X'
		|| board[2][0] == 'X' && board[0][2] == 'X' && board[1][1] == 'X'
		|| board[0][1] == 'X' && board[2][1] == 'X' && board[1][1] == 'X')
	{
		printBoard(board);
	 	printf("\nCongratulations player!!! You is winner!\n");
		return 0;
	}
	else if
	(board[2][0] == 'X' && board[2][2] == 'X' && board[2][1] == 'X'
	|| board[0][1] == 'X' && board[1][1] == 'X' && board[2][1] == 'X') 
	{
		printBoard(board);
		printf("\nCongratulations player!!! You is winner!\n");
		return 0;	
	}
	else if
	(board[0][1] == 'X' && board[0][2] == 'X' && board[0][0] == 'X'
		|| board[1][0] == 'X' && board[2][0] == 'X' && board[0][0] == 'X'
		|| board[1][1] == 'X' && board[2][2] == 'X' && board[0][0] == 'X')
	{
		printBoard(board);
	 	printf("\nCongratulations player!!! You is winner!\n");
		return 0;
	}
	else if
	(board[0][0] == 'X' && board[2][0] == 'X' && board[1][0] == 'X'
	|| board[1][1] == 'X' && board[1][2] == 'X' && board[1][0] == 'X') 
	{
		printBoard(board);
		printf("\nCongratulations player!!! You is winner!\n");
		return 0;	
	}
	else if
	(board[0][0] == 'X' && board[1][0] == 'X' && board[2][0] == 'X'
		|| board[1][1] == 'X' && board[0][2] == 'X' && board[2][0] == 'X'
		|| board[2][1] == 'X' && board[2][2] == 'X' && board[2][0] == 'X')
	{
		printBoard(board);
	 	printf("\nCongratulations player!!! You is winner!\n");
		return 0;
	}
	
	// Check if 0 has won, 3 0s in a row
	
	else if (board[0][0] == '0' && board[0][1] == '0' && board[0][2] == '0'
		|| board[2][0] == '0' && board[1][1] == '0' && board[0][2] == '0'
		|| board[2][2] == '0' && board[1][2] == '0' && board[0][2] == '0')
	{
		printBoard(board);
		printf("\n I beat u, suck it!!!\n");
		return 0;
	}
	else if
	(board[1][0] == '0' && board[1][1] == '0' && board[1][2] == '0')
	{
		printBoard(board);
		printf("\n I beat u, suck it!!!\n");
		return 0;
	}
	else if
	(board[2][0] == '0' && board[2][1] == '0' && board[2][2] == '0'
		|| board[0][0] == '0' && board[1][1] == '0' && board[2][2] == '0'
		|| board[0][2] == '0' && board[1][2] == '0' && board[2][2] == '0')
	{
		printBoard(board);
	 	printf("\n I beat u, suck it!!!\n");
		return 0;
	}	
	else if
	(board[1][1] == '0' && board[2][1] == '0' && board[0][1] == '0'
	|| board[0][0] == '0' && board[0][2] == '0' && board[0][1] == '0') 
	{
		printBoard(board);
		printf("\n I beat u, suck it!!!\n");
		return 0;	
	}
	else if
	(board[0][0] == '0' && board[2][2] == '0' && board[1][1] == '0'
		|| board[1][0] == '0' && board[1][2] == '0' && board[1][1] == '0'
		|| board[2][0] == '0' && board[0][2] == '0' && board[1][1] == '0'
		|| board[0][1] == '0' && board[2][1] == '0' && board[1][1] == '0')
	{
		printBoard(board);
	 	printf("\n I beat u, suck it!!!\n");
		return 0;
	}
	else if
	(board[2][0] == '0' && board[2][2] == '0' && board[2][1] == '0'
	|| board[0][1] == '0' && board[1][1] == '0' && board[2][1] == '0') 
	{
		printBoard(board);
		printf("\n I beat u, suck it!!!\n");
		return 0;	
	}
	else if
	(board[0][1] == '0' && board[0][2] == '0' && board[0][0] == '0'
		|| board[1][0] == '0' && board[2][0] == '0' && board[0][0] == '0'
		|| board[1][1] == '0' && board[2][2] == '0' && board[0][0] == '0')
	{
		printBoard(board);
	 	printf("\n I beat u, suck it!!!\n");
		return 0;
	}
	else if
	(board[0][0] == '0' && board[2][0] == '0' && board[1][0] == '0'
	|| board[1][1] == '0' && board[1][2] == '0' && board[1][0] == '0') 
	{
		printBoard(board);
		printf("\n I beat u, suck it!!!\n");
		return 0;	
	}
	else if
	(board[0][0] == '0' && board[1][0] == '0' && board[2][0] == '0'
		|| board[1][1] == '0' && board[0][2] == '0' && board[2][0] == '0'
		|| board[2][1] == '0' && board[2][2] == '0' && board[2][0] == '0')
	{
		printBoard(board);
	 	printf("\n I beat u, suck it!!!\n");
		return 0;
	}
	
	// Check for a draw
	
	else if (board[0][0] != ' ' && board[0][1] != ' ' && board[0][2] != ' '
		&& board[1][0] != ' ' && board[1][1] != ' ' && board[1][2] != ' '
		&& board[2][0] != ' ' && board[2][1] != ' ' && board[2][2] != ' ')
	{
		printBoard(board);
		printf("\nBoring!! A draw!\n");
		return 0;
	}
	
	return 1;
	
} 

