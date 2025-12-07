// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2025 ss
//
module;
export module game.ecs:PlayerSys;
import entt;
import spdlog;

import :EntityComp;
import :Tag;
import impl;
import utils;

namespace mc
{
constexpr glm::vec3 up = {0.0f, 1.0f, 0.0f};
export class PlayerSys
{
  private:
    entt::entity player_{entt::null};
    entt::registry& reg_;

    float xPos_ = 0.0f;
    float yPos_ = 0.0f; // 鼠标位置

    void handleInput(const impl::events::InputState& event)
    {
        // 键盘处理
        PlayerComp& pc = reg_.get<PlayerComp>(player_);
        const auto forwardXZ = glm::normalize(glm::vec3(pc.forward.x, 0, pc.forward.z));
        const auto right = glm::cross(forwardXZ, up);
        pc.targetDir = {0.0f, 0.0f, 0.0f}; // 每帧重置为0向量后再设置


        if (event.keyStates.w)
        {
            pc.targetDir += forwardXZ;
        }
        if (event.keyStates.s)
        {
            pc.targetDir -= forwardXZ;
        }
        if (event.keyStates.a)
        {
            pc.targetDir -= right;
        }
        if (event.keyStates.d)
        {
            pc.targetDir += right;
        }
        if (event.keyStates.space)
        {
            pc.targetDir += up;
        }
        if (event.keyStates.left_shift)
        {
            pc.targetDir -= up;
        }
        if (glm::length(pc.targetDir) > 0.001f)
        {
            pc.targetDir = glm::normalize(pc.targetDir);
        }

        constexpr double radius_89 = 89 * 3.14159265358979323846 / 180.0;
        // 鼠标处理
        float dx = xPos_ - event.mouseStates.x;
        float dy = yPos_ - event.mouseStates.y;
        if (dx != 0 || dy != 0)
        {
            xPos_ = event.mouseStates.x;
            yPos_ = event.mouseStates.y;
            dx *= impl::config::mouse_sensitivity;
            dy *= impl::config::mouse_sensitivity;
            pc.pitch += dy;
            pc.yaw += dx;
            if (pc.pitch > radius_89)
            {
                pc.pitch = radius_89;
            }
            else if (pc.pitch < -radius_89)
            {
                pc.pitch = -radius_89;
            }
            pc.yaw = Maths::normalizeAngle(pc.yaw);

            pc.forward = Maths::calculateForward(pc.pitch, pc.yaw);
        }

        // spdlog::debug("targetDir:({},{},{})", pc.targetDir.x, pc.targetDir.y, pc.targetDir.z);
        //spdlog::debug("pitch:{}, yaw:{}", pc.pitch, pc.yaw);
    }

  public:
    explicit PlayerSys(entt::registry& reg)
        : reg_(reg)
    {
    }
    ~PlayerSys() = default;

    void registerMove(entt::dispatcher& dp)
    {
        dp.sink<impl::events::InputState>().connect<&PlayerSys::handleInput>(this);
    }

    void update(entt::registry& reg) const
    {
        EntityComp& ec = reg.get<EntityComp>(player_);
        const PlayerComp& pc = reg.get<PlayerComp>(player_);

        ec.vel = glm::mix(ec.vel, pc.targetDir * 5.0f, 0.7f);
    }

    void create(entt::registry& reg)
    {
        const auto player = reg.create();
        TransformComp& tf = reg.emplace<TransformComp>(player);
        EntityComp& ec = reg.emplace<EntityComp>(player);
        PlayerComp& pc = reg.emplace<PlayerComp>(player);
        reg.emplace<PlayerTag>(player);

        tf.pos = {0.0f, 0.0f, 0.0f};
        ec.vel = {0.0f, 0.0f, 0.0f};
        pc.forward = {0.0f, 0.0f, -1.0f};
        pc.targetDir = {0.0f, 0.0f, 0.0f};

        player_ = player;
    }

    glm::mat4 getView(entt::registry& reg) const
    {
        const TransformComp& tf = reg.get<TransformComp>(player_);
        const PlayerComp& pc = reg.get<PlayerComp>(player_);
        return glm::gtc::lookAt(tf.pos, tf.pos + pc.forward, up);
    }

    PlayerSys(const PlayerSys&) = delete;
    PlayerSys(PlayerSys&&) = delete;
    PlayerSys& operator=(PlayerSys&) = delete;
    PlayerSys& operator=(PlayerSys&&) = delete;
};
} // namespace mc
