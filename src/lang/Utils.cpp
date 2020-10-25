#include <lang/Utils.hpp>
#include <ex/InvalidFileException.hpp>
#include <fstream>

namespace zinc {
namespace lang {
    char *Utils::readFile(char *fname)
    {
        char *val = nullptr;
        size_t flen = 0;
        std::ifstream file(fname);

        if (!file.is_open()) {
            throw zinc::ex::InvalidFileException(std::string(fname));
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