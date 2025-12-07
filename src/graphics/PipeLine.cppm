// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2025 ss
// 渲染管线（类似vk）
module;

export module graphics:PipeLine;
import :Shader;
import opengl;
import glm;

namespace mc
{
export class PipeLine
{
  private:
    const Shader* shader_{nullptr};
    bool depthTest_{true};
    bool cullFace_{true};
    glm::vec2 viewPort_{0, 0};

    static void setStatus(bool targetStatus, gl::glenum status)
    {
        if (targetStatus)
        {
            gl::enable(status);
        }
        else
        {
            gl::disable(status);
        }
    }

  public:
    explicit PipeLine(const Shader* shader, bool depthTest, bool cullFace, const glm::vec2& viewPort)
    {
        shader_ = shader;
        depthTest_ = depthTest;
        cullFace_ = cullFace;
        viewPort_ = viewPort;
    }
    ~PipeLine() = default;

    void bind() const
    {
        shader_->use();
        setStatus(depthTest_, gl::depth_test);
        setStatus(cullFace_, gl::cull_face);
        gl::viewport(0, 0, viewPort_.x, viewPort_.y);
    }
};
} // namespace mc
