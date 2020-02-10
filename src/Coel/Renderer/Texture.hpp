#pragma once

namespace Coel {
    class Texture final {
        unsigned int m_id, m_format;
        int m_width, m_height;

      public:
        Texture(const char *const filepath);
        Texture(const int width, const int height, const unsigned char *const data);

        void bind(const int slot) const;
        void setData(const unsigned char *const data) const;
    };
} // namespace Coel
