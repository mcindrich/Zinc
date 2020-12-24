#pragma once

#include "pattern/Pattern.h"

namespace zinc {
namespace lang {
    class ArrayValuePattern : public Pattern {
    public:
        bool matches(TokenIterator &beg, TokenIterator &end);
    };
}
}