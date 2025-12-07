// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2025 ss
// 输入系统
module;
#include <cassert>
export module core:InputSystem;
import entt;
import :Window;
import impl;
import glm;

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

        currentState.keyStates.w = window.isKeyPressed(impl::Key::w);
        currentState.keyStates.s = window.isKeyPressed(impl::Key::s);
        currentState.keyStates.d = window.isKeyPressed(impl::Key::d);
        currentState.keyStates.a = window.isKeyPressed(impl::Key::a);
        currentState.keyStates.left_alt = window.isKeyPressed(impl::Key::left_alt);
        currentState.keyStates.left_control = window.isKeyPressed(impl::Key::left_control);
        currentState.keyStates.left_shift = window.isKeyPressed(impl::Key::left_shift);
        currentState.keyStates.space = window.isKeyPressed(impl::Key::space);
        currentState.keyStates.esc = window.isKeyPressed(impl::Key::ecs);

        currentState.mouseStates.x = window.getMousePos().x;
        currentState.mouseStates.y = window.getMousePos().y;
        currentState.mouseStates.left = window.isButtonPressed(impl::Button::left);
        currentState.mouseStates.right = window.isButtonPressed(impl::Button::right);
        reg.ctx().get<entt::dispatcher>().trigger(currentState);
    }


    InputSystem(const InputSystem&) = delete;
    InputSystem& operator=(const InputSystem&) = delete;
    InputSystem(InputSystem&&) = default;
    InputSystem& operator=(InputSystem&&) = default;
};
} // namespace mc
