#pragma once

#include "LanguageDefinition.h"
#include "ast/AST.h"

namespace zinc {
namespace lang {
    class EnumDefinition : public LanguageDefinition {
    public:
        EnumDefinition(ASTPtr &n);

        std::string getName() const;
        std::string getValue(int n) const;

    private:
        std::string m_name;
        std::vector<std::string> m_values;
    };
}
}