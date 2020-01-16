//
// Created by w1jtoo on 16.01.2020.
//

#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <stdio.h>
#include "command_executer.h"
#include <string.h>
#include <ctype.h>

void *read_line(void) {
    int buffer_size = READ_LINE_BUFFER;
    unsigned int position = 0;
    char *buffer = malloc(sizeof(char) * buffer_size);
    char current_char;

    if (!buffer_size) {
        printf("can't allocate memory. ");
        exit(EXIT_FAILURE);
    }

    while (true) {
        char current_char = getch();
        if (current_char == EEXIST) { exit(EXIT_SUCCESS); }  // CTRL + Q
        if (current_char == '\b') {
            if (position > 0) {
                printf("\b \b");
                fflush(stdout);
                buffer[position - 1] = (char) 0;
                position --;
            }
            continue;
        }

//        TODO: if (current_char == '\t') { printf("hint here"); }

        if (current_char == '\r') {
            buffer[position] = SPECIAL_SYMBOL;
//            _putch( '\r' );    // Carriage return
            _putch('\n');    // Line feed
            return buffer;
        } else { buffer[position] = current_char; }
        position++;

        if (position > buffer_size) {
            buffer_size += READ_LINE_BUFFER;
            buffer = realloc(buffer, buffer_size);
            if (!buffer) {
                fprintf(stderr, "allocation error\n"); // TODO ADD to logger
                exit(EXIT_FAILURE);
            }
        }
        _putch(current_char);
    }
}

char **split_line(char *line) {
    int buffer_size = TOKEN_BUFFER_SIZE;
    int position = 0;
    char **tokens = malloc(sizeof(char *) * buffer_size);
    char *token;

    if (!tokens) {
        fprintf(stderr, "Allocation error");
        exit(EXIT_FAILURE);
    }
    token = strtok(line, TOKEN_DELIM);
    while (token != NULL) {
        tokens[position] = token;
        position++;
        if (position >= buffer_size) {
            buffer_size += TOKEN_BUFFER_SIZE;
            tokens = realloc(tokens, buffer_size * sizeof(char *));

            if (!tokens) {
                fprintf(stderr, "Allocation error");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, TOKEN_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}