module;
#include <glm/ext.hpp>
export module game.comp:transform;

export namespace mc
{
struct TransformComp
{
    glm::vec3 position = {0.0f, 0.0f, 0.0f};
};
}