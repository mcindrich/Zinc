#pragma once

#include <lang/pattern/Pattern.hpp>
#include <lang/ast/AST.hpp>

namespace zinc {
namespace lang {
    class TokenPattern : public Pattern {
    public:
        TokenPattern(TokenType tt);
        bool matches(TokenIterator &beg, TokenIterator &end);

    private:
        TokenType m_tok;
    }
}
}