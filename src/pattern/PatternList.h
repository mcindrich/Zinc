#pragma once

#include <pattern/Pattern.h>
#include <initializer_list>
#include <list>

namespace zinc {
namespace lang {
    class PatternList {
    public:
        PatternList(std::initializer_list<Pattern *> pl);

        bool matches(TokenIterator &curr, TokenIterator end);

        Pattern *getPattern(int idx) const;

    private:
        std::vector<Pattern *> m_patterns;
    };
}
}