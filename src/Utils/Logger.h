#pragma once

#include <string>
#include <iostream>
#include <sstream>

template <typename ...Args>
void Logger(int line, const char* fileName, const char * type, Args&& ...args) {
    std::ostringstream stream;
    //stream << fileName << " [" << line << "]: ";
    stream << "[" << type <<"]: ";
    (stream << ... << std::forward<Args>(args)) << '\n';

    std::cout << stream.str().c_str();
}

#define VK_LOGGER 1
#if VK_LOGGER
#define VK_LOG_INFO(...) Logger(__LINE__, __FILE__, "INFO", __VA_ARGS__)
#define VK_LOG_WARN(...) Logger(__LINE__, __FILE__, "WARN", __VA_ARGS__)
#define VK_LOG_ERROR(...) Logger(__LINE__, __FILE__, "ERROR", __VA_ARGS__)
#define VK_LOG_DEBUG(...) Logger(__LINE__, __FILE__, "DEBUG", __VA_ARGS__)
#else
#define VK_LOG_INFO(...)
#define VK_LOG_WARN(...)
#define VK_LOG_ERROR(...)
#define VK_LOG_DEBUG(...)
#endif 