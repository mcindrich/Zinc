#pragma once

#include <lang/Tokenizer.hpp>
#include <lang/ast/AST.hpp>

namespace zinc {
namespace lang {
    class Pattern {
    public:
        virtual bool matches(TokenIterator &start, TokenIterator &end) = 0;
        std::unique_ptr<AST> &getNode();

    protected:
        // temporary node which derived classes can use to create a tree along
        // the way if the pattern is matching

        // if matches returns false, node will be deleted and it cannot be used
        std::unique_ptr<AST> m_node;
    };
}
}