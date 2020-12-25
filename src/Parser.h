#pragma once

#include <Tokenizer.h>
#include <ast/AST.h>
#include <memory>

namespace zinc {
namespace lang {
    class Parser {
    public:
        Parser();

        void parseFile(const std::string &file_name);

    private:
        bool parseTokens();
        ASTPtr m_root;
        Tokenizer m_tokenizer;
    };
}
}