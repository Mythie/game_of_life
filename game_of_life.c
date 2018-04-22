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
	gol* new_gol;
	// Set the size of the board
	new_gol->size = 20;
	// Dynamically fill the rows with zero's
	new_gol->board = malloc(new_gol->size * sizeof(int *));
	if(new_gol->board == NULL) {
		// TODO: Catch some errors
		return;
	}
	// Then dynamically fill the columns with 0's
	for(int i = 0; i < new_gol->size; i++) {
		new_gol->board[i] = malloc(new_gol->size * sizeof(int *));
		if(new_gol->board[i] == NULL) {
			// TODO: Catch some errors
			return;
		}
	}
	return new_gol*
}

/**
 * Create a board with the user specified sizing
 * @param size
 * @return gol[size][size]  The board of the size specified
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
		return;
	}
	// Then dynamically fill the columns with 0's
	for(int i = 0; i < new_gol->size; i++) {
		new_gol->board[i] = malloc(new_gol->size * sizeof(int *));
		if(new_gol->board[i] == NULL) {
			// TODO: Catch some errors
			return;
		}
	}
	return new_gol*
}

/**
 * Remove the board
 * @param gol  The board to remove
 */
void destroy_gol(gol* g) {
	free(g);
}

/**
 * 
 * @param
 * @param
 */
void set_pattern(gol* g, int** b) {
	
}

/**
 * @param
 */
void next_pattern(gol* g) {

}

/**
 * @param
 * @param
 * @param
 * @return
 */
int neighbour_sum(gol* g, int i, int j) {

}

/**
 * @param
 */
void print(gol* g) {

}