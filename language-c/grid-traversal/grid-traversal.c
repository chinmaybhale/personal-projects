#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

/* struct definition(s) */

/* forward declaration(s) */
void initGrid(int nRows, int nCols, int grid[nRows][nCols]);
void drawGrid(int nRows, int nCols, int grid[nRows][nCols]);
void moveCursor(int nRows, int nCols, int grid[nRows][nCols]);
int getCursorPosition(int nRows, int nCols, int grid[nRows][nCols]);
void setCursorPosition(int cursorPosition, int direction, int nRows, int nCols,
                       int grid[nRows][nCols]);
void initObstacles(int numObstacles, int nRows, int nCols,
                   int grid[nRows][nCols]);
void moveObstacles(int nRows, int nCols, int grid[nRows][nCols]);
int checkBorder(int xPosition, int yPosition, int nRows, int nCols);
void checkConditions(int nRows, int nCols, int grid[nRows][nCols]);

/* global variable(s) */
bool g_active = true;

int main(void) {
  int grid_size;

  // random initialization
  srand(time(NULL));

  // board initialization
  printf("Please enter grid size: ");
  scanf("%d", &grid_size);

  int grid[grid_size][grid_size];
  initGrid(grid_size, grid_size, grid);

  drawGrid(grid_size, grid_size, grid);

  printf("Grid initialized.\n");

  // main loop
  while(g_active) {
    moveCursor(grid_size, grid_size, grid);
    moveObstacles(grid_size, grid_size, grid);
    drawGrid(grid_size, grid_size, grid);
    printf("=========================================\n");
    checkConditions(grid_size, grid_size, grid);
  }

  return 0;
}

void initGrid(int nRows, int nCols, int grid[nRows][nCols]) {
  /**
   * initGrid initializes the grid with appropriate values.
   *
   * @param nRows: Represents the number of rows in the array.
   * @param nCols: Represents the number of columns in the array.
   * @param grid: Represents the multi-dimensional array.
   */

  auto int row, column;

  // initialize values to zero
  printf("Initializing grid default values...\n");

  for(row = 0; row < nRows; ++row) {
    for(column = 0; column < nCols; ++column) {
      grid[row][column] = 0;
    }
  }

  // set player starting point
  grid[0][0] = 1;

  int goalRow = rand() % nRows;
  int goalCol = rand() % nCols;

  grid[goalRow][goalCol] = 2;

  // add obstacles
  initObstacles(nRows, nRows, nCols, grid);
}

void initObstacles(int numObstacles, int nRows, int nCols,
                   int grid[nRows][nCols]) {
  /**
   * initObstacles places obstacles at various indices
   * of the grid.
   *
   * @param numObstacles: Represents the number of obstacles to add
   * @param nRows: Represents the number of rows in the grid.
   * @param nCols: Represents teh number of columns in the grid.
   * @param grid: Represents the multi-dimensional array.
   */

  auto int numGenerated = 0;
  auto int xPosition, yPosition;

  while(numGenerated < numObstacles) {
    xPosition = rand() % nRows;
    yPosition = rand() % nCols;

    if(grid[xPosition][yPosition] == 0) {
      grid[xPosition][yPosition] = 3;
      ++numGenerated;
    }
  }
}

void drawGrid(int nRows, int nCols, int grid[nRows][nCols]) {
  /**
   * drawGrid traverses a multi-dimensional array and prints
   * a bracket pair in place of each index to visually display
   * the grid. Additionally, drawGrid checks for the value of the
   * index and appropriately places a character within.
   *
   * @param nRows: Represents the number of rows in the array.
   * @param nCols: Represents the number of columns in the array.
   * @param grid: Represents the multi-dimensional array.
   */

  auto int row, column;

  for(row = 0; row < nRows; ++row) {
    for(column = 0; column < nCols; ++column) {
      if(grid[row][column] == 1) {
        printf("[*] ");
      }
      else if(grid[row][column] == 2) {
        printf("[x] ");
      }
      else if(grid[row][column] == 3) {
        printf("[#] ");
      }
      else {
        printf("[ ] ");
      }
    }

    printf("\n"); // next row
  }
}

void moveCursor(int nRows, int nCols, int grid[nRows][nCols]) {
  /**
   * moveCursor checks for a character input and appropriately sets
   * the value of the multi-dimensional array adjacent to the current
   * index of the cursor depending on the character inputted as follows:
   *
   * W: Up, A: Left, S: Down, D: Right.
   *
   * @param nRows: Represents the number of rows in the array.
   * @param nCols: Represents the number of columns in the array.
   * @param grid: Represents the multi-dimensional array.
   */

  auto char direction;

  printf("Direction: ");
  scanf(" %c", &direction);

  if(direction == 'q') {
    g_active = false;
    return;
  }

  switch(direction) {
  case 'd': {
    setCursorPosition(getCursorPosition(nRows, nCols, grid), 0,
                      nRows, nCols, grid);
  }
    break;
  case 'w': {
    setCursorPosition(getCursorPosition(nRows, nCols, grid), 90,
                      nRows, nCols, grid);
  }
    break;
  case 'a': {
    setCursorPosition(getCursorPosition(nRows, nCols, grid), 180,
                      nRows, nCols, grid);
  }
    break;
  case 's': {
    setCursorPosition(getCursorPosition(nRows, nCols, grid), 270,
                      nRows, nCols, grid);
  }
    break;
  }
}

