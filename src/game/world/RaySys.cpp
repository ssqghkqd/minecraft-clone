module;
#include <glm/vec3.hpp>
#include <optional>

#include "glm/common.hpp"
module game.RaySys;
import Config;
import game.World;

namespace mc::RaySys
{
std::optional<RayHitResult> checkRayHit(const Ray& ray, const World& world)
{
    RayHitResult result;
    glm::vec3 currentPos = ray.start;
    glm::vec3 previousPos = currentPos; // 上一步的向量
    const glm::vec3 dir = ray.direction;

    for (int i = 0; i < max_steps; i++)
    {
        const glm::ivec3 currentBlockPos = glm::floor(currentPos);
        if (world.isExistBlock(currentBlockPos))
        {
            result.hitPos = currentBlockPos;
            result.normal = calculateNormal(
                glm::floor(previousPos),
                glm::floor(currentPos));
            return result;
        }
        previousPos = currentPos;
        currentPos += step_distance * dir;
    }
    return std::nullopt;
}

glm::ivec3 calculateNormal(const glm::ivec3& prev, const glm::ivec3& current)
{
    glm::ivec3 result = glm::ivec3(0);
    const glm::ivec3 diff = prev - current;
    if (diff.x != 0)
    {
        result.x = diff.x > 0 ? 1 : -1;
    }
    else if (diff.y != 0)
    {
        result.y = diff.y > 0 ? 1 : -1;
    }
    else if (diff.z != 0)
    {
        result.z = diff.z > 0 ? 1 : -1;
    }
    return result;
}
} // namespace mc::RaySys