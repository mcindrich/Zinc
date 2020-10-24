#include <lang/Parser.hpp>
#include <ex/InvalidFileException.hpp>
#include <lang/Utils.hpp>
#include <iostream>

namespace zinc {
namespace lang {
    Parser::Parser()
    {
    }

    void Parser::parseFile(char *fname)
    {
        char *content = NULL;
        try {
            content = Utils::readFile(fname);

        } catch (ex::InvalidFileException &ex) {
            std::cerr << ex.what() << std::endl;
        }

        if (content) {
            m_tokenizer.tokenize(content);
            delete[] content;
        }
    }
}
}