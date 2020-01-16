//
// Created by w1jtoo on 16.01.2020.
//

#ifndef SHELLDOWN_COMMAND_EXECUTER_H
#define SHELLDOWN_COMMAND_EXECUTER_H

#define TOKEN_BUFFER_SIZE 64

#define TOKEN_DELIM " \t\r\n\a"

#define READ_LINE_BUFFER 1 << 10
#define SPECIAL_SYMBOL '\0'
//#define ETX 3

void *read_line(void);

char **split_line(char *line);

#endif //SHELLDOWN_COMMAND_EXECUTER_H
