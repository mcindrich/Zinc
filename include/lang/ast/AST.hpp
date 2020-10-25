#pragma once

// AST node class
#include <memory>

namespace zinc {
namespace lang {
    class AST {
    public:
        AST();

        virtual ~AST();

    private:
        std::unique_ptr<AST> m_next;
        std::unique_ptr<AST *> m_children;
    };
}
}