int getCursorPosition(int nRows, int nCols, int grid[nRows][nCols]) {
  /**
   * getCursorPosition traverses a multi-dimensional array and
   * searches for the cursor - distinguished by the value 1.
   *
   * @param nRows: Represents the number of rows in the array.
   * @param nCols: Represents the number of columns in the array.
   * @param grid: Represents the multi-dimensional array.
   * @return: Represents the cursors index.
   */

  auto int row, column, cursorPosition = 1;

  for(row = 0; row < nRows; ++row) {
    for(column = 0; column < nCols; ++column) {
      if(grid[row][column] == 1) {
        return cursorPosition;
      }

      ++cursorPosition;
    }
  }

  return cursorPosition;
}

void setCursorPosition(int cursorPosition, int direction, int nRows,
                       int nCols, int grid[nRows][nCols]) {
  /**
   * setCursorPosition receives the current position of the cursor
   * and the direction and moves the cursor appropriately - assumes
   * the boundaries have already been tested.
   *
   * @param cursorPosition: Represents the current cursor position.
   * @param directionTo: Represents the direction to move to.
   * @param nRows: Represents the number of rows in the array.
   * @param nCols: Represents the number of columns in the array.
   * @param grid: Represents the multi-dimensional array.
   */

  auto int row, column, gridPosition = 1;

  for(row = 0; row < nRows; ++row) {
    for(column = 0; column < nCols; ++column) {
      if(gridPosition == cursorPosition) {
        grid[row][column] = 0; // remove current position

        // set new position
        switch(direction) {
        case 0: {
          grid[row][column + 1] = 1; // move right
        }
          break;
        case 90: {
          grid[row - 1][column] = 1; // move up
        }
          break;
        case 180: {
          grid[row][column - 1] = 1; // move left
        }
          break;
        case 270: {
          grid[row + 1][column] = 1; // move down
        }
          break;
        }
      }

      ++gridPosition;
    }
  }
}

void moveObstacles(int nRows, int nCols, int grid[nRows][nCols]) {
  /**
   * moveObstacles traverses the grid and moves every obstacle to a
   * random adjacent position, or maintain position.
   *
   * @param nRows: Represents the number of rows in the grid.
   * @param nCols: Represents teh number of columns in the grid.
   * @param grid: Represents the multi-dimensional array.
   */

  auto int row, column, choice;

  for(row = 0; row < nRows; ++row) {
    for(column = 0; column < nCols; ++column) {
      if(grid[row][column] == 3) {
        grid[row][column] = 0; // reset current position

        // check for border
        if(checkBorder(row, column, nRows, nCols) != 0) {
          if(checkBorder(row, column, nRows, nCols) == 1) {
            if(grid[row][column - 1] != 2) {
              grid[row][column - 1] = 3;
            }
          }
          else if(checkBorder(row, column, nRows, nCols) == 2) {
            if(grid[row + 1][column] != 2) {
              grid[row + 1][column] = 3;
            }
          }
          else if(checkBorder(row, column, nRows, nCols) == 3) {
            if(grid[row][column + 1] != 2) {
              grid[row][column + 1] = 3;
            }
          }
          else if(checkBorder(row, column, nRows, nCols) == 4) {
            if(grid[row - 1][column] != 2) {
              grid[row - 1][column] = 3;
            }
          }
          else {
            grid[row][column] = 3;
          }
        }
        else {
          // set new position
          choice = rand() % 4;

          switch(choice) {
          case 0: {
            if(grid[row][column + 1] != 2) {
              grid[row][column + 1] = 3; // move right
            }
          }
            break;
          case 1: {
            if(grid[row - 1][column] != 2) {
              grid[row - 1][column] = 3; // move up
            }
          }
            break;
          case 2: {
            if(grid[row][column - 1] != 2) {
              grid[row][column - 1] = 3; // move left
            }
          }
            break;
          case 3: {
            if(grid[row + 1][column] != 2) {
              grid[row + 1][column] = 3; // move down
            }
          }
            break;
          default: {
            grid[row][column] = 3;     // maintain position
          }
            break;
          }
        }
      }
    }
  }
}

int checkBorder(int xPosition, int yPosition, int nRows, int nCols) {
  /**
   * checkBorder recieves a position and checks if that position
   * is located on a particular border. checkBorder then returns
   * the appropriate value that represents the border.
   *
   * 0: no border, 1: right border, 2: top border, 3: left border,
   * 4: bottom border.
   *
   * @param xPosition: Represents the elements row value.
   * @param yPosition: Represents the elements column value.
   * @param nRows: Represents the number of rows in the grid.
   * @param nCols: Represents teh number of columns in the grid.
   * @param grid: Represents the multi-dimensional array.
   */

  auto int borderValue;

  // check intersections
  if(xPosition == 0) {
    borderValue = 2;
  }
  else if(xPosition == nRows) {
    borderValue = 4;
  }
  else if(yPosition == 0) {
    borderValue = 3;
  }
  else if(yPosition == nCols) {
    borderValue = 1;
  }
  else {
    borderValue = 0;
  }

  return borderValue;
}

void checkConditions(int nRows, int nCols, int grid[nRows][nCols]) {
  /**
   * checkConditions traverses the grid and checks for the following:
   * 1. cursor exists
   * 2. exit exists
   *
   * @param nRows: Represents the number of rows in the grid.
   * @param nCols: Represents teh number of columns in the grid.
   * @param grid: Represents the multi-dimensional array.
   */

  auto int row, column;
  auto bool cursorExists = false, exitExists = false;

  for(row = 0; row < nRows; ++row) {
    for(column = 0; column < nCols; ++column) {
      if(grid[row][column] == 1) {
        cursorExists = true;
      }
      else if(grid[row][column] == 2) {
        exitExists = true;
      }
    }
  }

  if(!cursorExists) {
    printf("Game Over. You died.\n");
    g_active = false;
  }
  else if(!exitExists) {
    printf("You escaped. You win!\n");
    g_active = false;
  }
}
