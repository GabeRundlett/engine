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

    Shader::Shader(const char *const vertSrc, const char *const geomSrc, const char *const fragSrc) {
        m_id = glCreateProgram();
        compileShaderSource(m_id, GL_VERTEX_SHADER, vertSrc);
        compileShaderSource(m_id, GL_GEOMETRY_SHADER, geomSrc);
        compileShaderSource(m_id, GL_FRAGMENT_SHADER, fragSrc);
        glLinkProgram(m_id);
        glUseProgram(m_id);
    }

    void Shader::bind() const { glUseProgram(m_id); }

    Shader::Uniform<int> Shader::findInt(const char *const name) const { return {glGetUniformLocation(m_id, name)}; }
    Shader::Uniform<glm::ivec2> Shader::findInt2(const char *const name) const { return {glGetUniformLocation(m_id, name)}; }
    Shader::Uniform<glm::ivec3> Shader::findInt3(const char *const name) const { return {glGetUniformLocation(m_id, name)}; }
    Shader::Uniform<glm::ivec4> Shader::findInt4(const char *const name) const { return {glGetUniformLocation(m_id, name)}; }
    Shader::Uniform<float> Shader::findFloat(const char *const name) const { return {glGetUniformLocation(m_id, name)}; }
    Shader::Uniform<glm::vec2> Shader::findFloat2(const char *const name) const { return {glGetUniformLocation(m_id, name)}; }
    Shader::Uniform<glm::vec3> Shader::findFloat3(const char *const name) const { return {glGetUniformLocation(m_id, name)}; }
    Shader::Uniform<glm::vec4> Shader::findFloat4(const char *const name) const { return {glGetUniformLocation(m_id, name)}; }
    Shader::Uniform<glm::mat3> Shader::findMat3(const char *const name) const { return {glGetUniformLocation(m_id, name)}; }
    Shader::Uniform<glm::mat4> Shader::findMat4(const char *const name) const { return {glGetUniformLocation(m_id, name)}; }

    void Shader::send(const Shader::Uniform<int> uniform, const int value) const { glUniform1i(uniform.location, value); }
    void Shader::send(const Shader::Uniform<int> uniform, const int *const data) const {
        glUniform1iv(uniform.location, uniform.count, data);
    }
    void Shader::send(const Shader::Uniform<glm::ivec2> uniform, const void *const data) const {
        glUniform2iv(uniform.location, uniform.count, static_cast<const GLint *>(data));
    }
    void Shader::send(const Shader::Uniform<glm::ivec3> uniform, const void *const data) const {
        glUniform3iv(uniform.location, uniform.count, static_cast<const GLint *>(data));
    }
    void Shader::send(const Shader::Uniform<glm::ivec4> uniform, const void *const data) const {
        glUniform4iv(uniform.location, uniform.count, static_cast<const GLint *>(data));
    }
    void Shader::send(const Shader::Uniform<float> uniform, const float value) const { glUniform1f(uniform.location, value); }
    void Shader::send(const Shader::Uniform<float> uniform, const float *const data) const {
        glUniform1fv(uniform.location, uniform.count, data);
    }
    void Shader::send(const Shader::Uniform<glm::vec2> uniform, const void *const data) const {
        glUniform2fv(uniform.location, uniform.count, static_cast<const GLfloat *>(data));
    }
    void Shader::send(const Shader::Uniform<glm::vec3> uniform, const void *const data) const {
        glUniform3fv(uniform.location, uniform.count, static_cast<const GLfloat *>(data));
    }
    void Shader::send(const Shader::Uniform<glm::vec4> uniform, const void *const data) const {
        glUniform4fv(uniform.location, uniform.count, static_cast<const GLfloat *>(data));
    }
    void Shader::send(const Shader::Uniform<glm::mat3> uniform, const void *const data) const {
        glUniformMatrix3fv(uniform.location, uniform.count, false, static_cast<const GLfloat *>(data));
    }
    void Shader::send(const Shader::Uniform<glm::mat4> uniform, const void *const data) const {
        glUniformMatrix4fv(uniform.location, uniform.count, false, static_cast<const GLfloat *>(data));
    }
} // namespace Coel
