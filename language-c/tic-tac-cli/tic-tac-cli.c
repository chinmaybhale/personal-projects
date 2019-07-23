#include <stdio.h>
#include <stdbool.h>

/* forward declaration(s) */
int pickPos(void);
int checkOneWin(int nRows, int nCols, int board[nRows][nCols]);
int checkTwoWin(int nRows, int nCols, int board[nRows][nCols]);
bool checkChoiceOpen(int, int nRows, int nCols, int board[nRows][nCols]);
void translateChoice(int, int nRows, int nCols, int board[nRows][nCols]);
void drawBoard(int nRows, int nCols, int board[nRows][nCols]);
void drawLineBreak(void);

/* global variable(s) */
char g_playerOneSym;
char g_playerTwoSym;
bool g_playerOneTurn = true;

int main(void) {
  int boardSize;
  int choice;
  bool gameFlag = true;
  int turnCounter = 1;

  /* board init */
  printf("What size game would you like to play? ");
  printf("(i.e. To play a 3x3 board, enter '3'.)\n");

  do {
    printf("Game Board Size: ");
    scanf("%d", &boardSize);

    if(boardSize < 3) {
      printf("Sorry. The board size must be at least 3x3.\n");
    }
  }
  while(boardSize < 3);

  drawLineBreak();
  int board[boardSize][boardSize];
  printf("Initializing game board...\n\n");

  // set all initial values to zero
  for(int row = 0; row < boardSize; ++row) {
    for(int column = 0; column < boardSize; ++column) {
      board[row][column] = 0;
    }
  }

  // display board initially
  drawBoard(boardSize, boardSize, board);
  printf("\nGame board initialized.\n");

  drawLineBreak();
  /* assign player characters */
  printf("Please enter any single character to represent you.\n");

  // player one's assignment
  printf("Player 1's Symbol: ");
  scanf(" %c", &g_playerOneSym);

  // player two's assignment
  printf("Player 2's Symbol: ");
  scanf(" %c", &g_playerTwoSym);

  // feedback
  printf("Good choices!\n");

  drawLineBreak();
  /* main game loop init */
  printf("Game Begin!\n");
  drawBoard(boardSize, boardSize, board);

  while(gameFlag) {
    drawLineBreak();
    /* prompt turn */
    do {
      choice = pickPos();

      if(choice == -1) {
        gameFlag = false;
        break;
      }
    }
    while(!checkChoiceOpen(choice, boardSize, boardSize, board));

    // set choice
    translateChoice(choice, boardSize, boardSize, board);

    // re-draw board
    drawBoard(boardSize, boardSize, board);
    printf("Moves Completed: (%d/%d)\n", turnCounter, boardSize * boardSize);
    ++turnCounter;

    // check win-condition(s)
    if(checkOneWin(boardSize, boardSize, board) == 1) {
      drawLineBreak();
      printf("Player 1 Won in %d Moves!\n", (turnCounter / 2));
      gameFlag = false;
    }
    else if(checkTwoWin(boardSize, boardSize, board) == 2) {
      drawLineBreak();
      printf("Player 2 Won in %d Moves!\n", (turnCounter / 2));
      gameFlag = false;
    }
  }

  printf("\nGAME OVER.\n");
  return 0;
}


int pickPos(void) {
  auto int choice;

  if(g_playerOneTurn) {
    printf("Player 1's Choice: ");
    scanf("%d", &choice);
  }
  else {
    printf("Player 2's Choice: ");
    scanf("%d", &choice);
  }

  return choice;
}

bool checkChoiceOpen(int choice, int nRows, int nCols,
                 int board[nRows][nCols]) {
  auto int row, column, boardPosition = 1;

  /* check applicability to board size */
  if(choice > nRows * nCols) {
    printf("Sorry. That position doesn't exist.\n");
    return false;
  }
  /* traverse board */
  for(row = 0; row < nRows; ++row) {
    for(column = 0; column < nCols; ++column) {
      // find choice position
      if(boardPosition == choice) {
        if(board[row][column] == 0) {
          return true;
        }
        else {
          printf("Sorry. That position is already filled.\n");
          return false;
        }
      }

      ++boardPosition;
    }
  }

  return false;
}

