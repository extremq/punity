//
// Created by god on 21.11.2022.
//
#include <iostream>

#ifndef _PERROR_H
#define _PERROR_H

namespace Punity::Utils {
    // Simple error function
    static void Error(std::string const& error_message) {
        std::cout << "[ERROR] " << error_message << '\n';
        exit(EXIT_FAILURE);
    }

    static void Error(std::string const& error_message, std::string const& object_name) {
        std::cout << "[ERROR] [" << object_name << "] " << error_message << '\n';
        exit(EXIT_FAILURE);
    }
}
#endif //_PERROR_H
