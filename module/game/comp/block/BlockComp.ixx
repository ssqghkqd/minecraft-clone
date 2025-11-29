module;
#include "glm/vec3.hpp"
export module game.comp:block;


export namespace mc
{
enum class BlockType
{
    grass_block,
    cobblestone,
    planks
};
enum class BlockError {
    already_exists,
    out_of_bounds,
    invalid_block
};
struct BlockComp
{
    BlockType blockType;
    glm::ivec3 pos = glm::ivec3(0);
};
}