#include <pattern/PatternList.h>

namespace zinc {
namespace lang {
    PatternList::PatternList(std::initializer_list<Pattern *> pl)
        : m_patterns(pl)
    {
    }

    bool PatternList::matches(TokenIterator &beg, TokenIterator end)
    {
        bool retval = true;
        TokenIterator beg_tmp = beg;

        for (auto &pat : m_patterns) {
            if (!pat->matches(beg_tmp, end)) {
                retval = false;
                break;
            }
        }
        if (retval) {
            // shift iterator if all patterns recognized
            beg = beg_tmp;
        }
        return retval;
    }

    Pattern *PatternList::getPattern(int idx) const { return m_patterns[idx]; }
}
}