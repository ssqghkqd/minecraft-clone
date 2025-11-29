module;
#include <cmath>

#include "glm/ext/quaternion_geometric.hpp"
#include "glm/vec3.hpp"
module utils.maths;

namespace mc::Maths
{
float normalizeAngle(float angle)
{
    angle = std::fmod(angle, 2 * M_PI);
    if (angle < 0.0f)
    {
        angle += 2 * M_PI;
    }
    return angle;
}

// 此函数返回归一化的前向量
glm::vec3 calculateForward(float pitch, float yaw)
{
    return {
        -std::cos(pitch) * std::sin(yaw),
        std::sin(pitch),
        -std::cos(pitch) * std::cos(yaw)};
}
} // namespace mc::Maths