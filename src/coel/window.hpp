namespace coel {
    struct KeyPress {
        int key, scancode, mods;
    };
    struct KeyRepeat {
        int key, scancode, mods;
    };
    struct KeyRelease {
        int key, scancode, mods;
    };

    struct MousePress {
        int button, mods;
    };
    struct MouseRelease {
        int button, mods;
    };
    struct MouseScroll {
        double x, y;
    };
    struct MouseMove {
        double x, y;
    };

    struct WindowMove {
        int x, y;
    };
    struct WindowResize {
        int width, height;
    };
    struct WindowClose {};
    struct WindowFocus {};
    struct WindowDefocus {};

    enum KeyCode : const unsigned short {
        Space = 32,
        Apostrophe = 39,
        Comma = 44,
        Minus = 45,
        Period = 46,
        Slash = 47,

        SemiColon = 59,
        Equal = 60,

        LeftBracket = 91,
        RightBracket = 93,
        Backslash = 92,
        GraveAccent = 96,

        World1 = 161,
        World2 = 162,

        Escape = 256,
        Enter = 257,
        Tab = 258,
        Backspace = 259,
        Insert = 260,
        Delete = 261,
        Left = 262,
        Right = 263,
        Down = 264,
        Up = 265,
        PageUp = 266,
        PageDown = 267,
        Home = 268,
        End = 269,
        CapsLock = 280,
        ScrollLock = 281,
        NumLock = 282,
        PrintScreen = 283,
        PauseBreak = 284,

        LeftShift = 340,
        LeftControl = 341,
        LeftAlt = 342,
        LeftMenu = 343,

        RightShift = 344,
        RightControl = 345,
        RightAlt = 346,
        RightMenu = 347,

        Menu = 348,

        NumRow0 = 48,
        NumRow1 = 49,
        NumRow2 = 50,
        NumRow3 = 51,
        NumRow4 = 52,
        NumRow5 = 53,
        NumRow6 = 54,
        NumRow7 = 55,
        NumRow8 = 56,
        NumRow9 = 57,

        Numpad0 = 320,
        Numpad1 = 321,
        Numpad2 = 322,
        Numpad3 = 323,
        Numpad4 = 324,
        Numpad5 = 325,
        Numpad6 = 326,
        Numpad7 = 327,
        Numpad8 = 328,
        Numpad9 = 329,

        Decimal = 330,
        Divide = 331,
        Multiply = 332,
        Subtract = 333,
        Add = 334,
        NumpadEnter = 335,
        NumpadEqual = 336,

        F1 = 290,
        F2 = 291,
        F3 = 292,
        F4 = 293,
        F5 = 294,
        F6 = 295,
        F7 = 296,
        F8 = 297,
        F9 = 298,
        F10 = 299,
        F11 = 300,
        F12 = 301,
        F13 = 302,
        F14 = 303,
        F15 = 304,
        F16 = 305,
        F17 = 306,
        F18 = 307,
        F19 = 308,
        F20 = 309,
        F21 = 310,
        F22 = 311,
        F23 = 312,
        F24 = 313,
        F25 = 314,

        A = 65,
        B = 66,
        C = 67,
        D = 68,
        E = 69,
        F = 70,
        G = 71,
        H = 72,
        I = 73,
        J = 74,
        K = 75,
        L = 76,
        M = 77,
        N = 78,
        O = 79,
        P = 80,
        Q = 81,
        R = 82,
        S = 83,
        T = 84,
        U = 85,
        V = 86,
        W = 87,
        X = 88,
        Y = 89,
        Z = 90
    };
    enum class KeyMods : const unsigned short { Shift = 1, Control = 2, Alt = 4, Windows = 8, CapsLock = 16, NumLock = 32 };
    enum class MouseButton : const unsigned short {
        Button1 = 0,
        Button2 = 1,
        Button3 = 2,
        Button4 = 3,
        Button5 = 4,
        Button6 = 5,
        Button7 = 6,
        Button8 = 7,
        Left = Button1,
        Right = Button2,
        Middle = Button3
    };
} // namespace coel

namespace coel {
    enum class LayoutType : const unsigned char { Float, Int, UInt, Short, UShort, Byte, UByte };
    enum class ColorSpace : const unsigned char { RGB, RGBA };
} // namespace coel

