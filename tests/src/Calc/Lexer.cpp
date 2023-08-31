#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>

#include <tl/expected.hpp>
#include <spdlog/spdlog.h>

#include <Calc/Token.h>
#include <Calc/Lexer.h>

TEST_CASE("Test Lexer") {
    Calc::Lexer lexer;

    auto tokens = lexer.Process("Sample text");
    if (!tokens.has_value())
        SPDLOG_ERROR(tokens.error());

    REQUIRE_FALSE(tokens.has_value());
}
