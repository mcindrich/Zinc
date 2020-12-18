#include "lang/pattern/TokenPattern.hpp"
#include "lang/Token.hpp"
#include "lang/Tokenizer.hpp"
#include "lang/ast/AST.hpp"
#include "lang/pattern/ExpressionPattern.hpp"
#include <lang/pattern/FunctionCallPattern.hpp>
#include <lang/pattern/TokenPattern.hpp>
#include <stack>

namespace zinc {
namespace lang {
    bool FunctionCallPattern::matches(TokenIterator &beg, TokenIterator &end)
    {
        bool retval = true;
        TokenIterator beg_tmp = beg;
        TokenIterator parsed_correctly;

        // check for first token being word like 'simpleFunction'
        TokenPattern word_tp(TokenType::Word, ASTType::Basic, 1);
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