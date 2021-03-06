/* 
* Naughts and Crosses
* Operating System Principles
* Semester 2 2013
* RMIT
* Christian Rivers s3300619
* Created 14/09/2013 
* VERSION 0.4
*
* gcc -W -Wall -pthread -ansi -o tictactoe tictactoe.c
*/




#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#define ROWS 3
#define COLUMNS 3

void printBoard(char board[][COLUMNS]);
void* compGeniusX(void *arg);
void* compGenius0(void *arg);
int checkWin(char board[][COLUMNS]);

int turn = 1;
int gameOver = 0;
pthread_t threadId[2];
pthread_mutex_t lock;


/* Create Board */
char board[ROWS][COLUMNS] = {
    {' ', ' ', ' '} ,
    {' ', ' ', ' '} ,
    {' ', ' ', ' '}
};


int main()
{
    int err;
	
	/* Display Board */
	printBoard(board);
	
    
    /* Start game */
    
    /* crete thread 1 */
    
    err = pthread_create(&(threadId[0]), NULL, &compGeniusX, NULL);
    if (err != 0)
    {
        printf("\ncan't create thread :[%s]", strerror(err));
    }
    
     /* crete thread 2 */
    
    err = pthread_create(&(threadId[1]), NULL, &compGenius0, NULL);
    if (err != 0)
    {
        printf("\ncan't create thread :[%s]", strerror(err));
    }
    
    pthread_join(threadId[0], NULL);
    pthread_join(threadId[1], NULL);
    pthread_mutex_destroy(&lock);
    
	
	return 0;
}

void printBoard(char board[][COLUMNS])
{
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
}

void* compGeniusX(void *arg)
{
    do
    {
        pthread_mutex_lock(&lock);
        
        while (turn == 1 && gameOver == 0)
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
            
            /* Other moves */
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
            else if 
                (board[2][2] == ' ')
            {
                board[2][2] = 'X';
            }
            if (checkWin(board) == 0)
            {
                return NULL;
            }
            printBoard(board);
            
            turn = 2;
            
            /*pthread_mutex_unlock(&lock);*/
            printf("end of thread 1\n");
            sleep(1);
        }
    } while(gameOver == 0);
    
    return NULL;

}

/* Computer AI logic */
void* compGenius0(void *arg)
{
    do
    {
        pthread_mutex_lock(&lock);
        
        while (turn == 2 && gameOver == 0) {
            /* Check for 2 0s in play, to achieve winning state */
            
            if ((board[0][0] == '0' && board[0][1] == '0' && board[0][2] == ' ')
                || (board[2][0] == '0' && board[1][1] == '0' && board[0][2] == ' ')
                || (board[2][2] == '0' && board[1][2] == '0' && board[0][2] == ' '))
            {
                board[0][2] = '0';
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
                 || (board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == ' ')
                 || (board[0][2] == 'X' && board[1][2] == 'X' && board[2][2] == ' '))
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
                return NULL;
            }
            printBoard(board);
            turn = 1;
            pthread_mutex_unlock(&lock);
            printf("end of thread 2\n");
            sleep(1);
        }
    } while(gameOver == 0);
    
    return NULL;
}

int checkWin(char board[][COLUMNS])
{
    pthread_mutex_lock(&lock);
    
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
		printf("\nCongratulations player!!! You is winner!\n");
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
	 	printf("\n I beat u, suck it!!!\n");
		return 0;
	}
	
	/* Check for a draw */
	
	else if (board[0][0] != ' ' && board[0][1] != ' ' && board[0][2] != ' '
		&& board[1][0] != ' ' && board[1][1] != ' ' && board[1][2] != ' '
		&& board[2][0] != ' ' && board[2][1] != ' ' && board[2][2] != ' ')
	{
		printBoard(board);
        gameOver = 1;
		printf("\nBoring!! A draw!\n");
		return 0;
	}
    
    pthread_mutex_unlock(&lock);
	
	return 1;
	
}


