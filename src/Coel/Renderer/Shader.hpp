#pragma once

namespace Coel {
    class Shader final {
        unsigned int m_id;

      public:
        Shader(const char *const vertSrc, const char *const fragSrc);
        void bind() const;
        void sendInt(const char *const location, const int value) const;
        void sendInt2(const char *const location, void *data) const;
        void sendInt3(const char *const location, void *data) const;
        void sendInt4(const char *const location, void *data) const;
        void sendFloat(const char *const location, const float value) const;
        void sendFloat2(const char *const location, void *data) const;
        void sendFloat3(const char *const location, void *data) const;
        void sendFloat4(const char *const location, void *data) const;
        void sendMat4(const char *const location, void *data) const;
    };
}

