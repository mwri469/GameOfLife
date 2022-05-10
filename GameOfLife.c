/********************************************************
*                 Conways Game of Life                  *
*   The Game of Life is a cellular automaton devised    *
*   by the British mathematician John Horton Conway     *
*   in 1970.                                            *
*   This is my attempt at a a adaptation using basic    *
*                       Author:                         *
*                    Martin  Wright                     *
*                      11 OCT 2021                      *
*********************************************************/
// Character is █
#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#define _CRT_SECURE_NO_WARNINGS
#define NUM_ROWS 22
#define NUM_COLS 64


void PrintArray(int cells[NUM_ROWS][NUM_COLS]);
int CheckNeighbours(int cells[NUM_ROWS][NUM_COLS], int position);
void PrintPositions(void);
void NextIter(int cells[NUM_ROWS][NUM_COLS]);
void PrintBanner(void);
void GetNeighbours(int cells[NUM_ROWS][NUM_COLS], int i, int j, int *L, int *R, int *U, int *D, int *UL, int *UR, int *DL, int *DR);
int CountNeighbours(int L, int R, int U, int D, int UL, int UR, int DL, int DR);
void CreatePattern(int cells[NUM_ROWS][NUM_COLS]);
void InitialiseCells(int cells[NUM_ROWS][NUM_COLS]);
void CreateGlider(int cells[NUM_ROWS][NUM_COLS], int position);
void CreatePentaDecathlon(int cells[NUM_ROWS][NUM_COLS], int position);
int GetPosition(int i, int j);
void CreateGliderGun(int cells[NUM_ROWS][NUM_COLS], int position);
void CreateSquare(int cells[NUM_ROWS][NUM_COLS], int position);

int main(void)
{
    system("cls"); // Clear the console
    
    int user, isTrue = 1, iteration = 0, maxIter; // Initialise values

    PrintBanner(); // Print the game banner

    printf("What is the maximum number of iterations to run?\n");
    scanf("%d", &maxIter);
    system("cls");
    PrintBanner();
    int cells[NUM_ROWS][NUM_COLS] = { 0 };
    InitialiseCells(cells); 
    CreatePentaDecathlon(cells, 348);
    PrintArray(cells); // Initialise the array and display it to the user

    while (isTrue) {
        printf("next iteration?\n"); // Ask if the user wants to iterate again
        scanf("%d", &user);
        if (user){
            // Place cursor to print over the old game
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            COORD pos = {0, 3};
            SetConsoleCursorPosition(hConsole, pos);
            WriteConsole(hConsole, "", 5, NULL, NULL);
            NextIter(cells);
            PrintArray(cells);
            if (iteration > maxIter) {
                isTrue = 0;
            }
            iteration++;
        } else {
            // User wants to finish
            
            isTrue = 0; // Exits the while loop
        }
    }
    printf("\n\n");
    printf("=================The end.=================\n");
    printf("       %d iterations were completed.\n\n", iteration - 1);

    
    return 0;
}

/*
    cl /W4 GameOfLife.c
    GameOfLife
    1\n
*/

int GetPosition(int i, int j) {
    /*
    *********************************************************
    *   This function returns the position of a set of      *
    *   row and column co ordinates.                        *
    *********************************************************/
    return (i * NUM_COLS) + j;
}

void CreateGliderGun(int cells[NUM_ROWS][NUM_COLS], int position) {
    int i, j, currentPos, newPos;
    for (i = 0; i < NUM_ROWS; i++) {
        for (j = 0; j < NUM_COLS; j++) {
            currentPos = (NUM_COLS * i) + j;
            if (currentPos == position) {
                CreateSquare(cells, currentPos);
                newPos = GetPosition(i - 2, j + 34);
                CreateSquare(cells, newPos);
            } else if (currentPos == position + 10) {
                cells[i][j] = 1; cells[i + 1][j] = 1; cells[i + 2][j] = 1;
                cells[i - 1][j + 1] = 1; cells[i - 2][j + 2] = 1; cells[i - 2][j + 3] = 1;
                cells[i + 3][j + 1] = 1; cells[i + 4][j + 2] = 1; cells[i + 4][j + 3] = 1;
                cells[i + 1][j + 4] = 1; cells[i - 1][j + 5] = 1; cells[i + 3][j + 5] = 1;
                cells[i][j + 6] = 1; cells[i + 1][j + 6] =1; cells[i + 2][j + 6] = 1; cells[i + 1][j + 7] = 1;
                newPos = GetPosition(i - 2, j + 10);
                CreateSquare(cells, newPos);
                cells[i][j + 10] = 1; cells[i][j + 11] = 1; cells[i - 3][j + 12] = 1; cells[i + 1][j + 12] = 1;
                cells[i - 4][j + 14] = 1; cells[i - 3][j + 14] = 1; cells[i + 1][j + 14] = 1; cells[i + 2][j + 14] = 1;
            }
        }
    }
}

