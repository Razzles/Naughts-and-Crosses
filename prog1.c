/*
 * Naughts and Crosses
 * Operating System Principles
 * Semester 2 2013
 * RMIT
 * Christian Rivers s3300619
 * Created 14/09/2013
 * VERSION 1.0
 *Last edited 10/10/13
 * gcc -o tictactoe prog1.c -lpthread
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#define ROWS 3
#define COLUMNS 3
#define NUMBERTHREADS 6
int counter = 0;
int turn = 1;
int gameOver = 0;
pthread_t threadId[NUMBERTHREADS];
pthread_mutex_t lock1;
pthread_mutex_t lock2;
pthread_mutex_t lock3;
pthread_mutex_t lock4;


/* Create Board as a global array*/
char board[ROWS][COLUMNS] = {
    {' ', ' ', ' '} ,
    {' ', ' ', ' '} ,
    {' ', ' ', ' '}
};

/* Display Menu */
void displayMenu()
{
    printf("\n**** Choose an option ****\n\n1 - CPU vs CPU\n2 - Human vs CPU\n3 - Human vs Human\n\n\n");
    
}

/* locks the function and returns the currnt player turn */
int checkTurn()
{
    pthread_mutex_lock(&lock1);
    int rturn = getTurn();
    pthread_mutex_unlock(&lock1);
    return rturn;

}

int getTurn()
{
    return turn;
}

/* locks the function and sets the current player turn */
void change_turn()
{
    pthread_mutex_lock(&lock2);
    if (turn == 1)
    {
         turn = 2;
    }
    else
    {
         turn = 1;   
    }
    pthread_mutex_unlock(&lock2);
}

/* not implemented in code, but locks the function and edits the board */
void addX0(int row, int col, int x0)
{
    pthread_mutex_lock(&lock4);
    if (x0 == 1) {
        board[row][col] = 'X';
    }
    else
    {
        board[row][col] = '0';
    }
    pthread_mutex_lock(&lock4);
}

/* prints the board to the console */
void printBoard(char board[][COLUMNS])
{
    pthread_mutex_lock(&lock3);
	int i;
	int j;
    printf("     1   2   3\n");
	printf("    -----------\n");
	for (i = 0; i < ROWS; i++)
	{
		printf(" %d |",i+1);
		for (j = 0; j < COLUMNS; j++)
		{
			printf(" %c |", board[i][j]);	
		}
		printf("\n    -----------\n");
	}
    sleep(0);
    pthread_mutex_unlock(&lock3);
}

/* checks for a winning state and exits */
int checkWin(char board[][COLUMNS])
{
    
	/* Check if X has won, 3 Xs in a row */
	
	if ((board[0][0] == 'X' && board[0][1] == 'X' && board[0][2] == 'X')
		|| (board[1][0] == 'X' && board[1][1] == 'X' && board[1][2] == 'X')
		|| (board[2][0] == 'X' && board[2][1] == 'X' && board[2][2] == 'X')
        || (board[0][0] == 'X' && board[1][0] == 'X' && board[2][0] == 'X')
        || (board[0][1] == 'X' && board[1][1] == 'X' && board[2][1] == 'X')
		|| (board[0][2] == 'X' && board[1][2] == 'X' && board[2][2] == 'X')
		|| (board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == 'X')
        || (board[2][0] == 'X' && board[1][1] == 'X' && board[0][2] == 'X')
        )
	{
		printBoard(board);
        gameOver = 1;
		printf("\nX winner yes.\n");
		return 0;
	}	
	/* Check if 0 has won, 3 0s in a row */
	
	else if
        ((board[0][0] == '0' && board[0][1] == '0' && board[0][2] == '0')
        || (board[1][0] == '0' && board[1][1] == '0' && board[1][2] == '0')
        || (board[2][0] == '0' && board[2][1] == '0' && board[2][2] == '0')
        || (board[0][0] == '0' && board[1][0] == '0' && board[2][0] == '0')
        || (board[0][1] == '0' && board[1][1] == '0' && board[2][1] == '0')
        || (board[0][2] == '0' && board[1][2] == '0' && board[2][2] == '0')
        || (board[0][0] == '0' && board[1][1] == '0' && board[2][2] == '0')
        || (board[2][0] == '0' && board[1][1] == '0' && board[0][2] == '0')
        )
	{
		printBoard(board);
        gameOver = 1;
	 	printf("\n 0 is did win!\n");
		return 0;
	}
	
	/* Check for a draw */
	
	else if (board[0][0] != ' ' && board[0][1] != ' ' && board[0][2] != ' '
		&& board[1][0] != ' ' && board[1][1] != ' ' && board[1][2] != ' '
		&& board[2][0] != ' ' && board[2][1] != ' ' && board[2][2] != ' ')
	{
        gameOver = 1;
		printBoard(board);
		printf("\nBoring!! A draw!\n");
		return 0;
	}
	
	return 1;
	
}

