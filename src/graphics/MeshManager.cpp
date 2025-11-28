module;
#include <vector>
module graphics.MeshManager;
import opengl;


namespace mc
{
const MeshManager::Mesh& MeshManager::getCubeMesh()
{
    static const Mesh quadMesh = createCubeMesh(); // 静态初始化，只创建一次
    return quadMesh;
}

// ======================= 私有方法 =======================

MeshManager::Mesh MeshManager::createCubeMesh()
{
    Mesh mesh;

    // 立方体顶点数据 (位置 + UV)
    // 每个面2个三角形，共6个面
    const std::vector<Vertex> vertices = {
        // 前面 (Z正方向)
        {{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f}}, // 左下
        {{0.5f, -0.5f, 0.5f}, {1.0f, 0.0f}},  // 右下
        {{0.5f, 0.5f, 0.5f}, {1.0f, 1.0f}},   // 右上
        {{-0.5f, 0.5f, 0.5f}, {0.0f, 1.0f}},  // 左上

        // 后面 (Z负方向)
        {{0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}},  // 右下
        {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}}, // 左下
        {{-0.5f, 0.5f, -0.5f}, {1.0f, 1.0f}},  // 左上
        {{0.5f, 0.5f, -0.5f}, {0.0f, 1.0f}},   // 右上

        // 右面 (X正方向)
        {{0.5f, -0.5f, 0.5f}, {0.0f, 0.0f}},  // 前下
        {{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}}, // 后下
        {{0.5f, 0.5f, -0.5f}, {1.0f, 1.0f}},  // 后上
        {{0.5f, 0.5f, 0.5f}, {0.0f, 1.0f}},   // 前上

        // 左面 (X负方向)
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}}, // 后下
        {{-0.5f, -0.5f, 0.5f}, {1.0f, 0.0f}},  // 前下
        {{-0.5f, 0.5f, 0.5f}, {1.0f, 1.0f}},   // 前上
        {{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f}},  // 后上

        // 上面 (Y正方向)
        {{-0.5f, 0.5f, 0.5f}, {0.0f, 0.0f}},  // 前左
        {{0.5f, 0.5f, 0.5f}, {1.0f, 0.0f}},   // 前右
        {{0.5f, 0.5f, -0.5f}, {1.0f, 1.0f}},  // 后右
        {{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f}}, // 后左

        // 下面 (Y负方向)
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}}, // 后左
        {{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}},  // 后右
        {{0.5f, -0.5f, 0.5f}, {1.0f, 1.0f}},   // 前右
        {{-0.5f, -0.5f, 0.5f}, {0.0f, 1.0f}}   // 前左
    };

    // 索引数据 - 每个面2个三角形
    const std::vector<unsigned int> indices = {
        // 前面
        0, 1, 2, 2, 3, 0,
        // 后面
        4, 5, 6, 6, 7, 4,
        // 右面
        8, 9, 10, 10, 11, 8,
        // 左面
        12, 13, 14, 14, 15, 12,
        // 上面
        16, 17, 18, 18, 19, 16,
        // 下面
        20, 21, 22, 22, 23, 20
    };

    gl::genVertexArrays(1, &mesh.vao);
    gl::genBuffers(1, &mesh.vbo);
    gl::genBuffers(1, &mesh.ebo);

    gl::bindVertexArray(mesh.vao);

    // 顶点缓冲区 (使用Vertex结构)
    gl::bindBuffer(gl::array_buffer, mesh.vbo);
    gl::bufferData(gl::array_buffer, vertices.size() * sizeof(Vertex), vertices.data(), gl::static_draw);

    // 索引缓冲区
    gl::bindBuffer(gl::element_array_buffer, mesh.ebo);
    gl::bufferData(gl::element_array_buffer, indices.size() * sizeof(unsigned int), indices.data(), gl::static_draw);

    // 位置属性 (属性索引0)
    gl::vertexAttribPointer(0, 3, gl::FLOAT, gl::FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
    gl::enableVertexAttribArray(0);

    // UV属性 (属性索引1)
    gl::vertexAttribPointer(1, 2, gl::FLOAT, gl::FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
    gl::enableVertexAttribArray(1);

    gl::bindVertexArray(0);
    mesh.indexCount = static_cast<int>(indices.size());

    return mesh;
}

MeshManager::~MeshManager()
{
    // 清理所有网格资源
    for (auto& [key, meshPtr] : m_meshes)
    {
        if (meshPtr->vao)
            gl::deleteVertexArrays(1, &meshPtr->vao);
        if (meshPtr->vbo)
            gl::deleteBuffers(1, &meshPtr->vbo);
        if (meshPtr->ebo)
            gl::deleteBuffers(1, &meshPtr->ebo);
    }
}
} // namespace th