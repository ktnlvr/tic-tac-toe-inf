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

i4
exit_upon_dial_up(void*, char* _, char* __, u2 ___) {
  endwin();
  printf("Dial up hook called!\n");
  exit(0);
}

i4
main(int argc, char* argv[]) {
  tui tui = tui_new();
  tui.hooks.try_dial_up_hook = exit_upon_dial_up;

  bool refresh_required = false;
  while (tui_display(&tui, &refresh_required) == 0)
    if (refresh_required)
      refresh();

  return 0;
}
