// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2025 ss
//
module;
#include <memory>
#include <vector>
export module graphics:MeshManager;
import :Mesh;

namespace mc
{
export class MeshManager
{
  private:
  public:
    MeshManager() = default;
    ~MeshManager() = default;

    static std::unique_ptr<Mesh> createMesh(const std::vector<impl::graphics::Vertex>& vertices)
    {
        auto mesh = std::make_unique<Mesh>(vertices);
        return mesh;
    }

    MeshManager(const MeshManager&) = delete;
    MeshManager& operator=(const MeshManager&) = delete;
    MeshManager(const MeshManager&&) = delete;
    MeshManager& operator=(const MeshManager&&) = delete;
};
} // namespace mc
