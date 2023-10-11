#include "./common/board.h"

#include <memory.h>

#define GROW_BOARD_CAPACITY(c) ((c + 1) * 3)

board_mark*
board_get(board* self, i4 x, i4 y) {
  for (sz i = 0; i < self->size; i++)
    if (self->data[i].x == x && self->data[i].y == y)
      return &self->data[i].mark;
  return NULL;
}

void
board_insort(board* self, i4 x, i4 y, board_mark mark) {
  // TODO: actual sorted insert
  if (self->capacity < self->size + 1) {
    sz new_capacity = GROW_BOARD_CAPACITY(self->capacity);
    board_cell* data =
      self->capacity ? realloc(self->data, new_capacity * sizeof self->data[0])
                     : malloc(new_capacity * sizeof self->data[0]);
    self->data = data;
    self->capacity = new_capacity;
  }

  board_mark* mark_ptr = board_get(self, x, y);
  if (mark_ptr != NULL) {
    *mark_ptr = mark;
  } else {
    self->data[self->size].x = x;
    self->data[self->size].y = y;
    self->data[self->size++].mark = mark;
  }
}
