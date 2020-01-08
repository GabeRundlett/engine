#pragma once

#ifndef NDEBUG
#define DEBUG_ENABLE_PROFILING
#endif

#include <fstream>

namespace debug { namespace profile {
    struct Session {
        const char *const m_name, *const m_output_filename;
        std::ofstream m_output;
        unsigned long long m_profile_count, m_last_start_time;
        bool m_stopped;
        static Session *s_session;
        Session(const char *const session_name, const char *const session_file = "results.json");
        ~Session();
        void end();
    };
    struct ScopedProfile {
        const char *const m_name;
        unsigned long long m_start_time;
        bool m_stopped;
        ScopedProfile(const char *const function_name);
        ~ScopedProfile();
        void end();
    };
#ifdef DEBUG_ENABLE_PROFILING
#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) ||              \
    defined(__ghs__)
#define DEBUG_FUNC_SIG __PRETTY_FUNCTION__
#elif defined(__DMC__) && (__DMC__ >= 0x810)
#define DEBUG_FUNC_SIG __PRETTY_FUNCTION__
#elif defined(__FUNCSIG__)
#define DEBUG_FUNC_SIG __FUNCSIG__
#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
#define DEBUG_FUNC_SIG __FUNCTION__
#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
#define DEBUG_FUNC_SIG __FUNC__
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
#define DEBUG_FUNC_SIG __func__
#elif defined(__cplusplus) && (__cplusplus >= 201103)
#define DEBUG_FUNC_SIG __func__
#else
#define DEBUG_FUNC_SIG "unknown function signature macro"
#endif
#define DEBUG_PROFILE_SESSION(name, filename) ::debug::profile::Session db_##name(#name, filename)
#define DEBUG_END_PROFILE_SESSION(name) db_##name.end()
#define DEBUG_BEGIN_PROFILE(name) ::debug::profile::ScopedProfile db_profile_##name(#name)
#define DEBUG_END_PROFILE(name) db_profile_##name.end()
#define DEBUG_BEGIN_FUNC_PROFILE ::debug::profile::ScopedProfile db_profile_##DEBUG_FUNC_SIG(DEBUG_FUNC_SIG)
#define DEBUG_END_FUNC_PROFILE db_profile_##DEBUG_FUNC_SIG.end()
#else
#define DEBUG_PROFILE_SESSION(name, filename)
#define DEBUG_END_PROFILE_SESSION(name)
#define DEBUG_BEGIN_PROFILE(name)
#define DEBUG_END_PROFILE(name)
#define DEBUG_BEGIN_FUNC_PROFILE
#define DEBUG_END_FUNC_PROFILE
#endif
}} // namespace debug::profile
