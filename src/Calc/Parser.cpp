#include "spdlog/spdlog.h"
#include "tl/expected.hpp"
#include <Calc/Parser.h>

#include <memory>
#include <cassert>

#define ASSERT_HAS_VALUE_RETURN(value) do { if (!(value).has_value()) return (value); } while(0)


namespace Calc {

    Parser::ParseResult Parser::Parse(const std::vector<Token>& tokens) {
        Parser parser(tokens);
        auto res = parser.Term();
        ASSERT_HAS_VALUE_RETURN(res);

        if (parser.current_token_i < tokens.size()) {
            return tl::unexpected(Parser::Error("Unexpected token."));
        }

        return res;
    }

    Parser::ParseResult Parser::Term() {
        Parser::ParseResult expr = Factor();
        ASSERT_HAS_VALUE_RETURN(expr);

        while (MatchAnyToken({Token::Type::Add, Token::Type::Subtract})) {
            Token op = PeekToken(-1);

            Parser::ParseResult right = Factor();
            ASSERT_HAS_VALUE_RETURN(right);

            expr.value() = std::make_shared<BinaryExpression>(expr.value(), op, right.value());
        }

        return expr;
    }

    Parser::ParseResult Parser::Factor() {
        Parser::ParseResult expr = Unary();
        ASSERT_HAS_VALUE_RETURN(expr);

        while (MatchAnyToken({Token::Type::Multiply, Token::Type::Divide, Token::Type::Power, Token::Type::Modulo})) {
            Token op = PeekToken(-1);

            Parser::ParseResult right = Unary();
            ASSERT_HAS_VALUE_RETURN(right);

            expr.value() = std::make_shared<BinaryExpression>(expr.value(), op, right.value());
        }

        return expr;
    }

    Parser::ParseResult Parser::Unary() {
        if (MatchAnyToken({Token::Type::Subtract})) {
            Parser::ParseResult expr = Primary();
            ASSERT_HAS_VALUE_RETURN(expr);

            return std::make_shared<UnaryExpression>(Token(Token::Type::Subtract), expr.value());
        }

        auto expr = Primary();
        ASSERT_HAS_VALUE_RETURN(expr);

        if (MatchAnyToken({Token::Type::Factorial}))
            return std::make_shared<UnaryExpression>(Token(Token::Type::Factorial), expr.value());

        return expr;
    }

    Parser::ParseResult Parser::Primary() {
        if (MatchAnyToken({Token::Type::Number}))
            return std::make_shared<LiteralExpression>(PeekToken(-1));

        if (MatchAnyToken({Token::Type::Identifier})) {
            auto t = PeekToken(-1);
            double n = 0;
            // Reference: https://en.wikipedia.org/wiki/List_of_mathematical_constants#List
            switch (Hash(t.id.c_str())) {
                case Hash("e"):   n = 2.71828182845904523536; break;
                case Hash("Pi"):  n = 3.14159265358979323846; break;
                default:
                    return tl::unexpected(Parser::Error(fmt::format("Unknown identifier \"{}\"", t.id)));
            }

            return std::make_shared<LiteralExpression>(Token(n));
        }

        // FIXME: code duplication
        if (MatchAnyToken({Token::Type::OpenBracket})) {
            Parser::ParseResult expr = Term();
            ASSERT_HAS_VALUE_RETURN(expr);

            if (!MatchAnyToken({Token::Type::CloseBracket})) {
                return tl::unexpected(Parser::Error("Expected ')' token."));
            }

            return std::make_shared<GroupingExpression>(expr.value());;
        }
        else if (MatchAnyToken({Token::Type::StraightBracket})) {
            Parser::ParseResult expr = Term();
            ASSERT_HAS_VALUE_RETURN(expr);

            if (!MatchAnyToken({Token::Type::StraightBracket})) {
                return tl::unexpected(Parser::Error("Expected '|' closing bracket."));
            }

            return std::make_shared<AbsoluteExpression>(expr.value());
        }

        return tl::unexpected(Parser::Error("Expected a number or a parethesized expression."));
    }

    void Parser::Advance(int token_count) {
        current_token_i = std::clamp<std::size_t>(current_token_i + token_count, 0, tokens.size());
    }

    Token Parser::PeekToken(int offset) const {
        auto i = current_token_i + offset;
        assert(i >= 0 && i < tokens.size());
        return tokens[i];
    }

    bool Parser::MatchAnyToken(std::initializer_list<Token::Type> possible_matches) {
        if (possible_matches.size() == 0 || current_token_i >= tokens.size())
            return false;

        for (int i = 0; i < possible_matches.size(); i++)
            if (PeekToken().type == *(possible_matches.begin() + i)) {
                Advance();
                return true;
            }

        return false;
    }

}
