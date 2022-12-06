//
// Created by god on 21.11.2022.
//

#ifndef _PERROR_H
#define _PERROR_H

#include <iostream>

namespace Punity::Utils {
    void Error(std::string const& error_message);
    void Error(std::string const& error_message, std::string const& object_name);
}
#endif //_PERROR_H
