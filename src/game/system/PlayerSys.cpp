module;
#include <entt/entt.hpp>
#include <glm/glm.hpp>

#include "glm/ext/matrix_transform.hpp"

module game.system.PlayerSys;
import game.comp;
import spdlog;
import core.Window;
import glfw;

namespace mc::PlayerSys
{

static entt::entity m_player = entt::null;
void createPlayer(entt::registry& reg)
{
    m_player = reg.create();
    auto& tf = reg.emplace<TransformComp>(m_player);
    auto& pc = reg.emplace<PlayerComp>(m_player);
    [[maybe_unused]] auto& ec = reg.emplace<EntityComp>(m_player);
    reg.emplace<PlayerTag>(m_player);
    // 暂时不贴可渲染

    tf.position = {0.0f, 0.0f, 0.0f};
    pc.forward = {1.0f, 0.0f, 0.0f};

    spdlog::info("玩家已创建");
}

void updateMovement(entt::registry& reg, const Window& window)
{
    auto& ec = reg.get<EntityComp>(m_player);
    const auto& pc = reg.get<PlayerComp>(m_player);
    // 玩家朝向在xz平面上的投影的方向向量
    const glm::vec3 xzForward = glm::normalize(glm::vec3(pc.forward.x, 0.0f, pc.forward.z));
    // xzForward的右方向 通过与上向量叉乘得到
    const glm::vec3 xzRight = glm::normalize(glm::cross(xzForward, glm::vec3(0.0f, 1.0f, 0.0f)));

    if (window.isKeyPressed(glfw::key_w))
    {
        ec.vel += 4.0f * xzForward;
    }
    if (window.isKeyPressed(glfw::key_s))
    {
        ec.vel += -4.0f * xzForward;
    }
    if (window.isKeyPressed(glfw::key_d))
    {
        ec.vel += 4.0f * xzRight;
    }
    if (window.isKeyPressed(glfw::key_a))
    {
        ec.vel += -4.0f * xzRight;
    }
    if (window.isKeyPressed(glfw::key_left_shift))
    {
        ec.vel += -4.0f * glm::vec3(0.0f, 1.0f, 0.0f);
    }
    if (window.isKeyPressed(glfw::key_space))
    {
        ec.vel += 4.0f * glm::vec3(0.0f, 1.0f, 0.0f);
    }
}

glm::mat4 getPlayerView(entt::registry& reg)
{
    const auto& pc = reg.get<PlayerComp>(m_player);
    const auto& tf = reg.get<TransformComp>(m_player);
    return glm::lookAt(tf.position, tf.position + pc.forward, glm::vec3(0.0f, 1.0f, 0.0f));
}

} // namespace mc