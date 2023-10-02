#include <memory>
#include <stdio.h>
#include <filesystem>

#include <fmt/std.h>
#include <fmt/format.h>
#include <spdlog/spdlog.h>

#include <Calc/Token.h>
#include <Calc/Lexer.h>
#include <Calc/Parser.h>
#include <Calc/Expression.h>
#include <Calc/ExpressionFormatter.h>

using namespace Calc;


int main(int argc, char const* argv[]) {
    if (argc < 2) {
        SPDLOG_TRACE(
            "Usage: {} <expression>",
            std::filesystem::path(argv[0]).filename().stem()
        );
        return 0;
    }

    std::string expression;
    for (int i = 1; i < argc; i++) {
        expression += argv[i];
        expression += (i < argc - 1) ? " " : "";
    }

#ifndef NDEBUG
    SPDLOG_DEBUG("expression=\"{}\"", expression);
#endif

    auto tokens = Lexer::Tokenize(expression);
    if (!tokens.has_value()) {
        SPDLOG_ERROR(tokens.error().description);
        printf("| %s\n| ", tokens.error().source.c_str());
        for (int i = 0; i < tokens.error().position; i++)
            printf(" ");
        printf("^\n");
        return 1;
    }

#ifndef NDEBUG
    std::string tokens_repr = "[";
    for (int i = 0; i < tokens.value().size(); i++) {
        auto token = tokens.value()[i];

        tokens_repr += token.ToString();

        if (i + 1 < tokens.value().size())
            tokens_repr += ", ";
    }
    tokens_repr += "]";
    SPDLOG_DEBUG("tokens={}", tokens_repr);
#endif

    auto root = Parser::Parse(tokens.value());
    if (!root.has_value()) {
        SPDLOG_ERROR("{}", root.error().description);
        return 2;
    }

#ifndef NDEBUG
    SPDLOG_DEBUG("ast={}", ExpressionFormatter::Format(root.value()));
#endif

    return 0;
}
