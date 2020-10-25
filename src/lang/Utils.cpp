#include <lang/Utils.hpp>
#include <ex/InvalidFileException.hpp>
#include <fstream>

namespace zinc {
namespace lang {
    char *Utils::readFile(const std::string &file_name)
    {
        char *val = nullptr;
        size_t flen = 0;
        std::ifstream file(file_name);

        if (!file.is_open()) {
            throw zinc::ex::InvalidFileException(file_name);
        }

        file.seekg(0, std::ios::end);
        flen = file.tellg();
        file.seekg(0);

        val = new char[flen + 1];
        file.read(val, flen);
        val[flen] = 0;

        return val;
    }
}
}