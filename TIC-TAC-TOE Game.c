#include<stdio.h>
#include<stdlib.h>
struct Player
{
	char symbol;
	int score;
};
char** initializeGrid() 
{
    char** grid = (char**)malloc(3 * sizeof(char*));
    int i,j;
    for (i = 0; i < 3; i++) 
	{
        grid[i] = (char*)malloc(3 * sizeof(char));
        for (j = 0; j < 3; j++) 
		{
            grid[i][j] = ' ';
        }
    }
    return grid;
}
void printGrid(char** grid) 
{
    printf("\n");
    int i,j;
    for (i = 0; i < 3; i++) 
	{
        for (j = 0; j < 3; j++) 
		{
            printf(" %c ", grid[i][j]);
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("---|---|---\n");
    }
    printf("\n");
}
int checkWin(char** grid, char symbol) 
{
    int i;
    for (i = 0; i < 3; i++) 
	{
        if ((grid[i][0] == symbol && grid[i][1] == symbol && grid[i][2] == symbol) ||
            (grid[0][i] == symbol && grid[1][i] == symbol && grid[2][i] == symbol)) 
		{
            return 1;
        }
    }
    if ((grid[0][0] == symbol && grid[1][1] == symbol && grid[2][2] == symbol) ||
        (grid[0][2] == symbol && grid[1][1] == symbol && grid[2][0] == symbol)) 
	{
        return 1;
    }
    return 0;
}
int main() 
{
    // Initialize players
    struct Player playerX = {'X', 0};
    struct Player playerO = {'O', 0};
    struct Player* currentPlayer;
    
    // Initialize the grid
    char** grid = initializeGrid();
    
    int moves = 0;
    int row, col;
    int gameWon = 0;

    // Game loop (max 9 moves)
    while (moves < 9 && !gameWon) 
	{
        currentPlayer = (moves % 2 == 0) ? &playerX : &playerO;

        // Print current grid
        printGrid(grid);
        
        // Get input from the current player
        printf("Player %c, enter your move (row and column): ", currentPlayer->symbol);
        scanf("%d %d", &row, &col);
        
        // Validate input
        if (row < 1 || row > 3 || col < 1 || col > 3 || grid[row-1][col-1] != ' ') 
		{
            printf("Invalid move. Try again.\n");
            continue;
        }
        
        // Update the grid
        grid[row-1][col-1] = currentPlayer->symbol;
        moves++;
        
        // Check if the current player has won
        if (checkWin(grid, currentPlayer->symbol)) 
		{
            printGrid(grid);
            printf("Player %c wins!\n", currentPlayer->symbol);
            currentPlayer->score = 1;
            gameWon = 1;
        }
    }
    if (!gameWon) 
	{
        printGrid(grid);
        printf("It's a tie!\n");
    }
    int i;
    for (i = 0; i < 3; i++) 
	{
        free(grid[i]);
    }
    free(grid);

    return 0;
}


