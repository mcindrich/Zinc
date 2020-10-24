#pragma once

#include <string>

namespace zinc {
namespace lang {
    enum class TokenType {
        // basic ones
        None = 0,
        Word,
        Space,
        Newline,
        String,
        Number,
        Comment,
        // all parenthesis types
        LParenth,
        RParenth,
        LBrace,
        RBrace,
        LBracket,
        RBracket,
        // operators and separators
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
        Obj,
        Fn,
        If,
        Else,
        For,
        Module,
        Import
    };
    struct Token {
        std::string value;
        TokenType type;
    };
}
}