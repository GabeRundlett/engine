#include "window.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <stb/image.hpp>

#include <iostream>

namespace coel {
    static constexpr unsigned int s_vbuffer_size = 4096, s_ibuffer_size = 4096;

    static unsigned int s_vao_id, s_vbo_id, s_ibo_id;
    static unsigned char *s_vbuffer_pointer;
    static unsigned short *s_ibuffer_pointer;
    static unsigned int s_vertex_count = 0, s_index_count = 0, s_texture_count = 0;

    Window::Window(const unsigned int width, const unsigned int height, const char *const title)
        : width(width), height(height), title(title) {
        // init window manager
        glfwInit();
        GLFWwindow *result = glfwCreateWindow(width, height, title, nullptr, nullptr);
        window_handle = reinterpret_cast<void *>(result);
        glfwMakeContextCurrent(result);
        // window manager prop
        glfwSwapInterval(false);
        glfwSetWindowUserPointer(result, this);
        // init opengl context
        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        // opengl prop
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        // set window callbacks
        glfwSetKeyCallback(result, [](GLFWwindow *w, int key, int scancode, int action, int mods) {
            Window *const window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(w));
            switch (action) {
            case GLFW_PRESS: window->key_press({key, scancode, mods}); break;
            case GLFW_REPEAT: window->key_repeat({key, scancode, mods}); break;
            case GLFW_RELEASE: window->key_release({key, scancode, mods}); break;
            }
        });
        glfwSetMouseButtonCallback(result, [](GLFWwindow *w, int button, int action, int mods) {
            Window *const window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(w));
            switch (action) {
            case GLFW_PRESS: window->mouse_press({button, mods}); break;
            case GLFW_RELEASE: window->mouse_release({button, mods}); break;
            }
        });
        glfwSetCursorPosCallback(result, [](GLFWwindow *w, double xPos, double yPos) {
            Window *const window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(w));
            window->mouse_move({xPos, yPos});
        });
        glfwSetScrollCallback(result, [](GLFWwindow *w, double xOffset, double yOffset) {
            Window *const window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(w));
            window->mouse_scroll({xOffset, yOffset});
        });
        glfwSetWindowPosCallback(result, [](GLFWwindow *w, int xPos, int yPos) {
            Window *const window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(w));
            window->window_move({xPos, yPos});
        });
        glfwSetWindowSizeCallback(result, [](GLFWwindow *w, int width, int height) {
            Window *const window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(w));
            renderer::viewport(width, height);
            window->window_resize({width, height});
        });
        glfwSetWindowFocusCallback(result, [](GLFWwindow *w, int focus) {
            Window *const window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(w));
            switch (focus) {
            case GLFW_TRUE: window->window_focus({}); return;
            case GLFW_FALSE: window->window_defocus({}); return;
            }
        });
        glfwSetWindowCloseCallback(result, [](GLFWwindow *w) {
            Window *const window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(w));
            window->window_close({});
        });

        // init renderer
        glGenVertexArrays(1, &s_vao_id);
        glBindVertexArray(s_vao_id);

        glGenBuffers(1, &s_vbo_id);
        glBindBuffer(GL_ARRAY_BUFFER, s_vbo_id);
        glBufferData(GL_ARRAY_BUFFER, s_vbuffer_size, nullptr, GL_DYNAMIC_DRAW);

        glGenBuffers(1, &s_ibo_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_ibo_id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, s_ibuffer_size, nullptr, GL_DYNAMIC_DRAW);

        s_vbuffer_pointer = reinterpret_cast<unsigned char *>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
        s_ibuffer_pointer = reinterpret_cast<unsigned short *>(glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY));
    }
    const bool Window::update() {
        GLFWwindow *window = reinterpret_cast<GLFWwindow *>(window_handle);
        glfwPollEvents();
        glfwSwapBuffers(window);
        return !glfwWindowShouldClose(window);
    }
    float Window::get_time() { return glfwGetTime(); }
    Shader::Shader(const char *const vert_src, const char *const frag_src) : vert_src(vert_src), frag_src(frag_src) {
        int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vert_src, NULL);
        glCompileShader(vertexShader);

        int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &frag_src, NULL);
        glCompileShader(fragmentShader);

        id = glCreateProgram();
        glAttachShader(id, vertexShader);
        glAttachShader(id, fragmentShader);
        glLinkProgram(id);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        glUseProgram(id);
    }
    void Shader::send_int(const char *const name, const int value) const { glUniform1i(glGetUniformLocation(id, name), value); }
    Texture::Texture(const char *const filepath) : filepath(filepath) {
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load(filepath, &width, &height, &channels, 0);

        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        switch (channels) {
        case 3: glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data); break;
        case 4: glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); break;
        default: glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); break;
        }
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
        ++s_texture_count;
    }
    Model::Model(const char *const filepath) : vdata(nullptr), idata(nullptr), vsize(0), isize(0) {}
    Model::Model(const void *vdata, const unsigned int vsize, const unsigned short *idata, const unsigned int isize)
        : vdata(vdata), idata(idata), vsize(vsize), isize(isize) {}
    void Material::init_tex_mat(const Shader *const shader, const unsigned int slot, const Texture *texture,
                                const char *const name) {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, texture->id);
        shader->send_int(name, slot);
    }
    Renderable::Renderable(const Model *const model, const Material *const material) : model(model), material(material) {}
    namespace renderer {
        namespace _internal {
            static unsigned short s_layout_count = 0, s_layout_stride = 0;
            static unsigned char *s_layout_begin = 0;
            void setup_layout(const LayoutType type, const unsigned int count) {
                ++s_layout_count;
                switch (type) {
                case LayoutType::Float: s_layout_stride += 4 * count; break;
                case LayoutType::Int: s_layout_stride += 4 * count; break;
                case LayoutType::UInt: s_layout_stride += 4 * count; break;
                case LayoutType::Short: s_layout_stride += 2 * count; break;
                case LayoutType::UShort: s_layout_stride += 2 * count; break;
                case LayoutType::Byte: s_layout_stride += count; break;
                case LayoutType::UByte: s_layout_stride += count; break;
                default: break; // Invalid layout type
                }
            }
            void set_layout(const unsigned int i, const LayoutType type, const unsigned int count) {
                glEnableVertexAttribArray(i);
                unsigned int gl_type;
                switch (type) {
                case LayoutType::Float:
                    glVertexAttribPointer(i, count, GL_FLOAT, GL_FALSE, s_layout_stride, s_layout_begin);
                    s_layout_begin += 4 * count;
                    break;
                case LayoutType::Int:
                    glVertexAttribPointer(i, count, GL_INT, GL_FALSE, s_layout_stride, s_layout_begin);
                    s_layout_begin += 4 * count;
                    break;
                case LayoutType::UInt:
                    glVertexAttribPointer(i, count, GL_UNSIGNED_INT, GL_FALSE, s_layout_stride,
                                          reinterpret_cast<const void *>(0));
                    s_layout_begin += 4 * count;
                    break;
                case LayoutType::Short:
                    glVertexAttribPointer(i, count, GL_SHORT, GL_FALSE, s_layout_stride, s_layout_begin);
                    s_layout_begin += 2 * count;
                    break;
                case LayoutType::UShort:
                    glVertexAttribPointer(i, count, GL_UNSIGNED_SHORT, GL_FALSE, s_layout_stride, s_layout_begin);
                    s_layout_begin += 2 * count;
                    break;
                case LayoutType::Byte:
                    glVertexAttribPointer(i, count, GL_BYTE, GL_FALSE, s_layout_stride, s_layout_begin);
                    s_layout_begin += count;
                    break;
                case LayoutType::UByte:
                    glVertexAttribPointer(i, count, GL_UNSIGNED_BYTE, GL_FALSE, s_layout_stride, s_layout_begin);
                    s_layout_begin += count;
                    break;
                default: break; // Invalid layout type
                }
            }
        } // namespace _internal
        void clear(const unsigned int color) {
            const float fac = 1.f / 255;
            const float r = static_cast<const unsigned char>(color >> 24);
            const float g = static_cast<const unsigned char>(color >> 16);
            const float b = static_cast<const unsigned char>(color >> 8);
            const float a = static_cast<const unsigned char>(color);
            glClearColor(r * fac, g * fac, b * fac, a * fac);
            glClear(GL_COLOR_BUFFER_BIT);
        }
        void clear(const float r, const float g, const float b, const float a) {
            glClearColor(r, g, b, a);
            glClear(GL_COLOR_BUFFER_BIT);
        }
        void submit(const Model *const model) {
            const unsigned int vsize = model->vsize, isize = model->isize;
            const unsigned char *vdata = reinterpret_cast<const unsigned char *>(model->vdata);
            const unsigned short *idata = model->idata;
            for (unsigned int i = 0; i < vsize; ++i)
                s_vbuffer_pointer[i] = vdata[i];
            s_vbuffer_pointer += vsize;
            const unsigned short index_count = isize / sizeof(unsigned short);
            for (unsigned int i = 0; i < index_count; ++i)
                s_ibuffer_pointer[i] = idata[i] + s_vertex_count;
            s_vertex_count += vsize / _internal::s_layout_stride;
            s_ibuffer_pointer += index_count;
            s_index_count += index_count;
        }
        void flush() {
            glUnmapBuffer(GL_ARRAY_BUFFER);
            glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
            glBindVertexArray(s_vao_id);
            glDrawElements(GL_TRIANGLES, s_index_count, GL_UNSIGNED_SHORT, nullptr);
            s_vbuffer_pointer = reinterpret_cast<unsigned char *>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
            s_ibuffer_pointer = reinterpret_cast<unsigned short *>(glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY));
            s_vertex_count = 0;
            s_index_count = 0;
        }
        void viewport(const float width, const float height) { glViewport(0, 0, width, height); }
    } // namespace renderer
} // namespace coel
