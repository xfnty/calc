#include <memory>
#include <stdio.h>
#include <string.h>
#include <filesystem>

#include <fmt/std.h>
#include <fmt/format.h>
#include <linenoise.hpp>
#include <spdlog/spdlog.h>

#include <Calc/Util.h>
#include <Calc/Token.h>
#include <Calc/Lexer.h>
#include <Calc/Parser.h>
#include <Calc/Expression.h>
#include <Calc/ExpressionFormatter.h>
#include <Calc/ExpressionEvaluator.h>

using namespace Calc;


bool Evaluate(const std::string& input);

int main(int argc, char const* argv[]) {
    if (argc <= 1 || argc > 2) {
        SPDLOG_INFO("Usage: calc [-i]");
        return 0;
    }

    if (strcmp(argv[1], "-i") == 0) {
        linenoise::SetHistoryMaxLen(32);

        std::string line;
        bool should_quit = false;
        while (!(should_quit = linenoise::Readline("> ", line))) {
            Evaluate(line);
            linenoise::AddHistory(line.c_str());
        }

        return 0;
    }

    return !Evaluate(argv[1]);
}

bool Evaluate(const std::string& input) {
#ifndef NDEBUG
    SPDLOG_DEBUG("expression=\"{}\"", input);
#endif

    auto tokens = Lexer::Tokenize(input);
    if (!tokens.has_value()) {
        SPDLOG_ERROR(tokens.error().description);
        printf("| %s\n| ", tokens.error().source.c_str());
        for (int i = 0; i < tokens.error().position; i++)
            printf(" ");
        printf("^\n");
        return false;
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
        SPDLOG_ERROR(root.error().description);
        return false;
    }

#ifndef NDEBUG
    SPDLOG_DEBUG("ast={}", ExpressionFormatter::Format(root.value()));
#endif

    auto eval_result = ExpressionEvaluator::Evaluate(root.value());
    if (!eval_result.has_value()) {
        SPDLOG_ERROR(eval_result.error().description);
        return false;
    }

    SPDLOG_TRACE(eval_result.value());
    return true;
}
