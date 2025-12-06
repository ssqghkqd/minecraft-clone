// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2025 ss
//
module;

export module game.ecs:EntityMoveSys;
import entt;

import :EntityComp;
import :Tag;

namespace mc::EntityMoveSys
{
export void update(entt::registry& reg, float dt)
{
    static auto view = reg.view<TransformComp, EntityComp>();

    view.each([dt](TransformComp& tf, const EntityComp& ec)
              {
                  tf.pos = ec.vel * dt;
              });
}
} // namespace mc::EntityMoveSys