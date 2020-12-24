#pragma once

#include <string>

namespace zinc {
namespace lang {
    class Utils {
    public:
        static std::string readFile(const std::string &file_name);
    };
}
}