/* algorithm for computer 0 player */
void* comp_ai0(void *arg)
{
    int ranNum;
    do
    {
        counter++;
        while (checkTurn() == 2) {
            

            
            /* Check for 2 0s in play, to achieve winning state */
            
            if ((board[0][0] == '0' && board[0][1] == '0' && board[0][2] == ' ')
                || (board[2][0] == '0' && board[1][1] == '0' && board[0][2] == ' ')
                || (board[2][2] == '0' && board[1][2] == '0' && board[0][2] == ' '))
            {
                addX0(0,2,2);
            }
            else if
                ((board[1][0] == '0' && board[1][1] == '0' && board[1][2] == ' ')
                 || (board[0][2] == '0' && board[2][2] == '0' && board[1][2] == ' '))
            {
                board[1][2] = '0';
            }
            else if
                ((board[2][0] == '0' && board[2][1] == '0' && board[2][2] == ' ')
                 || (board[0][0] == '0' && board[1][1] == '0' && board[2][2] == ' ')
                 || (board[0][2] == '0' && board[1][2] == '0' && board[2][2] == ' '))
            {
                board[2][2] = '0';
            }
            else if
                ((board[1][1] == '0' && board[2][1] == '0' && board[0][1] == ' ')
                 || (board[0][0] == '0' && board[0][2] == '0' && board[0][1] == ' '))
            {
                board[0][1] = '0';
            }
            else if
                ((board[0][0] == '0' && board[2][2] == '0' && board[1][1] == ' ')
                 || (board[1][0] == '0' && board[1][2] == '0' && board[1][1] == ' ')
                 || (board[2][0] == '0' && board[0][2] == '0' && board[1][1] == ' ')
                 || (board[0][1] == '0' && board[2][1] == '0' && board[1][1] == ' '))
            {
                board[1][1] = '0';
            }
            else if
                ((board[2][0] == '0' && board[2][2] == '0' && board[2][1] == ' ')
                 || (board[0][1] == '0' && board[1][1] == '0' && board[2][1] == ' '))
            {
                board[2][1] = '0';
            }
            else if
                ((board[0][1] == '0' && board[0][2] == '0' && board[0][0] == ' ')
                 || (board[1][0] == '0' && board[2][0] == '0' && board[0][0] == ' ')
                 || (board[1][1] == '0' && board[2][2] == '0' && board[0][0] == ' '))
            {
                board[0][0] = '0';
            }
            else if
                ((board[0][0] == '0' && board[2][0] == '0' && board[1][0] == ' ')
                 || (board[1][1] == '0' && board[1][2] == '0' && board[1][0] == ' '))
            {
                board[1][0] = '0';
            }
            else if
                ((board[0][0] == '0' && board[1][0] == '0' && board[2][0] == ' ')
                 || (board[1][1] == '0' && board[0][2] == '0' && board[2][0] == ' ')
                 || (board[2][1] == '0' && board[2][2] == '0' && board[2][0] == ' '))
            {
                board[2][0] = '0';
            }
            
            
            /* Check for 2 Xs in play, to avoid losing state */
            
            else if
                ((board[0][0] == 'X' && board[0][1] == 'X' && board[0][2] == ' ')
                 || (board[2][0] == 'X' && board[1][1] == 'X' && board[0][2] == ' ')
                 || (board[2][2] == 'X' && board[1][2] == 'X' && board[0][2] == ' '))
            {
                board[0][2] = '0';
            }
            else if
                ((board[1][0] == 'X' && board[1][1] == 'X' && board[1][2] == ' ')
                 || (board[0][2] == 'X' && board[2][2] == 'X' && board[1][2] == ' ')
                 || (board [0][2] == 'X' && board[2][0] == 'X' && board[1][2] == ' '))
            {
                board[1][2] = '0';
            }
            else if
                ((board[2][0] == 'X' && board[2][1] == 'X' && board[2][2] == ' ')
                 || (board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == ' '))
            {
                board[2][2] = '0';
            }
            else if
                ((board[1][1] == 'X' && board[2][1] == 'X' && board[0][1] == ' ')
                 || (board[0][0] == 'X' && board[0][2] == 'X' && board[0][1] == ' '))
            {
                board[0][1] = '0';
            }
            else if
                ((board[0][0] == 'X' && board[2][2] == 'X' && board[1][1] == ' ')
                 || (board[1][0] == 'X' && board[1][2] == 'X' && board[1][1] == ' ')
                 || (board[2][0] == 'X' && board[0][2] == 'X' && board[1][1] == ' ')
                 || (board[0][1] == 'X' && board[2][1] == 'X' && board[1][1] == ' '))
            {
                board[1][1] = '0';
            }
            else if
                ((board[2][0] == 'X' && board[2][2] == 'X' && board[2][1] == ' ')
                 || (board[0][1] == 'X' && board[1][1] == 'X' && board[2][1] == ' '))
            {
                board[2][1] = '0';
            }
            else if
                ((board[0][1] == 'X' && board[0][2] == 'X' && board[0][0] == ' ')
                 || (board[1][0] == 'X' && board[2][0] == 'X' && board[0][0] == ' ')
                 || (board[1][1] == 'X' && board[2][2] == 'X' && board[0][0] == ' '))
            {
                board[0][0] = '0';
            }
            else if
                ((board[0][0] == 'X' && board[2][0] == 'X' && board[1][0] == ' ')
                 || (board[1][1] == 'X' && board[1][2] == 'X' && board[1][0] == ' '))
            {
                board[1][0] = '0';	
            }
            else if
                ((board[0][0] == 'X' && board[1][0] == 'X' && board[2][0] == ' ')
                 || (board[1][1] == 'X' && board[0][2] == 'X' && board[2][0] == ' ')
                 || (board[2][1] == 'X' && board[2][2] == 'X' && board[2][0] == ' '))
            {
                board[2][0] = '0';
            }
            
            
            /* Other moves */
            
            /* Added randomness so we get multiple game results instead of just one */
            
            else
            {
                srand(time(NULL));
                ranNum = (rand() % 9) + 1;
                switch (ranNum) {
                    case 1:
                        if (board[0][0] == ' ')
                        {
                            board[0][0] = '0';
                        }
                        else if
                            (board[0][2] == ' ')
                        {
                            board[0][2] = '0';
                        }
                        else if
                            (board[1][1] == ' ')
                        {
                            board[1][1] = '0';
                        }
                        else if
                            (board[0][1] == ' ')
                        {
                            board[0][1] = '0';
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
                        break;
                    case 2:
                        if (board[0][2] == ' ')
                        {
                            board[0][2] = '0';
                        }
                        
                        else if
                            (board[1][1] == ' ')
                        {
                            board[1][1] = '0';
                        }
                        else if
                            (board[0][1] == ' ')
                        {
                            board[0][1] = '0';
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
                        else if
                            (board[0][0] == ' ')
                        {
                            board[0][0] = '0';
                        }
                        break;
                    case 3:
                        if (board[1][1] == ' ')
                        {
                            board[1][1] = '0';
                        }
                        else if
                            (board[0][1] == ' ')
                        {
                            board[0][1] = '0';
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
                        else if
                            (board[0][0] == ' ')
                        {
                            board[0][0] = '0';
                        }
                        else if
                            (board[0][2] == ' ')
                        {
                            board[0][2] = '0';
                        }
                        break;
                    case 4:
                        if (board[0][1] == ' ')
                        {
                            board[0][1] = '0';
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
                        else if
                            (board[0][0] == ' ')
                        {
                            board[0][0] = '0';
                        }
                        else if
                            (board[0][2] == ' ')
                        {
                            board[0][2] = '0';
                        }
                        else if
                            (board[1][1] == ' ')
                        {
                            board[1][1] = '0';
                        }
                        break;
                    case 5:
                        if (board[1][0] == ' ')
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
                        else if
                            (board[0][0] == ' ')
                        {
                            board[0][0] = '0';
                        }
                        else if
                            (board[0][2] == ' ')
                        {
                            board[0][2] = '0';
                        }
                        else if
                            (board[1][1] == ' ')
                        {
                            board[1][1] = '0';
                        }
                        else if
                            (board[0][1] == ' ')
                        {
                            board[0][1] = '0';
                        }
                        break;
                    case 6:
                        if (board[1][2] == ' ')
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
                        else if
                            (board[0][0] == ' ')
                        {
                            board[0][0] = '0';
                        }
                        else if
                            (board[0][2] == ' ')
                        {
                            board[0][2] = '0';
                        }
                        else if
                            (board[1][1] == ' ')
                        {
                            board[1][1] = '0';
                        }
                        else if
                            (board[0][1] == ' ')
                        {
                            board[0][1] = '0';
                        }
                        else if
                            (board[1][0] == ' ')
                        {
                            board[1][0] = '0';
                        }
                        break;
                    case 7:
                        if (board[2][0] == ' ')
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
                        else if
                            (board[0][0] == ' ')
                        {
                            board[0][0] = '0';
                        }
                        else if
                            (board[0][2] == ' ')
                        {
                            board[0][2] = '0';
                        }
                        else if
                            (board[1][1] == ' ')
                        {
                            board[1][1] = '0';
                        }
                        else if
                            (board[0][1] == ' ')
                        {
                            board[0][1] = '0';
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
                        break;
                    case 8:
                        if (board[2][1] == ' ')
                        {
                            board[2][1] = '0';
                        }
                        else if
                            (board[2][2] == ' ')
                        {
                            board[2][2] = '0';
                        }
                        else if
                            (board[0][0] == ' ')
                        {
                            board[0][0] = '0';
                        }
                        else if
                            (board[0][2] == ' ')
                        {
                            board[0][2] = '0';
                        }
                        else if
                            (board[1][1] == ' ')
                        {
                            board[1][1] = '0';
                        }
                        else if
                            (board[0][1] == ' ')
                        {
                            board[0][1] = '0';
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
                        break;
                    case 9:
                        if (board[2][2] == ' ')
                        {
                            board[2][2] = '0';
                        }
                        else if
                            (board[0][0] == ' ')
                        {
                            board[0][0] = '0';
                        }
                        else if
                            (board[0][2] == ' ')
                        {
                            board[0][2] = '0';
                        }
                        else if
                            (board[1][1] == ' ')
                        {
                            board[1][1] = '0';
                        }
                        else if
                            (board[0][1] == ' ')
                        {
                            board[0][1] = '0';
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
                        break;
                    default:
                        break;
                }
            }

            if (checkWin(board) == 0)
            {
                return NULL;
            }
            
            printBoard(board);
            
            change_turn();
           
            sleep(0);
        }
    } while(gameOver == 0);
    
    return NULL;
}


/* repeat of 0 algorith but with X */
void* comp_aix (void* unused)
{
    int ranNum;
    
    do
    {        
        counter++;
        while (checkTurn() == 1)
        {

            /* Check for 2 Xs in play, to achieve winning state */
        
            if
                ((board[0][0] == 'X' && board[0][1] == 'X' && board[0][2] == ' ')
                 || (board[2][0] == 'X' && board[1][1] == 'X' && board[0][2] == ' ')
                 || (board[2][2] == 'X' && board[1][2] == 'X' && board[0][2] == ' '))
            {
                board[0][2] = 'X';
            }
            else if
                ((board[1][0] == 'X' && board[1][1] == 'X' && board[1][2] == ' ')
                 || (board[0][2] == 'X' && board[2][2] == 'X' && board[1][2] == ' ')
                 || (board [0][2] == 'X' && board[2][0] == 'X' && board[1][2] == ' '))
            {
                board[1][2] = 'X';
            }
            else if
                ((board[2][0] == 'X' && board[2][1] == 'X' && board[2][2] == ' ')
                 || (board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == ' ')
                 || (board[0][2] == 'X' && board[1][2] == 'X' && board[2][2] == ' '))
            {
                board[2][2] = 'X';
            }
            else if
                ((board[1][1] == 'X' && board[2][1] == 'X' && board[0][1] == ' ')
                 || (board[0][0] == 'X' && board[0][2] == 'X' && board[0][1] == ' '))
            {
                board[0][1] = 'X';
            }
            else if
                ((board[0][0] == 'X' && board[2][2] == 'X' && board[1][1] == ' ')
                 || (board[1][0] == 'X' && board[1][2] == 'X' && board[1][1] == ' ')
                 || (board[2][0] == 'X' && board[0][2] == 'X' && board[1][1] == ' ')
                 || (board[0][1] == 'X' && board[2][1] == 'X' && board[1][1] == ' '))
            {
                board[1][1] = 'X';
            }
            else if
                ((board[2][0] == 'X' && board[2][2] == 'X' && board[2][1] == ' ')
                 || (board[0][1] == 'X' && board[1][1] == 'X' && board[2][1] == ' '))
            {
                board[2][1] = 'X';
            }
            else if
                ((board[0][1] == 'X' && board[0][2] == 'X' && board[0][0] == ' ')
                 || (board[1][0] == 'X' && board[2][0] == 'X' && board[0][0] == ' ')
                 || (board[1][1] == 'X' && board[2][2] == 'X' && board[0][0] == ' '))
            {
                board[0][0] = 'X';
            }
            else if
                ((board[0][0] == 'X' && board[2][0] == 'X' && board[1][0] == ' ')
                 || (board[1][1] == 'X' && board[1][2] == 'X' && board[1][0] == ' '))
            {
                board[1][0] = 'X';
            }
            else if
                ((board[0][0] == 'X' && board[1][0] == 'X' && board[2][0] == ' ')
                 || (board[1][1] == 'X' && board[0][2] == 'X' && board[2][0] == ' ')
                 || (board[2][1] == 'X' && board[2][2] == 'X' && board[2][0] == ' '))
            {
                board[2][0] = 'X';
            }
            
            /* Check for 2 0s in play, to avoid losing state */
            
            else if ((board[0][0] == '0' && board[0][1] == '0' && board[0][2] == ' ')
                     || (board[2][0] == '0' && board[1][1] == '0' && board[0][2] == ' ')
                     || (board[2][2] == '0' && board[1][2] == '0' && board[0][2] == ' '))
            {
                board[0][2] = 'X';
            }
            else if
                ((board[1][0] == '0' && board[1][1] == '0' && board[1][2] == ' ')
                 || (board[0][2] == '0' && board[2][2] == '0' && board[1][2] == ' '))
            {
                board[1][2] = 'X';
            }
            else if
                ((board[2][0] == '0' && board[2][1] == '0' && board[2][2] == ' ')
                 || (board[0][0] == '0' && board[1][1] == '0' && board[2][2] == ' ')
                 || (board[0][2] == '0' && board[1][2] == '0' && board[2][2] == ' '))
            {
                board[2][2] = 'X';
            }
            else if
                ((board[1][1] == '0' && board[2][1] == '0' && board[0][1] == ' ')
                 || (board[0][0] == '0' && board[0][2] == '0' && board[0][1] == ' '))
            {
                board[0][1] = 'X';
            }
            else if
                ((board[0][0] == '0' && board[2][2] == '0' && board[1][1] == ' ')
                 || (board[1][0] == '0' && board[1][2] == '0' && board[1][1] == ' ')
                 || (board[2][0] == '0' && board[0][2] == '0' && board[1][1] == ' ')
                 || (board[0][1] == '0' && board[2][1] == '0' && board[1][1] == ' '))
            {
                board[1][1] = 'X';
            }
            else if
                ((board[2][0] == '0' && board[2][2] == '0' && board[2][1] == ' ')
                 || (board[0][1] == '0' && board[1][1] == '0' && board[2][1] == ' '))
            {
                board[2][1] = 'X';
            }
            else if
                ((board[0][1] == '0' && board[0][2] == '0' && board[0][0] == ' ')
                 || (board[1][0] == '0' && board[2][0] == '0' && board[0][0] == ' ')
                 || (board[1][1] == '0' && board[2][2] == '0' && board[0][0] == ' '))
            {
                board[0][0] = 'X';
            }
            else if
                ((board[0][0] == '0' && board[2][0] == '0' && board[1][0] == ' ')
                 || (board[1][1] == '0' && board[1][2] == '0' && board[1][0] == ' '))
            {
                board[1][0] = 'X';
            }
            else if
                ((board[0][0] == '0' && board[1][0] == '0' && board[2][0] == ' ')
                 || (board[1][1] == '0' && board[0][2] == '0' && board[2][0] == ' ')
                 || (board[2][1] == '0' && board[2][2] == '0' && board[2][0] == ' '))
            {
                board[2][0] = 'X';
            }
            
             /* Added randomness so we get multiple game results instead of just one */
            
            else
            {
                srand(time(NULL));
                ranNum = (rand() % 9) + 1;
                switch (ranNum) {
                    case 1:
                        if (board[0][0] == ' ')
                        {
                            board[0][0] = 'X';
                        }
                        else if
                            (board[0][2] == ' ')
                        {
                            board[0][2] = 'X';
                        }
                        else if
                            (board[1][1] == ' ')
                        {
                            board[1][1] = 'X';
                        }
                        else if
                            (board[0][1] == ' ')
                        {
                            board[0][1] = 'X';
                        }
                        else if
                            (board[1][0] == ' ')
                        {
                            board[1][0] = 'X';
                        }
                        else if
                            (board[1][2] == ' ')
                        {
                            board[1][2] = 'X';
                        }
                        else if
                            (board[2][0] == ' ')
                        {
                            board[2][0] = 'X';
                        }
                        else if 
                            (board[2][1] == ' ')
                        {
                            board[2][1] = 'X';
                        }
                        else if 
                            (board[2][2] == ' ')
                        {
                            board[2][2] = 'X';
                        }
                        break;
                    case 2:
                        if (board[0][2] == ' ')
                        {
                            board[0][2] = 'X';
                        }
                        
                        else if
                            (board[1][1] == ' ')
                        {
                            board[1][1] = 'X';
                        }
                        else if
                            (board[0][1] == ' ')
                        {
                            board[0][1] = 'X';
                        }
                        else if
                            (board[1][0] == ' ')
                        {
                            board[1][0] = 'X';
                        }
                        else if
                            (board[1][2] == ' ')
                        {
                            board[1][2] = 'X';
                        }
                        else if
                            (board[2][0] == ' ')
                        {
                            board[2][0] = 'X';
                        }
                        else if
                            (board[2][1] == ' ')
                        {
                            board[2][1] = 'X';
                        }
                        else if
                            (board[2][2] == ' ')
                        {
                            board[2][2] = 'X';
                        }
                        else if
                            (board[0][0] == ' ')
                        {
                            board[0][0] = 'X';
                        }
                        break;
                    case 3:
                        if (board[1][1] == ' ')
                        {
                            board[1][1] = 'X';
                        }
                        else if
                            (board[0][1] == ' ')
                        {
                            board[0][1] = 'X';
                        }
                        else if
                            (board[1][0] == ' ')
                        {
                            board[1][0] = 'X';
                        }
                        else if
                            (board[1][2] == ' ')
                        {
                            board[1][2] = 'X';
                        }
                        else if
                            (board[2][0] == ' ')
                        {
                            board[2][0] = 'X';
                        }
                        else if
                            (board[2][1] == ' ')
                        {
                            board[2][1] = 'X';
                        }
                        else if
                            (board[2][2] == ' ')
                        {
                            board[2][2] = 'X';
                        }
                        else if
                            (board[0][0] == ' ')
                        {
                            board[0][0] = 'X';
                        }
                        else if
                            (board[0][2] == ' ')
                        {
                            board[0][2] = 'X';
                        }
                        break;
                    case 4:
                        if (board[0][1] == ' ')
                        {
                            board[0][1] = 'X';
                        }
                        else if
                            (board[1][0] == ' ')
                        {
                            board[1][0] = 'X';
                        }
                        else if
                            (board[1][2] == ' ')
                        {
                            board[1][2] = 'X';
                        }
                        else if
                            (board[2][0] == ' ')
                        {
                            board[2][0] = 'X';
                        }
                        else if
                            (board[2][1] == ' ')
                        {
                            board[2][1] = 'X';
                        }
                        else if
                            (board[2][2] == ' ')
                        {
                            board[2][2] = 'X';
                        }
                        else if
                            (board[0][0] == ' ')
                        {
                            board[0][0] = 'X';
                        }
                        else if
                            (board[0][2] == ' ')
                        {
                            board[0][2] = 'X';
                        }
                        else if
                            (board[1][1] == ' ')
                        {
                            board[1][1] = 'X';
                        }
                        break;
                    case 5:
                        if (board[1][0] == ' ')
                        {
                            board[1][0] = 'X';
                        }
                        else if
                            (board[1][2] == ' ')
                        {
                            board[1][2] = 'X';
                        }
                        else if
                            (board[2][0] == ' ')
                        {
                            board[2][0] = 'X';
                        }
                        else if
                            (board[2][1] == ' ')
                        {
                            board[2][1] = 'X';
                        }
                        else if
                            (board[2][2] == ' ')
                        {
                            board[2][2] = 'X';
                        }
                        else if
                            (board[0][0] == ' ')
                        {
                            board[0][0] = 'X';
                        }
                        else if
                            (board[0][2] == ' ')
                        {
                            board[0][2] = 'X';
                        }
                        else if
                            (board[1][1] == ' ')
                        {
                            board[1][1] = 'X';
                        }
                        else if
                            (board[0][1] == ' ')
                        {
                            board[0][1] = 'X';
                        }
                        break;
                    case 6:
                        if (board[1][2] == ' ')
                        {
                            board[1][2] = 'X';
                        }
                        else if
                            (board[2][0] == ' ')
                        {
                            board[2][0] = 'X';
                        }
                        else if
                            (board[2][1] == ' ')
                        {
                            board[2][1] = 'X';
                        }
                        else if
                            (board[2][2] == ' ')
                        {
                            board[2][2] = 'X';
                        }
                        else if
                            (board[0][0] == ' ')
                        {
                            board[0][0] = 'X';
                        }
                        else if
                            (board[0][2] == ' ')
                        {
                            board[0][2] = 'X';
                        }
                        else if
                            (board[1][1] == ' ')
                        {
                            board[1][1] = 'X';
                        }
                        else if
                            (board[0][1] == ' ')
                        {
                            board[0][1] = 'X';
                        }
                        else if
                            (board[1][0] == ' ')
                        {
                            board[1][0] = 'X';
                        }
                        break;
                    case 7:
                        if (board[2][0] == ' ')
                        {
                            board[2][0] = 'X';
                        }    
                        else if
                            (board[2][1] == ' ')
                        {
                            board[2][1] = 'X';
                        }
                        else if
                            (board[2][2] == ' ')
                        {
                            board[2][2] = 'X';
                        }
                        else if
                            (board[0][0] == ' ')
                        {
                            board[0][0] = 'X';
                        }
                        else if
                            (board[0][2] == ' ')
                        {
                            board[0][2] = 'X';
                        }
                        else if
                            (board[1][1] == ' ')
                        {
                            board[1][1] = 'X';
                        }
                        else if
                            (board[0][1] == ' ')
                        {
                            board[0][1] = 'X';
                        }
                        else if
                            (board[1][0] == ' ')
                        {
                            board[1][0] = 'X';
                        }
                        else if
                            (board[1][2] == ' ')
                        {
                            board[1][2] = 'X';
                        }
                        break;
                    case 8:
                        if (board[2][1] == ' ')
                        {
                            board[2][1] = 'X';
                        }   
                        else if
                            (board[2][2] == ' ')
                        {
                            board[2][2] = 'X';
                        }
                        else if
                            (board[0][0] == ' ')
                        {
                            board[0][0] = 'X';
                        }
                        else if
                            (board[0][2] == ' ')
                        {
                            board[0][2] = 'X';
                        }
                        else if
                            (board[1][1] == ' ')
                        {
                            board[1][1] = 'X';
                        }
                        else if
                            (board[0][1] == ' ')
                        {
                            board[0][1] = 'X';
                        }
                        else if
                            (board[1][0] == ' ')
                        {
                            board[1][0] = 'X';
                        }
                        else if
                            (board[1][2] == ' ')
                        {
                            board[1][2] = 'X';
                        }
                        else if
                            (board[2][0] == ' ')
                        {
                            board[2][0] = 'X';
                        }
                        break;
                    case 9:
                        if (board[2][2] == ' ')
                        {
                            board[2][2] = 'X';
                        }
                        else if
                            (board[0][0] == ' ')
                        {
                            board[0][0] = 'X';
                        }
                        else if
                            (board[0][2] == ' ')
                        {
                            board[0][2] = 'X';
                        }
                        else if
                            (board[1][1] == ' ')
                        {
                            board[1][1] = 'X';
                        }
                        else if
                            (board[0][1] == ' ')
                        {
                            board[0][1] = 'X';
                        }
                        else if
                            (board[1][0] == ' ')
                        {
                            board[1][0] = 'X';
                        }
                        else if
                            (board[1][2] == ' ')
                        {
                            board[1][2] = 'X';
                        }
                        else if
                            (board[2][0] == ' ')
                        {
                            board[2][0] = 'X';
                        }
                        else if
                            (board[2][1] == ' ')
                        {
                            board[2][1] = 'X';
                        }
                        break;
                    default:
                        break;
                }
            }
            
            
            if (checkWin(board) == 0)
            {
                return NULL;
            }
            
            printBoard(board);
            
            change_turn();
            
            
            sleep(0);
        }
    } while(gameOver == 0);
       
    return NULL;
}


/* allow player 1 input */
void* humanTurn(void* unused)
{
	int x, y;
    do
    {
        counter++;
        while (checkTurn() == 1);
        {
            do
            {
                do
                {   
                    sleep(1); 
                    printf("Enter row number: ");
        
                    /* Need to not use scanf, its error checking is shit. */
                    scanf("%d", &x);
                    if (x < 1 || x > ROWS)
                    {
                        printf("\nA number between 1 and 3 please!\n");
                    }
                } while (x < 1 || x > ROWS);
                x--;
    
                do
                {
                    printf("Enter column number: ");
                    scanf("%d", &y);;
                    if (y < 1 || y > COLUMNS)
                    {
                        printf("\nA number between 1 and 3 please!\n");
                    }
                } while (y < 1 || y > COLUMNS);
                y--;
    
                /* Make sure the position entered is empty */
    
                if (board[x][y] != ' ')
                {
                    printf("\nThat position is filled! Try again!\n");
                }
            } while (board[x][y] != ' ');
        
            board[x][y] = 'X';
        
            if (checkWin(board) == 0)
            {
                return NULL;
            }
        
            printBoard(board);
        
            change_turn();
        
            sleep(0);
        }
            
    } while (gameOver == 0);
}

/* allow player 2 input */
void* human2Turn(void* unused)
{
    int x, y;
    do
    {   counter++;
        while (checkTurn() == 2);
        {
            do
            {
                do
                {	
                    printf("Player 2 Enter row number: ");
                    
                    /* Need to not use scanf, its error checking is shit. */
                    scanf("%d", &x);
                    if (x < 1 || x > ROWS)
                    {
                        printf("\nA number between 1 and 3 please!\n");
                    }
                } while (x < 1 || x > ROWS);
                x--;
                
                do
                {
                    printf("Player 2 Enter column number: ");
                    scanf("%d", &y);;
                    if (y < 1 || y > COLUMNS)
                    {
                        printf("\nA number between 1 and 3 please!\n");
                    }
                } while (y < 1 || y > COLUMNS);
                y--;
                
                /* Make sure the position entered is empty */
                
                if (board[x][y] != ' ')
                {
                    printf("\nThat position is filled! Try again!\n");
                }
            } while (board[x][y] != ' ');
            
            board[x][y] = '0';
            
            if (checkWin(board) == 0)
            {
                return NULL;
            }
            
            printBoard(board);
            
            change_turn();
            
            sleep(0);
        }
        
    } while (gameOver == 0);
}

/* start 2 CPU threads */
void cpuVsCpu()
{
    pthread_create (&threadId[0], NULL, &comp_aix, NULL);
    
    pthread_create (&threadId[1], NULL, &comp_ai0, NULL);
    
    pthread_join(threadId[0], NULL);
    pthread_join(threadId[1], NULL);

    
}


/* start a human and a CPU thread */
void humanVsCpu()
{
    pthread_create (&threadId[0], NULL, &humanTurn, NULL);
    
    pthread_create (&threadId[1], NULL, &comp_ai0, NULL);
    
    pthread_join(threadId[0], NULL);
    pthread_join(threadId[1], NULL);

}


/* start 2 human threads */
void humanVshuman()
{

    pthread_create (&threadId[0], NULL, &humanTurn, NULL);
    
    pthread_create (&threadId[1], NULL, &human2Turn, NULL);
    
    pthread_join(threadId[0], NULL);
    pthread_join(threadId[1], NULL);
    
}

int main ()
{
//    int inputChar;
//    
//    /* Display Menu */
//    displayMenu();
//    
//    /* Take input */
//    inputChar = getchar();
//    
//    /* Display Board */
//    printBoard(board);
//    
//    switch (inputChar) {
//        case '1':
//            cpuVsCpu();
//            break;
//        case '2':
//            humanVsCpu();
//            break;
//        case '3':
//            humanVshuman();
//            break;
//    }
    int i;
    
    for (i = 0; i < 1000; i++) {
        cpuVsCpu();
    }

    
    pthread_mutex_destroy(&lock1);
    pthread_mutex_destroy(&lock2);
    pthread_mutex_destroy(&lock3);
    pthread_mutex_destroy(&lock4);
    
    printf("%d",counter);
    
    return 0;

}