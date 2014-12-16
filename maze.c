/*
  MAZE.C

  Implementation of maze functions
*/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "maze.h"


/*  CREATES A MAZE FROM A FILE  */
int MAX_CHARS_PER_ROW = 50;
int MAX_ROWS = 10;
int DELTA_CHARS = 10;
int DELTA_ROWS = 5;

//FUNCTION TO MALLOC SPACE NEEDED FOR 2D ARRAY
char **make2DArray(int rows, int columns)
{
	char **array = (char**) malloc(rows * sizeof(char *));
	int i;
	for(i = 0; i<rows; i++) {
		array[i] = (char*) malloc(columns * sizeof(char));
		memset(array[i], 0, columns);
	}
	
	return array;
}

//FUNCTION TO FREE MEMORY
void free2DArray(char** array, int rows) {

	int n;
    for ( n = 0; n < rows; n++ )
        free(array[n]);

    free(array);
}

//FUNCTION TO READ IN MAZE FROM FILE
void GetMazeFromFile(char * filename, struct maze * maze) 
{
    //FLAGS TO ERROR CHECK
	int success = 0;
	int number_of_rows = 0;
	int found_start = 0;
	int found_exit = 0;
	int iLoop = 0;
	
	char** ioMaze = NULL;
	
	while (success == 0)
	{
		// INTITIALIZE START AND EXIT POSITIONS
		found_start = 0;
		found_exit = 0;

		success = 1; //ASSUME THAT THE MAZE IS READ IN CORRECTLY, IF NOT, SET SUCCESS TO 0 SO THE PROGRAM TRIES AGAIN
        //ERROR WITH THE FILE
		FILE* fp = fopen(filename, "r");
		if(!fp) 
			{ 
			printf("There was a problem opening the file\n"); 
			exit(0); 
			} 
  
		int maze_size = sizeof(char) * (MAX_CHARS_PER_ROW) * (MAX_ROWS);
		
		// ALLOCATE MAZE SIZE
		ioMaze = make2DArray(MAX_ROWS, MAX_CHARS_PER_ROW);
		
	    char ioLine[MAX_CHARS_PER_ROW];
	    memset(ioLine, 0, MAX_CHARS_PER_ROW);
	    
	    // READS IN A LINE, INCLUDING THE NEWLINE CHARACTER 
	    while( fgets((char*)ioLine, sizeof(ioLine), fp) )
	    {
				// GET THE LENGTH OF THE STRING THAT WAS READ INTO THE ARRAY (INCLUDING NEWLINE CHAR)
	            size_t len = strlen((char *)ioLine);

				if (len == (MAX_CHARS_PER_ROW - 1))
					{ 
					// IT IS POSSIBLE TO HAVE A STRING LONGER THAN THE MAX_CHARS_PER_ROW SIZE
					// THE FILE NEEDS TO BE RESET WITH LONFER LINE LENGTHS
					rewind(fp);
					MAX_CHARS_PER_ROW = MAX_CHARS_PER_ROW + DELTA_CHARS;
					number_of_rows = 0;
					free2DArray(ioMaze, MAX_ROWS);
					success = 0;
					break;
					}
					
				if (number_of_rows > (MAX_ROWS-1))
					{ // IT IS POSSIBLE TO HAVE A STRING LONGER THAN THE MAX_CHARS_PER_ROW SIZE
                     // THE FILE NEEDS TO BE RESET WITH LONFER LINE LENGTH
					rewind(fp);
					free2DArray(ioMaze, MAX_ROWS);
					MAX_ROWS = MAX_ROWS + DELTA_ROWS;
					number_of_rows = 0;
					success = 0;
					break;
					}
	
				// REPLACE A NEW LINE CHARACTER AT THE END OF THE LINE 
				// WITH A NULL CHARACTER 
	            if(len > 1 &&  ioLine[len-1] == '\n')
	                ioLine[len-1] = 0;
	
	            len = strlen((char *)ioLine);

				//  THE LINE WE READ IN FALLS WITHIN OUR ARRAY SIZE SO ADD IT TO THE ARRAY
				memcpy(&ioMaze[number_of_rows][0], ioLine, len);
				
				// CHECK FOR BOTH THE START AND EXIT IN THE MAZE
				if (!found_start)
				{
					for(iLoop = 0; iLoop<len; iLoop++)
						{
							if (ioMaze[number_of_rows][iLoop] == 'S')
							{
								maze->startx = iLoop;
								maze->starty = number_of_rows;
								found_start = 1;
							}
						}	
				}

				if (!found_exit)
				{
					for(iLoop = 0; iLoop<len; iLoop++)
						{
							if (ioMaze[number_of_rows][iLoop] == 'E')
							{
								maze->exitx = iLoop;
								maze->exity = number_of_rows;
								found_exit = 1;
							}
						}
				}
				
				number_of_rows++;
	    }
	    
	    fclose(fp);
    
	}
	
	// ROWS SHOULD RETURN THE NUMBER OF LINES READ INTO THE ARRAY
	maze->numrows = number_of_rows;
	maze->numcols = MAX_CHARS_PER_ROW;
	maze->map = ioMaze;

// IF NOT START OR END PRINT ERROR AND EXIT PROGRAM	
if (found_start == 0)
{
	printf("\nNO START. PROGRAM EXIT!\n");
	exit(1);
}


if (found_exit == 0)
{
	printf("\nNO EXIT. PROGRAM EXIT\n");
	exit(1);
}

return;
}
/*  FREES MEMORY USED BY THE MAZE  */

void FreeMaze(struct maze * maze) {
    int n;

    for ( n = 0; n < maze->numrows; n++ )
        free(maze->map[n]);

    free(maze->map);
}


/*  OUTPUTS THE MAZE  */

void PrintMaze(struct maze * maze) {
    int n;

    for ( n = 0; n < maze->numrows; ++n )
        puts(maze->map[n]);
}
