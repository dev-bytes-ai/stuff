#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define BOARD_SIZE 8

// Define the chessboard
char board[BOARD_SIZE][BOARD_SIZE] = {{'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
                                      {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
                                      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                      {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
                                      {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}};

// Function to print the chessboard
void printBoard() {
  printf("  a b c d e f g h\n");
  for (int i = 0; i < BOARD_SIZE; i++) {
    printf("%d ", 8 - i);
    for (int j = 0; j < BOARD_SIZE; j++) {
      printf("%c ", board[i][j]);
    }
    printf("%d\n", 8 - i);
  }
  printf("  a b c d e f g h\n");
}

// Convert algebraic notation to array index
bool convertPosition(const char *move, int *fromRow, int *fromCol, int *toRow,
                     int *toCol) {
  if (strlen(move) != 4)
    return false;

  *fromCol = move[0] - 'a';
  *fromRow = 8 - (move[1] - '0');
  *toCol = move[2] - 'a';
  *toRow = 8 - (move[3] - '0');

  return (*fromRow >= 0 && *fromRow < BOARD_SIZE && *fromCol >= 0 &&
          *fromCol < BOARD_SIZE && *toRow >= 0 && *toRow < BOARD_SIZE &&
          *toCol >= 0 && *toCol < BOARD_SIZE);
}

// Make a move on the board if valid
bool makeMove(const char *move) {
  int fromRow, fromCol, toRow, toCol;
  if (!convertPosition(move, &fromRow, &fromCol, &toRow, &toCol)) {
    printf("Invalid move format!\n");
    return false;
  }

  if (board[fromRow][fromCol] == ' ') {
    printf("No piece at the source!\n");
    return false;
  }

  // For now, just move the piece without validating chess rules
  board[toRow][toCol] = board[fromRow][fromCol];
  board[fromRow][fromCol] = ' ';

  return true;
}

int main() {
  char move[5];
  bool isGameOver = false;
  int turn = 0;

  printf("Welcome to Simple Chess!\n");
  while (!isGameOver) {
    printBoard();
    if (turn % 2 == 0) {
      printf("White's move: ");
    } else {
      printf("Black's move: ");
    }

    // Get the move from the user
    scanf("%4s", move);

    // Make the move
    if (makeMove(move)) {
      turn++;
    } else {
      printf("Invalid move. Try again.\n");
    }

    // You can add logic here to check for checkmate, stalemate, etc.
  }

  return 0;
}
