// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2025 ss
// 初始化 纯过程函数
module;

export module core:Init;
import entt;
import spdlog;

import utils;
import Config;

import :InputSystem;
import :Window;
import :AppLogicSys;

namespace mc::Init
{
void initBasic()
{
    Time::init();
    spdlog::set_pattern("[%H:%M:%S][%l] %v");
}

void initManager(entt::registry& reg)
{
    auto& dp = reg.ctx().emplace<entt::dispatcher>();
    auto& window = reg.ctx().emplace<Window>();
    window.createWindow(window_width * window_scale, window_height * window_scale, window_title);

    reg.ctx().emplace<InputSystem>();

    AppLogic::init(dp);
}

export void init(entt::registry& reg)
{
    initBasic();
    initManager(reg);
}
}


