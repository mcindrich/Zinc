#include <pattern/TokenPattern.h>
#include <Token.h>
#include <Tokenizer.h>
#include <ast/AST.h>
#include <pattern/ExpressionPattern.h>
#include <pattern/FunctionCallPattern.h>
#include <pattern/TokenPattern.h>
#include <stack>

namespace zinc {
namespace lang {
    bool FunctionCallPattern::matches(TokenIterator &beg, TokenIterator &end)
    {
        bool retval = true;
        TokenIterator beg_tmp = beg;

        // check for first token being word like 'simpleFunction'
        TokenPattern word_tp(TokenType::Word, ASTType::FunctionCall, 1);
        ExpressionPattern ep(TokenType::Newline);

        if (word_tp.matches(beg_tmp, end)) {
            // move created AST node into root of this pattern node
            m_node = std::move(word_tp.getNode());
            std::stack<TokenType> parenth_stack;
            std::vector<Token> tmp_tokens;

            // now go from beg to end, if end reached => error, use stack for
            // parenthesis and check when matched last one

            if (beg_tmp->type == TokenType::LParenth) {
                parenth_stack.push(beg_tmp->type);
                tmp_tokens.push_back(*beg_tmp);
                beg_tmp++;

                // until last parenthesis found iterate and create new list of
                // tokens

                while (beg_tmp != end && parenth_stack.size() > 0
                    && beg_tmp->type != TokenType::Newline) {
                    if (beg_tmp->type == TokenType::RParenth) {
                        parenth_stack.pop();
                    } else if (beg_tmp->type == TokenType::LParenth) {
                        parenth_stack.push(beg_tmp->type);
                    }
                    tmp_tokens.push_back(*beg_tmp);
                    beg_tmp++;
                }

                if (parenth_stack.size() == 0) {
                    // create expression pattern and call match for inner tokens
                    TokenIterator beg2 = tmp_tokens.begin();
                    TokenIterator end2 = tmp_tokens.end();

                    if (ep.matches(beg2, end2)) {
                        m_node->setChild(0, ep.getNode());
                    } else {
                        retval = false;
                    }
                } else {
                    retval = false;
                }
            } else {
                retval = false;
            }
        } else {
            retval = false;
        }

        if (retval) {
            // if all parsed correctly => move iterator to correct position
            // if not => iterator will stay at the same spot for further parsing
            // and analysis
            beg = beg_tmp++;
        }
        return retval;
    }
}
}