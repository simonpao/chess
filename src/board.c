/* Simon Paonessa
 * Chess Game, board.c
 */

#include "globals.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* Set the board with initial filled and unfilled positions
 * i.e. First two and last two columns filled, others open
 */
extern void initBoard(board b)
{
	int i, j, last;

	for (i=BMIN; i<=BMAX; i++)
		for (j=BMIN; j<=BMAX; j++)
			b[i][j] = OPEN;
	last = BSIZE - 1;
	for (i=0; i<BSIZE; i++)
		b[0][i] = b[last][i] = b[i][0] = b[i][last] = FILLED;

}
/* Set the peices on the board at the start of the game
 */
extern void setPieces(board b)
{
	int i;

	b[BMIN][BMIN] = b[BMIN][BMAX] = ROOK;
	b[BMAX][BMIN] = b[BMAX][BMAX] = CROOK;
	b[BMIN][BMIN+1] = b[BMIN][BMAX-1] = KNIGHT;
	b[BMAX][BMIN+1] = b[BMAX][BMAX-1] = CKNIGHT;
	b[BMIN][BMIN+2] = b[BMIN][BMAX-2] = BISHOP;
	b[BMAX][BMIN+2] = b[BMAX][BMAX-2] = CBISHOP;
	b[BMIN][BMIN+3] = KING;
	b[BMAX][BMAX-3] = CKING;
	b[BMIN][BMAX-3] = QUEEN;
	b[BMAX][BMIN+3] = CQUEEN;

	for(i=BMIN; i<=BMAX; i++)
	{
		b[BMIN+1][i] = PAWN;
		b[BMAX-1][i] = CPAWN;
	}
}
/* Print the current board state onto the standard output
 * Example of output:
 *
 *      A B C D E F G H
 *
 *  1   R K B X Q B K R   1
 *  2   P P P P P P P P   2
 *  3   - - - - - - - -   3
 *  4   - - - - - - - -   4
 *  5   - - - - - - - -   5
 *  6   - - - - - - - -   6
 *  7   p p p p p p p p   7
 *  8   r k b q x b k r   8
 *  
 *      A B C D E F G H
 */
extern void printBoard(board b)
{
	int i, j;
	int row = 1;

	printf("    "); // spacer

	// ASCII codes for capital 'A' through 'H' representing the column letters
	for(i=65; i<=72; i++)
		printf("%c ", i); 		// print as character

	putchar('\n'); 				// newline

	for(i=BMIN; i<=BMAX; i++) 	// for each row of the board
	{
		putchar('\n'); 			//newline
		printf("%d   ", row); 	// the row number
		for(j=BMIN; j<=BMAX; j++) { // for each column of the board
			// If printing a player one peice, print the char in yellow
			if(b[i][j] == ROOK ||
			   b[i][j] == KNIGHT ||
			   b[i][j] == BISHOP ||
			   b[i][j] == QUEEN ||
			   b[i][j] == KING ||
			   b[i][j] == PAWN)
			   printf(YEL "%c " RESET, b[i][j]);
			// If printing a player two peice, print the char in magenta
			else if(b[i][j] == CROOK ||
			   b[i][j] == CKNIGHT ||
			   b[i][j] == CBISHOP ||
			   b[i][j] == CQUEEN ||
			   b[i][j] == CKING ||
			   b[i][j] == CPAWN)
			   printf(GRN "%c " RESET, b[i][j]);
			// If printing an empty part of the board, print as default
			else 
				printf("%c ", b[i][j]);
		}
		printf("  %d", row); 	// the row number
		row++;					// increment the row number
	}
	putchar('\n');				// newline
	putchar('\n');				// newline
	printf("    ");				// spacer
	for(i=65; i<=72; i++)		// ASCII codes for capital 'A' through 'H' representing the column letters
		printf("%c ", i); 		// print as character
	putchar('\n');				// newline
}
/* Calls the appropriate validation function for the supplied player piece
 */
