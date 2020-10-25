#pragma once

#include <string>

namespace zinc {
namespace lang {
    class Utils {
    public:
        static char *readFile(const std::string &file_name);
    };
}
}