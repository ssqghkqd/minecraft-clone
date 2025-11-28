module;
#include <glm/vec3.hpp>

#include "entt/entity/registry.hpp"
module game.system;
import game.comp;
import spdlog;

namespace mc::EntityMoveSys
{
void update(entt::registry& reg, float dt)
{
    static const auto view = reg.view<TransformComp, EntityComp>();
    view.each([dt](TransformComp& tf, const EntityComp& ec)
              {
                  tf.position += ec.vel * dt;
              });
}
} // namespace mc::EntityMoveSys