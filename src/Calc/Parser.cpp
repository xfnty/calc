#include <Calc/Parser.h>

#define ASSERT_RETURN_HAS_VALUE(value) do { if (!(value).has_value()) return (value); } while(0)


namespace Calc {

    tl::expected<Expression*, Parser::Error> Parser::Parse(const std::vector<Token>& tokens) {
        Parser parser(tokens);
        return parser.Term();
    }

    tl::expected<Expression*, Parser::Error> Parser::Term() {
        tl::expected<Expression*, Parser::Error> expr = Factor();
        ASSERT_RETURN_HAS_VALUE(expr);

        while (MatchAnyToken({Token::Type::Add, Token::Type::Subtract})) {
            Token op = PeekToken(-1);

            tl::expected<Expression*, Parser::Error> right = Factor();
            ASSERT_RETURN_HAS_VALUE(right);

            // FIXME: *new*
            expr.value() = new BinaryExpression(expr.value(), op, right.value());
        }

        return expr;
    }

    tl::expected<Expression*, Parser::Error> Parser::Factor() {
        tl::expected<Expression*, Parser::Error> expr = Unary();
        ASSERT_RETURN_HAS_VALUE(expr);

        while (MatchAnyToken({Token::Type::Multiply, Token::Type::Divide})) {
            Token op = PeekToken(-1);

            tl::expected<Expression*, Parser::Error> right = Unary();
            ASSERT_RETURN_HAS_VALUE(right);

            expr.value() = new BinaryExpression(expr.value(), op, right.value());
        }

        return expr;
    }

    tl::expected<Expression*, Parser::Error> Parser::Unary() {
        if (MatchAnyToken({Token::Type::Subtract})) {
            tl::expected<Expression*, Parser::Error> expr = Primary();
            ASSERT_RETURN_HAS_VALUE(expr);

            return new UnaryExpression(Token(Token::Type::Subtract), expr.value());
        }

        return Primary();
    }

    tl::expected<Expression*, Parser::Error> Parser::Primary() {
        if (MatchAnyToken({Token::Type::Number}))
            return new LiteralExpression(PeekToken(-1));

        if (MatchAnyToken({Token::Type::OpenBracket})) {
            tl::expected<Expression*, Parser::Error> expr = Term();
            ASSERT_RETURN_HAS_VALUE(expr);

            if (!MatchAnyToken({Token::Type::CloseBracket})) {
                return tl::unexpected(Parser::Error("Expected ')' token."));
            }

            return expr;
        }

        return tl::unexpected(Parser::Error("Could not parse the expression."));
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
