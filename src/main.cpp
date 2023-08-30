#include <fmt/core.h>

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

int main(int argc, char const* argv[]) {
    fmt::print("fmt is working\n");

    auto console = spdlog::stdout_color_mt("console");

    spdlog::set_level(spdlog::level::trace);

    SPDLOG_TRACE("Hello, World");
    SPDLOG_LOGGER_TRACE(console, "trace");
    SPDLOG_LOGGER_DEBUG(console, "debug");
    SPDLOG_LOGGER_INFO(console, "info");
    SPDLOG_LOGGER_WARN(console, "warning");
    SPDLOG_LOGGER_ERROR(console, "error");
    SPDLOG_LOGGER_CRITICAL(console, "critical");
    return 0;
}
