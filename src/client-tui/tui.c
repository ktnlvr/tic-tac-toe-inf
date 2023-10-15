#include "./client-tui/tui.h"

#include <ncurses.h>
#include <string.h>

void
tui_init() {
  initscr();
  curs_set(0);
  keypad(stdscr, TRUE);
  noecho();
}

bool
ipv4_addr_filter(i4 input_key) {
  return ('0' <= input_key && input_key <= '9') || input_key == '.';
}

bool
port_filter(i4 input_key) {
  return ('0' <= input_key && input_key <= '9');
}

bool
no_space_filter(i4 input_key) {
  return (input_key != ' ');
}

void
tui_show_connect_screen(char* name, char* host_ipv4, char* port) {

  static const i4 field_count = 3;
  static const char* names[3] = { "Nickname", "IPv4", "Port" };
  static const sz buffer_lengths[3] = { NAME_STRING_MAX_LEN,
                                        IPV4_STRING_MAX_LEN,
                                        PORT_STRING_MAX_LEN };
  char* buffers[] = { name, host_ipv4, port };

  bool (*filters[3])(i4) = { no_space_filter, ipv4_addr_filter, port_filter };

  sz active_idx = 0;

  i4 key = ERR;
  for (;;) {
    erase();
    box(stdscr, 0, 0);
    mvwprintw(stdscr, 0, 2, "TicTacToeInf: Connect");

    for (sz i = 0; i < field_count; i++) {
      if (i == active_idx)
        wattron(stdscr, A_STANDOUT);
      mvwprintw(stdscr, 2 + i, 3, names[i]);
      if (i == active_idx)
        wattroff(stdscr, A_STANDOUT);
      wprintw(stdscr, ": ");
      wprintw(stdscr, buffers[i]);
    }

    if (active_idx == 3)
      wattron(stdscr, A_STANDOUT);
    mvwprintw(stdscr, 6, 3, " Connect! ");
    if (active_idx == 3)
      wattroff(stdscr, A_STANDOUT);

    refresh();

    key = wgetch(stdscr);
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
            ch key_ascii = key & 0x7F;
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

tui_game_state
tui_game_new() {
  tui_game_state ret;
  ret.camera_x = 0;
  ret.camera_y = 0;
  ret.board = board_new();
  return ret;
}

void
tui_game_delete(tui_game_state* state) {
  board_delete(&state->board);
}

void
tui_game_screen_display(tui_game_state* state) {
  erase();
  i4 min_x = 1, min_y = 1, max_x, max_y;
  // this is a macro, so it doesn't accept pointers
  getmaxyx(stdscr, max_y, max_x);

  // account for box boundaries
  max_x -= 1;
  max_y -= 1;

  i4 center_x = (max_x - min_x) / 2;
  i4 center_y = (max_y - min_y) / 2;

  for (sz i = 0; i < state->board.size; i++) {
    board_cell cell = state->board.data[i];
    mvaddch(cell.y + state->camera_y + min_y + center_y,
            cell.x - state->camera_x + min_x + center_x,
            cell.mark == BOARD_MARK_CROSS ? 'X' : 'O');
  }

  board_mark* hovered_cell =
    board_get(&state->board, state->camera_x, -state->camera_y);
  attron(A_STANDOUT);
  mvaddch(center_y + 1,
          center_x + 1,
          hovered_cell == NULL                ? '_'
          : *hovered_cell == BOARD_MARK_CROSS ? 'X'
          : *hovered_cell == BOARD_MARK_KNOT  ? 'O'
                                              : '?');
  attroff(A_STANDOUT);

  box(stdscr, 0, 0);
  mvwprintw(stdscr, 0, 2, " TicTacToeInf: You vs %s ", state->opponent_name);
}

void
tui_game_screen_handle_input(tui_game_state* state, i4 key) {
  switch (key) {
    case KEY_RIGHT:
      state->camera_x += 1;
      break;
    case KEY_LEFT:
      state->camera_x -= 1;
      break;
    case KEY_UP:
      state->camera_y += 1;
      break;
    case KEY_DOWN:
      state->camera_y -= 1;
      break;
  }
}
