#include "./common/protocol.h"

void
packet_delete(packet* pkg) {
  if (pkg != NULL)
    free((void*)pkg->payload);
}
