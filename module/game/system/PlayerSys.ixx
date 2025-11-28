module;
#include <entt/entt.hpp>
#include <glm/glm.hpp>
export module game.system.PlayerSys;
import core.Window;

export namespace mc::PlayerSys
{
void createPlayer(entt::registry& reg);
void updateMovement(entt::registry& reg, const Window& window);
glm::mat4 getPlayerView(entt::registry& reg);
void update(entt::registry& reg);
}
