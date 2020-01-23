//
// Created by w1jtoo on 18.01.2020.
//

#include <corecrt_wstdio.h>
#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

COORD               line_start = {0, 0};
HANDLE              console_handle;
CONSOLE_CURSOR_INFO console_info;

void update_line_start(void) {
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(console_handle, &info);
    line_start.X = info.dwCursorPosition.X;
    line_start.Y = info.dwCursorPosition.Y;
}

void console_initialize(void) {
    console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(console_handle, &console_info);
}

void clear_part(unsigned int max_length) {
    CONSOLE_SCREEN_BUFFER_INFO current_position;
    int                        index = 0;
    GetConsoleScreenBufferInfo(console_handle, &current_position);
    COORD position = current_position.dwCursorPosition;

    console_info.bVisible = false;                        // hide cursor
    SetConsoleCursorInfo(console_handle, &console_info);  // hide cursor
    SetConsoleCursorPosition(console_handle, line_start);

    for (; index < max_length; index++) {
        putchar(' ');
    }

    console_info.bVisible = true;
    SetConsoleCursorInfo(console_handle, &console_info);
    SetConsoleCursorPosition(console_handle, position);
}


void update(char *buffer, unsigned int cursor_position, unsigned int max_length) {
    int   index    = 0;
    COORD position = {line_start.X + cursor_position, line_start.Y};

    console_info.bVisible = false;                        // hide cursor
    SetConsoleCursorInfo(console_handle, &console_info);  // hide cursor
    SetConsoleCursorPosition(console_handle, line_start);

    for (; index < max_length; index++) {
        putchar(buffer[index]);
    }

    console_info.bVisible = true;
    SetConsoleCursorInfo(console_handle, &console_info);
    SetConsoleCursorPosition(console_handle, position);
}
