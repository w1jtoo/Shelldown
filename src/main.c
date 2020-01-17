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
        get_current_directory(current_directory, FILENAME_MAX);
        printf("\nYou now here -> %s \n%s$%s>", current_directory, getenv("USERNAME"), getenv("COMPUTERNAME"));
        line = read_line();
        args = split_line(line);

        switch (execute(args)) {
            case not_in_builtins:
                printf("%s\n", line);
                system(line);
                break;
            case on_exit:
                exit_status = true;
                break;
            default:
                break;
        }

        free(line);
        free(args);
    } while (!exit_status);
}

int main(void) {
    loop();
    return EXIT_SUCCESS;
}

