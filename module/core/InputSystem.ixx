//
// Created by ss on 2025/11/22.
//
module;
#include <unordered_map>
#include <entt/entt.hpp>

export module core.InputSystem;
import glfw;

export namespace mc
{
struct angles
{
    double pitch;
    double yaw;
};

class InputSystem
{
  public:
    void processInput(entt::registry& registry);
    static void checkExit(entt::registry& reg);

    // 删除拷贝构造和赋值操作符
    InputSystem(const InputSystem&) = delete;
    InputSystem& operator=(const InputSystem&) = delete;

    // 移动语义也删除（单例不需要）
    InputSystem(InputSystem&&) = delete;
    InputSystem& operator=(InputSystem&&) = delete;

    InputSystem() = default;
    ~InputSystem() = default;


    // 更新所有按键状态（每帧调用）
    void update(entt::registry& reg);

    // 检查按键是否刚刚按下（需要释放后重新按下）
    bool isKeyJustPressed(int key);

    // 检查按键是否按下（持续检测）
    bool isKeyDown(int key) const;

    // 检查按键是否释放
    bool isKeyReleased(int key) const;

    static void mouseCallback(glfw::window* window, double xPos, double yPos);
    static angles getPitchYaw();

    void checkToggleCursor(entt::registry& reg);

  private:
    struct KeyState
    {
        bool current = false;  // 当前帧状态
        bool previous = false; // 上一帧状态
    };

    static double lastX, lastY, pitch, yaw;
    constexpr static double sensitivity = 0.001;

    std::unordered_map<int, KeyState> m_keyStates;
};
} // namespace th