// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2025 ss
//
module;

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

    static Mesh createMesh(const std::vector<impl::graphics::Vertex>& vertices)
    {
        Mesh mesh{vertices};
        return mesh;
    }

    MeshManager(const MeshManager&) = delete;
    MeshManager& operator=(const MeshManager&) = delete;
    MeshManager(const MeshManager&&) = default;
    MeshManager& operator=(const MeshManager&&) = default;
};
} // namespace mc
