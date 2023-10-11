#include "./common/board.h"
#include "./common/types.h"

#include <assert.h>

i4
main() {
  assert(true);

  board b = board_new();
  assert(board_get(&b, 0, 0) == NULL);

  board_insort(&b, 0, 0, BOARD_MARK_CROSS);
  assert(*board_get(&b, 0, 0) == BOARD_MARK_CROSS);

  board_insort(&b, 0, 0, BOARD_MARK_CROSS);
  board_insort(&b, 0, 2, BOARD_MARK_CROSS);
  board_insort(&b, 4, 0, BOARD_MARK_CROSS);
  board_insort(&b, 1, 1, BOARD_MARK_CROSS);
  board_insort(&b, 7, 8, BOARD_MARK_CROSS);
  board_insort(&b, 2, 9, BOARD_MARK_CROSS);
}
