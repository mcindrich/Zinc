#pragma once

// AST node class

namespace zinc {
namespace lang {
    class AST {

    private:
        AST *m_next;
        AST **m_children;
    };
}
}