namespace coel {
    struct Window {
        unsigned int width, height;
        const char *title;
        void *window_handle;
        Window() {}
        Window(const unsigned int width, const unsigned int height, const char *const title);
        void init(const unsigned int width, const unsigned int height, const char *const title);
        void update();
        void make_current();
        bool should_close();
        float get_time();
        virtual void key_press(const KeyPress &e) {}
        virtual void key_repeat(const KeyRepeat &e) {}
        virtual void key_release(const KeyRelease &e) {}
        virtual void mouse_press(const MousePress &e) {}
        virtual void mouse_release(const MouseRelease &e) {}
        virtual void mouse_scroll(const MouseScroll &e) {}
        virtual void mouse_move(const MouseMove &e) {}
        virtual void window_move(const WindowMove &e) {}
        virtual void window_resize(const WindowResize &e) {}
        virtual void window_close(const WindowClose &e) {}
        virtual void window_focus(const WindowFocus &e) {}
        virtual void window_defocus(const WindowDefocus &e) {}
        virtual Window operator=(const Window &w) {
            width = w.width, height = w.height, title = w.title, window_handle = w.window_handle;
            return *this;
        }
    };
    struct Shader {
        unsigned int id;
        const char *const vert_src, *const frag_src;
        Shader(const char *const vert_src, const char *const frag_src);
        void send_int(const char *const name, const int value) const;
        void send_float(const char *const name, const float value) const;
        void send_float2(const char *const name, const void *const data) const;
        void send_float3(const char *const name, const void *const data) const;
        void send_float4(const char *const name, const void *const data) const;
    };
    struct Texture {
        unsigned int id;
        int width, height;
        ColorSpace color_space;
        const char *filepath;
        Texture() {}
        Texture(const char *const filepath);
        Texture(const int width, const int height, ColorSpace space);
        void init(const int width, const int height, ColorSpace space);
        void update(const void *const data);
        Texture operator=(const Texture &t) {
            id = t.id, width = t.width, height = t.height, color_space = t.color_space, filepath = t.filepath;
        }
    };
    struct Model {
        const void *vdata;
        const unsigned short *idata;
        const unsigned int vsize, isize;
        Model(const char *const filepath);
        Model(const void *vdata, const unsigned int vsize, const unsigned short *idata, const unsigned int isize);
    };
    struct Material {
        const Shader *const shader;
        Material() : shader(nullptr){};
        template <typename... T> Material(const Shader *const shader, T... texture_shader_data) : shader(shader) {
            init_tex_mat(shader, 0, texture_shader_data...);
        }

      private:
        static void init_tex_mat(const Shader *const shader, const unsigned int slot, const Texture *texture,
                                 const char *const name);
        template <typename... T>
        inline static void init_tex_mat(const Shader *const shader, const unsigned int slot, const Texture *texture,
                                        const char *const name, T... texture_shader_data) {
            init_tex_mat(shader, slot, texture, name);
            init_tex_mat(shader, slot + 1, texture_shader_data...);
        }
    };
    namespace renderer {
        void clear(const unsigned int color);
        void clear(const float r, const float g, const float b, const float a = 1.f);
        static inline void clear(const float val = 0.25) { clear(val, val, val, 1.f); }
        void viewport(const float width, const float height);
        namespace batch2d {
            struct Vertex {
                float pos_x, pos_y, tex_u, tex_v;
                unsigned char col_r, col_g, col_b, col_a;
                float tid;
            };
            void init();
            void submit_rect(const float pos_x, const float pos_y, const float size_x, const float size_y,
                             const float tid = -1.f);
            void submit_rect(const float pos_x, const float pos_y, const float size_x, const float size_y,
                             const void *const col);
            void flush();
        } // namespace batch2d
        namespace batch3d {
            void init();
            void submit(const Model *const model);
            void flush();
        } // namespace batch3d
        namespace custom {
            void init();
            void submit(const Model *const model);
            void flush();
            void setup_layout(const LayoutType type, const unsigned int count);
            template <typename... P>
            static inline void setup_layout(const LayoutType type, const unsigned int count, P... param) {
                setup_layout(type, count);
                setup_layout(param...);
            }
            void set_layout(const unsigned int i, const LayoutType type, const unsigned int count);
            template <typename... P>
            static inline void set_layout(const unsigned int i, const LayoutType type, const unsigned int count, P... param) {
                set_layout(i, type, count);
                set_layout(i + 1, param...);
            }
            template <typename... P> static inline void layout(const LayoutType type, const unsigned int count, P... param) {
                renderer::custom::setup_layout(type, count, param...);
                renderer::custom::set_layout(0, type, count, param...);
            }
        } // namespace custom
    }     // namespace renderer
} // namespace coel
