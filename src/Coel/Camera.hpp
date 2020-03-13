#pragma once

#include "Input.hpp"

namespace Coel {
    class Camera3D {
      public:
        Math::Mat4 projMat{0}, tranMat{0}, rotMat{0};
        Math::Vec3 pos{}, rot{};
        float fov{90.f * (float)Math::PI / 180}, aspect{1.f};

        void updateAspect(const Math::Vec2i &size);
        void updateFov(const float radians);
        void updatePosition(const Math::Vec3 &p);
        void updateRotation(const Math::Vec3 &r);
    };
} // namespace Coel
