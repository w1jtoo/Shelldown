//
// Created by w1jtoo on 16.01.2020.
//
#include <stdio.h>
#include "builtins.h"
#include <stdbool.h>
#include <string.h>

int help(char **args) {
    printf("I'm help.");
    return SUCCESS_EXECUTED;
}

int program_exit(char **args) {
    return ON_EXIT;
}

char *builtin_str[] = {"?", "exit"};

int (*builtin_func[])(char **) = {&help, &program_exit};

int builtins_count() {
    return sizeof(builtin_str) / sizeof(char *);
}

int execute(char **args) {
    if (args[0] == NULL) {
        return SUCCESS_EXECUTED;
    }
    for (int i = 0; i < builtins_count(); i++) {
        if (strcmp(builtin_str[i], args[0]) == 0) {
            return (*builtin_func[i])(args);
        }
    }
    return NOT_FOUND_IN_BUILTINS;
}


