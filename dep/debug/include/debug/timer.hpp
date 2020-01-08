#pragma once

#ifndef NDEBUG
#define DEBUG_ENABLE_TIMING
#endif

namespace debug { namespace timer {
#ifdef DEBUG_ENABLE_TIMING
    namespace nanos {
        // This function returns the time, either since the program
        // started.
        unsigned long long now();
        // This function pauses execution by timing a while loop using
        // timer::now() to get the elapsed time since the function was
        // initially called.
        void sleep(const unsigned long long nanos);
    } // namespace nanos
    namespace micros {
        // This function returns the time, either since the program
        // started.
        unsigned long long now();
        // This function pauses execution by timing a while loop using
        // timer::now() to get the elapsed time since the function was
        // initially called.
        void sleep(const unsigned long long millis);
    } // namespace micros
    namespace millis {
        // This function returns the time, either since the program
        // started.
        unsigned long long now();
        // This function pauses execution by timing a while loop using
        // timer::now() to get the elapsed time since the function was
        // initially called.
        void sleep(const unsigned long long millis);
    } // namespace millis
    // This function returns the time, either since the program
    // started.
    double now();
    // This function pauses execution by timing a while loop using
    // timer::now() to get the elapsed time since the function was
    // initially called.
    void sleep(const double s);
#else
    namespace nanos {
        // This function returns 0 in release mode.
        static inline constexpr unsigned long long now() { return 0; }
        // This function does nothing in release mode.
        static inline void sleep(const unsigned long long nanos) {}
    } // namespace nanos
    namespace micros {
        // This function returns 0 in release mode.
        static inline constexpr unsigned long long now() { return 0; }
        // This function does nothing in release mode.
        static inline void sleep(const unsigned long long millis) {}
    } // namespace micros
    namespace millis {
        // This function returns 0 in release mode.
        static inline constexpr unsigned long long now() { return 0; }
        // This function does nothing in release mode.
        static inline void sleep(const unsigned long long millis) {}
    } // namespace millis
    // This function returns 0.0 in release mode.
    static inline constexpr double now(...) { return 0.0; }
    // This function does nothing in release mode.
    static inline void sleep(...) {}
#endif
}} // namespace debug::timer
