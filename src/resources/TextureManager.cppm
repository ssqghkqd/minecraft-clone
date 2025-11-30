// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2025 ss
// 纹理管理器
module;
#include <cassert>
#include <filesystem>
#include <string>
#include <unordered_map>

export module resources:TextureManager;
import opengl;
import spdlog;
import utils;
import stb_image;

namespace fs = std::filesystem;

export namespace mc
{
class TextureManager
{
  private:
    std::unordered_map<std::string, gl::uint> m_textures; // 纹理缓存
    gl::uint m_lastTexture = 0;

  public:
    TextureManager()
    {
        spdlog::info("纹理管理器已初始化");
    }
    ~TextureManager()
    {
        for (auto& [name, texture] : m_textures)
        {
            gl::deleteTextures(1, &texture);
        }
        m_textures.clear();
    }

    // path是完整路径（assets下的)
    gl::uint loadTexture(const std::string& textureName, const fs::path& path)
    {
        if (m_textures.contains(textureName))
        {
            return m_textures[textureName];
        }

        const auto fullPathPossible = FileUtils::getResourcePath(path, true);
        if (!fullPathPossible.has_value())
        {
            // 任何加载时错误应该直接退出程序
            spdlog::critical("纹理加载失败:{}不存在", textureName);
            throw std::runtime_error(fullPathPossible.error());
        }

        const auto fullPath = fullPathPossible.value();
        int width, height, nrChannels;
        unsigned char* data = stbi::load(fullPath.string().c_str(), &width, &height, &nrChannels, 0);

        if (!data)
        {
            const char* r = stbi::failureReason();
            spdlog::critical("加载{}失败 原因{}", textureName, r);
            throw std::runtime_error(fullPath.string());
        }

        gl::glenum format = gl::rgb;
        switch (nrChannels)
        {
            case 1:
                format = gl::red;
                break;
            case 3:
                format = gl::rgb;
                break;
            case 4:
                format = gl::rgba;
                break;
            default:
                stbi::imageFree(data);
                spdlog::critical("加载{}失败，原因不支持{}通道", fullPath.string(), nrChannels);
                throw std::runtime_error(stbi::failureReason());
        }

        gl::uint textureID;
        gl::genTextures(1, &textureID);
        gl::bindTexture(gl::texture_2d, textureID);

        gl::texParameteri(gl::texture_2d, gl::texture_wrap_s, gl::repeat);
        gl::texParameteri(gl::texture_2d, gl::texture_wrap_t, gl::repeat);
        gl::texParameteri(gl::texture_2d, gl::texture_min_filter, gl::linear_mipmap_linear);
        gl::texParameteri(gl::texture_2d, gl::texture_mag_filter, gl::linear);

        gl::texImage2D(gl::texture_2d, 0, format, width, height, 0, format, gl::unsigned_byte, data);
        gl::generateMipmap(gl::texture_2d);
        gl::activeTexture(gl::texture0);

        stbi::imageFree(data);

        m_textures[textureName] = textureID;

        spdlog::info("加载纹理{}， 宽{} 高{} 通道数{}", fullPath.string(), width, height, nrChannels);

        return textureID;
    }

    gl::uint getTexture(const std::string& name) const
    {
        const auto it = m_textures.find(name);
        if (it != m_textures.end())
        {
            return it->second;
        }
        return 0; // 无效纹理
    }

    void bind(gl::uint id)
    {
        assert(id != 0 && "id无效");
        if (id != m_lastTexture)
        {
            // 别检查 id不存在确实导致段错误，但不应该检查，应该在编程时发现bug，否则性能真的太差了
            gl::bindTexture(gl::texture_2d, id);
            m_lastTexture = id;
        }
    }

    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;
    TextureManager(TextureManager&&) = default;
    TextureManager& operator=(TextureManager&&) = default;
};
} // namespace mc
