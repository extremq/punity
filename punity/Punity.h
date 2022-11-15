//
// Created by god on 12.11.2022.
//

#ifndef _PUNITY_H
#define _PUNITY_H

#include <iostream>
#include <cstdlib>
#include "pico/stdlib.h"

#include "punity/Screen/PScreen.h"
#include "punity/Engine/PEngine.h"

// Start of Punity!
namespace Punity {
    // The statics
    static PScreen& Screen = PScreen::get();
    static PEngine& Engine = PEngine::get();

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

#endif //_PUNITY_H
