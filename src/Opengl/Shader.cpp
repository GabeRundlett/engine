#include "Common.hpp"
#include "../Shader.hpp"

#ifndef NDEBUG
#include <iostream>
#include <vector>
#endif

namespace Coel { namespace Opengl {
    static inline void compileShaderSource(const unsigned int program, const int type, const char *const src) {
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
        GL_CALL(mId = glCreateProgram());
        GL_CALL(compileShaderSource(mId, GL_VERTEX_SHADER, vertSrc));
        GL_CALL(compileShaderSource(mId, GL_FRAGMENT_SHADER, fragSrc));
        GL_CALL(glLinkProgram(mId));
        GL_CALL(glUseProgram(mId));
    }

    void Shader::bind() const { GL_CALL(glUseProgram(mId)); }

    void Shader::sendInt(const char *const location, const int value) const {
        glUniform1i(glGetUniformLocation(mId, location), value);
    }

    void Shader::sendInt2(const char *const location, void *data) const {
        glUniform2iv(glGetUniformLocation(mId, location), 1, static_cast<int *>(data));
    }

    void Shader::sendInt3(const char *const location, void *data) const {
        glUniform3iv(glGetUniformLocation(mId, location), 1, static_cast<int *>(data));
    }

    void Shader::sendInt4(const char *const location, void *data) const {
        glUniform4iv(glGetUniformLocation(mId, location), 1, static_cast<int *>(data));
    }

    void Shader::sendFloat(const char *const location, const float value) const {
        glUniform1f(glGetUniformLocation(mId, location), value);
    }

    void Shader::sendFloat2(const char *const location, void *data) const {
        glUniform2fv(glGetUniformLocation(mId, location), 1, static_cast<float *>(data));
    }

    void Shader::sendFloat3(const char *const location, void *data) const {
        glUniform3fv(glGetUniformLocation(mId, location), 1, static_cast<float *>(data));
    }

    void Shader::sendFloat4(const char *const location, void *data) const {
        glUniform4fv(glGetUniformLocation(mId, location), 1, static_cast<float *>(data));
    }

    void Shader::sendMat4(const char *const location, void *data) const {
        glUniformMatrix4fv(glGetUniformLocation(mId, location), 1, false, static_cast<float *>(data));
    }
}} // namespace Coel::Opengl
