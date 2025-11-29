//
// Created by ss on 2025/11/22.
//
module;
export module Config;

export namespace mc
{
constexpr int window_width = 1280;
constexpr int window_height = 960;
constexpr const char* window_title = "Minecraft";
constexpr float window_scale = 1.0f;
constexpr float stat_interval = 1.0f;
constexpr int block_count = 10;

constexpr float max_distance = 10.0f; // 玩家手长度
constexpr float step_distance = 0.1f;
constexpr float max_steps = max_distance / step_distance;

} // namespace th