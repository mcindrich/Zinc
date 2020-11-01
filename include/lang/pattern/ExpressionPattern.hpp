#pragma once

#include <lang/pattern/Pattern.hpp>
#include <lang/ast/AST.hpp>

namespace zinc {
namespace lang {
    // class for matching expressions up until the ending_tok is seen
    // the use of ending_tok becomes clear when enum block, i.e. { Red, Blue }
    // can be parsed the same way as 2 + 3 using different ending tokens
    class ExpressionPattern : public Pattern {
    public:
        ExpressionPattern(TokenType ending_tok);
        bool matches(TokenIterator &beg, TokenIterator &end);

    private:
        TokenType m_endingToken;
    }
}
}