//
// Created by ss on 2025/11/22.
//
module;
#include "entt/entt.hpp"
export module core.Window;
import glfw;


export namespace mc
{

class Window
{
  public:
    void init(int width, int height, const char* title);
    void shutdown();
    ~Window();

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
    Window(Window&&) = delete;
    Window& operator=(Window&&) = delete;

    bool shouldClose() const;
    void swapBuffers() const;
    void pollEvents() const;
    void close() const;
    void updateFPS();
    void toggleCursor();
    void registerWindowSizeCallBack(entt::registry& reg);

    Window();

    // 判断一个键是否按下
    bool isKeyPressed(int key) const;
    bool isKeyRelease(int key) const;

  private:
    bool m_glfwInitialized = false;
    bool m_inited = false;
    glfw::window* m_window = nullptr;
    double m_lastTime = 0.0;
    int m_frameCount = 0;
    int m_fps = 0;
    bool m_isCursorVisible = false;
    entt::registry* m_registry = nullptr;
};
} // namespace th