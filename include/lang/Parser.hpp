#pragma once

#include <lang/Tokenizer.hpp>

namespace zinc {
namespace lang {
    class Parser {
    public:
        Parser();

        void parseFile(char *fname);

    private:
        Tokenizer m_tokenizer;
    };
}
}