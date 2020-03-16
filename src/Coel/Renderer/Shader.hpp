#pragma once

#include <glm/glm.hpp>

namespace Coel {
    class Shader final {
        unsigned int m_id;

      public:
        template <typename T> struct Uniform final { int location{}; };

        Shader(const char *const vertSrc, const char *const fragSrc);
        Shader(const char *const vertSrc, const char *const geomSrc, const char *const fragSrc);

        void bind() const;

        Uniform<int> findInt(const char *const name) const;
        Uniform<glm::ivec2> findInt2(const char *const name) const;
        Uniform<glm::ivec3> findInt3(const char *const name) const;
        Uniform<glm::ivec4> findInt4(const char *const name) const;
        Uniform<float> findFloat(const char *const name) const;
        Uniform<glm::vec2> findFloat2(const char *const name) const;
        Uniform<glm::vec3> findFloat3(const char *const name) const;
        Uniform<glm::vec4> findFloat4(const char *const name) const;
        Uniform<glm::mat3> findMat3(const char *const name) const;
        Uniform<glm::mat4> findMat4(const char *const name) const;
        void send(const Uniform<int> uniform, const int value) const;
        void send(const Uniform<glm::ivec2> uniform, const void *const data) const;
        void send(const Uniform<glm::ivec3> uniform, const void *const data) const;
        void send(const Uniform<glm::ivec4> uniform, const void *const data) const;
        void send(const Uniform<float> uniform, const float value) const;
        void send(const Uniform<glm::vec2> uniform, const void *const data) const;
        void send(const Uniform<glm::vec3> uniform, const void *const data) const;
        void send(const Uniform<glm::vec4> uniform, const void *const data) const;
        void send(const Uniform<glm::mat3> uniform, const void *const data) const;
        void send(const Uniform<glm::mat4> uniform, const void *const data) const;
    };

} // namespace Coel
