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

struct Buffer {
    char         *value;
    unsigned int max_position;
    unsigned int cursor_position;
    unsigned int buffer_size;
};

struct Node {
    struct Buffer *buffer;
    struct Node   *next;
    struct Node   *prev;
};

void print_list(struct Node *node);

void constrict(struct Node *node);

void append(struct Node **head_ref, struct Buffer *buffer_ref);

void push(struct Node **head_ref, struct Buffer *buffer_ref);

#endif //SHELLDOWN_UTILS_H
