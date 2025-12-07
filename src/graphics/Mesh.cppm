// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2025 ss
//
module;
#include <vector>
export module graphics:Mesh;
import opengl;
import impl;

namespace mc
{
export class Mesh
{
  private:
    friend class MeshManager;
    gl::buffer vao_{0}, vbo_{0};
    size_t vertexCount_{0};


  public:
    explicit Mesh(const std::vector<impl::graphics::Vertex>& vertices)
    {
        vertexCount_ = vertices.size();
        gl::genBuffers(1, &vbo_);
        gl::genVertexArrays(1, &vao_);

        gl::bindVertexArray(vao_);
        gl::bindBuffer(gl::array_buffer, vbo_);
        gl::bufferData(gl::array_buffer,
                       vertices.size() * sizeof(impl::graphics::Vertex),
                       vertices.data(),
                       gl::static_draw);

        gl::vertexAttribPointer(0,
                                3,
                                gl::FLOAT,
                                gl::FALSE,
                                sizeof(impl::graphics::Vertex),
                                (void*)offsetof(impl::graphics::Vertex, position));
        gl::enableVertexAttribArray(0);
        gl::vertexAttribPointer(1,
                                2,
                                gl::FLOAT,
                                gl::FALSE,
                                sizeof(impl::graphics::Vertex),
                                (void*)offsetof(impl::graphics::Vertex, texCoord));
        gl::enableVertexAttribArray(1);

        gl::bindVertexArray(0);
    }
    ~Mesh()
    {
        gl::deleteBuffers(1, &vbo_);
        gl::deleteVertexArrays(1, &vao_);
    }

    [[nodiscard]] gl::buffer getVAO() const
    {
        return vao_;
    }
    [[nodiscard]] gl::buffer getVBO() const
    {
        return vbo_;
    }
    size_t getVertexCount() const
    {
        return vertexCount_;
    }

    Mesh(const Mesh& other) = delete;
    Mesh(Mesh&& other) = default;
    Mesh& operator=(const Mesh& other) = delete;
    Mesh& operator=(Mesh&& other) = default;
};

} // namespace mc