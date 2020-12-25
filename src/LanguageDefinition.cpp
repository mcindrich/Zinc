#include "LanguageDefinition.h"

namespace zinc {
namespace lang {
    LanguageDefinition::LanguageDefinition(ASTPtr &n)
        : m_node(n)
    {
    }

    ASTPtr &LanguageDefinition::getNode() { return m_node; }
}
}