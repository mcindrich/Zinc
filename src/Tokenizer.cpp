#include <Token.h>
#include <Tokenizer.h>
#define ZINC_IS_DELIM(c)                                                       \
    (c == '#' || c == '^' || c == '$' || c == '=' || c == '-' || c == '+'      \
        || c == '%' || c == '/' || c == '*' || c == '&' || c == '|'            \
        || c == ';' || c == '\"' || c == '@' || c == '!' || c == '\''          \
        || c == '~' || c == '<' || c == '>' || c == '(' || c == ')'            \
        || c == '[' || c == ']' || c == '{' || c == '}' || c == ' '            \
        || c == '\t' || c == '\n' || c == '\r' || c == ',' || c == ':'         \
        || c == '.' || c == '`')

#define ZINC_IS_SPACE(c) (c == ' ' || c == '\t' || c == '\n' || c == '\r')
#define ZINC_LAST_TYPE_NEWLINE(t)                                              \
    (t == TokenType::Newline                                                   \
        || (t > TokenType::PARENTH_START && t < TokenType::PARENTH_END)        \
        || (t > TokenType::KW_START && t < TokenType::KW_END)                  \
        || t == TokenType::Comma)
#define ZINC_LEXER_DBG

#ifdef ZINC_LEXER_DBG
#include <iostream>
#endif

namespace zinc {
namespace lang {
    Tokenizer::Tokenizer() { }

    inline bool isDoubleToken(const std::string &INPUT, int pos);

    void Tokenizer::tokenize(std::string &input)
    {
        const std::string INPUT = input;
        splitIntoTokens(INPUT);

#ifdef ZINC_LEXER_DBG
        std::cout << ">> SPLIT_TOKENS" << std::endl;
        for (auto it = m_tokens.begin(); it != m_tokens.end(); it++) {
            std::cout << it->lineNumber << ": [\'" << it->value << "\', "
                      << (int)it->type << "]" << std::endl;
        }
        std::cout << ">> END SPLIT_TOKENS" << std::endl;
#endif
    }

    void Tokenizer::splitIntoTokens(const std::string &INPUT)
    {
        int lastToken = 0, lineNumber = 1;
        std::string sub;

        for (int i = 0; i < INPUT.length(); i++) {
            if (ZINC_IS_DELIM(INPUT[i])) {
                // first check for string and a comment
                if (INPUT[i] == '\"') {
                    // read string
                    int j = i + 1;
                    lastToken = i + 1;
                    for (; j < INPUT.length(); j++) {
                        if (INPUT[j] == '\"') {
                            break;
                        } else if (INPUT[j] == '\n') {
                            // throw exception => string unfinished and newline
                            // started
                        }
                    }
                    sub = INPUT.substr(lastToken, j - lastToken);
                    m_tokens.push_back(
                        Token(sub, TokenType::String, lineNumber));
                    i = j;
                } else if (INPUT[i] == '`') {
                    // comment, ignore the line
                    int curr = i + 1;
                    for (++i; i < INPUT.length() && INPUT[i] != '\n'; ++i)
                        ;
                    ++lineNumber;
                } else {
                    sub = INPUT.substr(lastToken, i - lastToken);
                    if (sub.length()) {
                        m_tokens.push_back(Token(sub, lineNumber));
                    }

                    if (!ZINC_IS_SPACE(INPUT[i])) {
                        if ((i < INPUT.length() - 1)
                            && isDoubleToken(INPUT, i)) {
                            std::string doubleToken;
                            doubleToken.reserve(2);
                            doubleToken += INPUT[i];
                            doubleToken += INPUT[i + 1];
                            ++i;
                            m_tokens.push_back(Token(doubleToken, lineNumber));
                        } else {
                            m_tokens.push_back(Token(INPUT[i], lineNumber));
                        }
                    } else {
                        if (INPUT[i] == '\n') {
                            if (m_tokens.size()
                                && !ZINC_LAST_TYPE_NEWLINE(
                                    m_tokens.back().type)) {
                                sub = "[NEW_LINE]";
                                m_tokens.push_back(
                                    Token(sub, TokenType::Newline, lineNumber));
                            }
                            ++lineNumber;
                        }
                    }
                }
                lastToken = i + 1;
            }
        }
        sub = INPUT.substr(lastToken, INPUT.size() - lastToken);
        if (sub.length()) {
            m_tokens.push_back(Token(sub, lineNumber));
        }

        // initialize the iterator after tokenization
        if (m_tokens.back().type != TokenType::Newline) {
            sub = "[NEW_LINE]";
            m_tokens.push_back(Token(sub, TokenType::Newline, lineNumber));
        }
        m_currentIterator = m_tokens.begin();
    }

    inline bool isDoubleToken(const std::string &INPUT, int pos)
    {
        bool ret = false;
        const std::string dt = INPUT.substr(pos, 2);

        if (dt == "<=" || dt == ">=" || dt == "<<" || dt == ">>" || dt == "!="
            || dt == "==" || dt == "&&" || dt == "||" || dt == "->"
            || ((dt[0] == '+' || dt[0] == '-' || dt[0] == '*' || dt[0] == '/')
                && dt[1] == '=')) {
            ret = true;
        }
        return ret;
    }

    TokenIterator &Tokenizer::getIterator() { return m_currentIterator; }
    TokenIterator Tokenizer::getEndingIterator() { return m_tokens.end(); }

}
}