extern bool validMove(piece p,  // the piece to be validated
					  board b,  // the current board state
					  int si, 	// starting row
					  int sj, 	// starting column
					  int fi, 	// finishing row
					  int fj)	// finishing column
{
	// if starting and ending positions are the same, the move is invalid
	// return FALSE
	if(si == fi && sj == fj) return FALSE;

	// call the appropriate validation function based upon the piece parameter
	// and return its value
	switch(p)
	{
	case KNIGHT:
		return validKnightMove(p, b, si, sj, fi, fj, PLAYERONE);
	case CKNIGHT:
		return validKnightMove(p, b, si, sj, fi, fj, PLAYERTWO);
	case ROOK:
		return validRookMove(p, b, si, sj, fi, fj, PLAYERONE);
	case CROOK:
		return validRookMove(p, b, si, sj, fi, fj, PLAYERTWO);
	case BISHOP:
		return validBishopMove(p, b, si, sj, fi, fj, PLAYERONE);
	case CBISHOP:
		return validBishopMove(p, b, si, sj, fi, fj, PLAYERTWO);
	case KING:
		return validKingMove(p, b, si, sj, fi, fj, PLAYERONE);
	case CKING:
		return validKingMove(p, b, si, sj, fi, fj, PLAYERTWO);
	case QUEEN:
		return validQueenMove(p, b, si, sj, fi, fj, PLAYERONE);
	case CQUEEN:
		return validQueenMove(p, b, si, sj, fi, fj, PLAYERTWO);
	case PAWN:
		return validPawnMove(p, b, si, sj, fi, fj, PLAYERONE);
	case CPAWN:
		return validPawnMove(p, b, si, sj, fi, fj, PLAYERTWO);
	default:
		return FALSE; // if the piece parameter is not one of the valid pieces, return FALSE
	}
}
/* Determine if the piece parameter p and the piece on board b at position i,j
 * belong to the same player
 */
static bool isOwnGuy(board b, piece p, int i, int j)
{
	// All player one pieces are uppercase characters, so if piece p and 
	// piece on board b at i,j are both uppercase, then they both belong
	// to player one
	if(isupper(p))
		if(isupper(b[i][j]))
			return TRUE;

	// All player two pieces are lowercase
	if(islower(p))
		if(islower(b[i][j]))
			return TRUE;

	// If the pieces are both both upper or both lower, return TRUE
	return FALSE;
}
/* determine if a knight's movement is valid
 * knights can only move two spaces vertically and one space horizontally or
 * two spaces horizontally and one space vertically
 * knights can jump over other pieces
 */
static bool validKnightMove(piece p, board b, int si, int sj, int fi, int fj, player ply)
{
	if(isOwnGuy(b, p, fi, fj) == TRUE) return FALSE; // if trying to take own piece

	//if(kingInCheck(b, p, p) > 0) return FALSE;	 // if the player's king will be in check as a result of this move

	if(si == fi || sj == fj) return FALSE;			 // if the knight is being moved only horizontally or only vertically

	fi = abs(si - fi);								// |start_row-finish_row| should equal either 1 or 2
	fj = abs(sj - fj);								// |start_col-finish_col| should equal either 1 or 2

	if(fi != 1 && fj != 1) return FALSE;			// if neither vertical or horizontal position change equal 1

	if(abs(fi - fj) != 1) return FALSE;				// |delta_vert-delta_hor| should equal 1 because |1-2| = 1

	return TRUE;									// return true otherwise
}
/* determine if rook's move is valid
 * rooks can only move horizontally or vertically
 * they are not bound by any number of spaces moved but they cannot move through other pieces
 */
static bool validRookMove(piece p, board b, int si, int sj, int fi, int fj, player ply)
{
	if(isOwnGuy(b, p, fi, fj) == TRUE) return FALSE; 			// if trying to take own piece

	if(peopleInPath(b, si, sj, fi, fj) == TRUE) return FALSE;	// if there are other pieces in the move path of the rook

	//if(kingInCheck(b, p, fi, fj) > 0) return FALSE;	 		// if the player's king will be in check as a result of this move

	if(!(si == fi ^ sj == fj)) return FALSE; 					// if there is change to both vertical and horizontal position

	return TRUE;												// return true otherwise
}
/* determine is bishop's move is valid
 * bishops can only move diagonally
 * they are not bound by any number of spaces moved but they cannot move through other pieces
 */
