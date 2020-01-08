#pragma once

#ifndef NDEBUG
#define DEBUG_ENABLE_LOGGING
#endif

namespace debug { namespace log {
#ifdef DEBUG_ENABLE_LOGGING
    // This function is a wrapper for the printf function.
    void info(const char *const msg, ...);
    // This function writes the given string to the console in gray.
    void message(const char *const msg, ...);
    // This function writes the given string to the console in
    // green, prefaced with the tag "[SUCCESS]".
    void success(const char *const msg, ...);
    // This function writes the given string to the console in
    // yellow, prefaced with the tag "[WARNING]".
    void warning(const char *const msg, ...);
    // This function writes the given string to the console in
    // red, prefaced with the tag "[ERROR]".
    void error(const char *const msg, ...);
#else
    // This function does nothing in release mode.
    static inline void info(...) {}
    // This function does nothing in release mode.
    static inline void message(...) {}
    // This function does nothing in release mode.
    static inline void success(...) {}
    // This function does nothing in release mode.
    static inline void warning(...) {}
    // This function does nothing in release mode.
    static inline void error(...) {}
#endif
}} // namespace debug::log