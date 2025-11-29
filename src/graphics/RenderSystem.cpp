module;
#include <entt/entt.hpp>
#include <glm/ext.hpp>
module graphics.RenderSystem;
import Config;
import spdlog;
import opengl;
import game.comp;
import graphics.ShaderManager;
import graphics.TextureManager;

namespace mc
{

RenderSystem::RenderSystem(entt::registry& registry)
{
    init(registry, window_width, window_height);
}

void RenderSystem::init(entt::registry& registry, const int screenWidth, const int screenHeight)
{
    if (inited)
    {
        spdlog::warn("RenderSystem already initialized");
        return;
    }

    auto& shaderManager = registry.ctx().get<ShaderManager>();
    m_shader = &shaderManager.getShader("default");
    m_uiShader = &shaderManager.getShader("ui");

    auto& meshManager = registry.ctx().get<MeshManager>();
    m_cubeMesh = &meshManager.getCubeMesh();
    m_quadMesh = &meshManager.getQuadMesh();

    // 设置OpenGL状态
    gl::enable(gl::depth_test);
    gl::enable(gl::cull_face);

    spdlog::debug("OPENGL 状态设置完成");

    setProjection(screenWidth, screenHeight);

    gl::clearColor(0.53f, 0.81f, 0.98f, 1.0f);
    spdlog::info("渲染系统初始化完成");
    inited = true;
}

void RenderSystem::setProjection(int width, int height)
{
    const float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
    m_projection = glm::perspective(
        glm::radians(90.0f), // 视野角度
        aspectRatio,         // 宽高比
        0.1f,                // 近平面
        100.0f               // 远平面
    );

    m_orthoProjection = glm::ortho(0.0f, (float)width, (float)height, 0.0f, -1.0f, 1.0f);

    // 更新着色器
    m_shader->use();
    m_shader->set("projection", m_projection);
    m_uiShader->set("projection", m_orthoProjection);
}

void RenderSystem::renderEntity(entt::registry& registry,
                                const TransformComp& tf,
                                const RenderComp& rc,
                                const glm::mat4& view) const
{
    auto model = glm::mat4(1.0f);
    model = glm::translate(model, tf.position);

    m_shader->use();
    m_shader->set("model", model);
    m_shader->set("view", view);
    m_shader->set("projection", m_projection);

    const MeshManager::Mesh* mesh = m_cubeMesh;

    // TODO 优化批处理
    if (!rc.textureName.empty())
    {
        m_shader->set("Texture", 0);
        gl::activeTexture(gl::texture0);
        registry.ctx().get<TextureManager>().bind(rc.textureName);
    }

    // TODO 这里可以用实例化渲染 但目前还是不用并且我不知道实例化渲染需要准备什么（
    gl::bindVertexArray(mesh->vao);
    gf::drawElements(gl::triangles, mesh->indexCount, gl::unsigned_int, nullptr);
}

void RenderSystem::update(entt::registry& registry, const glm::mat4& viewMat) const
{
    gl::clear(gl::color_buffer_bit | gl::depth_buffer_bit);

    const auto view = registry.view<TransformComp, RenderComp>();
    view.each([&registry, this, viewMat](const TransformComp& tf, const RenderComp& rc)
              {
                  renderEntity(registry, tf, rc, viewMat);
              });
}

} // namespace mc