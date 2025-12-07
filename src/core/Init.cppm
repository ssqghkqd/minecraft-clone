// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2025 ss
// 初始化 纯过程函数
module;
#include <optional>
export module core:Init;
import entt;
import spdlog;
import opengl;
import glfw;

import utils;
import impl;

import :InputSystem;
import :Window;
import :AppLogicSys;

import graphics;
import game.ecs;
import resources;
import game;

using error = mc::impl::error::ErrorType;

namespace mc::Init
{
void initBasic()
{
    Time::init();
    spdlog::set_pattern("[%H:%M:%S][%l] %v");
    spdlog::set_level(spdlog::level_enum::debug);
}

std::optional<error>
loadResource(entt::registry& reg)
{
    auto& render = reg.ctx().get<Render>();
    auto& shaderM = render.getShaderManager();
    auto& textureM = render.getTextureManager();

    auto shaderPoss = shaderM.load("default",
                                   "shaders/default.vs",
                                   "shaders/default.fs");
    if (!shaderPoss.has_value())
    {
        return shaderPoss.error();
    }

    auto texturePoss = textureM.loadTexture("grass_block",
                                            "textures/grass_block.png");
    if (!texturePoss.has_value())
    {
        return texturePoss.error();
    }

    return std::nullopt;
}

std::optional<error> initGL()
{
    if (!glfw::init())
    {
        spdlog::critical("glfw初始化失败");
        return error::init_glfw_failed;
    }

    return std::nullopt;
}

void emplaceManager(entt::registry& reg)
{
    reg.ctx().emplace<entt::dispatcher>();
    // 1. core
    reg.ctx().emplace<Window>();
    reg.ctx().emplace<InputSystem>();

    // 2.resources
    reg.ctx().emplace<AudioManager>();

    // 3.graphics
    reg.ctx().emplace<Render>();

    // 4.game
    reg.ctx().emplace<PlayerSys>(reg);
    reg.ctx().emplace<World>();
}

void registerEvents(entt::registry& reg)
{
    auto& dp = reg.ctx().get<entt::dispatcher>();

    auto& playerSys = reg.ctx().get<PlayerSys>();

    AppLogic::registerHandle(dp);
    playerSys.registerMove(dp);
}

void initGame(entt::registry& reg)
{
    auto& playerSys = reg.ctx().get<PlayerSys>();
    auto& world = reg.ctx().get<World>();
    auto& render = reg.ctx().get<Render>();
    auto& textureM = render.getTextureManager();

    playerSys.create(reg);
    world.init();
    render.init(impl::config::window_width * impl::config::window_scale,
                impl::config::window_height * impl::config::window_scale);

    world.registerBlockTexture(impl::BlockType::grass_block, textureM.getTexture("grass_block"));
}

void createWindow(entt::registry& reg)
{
    auto& window = reg.ctx().get<Window>();
    window.createWindow(impl::config::window_width * impl::config::window_scale,
                        impl::config::window_height * impl::config::window_scale,
                        impl::config::window_title);
}

export std::optional<error>
init(entt::registry& reg)
{
    initBasic();
    initGL();
    emplaceManager(reg);
    createWindow(reg);
    registerEvents(reg);
    loadResource(reg);

    // const auto e = loadResource(reg);
    // if (e.has_value())
    // {
    //     return e;
    // }

    initGame(reg);
    return std::nullopt;
}
} // namespace mc::Init
