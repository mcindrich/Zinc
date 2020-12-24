#pragma once

#include <exception>
#include <stdexcept>
#include <string>

namespace zinc {
namespace ex {
    class InvalidFileException : public std::runtime_error {
    public:
        InvalidFileException(std::string fn)
            : std::runtime_error("Unable to open given file: \'" + fn + "\'.")
        {
        }
    };
}
}