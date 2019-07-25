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
    printf("Cursor Position Before Move: %d\n",
           getCursorPosition(grid_size, grid_size, grid));
    moveCursor(grid_size, grid_size, grid);
    drawGrid(grid_size, grid_size, grid);
    printf("Cursor Position After Move: %d\n",
           getCursorPosition(grid_size, grid_size, grid));
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
