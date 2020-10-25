#include <lang/Token.hpp>

namespace zinc {
namespace lang {
    static inline bool isNumber(std::string &s)
    {
        std::string::const_iterator it = s.begin();
        while (it != s.end() && std::isdigit(*it))
            ++it;
        return !s.empty() && it == s.end();
    }

    Token::Token(std::string &s, TokenType type, int ln)
        : value(s)
        , type(type)
        , lineNumber(ln)
    {
    }
    Token::Token(std::string &s, int ln)
        : value(s)
        , lineNumber(ln)
    {
        // check for keywords etc.
        if (s == "import") {
            type = TokenType::Import;
        } else if (s == "obj") {
            type = TokenType::Object;
        } else if (s == "fn") {
            type = TokenType::Function;
        } else if (s == "if") {
            type = TokenType::If;
        } else if (s == "else") {
            type = TokenType::Else;
        } else if (s == "for") {
            type = TokenType::For;
        } else if (s == "mod") {
            type = TokenType::Module;
        } else if (s == "enum") {
            type = TokenType::Enum;
        } else if (s == "->") {
            type = TokenType::Pointer;
        } else if (isNumber(s)) {
            type = TokenType::Number;
        } else {
            type = TokenType::Word;
        }
    }
    Token::Token(char c, int ln)
        : lineNumber(ln)
        , value(1, c)
    {
        switch (c) {
        case '.':
            type = TokenType::Dot;
            break;
        case ';':
            type = TokenType::Semicolon;
            break;
        case ':':
            type = TokenType::Colon;
            break;
        case ',':
            type = TokenType::Comma;
            break;
        case '(':
            type = TokenType::LParenth;
            break;
        case ')':
            type = TokenType::RParenth;
            break;
        case '[':
            type = TokenType::LBracket;
            break;
        case ']':
            type = TokenType::RBracket;
            break;
        case '{':
            type = TokenType::LBrace;
            break;
        case '}':
            type = TokenType::RBrace;
            break;
        case '@':
            type = TokenType::At;
            break;
        case '#':
            type = TokenType::Hash;
            break;
        case '+':
            type = TokenType::Plus;
            break;
        case '-':
            type = TokenType::Minus;
            break;
        case '*':
            type = TokenType::Star;
            break;
        case '/':
            type = TokenType::Slash;
            break;
        case '<':
            type = TokenType::LT;
            break;
        case '>':
            type = TokenType::GT;
            break;
        case '=':
            type = TokenType::Equal;
            break;
        default:
            type = TokenType::None;
            break;
        }
    }
}
}