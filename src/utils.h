//
// Created by w1jtoo on 17.01.2020.
//

#ifndef SHELLDOWN_UTILS_H
#define SHELLDOWN_UTILS_H

#ifdef _WIN32

#include <direct.h>

#define get_current_directory _getcwd

#include <windows.h>

#endif

#ifdef linux
#include <unistd.h>
#define get_current_directory getcwd
#endif


#endif //SHELLDOWN_UTILS_H
