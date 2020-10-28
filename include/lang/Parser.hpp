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
        // expr (2 + 3 | a + b | someVar<Type> = 2 + 3)
        std::unique_ptr<AST> parseExpression();
        // 10.20 | 10 | 1 etc.
        std::unique_ptr<AST> parseNumberExpression();
        // a | b | simpleVariable
        std::unique_ptr<AST> parseWordExpression();
        // someVar<Type>
        std::unique_ptr<AST> parseVariableDeclExpression();
        // ( fn funcName )(params...) -> RetType ';'
        std::unique_ptr<AST> parseFunctionDeclaration();
        // ( fn funcName )(params...) -> RetType {...}
        std::unique_ptr<AST> parseFunctionInitialization();
        // obj [expr] {}
        std::unique_ptr<AST> parseObjStatement();

        std::unique_ptr<AST> m_root;
        Tokenizer m_tokenizer;
    };
}
}