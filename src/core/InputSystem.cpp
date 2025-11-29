module;
#include <entt/entt.hpp>

module core.InputSystem;
import core.Window;
import glfw;
import game.system.PlayerSys;
import Config;
import utils.maths;

namespace mc
{
double InputSystem::lastX = window_width * 0.5;
double InputSystem::lastY = window_height * 0.5;
double InputSystem::pitch = 0.0;
double InputSystem::yaw = 0.0;

// 89度对应的弧度制
constexpr double radius_89 = 89 * 3.14159265358979323846 / 180.0;

InputSystem::InputSystem(entt::registry& reg)
{
    m_registry = &reg;
}

void InputSystem::processInput(entt::registry& registry)
{
    // 检查是否退出
    checkExit(registry);
    PlayerSys::updateMovement(registry, registry.ctx().get<Window>());
    checkToggleCursor(registry);
    update(registry);
}

void InputSystem::checkExit(entt::registry& reg)
{
    const auto& window = reg.ctx().get<Window>();
    if (window.isKeyPressed(glfw::key_escape))
    {
        window.close();
    }
}
void InputSystem::checkToggleCursor(entt::registry& reg)
{
    if (isKeyJustPressed(glfw::key_left_alt))
    {
        reg.ctx().get<Window>().toggleCursor();
    }
}

void InputSystem::update(entt::registry& reg)
{
    const auto& window = reg.ctx().get<Window>();
    // 更新所有按键状态
    for (auto& [key, state] : m_keyStates)
    {
        state.previous = state.current;
        state.current = window.isKeyPressed(key);
    }
}

bool InputSystem::isKeyJustPressed(int key)
{
    // 确保按键已注册
    if (!m_keyStates.contains(key))
    {
        m_keyStates[key] = {false, false};
    }

    const auto& state = m_keyStates[key];
    return state.current && !state.previous;
}

bool InputSystem::isKeyDown(int key) const
{
    const auto it = m_keyStates.find(key);
    return it != m_keyStates.end() && it->second.current;
}

bool InputSystem::isKeyReleased(int key) const
{
    const auto it = m_keyStates.find(key);
    return it != m_keyStates.end() && !it->second.current;
}

void InputSystem::mouseCallback([[maybe_unused]] glfw::window* window, double xPos, double yPos)
{
    // 必须有这个第一个参数 glfw要求 但不加maybe编译器报错
    double offsetX = xPos - lastX;
    double offsetY = yPos - lastY;
    lastX = xPos;
    lastY = yPos;
    offsetX *= sensitivity;
    offsetY *= sensitivity;
    pitch -= offsetY; // Y轴反转
    yaw -= offsetX;
    if (pitch > radius_89)
    {
        pitch = radius_89;
    }
    if (pitch < -radius_89)
    {
        pitch = -radius_89;
    }
    // 限制在[0,2pi)
    yaw = Maths::normalizeAngle(yaw);
}

angles InputSystem::getPitchYaw()
{
    return {pitch, yaw};
}

void InputSystem::mouseButtonCallback([[maybe_unused]]glfw::window* window, int button, int action, [[maybe_unused]]int mods)
{
    if (button == glfw::mouse_button_left && action == glfw::press)
    {
        PlayerSys::destroyBlock(*m_registry);
    }
    if (button == glfw::mouse_button_right && action == glfw::press)
    {
        PlayerSys::placeBlock(*m_registry);
    }
}

} // namespace mc
