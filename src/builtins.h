//
// Created by w1jtoo on 16.01.2020.
//

#ifndef SHELLDOWN_BUILTINS_H
#define SHELLDOWN_BUILTINS_H

#include <stdbool.h>

#define SUCCESS_EXECUTED 1
#define NOT_FOUND_IN_BUILTINS 2
#define ON_EXIT 3

int help(char **args);

int program_exit(char **args);

int builtins_count();

int execute(char **args);

#endif //SHELLDOWN_BUILTINS_H
