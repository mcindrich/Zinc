#include "FunctionDefinition.h"
#include "LanguageDefinition.h"

namespace zinc {
namespace lang {
    FunctionDefinition::FunctionDefinition(ASTPtr &n)
        : LanguageDefinition(n)
        , m_paramCount(0)
    {
        m_name = m_node->getChild(0)->getToken().value;
        ASTPtr &expr_node = m_node->getChild(1);

        if (expr_node && expr_node->getType() == ASTType::Operator) {
            // if first op is -> , get the return type, if not -> return type is
            // empty
        }
    }

}
}