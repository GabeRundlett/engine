#pragma once

#include "Input.hpp"

namespace Coel {
    class Camera3D {
      public:
        Math::Mat4 projMat{0}, tranMat{0}, rotMat{0};

        void resizeProjection(const Math::Vec2i &size);
        void updatePosition(const Math::Vec3 &p);
        void updateRotation(const Math::Vec3 &r);
    };
} // namespace Coel
