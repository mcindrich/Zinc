#pragma once

#include <lang/Token.hpp>
#include <list>

namespace zinc {
namespace lang {

    class Tokenizer {
    public:
        Tokenizer();
        void tokenize(char *input);

    private:
        void splitIntoTokens(const std::string &INPUT);
        std::list<Token> m_tokens;
    };
}
}