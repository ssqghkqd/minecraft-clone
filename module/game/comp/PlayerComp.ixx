module;
#include <glm/vec3.hpp>
export module game.comp:player;

export namespace mc
{
struct PlayerComp
{
    // 并不一定为单位向量
    glm::vec3 forward = glm::vec3(0.0f);

};
}
