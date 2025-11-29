module;
#include <expected>
#include <glm/vec3.hpp>
#include <string>

#include "entt/entity/registry.hpp"
module game.World;
import Config;
import game.comp;
import spdlog;

namespace mc
{
World::World()
{
    m_blockMap.reserve(block_count);
    m_blockTextures.reserve(block_count);
}
World::~World()
{
    m_blockTextures.clear();
    m_blockMap.clear();
}

std::expected<entt::entity, BlockError> World::createBlock(entt::registry& reg, const glm::ivec3& pos, const BlockType type)
{
    if (m_blockMap.contains(pos))
    {
        return std::unexpected(BlockError::already_exists);
    }

    const auto block = reg.create();
    auto& tf = reg.emplace<TransformComp>(block);
    auto& bc = reg.emplace<BlockComp>(block);
    reg.emplace<BlockTag>(block);
    auto& rc = reg.emplace<RenderComp>(block);

    tf.position = pos;
    bc.blockType = type;
    bc.pos = pos;
    rc.textureName = m_blockTextures[type];
    m_blockMap.emplace(pos, block);
    return block;
}

void World::destroyBlock(entt::registry& reg, const glm::ivec3& pos)
{
    if (!m_blockMap.contains(pos))
    {
        return;
    }

    reg.destroy(m_blockMap[pos]);
    m_blockMap.erase(pos);
}

void World::registerBlockTex(BlockType type, const std::string& texName)
{
    if (m_blockTextures.contains(type))
    {
        spdlog::warn("{}方块已经注册", texName);
    }
    m_blockTextures.emplace(type, texName);
}

bool World::isExistBlock(const glm::ivec3& pos) const
{
    return m_blockMap.contains(pos);
}
} // namespace mc
