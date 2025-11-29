module;
module core.Init;
import entt;
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
import game.system.PlayerSys;
import game.World;

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
    auto& audio = reg.ctx().get<AudioManager>();
    auto& world = reg.ctx().get<World>();
    texture.loadTexture("grass_block", "textures/grass_block.png");
    texture.loadTexture("cobblestone", "textures/cobblestone.png");

    world.registerBlockTex(BlockType::grass_block, "grass_block");
    world.registerBlockTex(BlockType::cobblestone, "cobblestone");
    audio.loadMusic("creeper?", "musics/revenge.mp3");
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

    reg.ctx().emplace<World>();
}

void gameStatusSet(entt::registry& reg)
{
    PlayerSys::createPlayer(reg);
    auto& audio = reg.ctx().get<AudioManager>();
    auto& world = reg.ctx().get<World>();
    audio.playMusic("creeper?");

    for (int x = 0; x < 16; x++)
    {
        for (int z = 0; z < 16; z++)
        {
            world.createBlock(reg, {x, 0, z}, BlockType::grass_block);
            world.createBlock(reg, {x, -16, z}, BlockType::cobblestone);
        }
    }
    for (int y = -16; y < 0; y++)
    {
        for (int z = 0; z < 16; z++)
        {
            world.createBlock(reg, {0, y, z}, BlockType::cobblestone);
        }
    }
    for (int y = -16; y < 0; y++)
    {
        for (int x = 0; x < 16; x++)
        {
            world.createBlock(reg, {x, y, 0}, BlockType::cobblestone);
        }
    }
    for (int y = -16; y < 0; y++)
    {
        for (int z = 0; z < 16; z++)
        {
            world.createBlock(reg, {15, y, z}, BlockType::cobblestone);
        }
    }
    for (int y = -16; y < 0; y++)
    {
        for (int x = 0; x < 16; x++)
        {
            world.createBlock(reg, {x, y, 15}, BlockType::cobblestone);
        }
    }
}
} // namespace mc::Init