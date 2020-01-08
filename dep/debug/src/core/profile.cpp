#include "../../include/debug/debug.hpp"
#include <debug/debug.hpp>

#include <algorithm>
#include <fstream>
#include <thread>

namespace debug { namespace profile {
    Session *Session::s_session = nullptr;

    Session::Session(const char *const session_name, const char *const session_file)
        : m_stopped(0), m_name(session_name), m_output_filename(session_file), m_output(session_file), m_profile_count(0) {
        if (s_session != nullptr) s_session->end();
        s_session = this;
        m_output << "{\"otherData\": {},\"displayTimeUnit\":\"ns\",\"traceEvents\":[";
        m_output.flush();
    }
    Session::~Session() { end(); }
    void Session::end() {
        if (m_stopped == 0) {
            m_stopped = 1;
            m_output << "]}";
            m_output.flush();
            s_session = nullptr;
        }
    }

    ScopedProfile::ScopedProfile(const char *const function_name) : m_name(function_name), m_stopped(false) {
        auto now = timer::nanos::now();
        if (now == Session::s_session->m_last_start_time) timer::nanos::sleep(1000);
        m_start_time = timer::nanos::now();
        Session::s_session->m_last_start_time = m_start_time;
    }
    ScopedProfile::~ScopedProfile() {
        if (!m_stopped) { end(); }
    }
    void ScopedProfile::end() {
        auto end = timer::nanos::now();
        auto threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());

        if (Session::s_session != nullptr) {
            auto &session = *Session::s_session;
            auto &file = session.m_output;

            if (!session.m_stopped) {
                if (Session::s_session->m_profile_count != 0) file << ",";

                file << "{";
                file << "\"cat\":\"function\",";
                file << "\"dur\":" << double(end - m_start_time) / 1000 << ',';
                file << "\"name\":\"" << m_name << "\",";
                file << "\"ph\":\"X\",";
                file << "\"pid\":0,";
                file << "\"tid\":" << threadID << ",";
                file << "\"ts\":" << double(m_start_time) / 1000;
                file << "}";

                file.flush();

                ++Session::s_session->m_profile_count;
            }
        }

        m_stopped = true;
    }
}} // namespace debug::profile
