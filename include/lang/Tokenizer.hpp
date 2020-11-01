#pragma once

#include <lang/Token.hpp>
#include <list>

namespace zinc {
namespace lang {
    typedef std::list<Token>::iterator TokenIterator;

    class Tokenizer {
    public:
        Tokenizer();
        void tokenize(std::string &input);

    private:
        void splitIntoTokens(const std::string &INPUT);

        std::list<Token> m_tokens;
        TokenIterator m_currentIterator;
    };
}
}