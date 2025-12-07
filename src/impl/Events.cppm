// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2025 ss
// 事件s
module;

export module impl:Events;

namespace mc::impl::events
{
export struct InputState
{
    // 当前帧所有按键的状态 作为一个事件
    struct
    {
        bool w;
        bool a;
        bool s;
        bool d;
        bool space;
        bool left_shift;
        bool left_alt;
        bool left_control;
        bool esc;

    } keyStates;

    struct
    {
        bool left;
        bool right;
        float x;
        float y;
    } mouseStates;

};

export struct AppShutDownRequestEvent
{
};
export struct WindowToggleCursorEvent
{
};

} // namespace mc::impl::events
