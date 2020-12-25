#include "EnumDefinition.h"
#include "LanguageDefinition.h"

namespace zinc {
namespace lang {
    EnumDefinition::EnumDefinition(ASTPtr &n)
        : LanguageDefinition(n)
    {
        m_name = m_node->getChild(0)->getToken().value;
    }

}
}