#pragma once

#include <vector>
#include <lang/Token.hpp>

namespace zinc {
namespace lang {

    class Tokenizer {
    public:
        Tokenizer();
        void tokenize(char *input);

    private:
        std::vector<Token> m_tokens;
    };
}
}