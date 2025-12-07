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

  public:
    World() = default;
    ~World() = default;

    void init()
    {
        chunks.reserve(16);
        chunks.push_back(std::make_unique<Chunk>(glm::ivec2(0, 0)));
        chunks.push_back(std::make_unique<Chunk>(glm::ivec2(1, 0)));
        chunks.push_back(std::make_unique<Chunk>(glm::ivec2(0, 1)));
        chunks.push_back(std::make_unique<Chunk>(glm::ivec2(1, 1)));
        for (int i =0; i < 16; i++)
        {
            for (int j = 0; j < 16; j++)
            {
                chunks[0]->setBlock({i,0,j}, impl::BlockType::grass_block);
                chunks[1]->setBlock({i,0,j}, impl::BlockType::grass_block);
                chunks[2]->setBlock({i,0,j}, impl::BlockType::grass_block);
                chunks[3]->setBlock({i,0,j}, impl::BlockType::grass_block);
            }
        }

    }

    [[nodiscard]] const std::unordered_map<impl::BlockType, std::vector<impl::Vertex>>&
        getRenderInfor() const
    {
        return chunks[0]->getRenderInfor();
    }

    World(const World&) = delete;
    World(const World&&) = delete;
    World& operator=(const World&) = delete;
    World& operator=(World&&) = delete;
};
} // namespace mc