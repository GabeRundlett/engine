#include <Renderer.hpp>
#include <Window.hpp>

#define GLFW_INCLUDE_NONE 1
#include <GLFW/glfw3.h>

namespace Coel { namespace Windows {
    namespace defaultCallbacks {
        static void keyPress(const KeyPress &) {}
        static void keyRepeat(const KeyRepeat &) {}
        static void keyRelease(const KeyRelease &) {}

        static void mousePress(const MousePress &) {}
        static void mouseRelease(const MouseRelease &) {}
        static void mouseMove(const MouseMove &) {}
        static void mouseScroll(const MouseScroll &) {}

        static void windowMove(const WindowMove &) {}
        static void windowResize(const WindowResize &) {}
        static void windowFocus(const WindowFocus &) {}
        static void windowDefocus(const WindowDefocus &) {}
        static void windowClose(const WindowClose &) {}
    } // namespace defaultCallbacks

    Window::Window(const int width, const int height, const char *const title)
        : mKeyPressCallback(defaultCallbacks::keyPress), mKeyRepeatCallback(defaultCallbacks::keyRepeat),
          mKeyReleaseCallback(defaultCallbacks::keyRelease), mMousePressCallback(defaultCallbacks::mousePress),
          mMouseReleaseCallback(defaultCallbacks::mouseRelease), mMouseMoveCallback(defaultCallbacks::mouseMove),
          mMouseScrollCallback(defaultCallbacks::mouseScroll), mWindowMoveCallback(defaultCallbacks::windowMove),
          mWindowResizeCallback(defaultCallbacks::windowResize), mWindowFocusCallback(defaultCallbacks::windowFocus),
          mWindowDefocusCallback(defaultCallbacks::windowDefocus), mWindowCloseCallback(defaultCallbacks::windowClose) {

        // DEBUG_BEGIN_FUNC_PROFILE;

        glfwInit();
        {
            // DEBUG_BEGIN_PROFILE(glfwCreateWindow);
            mWindow = glfwCreateWindow(width, height, title, nullptr, nullptr);
            if (mWindow)
                mFlags |= Flags::OPEN_STATUS;
            else
                mFlags &= ~Flags::OPEN_STATUS;
        }

        Renderer::setAPI(RendererAPI::OPENGL);
        mContext = createContext(mWindow);
        Renderer::init();

        glfwSwapInterval(0);

        glfwSetWindowUserPointer(mWindow, this);
        glfwSetKeyCallback(mWindow, [](GLFWwindow *w, int key, int scancode, int action, int mods) {
            Window *const window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(w));
            switch (action) {
            case GLFW_PRESS: window->mKeyPressCallback({key, scancode, mods}); break;
            case GLFW_REPEAT: window->mKeyRepeatCallback({key, scancode, mods}); break;
            case GLFW_RELEASE: window->mKeyReleaseCallback({key, scancode, mods}); break;
            }
        });
        glfwSetMouseButtonCallback(mWindow, [](GLFWwindow *w, int button, int action, int mods) {
            Window *const window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(w));
            switch (action) {
            case GLFW_PRESS: window->mMousePressCallback({button, mods}); break;
            case GLFW_RELEASE: window->mMouseReleaseCallback({button, mods}); break;
            }
        });
        glfwSetCursorPosCallback(mWindow, [](GLFWwindow *w, double xPos, double yPos) {
            Window *const window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(w));
            window->mMouseMoveCallback({xPos, yPos});
        });
        glfwSetScrollCallback(mWindow, [](GLFWwindow *w, double xOffset, double yOffset) {
            Window *const window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(w));
            window->mMouseScrollCallback({xOffset, yOffset});
        });
        glfwSetWindowPosCallback(mWindow, [](GLFWwindow *w, int xPos, int yPos) {
            Window *const window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(w));
            window->mWindowMoveCallback({xPos, yPos});
        });
        glfwSetWindowSizeCallback(mWindow, [](GLFWwindow *w, int width, int height) {
            Window *const window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(w));
            Renderer::set_viewport(0, 0, width, height);
            window->mWidth = width, window->mHeight = height;
            window->mWindowResizeCallback({width, height});
        });
        glfwSetWindowFocusCallback(mWindow, [](GLFWwindow *w, int focus) {
            Window *const window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(w));
            switch (focus) {
            case GLFW_TRUE: window->mWindowFocusCallback({}); return;
            case GLFW_FALSE: window->mWindowDefocusCallback({}); return;
            }
        });
        glfwSetWindowCloseCallback(mWindow, [](GLFWwindow *w) {
            Window *const window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(w));
            window->mWindowCloseCallback({});
        });
    }

    Window::~Window() {}

    bool Window::shouldClose() const {
        // DEBUG_BEGIN_FUNC_PROFILE;

        return glfwWindowShouldClose(mWindow);
    }

    void Window::update() {
        // DEBUG_BEGIN_FUNC_PROFILE;

        mContext->swap();
        glfwPollEvents();
    }

    void Window::bind() {
        // DEBUG_BEGIN_FUNC_PROFILE;

        mContext->bind();
    }

    void Window::close() {
        // DEBUG_BEGIN_FUNC_PROFILE;

        mFlags &= ~Flags::OPEN_STATUS;
        glfwDestroyWindow(mWindow);
    }

    void Window::onKeyPress(void (*const f)(const KeyPress &)) { mKeyPressCallback = f; }
    void Window::onKeyRepeat(void (*const f)(const KeyRepeat &)) { mKeyRepeatCallback = f; }
    void Window::onKeyRelease(void (*const f)(const KeyRelease &)) { mKeyReleaseCallback = f; }

    void Window::onMousePress(void (*const f)(const MousePress &)) { mMousePressCallback = f; };
    void Window::onMouseRelease(void (*const f)(const MouseRelease &)) { mMouseReleaseCallback = f; };
    void Window::onMouseMove(void (*const f)(const MouseMove &)) { mMouseMoveCallback = f; };
    void Window::onMouseScroll(void (*const f)(const MouseScroll &)) { mMouseScrollCallback = f; };

    void Window::onWindowMove(void (*const f)(const WindowMove &)) { mWindowMoveCallback = f; };
    void Window::onWindowResize(void (*const f)(const WindowResize &)) { mWindowResizeCallback = f; };
    void Window::onWindowFocus(void (*const f)(const WindowFocus &)) { mWindowFocusCallback = f; };
    void Window::onWindowDefocus(void (*const f)(const WindowDefocus &)) { mWindowDefocusCallback = f; };
    void Window::onWindowClose(void (*const f)(const WindowClose &)) { mWindowCloseCallback = f; };
}} // namespace Coel::Windows
