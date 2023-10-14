#include "./client-tui/tui.h"

#include <ncurses.h>
#include <string.h>

tui_screen_state
tui_init() {
  tui_screen_state ret;
  ret.ncurses_window = initscr();
  curs_set(0);
  keypad(ret.ncurses_window, TRUE);
  noecho();
  return ret;
}

bool
ipv4_addr_filter(int input_key) {
  return ('0' <= input_key && input_key <= '9') || input_key == '.';
}

bool
port_filter(int input_key) {
  return ('0' <= input_key && input_key <= '9');
}

bool
no_space_filter(int input_key) {
  return (input_key != ' ');
}

void
tui_show_connect_screen(tui_screen_state* tui,
                        char* name,
                        char* host_ipv4,
                        char* port) {

  static const int field_count = 3;
  static const char* names[3] = { "Nickname", "IPv4", "Port" };
  static const sz buffer_lengths[3] = { NAME_STRING_MAX_LEN,
                                        IPV4_STRING_MAX_LEN,
                                        PORT_STRING_MAX_LEN };
  char* buffers[] = { name, host_ipv4, port };

  bool (*filters[3])(int) = { no_space_filter, ipv4_addr_filter, port_filter };

  sz active_idx = 0;

  i4 key = ERR;
  for (;;) {
    erase();
    box(tui->ncurses_window, 0, 0);
    mvwprintw(tui->ncurses_window, 0, 2, "TicTacToeInf: Connect");

    for (sz i = 0; i < field_count; i++) {
      if (i == active_idx)
        wattron(tui->ncurses_window, A_STANDOUT);
      mvwprintw(tui->ncurses_window, 2 + i, 3, names[i]);
      if (i == active_idx)
        wattroff(tui->ncurses_window, A_STANDOUT);
      wprintw(tui->ncurses_window, ": ");
      wprintw(tui->ncurses_window, buffers[i]);
    }

    if (active_idx == 3)
      wattron(tui->ncurses_window, A_STANDOUT);
    mvwprintw(tui->ncurses_window, 6, 3, " Connect! ");
    if (active_idx == 3)
      wattroff(tui->ncurses_window, A_STANDOUT);

    refresh();

    key = wgetch(tui->ncurses_window);
    switch (key) {
      case '\n':
      case '\r':
      case KEY_ENTER:
        if (active_idx == 3)
          return;
      case KEY_DOWN:
        active_idx = (active_idx + 1) % (field_count + 1);
        break;
      case KEY_UP:
        active_idx = (active_idx + 3) % (field_count + 1);
        break;
      case ERR:
        break;
      default:
        for (sz i = 0; i < field_count; i++) {
          if (active_idx == i) {
            sz len = strlen(buffers[i]);
            char key_ascii = key & 0x7F;
            if (key == KEY_BACKSPACE && len > 0) {
              buffers[i][len - 1] = '\0';
            } else if (0x20 < key_ascii && key_ascii < 0x7B &&
                       len + 1 < buffer_lengths[i] && filters[i](key_ascii)) {
              buffers[i][len] = key_ascii;
            }
          }
        }
    }
  }
}