static bool validBishopMove(piece p, board b, int si, int sj, int fi, int fj, player ply)
{
	if(isOwnGuy(b, p, fi, fj) == TRUE) return FALSE; 			// if trying to take own piece

	if(peopleInPath(b, si, sj, fi, fj) == TRUE) return FALSE;	// if there are other pieces in the move path of the bishop

	//if(kingInCheck(b, p, fi, fj) > 0) return FALSE;	 		// if the player's king will be in check as a result of this move

	if(abs(fi-si) != abs(fj-sj)) return FALSE;					// if the change in horizontal position does not equal the change in vertical position

	return TRUE;												// return true otherwise
}
/* determine if king's move is valid
 * kings can only move one space at a time either horizontally, vertically, or diagonally
 */
static bool validKingMove(piece p, board b, int si, int sj, int fi, int fj, player ply)
{
	if(isCastling(p, b, si, sj, fi, fj, ply) == TRUE) return TRUE ; // if this is a castling maneuver, return TRUE

	if(isOwnGuy(b, p, fi, fj) == TRUE) return FALSE; 			// if trying to take own piece

	//if(kingInCheck(b, p, fi, fj) > 0) return FALSE;	 		// if the player's king will be in check as a result of this move

	if(abs(si-fi) > 1 || abs(sj-fj) > 1) return FALSE;			// if the change in either horizontal or vertical position is greater than one
	
	return TRUE;												// return true otherwise
}
/* determine if queen's move is valid 
 * queens can move either diagonally, horizontally, or vertically
 * they are not bound by any number of spaces moved but they cannot move through other pieces
 */
static bool validQueenMove(piece p, board b, int si, int sj, int fi, int fj, player ply)
{
	if(isOwnGuy(b, p, fi, fj) == TRUE) return FALSE; 			// if trying to take own piece

	if(peopleInPath(b, si, sj, fi, fj) == TRUE) return FALSE;	// if there are other pieces in the move path of the queen

	//if(kingInCheck(b, p, fi, fj) > 0) return FALSE;	 		// if the player's king will be in check as a result of this move

	if(validRookMove(p, b, si, sj, fi, fj, ply) || 				// The queen's valid moves are the same as that of the rook
	   validBishopMove(p, b, si, sj, fi, fj, ply))				// and bishop combines, so validate that the move is valid based
		return TRUE;											// on either of those two rule sets

	return FALSE;												// return FALSE otherwise
}
/* determine if pawn move is valid 
 * pawns cannot move horizontally
 * they can move two spaces vertically if it is their opening move and one space vertically at all times (including the opening move)
 * they cannot move diagonally except when taking an opponent's piece
 * they must move one space diagonally in order to take an opponent's piece
 */
static bool validPawnMove(piece p, board b, int si, int sj, int fi, int fj, player ply)
{
	if(isOwnGuy(b, p, fi, fj) == TRUE) return FALSE; 			// if trying to take own piece

	if(peopleInPath(b, si, sj, fi, fj) == TRUE) return FALSE;	// if there are other pieces in the move path of the queen

	//if(kingInCheck(b, p, fi, fj) > 0) return FALSE;	 		// if the player's king will be in check as a result of this move

	if(fj - sj != 0) {											// if there is change in horizontal position
		if(b[fi][fj] == OPEN)									// if the space the pawn is trying to move to does not contain a piece
			return FALSE;										// this is an invalid move
		if(abs(fj - sj) != 1)									// if the pawn is trying to move more than one space horizontally
			return FALSE;										// this is an invalid move
	}
	
	if(fj - sj == 0)											// if there is no change in horizontal position
		if(b[fi][fj] != OPEN)									// if the space the pawn is trying to move to contains a piece
			return FALSE;										// this is an invalid move

	if(isupper(p))												// if the piece belongs to player one
	{
		if(fi - si > 2 || fi - si < 1) return FALSE;			// if vertical position change is greater than 2 or less than 1
		if(fi - si == 2)										// if the pawn is trying to move two spaces
			if(si != 2)											// if the pawn is not starting its move from its starting location
				return FALSE;									// this is an invalid move
	}
	else														// if the piece belongs to player two
	{
		if(si - fi > 2 || si - fi < 1) return FALSE;			// if vertical position change is greater than 2 or less than 1
		if(si - fi == 2)										// if the pawn is trying to move two spaces
			if(si != 7)											// if the pawn is not starting its move from its starting location
				return FALSE;									// this is an invalid move
	}
	return TRUE;												// return TRUE otherwise
}
/* determines if there are player pieces along a given path
 */
