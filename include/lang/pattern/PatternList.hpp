#pragma once

#include <pattern/Pattern.hpp>
#include <initializer_list>
#include <list>

namespace zinc {
namespace lang {
    class PatternList {
    public:
        PatternList(std::initializer_list<Pattern> &pl);

    private:
        std::list<Pattern> m_patterns;
    };
}
}