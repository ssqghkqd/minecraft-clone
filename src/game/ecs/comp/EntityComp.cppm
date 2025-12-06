// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2025 ss
//
module;

export module game.ecs:EntityComp;
import glm;

namespace mc
{
export struct TransformComp
{
    glm::vec3 pos{0.0f};
};

export struct EntityComp
{
    glm::vec3 vel{0.0f};
};

export struct PlayerComp
{
    glm::vec3 forward{0.0f};
    glm::vec3 targetDir{0.0f}; // 移动趋势向量
};
}