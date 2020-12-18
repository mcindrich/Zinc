#include "lang/pattern/TokenPattern.hpp"
#include <lang/pattern/ExpressionPattern.hpp>
#include <lang/pattern/PatternList.hpp>
#include <lang/ast/OperatorAST.hpp>
#include <lang/ast/OperandAST.hpp>
#include <stack>
#include <utility>
#include <iostream>

#define IS_OPERATOR(t) (t > TokenType::OP_START && t < TokenType::OP_END)

namespace zinc {
namespace lang {
    ExpressionPattern::ExpressionPattern(TokenType ending_tok)
        : m_endingToken(ending_tok)
    {
    }

    bool ExpressionPattern::matches(TokenIterator &beg, TokenIterator &end)
    {
        bool retval = true;
        TokenIterator &it = beg;

        std::stack<Token> op_stack;
        std::stack<ASTPtr> expr_stack;

        while (it != end && it->type != m_endingToken) {
            if (it->type == TokenType::LParenth) {
                op_stack.push(*it);
            } else if (it->type == TokenType::RParenth) {
                while (op_stack.size()
                    && op_stack.top().type != TokenType::LParenth) {
                    Token op = op_stack.top();
                    op_stack.pop();
                    if (expr_stack.size() < 2) {
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
                op_stack.pop();
            } else if (it->type == TokenType::LBracket) {
                op_stack.push(*it);
            } else if (it->type == TokenType::RBracket) {
                while (op_stack.size()
                    && op_stack.top().type != TokenType::LBracket) {
                    Token op = op_stack.top();
                    op_stack.pop();
                    if (expr_stack.size() < 2) {
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
                op_stack.pop();
            } else if (IS_OPERATOR(it->type)) {
                while (op_stack.size() && op_stack.top().type >= it->type) {
                    Token op = op_stack.top();
                    op_stack.pop();

                    if (expr_stack.size() < 2) {
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
                op_stack.push(*it);
            } else {
                // check for all patterns
                // testing: use only numbers
                if (it->type == TokenType::Number) {
                    expr_stack.push(ASTPtr(new OperandAST(*it)));
                } else if (it->type == TokenType::Word) {
                    // for now just push => TODO: add function and other pattern
                    // checkings like simpleFunction(...)
                    expr_stack.push(ASTPtr(new OperandAST(*it)));
                } else {
                    retval = false;
                    break;
                }
            }
            ++it;
        }

        while (op_stack.size() && op_stack.top().type >= it->type) {
            Token op = op_stack.top();
            op_stack.pop();

            if (expr_stack.size() < 2) {
                break;
            } else {
                ASTPtr right = std::move(expr_stack.top());
                expr_stack.pop();
                ASTPtr left = std::move(expr_stack.top());
                expr_stack.pop();
                expr_stack.push(ASTPtr(new OperatorAST(op, left, right)));
            }
        }

        if (expr_stack.size() == 1 && op_stack.size() == 0 && retval) {
            // parsed correctly => return last node on the stack
            m_node = std::move(expr_stack.top());
            expr_stack.pop();
        }

        // move over ending token
        ++it;
        return retval;
    }
}
}