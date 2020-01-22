#pragma once

#include <glad/glad.h>

#if NDEBUG
#define GL_CALL(x) x
#else
#include <iostream>

namespace Coel { namespace Opengl {
    static inline GLenum checkError() { return glGetError(); }

    static inline bool sendError(const char *const function, const char *const file, const unsigned int line) {
        GLenum error = checkError();
        if (error != GL_NO_ERROR) {
            std::cout << "\033[30;41m ERROR \033[0;31m OpenGL (" << std::hex << error << "): \033[0m" << function
                      << " \033[0;90m" << file << ":\033[33m" << std::dec << line << "\033[0m\n";
            return true;
        }
        return false;
    }

    static void fail() {
        while (true) {} //
    }
}} // namespace Coel::Opengl

#define GL_CALL(x)                                                                                                             \
    ::Coel::Opengl::checkError();                                                                                              \
    x;                                                                                                                         \
    if (::Coel::Opengl::sendError(#x, __FILE__, __LINE__)) ::Coel::Opengl::fail();

#endif
