#pragma once

namespace Coel {
    namespace Format {
        enum ID {
            RGB8,
            RGBA8,
            RGB32F,
            Depth,
        };
    }

    namespace Filter {
        enum Mode {
            Nearest,
            Linear,
        };
    }

    namespace Wrap {
        enum Mode {
            Repeat,
            ClampToEdge,
            ClampToBorder,
        };
    }

    class Texture final {
        unsigned int m_id, m_formatData[3];
        int m_width, m_height;

      public:
        Texture(const char *const filepath);
        Texture(const int width, const int height, unsigned char format = Format::RGB32F,
                const unsigned char *const data = nullptr);

        void bind(const int slot) const;
        void setData(const unsigned char *const data) const;

        void setMinFilter(const unsigned char mode);
        void setMagFilter(const unsigned char mode);
        void setWrap(const unsigned char mode);
    };
} // namespace Coel
