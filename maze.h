#ifndef MAZE_H
#define MAZE_H
#include<stdbool.h>
typedef struct
{
  int numrow, numcol;     
  int startrow, startcol; 
  int * * cells;
} Maze;
 
enum {EAST, SOUTH, WEST, NORTH}; 

bool readMaze(const char * filename, Maze ** maz);
void printMaze(Maze * maz);
void freeMaze(Maze * maz);
int canMove(Maze * maz, int row, int col, int dir);
void move(Maze * maz, int row, int col, int distance);
void findDistance(Maze * maz);
#endif
  
  
