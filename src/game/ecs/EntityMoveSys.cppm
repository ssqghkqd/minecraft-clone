// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2025 ss
//
module;

export module game.ecs:EntityMoveSys;
import entt;

import :EntityComp;
import :Tag;
import spdlog;

namespace mc::EntityMoveSys
{
export void update(entt::registry& reg, float dt)
{
    static auto view = reg.view<TransformComp, EntityComp>();

    view.each([dt](TransformComp& tf, const EntityComp& ec)
              {
                  tf.pos += ec.vel * dt;
                  //spdlog::debug("玩家位置({},{},{})", tf.pos.x, tf.pos.y, tf.pos.z);
              });
}
} // namespace mc::EntityMoveSys