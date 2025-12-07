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
    auto& shaderM = reg.ctx().get<ShaderManager>();
    auto& textureM = reg.ctx().get<TextureManager>();

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
    if (!gl::loadGLLoader((gl::loadproc)glfw::getProcAddress))
    {
        spdlog::critical("gl函数指针加载失败");
        return error::init_glad_failed;
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
    reg.ctx().emplace<TextureManager>();
    reg.ctx().emplace<AudioManager>();

    // 3.graphics
    reg.ctx().emplace<ShaderManager>();
    reg.ctx().emplace<RenderSystem>();

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

export std::optional<error>
init(entt::registry& reg)
{
    initBasic();
    initGL();

    emplaceManager(reg);
    registerEvents(reg);

    const auto e = loadResource(reg);
    if (e.has_value())
    {
        return e;
    }



    return std::nullopt;
}
} // namespace mc::Init
