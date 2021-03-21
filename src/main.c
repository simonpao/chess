/* Simon Paonessa
 * Chess Game, main.c
 */

#include "globals.h"
#include <stdio.h>
#include <stdlib.h>

// Program entry point
int main()
{
	char s[2];			// Container for player starting position input
	char f[2];			// Container for player ending position input
	state *b;			/* Pointer to a board structure (defined in globals.h)
						 * Memory to be allocated later
						 */
	int i, j, k, l;		// Placeholders for integer values of start and end location
	status rc = ERROR;	/* Placeholder for status of the player move
						 * Valid input will cause rc to be assigned value OK
						 * Defult value is ERROR before each move until OK status is determined
						 */
	int p ;				// Placeholder for user input of number of players
	int gameStat = 0;	// Variable for status of chess game (i.e. check=1, checkmate=2 or normal=0)

	// boardMaps for each player piece, declared as length 16 arrays, one for each piece
	boardMap ply1[16], ply2[16];

	// Allocate memory for the game board
	b = (state *) malloc (sizeof(state));
	b->value = 0;

	system("clear");			// Clear all text from the command line

	initBoard(b->br);			// Initialize the board array with open and filled spaces
	setPieces(b->br);			// Set the pieces in their initial positions on the board
	setBoardMap(ply1, ply2);	/* Initialize the position of each player piece in their 
								 * boardMap variable for starting locations
								 */
	do { // Loop through asking the number of players while the user has not entered either 1 or 2
		// Ask the user for the number of players who will be playing the game and accept input
		printf("Number of players(1 or 2): ");
		scanf("%d", &p);
		if(p < 1 || p > 2)  // If the input is not either 1 or 2
		{
			// Print error
			printf(CYN "Invalid number of players.\n" RESET);
		}
	} while( p < 1 || p > 2 ) ;

	system("clear");		// Clear all text from the command line
	printBoard(b->br);      // Print the characters of the board on the command line

	if ( p == 2 )	// If the user selected two player modesing
	{
		while(gameStat < CHECKMATE)	// While the game is in a state of either normal (0) or check (1)
		{
			// While still waiting for a valid move and game is not in a state of checkmate (2)
			while(rc != OK && gameStat != CHECKMATE)
			{	// Prompt for player one move input
				printf(YEL "Player one, enter move: " RESET);
				scanf("%s %s", s, f);

				// Evaluate the legitimacy of the move
				rc = evalMove(s, f, &i, &j, &k, &l);
				// Make the move to the user defined location
				rc = makeMove(b->br, i, j, k, l, PLAYERONE, ply1);

				// If the move could not be made, inform the user and prompt them again
				if(rc == ERROR)
					printf("Invalid move.\n");
			}
			system("clear");	// Clear all text from the command line
			printBoard(b->br);	// Print the board with the moved piece in its new position
			if((gameStat = kingInCheck(ply2, b->br, PLAYERONE)) > 0)	// If move causes state of check
				printCheckMsg(gameStat, PLAYERONE);						// print the message to the user
			rc = ERROR;			// Assign rc the value of ERROR once again for the next player's move

			// While still waiting for a valid move and game is not in a state of checkmate (2)
			while(rc != OK && gameStat != CHECKMATE)
			{	// Prompt for player one move input
				printf(GRN "Player two, enter move: " RESET);
				scanf("%s %s", s, f);

				// Evaluate the legitimacy of the move
				rc = evalMove(s, f, &i, &j, &k, &l);
				// Make the move to the user defined location
				rc = makeMove(b->br, i, j, k, l, PLAYERTWO, ply2);

				// If the move could not be made, inform the user and prompt them again
				if(rc == ERROR)
					printf("Invalid move.\n");
			}
			system("clear");	// Clear all text from the command line
			printBoard(b->br);	// Print the board with the moved piece in its new position
			if((gameStat = kingInCheck(ply1, b->br, PLAYERTWO)) > 0)	// If move causes state of check
				printCheckMsg(gameStat, PLAYERTWO);						// print the message to the user
			rc = ERROR;			// Assign rc the value of ERROR once again for the next player's move
		}
	}
	else if(p == 1) // Single player mode is not yet implemented
	{
		printf("Single player mode is not yet implemented.\n");
	}
	return 0; // End program
}
