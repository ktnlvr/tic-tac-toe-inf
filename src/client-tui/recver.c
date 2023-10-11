#include "common/protocol.h"
#include <sys/socket.h>
#include <stdio.h>

#include "src/client-tui/sender.h"

void packet_ping(u1 *buf);
void packet_begin(u1 *buf);
void packet_put(u1 *buf);
void packet_end(u1 *buf);

void (*packet_handler[])(u1 *buf) = {
  [PACKET_SERVER_ID_PING]  = packet_ping,
  [PACKET_SERVER_ID_BEGIN] = packet_begin,
  [PACKET_SERVER_ID_PUT]   = packet_put,
  [PACKET_SERVER_ID_END]   = packet_end,
};

#define PACKET_SERVER_MAX_LEN 19

void recv_packet(fd sockfd) {
  i4 len;
  
  u1 buf[PACKET_SERVER_MAX_LEN];
  
  recv(sockfd, &len, sizeof(len), 0);

  recv(sockfd, buf, len, 0);
  
  packet_handler[*(u1*)buf](buf + 1);
}

#define PACKET_get_i4 *(i4*)buf++
#define PACKET_get_u1 *(u1*)buf++

void
packet_ping
 (u1 *buf) {
  i4 n = PACKET_get_i4;
  printf("ping %i recved\n", n);
  send_packet_pong(n);
}

void
packet_begin
 (u1 *buf) {
  
}

void
packet_put
 (u1 *buf) {
  
}

void
packet_end
 (u1 *buf) {
  
}
