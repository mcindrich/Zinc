#include <lang/pattern/ExpressionPattern.hpp>
#include <lang/ast/OperatorAST.hpp>
#include <stack>

#define IS_OPERATOR(t) (t > TokenType::OP_START && t < TokenType::OP_END)

namespace zinc {
namespace lang {
    ExpressionPattern::ExpressionPattern(TokenType ending_tok)
        : m_endingToken(ending_tok)
    {
    }

    bool ExpressionPattern::matches(TokenIterator &beg, TokenIterator &end)
    {
        bool retval = false;
        // use copies instead of references in case some patterns don't match ->
        // normally getting back to the last point and no need to reverse the
        // referenced iterator
        TokenIterator it = beg;
        bool pass_ok = true;

        std::stack<Token> op_stack;
        std::stack<ASTPtr> expr_stack;

        while (it != end && it->type != TokenType::Newline) {
            if (it->type == TokenType::LParenth) {
                op_stack.push(*it);
            } else if (it->type == TokenType::RParenth) {
            } else if (IS_OPERATOR(it->type)) {
                while (op_stack.size() && op_stack.top().type >= it->type) {
                    Token op = op_stack.top();
                    op_stack.pop();
                    if (expr_stack.size() < 2) {
                        // error -> cant pop operands from stack
                        pass_ok = false;
                        break;
                    } else {
                        ASTPtr right = std::move(expr_stack.top());
                        expr_stack.pop();
                        ASTPtr left = std::move(expr_stack.top());
                        expr_stack.pop();
                        expr_stack.push(
                            ASTPtr(new OperatorAST(op, left, right)));
                    }
                }
            } else {
                // check for all patterns
            }
            ++it;
        }
        return retval;
    }
}
}