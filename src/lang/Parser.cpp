#include "lang/Token.hpp"
#include "lang/Tokenizer.hpp"
#include "lang/ast/AST.hpp"
#include <lang/Parser.hpp>
#include <lang/pattern/PatternList.hpp>
#include <lang/pattern/ExpressionPattern.hpp>
#include <lang/pattern/TokenPattern.hpp>
#include <lang/Utils.hpp>
#include <ex/InvalidFileException.hpp>
#include <iostream>
#include <stack>

namespace zinc {
namespace lang {
    Parser::Parser() { }

    void Parser::parseFile(const std::string &file_name)
    {
        std::string content;
        try {
            content = Utils::readFile(file_name);
        } catch (ex::InvalidFileException &ex) {
            std::cerr << ex.what() << std::endl;
        }

        if (content.size()) {
            try {
                m_tokenizer.tokenize(content);
                parseTokens();
            } catch (std::runtime_error &ex) {
                std::cerr << ex.what() << std::endl;
            }
        }
    }

    static inline void AST_PRINT(std::unique_ptr<AST> &node, int ind)
    {
        if (!node) {
            return;
        }
        for (int j = 0; j < ind; j++) {
            std::cout << "  ";
        }
        std::cout << "> [\"" << node->getToken().value << "\"]" << std::endl;
        for (int i = 0; i < node->getChildrenCount(); i++) {
            AST_PRINT(node->getChild(i), ind + 1);
        }
        AST_PRINT(node->getNext(), ind);
    }

