#include "Camera.hpp"

namespace Coel {
    void Camera3D::resizeProjection(const Math::Vec2i &size) {
        projMat = Math::Mat4::perspective(70.f * Math::PI / 180, (float)size.x / size.y, 0.01f, 200.f);
    }
    void Camera3D::updateRotation(const Math::Vec3 &r) {
        rotMat = Math::Mat4::identity();
        rotMat *= Math::Mat4::rotation(r.x, {1, 0, 0});
        rotMat *= Math::Mat4::rotation(r.y, {0, 1, 0});
    }
    void Camera3D::updatePosition(const Math::Vec3 &p) { tranMat = Math::Mat4::translation(p); }
} // namespace Coel