int checkOneWin(int nRows, int nCols, int board[nRows][nCols]) {
  auto int row, column;

  /* player one win condition(s) */
  // horizontal check
  for(row = 0; row < nRows; ++row) {
    for(column = 0; column < nCols - 2; ++column) {
      if(board[row][column + 0] == 1)
        if(board[row][column + 1] == 1)
          if(board[row][column + 2] == 1) {
            return 1;
          }
    }
  }

  // vertical check
  for(column = 0; column < nCols; ++column) {
    for(row = 0; row < nRows - 2; ++row) {
      if(board[row + 0][column] == 1)
        if(board[row + 1][column] == 1)
          if(board[row + 2][column] == 1) {
            return 1;
          }
    }
  }

  // diagonal check
  for(row = 0; row < nRows - 2; ++row) {
    for(column = 0; column < nCols - 2; ++column) {
      if(board[row + 0][column + 0] == 1)
        if(board[row + 1][column + 1] == 1)
          if(board[row + 2][column + 2] == 1) {
            return 1;
          }
    }
  }

  return 0;
}

int checkTwoWin(int nRows, int nCols, int board[nRows][nCols]) {
  auto int row, column;

  /* player one win condition(s) */
  // horizontal check
  for(row = 0; row < nRows; ++row) {
    for(column = 0; column < nCols - 2; ++column) {
      if(board[row][column + 0] == 2)
        if(board[row][column + 1] == 2)
          if(board[row][column + 2] == 2) {
            return 2;
          }
    }
  }

  // vertical check
  for(column = 0; column < nCols; ++column) {
    for(row = 0; row < nRows - 2; ++row) {
      if(board[row + 0][column] == 2)
        if(board[row + 1][column] == 2)
          if(board[row + 2][column] == 2) {
            return 2;
          }
    }
  }

  // diagonal check
  for(row = 0; row < nRows - 2; ++row) {
    for(column = 0; column < nCols - 2; ++column) {
      if(board[row + 0][column + 0] == 2)
        if(board[row + 1][column + 1] == 2)
          if(board[row + 2][column + 2] == 2) {
            return 2;
          }
    }
  }

  return 0;
}

void translateChoice(int choice, int nRows, int nCols,
                     int board[nRows][nCols]) {
  auto int row, column, boardPosition = 1;

  /* traverse board */
  for(row = 0; row < nRows; ++row) {
    for(column = 0; column < nCols; ++column) {
      /* test if current position is equal to the chosen
         position */
      if(boardPosition == choice) {
        if(g_playerOneTurn) {
          board[row][column] = 1; // player one's turn

          // switch turn to player 2
          g_playerOneTurn = false;
        }
        else {
          board[row][column] = 2; // player two's turn

          // switch turn to player 1
          g_playerOneTurn = true;
        }
      }

      ++boardPosition;
    }
  }
}

void drawBoard(int nRows, int nCols, int board[nRows][nCols]) {
  auto int row, column, boardPosition = 1;

  /* display table with board position(s) */
  for(row = 0; row < nRows; ++row) {
    for(column = 0; column < nCols; ++column) {
      /* check for move(s) and default(s)*/
      if(board[row][column] == 1) {
        printf("[ %c ] ", g_playerOneSym);
      }
      else if(board[row][column] == 2) {
        printf("[ %c ] ", g_playerTwoSym);
      }
      else {
        if(boardPosition < 10) {
          printf("[00%d] ", boardPosition); // 1 digit
        }
        else if(boardPosition < 100) {
          printf("[0%d] ", boardPosition);  // 2 digits
        }
        else {
          printf("[%d] ", boardPosition);   // 3 digits
        }
      }

      ++boardPosition;
    }

    printf("\n"); // next row
  }
}

void drawLineBreak(void) {
  printf("-------------------------\n");
}
