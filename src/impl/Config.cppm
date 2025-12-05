// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2025 ss
// 配置数据
module;

export module impl:Config;

export namespace mc::impl::config
{
constexpr int window_width = 1920;
constexpr int window_height = 1080;
constexpr const char* window_title = "Minecraft";
constexpr float window_scale = 0.5f;
constexpr float stat_interval = 1.0f;
constexpr int block_count = 10;

constexpr float max_distance = 10.0f; // 玩家手长度
constexpr float step_distance = 0.01f;
constexpr float max_steps = max_distance / step_distance;

}