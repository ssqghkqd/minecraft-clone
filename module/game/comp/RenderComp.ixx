//
// Created by ss on 2025/11/22.
//
module;
#include <string>
#include <glm/ext.hpp>
export module game.comp:render;
export namespace mc
{
struct RenderComp
{
    std::string textureName;
    glm::vec3 size = glm::vec3(0.0f);
    glm::mat4 view = glm::mat4(0.0f);
};
} // namespace th
