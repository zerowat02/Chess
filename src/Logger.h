#pragma once
#include <Arduino.h>
#include <functional>
#include <string>

enum class LogLevel { DEBUG = 0, INFO = 1, WARN = 2, ERROR = 3 };

class Logger {
public:
    using MQTTCallback = std::function<void(const std::string&)>;

    static void setLevel(LogLevel level);
    static void setMQTTCallback(MQTTCallback cb);

    static void debug(const char* tag, const char* fmt, ...);
    static void info (const char* tag, const char* fmt, ...);
    static void warn (const char* tag, const char* fmt, ...);
    static void error(const char* tag, const char* fmt, ...);

private:
    static LogLevel      _level;
    static MQTTCallback  _mqttCb;

    static void log(LogLevel level, const char* tag, const char* fmt, va_list args);
};
