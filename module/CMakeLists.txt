set(CORES
        core/App.ixx
        core/ConfigManager.ixx
        core/Init.ixx
        core/InputSystem.ixx
        core/Window.ixx
)

set(GAMES
        game/comp/TagComp.ixx
        game/comp/Comp.ixx
        game/comp/TransformComp.ixx
        game/comp/EntityComp.ixx
        game/comp/block/BlockComp.ixx
        game/comp/PlayerComp.ixx

        game/system/PlayerSys.ixx
        game/system/EntityMoveSys.ixx

        game/world/World.ixx
        game/world/RaySys.ixx
)

set(GRAPHICS
        graphics/MeshManager.ixx
        graphics/ShaderManager.ixx
        graphics/Shader.ixx
        resources/TextureManager.ixx
)

set(RESOURCES
        resources/AudioManager.ixx
)

set(UTILS
        utils/Random.ixx
        utils/Time.ixx
        utils/Config.ixx
        utils/FileManager.ixx
        utils/Math.ixx
        utils/glm_hash.ixx
)

set(THIRD_PARTY
        thirdparty/stb_image.ixx
        thirdparty/miniaudio.ixx
)


# 添加模块文件到目标
target_sources(${PROJECT_NAME}
        PUBLIC
        FILE_SET cxx_modules TYPE CXX_MODULES
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
        FILES ${CORES} ${UTILS} ${GAMES} ${GRAPHICS} ${RESOURCES} ${THIRD_PARTY}
)