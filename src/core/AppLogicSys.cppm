// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2025 ss
// 一个专门处理全局性、非游戏性输入逻辑的系统
module;

export module core:AppLogicSys;
import entt;
import :Events;
import spdlog;

namespace mc::AppLogic
{
struct Handler
{
    entt::dispatcher& dp;
    events::InputState m_prevState{};
    void handleInput(const events::InputState& event)
    {
        if (event.keyActions.esc)
        {
            dp.trigger(events::AppShutDownRequestEvent{});
        }
        // 按键防抖
        if (event.keyActions.left_alt && !m_prevState.keyActions.left_alt)
        {
            dp.trigger(events::WindowToggleCursorEvent{});
        }
        m_prevState = event;
    }
};

export void init(entt::dispatcher& dp)
{
    static Handler handler{dp};
    dp.sink<events::InputState>().connect<&Handler::handleInput>(handler);
}
} // namespace mc::AppLogic
