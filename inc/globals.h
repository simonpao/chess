/*
 * Chess Game, globals.h
 */

#ifndef _globals
#define _globals

// Color codes for printing colored text on command line
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

// Used for the status of an operation
typedef enum { OK, ERROR } status;
// Definition of boolean variable, required in C
typedef enum { FALSE=0, TRUE=1 } bool;
typedef void *genericPtr;

#endif

#ifndef _board
#define _board

// Definition of player variable
typedef enum { PLAYERONE, PLAYERTWO } player; 

// Chess board minimum, maximum and size
#define BMIN 1
#define BMAX 8
#define BSIZE 10

// Whether a space is open or occupied
#define FILLED '+'
#define OPEN '-'

// definition of piece variable as C char
typedef char piece;
// definition of board varivle as two-dimentional char array
typedef char board[BSIZE][BSIZE];

// Definition of player one pieces
#define ROOK 'R'
#define KNIGHT 'K'
#define BISHOP 'B'
#define QUEEN 'Q'
#define KING 'X'
#define PAWN 'P'

// Definition of player two pieces
#define CROOK 'r'
#define CKNIGHT 'k'
#define CBISHOP 'b'
#define CQUEEN 'q'
#define CKING 'x'
#define CPAWN 'p'

// Structure which defines location and type of player piece
typedef struct 
{
	int i;
	int j;
	piece p;
} boardMap;

// Structure which defines a current board state
typedef struct
{
	board br;
	int value;
} state;

// declaration of board.c functions
extern void initBoard(board b);
extern void setPieces(board b);
extern void printBoard(board b);
extern bool validMove(piece p, board b, int, int, int, int);
static bool isOwnGuy(board b, piece p, int, int);
static bool validKnightMove(piece p, board b, int, int, int, int, player);
static bool validRookMove(piece, board b, int, int, int, int, player);
static bool validBishopMove(piece, board b, int, int, int, int, player);
static bool validKingMove(piece, board b, int, int, int, int, player);
static bool validQueenMove(piece, board b, int, int, int, int, player);
static bool validPawnMove(piece, board b, int, int, int, int, player);
static bool peopleInPath(board b, int si, int sj, int fi, int fj);
static bool isCastling(piece p, board b, int si, int sj, int fi, int fj, player ply);

#endif

#ifndef _move
#define _move

// declaration of move.c functions
extern status evalMove(char s[], char f[], int *i, int *j, int *k, int *l);
extern int evalRow(char row);
extern status makeMove(board b, int si, int sj, int fi, int fj, player ply, boardMap map[]);
extern void updateBoardMap(boardMap map[], int si, int sj, int fi, int fj);
extern void deleteFromBoardMap(int i, int j, boardMap map[]);
extern void setBoardMap(boardMap map1[], boardMap map2[]);

#endif

#ifndef _win
#define _win

// define constants for game conditions check and checkmate
#define CHECK 1
#define CHECKMATE 2

// declaration of win.c functions
extern int kingInCheck(boardMap map[], board b, player p);
extern void printCheckMsg(int stat, player ply);
extern piece whatPiece(board b, int i, int j);
extern int checkMate(int x, int y);

#endif