void CreateSquare(int cells[NUM_ROWS][NUM_COLS], int position) {
    int i, j, currentPos;
    for (i = 0; i < NUM_ROWS; i++) {
        for (j = 0; j < NUM_COLS; j++) {
            currentPos = (NUM_COLS * i) + j;
            if (currentPos == position) {
                cells[i][j] = 1;
                cells[i][j + 1] = 1;
                cells[i + 1][j] = 1;
                cells[i + 1][j + 1] = 1;
                return;
            }
        }
    }
}

void CreatePentaDecathlon(int cells[NUM_ROWS][NUM_COLS], int position) {
    /*
    *********************************************************
    *   This function creates a penta-decathlon at the      *
    *   position dictated by the user.                      *
    *********************************************************/
    int i, j, k, currentPos;
    for (i = 0; i < NUM_ROWS; i++) {
        for (j = 0; j < NUM_COLS; j++) {
            currentPos = (i * NUM_COLS) + j;
            if (currentPos == position) {
                for (k = 0; k < 10; k++) {
                    if (k == 2 || k == 7) {
                        cells[i + k][j + 1] = 1;
                        cells[i + k][j - 1] = 1;
                    } else {
                        cells[i + k][j] = 1;
                    }
                }
            }
        }
    }
}

void CreateGlider(int cells[NUM_ROWS][NUM_COLS], int position) {
    /********************************************************
    *   This function simply initialises an example         *
    *   pattern for a run of the game of life.              *
    *   The position input refers to the top cell           *
    *   position.                                           *
    *   When complete, the pattern should look like:        *
    *                                                       *
    *                          █                            *
    *                        █ █                            *
    *                         ██                            *
    *                                                       *
    *********************************************************/
   int i, j, k, currentPos;
   for (i = 0; i < NUM_ROWS; i++) {
       for (j = 0; j < NUM_COLS; j++) {
            currentPos = (i * NUM_COLS) + j;
            if (currentPos == position) {
                
                for (k = 0; k < 3; k++) {
                   cells[i + k][j] = 1;
                }
                cells[i + 2][j - 1] = 1;
                cells[i + 1][j - 2] = 1;
            }
       }
   }
    cells[5][4] = 1;
    cells[4][3] = 1;
}

void InitialiseCells(int cells[NUM_ROWS][NUM_COLS]) {
    /********************************************************
    *   This function initialises the game array that we    *
    *   use to play the game of life.                       *
    *   A value of 0 means the cell is dead.                *
    *   A value of 1 means the cell is alive.               *
    *   A value of 2 means it forms the border              *
    *********************************************************/
   int i, j; // Initialise parameters
   for (i = 0; i < NUM_ROWS; i++) {
       for (j = 0; j < NUM_COLS; j++) {
           if (!i || !j || i == NUM_ROWS - 1 || j == NUM_COLS - 1) {
               cells[i][j] = 2; // Border cell
           } else {
               cells[i][j] = 0; // Dead cell, as the game has not started yet
           }
       }
   }
}

void CreatePattern(int cells[NUM_ROWS][NUM_COLS]) {
    /********************************************************
    *   This function simply initialises an example         *
    *   pattern for a run of the game of life.              *
    *   When complete, the pattern should look like:        *
    *                                                       *
    *                          █                            *
    *                         ███                           *
    *                                                       *
    *********************************************************/
    cells[(NUM_ROWS / 2) - 1][(NUM_COLS / 2) - 1]  = 1; // Middle bottom
    cells[(NUM_ROWS / 2) - 1][(NUM_COLS / 2) - 2]  = 1; // Bottom left
    cells[(NUM_ROWS / 2) - 1][(NUM_COLS / 2)]  = 1; // Bottom right
    cells[(NUM_ROWS / 2) - 2][(NUM_COLS / 2) - 1]  = 1; // Top
}

void PrintBanner(void) {
    /********************************************************
    *   This function prints the banner for the game.       *
    *********************************************************/
    printf("............***************************............\n");
	printf("............* GAME OF LIFE SIMULATION *............\n");
	printf("............***************************............\n");
}

void PrintArray(int cells[NUM_ROWS][NUM_COLS]) {
    /********************************************************
    *   This is a simple function that prints out the       *
    *   array representing the game.                        *
    *********************************************************/
    int i, j; // Initialise counters
    
    setlocale(LC_ALL, "en_US.UTF-8"); // Create a solid block that will represent a live cell
    wchar_t box = 0x2588;

    for (i = 0; i < NUM_ROWS; i++) {
        
        for (j = 0; j < NUM_COLS; j++) { // Nested for loop runs thru entire board

            if (cells[i][j] == 2) {
                printf("*"); // Print a border
            } else if (cells[i][j]) {
                printf("%lc", box); // Print the solid block for all live cells

            } else if (!cells[i][j]) {
                printf(" "); // Print an empty space for dead cells
            }
        }
        printf("\n");
    }
    printf("\n");
}

