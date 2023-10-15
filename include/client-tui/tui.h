#pragma once

#include <ncurses.h>

#include "./common/board.h"
#include "./common/types.h"

#define PORT_STRING_MAX_LEN (5 + 1)  // len = strlen("65535") + 1
#define IPV4_STRING_MAX_LEN (15 + 1) // len = strlen("127.127.127.127") + 1
#define NAME_STRING_MAX_LEN (32 + 1)

void
tui_init();

void
tui_show_connect_screen(char* name, char* host_ipv4, char* port);

typedef struct tui_game_state {
  int camera_x, camera_y;
  board board;
  const char* opponent_name;
} tui_game_state;

tui_game_state
tui_game_new();

void
tui_game_delete(tui_game_state*);

void
tui_game_screen_display(tui_game_state*);

void
tui_game_screen_handle_input(tui_game_state*, i4 key);
