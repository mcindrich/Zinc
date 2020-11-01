#pragma once

#include <lang/pattern/Pattern.hpp>
#include <initializer_list>
#include <list>

namespace zinc {
namespace lang {
    class PatternList {
    public:
        PatternList(std::initializer_list<Pattern *> pl, TokenIterator &curr,
            TokenIterator end);

        bool matches();

    private:
        std::list<Pattern *> m_patterns;
        TokenIterator &m_currIterator, m_endIterator;
    };
}
}