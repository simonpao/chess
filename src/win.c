/* Simon Paonessa
 * Chess Game, win.c
 */

#include "globals.h"
#include <stdio.h>
#include <ctype.h>

extern piece whatPiece(board b, int i, int j)
{
	if(isupper(b[i][j]))
		switch(b[i][j])
	{
		case KNIGHT:
			return KNIGHT;
		case ROOK:
			return ROOK;
		case BISHOP:
			return BISHOP;
		case QUEEN:
			return QUEEN;
		case PAWN:
			return PAWN;
		case KING:
			return KING;
	}
	else
		switch(b[i][j])
	{
		case CKNIGHT:
			return CKNIGHT;
		case CROOK:
			return CROOK;
		case CBISHOP:
			return CBISHOP;
		case CQUEEN:
			return CQUEEN;
		case CPAWN:
			return CPAWN;
		case CKING:
			return CKING;
	}
	return '5';
}
extern int checkMate(int x, int y)
{
	return 0; // Does not currently do anything
}
extern int kingInCheck(boardMap map[], board b, player p)
{
	return 0; // Does not currently do anything
}
extern void printCheckMsg(int stat, player ply)
{
	if(stat == CHECK)
		printf("Your King is in Check");
	else if(stat == CHECKMATE)
		printf("Your King is in Checkmate");

	if(ply == PLAYERONE)
		printf(", player one.");
	else if(ply == PLAYERTWO)
		printf(", player two.");
}
