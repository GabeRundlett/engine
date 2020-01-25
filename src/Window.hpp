#pragma once

#include "Events.hpp"
#include "Context.hpp"

namespace Coel {
    class Window {
      public:
        virtual bool shouldClose() const = 0;
        virtual bool isOpen() const = 0;

        virtual void update() = 0;
        virtual void bind() = 0;
        virtual void close() = 0;

        virtual void hideCursor(const bool val) const = 0;
        virtual void setCursorPos(const Math::Vec2d &pos) const = 0;

        virtual double getTime() const = 0;

        virtual void onKeyPress(void (*const f)(const KeyPress &)) = 0;
        virtual void onKeyRepeat(void (*const f)(const KeyRepeat &)) = 0;
        virtual void onKeyRelease(void (*const f)(const KeyRelease &)) = 0;

        virtual void onMousePress(void (*const f)(const MousePress &)) = 0;
        virtual void onMouseRelease(void (*const f)(const MouseRelease &)) = 0;
        virtual void onMouseMove(void (*const f)(const MouseMove &)) = 0;
        virtual void onMouseScroll(void (*const f)(const MouseScroll &)) = 0;

        virtual void onWindowMove(void (*const f)(const WindowMove &)) = 0;
        virtual void onWindowResize(void (*const f)(const WindowResize &)) = 0;
        virtual void onWindowFocus(void (*const f)(const WindowFocus &)) = 0;
        virtual void onWindowDefocus(void (*const f)(const WindowDefocus &)) = 0;
        virtual void onWindowClose(void (*const f)(const WindowClose &)) = 0;
    };

} // namespace Coel

namespace Coel { namespace Windows {
    class Window final : public ::Coel::Window {
        enum Flags { NONE, OPEN_STATUS };

        GLFWwindow *mWindow;
        Scope<Context> mContext;
        int mWidth, mHeight;
        unsigned char mFlags;

        void (*mKeyPressCallback)(const KeyPress &);
        void (*mKeyRepeatCallback)(const KeyRepeat &);
        void (*mKeyReleaseCallback)(const KeyRelease &);

        void (*mMousePressCallback)(const MousePress &);
        void (*mMouseReleaseCallback)(const MouseRelease &);
        void (*mMouseMoveCallback)(const MouseMove &);
        void (*mMouseScrollCallback)(const MouseScroll &);

        void (*mWindowMoveCallback)(const WindowMove &);
        void (*mWindowResizeCallback)(const WindowResize &);
        void (*mWindowFocusCallback)(const WindowFocus &);
        void (*mWindowDefocusCallback)(const WindowDefocus &);
        void (*mWindowCloseCallback)(const WindowClose &);

      public:
        Window(const int width, const int height, const char *const title);
        ~Window();

        bool shouldClose() const override;
        bool isOpen() const override { return mFlags | Flags::OPEN_STATUS; }

        void update() override;
        void bind() override;
        void close() override;

        void hideCursor(const bool val) const override;
        void setCursorPos(const Math::Vec2d &pos) const override;

        double getTime() const override;

        void onKeyPress(void (*const f)(const KeyPress &)) override;
        void onKeyRepeat(void (*const f)(const KeyRepeat &)) override;
        void onKeyRelease(void (*const f)(const KeyRelease &)) override;

        void onMousePress(void (*const f)(const MousePress &)) override;
        void onMouseRelease(void (*const f)(const MouseRelease &)) override;
        void onMouseMove(void (*const f)(const MouseMove &)) override;
        void onMouseScroll(void (*const f)(const MouseScroll &)) override;

        void onWindowMove(void (*const f)(const WindowMove &)) override;
        void onWindowResize(void (*const f)(const WindowResize &)) override;
        void onWindowFocus(void (*const f)(const WindowFocus &)) override;
        void onWindowDefocus(void (*const f)(const WindowDefocus &)) override;
        void onWindowClose(void (*const f)(const WindowClose &)) override;
    };
}} // namespace Coel::Windows

namespace Coel {
    static inline Ref<Window> createWindow(const unsigned int width, const unsigned int height, const char *const title) {
#if _WIN64 || _WIN32
        return createRef<Windows::Window>(width, height, title);
#elif __APPLE__ && __MACH__
        return createRef<Windows::Window>(width, height, title);
#elif __linux__
        return createRef<Windows::Window>(width, height, title);
#endif
    }
} // namespace Coel
