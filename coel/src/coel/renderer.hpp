#pragma once

// Add new Renderer APIs
#define COEL_SET_DEFAULT_RENDERER_API_OPENGL

#ifdef COEL_SET_DEFAULT_RENDERER_API_OPENGL
#define _COEL_DEFAULT_RENDERER_API OpenGL
#endif
#ifdef COEL_SET_DEFAULT_RENDERER_API_VULKAN
#define _COEL_DEFAULT_RENDERER_API Vulkan
#endif
#ifdef COEL_SET_DEFAULT_RENDERER_API_DIRECT3D
#define _COEL_DEFAULT_RENDERER_API Direct3D
#endif
#ifdef COEL_SET_DEFAULT_RENDERER_API_AGNOSTIC
#define _COEL_DEFAULT_RENDERER_API Agnostic
#endif
#ifndef _COEL_DEFAULT_RENDERER_API
#ifdef _CONFIG_PLATFORM_WINDOWS
#define _COEL_DEFAULT_RENDERER_API Direct3D
#else
#ifdef _CONFIG_PLATFORM_LINUX
#define _COEL_DEFAULT_RENDERER_API OpenGL
#else
#define _COEL_DEFAULT_RENDERER_API Agnostic
#endif
#endif
#endif

namespace coel {
enum class RendererAPI { None, Agnostic, Vulkan, Direct3D, OpenGL };
struct VBO {
    unsigned int id, size, dim;
};
struct IBO {
    unsigned int id, count;
};
struct Shader {
    unsigned int id;
};
struct Texture {
    unsigned int id;
    int width, height, channels;
};
} // namespace coel

namespace coel { namespace renderer { namespace _internal {

    //
    //
    //
    //
    //

    namespace agnostic {
        namespace vbo {
            VBO create(const float *data, const unsigned int vertex_size, const unsigned short count);
        } // namespace vbo
        namespace ibo {
            IBO create(const unsigned short *data, const unsigned short count);
        } // namespace ibo
        namespace shader {
            Shader create(const char *vert_src, const char *frag_src);
            void bind(const Shader *shader);
            void send_int(const Shader *shader, const char *uniform_name, const int data);
            void send_float(const Shader *shader, const char *uniform_name, const float data);
            void send_vec2(const Shader *shader, const char *uniform_name, const float *data);
            void send_vec3(const Shader *shader, const char *uniform_name, const float *data);
            void send_vec4(const Shader *shader, const char *uniform_name, const float *data);
            void send_mat3(const Shader *shader, const char *uniform_name, const float *data);
            void send_mat4(const Shader *shader, const char *uniform_name, const float *data);
        } // namespace shader
        namespace texture {
            Texture create(const char *file_path);
        }
        namespace batch {
            void init();
            void begin(Shader *const shader);
            void submit(const float pos[2], const float size[2]);
            void submit(const float x, const float y, const float w, const float h, const Texture *const texture);
            void end();
        } // namespace batch
        void clear(const unsigned int value);
        void clear(const float r, const float g, const float b, const float a);
        void resize_viewport(const unsigned int width, const unsigned int height);
        void draw_buffers(const IBO *ibo);
    } // namespace agnostic

    //
    //
    //
    //
    //

    namespace vulkan {
        namespace vbo {
            VBO create(const float *data, const unsigned int vertex_size, const unsigned short count);
        } // namespace vbo
        namespace ibo {
            IBO create(const unsigned short *data, const unsigned short count);
        } // namespace ibo
        namespace shader {
            Shader create(const char *vert_src, const char *frag_src);
            void bind(const Shader *shader);
            void send_int(const Shader *shader, const char *uniform_name, const int data);
            void send_float(const Shader *shader, const char *uniform_name, const float data);
            void send_vec2(const Shader *shader, const char *uniform_name, const float *data);
            void send_vec3(const Shader *shader, const char *uniform_name, const float *data);
            void send_vec4(const Shader *shader, const char *uniform_name, const float *data);
            void send_mat3(const Shader *shader, const char *uniform_name, const float *data);
            void send_mat4(const Shader *shader, const char *uniform_name, const float *data);
        } // namespace shader
        namespace texture {
            Texture create(const char *file_path);
        }
        namespace batch {
            void init();
            void begin(Shader *const shader);
            void submit(const float pos[2], const float size[2]);
            void submit(const float x, const float y, const float w, const float h, const Texture *const texture);
            void end();
        } // namespace batch
        void clear(const unsigned int value);
        void clear(const float r, const float g, const float b, const float a);
        void resize_viewport(const unsigned int width, const unsigned int height);
        void draw_buffers(const IBO *ibo);
    } // namespace vulkan

