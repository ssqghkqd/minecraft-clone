// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2025 ss
// 渲染管线（类似vk）
module;
export module graphics:Pipeline;
import :Shader;
import opengl;
import glm;

namespace mc
{
export class Pipeline
{
  public:
    struct PipelineState
    {
        Shader* shader_{nullptr};
        bool depthTest_{true};
        bool cullFace_{true};
        glm::vec2 viewPort_{0, 0};
    };

    explicit Pipeline(const PipelineState& state)
    {
        state_ = state;
    }
    ~Pipeline() = default;

    void bind()
    {
        if (currentPipeline != this)
        {
            state_.shader_->use();
            setStatus(state_.depthTest_, gl::depth_test);
            setStatus(state_.cullFace_, gl::cull_face);
            gl::viewport(0, 0, state_.viewPort_.x, state_.viewPort_.y);
        }
        currentPipeline = this;
    }

    template<typename T>
    void setUniform(const char* name, T value)
    {
        state_.shader_->set(name, value);
    }

  private:
    PipelineState state_{};

    inline static Pipeline* currentPipeline{nullptr};

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
};
} // namespace mc
