#include "Log.hpp"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace zui {

std::shared_ptr<spdlog::logger> Logger::s_logger;

using ConsoleSink = spdlog::sinks::stdout_color_sink_mt;

void Logger::Init() {
    std::shared_ptr<ConsoleSink> consoleSink = std::make_shared<ConsoleSink>();

    consoleSink->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] [thread %t] %s:%# %! >> %v");
    s_logger = std::make_shared<spdlog::logger>("Zui", consoleSink);
    spdlog::register_logger(s_logger);

    s_logger->set_level(spdlog::level::trace);
    s_logger->flush_on(spdlog::level::err);
}

} // namespace zui
