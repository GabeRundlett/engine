#include "../coel.hpp"
#include <glad/glad.h>

#ifndef NDEBUG
#include <iostream>
#include <vector>
#endif

namespace coel { namespace shader {
    namespace _internal {
        Shader create_program() { return {glCreateProgram()}; }
        void link_program(const Shader &s) {
            glLinkProgram(s.id);
            glUseProgram(s.id);
        }
        void compile_sources(const Shader &s, const ShaderType type, const char *const src) {
            int compiled_object_id;
            switch (type) {
            case ShaderType::Vertex: compiled_object_id = glCreateShader(GL_VERTEX_SHADER); break;
            case ShaderType::Fragment: compiled_object_id = glCreateShader(GL_FRAGMENT_SHADER); break;
            case ShaderType::Geometry: compiled_object_id = glCreateShader(GL_GEOMETRY_SHADER); break;
            case ShaderType::Tesselation: compiled_object_id = 0; break;
            case ShaderType::Compute: compiled_object_id = glCreateShader(GL_COMPUTE_SHADER); break;
            default: compiled_object_id = 0; break;
            }
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
            glAttachShader(s.id, compiled_object_id);
            glDeleteShader(compiled_object_id);
        }
    } // namespace _internal
    void bind(const Shader &s) { glUseProgram(s.id); }
    void send_int(const Shader &s, const char *const name, const int value) {
        glUniform1i(glGetUniformLocation(s.id, name), value);
    }
    void send_float(const Shader &s, const char *const name, const float value) {
        glUniform1f(glGetUniformLocation(s.id, name), value);
    }
    void send_float2(const Shader &s, const char *const name, const void *const data) {
        glUniform2fv(glGetUniformLocation(s.id, name), 1, reinterpret_cast<const float *const>(data));
    }
    void send_float3(const Shader &s, const char *const name, const void *const data) {
        glUniform3fv(glGetUniformLocation(s.id, name), 1, reinterpret_cast<const float *const>(data));
    }
    void send_float4(const Shader &s, const char *const name, const void *const data) {
        glUniform4fv(glGetUniformLocation(s.id, name), 1, reinterpret_cast<const float *const>(data));
    }
}} // namespace coel::shader
