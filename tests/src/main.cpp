#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>

#include <spdlog/spdlog.h>

TEST_CASE("Test Case") {
    SPDLOG_TRACE("Some trace message with param {}", 42);
    SPDLOG_DEBUG("Some debug {}", fmt::to_string(123));
}
