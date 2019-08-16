#include "window.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace coel {
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
            // renderer::resize_viewport(width, height);
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
    }
    const bool Window::update() {
        GLFWwindow *window = reinterpret_cast<GLFWwindow *>(window_handle);
        glfwPollEvents();
        glfwSwapBuffers(window);
        glClear(GL_COLOR_BUFFER_BIT);
        return !glfwWindowShouldClose(window);
    }
    Shader::Shader(const char *const vert_src, const char *const frag_src) : vert_src(vert_src), frag_src(frag_src) {
        int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vert_src, NULL);
        glCompileShader(vertexShader);

        int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &frag_src, NULL);
        glCompileShader(fragmentShader);

        int shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        glUseProgram(shaderProgram);
    }
    Texture::Texture(const char *const filepath) : filepath(filepath) {}
    Model::Model(const char *const filepath) {}
    Model::Model(const float *pos_data, const unsigned short *ind_data) {}
    Material::Material(const Shader *const shader, const Texture textures[32]) : shader(shader), textures(textures) {}
    Renderable::Renderable(const Model *const model, const Material *const material) : model(model), material(material) {}
    namespace renderer {
        void clear(unsigned int color) {}
        void submit(const Renderable *const r) {}
        void flush() {}
    } // namespace renderer
} // namespace coel
