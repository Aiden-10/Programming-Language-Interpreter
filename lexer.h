// lexer.h
// 
// This file is responsible for lexical analysis.
// The lexer transforms source code into a sequence of tokens.
// These tokens represent the basic building blocks of the language,
// such as keywords, identifiers, numbers, and operators.
// The parser then uses these tokens to analyze the programs syntax.

#pragma once

#include <vector>
#include <stdexcept>

enum class TokenType {
    // Keywords
    LET,
    PRINT,

    // Literals and identifiers
    IDENTIFIER,
    NUMBER,

    // Operators
    PLUS,
    MINUS,
    STAR,
    SLASH,
    EQUAL,

    // Punctuation
    LEFT_PAREN,
    RIGHT_PAREN,
    SEMICOLON,

    // Special
    END_OF_FILE,
    INVALID
};

struct Token {
    TokenType type;
    std::string_view value;
};

class Lexer {
private:
    std::string_view source;
    size_t current = 0;

public:
    Lexer(std::string_view source) : source(source) {};

    Token nextToken() {
        Token token = {};

        // Remove whitespace
        while (current < source.size() && std::isspace(source[current])) {
            current++;
        }

        // Check EOF
        if (current >= source.size()) {
            token.value = "";
            token.type = TokenType::END_OF_FILE;
            return token;
        }

        // Check punctuation
        if (current < source.size() && 
            (source[current] == '(' || 
             source[current] == ')' ||
             source[current] == ';')
            ) {
            switch (source[current]) {
            case ')': {
                token.type = TokenType::RIGHT_PAREN;
                break;
            }
            case '(': {
                token.type = TokenType::LEFT_PAREN;
                break;
            }
            case ';': {
                token.type = TokenType::SEMICOLON;
                break;
            }
            default:
                token.type = TokenType::INVALID;
            }
            token.value = source.substr(current, 1);
            current++;
            return token;
        }

        // Check operators
        if (current < source.size() && 
            (source[current] == '+'  || 
             source[current] == '-'  ||
             source[current] == '='  ||
             source[current] == '*'  ||
             source[current] == '/')
            ) {
            // Get operator type
            switch (source[current]) {
            case '+': {
                token.type = TokenType::PLUS;
                break;
            }
            case '-': {
                token.type = TokenType::MINUS;
                break;
            }
            case '=': {
                token.type = TokenType::EQUAL;
                break;
            }
            case '*': {
                token.type = TokenType::STAR;
                break;
            }
            case '/': {
                token.type = TokenType::SLASH;
                break;
            }
            default:
                token.type = TokenType::INVALID;
            }
            token.value = source.substr(current, 1);
            current++;
            return token;
        }

        // Check numbers
        if (std::isdigit(source[current])) {
            size_t initial_index = current;
            // Scan whole number
            while (current < source.size() && std::isdigit(source[current])) {
                current++;
            }
            token.value = source.substr(initial_index, current - initial_index);
            token.type = TokenType::NUMBER;
            return token;
        }

        // Check keywords and identifiers
        if (std::isalpha(static_cast<unsigned char>(source[current])) ||
            source[current] == '_') {

            size_t initial_index = current;

            while (current < source.size() &&
                (std::isalnum(static_cast<unsigned char>(source[current])) ||
                    source[current] == '_')) {
                current++;
            }

            token.value = source.substr(initial_index, current - initial_index);

            if (token.value == "let") {
                token.type = TokenType::LET;
            }
            else if (token.value == "print") {
                token.type = TokenType::PRINT;
            }
            else {
                token.type = TokenType::IDENTIFIER;
            }

            return token;
        }

        throw std::runtime_error(
            "Invalid character: " + std::string(source.substr(current, 1))
        );
    }

    // return the full program back tokenized
    std::vector<Token> tokenize() {
        std::vector<Token> tokens;
        
        while (true) {
            Token token = nextToken();
            tokens.push_back(token);

            if (token.type == TokenType::END_OF_FILE) {
                break;
            }
        }

        return tokens;
    }
};

std::string_view tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::LET:         return "LET";
        case TokenType::PRINT:       return "PRINT";
        case TokenType::IDENTIFIER:  return "IDENTIFIER";
        case TokenType::NUMBER:      return "NUMBER";
        case TokenType::PLUS:        return "PLUS";
        case TokenType::MINUS:       return "MINUS";
        case TokenType::STAR:        return "STAR";
        case TokenType::SLASH:       return "SLASH";
        case TokenType::EQUAL:       return "EQUAL";
        case TokenType::LEFT_PAREN:  return "LEFT_PAREN";
        case TokenType::RIGHT_PAREN: return "RIGHT_PAREN";
        case TokenType::SEMICOLON:   return "SEMICOLON";
        case TokenType::END_OF_FILE: return "EOF";
        case TokenType::INVALID:     return "INVALID";
        default:                     return "UNKNOWN";
    }
}

