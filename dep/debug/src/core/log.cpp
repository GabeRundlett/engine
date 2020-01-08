#include <cstdio>
#include <stdarg.h>

namespace debug { namespace log {
    void info(const char *const msg, ...) {
        va_list args;
        va_start(args, msg);
        vprintf(msg, args);
        va_end(args);
    }
    void message(const char *const msg, ...) {
        char buffer[512];
        va_list args;
        va_start(args, msg);
        vsprintf(buffer, msg, args);
        info("\033[90m%s\n\033[0m", buffer);
        va_end(args);
    }
    void success(const char *const msg, ...) {
        char buffer[512];
        va_list args;
        va_start(args, msg);
        vsprintf(buffer, msg, args);
        info("\033[30;42m SUCCESS \033[0;32m %s\n\033[0m", buffer);
        va_end(args);
    }
    void warning(const char *const msg, ...) {
        char buffer[512];
        va_list args;
        va_start(args, msg);
        vsprintf(buffer, msg, args);
        info("\033[30;43m WARNING \033[0;33m %s\n\033[0m", buffer);
        va_end(args);
    }
    void error(const char *const msg, ...) {
        char buffer[512];
        va_list args;
        va_start(args, msg);
        vsprintf(buffer, msg, args);
        info("\033[30;41m  ERROR  \033[0;31m %s\n\033[0m", buffer);
        va_end(args);
    }
}} // namespace debug::log
