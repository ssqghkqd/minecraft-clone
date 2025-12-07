// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2025 ss
//
module;
#include <cstdint>
#include <unordered_map>
#include <vector>
export module graphics.impl.Mesh;
import opengl;
import impl;
import entt;
import resources;

namespace mc::Mesh
{
export struct RenderBatch
{
    gl::uint vao;
    gl::uint vbo;
    gl::uint texture;
    uint32_t vertexCount;

public:
    void destory() const
    {
        gl::deleteBuffers(1, &vbo);
        gl::deleteVertexArrays(1, &vao);
    }
};

} // namespace mc::Mesh