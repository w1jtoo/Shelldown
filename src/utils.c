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


void append(struct Node **head_ref, struct Buffer *buffer_ref) {
    /* 1. allocate node */
    struct Node *new_node = (struct Node *) malloc(sizeof(struct Node));

    struct Node *last = *head_ref; /* used in step 5*/

    /* 2. put in the data  */
    new_node->buffer = buffer_ref;

    /* 3. This new node is going to be the last node, so
          make next of it as NULL*/
    new_node->next = NULL;

    /* 4. If the Linked List is empty, then make the new
          node as head */
    if (*head_ref == NULL) {
        new_node->prev = NULL;
        *head_ref = new_node;
        return;
    }

    /* 5. Else traverse till the last node */
    while (last->next != NULL)
        last = last->next;

    /* 6. Change the next of last node */
    last->next = new_node;

    /* 7. Make last node as previous of new node */
    new_node->prev = last;

}

/* Given a reference (pointer to pointer) to the head of a list
   and an int, inserts a new node on the front of the list. */
void push(struct Node **head_ref, struct Buffer *buffer_ref) {
    /* 1. allocate node */


    struct Node *new_node = (struct Node *) malloc(sizeof(struct Node));

    /* 2. put in the data  */
    new_node->buffer = buffer_ref;

    /* 3. Make next of new node as head and previous as NULL */
    new_node->next = (*head_ref);
    new_node->prev = NULL;

    /* 4. change prev of head node to new node */
    if ((*head_ref) != NULL)
        (*head_ref)->prev = new_node;

    /* 5. move the head to point to the new node */
    (*head_ref) = new_node;
}

#include <stdio.h>
#include <stdbool.h>

void print_list(struct Node *node) {
    printf("\nTraversal in forward direction \n");
    bool is_first = true;

    while (node != NULL) {
        if (is_first) {
            printf("HEAD: ");
            is_first = false;
        }

        printf("MAX LENGTH %d \n", node->buffer->max_position);
        printf("VALUE %s \n", node->buffer->value);
        node = node->next;
    }
}

bool is_char_array_empty(char *array, char filler) {
    unsigned int len   = sizeof(*array) / sizeof(array[0]);
    for (int     index = 0; index < len; index++) {
        if (array[index] != filler) return false;
    }
    return true;
}

void constrict(struct Node *node) {
    while (node != NULL && node->next != NULL) {
        if (is_char_array_empty(node->buffer->value, '\0') &&
            is_char_array_empty(node->next->buffer->value, '\0')) {
            if (node->prev != NULL) {
                node->prev->next = node->next;
            }

            node->next = node->prev;
//            free(node);
        }
        node = node->next;
    }
}

void make_warning_sound(void) {
#ifdef _WIN32
    MessageBeep(MB_ICONWARNING);
#endif
}