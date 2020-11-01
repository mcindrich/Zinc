#include <lang/pattern/PatternList.hpp>

namespace zinc {
namespace lang {
    PatternList::PatternList(std::initializer_list<Pattern *> pl,
        TokenIterator &curr, TokenIterator end)
        : m_patterns(pl)
        , m_currIterator(curr)
        , m_endIterator(end)
    {
    }

    bool PatternList::matches()
    {
        bool retval = true;
        for (auto &i : m_patterns) {
            if (!i->matches(m_currIterator, m_endIterator)) {
                retval = false;
                break;
            }
        }
        return retval;
    }
}
}