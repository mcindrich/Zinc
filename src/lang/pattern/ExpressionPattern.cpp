#include <lang/pattern/ExpressionPattern.hpp>

namespace zinc {
namespace lang {
    ExpressionPattern::ExpressionPattern(TokenType ending_tok)
        : m_endingToken(ending_tok)
    {
    }

    bool ExpressionPattern::matches(TokenIterator &beg, TokenIterator &end)
    {
        bool retval = false;

        return retval;
    }
}
}