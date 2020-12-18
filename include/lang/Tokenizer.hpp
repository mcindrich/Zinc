#pragma once

#include <lang/Token.hpp>
#include <vector>

namespace zinc {
namespace lang {
    typedef std::vector<Token>::iterator TokenIterator;

    class Tokenizer {
    public:
        Tokenizer();
        void tokenize(std::string &input);

        TokenIterator &getIterator();
        TokenIterator getEndingIterator();

    private:
        void splitIntoTokens(const std::string &INPUT);

        std::vector<Token> m_tokens;
        TokenIterator m_currentIterator;
    };
}
}