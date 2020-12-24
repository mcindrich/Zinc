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
        "ASTType::Unknown",
        "ASTType::Basic",
        "ASTType::Operand",
        "ASTType::Operator",
        "ASTType::VariableDef",
        "ASTType::ObjectDef",
        "ASTType::EnumDef",
        "ASTType::FunctionDef",
        "ASTType::FunctionCall",
        "ASTType::Return",
        "ASTType::Import",
        "ASTType::Namespace",
        "ASTType::If",
        "ASTType::Else",
        "ASTType::For",
        "ASTType::While",
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