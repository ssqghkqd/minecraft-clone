// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2025 ss
// 初始化 纯过程函数
module;
#include <optional>
export module core:Init;
import entt;
import spdlog;

import utils;
import impl;

import :InputSystem;
import :Window;
import :AppLogicSys;

import graphics;
import game.ecs;

namespace mc::Init
{
void initBasic()
{
    Time::init();
    spdlog::set_pattern("[%H:%M:%S][%l] %v");
    spdlog::set_level(spdlog::level_enum::debug);
}

void initManager(entt::registry& reg)
{
    auto& dp = reg.ctx().emplace<entt::dispatcher>();
    auto& window = reg.ctx().emplace<Window>();
    window.createWindow(impl::config::window_width * impl::config::window_scale,
                        impl::config::window_height * impl::config::window_scale,
                        impl::config::window_title);

    reg.ctx().emplace<InputSystem>();

    reg.ctx().emplace<ShaderManager>();

    reg.ctx().emplace<RenderSystem>();
    auto& ps = reg.ctx().emplace<PlayerSys>(reg);

    ps.create(reg);
    ps.registerMove(dp);
    AppLogic::init(dp);
}

std::optional<impl::error::ErrorType>
loadResource(entt::registry& reg)
{
    auto& shaderM = reg.ctx().get<ShaderManager>();
    auto shaderPoss = shaderM.load("default", "shaders/default.vs", "shaders/default.fs");
    if (!shaderPoss.has_value())
    {
        return shaderPoss.error();
    }

    return std::nullopt;
}

void initOtherManager(entt::registry& reg)
{
    auto& rs = reg.ctx().get<RenderSystem>();
    auto& shaderM = reg.ctx().get<ShaderManager>();

    rs.init(impl::config::window_width * impl::config::window_scale,
            impl::config::window_height * impl::config::window_scale,
            {shaderM.get("default")},
            0);
}

export std::optional<impl::error::ErrorType>
init(entt::registry& reg)
{
    initBasic();
    initManager(reg);
    const auto initMPoss = loadResource(reg);
    if (initMPoss.has_value())
    {
        return initMPoss;
    }

    return std::nullopt;
}
} // namespace mc::Init
