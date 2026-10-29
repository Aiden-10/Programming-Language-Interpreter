// ast.h
//
// This file defines the Abstract Syntax Tree (AST) structure.
// The AST represents the source code as a hierarchy of expressions
// and statements, preserving the programs structure.
// These nodes are constructed by the parser and later processed
// by the interpreter to execute the program.

#pragma once

#include <string>
#include <memory>
#include <vector>

// --------------------------------
// Expression Node
// --------------------------------
// these nodes will produce a value

struct Expression {
    virtual ~Expression() = default;
};

struct NumberExpression : Expression {
    int value;

    NumberExpression(int value) : value(value) {}
};

struct IdentifierExpression : Expression {
    std::string name;

    IdentifierExpression(std::string name) : name(std::move(name)) {}
};

struct BinaryExpression : Expression {
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;
    char op;

    BinaryExpression(std::unique_ptr<Expression> left, char op, std::unique_ptr<Expression> right) : left(std::move(left)), op(op), right(std::move(right)) {}
};

// --------------------------------
// Statement Node
// --------------------------------
// these nodes will perform an action

struct Statement {
    virtual ~Statement() = default;
};

struct PrintStatement : Statement {
    std::unique_ptr<Expression> expression;

    explicit PrintStatement(std::unique_ptr<Expression> expr) : expression(std::move(expr)) {}
};

struct VariableDeclaration : Statement {
    std::string name;
    std::unique_ptr<Expression> initializer;

    VariableDeclaration(std::string name, std::unique_ptr<Expression> initializer) : name(std::move(name)), initializer(std::move(initializer)) {}
};

struct ExpressionStatement : Statement {
    std::unique_ptr<Expression> expression;

    explicit ExpressionStatement(std::unique_ptr<Expression> expr) : expression(std::move(expr)) {}
};