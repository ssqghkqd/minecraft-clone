// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2025 ss
// 音频管理器
module;
#include <filesystem>
#include <list>
#include <string>
#include <unordered_map>

export module resources:AudioManager;
import miniaudio;
import spdlog;
import utils;

namespace fs = std::filesystem;

export namespace mc
{

class AudioManager
{
  private:
    ma::engine m_engine{};
    ma::sound m_music{};                                                   // 音乐专用通道
    std::unordered_map<std::string, std::filesystem::path> m_musicPaths{}; // 音乐路径表
    std::unordered_map<std::string, ma::sound*> m_sounds{};                // 音效
    std::list<ma::sound*> m_activeSounds{};

    float m_masterVolume = 0.2f;
    float m_musicVolume = 1.0f;
    float m_sfxVolume = 1.0f;

  public:
    AudioManager()
    {
        const ma::result result = ma::engineInit(nullptr, &m_engine);
        if (result != ma::success)
        {
            spdlog::critical("ma引擎初始化失败:{}", std::string(ma::resultDescription(result)));
            throw std::runtime_error("音频系统初始化失败");
        }
        spdlog::info("音频系统初始化成功");
    }

    ~AudioManager()
    {
        ma::soundUninit(&m_music);
        for (auto& [name, sound] : m_sounds)
        {
            ma::soundUninit(sound);
        }
        ma::engineUninit(&m_engine);
    }

    void loadMusic(const std::string& name, const fs::path& path)
    {
        if (!FileUtils::isExist(path))
        {
            spdlog::critical("音乐加载失败，{}不存在", path);
            throw std::runtime_error("音乐加载失败");
        }
        m_musicPaths[name] = path;
        spdlog::info("存储音乐{}->{}", name, path.string());
    }

    // 播放音乐（单实例）
    void playMusic(const std::string& name, float volume, bool loop) noexcept
    {
        if (!m_musicPaths.contains(name))
        {
            spdlog::error("{} 未加载", name);
            return;
        }

        ma::soundUninit(&m_music);
        const auto fullPath = FileUtils::getResourcePath(m_musicPaths[name], true).value();

        const auto result = ma::soundInitFromFile(
            &m_engine,
            fullPath.c_str(),
            ma::sound_flag_stream | ma::sound_flag_async,
            nullptr,
            nullptr,
            &m_music);

        if (result == ma::success)
        {
            ma::soundSetVolume(&m_music, volume * m_musicVolume * m_masterVolume);
            ma::soundSetLooping(&m_music, loop);
            ma::soundStart(&m_music);
            return;
        }
        spdlog::error("音乐播放失败 名称{}，原因:{}", name, ma::resultDescription(result));
    }

    /*
     * sounds哈希表里存储的是模板masound对象，几乎静态
     * 播放时将会分配一块内存通过ma提供的复制播放来播放，存入activesound链表 所有权归他所有并且由cleansound定时检查清理
     * 一些踩坑实录：ma没有提供什么一次加载直接播放什么的 搞了半天最后看到了原来是这样实现的
     */
    void loadSound(const std::string& name, const fs::path& path)
    {
        if (m_sounds.contains(name))
        {
            spdlog::warn("音频已经加载，名：{}", name);
            return;
        }

        const auto fullPathPossible = FileUtils::getResourcePath(path, true);

        if (!fullPathPossible.has_value())
        {
            spdlog::critical("音效加载失败，{}不存在", fullPathPossible.error());
            throw std::runtime_error("音效加载失败");
        }
        const auto fullPath = fullPathPossible.value();

        const auto templateSound = (ma::sound*)malloc(sizeof(ma::sound));
        if (templateSound == nullptr)
        {
            spdlog::critical("内存不足，分配失败");
            throw std::runtime_error("内存不足");
        }
        const ma::result result = ma::soundInitFromFile(
            &m_engine,
            fullPath.c_str(),
            ma::sound_flag_decode,
            nullptr,
            nullptr,
            templateSound);

        if (result != ma::success)
        {
            spdlog::error("加载{} ,失败: {}", path.string(), ma::resultDescription(result));
            free(templateSound);
            throw std::runtime_error("音效加载失败");
        }

        m_sounds[name] = templateSound; // 存储模板
    }

    void playSound(const std::string& name, const float volume, bool loop) noexcept
    {
        if (!m_sounds.contains(name))
        {
            spdlog::error("{} 未加载", name);
            return;
        }

        /*
         * 【内存管理经验】（亲身经历都是）
         * 1.第一反应是使用智能指针 但这里不能使用
         *  如果你直接使用 会导致编译失败
         *  如果你套用自定义删除器 你需要尤其注意move出去移动所有权 否则自动析构 音频驱动将会段错误
         * 2.为什么不用new？ 因为new会尝试调用构造函数 但masound没有，并且还有异常开销
         * 提示：成功路径不需要释放 因为有清理函数检查 失败路径一定要free（malloc成功之后）
         */
        // TODO 可以用对象池 这里malloc可能内存碎片 但目前性能好不用
        const auto sound = (ma::sound*)malloc(sizeof(ma::sound));
        if (sound == nullptr)
        {
            spdlog::error("malloc failed");
            return;
        }
        const ma::result result = ma::soundInitCopy(
            &m_engine,
            m_sounds[name],
            ma::sound_flag_decode,
            nullptr,
            sound);

        if (result != ma::success)
        {
            free(sound);
            spdlog::error("播放失败 {}: {}", name, ma::resultDescription(result));
            return;
        }

        ma::soundSetVolume(sound, volume * m_masterVolume * m_sfxVolume);
        ma::soundSetLooping(sound, loop);
        ma::soundStart(sound);
        m_activeSounds.push_back(sound);
    }

    void cleanSound()
    {
        /*
         * 将会被每秒调用 注意这里播放完的音频将被清理！不要手动管理
         * 频率不要太高（目前1hz） 一开始我用是vector 现在是链表 但仍然保持低频清理
         */
        for (auto it = m_activeSounds.begin(); it != m_activeSounds.end();)
        {
            if (!ma::soundIsPlaying(*it))
            {
                ma::soundUninit(*it);
                free(*it);
                it = m_activeSounds.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }

    AudioManager(const AudioManager&) = delete;
    AudioManager& operator=(const AudioManager&) = delete;
    AudioManager(AudioManager&&) noexcept = default;
    AudioManager& operator=(AudioManager&&) noexcept = default;
};

} // namespace mc