#include<stdio.h>

/*
 * 0 -> Represents empty
 */
#define EMPTY_MARKER 0

/*
 * +X -> Represents X
 */
#define X_MARKER 1

/*
 * -1 -> Represents O
 */
#define O_MARKER -1

#define BOARD_WIDTH 3

#define BOARD_HEIGHT 3

enum GAME_STATE {IN_GAME, X_WON, O_WON, GAME_DRAW};

enum TURN {X_TURN, O_TURN};

#define BOT_IS X_TURN

/*
 * setups the game for play
 */
void init(int board[BOARD_HEIGHT][BOARD_WIDTH], enum TURN *turn);

/*
 * prints the board
 */
void print_board(int board[BOARD_HEIGHT][BOARD_WIDTH]);

/*
 * returns the state of the board passwd to it.
 */
enum GAME_STATE current_game_state(int board[BOARD_HEIGHT][BOARD_WIDTH]);

/*
 * Finds the minmax and the positions
 */
int minimax(int board[BOARD_HEIGHT][BOARD_WIDTH],
		 int depth, int *pos_row, int *pos_col);
