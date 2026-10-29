// interpreter.h
//
// This file is responsible for interpreting the AST.
// The interpreter executes statements and evaluates expressions
// to produce the program's runtime behavior.

#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

#include "ast.h"

class Interpreter {
private:
    std::unordered_map<std::string, int> variables;

public:
    void execute(const Program& program) {
        for (const auto& statement : program.statements) {
            executeStatement(*statement);
        }
    }

private:
    void executeStatement(const Statement& statement) {
        if (const auto* declaration = dynamic_cast<const VariableDeclaration*>(&statement)) {
            // Execute
            int value = evaluateExpression(*declaration->initializer);
            // Add/update variable in our map
            variables[declaration->name] = value;
        }
        else if (const auto* print = dynamic_cast<const PrintStatement*>(&statement)) {
            // Execute print
            int value = evaluateExpression(*print->expression);
            std::cout << value << std::endl;
        }

    }

    int evaluateExpression(const Expression& expression) {
        if (const auto& number = dynamic_cast<const NumberExpression*>(&expression)) {
            return number->value;
        }
        else if (const auto& identifier = dynamic_cast<const IdentifierExpression*>(&expression)) {
            if (!variables.contains(identifier->name))
                throw std::runtime_error("Variable does not exist");

            return variables[identifier->name];
        }
        else if (const auto* binary = dynamic_cast<const BinaryExpression*>(&expression)) {
            int left = evaluateExpression(*binary->left);
            int right = evaluateExpression(*binary->right);

            switch (binary->op) {
                case '+':
                    return left + right;
                case '-':
                    return left - right;
                case '*':
                    return left * right;
                case '/':
                    if (right == 0)
                        throw std::runtime_error("Divide by zero");

                    return left / right;

                default:
                    throw std::runtime_error("Unknown Expression");
            }
        }
    }
};