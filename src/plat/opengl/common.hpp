#pragma once

#include <glad/glad.h>

#if NDEBUG
#define GL_CALL(x) x
#else
#include <iostream>

namespace coel { namespace opengl {
    static inline GLenum check_error() { return glGetError(); }

    static inline bool send_error(const char *const function, const char *const file, const unsigned int line) {
        GLenum error = check_error();
        if (error != GL_NO_ERROR) {
            std::cout << "\033[30;41m ERROR \033[0;31m OpenGL (" << std::hex << error << "): \033[0m" << function
                      << " \033[0;90m" << file << ":\033[33m" << std::dec << line << "\033[0m\n";
            return true;
        }
        return false;
    }
}} // namespace coel::opengl

#define GL_CALL(x)                                                                                                             \
    ::coel::opengl::check_error();                                                                                             \
    x;                                                                                                                         \
    if (::coel::opengl::send_error(#x, __FILE__, __LINE__))                                                                    \
        while (true) {}
#endif
