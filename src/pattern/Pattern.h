#pragma once

#include <Tokenizer.h>
#include <ast/AST.h>

namespace zinc {
namespace lang {
    class Pattern {
    public:
        virtual bool matches(TokenIterator &start, TokenIterator &end) = 0;
        ASTPtr &getNode();

    protected:
        // temporary node which derived classes can use to create a tree along
        // the way if the pattern is matching

        // if matches returns false, node will be deleted and it cannot be used
        ASTPtr m_node;
    };
}
}