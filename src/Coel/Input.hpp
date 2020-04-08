#pragma once

#include <glm/glm.hpp>

namespace Coel {
    namespace Key {
        enum KeyboardKeyID : const unsigned short {
            Space = ' ',
            Apostrophe = '\'',
            Comma = ',',
            Minus = '-',
            Period = '.',
            Slash = '/',

            SemiColon = ';',
            Equal = '=',

            LeftBracket = '[',
            RightBracket = ']',
            Backslash = '\\',
            GraveAccent = '`',

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

            NumRow0 = '0',
            NumRow1,
            NumRow2,
            NumRow3,
            NumRow4,
            NumRow5,
            NumRow6,
            NumRow7,
            NumRow8,
            NumRow9,

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

            A = 'A',
            B,
            C,
            D,
            E,
            F,
            G,
            H,
            I,
            J,
            K,
            L,
            M,
            N,
            O,
            P,
            Q,
            R,
            S,
            T,
            U,
            V,
            W,
            X,
            Y,
            Z,
        };
    }
    namespace Button {
        enum MouseButtonID {
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
            Middle = Button3,
        };
    }
    namespace Mod {
        enum ModID {
            Shift = 1,
            Control = 2,
            Alt = 4,
            Windows = 8,
            CapsLock = 16,
            NumLock = 32,
        };
    }
    namespace Action {
        enum ActionID {
            Release,
            Press,
            Repeat,
        };
    }
    struct KeyInfo {
        int code, scancode, action, mods;
        unsigned int character;
    };
    struct MouseInfo {
        glm::dvec2 pos, scrollOffset;
        int button, action, mods;
    };
} // namespace Coel
