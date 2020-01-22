//
// Created by w1jtoo on 16.01.2020.
//
#include <stdio.h>
#include "builtins.h"
#include <stdbool.h>
#include <string.h>
#include <direct.h>


ExecuteResult help(char **args) {
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
            "|              # exit - safe close interpreter         |\n"
            "|              # ?    - show this text                 |\n"
            "|                                                      |\n"
            "|              type help to print cmd help             |\n"
            "+---------------------+--------------------------------+\n");
    return executed_successful;
}

ExecuteResult program_exit(char **args) {
    return on_exit;
}

ExecuteResult change_directory(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "Shelldown: expected argument to \"cd\"\n");
    } else {
        if (_chdir(args[1]) != 0) {
            perror("can't change directory");
        }
    }
    return executed_successful;
}

char *builtin_str[] = {"?", "exit", "cd"};

ExecuteResult (*builtin_func[])(char **) = {&help, &program_exit, &change_directory};


unsigned int builtins_count() {
    return sizeof(builtin_str) / sizeof(char *);
}


ExecuteResult execute(char **args) {
    if (args[0] == NULL) {
        return executed_successful;
    }
    for (int i = 0; i < builtins_count(); i++) {
        if (strcmp(builtin_str[i], args[0]) == 0) {
            return (*builtin_func[i])(args);
        }
    }
    return not_in_builtins;
}


