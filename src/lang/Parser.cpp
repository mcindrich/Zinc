#include <lang/Parser.hpp>
#include <ex/InvalidFileException.hpp>
#include <lang/Utils.hpp>
#include <iostream>

namespace zinc {
namespace lang {
    Parser::Parser() { }

    void Parser::parseFile(const std::string &file_name)
    {
        std::string content;
        try {
            content = Utils::readFile(file_name);
        } catch (ex::InvalidFileException &ex) {
            std::cerr << ex.what() << std::endl;
        }

        if (content.size()) {
            try {
                m_tokenizer.tokenize(content);
            } catch (std::runtime_error &ex) {
                std::cerr << ex.what() << std::endl;
            }
        }
    }
}
}