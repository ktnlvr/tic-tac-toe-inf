#include "./common/board.h"

#define GROW_BOARD_CAPACITY(c) ((c + 1) * 3)

bool
a_lt_cmp_b(i4 a_x, i4 a_y, i4 b_x, i4 b_y) {
  if (a_x < b_x)
    if (a_y < b_y)
      return true;
  return false;
}

sz
board_get_impl(board_cell* data, sz len, i4 x, i4 y) {
  if (len == 0)
    return len;

  sz l = 0;
  sz r = len - 1;
  while (l <= r) {
    sz m = (l + r) / 2;
    board_cell c = data[m];
    if (a_lt_cmp_b(c.x, c.y, x, y))
      l = m + 1;
    else if (a_lt_cmp_b(x, y, c.x, c.y))
      r = m - 1;
    else
      return m;
  }

  return len;
}

board_mark*
board_get(board* self, i4 x, i4 y) {
  sz idx = board_get_impl(self->data, self->size, x, y);
  return idx == self->size ? NULL : &self->data[idx].mark;
}

void
board_insort_impl(board_cell* data, sz len, i4 x, i4 y, board_mark mark) {
  if (len != 0) {
    sz l = 0;
    sz r = len - 1;
    while (l <= r) {
      sz m = (l + r) / 2;
      board_cell c = data[m];
      if (a_lt_cmp_b(c.x, c.y, x, y))
        l = m + 1;
      else if (a_lt_cmp_b(x, y, c.x, c.y))
        r = m - 1;
      else {
        // TODO: maybe deny overwrite?
        data[m].mark = mark;
        return;
      }
    }
    data[(l + r) / 2].x = x;
    data[(l + r) / 2].y = y;
    data[(l + r) / 2].mark = mark;
  } else {
    data[0].x = x;
    data[0].y = y;
    data[0].mark = mark;
  }
}

void
board_insort(board* self, i4 x, i4 y, board_mark mark) {
  if (self->capacity < self->size + 1) {
    sz new_capacity = GROW_BOARD_CAPACITY(self->capacity);
    board_cell* data =
      self->capacity ? realloc(self->data, new_capacity * sizeof self->data[0])
                     : malloc(new_capacity * sizeof self->data[0]);
    self->data = data;
    self->capacity = new_capacity;
  }

  board_insort_impl(self->data, self->size, x, y, mark);
  self->size++;
}
