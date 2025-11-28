module;
#include <entt/entt.hpp>

#include "glm/vec3.hpp"
export module game.system.BlockSys;
import game.comp;

export namespace mc::BlockSys
{
entt::entity createBlock(entt::registry& reg, const glm::vec3& pos, BlockType type);
void registerBlockTex(const std::string& texName, BlockType type);
}