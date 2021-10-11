#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "maze.h"

bool readMaze(const char * filename, Maze ** maz)
{
  FILE * fptr = fopen(filename, "r");
  if (fptr == NULL)
  {
    return false; 
  }
  int linelength = 0; 
  int maxlinelength = 0; 
  int numline = 0;
  int onech; 
  
  while (! feof(fptr))
  {
    onech = fgetc(fptr); 
    if (onech != EOF)
    {
      linelength++; 
      if (onech == '\n')
      {
        numline++; 
        if (maxlinelength < linelength)
        {
          maxlinelength = linelength;
        }
        linelength = 0;
      }
    }
  }
  if (numline < 2)
  {
    fclose(fptr); 
    return false; 
  }
  Maze * mz = malloc(sizeof(Maze));
  * maz = mz; 
  mz -> numrow = numline; 
  mz -> numcol = maxlinelength; 
  mz -> cells = malloc(sizeof(int *) * numline);
  int indrow = 0;
  int indcol = 0; 
  for (indrow = 0; indrow < numline; indrow++)
  {
    (mz -> cells)[indrow] = malloc(sizeof(int) * maxlinelength);
    for (indcol = 0; indcol < maxlinelength; indcol++)
    {
      (mz -> cells)[indrow][indcol] = -1;
    } 
  }
  fseek(fptr, 0, SEEK_SET);
  indrow = 0; 
  indcol = 0; 
  while (indrow < numline)
  {
    bool breakline = false; 
    while (breakline == false)
    {
      onech = fgetc(fptr);
      if (onech == EOF)
      {
        return false; 
      }
      switch (onech)
      {
        case ' ':
        mz -> cells[indrow][indcol] = numline * maxlinelength + 1; 
        break; 
        case 's':
        mz -> cells[indrow][indcol] = 0;
        mz -> startrow = indrow; 
        mz -> startcol = indcol; 
        break; 
        case '\n':
        breakline = true; 
        break; 
        case 'b':
        mz -> cells[indrow][indcol] = -1; 
      }
      indcol++; 
    }
    indrow++;
    indcol = 0; 
  }
  fclose(fptr); 
  return true;    
}

void printMaze(Maze * maz)
{
  if (maz == NULL)
  {
    return;
  }
  int indrow;
  int indcol; 
  for (indrow = 0; indrow < (maz -> numrow); indrow++)
  {
    for (indcol = 0; indcol < (maz -> numcol); indcol++)
    {
      printf("%4d ", (maz -> cells)[indrow][indcol]);
    }
    printf("\n");
  }
}

void freeMaze(Maze * maz)
{
  int indrow;
  for (indrow = 0; indrow < (maz -> numrow); indrow++)
  {
    free((maz -> cells)[indrow]);
  }
  free(maz -> cells);
  free(maz);
}      

int canMove(Maze * maz, int row, int col, int dir)
{
  switch (dir) 
  {
    case NORTH:
    row--;
    break;
    case SOUTH:
    row++;
    break; 
    case WEST:
    col--;
    break; 
    case EAST: 
    col++; 
    break; 
  }
  if (row < 0)
  {
    return -1; 
  }
  if (row >= (maz -> numrow))
  {
    return -1; 
  }
  if (col < 0)
  {
    return -1;
  }
  if (col >= (maz -> numcol))
  {
    return -1;
  }
  return (maz -> cells)[row][col];
}

void move(Maze * maz, int row, int col, int distance)
{
  int dest; 
  if (distance == -1)
  {
    fprintf(stderr, "WRONG. Enter a brick.\n");
    return; 
  }
  (maz -> cells)[row][col] = distance; 
  dest = canMove(maz, row, col, EAST);
  if (dest > (distance + 1))
  {
    move(maz, row, col + 1, distance + 1);
  }
  dest = canMove(maz, row, col, WEST);
  if (dest > (distance + 1))
  {
    move(maz, row , col - 1, distance + 1); 
  }
  dest = canMove(maz, row, col, NORTH);
  if (dest > (distance + 1))
  {
    move(maz, row - 1, col, distance + 1);
  }
  dest = canMove(maz, row, col, SOUTH);
  if (dest > (distance + 1))
  {
    move(maz, row + 1, col, distance + 1);
  }
}

void findDistance(Maze * maz)
{
  if (maz == NULL)
  {
    return;
  }
  move(maz, maz -> startrow, maz -> startcol, 0);
}
