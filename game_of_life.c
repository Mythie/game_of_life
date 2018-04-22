typedef struct gol{
	int **board;
	size_t size;
}gol;

/**
 * Create a board with the default sizing (20x20)
 * @return gol[20][20]  The board in the default sizing
 */
gol* create_default_gol() {

}

/**
 * Create a board with the user specified sizing
 * @param size
 * @return gol[size][size]  The board of the size specified
 */
gol* create_gol(size_t size) {

}

/**
 * Remove the board
 * @param gol  The board to remove
 */
void destroy_gol(gol* g) {

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