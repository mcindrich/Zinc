#pragma once

#include <string>

namespace zinc {
namespace lang {
    enum class TokenType {
        // basic ones
        None = 0,
        Word,
        String,
        Newline,
        Number,
        Comment,
        At,
        Hash,
        // all parenthesis types
        LParenth,
        RParenth,
        LBrace,
        RBrace,
        LBracket,
        RBracket,
        // operators and separators
        Semicolon,
        Colon,
        Dot,
        Comma,
        Plus,
        Minus,
        Star,
        Slash,
        LT,
        GT,
        LTE,
        GTE,
        EQ, // ==
        ShiftL,
        ShiftR,
        Pointer,
        Equal, // =
        // keywords
        Enum,
        Object,
        Function,
        If,
        Else,
        For,
        Module,
        Import
    };
    struct Token {
        std::string value;
        TokenType type;
        int lineNumber;

        Token(std::string &s, TokenType type, int ln);
        Token(std::string &s, int ln);
        Token(char c, int ln);
    };
}
}