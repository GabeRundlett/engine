#include "Camera.hpp"
#include <glm/ext.hpp>

namespace Coel {
    void Camera3D::updateAspect(const glm::ivec2 &size) {
        aspect = float(size.x) / size.y;
        projMat = glm::perspective(fov, aspect, 0.01f, 200.f);
    }
    void Camera3D::updateFov(const float radians) {
        fov = radians;
        projMat = glm::perspective(fov, aspect, 0.01f, 200.f);
    }
    void Camera3D::updatePosition(const glm::vec3 &p) {
        tranMat = glm::translate(glm::mat4{1}, p);
        pos = p;
    }
    void Camera3D::updateRotation(const glm::vec3 &r) {
        rotMat = glm::rotate(glm::mat4{1}, r.x, {1, 0, 0}) * glm::rotate(glm::mat4{1}, r.x, {1, 0, 0});
        rot = r;
    }
} // namespace Coel
