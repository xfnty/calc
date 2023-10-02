#include <Calc/Parser.h>

#include <cassert>

#include <spdlog/spdlog.h>

#include <Calc/Util.h>


namespace Calc {

    Parser::ParseResult Parser::Parse(const std::vector<Token>& tokens) {
        Parser parser(tokens);
        auto res = parser.Term();
        ASSERT_HAS_VALUE_PROPAGATE(res);

        if (parser.current_token_i < tokens.size()) {
            return tl::unexpected(Parser::Error("Unexpected token."));
        }

        return res;
    }

    Parser::ParseResult Parser::Term() {
        Parser::ParseResult expr = Factor();
        ASSERT_HAS_VALUE_PROPAGATE(expr);

        while (MatchAnyToken({Token::Type::Add, Token::Type::Subtract})) {
            Token op = PeekToken(-1);

            Parser::ParseResult right = Factor();
            ASSERT_HAS_VALUE_PROPAGATE(right);

            expr.value() = std::make_shared<BinaryExpression>(expr.value(), op, right.value());
        }

        return expr;
    }

    Parser::ParseResult Parser::Factor() {
        Parser::ParseResult expr = Unary();
        ASSERT_HAS_VALUE_PROPAGATE(expr);

        while (MatchAnyToken({Token::Type::Multiply, Token::Type::Divide, Token::Type::Power, Token::Type::Modulo})) {
            Token op = PeekToken(-1);

            Parser::ParseResult right = Unary();
            ASSERT_HAS_VALUE_PROPAGATE(right);

            expr.value() = std::make_shared<BinaryExpression>(expr.value(), op, right.value());
        }

        return expr;
    }

    Parser::ParseResult Parser::Unary() {
        if (MatchAnyToken({Token::Type::Subtract})) {
            Parser::ParseResult expr = Primary();
            ASSERT_HAS_VALUE_PROPAGATE(expr);

            return std::make_shared<UnaryExpression>(Token(Token::Type::Subtract), expr.value());
        }

        auto expr = Primary();
        ASSERT_HAS_VALUE_PROPAGATE(expr);

        if (MatchAnyToken({Token::Type::Factorial}))
            return std::make_shared<UnaryExpression>(Token(Token::Type::Factorial), expr.value());

        return expr;
    }

    Parser::ParseResult Parser::Primary() {
        if (MatchAnyToken({Token::Type::Number, Token::Type::Identifier}))
            return std::make_shared<LiteralExpression>(PeekToken(-1));

        // FIXME: code duplication
        if (MatchAnyToken({Token::Type::OpenBracket})) {
            Parser::ParseResult expr = Term();
            ASSERT_HAS_VALUE_PROPAGATE(expr);

            if (!MatchAnyToken({Token::Type::CloseBracket})) {
                return tl::unexpected(Parser::Error("Expected ')' token."));
            }

            return std::make_shared<GroupingExpression>(expr.value());;
        }
        else if (MatchAnyToken({Token::Type::StraightBracket})) {
            Parser::ParseResult expr = Term();
            ASSERT_HAS_VALUE_PROPAGATE(expr);

            if (!MatchAnyToken({Token::Type::StraightBracket})) {
                return tl::unexpected(Parser::Error("Expected '|' closing bracket."));
            }

            return std::make_shared<AbsoluteExpression>(expr.value());
        }

        return tl::unexpected(Parser::Error("Expected a literal or a parethesized expression."));
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
