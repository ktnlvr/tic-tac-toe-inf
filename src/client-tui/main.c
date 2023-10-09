#include "./common/types.h"
#include <ncurses.h>
#include <stdio.h>

#include "./common/protocol.h"

i4
main() {
  packet p = { .packet_id = S2V_PING, .payload_size = 0, .payload = malloc(1) };
  packet_delete(&p);
  return 0;
}
