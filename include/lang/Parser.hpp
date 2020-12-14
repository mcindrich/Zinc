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
        void parseTokens();
        ASTPtr m_root;
        Tokenizer m_tokenizer;
    };
}
}