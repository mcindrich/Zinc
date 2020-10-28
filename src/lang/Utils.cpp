#include <lang/Utils.hpp>
#include <ex/InvalidFileException.hpp>
#include <fstream>

namespace zinc {
namespace lang {
    std::string Utils::readFile(const std::string &file_name)
    {
        std::ifstream file(file_name);
        std::string str;

        if (!file.is_open()) {
            throw zinc::ex::InvalidFileException(file_name);
        }

        file.seekg(0, std::ios::end);
        str.reserve(file.tellg());
        file.seekg(0, std::ios::beg);

        str.assign((std::istreambuf_iterator<char>(file)),
            std::istreambuf_iterator<char>());
        return str;
    }
}
}