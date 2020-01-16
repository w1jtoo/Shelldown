#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "builtins.h"
#include "stdutils.h"


void loop(void) {
    bool exit_status = false;
    char *line;
    char **args;

    do {
        printf("> ");
        line = read_line();
        args = split_line(line);

        switch (execute(args)) {
            case NOT_FOUND_IN_BUILTINS:
                system(line);
                break;
            case ON_EXIT:
                exit_status = true;
                break;
            default:
                break;
        }

        free(line);
    } while (!exit_status);
}

int main(void) {
    loop();
    return EXIT_SUCCESS;
}

