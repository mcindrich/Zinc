#include <pattern/TokenPattern.h>

namespace zinc {
namespace lang {
    TokenPattern::TokenPattern(TokenType tt, ASTType at, int nch = 0)
        : m_tok(tt)
        , m_nch(nch)
        , m_ast_type(at)
    {
    }

    bool TokenPattern::matches(TokenIterator &beg, TokenIterator &end)
    {
        bool retval = false;
        if (beg != end && beg->type == m_tok) {
            // token matches => set to true and create node for later use
            // also update iterator
            m_node = ASTPtr(new AST(*beg, m_ast_type, m_nch));
            ++beg;
            retval = true;
        }
        return retval;
    }
}
}