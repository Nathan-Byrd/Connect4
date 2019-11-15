#include <stdlib.h>
#include <stdio.h>
#include "board.h"
#include "CursorTrakedWindow.h"

Board makeBoard(int numRows, int numCols, char blankChar,int numToWin) {
  Board board;

  board.theBoard = (char**)malloc(numRows * sizeof(char*));
  for (int i = 0; i < numRows; ++i) {
    board.theBoard[i] = (char*)malloc(numCols * sizeof(char));
    for (int j = 0; j < numCols; ++j) {
      board.theBoard[i][j] = blankChar;
    }
  }

  board.numRows = numRows;
  board.numCols = numCols;
  board.blankChar = blankChar;
  board.numtoWin = numToWin;
  return board;
}

void printBoard(Board board) {
  //print column header


  for (int row = 0; row < board.numRows; ++row) {
    for (int col = 0; col < board.numCols; ++col) {
      printf("%c ", board.theBoard[row][col]);
    }
    printf("\n");
  }
}

void cleanUpBoard(Board* board) {

  for (int row = 0; row < board->numRows; ++row) {
    free(board->theBoard[row]);
  }
  free(board->theBoard);
  board->theBoard = NULL;
  board->numRows = 0;
  board->numCols = 0;
}

void placeMove(Move move, Board *board, CursorTrackedWindow *win) {

  board->theBoard[move.row][move.col] = move.marker;
  addCharacter(win,move.row + 1,move.col,move.marker);
  CursorTrackedWindowMove(win, win->cursorRow, win->cursorCol);

  if(move.marker == 'X') {
    addCharacter(win,win->cursorRow,win->cursorCol,'O');
  }
  else{
    addCharacter(win,win->cursorRow,win->cursorCol,'X');
  }
  CursorTrackedWindowMove(win, win->cursorRow, win->cursorCol);
  wrefresh(win->cursesWin);

}

bool isColumnFull(Board *board, int col) {
  return board->theBoard[0][col] != '*';
}

int findDropSpace(Board* board,int col){
  int i = board -> numRows -1;
  while(true){
    if(board -> theBoard[i][col] == '*'){
      return  i;
    }
    i--;
  }


}
