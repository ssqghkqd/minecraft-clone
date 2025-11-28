module;
#include "glm/vec3.hpp"
export module game.comp:entity;


export namespace mc
{
struct EntityComp // 这里的实体是mc中的实体
{
    glm::vec3 vel = {0.0f, 0.0f, 0.0f};
};
}
