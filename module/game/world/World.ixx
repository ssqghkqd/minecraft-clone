module;
#include <expected>
#include <glm/vec3.hpp>
#include <string>
#include <unordered_map>

#include "entt/entity/entity.hpp"
export module game.World;
import game.comp;
import utils.glm_hash;

export namespace mc
{
class World
{
  public:
    World();
    ~World();
    std::expected<entt::entity, BlockError> createBlock(entt::registry& reg, const glm::ivec3& pos, BlockType type);
    void destroyBlock(entt::registry& reg, const glm::ivec3& pos);
    void registerBlockTex(BlockType type, const std::string& texName);
    bool isExistBlock(const glm::ivec3& pos) const;

  private:
    std::unordered_map<glm::ivec3, entt::entity> m_blockMap{};
    std::unordered_map<BlockType, std::string> m_blockTextures{};
};
} // namespace mc
