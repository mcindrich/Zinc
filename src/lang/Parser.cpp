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
        std::cout << "- [\"" << node->getToken().value << "\"]" << std::endl;
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

        // token patterns => match keywords and stuff like that
        TokenPattern obj_tp(TokenType::Object, ASTType::ObjectDef, 2);
        TokenPattern func_tp(TokenType::Function, ASTType::FunctionDef, 3);
        TokenPattern if_tp(TokenType::If, ASTType::If, 2);
        TokenPattern else_tp(TokenType::Else, ASTType::Else, 1);
        TokenPattern for_tp(TokenType::For, ASTType::For, 1);
        TokenPattern word_tp(TokenType::Word, ASTType::Basic, 0);
        TokenPattern import_tp(TokenType::Import, ASTType::Import, 1);

        // block parts
        TokenPattern block_start_tp(TokenType::LBrace, ASTType::Basic, 1);
        TokenPattern block_end_tp(TokenType::RBrace, ASTType::Basic, 1);

        // use for parsing blocks of data
        std::stack<ASTPtr> node_stack;

        // build pattern list vector
        std::vector<PatternList> pl_vec;

        // object definition
        pl_vec.push_back(PatternList({ &obj_tp, &ep_lbrace }));
        // function definition
        pl_vec.push_back(PatternList({ &func_tp, &word_tp, &ep_lbrace }));
        // import
        pl_vec.push_back(PatternList({ &import_tp, &ep_newline }));
        // block start
        pl_vec.push_back(PatternList({ &block_start_tp }));
        // block end
        pl_vec.push_back(PatternList({ &block_end_tp }));
        // expression pattern list
        pl_vec.push_back(PatternList({ &ep_newline }));

        TokenIterator curr = m_tokenizer.getIterator();
        TokenIterator end = m_tokenizer.getEndingIterator();

        bool root_init = false;
        bool done = false;

        ASTPtr tmp_node;

        while (curr != end) {
            for (PatternList &pl : pl_vec) {
                if (pl.matches(curr, end)) {
                    ASTType first_nt = pl.getPattern(0)->getNode()->getType();

                    switch (first_nt) {
                    case ASTType::Import:
                        tmp_node = std::move(pl.getPattern(0)->getNode());
                        tmp_node->setChild(0, pl.getPattern(1)->getNode());
                        break;
                    default:
                        break;
                    }
                    // found pattern => parse further
                    break;
                }
            }
        }
        AST_PRINT(tmp_node, 0);
    }
}
}