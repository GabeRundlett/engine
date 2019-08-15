#include "renderer.hpp"
#include "glad/glad.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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

        namespace texture {
            Texture create(const char *file_path) { return {0, 0, 0}; }
        } // namespace texture

        //
        //
        //
        //
        //

        namespace batch {
            void init() {}
            void begin(Shader *const shader) {}
            void submit(const float pos[2], const float size[2]) {}
            void submit(const float x, const float y, const float w, const float h, const Texture *const texture) {}
            void end() {}
        } // namespace batch

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

        namespace texture {
            Texture create(const char *file_path) { return {0, 0, 0}; }
        } // namespace texture

        //
        //
        //
        //
        //

        namespace batch {
            void init() {}
            void begin(Shader *const shader) {}
            void submit(const float pos[2], const float size[2]) {}
            void submit(const float x, const float y, const float w, const float h, const Texture *const texture) {}
            void end() {}
        } // namespace batch

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

        namespace texture {
            Texture create(const char *file_path) { return {0, 0, 0}; }
        } // namespace texture

        //
        //
        //
        //
        //

        namespace batch {
            void init() {}
            void begin(Shader *const shader) {}
            void submit(const float pos[2], const float size[2]) {}
            void submit(const float x, const float y, const float w, const float h, const Texture *const texture) {}
            void end() {}
        } // namespace batch

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
            VBO create(const float *data, const unsigned int vertex_dim, const unsigned short count) {
                if (s_vbo_count < 32) {
                    if (s_vao_needs_init) {
                        s_vao_needs_init = false;
                        glGenVertexArrays(1, &s_vao_id);
                        glBindVertexArray(s_vao_id);
                    }
                    VBO result;
                    result.dim = vertex_dim;
                    result.size = vertex_dim * count * sizeof(float);
                    glGenBuffers(1, &result.id);
                    glBindBuffer(GL_ARRAY_BUFFER, result.id);
                    glBufferData(GL_ARRAY_BUFFER, result.size, data, GL_STATIC_DRAW);
                    glEnableVertexAttribArray(s_vbo_count);
                    glVertexAttribPointer(s_vbo_count, vertex_dim, GL_FLOAT, GL_FALSE, vertex_dim * sizeof(float),
                                          (const void *)0);
                    s_vbo_size += result.size;
                    ++s_vbo_count;
                    return result;
                }
                return {0, vertex_dim * count * sizeof(float), vertex_dim};
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
            void send_int(const Shader *shader, const char *uniform_name, const int data) {
                glUniform1i(glGetUniformLocation(shader->id, uniform_name), data);
            }
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

        namespace texture {
            Texture slot[32];
            unsigned int texture_count = 0;
            Texture create(const char *file_path) {
                Texture result;
                unsigned char *data = stbi_load(file_path, &result.width, &result.height, &result.channels, 0);
                glGenTextures(1, &result.id);
                glBindTexture(GL_TEXTURE_2D, result.id);

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, result.width, result.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
                stbi_image_free(data);
                slot[texture_count] = result;
                ++texture_count;
                return result;
            }
        } // namespace texture

        //
        //
        //
        //
        //

        namespace batch {
            // max sprites is 16383 because that is the floored version of 65535 / 4
            struct VertexData {
                float x, y, u, v;
                float tid;
            };
            static constexpr unsigned int s_max_sprites = 16383, s_vertex_size = sizeof(VertexData),
                                          s_sprite_size = s_vertex_size * 4, s_max_index = s_max_sprites * 6,
                                          s_buffer_size = s_sprite_size * s_max_sprites;

            static unsigned int s_vao_id, s_vbo_id, s_ibo_id;
            static unsigned short s_indices[s_max_index];
            static unsigned int s_index_count = 0;
            static VertexData *s_buffer_pointer;
            static Shader *s_current_shader;

            void init() {
                // Generate an OpenGL VAO
                glGenVertexArrays(1, &s_vao_id);
                glBindVertexArray(s_vao_id);
                // Generate the OpenGL data buffer (to hold the vertex data)
                glGenBuffers(1, &s_vbo_id);
                glBindBuffer(GL_ARRAY_BUFFER, s_vbo_id);
                glBufferData(GL_ARRAY_BUFFER, s_buffer_size, nullptr, GL_DYNAMIC_DRAW);
                // Assign the vertex attributes
                glEnableVertexAttribArray(0);
                glEnableVertexAttribArray(1);
                glEnableVertexAttribArray(2);
                glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, s_vertex_size, reinterpret_cast<const void *>(0));
                glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, s_vertex_size, reinterpret_cast<const void *>(8));
                glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, s_vertex_size, reinterpret_cast<const void *>(16));
                // Fill the index array
                unsigned int offset = 0;
                for (unsigned int i = 0; i < s_max_index; i += 6) {
                    s_indices[i + 0] = offset + 0;
                    s_indices[i + 1] = offset + 1;
                    s_indices[i + 2] = offset + 2;
                    s_indices[i + 3] = offset + 1;
                    s_indices[i + 4] = offset + 3;
                    s_indices[i + 5] = offset + 2;
                    offset += 4;
                }
                // Generate the OpenGL index buffer
                glGenBuffers(1, &s_ibo_id);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_ibo_id);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, s_max_index * sizeof(unsigned short), s_indices, GL_STATIC_DRAW);
            }
            void begin(Shader *const shader) {
                shader::bind(shader);
                s_current_shader = shader;
                glBindBuffer(GL_ARRAY_BUFFER, s_vbo_id);
                s_buffer_pointer = reinterpret_cast<VertexData *>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
            }
            void submit(const float pos[2], const float size[2], const Texture *const texture) {
                submit(pos[0], pos[1], size[0], size[1], texture);
            }
            void submit(const float x, const float y, const float w, const float h, const Texture *const texture) {
                s_index_count += 6;
                if (s_index_count > s_max_index) {
                    end();
                    begin(s_current_shader);
                }
                float texture_id = -1;

                if (texture)
                    for (unsigned int i = 0; i < 32; ++i)
                        if (texture->id == texture::slot[i].id) {
                            texture_id = i;
                            break;
                        }

                s_buffer_pointer->x = x;
                s_buffer_pointer->y = y;
                s_buffer_pointer->u = 0;
                s_buffer_pointer->v = 1;
                s_buffer_pointer->tid = texture_id;
                ++s_buffer_pointer;

                s_buffer_pointer->x = x + w;
                s_buffer_pointer->y = y;
                s_buffer_pointer->u = w / h;
                s_buffer_pointer->v = 1;
                s_buffer_pointer->tid = texture_id;
                ++s_buffer_pointer;

                s_buffer_pointer->x = x;
                s_buffer_pointer->y = y + h;
                s_buffer_pointer->u = 0;
                s_buffer_pointer->v = 0;
                s_buffer_pointer->tid = texture_id;
                ++s_buffer_pointer;

                s_buffer_pointer->x = x + w;
                s_buffer_pointer->y = y + h;
                s_buffer_pointer->u = w / h;
                s_buffer_pointer->v = 0;
                s_buffer_pointer->tid = texture_id;
                ++s_buffer_pointer;
            }
            void end() {
                glUnmapBuffer(GL_ARRAY_BUFFER);
                /*for (unsigned int i = 0; i < 32; ++i) {
                    glActiveTexture(GL_TEXTURE0 + i);
                    glBindTexture(GL_TEXTURE_2D, texture::slot[i].id);
                }*/

                glBindVertexArray(s_vao_id);
                glDrawElements(GL_TRIANGLES, s_index_count, GL_UNSIGNED_SHORT, nullptr);
                s_index_count = 0;
            }
        } // namespace batch

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
