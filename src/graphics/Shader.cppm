// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2025 ss
// 着色器对象  这个类不是单例注意
module;
#include <array>
#include <cassert>
#include <expected>
#include <filesystem>

export module graphics:Shader;
import utils;
import impl;

import spdlog;
import opengl;
import glm;

namespace fs = std::filesystem;

namespace mc
{
using shaders = std::array<gl::shader, 2>;
export class Shader
{
  private:
    // 这其实就是uint
    gl::shader m_id{};
    shaders m_shaders{};

    static gl::shader createShader(const gl::glenum type, const char* shaderSource)
    {
        const gl::shader shader = gl::createShader(type);
        gl::shaderSource(shader, 1, &shaderSource, nullptr);
        gl::compileShader(shader);
        return shader;
    }

    static bool checkShader(gl::shader shader)
    {
        int success = 0;
        gl::getShaderiv(shader, gl::compile_status, &success);
        if (!success)
        {
            constexpr std::size_t max_shader_log_length = 4096;
            char shaderLog[max_shader_log_length]{};
            gl::getShaderInfoLog(shader, max_shader_log_length - 1, nullptr, shaderLog);
            spdlog::critical("着色器编译失败:{}", shaderLog);
            return false;
        }
        return true;
    }

    static gl::shader createShaderProgram(const shaders& shaders)
    {
        gl::shader id = gl::createProgram();
        for (const auto& shader : shaders)
        {
            gl::attachShader(id, shader);
        }
        gl::linkProgram(id);
        return id;
    }

    static bool checkProgram(gl::shader id)
    {
        int success = 0;
        gl::getProgramiv(id, gl::link_status, &success);
        if (!success)
        {
            constexpr std::size_t max_shader_log_length = 4096;
            char programLog[max_shader_log_length]{};
            gl::getProgramInfoLog(id, max_shader_log_length - 1, nullptr, programLog);
            spdlog::critical("着色器程序链接失败:{}", programLog);
            return false;
        }
        return true;
    }

  public:
    Shader() = default;
    ~Shader() = default;

    std::expected<gl::shader, impl::error::ErrorType>
    load(const fs::path& vertPath, const fs::path& fragPath)
    {
        const auto vertPathPossible = FileUtils::getResourcePath(vertPath, false);
        const auto fragPathPossible = FileUtils::getResourcePath(fragPath, false);
        if (!vertPathPossible.has_value() || !fragPathPossible.has_value())
        {
            spdlog::critical("着色器文件不存在");
            return std::unexpected(impl::error::ErrorType::file_not_found);
        }
        const auto vertSourcePossible = FileUtils::readFileToString(vertPathPossible.value());
        const auto fragSourcePossible = FileUtils::readFileToString(fragPathPossible.value());

        if (!vertSourcePossible.has_value() || !fragSourcePossible.has_value())
        {
            spdlog::critical("无法读取着色器代码");
            return std::unexpected(impl::error::ErrorType::file_open_failed);
        }

        const auto vertShader = createShader(gl::vertex_shader, vertSourcePossible.value().c_str());
        const auto fragShader = createShader(gl::fragment_shader, fragSourcePossible.value().c_str());
        if (!checkShader(vertShader))
        {
            return std::unexpected(impl::error::ErrorType::shader_vert_failed);
        }

        if (!checkShader(fragShader))
        {
            return std::unexpected(impl::error::ErrorType::shader_frag_failed);
        }

        m_shaders[0] = vertShader;
        m_shaders[1] = fragShader;

        m_id = createShaderProgram(m_shaders);
        if (!checkProgram(m_id))
        {
            return std::unexpected(impl::error::ErrorType::shader_program_failed);
        }

        for (auto& shader : m_shaders)
        {
            gl::deleteShader(shader);
            shader = 0;
        }
        return m_id;
    }

    // 请避免string的构造开销
    void set(const char* name, const glm::mat4& mat) const
    {
        const int location = gl::getUniformLocation(m_id, name);
        assert(location >= 0 && "找不到uniform！");
        gl::uniformMatrix4fv(location, 1, gl::FALSE, glm::gtc::value_ptr(mat));
    }
};
} // namespace mc
