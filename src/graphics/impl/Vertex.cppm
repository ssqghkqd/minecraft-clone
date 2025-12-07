// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2025 ss
//
module;
#include <array>
export module impl:Vertex;
import glm;

namespace mc::impl::graphics
{
export struct Vertex
{
    glm::vec3 position;
    glm::vec2 texCoord;
};

export constexpr std::array normals = {
    glm::ivec3(0, 0, 1),   // 朝前
    glm::ivec3(0, 0, -1),  // 朝后
    glm::ivec3(1, 0, 0),   // 朝右
    glm::ivec3(-1, 0, 0),  // 朝左
    glm::ivec3(0, 1, 0),   // 朝上
    glm::ivec3(0, -1, 0)}; // 朝下

export
{
    // 北面 (North) - z = 1.0，外法线(0,0,1)
    // 从外部看（北面外部，即z>1），顶点顺序为逆时针
    constexpr std::array<Vertex, 6> north_face = {{
        {{0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}}, // 左下
        {{0.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}, // 左上
        {{1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}}, // 右上
        {{0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}}, // 左下
        {{1.0f, 0.0f, 1.0f}, {1.0f, 0.0f}}, // 右下
        {{1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}}  // 右上
    }};

    // 南面 (South) - z = 0.0，外法线(0,0,-1)
    // 从外部看（南面外部，即z<0），顶点顺序为逆时针
    constexpr std::array<Vertex, 6> south_face = {{
        {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}, // 左下
        {{0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}}, // 左上
        {{1.0f, 1.0f, 0.0f}, {1.0f, 1.0f}}, // 右上
        {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}, // 左下
        {{1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}}, // 右下
        {{1.0f, 1.0f, 0.0f}, {1.0f, 1.0f}}  // 右上
    }};

    // 东面 (East) - x = 1.0，外法线(1,0,0)
    // 从外部看（东面外部，即x>1），顶点顺序为逆时针
    // 注意：从东边看，纹理的x方向对应z轴，y方向对应y轴
    constexpr std::array<Vertex, 6> east_face = {{
        {{1.0f, 0.0f, 1.0f}, {0.0f, 0.0f}}, // 左下 (北下)
        {{1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}, // 左上 (北上)
        {{1.0f, 1.0f, 0.0f}, {1.0f, 1.0f}}, // 右上 (南上)
        {{1.0f, 0.0f, 1.0f}, {0.0f, 0.0f}}, // 左下
        {{1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}}, // 右下 (南下)
        {{1.0f, 1.0f, 0.0f}, {1.0f, 1.0f}}  // 右上
    }};

    // 西面 (West) - x = 0.0，外法线(-1,0,0)
    // 从外部看（西面外部，即x<0），顶点顺序为逆时针
    constexpr std::array<Vertex, 6> west_face = {{
        {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}, // 左下 (南下)
        {{0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}}, // 左上 (南上)
        {{0.0f, 1.0f, 1.0f}, {1.0f, 1.0f}}, // 右上 (北上)
        {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}, // 左下
        {{0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}}, // 右下 (北下)
        {{0.0f, 1.0f, 1.0f}, {1.0f, 1.0f}}  // 右上
    }};

    // 上面 (Top) - y = 1.0，外法线(0,1,0)
    // 从外部看（上面外部，即y>1），顶点顺序为逆时针
    // 纹理：x对应x轴，z对应y轴
    constexpr std::array<Vertex, 6> top_face = {{
        {{0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}}, // 左下 (西南)
        {{0.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}, // 左上 (西北)
        {{1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}}, // 右上 (东北)
        {{0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}}, // 左下
        {{1.0f, 1.0f, 0.0f}, {1.0f, 0.0f}}, // 右下 (东南)
        {{1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}}  // 右上
    }};

    // 下面 (Bottom) - y = 0.0，外法线(0,-1,0)
    // 从外部看（下面外部，即y<0），顶点顺序为逆时针
    constexpr std::array<Vertex, 6> bottom_face = {{
        {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}, // 左下 (西南)
        {{0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}}, // 左上 (西北)
        {{1.0f, 0.0f, 1.0f}, {1.0f, 1.0f}}, // 右上 (东北)
        {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}, // 左下
        {{1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}}, // 右下 (东南)
        {{1.0f, 0.0f, 1.0f}, {1.0f, 1.0f}}  // 右上
    }};

    constexpr std::array vertices = {north_face, south_face, east_face, west_face, top_face, bottom_face};
}
} // namespace mc::impl