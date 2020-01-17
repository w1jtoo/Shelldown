//
// Created by w1jtoo on 16.01.2020.
//

#ifndef SHELLDOWN_BUILTINS_H
#define SHELLDOWN_BUILTINS_H

#include <stdbool.h>

typedef enum {
    not_in_builtins,
    executed_successful,
    on_exit
} ExecuteResult;


ExecuteResult help(char **args);

ExecuteResult program_exit(char **args);

unsigned int builtins_count();

ExecuteResult execute(char **args);

#endif //SHELLDOWN_BUILTINS_H
