#include <stdio.h>
#include <stdlib.h>
#include "game_of_life.h"

#define DEFAULT_GOL_SIZE 20

/**
 * Create a board with the default sizing (20x20)
 * @return gol[20][20]  The board in the default sizing
 */

gol* create_default_gol() {
    size_t size = DEFAULT_GOL_SIZE;
    return create_gol(size);
}

gol* create_gol(size_t size) {
    //`gol *new_gol;
    gol *new_gol = malloc(sizeof(gol*));

    new_gol->size = size;
    new_gol->board = malloc(sizeof(int *) * new_gol->size);
    if(new_gol->board == NULL) {
        printf("Hit Null on malloc 1d");
        return NULL;
    }

    for(int i = 0; i < new_gol->size; i++) {
        new_gol->board[i] = malloc(sizeof(int *) * new_gol->size);
        if(new_gol->board[i] == NULL) {
            printf("Hit Null on Malloc 2d");
            // TODO: Catch some errors
            return NULL;
        }
    }

    // Zero out the board, this is needed since malloc won't always create a zeroed array??
    // Could use memset but opted against importing another library.
    for(int i = 0; i < new_gol->size; i++) {
        for(int j = 0; j < new_gol->size; j++) {
            new_gol->board[i][j] = 0;
        }
    }
    return new_gol;
}

// TODO: Probably go over every item in "g" and free them
void destroy_gol(gol* g) {
    free(g);
}

void set_pattern(gol *g, int **b) {
    // TODO: Further implement this
    // Thoughts: Iterate over b since we know it's an int sizeof(b)/sizeof(int *)??
    // This way if we apply a smaller config to a bigger board it will only be applied to
    // a smaller area of the board as opposed to changing the whole thing :)

    // Could use memset?
    for(int i = 0; i < g->size; i++) {
        for(int j = 0; j < g->size; j++) {
            g->board[i][j] = b[i][j];
        }
    }
    printf("\n");
}

void next_pattern(gol *g) {
    // Create a second board
    // NOTE: We don't need to zero this one out as we will be using our
    // reference board and writing values to it accordingly
    int **b = malloc(g->size * sizeof(int *));
    // Create the second board continued
    for(int i = 0; i < g->size; i++) {
        b[i] = malloc(g->size * sizeof(int *));
    }

    for(int i = 0; i < g->size; i++) {
        for (int j = 0; j < g->size; j++) {
            int sum = neighbour_sum(g, i, j);
            //printf("board[%d][%d] sum: %d\n", i, j, sum);
            /*
             * As per the rules:
             * Any live cell with 2-3 neighbours lives either through survival
             * Any dead cell with 3 neighbours gains life through reproduction
             * anything else will die either from famine or overpopulation
             */
            // Alive and has two or three neighbours
            if((g->board[i][j] == 1) && (sum == 2 || sum == 3)) {
                // Lives
                b[i][j] = 1;
            }
            // Dead and has exactly three neighbours
            else if((g->board[i][j] == 0) && (sum == 3)) {
                // Lives
                b[i][j] = 1;
            }
            // Otherwise
            else {
                // Dies (overpopulation or crowding)
                b[i][j] = 0;
            }
        }
    }
    // Finalise it by setting the game state we just created on our board.
    set_pattern(g, b);
}

int neighbour_sum(gol *g, int i, int j) {
    // Start off with zero and increment as we hit matches
    if(i >= g->size || j >= g->size) {
        printf("Neighbour sum out of bounds i: %d\tj: %d\n", i, j);
        return 0;
    }

    int sum = 0;
    int n = (int)g->size;
    // Top-left
    sum += g->board[(i-1+n)%n][(j-1+n)%n];
    // Top center
    sum += g->board[(i-1+n)%n][j];
    // Top right
    sum += g->board[(i-1+n)%n][(j+1)%n];
    // Right
    sum += g->board[i%n][(j+1)%n];
    // Bottom right
    sum += g->board[(i+1)%n][(j+1)%n];
    // Bottom Center
    sum += g->board[(i+1)%n][j];
    // Bottom Left
    sum += g->board[(i+1)%n][(j-1+n)%n];
    // Left
    sum += g->board[i][(j-1+n)%n];
    // Return the sum
    return sum;
}

void print(gol* g) {
    // For each row
    for(int i = 0; i < g->size; i++) {
        // For each column
        for(int j = 0; j < g->size; j++) {
            // Print it's status
            printf("%s", (g->board[i][j] == 0 ? "." : "x"));
        }
        printf("\n");
    }
}