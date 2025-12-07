// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2025 ss
//
module;
#include <memory>
#include <unordered_map>
export module game:World;
import :Chunk;
import glm;
import impl;

namespace mc
{
export class World
{
  private:
    std::vector<std::unique_ptr<Chunk>> chunks{};
    std::unordered_map<impl::BlockType, uint32_t> blockTextures_{};
    std::unordered_map<uint32_t, std::vector<impl::graphics::Vertex>> blockVertices_{};
    bool dirty_{true};

  public:
    World() = default;
    ~World() = default;

    void init()
    {
        chunks.reserve(256);
        for (int x = -8; x < 8; x++)
        {
            for (int y = -8; y < 8; y++)
            {
                chunks.push_back(std::make_unique<Chunk>(glm::ivec2(x, y)));
            }
        }

        for (int i = 0; i < 256; i++)
        {
            for (int x = 0; x < 16; x++)
            {
                for (int y = 0; y < 16; y++)
                {
                    chunks[i]->setBlock({x, 0, y}, impl::BlockType::grass_block);
                }
            }
        }
    }

    [[nodiscard]] const std::unordered_map<uint32_t, std::vector<impl::graphics::Vertex>>&
    getRenderInfor()
    {
        if (!dirty_)
        {
            return blockVertices_;
        }

        // 清空上一帧数据
        for (auto& [textureID, vertices] : blockVertices_)
        {
            vertices.clear();
        }

        // 遍历所有chunks
        for (const auto& chunk : chunks)
        {
            auto& chunkVertices = chunk->getVertexDict();

            for (auto& [textureID, vertices] : chunkVertices)
            {
                // 获取最终纹理ID
                uint32_t finalTextureID = blockTextures_[textureID];

                // 追加顶点
                auto& targetVector = blockVertices_[finalTextureID];
                targetVector.insert(targetVector.end(),
                                    vertices.begin(),
                                    vertices.end());
            }
        }
        dirty_ = false;
        return blockVertices_;
    }

    void registerBlockTexture(impl::BlockType blockType, uint32_t texture)
    {
        if (blockTextures_.contains(blockType))
        {
            return;
        }
        blockTextures_[blockType] = texture;
    }

    World(const World&) = delete;
    World(const World&&) = delete;
    World& operator=(const World&) = delete;
    World& operator=(World&&) = delete;
};
} // namespace mc