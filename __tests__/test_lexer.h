#pragma once

#include <stdexcept>
#include <vector>
#include "../lexer.h"

#define ERROR(msg) std::runtime_error(std::string("") + (msg))

inline void testLexerIdentifiers() {
    Lexer lexer("let x = 10;");

    std::vector<Token> tokens = lexer.tokenize();

    if (tokens.size() != 6) {
        throw ERROR("Expected 6 tokens including EOF");
    }

    if (tokens.at(1).value != "x" && tokens.at(1).type != TokenType::IDENTIFIER) {
        throw ERROR("Expected identifier 'x'");
    }
}

inline void testLexerNumbers() {
    Lexer lexer("let x = 10;");

    std::vector<Token> tokens = lexer.tokenize();

    if (tokens.size() != 6) {
        throw ERROR("Expected 6 tokens including EOF");
    }

    if (tokens.at(3).value != "10" && tokens.at(3).type != TokenType::NUMBER) {
        throw ERROR("Expected number '10'");
    }
}

inline void testLexerPrint() {
    Lexer lexer("print(x);");

    std::vector<Token> tokens = lexer.tokenize();

    if (tokens.size() != 6) {
        throw ERROR("Expected 6 tokens including EOF");
    }

    if (tokens.at(0).type != TokenType::PRINT       ||
        tokens.at(1).type != TokenType::LEFT_PAREN  ||
        tokens.at(2).type != TokenType::IDENTIFIER  ||
        tokens.at(3).type != TokenType::RIGHT_PAREN || 
        tokens.at(4).type != TokenType::SEMICOLON   ||
        tokens.at(5).type != TokenType:: END_OF_FILE) {
        throw ERROR("Incorrect print statement tokens");
    }
}

inline void testLexerOperators() {
    Lexer lexer("3 + 5 - 10;");

    std::vector<Token> tokens = lexer.tokenize();

    if (tokens.size() != 7) {
        throw std::runtime_error("Expected 7 tokens including EOF");
    }

    if (tokens.at(1).type != TokenType::PLUS ||
        tokens.at(3).type != TokenType::MINUS) {
        throw ERROR("Incorrect operator tokens");
    }
}

inline void testLexerWhitespace() {
    Lexer lexer("let     y =   3;");

    std::vector<Token> tokens = lexer.tokenize();

    if (tokens.size() != 6) {
        throw ERROR("Expected 6 tokens including EOF");
    }

    if (tokens.at(0).type != TokenType::LET         ||
        tokens.at(1).type != TokenType::IDENTIFIER  || 
        tokens.at(2).type != TokenType::EQUAL       ||
        tokens.at(3).type != TokenType::NUMBER      ||
        tokens.at(4).type != TokenType::SEMICOLON   ||
        tokens.at(5).type != TokenType::END_OF_FILE) {
        throw ERROR("Incorrect whitespace handling");
    }
}   

inline void testLexerInvalidCharacter() {
    Lexer lexer("let x = @;");

    bool threw = false;

    try {
        lexer.tokenize();
    }
    catch (const std::runtime_error&) {
        threw = true;
    }

    if (!threw) {
        throw ERROR("Expected error for invalid character '@'");
    }
}

inline void testLexerEOF() {
    Lexer lexer(" \t\n");

    std::vector<Token> tokens = lexer.tokenize();

    if (tokens.size() != 1) {
        throw ERROR("Expected only EOF token");
    }

    if (tokens.at(0).type != TokenType::END_OF_FILE) {
        throw ERROR("Expected EOF token");
    }
}

inline void testLexerFullProgram() {
    Lexer lexer(
        "let interest_rate = 10;\n"
        "let price = 5;\n"
        "let z = interest_rate + price;\n"
        "print(z);"
    );

    std::vector<Token> tokens = lexer.tokenize();

    std::vector<TokenType> expected = {
        TokenType::LET,
        TokenType::IDENTIFIER,
        TokenType::EQUAL,
        TokenType::NUMBER,
        TokenType::SEMICOLON,

        TokenType::LET,
        TokenType::IDENTIFIER,
        TokenType::EQUAL,
        TokenType::NUMBER,
        TokenType::SEMICOLON,

        TokenType::LET,
        TokenType::IDENTIFIER,
        TokenType::EQUAL,
        TokenType::IDENTIFIER,
        TokenType::PLUS,
        TokenType::IDENTIFIER,
        TokenType::SEMICOLON,

        TokenType::PRINT,
        TokenType::LEFT_PAREN,
        TokenType::IDENTIFIER,
        TokenType::RIGHT_PAREN,
        TokenType::SEMICOLON,
        TokenType::END_OF_FILE
    };

    if (tokens.size() != expected.size()) {
        throw ERROR("Incorrect number of tokens");
    }

    for (size_t i = 0; i < expected.size(); i++) {
        if (tokens.at(i).type != expected.at(i)) {
            throw ERROR("Incorrect token type at index " + std::to_string(i));
        }
    }

    if (tokens.at(1).value != "interest_rate" ||
        tokens.at(3).value != "10"            ||
        tokens.at(6).value != "price"         ||
        tokens.at(8).value != "5"             ||
        tokens.at(11).value != "z"            ||
        tokens.at(13).value != "interest_rate"||
        tokens.at(15).value != "price"        ||
        tokens.at(19).value != "z") {
        throw ERROR("Incorrect token values");
    }
}