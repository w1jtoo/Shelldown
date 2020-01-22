//
// Created by w1jtoo on 17.01.2020.
//

#ifndef SHELLDOWN_UTILS_H
#define SHELLDOWN_UTILS_H

#ifdef _WIN32

#include <direct.h>

#define get_current_directory _getcwd

#include <windows.h>

#endif

#ifdef linux
#include <unistd.h>
#define get_current_directory getcwd
#endif

void insert_to_array(char *array, unsigned short position, char ch, unsigned int buffer_size);

void delete_symbol(char *array, unsigned short position, unsigned int buffer_size);

void make_warning_sound(void);

#endif //SHELLDOWN_UTILS_H
