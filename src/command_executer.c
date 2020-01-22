//
// Created by w1jtoo on 16.01.2020.
//

#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "command_executer.h"
#include "utils.h"
#include "tui_controller.h"

void initialize(void) {
    console_initialize();
}


void *read_line(void) {
    int          buffer_size  = READ_LINE_BUFFER;
    unsigned int position     = 0;
    char         *buffer      = malloc(sizeof(char) * buffer_size);
    int          max_position = 0;

    for (int i = 0; i < buffer_size; i++) { buffer[i] = '\0'; }

    int current_char;

    if (!buffer_size) {
        printf("can't allocate memory. ");
        exit(EXIT_FAILURE);
    }
    update_line_start();
    while (true) {
        current_char = _getch();

        switch (current_char) {
            case 0: // NUMPAD
            case 224: // DEFAULT
                switch (_getch()) {
                    case DOWN_ARROW:
                    case UP_ARROW:
                        break;
                    case LEFT_ARROW:
                        if (position > 0) position--;
                        else make_warning_sound();
                        break;
                    case RIGHT_ARROW:
                        if (position < max_position) position++;
                        else make_warning_sound();
                        break;
                    default:
                        break;
                }
                break;
            case DC1: // CTRL + Q
                exit(EXIT_SUCCESS);
            case BACKSPACE:
                if (position > 0) {
//                    printf("\b \b");
//                    fflush(stdout);
                    position--;
                    delete_symbol(buffer, position, max_position);
                } else {
                    MessageBeep(MB_ICONWARNING); // TODO make cross platform function
                }
                break;
            case CARRIAGE_RETURN:
//            _putch( '\r' );    // Carriage return
                _putch('\n');    // Line feed
                return buffer;
            case HORIZONTAL_TAB:
                printf("\nhint here\n");
                break;
            default:
                if (!isprint(current_char)) break;

                insert_to_array(buffer, position, (char) current_char, max_position);
                max_position++;
                position++;
                break;
        }


        if (position > max_position) max_position = (int) position;
        update(buffer, position, max_position);

        if (max_position + 1 > buffer_size) {
            int old_size = buffer_size;
            buffer_size += READ_LINE_BUFFER;
            buffer       = realloc(buffer, buffer_size);
            for (; old_size < buffer_size; old_size++) { buffer[old_size] = '\0'; }
            if (!buffer) {
                fprintf(stderr, "allocation error\n"); // TODO ADD to logger
                exit(EXIT_FAILURE);
            }
        }
    }
}

char **split_line(char *line) {
    char *line_copy = malloc(sizeof(line));
    strcpy(line_copy, line); // need not to mutate line, so copy it

    int  buffer_size = TOKEN_BUFFER_SIZE;
    int  position    = 0;
    char **tokens    = malloc(sizeof(char *) * buffer_size);
    char *token;

    if (!tokens) {
        fprintf(stderr, "Allocation error");
        exit(EXIT_FAILURE);
    }
    token = strtok(line_copy, TOKEN_DELIM);
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