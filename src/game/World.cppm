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
    std::vector<std::unique_ptr<Chunk>> chunks{16};

  public:
    World() = default;
    ~World() = default;

    void init()
    {
    }


    World(const World&) = delete;
    World(const World&&) = delete;
    World& operator=(const World&) = delete;
    World& operator=(World&&) = delete;
};
} // namespace mc