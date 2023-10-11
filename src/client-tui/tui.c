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
  wprintw(w, "%s%s", field->prompt, ": ");
  if (active)
    attroff(A_BOLD);

  wprintw(w, "%s\n", field->buf);
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

#define NAME_FIELD_IDX 0
#define IPV4_FIELD_IDX 1
#define PORT_FIELD_IDX 2

bool
tui_select_next(int key) {
  return key == KEY_DOWN || key == KEY_CTAB || key == KEY_ENTER ||
         key == '\n' || key == '\r';
}

bool
tui_select_prev(int key) {
  return key == KEY_UP || key == KEY_BTAB;
}

i4
tui_display(tui* tui) {
  u1* const active_ui_element_idx = &tui->active_ui_element;
  erase();

  switch (tui->ui_mode) {
    case UI_MODE_UNINITIALIZED: {
      // Set up ncurses data
      tui->ncurses_window = initscr();
      memset((void*)&tui->data, 0x00, sizeof tui->data.dial_in);

      tui->ui_mode = UI_MODE_DIAL_IN;
      tui_text_input_field* const fields = tui->data.dial_in.fields;

      fields[NAME_FIELD_IDX].prompt = "Name";
      fields[NAME_FIELD_IDX].buf = tui->data.dial_in.name_buf;
      fields[NAME_FIELD_IDX].buflen = NAME_STRING_MAX_LEN;
      fields[NAME_FIELD_IDX].filter = no_space_filter;

      fields[IPV4_FIELD_IDX].prompt = "IPv4";
      fields[IPV4_FIELD_IDX].buf = tui->data.dial_in.ipv4_buf;
      fields[IPV4_FIELD_IDX].buflen = IPV4_STRING_MAX_LEN;
      fields[IPV4_FIELD_IDX].filter = ipv4_addr_filter;

      fields[PORT_FIELD_IDX].prompt = "Port";
      fields[PORT_FIELD_IDX].buf = tui->data.dial_in.port_buf;
      fields[PORT_FIELD_IDX].buflen = PORT_STRING_MAX_LEN;
      fields[PORT_FIELD_IDX].filter = port_filter;

      curs_set(0);
      keypad(tui->ncurses_window, TRUE);
    }
    case UI_MODE_DIAL_IN: {
      tui_text_input_field* fields = tui->data.dial_in.fields;

      // TODO: make this use box(...)
      wprintw(tui->ncurses_window, "+---------------------------+\n");
      wprintw(tui->ncurses_window, "| xoxo Tic-Tac-Toe-Inf oxox |\n");
      wprintw(tui->ncurses_window, "+---------------------------+\n\n");

      sz field_count = sizeof tui->data.dial_in.fields / sizeof fields[0];

      for (sz i = 0; i < field_count; i++) {
        tui_text_input_field* field = fields + i;
        tui_text_input_field_draw(field, tui, *active_ui_element_idx == i);
      }

      i4 key = getch();

      if ((key == KEY_ENTER || key == '\n' || key == '\r') &&
          *active_ui_element_idx == field_count - 1 &&
          tui->hooks.try_dial_up_hook) {
        tui->hooks.try_dial_up_hook(tui->hooks.try_dial_up_payload,
                                    fields[0].buf,
                                    fields[1].buf,
                                    (u2)(atoi(fields[2].buf)));
      }

      if (tui_select_next(key))
        *active_ui_element_idx = (*active_ui_element_idx + 1) % field_count;
      if (tui_select_prev(key))
        *active_ui_element_idx =
          (*active_ui_element_idx + field_count - 1) % field_count;

      for (sz i = 0; i < field_count; i++) {
        tui_text_input_field* field = fields + i;
        if (*active_ui_element_idx == i)
          tui_text_input_field_handle_input(field, key);
      }

      break;
    }
    default:
      endwin();
      exit(-42069);
      break;
  }

  return 0;
}
