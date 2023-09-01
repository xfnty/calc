#include <stdio.h>

#include <spdlog/spdlog.h>
#include <fmt/format.h>

#include <Calc/Lexer.h>
#include <Calc/Token.h>
#include <Calc/Parser.h>


int main(int argc, char const* argv[]) {
    if (argc < 2) {
        SPDLOG_TRACE("Usage: calc <expression>");
        return 0;
    }

    std::string expression;
    for (int i = 1; i < argc; i++) {
        expression += argv[i];
        expression += (i < argc - 1) ? " " : "";
    }
    SPDLOG_DEBUG("expression=\"{}\"", expression);

    Calc::Lexer lexer;
    auto tokens = lexer.Process(expression);
    if (!tokens.has_value()) {
        SPDLOG_ERROR(tokens.error().description);
        printf("| %s\n| ", tokens.error().source.c_str());
        for (int i = 0; i < tokens.error().position; i++)
            printf(" ");
        printf("^\n");
        return 1;
    }

    std::string tokens_repr = "[";
    for (int i = 0; i < tokens.value().size(); i++) {
        auto token = tokens.value()[i];

        if (token.type == Calc::Token::Type::Number)
            tokens_repr += fmt::format("{}({})", Calc::Token::Names[(int)token.type], token.number);
        else
            tokens_repr += Calc::Token::Names[(int)token.type];

        if (i + 1 < tokens.value().size())
            tokens_repr += ", ";
    }
    tokens_repr += "]";
    SPDLOG_DEBUG("tokens={}", tokens_repr);

    Calc::Parser parser;
    auto ast = parser.Process(tokens.value());
    if (!ast.has_value()) {
        SPDLOG_ERROR(ast.error().description);
        return 2;
    }
}
