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
    buffers_head = NULL;
    buffer_tail  = (struct Node *) malloc(sizeof(struct Node));
    console_initialize();
}


void *read_line(void) {
    unsigned int buffer_size    = READ_LINE_BUFFER;
    unsigned int position       = 0;
    char         *buffer_values = malloc(sizeof(char) * buffer_size);
    unsigned int max_position   = 0;
    int          current_char;

    for (int i = 0; i < buffer_size; i++) { buffer_values[i] = '\0'; } // fill in the string

    struct Buffer *buffer = (struct Buffer *) malloc(sizeof(struct Buffer)); // initializing
    buffer->value           = buffer_values;
    buffer->max_position    = max_position;
    buffer->cursor_position = position;

    append(&buffers_head, buffer);
    constrict(buffers_head);

    struct Node *buffer_pointer = buffers_head; // initialize pointer to current command
    while (buffer_pointer->next != NULL) {
        buffer_pointer = buffer_pointer->next;
    }

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
                        if (buffer_pointer->next != NULL) {
                            buffer_pointer = buffer_pointer->next;
                            clear_part(buffer->max_position);
                            buffer = buffer_pointer->buffer;
//                            printf("%s", buffer_pointer->next->value);
                        } else {
                            make_warning_sound();
                        }
                        break;
                    case UP_ARROW:
                        if (buffer_pointer->prev != NULL) {
                            buffer_pointer = buffer_pointer->prev;
                            clear_part(buffer->max_position);
                            buffer = buffer_pointer->buffer;
                        } else {
                            make_warning_sound();
                        }
                        break;
                    case LEFT_ARROW:
                        if (buffer->cursor_position > 0)
                            buffer->cursor_position--;
                        else make_warning_sound();
                        break;
                    case RIGHT_ARROW:
                        if (buffer->cursor_position < buffer->max_position)
                            buffer->cursor_position++;
                        else make_warning_sound();
                        break;
                    default:
                        break;
                }
                break;
            case DC1: // CTRL + Q
                exit(EXIT_SUCCESS);
            case BACKSPACE:
                if (buffer->cursor_position > 0) {
//                    printf("\b \b");
//                    fflush(stdout);
                    buffer->cursor_position--;
                    delete_symbol(buffer->value, buffer->cursor_position, buffer->max_position);
                } else {
                    MessageBeep(MB_ICONWARNING); // TODO make cross platform function
                }
                break;
            case CARRIAGE_RETURN:
//            _putch( '\r' );    // Carriage return
                _putch('\n');    // Line feed
                return buffer->value;
            case HORIZONTAL_TAB:
//                printf("\nhint here\n");
                print_list(buffers_head);
                break;
            default:
                if (!isprint(current_char)) break;

                insert_to_array(buffer->value, buffer->cursor_position, (char) current_char, buffer->max_position);
                buffer->max_position++;
                buffer->cursor_position++;
                break;
        }

        if (buffer->cursor_position > buffer->max_position)
            buffer->max_position = (int) buffer->cursor_position;
        update(buffer->value, buffer->cursor_position, buffer->max_position);

        if (buffer->max_position + 1 > buffer->buffer_size) {
            unsigned int old_size = buffer->buffer_size;
            buffer->buffer_size += READ_LINE_BUFFER;
            buffer->value         = realloc(buffer->value, buffer_size);
            for (; old_size < buffer_size; old_size++) { buffer->value[old_size] = '\0'; }
            if (!buffer->value) {
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