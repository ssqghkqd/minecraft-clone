module;
#include <entt/entt.hpp>

module core.Init;

import spdlog;
import utils.Time;
import utils.JsonManager;
import core.ConfigManager;
import graphics.TextureManager;
import resources.AudioManager;
import core.Window;
import core.InputSystem;
import graphics.MeshManager;
import graphics.ShaderManager;
import graphics.RenderSystem;
import game.comp;

namespace mc::Init
{
void init(entt::registry& reg)
{
    loadCore(reg);
    loadResources(reg);
    gameStatusSet(reg);
}

void loadResources(entt::registry& reg)
{
    auto& texture = reg.ctx().get<TextureManager>();
    texture.loadTexture("grass_block", "textures/grass_block.png");

}

void loadCore(entt::registry& reg)
{
    // 更新时间
    Time::init();
    spdlog::set_pattern("[%H:%M:%S][%l] - %v");
    spdlog::info("游戏开始初始化");
    // 初始化并存入注册表
    reg.ctx().emplace<Window>();
    // 输入系统不初始化
    reg.ctx().emplace<InputSystem>();
    // mesh初始化网格
    auto& meshManager = reg.ctx().emplace<MeshManager>();
    meshManager.getCubeMesh();
    // shader管理器
    auto& shaderManager = reg.ctx().emplace<ShaderManager>();
    auto& shader = shaderManager.loadShader("default", "default.vs", "default.fs");
    spdlog::info("加载着色器{}", shader.getID());
    // 初始化渲染系统 （必须放在此处，依赖shader管理器和mesh管理器）
    reg.ctx().emplace<RenderSystem>(reg);
    // 纹理系统
    reg.ctx().emplace<TextureManager>();
    // 音频系统
    reg.ctx().emplace<AudioManager>();

    reg.ctx().emplace<ConfigManager>();

}

void gameStatusSet(entt::registry& reg)
{
    // PlayerSys::createPlayer(reg);

    auto block = reg.create();
    auto& tf = reg.emplace<TransformComp>(block);
    auto& rc = reg.emplace<RenderComp>(block);
    tf.position = {0.0f, 0.0f, 0.0f};
    rc.size = {1.0f, 1.0f, 1.0f};
    rc.textureName = "grass_block";
}
}