static bool peopleInPath(board b, int si, int sj, int fi, int fj)
{
	int i;

	if(si == fi)							// if the path is horizontal
	{
		if(fj > sj)							// if the path is horizontal moving right along the board
			for(i=sj+1; i<fj; i++)			// for each space along the path
				if(b[si][i] != OPEN)		// test if there is a piece occupying that space
					return TRUE;			// return true if there is

		if(fj < sj)							// if the path is horizontal moving left along the board
			for(i=fj+1; i<sj; i++)			// for each space along the path
				if(b[si][i] != OPEN)		// test if there is a piece occupying that space
					return TRUE;			// return true if there is
	}
	else if(sj == fj)						// if the path is vertical
	{
		if(fi > si)							// if the path is vertical moving down along the board
			for(i=si+1; i<fi; i++)			// for each space along the path
				if(b[i][sj] != OPEN)		// test if there is a piece occupying that space
					return TRUE;			// return true if there is

		if(fi < si)							// if the path is vertical moving up along the board
			for(i=fi+1; i<si; i++)			// for each space along the path
				if(b[i][sj] != OPEN)		// test if there is a piece occupying that space
					return TRUE;			// return true if there is
	}
	else									// if the path is diagonal
	{
		if(fi > si && fj > sj)				// if the path is diagonal moving down and right along the board
			for(i=1; i<(fi-si); i++)		// for each space along the path
				if(b[si+i][sj+i] != OPEN)	// test if there is a piece occupying that space
					return TRUE;			// return true if there is

		if(fi < si && fj > sj)				// if the path is diagonal moving up and right along the board
			for(i=1; i<(si-fi); i++)		// for each space along the path
				if(b[si-i][sj+i] != OPEN)	// test if there is a piece occupying that space
					return TRUE;			// return true if there is

		if(fi < si && fj < sj)				// if the path is diagonal moving up and left along the board
			for(i=1; i<(si-fi); i++)		// for each space along the path
				if(b[si-i][sj-i] != OPEN)	// test if there is a piece occupying that space
					return TRUE;			// return true if there is

		if(fi > si && fj < sj)				// if the path is diagonal moving down and left along the board
			for(i=1; i<(fi-si); i++)		// for each space along the path
				if(b[si+i][sj-i] != OPEN)	// test if there is a piece occupying that space
					return TRUE;			// return true if there is
	}
	return FALSE;							// return FALSE otherwise
}
/* This function is intended to determine if a move is intended to be a castling maneuver
 * castling is when the king takes cover at the side of its nearest rook
 * castling can only occur when there are no pieces (i.e. the knight and the bishop) in the path of the maneuver
 * neither the rook nor the king have previously been moved during the game
 * and the king has not yet been placed into check 
 *
 * An example of this move would be if player one entered "1D 1A"
 * the king and rook would move from their original positions:
 *
 *		A B C D
 *		
 * 	 1	R - - X
 *
 * to their final positions:
 *
 *		A B C D
 *
 * 	 1	- X R -
 */
static bool isCastling(piece p, board b, int si, int sj, int fi, int fj, player ply)
{
	return FALSE; // This function has not yet been implemented
}
