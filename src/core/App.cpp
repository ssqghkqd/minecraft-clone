module;

module core.App;
import utils.Time;
import spdlog;
import Config;
import core.Init;
import core.Window;
import core.InputSystem;
import graphics.RenderSystem;

namespace mc
{

App::App()
{
    Init::init(m_registry);
}

void App::run()
{
    mainLoop();
}

void App::mainLoop()
{
    auto& window = m_registry.ctx().get<Window>();
    auto& inputSystem = m_registry.ctx().get<InputSystem>();
    const auto& renderSystem = m_registry.ctx().get<RenderSystem>();
    auto& audio = m_registry.ctx().get<AudioManager>();

    Time::gameStart();
    spdlog::info("游戏开始");
    double lastStatTime = 0.0;
    while (!window.shouldClose())
    {
        Time::update();
        const double currentTime = Time::getTime();
        window.updateFPS();
        window.pollEvents();
        // 处理输入
        inputSystem.processInput(m_registry);
        // 更新玩家移动
        //PlayerSys::update(m_registry, (float)Time::getDeltaTime());
        // 更新所有精灵移动
        //SpriteMovementSys::update(m_registry, (float)Time::getDeltaTime());



        renderSystem.update(m_registry);
        // if (currentTime - lastStatTime >= stat_interval)
        // {
        //     update(audio);
        //     lastStatTime = currentTime; // 重置计时器
        // }

        window.swapBuffers();
    }
}

void App::update(AudioManager& audioManager)
{
    audioManager.cleanSound();
}
} // namespace th
