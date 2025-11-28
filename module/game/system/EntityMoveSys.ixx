module;
#include "entt/entity/registry.hpp"
export module game.system;


export namespace mc::EntityMoveSys
{
void update(entt::registry& reg, float dt);
}