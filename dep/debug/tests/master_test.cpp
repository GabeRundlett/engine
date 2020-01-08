#include <debug/debug.hpp>

void func1() {
    DEBUG_BEGIN_FUNC_PROFILE;

    DEBUG_BEGIN_PROFILE(timing);
    auto t1 = debug::timer::now();

    debug::log::info("info %d\n", 1);
    debug::log::message("message %d", 2);
    debug::log::warning("warning %d", 3);
    debug::log::error("error!");

    auto t2 = debug::timer::now();
    DEBUG_END_PROFILE(timing);

    debug::log::info("time elapsed: %f\n", t2 - t1);
}

int main() {
    DEBUG_PROFILE_SESSION(debug_prof1, "debug_prof1.json");
    for (unsigned int i = 0; i < 10; ++i)
        func1();
    DEBUG_PROFILE_SESSION(debug_prof2, "debug_prof2.json");
    for (unsigned int i = 0; i < 20; ++i)
        func1();
    DEBUG_PROFILE_SESSION(debug_prof3, "debug_prof3.json");
    for (unsigned int i = 0; i < 50; ++i)
        func1();
}
