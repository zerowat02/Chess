#include "Logger.h"
#include <stdarg.h>

LogLevel             Logger::_level  = LogLevel::DEBUG;
Logger::MQTTCallback Logger::_mqttCb = nullptr;

static const char* levelStr(LogLevel l)
{
    switch (l) {
        case LogLevel::DEBUG: return "DEBUG";
        case LogLevel::INFO:  return "INFO ";
        case LogLevel::WARN:  return "WARN ";
        case LogLevel::ERROR: return "ERROR";
        default:              return "?????";
    }
}

void Logger::setLevel(LogLevel level)      { _level  = level; }
void Logger::setMQTTCallback(MQTTCallback cb) { _mqttCb = cb; }

void Logger::log(LogLevel level, const char* tag, const char* fmt, va_list args)
{
    if (level < _level) return;

    char msg[256];
    vsnprintf(msg, sizeof(msg), fmt, args);

    char line[300];
    snprintf(line, sizeof(line), "[%7lums][%s][%s] %s", millis(), levelStr(level), tag, msg);

    Serial.println(line);

    if (_mqttCb)
        _mqttCb(std::string(line));
}

void Logger::debug(const char* tag, const char* fmt, ...) { va_list a; va_start(a, fmt); log(LogLevel::DEBUG, tag, fmt, a); va_end(a); }
void Logger::info (const char* tag, const char* fmt, ...) { va_list a; va_start(a, fmt); log(LogLevel::INFO,  tag, fmt, a); va_end(a); }
void Logger::warn (const char* tag, const char* fmt, ...) { va_list a; va_start(a, fmt); log(LogLevel::WARN,  tag, fmt, a); va_end(a); }
void Logger::error(const char* tag, const char* fmt, ...) { va_list a; va_start(a, fmt); log(LogLevel::ERROR, tag, fmt, a); va_end(a); }
