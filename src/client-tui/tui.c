#include "./client-tui/tui.h"

#include <ncurses.h>
#include <string.h>

tui
tui_new() {
  tui ret;
  memset(&ret, 0x00, sizeof ret);
  ret.ui_mode = UI_MODE_UNINITIALIZED;
  return ret;
}

void
tui_text_input_field_draw(tui_text_input_field* field, tui* tui, bool active) {
  WINDOW* w = tui->ncurses_window;

  if (active)
    attron(A_BOLD);

  wprintw(w, field->prompt);
  wprintw(w, ": ");

  if (active)
    attroff(A_BOLD);

  wprintw(w, field->buf);
  waddch(w, '\n');
}

void
tui_text_input_field_handle_input(tui_text_input_field* field, int input_key) {
  if (input_key == KEY_BACKSPACE) {
    memset(field->buf, '\0', field->buflen);
    return;
  }

  sz len = strlen(field->buf);
  if (len + 1 == field->buflen) {
    return;
  }

  if (field->filter)
    if (!field->filter(input_key))
      return;

  // Keypress to ASCII
  char c = input_key & 0x7F;
  if (c < 32 || c > 0x7E)
    return;

  if (len != field->buflen - 1)
    field->buf[len] = c;
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

i4
tui_display(tui* tui) {
  erase();

  u1* active_ui = &tui->active_ui_element;

  switch (tui->ui_mode) {
    case UI_MODE_UNINITIALIZED:
      // Set up ncurses data
      tui->ncurses_window = initscr();
      memset((void*)&tui->data, 0x00, sizeof tui->data.dial_in);

      tui->ui_mode = UI_MODE_DIAL_IN;
      tui_text_input_field* fields = tui->data.dial_in.fields;

      fields[0].prompt = "Name";
      fields[0].buf = tui->data.dial_in.name_buf;
      fields[0].buflen = NAME_STRING_MAX_LEN;
      fields[0].filter = no_space_filter;

      fields[1].prompt = "IPv4";
      fields[1].buf = tui->data.dial_in.ipv4_buf;
      fields[1].buflen = IPV4_STRING_MAX_LEN;
      fields[1].filter = ipv4_addr_filter;

      fields[2].prompt = "Port";
      fields[2].buf = tui->data.dial_in.port_buf;
      fields[2].buflen = PORT_STRING_MAX_LEN;
      fields[2].filter = port_filter;

      curs_set(0);
      keypad(tui->ncurses_window, TRUE);
    case UI_MODE_DIAL_IN:
      // TODO: make this use box(...)
      wprintw(tui->ncurses_window, "+---------------------------+\n");
      wprintw(tui->ncurses_window, "| xoxo Tic-Tac-Toe-Inf oxox |\n");
      wprintw(tui->ncurses_window, "+---------------------------+\n\n");

      sz field_count =
        sizeof tui->data.dial_in.fields / sizeof tui->data.dial_in.fields[0];

      for (sz i = 0; i < field_count; i++) {
        tui_text_input_field* field = tui->data.dial_in.fields + i;
        tui_text_input_field_draw(field, tui, *active_ui == i);
      }

      i4 key = getch();

      if (key == KEY_DOWN || key == KEY_CTAB || key == KEY_ENTER ||
          key == '\n' || key == '\r')
        *active_ui = (*active_ui + 1) % field_count;
      if (key == KEY_UP || key == KEY_BTAB)
        *active_ui = (*active_ui + field_count - 1) % field_count;

      for (sz i = 0; i < field_count; i++) {
        tui_text_input_field* field = tui->data.dial_in.fields + i;
        if (*active_ui == i)
          tui_text_input_field_handle_input(field, key);
      }

      break;
    default:
      endwin();
      exit(-42069);
      break;
  }

  return 0;
}
