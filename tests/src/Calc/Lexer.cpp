#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>

#include <vector>

#include <tl/expected.hpp>
#include <spdlog/spdlog.h>

#include <Calc/Token.h>
#include <Calc/Lexer.h>

using namespace Calc;


TEST_CASE("Lexer") {

    SECTION("Valid data") {
        auto tokens = Lexer::Tokenize("+-/*()123E");
        REQUIRE(tokens.has_value());

        auto ideal_output = std::vector<Token>{
            Token(Token::Type::Add),
            Token(Token::Type::Subtract),
            Token(Token::Type::Divide),
            Token(Token::Type::Multiply),
            Token(Token::Type::OpenBracket),
            Token(Token::Type::CloseBracket),
            Token(123),
            Token("E"),
        };
        REQUIRE(tokens.value() == ideal_output);
    }

    SECTION("Invalid data") {
        auto tokens = Lexer::Tokenize("1 + 2 + $");
        REQUIRE(!tokens.has_value());
        REQUIRE(tokens.error().type == Lexer::Error::Type::InvalidToken);
    }
}
