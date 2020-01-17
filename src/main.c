#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "builtins.h"
#include "command_executer.h"
#include "utils.h"

void loop(void) {
    bool exit_status = false;
    char *line;
    char **args;
    char current_directory[FILENAME_MAX];
    do {
        get_current_directory( current_directory, FILENAME_MAX );
        printf("%s> ", current_directory);
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

