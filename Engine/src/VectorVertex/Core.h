//
// Created by bios on 9/6/23.
//

#ifndef GAMEENGINE_CORE_H
#define GAMEENGINE_CORE_H

#include <iostream>
#include <dlfcn.h>
#include "../Core/Log.h"
#include "Application.h"

#define LOAD_LIBRARY_AND_SYMBOLS(libname, libhandle, symbol_type, symbol, symbol_var) \
    do {                                                                             \
        libhandle = dlopen(libname, RTLD_LAZY);                                      \
        if (!libhandle) {                                                            \
            std::cerr << "Error loading library " << libname << ": " << dlerror() << std::endl; \
            exit(1);                                                                 \
        }                                                                            \
        symbol_var = (symbol_type)dlsym(libhandle, symbol);                          \
        if (!symbol_var) {                                                           \
            std::cerr << "Error loading symbol " << symbol << ": " << dlerror() << std::endl; \
            exit(1);                                                                 \
        }                                                                            \
    } while (0)

#define CLOSE_LIBRARY(libhandle)                                                   \
    do {                                                                           \
        if (libhandle) {                                                           \
            dlclose(libhandle);                                                    \
            libhandle = nullptr;                                                   \
        }                                                                          \
    } while (0)

#endif //GAMEENGINE_CORE_H
