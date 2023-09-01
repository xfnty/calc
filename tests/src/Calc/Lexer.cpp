#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>

#include <tl/expected.hpp>
#include <vector>
#include <spdlog/spdlog.h>

#include <Calc/Token.h>
#include <Calc/Lexer.h>

using namespace Calc;

TEST_CASE("Test Lexer") {
    Lexer lexer;

    SECTION("Check valid data") {
        auto tokens = lexer.Process("+123-");
        REQUIRE(tokens.has_value());

        auto ideal_output = std::vector<Token>{
            Token(Token::Type::Add),
            Token(Token::Type::Number, 123),
            Token(Token::Type::Subtract),
        };
        REQUIRE(tokens.value() == ideal_output);
    }

    SECTION("Check invalid data") {
        auto tokens = lexer.Process("a");
        REQUIRE_FALSE(tokens.has_value());
        REQUIRE(tokens.error().type == Lexer::Error::Type::InvalidToken);
    }
}
