// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2025 ss
// 一个专门处理全局性、非游戏性输入逻辑的系统
module;

export module core:AppLogicSys;
import entt;
import impl;
import spdlog;

namespace mc::AppLogic
{
struct Handler
{
    entt::dispatcher& dp;
    impl::events::InputState m_prevState{};
    void handleInput(const impl::events::InputState& event)
    {
        if (event.keyStates.esc)
        {
            dp.trigger(impl::events::AppShutDownRequestEvent{});
        }
        // 按键防抖
        if (event.keyStates.left_alt && !m_prevState.keyStates.left_alt)
        {
            dp.trigger(impl::events::WindowToggleCursorEvent{});
        }
        m_prevState = event;
    }
};

export void registerHandle(entt::dispatcher& dp)
{
    static Handler handler{dp};
    dp.sink<impl::events::InputState>().connect<&Handler::handleInput>(handler);
}
} // namespace mc::AppLogic
