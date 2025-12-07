// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2025 ss
//
module;
#include <memory>
#include <optional>
#include <unordered_map>
#include <vector>
export module graphics:Render;
import opengl;
import impl;
import glm;

import :Mesh;
import :MeshManager;
import :TextureManager;
import :ShaderManager;
import :Pipeline;

namespace mc
{
export class Render
{
    MeshManager meshManager_{};
    TextureManager textureManager_{};
    ShaderManager shaderManager_{};

    std::unique_ptr<Pipeline> pipelineDefault_;

    std::unordered_map<gl::uint, std::unique_ptr<Mesh>> meshes_{};

  public:
    TextureManager& getTextureManager() { return textureManager_; }
    ShaderManager& getShaderManager() { return shaderManager_; }

    std::optional<impl::error::ErrorType> init(int width, int height)
    {
        meshes_.reserve(500);
        const auto shader = shaderManager_.get("default");

        gl::clearColor(0.53f, 0.81f, 0.98f, 1.0f);


        auto pipelineState = Pipeline::PipelineState{.shader_ = shader,
                                                     .depthTest_ = true,
                                                     .cullFace_ = false,
                                                     .viewPort_ = {width, height}};
        pipelineDefault_ = std::make_unique<Pipeline>(pipelineState);

        setProjection(width, height);
        return std::nullopt;
    }

    void beginFrame()
    {
        gl::clear(gl::color_buffer_bit | gl::depth_buffer_bit);
    }
    void endFrame()
    {
    }

    void setProjection(int width, int height)
    {
        const auto projection = glm::gtc::perspective(glm::radians(90.0f),
                                                      (float)width / (float)height,
                                                      0.1f,
                                                      100.0f);
        pipelineDefault_->bind();
        pipelineDefault_->setUniform<glm::mat4>("projection", projection);
    }

    void renderWorld(const std::unordered_map<gl::uint, std::vector<impl::graphics::Vertex>>& vertexDict,
                     const glm::mat4& view)
    {
        pipelineDefault_->bind();
        pipelineDefault_->setUniform<glm::mat4>("view", view);
        for (const auto& [id, vertices] : vertexDict)
        {
            auto mesh = meshManager_.createMesh(vertices);
            meshes_.clear();
            meshes_[id] = std::move(mesh);
        }


        for (const auto& [id, mesh] : meshes_)
        {
            gl::bindTexture(gl::texture_2d, id);
            gl::bindVertexArray(mesh->getVAO());
            gl::drawArrays(gl::triangles, 0, mesh->getVertexCount());
        }
    }
};
} // namespace mc