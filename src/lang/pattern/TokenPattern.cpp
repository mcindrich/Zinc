#include <lang/pattern/TokenPattern.hpp>

namespace zinc {
namespace lang {
    TokenPattern::TokenPattern(TokenType tt)
        : m_tok(tt)
    {
    }

    bool TokenPattern::matches(TokenIterator &beg, TokenIterator &end)
    {
        bool retval = false;
        return retval;
    }
}
}