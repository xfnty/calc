#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>

#include <tl/expected.hpp>

TEST_CASE("Test Case") {
    tl::expected<int, int> v = tl::expected<int, int>(123);
}
