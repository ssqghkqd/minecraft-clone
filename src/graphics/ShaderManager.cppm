// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2025 ss
//
module;
#include <expected>
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>

export module graphics:ShaderManager;
import entt;
import spdlog;

import :Shader;

namespace fs = std::filesystem;

namespace mc
{
export class ShaderManager
{
  private:
    std::pmr::unordered_map<std::string, std::unique_ptr<Shader>> m_shaders{};

  public:
    ShaderManager() = default;
    ~ShaderManager() = default;

    std::expected<Shader*, impl::error::ErrorType>
    load(const std::string& name, const fs::path& vertPath, const fs::path& fragPath)
    {
        const auto it = m_shaders.find(name);
        if (it != m_shaders.end())
        {
            return it->second.get();
        }

        auto [id, inserted] = m_shaders.emplace(name, std::make_unique<Shader>());
        auto shaderPossible = id->second->load(vertPath, fragPath);
        if (!shaderPossible.has_value())
        {
            return std::unexpected(shaderPossible.error());
        }
        spdlog::debug("加载着色器{}", name);
        return id->second.get();
    }

    Shader* get(const std::string& name)
    {
        // 不要用contains 否则两次查找
        const auto it = m_shaders.find(name);
        if (it != m_shaders.end())
        {
            return it->second.get();
        }
        return nullptr;
    }

    ShaderManager(const ShaderManager&) = delete;
    ShaderManager& operator=(const ShaderManager&) = delete;
    ShaderManager(ShaderManager&&) = default;
    ShaderManager& operator=(ShaderManager&&) = default;
};
} // namespace mc
