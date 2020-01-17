//
// Created by w1jtoo on 16.01.2020.
//
#include <stdio.h>
#include "builtins.h"
#include <stdbool.h>
#include <string.h>

int help(char **args) {
    printf(
            "+------------------------------------------------------+\n"
            "|------------------------------------------------------|\n"
            "||   ,+.  .  . ,++. ,    ,    ,+.   ,+.  ,   . .  .   ||\n"
            "||  (   ` +  + +    +    +    +  \\ /   \\ + . + +\\ +   ||\n"
            "||   `+.  +--+ ++   |    |    |  + +   + | ) ) | \\|   ||\n"
            "||  .   ) +  + +    +    +    +  / \\   / +/+/  +  +   ||\n"
            "||   `+'  '  ' `++' `++' `++' `+'   `+'  ' '   '  '   ||\n"
            "|------------------------------------------------------|\n"
            "+------------------------------------------------------+\n"
            "|Shelldown is command-line interpreter superstructure  |\n"
            "|with supporting all NT systems and commands. When     |\n"
            "|shelldown get a command its check if it is in builtins|\n"
            "|and after go to path (execute in cmd).                |\n"
            "|Builtin commands:                                     |\n"
            "|                                                      |\n"
            "|              # cd   - change directory               |\n"
            "|              # exit | safe close inter preter        |\n"
            "|              # ?    | show this text                 |\n"
            "|                                                      |\n"
            "|              type help to print cmd help             |\n"
            "+---------------------+--------------------------------+\n");
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


