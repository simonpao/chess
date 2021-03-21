/* Simon Paonessa
 * Chess Game, move.c
 */

#include "globals.h"
#include <ctype.h>
#include <stdlib.h>

/* Will evaluate user input to determine first if it is valid input
 * and second to convert input into numberic, program readable values
 * e.g. input of "2B 4B" will assign i=2, j=2, k=4, l=2
 */
extern status evalMove(char s[], // Starting position of player move (e.g. 1A)
					   char f[], // Ending position of player move
					   int *i,   // Pointer to varible in main function, will hold integer value of starting row
					   int *j,   // Pointer to varible in main function, will hold integer value of starting column
					   int *k,   // Pointer to varible in main function, will hold integer value of ending row
					   int *l)	 // Pointer to varible in main function, will hold integer value of ending column
{
	// If starting and ending rows are not digits and columns are not letters...
	if(!(isalpha(s[1]) || isdigit(s[0]) || isalpha(f[1]) || isdigit(f[0])))
		return ERROR;

	// If evalRow returns an error
	if((*j = evalRow(s[1])) == 0)
		return ERROR;

	// convert character into integer
	*i = atoi(&s[0]);

	// If evalRow returns an error
	if((*l = evalRow(f[1])) == 0)
		return ERROR;

	// convert character into integer
	*k = atoi(&f[0]);

	// the input is valid
	return OK;
}
/* Will return integer value for column letter
 */
extern int evalRow(char row)
{
	// Return the corresponding integer value for the passed row value
	switch(toupper(row))
	{
		case 'A': return 1 ;
		case 'B': return 2 ;
		case 'C': return 3 ;
		case 'D': return 4 ;
		case 'E': return 5 ;
		case 'F': return 6 ;
		case 'G': return 7 ;
		case 'H': return 8 ;
		default:  return 0 ; // Error value
	}
}
/* Will evaluate user move to determine if it is valid based on the bounds
 * of the chess board and the piece belonging to the current player.
 *
 * Will also call function validMove() in order to make sure that the move
 * is valid based on the chess piece in question.
 *
 * If the move is valid, the piece will be moved to the specified space and
 * any opponent piece will be removed from the game.
 */
extern status makeMove(board b,			// The current board configuration
					   int si,			// Starting player move row
					   int sj,			// Starting player move column
					   int fi,			// Ending player move row
					   int fj,			// Ending player move column
					   player ply,		// Current player (PLAYERONE or PLAYERTWO)
					   boardMap map[])	// Current configuration of player pieces
{
	// If the move is outside the bounds of the board, return error
	if(fi < BMIN || fi > BMAX || fj < BMIN || fj > BMAX)
		return ERROR;

	// If the piece in the starting location is not the current player's piece, return error
	if(ply == PLAYERONE && islower(b[si][sj])) return ERROR;
	if(ply == PLAYERTWO && isupper(b[si][sj])) return ERROR;

	// If validMove returns false, return error
	if(validMove(b[si][sj], b, si, sj, fi, fj) == FALSE)
		return ERROR;

	// If the ending location is not empty...
	if(b[fi][fj] != OPEN)
		deleteFromBoardMap(fi, fj, map); // delete that piece from the board

	// Copy the piece from the starting location to the ending location in the array
	b[fi][fj] = b[si][sj];
	// Make the starting location in the array open
	b[si][sj] = OPEN;

	// Will update the player's boardMap to place the moved piece into its new location
	updateBoardMap(map, si, sj, fi, fj);
	return OK;	// No error occured, so return OK
}
/* Will update a boardMap piece location to its new location
 */
extern void updateBoardMap(boardMap map[],	// Current configuration of player pieces
						   int si,			// Starting player move row
						   int sj,			// Starting player move column
						   int fi,			// Ending player move row
						   int fj)			// Ending player move column
{
	int i;
	// Find the piece based on starting location provided
	for(i=0; i<16; i++)
		if(map[i].i == si && map[i].j == sj)
		{
			// update location to new location provided
			map[i].i = fi;
			map[i].j = fj;
			break;
		}
}
/* Deletes a player's peice from the board map
 */
extern void deleteFromBoardMap(int i,			// Row of piece to remove
							   int j,			// Column of piece to remove
							   boardMap map[])	// Current configuration of player pieces
{
	int k;
	
	for(k=0; k<16; k++)
		if(map[k].i == i && map[k].j == j)
		{
			// Assign value of -1, meaning piece is off board
			map[k].i = -1;
			map[k].j = -1;
			break;
		}
}
/* Setup the initial board map at the beginning of the game
 * This function will only be called at the beginning of a new game,
 * and will assign all peices on each player's board map their starting coordinates
 */
extern void setBoardMap(boardMap map1[], boardMap map2[])
{
	int i, j=8;

	// Kings starting position
	map1[0].p = KING; map1[0].i = BMIN; map1[0].j = BMIN+3;
	map2[0].p = CKING; map2[0].i = BMAX; map2[0].j = BMAX-3;

	// Queens starting position
	map1[1].p = QUEEN; map1[1].i = BMIN; map1[1].j = BMAX-3;
	map2[1].p = CQUEEN; map2[1].i = BMAX; map2[1].j = BMIN+3;

	// The four rooks (two for each player)
	map1[2].p = map1[3].p = ROOK;
	map2[2].p = map2[3].p = CROOK;
	map1[2].i = BMIN; map1[2].j = BMIN;
	map1[3].i = BMIN; map1[3].j = BMAX;
	map2[2].i = BMAX; map2[2].j = BMIN;
	map2[3].i = BMAX; map2[3].j = BMAX;

	// The four knights (two for each player)
	map1[4].p = map1[5].p = KNIGHT;
	map2[4].p = map2[5].p = CKNIGHT;
	map1[4].i = BMIN; map1[4].j = BMIN+1;
	map1[5].i = BMIN; map1[5].j = BMAX-1;
	map2[4].i = BMAX; map2[4].j = BMIN+1;
	map2[5].i = BMAX; map2[5].j = BMAX-1;

	// The four bishops (two for each player)
	map1[6].p = map1[7].p = BISHOP;
	map2[6].p = map2[7].p = CBISHOP;
	map1[6].i = BMIN; map1[6].j = BMIN+2;
	map1[7].i = BMIN; map1[7].j = BMAX-2;
	map2[6].i = BMAX; map2[6].j = BMIN+2;
	map2[7].i = BMAX; map2[7].j = BMAX-2;

	// set eight pawns for each player
	for(i=BMIN; i<=BMAX; i++)
	{
		map1[j].p = PAWN; map2[j].p = CPAWN;
		map1[j].i = BMIN+1; map2[j].i = BMIN-1;
		map1[j].j = i; map2[j].j = i;
		j++;
	}
}
