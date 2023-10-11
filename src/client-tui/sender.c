#include "common/sender.h"
#include "src/client-tui/sender.h"
#include "common/protocol.h"
#include "common/types.h"
#include <sys/socket.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

fd sockfd;

void
send_packet_pong
 (i4 number)
{
  u1 buf
   [PACKET_METADATA_LEN +
    sizeof(i4)];

  PACKET_begin(PACKET_CLIENT_ID_PONG);
  PACKET_append_i4(number);
  PACKET_end;
}

void
send_packet_begin
 (PACKET_ARGS,
  u1 *name,
  i4  name_len)
{
  u1 buf
   [PACKET_METADATA_LEN + 
    sizeof(i4) +
    NAME_LEN_MAX];

  PACKET_begin(PACKET_CLIENT_ID_NEW);
  PACKET_append_i4(name_len);
  PACKET_append_str(name, name_len);
  PACKET_end;
}

void
send_packet_put
 (PACKET_ARGS,
  i4 x,
  i4 y)
{
  u1 buf
   [PACKET_METADATA_LEN +
    sizeof(i4) + 2];

  PACKET_begin(PACKET_CLIENT_ID_PUT);
  PACKET_append_i4(x);
  PACKET_append_i4(y);
  PACKET_end;
}
