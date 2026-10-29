#include <iostream>
#include <string>

#include "lexer.h"
#include "parser.h"
#include "interpreter.h"

int main() {
    std::string source =
        "let interest_rate = 10;\n"
        "let price = 5;\n"
        "let z = interest_rate + price;\n"
        "print(z);";

    Parser parser(source);

    auto ast = parser.parseProgram();

    if (!ast) {
        std::cerr << "Parsing failed!\n";
        return 1;
    }

    try {
        Interpreter interpreter;
        interpreter.execute(*ast);
    }
    catch (const std::exception& error) {
        std::cerr << "Runtime error: " << error.what() << '\n';
        return 1;
    }

    return 0;
}