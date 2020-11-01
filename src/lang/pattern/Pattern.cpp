#include <lang/pattern/Pattern.hpp>

namespace zinc {
namespace lang {
    std::unique_ptr<AST> &Pattern::getNode() { return m_node; }
}
}