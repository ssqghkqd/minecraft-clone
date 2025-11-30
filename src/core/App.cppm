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
import :Events;

namespace mc
{
struct AppHandler
{
    Window& window;
    void handleAppShutDownRequestEvent([[maybe_unused]] const events::AppShutDownRequestEvent& event) const
    {
        window.closeWindow();
    }
    void handleWindowToggleCursorEvent([[maybe_unused]] const events::WindowToggleCursorEvent& event) const
    {
        window.toggleCursor();
    };
};

export class App
{
  private:
    entt::registry m_registry{};

  public:
    App()
    {
        Init::init(m_registry);
        registerEvent();
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

    void registerEvent()
    {
        auto& dp = m_registry.ctx().get<entt::dispatcher>();
        auto& window = m_registry.ctx().get<Window>();
        static AppHandler appHandler{window};
        dp.sink<events::AppShutDownRequestEvent>()
            .connect<&AppHandler::handleAppShutDownRequestEvent>(appHandler);
        dp.sink<events::WindowToggleCursorEvent>()
            .connect<&AppHandler::handleWindowToggleCursorEvent>(appHandler);
    }
};
} // namespace mc
