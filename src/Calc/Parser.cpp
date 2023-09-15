#include <Calc/Parser.h>

#include <algorithm>
#include "Calc/Expression.h"
#include "Calc/Token.h"
#include "tl/expected.hpp"

#define ASSERT_RETURN(cond, x, value) do { if (!(cond)) { SPDLOG_DEBUG("{}", (x)); return (value);} } while(0)


namespace Calc {

    tl::expected<Expression*, Parser::Error> Parser::Parse(const std::vector<Token>& tokens) {
        Parser parser(tokens);

        Expression* expr = parser.Term();
        if (expr == nullptr)
            return tl::unexpected(Parser::Error());

        return expr;
    }

    Expression* Parser::Term() {
        Expression* expr = Factor();
        ASSERT_RETURN(expr != nullptr, 1, nullptr);

        while (MatchAnyToken({Token::Type::Add, Token::Type::Subtract})) {
            Token op = PeekToken(-1);

            Expression* right = Factor();
            ASSERT_RETURN(right != nullptr, 2, nullptr);

            expr = new BinaryExpression(expr, op, right);  // FIXME: *new*
        }

        return expr;
    }

    Expression* Parser::Factor() {
        Expression* expr = Unary();
        ASSERT_RETURN(expr != nullptr, 3, nullptr);

        while (MatchAnyToken({Token::Type::Multiply, Token::Type::Divide})) {
            Token op = PeekToken(-1);

            Expression* right = Unary();
            ASSERT_RETURN(right != nullptr, 4, nullptr);

            expr = new BinaryExpression(expr, op, right);
        }

        return expr;
    }

    Expression* Parser::Unary() {
        if (MatchAnyToken({Token::Type::Subtract})) {
            Expression* expr = Primary();
            ASSERT_RETURN(expr != nullptr, 5, nullptr);

            return new UnaryExpression(Token(Token::Type::Subtract), expr);
        }

        Expression* expr = Primary();
        ASSERT_RETURN(expr != nullptr, 6, nullptr);
        return expr;
    }

    Expression* Parser::Primary() {
        if (MatchAnyToken({Token::Type::Number}))
            return new LiteralExpression(PeekToken(-1));

        if (MatchAnyToken({Token::Type::OpenBracket})) {
            Expression* expr = Term();
            ASSERT_RETURN(expr != nullptr, 7, nullptr);
            ASSERT_RETURN(MatchAnyToken({Token::Type::CloseBracket}), 8, nullptr);
            return expr;
        }

        ASSERT_RETURN(false, 9, nullptr);
    }

    void Parser::Advance(int token_count) {
        current_token_i = std::clamp<std::size_t>(current_token_i + token_count, 0, tokens.size());
    }

    Token Parser::PeekToken(int offset) const {
        return tokens[std::clamp<std::size_t>(current_token_i + offset, 0, tokens.size())];
    }

    bool Parser::MatchAnyToken(std::initializer_list<Token::Type> possible_matches) {
        if (possible_matches.size() == 0 || tokens.size() == 0)
            return false;

        for (int i = 0; i < possible_matches.size(); i++)
            if (PeekToken().type == *(possible_matches.begin() + i)) {
                Advance();
                return true;
            }

        return false;
    }

}
