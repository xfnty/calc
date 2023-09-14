#include <memory>
#include <stdio.h>
#include <filesystem>

#include <fmt/std.h>
#include <fmt/format.h>
#include <spdlog/spdlog.h>

#include <Calc/Lexer.h>
#include <Calc/Token.h>
#include <Calc/AST/Expression.h>
#include <Calc/AST/ExpressionVisitor.h>
#include <Calc/AST/ExpressionVisitors/ASTPrinter.h>

using namespace Calc;
using namespace AST;
using namespace ExpressionVisitors;


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
    SPDLOG_DEBUG("expression=\"{}\"", expression);

    auto tokens = Lexer::Tokenize(expression);
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

        if (token.type == Token::Type::Number)
            tokens_repr += fmt::to_string(token.number);
        else
            tokens_repr += Token::Names[(int)token.type];

        if (i + 1 < tokens.value().size())
            tokens_repr += ", ";
    }
    tokens_repr += "]";
    SPDLOG_DEBUG("tokens={}", tokens_repr);

    // WTF: temporary values "expire" (probably) during the execution
    auto sample_expr = *(new BinaryExpression(
        *(new LiteralExpression(Token(2))),
        Token::Type::Add,
        *(new GroupingExpression(
            *(new BinaryExpression(
                *(new UnaryExpression(
                    Token::Type::Subtract,
                    *(new LiteralExpression(Token(10)))
                )),
                Token(Token::Type::Divide),
                *(new LiteralExpression(
                    Token(5)
                ))
            ))
        ))
    ));

    ASTPrinter ast_printer;
    sample_expr.Accept(ast_printer);
    SPDLOG_DEBUG("ast=({})", ast_printer.GetBuffer());
}
