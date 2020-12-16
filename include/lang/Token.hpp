#pragma once

#include <string>

namespace zinc {
namespace lang {
    enum class TokenType {
        // basic ones
        BASIC_START,
        None = 0,
        Word,
        String,
        Newline,
        Number,
        Comment,
        At,
        Hash,
        BASIC_END,
        // all parenthesis types
        PARENTH_START,
        LParenth,
        RParenth,
        LBrace,
        RBrace,
        LBracket,
        RBracket,
        PARENTH_END,
        // operators and separators
        OP_START,
        Semicolon,
        Comma,
        Pointer, // ->
        Colon,
        Dot,
        LT,
        GT,
        LTE,
        GTE,
        EQ, // ==
        ShiftL,
        ShiftR,
        Equal, // =
        Plus,
        Minus,
        Star,
        Slash,
        OP_END,
        // keywords
        KW_START,
        Enum,
        Object,
        Function,
        If,
        Else,
        For,
        Module,
        Import,
        KW_END
    };
    struct Token {
        std::string value;
        TokenType type;
        int lineNumber;
        Token();
        Token(std::string &s, TokenType type, int ln);
        Token(std::string &s, int ln);
        Token(char c, int ln);
    };
}
}