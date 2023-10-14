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
  char name[NAME_LEN_MAX] = "", host[IPV4_STRING_MAX_LEN] = "",
       port[PORT_STRING_MAX_LEN] = "";

  if (argc >= 2)
    strlcpy(host, argv[1], IPV4_STRING_MAX_LEN);
  if (argc >= 3)
    strlcpy(port, argv[2], PORT_STRING_MAX_LEN);

  tui_init();
  tui_show_connect_screen(name, host, port);

  printf("%s is connecting to %s:%s!\n", name, host, port);
  endwin();

  return 0;
}
