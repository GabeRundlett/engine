#include "Camera.hpp"

namespace Coel {
    void Camera3D::updateAspect(const Math::Vec2i &size) {
        aspect = float(size.x) / size.y;
        projMat = Math::Mat4::perspective(fov, aspect, 0.01f, 200.f);
    }
    void Camera3D::updateFov(const float radians) {
        fov = radians;
        projMat = Math::Mat4::perspective(fov, aspect, 0.01f, 200.f);
    }
    void Camera3D::updatePosition(const Math::Vec3 &p) {
        tranMat = Math::Mat4::translation(p);
        pos = p;
    }
    void Camera3D::updateRotation(const Math::Vec3 &r) {
        rotMat = Math::Mat4::identity();
        rotMat *= Math::Mat4::rotation(r.x, {1, 0, 0});
        rotMat *= Math::Mat4::rotation(r.y, {0, 1, 0});
        rot = r;
    }
} // namespace Coel
