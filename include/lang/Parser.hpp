#pragma once

#include <lang/Tokenizer.hpp>
#include <lang/ast/AST.hpp>
#include <memory>

namespace zinc {
namespace lang {
    class Parser {
    public:
        Parser();

        void parseFile(const std::string &file_name);

    private:
        void formAST();

        std::unique_ptr<AST> parseNumberExpression();
        std::unique_ptr<AST> parseWordExpression();
        std::unique_ptr<AST> parseVariableInitExpression();
        std::unique_ptr<AST> parseFunctionExpression();

        std::unique_ptr<AST> m_root;
        Tokenizer m_tokenizer;
    };
}
}