    //
    //
    //
    //
    //

    namespace direct3d {
        namespace vbo {
            VBO create(const float *data, const unsigned int vertex_size, const unsigned short count);
        } // namespace vbo
        namespace ibo {
            IBO create(const unsigned short *data, const unsigned short count);
        } // namespace ibo
        namespace shader {
            Shader create(const char *vert_src, const char *frag_src);
            void bind(const Shader *shader);
            void send_int(const Shader *shader, const char *uniform_name, const int data);
            void send_float(const Shader *shader, const char *uniform_name, const float data);
            void send_vec2(const Shader *shader, const char *uniform_name, const float *data);
            void send_vec3(const Shader *shader, const char *uniform_name, const float *data);
            void send_vec4(const Shader *shader, const char *uniform_name, const float *data);
            void send_mat3(const Shader *shader, const char *uniform_name, const float *data);
            void send_mat4(const Shader *shader, const char *uniform_name, const float *data);
        } // namespace shader
        namespace texture {
            Texture create(const char *file_path);
        }
        namespace batch {
            void init();
            void begin(Shader *const shader);
            void submit(const float pos[2], const float size[2]);
            void submit(const float x, const float y, const float w, const float h, const Texture *const texture);
            void end();
        } // namespace batch
        void clear(const unsigned int value);
        void clear(const float r, const float g, const float b, const float a);
        void resize_viewport(const unsigned int width, const unsigned int height);
        void draw_buffers(const IBO *ibo);
    } // namespace direct3d

    //
    //
    //
    //
    //

    namespace opengl {
        namespace vbo {
            VBO create(const float *data, const unsigned int vertex_size, const unsigned short count);
        } // namespace vbo
        namespace ibo {
            IBO create(const unsigned short *data, const unsigned short count);
        } // namespace ibo
        namespace shader {
            Shader create(const char *vert_src, const char *frag_src);
            void bind(const Shader *shader);
            void send_int(const Shader *shader, const char *uniform_name, const int data);
            void send_float(const Shader *shader, const char *uniform_name, const float data);
            void send_vec2(const Shader *shader, const char *uniform_name, const float *data);
            void send_vec3(const Shader *shader, const char *uniform_name, const float *data);
            void send_vec4(const Shader *shader, const char *uniform_name, const float *data);
            void send_mat3(const Shader *shader, const char *uniform_name, const float *data);
            void send_mat4(const Shader *shader, const char *uniform_name, const float *data);
        } // namespace shader
        namespace texture {
            Texture create(const char *file_path);
        }
        namespace batch {
            void init();
            void begin(Shader *const shader);
            void submit(const float pos[2], const float size[2]);
            void submit(const float x, const float y, const float w, const float h, const Texture *const texture);
            void end();
        } // namespace batch
        void clear(const unsigned int value);
        void clear(const float r, const float g, const float b, const float a);
        void resize_viewport(const unsigned int width, const unsigned int height);
        void draw_buffers(const IBO *ibo);
    } // namespace opengl
}}}   // namespace coel::renderer::_internal
//
//
//
//
//

//
//
//
//
//
namespace coel { namespace renderer {
    namespace vbo {
        template <RendererAPI R = RendererAPI::_COEL_DEFAULT_RENDERER_API>
        VBO create(const float *data, const unsigned int vertex_size, const unsigned short count) {
            switch (R) {
            case RendererAPI::Agnostic: return _internal::agnostic::vbo::create(data, vertex_size, count);
            case RendererAPI::Vulkan: return _internal::vulkan::vbo::create(data, vertex_size, count);
            case RendererAPI::Direct3D: return _internal::direct3d::vbo::create(data, vertex_size, count);
            case RendererAPI::OpenGL: return _internal::opengl::vbo::create(data, vertex_size, count);
            default: return {0, 0, 0};
            }
        }
    } // namespace vbo

