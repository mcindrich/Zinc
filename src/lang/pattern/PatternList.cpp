#include <lang/pattern/PatternList.hpp>

namespace zinc {
namespace lang {
    PatternList::PatternList(std::initializer_list<Pattern> &pl)
        : m_patterns(pl)
    {
    }
}
}