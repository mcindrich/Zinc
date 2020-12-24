#pragma once

#include "Token.h"
#include "Tokenizer.h"
#include <exception>
#include <sstream>
#include <stdexcept>

namespace zinc {
    namespace lang {
        class PatternNotFoundException : public std::exception {
            public:
                PatternNotFoundException(TokenIterator b, TokenIterator e):m_beg(b), m_end(e) {
                    std::stringstream ss;
                    ss << "Pattern not found at line " << m_beg->lineNumber << ": \n";
                    ss << '\t';

                    // add to buffer all tokens from the same line
                    while(m_beg != m_end && m_beg->type != TokenType::Newline) {
                        ss << m_beg->value << " ";
                        m_beg++;
                    }

                    ss << '\n';

                    m_val = ss.str();
                }

                const char *what() const noexcept {
                    return m_val.c_str();
                }
                
            private:
                std::string m_val;
                TokenIterator m_beg;
                TokenIterator m_end;
        };
    }
}