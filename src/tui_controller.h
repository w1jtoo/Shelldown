//
// Created by w1jtoo on 18.01.2020.
//

#ifndef SHELLDOWN_TUI_CONTROLLER_H
#define SHELLDOWN_TUI_CONTROLLER_H

void update(char *buffer, unsigned int cursor_position, unsigned int max_length);

void clear_part(unsigned int max_length);

void update_line_start(void);

void console_initialize(void);


#endif //SHELLDOWN_TUI_CONTROLLER_H
