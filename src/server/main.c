#define _POSIX_C_SOURCE 202310
#include <common/types.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <threads.h>
#include <stdio.h>

#include "src/server/sender.h"
#include "src/server/recver.h"

#define loop while (1)

#define PORT "42069"

int
main
 ()
{
  struct sockaddr_storage their_addr;
  socklen_t addr_size;
  struct addrinfo hints, *res;
  fd sockfd, new_fd;

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  (void)getaddrinfo(NULL, PORT, &hints, &res);

  sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  (void)bind(sockfd, res->ai_addr, res->ai_addrlen);
  listen(sockfd, 20);

  addr_size = sizeof their_addr;

  // wait for connections
  new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);

  send_packet_ping(new_fd, 239);

  recv_packet(new_fd);
}
