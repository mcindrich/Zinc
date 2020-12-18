#pragma once

#include <lang/pattern/Pattern.hpp>

namespace zinc {
namespace lang {
    class FunctionCallPattern : public Pattern {
    public:
        bool matches(TokenIterator &beg, TokenIterator &end);
    };
}
}