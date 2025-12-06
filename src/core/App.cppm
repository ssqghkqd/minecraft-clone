// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2025 ss
// 主类 应用程序的生命周期管理a
module;
#include <string>
export module core:App;
import entt;
import spdlog;

import utils;
import impl;

import :Init;
import :InputSystem;

import game.ecs;

namespace mc
{
struct AppHandler
{
    Window& window;
    void handleAppShutDownRequestEvent([[maybe_unused]] const impl::events::AppShutDownRequestEvent& event) const
    {
        window.closeWindow();
    }
    void handleWindowToggleCursorEvent([[maybe_unused]] const impl::events::WindowToggleCursorEvent& event) const
    {
        window.toggleCursor();
    };
};

export class App
{
  private:
    entt::registry m_registry{};
    std::string m_errorInfor{};
    bool m_init_failed{false};

  public:
    App()
    {
        auto initPoss = Init::init(m_registry);
        if (initPoss.has_value())
        {
            m_errorInfor = impl::error::getError(initPoss.value());
            m_init_failed = true;
            return;
        }
        registerEvent();
    }
    ~App() = default; // 自动清理资源

    int run()
    {
        if (m_init_failed)
        {
            spdlog::critical("致命错误 退出程序:{}", m_errorInfor);
            return 1;
        }
        Time::gameStart();
        spdlog::debug("游戏开始");
        mainloop();
        return 0;
    }

    void mainloop()
    {
        auto& window = m_registry.ctx().get<Window>();
        auto& inputsys = m_registry.ctx().get<InputSystem>();
        auto& playerSys = m_registry.ctx().get<PlayerSys>();

        while (!window.shouldClose())
        {
            Time::update();
            window.pollEvents();

            inputsys.update(m_registry);

            playerSys.update(m_registry);

            window.swapBuffers();
        }
    }

    void registerEvent()
    {
        auto& dp = m_registry.ctx().get<entt::dispatcher>();
        auto& window = m_registry.ctx().get<Window>();
        static AppHandler appHandler{window};
        dp.sink<impl::events::AppShutDownRequestEvent>()
            .connect<&AppHandler::handleAppShutDownRequestEvent>(appHandler);
        dp.sink<impl::events::WindowToggleCursorEvent>()
            .connect<&AppHandler::handleWindowToggleCursorEvent>(appHandler);
    }
};
} // namespace mc
