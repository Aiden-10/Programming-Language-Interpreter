#pragma once

#include <string>
#include <vector>

enum class ErrorStage {
    LEXER,
    PARSER,
    RUNTIME
};

enum class ErrorSeverity {
    WARNING,
    ERROR
};


struct Error {
    ErrorStage stage;
    ErrorSeverity severity;
    uint64_t line;
    uint64_t column;
    std::string reason;
};

class ErrorHandler {
private:
    std::vector<Error> errors;

    std::string getStageString(Error error) {
        switch (error.stage) {
        case ErrorStage::LEXER:
            return "[Lexer] ";
        case ErrorStage::PARSER:
            return "[Parser] ";
        case ErrorStage::RUNTIME:
            return "[Runtime] ";
        default:
            return "[UNKNOWN] ";
        }
    }

    std::string getSeverityString(Error error) {
        switch (error.severity) {
        case ErrorSeverity::WARNING:
            return "WARNING ";
        case ErrorSeverity::ERROR:
            return "ERROR ";
        default:
            return "ERROR ";
        }
    }

public:
    void report(Error error) {
        errors.push_back(std::move(error));
    }

    const std::vector<Error>& getErrors() const {
        return errors;
    }

    bool hasErrors() const {
        for (const auto& error : errors) {
            if (error.severity == ErrorSeverity::ERROR) {
                return true;
            }
        }

        return false;
    }

    void displayErrors() {
        for (const auto& error : errors) {
            std::cout << getStageString(error) 
                      << getSeverityString(error)
                      << "Line " << error.line << ": "
                      << error.reason 
                      << std::endl;
        }
    }
};