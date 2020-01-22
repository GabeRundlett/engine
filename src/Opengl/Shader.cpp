#include "Common.hpp"
#include "../Shader.hpp"

#ifndef NDEBUG
#include <iostream>
#include <vector>
#endif

namespace Coel { namespace Opengl {
    static inline void compileShaderSource(const unsigned int program, const int type, const char *const src) {
        // DEBUG_BEGIN_FUNC_PROFILE;

        GL_CALL(int compiled_object_id = glCreateShader(type));
        GL_CALL(glShaderSource(compiled_object_id, 1, &src, nullptr));
        GL_CALL(glCompileShader(compiled_object_id));

#ifndef NDEBUG
        int temp = 0;
        GL_CALL(glGetShaderiv(compiled_object_id, GL_COMPILE_STATUS, &temp));
        if (temp == GL_FALSE) {
            temp = 0;
            GL_CALL(glGetShaderiv(compiled_object_id, GL_INFO_LOG_LENGTH, &temp));
            std::vector<char> infoLog(temp);
            GL_CALL(glGetShaderInfoLog(compiled_object_id, temp, &temp, &infoLog[0]));
            GL_CALL(glDeleteShader(compiled_object_id));
            std::cout << infoLog.data() << '\n';
        }
#endif

        GL_CALL(glAttachShader(program, compiled_object_id));
        GL_CALL(glDeleteShader(compiled_object_id));
    }

    Shader::Shader(const char *const vertSrc, const char *const fragSrc) {
        // DEBUG_BEGIN_FUNC_PROFILE;

        GL_CALL(mId = glCreateProgram());
        GL_CALL(compileShaderSource(mId, GL_VERTEX_SHADER, vertSrc));
        GL_CALL(compileShaderSource(mId, GL_FRAGMENT_SHADER, fragSrc));
        GL_CALL(glLinkProgram(mId));
        GL_CALL(glUseProgram(mId));
    }

    void Shader::bind() const {
        // DEBUG_BEGIN_FUNC_PROFILE;

        GL_CALL(glUseProgram(mId));
    }

    void Shader::sendInt(const char *const location, const int value) const {
        // DEBUG_BEGIN_FUNC_PROFILE;

        glUniform1i(glGetUniformLocation(mId, location), value);
    }

    void Shader::sendFloat(const char *const location, const float value) const {
        // DEBUG_BEGIN_FUNC_PROFILE;

        glUniform1f(glGetUniformLocation(mId, location), value);
    }
}} // namespace Coel::Opengl