    void Parser::parseTokens()
    {
        // tokenization succeeded -> search for patterns between tokens and
        // create an AST

        // create pattern lists for all statements
        // check if any matches => if matches add to the AST => if none found
        // its invalid syntax

        // watch for blocks => use stack to handle
        // configure patterns
        // expression pattern => match expressions
        ExpressionPattern ep_newline(TokenType::Newline);
        ExpressionPattern ep_lbrace(TokenType::LBrace);
        ExpressionPattern ep_rbrace(TokenType::RBrace);

        // token patterns => match keywords and stuff like that
        TokenPattern obj_tp(TokenType::Object, ASTType::ObjectDef, 2);
        TokenPattern func_tp(TokenType::Function, ASTType::FunctionDef, 3);
        TokenPattern enum_tp(TokenType::Enum, ASTType::EnumDef, 2);
        TokenPattern if_tp(TokenType::If, ASTType::If, 2);
        TokenPattern else_tp(TokenType::Else, ASTType::Else, 1);
        TokenPattern for_tp(TokenType::For, ASTType::For, 2);
        TokenPattern while_tp(TokenType::For, ASTType::For, 2);
        TokenPattern word_tp(TokenType::Word, ASTType::Basic, 0);
        TokenPattern import_tp(TokenType::Import, ASTType::Import, 1);
        TokenPattern namespace_tp(TokenType::Namespace, ASTType::Namespace, 1);
        TokenPattern ret_tp(TokenType::Return, ASTType::Return, 1);

        // block parts
        TokenPattern block_start_tp(TokenType::LBrace, ASTType::Basic, 0);
        TokenPattern block_end_tp(TokenType::RBrace, ASTType::Basic, 0);

        // build pattern list vector
        std::vector<PatternList> pl_vec({
            // object definition
            PatternList({ &obj_tp, &ep_lbrace }),
            // function definition
            PatternList({ &func_tp, &word_tp, &ep_lbrace }),
            // enum definition
            PatternList({ &enum_tp, &ep_lbrace, &ep_newline, &block_end_tp }),
            // import definition
            PatternList({ &import_tp, &ep_newline }),
            // namespace definition
            PatternList({ &namespace_tp, &ep_newline }),
            // return statement
            PatternList({ &ret_tp, &ep_newline }),
            // end block
            PatternList({ &block_end_tp }),
            // if statement
            PatternList({ &if_tp, &ep_lbrace }),
            // else statement
            PatternList({ &else_tp, &block_start_tp }),
            // for statement
            PatternList({ &for_tp, &ep_lbrace }),
            // while statement
            PatternList({ &while_tp, &ep_lbrace }),
            // simple expression goes last => check after all others
            PatternList({ &ep_newline }),
        });

        TokenIterator curr = m_tokenizer.getIterator();
        TokenIterator end = m_tokenizer.getEndingIterator();

        bool root_init = false;
        bool done = false;

        // use for parsing blocks of data
        std::stack<ASTPtr *> node_stack;
        // current node following AST position
        ASTPtr *tmp_node = &m_root;

        while (curr != end) {
            bool pattern_found = true;
            if (curr->type == TokenType::Newline) {
                ++curr;
                continue;
            }
            for (PatternList &pl : pl_vec) {
                if (pl.matches(curr, end)) {
                    auto first_nt = pl.getPattern(0)->getNode()->getType();

                    switch (first_nt) {
                    case ASTType::Import:
                        *tmp_node = std::move(pl.getPattern(0)->getNode());
                        (*tmp_node)->setChild(0, pl.getPattern(1)->getNode());
                        tmp_node = &(*tmp_node)->getNext();
                        break;
                    case ASTType::Namespace:
                        *tmp_node = std::move(pl.getPattern(0)->getNode());
                        (*tmp_node)->setChild(0, pl.getPattern(1)->getNode());
                        tmp_node = &(*tmp_node)->getNext();
                        break;
                    case ASTType::Return:
                        *tmp_node = std::move(pl.getPattern(0)->getNode());
                        (*tmp_node)->setChild(0, pl.getPattern(1)->getNode());
                        tmp_node = &(*tmp_node)->getNext();
                        break;
                    case ASTType::If:
                        // push current to stack
                        *tmp_node = std::move(pl.getPattern(0)->getNode());
                        (*tmp_node)->setChild(0, pl.getPattern(1)->getNode());
                        node_stack.push(tmp_node);
                        tmp_node = &(*tmp_node)->getChild(1);
                        break;
                    case ASTType::Else:
                        // push current to stack
                        *tmp_node = std::move(pl.getPattern(0)->getNode());
                        node_stack.push(tmp_node);
                        tmp_node = &(*tmp_node)->getChild(0);
                        break;
                    case ASTType::For:
                        // push current to stack
                        *tmp_node = std::move(pl.getPattern(0)->getNode());
                        (*tmp_node)->setChild(0, pl.getPattern(1)->getNode());
                        node_stack.push(tmp_node);
                        tmp_node = &(*tmp_node)->getChild(1);
                        break;
                    case ASTType::While:
                        // push current to stack
                        *tmp_node = std::move(pl.getPattern(0)->getNode());
                        (*tmp_node)->setChild(0, pl.getPattern(1)->getNode());
                        node_stack.push(tmp_node);
                        tmp_node = &(*tmp_node)->getChild(1);
                        break;
                    case ASTType::ObjectDef:
                        *tmp_node = std::move(pl.getPattern(0)->getNode());
                        (*tmp_node)->setChild(0, pl.getPattern(1)->getNode());
                        node_stack.push(tmp_node);
                        tmp_node = &(*tmp_node)->getChild(1);
                        break;
                    case ASTType::FunctionDef:
                        *tmp_node = std::move(pl.getPattern(0)->getNode());
                        (*tmp_node)->setChild(0, pl.getPattern(1)->getNode());
                        (*tmp_node)->setChild(1, pl.getPattern(2)->getNode());
                        node_stack.push(tmp_node);
                        tmp_node = &(*tmp_node)->getChild(2);
                        break;
                    case ASTType::EnumDef:
                        // push current to stack
                        *tmp_node = std::move(pl.getPattern(0)->getNode());
                        (*tmp_node)->setChild(0, pl.getPattern(1)->getNode());
                        (*tmp_node)->setChild(1, pl.getPattern(2)->getNode());
                        tmp_node = &(*tmp_node)->getNext();
                        break;
                    case ASTType::Basic: {
                        // check if its the right brace => ending block
                        auto tt = pl.getPattern(0)->getNode()->getToken().type;
                        if (tt == TokenType::RBrace) {
                            // block ending
                            tmp_node = node_stack.top();
                            node_stack.pop();
                            tmp_node = &(*tmp_node)->getNext();
                        }
                        break;
                    }
                    case ASTType::Operator:
                        // expression
                        *tmp_node = std::move(pl.getPattern(0)->getNode());
                        tmp_node = &(*tmp_node)->getNext();
                        break;
                    default:
                        pattern_found = false;
                        break;
                    }
                    // found pattern => parse further
                    break;
                }
            }
            if (!pattern_found) {
                // error on curr->line
                break;
            }
        }
        AST_PRINT(m_root, 0);
    }
}
}