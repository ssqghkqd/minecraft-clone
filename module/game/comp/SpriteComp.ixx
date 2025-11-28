//
// Created by ss on 2025/11/22.
//

module;
#include <glm/ext.hpp>
export module game.comp:sprite;

export namespace mc
{
struct SpriteComp
{
    glm::vec3 velocity = glm::vec3(0.0f);
};
} // namespace th