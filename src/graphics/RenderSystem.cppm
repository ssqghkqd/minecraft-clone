// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2025 ss
// 渲染系统
module;
#include <vector>
export module graphics:RenderSystem;
import opengl;
import glfw;
import spdlog;
import glm;

import :Shader;
import graphics.impl.Mesh;

namespace mc
{


export class RenderSystem
{
  private:
    std::vector<const Shader*> shaders_;
    size_t shaderIndex_ = 0;

    std::vector<Mesh::RenderBatch>* renderBatches_ = nullptr;

  public:
    RenderSystem() = default;
    ~RenderSystem() = default;

    void init(int width, int height, const std::vector<const Shader*>& shaders, size_t shaderIndex)
    {
        shaders_ = shaders;
        shaderIndex_ = shaderIndex;

        gl::enable(gl::depth_test);
        // mc天空色
        gl::clearColor(0.53f, 0.81f, 0.98f, 1.0f);
        gl::viewport(0, 0, width, height);

        setShaderAndUse(shaderIndex);
        updateProjection(width, height, shaders_[shaderIndex_]);
    }

    void setShaderAndUse(size_t index)
    {
        shaderIndex_ = index;
        shaders_[shaderIndex_]->use();
    }

    void updateProjection(int width, int height, const Shader* shader)
    {
        const auto projection = glm::gtc::perspective(
            glm::radians(90.0f),
            (float)width / (float)height,
            0.1f,
            100.0f);

        shader->set("projection", projection);
    }

    void frameBegin()
    {
        gl::clear(gl::color_buffer_bit | gl::depth_buffer_bit);
    }

    void render(std::vector<Mesh::RenderBatch>* batches, const glm::mat4& view)
    {
        renderBatches_ = batches;
        shaders_[shaderIndex_]->set("view", view);
        for (const auto& [id, vao, vbo, count] : *batches)
        {
            gl::activeTexture(gl::texture0);
            gl::bindTexture(gl::texture_2d, id);
            shaders_[shaderIndex_]->set("texture0", 0);
            gl::bindVertexArray(vao);
            gl::drawArrays(gl::triangles, 0, count);
            //spdlog::debug("vao:{},id:{},", vao, id);
        }
    }

    void frameEnd()
    {
        for (auto& it : *renderBatches_)
        {
            it.destory();
        }
    }

    RenderSystem(const RenderSystem&) = delete;
    RenderSystem(RenderSystem&&) = delete;
    RenderSystem& operator=(RenderSystem&) = delete;
    RenderSystem& operator=(RenderSystem&&) = delete;
};
} // namespace mc
