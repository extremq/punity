//
// Created by god on 06.12.2022.
//

#include "PError.h"

namespace Punity::Utils {
    // Simple error function
    void Error(std::string const& error_message) {
        std::cout << "[ERROR] " << error_message << '\n';
        exit(EXIT_FAILURE);
    }

    void Error(std::string const& error_message, std::string const& object_name) {
        std::cout << "[ERROR] [" << object_name << "] " << error_message << '\n';
        exit(EXIT_FAILURE);
    }
}