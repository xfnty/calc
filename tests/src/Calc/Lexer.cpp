#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>

#include <tl/expected.hpp>
#include <spdlog/spdlog.h>

#include <Calc/Token.h>
#include <Calc/Lexer.h>

TEST_CASE("Test Lexer") {
    Calc::Lexer lexer;

    SECTION("Check valid data") {
        auto tokens = lexer.Process("+-");
        REQUIRE(tokens.has_value());
    }

    SECTION("Check invalid data") {
        auto tokens = lexer.Process("a");
        REQUIRE_FALSE(tokens.has_value());
        REQUIRE(tokens.error().type == Calc::Lexer::Error::Type::InvalidToken);
    }
}
