#pragma once

namespace coel {
    enum class ShaderType : const unsigned char { Vertex, Fragment, Geometry, Tesselation, Compute };
    struct Shader {
        unsigned int id;
    };

    namespace shader {
        namespace _internal {
            Shader create_program();
            void link_program(const Shader &s);
            void compile_sources(const Shader &s, const ShaderType type, const char *const src);
            template <typename... T>
            inline void compile_sources(const Shader &s, const ShaderType type, const char *const src, T... param) {
                compile_sources(s, type, src);
                compile_sources(s, param...);
            }
        } // namespace _internal
        template <typename... T> Shader create(const ShaderType type, const char *const src, T... param) {
            const Shader shader = _internal::create_program();
            _internal::compile_sources(shader, type, src, param...);
            _internal::link_program(shader);
            return shader;
        }
        void send_int(const Shader &s, const char *const name, const int value);
        void send_float(const Shader &s, const char *const name, const float value);
        void send_float2(const Shader &s, const char *const name, const void *const data);
        void send_float3(const Shader &s, const char *const name, const void *const data);
        void send_float4(const Shader &s, const char *const name, const void *const data);
    } // namespace shader
} // namespace coel
