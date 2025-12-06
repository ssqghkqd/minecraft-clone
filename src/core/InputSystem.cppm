// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2025 ss
// 输入系统
module;

export module core:InputSystem;
import entt;
import :Window;
import impl;

namespace mc
{
export class InputSystem
{
private:
public:
    InputSystem() = default;
    ~InputSystem() = default;

    void update(entt::registry& reg)
    {
        const auto& window = reg.ctx().get<Window>();
        impl::events::InputState currentState{};

        currentState.keyActions.w = window.isKeyPressed(impl::Key::w);
        currentState.keyActions.s = window.isKeyPressed(impl::Key::s);
        currentState.keyActions.d = window.isKeyPressed(impl::Key::d);
        currentState.keyActions.a = window.isKeyPressed(impl::Key::a);
        currentState.keyActions.left_alt = window.isKeyPressed(impl::Key::left_alt);
        currentState.keyActions.left_control = window.isKeyPressed(impl::Key::left_control);
        currentState.keyActions.left_shift = window.isKeyPressed(impl::Key::left_shift);
        currentState.keyActions.space = window.isKeyPressed(impl::Key::space);
        currentState.keyActions.esc = window.isKeyPressed(impl::Key::ecs);
        reg.ctx().get<entt::dispatcher>().trigger(currentState);
    }

    InputSystem(const InputSystem&) = delete;
    InputSystem& operator=(const InputSystem&) = delete;
    InputSystem(InputSystem&&) = default;
    InputSystem& operator=(InputSystem&&) = default;
};
}
