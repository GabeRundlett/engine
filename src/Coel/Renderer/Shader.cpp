#include "Shader.hpp"

#include <glad/glad.h>

#ifndef NDEBUG
#include <iostream>
#include <vector>
#endif

namespace Coel {
    static inline void compileShaderSource(const uint32_t program, const int32_t type, const char *const src) {
        int32_t compiled_object_id = glCreateShader(type);
        glShaderSource(compiled_object_id, 1, &src, nullptr);
        glCompileShader(compiled_object_id);

#ifndef NDEBUG
        int32_t temp = 0;
        glGetShaderiv(compiled_object_id, GL_COMPILE_STATUS, &temp);
        if (temp == GL_FALSE) {
            temp = 0;
            glGetShaderiv(compiled_object_id, GL_INFO_LOG_LENGTH, &temp);
            std::vector<char> infoLog(temp + 100);
            glGetShaderInfoLog(compiled_object_id, temp, &temp, &infoLog[0]);
            glDeleteShader(compiled_object_id);
            std::cout << infoLog.data() << '\n';
        }
#endif

        glAttachShader(program, compiled_object_id);
        glDeleteShader(compiled_object_id);
    }

    void create(Shader &shader, const char *const vertSrc, const char *const fragSrc) {
        shader.id = glCreateProgram();
        compileShaderSource(shader.id, GL_VERTEX_SHADER, vertSrc);
        compileShaderSource(shader.id, GL_FRAGMENT_SHADER, fragSrc);
        glLinkProgram(shader.id);
        glUseProgram(shader.id);
    }

    void create(Shader &shader, const char *const vertSrc, const char *const geomSrc, const char *const fragSrc) {
        shader.id = glCreateProgram();
        compileShaderSource(shader.id, GL_VERTEX_SHADER, vertSrc);
        compileShaderSource(shader.id, GL_GEOMETRY_SHADER, geomSrc);
        compileShaderSource(shader.id, GL_FRAGMENT_SHADER, fragSrc);
        glLinkProgram(shader.id);
        glUseProgram(shader.id);
    }

    void bind(const Shader &shader) { glUseProgram(shader.id); }

    void destroy(Shader &shader) {
        glDeleteProgram(shader.id); //
    }

    Uniform<int> findInt(const Shader &shader, const char *const name) { return {glGetUniformLocation(shader.id, name)}; }
    Uniform<glm::ivec2> findInt2(const Shader &shader, const char *const name) {
        return {glGetUniformLocation(shader.id, name)};
    }
    Uniform<glm::ivec3> findInt3(const Shader &shader, const char *const name) {
        return {glGetUniformLocation(shader.id, name)};
    }
    Uniform<glm::ivec4> findInt4(const Shader &shader, const char *const name) {
        return {glGetUniformLocation(shader.id, name)};
    }
    Uniform<float> findFloat(const Shader &shader, const char *const name) { return {glGetUniformLocation(shader.id, name)}; }
    Uniform<glm::vec2> findFloat2(const Shader &shader, const char *const name) {
        return {glGetUniformLocation(shader.id, name)};
    }
    Uniform<glm::vec3> findFloat3(const Shader &shader, const char *const name) {
        return {glGetUniformLocation(shader.id, name)};
    }
    Uniform<glm::vec4> findFloat4(const Shader &shader, const char *const name) {
        return {glGetUniformLocation(shader.id, name)};
    }
    Uniform<glm::mat3> findMat3(const Shader &shader, const char *const name) {
        return {glGetUniformLocation(shader.id, name)};
    }
    Uniform<glm::mat4> findMat4(const Shader &shader, const char *const name) {
        return {glGetUniformLocation(shader.id, name)};
    }

    void send(const Uniform<int> uniform, const int32_t value) { glUniform1i(uniform.location, value); }
    void send(const Uniform<int> uniform, const int32_t *const data) { glUniform1iv(uniform.location, uniform.count, data); }
    void send(const Uniform<glm::ivec2> uniform, const void *const data) {
        glUniform2iv(uniform.location, uniform.count, static_cast<const GLint *>(data));
    }
    void send(const Uniform<glm::ivec3> uniform, const void *const data) {
        glUniform3iv(uniform.location, uniform.count, static_cast<const GLint *>(data));
    }
    void send(const Uniform<glm::ivec4> uniform, const void *const data) {
        glUniform4iv(uniform.location, uniform.count, static_cast<const GLint *>(data));
    }
    void send(const Uniform<float> uniform, const float value) { glUniform1f(uniform.location, value); }
    void send(const Uniform<float> uniform, const float *const data) { glUniform1fv(uniform.location, uniform.count, data); }
    void send(const Uniform<glm::vec2> uniform, const void *const data) {
        glUniform2fv(uniform.location, uniform.count, static_cast<const GLfloat *>(data));
    }
    void send(const Uniform<glm::vec3> uniform, const void *const data) {
        glUniform3fv(uniform.location, uniform.count, static_cast<const GLfloat *>(data));
    }
    void send(const Uniform<glm::vec4> uniform, const void *const data) {
        glUniform4fv(uniform.location, uniform.count, static_cast<const GLfloat *>(data));
    }
    void send(const Uniform<glm::mat3> uniform, const void *const data) {
        glUniformMatrix3fv(uniform.location, uniform.count, false, static_cast<const GLfloat *>(data));
    }
    void send(const Uniform<glm::mat4> uniform, const void *const data) {
        glUniformMatrix4fv(uniform.location, uniform.count, false, static_cast<const GLfloat *>(data));
    }
} // namespace Coel
