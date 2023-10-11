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
exit_upon_dial_up(void*, char* _, char* __, u2 ___) {
  endwin();
  printf("Dial up hook called!\n");
  exit(0);
}

i4
main(int argc, char* argv[]) {
  struct sockaddr_in server;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if (sockfd == -1) {
    printf("Could not create socket");
  }
  puts("Socket created");

  server.sin_addr.s_addr = inet_addr(argv[1]);
  server.sin_family = AF_INET;
  server.sin_port = htons(PORT);

  if (connect(sockfd, (struct sockaddr*)&server, sizeof(server)) < 0) {
    perror("connect failed. Error");
    return 1;
  }
  puts("Socket connected");

  /*
  int buf;
  if (recv(sockfd, &buf, 4, 0) < 0) {
    puts("recv failed");
    return 1;
  }

  printf("%i\n", buf);

  u1 *buf2 = malloc(5);
  recv(sockfd, buf2, 5, 0);

  printf("%i %i\n", *(u1*)buf2, *(u4*)(buf2+1));
  */

  recv_packet(sockfd);
  tui tui = tui_new();
  tui.hooks.try_dial_up_hook = exit_upon_dial_up;

  bool refresh_required = false;
  while (tui_display(&tui, &refresh_required) == 0)
    if (refresh_required)
      refresh();

  return 0;
}
