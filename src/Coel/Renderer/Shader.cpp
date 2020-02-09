#include "Shader.hpp"

#include <glad/glad.h>

#ifndef NDEBUG
#include <iostream>
#include <vector>
#endif

namespace Coel {
    static inline void compileShaderSource(const unsigned int program, const int type, const char *const src) {
        int compiled_object_id = glCreateShader(type);
        glShaderSource(compiled_object_id, 1, &src, nullptr);
        glCompileShader(compiled_object_id);

#ifndef NDEBUG
        int temp = 0;
        glGetShaderiv(compiled_object_id, GL_COMPILE_STATUS, &temp);
        if (temp == GL_FALSE) {
            temp = 0;
            glGetShaderiv(compiled_object_id, GL_INFO_LOG_LENGTH, &temp);
            std::vector<char> infoLog(temp);
            glGetShaderInfoLog(compiled_object_id, temp, &temp, &infoLog[0]);
            glDeleteShader(compiled_object_id);
            std::cout << infoLog.data() << '\n';
        }
#endif

        glAttachShader(program, compiled_object_id);
        glDeleteShader(compiled_object_id);
    }

    Shader::Shader(const char *const vertSrc, const char *const fragSrc) {
        m_id = glCreateProgram();
        compileShaderSource(m_id, GL_VERTEX_SHADER, vertSrc);
        compileShaderSource(m_id, GL_FRAGMENT_SHADER, fragSrc);
        glLinkProgram(m_id);
        glUseProgram(m_id);
    }

    void Shader::bind() const { glUseProgram(m_id); }

    void Shader::sendInt(const char *const location, const int value) const {
        glUniform1i(glGetUniformLocation(m_id, location), value);
    }

    void Shader::sendInt2(const char *const location, void *data) const {
        glUniform2iv(glGetUniformLocation(m_id, location), 1, static_cast<GLint *>(data));
    }

    void Shader::sendInt3(const char *const location, void *data) const {
        glUniform3iv(glGetUniformLocation(m_id, location), 1, static_cast<GLint *>(data));
    }

    void Shader::sendInt4(const char *const location, void *data) const {
        glUniform4iv(glGetUniformLocation(m_id, location), 1, static_cast<GLint *>(data));
    }

    void Shader::sendFloat(const char *const location, const float value) const {
        glUniform1f(glGetUniformLocation(m_id, location), value);
    }

    void Shader::sendFloat2(const char *const location, void *data) const {
        glUniform2fv(glGetUniformLocation(m_id, location), 1, static_cast<GLfloat *>(data));
    }

    void Shader::sendFloat3(const char *const location, void *data) const {
        glUniform3fv(glGetUniformLocation(m_id, location), 1, static_cast<GLfloat *>(data));
    }

    void Shader::sendFloat4(const char *const location, void *data) const {
        glUniform4fv(glGetUniformLocation(m_id, location), 1, static_cast<GLfloat *>(data));
    }

    void Shader::sendMat4(const char *const location, void *data) const {
        glUniformMatrix4fv(glGetUniformLocation(m_id, location), 1, false, static_cast<GLfloat *>(data));
    }
} // namespace Coel
