#include "renderer.hpp"
#include "glad/glad.h"

#ifndef _CONFIG_RELEASE
#include <iostream>
#include <vector>
#endif

namespace coel { namespace renderer { namespace _internal {
    namespace agnostic {

        //
        //
        //
        //
        //

        namespace vbo {
            VBO create(const float *data, const unsigned int vertex_size, const unsigned short count) { return {0, 0, 0}; }
        } // namespace vbo

        //
        //
        //
        //
        //

        namespace ibo {
            IBO create(const unsigned short *data, const unsigned short count) { return {0, 0}; }
        } // namespace ibo

        //
        //
        //
        //
        //

        namespace shader {
            Shader create(const char *vert_src, const char *frag_src) { return {0}; }
            void bind(const Shader *shader) {}
            void send_int(const Shader *shader, const char *uniform_name, const int data) {}
            void send_float(const Shader *shader, const char *uniform_name, const float data) {}
            void send_vec2(const Shader *shader, const char *uniform_name, const float *data) {}
            void send_vec3(const Shader *shader, const char *uniform_name, const float *data) {}
            void send_vec4(const Shader *shader, const char *uniform_name, const float *data) {}
            void send_mat3(const Shader *shader, const char *uniform_name, const float *data) {}
            void send_mat4(const Shader *shader, const char *uniform_name, const float *data) {}
        } // namespace shader

        //
        //
        //
        //
        //

        void clear(const unsigned int value) {}

        //
        //
        //
        //
        //

        void clear(const float r, const float g, const float b, const float a) {}

        //
        //
        //
        //
        //

        void resize_viewport(const unsigned int width, const unsigned int height) {}

        //
        //
        //
        //
        //

        void draw_buffers(const IBO *ibo) {}
    } // namespace agnostic

    //
    //
    //
    //
    //

    namespace vulkan {

        //
        //
        //
        //
        //

        namespace vbo {
            VBO create(const float *data, const unsigned int vertex_size, const unsigned short count) { return {0, 0, 0}; }
        } // namespace vbo

        //
        //
        //
        //
        //

        namespace ibo {
            IBO create(const unsigned short *data, const unsigned short count) { return {0, 0}; }
        } // namespace ibo

        //
        //
        //
        //
        //

        namespace shader {
            Shader create(const char *vert_src, const char *frag_src) { return {0}; }
            void bind(const Shader *shader) {}
            void send_int(const Shader *shader, const char *uniform_name, const int data) {}
            void send_float(const Shader *shader, const char *uniform_name, const float data) {}
            void send_vec2(const Shader *shader, const char *uniform_name, const float *data) {}
            void send_vec3(const Shader *shader, const char *uniform_name, const float *data) {}
            void send_vec4(const Shader *shader, const char *uniform_name, const float *data) {}
            void send_mat3(const Shader *shader, const char *uniform_name, const float *data) {}
            void send_mat4(const Shader *shader, const char *uniform_name, const float *data) {}
        } // namespace shader

        //
        //
        //
        //
        //

        void clear(const unsigned int value) {}

        //
        //
        //
        //
        //

        void clear(const float r, const float g, const float b, const float a) {}

        //
        //
        //
        //
        //

        void resize_viewport(const unsigned int width, const unsigned int height) {}

        //
        //
        //
        //
        //

        void draw_buffers(const IBO *ibo) {}
    } // namespace vulkan

    //
    //
    //
    //
    //

    namespace direct3d {

        //
        //
        //
        //
        //

        namespace vbo {
            VBO create(const float *data, const unsigned int vertex_size, const unsigned short count) { return {0, 0, 0}; }
        } // namespace vbo

        //
        //
        //
        //
        //

        namespace ibo {
            IBO create(const unsigned short *data, const unsigned short count) { return {0, 0}; }
        } // namespace ibo

        //
        //
        //
        //
        //

        namespace shader {
            Shader create(const char *vert_src, const char *frag_src) { return {0}; }
            void bind(const Shader *shader) {}
            void send_int(const Shader *shader, const char *uniform_name, const int data) {}
            void send_float(const Shader *shader, const char *uniform_name, const float data) {}
            void send_vec2(const Shader *shader, const char *uniform_name, const float *data) {}
            void send_vec3(const Shader *shader, const char *uniform_name, const float *data) {}
            void send_vec4(const Shader *shader, const char *uniform_name, const float *data) {}
            void send_mat3(const Shader *shader, const char *uniform_name, const float *data) {}
            void send_mat4(const Shader *shader, const char *uniform_name, const float *data) {}
        } // namespace shader

        //
        //
        //
        //
        //

        void clear(const unsigned int value) {}

        //
        //
        //
        //
        //

        void clear(const float r, const float g, const float b, const float a) {}

        //
        //
        //
        //
        //

        void resize_viewport(const unsigned int width, const unsigned int height) {}

        //
        //
        //
        //
        //

        void draw_buffers(const IBO *ibo) {}

        //
        //
        //
        //
        //

    } // namespace direct3d

    //
    //
    //
    //
    //

    namespace opengl {

        //
        //
        //
        //
        //

