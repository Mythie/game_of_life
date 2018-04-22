#ifndef game_of_life_h
#define game_of_life_h

#include <stdio.h>
#include <stdlib.h>

typedef struct gol{
	int **board;
	size_t size;
}gol;

gol* create_default_gol();

gol* create_gol(size_t size);

void destroy_gol(gol* g);

void set_pattern(gol* g, int** b);

void next_pattern(gol* g);

int neighbour_sum(gol* g, int i, int j);

void print(gol* g);

#endif