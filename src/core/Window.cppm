// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2025 ss
// 窗口主类
module;
#include <optional>
export module core:Window;
import glfw;
import spdlog;
import opengl;
import entt;

import impl;

namespace mc
{

export class Window
{
  private:
    glfw::window* m_window = nullptr;
    bool m_isDisplayCursor = false;

    double m_lastTime = 0.0;
    int fps_ = 0;

  public:
    Window() = default;
    ~Window()
    {
        glfw::destroyWindow(m_window);
        m_window = nullptr;
    }

    std::optional<impl::error::ErrorType> createWindow(int width, int height, const char* title)
    {
        if (m_window != nullptr)
        {
            spdlog::warn("窗口已经创建");
            return std::nullopt;
        }

        glfw::windowHint(glfw::scale_to_monitor, glfw::FALSE);  // 禁用系统缩放
        glfw::windowHint(glfw::scale_framebuffer, glfw::FALSE); // 禁用帧缓冲缩放
        glfw::windowHint(glfw::context_version_major, 3);
        glfw::windowHint(glfw::context_version_minor, 3);
        glfw::windowHint(glfw::opengl_profile, glfw::opengl_core_profile);
        m_window = glfw::createWindow(width, height, title, nullptr, nullptr);

        if (!m_window)
        {
            spdlog::critical("窗口创建失败");
            return impl::error::ErrorType::window_create_window_failed;
        }
        spdlog::debug("窗口创建成功");
        glfw::makeContextCurrent(m_window);
        spdlog::debug("创建opengl上下文");

        glfw::swapInterval(0); // Vsync

        glfw::setInputMode(m_window, glfw::cursor, glfw::cursor_disabled);

        return std::nullopt;
    }

    bool shouldClose() const
    {
        return glfw::windowShouldClose(m_window);
    }

    void swapBuffers() const
    {
        glfw::swapBuffers(m_window);
    }

    void pollEvents() const
    {
        glfw::pollEvents();
    }

    void closeWindow() const
    {
        glfw::setWindowShouldClose(m_window, true);
    }

    void toggleCursor()
    {
        if (m_isDisplayCursor)
        {
            glfw::setInputMode(m_window, glfw::cursor, glfw::cursor_disabled);
            m_isDisplayCursor = false;
        }
        else
        {
            glfw::setInputMode(m_window, glfw::cursor, glfw::cursor_normal);
            m_isDisplayCursor = true;
        }
        spdlog::info("鼠标模式: {}", m_isDisplayCursor ? "显示" : "隐藏");
    }

    [[nodiscard]] bool isKeyPressed(impl::Key key) const
    {
        return glfw::getKey(m_window, static_cast<int>(key)) == glfw::press;
    }

    [[nodiscard]] impl::MousePos getMousePos() const
    {
        double xpos, ypos;
        glfw::getCursorPos(m_window, &xpos, &ypos);
        return {.x = (float)xpos, .y = (float)ypos};
    }

    [[nodiscard]] bool isButtonPressed(impl::Button button) const
    {
        return glfw::getMouseButton(m_window, static_cast<int>(button)) == glfw::press;
    }

    void updateFPS(double currentTime)
    {
        fps_++;
        if (currentTime - m_lastTime >= 1.0)
        {
            m_lastTime = currentTime;
            spdlog::info("FPS: {}", fps_);
            fps_ = 0;
        }
    }

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
    Window(Window&&) = default;
    Window& operator=(Window&&) = default;
};
} // namespace mc
