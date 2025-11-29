module;
#include <optional>

#include "glm/vec3.hpp"
export module game.RaySys;
import game.World;

export namespace mc::RaySys
{
struct Ray
{
    glm::vec3 start; // 起始位置
    // 单位向量
    glm::vec3 direction = glm::vec3(0.0f);
};

struct RayHitResult
{
    glm::ivec3 hitPos; // 被击中方块
    glm::ivec3 normal; // 被击中面的法向量
};

std::optional<RayHitResult> checkRayHit(const Ray& ray, const World& world);
glm::ivec3 calculateNormal(const glm::ivec3& prev, const glm::ivec3& current);

}
