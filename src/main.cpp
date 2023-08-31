#include <stdio.h>
#include <spdlog/spdlog.h>

#include <Calc/Lexer.h>
#include <Calc/Token.h>

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
        return -1;
    }

    for (auto token : tokens.value()) {
        if (token.type == Calc::Token::Type::Number)
            SPDLOG_TRACE("{}({})", Calc::Token::Names[(int)token.type], token.number);
        else
            SPDLOG_TRACE(Calc::Token::Names[(int)token.type]);
    }
}
