#pragma once

#include <lang/Tokenizer.hpp>

namespace zinc {
namespace lang {
    class Parser {
    public:
        Parser();

    private:
        Tokenizer m_tokenizer;
    };
}
}