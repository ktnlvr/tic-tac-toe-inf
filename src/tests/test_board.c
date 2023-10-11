#include "./common/board.h"
#include "./common/types.h"

#include <stdio.h>
#include <assert.h>

i4
main() {
  assert(true);

  board b = board_new();
  assert(board_get(&b, 0, 0) == NULL);

  board_insort(&b, 0, 0, BOARD_MARK_KNOT);
  assert(*board_get(&b, 0, 0) == BOARD_MARK_KNOT);

  board_insort(&b, 0, 0, (board_mark)0xF1);
  board_insort(&b, 0, 2, (board_mark)0xF2);
  board_insort(&b, 4, 0, (board_mark)0xF3);
  board_insort(&b, 1, 1, (board_mark)0xF4);
  board_insort(&b, 7, 8, (board_mark)0xF5);
  board_insort(&b, 2, 9, (board_mark)0xF6);

  assert(b.size == 6);
  for (sz i = 0; i < 6; i++)
    assert(b.data[i].mark == 0xF1 + i);

  return 0;
}
