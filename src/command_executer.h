//
// Created by w1jtoo on 16.01.2020.
//

#ifndef SHELLDOWN_COMMAND_EXECUTER_H
#define SHELLDOWN_COMMAND_EXECUTER_H

#include "utils.h"

#define DC1 17

#define LEFT_ARROW 75
#define UP_ARROW 72
#define RIGHT_ARROW 77
#define DOWN_ARROW 80

#define BACKSPACE 8
#define CARRIAGE_RETURN 13
#define VERTICAL_TAB 11
#define HORIZONTAL_TAB 9


#define TOKEN_BUFFER_SIZE 64

#define TOKEN_DELIM " \t\r\n\a"

#define READ_LINE_BUFFER 1 << 5
#define SPECIAL_SYMBOL '\0'
//#define ETX 3

struct Node *buffers_head;

void initialize(void);

void *read_line(void);

char **split_line(char *line);

struct Node *buffer_tail;

#endif //SHELLDOWN_COMMAND_EXECUTER_H
