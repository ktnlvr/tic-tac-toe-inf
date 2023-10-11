#pragma once

#include "types.h"

#define PORT 42069

enum packet_id_server {
  PACKET_SERVER_ID_PING  = 0x0,
  PACKET_SERVER_ID_BEGIN = 0x1,
  PACKET_SERVER_ID_PUT   = 0x2,
  PACKET_SERVER_ID_END   = 0x3,
};

enum packet_id_client {
  PACKET_CLIENT_ID_PONG  = 0x0,
  PACKET_CLIENT_ID_NEW   = 0x1,
  PACKET_CLIENT_ID_PUT   = 0x2,
};
