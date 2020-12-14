#pragma once

// AST node class
#include <lang/Token.hpp>
#include <vector>
#include <memory>
#include <iostream>

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
        Return,
        Import,
        Namespace,
        If,
        Else,
        For,
        While,
    };

    class AST {
    public:
        AST();
        AST(Token &tok, ASTType type, int nch);

        void setChild(int n, ASTPtr &node);
        ASTPtr &getChild(int n);

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
}
}