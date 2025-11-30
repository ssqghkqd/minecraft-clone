# src/CMakeLists.txt

set(THIRD_PARTY_SOURCES
        thirdparty/miniaudio.cpp
        thirdparty/stb_image.cpp
)

# 合并所有源文件
set(SOURCES
        main.cpp
        ${THIRD_PARTY_SOURCES}
)
# ----------------------------------------------

# 模块接口文件
set(THIRD_PARTY
        thirdparty/entt.cppm
        thirdparty/glfw.cppm
        thirdparty/miniaudio.cppm
        thirdparty/nlohmann_json.cppm
        thirdparty/opengl.cppm
        thirdparty/spdlog.cppm
        thirdparty/stb_image.cppm
)

set(CORES
        core/App.cppm
        core/Window.cppm
        core/Init.cppm
        core/core.cppm
        core/AppLogicSys.cppm
        core/Events.cppm
        core/InputSystem.cppm
)

set(UTILS
        utils/utils.cppm
        utils/Config.cppm
        utils/FileUtils.cppm
        utils/Math.cppm
        utils/Time.cppm
        utils/Random.cppm
)

set(RESOURCES
    resources/AudioManager.cppm
        resources/TextureManager.cppm
        resources/resources.cppm
)


target_sources(${PROJECT_NAME}
        PRIVATE
        ${SOURCES}
)

target_sources(${PROJECT_NAME}
        PUBLIC
        FILE_SET cxx_modules TYPE CXX_MODULES
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/third_party/glm
        FILES ${CORES} ${UTILS} ${GAMES} ${GRAPHICS} ${RESOURCES} ${THIRD_PARTY} ../third_party/glm/glm.cppm
)

# 包含目录 - 确保头文件能被找到
target_include_directories(${PROJECT_NAME} PRIVATE
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/third_party>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/third_party/entt/src>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/third_party/spdlog/include>
)

# 编译器配置
set_target_warnings(${PROJECT_NAME})
set_cpp_standard(${PROJECT_NAME} 23)

# 链接库
target_link_libraries(${PROJECT_NAME} PRIVATE
        glfw
        glad
        -lc++
        -lc++abi
)

# 编译定义
target_compile_definitions(${PROJECT_NAME} PRIVATE
        $<$<BOOL:${APPLE}>:GL_SILENCE_DEPRECATION>
)


# 可选：为每个模块设置源码组（在IDE中更好看）
source_group("Core" FILES ${CORE_SOURCES})
source_group("Game Systems" FILES ${GAME_SOURCES})
source_group("Graphics" FILES ${GRAPHICS_SOURCES})
source_group("Utils" FILES ${UTILS_SOURCES})
source_group("Resources" FILES ${RESOURCES_SOURCES})
source_group("Main" FILES main.cpp)