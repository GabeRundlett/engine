#pragma once

#include "../core.hpp"
#include "../renderer.hpp"

namespace coel {
	class Shader {
	public:
		virtual void bind() const = 0;
		virtual void send_int(const char* const location, const int value) const = 0;
		virtual void send_float(const char* const location, const float value) const = 0;
	};

	namespace opengl {
		class Shader final : public coel::Shader {
			unsigned int m_id;

		public:
			Shader(const char* const vert_src, const char* const frag_src);
			void bind() const override;
			void send_int(const char* const location, const int value) const override;
			void send_float(const char* const location, const float value) const override;
		};
	}

	static inline Ref<Shader> create_shader(const char* const vert_src, const char* const frag_src) {
		switch (Renderer::get_api()) {
		case RendererAPI::OpenGL: return create_ref<opengl::Shader>(vert_src, frag_src);
		case RendererAPI::Vulkan:
		case RendererAPI::Direct3D:
		default: return nullptr;
		}
	}
}
