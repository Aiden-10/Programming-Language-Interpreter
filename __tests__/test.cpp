
#include <iostream>
#include <exception>
#include <string>

#include "test_lexer.h"
#include "test_parser.h"
#include "test_interpreter.h"

bool runTest(const std::string& name, void (*test)()) {
    try {
        test();
        std::cout << "[PASS] " << name << '\n';
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "[FAIL] " << name
                  << ": " << e.what() << '\n';
        return false;
    }
    catch (...) {
        std::cerr << "[FAIL] " << name
                  << ": Unknown exception\n";
        return false;
    }
}

int main() {
    int passed = 0;
    int failed = 0;

    auto run = [&](const std::string& name, void (*test)()) {
        if (runTest(name, test))
            ++passed;
        else
            ++failed;
    };

    // Lexer Tests
    run("Lexer identifiers", testLexerIdentifiers);
    run("Lexer numbers", testLexerNumbers);
    run("Lexer print", testLexerPrint);
    run("Lexer operators", testLexerOperators);
    run("Lexer whitespace", testLexerWhitespace);
    run("Lexer invalid character", testLexerInvalidCharacter);
    run("Lexer EOF", testLexerEOF);
    run("Lexer full program", testLexerFullProgram);

    // Parser Tests
    // run("Parser binary expression", testParserBinaryExpression);

    // Interpreter Tests
    // run("Interpreter addition", testInterpreterAddition);

    std::cout << "Passed: " << passed << " | Failed: " << failed << '\n';

    return failed == 0 ? 0 : 1;
}
