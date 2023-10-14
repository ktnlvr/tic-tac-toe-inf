#pragma once

#include <ncurses.h>

#include "./common/types.h"

#define PORT_STRING_MAX_LEN (5 + 1)  // len = strlen("65535") + 1
#define IPV4_STRING_MAX_LEN (15 + 1) // len = strlen("127.127.127.127") + 1
#define NAME_STRING_MAX_LEN (32 + 1)

void
tui_init();

void
tui_show_connect_screen(char* name, char* host_ipv4, char* port);
