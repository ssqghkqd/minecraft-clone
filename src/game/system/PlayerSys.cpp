module;
#include <entt/entt.hpp>
#include <glm/glm.hpp>

#include "glm/ext/matrix_transform.hpp"
module game.system.PlayerSys;
import game.comp;
import spdlog;
import core.Window;
import glfw;
import core.InputSystem;
import utils.maths;
import game.RaySys;
import game.World;

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
    auto& pc = reg.get<PlayerComp>(m_player);
    // 玩家朝向在xz平面上的投影的方向向量
    const glm::vec3 xzForward = glm::normalize(glm::vec3(pc.forward.x, 0.0f, pc.forward.z));
    // xzForward的右方向 通过与上向量叉乘得到
    const glm::vec3 xzRight = glm::normalize(glm::cross(xzForward, glm::vec3(0.0f, 1.0f, 0.0f)));

    pc.dir = glm::vec3(0.0f);
    if (window.isKeyPressed(glfw::key_w))
    {
        pc.dir += xzForward;
    }
    if (window.isKeyPressed(glfw::key_s))
    {
        pc.dir -= xzForward;
    }
    if (window.isKeyPressed(glfw::key_d))
    {
        pc.dir += xzRight;
    }
    if (window.isKeyPressed(glfw::key_a))
    {
        pc.dir -= xzRight;
    }
    if (window.isKeyPressed(glfw::key_left_shift))
    {
        pc.dir += glm::vec3(0.0f, -1.0f, 0.0f);
    }
    if (window.isKeyPressed(glfw::key_space))
    {
        pc.dir += glm::vec3(0.0f, 1.0f, 0.0f);
    }

    if (glm::length(pc.dir) > 0.0f)
    {
        pc.dir = glm::normalize(pc.dir);
    }
}

void update(entt::registry& reg)
{
    auto& ec = reg.get<EntityComp>(m_player);
    auto& pc = reg.get<PlayerComp>(m_player);
    const auto targetVel = 20.0f * pc.dir;
    auto [pitch, yaw] = InputSystem::getPitchYaw();

    ec.vel = glm::mix(ec.vel, targetVel, 0.7f);
    pc.forward = Maths::calculateForward(pitch, yaw);
}

glm::mat4 getPlayerView(entt::registry& reg)
{
    const auto& pc = reg.get<PlayerComp>(m_player);
    const auto& tf = reg.get<TransformComp>(m_player);
    return glm::lookAt(tf.position, tf.position + pc.forward, glm::vec3(0.0f, 1.0f, 0.0f));
}

void placeBlock(entt::registry& reg)
{
    const auto& tf = reg.get<TransformComp>(m_player);
    const auto& pc = reg.get<PlayerComp>(m_player);

    auto& world = reg.ctx().get<World>();
    RaySys::Ray ray;
    ray.start = tf.position;
    ray.direction = pc.forward;
    const auto hitResult = RaySys::checkRayHit(ray, world);
    if (hitResult.has_value())
    {
        world.createBlock(reg, hitResult->hitPos + hitResult->normal, BlockType::planks);
    }
}
void destroyBlock(entt::registry& reg)
{
    const auto& tf = reg.get<TransformComp>(m_player);
    const auto& pc = reg.get<PlayerComp>(m_player);

    auto& world = reg.ctx().get<World>();
    RaySys::Ray ray;
    ray.start = tf.position;
    ray.direction = pc.forward;
    const auto hitResult = RaySys::checkRayHit(ray, world);
    if (hitResult.has_value())
    {
        world.destroyBlock(reg, hitResult->hitPos);
    }
}

} // namespace mc::PlayerSys