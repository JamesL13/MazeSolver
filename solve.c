/*
  SOLVE.C
  Implementation of maze solving operation
*/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "solve.h"

//MAKE THE INTEGER ARRAY
int **make2DIntArray(int rows, int columns)
{
	int** array = (int**) malloc(rows * sizeof(int *));
	int i;
	for(i = 0; i<rows; i++) {
		array[i] = (int*) malloc(columns * sizeof(int));
		int j=0;
		for(j=0; j<columns;j++)
			array[i][j] = READY;
	}
	
	return array;
}

//GET THE NODE CONTENT
char getNodeContent(struct maze* maze, int iNodeNumber)
{
	int nRow = iNodeNumber / maze->numcols;
	int nCol = iNodeNumber - (nRow * maze->numcols);
	return maze->map[nRow][nCol];
}

//CHANGE THE NODE CONTENT IF ITS PART OF THE PATH
void changeNodeContent(struct maze* maze, int iNodeNumber, char pathChar)
{
	int nRow = iNodeNumber / maze->numcols;
	int nCol = iNodeNumber - (nRow * maze->numcols);
	maze->map[nRow][nCol] = pathChar;
}

//GET NODE STATUS CONTENT ON IF IT HAS BEEN VISITED
int getNodeStatusContent(int** mazeStatus, int iNodeNumber, int cols)
{
	int nRow = iNodeNumber / cols;
	int nCol = iNodeNumber - (nRow * cols);
	return mazeStatus[nRow][nCol];
}

//CHANGE THE NODE STATUS CONTENT IF WE HAVE VISITED IT
void changeNodeStatus(int** mazeStatus, int iNodeNumber, int cols, int status)
{
	int nRow = iNodeNumber / cols;
	int nCol = iNodeNumber - (nRow * cols);
	mazeStatus[nRow][nCol] = status;
}

//FIND THE SHORTEST PATH
void shortestPath(struct maze* maze, int nodeStart)
{
	int empty = 0;
	int rows = maze->numrows;
	int cols = maze->numcols;
	int maxsize = rows * cols;
	int Queue[maxsize];
	int Origin[maxsize];
	int i;
	int exitNode = 0;
	char moveToSpot;
	
	for(i=0; i<maxsize;i++)
	{
		Queue[i] = 0;
		Origin[i]=0;
	}
	
	int front = 0;
	int rear= 0;
	
	// CREATE ARRAY TO HOLD THE STATUS OF EACH GRID POINT WE HAVE CHECKED
	int** mazeStatus = make2DIntArray(rows, cols);
	
	Queue[rear] = nodeStart;
	Origin[rear] = -1;
	rear++;
	
	int current, left, right, top, down;
	
	while(front != rear )  // WHILE THE QUEUE IS NOT EMPTY EXECUTE THE FOLLOWING
	{

		if (Queue[front]==exitNode )
			break; // MAZE IS SOLVED
			
		current = Queue[front];
		left = current - 1;

		if (left >=0 && left/cols==current/cols) 	//IF LEFT NODE EXITS
		{
			moveToSpot = getNodeContent(maze, left);
			if (moveToSpot == MAZE_EXIT)
			{
				// EXIT IS FOUND
				exitNode = left;
			}
			if (moveToSpot == MAZE_PATH ||  moveToSpot == MAZE_EXIT)
			{   //CHECK TO SEE IF THE NODE HAS BEEN VISITED
				if (getNodeStatusContent(mazeStatus, left, cols) == READY)
					{
						Queue[rear] = left;
						Origin[rear] = current;
                        //CHANGE THE NODE STATUS
						changeNodeStatus(mazeStatus, left, cols, WAITING);
						rear++;
					}	
			}
		}
		
		right = current + 1;
		if (right < maxsize &&  (right / cols) == (current / cols) ) //IF RIGHT NODE EXITS
			{
			moveToSpot = getNodeContent(maze, right);
			if (moveToSpot == MAZE_EXIT)
			{
				// EXIT IS FOUND
				exitNode = right;
			}
			if (moveToSpot == MAZE_PATH ||  moveToSpot == MAZE_EXIT)
				{   //CHECK TO SEE IF THE NODE HAS BEEN VISITED
					if (getNodeStatusContent(mazeStatus, right, cols) == READY)
						{
							Queue[rear] = right;
							Origin[rear] = current;
                            //CHANGE THE NODE STATUS
							changeNodeStatus(mazeStatus, right, cols, WAITING);
							rear++;
						}	
				}
			}
		
		top = current - cols;
		if (top >= 0 && top < maxsize)
			{
			moveToSpot = getNodeContent(maze, top);
			if (moveToSpot == MAZE_EXIT)
			{
				// EXIT IS FOUND
				exitNode = top;
			}
			if (moveToSpot == MAZE_PATH ||  moveToSpot == MAZE_EXIT)
				{   //CHECK TO SEE IF THE NODE HAS BEEN VISITED
					if (getNodeStatusContent(mazeStatus, top, cols) == READY)
						{
							Queue[rear] = top;
							Origin[rear] = current;
                            //CHANGE THE NODE STATUS
							changeNodeStatus(mazeStatus, top, cols, WAITING);
							rear++;
						}	
				}
			}
			
		down = current + cols;
		if (down < maxsize && down > 0 )
			{
			moveToSpot = getNodeContent(maze, down);
			if (moveToSpot == MAZE_EXIT)
			{
				// EXIT FOUND
				exitNode = down;
			}
			if (moveToSpot == MAZE_PATH ||  moveToSpot == MAZE_EXIT)
				{   //CHECK TO SEE IF THE NODE HAS BEEN VISTED
					if (getNodeStatusContent(mazeStatus, down, cols) == READY)
						{   
							Queue[rear] = down;
							Origin[rear] = current;
							//CHANGE THE NODE STATUS
                            changeNodeStatus(mazeStatus, down, cols, WAITING);
							rear++;
						}	
				}
			}
		
		changeNodeStatus(mazeStatus, current, cols, PROCESSED);
		front++;
			
	}
	
	// UPDATE THE MAZE WITH THE PATH
	current = exitNode;
	changeNodeContent(maze, exitNode, MAZE_TRAIL);
	for(i=front; i>=0; i--)
			{
				if (Queue[i]==current)
				{
					current=Origin[i];
					if (current==-1)		// MAZE IS SOLVED
						return;
					changeNodeContent(maze, current, MAZE_TRAIL);
				}
			}
	
	return;
}
//FIND PATH
void findPath(struct maze* theMaze)
{
	int iStartNode = theMaze->starty * theMaze->numcols + theMaze->startx;
	
	return (shortestPath(theMaze, iStartNode));
}






