#pragma once

#include <Coel/Input.hpp>

namespace Coel {
    class Camera3D {
      public:
        glm::mat4 projMat{1}, tranMat{1}, rotMat{1}, viewMat{1};
        glm::vec3 pos{}, rot{};
        float fov{glm::radians(90.f)}, aspect{1.f};

        void updateAspect(const glm::ivec2 &size);
        void updateFov(const float radians);
        void updatePosition(const glm::vec3 &p);
        void updateRotation(const glm::vec3 &r);
    };
} // namespace Coel
