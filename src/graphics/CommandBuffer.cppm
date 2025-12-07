// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2025 ss
//
module;
#include <functional>
#include <vector>
export module graphics:CommandBuffer;

namespace mc
{
export class CommandBuffer
{
    std::vector<std::function<void()>> commands_;

  public:
    void begin()
    {
    }
    void end()
    {
    }

    // 状态命令


};
} // namespace mc