void PrintPositions(void) {
    /********************************************************
    *   Sometimes it can be difficult trying to             *
    *   visualise the array, so I have created this         *
    *   function to make locating each position easier      *
    *********************************************************/
    int i, j, pos; // Initialise values

    for (i = 0; i < NUM_ROWS; i++) {
        for (j = 0; j < NUM_COLS; j++) {

            pos = (i * NUM_COLS) + j; // Checks current position

            if (pos < 10) {
                printf("%d  ", pos); // Prints a single digit
            } else {
                printf("%d ", pos); // Prints 2 digits
            }
        }
        printf("\n");
    }
    printf("\n");
}

int CheckNeighbours(int cells[NUM_ROWS][NUM_COLS], int position) {
    /********************************************************
    *   This function is given a cell on the board and      *
    *   checks if the cell should live or die.              *
    *   If the cell survives this iteration, it returns     *
    *   a 1. Otherwise, the cell dies and the function      *
    *   returns a 0.                                        *
    *********************************************************/
    // Initialise counters
    int i, j, currentPos, numAlive = 0;
    // Initialise positions
    int left, right, up, down, upLeft, upRight, downLeft, downRight;

    for (i = 0; i < NUM_ROWS; i++) {
        for (j = 0; j < NUM_COLS; j++) {
            currentPos = (i * NUM_COLS) + j;
            if (!i || !j || i == NUM_ROWS - 1 || j == NUM_COLS - 1) {
                cells[i][j] = 2;
            
            } else if (currentPos == position && cells[i][j] == 1) { // Checks the living cells
                // Get the number of living neighbours
                GetNeighbours(cells, i, j, &left, &right, &up, &down, &upLeft, &upRight, &downLeft, &downRight);
                numAlive = CountNeighbours(left, right, up, down, upLeft, upRight, downLeft, downRight);
                
                if (numAlive < 2 || numAlive > 3) { // Is the cell alive for the next iteration?
                    return 0;
                } else {
                    return 1;
                }
            } else if (currentPos == position && !cells[i][j]) { // Checks the dead cells
                // Get the number of living neighbours
                GetNeighbours(cells, i, j, &left, &right, &up, &down, &upLeft, &upRight, &downLeft, &downRight);
                numAlive = CountNeighbours(left, right, up, down, upLeft, upRight, downLeft, downRight);
                
                if (numAlive == 3) { // Is the cell alive for the next iteration?
                    return 1;
                } else {
                    return 0;
                }
            } 
        }
        
    }
    
}

void GetNeighbours(int cells[NUM_ROWS][NUM_COLS], int i, int j, int *L, int *R, int *U, int *D, int *UL, int *UR, int *DL, int *DR) {
    /********************************************************
    *   This function obtains the position of               *
    *   neighbouring cells to a given coordinate on the     *
    *   array, and assigns the position of each adjacent    *
    *   cell to the pointers given as inputs.               *
    *********************************************************/
    *L = cells[i][j - 1];
    *R = cells[i][j + 1];
    *U = cells[i - 1][j];
    *D = cells[i + 1][j];
    *UL = cells[i - 1][j - 1];
    *UR = cells[i - 1][j + 1];
    *DL = cells[i + 1][j - 1];
    *DR = cells[i + 1][j + 1];

}

int CountNeighbours(int L, int R, int U, int D, int UL, int UR, int DL, int DR) {
    /********************************************************
    *   This function takes the state of adjacent cells     *
    *   and outputs how many are alive.                     *
    
    *********************************************************/
    int count = 0; // Initialise the counter
    if (L == 1) {
        count++;
    }
    if (R == 1) {
        count++;
    }
    if (U == 1) {
        count++;
    }
    if (D == 1) {
        count++;
    }
    if (UL == 1) {
        count++;
    }
    if (UR == 1) {
        count++;
    }
    if (DL == 1) {
        count++;
    }
    if (DR == 1) {
        count++;
    }
    return count; // Return how many are alive
}

void NextIter(int cells[NUM_ROWS][NUM_COLS]) {
    /********************************************************
    *   This function runs one iteration of the game,       *
    *   killing and bringing to life the appropriate        *
    *   cells.                                              *
    *********************************************************/
    // Initialise values
    int i, j, isAlive, currentPos;
    // Create similar array to copy values for the next iteration
    int cellsReplica[NUM_ROWS][NUM_COLS] = { 0 }; 
    InitialiseCells(cellsReplica);

    for (i = 0; i < NUM_ROWS; i++) {
        for (j = 0; j < NUM_COLS; j++) {
            currentPos = (i * NUM_COLS) + j; // Checks the current position
            
            isAlive = CheckNeighbours(cells, currentPos); // Checks if the cell will be alive

            if (isAlive) {
                // If the cell is alive, change the replica array
                cellsReplica[i][j] = 1;
            }
        }
    } 
    for (i = 0; i < NUM_ROWS; i++) {
        for (j = 0; j < NUM_COLS; j++) {
            if (!i || !j || i == NUM_ROWS - 1 || j == NUM_COLS - 1) {
                cells[i][j] = 2;
            } else {
                cells[i][j] = cellsReplica[i][j]; // Transfers replica array to actual array
            }
            
        }
    } 
}
