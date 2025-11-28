module;
#include <entt/entt.hpp>
#include <glm/glm.hpp>
#include <string>
#include <unordered_map>

module game.system.BlockSys;
import game.comp;
import spdlog;

namespace mc::BlockSys
{
static std::unordered_map<BlockType, std::string> m_blockTextures;

entt::entity createBlock(entt::registry& reg, const glm::vec3& pos, const BlockType type)
{
    const auto block = reg.create();
    auto& tf = reg.emplace<TransformComp>(block);
    auto& bc = reg.emplace<BlockComp>(block);
    reg.emplace<BlockTag>(block);
    auto& rc = reg.emplace<RenderComp>(block);

    tf.position = pos;
    bc.blockType = type;
    rc.textureName = m_blockTextures[type];
    return block;
}

void registerBlockTex(const std::string& texName, BlockType type)
{
    if (m_blockTextures.contains(type))
    {
        spdlog::warn("block已经被注册");
        return;
    }
    m_blockTextures[type] = texName;
}
}