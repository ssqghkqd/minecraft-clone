// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2025 ss
// 主类 应用程序的生命周期管理
module;

export module core:App;
import entt;
import spdlog;

import utils;
import Config;

import :Init;
import :InputSystem;

export namespace mc
{
class App
{
  private:
    entt::registry m_registry{};

  public:
    App()
    {
        Init::init(m_registry);
    }
    ~App() = default; // 自动清理资源

    void run()
    {
        Time::gameStart();
        spdlog::info("游戏开始");
        mainloop();
    }

    void mainloop()
    {
        auto& window = m_registry.ctx().get<Window>();
        auto& inputsys = m_registry.ctx().get<InputSystem>();

        while (!window.shouldClose())
        {
            Time::update();
            window.pollEvents();

            inputsys.update(m_registry);

            window.swapBuffers();
        }
    }
};
} // namespace mc
