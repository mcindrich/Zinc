#pragma once

#include <pattern/Pattern.h>

namespace zinc {
namespace lang {
    class FunctionCallPattern : public Pattern {
    public:
        bool matches(TokenIterator &beg, TokenIterator &end);
    };
}
}