#include <chrono>

namespace debug { namespace timer {
    using namespace std::chrono;
    static auto global_start = steady_clock::now();
    namespace nanos {
        unsigned long long now() { return duration_cast<nanoseconds>(steady_clock::now() - global_start).count(); }
        void sleep(const unsigned long long ns) {
            const auto start = now();
            while (now() - start < ns) {} // block
        }
    } // namespace nanos
    namespace micros {
        unsigned long long now() { return duration_cast<microseconds>(steady_clock::now() - global_start).count(); }
        void sleep(const unsigned long long ns) {
            const auto start = now();
            while (now() - start < ns) {} // block
        }
    } // namespace micros
    namespace millis {
        unsigned long long now() { return duration_cast<milliseconds>(steady_clock::now() - global_start).count(); }
        void sleep(const unsigned long long millis) {
            const auto start = now();
            while (now() - start < millis) {} // block
        }
    } // namespace millis
    double now() { return static_cast<double>(micros::now()) / 1000000.0; }
    void sleep(const double s) { micros::sleep(s * 1000000); }
}} // namespace debug::timer
