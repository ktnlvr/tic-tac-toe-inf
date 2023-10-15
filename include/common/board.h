#pragma once

#include "./common/types.h"

typedef enum board_mark {
  BOARD_MARK_KNOT,
  BOARD_MARK_CROSS,
} board_mark;

typedef struct board_cell {
  i4 x;
  i4 y;
  board_mark mark;
} board_cell;

typedef struct board {
  sz capacity;
  sz size;
  board_cell* data;
} board;

board
board_new();

void
board_delete(board*);

// It's like insert, but sorted
void
board_insort(board*, i4 x, i4 y, board_mark mark);

board_mark*
board_get(board* self, i4 x, i4 y);
