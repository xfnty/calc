#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>

#include <vector>

#include <tl/expected.hpp>
#include <spdlog/spdlog.h>

#include <Calc/Token.h>
#include <Calc/Lexer.h>
#include <Calc/Parser.h>

using namespace Calc;


TEST_CASE("Parser") {

    SECTION("Valid expression") {
        auto tokens = Lexer::Tokenize("2+2 * (1 / 0.5) * Pi");
        REQUIRE(tokens.has_value());

        auto ast = Parser::Parse(tokens.value());
        REQUIRE(ast.has_value());
    }

    SECTION("Invalid expression") {
        auto tokens = Lexer::Tokenize("2+2 * (1 / 0.5) +");
        REQUIRE(tokens.has_value());
    }

}
