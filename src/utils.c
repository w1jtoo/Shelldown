//
// Created by w1jtoo on 17.01.2020.
//

#include "utils.h"
#include "command_executer.h"

void insert_to_array(char *array, unsigned short position, char ch, unsigned int buffer_size) {
    int index       = buffer_size;

    for (; index > position; index--) {
        array[index] = array[index - 1];
    }
    array[position] = ch;
}

void delete_symbol(char *array, unsigned short position, unsigned int buffer_size) {
    int index = position;

    for (; index < buffer_size; index++) {
        array[index] = array[index + 1];
    }
}

void make_warning_sound(void) {
#ifdef _WIN32
    MessageBeep(MB_ICONWARNING);
#endif
}