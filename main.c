#include <stdlib.h>
#include <stdio.h>
#include "game_of_life.h"

int main() {
	printf("Game of Life\n");
	printf("-----------------------");

	gol* g = create_default_gol();

	print(g);
	return 0;
}