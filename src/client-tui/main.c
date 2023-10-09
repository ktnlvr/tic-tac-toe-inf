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

#include "./common/protocol.h"
#include "./common/types.h"

i4
main(int argc, char* argv[]) {
  fd sockfd;
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

  int buf;
  if (recv(sockfd, &buf, 4, 0) < 0) {
    puts("recv failed");
    return 1;
  }

  printf("%X", buf);

  return 0;
}
