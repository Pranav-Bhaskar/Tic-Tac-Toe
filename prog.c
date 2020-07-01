/*
 * Will try to use the kernel coding standards. Although I cant promise it since
 * I have some time constrains. I will also be changing the interface a bit to
 * suite my current style.
 */

#include "prog.h"

void init(int board[BOARD_HEIGHT][BOARD_WIDTH], enum TURN *turn)
{
	int i;
	int j;
	for (i = 0; i < BOARD_HEIGHT; i++)
		for (j = 0; j < BOARD_WIDTH; j++)
			board[i][j] = EMPTY_MARKER;
	
	*turn = O_TURN;
	printf("\nBoard Is Cleared");
}

void print_board(int board[BOARD_HEIGHT][BOARD_WIDTH])
{
	int i;
	int j;
	printf("\nBOARD\n\t||=||=||=||\n\t");
	for (i = 0; i < BOARD_HEIGHT; i++) {
		printf("||");
		for (j = 0; j < BOARD_WIDTH; j++) {
			switch (board[i][j]) {
			case EMPTY_MARKER :
				printf(" ");
				break;
			case X_MARKER :
				printf("X");
				break;
			case O_MARKER:
				printf("O");
			}
			printf("||");
		}
		printf("\n\t");
	}
	printf("||=||=||=||");
}

enum GAME_STATE current_game_state(int board[BOARD_HEIGHT][BOARD_WIDTH])
{
	int i;
	int j;
	int sum;
	
	int prim_diagnol_sum;
	int sec_diagnol_sum;
	
	prim_diagnol_sum = 0;
	sec_diagnol_sum = 0;
	
	for (i = 0; i < BOARD_HEIGHT; i++) {
		sum = 0;
		for (j = 0; j < BOARD_WIDTH; j++) {
			sum += board[i][j];
			if (i == j)
				prim_diagnol_sum += board[i][j];
			if ((i + j) == (BOARD_HEIGHT - 1))
				sec_diagnol_sum += board[i][j];
		}
		if (sum == BOARD_WIDTH * X_MARKER)
			return X_WON;
		if (sum == BOARD_WIDTH * O_MARKER)
			return O_WON;
	}
	
	if (prim_diagnol_sum == BOARD_WIDTH * X_MARKER)
		return X_WON;
	if (prim_diagnol_sum == BOARD_WIDTH * O_MARKER)
		return O_WON;
	
	if (sec_diagnol_sum == BOARD_WIDTH * X_MARKER)
		return X_WON;
	if (sec_diagnol_sum == BOARD_WIDTH * O_MARKER)
		return O_WON;
	
	for (j = 0; j < BOARD_WIDTH; j++) {
		sum = 0;
		for (i = 0; i < BOARD_HEIGHT; i++)
			sum += board[i][j];
		if (sum == BOARD_HEIGHT * X_MARKER)
			return X_WON;
		if (sum == BOARD_HEIGHT * O_MARKER)
			return O_WON;
	}
	
	for (i = 0; i < BOARD_HEIGHT; i++)
		for (j = 0; j < BOARD_WIDTH; j++)
			if (board[i][j] == EMPTY_MARKER)
				return IN_GAME;
	
	return GAME_DRAW;
}

void bot_make_your_move(int board[BOARD_HEIGHT][BOARD_WIDTH])
{
	int pos_row;
	int pos_col;
	
	minimax(board, 0, &pos_row, &pos_col);
	
	if (BOT_IS == X_TURN)
		board[pos_row][pos_col] = X_MARKER;
	else
		board[pos_row][pos_col] = O_MARKER;
}

int minimax(int board[BOARD_HEIGHT][BOARD_WIDTH],
		 int depth, int *pos_row, int *pos_col)
{
	int i;
	int j;
	int bestScore;
	int tmp;
	int score;
	
	switch (current_game_state(board)) {
	case GAME_DRAW :
		return 0;
	case X_WON :
		if (BOT_IS == X_TURN)
			return 1;
		else
			return -1;
	case O_WON :
		if (BOT_IS == O_TURN)
			return 1;
		else
			return -1;
	}
	
	if ((depth & 1) == 0) {	//bot turn
		bestScore = -999;
		for (i = 0; i < BOARD_HEIGHT; i++) {
			for (j = 0; j < BOARD_WIDTH; j++) {
				if (board[i][j] != EMPTY_MARKER)
					continue;
				
				if (BOT_IS == X_TURN)
					board[i][j] = X_MARKER;
				else
					board[i][j] = O_MARKER;
				score = minimax(board, depth + 1, &tmp, &tmp);
				board[i][j] = EMPTY_MARKER;
				
				if (bestScore < score) {
					bestScore = score;
					*pos_row = i;
					*pos_col = j;
				}
			}
		}
	} else {		//humans turn
		bestScore = 999;
		for (i = 0; i < BOARD_HEIGHT; i++) {
			for (j = 0; j < BOARD_WIDTH; j++) {
				if (board[i][j] != EMPTY_MARKER)
					continue;
				
				if (BOT_IS == X_TURN)
					board[i][j] = O_MARKER;
				else
					board[i][j] = X_MARKER;
				score = minimax(board, depth + 1, &tmp, &tmp);
				board[i][j] = EMPTY_MARKER;
				
				if (bestScore > score) {
					bestScore = score;
					*pos_row = i;
					*pos_col = j;
				}
			}
		}
	}
	return bestScore;
}

int get_num_from_user(const char* message, int upper_bound)
{
	int num;
	do {
		printf("%s", message);
		scanf("%d", &num);
	} while ((num >= upper_bound) || (num < 0));
	
	return num;
}

void prompt_user(int board[BOARD_HEIGHT][BOARD_WIDTH])
{
	int pos_row;
	int pos_col;
	
	do {
		pos_row = get_num_from_user("\nEnter Row : ", BOARD_HEIGHT);
		pos_col = get_num_from_user("\nEnter Col : ", BOARD_WIDTH);
	} while (board[pos_row][pos_col] != EMPTY_MARKER);
	
	board[pos_row][pos_col] = O_MARKER;
}

int main ()
{
	int board[BOARD_HEIGHT][BOARD_WIDTH];
	enum TURN turn;
	enum GAME_STATE game_state;
	
	init(board, &turn);
	while (BOARD_HEIGHT == BOARD_WIDTH) {
		print_board(board);
		game_state = current_game_state(board);
		if (game_state == GAME_DRAW) {
			printf("\nGAME DRAW");
			break;
		} else if (game_state == X_WON) {
			printf("\nX WON");
			break;
		} else if (game_state == O_WON) {
			printf("\nO WON");
			break;
		} else if (game_state == IN_GAME) {
			if (turn == BOT_IS)
				bot_make_your_move(board);
			else if (turn == O_TURN)
				prompt_user(board);
			
			if (turn == X_TURN)
				turn = O_TURN;
			else
				turn = X_TURN;
		}
	}
	printf("\nGAME ENDED\n");
	return 0;
}
