// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2025 ss
// 事件s
module;

export module core:Events;

namespace mc::events
{
    export struct InputState
    {
        // 当前帧所有按键的状态 作为一个事件
        struct
        {
            bool w;
            bool a;
            bool s;
            bool d;
            bool space;
            bool left_shift;
            bool left_alt;
            bool left_control;

        } keyActions;
    };


}
