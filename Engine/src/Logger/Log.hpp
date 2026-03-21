#pragma once

#include <spdlog/spdlog.h>
// enum class LogChannel : uint8_t { CORE, RENDERER, ASSETS, AUDIO, TIME, LOGGER, EVENT, WINDOW, PLATFORM, COUNT };
// i will add this later

namespace zui {

class Logger {
public:
    static void Init();
    static std::shared_ptr<spdlog::logger>& GetLogger() { return s_logger; }

private:
    static std::shared_ptr<spdlog::logger> s_logger;
};

} // namespace zui

#define LOGGER_TRACE(...)                                                                                              \
    ::zui::Logger::GetLogger()->log(spdlog::source_loc{__FILE__, __LINE__, __FUNCTION__}, spdlog::level::trace,        \
                                    __VA_ARGS__)
#define LOGGER_DEBUG(...)                                                                                              \
    ::zui::Logger::GetLogger()->log(spdlog::source_loc{__FILE__, __LINE__, __FUNCTION__}, spdlog::level::debug,        \
                                    __VA_ARGS__)
#define LOGGER_INFO(...)                                                                                               \
    ::zui::Logger::GetLogger()->log(spdlog::source_loc{__FILE__, __LINE__, __FUNCTION__}, spdlog::level::info,         \
                                    __VA_ARGS__)
#define LOGGER_WARN(...)                                                                                               \
    ::zui::Logger::GetLogger()->log(spdlog::source_loc{__FILE__, __LINE__, __FUNCTION__}, spdlog::level::warn,         \
                                    __VA_ARGS__)
#define LOGGER_ERROR(...)                                                                                              \
    ::zui::Logger::GetLogger()->log(spdlog::source_loc{__FILE__, __LINE__, __FUNCTION__}, spdlog::level::err,          \
                                    __VA_ARGS__)
#define LOGGER_CRITICAL(...)                                                                                           \
    ::zui::Logger::GetLogger()->log(spdlog::source_loc{__FILE__, __LINE__, __FUNCTION__}, spdlog::level::critical,     \
                                    __VA_ARGS__)

#define LOG_NULL(what) LOGGER_ERROR("{} is nullptr!", what)

#define LOG_NULL_CTX(what, fmt, ...) LOGGER_ERROR("{} is nullptr! " fmt, what, ##__VA_ARGS__)
