//
// Created by ss on 2025/11/22.
//
module;
#include <glm/glm.hpp>
#include <entt/entt.hpp>

#include "glm/ext/matrix_transform.hpp"
export module graphics.RenderSystem;
import graphics.MeshManager;
import graphics.Shader;
import game.comp;

export namespace mc
{
class RenderSystem
{
  public:
    ~RenderSystem() = default;

    void init(entt::registry& registry, int screenWidth, int screenHeight);

    void update(entt::registry& registry, const glm::mat4& viewMat) const;

    void setProjection(int width, int height);

    void renderEntity(entt::registry& registry,
                      const TransformComp& tf,
                      const RenderComp& rc,
                      const glm::mat4& view) const;


    // 删除拷贝构造和赋值操作符
    RenderSystem(const RenderSystem&) = delete;

    RenderSystem& operator=(const RenderSystem&) = delete;

    // 移动语义也删除（单例不需要）
    RenderSystem(RenderSystem&&) = delete;

    RenderSystem& operator=(RenderSystem&&) = delete;

    explicit RenderSystem(entt::registry& registry);

  private:
    glm::mat4 m_projection{};
    glm::mat4 m_orthoProjection{};
    bool inited = false;

    const Shader* m_shader = nullptr;
    const Shader* m_uiShader = nullptr;
    const MeshManager::Mesh* m_cubeMesh = nullptr;
    const MeshManager::Mesh* m_quadMesh = nullptr;
};
} // namespace mc
