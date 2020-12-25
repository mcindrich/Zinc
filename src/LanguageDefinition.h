#pragma once

#include "ast/AST.h"

namespace zinc {
namespace lang {
    class LanguageDefinition {
    public:
        LanguageDefinition(ASTPtr &n);

        ASTPtr &getNode();

    protected:
        ASTPtr &m_node;
    };
}
}