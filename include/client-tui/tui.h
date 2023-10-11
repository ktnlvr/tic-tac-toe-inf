#pragma once

#include <ncurses.h>

#include "./common/types.h"

#define PORT_STRING_MAX_LEN (5 + 1)  // len = strlen("65535") + 1
#define IPV4_STRING_MAX_LEN (15 + 1) // len = strlen("127.127.127.127") + 1
#define NAME_STRING_MAX_LEN (32 + 1)

typedef enum {
  /// Default-initialized marker
  UI_MODE_UNINITIALIZED = 0,
  /// Dial in the port & ip
  UI_MODE_DIAL_IN,
  /// Currently connecting to a host
  UI_MODE_CONNECTING,
} tui_screen_id;

typedef struct tui_text_input_field {
  const char* prompt;
  char* buf;
  sz buflen;
  bool (*filter)(int);
} tui_text_input_field;

typedef struct tui_hooks {
  void* try_dial_up_payload;
  i4 (*try_dial_up_hook)(void* payload,
                         char name[NAME_STRING_MAX_LEN],
                         char host_ipv4[IPV4_STRING_MAX_LEN],
                         u2 port);
} tui_hooks;

typedef struct tui {
  tui_screen_id ui_mode;
  tui_hooks hooks;

  WINDOW* ncurses_window;

  u1 active_ui_element;

  union {
    struct {
      ch name_buf[NAME_STRING_MAX_LEN];
      ch ipv4_buf[IPV4_STRING_MAX_LEN];
      ch port_buf[PORT_STRING_MAX_LEN];
      tui_text_input_field fields[3];
    } dial_in;
  } data;
} tui;

tui
tui_new();

i4
tui_display(tui* tui);

void
tui_text_input_field_draw(tui_text_input_field* field, tui* tui, bool active);

void
tui_text_input_field_handle_input(tui_text_input_field* field, int input_char);
