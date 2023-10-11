#include "common/protocol.h"
#include <sys/socket.h>
#include <stdio.h>

void recv_packet_pong(u1 *buf);
void recv_packet_new(u1 *buf);
void recv_packet_put(u1 *buf);

void (*packet_handler[])(u1 *buf) = {
  [PACKET_CLIENT_ID_PONG] = recv_packet_pong,
  [PACKET_CLIENT_ID_NEW]  = recv_packet_new,
  [PACKET_CLIENT_ID_PUT]  = recv_packet_put,
};

#define PACKET_CLIENT_MAX_LEN 19

void recv_packet(fd sockfd) {
  i4 len;
  
  u1 buf[PACKET_CLIENT_MAX_LEN];
  
  recv(sockfd, &len, sizeof(len), 0);

  recv(sockfd, buf, len, 0);
  
  packet_handler[*(u1*)buf](buf + 1);
}

#define PACKET_begin
#define PACKET_get_i4 *(i4*)buf++
#define PACKET_get_u1 *(u1*)buf++

void
recv_packet_pong
 (u1 *buf) {
  printf("pong %i recved\n", PACKET_get_i4);
}

void
recv_packet_new
 (u1 *buf) {
  
}

void
recv_packet_put
 (u1 *buf) {
  
}
