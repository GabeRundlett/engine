#pragma once

#include <Coel/Renderer/Batch.hpp>

namespace Coel { namespace Renderer {
    class Batch2d final {
      public:
        struct Vertex {
            float x, y;
        };

        Batch2d();
        ~Batch2d();

        void begin();
        void flush();

        void submitRect(float x, float y, float w, float h);

      private:
        Batch batch;
        Vertex *vertexHandle;
        unsigned int *indexHandle;
        unsigned int vertexCount{}, indexCount{};
    };
}} // namespace Coel::Renderer