    //
    //
    //
    //
    //

    namespace ibo {
        template <RendererAPI R = RendererAPI::_COEL_DEFAULT_RENDERER_API>
        IBO create(const unsigned short *data, const unsigned short count) {
            switch (R) {
            case RendererAPI::Agnostic: return _internal::agnostic::ibo::create(data, count);
            case RendererAPI::Vulkan: return _internal::vulkan::ibo::create(data, count);
            case RendererAPI::Direct3D: return _internal::direct3d::ibo::create(data, count);
            case RendererAPI::OpenGL: return _internal::opengl::ibo::create(data, count);
            default: return {0, 0};
            }
        }
    } // namespace ibo

    namespace renderable {
    }

    //
    //
    //
    //
    //

    namespace shader {
        template <RendererAPI R = RendererAPI::_COEL_DEFAULT_RENDERER_API>
        Shader create(const char *vert_src, const char *frag_src) {
            switch (R) {
            case RendererAPI::Agnostic: return _internal::agnostic::shader::create(vert_src, frag_src);
            case RendererAPI::Vulkan: return _internal::vulkan::shader::create(vert_src, frag_src);
            case RendererAPI::Direct3D: return _internal::direct3d::shader::create(vert_src, frag_src);
            case RendererAPI::OpenGL: return _internal::opengl::shader::create(vert_src, frag_src);
            default: return {0};
            }
        }
        template <RendererAPI R = RendererAPI::_COEL_DEFAULT_RENDERER_API> void bind(const Shader *shader) {
            switch (R) {
            case RendererAPI::Agnostic: _internal::agnostic::shader::bind(shader); return;
            case RendererAPI::Vulkan: _internal::vulkan::shader::bind(shader); return;
            case RendererAPI::Direct3D: _internal::direct3d::shader::bind(shader); return;
            case RendererAPI::OpenGL: _internal::opengl::shader::bind(shader); return;
            default: return;
            }
        }
        template <RendererAPI R = RendererAPI::_COEL_DEFAULT_RENDERER_API>
        void send_int(const Shader *shader, const char *uniform_name, const int data) {
            switch (R) {
            case RendererAPI::Agnostic: _internal::agnostic::shader::send_int(shader, uniform_name, data); return;
            case RendererAPI::Vulkan: _internal::vulkan::shader::send_int(shader, uniform_name, data); return;
            case RendererAPI::Direct3D: _internal::direct3d::shader::send_int(shader, uniform_name, data); return;
            case RendererAPI::OpenGL: _internal::opengl::shader::send_int(shader, uniform_name, data); return;
            default: return;
            }
        }
        template <RendererAPI R = RendererAPI::_COEL_DEFAULT_RENDERER_API>
        void send_float(const Shader *shader, const char *uniform_name, const float data) {
            switch (R) {
            case RendererAPI::Agnostic: _internal::agnostic::shader::send_float(shader, uniform_name, data); return;
            case RendererAPI::Vulkan: _internal::vulkan::shader::send_float(shader, uniform_name, data); return;
            case RendererAPI::Direct3D: _internal::direct3d::shader::send_float(shader, uniform_name, data); return;
            case RendererAPI::OpenGL: _internal::opengl::shader::send_float(shader, uniform_name, data); return;
            default: return;
            }
        }
        template <RendererAPI R = RendererAPI::_COEL_DEFAULT_RENDERER_API>
        void send_vec2(const Shader *shader, const char *uniform_name, const float *data) {
            switch (R) {
            case RendererAPI::Agnostic: _internal::agnostic::shader::send_vec2(shader, uniform_name, data); return;
            case RendererAPI::Vulkan: _internal::vulkan::shader::send_vec2(shader, uniform_name, data); return;
            case RendererAPI::Direct3D: _internal::direct3d::shader::send_vec2(shader, uniform_name, data); return;
            case RendererAPI::OpenGL: _internal::opengl::shader::send_vec2(shader, uniform_name, data); return;
            default: return;
            }
        }
        template <RendererAPI R = RendererAPI::_COEL_DEFAULT_RENDERER_API>
        void send_vec3(const Shader *shader, const char *uniform_name, const float *data) {
            switch (R) {
            case RendererAPI::Agnostic: _internal::agnostic::shader::send_vec3(shader, uniform_name, data); return;
            case RendererAPI::Vulkan: _internal::vulkan::shader::send_vec3(shader, uniform_name, data); return;
            case RendererAPI::Direct3D: _internal::direct3d::shader::send_vec3(shader, uniform_name, data); return;
            case RendererAPI::OpenGL: _internal::opengl::shader::send_vec3(shader, uniform_name, data); return;
            default: return;
            }
        }
        template <RendererAPI R = RendererAPI::_COEL_DEFAULT_RENDERER_API>
        void send_vec4(const Shader *shader, const char *uniform_name, const float *data) {
            switch (R) {
            case RendererAPI::Agnostic: _internal::agnostic::shader::send_vec4(shader, uniform_name, data); return;
            case RendererAPI::Vulkan: _internal::vulkan::shader::send_vec4(shader, uniform_name, data); return;
            case RendererAPI::Direct3D: _internal::direct3d::shader::send_vec4(shader, uniform_name, data); return;
            case RendererAPI::OpenGL: _internal::opengl::shader::send_vec4(shader, uniform_name, data); return;
            default: return;
            }
        }
        template <RendererAPI R = RendererAPI::_COEL_DEFAULT_RENDERER_API>
        void send_mat3(const Shader *shader, const char *uniform_name, const float *data) {
            switch (R) {
            case RendererAPI::Agnostic: _internal::agnostic::shader::send_mat3(shader, uniform_name, data); return;
            case RendererAPI::Vulkan: _internal::vulkan::shader::send_mat3(shader, uniform_name, data); return;
            case RendererAPI::Direct3D: _internal::direct3d::shader::send_mat3(shader, uniform_name, data); return;
            case RendererAPI::OpenGL: _internal::opengl::shader::send_mat3(shader, uniform_name, data); return;
            default: return;
            }
        }
        template <RendererAPI R = RendererAPI::_COEL_DEFAULT_RENDERER_API>
        void send_mat4(const Shader *shader, const char *uniform_name, const float *data) {
            switch (R) {
            case RendererAPI::Agnostic: _internal::agnostic::shader::send_mat4(shader, uniform_name, data); return;
            case RendererAPI::Vulkan: _internal::vulkan::shader::send_mat4(shader, uniform_name, data); return;
            case RendererAPI::Direct3D: _internal::direct3d::shader::send_mat4(shader, uniform_name, data); return;
            case RendererAPI::OpenGL: _internal::opengl::shader::send_mat4(shader, uniform_name, data); return;
            default: return;
            }
        }
    } // namespace shader

