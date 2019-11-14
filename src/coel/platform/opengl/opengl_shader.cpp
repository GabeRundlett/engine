#include "../../core/renderer/shader.hpp"
#include "common.hpp"

#ifndef NDEBUG
#include <iostream>
#include <vector>
#endif

namespace coel { namespace opengl {
    static inline void compile_shader_source(const unsigned int program, const int type, const char *const src) {
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

    Shader::Shader(const char *const vert_src, const char *const frag_src) {
        GL_CALL(m_id = glCreateProgram());
        GL_CALL(compile_shader_source(m_id, GL_VERTEX_SHADER, vert_src));
        GL_CALL(compile_shader_source(m_id, GL_FRAGMENT_SHADER, frag_src));
        GL_CALL(glLinkProgram(m_id));
        GL_CALL(glUseProgram(m_id));
    }

    void Shader::bind() const {}

    void Shader::send_int(const char *const location, const int value) const {}

    void Shader::send_float(const char *const location, const float value) const {}
}} // namespace coel::opengl
