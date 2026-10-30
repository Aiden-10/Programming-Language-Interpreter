#include <iostream>
#include <string>

#include "lexer.h"
#include "parser.h"
#include "interpreter.h"

int main() {
    std::string source =
        "let interest_rate = 10@;\n"
        "let price = 5%%;\n"
        "let z = interest_rate + price;\n"
        "print(z);\n"
        "print(10 + 5 * 2);\n"
        "print((10 + 5) * 2);\n"
        "print(20 / 5 + 3);\n"
        "print(20 / (5 + 5));\n"
        "print(10 - 6 / 2);\n"
        "print(2 + 3 * 4 - 8 / 2);\n"
        "print(20 / 5 / 2);\n"
        "print(8 - 3 - 2);\n"
        "print(z * 2 + price);";

    ErrorHandler errorHandler;
    Parser parser(source, errorHandler);

    auto ast = parser.parseProgram();

    if (!ast) {
        errorHandler.displayErrors();
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