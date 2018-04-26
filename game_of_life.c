#include <stdio.h>
#include <stdlib.h>

typedef struct gol{
	int **board;
	size_t size;
}gol;

/**
 * Create a board with the default sizing (20x20)
 * @return gol[20][20]  The board in the default sizing
 */
gol* create_default_gol() {
	// Create the gol instance
	gol** new_gol;
	// Set the size of the board
	new_gol->size = 20;
	// Dynamically fill the rows with zero's
	new_gol->board = malloc(new_gol->size * sizeof(int *));
	if(new_gol->board == NULL) {
		// TODO: Catch some errors
		return NULL;
	}
	// Then dynamically fill the columns with 0's
	for(int i = 0; i < new_gol->size; i++) {
		new_gol->board[i] = malloc(new_gol->size * sizeof(int *));
		if(new_gol->board[i] == NULL) {
			// TODO: Catch some errors
			return NULL;
		}
	}
	return new_gol;
}

/**
 * Create a board with the user specified sizing
 * @param size_t 	The size of the board
 * @return gol[size][size] 	The board of the size specified
 */
gol* create_gol(size_t size) {
	// Create the gol instance
	gol* new_gol;
	// Set the size of the board
	new_gol->size = size;
	// Dynamically fill the rows with zero's
	new_gol->board = malloc(new_gol->size * sizeof(int *));
	if(new_gol->board == NULL) {
		// TODO: Catch some errors
		return NULL;
	}
	// Then dynamically fill the columns with 0's
	for(int i = 0; i < new_gol->size; i++) {
		new_gol->board[i] = malloc(new_gol->size * sizeof(int *));
		if(new_gol->board[i] == NULL) {
			// TODO: Catch some errors
			return NULL;
		}
	}
	return new_gol;
}

/**
 * Remove the board
 * @param gol 	The board to remove
 */
void destroy_gol(gol* g) {
	free(g);
}

/**
 * This sets the pattern, in reality the pattern is actually passed to it and it's applied to the board?
 * @param gol 	The board
 * @param int[][] 	The pattern to apply?
 */
void set_pattern(gol* g, int** b) {

}

/**
 * Despite the name this actually progresses the board, evolve would be a more suitable name
 * @param
 */
void next_pattern(gol* g) {

}

/**
 * This takes in a board and a position and checks the neighbors values to calculate their sum (1 or 0)
 * @param gol 	The board
 * @param int 	The x location of the cell
 * @param int 	The y location of the cell
 * @return int 	The amount of alive neighbours next to the cell.
 */
int neighbour_sum(gol* g, int i, int j) {
	return 0;
}

/**
 * Prints the current state of the board
 * @param gol  The board
 */
void print(gol* g) {
	// For each row?
	for(int i = 0; i < g->size; i++) {
		// For each column
		for(int j = 0; j < g->size; j++) {
			// Print it's status
			printf("%s", (g->board[i][j] == 0 ? "o" : "x"));
			// If this is the last item print a new line
			if(j == g->size - 1){ printf("\n"); }
		}
	}
}