        static bool s_vao_needs_init = true;
        static unsigned int s_vao_id, s_vbo_count = 0, s_vbo_size = 0;
        namespace vbo {
            VBO create(const float *data, const unsigned int vertex_size, const unsigned short count) {
                if (s_vao_needs_init) {
                    s_vao_needs_init = false;
                    glGenVertexArrays(1, &s_vao_id);
                    glBindVertexArray(s_vao_id);
                }
                VBO result;
                result.size = vertex_size * count;
                glGenBuffers(1, &result.id);
                glBindBuffer(GL_ARRAY_BUFFER, result.id);
                glBufferData(GL_ARRAY_BUFFER, result.size, data, GL_STATIC_DRAW);

                glEnableVertexAttribArray(s_vbo_count);
                glVertexAttribPointer(s_vbo_count, count, GL_FLOAT, GL_FALSE, vertex_size, (const void *)0);
                s_vbo_size += result.size;
                ++s_vbo_count;
                return result;
            }
        } // namespace vbo

        //
        //
        //
        //
        //

        namespace ibo {
            IBO create(const unsigned short *data, const unsigned short count) {
                IBO result;
                result.count = count;
                glGenBuffers(1, &result.id);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, result.id);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned short), data, GL_STATIC_DRAW);
                return result;
            }
        } // namespace ibo

        //
        //
        //
        //
        //

        namespace shader {
            Shader create(const char *vert_src, const char *frag_src) {
                unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
                glShaderSource(vertexShader, 1, &vert_src, 0);
                glCompileShader(vertexShader);

#ifndef _CONFIG_RELEASE
                int temp = 0;
                glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &temp);
                if (temp == GL_FALSE) {
                    temp = 0;
                    glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &temp);
                    std::vector<char> infoLog(temp);
                    glGetShaderInfoLog(vertexShader, temp, &temp, &infoLog[0]);
                    glDeleteShader(vertexShader);
                    std::cout << "Vertex Shader failed to compile\n" << infoLog.data() << '\n';
                    return {0};
                }
#endif

                unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
                glShaderSource(fragmentShader, 1, &frag_src, 0);
                glCompileShader(fragmentShader);

#ifndef _CONFIG_RELEASE
                glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &temp);
                if (temp == GL_FALSE) {
                    glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &temp);
                    std::vector<char> infoLog(temp);
                    glGetShaderInfoLog(fragmentShader, temp, &temp, &infoLog[0]);
                    glDeleteShader(fragmentShader);
                    glDeleteShader(vertexShader);
                    std::cout << "Fragment Shader failed to compile\n" << infoLog.data() << '\n';
                    return {0};
                }
#endif

                Shader result;
                result.id = glCreateProgram();

                glAttachShader(result.id, vertexShader);
                glAttachShader(result.id, fragmentShader);
                glLinkProgram(result.id);

#ifndef _CONFIG_RELEASE
                glGetProgramiv(result.id, GL_LINK_STATUS, (int *)&temp);
                if (temp == GL_FALSE) {
                    glGetProgramiv(result.id, GL_INFO_LOG_LENGTH, &temp);
                    std::vector<char> infoLog(temp);
                    glGetProgramInfoLog(result.id, temp, &temp, &infoLog[0]);
                    glDeleteProgram(result.id);
                    glDeleteShader(vertexShader);
                    glDeleteShader(fragmentShader);
                    std::cout << "Failed to create Shader Program\n" << infoLog.data() << '\n';
                    return {0};
                }
#endif
                glDetachShader(result.id, vertexShader);
                glDetachShader(result.id, fragmentShader);
                return result;
            }
            void bind(const Shader *shader) { glUseProgram(shader->id); }
            void send_int(const Shader *shader, const char *uniform_name, const int data) {}
            void send_float(const Shader *shader, const char *uniform_name, const float data) {
                glUniform1f(glGetUniformLocation(shader->id, uniform_name), data);
            }
            void send_vec2(const Shader *shader, const char *uniform_name, const float *data) {
                glUniform2fv(glGetUniformLocation(shader->id, uniform_name), 1, data);
            }
            void send_vec3(const Shader *shader, const char *uniform_name, const float *data) {
                glUniform3fv(glGetUniformLocation(shader->id, uniform_name), 1, data);
            }
            void send_vec4(const Shader *shader, const char *uniform_name, const float *data) {
                glUniform4fv(glGetUniformLocation(shader->id, uniform_name), 1, data);
            }
            void send_mat3(const Shader *shader, const char *uniform_name, const float *data) {
                glUniformMatrix3fv(glGetUniformLocation(shader->id, uniform_name), 1, GL_FALSE, data);
            }
            void send_mat4(const Shader *shader, const char *uniform_name, const float *data) {
                glUniformMatrix4fv(glGetUniformLocation(shader->id, uniform_name), 1, GL_FALSE, data);
            }
        } // namespace shader

        //
        //
        //
        //
        //

        void clear(const unsigned int value) {
            glClear(GL_COLOR_BUFFER_BIT);
            const float fac = 1.f / 255;
            const float r = static_cast<const unsigned char>(value >> 24);
            const float g = static_cast<const unsigned char>(value >> 16);
            const float b = static_cast<const unsigned char>(value >> 8);
            const float a = static_cast<const unsigned char>(value);
            glClearColor(r * fac, g * fac, b * fac, a * fac);
        }

        //
        //
        //
        //
        //

        void clear(const float r, const float g, const float b, const float a) {
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(r, g, b, a);
        }

        //
        //
        //
        //
        //

        void resize_viewport(const unsigned int width, const unsigned int height) { glViewport(0, 0, width, height); }

        //
        //
        //
        //
        //

        void draw_buffers(const IBO *ibo) { glDrawElements(GL_TRIANGLES, ibo->count, GL_UNSIGNED_SHORT, nullptr); }
    } // namespace opengl
}}}   // namespace coel::renderer::_internal
