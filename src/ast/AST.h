#pragma once

// AST node class
#include <Token.h>
#include <iostream>
#include <memory>
#include <vector>

namespace zinc {
namespace lang {
    // use for shorter names -> no need for the whole name every time
    class AST;
    using ASTPtr = std::unique_ptr<AST>;

    enum class ASTType {
        Unknown = 0,
        Basic, // used for temp storage for words, numbers etc
        Operand, // expression operand
        Operator,
        VariableDef,
        ObjectDef,
        EnumDef,
        FunctionDef,
        FunctionCall,
        ArrayValue, // a[10]
        Return,
        Import,
        Namespace,
        If,
        Else,
        For,
        While,
    };

    // used for debugging and possibly in the future for error messages
    inline const char *ASTTypeNameMap[] = {
        "Unknown",
        "Basic",
        "Operand",
        "Operator",
        "VariableDef",
        "ObjectDef",
        "EnumDef",
        "FunctionDef",
        "FunctionCall",
        "ArrayValue",
        "Return",
        "Import",
        "Namespace",
        "If",
        "Else",
        "For",
        "While",
    };

    class AST {
    public:
        AST();
        AST(Token &tok, ASTType type, int nch);

        void setChild(int n, ASTPtr &node);
        ASTPtr &getChild(int n);

        void print(int ind);

        void setNext(ASTPtr &node);
        ASTPtr &getNext();

        Token &getToken();
        ASTType getType() const;

        int getChildrenCount() const;

        ~AST();

    private:
        Token m_token;
        ASTType m_type;
        ASTPtr m_next;
        std::vector<ASTPtr> m_children;
    };
} // namespace lang
} // namespace zinc