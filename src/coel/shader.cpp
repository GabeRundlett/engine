#include "../coel.hpp"
#include <glad/glad.h>

#ifndef NDEBUG
#include <iostream>
#include <vector>
#endif

namespace coel {
    void Shader::create_program() { id = glCreateProgram(); }
    void Shader::link_program() {
        glLinkProgram(id);
        glUseProgram(id);
    }
    void Shader::compile_sources(const ShaderType type, const char *const src) {
        int compiled_object_id;
        switch (type) {
        case ShaderType::Vertex: compiled_object_id = glCreateShader(GL_VERTEX_SHADER); break;
        case ShaderType::Fragment: compiled_object_id = glCreateShader(GL_FRAGMENT_SHADER); break;
        case ShaderType::Geometry: compiled_object_id = glCreateShader(GL_GEOMETRY_SHADER); break;
        case ShaderType::Tesselation: compiled_object_id = 0; break;
        case ShaderType::Compute: compiled_object_id = glCreateShader(GL_COMPUTE_SHADER); break;
        }
        glShaderSource(compiled_object_id, 1, &src, NULL);
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
        glAttachShader(id, compiled_object_id);
        glDeleteShader(compiled_object_id);
    }
    void Shader::send_int(const char *const name, const int value) const { glUniform1i(glGetUniformLocation(id, name), value); }
    void Shader::send_float(const char *const name, const float value) const {
        glUniform1f(glGetUniformLocation(id, name), value);
    }
    void Shader::send_float2(const char *const name, const void *const data) const {
        glUniform2fv(glGetUniformLocation(id, name), 1, reinterpret_cast<const float *const>(data));
    }
    void Shader::send_float3(const char *const name, const void *const data) const {
        glUniform3fv(glGetUniformLocation(id, name), 1, reinterpret_cast<const float *const>(data));
    }
    void Shader::send_float4(const char *const name, const void *const data) const {
        glUniform4fv(glGetUniformLocation(id, name), 1, reinterpret_cast<const float *const>(data));
    }

    //

    Model::Model(const char *const filepath) : vdata(nullptr), idata(nullptr), vsize(0), isize(0) {}
    Model::Model(const void *vdata, const unsigned int vsize, const unsigned short *idata, const unsigned int isize)
        : vdata(vdata), idata(idata), vsize(vsize), isize(isize) {}
    void Material::init_tex_mat(const Shader *const shader, const unsigned int slot, const Texture *texture,
                                const char *const name) {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, texture->id);
        shader->send_int(name, slot);
    }
} // namespace coel