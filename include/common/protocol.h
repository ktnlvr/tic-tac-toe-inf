#include "types.h"

#pragma once

#define PORT 42069

typedef enum client2server_packet_id {
  C2S_PONG,
} client2server_packet_id;

typedef enum server2client_packet_id {
  S2V_PING,
} server2client_packet_id;

typedef struct packet {
  u1 packet_id;

  size_t payload_size;
  u1* payload;
} packet;

void
packet_delete(packet* pkg);
