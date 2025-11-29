module;
#include <glm/vec3.hpp>
export module game.comp:player;

export namespace mc
{
struct PlayerComp
{
    // 单位向量
    glm::vec3 forward = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 dir = glm::vec3(0.0f); // 移动的单位向量

};
}
