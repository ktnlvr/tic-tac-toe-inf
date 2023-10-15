#include <errno.h>
#include <ncurses.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <arpa/inet.h>

#include "./client-tui/tui.h"
#include "./common/protocol.h"
#include "./common/types.h"
#include "./src/client-tui/recver.h"
#include "./src/client-tui/sender.h"

i4
main(int argc, char* argv[]) {
  char name[NAME_STRING_MAX_LEN] = "", host[IPV4_STRING_MAX_LEN] = "",
       port[PORT_STRING_MAX_LEN] = "";

  if (argc >= 2)
    strlcpy(host, argv[1], IPV4_STRING_MAX_LEN);
  if (argc >= 3)
    strlcpy(port, argv[2], PORT_STRING_MAX_LEN);

  tui_init();
  tui_show_connect_screen(name, host, port);

  printf("%s is connecting to %s:%s!\n", name, host, port);
  endwin();

  tui_game_state game = tui_game_new();
  game.opponent_name = "CPU";

  board_insort(&game.board, 0, 0, BOARD_MARK_CROSS);
  board_insort(&game.board, 6, 4, BOARD_MARK_CROSS);
  board_insort(&game.board, -3, -3, BOARD_MARK_KNOT);

  for (;;) {
    tui_game_screen_display(&game);
    tui_game_screen_handle_input(&game, getch());
  }

  tui_game_delete(&game);

  return 0;
}