    //
    //
    //
    //
    //

    namespace texture {
        template <RendererAPI R = RendererAPI::_COEL_DEFAULT_RENDERER_API> Texture create(const char *file_path) {
            switch (R) {
            case RendererAPI::Agnostic: return _internal::agnostic::texture::create(file_path);
            case RendererAPI::Vulkan: return _internal::vulkan::texture::create(file_path);
            case RendererAPI::Direct3D: return _internal::direct3d::texture::create(file_path);
            case RendererAPI::OpenGL: return _internal::opengl::texture::create(file_path);
            default: return {0, 0, 0};
            }
        }
    } // namespace texture

    //
    //
    //
    //
    //

    namespace batch {
        template <RendererAPI R = RendererAPI::_COEL_DEFAULT_RENDERER_API> void init() {
            switch (R) {
            case RendererAPI::Agnostic: _internal::agnostic::batch::init(); return;
            case RendererAPI::Vulkan: _internal::vulkan::batch::init(); return;
            case RendererAPI::Direct3D: _internal::direct3d::batch::init(); return;
            case RendererAPI::OpenGL: _internal::opengl::batch::init(); return;
            default: return;
            }
        }
        template <RendererAPI R = RendererAPI::_COEL_DEFAULT_RENDERER_API> void begin(Shader *const shader) {
            switch (R) {
            case RendererAPI::Agnostic: _internal::agnostic::batch::begin(shader); return;
            case RendererAPI::Vulkan: _internal::vulkan::batch::begin(shader); return;
            case RendererAPI::Direct3D: _internal::direct3d::batch::begin(shader); return;
            case RendererAPI::OpenGL: _internal::opengl::batch::begin(shader); return;
            default: return;
            }
        }
        template <RendererAPI R = RendererAPI::_COEL_DEFAULT_RENDERER_API>
        void submit(const float pos[2], const float size[2]) {
            switch (R) {
            case RendererAPI::Agnostic: _internal::agnostic::batch::submit(pos, size); return;
            case RendererAPI::Vulkan: _internal::vulkan::batch::submit(pos, size); return;
            case RendererAPI::Direct3D: _internal::direct3d::batch::submit(pos, size); return;
            case RendererAPI::OpenGL: _internal::opengl::batch::submit(pos, size); return;
            default: return;
            }
        }
        template <RendererAPI R = RendererAPI::_COEL_DEFAULT_RENDERER_API>
        void submit(const float x, const float y, const float w, const float h, const Texture *const texture) {
            switch (R) {
            case RendererAPI::Agnostic: _internal::agnostic::batch::submit(x, y, w, h, texture); return;
            case RendererAPI::Vulkan: _internal::vulkan::batch::submit(x, y, w, h, texture); return;
            case RendererAPI::Direct3D: _internal::direct3d::batch::submit(x, y, w, h, texture); return;
            case RendererAPI::OpenGL: _internal::opengl::batch::submit(x, y, w, h, texture); return;
            default: return;
            }
        }
        template <RendererAPI R = RendererAPI::_COEL_DEFAULT_RENDERER_API> void end() {
            switch (R) {
            case RendererAPI::Agnostic: _internal::agnostic::batch::end(); return;
            case RendererAPI::Vulkan: _internal::vulkan::batch::end(); return;
            case RendererAPI::Direct3D: _internal::direct3d::batch::end(); return;
            case RendererAPI::OpenGL: _internal::opengl::batch::end(); return;
            default: return;
            }
        }
    } // namespace batch

