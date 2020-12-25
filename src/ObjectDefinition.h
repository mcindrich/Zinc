#pragma once

#include "LanguageDefinition.h"
#include "FunctionDefinition.h"
#include <vector>
namespace zinc {
namespace lang {
    class ObjectDefinition : public LanguageDefinition {
    public:
        ObjectDefinition(ASTPtr &n);

    private:
        std::string m_name;
        std::vector<ObjectDefinition> m_objDefs;
        std::vector<FunctionDefinition> m_funcDefs;
    };
}
}