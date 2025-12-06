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

namespace mc
{
export class RenderSystem
{
  private:
    std::vector<const Shader*> shaders_;
    size_t shaderIndex_ = 0;

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

        updateProjection(width, height, shaders_[shaderIndex_]);
    }

    void setShader(size_t index)
    {
        shaderIndex_ = index;
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


    RenderSystem(const RenderSystem&) = delete;
    RenderSystem(RenderSystem&&) = delete;
    RenderSystem& operator=(RenderSystem&) = delete;
    RenderSystem& operator=(RenderSystem&&) = delete;
};
} // namespace mc