    //
    //
    //
    //
    //

    template <RendererAPI R = RendererAPI::_COEL_DEFAULT_RENDERER_API> void clear(const unsigned int value) {
        switch (R) {
        case RendererAPI::Agnostic: _internal::agnostic::clear(value); return;
        case RendererAPI::Vulkan: _internal::vulkan::clear(value); return;
        case RendererAPI::Direct3D: _internal::direct3d::clear(value); return;
        case RendererAPI::OpenGL: _internal::opengl::clear(value); return;
        default: return;
        }
    }

    //
    //
    //
    //
    //

    template <RendererAPI R = RendererAPI::_COEL_DEFAULT_RENDERER_API>
    void clear(const float r, const float g, const float b, const float a) {
        switch (R) {
        case RendererAPI::Agnostic: _internal::agnostic::clear(r, g, b, a); return;
        case RendererAPI::Vulkan: _internal::vulkan::clear(r, g, b, a); return;
        case RendererAPI::Direct3D: _internal::direct3d::clear(r, g, b, a); return;
        case RendererAPI::OpenGL: _internal::opengl::clear(r, g, b, a); return;
        default: return;
        }
    }

    //
    //
    //
    //
    //

    template <RendererAPI R = RendererAPI::_COEL_DEFAULT_RENDERER_API>
    void resize_viewport(const unsigned int width, const unsigned int height) {
        switch (R) {
        case RendererAPI::Agnostic: _internal::agnostic::resize_viewport(width, height); return;
        case RendererAPI::Vulkan: _internal::vulkan::resize_viewport(width, height); return;
        case RendererAPI::Direct3D: _internal::direct3d::resize_viewport(width, height); return;
        case RendererAPI::OpenGL: _internal::opengl::resize_viewport(width, height); return;
        default: return;
        }
    }

    //
    //
    //
    //
    //

    template <RendererAPI R = RendererAPI::_COEL_DEFAULT_RENDERER_API> void draw_buffers(const IBO *ibo) {
        switch (R) {
        case RendererAPI::Agnostic: _internal::agnostic::draw_buffers(ibo); return;
        case RendererAPI::Vulkan: _internal::vulkan::draw_buffers(ibo); return;
        case RendererAPI::Direct3D: _internal::direct3d::draw_buffers(ibo); return;
        case RendererAPI::OpenGL: _internal::opengl::draw_buffers(ibo); return;
        default: return;
        }
    }
}} // namespace coel::renderer
