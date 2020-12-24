#include "pattern/ArrayValuePattern.h"
#include <pattern/TokenPattern.h>
#include <pattern/ExpressionPattern.h>
#include <pattern/FunctionCallPattern.h>
#include <pattern/PatternList.h>
#include <ast/OperatorAST.h>
#include <ast/OperandAST.h>
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
        bool err = false;
        TokenIterator &it = beg;

        std::stack<Token> op_stack;
        std::stack<ASTPtr> expr_stack;

        // watch for functions when the word appears
        FunctionCallPattern fcp;
        ArrayValuePattern avp;

        while (it != end && it->type != m_endingToken) {
            if (it->type == TokenType::LParenth) {
                op_stack.push(*it);
            } else if (it->type == TokenType::RParenth) {
                while (op_stack.size()
                    && op_stack.top().type != TokenType::LParenth) {
                    Token op = op_stack.top();
                    op_stack.pop();
                    if (expr_stack.size() < 2) {
                        err = true;
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
                        err = true;
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
                        err = true;
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

                    // std::cout << "WORD: " << it->value << std::endl;
                    if ((it + 1) != end
                        && (it + 1)->type == TokenType::LParenth) {
                        if (fcp.matches(it, end)) {
                            expr_stack.push(std::move(fcp.getNode()));
                            continue;
                        } else {
                            // error => a(... but not function call
                            err = true;
                        }
                    } else if ((it + 1) != end
                        && (it + 1)->type == TokenType::LBracket) {
                        if (avp.matches(it, end)) {
                            expr_stack.push(std::move(fcp.getNode()));
                            continue;
                        } else {
                            // error => a(... but not function call
                            err = true;
                        }
                    } else {
                        expr_stack.push(ASTPtr(new OperandAST(*it)));
                    }
                } else {
                    retval = false;
                    break;
                }
            }
            if (err) {
                break;
            }
            ++it;
        }

        while (op_stack.size() && op_stack.top().type >= it->type && !err) {
            Token op = op_stack.top();
            op_stack.pop();

            if (expr_stack.size() < 2) {
                // unable to finish tree creation when no 2 nodes can be added
                // together with an operator
                err = true;
                break;
            } else {
                ASTPtr right = std::move(expr_stack.top());
                expr_stack.pop();
                ASTPtr left = std::move(expr_stack.top());
                expr_stack.pop();
                expr_stack.push(ASTPtr(new OperatorAST(op, left, right)));
            }
        }

        if (expr_stack.size() == 1 && op_stack.size() == 0 && retval && !err) {
            // parsed correctly => return last node on the stack
            m_node = std::move(expr_stack.top());
            expr_stack.pop();
        } else {
            retval = false;
        }

        // move over ending token if not already parsed everything
        if (it != end) {
            ++it;
        }
        return retval;
    }
}
}