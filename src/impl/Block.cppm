// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2025 ss
//
module;

export module impl:Block;

namespace mc::impl
{
export enum class BlockType
{
    air,
    grass_block
};
export struct Block
{
    BlockType type = BlockType::air;
};
}