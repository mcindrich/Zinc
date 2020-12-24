#pragma once

#include <pattern/Pattern.h>
#include <ast/AST.h>

namespace zinc {
namespace lang {
    class TokenPattern : public Pattern {
    public:
        TokenPattern(TokenType tt, ASTType type, int nch);
        bool matches(TokenIterator &beg, TokenIterator &end);

    private:
        TokenType m_tok;
        int m_nch;
        ASTType m_ast_type;
    };
}
}