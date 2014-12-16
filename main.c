/*
  MAIN.C

  Main function for maze solver
*/

#include <stdio.h>
#include <stdlib.h>

#include "maze.h"
#include "solve.h"


int main(int argc, char *argv[]) {
    struct maze maze;
// INCASE OF NO INPUT OF MAZE
    if ( argc < 2 ) {
        puts("You must specify the filename of your maze");
        return EXIT_FAILURE;
    }
    else if ( argc > 2 ) {
        puts("Too many command line arguments");
        return EXIT_FAILURE;
    }

    GetMazeFromFile(argv[1], &maze);

	// IF YOU GET TO HERE YOU HAD SUCCESS ON READING IN MAZE

//    CALL FUNCTIONS TO PRINT MAZE WITH AND WITHOUT THE SHORTEST PATH.
    PrintMaze(&maze);
	findPath(&maze);
    printf("\n");
    PrintMaze(&maze);
    FreeMaze(&maze);

    return EXIT_SUCCESS;
}
