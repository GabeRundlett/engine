#pragma once

#include <glm/glm.hpp>

namespace Coel {
    template <typename T> struct Uniform final { int location{}, count{1}; };
    struct Shader {
        unsigned int id{};
    };

    void create(Shader &shader, const char *const vertSrc, const char *const fragSrc);
    void create(Shader &shader, const char *const vertSrc, const char *const geomSrc, const char *const fragSrc);
    void bind(const Shader &shader);
    void destroy(Shader &shader);

    Uniform<int> findInt(const Shader &shader, const char *const name);
    Uniform<glm::ivec2> findInt2(const Shader &shader, const char *const name);
    Uniform<glm::ivec3> findInt3(const Shader &shader, const char *const name);
    Uniform<glm::ivec4> findInt4(const Shader &shader, const char *const name);
    Uniform<float> findFloat(const Shader &shader, const char *const name);
    Uniform<glm::vec2> findFloat2(const Shader &shader, const char *const name);
    Uniform<glm::vec3> findFloat3(const Shader &shader, const char *const name);
    Uniform<glm::vec4> findFloat4(const Shader &shader, const char *const name);
    Uniform<glm::mat3> findMat3(const Shader &shader, const char *const name);
    Uniform<glm::mat4> findMat4(const Shader &shader, const char *const name);
    void send(const Uniform<int> uniform, const int32_t value);
    void send(const Uniform<int> uniform, const int32_t *const data);
    void send(const Uniform<glm::ivec2> uniform, const void *const data);
    void send(const Uniform<glm::ivec3> uniform, const void *const data);
    void send(const Uniform<glm::ivec4> uniform, const void *const data);
    void send(const Uniform<float> uniform, const float value);
    void send(const Uniform<float> uniform, const float *const data);
    void send(const Uniform<glm::vec2> uniform, const void *const data);
    void send(const Uniform<glm::vec3> uniform, const void *const data);
    void send(const Uniform<glm::vec4> uniform, const void *const data);
    void send(const Uniform<glm::mat3> uniform, const void *const data);
    void send(const Uniform<glm::mat4> uniform, const void *const data);
} // namespace Coel
