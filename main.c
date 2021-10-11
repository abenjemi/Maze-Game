#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

int main(int argc, char * argv[])
{
  if (argc < 2)
  {
    fprintf(stderr, "need a file name\n");
    return -1;
  }

  Maze * maz;
  int rtv; 
  rtv = readMaze(argv[1], &maz); 
  if (rtv == 0)
  {
    return -1;
  }
  findDistance(maz);
  printMaze(maz);
  freeMaze(maz); 
  return 0;
}
