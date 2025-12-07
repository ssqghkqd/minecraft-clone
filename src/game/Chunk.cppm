// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2025 ss
//
module;
#include <cstdint>
#include <unordered_map>
#include <vector>
export module game:Chunk;
import impl;
import glm;

namespace mc
{
constexpr uint8_t chunk_x_size = 16;
constexpr uint8_t chunk_y_size = 128;
constexpr uint8_t chunk_z_size = 16;

export class Chunk
{
  private:
    impl::Block blocks_[chunk_x_size * chunk_y_size * chunk_z_size]{};
    glm::ivec2 chunkPos_ = glm::ivec2(0);
    std::unordered_map<impl::BlockType, std::vector<impl::graphics::Vertex>> blockVertices_{};
    bool dirty = false;

    static uint32_t toIndex(uint8_t x, uint8_t y, uint8_t z)
    {
        return y * (chunk_x_size * chunk_z_size) + z * chunk_x_size + x;
    }

    void rebuildDict()
    {
        dirty = false;
        for (int x = 0; x < chunk_x_size; ++x)
        {
            for (int y = 0; y < chunk_y_size; ++y)
            {
                for (int z = 0; z < chunk_z_size; ++z)
                {
                    if (!isBlock(glm::ivec3(x, y, z)))
                    {
                        continue;
                    }

                    for (int i = 0; i < 6; i++)
                    {
                        const auto neibor = glm::ivec3(x, y, z) + impl::graphics::normals[i];
                        // 在边界处的面不考虑 一律添加 必须先检查是否在区块内防止越界
                        if (isInChunk(neibor))
                        {
                            if (isBlock(neibor))
                            {
                                continue;
                            }
                        }
                        addFace(i, getBlock({x, y, z}), {x + chunkPos_.x * 16, y, z + chunkPos_.y * 16});
                    }
                }
            }
        }
    }

    void addFace(size_t i, impl::BlockType type, const glm::ivec3& blockPos)
    {
        auto& vertices = blockVertices_[type];
        for (int j = 0; j < 6; j++)
        {
            auto vertex = impl::graphics::vertices[i][j];
            vertex.position += blockPos;
            vertices.push_back(vertex);
        }
    }

  public:
    explicit Chunk(const glm::ivec2& chunkPos)
    {
        chunkPos_ = chunkPos;
    }
    ~Chunk() = default;

    const std::unordered_map<impl::BlockType, std::vector<impl::graphics::Vertex>>&
    getVertexDict()
    {
        if (dirty)
        {
            rebuildDict();
        }
        return blockVertices_;
    }

    void setBlock(const glm::ivec3& pos, impl::BlockType blockType)
    {
        dirty = true;
        blocks_[toIndex(pos.x, pos.y, pos.z)].type = blockType;
    }

    void destoryBlock(const glm::ivec3& pos)
    {
        dirty = true;
        blocks_[toIndex(pos.x, pos.y, pos.z)].type = impl::BlockType::air;
    }

    [[nodiscard]] impl::BlockType getBlock(const glm::ivec3& pos) const
    {
        return blocks_[toIndex(pos.x, pos.y, pos.z)].type;
    }

    [[nodiscard]] bool isBlock(const glm::ivec3& pos) const
    {
        return blocks_[toIndex(pos.x, pos.y, pos.z)].type != impl::BlockType::air;
    }

    static bool isInChunk(const glm::ivec3& pos)
    {
        if (pos.x < 0 || pos.y < 0 || pos.z < 0 || pos.x > chunk_x_size || pos.y > chunk_y_size || pos.z > chunk_z_size)
        {
            return false;
        }
        return true;
    }
};
} // namespace mc
