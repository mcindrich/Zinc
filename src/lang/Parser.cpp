#include <lang/Parser.hpp>
#include <lang/pattern/PatternList.hpp>
#include <lang/pattern/ExpressionPattern.hpp>
#include <lang/pattern/TokenPattern.hpp>
#include <lang/Utils.hpp>
#include <ex/InvalidFileException.hpp>
#include <iostream>

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

    static inline void astPrint(std::unique_ptr<AST> &node, int ind) { }

    void Parser::parseTokens()
    {
        // tokenization succeeded -> search for patterns between tokens and
        // create an AST
        ExpressionPattern ep(TokenType::Newline);
        PatternList pat_list({ &ep }, m_tokenizer.getIterator(),
            m_tokenizer.getEndingIterator());

        if (pat_list.matches()) {
            astPrint(ep.getNode(), 0);
        }
    }
}
}