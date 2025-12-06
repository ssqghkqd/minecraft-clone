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

namespace mc
{

export class PlayerSys
{
  private:
    entt::entity player_{entt::null};
    entt::registry& reg_;

  public:
    explicit PlayerSys(entt::registry& reg)
        : reg_(reg)
    {
    }
    ~PlayerSys() = default;

    void registerMove(entt::dispatcher& dp)
    {
        dp.sink<impl::events::InputState>().connect<&PlayerSys::updatePlayerDir>(this);
    }

    void update(entt::registry& reg) const
    {
        EntityComp& ec = reg.get<EntityComp>(player_);
        const PlayerComp& pc = reg.get<PlayerComp>(player_);
        const float targetSpeed = glm::length(pc.targetDir) * 5.0f;

        ec.vel = glm::clamp(ec.vel, targetSpeed, 0.7f);
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

    void updatePlayerDir(const impl::events::InputState& event) const
    {
        PlayerComp& pc = reg_.get<PlayerComp>(player_);

        constexpr glm::vec3 up = {0.0f, 1.0f, 0.0f};
        const auto right = glm::cross(pc.forward, up);
        pc.targetDir = {0.0f, 0.0f, 0.0f}; // 每帧重置为0向量后再设置

        if (event.keyActions.w)
        {
            pc.targetDir += pc.forward;
        }
        if (event.keyActions.s)
        {
            pc.targetDir -= pc.forward;
        }
        if (event.keyActions.a)
        {
            pc.targetDir -= right;
        }
        if (event.keyActions.d)
        {
            pc.targetDir += right;
        }
        if (event.keyActions.space)
        {
            pc.targetDir += up;
        }
        if (event.keyActions.left_shift)
        {
            pc.targetDir -= up;
        }

        pc.targetDir = glm::normalize(pc.targetDir);
    }

    PlayerSys(const PlayerSys&) = delete;
    PlayerSys(PlayerSys&&) = delete;
    PlayerSys& operator=(PlayerSys&) = delete;
    PlayerSys& operator=(PlayerSys&&) = delete;
};
} // namespace mc
