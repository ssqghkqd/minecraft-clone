// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2025 ss
// 初始化 纯过程函数
module;

export module core:Init;
import entt;
import spdlog;

import utils;
import Config;

import :Window;

namespace mc::Init
{
void initBasic()
{
    Time::init();
    spdlog::set_pattern("[%H:%M:%S][%l] %v");
}

void initManager(entt::registry& reg)
{
    auto& window = reg.ctx().emplace<Window>();
    window.createWindow(window_width * window_scale, window_height * window_scale, window_title);
}

export void init(entt::registry& reg)
{
    initBasic();
    initManager(reg);
}
}


