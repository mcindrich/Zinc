#pragma once

#include "LanguageDefinition.h"
#include "ast/AST.h"

namespace zinc {
namespace lang {
    class FunctionDefinition : public LanguageDefinition {
    public:
        FunctionDefinition(ASTPtr &n);

        std::string getName() const;
        int getParamCount() const;

    private:
        int m_paramCount;
        std::string m_name;
        std::string m_retType;
    };
}
}