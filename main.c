#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "game_of_life.h"

// Function prototypes

// Main functions
int** create_board(size_t size);

//void get_initial_pattern(gol *g);

void create_glider_gun_gol(gol *g);

void create_light_weight_spaceship(gol *g);

void create_pulsar_gol(gol *g);

void create_random_gol(gol *g);

// Utilities
void print_n(char *c);

void printDash();

// Main function
int main() {

    /**
     * TODO ->
     * While(1)
     *  Display menu
     *  Take action input
     *  Perform action
     *  Clear console? (Stop it from getting huge)
     * Call it a day
     */
    print_n("Conway's Game of Life");
	// Setup initial variables
	gol *g = malloc(sizeof(gol *)); // This is so we can implement destroy_gol easily
    // This acts as a bool to stop someone from attempting to print the next step with an empty/null struct
	int gol_initialized = 0;
    // This acts as a bool
	int running = 1;
	// Start the loop
    // While(1) is bad practice so lets avoid that by assigning it to variable
    while(running) {
        printDash();
        print_n("Options");
        printDash();

        print_n("1. Select initial pattern");
        print_n("2. Print next pattern");
        print_n("3. Exit program");

        // Initialise an empty choice
        int choice;
        // Get the choice input.
        do {
            printf("Enter your selection [1-3]: ");
            // This catches the invalid input in scanf that causes an infinite loop
            // @Source: https://stackoverflow.com/questions/25945791/character-input-in-scanfd-value
            if(scanf("%d", &choice) == 0) {
                printf("Invalid input caused scanf buffer overflow, exiting now...");
                exit(1);
            }
        } while(choice < 1 || choice > 3);

        // Use a switch statement to call actions based on the choice.
        switch(choice) {
            // Select initial pattern
            case 1:
                free(g);
                /**
                 * TODO: Refactor this entire case.
                 * I previously had it in a series of methods however I was getting segfaults since my
                 * pointers were moving for some reason?
                 */
                printDash();
                print_n("Initial pattern options");
                printDash();

                int pChoice;

                print_n("1. Random");
                print_n("2. Glider Gun");
                print_n("3. Pulsar");
                print_n("4. Lightweight Space Ship");
                do {
                    printf("Enter your selection: ");
                    if(scanf("%d", &pChoice) == 0) {
                        printf("Invalid input caused scanf buffer overflow, exiting now...");
                        exit(1);
                    }
                } while(pChoice < 1 || pChoice > 4);

                switch(pChoice) {
                    case 1:
                        print_n("Creating random pattern...");
                        g = create_default_gol();
                        create_random_gol(g);
                        break;
                    case 2:
                        print_n("Creating Glider Gun pattern...");
                        g = create_gol((size_t)40);
                        create_glider_gun_gol(g);
                        break;
                    case 3:
                        print_n("Creating Pulsar pattern...");
                        g = create_default_gol();
                        create_pulsar_gol(g);
                        break;
                    case 4:
                        print_n("Creating Lightweight Space Ship pattern...");
                        g = create_default_gol();
                        create_light_weight_spaceship(g);
                        break;
                }

                print(g);
                gol_initialized = 1;
                break;
            // Print next pattern (evolve/step)
            case 2:
                if(!gol_initialized) {
                    print_n("You need to select a pattern first!");
                    break;
                }
                next_pattern(g);
                print(g);
                break;
            // Exit program
            case 3:
                running = 0;
                break;
            // This should never reach execution, if it does then congrats?
            default:
                print_n("How did this happen?!");
                break;
        }
    }

    return 0;
}

// Function implementations

// This wasn't working so I canned it.
//void get_initial_pattern(gol *g) {
//    printDash();
//    print_n("Initial pattern options");
//    printDash();
//
//    int choice;
//
//    print_n("1. Random");
//    print_n("2. Glider Gun");
//    print_n("3. Pulsar");
//    print_n("4. Lightweight Space Ship");
//    do {
//        printf("Enter your selection: ");
//        if(scanf("%d", &choice) == 0) {
//            printf("Invalid input caused scanf buffer overflow, exiting now...");
//            exit(1);
//        }
//    } while(choice < 1 || choice > 4);
//
//    switch(choice) {
//        case 1:
//            print_n("Creating random pattern...");
//            create_random_gol(g);
//            break;
//        case 2:
//            print_n("Creating Glider Gun pattern...");
//            break;
//        case 3:
//            print_n("Creating Pulsar pattern...");
//            break;
//        case 4:
//            print_n("Creating Lightweight Space Ship pattern...");
//            create_light_weight_spaceship(g);
//            break;
//    }
//
//    print(g);
//
//}

void create_random_gol(gol *g) {
    // Set our struct to the default values
//    g = create_default_gol();
    // Seed our random
    srand((unsigned)time(0));
    // Create a second board
    int **board = create_board(g->size);
    // Fill the board with values
    for(int i = 0; i < g->size; i++) {
        for(int j = 0; j < g->size; j++) {
            // If rand is even then make it an alive cell, otherwise make it a dead cell
            board[i][j] = (rand() % 2 == 0 ? 1 : 0);
        }
    }

    // Apply the board to our gol struct
    set_pattern(g, board);
    // Free the board variable for garbage collection.
    free(board);
}

void create_glider_gun_gol(gol *g) {
    const int pSize = 40;
    int pattern[pSize][pSize] = {
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0},
            {0,0,1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,1,1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    };

    // I know I could just use &pattern but I want to have buffer for actions on the board
    int **b = create_board(g->size);
    for(int i = 0; i < pSize; i++) {
        for(int j = 0; j < pSize; j++) {
            b[i][j] = pattern[i][j];
        }
    }

    set_pattern(g, b);

    free(b);
}

void create_pulsar_gol(gol *g) {
    // Create our pattern
    int pattern[17][17] = {
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0},
            {0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0},
            {0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0},
            {0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0},
            {0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0},
            {0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0},
            {0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    };

    int **b = create_board(g->size);
    for(int i = 0; i < 17; i++) {
        for(int j = 0; j < 17; j++) {
            b[i][j] = pattern[i][j];
        }
    }

    set_pattern(g, b);

    free(b);
}

void create_light_weight_spaceship(gol *g) {
    // Create a board of default size so there's room for movement
//    g = create_default_gol();
    // Create our pattern
    int pattern[10][10] = {
            {0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,1,0,0,1,0,0},
            {0,0,0,1,0,0,0,0,0,0},
            {0,0,0,1,0,0,0,1,0,0},
            {0,0,0,1,1,1,1,0,0,0},
            {0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0}
    };

    int **b = create_board(g->size);
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            b[i][j] = pattern[i][j];
        }
    }

    set_pattern(g, b);

    free(b);
}

int** create_board(size_t size) {
    int **b = malloc(sizeof(int *) * size);
    for(int i = 0; i < size; i++) {
        b[i] = malloc(sizeof(int *) * size);
    }

    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            b[i][j] = 0;
        }
    }

    return b;
}

void printDash() {
    printf("-----------------------\n");
}

void print_n(char *c) {
    printf("%s\n", c);
}