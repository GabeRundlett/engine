#pragma once

#include <Coel/Renderer/Batch.hpp>

namespace Coel { namespace Renderer {
    struct Sprite final {
      public:
        struct Vertex {
            float x, y;
        };
        void deinit();
        void begin();
        void submit(float x, float y, float w, float h);
        void flush();

        Sprite();

      private:
        Batch batch;
        Shader shader;
        Vertex *vertexHandle{};
        unsigned int *indexHandle{};
        unsigned int vertexCount{}, indexCount{};
    };
}} // namespace Coel::Renderer
