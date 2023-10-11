#pragma once

#include "common/types.h"

#define PACKET_skip_i4       cur += 4
#define PACKET_prepend_i4(i) *(i4*)buf = i
#define PACKET_append_i4(i)  *(i4*)cur = i; cur += sizeof(i4)
#define PACKET_append_u1(i)  *(u1*)cur = i; cur += sizeof(u1)
#define PACKET_append_str(str, str_len) memcpy((void*)cur, (void *)str, str_len); cur += str_len

#define PACKET_ARGS fd sockfd

#define NAME_LEN_MAX 16

#define PACKET_METADATA_LEN sizeof(u4) + sizeof(u1)

#define PACKET_begin(id) \
  u1 *cur = buf; \
  PACKET_skip_i4; \
  PACKET_append_u1(id)

#define PACKET_end \
  i4 packet_len = (sz)(cur - buf); \
  PACKET_prepend_i4(packet_len - sizeof(i4)); \
  send(sockfd, buf, packet_len, 0);
